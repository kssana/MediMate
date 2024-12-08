#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <AccelStepper.h>

// Wi-Fi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// HTTP server details
const char* serverName = "http://your_server_address/get_datetime";

// NTP server details
const long utcOffsetInSeconds = 3600; // Adjust according to your timezone
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

// Stepper motor setup
const int motorPin1 = 14;
const int motorPin2 = 27;
const int motorPin3 = 26;
const int motorPin4 = 25;
AccelStepper stepper(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  // Initialize NTP client
  timeClient.begin();
  
  // Initialize stepper motor
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
}

void loop() {
  // Get date and time from NTP server
  timeClient.update();
  String ntpDateTime = timeClient.getFormattedTime();
  Serial.println("NTP Date and Time: " + ntpDateTime);
  
  // Get date and time from HTTP server
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      String httpDateTime = http.getString();
      Serial.println("HTTP Date and Time: " + httpDateTime);
      
      // Compare date and time
      if (ntpDateTime == httpDateTime) {
        Serial.println("Date and Time match. Rotating stepper motor.");
        stepper.moveTo(200); // Rotate stepper motor
        while (stepper.distanceToGo() != 0) {
          stepper.run();
        }
      } else {
        Serial.println("Date and Time do not match.");
      }
    } else {
      Serial.println("Error in HTTP request");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
  
  delay(60000); // Delay 1 minute before next check
}
