# ਨਜ਼ਦੀਕੀ ਦਾ ਪਤਾ ਲਗਾਓ - Wio Terminal

ਇਸ ਪਾਠ ਦੇ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਆਪਣੇ Wio Terminal ਵਿੱਚ ਇੱਕ ਨਜ਼ਦੀਕੀ ਸੈਂਸਰ ਸ਼ਾਮਲ ਕਰੋਗੇ ਅਤੇ ਇਸ ਤੋਂ ਦੂਰੀ ਪੜ੍ਹੋਗੇ।

## ਹਾਰਡਵੇਅਰ

Wio Terminal ਨੂੰ ਇੱਕ ਨਜ਼ਦੀਕੀ ਸੈਂਸਰ ਦੀ ਲੋੜ ਹੈ।

ਤੁਸੀਂ ਜੋ ਸੈਂਸਰ ਵਰਤੋਗੇ ਉਹ ਹੈ [Grove Time of Flight ਦੂਰੀ ਸੈਂਸਰ](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)। ਇਹ ਸੈਂਸਰ ਦੂਰੀ ਦਾ ਪਤਾ ਲਗਾਉਣ ਲਈ ਲੇਜ਼ਰ ਰੇਂਜਿੰਗ ਮੋਡੀਊਲ ਦੀ ਵਰਤੋਂ ਕਰਦਾ ਹੈ। ਇਸ ਸੈਂਸਰ ਦੀ ਰੇਂਜ 10mm ਤੋਂ 2000mm (1cm - 2m) ਹੈ, ਅਤੇ ਇਹ ਇਸ ਰੇਂਜ ਵਿੱਚ ਕਾਫ਼ੀ ਸਹੀ ਮਾਪ ਦਿੰਦਾ ਹੈ, ਜਿੱਥੇ 1000mm ਤੋਂ ਵੱਧ ਦੂਰੀਆਂ ਨੂੰ 8109mm ਵਜੋਂ ਦਰਸਾਇਆ ਜਾਂਦਾ ਹੈ।

ਲੇਜ਼ਰ ਰੇਂਜਫਾਈਂਡਰ ਸੈਂਸਰ ਦੇ ਪਿੱਛੇ ਵਾਲੇ ਪਾਸੇ ਹੈ, ਜੋ Grove ਸਾਕਟ ਦੇ ਉਲਟ ਪਾਸੇ ਹੈ।

ਇਹ ਇੱਕ I²C ਸੈਂਸਰ ਹੈ।

### Time of Flight ਸੈਂਸਰ ਨੂੰ ਜੋੜੋ

Grove Time of Flight ਸੈਂਸਰ ਨੂੰ Wio Terminal ਨਾਲ ਜੋੜਿਆ ਜਾ ਸਕਦਾ ਹੈ।

#### ਕੰਮ - Time of Flight ਸੈਂਸਰ ਨੂੰ ਜੋੜੋ

Time of Flight ਸੈਂਸਰ ਨੂੰ ਜੋੜੋ।

