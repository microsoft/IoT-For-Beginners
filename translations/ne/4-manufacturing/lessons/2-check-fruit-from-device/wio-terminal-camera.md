# तस्बिर खिच्नुहोस् - Wio Terminal

यस पाठको यस भागमा, तपाईं आफ्नो Wio Terminal मा क्यामेरा थप्नुहुनेछ र यसबाट तस्बिरहरू खिच्नुहुनेछ।

## हार्डवेयर

Wio Terminal लाई क्यामेरा चाहिन्छ।

तपाईंले प्रयोग गर्ने क्यामेरा [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/) हो। यो २ मेगापिक्सेल क्यामेरा हो जुन OV2640 इमेज सेन्सरमा आधारित छ। यसले SPI इन्टरफेसमार्फत तस्बिरहरू खिच्छ र I2C मार्फत सेन्सरलाई कन्फिगर गर्दछ।

## क्यामेरा जडान गर्नुहोस्

ArduCam सँग Grove सकेट छैन, यसको सट्टा यो SPI र I2C बसहरूलाई Wio Terminal का GPIO पिनहरू मार्फत जडान गर्दछ।

### कार्य - क्यामेरा जडान गर्नुहोस्

क्यामेरा जडान गर्नुहोस्।

![ArduCam सेन्सर](../../../../../translated_images/ne/arducam.20e4e4cbb2682965.webp)

