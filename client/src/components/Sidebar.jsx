import { Link } from "react-router-dom";
import {
  Gauge,
  MonitorSmartphone,
  Lock,
  Settings as SettingsIcon,
  BarChart4
} from 'lucide-react';

function Sidebar() {
  return (
    <div className="bg-gray-900 text-white w-64 min-h-screen p-4">
      <h2 className="text-2xl font-bold mb-6">ESP32 Security</h2>
      <nav>
        <ul className="space-y-4">
          <li>
            <Link to="/" className="flex items-center gap-3 p-2 hover:bg-gray-700 rounded">
              <Gauge size={20} />
              Dashboard
            </Link>
          </li>
          <li>
            <Link to="/devices" className="flex items-center gap-3 p-2 hover:bg-gray-700 rounded">
              <MonitorSmartphone size={20} />
              Devices
            </Link>
          </li>
          <li>
            <Link to="/logs" className="flex items-center gap-3 p-2 hover:bg-gray-700 rounded">
              <Lock size={20} />
              Security Logs
            </Link>
          </li>
          <li>
            <Link to="/settings" className="flex items-center gap-3 p-2 hover:bg-gray-700 rounded">
              <SettingsIcon size={20} />
              Settings
            </Link>
          </li>
          <li>
            <Link to="/generate-json" className="flex items-center gap-3 p-2 hover:bg-gray-700 rounded">
              <BarChart4 size={20} />
              Config Generator
            </Link>
          </li>
        </ul>
      </nav>
    </div>
  );
}

export default Sidebar;
