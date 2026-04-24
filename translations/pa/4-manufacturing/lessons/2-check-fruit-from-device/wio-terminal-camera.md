# ਤਸਵੀਰ ਕੈਪਚਰ ਕਰੋ - Wio ਟਰਮੀਨਲ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਭਾਗ ਵਿੱਚ, ਤੁਸੀਂ ਆਪਣੇ Wio ਟਰਮੀਨਲ ਵਿੱਚ ਕੈਮਰਾ ਜੋੜੋਗੇ ਅਤੇ ਇਸ ਤੋਂ ਤਸਵੀਰਾਂ ਕੈਪਚਰ ਕਰੋਗੇ।

## ਹਾਰਡਵੇਅਰ

Wio ਟਰਮੀਨਲ ਨੂੰ ਇੱਕ ਕੈਮਰੇ ਦੀ ਲੋੜ ਹੈ।

ਤੁਸੀਂ ਜੋ ਕੈਮਰਾ ਵਰਤੋਗੇ ਉਹ ਹੈ [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)। ਇਹ ਇੱਕ 2 ਮੇਗਾਪਿਕਸਲ ਕੈਮਰਾ ਹੈ ਜੋ OV2640 ਇਮੇਜ ਸੈਂਸਰ 'ਤੇ ਆਧਾਰਿਤ ਹੈ। ਇਹ ਤਸਵੀਰਾਂ ਕੈਪਚਰ ਕਰਨ ਲਈ SPI ਇੰਟਰਫੇਸ ਰਾਹੀਂ ਸੰਚਾਰ ਕਰਦਾ ਹੈ ਅਤੇ ਸੈਂਸਰ ਨੂੰ ਸੰਰਚਿਤ ਕਰਨ ਲਈ I2C ਵਰਤਦਾ ਹੈ।

## ਕੈਮਰੇ ਨੂੰ ਜ਼ੋੜੋ

ArduCam ਵਿੱਚ Grove ਸਾਕਟ ਨਹੀਂ ਹੈ, ਇਸ ਲਈ ਇਹ SPI ਅਤੇ I2C ਬੱਸਾਂ ਨੂੰ Wio ਟਰਮੀਨਲ ਦੇ GPIO ਪਿੰਸ ਰਾਹੀਂ ਜ਼ੋੜਦਾ ਹੈ।

### ਕੰਮ - ਕੈਮਰੇ ਨੂੰ ਜ਼ੋੜੋ

ਕੈਮਰੇ ਨੂੰ ਜ਼ੋੜੋ।

![ArduCam ਸੈਂਸਰ](../../../../../translated_images/pa/arducam.20e4e4cbb2682965.webp)

