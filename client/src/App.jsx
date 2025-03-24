import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import Sidebar from "./components/Sidebar";
import Navbar from "./components/Navbar";
import Dashboard from "./pages/Dashboard";
import Devices from "./pages/Devices";
import SecurityLogs from "./pages/SecurityLogs";
import Settings from "./pages/Settings";
import { ThemeProvider } from "./contexts/ThemeContext";
<<<<<<< HEAD
import Data from "./pages/Data";
=======
import WifiJsonGenerator from "./json/WifiJsonGenerator";
>>>>>>> cce126cad8feb14874b1e517cfa3022574ccc42b

function App() {
  return (
    <ThemeProvider>
        <Router>
        <div className="flex min-h-screen bg-gray-100">
          {/* Sidebar */}
          <div className="w-64 fixed h-full bg-gray-900 text-white">
            <Sidebar />
          </div>

          {/* Main Content */}
          <div className="flex-1 ml-64">
            <Navbar />
            <div className="pt-16 p-6">
              <Routes>
                <Route path="/" element={<Dashboard />} />
                <Route path="/devices" element={<Devices />} />
                <Route path="/logs" element={<SecurityLogs />} />
                <Route path="/settings" element={<Settings />} />
<<<<<<< HEAD
                <Route path="/data" element={<Data />} />
=======
                <Route path="/generate-json" element={<WifiJsonGenerator />} />
>>>>>>> cce126cad8feb14874b1e517cfa3022574ccc42b
              </Routes>
            </div>
          </div>
        </div>
      </Router>
    </ThemeProvider>
  );
}

export default App;
