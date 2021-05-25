#include <Arduino.h>
#include <ArduinoJson.h>
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

void clientCallback(char *topic, uint8_t *payload, unsigned int length)
{
    char buff[length + 1];
    for (int i = 0; i < length; i++)
    {
        buff[i] = (char)payload[i];
    }
    buff[length] = '\0';

    Serial.print("Message received:");
    Serial.println(buff);

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, buff);
    JsonObject obj = doc.as<JsonObject>();

    bool relay_on = obj["relay_on"];

    if (relay_on)
        digitalWrite(PIN_WIRE_SCL, HIGH);
    else
        digitalWrite(PIN_WIRE_SCL, LOW);
}

void reconnectMQTTClient()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");

        if (client.connect(CLIENT_NAME.c_str()))
        {
            Serial.println("connected");
            client.subscribe(SERVER_COMMAND_TOPIC.c_str());
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
    client.setCallback(clientCallback);
    reconnectMQTTClient();
}

void setup()
{
	Serial.begin(9600);

	while (!Serial)
		; // Wait for Serial to be ready

	delay(1000);

    pinMode(A0, INPUT);
    pinMode(PIN_WIRE_SCL, OUTPUT);

    connectWiFi();
    createMQTTClient();
}

void loop()
{
    reconnectMQTTClient();
    client.loop();

    int soil_moisture = analogRead(A0);

    DynamicJsonDocument doc(1024);
    doc["soil_moisture"] = soil_moisture;

    string telemetry;
    JsonObject obj = doc.as<JsonObject>();
    serializeJson(obj, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());

    delay(10000);
}
