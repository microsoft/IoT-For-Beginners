<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2026-01-07T06:47:13+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "ml"
}
-->
# ഒരു ചിത്രം പിടിക്കുക - Wio ടെർമിനൽ

പാഠത്തിന്റെ ഈ ഭാഗത്തിൽ, നിങ്ങൾ നിങ്ങളുടെ Wio ടെർമിനലിലേക്ക് ഒരു ക്യാമറ ചേർത്ത്, അതിൽ നിന്നു ചിത്രങ്ങൾ പകർന്നു പിടിക്കും.

## ഹാർഡ്‌വെയർ

Wio ടെർമിനലിന് ഒരു ക്യാമറ ആവശ്യമുണ്ട്.

നിങ്ങൾ ഉപയോഗിക്കുന്ന ക്യാമറ [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/) ആണ്. ഇത് OV2640 ഇമേജ് സെൻസർ അടിസ്ഥാനമാക്കിയുള്ള 2 മെഗാപിക്‌സൽ ക്യാമറയാണ്. ഇത് ചിത്രങ്ങൾ പകർന്നു പിടിക്കാൻ SPI ഇന്റർഫേസ് വഴി ആശയവിനിമയം നടത്തുന്നു, സെൻസർ ക്രമീകരിക്കാൻ I<sup>2</sup>C ഉപയോഗിക്കുന്നു.

## ക്യാമറ കണക്റ്റ് ചെയ്യുക

ArduCam-ന് Grove സൊക്കറ്റ് ഇല്ല, പകരം അത് SPI-യും I<sup>2</sup>C ബസ്സുകളിലേക്കും Wio ടെർമിനലിലെ GPIO പിനുകൾ വഴി കണക്റ്റ് ചെയ്യുന്നു.

### ഒരു ജോലി - ക്യാമറ കണക്റ്റ് ചെയ്യുക

ക്യാമറ കണക്റ്റ് ചെയ്യുക.

![An ArduCam sensor](../../../../../translated_images/ml/arducam.20e4e4cbb2682965.png)

1. ArduCam-ന്റെ അടിത്തറയിലെ പിനുകൾ Wio ടെർമിനലിലെ GPIO പിനുകളിലേക്ക് കണക്റ്റ് ചെയ്യണം. ശരിയായ പിനുകൾ കണ്ടെത്താൻ ഇടത്തരം വയ്ക്കാൻ, Wio ടെർമിനലുമായി ಜೊതിക്കപ്പെട്ട GPIO പിന് സ്റ്റിക്കർ പിനുകൾ ചുറ്റി ഒട്ടിക്കുക:

    ![The wio terminal with the GPIO pin sticker on](../../../../../translated_images/ml/wio-terminal-pin-sticker.b90b1535937b84bd.png)

1. ജമ്പർ വയറുകൾ ഉപയോഗിച്ച് താഴെയുള്ള കണക്ഷനുകൾ ചെയ്യുക:

    | ArduCAM പിന് | Wio ടെർമിനൽ പിന് | വിവരണം                             |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | SPI ചിപ് സെലക്ട്                         |
    | MOSI        | 19 (SPI_MOSI)    | SPI കൺട്രോളർ ഔട്ട്പുട്ട്, പെരിഫറൽ ഇൻപുട്ട് |
    | MISO        | 21 (SPI_MISO)    | SPI കൺട്രോളർ ഇൻപുട്ട്, പെരിഫറൽ ഔട്ട്പുട്ട് |
    | SCK         | 23 (SPI_SCLK)    | SPI സീരിയൽ മണിക്കൂർ                        |
    | GND         | 6 (GND)          | ഗ്രൗണ്ട് - 0V                             |
    | VCC         | 4 (5V)           | 5V പവർ സപ്ലൈ                         |
    | SDA         | 3 (I2C1_SDA)     | I<sup>2</sup>C സീരിയൽ ഡാറ്റ              |
    | SCL         | 5 (I2C1_SCL)     | I<sup>2</sup>C സീരിയൽ മണിക്കൂർ             |

    ![The wio terminal connected to the ArduCam with jumper wires](../../../../../translated_images/ml/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.png)

    GND ഉം VCC ഉം കണക്ഷനുകൾ ArduCam-ലേക്ക് 5V പവർ സപ്ലൈ നൽകുന്നു. ഇത് Grove സെൻസറുകൾ (3V-ൽ പ്രവർത്തിക്കുന്നത്) ലെ വന്നുള്ള 5V-ൽ പ്രവർത്തിക്കുന്നു. ഈ പവർ USB-C കണക്ഷനിൽ നിന്നാണ് നേരിട്ട് നേടുന്നത്, അത് ഉപകരണം പവർ ചെയ്യുന്നു.

    > 💁 SPI കണക്ഷനിൽ, ArduCam-ലും Wio ടെർമിനലിലുമായി പിന് ലേബലുകളും കോഡിൽ ഉപയോഗിക്കുന്ന പിന് പേരുകളും പഴയ നാമകരണം തുടരുമ്. ഈ പാഠത്തിലെ നിർദ്ദേശങ്ങൾ പുതിയ നാമകരണ അനുഭവത്തിനൊപ്പം മാത്രമെ ഉപയോഗിക്കുന്നത്, പിന് പേര് കോഡിൽ ഉപയോഗിക്കുമ്പോൾ ഒഴികെ.

