#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

#include <EEPROM.h>

#include "wifi_config.h"
#include "mqtt_config.h"
#include "functions.h"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(36, 14, NEO_GRB + NEO_KHZ800);
WiFiClient espClient;
PubSubClient client(espClient);

bool boot = true;
MQTT broker_info;

void setup(){
  Serial.begin(115200);
  EEPROM.begin(1000);
  pixels.begin();
  pixels.show();
}

void loop(){
  if(boot){
    loadInfo(broker_info);
    client.setServer(broker_info.broker.c_str(), 1883);
    client.setCallback(callback);
    boot = false;
  }
  if (!client.connected()) {
    reconnect(client, broker_info.id, broker_info.owner, broker_info.email, broker_info.token);
    movePixel(pixels, 0xff0000, 100);
    pixels.setPixelColor(0, 0, 0, 0);
    pixels.show();
  }
  if(Serial.available()){
    StaticJsonBuffer<300> jsonBuffer;
    String inp = Serial.readStringUntil('\n');
    JsonObject& req = jsonBuffer.parseObject(inp);
    JsonObject& res = jsonBuffer.createObject();
    if(req.success()){
      String function;
      function = req["function"].asString();
      if(function == "setup"){
        broker_info.broker = req["broker"].asString();
        broker_info.id = req["id"].asString();
        broker_info.email = req["email"].asString();
        broker_info.owner = req["owner"].asString();
        broker_info.token = req["token"].asString();
        saveInfo(broker_info);
      }
      if(function == "info"){
        res["broker"] = broker_info.broker;
        res["id"] = broker_info.id;
        res["email"] = broker_info.email;
        res["owner"] = broker_info.owner;
        res["token"] = broker_info.token;
        String out;
        res.printTo(out);
        Serial.print(out);
      }
    }
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
    handleNotification(req, res, pixels);
    String output;
    res.printTo(output);
    Serial.println(output);
  }
}
