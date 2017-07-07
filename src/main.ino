#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

#include "wifi_config.h"
#include "mqtt_config.h"
#include "functions.h"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(8, 14, NEO_GRB + NEO_KHZ800);
WiFiClient espClient;
PubSubClient client(espClient);

bool req_message;
const char* mqtt_server = "192.168.1.17";

void setup(){
  Serial.begin(115200);
  setup_wifi();
  pixels.begin();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop(){
  if (!client.connected()) {
    pixels.setPixelColor(0, 255, 0, 0);
    pixels.show();
    reconnect(client, "Arduino", "vcamargo.e", "vcamargo.e@gmail.com", "lDOabObMbb");
    pixels.setPixelColor(0, 0, 255, 0);
    pixels.show();
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  String input_message= "";
  for (int i = 0; i < length; i++) {
    input_message += (char)payload[i];
  }
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& req = jsonBuffer.parseObject(input_message);
  JsonObject& res = jsonBuffer.createObject();
  if(req.success()){
    setAll(req, res, pixels);
    setPixel(req, res, pixels);
    String output;
    res.printTo(output);
    Serial.println(output);
  }
}
