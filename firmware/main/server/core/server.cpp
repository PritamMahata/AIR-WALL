#include "server.h"
#include "../api/api_handler.h"
#include "../encryptor.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");  // WebSocket endpoint

// Store clients
void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
                      AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        Serial.printf("📡 WebSocket Client #%u connected\n", client->id());
        client->text("✅ Connected to ESP32 WebSocket");
    } else if (type == WS_EVT_DISCONNECT) {
        Serial.printf("❌ WebSocket Client #%u disconnected\n", client->id());
    } else if (type == WS_EVT_DATA) {
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
            String encryptedMsg = String((char *)data);
            String decrypted = decryptAES(encryptedMsg, AES_KEY);
            Serial.printf("🔓 Decrypted from client: %s\n", decrypted.c_str());

            // Echo back encrypted response
            String response = "{\"status\":\"Online\"}";
            String encryptedResponse = encryptAES(response, AES_KEY);
            client->text(encryptedResponse);
        }
    }
}

void broadcastEncrypted(const String &message) {
    String encrypted = encryptAES(message, AES_KEY);
    ws.textAll(encrypted);
}

void startServer() {
    setupAPI(server);  // existing HTTP API

    // WebSocket setup
    ws.onEvent(onWebSocketEvent);
    server.addHandler(&ws);

    server.begin();
    Serial.println("🚀 Web Server + WebSocket Started!");
}
