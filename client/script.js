// AES Encryption/Decryption
const AES_KEY = "1234567890123456"; // Must match ESP32's key
let socket;

function encryptData(data) {
  const key = CryptoJS.enc.Utf8.parse(AES_KEY);
  const encrypted = CryptoJS.AES.encrypt(data, key, {
    mode: CryptoJS.mode.ECB,
    padding: CryptoJS.pad.Pkcs7,
  });
  return CryptoJS.enc.Base64.stringify(encrypted.ciphertext);
}

function decryptData(base64) {
  const key = CryptoJS.enc.Utf8.parse(AES_KEY);
  const raw = CryptoJS.enc.Base64.parse(base64);
  const decrypted = CryptoJS.AES.decrypt({ ciphertext: raw }, key, {
    mode: CryptoJS.mode.ECB,
    padding: CryptoJS.pad.Pkcs7,
  });
  return decrypted.toString(CryptoJS.enc.Utf8);
}

// Logging
function log(msg) {
  const logContainer = document.getElementById("log");
  const entry = document.createElement("div");
  entry.className = "log-entry";
  entry.textContent = `[${new Date().toLocaleTimeString()}] ${msg}`;
  logContainer.appendChild(entry);
  logContainer.scrollTop = logContainer.scrollHeight;
}

function clearLog() {
  document.getElementById("log").innerHTML = "";
}

// WebSocket Connection
function connectWS() {
  const url = document.getElementById("wsUrl").value;

  if (socket && socket.readyState === WebSocket.OPEN) {
    socket.close();
  }

  try {
    socket = new WebSocket(url);

    socket.onopen = () => {
      log("✅ WebSocket connected");
      updateConnectionStatus(true);
      document.getElementById("connectBtn").disabled = true;
      document.getElementById("disconnectBtn").disabled = false;
    };

    socket.onmessage = (event) => {
      try {
        const decrypted = decryptData(event.data);
        log("🔓 Decrypted: " + decrypted);

        // Try to parse as JSON and update UI
        try {
          const data = JSON.parse(decrypted);
          updateSensorData(data);
        } catch (e) {
          // Not JSON or parsing error
        }
      } catch (e) {
        log("⚠️ Decryption error: " + e.message);
      }
    };

    socket.onclose = () => {
      log("❌ WebSocket disconnected");
      updateConnectionStatus(false);
      document.getElementById("connectBtn").disabled = false;
      document.getElementById("disconnectBtn").disabled = true;
    };

    socket.onerror = (e) => {
      log("⚠️ Error: " + e.type);
      updateConnectionStatus(false);
    };
  } catch (e) {
    log("⚠️ Connection error: " + e.message);
    updateConnectionStatus(false);
  }
}

function disconnectWS() {
  if (socket) {
    socket.close();
    socket = null;
  }
}

function updateConnectionStatus(connected) {
  const indicator = document.getElementById("statusIndicator");
  const text = document.getElementById("statusText");

  if (connected) {
    indicator.classList.add("connected");
    text.textContent = "Connected";
  } else {
    indicator.classList.remove("connected");
    text.textContent = "Disconnected";
  }
}

// Send Commands
function sendEncrypted() {
  const msg = document.getElementById("message").value;
  sendCommand(msg);
}

function sendCommand(msg) {
  if (!socket || socket.readyState !== WebSocket.OPEN) {
    log("⚠️ WebSocket not connected");
    return;
  }

  try {
    const encrypted = encryptData(msg);
    log("🔐 Sent: " + msg);
    socket.send(encrypted);
  } catch (e) {
    log("⚠️ Encryption error: " + e.message);
  }
}

function callStatus() {
  fetch("/status")
    .then((r) => r.text())
    .then((data) => {
      log("📦 Raw /status: " + data);
      try {
        const decoded = decryptData(data);
        log("🔓 Decoded: " + decoded);

        // Try to parse as JSON and update UI
        try {
          const jsonData = JSON.parse(decoded);
          updateSensorData(jsonData);
        } catch (e) {
          // Not JSON or parsing error
        }
      } catch (e) {
        log("⚠️ Decoding error: " + e.message);
      }
    })
    .catch((e) => log("⚠️ Fetch error: " + e.message));
}

function callDecrypt() {
  const msg = document.getElementById("message").value;
  const encrypted = encryptData(msg);

  fetch("/decrypt", {
    method: "POST",
    headers: { "Content-Type": "application/x-www-form-urlencoded" },
    body: "data=" + encodeURIComponent(encrypted),
  })
    .then((r) => r.text())
    .then((txt) => log("🧩 Decrypted result: " + txt))
    .catch((e) => log("⚠️ Fetch error: " + e.message));
}

// Device Controls
function toggleLED() {
  const ledState = document.getElementById("ledToggle").checked;
  const command = JSON.stringify({
    cmd: "led",
    state: ledState ? "on" : "off",
  });
  sendCommand(command);
}

function setBrightness(value) {
  const command = JSON.stringify({
    cmd: "brightness",
    value: parseInt(value),
  });
  sendCommand(command);
}

function updateBrightnessValue(value) {
  document.getElementById("brightnessValue").textContent = value;
}

function requestTemperature() {
  sendCommand(JSON.stringify({ cmd: "getTemperature" }));
}

function requestHumidity() {
  sendCommand(JSON.stringify({ cmd: "getHumidity" }));
}

function requestAllSensors() {
  sendCommand(JSON.stringify({ cmd: "getAllSensors" }));
}

// Update Sensor Data
function updateSensorData(data) {
  if (data.temperature !== undefined) {
    document.getElementById(
      "temperatureValue"
    ).textContent = `${data.temperature}°C`;
    addDataToChart(temperatureChart, data.temperature);
  }

  if (data.humidity !== undefined) {
    document.getElementById("humidityValue").textContent = `${data.humidity}%`;
    addDataToChart(humidityChart, data.humidity);
  }

  if (data.battery !== undefined) {
    document.getElementById("batteryValue").textContent = `${data.battery}%`;
    updateStatusPieChart(data);
  }
}

