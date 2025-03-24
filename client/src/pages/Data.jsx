import { useEffect, useState } from "react";

const Data = () => {
    const [ws, setWs] = useState(null);
    const [data, setData] = useState({ temperature: 0, humidity: 0 });
    const [ledState, setLedState] = useState(false);
    const [ip, setIP] = useState("192.168.32.120");
    useEffect(() => {
        const socket = new WebSocket(`ws://${ip}/ws`); // Change to ESP32 IP
        setWs(socket);

        socket.onmessage = (event) => {
            const receivedData = JSON.parse(event.data);
            setData(receivedData);
            console.log(receivedData);

        };

        return () => socket.close();
    }, []);

    const toggleLED = () => {
        // if (ws) {
        //     ws.send(JSON.stringify({ command: "toggle_led", state: ledState ? 0 : 1 }));
        //     setLedState(!ledState);
        // }
        


    };

    return (
        <div className="p-4 bg-gray-900 text-white">
            <h1 className="text-2xl mb-4">ESP32 IoT Dashboard</h1>
            <p>🌡️ Temperature: {data.temperature} °C</p>
            <p>💧 Humidity: {data.humidity} %</p>
            <button onClick={toggleLED} className="mt-4 p-2 bg-blue-500 rounded text-black">
                {ledState ? "Turn Off LED" : "Turn On LED"}
            </button>
        </div>
    );
};

export default Data;
