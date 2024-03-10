#include <dht11.h>
#define DHT11PIN 32
#include <ArduinoMqttClient.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include "secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
const char* ssid = SECRET_SSID;
const char* pass = SECRET_PASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

#define MQTT_SERVER "192.168.1.120"
#define MQTT_PORT 1883
#define MQTT_USER "your_username"
#define MQTT_PASSWORD "your_password"
const char topic[]  = "real_unique_topic";
const char topic2[]  = "real_unique_topic_2";
const char topic3[]  = "real_unique_topic_3";

//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;
int count = 0;

dht11 DHT11;

void  setup()
{
    //Initialize serial and wait for port to open:
  Serial.begin(115200);
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  // Auto reconnect is set true as default
  // To set auto connect off, use the following function
  //    WiFi.setAutoReconnect(false);

  // Will try for about 10 seconds (20x 500ms)
  int tryDelay = 500;
  int numberOfTries = 20;
  int connected = false;
  // Wait for the WiFi event
  while (!connected) {
      delay(tryDelay);
      if(numberOfTries <= 0){
        Serial.print("[WiFi] Failed to connect to WiFi!");
        // Use discon nect function to force stop trying to connect
        WiFi.disconnect();
      } else {
        numberOfTries--;
      }
  }
  Serial.println("Wifi connected!");


  Serial.println();
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }
  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

float getTemperature(){
  int chk = DHT11.read(DHT11PIN);
  return (float)DHT11.temperature;
}

float gethumidity(){
  int chk = DHT11.read(DHT11PIN);
  return (float)DHT11.temperature;
}

void loop()
{
  Serial.println();

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);
  delay(2000);

}