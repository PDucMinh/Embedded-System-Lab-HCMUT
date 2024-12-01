#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//Wifi name
#define WLAN_SSID ""
//Wifi password
#define WLAN_PASS ""

//setup Adafruit
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
//fill your username
#define AIO_USERNAME ""
//fill your key
#define AIO_KEY ""

//setup MQTT
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

//setup publish
Adafruit_MQTT_Publish temperature_pub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/cambien1");

//setup subcribe
Adafruit_MQTT_Subscribe temperature_sub = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/cambien1", MQTT_QOS_1);

int led_counter = 0;
int led_status = HIGH;

void setup() {
  // put your setup code here, to run once:
  //set pin 2,5 as OUTPUT
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  //set busy pin HIGH
  digitalWrite(5, HIGH);

  Serial.begin(115200);

  //connect Wifi
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  //subscribe temperature feed
  mqtt.subscribe(&temperature_sub);

  //connect MQTT
  while (mqtt.connect() != 0) {
    mqtt.disconnect();
    delay(500);
  }

  //finish setup, set busy pin LOW
  digitalWrite(5, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  //receive packet
  mqtt.processPackets(1);

  //read serial
  if (Serial.available() > 0) {
    String msg = Serial.readStringUntil('#');  // Read until '#' delimiter

    if (msg.startsWith("!TEMP:")) {
      msg.remove(0, 6);              // Remove "!TEMP:"
      msg.remove(msg.length() - 1);  // Remove "#"

      float temperature = msg.toFloat();

      if (!isnan(temperature)) {  // Check for valid conversion
        Serial.print("Temperature received: ");
        Serial.println(temperature);

        if (!temperature_pub.publish(temperature)) {
          Serial.println(F("Failed to publish temperature"));
        } else {
          Serial.println(F("Temperature published!"));
        }
      } else {
        Serial.println("Invalid temperature value received.");
      }
    }
  }

  led_counter++;
  if (led_counter == 100) {
    // every 1s
    led_counter = 0;
    //toggle LED
    if (led_status == HIGH) led_status = LOW;
    else led_status = HIGH;

    digitalWrite(2, led_status);
  }

  delay(10);
}