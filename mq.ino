#include <WiFi.h>
#include <HTTPClient.h>

// WiFi Configuration
const char* ssid = "@hankaicuyy";
const char* password = "loliloliloli";

// Sensor configuration
const int sensorPin = 4;
const String sensorName = "gas";

// RestAPI Configuration
const char* baseRoute = "https://192.168.43.11/";
const int requestDelay = 1000;

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi network");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(requestDelay);
  int gas = analogRead(sensorPin);

  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HttpClient http;

    http.begin(client, baseRoute+sensorName);
    http.POST(String(gas));

    http.end();
  }else{
    Serial.println("WiFi Disconnected");
  }
}