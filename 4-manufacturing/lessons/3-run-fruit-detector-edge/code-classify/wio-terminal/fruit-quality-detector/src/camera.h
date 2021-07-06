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
