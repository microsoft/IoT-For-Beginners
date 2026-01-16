<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2026-01-07T07:10:36+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "kn"
}
-->
# ಹತ್ತಿರವನ್ನು ಕಂಡುಹಿಡಿ - ವಾಸ್ತವಿಕ IoT ಹาร์ಡ್ವೇರ್

ಪಾಠದ ಈ ಭಾಗದಲ್ಲಿ, ನೀವು ನಿಮ್ಮ ವಾಸ್ತವಿಕ IoT ಸಾಧನಕ್ಕೆ ಹತ್ತಿರದ ಸೆನ್ಸಾರನ್ನು ಸೇರಿಸಿ, ಅದರಿಂದ ದೂರವನ್ನು ಓದಲು ಮಾಡುತ್ತೀರಿ.

## ಹಾರ್ಡ್ವೇರ್

ವಾಸ್ತವಿಕ IoT ಸಾಧನವು ನಕಲಿ ದೂರ ಸೆನ್ಸಾರವನ್ನು ಬಳಸಲಿದೆ.

ಭೌತಿಕ IoT ಸಾಧನದಲ್ಲಿ ದೂರವನ್ನು ಕಂಡುಹಿಡಿಯಲು ಲೇಸರ್ ರೇಂಜಿಂಗ್ ಮೋಡ್ಯೂಲ್ ಇರುವ ಸೆನ್ಸಾರನ್ನು ಬಳಸುತ್ತಿರಿ.

### CounterFit ಗೆ ದೂರ ಸೆನ್ಸಾರವನ್ನು ಸೇರಿಸಿ

ವಾಸ್ತವಿಕ ದೂರ ಸೆನ್ಸಾರವನ್ನು ಬಳಸಲು, ನೀವು ಅದನ್ನು CounterFit ಅಪ್ಲಿಕೇಶನ್ಗೆ ಸೇರಿಸಬೇಕು

#### ಕಾರ್ಯ - CounterFit ಗೆ ದೂರ ಸೆನ್ಸಾರವನ್ನು ಸೇರಿಸಿ

CounterFit ಅಪ್ಲಿಕೇಶನ್ಗೆ ದೂರ ಸೆನ್ಸಾರವನ್ನು ಸೇರಿಸಿ.

1. `fruit-quality-detector` ಕೋಡ್ ಅನ್ನು VS Code ನಲ್ಲಿ ತೆರೆಯಿರಿ ಮತ್ತು ವಾಸ್ತವಿಕ ವಾತಾವರಣವು ಸಕ್ರಿಯವಾಗಿದೆ ಎಂದು ಖಚಿತಪಡಿಸಿಕೊಳ್ಳಿ.

