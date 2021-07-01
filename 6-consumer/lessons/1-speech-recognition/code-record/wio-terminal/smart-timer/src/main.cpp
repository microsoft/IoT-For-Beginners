#include <Arduino.h>
#include <sfud.h>
#include <SPI.h>

#include "mic.h"

void setup()
{
    Serial.begin(9600);

    while (!Serial)
        ; // Wait for Serial to be ready

    delay(1000);

    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);

    pinMode(WIO_KEY_C, INPUT_PULLUP);

    mic.init();

    Serial.println("Ready.");
}

void processAudio()
{

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