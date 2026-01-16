<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2026-01-07T06:45:31+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "te"
}
-->
# చిత్రం తీసుకోండి - Wio Terminal

ఈ పాఠం భాగంలో, మీరు మీ Wio Terminalకి కెమెరాను జోడించి, దానితో నుండి చిత్రాలను గ్రహిస్తారు.

## హార్డు‌వేర్

Wio Terminalకి కెమెరా అవసరం.

మీరు ఉపయోగించబోయే కెమెరా [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/) . ఇది OV2640 ఇమేజ్ సెన్సార్ ఆధారమైన 2 మెగాపిక్సెల్ కెమెరా. ఇది చిత్రాలను గ్రహించడానికి SPI ఇంటర్ఫేస్ ద్వారా కమ్యూనికేట్ చేస్తుంది, మరియు సెన్సార్‌ను కాన్ఫిగర్ చేయడానికి I<sup>2</sup>C ఉపయోగిస్తుంది.

## కెమెరాను కనెక్ట్ చేయండి

ArduCamకి Grove సాకెట్ లేదు, దాని బదులు ఇది Wio Terminal పై GPIO పిన్ల ద్వారా SPI మరియు I<sup>2</sup>C బస్సులకు కనెక్ట్ అవుతుంది.

### పని - కెమెరాను కనెక్ట్ చేయండి

కెమెరాను కనెక్ట్ చేయండి.

![An ArduCam sensor](../../../../../translated_images/te/arducam.20e4e4cbb2682965.png)

1. ArduCam ఆధారంలోని పిన్లు Wio Terminal పైని GPIO పిన్లకు కనెక్ట్ చేయాలి. సరైన పిన్లను కనుగొనడానికి సులభం గా చేయడానికి, Wio Terminal తో వస్తు GPIO పిన్ స్టికర్‌ను పిన్ల చుట్టూ జతచేయండి:

    ![The wio terminal with the GPIO pin sticker on](../../../../../translated_images/te/wio-terminal-pin-sticker.b90b1535937b84bd.png)

1. జంపర్ వైర్స్ ఉపయోగించి, క్రింది కనెక్షన్లు చేయండి:

    | ArduCAM పిన్ | Wio Terminal పిన్ | వివరణ                                  |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | SPI చిప్ సెలెక్ట్                       |
    | MOSI        | 19 (SPI_MOSI)    | SPI కంట్రోలర్ అవుట్‌పుట్, పిరిఫెరల్ ఇన్‌పుట్ |
    | MISO        | 21 (SPI_MISO)    | SPI కంట్రోలర్ ఇన్‌పుట్, పిరిఫెరల్ అవుట్‌పుట్ |
    | SCK         | 23 (SPI_SCLK)    | SPI సీరియల్ క్లాక్                     |
    | GND         | 6 (GND)          | గ్రౌండ్ - 0V                           |
    | VCC         | 4 (5V)           | 5V పవర్ సరఫరా                        |
    | SDA         | 3 (I2C1_SDA)     | I<sup>2</sup>C సీరియల్ డేటా               |
    | SCL         | 5 (I2C1_SCL)     | I<sup>2</sup>C సీరియల్ క్లాక్              |

    ![The wio terminal connected to the ArduCam with jumper wires](../../../../../translated_images/te/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.png)

    GND మరియు VCC కనెక్షన్లు ArduCamకి 5V పవర్ సరఫరా చేస్తాయి. ఇది Grove సెన్సార్ల వారిగా 3V వద్ద కాకుండా 5V వద్ద పని చేస్తుంది. ఈ పవర్ డివైస్ కి పవర్ ఇస్తున్న USB-C కనెక్షన్ నుండి నేరుగా వస్తుంది.

    > 💁 SPI కనెక్షన్ కొరకు ArduCam మరియు Wio Terminal పిన్ లేబుల్స్ ఇంకా పాత పేర్లు ఉపయోగిస్తుంటాయి. ఈ పాఠంలో సూచనలు కొత్త పేర్లను ఉపయోగిస్తాయి, కానీ కోడ్‌లో పిన్ పేర్లు పాతవి ఉంటాయి.