1. ഇനി Wio ടെർമിനൽ നിങ്ങളുടെ കമ്പ്യൂട്ടറുമായി കണക്റ്റ് ചെയ്യാം.

## ഡിവൈസ് ക്യാമറയുമായി കണക്റ്റ് ചെയ്യാൻ പ്രോഗ്രാം ചെയ്യുക

Wio ടെർമിനലിൽ ഇപ്പോൾ ലെ അറ്റാച്ച് ചെയ്ത ArduCAM ക്യാമറ ഉപയോഗിക്കാൻ പ്രോഗ്രാം ചെയ്യാം.

### ഒരു ജോലി - ഡിവൈസ് ക്യാമറയുമായി കണക്റ്റ് ചെയ്യാൻ പ്രോഗ്രാം ചെയ്യുക

1. PlatformIO ഉപയോഗിച്ച് പുതിയ Wio ടെർമിനൽ പ്രൊജക്ട് സൃഷ്ടിക്കുക. ഈ പ്രൊജക്ട് `fruit-quality-detector` എന്ന് വിളിക്കുക. സെറിയൽ-Port ക്രമീകരിക്കാൻ `setup` function-ൽ കോഡ് ചേർക്കുക.

1. WiFi കണക്ഷൻ ഏർപ്പെടുത്താൻ കോഡ് ചേർക്കുക, നിങ്ങളുടെ WiFi രേഖകളും `config.h` ഫയലിൽ ഉൾപ്പെടുത്തുക. `platformio.ini` ഫയലിൽ ആവശ്യമായ ലൈബ്രറികൾ ചേർക്കാൻ മറക്കരുത്.

1. ArduCam ലൈബ്രറി Arduino ലൈബ്രറിയായി `platformio.ini`-ൽ നിന്നും ഇൻസ്റ്റാൾ ചെയ്യാനാവില്ല. പകരം GitHub പേജ് വഴി സോഴ്സ് കോഡ് ഡൗൺലോഡ് ചെയ്ത് ഇൻസ്റ്റാൾ ചെയ്തിരിക്കണം. ഇവയിൽ നിന്നെുകണ്ടു ലഭിക്കുന്നു:

    * GitHub repo [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git) ക്ലോൺ ചെയ്യുക
    * GitHub-ൽ [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) ലഭിച്ചുകൊണ്ട് **Code** ബട്ടൺ ക്ലിക്ക് ചെയ്ത് zip ആയി ഡൗൺലോഡ് ചെയ്യുക

1. ഈ കോഡ് ലൊകരിൽ നിന്നും `ArduCAM` ഫോൾഡർ മാത്രം വേണം. മൊത്തം ഫോൾഡർ നിങ്ങളുടെ പ്രൊജക്ടിലെ `lib` ഫോൾഡറിലേക്ക് കോപ്പി ചെയ്യുക.

    > ⚠️ മൊത്തം ഫോൾഡർ കോപ്പി ചെയ്യണം, അഥവാ കോഡ് `lib/ArduCam`-ൽ തന്നെ വേണം. `ArduCam` ഫോൾഡറിലെ ഉള്ളടക്കം സൂക്ഷിച്ച് `lib`-ലേക്ക് മാറ്റരുത്; മുഴുവൻ ഫോൾഡർ കോപ്പി ചെയ്യുക.

