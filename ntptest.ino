#include <WiFi.h>
#include "time.h"

// Wi-Fi credentials
const char* ssid = "enter ssid";
const char* password = "enter pass";

// NTP server details
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 16200;   // GMT offset in seconds (UTC+1:00 for Central European Time)
const int daylightOffset_sec = 3600; // Daylight offset in seconds (for DST)

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize time library
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // Wait for time to sync
  while (!time(nullptr)) {
    Serial.println("Waiting for time sync...");
    delay(1000);
  }
}

void loop() {
  // Obtain current time
  time_t now;
  struct tm timeinfo;
  char dateTime[20];

  time(&now);
  localtime_r(&now, &timeinfo);

  strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", &timeinfo);

  // Print formatted date and time
  Serial.println("Current Date and Time: " + String(dateTime));

  delay(10000); // Delay 1 minute before next check
}
