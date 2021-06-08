#include <Arduino.h>
#include <rpcWiFi.h>
#include "SD/Seeed_SD.h"
#include <Seeed_FS.h>
#include <SPI.h>

#include "config.h"
#include "camera.h"

Camera camera = Camera(JPEG, OV2640_640x480);

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

void setupSDCard()
{
    while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
    {
        Serial.println("SD Card Error");
    }
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

    setupSDCard();
}

int fileNum = 1;

void saveToSDCard(byte *buffer, uint32_t length)
{
    char buff[16];
    sprintf(buff, "%d.jpg", fileNum);
    fileNum++;

    File outFile = SD.open(buff, FILE_WRITE );
    outFile.write(buffer, length);
    outFile.close();

    Serial.print("Image written to file ");
    Serial.println(buff);
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

        saveToSDCard(buffer, length);
        
        delete(buffer);
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