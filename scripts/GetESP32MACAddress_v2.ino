/*
  GetESP32MACAddress_v2

  Updated to include delay calls to give time for initialization
  Suggestions from Gemini: https://gemini.google.com/share/ad0dc4029b7b
  
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/get-change-esp32-esp8266-mac-address-arduino/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.  
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/
#include <WiFi.h>
#include <esp_wifi.h>

void readMacAddress(){
  uint8_t baseMac[6];
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
  if (ret == ESP_OK) {
    Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                  baseMac[0], baseMac[1], baseMac[2],
                  baseMac[3], baseMac[4], baseMac[5]);
  } else {
    Serial.println("Failed to read MAC address");
  }
}

void setup(){
  Serial.begin(9600);
  delay(1000); // Give serial time to initialize

  Serial.println("Initializing WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.STA.begin();
  delay(100); // Give WiFi time to initialize

  Serial.println("[DEFAULT] ESP32 Board MAC Address: ");
  readMacAddress();
}
 
void loop(){

}