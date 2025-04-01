// Function to format time in hh:mm:ss format from millis()
String getFormattedTime() {
    unsigned long currentMillis = millis();
    unsigned long totalSeconds = currentMillis / 1000;
    unsigned long seconds = totalSeconds % 60;
    unsigned long minutes = (totalSeconds / 60) % 60;
    unsigned long hours = (totalSeconds / 3600) % 24;
  
    char timeString[9];
    sprintf(timeString, "%02lu:%02lu:%02lu", hours, minutes, seconds);  // Format time as hh:mm:ss
  
    return String(timeString);
  }