const xValues = ["Allowed", "Not Allowed"];
const yValues = [80, 20];
const barColors = ["#b91d47", "#00aba9"];

new Chart("threatChart", {
  type: "doughnut",
  data: {
    labels: xValues,
    datasets: [
      {
        backgroundColor: barColors,
        data: yValues,
      },
    ],
  },
  options: {
    title: {
      display: false,
      text: "World Wide Wine Production 2018",
    },
  },
});

const trafficxValues = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
const trafficyValues = [7, 8, 8, 56, 45, 32, 10, 11, 14, 14];
new Chart("trafficChart", {
  type: "line",
  data: {
    labels: trafficxValues,
    datasets: [
      {
        fill: false,
        lineTension: 0,
        backgroundColor: "rgba(0,0,255,1.0)",
        borderColor: "rgba(0,0,255,0.5)",
        data: trafficyValues,
      },
    ],
  },
  options: {
    legend: { display: false },
    scales: {
      yAxes: [{ ticks: { min: 0, max: 100 } }],
    },
  },
});

const themeToggle = document.getElementById("themeToggle");
const htmlElement = document.documentElement;

themeToggle.addEventListener("click", () => {
  const isLightTheme = htmlElement.dataset.theme === "light";
  htmlElement.dataset.theme = isLightTheme ? "dark" : "light";
  themeToggle.textContent = isLightTheme ? "🌞" : "🌓";
});

let serial_output = document.getElementById("serial_output");
let memoryInfo = document.getElementById("memoryInfo");
let flashMemoryInfo = document.getElementById("flashMemoryInfo");
let messageLimit = 50; // Set the number of messages you want to keep
let messages = []; // Array to store incoming messages

let netInfo = document.getElementById("netInfo");
let chipInfo = document.getElementById("chipInfo");
let signalStrength = document.getElementById("signalStrength");
let signalInfo = document.getElementById("signalInfo");
let terminal = document.querySelector(".terminal");

let ws = new WebSocket("ws://" + window.location.hostname + ":81");
ws.onmessage = function (event) {
  try {
    let data = JSON.parse(event.data);
    console.log(data);
    messages.push(data.serialData);
    if (messages.length > messageLimit) {
      messages.shift(); // Remove the first (oldest) message
    }
    serial_output.innerHTML = "";
    messages.forEach((msg) => {
      serial_output.innerHTML += msg + "<br>";
    });

    netInfo.innerHTML = data.netInfo;
    chipInfo.innerHTML = data.chipInfo;

    let power = 100 - -data.signalStrength;
    if (power >= 60) {
      document.getElementById("signalStrength").style.backgroundColor =
        "#00dc09";
    } else if (power <= 60 && power >= 40) {
      document.getElementById("signalStrength").style.backgroundColor =
        "#5852ff";
    } else {
      document.getElementById("signalStrength").style.backgroundColor =
        "#fe0000";
    }
    signalStrength.style.width = `${power}%`;
    signalInfo.innerHTML = `${power}% (${data.signalStrength}) dBm`;

    const seconds = data.runtimeInfo;
    const hours = Math.floor(seconds / 3600);
    const minutes = Math.floor((seconds % 3600) / 60);
    const remainingSeconds = seconds % 60;
    uptime.innerHTML = `${hours}h ${minutes}m ${remainingSeconds}s`;
  } catch (error) {
    console.error("Error parsing WebSocket message: ", error);
  }
  terminal.scrollTop = terminal.scrollHeight;
};
