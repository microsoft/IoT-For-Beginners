#pragma once

#include <string>

using namespace std;

// WiFi credentials
const char *SSID = "<SSID>";
const char *PASSWORD = "<PASSWORD>";

// MQTT settings
const string ID = "<ID>";

const string BROKER = "test.mosquitto.org";
const string CLIENT_NAME = ID + "temperature_sensor_client";

const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";