1. CounterFit ಶಿಮ್ ಅನ್ನು ಫಿಸರ್ಸಾಕ್ ಮಾಡಬಹುದಾದ ಹೆಚ್ಚುವರಿ Pip ಪ್ಯಾಕೇಜ್ ಅನ್ನು ಸ್ಥಾಪಿಸಿ, ಇದು [rpi-vl53l0x Pip package](https://pypi.org/project/rpi-vl53l0x/) ಅನ್ನು ಸಿಮ್ಯುಲೇಟ್ ಮಾಡುತ್ತದೆ, Python ಪ್ಯಾಕೇಜ್ ಆಗಿದ್ದು [VL53L0X ಸಮಯದ ಹಾರಾಟದ ದೂರ ಸೆನ್ಸಾರ](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/) ಜೊತೆಗೆ ಸಂವಹನ ಮಾಡುತ್ತದೆ. ಇದನ್ನು ವಾಸ್ತವಿಕ ವಾತಾವರಣ ಸಕ್ರಿಯಗೊಂಡಿರುವ ಟರ್ಮಿನಲ್ನಿಂದ ಸ್ಥಾಪಿಸುತ್ತಿದ್ದೀರಿ ಎಂದು ಖಚಿತಪಡಿಸಿಕೊಳ್ಳಿ.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. CounterFit ವೆಬ್ ಅಪ್ಲಿಕೇಶನ್ ಚಾಲಿತವಾಗಿದ್ದು ಎಂದು ಖಚಿತಪಡಿಸಿಕೊಳ್ಳಿ

1. ದೂರ ಸೆನ್ಸಾರವನ್ನು ರಚಿಸಿ:

    1. *Sensors* ಪೇನ್‌ನ *Create sensor* ಬಾಕ್ಸ್‌ನಲ್ಲಿ, *Sensor type* ಬಾಕ್ಸ್‌ನಿಂದ ಡ್ರಾಪ್ ಮಾಡಿ *Distance* ಆಯ್ಕೆಮಾಡಿ.

    1. *Units* ಅನ್ನು `Millimeter` ಆಗಿಯೇ ಇಡಿ

    1. ಈ ಸೆನ್ಸಾರವು I<sup>2</sup>C ಸೆನ್ಸಾರ ಆಗಿದ್ದು, ಅದರಿಂದ ವಿಳಾಸವನ್ನು `0x29` ಎಂದು ಸೆಟ್ ಮಾಡಿ. ನೀವು ಭೌತಿಕ VL53L0X ಸೆನ್ಸಾರ ಬಳಸಿದರೆ ಇದು ಈ ವಿಳಾಸಕ್ಕೆ ಹಾರ್ಡ್‌ಕೋಡ್ ಆಗಿರುತ್ತದೆ.

    1. ದೂರ ಸೆನ್ಸಾರವನ್ನು ರಚಿಸಲು **Add** ಬಟನ್ ಕ್ಲಿಕ್ ಮಾಡಿ

    ![The distance sensor settings](../../../../../translated_images/kn/counterfit-create-distance-sensor.967c9fb98f27888d.png)

    ದೂರ ಸೆನ್ಸಾರವನ್ನು ರಚಿಸಲಾಗುತ್ತದೆ ಮತ್ತು ಸೆನ್ಸಾರಗಳ ಪಟ್ಟಿಯಲ್ಲಿ ಕಾಣಿಸುತ್ತದೆ.

    ![The distance sensor created](../../../../../translated_images/kn/counterfit-distance-sensor.079eefeeea0b68af.png)

## ದೂರ ಸೆನ್ಸಾರವನ್ನು ಪ್ರೋಗ್ರಾಮ್ಮಿಂಗ್ ಮಾಡಿ

ಈಗ ವಾಸ್ತವಿಕ IoT ಸಾಧನವನ್ನು ನಕಲಿ ದೂರ ಸೆನ್ಸಾರವನ್ನು ಬಳಸಲು ಪ್ರೋಗ್ರಾಮ್ ಮಾಡಬಹುದು.

### ಕಾರ್ಯ - ಸಮಯದ ಹಾರಾಟ ಸೆನ್ಸಾರವನ್ನು ಪ್ರೋಗ್ರಾಮ್ ಮಾಡಿ

1. `fruit-quality-detector` ಪ್ರಾಜೆಕ್ಟ್‌ನಲ್ಲಿ `distance-sensor.py` ಎಂಬ ಹೊಸ ಫೈಲ್ ರಚಿಸಿ.

    > 💁 ಬಹು IoT ಸಾಧನಗಳನ್ನು ಅನುಕರಿಸಲು ಸುಲಭವಾದ ಮಾರ್ಗವೆಂದರೆ ಪ್ರತಿ ಸಾಧನವನ್ನು ವಿಭಿನ್ನ Python ಫೈಲ್‌ನಲ್ಲಿ ಮಾಡುವುದು, ನಂತರ ಅವನ್ನು ಒಟ್ಟಿಗೆ ಚಾಲನೆ ಮಾಡುವುದು.

1. ಕೆಳಗಿನ ಕೋಡ್ ಬಳಸಿ CounterFit ಗೆ ಸಂಪರ್ಕ ಪ್ರಾರಂಭಿಸಿ:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. ಇದರ ಕೆಳಗೆ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    ಇದು VL53L0X ಸಮಯದ ಹಾರಾಟ ಸೆನ್ಸಾರಕ್ಕಾಗಿ ಸೆನ್ಸಾರ ಲೈಬ್ರರಿ ಶಿಮ್ ಅನ್ನು ಆಮದು ಮಾಡುತ್ತದೆ.

1. ಇದರ ಕೆಳಗೆ, ಸೆನ್ಸಾರವನ್ನು ಪ್ರాప్త ಮಾಡಬೇಕಾದ ಕೋಡ್ ಸೇರಿಸಿ:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    ಈ ಕೋಡ್ ಒಂದು ದೂರ ಸೆನ್ಸಾರವನ್ನು ಘೋಷಿಸುತ್ತದೆ ನಂತರ ಅದು ಸೆನ್ಸಾರವನ್ನು ಪ್ರಾರಂಭಿಸುತ್ತದೆ.

1. ಕೊನೆಗೆ, ದೂರಗಳನ್ನು ಓದಲು ಒಂದು ಅಸಂಖ್ಯಾತ ಲೂಪ್ ಸೇರಿಸಿ:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    ಈ ಕೋಡ್ ಸೆನ್ಸಾರದಿಂದ ಓದಲು ಮೌಲ್ಯ ಸಿದ್ಧವಾಗುವವರೆಗೆ ಕಾಯುತ್ತದೆ ನಂತರ ಅದನ್ನು ಕಾನ್ಸೋಲ್‌ಗೆ ಮುದ್ರಿಸುತ್ತದೆ.

1. ಈ ಕೋಡ್ ಅನ್ನು ಚಾಲನೆ ಮಾಡಿ.

    > 💁 ಈ ಫೈಲ್ `distance-sensor.py` ಎಂದು ಕರೆಸಲಾಗಿದೆ ಎಂದು ಮರೆತಬೇಡಿ! Python ಮೂಲಕ ಅದನ್ನು ಕಾರ್ಯಗತಗೊಳಿಸಿ, `app.py` ಮೂಲಕವಲ್ಲ.

1. ನೀವು ದೂರ ಮೌಲ್ಯಗಳನ್ನು ಕಾನ್ಸೋಲ್‌ನಲ್ಲಿ ಕಾಣುತ್ತೀರಿ. ಮೌಲ್ಯವನ್ನು CounterFit ನಲ್ಲಿ ಬದಲಾಯಿಸಿ ಇದನ್ನು ಬದಲಾಯಿಸುವುದನ್ನು ನೋಡಿ, ಅಥವಾ ಯಾದೃಚ್ಛಿಕ ಮೌಲ್ಯಗಳನ್ನು ಬಳಸಿ.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 ಈ ಕೋಡ್ ಅನ್ನು ನೀವು [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಕಾಣಬಹುದು.

😀 ನಿಮ್ಮ ಹತ್ತಿರದ ಸೆನ್ಸಾರ ಪ್ರೋಗ್ರಾಂ ಯಶಸ್ವಿಯಾಯಿತು!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ಅಜ್ಞಾಪನೆ**:  
ಈ ದಾಖಲೆವನ್ನು AI ಅನುವಾದ ಸೇವೆ [Co-op Translator](https://github.com/Azure/co-op-translator) ಬಳಸಿ ಅನುವಾದಿಸಲಾಗಿದೆ. ನಾವು ಸರಳತೆಗೆ ಪ್ರಯತ್ನಿಸಿದರೂ, ಸ್ವಯಂಚಾಲಿತ ಅನುವಾದಗಳಲ್ಲಿ ತಪ್ಪುಗಳು ಅಥವಾ ಅಸೂಯೆಗಳು ಇರಬಹುದಾಗಿದೆ ಎಂಬುದನ್ನು ದಯವಿಟ್ಟು ತಿಳಿದುಗೊಳ್ಳಿ. ಮೂಲ ಭಾಷೆಯಲ್ಲಿ ಇರುವ ಮೂಲ ದಾಖಲೆ ನಿಖರ ಮತ್ತು ಅಧಿಕೃತ ಮೂಲವಾಗಿರುತ್ತದೆ. ಮಹತ್ವದ ಮಾಹಿತಿಗಾಗಿ ವೃತ್ತಿಪರ ಮಾನವ ಅನುವಾದವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗಿದೆ. ಈ ಅನುವಾದ ಬಳಕೆಯಿಂದ ಉಂಟಾಗುವ ಯಾವುದೇ ಅರ್ಥಗ್ರಹಣ ತಪ್ಪುಗಳಿಗೆ ಅಥವಾ ತಪ್ಪಿದ ವಿವರಣೆಗಳಿಗೆ ನಾವು ಹೊಣೆಗಾರರಾಗಿರುವುದಿಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->