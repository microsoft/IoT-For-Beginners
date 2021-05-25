#include <Arduino.h>
#include <wiring_private.h>
#include <TinyGPS++.h>

static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
TinyGPSPlus gps;

void setup()
{
	Serial.begin(9600);

	while (!Serial)
		; // Wait for Serial to be ready

	delay(1000);

	Serial3.begin(9600);

	while (!Serial3)
		; // Wait for Serial3 to be ready

	delay(1000);

	pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
}

void print_gps_data()
{
	if (gps.encode(Serial3.read()))
	{
		if (gps.location.isValid())
		{
			Serial.print(gps.location.lat(), 6);
			Serial.print(F(","));
			Serial.print(gps.location.lng(), 6);
			Serial.print(" - from ");
			Serial.print(gps.satellites.value());
			Serial.println(" satellites");
		}
	}
}

void loop()
{
	while (Serial3.available() > 0)
	{
		print_gps_data();
	}

	delay(1000);
}

void SERCOM3_0_Handler()
{
	Serial3.IrqHandler();
}

void SERCOM3_1_Handler()
{
	Serial3.IrqHandler();
}

void SERCOM3_2_Handler()
{
	Serial3.IrqHandler();
}

void SERCOM3_3_Handler()
{
	Serial3.IrqHandler();
}