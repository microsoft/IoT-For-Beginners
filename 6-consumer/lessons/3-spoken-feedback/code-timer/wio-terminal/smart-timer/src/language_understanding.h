#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>

#include "config.h"

class LanguageUnderstanding
{
public:
    LanguageUnderstanding()
    {
        _client.setCACert(FUNCTIONS_CERTIFICATE);
    }

    int GetTimerDuration(String text)
    {
        DynamicJsonDocument doc(1024);
        doc["text"] = text;

        String body;
        JsonObject obj = doc.as<JsonObject>();
        serializeJson(obj, body);

        HTTPClient httpClient;
        httpClient.begin(_client, FUNCTION_URL);

        int httpResponseCode = httpClient.sendRequest("POST", body);

        int seconds = 0;
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
            Serial.println(result);

            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());

            JsonObject obj = doc.as<JsonObject>();
            seconds = obj["seconds"].as<int>();
        }
        else
        {
            Serial.print("Failed to understand text - error ");
            Serial.println(httpResponseCode);
        }

        httpClient.end();

        return seconds;
    }

private:
    // WiFiClient _client;
    WiFiClientSecure _client;
};

LanguageUnderstanding languageUnderstanding;