1. ArduCam ലൈബ്രറി വിവിധ ക്യാമറകൾക്ക് പ്രവർത്തിക്കുന്നു. നിങ്ങൾ ഉപയോഗിക്കാൻ പോകുന്ന ക്യാമറയുടെ തരമനുസരിച്ച് കോമ്പൈലർ ഫ്ലാഗുകൾ സജ്ജീകരിക്കണം - ഇതിലൂടെ ഉപയോഗിക്കാത്ത ക്യാമറുകൾക്ക് ബന്ധപ്പെട്ട കോഡ് അപ്രാപ്തമാക്കി ലൈബ്രറിയെ ചെറുതാക്കും. OV2640 ക്യാമറയ്ക്കായി ലൈബ്രറി ക്രമീകരിക്കാൻ `platformio.ini` ഫയൽ അവസാനം താഴെയുള്ള കോഡ് ചേർക്കുക:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    ഇത് 2 കോമ്പൈലർ ഫ്ലാഗുകൾ സജ്ജീകരിക്കുന്നു:

      * `ARDUCAM_SHIELD_V2` ലൈബ്രറിയിൽ ക്യാമറ Arduino ബോർഡിൽ (shield ആയി അറിയപ്പെടുന്നത്) ഉണ്ടെന്ന് അറിയിക്കുന്നത്.
      * `OV2640_CAM` ലൈബ്രറിയിൽ OV2640 ക്യാമറയ്ക്ക് ബന്ധപ്പെട്ട കോഡ് മാത്രമേ വേണമെന്ന് അറിയിക്കുന്നത്.

1. `src` ഫോൾഡറിൽ `camera.h` എന്ന ഹെഡർ ഫയൽ ചേർക്കുക. ഇത് ക്യാമറയുമായി ആശയവിനിമയം നടത്താൻ കോഡ് ഇടുന്നതാണ്. താഴെയുള്ള കോഡ് ചേർക്കുക:

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
            // CPLD പുനഃസജ്ജമാക്കുക
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // ArduCAM SPI ബസ് ശരിയാണോ എന്ന് പരിശോധന നടത്തുക
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // MCU മത് മാറ്റുക
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // ക്യാമറ മോഡ്യൂൾ തരം OV2640 ആണോ എന്ന് പരിശോധിക്കുക
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
    
            // ചിത്ര ഫയൽ നീളം നേടുക
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
    
            // ബഫർ സൃഷ്ടിക്കുക
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
                //FIFO-യിൽ നിന്ന് JPEG ഡാറ്റ വായിക്കുക
                if ((temp == 0xD9) && (temp_last == 0xFF)) //അന്ത്യമായതായി കണ്ടെത്തിയാൽ, while ലൂപ്പ് മുടക്കുക
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //ബഫർ പൂർണ്ണമല്ലെങ്കിൽ ചിത്ര ഡാറ്റ ബഫറിലേക്ക് എഴുതുക
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
    
            // ബഫർ മടക്കുക
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    ഇത് ArduCam ലൈബ്രറികൾ ഉപയോഗിച്ച് ക്യാമറ ക്രമീകരിക്കുന്ന, SPI ബസ്സ് ഉപയോഗിച്ച് ആവശ്യപ്പെടുമ്പോൾ ചിത്രങ്ങൾ എടുക്കുന്നതും ഇതാണ്. ഈ കോഡ് ArduCam-ന് മാത്രം പ്രത്യേകം, അതിനാൽ ഇതിന്റെ പ്രവർത്തനം ഇപ്പോൾ മനസ്സിലാക്കേണ്ടതില്ല.

1. `main.cpp`-ലുളള മറ്റ് `include` പ്രഖ്യാപനങ്ങൾക്കു താഴെ താഴെയുള്ള കോഡ് ചേർക്കുക,camera.h ഉൾപ്പെടുത്തുകയും ക്യാമറ ക്ലാസ് ഒബ്ജക്റ്റ് സൃഷ്ടിക്കുകയുമാണ്:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    ഇത് JPEG രൂപത്തിൽ 640x480 റെസല്യൂഷനിൽ ചിത്രങ്ങൾ സംരക്ഷിക്കുന്ന `Camera` ഒബ്ജക്റ്റ് സൃഷ്ടിക്കുന്നു. ഉയർന്ന റെസല്യൂഷൻ (3280x2464 വരെ) പിന്തുണയ്ക്കും, പക്ഷേ ഇമേജ് ക്ലാസ്‌ഫയർ വളരെ ചെറിയ ചിത്രം (227x227) ഉപയോഗിച്ച് പ്രവർത്തിക്കുന്നതിനാൽ വലിയ ചിത്രങ്ങൾ പകർന്നു അയക്കേണ്ട ആവശ്യമില്ല.

