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

// void alarmRead(){
//   StaticJsonBuffer<200> jsonBuffer;
//   JsonObject& res = jsonBuffer.createObject();
//   char* function;
//   function = "alarmRead";
//   res["function"] = function;
//   res["alarm"] = digitalRead(2);
//   res["status"] = true;
//   res.printTo(Serial);
// }

#endif
