<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2026-01-07T06:49:05+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "kn"
}
-->
# ಒಂದು ಚಿತ್ರವನ್ನು ಸೆರೆಹಿಡಿಯಿರಿ - Wio ಟೆರ್ಮಿನಲ್

ಪಾಠದ ಈ ಭಾಗದಲ್ಲಿ, ನೀವು ನಿಮ್ಮ Wio ಟೆರ್ಮಿನಲ್‌ಗೆ ಕ್ಯಾಮೆರಾವನ್ನು ಸೇರಿಸುತ್ತೀರಿ ಮತ್ತು ಅದರಿಂದ ಚಿತ್ರಗಳನ್ನು ಸೆರೆಹಿಡಿಯುತ್ತೀರಿ.

## ಹಾರ್ಡ್ವೇರ್

Wio ಟೆರ್ಮಿನಲ್‌ಗೆ ಕ್ಯಾಮೆರಾ ಅವಶ್ಯಕವಾಗಿದೆ.

ನೀವು ಬಳಸಲಿರುವ ಕ್ಯಾಮೆರಾ ಒಂದು [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/) ಆಗಿದೆ. ಇದು OV2640 ಚಿತ್ರ ಸೆನ್ಸರ್ ಆಧರಿತ 2 ಮೆಗಾಪಿಕ್ಸೆಲ್ ಕ್ಯಾಮೆರಾ. ಅದು SPI ಇಂಟರ್ಫೇಸ್ ಮೂಲಕ ಚಿತ್ರಗಳನ್ನು ಸೆರೆಹಿಡಿಯುತ್ತದೆ ಮತ್ತು ಸೆನ್ಸರ್ ಅನ್ನು ಸಂರಚಿಸಲು I<sup>2</sup>Cನ್ನು ಬಳಸುತ್ತದೆ.

## ಕ್ಯಾಮೆರಾವನ್ನು ಸಂಪರ್ಕಿಸಿ

ArduCam ನಿಗೆ Grove ಸಾಕೆಟ್ ಇರುವುದಿಲ್ಲ, ಬದಲಿಗೆ ಇದು Wio ಟೆರ್ಮಿನಲ್‌ನ GPIO ಪಿನ್ ಗಳ ಮೂಲಕ SPI ಮತ್ತು I<sup>2</sup>C ಬಸ್ಸುಗಳಿಗೆ ಸಂಪರ್ಕಿಸುತ್ತದೆ.

### ಕಾರ್ಯ - ಕ್ಯಾಮೆರಾವನ್ನು ಸಂಪರ್ಕಿಸಿ

ಕ್ಯಾಮೆರಾವನ್ನು ಸಂಪರ್ಕಿಸಿ.

![ArduCam ಸೆನ್ಸರ್](../../../../../translated_images/kn/arducam.20e4e4cbb2682965.png)

1. ArduCam ಬೇಸ್上的 ಪಿನ್‌ಗಳನ್ನು Wio ಟೆರ್ಮಿನಲ್‌ನ GPIO ಪಿನ್‌ಗಳಿಗೆ ಸಂಪರ್ಕಿಸುವುದು ಅಗತ್ಯ. ಸರಿಯಾದ ಪಿನ್‌ಗಳನ್ನು ಸಿಗಲು ಸುಲಭಗೊಳಿಸಲು, Wio ಟೆರ್ಮಿನಲ್ ಪ್ರ accompaniesಡುವ GPIO ಪಿನ್ ಸ್ಟಿಕರ್ ಅನ್ನು ಪಿನ್‌ಗಳ ಸುತ್ತ.Attach ಮಾಡಿ:

    ![Wio ಟೆರ್ಮಿನಲ್ GPIO ಪಿನ್ ಸ್ಟಿಕರ್ ಜೊತೆಗೆ](../../../../../translated_images/kn/wio-terminal-pin-sticker.b90b1535937b84bd.png)

1. ಜಂಪರ್ ವೈರ್‌ಗಳನ್ನು ಬಳಸಿ ಕೆಳಗಿನ ಸಂಪರ್ಕಗಳನ್ನು ಮಾಡಿ:

    | ArduCAM ಪಿನ್ | Wio ಟೆರ್ಮಿನಲ್ ಪಿನ್ | ವಿವರಣೆ                             |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | SPI ಚಿಪ್ ಸೆಲೆಕ್ಟ್                         |
    | MOSI        | 19 (SPI_MOSI)    | SPI ನಿಯಂತ್ರಕ ಔಟ್‌ಪುಟ್, ಪೆರಿಫೆರಲ್ ಇನ್‌ಪುಟ್ |
    | MISO        | 21 (SPI_MISO)    | SPI ನಿಯಂತ್ರಕ ಇನ್‌ಪುಟ್, ಪೆರಿಫೆರಲ್ ಔಟ್‌ಪುಟ್ |
    | SCK         | 23 (SPI_SCLK)    | SPI ಸರಣಿಗೊಳಾದ ಘಂಟೆ                        |
    | GND         | 6 (GND)          | ಗ್ರೌಂಡ್ - 0V                             |
    | VCC         | 4 (5V)           | 5V ವಿದ್ಯುತ್ ಪೂರೈಕೆ                         |
    | SDA         | 3 (I2C1_SDA)     | I<sup>2</sup>C ಸರಣಿಗೊಳಾದ ಡೇಟಾ              |
    | SCL         | 5 (I2C1_SCL)     | I<sup>2</sup>C ಸರಣಿಗೊಳಾದ ಘಂಟೆ             |

    ![ಜಂಪರ್ ವೈರ್‌ಗಳು ಮೂಲಕ ArduCam ಗೆ ಸಂಪರ್ಕಗೊಂಡ Wio ಟೆರ್ಮಿನಲ್](../../../../../translated_images/kn/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.png)

    GND ಮತ್ತು VCC ಸಂಪರ್ಕಗಳು ArduCam ಗೆ 5V ವಿದ್ಯುತ್ ಪೂರೈಸುತ್ತವೆ. ಇದು Grove ಸೆನ್ಸರ್‌ಗಳಂತೆ 3V ನಲ್ಲಿ ಮಾತನಾಡುವುದಿಲ್ಲ, ಬದಲಾಗಿ 5V ನಲ್ಲಿ ಕಾರ್ಯನಿರ್ವಹಿಸುತ್ತದೆ. ಈ ವಿದ್ಯುತ್ ಸಾಧನಕ್ಕೆ ವಿದ್ಯುತ್ ಒದಗಿಸುವ USB-C ಸಂಪರ್ಕದಿಂದ ನೇರವಾಗಿ ಬರುತ್ತದೆ.

    > 💁 SPI ಸಂಪರ್ಕಕ್ಕೆ ArduCam ಮತ್ತು Wio ಟೆರ್ಮಿನಲ್上的 ಪಿನ್ ಲೇಬಲ್‌ಗಳು ಹಳೆಯ ಹೆಸರಿಡುವ ಪದ್ಧತಿಯನ್ನು ಬಳಕೆ ಮಾಡುತ್ತವೆ. ಈ ಪಾಠದಲ್ಲಿ ಸೂಚನೆಗಳು ಹೊಸ ಹೆಸರಿಡುವ ಪದ್ಧತಿಯನ್ನು ಬಳಸುತ್ತವೆ, ಆದರೆ ಕೋಡ್‌ನಲ್ಲಿ ಪಿನ್ ಹೆಸರಿಗಳನ್ನು ಬಳಸಿದಾಗ ಹಳೆಯ ಹೆಸರಿಡುವ ಪದ್ಧತಿ ಬಳಕೆ ಮಾಡಲಾಗುತ್ತದೆ.

