<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-27T10:52:33+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "pa"
}
-->
# ਨਜ਼ਦੀਕੀ ਦਾ ਪਤਾ ਲਗਾਓ - ਰਾਸਪਬੈਰੀ ਪਾਈ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਆਪਣੇ ਰਾਸਪਬੈਰੀ ਪਾਈ ਵਿੱਚ ਇੱਕ ਨਜ਼ਦੀਕੀ ਸੈਂਸਰ ਜੋੜੋਗੇ ਅਤੇ ਇਸ ਤੋਂ ਦੂਰੀ ਪੜ੍ਹੋਗੇ।

## ਹਾਰਡਵੇਅਰ

ਰਾਸਪਬੈਰੀ ਪਾਈ ਨੂੰ ਇੱਕ ਨਜ਼ਦੀਕੀ ਸੈਂਸਰ ਦੀ ਲੋੜ ਹੈ।

ਤੁਹਾਡਾ ਸੈਂਸਰ [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html) ਹੈ। ਇਹ ਸੈਂਸਰ ਦੂਰੀ ਦਾ ਪਤਾ ਲਗਾਉਣ ਲਈ ਲੇਜ਼ਰ ਰੇਂਜਿੰਗ ਮੋਡੀਊਲ ਵਰਤਦਾ ਹੈ। ਇਸ ਸੈਂਸਰ ਦੀ ਰੇਂਜ 10mm ਤੋਂ 2000mm (1cm - 2m) ਹੈ, ਅਤੇ ਇਹ ਇਸ ਰੇਂਜ ਵਿੱਚ ਕਾਫੀ ਸਹੀ ਮਾਪ ਦਿੰਦਾ ਹੈ। 1000mm ਤੋਂ ਵੱਧ ਦੂਰੀਆਂ ਨੂੰ 8109mm ਵਜੋਂ ਦਰਸਾਇਆ ਜਾਂਦਾ ਹੈ।

ਲੇਜ਼ਰ ਰੇਂਜਫਾਈਂਡਰ ਸੈਂਸਰ ਦੇ ਪਿੱਛੇ ਹੈ, Grove ਸਾਕਟ ਦੇ ਵਿਰੁੱਧ ਪਾਸੇ।

ਇਹ ਇੱਕ I²C ਸੈਂਸਰ ਹੈ।

### ਟਾਈਮ ਆਫ ਫਲਾਈਟ ਸੈਂਸਰ ਨੂੰ ਕਨੈਕਟ ਕਰੋ

Grove ਟਾਈਮ ਆਫ ਫਲਾਈਟ ਸੈਂਸਰ ਨੂੰ ਰਾਸਪਬੈਰੀ ਪਾਈ ਨਾਲ ਜੋੜਿਆ ਜਾ ਸਕਦਾ ਹੈ।

#### ਕੰਮ - ਟਾਈਮ ਆਫ ਫਲਾਈਟ ਸੈਂਸਰ ਨੂੰ ਜੋੜੋ

ਟਾਈਮ ਆਫ ਫਲਾਈਟ ਸੈਂਸਰ ਨੂੰ ਜੋੜੋ।

![A grove time of flight sensor](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.pa.png)

1. Grove ਕੇਬਲ ਦੇ ਇੱਕ ਸਿਰੇ ਨੂੰ ਟਾਈਮ ਆਫ ਫਲਾਈਟ ਸੈਂਸਰ ਦੇ ਸਾਕਟ ਵਿੱਚ ਪਾਓ। ਇਹ ਕੇਵਲ ਇੱਕ ਹੀ ਦਿਸ਼ਾ ਵਿੱਚ ਜਾਵੇਗੀ।

1. ਰਾਸਪਬੈਰੀ ਪਾਈ ਨੂੰ ਬੰਦ ਰੱਖਦੇ ਹੋਏ, Grove ਕੇਬਲ ਦੇ ਦੂਜੇ ਸਿਰੇ ਨੂੰ Grove Base hat ਦੇ I²C ਸਾਕਟ ਵਿੱਚ ਜੋੜੋ। ਇਹ ਸਾਕਟ ਹੇਠਲੀ ਲਾਈਨ ਵਿੱਚ ਹਨ, GPIO ਪਿੰਸ ਦੇ ਵਿਰੁੱਧ ਪਾਸੇ ਅਤੇ ਕੈਮਰਾ ਕੇਬਲ ਸਲਾਟ ਦੇ ਨੇੜੇ।

![The grove time of flight sensor connected to the I squared C socket](../../../../../translated_images/pi-time-of-flight-sensor.58c8dc04eb3bfb57a7c3019f031433ef4d798d4d7603d565afbf6f3802840dba.pa.png)

## ਟਾਈਮ ਆਫ ਫਲਾਈਟ ਸੈਂਸਰ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ

ਹੁਣ ਰਾਸਪਬੈਰੀ ਪਾਈ ਨੂੰ ਜੋੜੇ ਗਏ ਟਾਈਮ ਆਫ ਫਲਾਈਟ ਸੈਂਸਰ ਨੂੰ ਵਰਤਣ ਲਈ ਪ੍ਰੋਗਰਾਮ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

### ਕੰਮ - ਟਾਈਮ ਆਫ ਫਲਾਈਟ ਸੈਂਸਰ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ

ਡਿਵਾਈਸ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ।

1. ਪਾਈ ਨੂੰ ਚਾਲੂ ਕਰੋ ਅਤੇ ਇਸ ਦੇ ਬੂਟ ਹੋਣ ਦੀ ਉਡੀਕ ਕਰੋ।