1. ఇప్పుడు మీరు Wio Terminalను మీ కంప్యూటరికి కనెక్ట్ చేయవచ్చు.

## కెమెరాతో కనెక్ట్ అవ్వడానికి డివైస్ ను ప్రోగ్రామ్ చేయండి

Wio Terminal ఇప్పుడు జతచేసిన ArduCAM కెమెరాను ఉపయోగించడానికి ప్రోగ్రామ్ చేయవచ్చు.

### పని - కెమెరాకు కనెక్ట్ అవ్వటానికి డివైస్ ను ప్రోగ్రామ్ చేయండి

1. PlatformIO ఉపయోగించి కొత్త Wio Terminal ప్రాజెక్ట్ సృష్టించండి. ఈ ప్రాజెక్ట్ పేరు `fruit-quality-detector` ఉంచండి. `setup` ఫంక్షన్‌లో సీరియల్ పోర్ట్ కాన్ఫిగర్ చేసే కోడ్ జోడించండి.

1. మీ WiFi క్రెడెన్షియల్స్ తో WiFiకి కనెక్ట్ అయ్యే కోడ్ జోడించండి, ఇది `config.h` ఫైల్‌లో ఉండాలి. అవసరమైన లైబ్రరీలను `platformio.ini` ఫైల్‌లో జోడించండి.

1. ArduCam లైబ్రరీ Arduino లైబ్రరీగా `platformio.ini` నుండి ఇన్స్టాల్ కావడం లేదు. దీన్ని GitHub నుండి సోర్స్ ద్వారా ఇన్స్టాల్ చేయాలి. మీరు ఈ విధంగా పొందవచ్చు:

    * [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git) నుండి రిపోలను క్లోన్ చేయండి
    * లేదా GitHubలోని [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) వెబ్‌సైట్ నుండి **Code** బటన్ ద్వారా కోడ్‌ను జిప్ డౌన్లోడ్ చేసుకోండి

1. ఈ కోడ్ నుండి మీరు కేవలం `ArduCAM` ఫోల్డర్ మాత్రమే అవసరం. ఈ ఫోల్డర్‌ను మీ ప్రాజెక్ట్‌లోని `lib` ఫోల్డర్‌లో కాపి చేయండి.

    > ⚠️ మొత్తం ఫోల్డర్ కాపీ చేయాలి, కేవలం `ArduCam` ఫోల్డర్ లోని ఫైళ్లు కాపీ చేయవద్దు, మొత్తం ఫోల్డర్ కాపీ చేయండి.

1. ArduCam లైబ్రరీ కోడ్ వేర్వేరు రకాల కెమెరాల కోసం పనిచేస్తుంది. మీరు ఉపయోగించాలనుకుంటున్న కెమెరా రకం కంపైలర్ ఫ్లాగ్స్ ద్వారా కాన్ఫిగర్ చేయబడుతుంది – ఇది మీకు అవసరం లేని కెమెరా కోడ్‌ను తొలగించి లైబ్రరీని చిన్నదిగా ఉంచుతుంది. OV2640 కెమెరాకు లైబ్రరీని కాన్ఫిగర్ చేయడానికి `platformio.ini` ఫైల్ చివరకి క్రింది కోడ్ జోడించండి:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    ఇది 2 కంపైలర్ ఫ్లాగ్స్‌నూ సెట్ చేస్తుంది:

      * `ARDUCAM_SHIELD_V2` లైబ్రరీకి కెమెరా Arduino బోర్డు (షీల్డ్) మీద ఉందని చెపుతుంది.
      * `OV2640_CAM` లైబ్రరీకి కేవలం OV2640 కెమెరా కోడ్ మాత్రమే చేర్చమని చెపుతుంది.

