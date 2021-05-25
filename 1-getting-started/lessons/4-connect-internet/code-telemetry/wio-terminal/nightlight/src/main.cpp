#include <Arduino.h>
#include <ArduinoJSON.h>
#include <PubSubClient.h>
#include <rpcWiFi.h>
#include <SPI.h>

#include "config.h"

void connectWiFi()
{
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Connecting to WiFi..");
        WiFi.begin(SSID, PASSWORD);
        delay(500);
    }

    Serial.println("Connected!");
}

WiFiClient wioClient;
PubSubClient client(wioClient);

void reconnectMQTTClient()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");

        if (client.connect(CLIENT_NAME.c_str()))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("Retying in 5 seconds - failed, rc=");
            Serial.println(client.state());
            
            delay(5000);
        }
    }
}

void createMQTTClient()
{
    client.setServer(BROKER.c_str(), 1883);
    reconnectMQTTClient();
}

void setup()
{
	Serial.begin(9600);

	while (!Serial)
		; // Wait for Serial to be ready

	delay(1000);

    pinMode(WIO_LIGHT, INPUT);
    pinMode(D0, OUTPUT);

    connectWiFi();
    createMQTTClient();
}

void loop()
{
    reconnectMQTTClient();
    client.loop();

    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    JsonObject obj = doc.as<JsonObject>();
    serializeJson(obj, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());

    delay(2000);
}