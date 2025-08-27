<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-27T10:54:48+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "pa"
}
-->
# ਨਜ਼ਦੀਕੀ ਦਾ ਪਤਾ ਲਗਾਓ - ਵਰਚੁਅਲ IoT ਹਾਰਡਵੇਅਰ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਭਾਗ ਵਿੱਚ, ਤੁਸੀਂ ਆਪਣੇ ਵਰਚੁਅਲ IoT ਡਿਵਾਈਸ ਵਿੱਚ ਇੱਕ ਨਜ਼ਦੀਕੀ ਸੈਂਸਰ ਸ਼ਾਮਲ ਕਰੋਗੇ ਅਤੇ ਇਸ ਤੋਂ ਦੂਰੀ ਪੜ੍ਹੋਗੇ।

## ਹਾਰਡਵੇਅਰ

ਵਰਚੁਅਲ IoT ਡਿਵਾਈਸ ਇੱਕ ਨਕਲੀ ਦੂਰੀ ਸੈਂਸਰ ਦੀ ਵਰਤੋਂ ਕਰੇਗਾ।

ਇੱਕ ਭੌਤਿਕ IoT ਡਿਵਾਈਸ ਵਿੱਚ, ਤੁਸੀਂ ਦੂਰੀ ਦਾ ਪਤਾ ਲਗਾਉਣ ਲਈ ਲੇਜ਼ਰ ਰੇਂਜਿੰਗ ਮੋਡੀਊਲ ਵਾਲੇ ਸੈਂਸਰ ਦੀ ਵਰਤੋਂ ਕਰਦੇ ਹੋ।

### CounterFit ਵਿੱਚ ਦੂਰੀ ਸੈਂਸਰ ਸ਼ਾਮਲ ਕਰੋ

ਵਰਚੁਅਲ ਦੂਰੀ ਸੈਂਸਰ ਦੀ ਵਰਤੋਂ ਕਰਨ ਲਈ, ਤੁਹਾਨੂੰ ਇਸਨੂੰ CounterFit ਐਪ ਵਿੱਚ ਸ਼ਾਮਲ ਕਰਨਾ ਪਵੇਗਾ।

#### ਕੰਮ - CounterFit ਵਿੱਚ ਦੂਰੀ ਸੈਂਸਰ ਸ਼ਾਮਲ ਕਰੋ

CounterFit ਐਪ ਵਿੱਚ ਦੂਰੀ ਸੈਂਸਰ ਸ਼ਾਮਲ ਕਰੋ।

1. VS Code ਵਿੱਚ `fruit-quality-detector` ਕੋਡ ਖੋਲ੍ਹੋ ਅਤੇ ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਵਰਚੁਅਲ ਵਾਤਾਵਰਣ ਐਕਟੀਵੇਟ ਹੈ।

