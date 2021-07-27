#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

#include "config.h"

class TextTranslator
{
public:
    String translateText(String text, String from_language, String to_language)
    {
        DynamicJsonDocument doc(1024);
        doc["text"] = text;
        doc["from_language"] = from_language;
        doc["to_language"] = to_language;

        String body;
        serializeJson(doc, body);

        Serial.print("Translating ");
        Serial.print(text);
        Serial.print(" from ");
        Serial.print(from_language);
        Serial.print(" to ");
        Serial.println(to_language);

        HTTPClient httpClient;
        httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

        int httpResponseCode = httpClient.POST(body);

        String translated_text = "";

        if (httpResponseCode == 200)
        {
            translated_text = httpClient.getString();
            Serial.print("Translated: ");
            Serial.println(translated_text);
        }
        else
        {
            Serial.print("Failed to translate text - error ");
            Serial.println(httpResponseCode);
        }

        httpClient.end();

        return translated_text;
    }

private:
    WiFiClient _client;
};

TextTranslator textTranslator;
