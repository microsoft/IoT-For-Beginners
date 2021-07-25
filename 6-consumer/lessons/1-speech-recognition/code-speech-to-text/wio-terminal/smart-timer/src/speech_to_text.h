#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#include "config.h"
#include "flash_stream.h"

class SpeechToText
{
public:
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _speech_client.setCACert(SPEECH_CERTIFICATE);
        _access_token = getAccessToken();
    }

    String convertSpeechToText()
    {
        char url[128];
        sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

        HTTPClient httpClient;
        httpClient.begin(_speech_client, url);

        httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
        httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
        httpClient.addHeader("Accept", "application/json;text/xml");

        Serial.println("Sending speech...");

        FlashStream stream;
        int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

        Serial.println("Speech sent!");

        String text = "";

        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
            Serial.println(result);

            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());

            JsonObject obj = doc.as<JsonObject>();
            text = obj["DisplayText"].as<String>();
        }
        else if (httpResponseCode == 401)
        {
            Serial.println("Access token expired, trying again with a new token");
            _access_token = getAccessToken();
            return convertSpeechToText();
        }
        else
        {
            Serial.print("Failed to convert text to speech - error ");
            Serial.println(httpResponseCode);
        }

        httpClient.end();

        return text;
    }

    String AccessToken()
    {
        return _access_token;
    }

private:
    String getAccessToken()
    {
        char url[128];
        sprintf(url, TOKEN_URL, SPEECH_LOCATION);

        HTTPClient httpClient;
        httpClient.begin(_token_client, url);

        httpClient.addHeader("Ocp-Apim-Subscription-Key", SPEECH_API_KEY);
        int httpResultCode = httpClient.POST("{}");

        if (httpResultCode != 200)
        {
            Serial.println("Error getting access token, trying again...");
            delay(10000);
            return getAccessToken();
        }

        Serial.println("Got access token.");
        String result = httpClient.getString();

        httpClient.end();

        return result;
    }

    WiFiClientSecure _token_client;
    WiFiClientSecure _speech_client;
    String _access_token;
};

SpeechToText speechToText;
