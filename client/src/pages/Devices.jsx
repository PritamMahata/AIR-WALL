import { useState } from "react";
import { RefreshCw, Power, Wifi, ShieldCheck } from "lucide-react";

const devicesList = [
  { id: 1, name: "ESP32-CAM", status: "Online", ip: "192.168.1.10" },
  { id: 2, name: "ESP32-Sensor", status: "Offline", ip: "192.168.1.12" },
  { id: 3, name: "ESP32-Security", status: "Online", ip: "192.168.1.14" },
];

const Devices = () => {
  const [devices, setDevices] = useState(devicesList);

  return (
    <div className="bg-white dark:bg-gray-800 text-gray-900 dark:text-white p-6 rounded-lg shadow-md w-306">
      <h2 className="text-2xl font-bold mb-4">Connected Devices</h2>
      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-4">
        {devices.map((device) => (
          <div
            key={device.id}
            className={`p-4 rounded-lg shadow-lg ${
              device.status === "Online"
                ? "bg-green-100 dark:bg-green-800"
                : "bg-red-100 dark:bg-red-800"
            }`}
          >
            <div className="flex justify-between">
              <h3 className="text-lg font-semibold">{device.name}</h3>
              {device.status === "Online" ? (
                <ShieldCheck className="text-green-500" size={20} />
              ) : (
                <Power className="text-red-500" size={20} />
              )}
            </div>
            <p className="mt-2 text-sm">IP: {device.ip}</p>
            <p className="mt-1 text-sm">
              Status:{" "}
              <span
                className={`font-bold ${
                  device.status === "Online" ? "text-green-600" : "text-red-600"
                }`}
              >
                {device.status}
              </span>
            </p>
          </div>
        ))}
      </div>
    </div>
  );
};

export default Devices;
