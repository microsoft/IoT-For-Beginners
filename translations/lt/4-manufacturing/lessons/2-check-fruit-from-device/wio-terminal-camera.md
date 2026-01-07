<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-28T19:11:52+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "lt"
}
-->
# Užfiksuokite vaizdą - Wio Terminal

Šioje pamokos dalyje pridėsite kamerą prie savo Wio Terminal ir užfiksuosite vaizdus.

## Aparatinė įranga

Wio Terminal reikia kameros.

Naudojama kamera yra [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Tai 2 megapikselių kamera, pagrįsta OV2640 vaizdo jutikliu. Ji perduoda duomenis per SPI sąsają, kad užfiksuotų vaizdus, ir naudoja I2C, kad sukonfigūruotų jutiklį.

## Prijunkite kamerą

ArduCam neturi Grove jungties, vietoj to ji jungiasi prie SPI ir I2C magistralių per GPIO kaiščius ant Wio Terminal.

### Užduotis - prijunkite kamerą

Prijunkite kamerą.

![ArduCam jutiklis](../../../../../translated_images/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.lt.png)

1. ArduCam apačioje esantys kaiščiai turi būti prijungti prie GPIO kaiščių ant Wio Terminal. Kad būtų lengviau rasti tinkamus kaiščius, uždėkite GPIO kaiščių lipduką, kuris yra komplekte su Wio Terminal:

    ![Wio Terminal su GPIO kaiščių lipduku](../../../../../translated_images/wio-terminal-pin-sticker.b90b1535937b84bd.lt.png)

1. Naudodami jungiamuosius laidus, atlikite šiuos sujungimus:

    | ArduCAM kaištis | Wio Terminal kaištis | Aprašymas                              |
    | --------------- | -------------------- | -------------------------------------- |
    | CS              | 24 (SPI_CS)          | SPI Chip Select                        |
    | MOSI            | 19 (SPI_MOSI)        | SPI Valdiklio išvestis, periferijos įvestis |
    | MISO            | 21 (SPI_MISO)        | SPI Valdiklio įvestis, periferijos išvestis |
    | SCK             | 23 (SPI_SCLK)        | SPI Serijinis laikrodis                |
    | GND             | 6 (GND)              | Žemė - 0V                              |
    | VCC             | 4 (5V)               | 5V maitinimo šaltinis                  |
    | SDA             | 3 (I2C1_SDA)         | I2C Serijiniai duomenys                |
    | SCL             | 5 (I2C1_SCL)         | I2C Serijinis laikrodis                |

    ![Wio Terminal prijungtas prie ArduCam su jungiamaisiais laidais](../../../../../translated_images/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.lt.png)

    GND ir VCC jungtys suteikia 5V maitinimą ArduCam. Ji veikia 5V, skirtingai nei Grove jutikliai, kurie veikia 3V. Šis maitinimas gaunamas tiesiai iš USB-C jungties, kuri maitina įrenginį.

    > 💁 SPI jungčiai ArduCam ir Wio Terminal kaiščių pavadinimai, naudojami kode, vis dar naudoja seną pavadinimų konvenciją. Šios pamokos instrukcijos naudos naują pavadinimų konvenciją, išskyrus atvejus, kai kaiščių pavadinimai naudojami kode.

1. Dabar galite prijungti Wio Terminal prie savo kompiuterio.

## Užprogramuokite įrenginį, kad jis prisijungtų prie kameros

Dabar Wio Terminal galima užprogramuoti naudoti prijungtą ArduCAM kamerą.

### Užduotis - užprogramuokite įrenginį, kad jis prisijungtų prie kameros

1. Sukurkite naują Wio Terminal projektą naudodami PlatformIO. Pavadinkite šį projektą `fruit-quality-detector`. Pridėkite kodą `setup` funkcijoje, kad sukonfigūruotumėte serijinį prievadą.

1. Pridėkite kodą, kad prisijungtumėte prie WiFi, su savo WiFi prisijungimo duomenimis faile, pavadintame `config.h`. Nepamirškite pridėti reikalingų bibliotekų į `platformio.ini` failą.

1. ArduCam biblioteka nėra prieinama kaip Arduino biblioteka, kurią galima įdiegti iš `platformio.ini` failo. Vietoj to ją reikės įdiegti iš šaltinio jų GitHub puslapyje. Ją galite gauti:

    * Klonuodami repozitoriją iš [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Apsilankę repozitorijoje GitHub adresu [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) ir atsisiųsdami kodą kaip zip failą iš **Code** mygtuko

1. Jums reikės tik `ArduCAM` aplanko iš šio kodo. Nukopijuokite visą aplanką į `lib` aplanką savo projekte.

    > ⚠️ Visas aplankas turi būti nukopijuotas, kad kodas būtų `lib/ArduCam`. Nekopijuokite tik `ArduCam` aplanko turinio į `lib` aplanką, nukopijuokite visą aplanką.

1. ArduCam bibliotekos kodas veikia su kelių tipų kameromis. Kameros tipas, kurį norite naudoti, yra konfigūruojamas naudojant kompiliatoriaus vėliavėles - tai sumažina sukurtos bibliotekos dydį, pašalinant kodą kameroms, kurių nenaudojate. Norėdami sukonfigūruoti biblioteką OV2640 kamerai, pridėkite šiuos nustatymus į `platformio.ini` failo pabaigą:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Tai nustato 2 kompiliatoriaus vėliavėles:

      * `ARDUCAM_SHIELD_V2`, kad biblioteka žinotų, jog kamera yra ant Arduino plokštės, vadinamos "shield".
      * `OV2640_CAM`, kad biblioteka įtrauktų tik kodą OV2640 kamerai.

1. Pridėkite antraštės failą į `src` aplanką, pavadintą `camera.h`. Jame bus kodas, skirtas bendrauti su kamera. Pridėkite šį kodą į šį failą:

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

    Tai yra žemo lygio kodas, kuris konfigūruoja kamerą naudojant ArduCam bibliotekas ir ištraukia vaizdus, kai to reikia, naudojant SPI magistralę. Šis kodas yra labai specifinis ArduCam, todėl šiuo metu nereikia jaudintis, kaip jis veikia.

1. `main.cpp` faile pridėkite šį kodą po kitais `include` teiginiais, kad įtrauktumėte naują failą ir sukurtumėte kameros klasės egzempliorių:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Tai sukuria `Camera`, išsaugančią vaizdus kaip JPEG failus 640x480 raiška. Nors palaikomos didesnės raiškos (iki 3280x2464), vaizdų klasifikatorius veikia su daug mažesniais vaizdais (227x227), todėl nėra reikalo fiksuoti ir siųsti didesnių vaizdų.

1. Pridėkite šį kodą žemiau, kad apibrėžtumėte funkciją, skirtą kameros nustatymui:

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

    Ši `setupCamera` funkcija pradeda konfigūruoti SPI chip select kaištį (`PIN_SPI_SS`) kaip aukštą, padarydama Wio Terminal SPI valdikliu. Tada ji pradeda I2C ir SPI magistrales. Galiausiai ji inicializuoja kameros klasę, kuri konfigūruoja kameros jutiklio nustatymus ir užtikrina, kad viskas būtų tinkamai prijungta.

1. Iškvieskite šią funkciją `setup` funkcijos pabaigoje:

    ```cpp
    setupCamera();
    ```

1. Sukurkite ir įkelkite šį kodą, ir patikrinkite išvestį serijiniame monitoriuje. Jei matote `Error setting up the camera!`, patikrinkite laidus, kad įsitikintumėte, jog visi kabeliai jungia tinkamus ArduCam kaiščius su tinkamais GPIO kaiščiais ant Wio Terminal, ir visi jungiamieji laidai yra tinkamai prijungti.

## Užfiksuokite vaizdą

Dabar Wio Terminal galima užprogramuoti, kad užfiksuotų vaizdą, kai paspaudžiamas mygtukas.

### Užduotis - užfiksuokite vaizdą

1. Mikrovaldikliai vykdo jūsų kodą nuolat, todėl nėra lengva inicijuoti veiksmą, pvz., fotografavimą, nereaguojant į jutiklį. Wio Terminal turi mygtukus, todėl kamerą galima nustatyti taip, kad ją inicijuotų vienas iš mygtukų. Pridėkite šį kodą `setup` funkcijos pabaigoje, kad sukonfigūruotumėte C mygtuką (vieną iš trijų mygtukų viršuje, esantį arčiausiai maitinimo jungiklio).

    ![C mygtukas viršuje, arčiausiai maitinimo jungiklio](../../../../../translated_images/wio-terminal-c-button.73df3cb1c1445ea0.lt.png)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    `INPUT_PULLUP` režimas iš esmės apverčia įvestį. Pavyzdžiui, paprastai mygtukas siųstų žemą signalą, kai nėra paspaustas, ir aukštą signalą, kai paspaustas. Kai nustatytas `INPUT_PULLUP`, jis siunčia aukštą signalą, kai nėra paspaustas, ir žemą signalą, kai paspaustas.

1. Pridėkite tuščią funkciją, kad reaguotų į mygtuko paspaudimą prieš `loop` funkciją:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Iškvieskite šią funkciją `loop` metode, kai mygtukas paspaustas:

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

    Šis kodas patikrina, ar mygtukas paspaustas. Jei jis paspaustas, iškviečiama `buttonPressed` funkcija, o ciklas užlaikomas 2 sekundėms. Tai leidžia mygtukui būti atleistas, kad ilgas paspaudimas nebūtų užregistruotas du kartus.

    > 💁 Wio Terminal mygtukas nustatytas kaip `INPUT_PULLUP`, todėl siunčia aukštą signalą, kai nėra paspaustas, ir žemą signalą, kai paspaustas.

1. Pridėkite šį kodą į `buttonPressed` funkciją:

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

    Šis kodas pradeda kameros fiksavimą, iškviesdamas `startCapture`. Kameros aparatinė įranga neveikia grąžindama duomenis, kai jų prašoma, vietoj to siunčiate instrukciją pradėti fiksavimą, ir kamera fone dirba, kad užfiksuotų vaizdą, konvertuotų jį į JPEG ir išsaugotų vietiniame buferyje pačioje kameroje. `captureReady` skambutis tada patikrina, ar vaizdo fiksavimas baigtas.

    Kai fiksavimas baigtas, vaizdo duomenys kopijuojami iš buferio kameroje į vietinį buferį (baitų masyvą) naudojant `readImageToBuffer` skambutį. Buferio ilgis tada siunčiamas į serijinį monitorių.

1. Sukurkite ir įkelkite šį kodą, ir patikrinkite išvestį serijiniame monitoriuje. Kiekvieną kartą paspaudus C mygtuką, bus užfiksuotas vaizdas, ir serijiniame monitoriuje bus matomas vaizdo dydis.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Skirtingi vaizdai turės skirtingus dydžius. Jie suspausti kaip JPEG failai, o JPEG failo dydis tam tikrai raiškai priklauso nuo to, kas yra vaizde.

> 💁 Šį kodą galite rasti [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal) aplanke.

😀 Jūs sėkmingai užfiksavote vaizdus su savo Wio Terminal.

## Pasirinktinai - patikrinkite kameros vaizdus naudodami SD kortelę

Lengviausias būdas pamatyti vaizdus, kuriuos užfiksavo kamera, yra įrašyti juos į SD kortelę Wio Terminal ir tada peržiūrėti juos savo kompiuteryje. Atlikite šį žingsnį, jei turite atsarginę microSD kortelę ir microSD kortelės lizdą savo kompiuteryje arba adapterį.

Wio Terminal palaiko tik microSD korteles iki 16GB dydžio. Jei turite didesnę SD kortelę, ji neveiks.

### Užduotis - patikrinkite kameros vaizdus naudodami SD kortelę

1. Formatuokite microSD kortelę kaip FAT32 arba exFAT naudodami atitinkamas programas savo kompiuteryje (Disk Utility macOS, File Explorer Windows arba komandinės eilutės įrankius Linux).

1. Įdėkite microSD kortelę į lizdą tiesiai po maitinimo jungikliu. Įsitikinkite, kad ji visiškai įdėta, kol spragtelės ir liks vietoje, gali tekti ją stumti nagais arba plonu įrankiu.

1. Pridėkite šiuos `include` teiginius `main.cpp` failo viršuje:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Pridėkite šią funkciją prieš `setup` funkciją:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Tai konfigūruoja SD kortelę naudojant SPI magistralę.

1. Iškvieskite tai iš `setup` funkcijos:

    ```cpp
    setupSDCard();
    ```

1. Pridėkite šį kodą virš `buttonPressed` funkcijos:

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

    Tai apibrėžia globalų kintamąjį failų skaičiui. Jis naudojamas vaizdo failų pavadinimams, kad būtų galima užfiksuoti kelis vaizdus su didėjančiais failų pavadinimais - `1.jpg`, `2.jpg` ir t. t.

    Tada apibrėžiama `saveToSDCard` funkcija, kuri priima baitų duomenų buferį ir buferio ilgį. Failo pavadinimas sukuriamas naudojant failų skaičių, o failų skaičius padidinamas, pasiruošiant kitam failui. Tada binariniai duomenys iš buferio įrašomi į failą.

1. Iškvieskite `saveToSDCard` funkciją iš `buttonPressed` funkcijos. Skambutis turėtų būti **prieš** buferio ištrynimą:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Sukurkite ir įkelkite šį kodą, ir patikrinkite išvestį serijiniame monitoriuje. Kiekvieną kartą paspaudus C mygtuką, bus užfiksuotas vaizdas ir išsaugotas SD kortelėje.

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

1. Išjunkite microSD kortelę ir išimkite ją, šiek tiek paspausdami ir atleisdami, ir ji iššoks. Gali tekti naudoti ploną įrankį, kad tai padarytumėte. Įdėkite microSD kortelę į savo kompiuterį, kad peržiūrėtumėte vaizdus.

    ![Banano nuotrauka, užfiksuota naudojant ArduCam](../../../../../translated_images/banana-arducam.be1b32d4267a8194b0fd042362e56faa431da9cd4af172051b37243ea9be0256.lt.jpg)
💁 Gali prireikti kelių vaizdų, kol fotoaparato baltos spalvos balansas prisitaikys. Tai pastebėsite pagal užfiksuotų vaizdų spalvą, pirmieji keli gali atrodyti netinkamos spalvos. Visada galite tai apeiti pakeisdami kodą, kad užfiksuotumėte kelis vaizdus, kurie ignoruojami funkcijoje `setup`.


---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.