1. ਇੱਕ ਹੋਰ Pip ਪੈਕੇਜ ਇੰਸਟਾਲ ਕਰੋ ਜੋ ਇੱਕ CounterFit ਸ਼ਿਮ ਇੰਸਟਾਲ ਕਰੇ ਜੋ ਦੂਰੀ ਸੈਂਸਰਾਂ ਨਾਲ ਗੱਲਬਾਤ ਕਰ ਸਕੇ, [rpi-vl53l0x Pip ਪੈਕੇਜ](https://pypi.org/project/rpi-vl53l0x/) ਦੀ ਨਕਲ ਕਰਕੇ। ਇਹ ਪੈਕੇਜ ਇੱਕ VL53L0X ਟਾਈਮ-ਆਫ-ਫਲਾਈਟ ਦੂਰੀ ਸੈਂਸਰ ਨਾਲ ਸੰਚਾਰ ਕਰਦਾ ਹੈ। ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਤੁਸੀਂ ਇਸਨੂੰ ਉਸ ਟਰਮੀਨਲ ਤੋਂ ਇੰਸਟਾਲ ਕਰ ਰਹੇ ਹੋ ਜਿੱਥੇ ਵਰਚੁਅਲ ਵਾਤਾਵਰਣ ਐਕਟੀਵੇਟ ਹੈ।

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. ਯਕੀਨੀ ਬਣਾਓ ਕਿ CounterFit ਵੈੱਬ ਐਪ ਚੱਲ ਰਿਹਾ ਹੈ।

1. ਇੱਕ ਦੂਰੀ ਸੈਂਸਰ ਬਣਾਓ:

    1. *Sensors* ਪੈਨ ਵਿੱਚ *Create sensor* ਬਾਕਸ ਵਿੱਚ, *Sensor type* ਡ੍ਰੌਪਡਾਊਨ ਵਿੱਚੋਂ *Distance* ਚੁਣੋ।

    1. *Units* ਨੂੰ `Millimeter` ਹੀ ਰਹਿਣ ਦਿਓ।

    1. ਇਹ ਸੈਂਸਰ ਇੱਕ I²C ਸੈਂਸਰ ਹੈ, ਇਸ ਲਈ ਐਡਰੈੱਸ ਨੂੰ `0x29` ਸੈੱਟ ਕਰੋ। ਜੇ ਤੁਸੀਂ ਇੱਕ ਭੌਤਿਕ VL53L0X ਸੈਂਸਰ ਦੀ ਵਰਤੋਂ ਕਰਦੇ, ਤਾਂ ਇਹ ਐਡਰੈੱਸ ਹਾਰਡਕੋਡ ਹੋਵੇਗਾ।

    1. ਦੂਰੀ ਸੈਂਸਰ ਬਣਾਉਣ ਲਈ **Add** ਬਟਨ ਚੁਣੋ।

    ![ਦੂਰੀ ਸੈਂਸਰ ਸੈਟਿੰਗ](../../../../../translated_images/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.pa.png)

    ਦੂਰੀ ਸੈਂਸਰ ਬਣਾਇਆ ਜਾਵੇਗਾ ਅਤੇ ਸੈਂਸਰਾਂ ਦੀ ਸੂਚੀ ਵਿੱਚ ਦਿਖਾਈ ਦੇਵੇਗਾ।

    ![ਦੂਰੀ ਸੈਂਸਰ ਬਣਾਇਆ ਗਿਆ](../../../../../translated_images/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.pa.png)

## ਦੂਰੀ ਸੈਂਸਰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ

ਹੁਣ ਵਰਚੁਅਲ IoT ਡਿਵਾਈਸ ਨੂੰ ਨਕਲੀ ਦੂਰੀ ਸੈਂਸਰ ਦੀ ਵਰਤੋਂ ਕਰਨ ਲਈ ਪ੍ਰੋਗਰਾਮ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

### ਕੰਮ - ਟਾਈਮ ਆਫ ਫਲਾਈਟ ਸੈਂਸਰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ

1. `fruit-quality-detector` ਪ੍ਰੋਜੈਕਟ ਵਿੱਚ ਇੱਕ ਨਵੀਂ ਫਾਈਲ ਬਣਾਓ ਜਿਸਦਾ ਨਾਮ `distance-sensor.py` ਰੱਖੋ।

    > 💁 ਕਈ IoT ਡਿਵਾਈਸਾਂ ਨੂੰ ਨਕਲੀ ਬਣਾਉਣ ਦਾ ਆਸਾਨ ਤਰੀਕਾ ਇਹ ਹੈ ਕਿ ਹਰ ਇੱਕ ਨੂੰ ਵੱਖ-ਵੱਖ Python ਫਾਈਲ ਵਿੱਚ ਬਣਾਓ ਅਤੇ ਫਿਰ ਉਨ੍ਹਾਂ ਨੂੰ ਇੱਕੋ ਸਮੇਂ ਚਲਾਓ।

1. ਹੇਠਾਂ ਦਿੱਤੇ ਕੋਡ ਨਾਲ CounterFit ਨਾਲ ਕਨੈਕਸ਼ਨ ਸ਼ੁਰੂ ਕਰੋ:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. ਇਸ ਤੋਂ ਹੇਠਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    ਇਹ VL53L0X ਟਾਈਮ ਆਫ ਫਲਾਈਟ ਸੈਂਸਰ ਲਈ ਸੈਂਸਰ ਲਾਇਬ੍ਰੇਰੀ ਸ਼ਿਮ ਨੂੰ ਇੰਪੋਰਟ ਕਰਦਾ ਹੈ।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, ਸੈਂਸਰ ਤੱਕ ਪਹੁੰਚ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    ਇਹ ਕੋਡ ਦੂਰੀ ਸੈਂਸਰ ਨੂੰ ਡਿਕਲੇਅਰ ਕਰਦਾ ਹੈ ਅਤੇ ਫਿਰ ਸੈਂਸਰ ਨੂੰ ਸ਼ੁਰੂ ਕਰਦਾ ਹੈ।

1. ਆਖਰ ਵਿੱਚ, ਦੂਰੀਆਂ ਪੜ੍ਹਨ ਲਈ ਇੱਕ ਅਨੰਤ ਲੂਪ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    ਇਹ ਕੋਡ ਸੈਂਸਰ ਤੋਂ ਪੜ੍ਹਨ ਲਈ ਇੱਕ ਮੁੱਲ ਦੀ ਉਪਲਬਧਤਾ ਦੀ ਉਡੀਕ ਕਰਦਾ ਹੈ ਅਤੇ ਫਿਰ ਇਸਨੂੰ ਕੰਸੋਲ 'ਤੇ ਪ੍ਰਿੰਟ ਕਰਦਾ ਹੈ।

1. ਇਸ ਕੋਡ ਨੂੰ ਚਲਾਓ।

    > 💁 ਯਾਦ ਰੱਖੋ ਕਿ ਇਸ ਫਾਈਲ ਦਾ ਨਾਮ `distance-sensor.py` ਹੈ! ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਇਸਨੂੰ Python ਰਾਹੀਂ ਚਲਾਓ, ਨਾ ਕਿ `app.py` ਰਾਹੀਂ।

1. ਤੁਸੀਂ ਕੰਸੋਲ ਵਿੱਚ ਦੂਰੀ ਦੇ ਮਾਪ ਵੇਖੋਗੇ। CounterFit ਵਿੱਚ ਮੁੱਲ ਬਦਲੋ ਜਾਂ ਰੈਂਡਮ ਮੁੱਲਾਂ ਦੀ ਵਰਤੋਂ ਕਰੋ।

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਨਜ਼ਦੀਕੀ ਸੈਂਸਰ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ ਨੂੰ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਵਿੱਚ ਰੱਖੋ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਇਸ ਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਮੌਜੂਦ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤ ਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।