![ਇੱਕ Grove Time of Flight ਸੈਂਸਰ](../../../../../translated_images/pa/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Grove ਕੇਬਲ ਦੇ ਇੱਕ ਸਿਰੇ ਨੂੰ Time of Flight ਸੈਂਸਰ ਦੇ ਸਾਕਟ ਵਿੱਚ ਪਾਓ। ਇਹ ਸਿਰਫ਼ ਇੱਕ ਹੀ ਦਿਸ਼ਾ ਵਿੱਚ ਜਾਵੇਗਾ।

1. ਆਪਣੇ Wio Terminal ਨੂੰ ਆਪਣੇ ਕੰਪਿਊਟਰ ਜਾਂ ਹੋਰ ਪਾਵਰ ਸਪਲਾਈ ਤੋਂ ਡਿਸਕਨੈਕਟ ਕਰਕੇ ਰੱਖੋ। ਫਿਰ Grove ਕੇਬਲ ਦੇ ਦੂਜੇ ਸਿਰੇ ਨੂੰ Wio Terminal ਦੇ ਖੱਬੇ ਪਾਸੇ ਵਾਲੇ Grove ਸਾਕਟ ਵਿੱਚ ਪਾਓ ਜਦੋਂ ਤੁਸੀਂ ਸਕ੍ਰੀਨ ਵੱਲ ਦੇਖ ਰਹੇ ਹੋ। ਇਹ ਸਾਕਟ ਪਾਵਰ ਬਟਨ ਦੇ ਸਭ ਤੋਂ ਨੇੜੇ ਹੈ। ਇਹ ਇੱਕ ਕਾਂਬਾਈਨਡ ਡਿਜ਼ਿਟਲ ਅਤੇ I²C ਸਾਕਟ ਹੈ।

![Time of Flight ਸੈਂਸਰ Wio Terminal ਦੇ ਖੱਬੇ ਸਾਕਟ ਨਾਲ ਜੁੜਿਆ ਹੋਇਆ](../../../../../translated_images/pa/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. ਹੁਣ ਤੁਸੀਂ Wio Terminal ਨੂੰ ਆਪਣੇ ਕੰਪਿਊਟਰ ਨਾਲ ਜੁੜ ਸਕਦੇ ਹੋ।

## Time of Flight ਸੈਂਸਰ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ

ਹੁਣ Wio Terminal ਨੂੰ ਜੁੜੇ ਹੋਏ Time of Flight ਸੈਂਸਰ ਦੀ ਵਰਤੋਂ ਕਰਨ ਲਈ ਪ੍ਰੋਗਰਾਮ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

### ਕੰਮ - Time of Flight ਸੈਂਸਰ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ

1. PlatformIO ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇੱਕ ਨਵਾਂ Wio Terminal ਪ੍ਰੋਜੈਕਟ ਬਣਾਓ। ਇਸ ਪ੍ਰੋਜੈਕਟ ਦਾ ਨਾਮ `distance-sensor` ਰੱਖੋ। `setup` ਫੰਕਸ਼ਨ ਵਿੱਚ ਸੀਰੀਅਲ ਪੋਰਟ ਨੂੰ ਕਨਫਿਗਰ ਕਰਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ।

1. ਪ੍ਰੋਜੈਕਟ ਦੇ `platformio.ini` ਫਾਈਲ ਵਿੱਚ Seeed Grove Time of Flight ਦੂਰੀ ਸੈਂਸਰ ਲਾਇਬ੍ਰੇਰੀ ਲਈ ਇੱਕ ਲਾਇਬ੍ਰੇਰੀ ਡਿਪੈਂਡੈਂਸੀ ਸ਼ਾਮਲ ਕਰੋ:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. `main.cpp` ਵਿੱਚ ਮੌਜੂਦਾ include ਡਾਇਰੈਕਟਿਵਜ਼ ਦੇ ਹੇਠਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ Time of Flight ਸੈਂਸਰ ਨਾਲ ਇੰਟਰੈਕਟ ਕਰਨ ਲਈ `Seeed_vl53l0x` ਕਲਾਸ ਦਾ ਇੱਕ ਇੰਸਟੈਂਸ ਡਿਕਲੇਅਰ ਕੀਤਾ ਜਾ ਸਕੇ:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. ਸੈਂਸਰ ਨੂੰ ਸ਼ੁਰੂ ਕਰਨ ਲਈ `setup` ਫੰਕਸ਼ਨ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. `loop` ਫੰਕਸ਼ਨ ਵਿੱਚ, ਸੈਂਸਰ ਤੋਂ ਇੱਕ ਮਾਪ ਪੜ੍ਹੋ:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    ਇਹ ਕੋਡ ਡੇਟਾ ਸਟ੍ਰਕਚਰ ਨੂੰ ਸ਼ੁਰੂ ਕਰਦਾ ਹੈ ਜਿਸ ਵਿੱਚ ਡੇਟਾ ਪੜ੍ਹਿਆ ਜਾਵੇਗਾ, ਫਿਰ ਇਸਨੂੰ `PerformSingleRangingMeasurement` ਮੈਥਡ ਵਿੱਚ ਪਾਸ ਕਰਦਾ ਹੈ ਜਿੱਥੇ ਇਹ ਦੂਰੀ ਦੇ ਮਾਪ ਨਾਲ ਭਰਿਆ ਜਾਵੇਗਾ।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, ਦੂਰੀ ਦੇ ਮਾਪ ਨੂੰ ਲਿਖੋ, ਫਿਰ 1 ਸਕਿੰਟ ਲਈ ਡਿਲੇ ਕਰੋ:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. ਇਸ ਕੋਡ ਨੂੰ ਬਿਲਡ ਕਰੋ, ਅੱਪਲੋਡ ਕਰੋ ਅਤੇ ਚਲਾਓ। ਤੁਸੀਂ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਨਾਲ ਦੂਰੀ ਦੇ ਮਾਪ ਦੇਖ ਸਕੋਗੇ। ਸੈਂਸਰ ਦੇ ਨੇੜੇ ਵਸਤੂਆਂ ਰੱਖੋ ਅਤੇ ਤੁਸੀਂ ਦੂਰੀ ਦੇ ਮਾਪ ਨੂੰ ਦੇਖੋਗੇ:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    ਰੇਂਜਫਾਈਂਡਰ ਸੈਂਸਰ ਦੇ ਪਿੱਛੇ ਵਾਲੇ ਪਾਸੇ ਹੈ, ਇਸ ਲਈ ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਤੁਸੀਂ ਦੂਰੀ ਮਾਪਣ ਸਮੇਂ ਸਹੀ ਪਾਸੇ ਦੀ ਵਰਤੋਂ ਕਰ ਰਹੇ ਹੋ।

    ![Time of Flight ਸੈਂਸਰ ਦੇ ਪਿੱਛੇ ਵਾਲੇ ਪਾਸੇ ਤੋਂ ਇੱਕ ਕੇਲੇ ਵੱਲ ਇਸ਼ਾਰਾ ਕਰਦਾ ਰੇਂਜਫਾਈਂਡਰ](../../../../../translated_images/pa/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਨਜ਼ਦੀਕੀ ਸੈਂਸਰ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਾਰਨਾ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੱਜੇਪਣ ਹੋ ਸਕਦੇ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼, ਜੋ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਹੈ, ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।