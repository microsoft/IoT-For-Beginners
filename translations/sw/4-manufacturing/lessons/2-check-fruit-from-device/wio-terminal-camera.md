<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-27T20:56:56+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "sw"
}
-->
# Kupiga Picha - Wio Terminal

Katika sehemu hii ya somo, utaongeza kamera kwenye Wio Terminal yako, na kupiga picha kutoka kwayo.

## Vifaa

Wio Terminal inahitaji kamera.

Kamera utakayotumia ni [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Hii ni kamera ya megapikseli 2 inayotumia sensa ya picha ya OV2640. Inawasiliana kupitia kiolesura cha SPI ili kupiga picha, na hutumia I2C kusanidi sensa.

## Unganisha Kamera

ArduCam haina soketi ya Grove, badala yake inaunganishwa kwenye mabasi ya SPI na I2C kupitia pini za GPIO kwenye Wio Terminal.

### Kazi - unganisha kamera

Unganisha kamera.

![Kihisi cha ArduCam](../../../../../translated_images/sw/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.png)

1. Pini kwenye msingi wa ArduCam zinahitaji kuunganishwa kwenye pini za GPIO za Wio Terminal. Ili iwe rahisi kupata pini sahihi, weka stika ya pini ya GPIO inayokuja na Wio Terminal kuzunguka pini:

    ![Wio Terminal ikiwa na stika ya pini ya GPIO](../../../../../translated_images/sw/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. Kwa kutumia nyaya za kuruka, fanya miunganisho ifuatayo:

    | Pini ya ArduCAM | Pini ya Wio Terminal | Maelezo                                |
    | --------------- | -------------------- | -------------------------------------- |
    | CS              | 24 (SPI_CS)         | SPI Chip Select                        |
    | MOSI            | 19 (SPI_MOSI)       | SPI Controller Output, Peripheral Input |
    | MISO            | 21 (SPI_MISO)       | SPI Controller Input, Peripheral Output |
    | SCK             | 23 (SPI_SCLK)       | SPI Serial Clock                       |
    | GND             | 6 (GND)             | Ardhi - 0V                             |
    | VCC             | 4 (5V)              | Ugavi wa umeme wa 5V                   |
    | SDA             | 3 (I2C1_SDA)        | I2C Data ya Serial                     |
    | SCL             | 5 (I2C1_SCL)        | I2C Saa ya Serial                      |

    ![Wio Terminal ikiwa imeunganishwa na ArduCam kwa nyaya za kuruka](../../../../../translated_images/sw/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.png)

    Muunganisho wa GND na VCC hutoa umeme wa 5V kwa ArduCam. Inafanya kazi kwa 5V, tofauti na vihisi vya Grove vinavyofanya kazi kwa 3V. Umeme huu unatoka moja kwa moja kwenye muunganisho wa USB-C unaotoa nguvu kwa kifaa.

    > 💁 Kwa muunganisho wa SPI, lebo za pini kwenye ArduCam na majina ya pini za Wio Terminal yanayotumika kwenye msimbo bado yanatumia mkataba wa zamani wa majina. Maelekezo katika somo hili yatatumia mkataba mpya wa majina, isipokuwa pale majina ya pini yanapotumika kwenye msimbo.

1. Sasa unaweza kuunganisha Wio Terminal kwenye kompyuta yako.

## Programu kifaa kuunganishwa na kamera

Wio Terminal sasa inaweza kupangwa kutumia kamera ya ArduCAM iliyounganishwa.

### Kazi - panga kifaa kuunganishwa na kamera

1. Unda mradi mpya wa Wio Terminal ukitumia PlatformIO. Uite mradi huu `fruit-quality-detector`. Ongeza msimbo kwenye kazi ya `setup` ili kusanidi bandari ya serial.

1. Ongeza msimbo wa kuunganisha kwenye WiFi, ukiweka maelezo ya WiFi yako kwenye faili inayoitwa `config.h`. Usisahau kuongeza maktaba zinazohitajika kwenye faili ya `platformio.ini`.

1. Maktaba ya ArduCam haipatikani kama maktaba ya Arduino inayoweza kusakinishwa kutoka faili ya `platformio.ini`. Badala yake, itahitaji kusakinishwa kutoka chanzo kwenye ukurasa wao wa GitHub. Unaweza kuipata kwa:

    * Kuiga repo kutoka [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Kwenda kwenye repo kwenye GitHub kwa [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) na kupakua msimbo kama zip kutoka kitufe cha **Code**

1. Unahitaji tu folda ya `ArduCAM` kutoka kwenye msimbo huu. Nakili folda nzima kwenye folda ya `lib` kwenye mradi wako.

    > ⚠️ Lazima unakili folda nzima, ili msimbo uwe kwenye `lib/ArduCam`. Usinakili tu yaliyomo kwenye folda ya `ArduCam` kwenye folda ya `lib`, nakili folda nzima.

1. Msimbo wa maktaba ya ArduCam unafanya kazi kwa aina nyingi za kamera. Aina ya kamera unayotaka kutumia inasanidiwa kwa kutumia bendera za mkusanyaji - hii hufanya maktaba iliyojengwa kuwa ndogo iwezekanavyo kwa kuondoa msimbo wa kamera ambazo hutumii. Ili kusanidi maktaba kwa kamera ya OV2640, ongeza yafuatayo mwishoni mwa faili ya `platformio.ini`:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Hii inaweka bendera 2 za mkusanyaji:

      * `ARDUCAM_SHIELD_V2` kuambia maktaba kwamba kamera iko kwenye bodi ya Arduino, inayojulikana kama shield.
      * `OV2640_CAM` kuambia maktaba kujumuisha tu msimbo wa kamera ya OV2640.

1. Ongeza faili ya kichwa kwenye folda ya `src` inayoitwa `camera.h`. Hii itakuwa na msimbo wa kuwasiliana na kamera. Ongeza msimbo ufuatao kwenye faili hii:

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

    Huu ni msimbo wa kiwango cha chini unaosanidi kamera kwa kutumia maktaba za ArduCam, na kutoa picha inapohitajika kwa kutumia basi la SPI. Msimbo huu ni maalum sana kwa ArduCam, kwa hivyo huhitaji kuwa na wasiwasi kuhusu jinsi unavyofanya kazi kwa sasa.

1. Katika `main.cpp`, ongeza msimbo ufuatao chini ya taarifa zingine za `include` ili kujumuisha faili hii mpya na kuunda mfano wa darasa la kamera:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Hii inaunda `Camera` inayohifadhi picha kama JPEGs kwa azimio la 640 kwa 480. Ingawa azimio la juu zaidi linaungwa mkono (hadi 3280x2464), kigeuzi cha picha hufanya kazi kwenye picha ndogo zaidi (227x227) kwa hivyo hakuna haja ya kupiga na kutuma picha kubwa zaidi.

1. Ongeza msimbo ufuatao chini ya hii ili kufafanua kazi ya kusanidi kamera:

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

    Kazi hii ya `setupCamera` huanza kwa kusanidi pini ya SPI chip select (`PIN_SPI_SS`) kama ya juu, na kufanya Wio Terminal kuwa mdhibiti wa SPI. Kisha huanzisha mabasi ya I2C na SPI. Hatimaye, inasanidi darasa la kamera ambalo husanidi mipangilio ya sensa ya kamera na kuhakikisha kila kitu kimeunganishwa kwa usahihi.

1. Ita kazi hii mwishoni mwa kazi ya `setup`:

    ```cpp
    setupCamera();
    ```

1. Jenga na pakia msimbo huu, na angalia matokeo kutoka kwa mfuatiliaji wa serial. Ikiwa utaona `Error setting up the camera!` basi angalia wiring kuhakikisha nyaya zote zinaunganisha pini sahihi kwenye ArduCam na pini sahihi za GPIO kwenye Wio Terminal, na nyaya zote za kuruka zimekaa vizuri.

## Piga picha

Wio Terminal sasa inaweza kupangwa kupiga picha wakati kitufe kinapobonyezwa.

### Kazi - piga picha

1. Microcontrollers huendesha msimbo wako mfululizo, kwa hivyo si rahisi kuanzisha kitu kama kupiga picha bila kujibu kihisi. Wio Terminal ina vitufe, kwa hivyo kamera inaweza kusanidiwa kuanzishwa na moja ya vitufe. Ongeza msimbo ufuatao mwishoni mwa kazi ya `setup` ili kusanidi kitufe cha C (kimoja kati ya vitufe vitatu juu, kilicho karibu zaidi na swichi ya nguvu).

    ![Kitufe cha C juu karibu na swichi ya nguvu](../../../../../translated_images/sw/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    Hali ya `INPUT_PULLUP` kimsingi inageuza pembejeo. Kwa mfano, kawaida kitufe kingetuma ishara ya chini wakati hakijabonyezwa, na ishara ya juu wakati kimebonyezwa. Kikiwa kimewekwa kwenye `INPUT_PULLUP`, hutuma ishara ya juu wakati hakijabonyezwa, na ishara ya chini wakati kimebonyezwa.

1. Ongeza kazi tupu ya kujibu bonyeza kitufe kabla ya kazi ya `loop`:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Ita kazi hii kwenye njia ya `loop` wakati kitufe kinapobonyezwa:

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

    Hii inakagua kuona ikiwa kitufe kimebonyezwa. Ikiwa kimebonyezwa, kazi ya `buttonPressed` inaitwa, na mzunguko unasubiri kwa sekunde 2. Hii ni kuruhusu muda wa kitufe kuachiliwa ili bonyeza kwa muda mrefu usihesabiwe mara mbili.

    > 💁 Kitufe kwenye Wio Terminal kimewekwa kwenye `INPUT_PULLUP`, kwa hivyo hutuma ishara ya juu wakati hakijabonyezwa, na ishara ya chini wakati kimebonyezwa.

1. Ongeza msimbo ufuatao kwenye kazi ya `buttonPressed`:

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

    Msimbo huu huanza upigaji picha kwa kuita `startCapture`. Vifaa vya kamera havifanyi kazi kwa kurudisha data unapoiomba, badala yake unatuma maagizo ya kuanza kupiga, na kamera itafanya kazi kwa nyuma kupiga picha, kuibadilisha kuwa JPEG, na kuihifadhi kwenye buffer ya ndani kwenye kamera yenyewe. Simu ya `captureReady` kisha hukagua kuona ikiwa upigaji picha umekamilika.

    Mara upigaji picha unapokamilika, data ya picha inanakiliwa kutoka kwenye buffer kwenye kamera hadi kwenye buffer ya ndani (array ya baiti) kwa simu ya `readImageToBuffer`. Urefu wa buffer kisha hutumwa kwa mfuatiliaji wa serial.

1. Jenga na pakia msimbo huu, na angalia matokeo kwenye mfuatiliaji wa serial. Kila wakati unapobonyeza kitufe cha C, picha itapigwa na utaona ukubwa wa picha ukitumwa kwa mfuatiliaji wa serial.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Picha tofauti zitakuwa na ukubwa tofauti. Zimebanwa kama JPEGs na ukubwa wa faili ya JPEG kwa azimio fulani hutegemea kile kilicho kwenye picha.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Umefanikiwa kupiga picha kwa kutumia Wio Terminal yako.

## Hiari - thibitisha picha za kamera kwa kutumia kadi ya SD

Njia rahisi ya kuona picha zilizopigwa na kamera ni kuziandika kwenye kadi ya SD kwenye Wio Terminal na kisha kuziona kwenye kompyuta yako. Fanya hatua hii ikiwa una kadi ndogo ya SD na soketi ya kadi ya SD kwenye kompyuta yako, au adapta.

Wio Terminal inasaidia tu kadi ndogo za SD zenye ukubwa wa hadi 16GB. Ikiwa una kadi ya SD kubwa zaidi basi haitafanya kazi.

### Kazi - thibitisha picha za kamera kwa kutumia kadi ya SD

1. Fomati kadi ndogo ya SD kama FAT32 au exFAT kwa kutumia programu husika kwenye kompyuta yako (Disk Utility kwenye macOS, File Explorer kwenye Windows, au kwa kutumia zana za mstari wa amri kwenye Linux).

1. Ingiza kadi ndogo ya SD kwenye soketi iliyo chini ya swichi ya nguvu. Hakikisha imeingia kabisa hadi igonge na ibaki mahali pake, unaweza kuhitaji kuisukuma kwa kutumia kucha au chombo chembamba.

1. Ongeza taarifa zifuatazo za kujumuisha juu ya faili ya `main.cpp`:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Ongeza kazi ifuatayo kabla ya kazi ya `setup`:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Hii inasanidi kadi ya SD kwa kutumia basi la SPI.

1. Ita hii kutoka kwenye kazi ya `setup`:

    ```cpp
    setupSDCard();
    ```

1. Ongeza msimbo ufuatao juu ya kazi ya `buttonPressed`:

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

    Hii inafafanua kigezo cha kimataifa kwa hesabu ya faili. Hii inatumika kwa majina ya faili ya picha ili picha nyingi ziweze kupigwa na majina ya faili yanayoongezeka - `1.jpg`, `2.jpg` na kadhalika.

    Kisha inafafanua `saveToSDCard` inayochukua buffer ya data ya baiti, na urefu wa buffer. Jina la faili linaundwa kwa kutumia hesabu ya faili, na hesabu ya faili inaongezeka tayari kwa faili inayofuata. Data ya binary kutoka kwenye buffer kisha inaandikwa kwenye faili.

1. Ita kazi ya `saveToSDCard` kutoka kwenye kazi ya `buttonPressed`. Simu inapaswa kuwa **kabla** ya buffer kufutwa:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Jenga na pakia msimbo huu, na angalia matokeo kwenye mfuatiliaji wa serial. Kila wakati unapobonyeza kitufe cha C, picha itapigwa na kuhifadhiwa kwenye kadi ya SD.

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

1. Zima kadi ndogo ya SD na uitoe kwa kuisukuma kidogo na kuachilia, na itatoka. Unaweza kuhitaji kutumia chombo chembamba kufanya hivyo. Unganisha kadi ndogo ya SD kwenye kompyuta yako ili kuona picha.

    ![Picha ya ndizi iliyopigwa kwa kutumia ArduCam](../../../../../translated_images/sw/banana-arducam.be1b32d4267a8194b0fd042362e56faa431da9cd4af172051b37243ea9be0256.jpg)
💁 Inaweza kuchukua picha chache kwa kamera kurekebisha usawa wa rangi yake. Utatambua hili kulingana na rangi ya picha zilizopigwa, picha za kwanza chache zinaweza kuonekana kuwa na rangi isiyo sahihi. Daima unaweza kulitatua hili kwa kubadilisha msimbo ili kupiga picha chache ambazo hazizingatiwi katika kazi ya `setup`.


---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.