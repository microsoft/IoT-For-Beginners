#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <rpcWiFi.h>
#include "SD/Seeed_SD.h"
#include <Seeed_FS.h>
#include <SPI.h>
#include <WiFiClient.h>

#include "config.h"
#include "camera.h"

Camera camera = Camera(JPEG, OV2640_640x480);

WiFiClient client;

void setupCamera()
{
    pinMode(PIN_SPI_SS, OUTPUT);
    digitalWrite(PIN_SPI_SS, HIGH);

    Wire.begin();
    SPI.begin();

    if (!camera.init())
    {
        Serial.println("Error setting up the camera!");
    }
}

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

void setup()
{
    Serial.begin(9600);

    while (!Serial)
        ; // Wait for Serial to be ready

    delay(1000);

    connectWiFi();

    setupCamera();

    pinMode(WIO_KEY_C, INPUT_PULLUP);
}

void classifyImage(byte *buffer, uint32_t length)
{
    HTTPClient httpClient;
    httpClient.begin(client, PREDICTION_URL);
    httpClient.addHeader("Content-Type", "application/octet-stream");

    int httpResponseCode = httpClient.POST(buffer, length);

    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        JsonArray predictions = obj["predictions"].as<JsonArray>();

        for(JsonVariant prediction : predictions) 
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();

            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }

    httpClient.end();
}

void buttonPressed()
{
    camera.startCapture();

    while (!camera.captureReady())
        delay(100);

    Serial.println("Image captured");

    byte *buffer;
    uint32_t length;

    if (camera.readImageToBuffer(&buffer, length))
    {
        Serial.print("Image read to buffer with length ");
        Serial.println(length);

        classifyImage(buffer, length);

        delete (buffer);
    }
}

void loop()
{
    if (digitalRead(WIO_KEY_C) == LOW)
    {
        buttonPressed();
        delay(2000);
    }

    delay(200);
}