1. `fruit-quality-detector` ਕੋਡ ਨੂੰ VS Code ਵਿੱਚ ਖੋਲ੍ਹੋ, ਜਾਂ ਤਾਂ ਸਿੱਧੇ ਪਾਈ 'ਤੇ ਜਾਂ Remote SSH ਐਕਸਟੈਂਸ਼ਨ ਰਾਹੀਂ ਕਨੈਕਟ ਕਰਕੇ।

1. rpi-vl53l0x Pip ਪੈਕੇਜ ਇੰਸਟਾਲ ਕਰੋ, ਜੋ ਕਿ VL53L0X ਟਾਈਮ-ਆਫ-ਫਲਾਈਟ ਦੂਰੀ ਸੈਂਸਰ ਨਾਲ ਇੰਟਰੈਕਟ ਕਰਨ ਵਾਲਾ ਇੱਕ ਪਾਇਥਨ ਪੈਕੇਜ ਹੈ। ਇਸ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ Pip ਕਮਾਂਡ ਨਾਲ ਇੰਸਟਾਲ ਕਰੋ:

    ```sh
    pip install rpi-vl53l0x
    ```

1. ਇਸ ਪ੍ਰੋਜੈਕਟ ਵਿੱਚ ਇੱਕ ਨਵੀਂ ਫਾਈਲ ਬਣਾਓ ਜਿਸਦਾ ਨਾਮ `distance-sensor.py` ਰੱਖੋ।

    > 💁 ਕਈ IoT ਡਿਵਾਈਸਾਂ ਨੂੰ ਸਿਮੂਲੇਟ ਕਰਨ ਦਾ ਆਸਾਨ ਤਰੀਕਾ ਇਹ ਹੈ ਕਿ ਹਰ ਇੱਕ ਨੂੰ ਵੱਖ-ਵੱਖ ਪਾਇਥਨ ਫਾਈਲ ਵਿੱਚ ਕਰੋ, ਫਿਰ ਉਨ੍ਹਾਂ ਨੂੰ ਇੱਕੋ ਸਮੇਂ ਚਲਾਓ।

1. ਇਸ ਫਾਈਲ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    ਇਹ Grove I²C ਬੱਸ ਲਾਇਬ੍ਰੇਰੀ ਅਤੇ Grove ਟਾਈਮ ਆਫ ਫਲਾਈਟ ਸੈਂਸਰ ਵਿੱਚ ਬਣੇ ਕੋਰ ਸੈਂਸਰ ਹਾਰਡਵੇਅਰ ਲਈ ਸੈਂਸਰ ਲਾਇਬ੍ਰੇਰੀ ਨੂੰ ਇੰਪੋਰਟ ਕਰਦਾ ਹੈ।

1. ਇਸ ਦੇ ਹੇਠਾਂ, ਸੈਂਸਰ ਤੱਕ ਪਹੁੰਚ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    ਇਹ ਕੋਡ Grove I²C ਬੱਸ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇੱਕ ਦੂਰੀ ਸੈਂਸਰ ਡਿਕਲੇਅਰ ਕਰਦਾ ਹੈ, ਫਿਰ ਸੈਂਸਰ ਨੂੰ ਸ਼ੁਰੂ ਕਰਦਾ ਹੈ।

1. ਆਖਿਰ ਵਿੱਚ, ਦੂਰੀਆਂ ਪੜ੍ਹਨ ਲਈ ਇੱਕ ਅਨੰਤ ਲੂਪ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    ਇਹ ਕੋਡ ਸੈਂਸਰ ਤੋਂ ਪੜ੍ਹਨ ਲਈ ਇੱਕ ਮੁੱਲ ਦੀ ਉਡੀਕ ਕਰਦਾ ਹੈ, ਫਿਰ ਇਸ ਨੂੰ ਕਨਸੋਲ ਵਿੱਚ ਪ੍ਰਿੰਟ ਕਰਦਾ ਹੈ।

1. ਇਸ ਕੋਡ ਨੂੰ ਚਲਾਓ।

    > 💁 ਯਾਦ ਰੱਖੋ ਕਿ ਇਸ ਫਾਈਲ ਦਾ ਨਾਮ `distance-sensor.py` ਹੈ! ਇਸ ਨੂੰ ਪਾਇਥਨ ਰਾਹੀਂ ਚਲਾਓ, ਨਾ ਕਿ `app.py` ਰਾਹੀਂ।

1. ਤੁਸੀਂ ਕਨਸੋਲ ਵਿੱਚ ਦੂਰੀ ਮਾਪ ਦੇਖੋਗੇ। ਸੈਂਸਰ ਦੇ ਨੇੜੇ ਵਸਤੂਆਂ ਰੱਖੋ ਅਤੇ ਤੁਸੀਂ ਦੂਰੀ ਮਾਪ ਦੇਖੋਗੇ:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    ਰੇਂਜਫਾਈਂਡਰ ਸੈਂਸਰ ਦੇ ਪਿੱਛੇ ਹੈ, ਇਸ ਲਈ ਦੂਰੀ ਮਾਪਣ ਸਮੇਂ ਸਹੀ ਪਾਸੇ ਦੀ ਵਰਤੋਂ ਯਕੀਨੀ ਬਣਾਓ।

    ![The rangefinder on the back of the time of flight sensor pointing at a banana](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4525dc26b4cdc71a076407aba3e72ba113ba2e38febae92c5.pa.png)

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਨਜ਼ਦੀਕੀ ਸੈਂਸਰ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀਤਾ ਲਈ ਯਤਨਸ਼ੀਲ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚੀਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।