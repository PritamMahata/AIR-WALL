import React, { useState } from 'react';

const WifiJsonGenerator = () => {
  const [wifiName, setWifiName] = useState('');
  const [wifiPassword, setWifiPassword] = useState('');

  const generateJson = () => {
    if (!wifiName || !wifiPassword) {
      alert('Please fill in both fields.');
      return;
    }

    const wifiData = {
      wifiName,
      wifiPassword,
    };

    const blob = new Blob([JSON.stringify(wifiData, null, 2)], { type: 'application/json' });
    const url = URL.createObjectURL(blob);

    const link = document.createElement('a');
    link.href = url;
    link.download = 'wifi_data.json';
    link.click();

    URL.revokeObjectURL(url);
  };

  return (
    <div className="min-h-screen flex items-center justify-center bg-gradient-to-r from-blue-100 to-purple-200 p-4 w-full">
      <div className="bg-white shadow-2xl rounded-2xl p-8 max-w-md w-full transition-transform transform hover:scale-105">
        <h2 className="text-2xl font-bold text-gray-800 mb-6 text-center">📶 Wi-Fi JSON Generator</h2>

        <div className="mb-4">
          <label htmlFor="wifiName" className="block text-gray-700 font-medium mb-1">Wi-Fi Name</label>
          <input
            type="text"
            id="wifiName"
            placeholder="Enter Wi-Fi Name"
            value={wifiName}
            onChange={(e) => setWifiName(e.target.value)}
            className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-400"
          />
        </div>

        <div className="mb-6">
          <label htmlFor="wifiPassword" className="block text-gray-700 font-medium mb-1">Wi-Fi Password</label>
          <input
            type="password"
            id="wifiPassword"
            placeholder="Enter Wi-Fi Password"
            value={wifiPassword}
            onChange={(e) => setWifiPassword(e.target.value)}
            className="w-full px-4 py-2 border border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-400"
          />
        </div>

        <button
          onClick={generateJson}
          className="w-full bg-blue-500 text-white font-semibold py-2 px-4 rounded-lg hover:bg-blue-600 active:bg-blue-700 transition duration-200"
        >
          Generate JSON & Download ⬇️
        </button>
      </div>
    </div>
  );
};

export default WifiJsonGenerator;
