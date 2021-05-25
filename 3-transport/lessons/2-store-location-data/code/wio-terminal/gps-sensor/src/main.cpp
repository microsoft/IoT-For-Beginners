#include <Arduino.h>
#include <ArduinoJson.h>
#include <rpcWiFi.h>
#include <SPI.h>
#include <wiring_private.h>

#include "config.h"

#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <iothubtransportmqtt.h>
#include "ntp.h"

#include <TinyGPS++.h>

IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
TinyGPSPlus gps;

static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
{
    if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
    {
        Serial.println("The device client is connected to iothub");
    }
    else
    {
        Serial.println("The device client has been disconnected");
    }
}

void connectIoTHub()
{
    IoTHub_Init();

    _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
    
    if (_device_ll_handle == NULL)
    {
        Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
        return;
    }
    
    IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
}

void sendTelemetry(const char *telemetry)
{
    IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
    IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
    IoTHubMessage_Destroy(message_handle);
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

    connectWiFi();

    initTime();

    connectIoTHub();
	delay(2000);
}

void work_delay(int delay_time)
{
    int current = 0;
    do
    {
        IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
        delay(100);
        current += 100;
    } while (current < delay_time);
}

void send_gps_data()
{
	if (gps.encode(Serial3.read()))
	{
		if (gps.location.isValid())
		{
            DynamicJsonDocument doc(1024);
            doc["gps"]["lat"] = gps.location.lat();
            doc["gps"]["lon"] = gps.location.lng();

            string telemetry;
            JsonObject obj = doc.as<JsonObject>();
            serializeJson(obj, telemetry);

            Serial.print("Sending telemetry ");
            Serial.println(telemetry.c_str());
            sendTelemetry(telemetry.c_str());
		}
	}
}

void loop()
{
    while (Serial3.available() > 0)
	{
		send_gps_data();
	}

    work_delay(60000);
}
