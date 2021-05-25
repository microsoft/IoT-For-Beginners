#include <Arduino.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <PubSubClient.h>
#include <rpcWiFi.h>
#include <SPI.h>

#include "config.h"

DHT dht(D0, DHT11);

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

    dht.begin();

    connectWiFi();
    createMQTTClient();
}

void loop()
{
    reconnectMQTTClient();
    client.loop();

    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];

    string telemetry;
    JsonObject obj = doc.as<JsonObject>();
    serializeJson(obj, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());

    delay(10 * 60 * 1000);
}
