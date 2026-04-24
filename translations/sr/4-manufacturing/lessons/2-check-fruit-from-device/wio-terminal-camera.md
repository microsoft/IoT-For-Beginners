# Снимање слике - Wio Terminal

У овом делу лекције, додаћете камеру на ваш Wio Terminal и снимати слике помоћу ње.

## Хардвер

Wio Terminal захтева камеру.

Камера коју ћете користити је [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Ово је камера од 2 мегапиксела заснована на сензору слике OV2640. Она комуницира преко SPI интерфејса за снимање слика и користи I²C за конфигурацију сензора.

## Повезивање камере

ArduCam нема Grove утичницу, већ се повезује на SPI и I²C магистрале преко GPIO пинова на Wio Terminal-у.

### Задатак - повежите камеру

Повежите камеру.

![Сензор ArduCam](../../../../../translated_images/sr/arducam.20e4e4cbb2682965.webp)

1. Пинови на дну ArduCam-а треба да буду повезани на GPIO пинове на Wio Terminal-у. Да бисте лакше пронашли одговарајуће пинове, залепите налепницу са GPIO пиновима која долази уз Wio Terminal око пинова:

    ![Wio Terminal са налепницом GPIO пинова](../../../../../translated_images/sr/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. Користећи жице за повезивање, направите следеће везе:

    | Пин на ArduCAM-у | Пин на Wio Terminal-у | Опис                                   |
    | ---------------- | --------------------- | -------------------------------------- |
    | CS               | 24 (SPI_CS)          | SPI Chip Select                        |
    | MOSI             | 19 (SPI_MOSI)        | SPI Контролерски излаз, периферни улаз |
    | MISO             | 21 (SPI_MISO)        | SPI Контролерски улаз, периферни излаз |
    | SCK              | 23 (SPI_SCLK)        | SPI Серијски сат                       |
    | GND              | 6 (GND)              | Земља - 0V                             |
    | VCC              | 4 (5V)               | Напајање од 5V                         |
    | SDA              | 3 (I2C1_SDA)         | I²C Серијски подаци                    |
    | SCL              | 5 (I2C1_SCL)         | I²C Серијски сат                       |

    ![Wio Terminal повезан са ArduCam-ом помоћу жица](../../../../../translated_images/sr/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.webp)

    GND и VCC везе обезбеђују напајање од 5V за ArduCam. Камера ради на 5V, за разлику од Grove сензора који раде на 3V. Ово напајање долази директно из USB-C конекције која напаја уређај.

    > 💁 За SPI везу, ознаке пинова на ArduCam-у и називи пинова на Wio Terminal-у који се користе у коду и даље користе стару конвенцију именовања. Упутства у овој лекцији користиће нову конвенцију именовања, осим када се називи пинова користе у коду.

1. Сада можете повезати Wio Terminal са вашим рачунаром.

## Програмирање уређаја за повезивање са камером

Wio Terminal сада може бити програмиран да користи повезану ArduCAM камеру.

### Задатак - програмирајте уређај за повезивање са камером

1. Направите нови Wio Terminal пројекат користећи PlatformIO. Назовите овај пројекат `fruit-quality-detector`. Додајте код у функцију `setup` за конфигурацију серијског порта.

1. Додајте код за повезивање на WiFi, са вашим WiFi акредитивима у фајлу под називом `config.h`. Не заборавите да додате потребне библиотеке у `platformio.ini` фајл.

1. ArduCam библиотека није доступна као Arduino библиотека која се може инсталирати из `platformio.ini` фајла. Уместо тога, мораће да се инсталира из извора са њихове GitHub странице. Можете је добити на један од следећих начина:

    * Клонирањем репозиторијума са [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Одласком на репозиторијум на GitHub-у на [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) и преузимањем кода као zip фајл преко дугмета **Code**

1. Потребан вам је само фолдер `ArduCAM` из овог кода. Копирајте цео фолдер у `lib` фолдер у вашем пројекту.

    > ⚠️ Цео фолдер мора бити копиран, тако да је код у `lib/ArduCam`. Немојте само копирати садржај фолдера `ArduCam` у `lib` фолдер, већ копирајте цео фолдер.

1. Код ArduCam библиотеке ради за више типова камера. Тип камере који желите да користите се конфигурише помоћу компајлерских застава - ово чини библиотеку што мањом тако што уклања код за камере које не користите. Да бисте конфигурисали библиотеку за OV2640 камеру, додајте следеће на крај `platformio.ini` фајла:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Ово поставља 2 компајлерске заставе:

      * `ARDUCAM_SHIELD_V2` да би се библиотеци рекло да је камера на Arduino плочи, познатој као shield.
      * `OV2640_CAM` да би се библиотеци рекло да укључи само код за OV2640 камеру.

1. Додајте хедер фајл у `src` фолдер под називом `camera.h`. Овај фајл ће садржати код за комуникацију са камером. Додајте следећи код у овај фајл:

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

    Ово је ниско-ниво код који конфигурише камеру користећи ArduCam библиотеке и извлачи слике када је то потребно користећи SPI магистралу. Овај код је веома специфичан за ArduCam, тако да не морате да бринете како функционише у овом тренутку.

1. У `main.cpp`, додајте следећи код испод осталих `include` изјава да бисте укључили овај нови фајл и креирали инстанцу класе камере:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Ово креира `Camera` која чува слике као JPEG-ове у резолуцији 640x480. Иако су подржане веће резолуције (до 3280x2464), класификатор слика ради са много мањим сликама (227x227), тако да нема потребе за снимањем и слањем већих слика.

1. Додајте следећи код испод овога да дефинишете функцију за подешавање камере:

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

    Ова функција `setupCamera` почиње конфигурисањем SPI chip select пина (`PIN_SPI_SS`) као високог, чиме Wio Terminal постаје SPI контролер. Затим покреће I²C и SPI магистрале. На крају, иницијализује класу камере која конфигурише подешавања сензора камере и осигурава да је све правилно повезано.

1. Позовите ову функцију на крају `setup` функције:

    ```cpp
    setupCamera();
    ```

1. Компилирајте и отпремите овај код и проверите излаз на серијском монитору. Ако видите `Error setting up the camera!`, проверите ожичење да бисте се уверили да су сви каблови правилно повезани на одговарајуће пинове на ArduCam-у и Wio Terminal-у, и да су сви каблови добро постављени.

## Снимање слике

Wio Terminal сада може бити програмиран да снима слике када се притисне дугме.

### Задатак - снимање слике

1. Микроконтролери извршавају ваш код континуирано, тако да није лако покренути нешто попут снимања фотографије без реаговања на сензор. Wio Terminal има дугмад, тако да се камера може подесити да се активира једним од дугмади. Додајте следећи код на крај `setup` функције да конфигуришете дугме C (једно од три дугмета на врху, најближе прекидачу за напајање).

    ![Дугме C на врху, најближе прекидачу за напајање](../../../../../translated_images/sr/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    Режим `INPUT_PULLUP` у суштини обрће улаз. На пример, нормално дугме би слало низак сигнал када није притиснуто, а висок сигнал када је притиснуто. Када је подешено на `INPUT_PULLUP`, шаље висок сигнал када није притиснуто, а низак сигнал када је притиснуто.

1. Додајте празну функцију за реаговање на притисак дугмета пре `loop` функције:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Позовите ову функцију у `loop` методи када је дугме притиснуто:

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

    Овај кључ проверава да ли је дугме притиснуто. Ако јесте, позива се функција `buttonPressed`, а петља се одлаже за 2 секунде. Ово је да би се омогућило време да се дугме отпусти како се дуг притисак не би регистровао два пута.

    > 💁 Дугме на Wio Terminal-у је подешено на `INPUT_PULLUP`, тако да шаље висок сигнал када није притиснуто, а низак сигнал када је притиснуто.

1. Додајте следећи код у функцију `buttonPressed`:

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

    Овај код започиње снимање камере позивом `startCapture`. Хардвер камере не ради тако што враћа податке када их затражите, већ шаљете инструкцију за почетак снимања, а камера ради у позадини да сними слику, претвори је у JPEG и сачува у локалном баферу на самој камери. Позив `captureReady` затим проверава да ли је снимање слике завршено.

    Када је снимање завршено, подаци слике се копирају из бафера на камери у локални бафер (низ бајтова) помоћу позива `readImageToBuffer`. Дужина бафера се затим шаље на серијски монитор.

1. Компилирајте и отпремите овај код и проверите излаз на серијском монитору. Сваки пут када притиснете дугме C, слика ће бити снимљена и видећете величину слике послату на серијски монитор.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Различите слике ће имати различите величине. Оне су компримоване као JPEG-ови, а величина JPEG фајла за дату резолуцију зависи од тога шта се налази на слици.

> 💁 Овај код можете пронаћи у фолдеру [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Успешно сте снимили слике помоћу вашег Wio Terminal-а.

## Опционо - верификација слика са камере помоћу SD картице

Најлакши начин да видите слике које је камера снимила је да их запишете на SD картицу у Wio Terminal-у, а затим их прегледате на вашем рачунару. Урадите овај корак ако имате резервну microSD картицу и microSD утичницу на вашем рачунару или адаптер.

Wio Terminal подржава само microSD картице до 16GB. Ако имате већу SD картицу, она неће радити.

### Задатак - верификација слика са камере помоћу SD картице

1. Форматирајте microSD картицу као FAT32 или exFAT користећи одговарајуће апликације на вашем рачунару (Disk Utility на macOS-у, File Explorer на Windows-у, или користећи алате командне линије на Linux-у).

1. Уметните microSD картицу у утичницу одмах испод прекидача за напајање. Уверите се да је потпуно уметнута док не кликне и остане на месту; можда ћете морати да је гурнете помоћу нокта или танког алата.

1. Додајте следеће `include` изјаве на врх `main.cpp` фајла:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Додајте следећу функцију пре `setup` функције:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Ово конфигурише SD картицу користећи SPI магистралу.

1. Позовите ово из `setup` функције:

    ```cpp
    setupSDCard();
    ```

1. Додајте следећи код изнад функције `buttonPressed`:

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

    Ово дефинише глобалну променљиву за бројач фајлова. Ово се користи за имена фајлова слика тако да се више слика може снимити са инкременталним именима фајлова - `1.jpg`, `2.jpg` и тако даље.

    Затим дефинише функцију `saveToSDCard` која узима бафер података бајтова и дужину бафера. Име фајла се креира користећи бројач фајлова, а бројач се инкрементира за следећи фајл. Бинарни подаци из бафера се затим уписују у фајл.

1. Позовите функцију `saveToSDCard` из функције `buttonPressed`. Позив треба да буде **пре** него што се бафер обрише:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Компилирајте и отпремите овај код и проверите излаз на серијском монитору. Сваки пут када притиснете дугме C, слика ће бити снимљена и сачувана на SD картицу.

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

1. Искључите microSD картицу и извадите је тако што ћете је благо гурнути и пустити, након чега ће искочити. Можда ћете морати да користите танак алат за ово. Уметните microSD картицу у ваш рачунар да бисте прегледали слике.

    ![Слика банане снимљена помоћу ArduCam-а](../../../../../translated_images/sr/banana-arducam.be1b32d4267a8194.webp)
💁 Може бити потребно неколико слика да би се бела равнотежа камере прилагодила. Приметићете ово на основу боје снимљених слика, прве неколико могу изгледати у погрешној боји. Увек можете заобићи ово тако што ћете променити код да снимите неколико слика које се игноришу у функцији `setup`.


---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.