1. ಈಗ ನೀವು Wio ಟೆರ್ಮಿನಲ್ ಅನ್ನು ನಿಮ್ಮ ಕಂಪ್ಯೂಟರ್‌ಗೆ ಸಂಪರ್ಕಿಸಬಹುದು.

## ಸಾಧನವನ್ನು ಕ್ಯಾಮೆರಾಗೆ ಸಂಪರ್ಕಿಸಲು ಪ್ರೋಗ್ರಾಮ್ ಮಾಡುವುದು

ಈಗ Wio ಟೆರ್ಮಿನಲ್ ಅನ್ನು ಇರಿಸಿದ ArduCAM ಕ್ಯಾಮೆರಾ ಬಳಕೆ ಮಾಡಲು ಪ್ರೋಗ್ರಾಮ್ ಮಾಡಬಹುದು.

### ಕಾರ್ಯ - ಸಾಧನವನ್ನು ಕ್ಯಾಮೆರಾಗೆ ಸಂಪರ್ಕಿಸಲು ಪ್ರೋಗ್ರಾಮ್ ಮಾಡಿ

1. PlatformIO ಬಳಸಿಕೊಂಡು ಹೊಸ Wio ಟೆರ್ಮಿನಲ್ ಪ್ರಾಜೆಕ್ಟ್ ಅನ್ನು ರಚಿಸಿ. ಈ ಪ್ರಾಜೆಕ್ಟ್ ಹೆಸರನ್ನು `fruit-quality-detector` ಎಂದು ಇಡಿ. ಸರಿಯೊಂದಿಗೆ ಸರಣಿಪೋರ್ಟ್ ಅನ್ನು ಸಂರಚಿಸಲು `setup` ಫಂಕ್ಷನ್‌ನಲ್ಲಿ ಕೋಡ್ ಸೇರಿಸಿ.

1. WiFiಗೆ ಸಂಪರ್ಕಿಸಲು `config.h` ಫೈಲ್‌‌ನಲ್ಲಿ ನಿಮ್ಮ WiFi ಕ್ರೆಡೆನ್ಶಿಯಲ್ಸ್ ಬಳಸಿ ಕೋಡ್ ಸೇರಿಸಿ. ಅಗತ್ಯವಿರುವ ಲೈಬ್ರರಿ‌ಗಳನ್ನು `platformio.ini` ಫೈಲ್‌ನಲ್ಲಿ ಸೇರಿಸುವುದನ್ನು ಮರೆಯಬೇಡಿ.

1. ArduCam ಲೈಬ್ರರಿ `platformio.ini` ಮೂಲಕ Arduino ಲೈಬ್ರರಿ ಆಗಿ ಲಭ್ಯವಿಲ್ಲ, ಅದನ್ನು ಆTheir GitHub ಪುಟದಿಂದ ಮೂಲದಿಂದ ಸ್ಥಾಪಿಸಬೇಕು. ಇದನ್ನು ನೀವು ಮಾಡಬಹುದೇ:

    * [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git) ದಿಂದ ರೆಪೊ ಕ್ಲೋನ್ ಮಾಡುವುದು
    * GitHub ನಲ್ಲಿ ರೆಪೊಗೆ ಭೇಟಿ ನೀಡಿ [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) ಮತ್ತು **Code** ಬಟನ್ ಮೂಲಕ ಜಿಪ್ ಆಗಿ ಕೋಡ್ ಡೌನ್‌ಲೋಡ್ ಮಾಡಿಕೊಳ್ಳಿ

1. ನಿಮಗೆ ഈ ಕೋಡ್‌ನ `ArduCAM` ಫೋಲ್ಡರ್ ಮಾತ್ರ ಬೇಕು. ಈ ಫೋಲ್ಡರ್ ಅನ್ನು ನಿಮ್ಮ ಪ್ರಾಜೆಕ್ಟ್‌ನ `lib` ಫೋಲ್ಡರ್‌ಗೆ ಸಂಪೂರ್ಣವಾಗಿ ನಕಲಿಸಿ.

    > ⚠️ ಸಂಪೂರ್ಣ ಫೋಲ್ಡರ್ ನಕಲಿಸಬೇಕು, ಆದ್ದರಿಂದ ಕೋಡ್ `lib/ArduCam` ನಲ್ಲಿ ಇರುತ್ತದೆ. `ArduCam` ಫೋಲ್ಡರ್‌ನ ವಿಷಯಗಳನ್ನು ಮಾತ್ರ `lib` ಫೋಲ್ಡರ್‌ಗೆ ನಕಲಿಸಬೇಡಿ, ಸಂಪೂರ್ಣ ಫೋಲ್ಡರ್‌ನನ್ನು ನಕಲಿಸಿ.

