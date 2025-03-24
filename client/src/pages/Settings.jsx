import { useState } from "react";
import { ToggleLeft, ToggleRight, Wifi, Lock } from "lucide-react";

function Settings() {
  const [autoLock, setAutoLock] = useState(true);
  const [wifiEnabled, setWifiEnabled] = useState(true);

  return (
    <div className="bg-white dark:bg-gray-800 text-gray-900 dark:text-white p-6 rounded-lg shadow-md w-306">
      <h2 className="text-2xl font-bold mb-4">Security Settings</h2>
      
      <div className="p-4 bg-gray-100 dark:bg-gray-700 rounded-lg mb-4">
        <div className="flex justify-between items-center">
          <span className="text-lg font-medium">Enable Auto-Lock</span>
          <button onClick={() => setAutoLock(!autoLock)}>
            {autoLock ? <ToggleRight size={30} className="text-green-500" /> : <ToggleLeft size={30} className="text-red-500" />}
          </button>
        </div>
      </div>

      <div className="p-4 bg-gray-100 dark:bg-gray-700 rounded-lg">
        <div className="flex justify-between items-center">
          <span className="text-lg font-medium">Enable WiFi</span>
          <button onClick={() => setWifiEnabled(!wifiEnabled)}>
            {wifiEnabled ? <Wifi size={30} className="text-green-500" /> : <Lock size={30} className="text-red-500" />}
          </button>
        </div>
      </div>
    </div>
  );
};

export default Settings;
