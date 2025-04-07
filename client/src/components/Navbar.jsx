import { useLocation } from "react-router-dom";

function Navbar() {
  const location = useLocation();

  // Get dynamic page title from route path
  const getPageTitle = () => {
    const path = location.pathname;
    if (path === "/") return "Dashboard";
    if (path === "/devices") return "Devices";
    if (path === "/logs") return "Security Logs";
    if (path === "/settings") return "Settings";
    if (path === "/generate-json") return "JSON Generator";
    return "ESP32 Security Dashboard"; // Default title
  };

  return (
    <nav className="bg-gray-500 p-4 text-white flex justify-center items-center">
      <h1 className="text-xl font-bold">{getPageTitle()}</h1>
    </nav>
  );
};

export default Navbar;