1. `src` ఫోల్డర్‌లో `camera.h` అనే హెడ్డర్ ఫైల్ జోడించండి. ఇది కెమెరాపై కమ్యూనికేట్ చేసే కోడ్ కలిగి ఉంటుంది. ఈ ఫైల్‌కు క్రింది కోడ్ జోడించండి:

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
            // CPLD ని రీసెట్ చేయండి
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // ArduCAM SPI బస్ బాగున్నదా prüfen
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // MCU మోడ్ మార్చండి
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // కెమెరా మాడ్యుల్ రకం OV2640 గా ఉందో చూడండి
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
    
            // ఇమేజ్ ఫైల్ పొడవు పొందండి
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
    
            // బఫర్ సృష్టించండి
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
                //FIFO నుండి JPEG డేటా చదవండి
                if ((temp == 0xD9) && (temp_last == 0xFF)) //చివర కనుగొనబడితే, while నుండి బయటికి రండి
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //బఫర్ పూర్తిగా లేకపోతే ఇమేజ్ డేటా వ్రాయండి
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
    
            // బఫర్ ని తిరిగి ఇవ్వండి
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    ఇది ArduCam లైబ్రరీలను ఉపయోగించి కెమెరాను నేరుగా కాన్ఫిగర్ చేయగల తక్కువ స్థాయి కోడ్. SPI బస్సు ద్వారా చిత్రాలను అవసరమైనప్పుడు పిలిచి తీసుకుంటుంది. ఈ కోడ్ ArduCamకు ప్రత్యేకమైనది కాబట్టి దీని పని విధానంపై ప్రస్తుతం మీరు విచారించాల్సిన అవసరం లేదు.

1. `main.cpp`లో, ఇతర `include` స్టేట్స్ కింద ఈ కొత్త ఫైల్ ని చేర్చడానికి మరియు `Camera` క్లాస్ యొక్క ఇన్‌స్టెన్స్ ను సృష్టించడానికి క్రింది కోడ్ జోడించండి:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    ఇది 640x480 రిజల్యూషన్‌లో JPEG గా చిత్రాలను సేవ్ చేసే `Camera` ని సృష్టిస్తుంది. ఎక్కువ రిజల్యూషన్లు (3280x2464 వరకు) समर्थించబడినప్పటికీ, ఇమేజ్ క్లాసిఫైయర్ చాలా చిన్న (227x227) చిత్రాలు ఉపయోగిస్తుందని పెద్ద చిత్రాలను క్యాప్చర్ చేసి పంపనవసరం లేదు.

1. కెమెరాను సెటప్ చేసే ఫంక్షన్ నిర్వచించడానికి ఈ క్రింది కోడ్ కూడా జోడించండి:

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

    ఈ `setupCamera` ఫంక్షన్ SPI చిప్ సెలెక్ట్ పిన్ (`PIN_SPI_SS`) ను హైగా సెట్ చేసి Wio Terminalను SPI కంట్రోలర్ గా ఉంచుతుంది. తరువాత I<sup>2</sup>C మరియు SPI బస్సులను ప్రారంభిస్తుంది. చివరగా కెమెరా క్లాస్ ని ఇనిషియలైజ్ చేసి కెమెరా సెన్సార్ సెట్టింగ్స్ ని కాన్ఫిగర్ చేసి కనెక్ట్ అయ్యే పన్నీ సరిగా ఉందని నిర్ధారిస్తుంది.

1. ఈ ఫంక్షన్‌ను `setup` ఫంక్షన్ చివర పిలవండి:

    ```cpp
    setupCamera();
    ```

