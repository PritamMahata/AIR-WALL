import React from "react";
import { FiWifi, FiAlertTriangle, FiCheckCircle } from "react-icons/fi";

function Dashboard() {
  return (
    <div className="p-6 w-304">
      {/* Dashboard Header */}

      {/* Status Cards */}
      <div className="grid grid-cols-1 sm:grid-cols-3 gap-6">
        {/* Connected Devices Card */}
        <div className="p-6 bg-white dark:bg-gray-800 shadow-lg rounded-xl flex items-center space-x-4 border-b-4 border-blue-500 transition-all hover:scale-105">
          <FiWifi className="text-blue-500 text-3xl" />
          <div>
            <p className="text-gray-500 dark:text-gray-300 text-sm">Connected Devices</p>
            <h2 className="text-2xl font-semibold text-gray-900 dark:text-white">10 Connected</h2>
          </div>
        </div>

        {/* Threats Detected Card */}
        <div className="p-6 bg-white dark:bg-gray-800 shadow-lg rounded-xl flex items-center space-x-4 border-b-4 border-red-500 transition-all hover:scale-105">
          <FiAlertTriangle className="text-red-500 text-3xl" />
          <div>
            <p className="text-gray-500 dark:text-gray-300 text-sm">Threats Detected</p>
            <h2 className="text-2xl font-semibold text-gray-900 dark:text-white">3 Detected</h2>
          </div>
        </div>

        {/* System Status Card */}
        <div className="p-6 bg-white dark:bg-gray-800 shadow-lg rounded-xl flex items-center space-x-4 border-b-4 border-green-500 transition-all hover:scale-105">
          <FiCheckCircle className="text-green-500 text-3xl" />
          <div>
            <p className="text-gray-500 dark:text-gray-300 text-sm">System Status</p>
            <h2 className="text-2xl font-semibold text-gray-900 dark:text-white">Stable</h2>
          </div>
        </div>
      </div>
    </div>
  );
};

export default Dashboard;
