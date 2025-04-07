import { useState } from "react";
import { Bell } from "lucide-react";

const logsList = [
  { id: 1, message: "Intrusion detected", type: "Alert", timestamp: "12:45 PM" },
  { id: 2, message: "New device connected", type: "Info", timestamp: "11:30 AM" },
  { id: 3, message: "ESP32 rebooted", type: "Warning", timestamp: "10:15 AM" },
  { id: 4, message: "ESP32 rebooted", type: "Warning", timestamp: "10:15 AM" },
];

function SecurityLogs() {
  const [logs, setLogs] = useState(logsList);
  const [filter, setFilter] = useState("All");

  const filteredLogs = logs.filter(
    (log) => filter === "All" || log.type === filter
  );

  // Function to return icon color based on type
  const getIconColor = (type) => {
    switch (type) {
      case "Alert":
        return "text-red-500";
      case "Warning":
        return "text-yellow-500";
      case "Info":
        return "text-blue-500";
      default:
        return "text-gray-500";
    }
  };

  return (
    <div className="bg-white dark:bg-gray-900 text-gray-900 dark:text-white p-4 sm:p-6 md:p-8 rounded-lg shadow-md w-full max-w-7xl mx-auto">
      <h2 className="text-2xl font-bold mb-6 text-center sm:text-left">Security Logs</h2>

      <div className="flex flex-col sm:flex-row sm:justify-between sm:items-center gap-4 mb-6">
        <h3 className="text-lg font-semibold">Recent Activity</h3>
        <select
          className="bg-gray-200 dark:bg-gray-700 text-sm p-2 rounded-md w-full sm:w-auto"
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
          <div
            key={log.id}
            className="p-4 rounded-lg shadow-md bg-gray-100 dark:bg-gray-800 transition-all"
          >
            <div className="flex justify-between items-center">
              <span className="font-medium">{log.message}</span>
              <Bell className={`${getIconColor(log.type)}`} size={20} />
            </div>
            <p className="text-sm mt-2">{log.timestamp}</p>
          </div>
        ))}
      </div>
    </div>
  );
}

export default SecurityLogs;