1. ఈ కోడ్‌ను బిల్డ్ చేసి అప్లోడ్ చేయండి, సీరియల్ మానిటర్ లో అవుట్పుట్‌ని తనిఖీ చేయండి. మీరు `Error setting up the camera!` అనే సందేశం చూస్తే, మీ వైర్పుల్లాన్ని తనిఖీ చేసి ArduCam పై ఉన్న పిన్లను Wio Terminal GPIO పిన్లకు సరిగ్గా కనెక్ట్ చేశారు మరియు జంపర్ వైర్లు సరిగా కదలకుండా ఉన్నాయి అని చూడండి.

## చిత్రం తీసుకోండి

Wio Terminal ఇప్పుడు బటన్ నొక్కినప్పుడు చిత్రం తీసుకోవడానికి ప్రోగ్రామ్ చేయవచ్చు.

### పని - చిత్రం తీసుకోండి

1. మైక్రోకంట్రోలర్లు మీ కోడ్‌ను నిరంతరం నడుపుతుంటాయి, కాబట్టి ఫోటో తీసుకోడానికి సెన్సార్ వంటి టiggers లేని ప్రాసెస్‌ను ట్రిగర్‌ చేయడం సులభం కాదు. Wio Terminal బటన్‌లను కలిగి ఉంది, కాబట్టి కెమెరా ఒక బటన్ తో ట్రిగర్ అయ్యేలా సెట్ చేయవచ్చు. క్రింది కో드를 `setup` ఫంక్షన్ చివర జోడించి C బటన్ (ముప్పై మూడు బటన్లలోకి ఒకటి, పవర్ స్విచ్ కు అత్యంత సమీపంలో ఉన్నది) ని కాన్ఫిగర్ చేయండి.

    ![The C button on the top closest to the power switch](../../../../../translated_images/te/wio-terminal-c-button.73df3cb1c1445ea0.png)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    `INPUT_PULLUP` మోడ్ ఇన్పుట్ ను వలయవంతం చేస్తుంది. ఉదాహరణకు, సాధారణంగా ఒక బటన్ నొక్కకపోతే లో (LOW) సిగ్నల్ పంపుతుంది, నొక్కితే హై (HIGH) సిగ్నల్ పంపుతుంది. కానీ `INPUT_PULLUP`లో, నొక్కకపోతే హై, నొక్కితే లో సిగ్నల్ పంపుతుంది.

1. బటన్ నొక్కినప్పుడు ప్రతిస్పందించే ఖాళీ ఫంక్షన్‌ను `loop` ఫంక్షన్ ముందు జోడించండి:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. బటన్ నొక్కినప్పుడు ఈ ఫంక్షన్‌ను `loop` లో పిలవండి:

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

    ఈ కీ బటన్ నొక్కబడిందో లేదో గుర్తిం్చుతుంది. నొక్కితే `buttonPressed` ఫంక్షన్ పిలవబడుతుంది, మరియు తరువాత 2 సెకండ్ల పాటు లూప్ నిలిపివేస్తుంది. ఇది బటన్ విడుదలకు సమయం ఇస్తుంది అలాగే దీర్ఘ నొక్కడాన్ని రెండు సార్లు నమోదు కాకుండా చేస్తుంది.

    > 💁 Wio Terminal లో బట్టన్ `INPUT_PULLUP`ని సెటప్ చేయబడింది, కాబట్టి నొక్కకపోతే హై సిగ్నల్, నొక్కితే లో సిగ్నల్ పంపుతుంది.