1. ArduCam ಲೈಬ್ರರಿ ಕೋಡ್ ಹಲವಾರು ರೀತಿಯ ಕ್ಯಾಮೆರಾಗಳಿಗೆ ಕೆಲಸ ಮಾಡುತ್ತದೆ. ನೀವು ಬಳಸಲು ಬಯಸುವ ಕ್ಯಾಮೆರಾ ಪ್ರಕಾರವನ್ನು ಕಂಪೈಲರ್ ಫ್ಲ್ಯಾಗ್‌ಗಳೊಂದಿಗೆ ಸಂರಚಿಸುತ್ತದೆ - ಇದರಿಂದ ನೀವು ಬಳಸದ ಕ್ಯಾಮೆರಾಗಳಿಗಾಗಿ ಇರುವ ಕೋಡ್ ತೆಗೆದುಬಿಡುವ ಮೂಲಕ ಲೈಬ್ರರಿ ಸಣ್ಣದಾಗಿ ಇರುತ್ತದೆ. OV2640 ಕ್ಯಾಮೆರಾಗೆ ಲೈಬ್ರರಿ ಸಂರಚಿಸಲು, `platformio.ini` ಫೈಲ್‌ನ ಕೊನೆಯಲ್ಲಿ ಕೆಳಗಿನುದನ್ನು ಸೇರಿಸಿ:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    ಇದು 2 ಕಂಪೈಲರ್ ಫ್ಲ್ಯಾಗ್‌ಗಳನ್ನು ಹೀಗೇ ಹೊಂದಿಸುತ್ತದೆ:

      * `ARDUCAM_SHIELD_V2` - ಲೈಬ್ರರಿಗೆ ಕ್ಯಾಮೆರಾ ಅರ್ಡೂઇನೋ ಬೋರ್ಡ್上的 ಶೀಲ್ಡ್ ಎಂಬುದಾಗಿ ತಿಳಿದುಕೊಳ್ಳಿಸಲು.
      * `OV2640_CAM` - ಲೈಬ್ರರಿಗೆ OV2640 ಕ್ಯಾಮೆರಾ ಕೋಡ್ ಮಾತ್ರ ಒಳಗೊಂಡಂತೆ ತಿಳಿಸುವುದಕ್ಕೆ.

1. `src` ಫೋಲ್ಡರ್‌ನಲ್ಲಿ `camera.h` ಎಂಬ ಹೆಡರ್ ಫೈಲ್ ಸೇರ್ಪಡೆ ಮಾಡಿ. ಇದು ಕ್ಯಾಮೆರಾ ಜೊತೆ ಸಂವಹನ ಮಾಡಲು ಕೋಡ್ ಹೊಂದಿರುತ್ತದೆ. ಈ ಫೈಲ್‌ಗೆ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    #pragma once
    
    #include <ArduCAM.h>
    #include <Wire.h>
    
    class Camera
    {
    public:
        Camera(int format, int image_size) : _arducam(OV2640, PIN_SPI_SS)
        {
            _format = format;
            _image_size = image_size;
        }
    
        bool init()
        {
            // CPLD ಅನ್ನು ಮರುಹೊಂದಿಸಿ
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // ArduCAM SPI ಬಸ್ ಸರಿಯಾಗಿದೆಯೇ ಎಂದು ಪರಿಶೀಲಿಸಿ
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // MCU ಮೋಡ್ ಅನ್ನು ಬದಲಾಯಿಸಿ
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // ಕ್ಯಾಮೆರಾ ಮೋಡ್ಯೂಲ್ ಪ್ರಕಾರ OV2640 ಆಗಿದೆಯೇ ಎಂದು ಪರಿಶೀಲಿಸಿ
            _arducam.wrSensorReg8_8(0xff, 0x01);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
            if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42)))
            {
                return false;
            }
            
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
            _arducam.OV2640_set_Light_Mode(Auto);
            _arducam.OV2640_set_Special_effects(Normal);
            delay(1000);
    
            return true;
        }
    
        void startCapture()
        {
            _arducam.flush_fifo();
            _arducam.clear_fifo_flag();
            _arducam.start_capture();
        }
    
        bool captureReady()
        {
            return _arducam.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK);
        }
    
        bool readImageToBuffer(byte **buffer, uint32_t &buffer_length)
        {
            if (!captureReady()) return false;
    
            // ಚಿತ್ರ ಫೈಲ್‌ನ ಉದ್ದವನ್ನು ಪಡೆಯಿರಿ
            uint32_t length = _arducam.read_fifo_length();
            buffer_length = length;
    
            if (length >= MAX_FIFO_SIZE)
            {
                return false;
            }
            if (length == 0)
            {
                return false;
            }
    
            // ಬಫರ್ ಸೃಷ್ಟಿಸಿ
            byte *buf = new byte[length];
    
            uint8_t temp = 0, temp_last = 0;
            int i = 0;
            uint32_t buffer_pos = 0;
            bool is_header = false;
    
            _arducam.CS_LOW();
            _arducam.set_fifo_burst();
            
            while (length--)
            {
                temp_last = temp;
                temp = SPI.transfer(0x00);
                //FIFO ನಿಂದ JPEG ಡೇಟಾವನ್ನು ಓದಿ
                if ((temp == 0xD9) && (temp_last == 0xFF)) //ಅಂತ್ಯವನ್ನು ಕಂಡುಹಿಡಿದರೆ, ವ್ಹೈಲ್ ನ್ನು ಬ್ರೇಕ್ ಮಾಡಿ
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //ಬಫರ್ ತುಂಬಿರುವುದಿಲ್ಲವಾದರೆ ಚಿತ್ರ ಡೇಟಾವನ್ನು ಬಫರ್ ಗೆ ಬರೆಯಿರಿ
                    if (i < 256)
                    {
                        buf[buffer_pos] = temp;
                        buffer_pos++;
                        i++;
                    }
                    else
                    {
                        _arducam.CS_HIGH();
    
                        i = 0;
                        buf[buffer_pos] = temp;
    
                        buffer_pos++;
                        i++;
    
                        _arducam.CS_LOW();
                        _arducam.set_fifo_burst();
                    }
                }
                else if ((temp == 0xD8) & (temp_last == 0xFF))
                {
                    is_header = true;
    
                    buf[buffer_pos] = temp_last;
                    buffer_pos++;
                    i++;
    
                    buf[buffer_pos] = temp;
                    buffer_pos++;
                    i++;
                }
            }
            
            _arducam.clear_fifo_flag();
    
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
    
            // ಬಫರ್ ಅನ್ನು ಹಿಂತಿರುಗಿಸಿ
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    ಇದು ಕಡಿಮೆಮಟ್ಟದ ಕೋಡ್ ಆಗಿದ್ದು, ArduCam ಲೈಬ್ರರಿಗಳನ್ನು ಬಳಸಿ ಕ್ಯಾಮೆರಾವನ್ನು ಸಂರಚಿಸುತ್ತದೆ ಮತ್ತು I<sup>2</sup>C ಬಸ್ಸನ್ನು ಬಳಸಿ ಅಗತ್ಯವಿರುವಾಗ ಚಿತ್ರಗಳನ್ನು SPI ಬಸ್ ಮೂಲಕ ಹೊರತೆಗೆದುಕೊಳ್ಳುತ್ತದೆ. ಈ ಕೋಡ್ ArduCam ಗೆ ಬಹಳ ವಿಶೇಷವಾದುದರಿಂದ, ಇದನ್ನು ಹೇಗೆ ಕೆಲಸ ಮಾಡುತ್ತದೆ ಎಂದು ಈ ಮಟ್ಟಿಗೆ ಚಿಂತಿಸಬೇಕಾಗಿಲ್ಲ.

