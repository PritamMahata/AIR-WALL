import { useContext } from "react";
import { ThemeContext } from "../contexts/ThemeContext";
import { Sun, Moon } from "lucide-react";
import { useLocation } from "react-router-dom";

const Navbar = () => {
  const { theme, toggleTheme } = useContext(ThemeContext);
  const location = useLocation();

  // Get dynamic page title from route path
  const getPageTitle = () => {
    const path = location.pathname;
    if (path === "/") return "Dashboard";
    if (path === "/devices") return "Devices";
    if (path === "/logs") return "Security Logs";
    if (path === "/settings") return "Settings";
    return "ESP32 Security Dashboard"; // Default title
  };

  return (
    <nav className="bg-blue-600 dark:bg-gray-800 p-4 text-white flex justify-between items-center">
      <h1 className="text-xl font-bold">{getPageTitle()}</h1>
      <button
        onClick={toggleTheme}
        className="bg-gray-200 dark:bg-gray-700 p-2 rounded-full text-black "
      >
        {theme === "light" ? <Moon size={20} /> : <Sun size={20} />}
      </button>
    </nav>
  );
};

export default Navbar;
