#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

#include "config.h"

class LanguageUnderstanding
{
public:
    int GetTimerDuration(String text)
    {
        DynamicJsonDocument doc(1024);
        doc["text"] = text;

        String body;
        serializeJson(doc, body);

        HTTPClient httpClient;
        httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

        int httpResponseCode = httpClient.POST(body);

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
    WiFiClient _client;
};

LanguageUnderstanding languageUnderstanding;