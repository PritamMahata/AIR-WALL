import { useState, useEffect } from "react";
import { io } from "socket.io-client";

const useWebSocket = (serverUrl) => {
  const [data, setData] = useState(null);
  const [isConnected, setIsConnected] = useState(false);

  useEffect(() => {
    const socket = io(serverUrl);

    socket.on("connect", () => {
      setIsConnected(true);
      console.log("Connected to ESP32 WebSocket server");
    });

    socket.on("message", (message) => {
      console.log("Received:", message);
      setData(message);
    });

    socket.on("disconnect", () => {
      setIsConnected(false);
      console.log("Disconnected from WebSocket server");
    });

    return () => {
      socket.disconnect();
    };
  }, [serverUrl]);

  return { data, isConnected };
};

export default useWebSocket;
