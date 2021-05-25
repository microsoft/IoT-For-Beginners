#include <Arduino.h>

void setup()
{
	Serial.begin(9600);

	while (!Serial)
		; // Wait for Serial to be ready

	delay(1000);

    pinMode(WIO_LIGHT, INPUT);
    pinMode(D0, OUTPUT);
}

void loop()
{
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);

    if (light < 200)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }

	delay(1000);
}