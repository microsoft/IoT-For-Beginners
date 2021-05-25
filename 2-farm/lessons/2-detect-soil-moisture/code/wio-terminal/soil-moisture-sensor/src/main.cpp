#include <Arduino.h>

void setup()
{
    pinMode(A0, INPUT);
}

void loop()
{
    int soil_moisture = analogRead(A0);
    
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);

    delay(5000);
}