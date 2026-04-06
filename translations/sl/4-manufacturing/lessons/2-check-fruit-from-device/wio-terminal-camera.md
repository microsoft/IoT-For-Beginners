# Zajem slike - Wio Terminal

V tem delu lekcije boste svojemu Wio Terminalu dodali kamero in zajeli slike z njo.

## Strojna oprema

Wio Terminal potrebuje kamero.

Kamera, ki jo boste uporabili, je [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). To je 2-megapikselna kamera, ki temelji na slikovnem senzorju OV2640. Komunicira prek SPI vmesnika za zajem slik in uporablja I²C za konfiguracijo senzorja.

## Povežite kamero

ArduCam nima Grove vtičnice, ampak se povezuje na SPI in I²C vodila prek GPIO pinov na Wio Terminalu.

### Naloga - povežite kamero

Povežite kamero.

![Senzor ArduCam](../../../../../translated_images/sl/arducam.20e4e4cbb2682965.webp)

1. Pini na spodnji strani ArduCam-a morajo biti povezani z GPIO pini na Wio Terminalu. Da boste lažje našli prave pine, pritrdite nalepko z GPIO pini, ki je priložena Wio Terminalu, okoli pinov:

    ![Wio Terminal z nalepko GPIO pinov](../../../../../translated_images/sl/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. Z uporabo povezovalnih žic naredite naslednje povezave:

    | Pin ArduCAM | Pin Wio Terminal | Opis                                    |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | SPI Chip Select                         |
    | MOSI        | 19 (SPI_MOSI)    | SPI izhod krmilnika, vhod periferije    |
    | MISO        | 21 (SPI_MISO)    | SPI vhod krmilnika, izhod periferije    |
    | SCK         | 23 (SPI_SCLK)    | SPI serijska ura                        |
    | GND         | 6 (GND)          | Zemlja - 0V                             |
    | VCC         | 4 (5V)           | 5V napajanje                            |
    | SDA         | 3 (I2C1_SDA)     | I²C serijski podatki                    |
    | SCL         | 5 (I2C1_SCL)     | I²C serijska ura                        |

    ![Wio Terminal povezan z ArduCam prek povezovalnih žic](../../../../../translated_images/sl/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.webp)

    Povezavi GND in VCC zagotavljata 5V napajanje za ArduCam. Kamera deluje na 5V, za razliko od Grove senzorjev, ki delujejo na 3V. To napajanje prihaja neposredno iz USB-C povezave, ki napaja napravo.

    > 💁 Pri SPI povezavi oznake pinov na ArduCam in imena pinov Wio Terminala, uporabljena v kodi, še vedno uporabljajo staro poimenovanje. Navodila v tej lekciji bodo uporabljala novo poimenovanje, razen kadar so imena pinov uporabljena v kodi.

1. Zdaj lahko povežete Wio Terminal z računalnikom.

## Programirajte napravo za povezavo s kamero

Wio Terminal je zdaj pripravljen za programiranje, da uporablja priključeno kamero ArduCAM.

### Naloga - programirajte napravo za povezavo s kamero

1. Ustvarite povsem nov projekt za Wio Terminal z uporabo PlatformIO. Projekt poimenujte `fruit-quality-detector`. Dodajte kodo v funkcijo `setup`, da konfigurirate serijski port.

1. Dodajte kodo za povezavo z WiFi, z vašimi WiFi poverilnicami v datoteki `config.h`. Ne pozabite dodati potrebnih knjižnic v datoteko `platformio.ini`.

1. Knjižnica ArduCam ni na voljo kot Arduino knjižnica, ki bi jo lahko namestili iz datoteke `platformio.ini`. Namesto tega jo boste morali namestiti iz izvorne kode z njihove strani GitHub. To lahko storite na enega od naslednjih načinov:

    * Klonirajte repozitorij z [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Obiščite repozitorij na GitHubu na [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) in prenesite kodo kot zip datoteko z gumbom **Code**

1. Potrebujete samo mapo `ArduCAM` iz te kode. Kopirajte celotno mapo v mapo `lib` v vašem projektu.

    > ⚠️ Celotno mapo je treba kopirati, tako da je koda v `lib/ArduCam`. Ne kopirajte samo vsebine mape `ArduCam` v mapo `lib`, ampak kopirajte celotno mapo.

1. Koda knjižnice ArduCam deluje za več vrst kamer. Vrsta kamere, ki jo želite uporabiti, je konfigurirana z zastavicami prevajalnika - to ohranja knjižnico čim manjšo, saj odstrani kodo za kamere, ki jih ne uporabljate. Za konfiguracijo knjižnice za kamero OV2640 dodajte naslednje na konec datoteke `platformio.ini`:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    To nastavi dve zastavici prevajalnika:

      * `ARDUCAM_SHIELD_V2`, da knjižnici pove, da je kamera na Arduino plošči, znani kot ščit.
      * `OV2640_CAM`, da knjižnici pove, naj vključi samo kodo za kamero OV2640.

1. Dodajte glavno datoteko v mapo `src`, imenovano `camera.h`. Ta bo vsebovala kodo za komunikacijo s kamero. V to datoteko dodajte naslednjo kodo:

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

    To je nizkonivojska koda, ki konfigurira kamero z uporabo knjižnic ArduCam in pridobi slike, ko je to potrebno, prek SPI vodila. Ta koda je zelo specifična za ArduCam, zato vam ni treba skrbeti, kako deluje.

1. V `main.cpp` dodajte naslednjo kodo pod druge izjave `include`, da vključite to novo datoteko in ustvarite instanco razreda kamere:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    To ustvari `Camera`, ki shranjuje slike kot JPEG pri ločljivosti 640 x 480. Čeprav so podprte višje ločljivosti (do 3280x2464), klasifikator slik deluje na veliko manjših slikah (227x227), zato ni potrebe po zajemanju in pošiljanju večjih slik.

1. Dodajte naslednjo kodo pod to, da definirate funkcijo za nastavitev kamere:

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

    Funkcija `setupCamera` začne z nastavitvijo SPI pina za izbiro čipa (`PIN_SPI_SS`) kot visok, kar naredi Wio Terminal SPI krmilnik. Nato zažene I²C in SPI vodila. Na koncu inicializira razred kamere, ki konfigurira nastavitve senzorja kamere in zagotovi, da je vse pravilno povezano.

1. To funkcijo pokličite na koncu funkcije `setup`:

    ```cpp
    setupCamera();
    ```

1. Sestavite in naložite to kodo ter preverite izhod na serijskem monitorju. Če vidite `Error setting up the camera!`, preverite ožičenje, da zagotovite, da so vse žice povezane na pravilne pine na ArduCam in GPIO pine na Wio Terminalu, ter da so vse povezovalne žice pravilno nameščene.

## Zajem slike

Wio Terminal je zdaj mogoče programirati za zajem slike, ko pritisnete gumb.

### Naloga - zajem slike

1. Mikrokrmilniki izvajajo vašo kodo neprekinjeno, zato ni enostavno sprožiti nekaj, kot je zajem fotografije, brez odziva na senzor. Wio Terminal ima gumbe, zato lahko kamero nastavite tako, da jo sproži eden od gumbov. Dodajte naslednjo kodo na konec funkcije `setup`, da konfigurirate gumb C (eden od treh gumbov na vrhu, najbližji stikalu za vklop).

    ![Gumb C na vrhu, najbližji stikalu za vklop](../../../../../translated_images/sl/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    Način `INPUT_PULLUP` v bistvu obrne vhod. Na primer, običajno bi gumb pošiljal nizek signal, ko ni pritisnjen, in visok signal, ko je pritisnjen. Ko je nastavljen na `INPUT_PULLUP`, pošilja visok signal, ko ni pritisnjen, in nizek signal, ko je pritisnjen.

1. Dodajte prazno funkcijo za odziv na pritisk gumba pred funkcijo `loop`:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. To funkcijo pokličite v metodi `loop`, ko je gumb pritisnjen:

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

    Ta ključ preveri, ali je gumb pritisnjen. Če je pritisnjen, se pokliče funkcija `buttonPressed`, zanka pa se za 2 sekundi ustavi. To omogoča čas za sprostitev gumba, da se dolg pritisk ne registrira dvakrat.

    > 💁 Gumb na Wio Terminalu je nastavljen na `INPUT_PULLUP`, zato pošilja visok signal, ko ni pritisnjen, in nizek signal, ko je pritisnjen.

1. Dodajte naslednjo kodo v funkcijo `buttonPressed`:

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

    Ta koda začne zajem kamere z klicem `startCapture`. Strojna oprema kamere ne deluje tako, da vrne podatke, ko jih zahtevate, ampak pošljete ukaz za začetek zajema, kamera pa v ozadju zajame sliko, jo pretvori v JPEG in shrani v lokalni medpomnilnik na sami kameri. Klic `captureReady` nato preveri, ali je zajem slike končan.

    Ko je zajem končan, se podatki slike kopirajo iz medpomnilnika na kameri v lokalni medpomnilnik (polje bajtov) s klicem `readImageToBuffer`. Dolžina medpomnilnika se nato pošlje na serijski monitor.

1. Sestavite in naložite to kodo ter preverite izhod na serijskem monitorju. Vsakič, ko pritisnete gumb C, se zajame slika in velikost slike se pošlje na serijski monitor.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Različne slike bodo imele različne velikosti. Stisnjene so kot JPEG, velikost JPEG datoteke za določeno ločljivost pa je odvisna od vsebine slike.

> 💁 To kodo najdete v mapi [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Uspešno ste zajeli slike z vašim Wio Terminalom.

## Neobvezno - preverite slike kamere z uporabo SD kartice

Najlažji način za ogled slik, ki jih je zajela kamera, je, da jih zapišete na SD kartico v Wio Terminalu in jih nato ogledate na računalniku. Ta korak izvedite, če imate na voljo mikroSD kartico in režo za mikroSD kartico na računalniku ali adapter.

Wio Terminal podpira samo mikroSD kartice do velikosti 16 GB. Če imate večjo SD kartico, ne bo delovala.

### Naloga - preverite slike kamere z uporabo SD kartice

1. Formatirajte mikroSD kartico kot FAT32 ali exFAT z ustreznimi aplikacijami na vašem računalniku (Disk Utility na macOS, File Explorer na Windows ali z ukaznimi orodji v Linuxu).

1. Vstavite mikroSD kartico v režo tik pod stikalom za vklop. Prepričajte se, da je popolnoma vstavljena, dokler ne klikne in ostane na mestu. Morda boste morali uporabiti noht ali tanek pripomoček.

1. Dodajte naslednje izjave `include` na vrh datoteke `main.cpp`:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Dodajte naslednjo funkcijo pred funkcijo `setup`:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Ta funkcija konfigurira SD kartico z uporabo SPI vodila.

1. To funkcijo pokličite iz funkcije `setup`:

    ```cpp
    setupSDCard();
    ```

1. Dodajte naslednjo kodo nad funkcijo `buttonPressed`:

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

    To definira globalno spremenljivko za število datotek. Ta se uporablja za imena datotek slik, tako da je mogoče zajeti več slik z naraščajočimi imeni datotek - `1.jpg`, `2.jpg` in tako naprej.

    Nato definira funkcijo `saveToSDCard`, ki sprejme medpomnilnik podatkov bajtov in dolžino medpomnilnika. Ustvari se ime datoteke z uporabo števca datotek, števec datotek pa se poveča za naslednjo datoteko. Dvojiški podatki iz medpomnilnika se nato zapišejo v datoteko.

1. Pokličite funkcijo `saveToSDCard` iz funkcije `buttonPressed`. Klic naj bo **preden** se medpomnilnik izbriše:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Sestavite in naložite to kodo ter preverite izhod na serijskem monitorju. Vsakič, ko pritisnete gumb C, se zajame slika in shrani na SD kartico.

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

1. Izklopite mikroSD kartico in jo odstranite tako, da jo rahlo pritisnete in sprostite, nato pa bo skočila ven. Morda boste morali uporabiti tanek pripomoček za to. Priključite mikroSD kartico v računalnik, da si ogledate slike.

    ![Slika banane, zajeta z ArduCam](../../../../../translated_images/sl/banana-arducam.be1b32d4267a8194.webp)
💁 Morda bo potrebnih nekaj slik, da se belina kamere prilagodi. To boste opazili glede na barvo posnetih slik, prve nekaj lahko izgledajo barvno nepravilne. To lahko vedno zaobidete tako, da spremenite kodo za zajem nekaj slik, ki so prezrte v funkciji `setup`.


---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.