1. క్రింది కోడ్‌ని `buttonPressed` ఫంక్షన్‌కు జోడించండి:

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

    ఈ కోడ్ కెమెరా క్యాప్చర్‌ను `startCapture` పిలుపుతో ప్రారంభిస్తుంది. కెమెరా హార్డ్‌వేర్ డిమాండ్ వచ్చినపుడు డేటా రిటర్న్ చేయదు, మీరు క్యాప్చర్ మొదలు పెట్టమని సూచన పంపుతారు; కెమెరా బ్యాక్‌గ్రౌండ్‌లో పని చేస్తూ చిత్రాన్ని JPEG గా మార్చి, ఆ క్యాప్చర్‌నే స్థానిక బఫర్‌లో నిల్వ చేస్తుంది. `captureReady` కాల్ క్యాప్చర్ ముగించిందో లేదో తనిఖీ చేస్తుంది.

    క్యాప్చర్ పూర్తయిన తర్వాత, `readImageToBuffer` కాల్‌తో బఫర్ నుండి చిత్ర డేటాను స్థానిక బఫర్ (బైట్ల ఆరే)కి కాపీ చేస్తుంది. ఆ తరువాత బఫర్ పొడవును సీరియల్ మానిటర్‌కు పంపుతుంది.

1. ఈ కోడ్‌ను బిల్డ్ చేసి అప్లోడ్ చేసి సీరియల్ మానిటర్ అవుట్పుట్ తనిఖీ చేయండి. మీరు ప్రతిసారి C బటన్ నొక్కినప్పుడు చిత్రం క్యాప్చర్ అవుతుంది మరియు చిత్రం పరిమాణం సీరియల్ మానిటర్‌లో కనిపిస్తుంది.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    వేరు వేరు చిత్రాలకు వేరు వేరు పరిమాణాలు ఉంటాయి. అవి JPEG గా కంప్రెస్ చేయబడి ఉంటాయి మరియు జిపెగ్ ఫైల్ పరిమాణం ఆ చిత్రంలో ఉన్న వస్తువుల ఆధారంగా మారవచ్చు.

> 💁 మీరు ఈ కోడ్‌ను [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal) ఫోల్డర్‌లో కనుగొనవచ్చు.

😀 మీరు విజయవంతంగా Wio Terminalతో చిత్రాలు క్యాప్చర్ చేసారు.

## ఐచ్ఛికం - కెమెరా చిత్రాలను SD కార్డు ఉపయోగించి ధృవీకరించండి

కెమెరా ద్వారా కెప్చర్ చేసిన చిత్రాలను చూడటానికి సులభమైన మార్గం, వాటిని Wio Terminalలో SD కార్డుకు రాయటం మరియు తరువాత మీ కంప్యూటరిపై చూడటం. మీ దగ్గర మైక్రోSD కార్డు మరియు మీ కంప్యూటర్లో మైక్రోSD సాకెట్ లేదా అడాప్టర్ ఉంటే ఈ దశ చేయండి.

Wio Terminal 16GB పరిమితితో మైక్రోSD కార్డ్స్ మాత్రమే మద్దతు ఇస్తుంది. మీరు పెద్ద SD కార్డు ఉంటే అది పని చేయదు.

### పని - SD కార్డు ఉపయోగించి కెమెరా చిత్రాలను ధృవీకరించండి

1. మీ కంప్యూటర్లో సంబంధిత అప్లికేషన్ల ద్వారా (macOS లో Disk Utility, Windows లో File Explorer, లేదా Linux లో కమాండ్ లైన్ టూల్స్ తో) మైక్రోSD కార్డును FAT32 లేదా exFAT గా ఫార్మాట్ చేయండి

1. మైక్రోSD కార్డును పవర్ స్విచ్ కింద ఉన్న సాకెట్‌లో పెట్టండి. అది క్లిక్ చేసి స్థిరంగా నిలవేవరకు పూర్తిగా నించేలా చేయండి, మీరు ఉంగరం లేదా పలుచని సాధనం ఉపయోగించి దాన్ని పుష్ చేయవలసి ఉంటే ఉంటుంది.

1. `main.cpp` ఫైల్ ప్రారంభంలో ఈ ఇన్స్ట్లూడ్స్ జోడించండి:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. `setup` ఫంక్షన్ ముందు క్రింది ఫంక్షన్ జోడించండి:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    ఇది SPI బస్సు ఉపయోగించి SD కార్డ్ కాన్ఫిగర్ చేస్తుంది.