1. ക്യാമറ ക്രമീകരിക്കാൻ താഴെ കൊടുക്കുന്ന കോഡ് ചേർക്കുക:

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

    ഈ `setupCamera` ഫംഗ്ഷൻ SPI ചിപ് സെലക്ട് പിനും (`PIN_SPI_SS`) ഉയർന്ന നിലയിൽ ക്രമീകരിച്ച് Wio ടെർമിനൽ SPI കൺട്രോളർ ആക്കുന്നു. ശേഷം I<sup>2</sup>C, SPI ബസ്സുകൾ ആരംഭിക്കും. അവസാനം ക്യാമറ ക്ലാസ്സ് ഇൻഷ്‌ടൻസ് ആരംഭിച്ച് സെൻസർ ക്രമീകരണങ്ങൾ നടത്തുകയും എല്ലാം ശരിയായ രീതിയിൽ ബന്ധിപ്പിച്ചിട്ടുണ്ടെന്ന് ഉറപ്പാക്കുകയും ചെയ്യും.

1. `setup` ഫംഗ്ഷൻ അവസാനം ഈ ഫംഗ്ഷൻ വിളിക്കുക:

    ```cpp
    setupCamera();
    ```

1. കോഡ് ബിൽഡ് ചെയ്ത് അപ്‌ലോഡ് ചെയ്യുക, സെരിയൽ മോണിറ്ററിൽ ഔട്ട്പുട്ട് പരിശോധിക്കുക. `Error setting up the camera!` എന്ന സന്ദേശം കാണുമെങ്കിൽ വയറിംഗ് പരിശോധിച്ച് എല്ലാം ശരിയായ GPIO പിനുകളിലേക്കുള്ള കേബിളുകൾ കണക്റ്റ് ചെയ്‌തിട്ടുണ്ടോയെന്ന് ഉറപ്പ് വരുത്തുക; ജമ്പർ വയറുകൾ ശരിയായ വിധത്തിൽ കഠിനമായി സീറ്റുചെയ്യപ്പെട്ടിട്ടുണ്ടോ എന്ന് പരിശോധിക്കുക.

## ഒരു ചിത്രം പകര്‍ത്തുക

Wio ടെർമിനലിനെ ഇനി ഒരു ബട്ടൺ അമർത്തുമ്പോൾ ചിത്രം പകര്‍ത്താൻ പ്രോഗ്രാം ചെയ്യാവുന്നതാണ്.

### ഒരു ജോലി - ഒരു ചിത്രം പകര്‍ത്തുക

1. മൈക്രോക്കൺട്രോളറുകൾ കോഡ് അനന്തം പ്രവർത്തിപ്പിക്കുന്നു, അതിനാൽ ഒരു സെൻസർ ഉണ്ടാകാതെ ഫോട്ടോ എടുക്കുന്നത് മെച്ചപ്പെട്ട രീതിയിൽ ട്രിഗർചെയ്യാൻ പറ്റില്ല. Wio ടെർമിനലിന് അടുക്കിലുള്ള ബട്ടണുകൾ ഉപയോഗിച്ച് ക്യാമറ ഒരു ബട്ടൺ അമർത്തലിലൂടെ ട്രിഗർചെയ്യാം. താഴെ കാണുന്ന കോഡ് `setup` ഫംഗ്ഷൻ അവസാനം ചേർക്കുക, കഴിയും സി ബട്ടൺ (മുകളിൽ മൂന്ന് ബട്ടണുകളിൽ പവർ സ്വിച്ച് അടുത്തതാണത്).

    ![The C button on the top closest to the power switch](../../../../../translated_images/ml/wio-terminal-c-button.73df3cb1c1445ea0.png)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    `INPUT_PULLUP` മോഡ് ഇൻപുട്ടിനെ പ്രത്യക്ഷമായി മറിക്കുകയാണ്. ഉദാഹരണത്തിന്, സാധാരണ ഒരു ബട്ടൺ അമർച്ച ചെയ്യാത്തപ്പോൾ ലോ സിഗ്നൽ അയയ്ക്കുകയും അമർത്തുമ്പോൾ ഹൈ സിഗ്നൽ അയയ്ക്കുകയും ചെയ്യും. എന്നാൽ `INPUT_PULLUP` ആയി ക്രമീകരിച്ചാൽ അമർത്താത്തപ്പോൾ ഹൈ സിഗ്നൽ അയയ്ക്കുകയും, അമർത്തിയപ്പോൾ ലോ സിഗ്നൽ അയയ്ക്കും.

