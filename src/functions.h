#ifndef functions_h
#define functions_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>

void setAll(JsonObject& req, JsonObject& res, Adafruit_NeoPixel& pix){
  String function;
  function = req["function"].asString();
  if(String(function) == "setAll"){
    res["function"] = function;
    uint8_t num_pixels = pix.numPixels();
    for(int i=0; i<num_pixels; i++){
      uint8_t red = req["red"];
      uint8_t green = req["green"];
      uint8_t blue = req["blue"];
      pix.setPixelColor(i, red, green, blue);
    }
    pix.show();
    res["status"] = true;
  }
};

void setPixel(JsonObject& req, JsonObject& res, Adafruit_NeoPixel& pix){
  String function;
  function = req["function"].asString();
  if(String(function) == "setPixel"){
    res["function"] = function;
    uint16_t index = req["index"];
    if(index <= pix.numPixels()){
      uint8_t red = req["red"];
      uint8_t green = req["green"];
      uint8_t blue = req["blue"];
      pix.setPixelColor(index, red, green, blue);
      pix.show();
      res["status"] = true;
    }
    else{
      res["status"] = false;
    }
  }
}

void handleNotification(JsonObject& req, JsonObject& res, Adafruit_NeoPixel& pix){
  String function;
  function = req["function"].asString();
  if(String(function) == "notification"){
    String app;
    app = req["app"].asString();
    uint32_t color = 0;
    bool change = false;
    if(String(app) == "WhatsApp"){
      color = pix.Color(0,20,0);
      change = 1;
    }
    else if(String(app) == "Messenger"){
      color = pix.Color(0,0,20);
      change = 1;
    }
    else if(String(app) == "clear"){
      color = pix.Color(0,0,0);
      change = 1;
    }
    if(change){
      uint8_t num_pixels = pix.numPixels();
      for(int i=0; i<num_pixels; i++){
        pix.setPixelColor(i, color);
        pix.show();
        delay(10);
      }
      res["status"] = true;
      res["app"] = req["app"];
    }
    else{
      res["status"] = false;
      res["app"] = req["app"];
    }

  }
}

void movePixel(Adafruit_NeoPixel& pix, uint32_t color, long t){
  uint16_t n_pixels = pix.numPixels();
  for(int i=0; i <= n_pixels; i++){
    delay(t);
    pix.setPixelColor(i-1, 0);
    pix.setPixelColor(i, color);
    pix.show();
  }
}

#endif