1. `main.cpp` ನಲ್ಲಿ ಇತರ `include` ಆದೇಶಗಳ ಕೆಳಗೆ ಈ ಹೊಸ ಫೈಲ್ ಅನ್ನು ಸೇರಿಸಿ ಮತ್ತು ಕ್ಯಾಮೆರಾ ಕ್ಲಾಸ್ ಇನ್ಸ್ಟಾನ್ಸ್ ರಚಿಸಿ:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    ಇದು 640 ರ 480 ರೆಸಾಲ್ಯೂಶನ್‌ನಲ್ಲಿ ಜೇಪಿಜಿ ಬಣ್ಣ ಚಿತ್ರಗಳಾಗಿ ಚಿತ್ರಗಳನ್ನು ಉಳಿಸುವ `Camera` ಅನ್ನು ರಚಿಸುತ್ತದೆ. ಹೆಚ್ಚಿನ ರೆಸಾಲ್ಯೂಶನ್‌ಗಳು (3280x2464 ವರೆಗೆ) ಬೆಂಬಲಿತವಾಗಿವೆ, ಆದರೆ ಚಿತ್ರ ವರ್ಗೀಕರಣಕಾರಿಕೆ (classification) ತುಂಬಾ ಸಣ್ಣ ಚಿತ್ರಗಳಲ್ಲಿ (227x227) ಕಾರ್ಯನಿರ್ವಹಿಸುತ್ತದೆ ಆದ್ದರಿಂದ ದೊಡ್ಡ ಚಿತ್ರಗಳನ್ನು ಹಿಡಿಯಿ ಕಳುಹಿಸುವ ಅಗತ್ಯವಿಲ್ಲ.

1. ಆಸಕ್ತಿಯಲ್ಲಿ ಈ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ ಮತ್ತು ಕ್ಯಾಮೆರಾ ಸೆಟಪ್ ಮಾಡಲು ಫಂಕ್ಷನ್ ವ್ಯಾಖ್ಯಾನಿಸಿ:

    ```cpp
    void setupCamera()
    {
        pinMode(PIN_SPI_SS, OUTPUT);
        digitalWrite(PIN_SPI_SS, HIGH);
    
        Wire.begin();
        SPI.begin();
    
        if (!camera.init())
        {
            Serial.println("Error setting up the camera!");
        }
    }
    ```

    ಈ `setupCamera` ಫಂಕ್ಷನ್ SPI ಚಿಪ್ ಸೆಲೆಕ್ಟ್ ಪಿನ್ (`PIN_SPI_SS`) ಅನ್ನು ಹೈ ಆಗಿ ಸಂರಚಿಸಿ Wio ಟೆರ್ಮಿನಲ್ ಅನ್ನು SPI ನಿಯಂತ್ರಕ ಮಾಡುತ್ತದೆ. ನಂತರ I<sup>2</sup>C ಮತ್ತು SPI ಬಸ್ಸುಗಳನ್ನು ಪ್ರಾರಂಭಿಸುತ್ತದೆ. ಕೊನೆಗೆ ಕ್ಯಾಮೆರಾ ಸೆನ್ಸರ್ ಸೆಟ್ಟಿಂಗ್‌ಗಳನ್ನು ಸಂರಚಿಸಿ ಎಲ್ಲಾ ಸಂಪರ್ಕಗಳು ಸರಿಯಾಗಿವೆ ಎಂದು ಖಚಿತಪಡಿಸುತ್ತದೆ.

1. ಈ ಫಂಕ್ಷನ್ ಅನ್ನು `setup` ಫಂಕ್ಷನ್‌ನ ಕೊನೆಯಲ್ಲಿ ಕರೆ ಮಾಡಿ:

    ```cpp
    setupCamera();
    ```