1. `loop` ഫംഗ്ഷൻക്ക് മുൻപ്, ബട്ടൺ അമർത്തലിന് പ്രതികരിക്കുന്ന പുതിയ ഒരു ശൂന്യ ഫംഗ്ഷൻ ചേർക്കുക:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. ബട്ടൺ അമർത്തിയപ്പോൾ ഇത് `loop` ഫംഗ്ഷനിൽ വിളിക്കുക:

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

    ഈ കീ ബട്ടൺ അമർത്തിയെന്ന് പരിശോധിക്കുന്നു. അമർത്തിയാൽ `buttonPressed` ഫംഗ്ഷൻ വിളിക്കപ്പെടും, തുടർന്ന് 2 സെക്കൻഡ് ഇടവേള നൽകുന്നു. ബട്ടൺ വിട്ടുപോയെന്ന് ഉറപ്പാക്കാൻ ഇത് ആണ്, അപ്പോൾ ലോംഗ് പ്രസ് രണ്ടുതവണ പിശക് ആയി രജിസ്റ്റർ ചെയ്യപ്പെടുകയില്ല.

    > 💁 Wio ടെർമിനലിലെ ബട്ടൺ `INPUT_PULLUP` ആയതിനാൽ അമർത്താത്തപ്പോൾ ഹൈ സിഗ്നൽ, അമർത്തുമ്പോൾ ലോ സിഗ്നൽ അയച്ചുകൊള്ളുന്നു.

1. `buttonPressed` ഫംഗ്ഷനിൽ താഴെ കാണുന്ന കോഡ് ചേർക്കുക:

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

    ഈ കോഡ് `startCapture` വിളിച്ച് ക്യാമറ ക്യാപ്ചർ ആരംഭിക്കുന്നു. ക്യാമറ ഹാർഡ്വെയർ ഡാറ്റ തിരികെ നൽകുന്നതുപോലെ പ്രവർത്തിക്കാതെ, ക്യാപ്ചർ തുടങ്ങാൻ നിര്‍ദ്ദേശം അയയ്ക്കുന്നു, പിന്നെ ക്യാമറ പിറകിൽ പ്രവർത്തിച്ച് ചിത്രം പകർന്നു പിടുത്തു JPEG ആയി മാറ്റി ക്യാമറയിലെ ലോക്കൽ ബഫറിൽ സൂക്ഷിക്കും. `captureReady` വിളിച്ചപ്പോൾ യഥാർത്ഥ ചിത്രം പകർന്നു കഴിഞ്ഞോ എന്ന് പരിശോധിക്കുന്നു.

    ക്യാപ്ചർ കഴിഞ്ഞാൽ, `readImageToBuffer` വിളിച്ച് ക്യാമറയിലെ ബഫർയിൽ നിന്നുള്ള ചിത്രം സ്ഥലത്തു ബഫറിലേക്ക് (ബൈറ്റുകളുടെ അറേ) കോപ്പി ചെയ്യും. ബഫറിന്റെ നീളം സെറിയൽ മോണിറ്ററിലേക്ക് അയയ്ക്കുന്നു.

1. കോഡ് ബിൽഡ് ചെയ്ത് അപ്‌ലോഡ് ചെയ്യുക, സെരിയൽ മോണിറ്റർ ഔട്ട്പുട്ട് പരിശോധിക്കുക. ഓരോ തവണയും C ബട്ടൺ അമർത്തുമ്പോൾ ചിത്രം പകർന്നു പിടിക്കും, ചിത്രത്തിന്റെ വലിപ്പം സെരിയൽ മോണിറ്ററിൽ കാണാം.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    വിവിധ ചിത്രങ്ങളുടെ വലിപ്പം വ്യത്യസ്തമാണ്. ഇവ JPEG ഉം കൊണ്ട് സംക്ഷിപ്തമാക്കപ്പെട്ടാണ്, ഒരു JPEG ഫയലിന്റെ വലിപ്പം ചിത്രത്തിലെ ഉള്ളടക്കത്തെ ആശ്രയിച്ചിരിക്കുന്നു.

