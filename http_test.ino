#include <WiFi.h>
#include <HTTPClient.h>

// Wi-Fi credentials
const char* ssid = "Enter SSID";
const char* password = "Enter pass";

// HTTP server details
const char* serverName = "your server url";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String httpDateTime = http.getString();
      Serial.println("HTTP Date and Time: " + httpDateTime);
    } else {
      Serial.println("Error in HTTP request");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }

  delay(10000); // Delay 1 minute before next check
}