// Tab Navigation
document.querySelectorAll(".tab").forEach((tab) => {
  tab.addEventListener("click", () => {
    // Remove active class from all tabs
    document
      .querySelectorAll(".tab")
      .forEach((t) => t.classList.remove("active"));
    document
      .querySelectorAll(".tab-content")
      .forEach((c) => c.classList.remove("active"));

    // Add active class to clicked tab
    tab.classList.add("active");
    document.getElementById(`${tab.dataset.tab}Tab`).classList.add("active");
  });
});

// Charts
let temperatureChart, humidityChart, statusPieChart, powerChart;
const maxDataPoints = 20;

function initCharts() {
  // Temperature Chart
  const tempCtx = document.getElementById("temperatureChart").getContext("2d");
  temperatureChart = new Chart(tempCtx, {
    type: "line",
    data: {
      labels: Array(maxDataPoints).fill(""),
      datasets: [
        {
          label: "Temperature (°C)",
          data: [],
          borderColor: "#e74c3c",
          backgroundColor: "rgba(231, 76, 60, 0.1)",
          borderWidth: 2,
          tension: 0.4,
          fill: true,
        },
      ],
    },
    options: {
      responsive: true,
      maintainAspectRatio: false,
      scales: {
        y: {
          beginAtZero: false,
          suggestedMin: 15,
          suggestedMax: 35,
        },
      },
      animation: {
        duration: 500,
      },
    },
  });

  // Humidity Chart
  const humidityCtx = document.getElementById("humidityChart").getContext("2d");
  humidityChart = new Chart(humidityCtx, {
    type: "line",
    data: {
      labels: Array(maxDataPoints).fill(""),
      datasets: [
        {
          label: "Humidity (%)",
          data: [],
          borderColor: "#3498db",
          backgroundColor: "rgba(52, 152, 219, 0.1)",
          borderWidth: 2,
          tension: 0.4,
          fill: true,
        },
      ],
    },
    options: {
      responsive: true,
      maintainAspectRatio: false,
      scales: {
        y: {
          beginAtZero: false,
          suggestedMin: 0,
          suggestedMax: 100,
        },
      },
      animation: {
        duration: 500,
      },
    },
  });

  // Status Pie Chart
  const statusCtx = document.getElementById("statusPieChart").getContext("2d");
  statusPieChart = new Chart(statusCtx, {
    type: "doughnut",
    data: {
      labels: ["Battery", "Used"],
      datasets: [
        {
          data: [75, 25],
          backgroundColor: ["#2ecc71", "#ecf0f1"],
          borderWidth: 0,
        },
      ],
    },
    options: {
      responsive: true,
      maintainAspectRatio: false,
      cutout: "70%",
      plugins: {
        legend: {
          position: "bottom",
        },
      },
    },
  });

  // Power Usage Chart
  const powerCtx = document.getElementById("powerChart").getContext("2d");
  powerChart = new Chart(powerCtx, {
    type: "bar",
    data: {
      labels: ["00:00", "04:00", "08:00", "12:00", "16:00", "20:00"],
      datasets: [
        {
          label: "Power Usage (mW)",
          data: [120, 90, 180, 270, 220, 150],
          backgroundColor: "#9b59b6",
        },
      ],
    },
    options: {
      responsive: true,
      maintainAspectRatio: false,
      scales: {
        y: {
          beginAtZero: true,
        },
      },
    },
  });
}

function addDataToChart(chart, value) {
  const now = new Date();
  const timeString = now.toLocaleTimeString([], {
    hour: "2-digit",
    minute: "2-digit",
  });

  // Add new data point
  chart.data.labels.push(timeString);
  chart.data.datasets[0].data.push(value);

  // Remove old data if we have more than maxDataPoints
  if (chart.data.labels.length > maxDataPoints) {
    chart.data.labels.shift();
    chart.data.datasets[0].data.shift();
  }

  chart.update();
}

function updateStatusPieChart(data) {
  if (data.battery !== undefined) {
    const batteryLevel = parseInt(data.battery);
    statusPieChart.data.datasets[0].data = [batteryLevel, 100 - batteryLevel];

    // Update color based on battery level
    let color = "#2ecc71"; // Green for good battery
    if (batteryLevel < 20) {
      color = "#e74c3c"; // Red for low battery
    } else if (batteryLevel < 50) {
      color = "#f39c12"; // Orange for medium battery
    }

    statusPieChart.data.datasets[0].backgroundColor[0] = color;
    statusPieChart.update();
  }
}

// Simulate data for demo purposes
let simulationInterval;

function startSimulation() {
  simulationInterval = setInterval(() => {
    // Generate random data
    const temperature = (20 + Math.random() * 10).toFixed(1);
    const humidity = Math.floor(30 + Math.random() * 50);
    const battery = Math.floor(50 + Math.random() * 50);

    // Update UI
    updateSensorData({
      temperature: parseFloat(temperature),
      humidity: humidity,
      battery: battery,
    });

    // Log simulated data
    log(
      `🤖 Simulated data: Temp=${temperature}°C, Humidity=${humidity}%, Battery=${battery}%`
    );
  }, 5000);
}

// function stopSimulation() {
//   clearInterval(simulationInterval);
// }

// Initialize
// document.addEventListener("DOMContentLoaded", () => {
//   initCharts();
//   startSimulation(); // Start simulation for demo

//   // Initialize with some data
//   updateSensorData({
//     temperature: 22.5,
//     humidity: 45,
//     battery: 78,
//   });
// });