> 💁 ഈ കോഡ് [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal) ഫോൾഡറിൽ ലഭ്യമാണ്.

😀 നിങ്ങൾ വിജയകരമായി Wio ടെർമിനലിൽ ചിത്രങ്ങൾ പകർന്നു പിടിച്ചു.

## ഐച്ഛികം - ക്യാമറ ചിത്രങ്ങൾ SD കാർഡ് ഉപയോഗിച്ച് സ്ഥിരീകരിക്കുക

ക്യാമറ പിടിച്ചെടുത്ത ചിത്രങ്ങൾ കാണാനുള്ള എളുപ്പം ഒരു SD കാർഡിൽ എഴുതുന്നതിനും പിന്നീട് നിങ്ങളുടെ കമ്പ്യൂട്ടറിൽ അവ കാണുന്നതിനുമാണ്. spare microSD കാർഡ്, microSD കാർഡ് സോക്കറ്റ് (അഡാപ്റ്റർ സഹിതം) ഉള്ളപ്പോൾ മാത്രം ഇത് ചെയ്യുക.

Wio ടെർമിനൽ 16GB വരെ microSD കാർഡുകൾ മാത്രം പിന്തുണയ്ക്കുന്നു. വലിയ കാർഡുകൾ പൊരുത്തപ്പെടില്ല.

### ഒരു ജോലി - ക്യാമറ ചിത്രങ്ങൾ SD കാർഡ് ഉപയോഗിച്ച് സ്ഥിരീകരിക്കുക

1. നിങ്ങളുടെ കമ്പ്യൂട്ടറിൽ അനുയോജ്യമായ ആപ്ലിക്കേഷൻ ഉപയോഗിച്ച് microSD കാർഡ് FAT32 അല്ലെങ്കിൽ exFAT ആയി ഫോർമാറ്റ് ചെയ്യുക (macOS-ൽ Disk Utility, Windows-ൽ File Explorer, Linux-ൽ കമാൻഡ് ലൈൻ ടൂൾസ്).

1. microSD കാർഡ് പവർ സ്വിച്ച് താഴെയുള്ള സോക്കറ്റിൽ ഇടുക. ഇത് ക്ലിക്കുചേർന്നും സ്ഥിതിചെയ്യുന്നതുമാകുന്നതുവരെ മൂടിക്കടക്കണം, നിങ്ങളുടെ നഖം അല്ലെങ്കിൽ നൂലി പോലുള്ള മെതിൾ ഉപകരണം ഉപയോഗിച്ച് അടിച്ചേക്കാവുന്നതാണ്.

1. `main.cpp` ഫയലിന്റെ മുകളില്‍ താഴെ കാണുന്ന include പ്രസ്താവനകള്‍ ചേർക്കുക:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. `setup`-ന് മുമ്പ് താഴെ കാണുന്ന ഫംഗ്ഷൻ ചേർക്കുക:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    ഇത് SPI ബസ് ഉപയോഗിച്ച് SD കാർഡ് ക്രമീകരിക്കുന്നു.

1. ഇത് `setup` ഫംഗ്ഷനിൽ വിളിക്കുക:

    ```cpp
    setupSDCard();
    ```

1. `buttonPressed` ഫംഗ്ഷൻക്ക് മുകളിൽ താഴെ കാണുന്ന കോഡ് ചേർക്കുക:

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

    ഇത് ഫയൽ കണക്കിന് ഒരു ഗ്ലോബൽ വർണന നൽകുന്നു. ചിത്രം ഫയൽ നാമങ്ങൾക്ക് ഇത് ഉപയോഗിക്കുന്നു, അതായത് പല ചിത്രങ്ങളും വ്യത്യസ്തമായ ഫയൽ നാമങ്ങളോടെ (1.jpg, 2.jpg തുടങ്ങിയവ) സേവ് ചെയ്യപ്പെടും.

    തുടർന്ന് `saveToSDCard` എന്ന ഫംഗ്ഷൻ നിർവ്വചിക്കുന്നു, ബൈറ്റുകളുടെ ബഫറും ബഫർ നീളവും സ്വീകരിച്ച് ഫയൽ നാമം സൃഷ്ടിക്കുകയും, കണക്കു കൂട്ടുകയും, ബഫറിൽ നിന്ന് ബൈനറി ഡാറ്റ ഫയലിലേക്ക് എഴുതുകയും ചെയ്യും.

