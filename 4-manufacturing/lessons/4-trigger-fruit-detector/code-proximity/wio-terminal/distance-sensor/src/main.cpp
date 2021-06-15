#include <Arduino.h>
#include "Seeed_vl53l0x.h"

Seeed_vl53l0x VL53L0X;

void setup()
{
    Serial.begin(9600);

    while (!Serial)
        ; // Wait for Serial to be ready

    delay(1000);

    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
}

void loop()
{
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);

    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
}