1. ArduCam को आधारमा रहेका पिनहरू Wio Terminal का GPIO पिनहरूसँग जडान गर्नुपर्छ। सही पिनहरू पत्ता लगाउन सजिलो बनाउन, Wio Terminal सँग आउने GPIO पिन स्टिकरलाई पिनहरूको वरिपरि टाँस्नुहोस्:

    ![GPIO पिन स्टिकर भएको Wio Terminal](../../../../../translated_images/ne/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. जम्पर तारहरूको प्रयोग गरेर, निम्न जडानहरू गर्नुहोस्:

    | ArduCAM पिन | Wio Terminal पिन | विवरण                                  |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | SPI चिप चयन                            |
    | MOSI        | 19 (SPI_MOSI)    | SPI कन्ट्रोलर आउटपुट, पेरिफेरल इनपुट  |
    | MISO        | 21 (SPI_MISO)    | SPI कन्ट्रोलर इनपुट, पेरिफेरल आउटपुट  |
    | SCK         | 23 (SPI_SCLK)    | SPI सिरियल क्लक                        |
    | GND         | 6 (GND)          | ग्राउन्ड - 0V                          |
    | VCC         | 4 (5V)           | 5V पावर सप्लाई                         |
    | SDA         | 3 (I2C1_SDA)     | I2C सिरियल डाटा                        |
    | SCL         | 5 (I2C1_SCL)     | I2C सिरियल क्लक                        |

    ![जम्पर तारहरूसँग Wio Terminal र ArduCam जडान गरिएको](../../../../../translated_images/ne/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.webp)

    GND र VCC जडानहरूले ArduCam लाई 5V पावर सप्लाई प्रदान गर्छ। यो 5V मा चल्छ, जबकि Grove सेन्सरहरू 3V मा चल्छन्। यो पावर USB-C जडानबाट सिधै आउँछ जसले उपकरणलाई पावर दिन्छ।

    > 💁 SPI जडानको लागि ArduCam र Wio Terminal पिन नामहरू कोडमा पुरानो नामकरण प्रणाली प्रयोग गर्छन्। यस पाठमा नयाँ नामकरण प्रणाली प्रयोग गरिनेछ, तर कोडमा प्रयोग गरिएका पिन नामहरूमा पुरानो नाम नै रहनेछ।

1. अब तपाईं Wio Terminal लाई आफ्नो कम्प्युटरसँग जडान गर्न सक्नुहुन्छ।

## क्यामेरासँग जडान गर्न उपकरणलाई प्रोग्राम गर्नुहोस्

अब Wio Terminal लाई जडान गरिएको ArduCAM क्यामेरा प्रयोग गर्न प्रोग्राम गर्न सकिन्छ।

### कार्य - क्यामेरासँग जडान गर्न उपकरणलाई प्रोग्राम गर्नुहोस्

1. PlatformIO प्रयोग गरेर नयाँ Wio Terminal प्रोजेक्ट बनाउनुहोस्। यस प्रोजेक्टलाई `fruit-quality-detector` नाम दिनुहोस्। `setup` फंक्शनमा सिरियल पोर्ट कन्फिगर गर्न कोड थप्नुहोस्।

1. WiFi सँग जडान गर्न कोड थप्नुहोस्, र आफ्नो WiFi प्रमाणपत्रहरू `config.h` नामक फाइलमा राख्नुहोस्। `platformio.ini` फाइलमा आवश्यक लाइब्रेरीहरू थप्न नबिर्सनुहोस्।

1. ArduCam लाइब्रेरी `platformio.ini` फाइलबाट सिधै इन्स्टल गर्न मिल्दैन। यसको सट्टा, यो लाइब्रेरी उनीहरूको GitHub पेजबाट स्रोतबाट इन्स्टल गर्नुपर्छ। तपाईं यसलाई निम्न तरिकाहरूबाट प्राप्त गर्न सक्नुहुन्छ:

    * [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git) बाट रिपोजिटरी क्लोन गर्नुहोस्।
    * GitHub मा [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) मा गएर **Code** बटनबाट कोडलाई zip फाइलको रूपमा डाउनलोड गर्नुहोस्।

1. तपाईंलाई केवल `ArduCAM` फोल्डर चाहिन्छ। यो फोल्डरलाई तपाईंको प्रोजेक्टको `lib` फोल्डरमा पूर्ण रूपमा कपी गर्नुहोस्।

    > ⚠️ पूरा फोल्डर कपी गर्नुपर्छ, ताकि कोड `lib/ArduCam` मा होस्। `ArduCam` फोल्डरको सामग्रीलाई मात्र `lib` फोल्डरमा कपी नगर्नुहोस्, पूरै फोल्डर कपी गर्नुहोस्।

1. ArduCam लाइब्रेरी कोड धेरै प्रकारका क्यामेराहरूका लागि काम गर्छ। तपाईंले प्रयोग गर्न चाहेको क्यामेराको प्रकार कम्पाइलर फ्ल्यागहरू प्रयोग गरेर कन्फिगर गरिन्छ - यसले प्रयोग नगरिएका क्यामेराहरूको कोड हटाएर लाइब्रेरीलाई सानो बनाउँछ। OV2640 क्यामेराका लागि लाइब्रेरी कन्फिगर गर्न, `platformio.ini` फाइलको अन्त्यमा निम्न थप्नुहोस्:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    यसले २ कम्पाइलर फ्ल्यागहरू सेट गर्छ:

      * `ARDUCAM_SHIELD_V2` लाइब्रेरीलाई क्यामेरा Arduino बोर्डमा छ भनेर बताउन।
      * `OV2640_CAM` लाइब्रेरीलाई केवल OV2640 क्यामेराको कोड समावेश गर्न बताउन।

1. `src` फोल्डरमा `camera.h` नामक हेडर फाइल थप्नुहोस्। यसमा क्यामेरासँग संवाद गर्न कोड हुनेछ। यस फाइलमा निम्न कोड थप्नुहोस्:

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

    यो कम-स्तरीय कोड हो जसले ArduCam लाइब्रेरीहरू प्रयोग गरेर क्यामेरालाई कन्फिगर गर्छ र आवश्यक पर्दा SPI बस प्रयोग गरेर तस्बिरहरू निकाल्छ। यो कोड ArduCam का लागि धेरै विशिष्ट छ, त्यसैले तपाईंलाई यसबारे अहिले चिन्ता लिनु पर्दैन।

1. `main.cpp` मा, अन्य `include` कथनहरू मुनि यो नयाँ फाइल समावेश गर्न र क्यामेरा क्लासको उदाहरण सिर्जना गर्न निम्न कोड थप्नुहोस्:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    यसले JPEG फर्म्याटमा 640x480 रिजोल्युसनमा तस्बिरहरू बचत गर्ने `Camera` सिर्जना गर्छ। यद्यपि उच्च रिजोल्युसनहरू समर्थित छन् (3280x2464 सम्म), इमेज क्लासिफायरले धेरै साना तस्बिरहरू (227x227) मा काम गर्छ, त्यसैले ठूलो तस्बिरहरू खिच्न र पठाउन आवश्यक छैन।

1. क्यामेरा सेटअप गर्न फंक्शन परिभाषित गर्न निम्न कोड थप्नुहोस्:

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

    यो `setupCamera` फंक्शनले SPI चिप चयन पिन (`PIN_SPI_SS`) लाई उच्च रूपमा कन्फिगर गरेर सुरु गर्छ, जसले Wio Terminal लाई SPI कन्ट्रोलर बनाउँछ। त्यसपछि यो I2C र SPI बसहरू सुरु गर्छ। अन्तमा, यो क्यामेरा क्लासलाई इनिसियलाइज गर्छ, जसले क्यामेरा सेन्सर सेटिङहरू कन्फिगर गर्छ र सबै कुरा सही रूपमा जडान भएको सुनिश्चित गर्छ।

1. `setup` फंक्शनको अन्त्यमा यो फंक्शनलाई कल गर्नुहोस्:

    ```cpp
    setupCamera();
    ```

1. यो कोड निर्माण र अपलोड गर्नुहोस्, र सिरियल मनिटरबाट आउटपुट जाँच गर्नुहोस्। यदि तपाईंले `Error setting up the camera!` देख्नुभयो भने, तारहरू सही पिनहरूमा जडान भएको सुनिश्चित गर्न जाँच गर्नुहोस्, र सबै जम्पर तारहरू सही रूपमा जडान भएको सुनिश्चित गर्नुहोस्।

## तस्बिर खिच्नुहोस्

अब Wio Terminal लाई बटन थिच्दा तस्बिर खिच्न प्रोग्राम गर्न सकिन्छ।

### कार्य - तस्बिर खिच्नुहोस्

1. माइक्रोकन्ट्रोलरहरूले तपाईंको कोड निरन्तर चलाउँछन्, त्यसैले तस्बिर खिच्ने जस्तो कार्य ट्रिगर गर्न सेन्सरको प्रतिक्रिया आवश्यक पर्छ। Wio Terminal सँग बटनहरू छन्, त्यसैले क्यामेरालाई यी बटनहरूमध्ये एकले ट्रिगर गर्न सकिन्छ। `setup` फंक्शनको अन्त्यमा निम्न कोड थप्नुहोस्:

    ![पावर स्विच नजिकको C बटन](../../../../../translated_images/ne/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    `INPUT_PULLUP` मोडले इनपुटलाई उल्टो बनाउँछ। उदाहरणका लागि, सामान्यतया बटनले थिचिएको छैन भने कम सिग्नल पठाउँछ, र थिचिएको छ भने उच्च सिग्नल पठाउँछ। `INPUT_PULLUP` मा सेट गर्दा, बटनले थिचिएको छैन भने उच्च सिग्नल पठाउँछ, र थिचिएको छ भने कम सिग्नल पठाउँछ।

1. बटन थिच्दा प्रतिक्रिया दिन खाली फंक्शन `loop` फंक्शनभन्दा अघि थप्नुहोस्:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. `loop` फंक्शनमा बटन थिच्दा यो फंक्शन कल गर्नुहोस्:

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

    यो कोडले बटन थिचिएको छ कि छैन जाँच्छ। यदि थिचिएको छ भने, `buttonPressed` फंक्शन कल हुन्छ, र लूप २ सेकेन्डको लागि रोक्छ। यो लामो प्रेसलाई दुई पटक दर्ता हुनबाट रोक्नको लागि हो।

    > 💁 Wio Terminal मा बटन `INPUT_PULLUP` मा सेट गरिएको छ, त्यसैले थिचिएको छैन भने उच्च सिग्नल पठाउँछ, र थिचिएको छ भने कम सिग्नल पठाउँछ।

1. `buttonPressed` फंक्शनमा निम्न कोड थप्नुहोस्:

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

    यो कोडले `startCapture` कल गरेर क्यामेरा क्याप्चर सुरु गर्छ। क्यामेरा हार्डवेयरले तपाईंले अनुरोध गर्दा डाटा फर्काउँदैन, यसको सट्टा तपाईंले क्याप्चर सुरु गर्न निर्देशन दिनुपर्छ, र क्यामेरा पृष्ठभूमिमा काम गरेर तस्बिर खिच्छ, यसलाई JPEG मा रूपान्तरण गर्छ, र क्यामेराको स्थानीय बफरमा भण्डारण गर्छ। `captureReady` कलले तस्बिर क्याप्चर समाप्त भएको छ कि छैन जाँच्छ।

    क्याप्चर समाप्त भएपछि, `readImageToBuffer` कलले क्यामेराको बफरबाट स्थानीय बफर (बाइटहरूको एरे) मा तस्बिर डाटा प्रतिलिपि गर्छ। बफरको लम्बाइ त्यसपछि सिरियल मनिटरमा पठाइन्छ।

1. यो कोड निर्माण र अपलोड गर्नुहोस्, र सिरियल मनिटरमा आउटपुट जाँच गर्नुहोस्। हरेक पटक तपाईंले C बटन थिच्दा, तस्बिर खिचिनेछ र तस्बिरको आकार सिरियल मनिटरमा देखिनेछ।

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    फरक तस्बिरहरूको फरक आकार हुनेछ। तिनीहरू JPEG रूपमा कम्प्रेस गरिएका छन्, र निश्चित रिजोल्युसनको JPEG फाइलको आकार तस्बिरमा के छ भन्नेमा निर्भर गर्दछ।

> 💁 तपाईं यो कोड [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal) फोल्डरमा फेला पार्न सक्नुहुन्छ।

😀 तपाईंले Wio Terminal प्रयोग गरेर सफलतापूर्वक तस्बिर खिच्नुभयो।

## वैकल्पिक - क्यामेरा तस्बिरहरू SD कार्ड प्रयोग गरेर प्रमाणित गर्नुहोस्

क्यामेराले खिचेका तस्बिरहरू हेर्नको सबैभन्दा सजिलो तरिका भनेको तिनीहरूलाई Wio Terminal मा SD कार्डमा लेख्नु र त्यसपछि आफ्नो कम्प्युटरमा हेर्नु हो। यदि तपाईंसँग अतिरिक्त माइक्रोSD कार्ड र आफ्नो कम्प्युटरमा माइक्रोSD कार्ड सकेट वा एडाप्टर छ भने यो चरण गर्नुहोस्।

Wio Terminal ले 16GB सम्मका माइक्रोSD कार्डहरू मात्र समर्थन गर्दछ। यदि तपाईंसँग ठूलो SD कार्ड छ भने यो काम गर्नेछैन।

### कार्य - SD कार्ड प्रयोग गरेर क्यामेरा तस्बिरहरू प्रमाणित गर्नुहोस्

1. आफ्नो कम्प्युटरमा सम्बन्धित एप्लिकेसनहरू (macOS मा Disk Utility, Windows मा File Explorer, वा Linux मा कमाण्ड लाइन उपकरणहरू) प्रयोग गरेर माइक्रोSD कार्डलाई FAT32 वा exFAT मा फर्म्याट गर्नुहोस्।

1. माइक्रोSD कार्डलाई पावर स्विचको ठीक तल रहेको सकेटमा राख्नुहोस्। यो क्लिक गरेर ठाउँमा रहन्छ भन्ने सुनिश्चित गर्नका लागि यसलाई पूर्ण रूपमा भित्र धकेल्नुहोस्। तपाईंलाई यसलाई धकेल्न नङ वा पातलो उपकरणको आवश्यकता पर्न सक्छ।

1. `main.cpp` फाइलको शीर्षमा निम्न `include` कथनहरू थप्नुहोस्:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. `setup` फंक्शनभन्दा अघि निम्न फंक्शन थप्नुहोस्:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    यसले SPI बस प्रयोग गरेर SD कार्डलाई कन्फिगर गर्छ।

1. `setup` फंक्शनबाट यसलाई कल गर्नुहोस्:

    ```cpp
    setupSDCard();
    ```

1. `buttonPressed` फंक्शनभन्दा माथि निम्न कोड थप्नुहोस्:

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

    यसले फाइल गणनाको लागि ग्लोबल भेरिएबल परिभाषित गर्छ। यो तस्बिर फाइल नामहरूको लागि प्रयोग गरिन्छ ताकि धेरै तस्बिरहरू क्रमिक फाइल नामहरूसँग खिच्न सकिन्छ - `1.jpg`, `2.jpg` आदि।

    त्यसपछि `saveToSDCard` फंक्शन परिभाषित गर्छ, जसले बफरको बाइट डाटा र बफरको लम्बाइ लिन्छ। फाइल गणनाको प्रयोग गरेर फाइल नाम सिर्जना गरिन्छ, र अर्को फाइलको लागि फाइल गणना बढाइन्छ। बफरबाट बाइनरी डाटा फाइलमा लेखिन्छ।

1. `buttonPressed` फंक्शनबाट `saveToSDCard` फंक्शनलाई कल गर्नुहोस्। यो कल बफर मेटाउनु अघि हुनुपर्छ:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. यो कोड निर्माण र अपलोड गर्नुहोस्, र सिरियल मनिटरमा आउटपुट जाँच गर्नुहोस्। हरेक पटक तपाईंले C बटन थिच्दा, तस्बिर खिचिनेछ र SD कार्डमा बचत हुनेछ।

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

1. माइक्रोSD कार्डलाई पावर अफ गर्नुहोस् र यसलाई हल्का धकेल्दै र छोडेर बाहिर निकाल्नुहोस्। यसले बाहिर निस्कनेछ। तपाईंलाई यसलाई निकाल्न पातलो उपकरणको आवश्यकता पर्न सक्छ। माइक्रोSD कार्डलाई आफ्नो कम्प्युटरमा प्लग गरेर तस्बिरहरू हेर्नुहोस्।

    ![ArduCam प्रयोग गरेर खिचिएको केरा](../../../../../translated_images/ne/banana-arducam.be1b32d4267a8194.webp)
💁 क्यामेराको सेतो सन्तुलन समायोजन गर्न केही तस्वीरहरू लाग्न सक्छ। तपाईंले यो समायोजन तस्वीरहरूको रंगको आधारमा देख्न सक्नुहुन्छ, पहिलो केही तस्वीरहरू रंगमा फरक देखिन सक्छ। तपाईंले सधैं यसलाई समायोजन गर्न कोड परिवर्तन गरेर `setup` फङ्सनमा केही तस्वीरहरू कैद गर्न सक्नुहुन्छ जुन बेवास्ता गरिन्छ।


---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।