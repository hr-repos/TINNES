#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "secret.h"
#include "DHT.h"
#include "time.h"
#include <WiFiClientSecure.h>
#define TOPIC "chat/message"

#define DHTPIN 32
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

//student:welkom01

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqtt_server = MQTT_HOST;

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 0;

WiFiClientSecure espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

void setup_wifi() {

    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
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

void printLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}


void callback(char* topic, byte* payload, unsigned int length) {
    char message[length + 1]; // +1 for null terminator
    for (int i = 0; i < length; i++) {
        message[i] = (char)payload[i];
    }
    message[length] = '\0';

    char receiver[11];
    for (int i = 0; i < 11; i++) {
        receiver[i] = message[i];
    }
    receiver[11] = '\0';
    
    if (!strcmp(receiver, "BOT-1051997")==0) {
        Serial.print("message ignored, receiver: ");
        Serial.println(receiver);
        return;
    }
    
    client.unsubscribe("chat/message");

    if (strcmp(message, "BOT-1051997: test") == 0) {
        Serial.println("Test message received");
        client.publish(TOPIC, "Test message received");
    } 
    else if (strcmp(message, "BOT-1051997: temperatuur") == 0) {
        Serial.println("temp request received");
        String newMessage = "BOT-1051997: temperature is now " + String(dht.readTemperature()) + "°C.";
        client.publish(TOPIC, newMessage.c_str());
    }
    else if (strcmp(message, "BOT-1051997: vochtigheid") == 0) {
        Serial.println("temp request received");
        String newMessage = "BOT-1051997: humidity is now " + String(dht.readHumidity()) + "%.";
        client.publish(TOPIC, newMessage.c_str());
    }
    else if (strcmp(message, "BOT-1051997: alle gegevens") == 0) {
        Serial.println("alle gegevens request received");
        String newMessage = "BOT-1051997: temperature is now " + String(dht.readTemperature()) + "°C. " + "Humidity is now " + String(dht.readHumidity()) + "%.";
        client.publish(TOPIC, newMessage.c_str());
    }
    else if (strcmp(message, "BOT-1051997: led:aan") == 0) {
        Serial.println("led on request received");
        digitalWrite(BUILTIN_LED, HIGH);
        client.publish(TOPIC, "BOT-1051997: led is now on");
    }
    else if (strcmp(message, "BOT-1051997: led:uit") == 0) {
        Serial.println("led off request received");
        digitalWrite(BUILTIN_LED, LOW);
        client.publish(TOPIC, "BOT-1051997: led is now off");
    }
    else {
        Serial.printf("Unrecognised message received: %s\n", message);
        client.publish(TOPIC, "BOT-1051997: message not recognised");
    }
    Serial.println();
    client.subscribe("chat/message");
}


void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "BOT-1051997";
        
        // Attempt to connect
        if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)) {
        Serial.println("connected");
        // Once connected, publish an announcement...
        client.publish("outTopic", "hello world");
        // ... and resubscribe
        client.subscribe("chat/message");
        } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
        }
    }
}

void setup() {
    pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
    Serial.begin(115200);

    setup_wifi();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();    
    client.setServer(mqtt_server, MQTT_PORT);
    espClient.setCACert(local_root_ca);
    client.setCallback(callback);
    dht.begin();
}

void loop() {

    if (!client.connected()) {
        delay(2000);
        reconnect();
    }
    client.loop();
}
