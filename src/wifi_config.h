#ifndef wifi_config_h
#define wifi_config_h

#include <Arduino.h>
const char* ssid = "TecMarte";
const char* password = "tecmarte2";

void setup_wifi(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

#endif;
