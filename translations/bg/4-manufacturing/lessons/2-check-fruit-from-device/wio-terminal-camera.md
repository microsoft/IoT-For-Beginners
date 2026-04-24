# Заснемане на изображение - Wio Terminal

В тази част на урока ще добавите камера към вашия Wio Terminal и ще заснемете изображения с нея.

## Хардуер

Wio Terminal се нуждае от камера.

Камерата, която ще използвате, е [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Това е 2-мегапикселова камера, базирана на сензора OV2640. Тя комуникира чрез SPI интерфейс за заснемане на изображения и използва I2C за конфигуриране на сензора.

## Свързване на камерата

ArduCam няма Grove конектор, вместо това се свързва към SPI и I2C шините чрез GPIO пиновете на Wio Terminal.

### Задача - свържете камерата

Свържете камерата.

![Сензор ArduCam](../../../../../translated_images/bg/arducam.20e4e4cbb2682965.webp)

1. Пиновете в основата на ArduCam трябва да бъдат свързани към GPIO пиновете на Wio Terminal. За да е по-лесно да намерите правилните пинове, прикрепете стикера за GPIO пинове, който идва с Wio Terminal, около пиновете:

    ![Wio Terminal със стикер за GPIO пинове](../../../../../translated_images/bg/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. Използвайки джъмпер кабели, направете следните връзки:

    | Пин на ArduCAM | Пин на Wio Terminal | Описание                                |
    | -------------- | ------------------- | --------------------------------------- |
    | CS             | 24 (SPI_CS)         | SPI Chip Select                         |
    | MOSI           | 19 (SPI_MOSI)       | SPI Контролер Изход, Периферен Вход     |
    | MISO           | 21 (SPI_MISO)       | SPI Контролер Вход, Периферен Изход     |
    | SCK            | 23 (SPI_SCLK)       | SPI Сериен Часовник                     |
    | GND            | 6 (GND)             | Земя - 0V                               |
    | VCC            | 4 (5V)              | 5V захранване                           |
    | SDA            | 3 (I2C1_SDA)        | I2C Сериен Данни                        |
    | SCL            | 5 (I2C1_SCL)        | I2C Сериен Часовник                     |

    ![Wio Terminal, свързан към ArduCam с джъмпер кабели](../../../../../translated_images/bg/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.webp)

    Връзките GND и VCC осигуряват 5V захранване за ArduCam. Камерата работи на 5V, за разлика от Grove сензорите, които работят на 3V. Това захранване идва директно от USB-C връзката, която захранва устройството.

    > 💁 За SPI връзката етикетите на пиновете на ArduCam и имената на пиновете на Wio Terminal, използвани в кода, все още използват старата конвенция за именуване. Инструкциите в този урок ще използват новата конвенция за именуване, освен когато имената на пиновете се използват в кода.

1. Сега можете да свържете Wio Terminal към вашия компютър.

## Програмиране на устройството за свързване с камерата

Сега Wio Terminal може да бъде програмиран да използва свързаната ArduCAM камера.

### Задача - програмирайте устройството за свързване с камерата

1. Създайте нов проект за Wio Terminal, използвайки PlatformIO. Наречете този проект `fruit-quality-detector`. Добавете код във функцията `setup`, за да конфигурирате серийния порт.

1. Добавете код за свързване към WiFi, като използвате вашите WiFi идентификационни данни в файл, наречен `config.h`. Не забравяйте да добавите необходимите библиотеки в `platformio.ini` файла.

1. Библиотеката ArduCam не е налична като Arduino библиотека, която може да бъде инсталирана от `platformio.ini` файла. Вместо това тя трябва да бъде инсталирана от изходния код от тяхната страница в GitHub. Можете да я получите по един от следните начини:

    * Клонирайте репото от [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Отидете на репото в GitHub на [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) и изтеглете кода като zip файл от бутона **Code**

1. Нуждаете се само от папката `ArduCAM` от този код. Копирайте цялата папка в папката `lib` във вашия проект.

    > ⚠️ Цялата папка трябва да бъде копирана, така че кодът да е в `lib/ArduCam`. Не копирайте само съдържанието на папката `ArduCam` в папката `lib`, копирайте цялата папка.

1. Кодът на библиотеката ArduCam работи за множество типове камери. Типът камера, който искате да използвате, се конфигурира чрез флагове на компилатора - това прави библиотеката възможно най-малка, като премахва кода за камери, които не използвате. За да конфигурирате библиотеката за камерата OV2640, добавете следното в края на `platformio.ini` файла:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Това задава 2 флага на компилатора:

      * `ARDUCAM_SHIELD_V2`, за да каже на библиотеката, че камерата е на Arduino платка, известна като shield.
      * `OV2640_CAM`, за да каже на библиотеката да включи само кода за камерата OV2640.

1. Добавете заглавен файл в папката `src`, наречен `camera.h`. Този файл ще съдържа код за комуникация с камерата. Добавете следния код в този файл:

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

    Това е ниско ниво код, който конфигурира камерата, използвайки библиотеките на ArduCam, и извлича изображенията, когато е необходимо, чрез SPI шината. Този код е много специфичен за ArduCam, така че не е нужно да се притеснявате как точно работи.

1. В `main.cpp` добавете следния код под другите `include` изявления, за да включите този нов файл и да създадете инстанция на класа за камерата:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Това създава `Camera`, която записва изображенията като JPEG с резолюция 640x480. Въпреки че се поддържат по-високи резолюции (до 3280x2464), класификаторът на изображения работи с много по-малки изображения (227x227), така че няма нужда да се заснемат и изпращат по-големи изображения.

1. Добавете следния код под това, за да дефинирате функция за настройка на камерата:

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

    Тази функция `setupCamera` започва с конфигуриране на SPI чип селект пина (`PIN_SPI_SS`) като висок, правейки Wio Terminal SPI контролер. След това стартира I2C и SPI шините. Накрая инициализира класа за камерата, който конфигурира настройките на сензора на камерата и гарантира, че всичко е правилно свързано.

1. Извикайте тази функция в края на функцията `setup`:

    ```cpp
    setupCamera();
    ```

1. Компилирайте и качете този код и проверете изхода от серийния монитор. Ако видите `Error setting up the camera!`, проверете окабеляването, за да се уверите, че всички кабели свързват правилните пинове на ArduCam с правилните GPIO пинове на Wio Terminal и че всички джъмпер кабели са правилно поставени.

## Заснемане на изображение

Сега Wio Terminal може да бъде програмиран да заснема изображение, когато се натисне бутон.

### Задача - заснемете изображение

1. Микроконтролерите изпълняват вашия код непрекъснато, така че не е лесно да се задейства нещо като заснемане на снимка, без да се реагира на сензор. Wio Terminal има бутони, така че камерата може да бъде настроена да се задейства от един от бутоните. Добавете следния код в края на функцията `setup`, за да конфигурирате бутона C (един от трите бутона отгоре, този най-близо до превключвателя за захранване).

    ![Бутон C, най-близо до превключвателя за захранване](../../../../../translated_images/bg/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    Режимът `INPUT_PULLUP` на практика обръща входа. Например, обикновено бутонът би изпращал нисък сигнал, когато не е натиснат, и висок сигнал, когато е натиснат. Когато е настроен на `INPUT_PULLUP`, той изпраща висок сигнал, когато не е натиснат, и нисък сигнал, когато е натиснат.

1. Добавете празна функция за реакция на натискането на бутона преди функцията `loop`:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Извикайте тази функция във функцията `loop`, когато бутонът е натиснат:

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

    Този код проверява дали бутонът е натиснат. Ако е натиснат, се извиква функцията `buttonPressed`, и цикълът се забавя с 2 секунди. Това е, за да се даде време бутонът да бъде освободен, така че дълго натискане да не се регистрира два пъти.

    > 💁 Бутонът на Wio Terminal е настроен на `INPUT_PULLUP`, така че изпраща висок сигнал, когато не е натиснат, и нисък сигнал, когато е натиснат.

1. Добавете следния код във функцията `buttonPressed`:

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

    Този код започва заснемането на изображение, като извиква `startCapture`. Хардуерът на камерата не работи, като връща данните, когато ги поискате, вместо това изпращате инструкция за започване на заснемане, и камерата работи във фонов режим, за да заснеме изображението, да го конвертира в JPEG и да го съхрани в локален буфер на самата камера. Извикването на `captureReady` проверява дали заснемането на изображението е завършено.

    След като заснемането е завършено, данните за изображението се копират от буфера на камерата в локален буфер (масив от байтове) с извикването на `readImageToBuffer`. Дължината на буфера след това се изпраща към серийния монитор.

1. Компилирайте и качете този код и проверете изхода на серийния монитор. Всеки път, когато натиснете бутона C, ще се заснеме изображение и ще видите размера на изображението, изпратен към серийния монитор.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Различните изображения ще имат различни размери. Те са компресирани като JPEG и размерът на JPEG файл за дадена резолюция зависи от съдържанието на изображението.

> 💁 Можете да намерите този код в папката [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Успешно заснехте изображения с вашия Wio Terminal.

## По избор - проверка на изображенията от камерата с помощта на SD карта

Най-лесният начин да видите изображенията, заснети от камерата, е да ги запишете на SD карта в Wio Terminal и след това да ги прегледате на вашия компютър. Изпълнете тази стъпка, ако разполагате с резервна microSD карта и microSD слот на вашия компютър или адаптер.

Wio Terminal поддържа само microSD карти с капацитет до 16GB. Ако имате по-голяма SD карта, тя няма да работи.

### Задача - проверка на изображенията от камерата с помощта на SD карта

1. Форматирайте microSD карта като FAT32 или exFAT, използвайки съответните приложения на вашия компютър (Disk Utility на macOS, File Explorer на Windows или командни инструменти в Linux).

1. Поставете microSD картата в слота точно под превключвателя за захранване. Уверете се, че е напълно вкарана, докато щракне и остане на място. Може да се наложи да я натиснете с нокът или тънък инструмент.

1. Добавете следните include изявления в началото на файла `main.cpp`:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Добавете следната функция преди функцията `setup`:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Това конфигурира SD картата, използвайки SPI шината.

1. Извикайте това от функцията `setup`:

    ```cpp
    setupSDCard();
    ```

1. Добавете следния код над функцията `buttonPressed`:

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

    Това дефинира глобална променлива за броя на файловете. Тя се използва за имената на файловете с изображения, така че могат да се заснемат множество изображения с нарастващи имена на файлове - `1.jpg`, `2.jpg` и т.н.

    След това дефинира функцията `saveToSDCard`, която приема буфер с байтови данни и дължината на буфера. Създава се име на файл, използвайки броя на файловете, и броят се увеличава за следващия файл. Бинарните данни от буфера след това се записват във файла.

1. Извикайте функцията `saveToSDCard` от функцията `buttonPressed`. Извикването трябва да бъде **преди** буферът да бъде изтрит:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Компилирайте и качете този код и проверете изхода на серийния монитор. Всеки път, когато натиснете бутона C, ще се заснеме изображение и ще се запише на SD картата.

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

1. Изключете захранването на microSD картата и я извадете, като я натиснете леко и я освободите, и тя ще изскочи. Може да се наложи да използвате тънък инструмент за това. Поставете microSD картата във вашия компютър, за да прегледате изображенията.

    ![Снимка на банан, заснета с ArduCam](../../../../../translated_images/bg/banana-arducam.be1b32d4267a8194.webp)
💁 Може да отнеме няколко изображения, докато баланса на бялото на камерата се настрои. Ще забележите това по цвета на заснетите изображения, първите няколко може да изглеждат с неправилен цвят. Винаги можете да заобиколите това, като промените кода да заснеме няколко изображения, които се игнорират във функцията `setup`.


---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматичните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия изходен език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален превод от човек. Не носим отговорност за каквито и да било недоразумения или погрешни интерпретации, произтичащи от използването на този превод.