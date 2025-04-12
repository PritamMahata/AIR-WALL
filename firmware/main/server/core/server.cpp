#include "server.h"
#include "../api/api_handler.h"
#include "../encryptor.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/"); // WebSocket endpoint

// WebSocket Event Handler
void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
                      AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        IPAddress clientIP = client->remoteIP();
        Serial.printf("📡 WebSocket Client #%u connected from IP: %s\n", client->id(), clientIP.toString().c_str());
        client->text("✅ Connected to ESP32 WebSocket");
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.printf("❌ WebSocket Client #%u disconnected\n", client->id());
    }
    else if (type == WS_EVT_DATA)
    {
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
        {
            String encryptedMsg = String((char *)data);
            String decrypted = decryptAES(encryptedMsg, AES_KEY);
            Serial.printf("🔓 Decrypted from client #%u: %s\n", client->id(), decrypted.c_str());

            DynamicJsonDocument doc(128);
            DeserializationError err = deserializeJson(doc, decrypted);
            if (!err)
            {
                String cmd = doc["command"] | "";
                if (cmd == "led")
                {
                    String action = doc["action"] | "";
                    if (action == "on")
                    {
                        digitalWrite(2, HIGH);
                        client->text(encryptAES("{\"status\":\"LED is ON\"}", AES_KEY));
                    }
                    else if (action == "off")
                    {
                        digitalWrite(2, LOW);
                        client->text(encryptAES("{\"status\":\"LED is OFF\"}", AES_KEY));
                    }
                    else
                    {
                        client->text(encryptAES("{\"error\":\"Invalid action\"}", AES_KEY));
                    }
                }
                else
                {
                    client->text(encryptAES("{\"error\":\"Unknown command\"}", AES_KEY));
                }
            }
            else
            {
                client->text(encryptAES("{\"error\":\"JSON parse error\"}", AES_KEY));
            }
        }
    }
}

// Broadcast Encrypted Message to All Clients
void broadcastEncrypted(const String &message)
{
    String encrypted = encryptAES(message, AES_KEY);
    ws.textAll(encrypted);
}

// Broadcast JSON Message
void broadcastJson(const DynamicJsonDocument &doc)
{
    String json;
    serializeJson(doc, json);
    broadcastEncrypted(json);
}

// Start Server
void startServer()
{
    setupAPI(server); // REST API setup

    // WebSocket setup
    ws.onEvent(onWebSocketEvent);
    server.addHandler(&ws);

    server.begin();
    Serial.println("🚀 Web Server + WebSocket Started!");
}
