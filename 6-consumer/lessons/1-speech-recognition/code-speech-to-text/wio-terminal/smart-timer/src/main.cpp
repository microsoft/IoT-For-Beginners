#include <Arduino.h>
#include <rpcWiFi.h>
#include <sfud.h>
#include <SPI.h>

#include "config.h"
#include "mic.h"
#include "speech_to_text.h"

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

    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);

    pinMode(WIO_KEY_C, INPUT_PULLUP);

    mic.init();

    speechToText.init();

    Serial.println("Ready.");
}

void processAudio()
{
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
}

void loop()
{
    if (digitalRead(WIO_KEY_C) == LOW && !mic.isRecording())
    {
        Serial.println("Starting recording...");
        mic.startRecording();
    }

    if (!mic.isRecording() && mic.isRecordingReady())
    {
        Serial.println("Finished recording");

        processAudio();

        mic.reset();
    }
}