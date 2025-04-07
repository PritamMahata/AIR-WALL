import React from 'react';
import {
  BarChart, Bar, XAxis, YAxis, CartesianGrid, Tooltip, ResponsiveContainer,
  LineChart, Line, PieChart, Pie, Cell, Legend
} from 'recharts';
import { Cpu, MemoryStick, HardDrive, Wifi, Shield, Users, AlertTriangle } from 'lucide-react';

const wirelessData = [
  { name: 'Clients', value: 40 },
  { name: 'Unassociated', value: 25 },
  { name: 'Access Point', value: 80 },
  { name: 'Out of Range', value: 15 }
];

const encryptionData = [
  { name: 'WEP', value: 20 },
  { name: 'Enterprise', value: 40 },
  { name: 'WPA2', value: 60 },
  { name: 'WPA', value: 30 },
  { name: 'OPEN', value: 70 }
];

const revenueData = [
  { date: 'Jan 22', revenue: -70 },
  { date: 'Feb 22', revenue: -65 },
  { date: 'Mar 22', revenue: -60 },
  { date: 'Apr 22', revenue: -62 },
  { date: 'May 22', revenue: -68 },
];

const pieData = [
  { name: 'Upload', value: 25 },
  { name: 'Download', value: 35 },
  { name: 'IoT Sync', value: 15 },
  { name: 'Security Check', value: 10 },
  { name: 'Other', value: 15 }
];

const COLORS = ['#8884d8', '#82ca9d', '#ffc658', '#ff8042', '#8dd1e1'];

const Dashboard = () => {
  return (
    <div className="p-6 bg-gray-100 min-h-screen grid grid-cols-1 sm:grid-cols-1 md:grid-cols-2 gap-6">

      {/* System Status & Disk Usage */}
      <div className="grid grid-cols-1 sm:grid-cols-2 gap-4">
        <div className="bg-white p-4 rounded-2xl shadow hover:shadow-md transition">
          <h2 className="text-lg font-semibold text-black flex items-center gap-2"><Cpu size={20} /> System Status</h2>
          <div className='flex justify-between items-center mt-4'>
            <div>
              <p className="text-3xl font-bold text-indigo-600">12%</p>
              <p className='text-black'>CPU</p>
            </div>
            <div>
              <p className="text-3xl font-bold text-green-600">15%</p>
              <p className='text-black'>MEM</p>
            </div>
          </div>
        </div>
        <div className="bg-white p-4 rounded-2xl shadow hover:shadow-md transition">
          <h2 className="text-lg font-semibold text-black flex items-center gap-2"><HardDrive size={20} /> Disk Usage</h2>
          <p className="text-3xl font-bold text-pink-600 mt-4">0%</p>
          <p className='text-black'>ROOT</p>
        </div>
      </div>

      {/* Wireless Charts */}
      <div className="bg-white p-4 rounded-2xl shadow hover:shadow-md transition">
        <h2 className="text-lg font-semibold mb-2 text-black flex items-center gap-2"><Wifi size={20} /> Wireless Landscape</h2>
        <ResponsiveContainer width="100%" height={200}>
          <BarChart layout="vertical" data={wirelessData}>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis type="number" />
            <YAxis dataKey="name" type="category" />
            <Tooltip />
            <Bar dataKey="value" fill="#8884d8" />
          </BarChart>
        </ResponsiveContainer>

        <h2 className="text-lg font-semibold mb-2 mt-6 text-black">Encryption Types</h2>
        <ResponsiveContainer width="100%" height={200}>
          <BarChart data={encryptionData}>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis dataKey="name" />
            <YAxis />
            <Tooltip />
            <Bar dataKey="value" fill="#82ca9d" />
          </BarChart>
        </ResponsiveContainer>
      </div>

      {/* Connected Devices */}
      <div className="bg-white p-4 rounded-2xl shadow hover:shadow-md transition">
        <h2 className="text-lg font-semibold mb-4 text-black flex items-center gap-2"><Users size={20} /> Connected Devices</h2>
        <div className="grid grid-cols-1 sm:grid-cols-3 gap-4 mb-4">
          <div className="bg-gray-100 p-3 rounded-lg text-center hover:bg-gray-200 transition">
            <p className="text-black">Connected</p>
            <p className="text-xl font-bold text-blue-600">10 Devices</p>
          </div>
          <div className="bg-gray-100 p-3 rounded-lg text-center hover:bg-gray-200 transition">
            <p className="text-black">Threats</p>
            <p className="text-xl font-bold text-red-600 flex items-center justify-center gap-1"><AlertTriangle size={16} />3</p>
          </div>
          <div className="bg-gray-100 p-3 rounded-lg text-center hover:bg-gray-200 transition">
            <p className="text-black">System</p>
            <p className="text-xl font-bold text-green-600">Stable</p>
          </div>
        </div>
        <div className="bg-gray-50 p-3 rounded-lg">
          <div className="flex justify-between mb-2">
            <p className="text-black">Online</p>
            <p className="text-black">3 Devices</p>
          </div>
          <div className="flex justify-between">
            <p className="text-black">Offline</p>
            <p className="text-black">7 Devices</p>
          </div>
        </div>
      </div>

      {/* Revenue Line Chart */}
      <div className="bg-white p-4 rounded-2xl shadow hover:shadow-md transition">
        <h2 className="text-lg font-semibold mb-2 text-black">Newsletter Revenue Over Time (USD)</h2>
        <ResponsiveContainer width="100%" height={250}>
          <LineChart data={revenueData}>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis dataKey="date" />
            <YAxis />
            <Tooltip />
            <Line type="monotone" dataKey="revenue" stroke="#8884d8" strokeWidth={2} />
          </LineChart>
        </ResponsiveContainer>
      </div>

      {/* Pie Chart */}
      <div className="bg-white p-4 rounded-2xl shadow hover:shadow-md transition">
        <h2 className="text-lg font-semibold mb-2 text-black flex items-center gap-2"><Shield size={20} /> Network Traffic</h2>
        <ResponsiveContainer width="100%" height={250}>
          <PieChart>
            <Pie
              data={pieData}
              cx="50%"
              cy="50%"
              innerRadius={60}
              outerRadius={80}
              fill="#8884d8"
              paddingAngle={5}
              dataKey="value"
            >
              {pieData.map((entry, index) => (
                <Cell key={`cell-${index}`} fill={COLORS[index % COLORS.length]} />
              ))}
            </Pie>
            <Tooltip />
            <Legend layout="horizontal" verticalAlign="bottom" align="center" />
          </PieChart>
        </ResponsiveContainer>
      </div>
    </div>
  );
};

export default Dashboard;
