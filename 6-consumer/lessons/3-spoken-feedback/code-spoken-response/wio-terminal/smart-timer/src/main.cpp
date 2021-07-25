#include <Arduino.h>
#include <arduino-timer.h>
#include <rpcWiFi.h>
#include <sfud.h>
#include <SPI.h>

#include "config.h"
#include "language_understanding.h"
#include "mic.h"
#include "speech_to_text.h"
#include "text_to_speech.h"

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
    textToSpeech.init();

    Serial.println("Ready.");
}

auto timer = timer_create_default();

void say(String text)
{
    Serial.println(text);
    textToSpeech.convertTextToSpeech(text);
}

bool timerExpired(void *announcement)
{
    say((char *)announcement);
    return false;
}

void processAudio()
{
    String text = speechToText.convertSpeechToText();
    Serial.println(text);

    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;

    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";

    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";

    say(begin_message);

    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
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

    timer.tick();
}
