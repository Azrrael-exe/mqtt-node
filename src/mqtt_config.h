#ifndef mqtt_config_h
#define mqtt_config_h

#include <Arduino.h>
#include <PubSubClient.h>

struct MQTT {
  String broker;
  String id;
  String email;
  String owner;
  String token;
};

void saveInfo(MQTT &info){
  EEPROM.write(0, info.broker.length());
  for(int i=0; i < info.broker.length(); i++){
    EEPROM.write(50+i, info.broker[i]);
  }
  EEPROM.write(1, info.id.length());
  for(int i=0; i < info.id.length(); i++){
    EEPROM.write(150+i, info.id[i]);
  }
  EEPROM.write(1, info.id.length());
  for(int i=0; i < info.id.length(); i++){
    EEPROM.write(150+i, info.id[i]);
  }
  EEPROM.write(2, info.email.length());
  for(int i=0; i < info.email.length(); i++){
    EEPROM.write(250+i, info.email[i]);
  }
  EEPROM.write(3, info.owner.length());
  for(int i=0; i < info.owner.length(); i++){
    EEPROM.write(350+i, info.owner[i]);
  }
  EEPROM.write(4, info.token.length());
  for(int i=0; i < info.token.length(); i++){
    EEPROM.write(450+i, info.token[i]);
  }
  EEPROM.commit();
}

void loadInfo(MQTT &info){
  uint8_t broker_size = EEPROM.read(0);
  info.broker = "";
  for(int i=0; i<broker_size; i++){
    info.broker += char(EEPROM.read(50 + i));
  }
  uint8_t id_size = EEPROM.read(1);
  info.id = "";
  for(int i=0; i<id_size; i++){
    info.id += char(EEPROM.read(150 + i));
  }
  uint8_t email_size = EEPROM.read(2);
  info.email = "";
  for(int i=0; i<email_size; i++){
    info.email += char(EEPROM.read(250 + i));
  }
  uint8_t owner_size = EEPROM.read(3);
  info.owner = "";
  for(int i=0; i<owner_size; i++){
    info.owner += char(EEPROM.read(350 + i));
  }
  uint8_t token_size = EEPROM.read(4);
  info.token = "";
  for(int i=0; i<token_size; i++){
    info.token += char(EEPROM.read(450 + i));
  }
}

void reconnect(PubSubClient& client, String id, String owner, String user, String password) {
  Serial.print("Attempting MQTT connection...");
  if (client.connect(id.c_str(), user.c_str(), password.c_str())) {
    Serial.println("connected");
    client.publish((owner + "/" + id).c_str(), (id + " Connected!").c_str());
    client.subscribe((owner + "/" + id + "/input").c_str());
  }
  else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 5 seconds");
  }
}

#endif
