function generateJson() {
    const wifiName = document.getElementById('wifiName').value.trim();
    const wifiPassword = document.getElementById('wifiPassword').value.trim();
  
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
    link.download = 'config.json';
    link.click();
  
    URL.revokeObjectURL(url);
  }
  