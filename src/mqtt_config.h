#ifndef mqtt_config_h
#define mqtt_config_h

#include <Arduino.h>
#include <PubSubClient.h>

void reconnect(PubSubClient& client, String id, String owner, String user, String password) {
  while (!client.connected()) {
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
      delay(5000);
    }
  }
}

#endif