1. ಈ ಕೋಡ್ ನಿರ್ಮಿಸಿ ಅಪ್ಲೋಡ್ ಮಾಡಿ ಮತ್ತು ಸರಣಿಮನಿಟರ್‌ನಿಂದ ಔಟ್‌ಪುಟ್ ಪರಿಶೀಲಿಸಿ. `Error setting up the camera!` ನೋಟವನ್ನು ನೋಡುವಾಗ, ಅರ್ಥವಾದ ಪಿನ್‌ಗಳು ArduCam ನಿಂದ Wio ಟೆರ್ಮಿನಲ್‌ನ GPIO ಪಿನ್‌ಗಳಿಗೆ ಸರಿಯಾಗಿ ಸಂಪರ್ಕಗೊಂಡಿವೆ ಎಂದು ತಪಾಸಣೆ ಮಾಡಿ ಮತ್ತು ಎಲ್ಲಾ ಜಂಪರ್ ವೈರ್‌ಗಳು ಸರಿಯಾಗಿವೆ ಎಂದು ಪರಿಶೀಲಿಸಿ.

## ಚಿತ್ರವನ್ನು ಸೆರೆಹಿಡಿಯಿರಿ

Wio ಟೆರ್ಮಿನಲ್ ಅನ್ನು ಬಟನ್ ಒತ್ತಿದಾಗ ಚಿತ್ರ ಸೆರೆಹಿಡಿಯಲು ಪ್ರೋಗ್ರಾಮ್ ಮಾಡಬಹುದು.

### ಕಾರ್ಯ - ಚಿತ್ರ ಸೆರೆಹಿಡಿಯಿರಿ

1. ಮೈಕ್ರೋ კონტრೋಲರ್‌ಗಳು ನಿಮ್ಮ ಕೋಡ್ ಅನ್ನು ನಿರಂತರವಾಗಿ ಚಾಲನೆ ಮಾಡುತ್ತವೆ, ಆದ್ದರಿಂದ ಸೆನ್ಸರ್ ಪ್ರತಿಕ್ರಿಯೆಗೆ ಇಲ್ಲದೆ ಫೋಟೋ ತೆಗೆದಂತಹ ಕ್ರಿಯೆಯನ್ನು ಪ್ರೇರೇಪಿಸುವುದು ಸುಲಭವಲ್ಲ. Wio ಟೆರ್ಮಿನಲ್ ಮೇಲೆ ಬಟನ್‌ಗಳು ಇದ್ದು, ಆದ್ದರಿಂದ ಒಂದರ ಮೂಲಕ ಕ್ಯಾಮೆರಾ ವೈಶಿಷ್ಟ್ಯಗಳನ್ನು ಪ್ರೇರೇಪಿಸಬಹುದು. C ಬಟನ್ (ಮೇಲಿನ ಮೂರು ಬಟನ್‌ಗಳಲ್ಲಿ ಪವರ್ ಸ್ವಿಚ್‌ಗೆ ಹತ್ತಿರದ ಬಟನ್) ಅನ್ನು ಸಂರಚಿಸಲು `setup` ಫಂಕ್ಷನ್‌ನ ಕೊನೆಯಲ್ಲಿ ಈ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ![ಪವರ್ ಸ್ವಿಚ್‌ಗೆ ಹತ್ತಿರದ C ಬಟನ್](../../../../../translated_images/kn/wio-terminal-c-button.73df3cb1c1445ea0.png)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    `INPUT_PULLUP` ಮೋಡ್ ಇನ್‌ಪುಟ್ ಅನ್ನು ಮೂಲತಃ ತಿರುಗಿಸುವಂತೆ ಮಾಡುತ್ತದೆ. ಉದಾಹರಣೆಗೆ, ಸಾಮಾನ್ಯವಾಗಿ ಬಟನ್ ಒತ್ತಿದಾಗ ಕಡಿಮೆ ಸಂಕೇತವನ್ನು ಮತ್ತು ಒತ್ತದಾಗ ಹೆಚ್ಚಿನ ಸಂಕೇತವನ್ನು ಕಳುಹಿಸುತ್ತದೆ. `INPUT_PULLUP` ನಲ್ಲಿ, ಬಟನ್ ಒತ್ತದಾಗ ಹೆಚ್ಚಿನ সংকೇತ ಮತ್ತು ಒತ್ತಿದಾಗ ಕಡಿಮೆ ಸಂಕೇತ ಕಳುಹಿಸುತ್ತದೆ.

1. `loop` ಫಂಕ್ಷನ್ ಗೆ ಮೊದಲು, ಬಟನ್ ಒತ್ತಲಿಗೆ ಪ್ರತಿಕ್ರಿಯಿಸುವ ಖಾಲಿ ಫಂಕ್ಷನ್ ಸೇರಿಸಿ:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. ಬಟನ್ ಒತ್ತಿದಾಗ ಈ ಫಂಕ್ಷನ್ ಅನ್ನು `loop` ವಿಧಾನದಲ್ಲಿ ಕರೆಮಾಡಿ:

    ```cpp
    void loop()
    {
        if (digitalRead(WIO_KEY_C) == LOW)
        {
            buttonPressed();
            delay(2000);
        }
    
        delay(200);
    }
    ```

    ಈ ಕೋಡ್ ಬಟನ್ ಒತ್ತಲ್ಪಟ್ಟಿದೆಯೇ ಎಂದು ಪರಿಶೀಲನೆ ಮಾಡುತ್ತದೆ. ಒತ್ತಿದರೆ `buttonPressed` ಫಂಕ್ಷನ್ ಅನ್ನು ಕರೆ ಮಾಡಿ, ಲೂಪ್ 2 ಸೆಕೆಂಡ್ ಗಳಿಗೆ ವಿಳಂಬಿಸುತ್ತದೆ. ಇದು ಬಟನ್ ಬಿಡುಗಡೆಗೆ ಸಮಯ ನೀಡಲು, ಉದ್ದ ಬಟನ್ ಒತ್ತುವಿಕೆ ಎರಡು ಬಾರಿ ಲೆಕ್ಕಿಸದಿರಲು ಸಹಾಯಮಾಡುತ್ತದೆ.

    > 💁 Wio ಟೆರ್ಮಿನಲ್上的 ಬಟನ್ `INPUT_PULLUP` ಗೆ ಹೊಂದಿಸಲಾಗಿದೆ, ಹೀಗಾಗಿ ಒತ್ತದಾಗ ಹೆಚ್ಚಿನ ಸಂಕೇತ ಮತ್ತು ಒತ್ತಿದಾಗ ಕಡಿಮೆ ಸಂಕೇತ ಕಳುಹಿಸುತ್ತದೆ.

