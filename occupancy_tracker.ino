#include <WiFi.h>
#include <HTTPClient.h>

// 1. Network & Cloud Setup
const char* ssid = ""; // Enter your open Wi-Fi name here
// Paste your Firebase URL below and KEEP the /occupancy.json at the end
const char* databaseURL = ""; 

void setup() {
  // 1. Give the power supply 2 seconds to stabilize on boot
  delay(2000); 
  
  Serial.begin(115200);
  
  // 2. Reduce Wi-Fi transmit power to prevent power-crashes
  WiFi.setTxPower(WIFI_POWER_8_5dBm); 
  
  // Connect to open Wi-Fi using ONLY the SSID
  WiFi.begin(ssid);

  Serial.print("Connecting to open Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(databaseURL);
    http.addHeader("Content-Type", "application/json");

    // 2. Generate dummy detection data
    int dummyFootfallCount = random(10, 50); 
    String jsonPayload = "{\"current_count\":" + String(dummyFootfallCount) + "}";

    // 3. Push data to Firebase via HTTP PUT
    int httpResponseCode = http.PUT(jsonPayload);

    if (httpResponseCode > 0) {
      Serial.print("Success! Firebase HTTP Code: ");
      Serial.println(httpResponseCode);
      Serial.println("Pushed: " + jsonPayload);
    } else {
      Serial.print("Error sending data. HTTP Code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  
  // Wait 5 seconds before the next push
  delay(5000); 
}