1. ArduCam ਦੇ ਬੇਸ ਦੇ ਪਿੰਸ ਨੂੰ Wio ਟਰਮੀਨਲ ਦੇ GPIO ਪਿੰਸ ਨਾਲ ਜ਼ੋੜਨਾ ਲਾਜ਼ਮੀ ਹੈ। ਸਹੀ ਪਿੰਸ ਲੱਭਣ ਲਈ, Wio ਟਰਮੀਨਲ ਨਾਲ ਆਉਣ ਵਾਲੇ GPIO ਪਿੰ ਸਟਿਕਰ ਨੂੰ ਪਿੰਸ ਦੇ ਆਲੇ-ਦੁਆਲੇ ਲਗਾਓ:

    ![GPIO ਪਿੰ ਸਟਿਕਰ ਨਾਲ Wio ਟਰਮੀਨਲ](../../../../../translated_images/pa/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. ਜੰਪਰ ਵਾਇਰਾਂ ਦੀ ਵਰਤੋਂ ਕਰਦੇ ਹੋਏ, ਹੇਠਾਂ ਦਿੱਤੇ ਗਏ ਕਨੈਕਸ਼ਨ ਬਣਾਓ:

    | ArduCAM ਪਿੰ | Wio ਟਰਮੀਨਲ ਪਿੰ | ਵੇਰਵਾ                              |
    | ----------- | -------------- | ----------------------------------- |
    | CS          | 24 (SPI_CS)    | SPI ਚਿਪ ਸਿਲੈਕਟ                    |
    | MOSI        | 19 (SPI_MOSI)  | SPI ਕੰਟਰੋਲਰ ਆਉਟਪੁੱਟ, ਪੈਰੀਫੇਰਲ ਇਨਪੁੱਟ |
    | MISO        | 21 (SPI_MISO)  | SPI ਕੰਟਰੋਲਰ ਇਨਪੁੱਟ, ਪੈਰੀਫੇਰਲ ਆਉਟਪੁੱਟ |
    | SCK         | 23 (SPI_SCLK)  | SPI ਸੀਰੀਅਲ ਕਲਾਕ                   |
    | GND         | 6 (GND)        | ਗ੍ਰਾਊਂਡ - 0V                       |
    | VCC         | 4 (5V)         | 5V ਪਾਵਰ ਸਪਲਾਈ                     |
    | SDA         | 3 (I2C1_SDA)   | I2C ਸੀਰੀਅਲ ਡਾਟਾ                   |
    | SCL         | 5 (I2C1_SCL)   | I2C ਸੀਰੀਅਲ ਕਲਾਕ                   |

    ![ਜੰਪਰ ਵਾਇਰਾਂ ਨਾਲ ArduCam ਨੂੰ Wio ਟਰਮੀਨਲ ਨਾਲ ਜੁੜਿਆ ਹੋਇਆ](../../../../../translated_images/pa/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.webp)

    GND ਅਤੇ VCC ਕਨੈਕਸ਼ਨ ArduCam ਨੂੰ 5V ਪਾਵਰ ਸਪਲਾਈ ਪ੍ਰਦਾਨ ਕਰਦੇ ਹਨ। ਇਹ 5V 'ਤੇ ਚਲਦਾ ਹੈ, ਜਿਵੇਂ ਕਿ Grove ਸੈਂਸਰ 3V 'ਤੇ ਚਲਦੇ ਹਨ। ਇਹ ਪਾਵਰ ਸਿੱਧੇ USB-C ਕਨੈਕਸ਼ਨ ਤੋਂ ਆਉਂਦੀ ਹੈ ਜੋ ਡਿਵਾਈਸ ਨੂੰ ਪਾਵਰ ਦਿੰਦੀ ਹੈ।

    > 💁 SPI ਕਨੈਕਸ਼ਨ ਲਈ ArduCam ਅਤੇ Wio ਟਰਮੀਨਲ ਪਿੰ ਨਾਂ ਜੋ ਕੋਡ ਵਿੱਚ ਵਰਤੇ ਜਾਂਦੇ ਹਨ, ਪੁਰਾਣੇ ਨਾਂਕਰਨ ਨੂੰ ਵਰਤਦੇ ਹਨ। ਇਸ ਪਾਠ ਵਿੱਚ ਨਵੇਂ ਨਾਂਕਰਨ ਦੀ ਵਰਤੋਂ ਕੀਤੀ ਜਾਵੇਗੀ, ਸਿਵਾਏ ਜਦੋਂ ਪਿੰ ਨਾਂ ਕੋਡ ਵਿੱਚ ਵਰਤੇ ਜਾਂਦੇ ਹਨ।

1. ਹੁਣ ਤੁਸੀਂ Wio ਟਰਮੀਨਲ ਨੂੰ ਆਪਣੇ ਕੰਪਿਊਟਰ ਨਾਲ ਜ਼ੋੜ ਸਕਦੇ ਹੋ।

## ਕੈਮਰੇ ਨਾਲ ਜੁੜਨ ਲਈ ਡਿਵਾਈਸ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ

ਹੁਣ Wio ਟਰਮੀਨਲ ਨੂੰ ArduCAM ਕੈਮਰੇ ਨਾਲ ਜੁੜਨ ਲਈ ਪ੍ਰੋਗਰਾਮ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

### ਕੰਮ - ਕੈਮਰੇ ਨਾਲ ਜੁੜਨ ਲਈ ਡਿਵਾਈਸ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ

1. PlatformIO ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇੱਕ ਨਵਾਂ Wio ਟਰਮੀਨਲ ਪ੍ਰੋਜੈਕਟ ਬਣਾਓ। ਇਸ ਪ੍ਰੋਜੈਕਟ ਨੂੰ `fruit-quality-detector` ਕਹੋ। `setup` ਫੰਕਸ਼ਨ ਵਿੱਚ ਸੀਰੀਅਲ ਪੋਰਟ ਨੂੰ ਸੰਰਚਿਤ ਕਰਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ।

1. WiFi ਨਾਲ ਜੁੜਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ, ਆਪਣੇ WiFi ਪ੍ਰਮਾਣ ਪੱਤਰਾਂ ਨੂੰ `config.h` ਫਾਈਲ ਵਿੱਚ ਰੱਖੋ। `platformio.ini` ਫਾਈਲ ਵਿੱਚ ਲੋੜੀਂਦੇ ਲਾਇਬ੍ਰੇਰੀਆਂ ਸ਼ਾਮਲ ਕਰਨਾ ਨਾ ਭੁੱਲੋ।

1. ArduCam ਲਾਇਬ੍ਰੇਰੀ Arduino ਲਾਇਬ੍ਰੇਰੀ ਵਜੋਂ ਉਪਲਬਧ ਨਹੀਂ ਹੈ ਜੋ `platformio.ini` ਫਾਈਲ ਤੋਂ ਇੰਸਟਾਲ ਕੀਤੀ ਜਾ ਸਕਦੀ ਹੈ। ਇਸ ਦੀ ਬਜਾਏ, ਇਸਨੂੰ ਉਨ੍ਹਾਂ ਦੇ GitHub ਪੇਜ ਤੋਂ ਸਰੋਤ ਤੋਂ ਇੰਸਟਾਲ ਕਰਨਾ ਪਵੇਗਾ। ਤੁਸੀਂ ਇਸਨੂੰ ਹਾਸਲ ਕਰ ਸਕਦੇ ਹੋ:

    * ਰਿਪੋ ਨੂੰ [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git) ਤੋਂ ਕਲੋਨ ਕਰਕੇ
    * ਜਾਂ GitHub 'ਤੇ ਰਿਪੋ 'ਤੇ ਜਾ ਕੇ ਅਤੇ **Code** ਬਟਨ ਤੋਂ ਕੋਡ ਨੂੰ ਜ਼ਿਪ ਵਜੋਂ ਡਾਊਨਲੋਡ ਕਰਕੇ

1. ਤੁਹਾਨੂੰ ਸਿਰਫ਼ `ArduCAM` ਫੋਲਡਰ ਦੀ ਲੋੜ ਹੈ। ਪੂਰੇ ਫੋਲਡਰ ਨੂੰ ਆਪਣੇ ਪ੍ਰੋਜੈਕਟ ਦੇ `lib` ਫੋਲਡਰ ਵਿੱਚ ਕਾਪੀ ਕਰੋ।

    > ⚠️ ਪੂਰੇ ਫੋਲਡਰ ਨੂੰ ਕਾਪੀ ਕਰਨਾ ਲਾਜ਼ਮੀ ਹੈ, ਤਾਂ ਜੋ ਕੋਡ `lib/ArduCam` ਵਿੱਚ ਹੋਵੇ। ਸਿਰਫ਼ `ArduCam` ਫੋਲਡਰ ਦੀ ਸਮੱਗਰੀ ਨੂੰ `lib` ਫੋਲਡਰ ਵਿੱਚ ਕਾਪੀ ਨਾ ਕਰੋ, ਸਗੋਂ ਪੂਰੇ ਫੋਲਡਰ ਨੂੰ ਕਾਪੀ ਕਰੋ।

1. ArduCam ਲਾਇਬ੍ਰੇਰੀ ਕੋਡ ਕਈ ਕਿਸਮ ਦੇ ਕੈਮਰਿਆਂ ਲਈ ਕੰਮ ਕਰਦਾ ਹੈ। ਤੁਸੀਂ ਜਿਸ ਕਿਸਮ ਦੇ ਕੈਮਰੇ ਦੀ ਵਰਤੋਂ ਕਰਨਾ ਚਾਹੁੰਦੇ ਹੋ, ਉਸਨੂੰ ਕੰਪਾਈਲਰ ਫਲੈਗਾਂ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਸੰਰਚਿਤ ਕੀਤਾ ਜਾਂਦਾ ਹੈ - ਇਹ ਲਾਇਬ੍ਰੇਰੀ ਨੂੰ ਜਿੰਨਾ ਸੰਭਵ ਹੋ ਸਕੇ ਛੋਟਾ ਰੱਖਦਾ ਹੈ। OV2640 ਕੈਮਰੇ ਲਈ ਲਾਇਬ੍ਰੇਰੀ ਨੂੰ ਸੰਰਚਿਤ ਕਰਨ ਲਈ, `platformio.ini` ਫਾਈਲ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਗਇਆ ਸ਼ਾਮਲ ਕਰੋ:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    ਇਹ 2 ਕੰਪਾਈਲਰ ਫਲੈਗ ਸੈਟ ਕਰਦਾ ਹੈ:

      * `ARDUCAM_SHIELD_V2` ਲਾਇਬ੍ਰੇਰੀ ਨੂੰ ਦੱਸਣ ਲਈ ਕਿ ਕੈਮਰਾ ਇੱਕ Arduino ਬੋਰਡ 'ਤੇ ਹੈ।
      * `OV2640_CAM` ਲਾਇਬ੍ਰੇਰੀ ਨੂੰ ਸਿਰਫ਼ OV2640 ਕੈਮਰੇ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰਨ ਲਈ ਦੱਸਣ ਲਈ।

1. `src` ਫੋਲਡਰ ਵਿੱਚ ਇੱਕ ਹੈਡਰ ਫਾਈਲ ਸ਼ਾਮਲ ਕਰੋ ਜਿਸਨੂੰ `camera.h` ਕਹੋ। ਇਹ ਫਾਈਲ ਕੈਮਰੇ ਨਾਲ ਸੰਚਾਰ ਕਰਨ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੇਗੀ। ਇਸ ਫਾਈਲ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਗਇਆ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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
            // Reset the CPLD
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // Check if the ArduCAM SPI bus is OK
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // Change MCU mode
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // Check if the camera module type is OV2640
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
    
            // Get the image file length
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
    
            // create the buffer
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
                //Read JPEG data from FIFO
                if ((temp == 0xD9) && (temp_last == 0xFF)) //If find the end ,break while,
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //Write image data to buffer if not full
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
    
            // return the buffer
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    ਇਹ ਨੀਵੇਂ ਪੱਧਰ ਦਾ ਕੋਡ ਹੈ ਜੋ ArduCam ਲਾਇਬ੍ਰੇਰੀਆਂ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਕੈਮਰੇ ਨੂੰ ਸੰਰਚਿਤ ਕਰਦਾ ਹੈ ਅਤੇ ਜਦੋਂ ਲੋੜ ਹੋਵੇ ਤਸਵੀਰਾਂ ਨੂੰ ਕੈਪਚਰ ਕਰਦਾ ਹੈ। 

1. `main.cpp` ਵਿੱਚ, ਹੋਰ `include` ਬਿਆਨਾਂ ਦੇ ਹੇਠਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਗਇਆ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    ਇਹ ਇੱਕ `Camera` ਬਣਾਉਂਦਾ ਹੈ ਜੋ ਤਸਵੀਰਾਂ ਨੂੰ JPEGs ਵਜੋਂ 640x480 ਰੈਜ਼ੋਲੂਸ਼ਨ 'ਤੇ ਸੇਵ ਕਰਦਾ ਹੈ। 

1. ਕੈਮਰੇ ਨੂੰ ਸੈਟਅੱਪ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਗਇਆ ਫੰਕਸ਼ਨ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ `setupCamera` ਫੰਕਸ਼ਨ SPI ਚਿਪ ਸਿਲੈਕਟ ਪਿੰ (`PIN_SPI_SS`) ਨੂੰ ਉੱਚਾ ਸੈਟ ਕਰਕੇ ਸ਼ੁਰੂ ਕਰਦਾ ਹੈ, SPI ਅਤੇ I2C ਬੱਸਾਂ ਨੂੰ ਸ਼ੁਰੂ ਕਰਦਾ ਹੈ, ਅਤੇ ਕੈਮਰੇ ਨੂੰ ਸੰਰਚਿਤ ਕਰਦਾ ਹੈ।

1. ਇਸ ਫੰਕਸ਼ਨ ਨੂੰ `setup` ਫੰਕਸ਼ਨ ਦੇ ਅੰਤ ਵਿੱਚ ਕਾਲ ਕਰੋ:

    ```cpp
    setupCamera();
    ```

1. ਇਸ ਕੋਡ ਨੂੰ ਬਣਾਓ ਅਤੇ ਅਪਲੋਡ ਕਰੋ, ਅਤੇ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਤੋਂ ਆਉਟਪੁੱਟ ਦੀ ਜਾਂਚ ਕਰੋ। 

## ਤਸਵੀਰ ਕੈਪਚਰ ਕਰੋ

ਹੁਣ Wio ਟਰਮੀਨਲ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ ਕਿ ਜਦੋਂ ਬਟਨ ਦਬਾਇਆ ਜਾਵੇ ਤਾਂ ਤਸਵੀਰ ਕੈਪਚਰ ਕਰੇ।

### ਕੰਮ - ਤਸਵੀਰ ਕੈਪਚਰ ਕਰੋ

1. ਮਾਈਕਰੋਕੰਟਰੋਲਰ ਤੁਹਾਡੇ ਕੋਡ ਨੂੰ ਲਗਾਤਾਰ ਚਲਾਉਂਦੇ ਹਨ, ਇਸ ਲਈ ਤਸਵੀਰ ਲੈਣ ਵਰਗੇ ਕੰਮ ਨੂੰ ਟ੍ਰਿਗਰ ਕਰਨਾ ਆਸਾਨ ਨਹੀਂ ਹੈ। Wio ਟਰਮੀਨਲ ਵਿੱਚ ਬਟਨ ਹਨ, ਇਸ ਲਈ ਕੈਮਰੇ ਨੂੰ ਇੱਕ ਬਟਨ ਦੁਆਰਾ ਟ੍ਰਿਗਰ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ। `setup` ਫੰਕਸ਼ਨ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਗਇਆ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ![ਪਾਵਰ ਸਵਿੱਚ ਦੇ ਕੋਲ C ਬਟਨ](../../../../../translated_images/pa/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    `INPUT_PULLUP` ਮੋਡ ਇੱਕ ਇਨਪੁੱਟ ਨੂੰ ਅਲਟਾ ਕਰਦਾ ਹੈ। 

1. ਬਟਨ ਦਬਾਉਣ ਲਈ ਪ੍ਰਤੀਕਿਰਿਆ ਕਰਨ ਲਈ `loop` ਫੰਕਸ਼ਨ ਤੋਂ ਪਹਿਲਾਂ ਇੱਕ ਖਾਲੀ ਫੰਕਸ਼ਨ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. ਜਦੋਂ ਬਟਨ ਦਬਾਇਆ ਜਾਵੇ ਤਾਂ `loop` ਫੰਕਸ਼ਨ ਵਿੱਚ ਇਸ ਫੰਕਸ਼ਨ ਨੂੰ ਕਾਲ ਕਰੋ:

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

    ਇਹ ਕੁੰਜੀ ਜਾਂਚਦੀ ਹੈ ਕਿ ਕੀ ਬਟਨ ਦਬਾਇਆ ਗਿਆ ਹੈ। 

1. `buttonPressed` ਫੰਕਸ਼ਨ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਗਇਆ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ ਕੈਮਰੇ ਕੈਪਚਰ ਨੂੰ ਸ਼ੁਰੂ ਕਰਦਾ ਹੈ। 

1. ਇਸ ਕੋਡ ਨੂੰ ਬਣਾਓ ਅਤੇ ਅਪਲੋਡ ਕਰੋ, ਅਤੇ ਸੀਰੀਅਲ ਮਾਨੀਟਰ 'ਤੇ ਆਉਟਪੁੱਟ ਦੀ ਜਾਂਚ ਕਰੋ। 

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    ਵੱਖ-ਵੱਖ ਤਸਵੀਰਾਂ ਦੇ ਵੱਖ-ਵੱਖ ਆਕਾਰ ਹੋਣਗੇ। 

😀 ਤੁਸੀਂ ਆਪਣੇ Wio ਟਰਮੀਨਲ ਨਾਲ ਤਸਵੀਰਾਂ ਕੈਪਚਰ ਕਰਨ ਵਿੱਚ ਸਫਲ ਹੋ ਗਏ ਹੋ।

## ਵਿਕਲਪਿਕ - ਕੈਮਰੇ ਦੀਆਂ ਤਸਵੀਰਾਂ ਨੂੰ SD ਕਾਰਡ ਦੀ ਵਰਤੋਂ ਨਾਲ ਸਤਿਆਪਿਤ ਕਰੋ

ਤਸਵੀਰਾਂ ਨੂੰ ਵੇਖਣ ਦਾ ਸਭ ਤੋਂ ਆਸਾਨ ਤਰੀਕਾ ਇਹ ਹੈ ਕਿ ਉਨ੍ਹਾਂ ਨੂੰ SD ਕਾਰਡ 'ਤੇ ਲਿਖੋ। 

### ਕੰਮ - SD ਕਾਰਡ ਦੀ ਵਰਤੋਂ ਨਾਲ ਕੈਮਰੇ ਦੀਆਂ ਤਸਵੀਰਾਂ ਨੂੰ ਸਤਿਆਪਿਤ ਕਰੋ

1. ਇੱਕ microSD ਕਾਰਡ ਨੂੰ FAT32 ਜਾਂ exFAT ਵਿੱਚ ਫਾਰਮੈਟ ਕਰੋ। 

1. microSD ਕਾਰਡ ਨੂੰ ਸਾਕਟ ਵਿੱਚ ਪਾਓ। 

1. `main.cpp` ਫਾਈਲ ਦੇ ਸ਼ੁਰੂ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤੇ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. `setup` ਫੰਕਸ਼ਨ ਤੋਂ ਪਹਿਲਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਫੰਕਸ਼ਨ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    ਇਹ SD ਕਾਰਡ ਨੂੰ ਸੰਰਚਿਤ ਕਰਦਾ ਹੈ। 

1. ਇਸਨੂੰ `setup` ਫੰਕਸ਼ਨ ਵਿੱਚ ਕਾਲ ਕਰੋ:

    ```cpp
    setupSDCard();
    ```

1. `buttonPressed` ਫੰਕਸ਼ਨ ਤੋਂ ਪਹਿਲਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਗਲੋਬਲ ਵੈਰੀਏਬਲ ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕਰਦਾ ਹੈ। 

1. `saveToSDCard` ਫੰਕਸ਼ਨ ਨੂੰ `buttonPressed` ਫੰਕਸ਼ਨ ਵਿੱਚ ਕਾਲ ਕਰੋ। 

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. ਇਸ ਕੋਡ ਨੂੰ ਬਣਾਓ ਅਤੇ ਅਪਲੋਡ ਕਰੋ। 

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

1. microSD ਕਾਰਡ ਨੂੰ ਬਾਹਰ ਕੱਢੋ ਅਤੇ ਆਪਣੇ ਕੰਪਿਊਟਰ ਵਿੱਚ ਪਾਓ। 

    ![ArduCam ਨਾਲ ਕੈਪਚਰ ਕੀਤੀ ਗਈ ਕੇਲੇ ਦੀ ਤਸਵੀਰ](../../../../../translated_images/pa/banana-arducam.be1b32d4267a8194.webp)
💁 ਕੈਮਰੇ ਦੇ ਵ੍ਹਾਈਟ ਬੈਲੈਂਸ ਨੂੰ ਆਪਣੇ ਆਪ ਠੀਕ ਕਰਨ ਲਈ ਕੁਝ ਚਿੱਤਰ ਲੱਗ ਸਕਦੇ ਹਨ। ਤੁਸੀਂ ਇਸਨੂੰ ਕੈਪਚਰ ਕੀਤੇ ਗਏ ਚਿੱਤਰਾਂ ਦੇ ਰੰਗ ਦੇ ਆਧਾਰ 'ਤੇ ਨੋਟਿਸ ਕਰੋਗੇ, ਪਹਿਲੇ ਕੁਝ ਚਿੱਤਰਾਂ ਦਾ ਰੰਗ ਠੀਕ ਨਹੀਂ ਲੱਗ ਸਕਦਾ। ਤੁਸੀਂ ਹਮੇਸ਼ਾ ਇਸਨੂੰ ਕੋਡ ਨੂੰ ਬਦਲ ਕੇ ਠੀਕ ਕਰ ਸਕਦੇ ਹੋ ਤਾਂ ਕਿ ਕੁਝ ਚਿੱਤਰ ਕੈਪਚਰ ਕੀਤੇ ਜਾਣ ਜੋ `setup` ਫੰਕਸ਼ਨ ਵਿੱਚ ਅਣਡਿੱਠੇ ਰਹਿੰਦੇ ਹਨ।


---

**ਅਸਵੀਕਰਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚਤਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਇਸ ਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਮੌਜੂਦ ਅਸਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤ ਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।