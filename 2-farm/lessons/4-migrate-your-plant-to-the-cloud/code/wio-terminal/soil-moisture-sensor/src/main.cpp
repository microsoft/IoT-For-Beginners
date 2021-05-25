#include <Arduino.h>
#include <ArduinoJson.h>
#include <rpcWiFi.h>
#include <SPI.h>

#include "config.h"

#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <iothubtransportmqtt.h>
#include "ntp.h"

IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;

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

int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
{
    Serial.printf("Direct method received %s\r\n", method_name);

    if (strcmp(method_name, "relay_on") == 0)
    {
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else if (strcmp(method_name, "relay_off") == 0)
    {
        digitalWrite(PIN_WIRE_SCL, LOW);
    }

    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
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
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
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

    pinMode(A0, INPUT);
    pinMode(PIN_WIRE_SCL, OUTPUT);

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

void loop()
{
    int soil_moisture = analogRead(A0);

    DynamicJsonDocument doc(1024);
    doc["soil_moisture"] = soil_moisture;

    string telemetry;
    JsonObject obj = doc.as<JsonObject>();
    serializeJson(obj, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());
    sendTelemetry(telemetry.c_str());

    work_delay(10000);
}
