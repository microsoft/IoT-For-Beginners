#include <Arduino.h>

void setup()
{
    pinMode(A0, INPUT);
    pinMode(PIN_WIRE_SCL, OUTPUT);
}

void loop()
{
    int soil_moisture = analogRead(A0);
    
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);

    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }

    delay(10000);
}