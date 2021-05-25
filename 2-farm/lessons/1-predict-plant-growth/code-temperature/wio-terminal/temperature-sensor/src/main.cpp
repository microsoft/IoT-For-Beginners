#include <Arduino.h>
#include <DHT.h>
#include <SPI.h>

#include "config.h"

DHT dht(D0, DHT11);

void setup()
{
    Serial.begin(9600);

    while (!Serial)
        ; // Wait for Serial to be ready

    delay(1000);

    dht.begin();
}

void loop()
{
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);
    Serial.print("Temperature: ");
    Serial.print(temp_hum_val[1]);
    Serial.println ("°C");

    delay(10000);
}