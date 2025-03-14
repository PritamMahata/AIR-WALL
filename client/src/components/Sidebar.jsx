import { Link } from "react-router-dom";

const Sidebar = () => {
  return (
    <div className="bg-gray-900 dark:bg-gray-700 text-white w-64 min-h-screen p-4">
      <h2 className="text-2xl font-bold mb-6">ESP32 Security</h2>
      <nav>
        <ul className="space-y-4">
          <li>
            <Link to="/" className="block p-2 hover:bg-gray-700 rounded">
              Dashboard
            </Link>
          </li>
          <li>
            <Link to="/devices" className="block p-2 hover:bg-gray-700 rounded">
              Devices
            </Link>
          </li>
          <li>
            <Link to="/logs" className="block p-2 hover:bg-gray-700 rounded">
              Security Logs
            </Link>
          </li>
          <li>
            <Link to="/settings" className="block p-2 hover:bg-gray-700 rounded">
              Settings
            </Link>
          </li>
        </ul>
      </nav>
    </div>
  );
};

export default Sidebar;