1. `buttonPressed` ಫಂಕ್ಷನ್‌ನಲ್ಲಿ ಈ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    camera.startCapture();
 
    while (!camera.captureReady())
        delay(100);

    Serial.println("Image captured");

    byte *buffer;
    uint32_t length;

    if (camera.readImageToBuffer(&buffer, length))
    {
        Serial.print("Image read to buffer with length ");
        Serial.println(length);

        delete(buffer);
    }
    ```

    ಈ ಕೋಡ್ ಕ್ಯಾಮೆರಾ ಸೆರೆಹಿಡುವಿಕೆಯನ್ನು `startCapture` ಮೂಲಕ ಪ್ರಾರಂಭಿಸುತ್ತದೆ. ಕ್ಯಾಮೆರಾ ಹಾರ್ಡ್‌ವೇರ್ ಬೇಡಿಕೆಯಾದಾಗ ಡೇಟಾ ಹಿಂತಿರುಗಿಸುವುದಿಲ್ಲ, ಬದಲಿಗೆ ಸೆರೆಹಿಡಿಸುವ ಸೂಚನೆಯನ್ನು ಕಳುಹಿಸಿ, ಕ್ಯಾಮೆರಾ ಬ್ಯಾಕ್ಗ್ರೌಂಡ್‌ನಲ್ಲಿ ಕಾರ್ಯನಿರ್ವಹಿಸಿ ಚಿತ್ರವನ್ನು ಸೆರೆಹಿಡಿಯುತ್ತದೆ, JPEGಗೆ ಪರಿವರ్తಿಸಿ, ಸ್ಥಳೀಯ ಬಫರ್‌ನಲ್ಲಿ ಸಂಗ್ರಹಿಸುತ್ತದೆ. `captureReady` ಕರೆ ಇದುವರೆಗೆ ಸೆರೆಹಿಡಿಸುವಿಕೆ ಪೂರ್ಣಗೊಂಡಿದೆಯೇ ಎಂದು ಪರಿಶೀಲಿಸುತ್ತದೆ.

    ಸೆರೆಹಿಡುವಿಕೆ ಪೂರ್ಣವಾದ ನಂತರ, ಇಮೇಜ್ ಡೇಟಾ ಕ್ಯಾಮೆರಾದ ಬಫರ್‌ನಿಂದ ಸ್ಥಳೀಯ ಬಫರ್‌ಗೆ (`byte` ಅರೆ) `readImageToBuffer` ಮೂಲಕ ನಕಲಿಸಲಾಗುತ್ತದೆ. ಬಫರ್‌ನ ಅಗಲವನ್ನು ಸರಣಿಮನಿಟರ್‌ಗೆ ಕಳುಹಿಸಲಾಗುತ್ತದೆ.

1. ಈ ಕೋಡ್ ಅನ್ನು ನಿರ್ಮಿಸಿ ಅಪ್ಲೋಡ್ ಮಾಡಿ ಮತ್ತು ಸರಣಿಮನಿಟರ್ ಆವರಣಕ್ಕೆ ಕಾಣುವ ಔಟ್‌ಪುಟ್ ಪರಿಶೀಲಿಸಿ. ಪ್ರತಿ ಸಾರಿ C ಬಟನ್ ಒತ್ತಿದಾಗ ಒಂದು ಇಮೇಜ್ ಸೆರೆಹಿಡಿಯಲಾಗುತ್ತದೆ ಮತ್ತು ಅದರ ಗಾತ್ರವನ್ನು ಸರಣಿಮನಿಟರ್ ಗೆ ಕಳುಹಿಸಲಾಗುತ್ತದೆ.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    ವಿಭಿನ್ನ ಚಿತ್ರಗಳು ವಿಭಿನ್ನ ಗಾತ್ರ ಹೊಂದಿರುತ್ತವೆ. ಅವು JPEG ಗಳಾಗಿ ಸಂಕೋಚಿತವಾಗಿವೆ ಮತ್ತು ನಿರ್ದಿಷ್ಟ ರೆಸಾಲ್ಯೂಶನ್‌ನಲ್ಲಿ JPEG ಫೈಲ್ ಗಾತ್ರವು ಚಿತ್ರದಲ್ಲಿರುವ ವಿಷಯದ ಮೇಲೆ ಅವಲಂಬಿತವಾಗಿದೆ.

> 💁 ನೀವು ಈ ಕೋಡ್ ಅನ್ನು [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal) ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಕಂಡುಹಿಡಿಯಬಹುದು.

😀 ನೀವು ಯಶಸ್ವಿಯಾಗಿ ನಿಮ್ಮ Wio ಟೆರ್ಮಿನಲ್ ಬಳಸಿ ಚಿತ್ರಗಳನ್ನು ಸೆರೆಹಿಡಿದಿದ್ದೀರಿ.

## ಐಚ್ಛಿಕ - SD ಕಾರ್ಡ್ ಬಳಸಿ ಕ್ಯಾಮೆರಾ ಚಿತ್ರಗಳನ್ನು ಪರಿಶೀಲಿಸಿ

ಕ್ಯಾಮೆರಾ ಸೆರೆಹಿಡಿದ ಚಿತ್ರಗಳನ್ನು ನೋಡಲು ಸುಲಭ ಮಾರ್ಗವೇ ಅವುಗಳನ್ನು Wio ಟೆರ್ಮಿನಲ್上的 SD ಕಾರ್ಡ್‌ಗೆ ಬರೆಯುವುದು ಮತ್ತು ನಂತರ ನಿಮ್ಮ ಕಂಪ್ಯೂಟರ್‌ನಲ್ಲಿ ಅವುಗಳನ್ನು ವೀಕ್ಷಿಸುವುದು. ಇದನ್ನು ನೀವು ನಿಮ್ಮ ಬಳಿ ಜಾಸ್ತಿ microSD ಕಾರ್ಡ್ ಮತ್ತು ನಿಮ್ಮ ಕಂಪ್ಯೂಟರ್‌ನಲ್ಲಿ microSD ಸಾರಿಗೆ ಸಾಕೆಟ್ (ಅಥವಾ ಅಡಾಪ್ಟರ್) ಇದ್ದರೆ ಮಾಡಿರಿ.

Wio ಟೆರ್ಮಿನಲ್‌ ಮಾತ್ರ 16GB ಗಾತ್ರದ microSD ಕಾರ್ಡ್‌ಗಳನ್ನು ಬೆಂಬಲಿಸುತ್ತದೆ. ದೊಡ್ಡ ಡಿಜಿಟಲ್ ಕಾರ್ಡ್ ಇದ್ದರೆ ಅದು ಕಾರ್ಯನಿರ್ವಹಿಸುವುದಿಲ್ಲ.

### ಕಾರ್ಯ - SD ಕಾರ್ಡ್ ಮೂಲಕ ಕ್ಯಾಮೆರಾ ಚಿತ್ರಗಳನ್ನು ಪರಿಶೀಲಿಸಿ

1. FAT32 ಅಥವಾ exFAT ರೂಪದಲ್ಲಿ microSD ಕಾರ್ಡ್ ಅನ್ನು ನಿಮ್ಮ ಕಂಪ್ಯೂಟರ್上的 ಸಂಬಂಧಿತ ಆಪ್ಲಿಕೇಶನ್ಸ್‌ ಉಪಯೋಗಿಸಿ ಫಾರ್ಮ್ಯಾಟ್ ಮಾಡಿ (macOS ನಲ್ಲಿ Disk Utility, Windows ನಲ್ಲಿ File Explorer ಅಥವಾ Linux ನಲ್ಲಿ ಕಮಾಂಡ್ ಲೈನ್ ಸಾಧನಗಳನ್ನು ಬಳಸಿ)

1. microSD ಕಾರ್ಡ್ ಅನ್ನು ಪವರ್ ಸ್ವಿಛ್ ಗೆ ಕೆಳಗೆ ಇರುವ ಸಾಕೆಟ್‌ನಲ್ಲಿ ಹರಿಸಿ. ಅದು ಕ್ಲಿಕ್ ಮಾಡಿ ಬಿಗಿದಂತೆ ಸಂಪೂರ್ಣ ಓದ್ದೇ ಇರುವುದನ್ನು ಖಚಿತಪಡಿಸಿಕೊಳ್ಳಿ, ನೀವು ನಖ ಅಥವಾ ಬारीಕ ಸಾಧನ ಬಳಸಿ ತಳ್ಳಬೇಕಾಗಬಹುದು.

1. `main.cpp` ಫೈಲ್ ಮೇಲ್ಭಾಗಕ್ಕೆ ಈ ಕೆಳಗಿನ ಇನ್‌ಕ್ಲೂಡ್‌ಗಳನ್ನ ಸೇರ್ಪಡೆ ಮಾಡಿ:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. `setup` ಫಂಕ್ಷನ್‌ಗೆ ಮುಂದೆ ಈ ಕೆಳಗಿನ ಫಂಕ್ಷನ್ ಸೇರಿಸಿ:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    ಇದು SPI ಬಸ್ಸು ಬಳಸಿ SD ಕಾರ್ಡ್ ಅನ್ನು ಸಂರಚಿಸುತ್ತದೆ.

1. ಇದನ್ನು `setup` ಫಂಕ್ಷನ್ ನಿಂದ ಕರೆಮಾಡಿ:

    ```cpp
    setupSDCard();
    ```

1. `buttonPressed` ಫಂಕ್ಷನ್ ಮೇಲು ಈ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    int fileNum = 1;

    void saveToSDCard(byte *buffer, uint32_t length)
    {
        char buff[16];
        sprintf(buff, "%d.jpg", fileNum);
        fileNum++;
    
        File outFile = SD.open(buff, FILE_WRITE );
        outFile.write(buffer, length);
        outFile.close();

        Serial.print("Image written to file ");
        Serial.println(buff);
    }
    ```

    ಇದು ಫೈಲ್ ಎಣಿಕೆಯನ್ನು ಹೊಂದಿರುವ ಜಾಗತಿಕ ವ್ಯತ್ಯಯವನ್ನು ವ್ಯಾಖ್ಯಾನಿಸುತ್ತದೆ. ಇದು ಚಿತ್ರ ಫೈಲ್ ಹೆಸರುಗಳಿಗೆ ಬಳಸಲಾಗುತ್ತುವುದು, ಹೀಗಾಗಿ ಅನೇಕ ಚಿತ್ರಗಳನ್ನು ಕ್ರಮವಾಗಿ ಹೆಚ್ಚಿಸುವ ಫೈಲ್ ಹೆಸರುಗಳೊಂದಿಗೆ (`1.jpg`, `2.jpg` ಮುಂತಾದವು) ಸೆರೆಹಿಡಿಯಬಹುದು.

    ನಂತರ ಬೈನರಿ ಡೇಟಾದ ಬಫರ್ ಮತ್ತು ಬಫರ್ ಅಗಲ ಅನ್ನು ತೆಗೆದುಕೊಳ್ಳುವ `saveToSDCard` ಅನ್ನು ವ್ಯಾಖ್ಯಾನಿಸುತ್ತದೆ. ಫೈಲ್ ಹೆಸರು ಫೈಲ್ ಎಣಿಕೆಗಳ ಮೂಲಕ ರಚಿಸಲ್ಪಡುತ್ತದೆ ಮತ್ತು ನಂತರ ಮುಂದೆ ಫೈಲ್ ಎಣಿಕೆಯನ್ನು ಹೆಚ್ಚಿಸಲಾಗುತ್ತದೆ. ಬಳಿಕ ಫೈಲ್‌ಗೆ ಡೇಟಾವನ್ನು ಬರೆಯಲಾಗುತ್ತದೆ.