1. దీన్ని `setup` ఫంక్షన్ నుండి పిలవండి:

    ```cpp
    setupSDCard();
    ```

1. `buttonPressed` ఫంక్షన్ పై క్రింది కోడ్ జోడించండి:

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

    ఇది గ్లోబల్ ఫైల్ కౌంట్ వేరియబుల్ నిర్వచిస్తుంది, ఇది చిత్ర ఫైల్ పేర్లకు ఉపయోగపడుతుంది కాబట్టి ఏకకాలంలో పలు చిత్రాలు క్యాప్చర్ అయ్యేందుకు పెరుగుతున్న ఫైల్ పేర్లను - `1.jpg`, `2.jpg` వంటివి - ఏర్పరచుతుంది.

    తరువాత `saveToSDCard` ఫంక్షన్ నిర్వచిస్తుంది, దీనికి బైట్ల బఫర్, బఫర్ పొడవు ఇవ్వబడతాయి. ఫైల్ పేరు ఫైల్ కౌంట్ ఉపయోగించి సృష్టించబడుతుంది, మరియు తర్వాత వాడటానికి ఫైల్ కౌంట్ పెరుగుతుంది. బఫర్ నుండి బైనరీ డేటా ఫైలుకు రాస్తుంది.

1. `buttonPressed` లో బఫర్ డిలీట్ చేసే ముందు `saveToSDCard` కాల్‌ను జోడించండి:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. ఈ కోడ్‌ను బిల్డ్ చేసి అప్లోడ్ చేసి సీరియల్ మానిటర్ అవుట్పుట్ తనిఖీ చేయండి. ప్రతిసారి మీరు C బటన్ నొక్కినప్పుడు చిత్రం క్యాప్చర్ అవుతుంది మరియు SD కార్డులో సేవ్ అవుతుంది.

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

1. మైక్రోSD కార్డును పవర్ ఆఫ్ చేసి, దాని సన్నని పిడుగుతో కొంచెం దింపి వదిలి, అది బయటకు వస్తుంది. దీన్ని చేయడానికి మీకు పలుచని సాధనం అవసరం కావచ్చు. తర్వాత మైక్రోSD కార్డును మీ కంప్యూటర్లో ప్లగ్ చేసి చిత్రాలను చూడండి.

    ![A picture of a banana captured using the ArduCam](../../../../../translated_images/te/banana-arducam.be1b32d4267a8194.jpg)

    > 💁 కెమెరా వైట్ బ్యాలెన్స్ సర్దుబాటు చేసుకోవడానికి కొన్ని చిత్రం తీసుకోవడానికి కొంత సమయం పడుతుంది. మీరు మొదటి కొన్ని చిత్రాలు రంగు పరిస్థితులు తేడాగా ఉంటాయని గమనిస్తారు. దీనిని మీరు కోడ్‌ను మార్చుకొని `setup` లో స్థానికంగా వీక్షించకుండా కొన్ని చిత్రం తీసి నవికారించవచ్చు.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**అస్పష్టత**:
ఈ పత్రాన్ని AI భాషాంతర సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడింది. మేము ఖచ్చితత్వాన్ని లక్ష్యంగా పెట్టుకున్నప్పటికీ, ఆటోమేటెడ్ అనువాదాలలో పొరపాట్లు లేదా తప్పిదాలు ఉండవచ్చును. అసలు పత్రం తల్లి భాషలోనే అధికారిక వనరు అని పరిగణించాలి. కీలకమైన సమాచారం కోసం ప్రొఫెషనల్ మానవ అనువాద సేవను ఉపయోగించాల్సిన అవసరం ఉంది. ఈ అనువాదం వాడకం వల్ల కలిగే అర్థం దొర్లకపోవడం లేదా తప్పుత అర్థం చేసుకోవడం కోసం మేము బాధ్యత వహించము.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->