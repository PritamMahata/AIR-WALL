import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import Sidebar from "./components/Sidebar";
import Navbar from "./components/Navbar";
import Dashboard from "./pages/Dashboard";
import Devices from "./pages/Devices";
import SecurityLogs from "./pages/SecurityLogs";
import Settings from "./pages/Settings";
import Data from "./pages/Data";
import WifiJsonGenerator from "./json/WifiJsonGenerator";
import { useEffect } from "react";
import { decryptAES } from "./utils/crypto.js"; // Adjust the import path as necessary


function App() {

    const loadData = async () => {
      try {
        const data = await fetch("http://192.168.39.120/status");
        const text = await data.text();
        console.log(text);
        const newdata = decryptAES(text);
        console.log(newdata)
      } catch (err) {
        console.error("❌ Fetch or Decrypt Error:", err.message || err);
      }
    };
    
  
  // useEffect(() => {
  //   const interval = setInterval(() => {
  //     loadData();
  //   }, 1000); // Fetch every 5 seconds
  
  //   return () => clearInterval(interval); // Cleanup on unmount
  // }, []);
  

  
  return (
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
                <Route path="/data" element={<Data />} />
                <Route path="/generate-json" element={<WifiJsonGenerator />} />
              </Routes>
            </div>
          </div>
        </div>
      </Router>
  );
}

export default App;