1. `buttonPressed` ಫಂಕ್ಷನಿನಲ್ಲಿ ಈ `saveToSDCard` ಕರೆ **ಬಫರ್ ಅನ್ನು ಅಳಿಸುವ ಮೊದಲು** ಸೇರಿಸಿ:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. ಈ ಕೋಡ್ ನಿರ್ಮಿಸಿ ಅಪ್ಲೋಡ್ ಮಾಡಿ ಮತ್ತು ಸರಣಿಮನಿಟರ್ ಔಟ್‌ಪುಟ್ ಪರಿಶೀಲಿಸಿ. ಪ್ರತಿ ಸಾರಿ C ಬಟನ್ ಒತ್ತಿದಾಗ ಇಮೇಜ್ ಸೆರೆಹಿಡಿಯಲ್ಪಟ್ಟು SD ಕಾರ್ಡ್‌ಗೆ ಉಳಿಸಲಾಗುತ್ತದೆ.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 16392
    Image written to file 1.jpg
    Image captured
    Image read to buffer with length 14344
    Image written to file 2.jpg
    ```

1. microSD ಕಾರ್ಡ್ ಪವರ್ ಆಫ್ ಮಾಡಿ ಮತ್ತು ಸ್ವಲ್ಪ ತಳ್ಳಿದ ನಂತರ ರಿಲೀಸ್ ಮಾಡಿ, ಅದು ಹೊರಬರುತ್ತದೆ. ಇದಕ್ಕೆ ನೀವು ಒಂದು ಸಣ್ಣ ಸಾಧನದ ಸಹಾಯ ಅಗತ್ಯವಿರಬಹುದು. microSD ಕಾರ್ಡ್ ನಿಮ್ಮ ಕಂಪ್ಯೂಟರ್ ಸಂಪರ್ಕಿಸಿ ಚಿತ್ರಗಳನ್ನು ವೀಕ್ಷಿಸಿ.

    ![ArduCam ಬಳಸಿ ಸೆರೆಹಿಡಿದ ಬಾಳೆಹಣ್ಣು ಚಿತ್ರ](../../../../../translated_images/kn/banana-arducam.be1b32d4267a8194.jpg)

    > 💁 ಕ್ಯಾಮೆರಾ ಬಿಳಿ ಸಮತೋಲನವನ್ನು ಸ್ವಯಂಚಾಲಿತವಾಗಿ ಹೊಂದಿಕೊಳ್ಳಲು ಕೆಲವು ಚಿತ್ರಗಳನ್ನು ಸೆರೆಹಿಡಿಯಬೇಕಾಗಬಹುದು. ಇವು ಸೆರೆಹಿಡಿದ ಚಿತ್ರಗಳ ಬಣ್ಣಾಧಾರಿತವಾಗಿರುವುದು ಗಮನಾರ್ಹ. ಮೊದಲ ಕೆಲವು ಚಿತ್ರಗಳು ಬಣ್ಣದಲ್ಲಿ ಬದಲಾವಣೆಯಾಗಿ ಕಂಡುಬರಬಹುದು. ನೀವು ಇದನ್ನು ಓಡಿಸಿಕೊಂಡು ಹೋಗಬಹುದು `setup` ಫಂಕ್ಷನ್ ನಲ್ಲಿ ಕೆಲವು ಚಿತ್ರಗಳನ್ನು ಸೆರೆಹಿಡಿದು ತಡೆಯುವ ಮೂಲಕ.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ಜಾಹೀರಾತು**:
ಈ ದಸ್ತಾವೇಜು [Co-op Translator](https://github.com/Azure/co-op-translator) ಎಂಬ AI ಭಾಷಾಂತರ ಸೇವೆಯನ್ನು ಬಳಸಿಕೊಂಡು ಭಾಷಾಂತರಿಸಲಾಗಿದೆ. ನಾವು ಶುದ್ಧತೆಗಾಗಿ ಪ್ರಯತ್ನಿಸುತ್ತಿದ್ದರೂ ಸಹ, ಸ್ವಯಂಚಾಲಿತ ಭಾಷಾಂತರದಲ್ಲಿ ತಪ್ಪುಗಳು ಅಥವಾ ಅಸತ್ಯತೆಯಿರುವ ಸಾಧ್ಯತೆ ಇದೆ ಎಂಬುದನ್ನು ದಯವಿಟ್ಟು ಗಮನಿಸಿ. ಮೂಲ ಭಾಷೆಯಲ್ಲಿರುವ ಮೂಲ ದಸ್ತಾವೇಜನ್ನು ಅಧಿಕೃತ ಮತ್ತು ನಂಬಿಗಸ್ತ ಮೂಲವೆಂದು ಪರಿಗಣಿಸಬೇಕು. ಮುಖ್ಯ ಮಾಹಿತಿಗೆ ವೃತ್ತಿಪರ ಮಾನವ ಭಾಷಾಂತರವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗುತ್ತದೆ. ಈ ಭಾಷಾಂತರವನ್ನು ಬಳಸುವ ಮುಂಭಾಗದಲ್ಲಿ ಉಂಟಾಗುವ ಯಾವುದೇ ತಪ್ಪು ಅರ್ಥಮಾಡಿಕೆಗಳ ಅಥವಾ ತಪ್ಪು ವಿವರಣೆಗಳಿಗಾಗಿ ನಾವು ಜವಾಬ್ದಾರಿಯಾಗಿಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->