1. `buttonPressed` ഫംഗ്ഷനിൽ ബഫർ ഡിലീറ്റ് ചെയ്യുന്നതിന് **മുന്‍പായി** `saveToSDCard` ഫംഗ്ഷൻ വിളിക്കുക:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. കോഡ് ബിൽഡ് ചെയ്ത് അപ്‌ലോഡ് ചെയ്യുക, സെരിയൽ മോണിറ്ററിൽ ഔട്ട്പുട്ട് പരിശോധിക്കുക. ഓരോ തവണയും C ബട്ടൺ അമർത്തുമ്പോൾ ചിത്രം പകർന്നു പിടിക്കുകയും SD കാർഡിൽ സേവ് ചെയ്യപ്പെടുകയും ചെയ്യും.

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

1. microSD കാർഡിന്റെ പവർ ഓഫാക്കി ഞെക്കി പുറത്തെടുക്കുക, അത് പിൻവാങ്ങി പുറത്ത് പണഞ്ഞു വരും. ഇത് ചെയ്യാൻ നിങ്ങൾക്ക് ഒരു ചെറു ഉപകരണം ഉപയോഗിക്കാൻ ആവാം. microSD കാർഡ് നിങ്ങളുടെ കമ്പ്യൂട്ടറിൽ കണക്റ്റ് ചെയ്ത് ചിത്രങ്ങൾ കാണുക.

    ![A picture of a banana captured using the ArduCam](../../../../../translated_images/ml/banana-arducam.be1b32d4267a8194.jpg)

    > 💁 ക്യാമറ വൈകി വൈറ്റ് ബാലൻസ് ക്രമീകരിക്കാൻ ചില ചിത്രങ്ങൾ എടുക്കേണ്ടി വരാം. ഇതിനുള്ള സൂചനയായി ചിത്രങ്ങളുടെ നിറം ആദ്യമായി സ്വാഭാവികമല്ലാതെ കാണാം. ഈ പ്രശ്‌നം പരാമർശിക്കാൻ നിങ്ങൾക്ക് സജ്ജമാക്കപ്പെട്ട `setup` ഫംഗ്ഷനിൽ ക്യാപ്ചർ ചെയ്ത ചിത്രങ്ങളിൽ ആദ്യ കുറെ(ignore) മാറ്റി പോകാം.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ഡിസ്ക്ലെയ്മർ**:  
ഈ ഡോക്യുമെന്റ് AI പരിഭാഷ സേവനം [Co-op Translator](https://github.com/Azure/co-op-translator) ഉപയോഗിച്ച് പരിഭാഷ ചെയ്തതാണ്. നാം കൃത്യതയ്ക്ക് ശ്രമിച്ചുവെങ്കിലും, ഓട്ടോമേറ്റഡ് പരിഭാഷകളിൽ പിശകുകൾ അല്ലെങ്കിൽ不ശുദ്ധികൾ ഉണ്ടായിരിക്കാൻ സാധ്യതയുണ്ട്. അതിന്റെ മാതൃഭാഷയിലെ അഭിമുഖ ഡോക്യുമെന്റിനെ മാത്രമേ കാര്യസൂത്രമായി കാണേണ്ടതുള്ളൂ. നിർണായക വിവരങ്ങൾക്കായി, പ്രൊഫഷണൽ മനുഷ്യ പരിഭാഷ നിർദ്ദേശിക്കപ്പെടുന്നു. ഈ പരിഭാഷ ഉപയോഗിച്ചതിനാൽ ഉണ്ടാകുന്ന അതൃപ്തി അല്ലെങ്കിൽ തെറ്റിദ്ധാരണകൾക്കായി ഞങ്ങൾ ഉത്തരവാദിത്തം വഹിക്കുന്നില്ല.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->