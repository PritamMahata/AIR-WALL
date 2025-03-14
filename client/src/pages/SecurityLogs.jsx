import { useState } from "react";
import { Bell, Filter } from "lucide-react";

const logsList = [
  { id: 1, message: "Intrusion detected", type: "Alert", timestamp: "12:45 PM" },
  { id: 2, message: "New device connected", type: "Info", timestamp: "11:30 AM" },
  { id: 3, message: "ESP32 rebooted", type: "Warning", timestamp: "10:15 AM" },
];

const SecurityLogs = () => {
  const [logs, setLogs] = useState(logsList);
  const [filter, setFilter] = useState("All");

  const filteredLogs = logs.filter(
    (log) => filter === "All" || log.type === filter
  );

  return (
    <div className="bg-white dark:bg-gray-800 text-gray-900 dark:text-white p-6 rounded-lg shadow-md w-306">
      <h2 className="text-2xl font-bold mb-4">Security Logs</h2>

      <div className="flex justify-between mb-4">
        <h3 className="text-lg">Recent Activity</h3>
        <select
          className="bg-gray-200 dark:bg-gray-700 p-2 rounded-md"
          onChange={(e) => setFilter(e.target.value)}
        >
          <option>All</option>
          <option>Alert</option>
          <option>Info</option>
          <option>Warning</option>
        </select>
      </div>

      <div className="space-y-4">
        {filteredLogs.map((log) => (
          <div key={log.id} className="p-4 rounded-lg shadow-md bg-gray-100 dark:bg-gray-700">
            <div className="flex justify-between">
              <span className="font-medium">{log.message}</span>
              <Bell className={`text-${log.type === "Alert" ? "red" : log.type === "Warning" ? "yellow" : "blue"}-500`} size={20} />
            </div>
            <p className="text-sm mt-2">{log.timestamp}</p>
          </div>
        ))}
      </div>
    </div>
  );
};

export default SecurityLogs;
