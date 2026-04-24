# Захоплення зображення - Wio Terminal

У цій частині уроку ви додасте камеру до вашого Wio Terminal і захопите зображення з неї.

## Апаратне забезпечення

Wio Terminal потребує камери.

Камера, яку ви будете використовувати, — це [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Це 2-мегапіксельна камера на основі сенсора зображення OV2640. Вона передає дані через SPI-інтерфейс для захоплення зображень і використовує I2C для налаштування сенсора.

## Підключення камери

ArduCam не має роз'єму Grove, натомість вона підключається до SPI та I2C шин через GPIO-піни на Wio Terminal.

### Завдання - підключення камери

Підключіть камеру.

![Сенсор ArduCam](../../../../../translated_images/uk/arducam.20e4e4cbb2682965.webp)

1. Піни на основі ArduCam потрібно підключити до GPIO-пінів на Wio Terminal. Щоб легше знайти потрібні піни, прикріпіть наклейку з GPIO-пінами, яка йде в комплекті з Wio Terminal, навколо пінів:

    ![Wio Terminal з наклейкою GPIO-пінів](../../../../../translated_images/uk/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. Використовуючи з'єднувальні дроти, зробіть наступні підключення:

    | Пін ArduCAM | Пін Wio Terminal | Опис                                    |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | Вибір чіпа SPI                          |
    | MOSI        | 19 (SPI_MOSI)    | Вихід контролера SPI, вхід периферії    |
    | MISO        | 21 (SPI_MISO)    | Вхід контролера SPI, вихід периферії    |
    | SCK         | 23 (SPI_SCLK)    | Серійний годинник SPI                   |
    | GND         | 6 (GND)          | Земля - 0В                              |
    | VCC         | 4 (5V)           | Живлення 5В                             |
    | SDA         | 3 (I2C1_SDA)     | Серійні дані I2C                        |
    | SCL         | 5 (I2C1_SCL)     | Серійний годинник I2C                   |

    ![Wio Terminal підключений до ArduCam за допомогою з'єднувальних дротів](../../../../../translated_images/uk/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.webp)

    З'єднання GND і VCC забезпечують живлення 5В для ArduCam. Камера працює на 5В, на відміну від датчиків Grove, які працюють на 3В. Це живлення надходить безпосередньо від USB-C підключення, яке живить пристрій.

    > 💁 Для SPI-з'єднання мітки пінів на ArduCam і назви пінів Wio Terminal, які використовуються в коді, все ще використовують стару систему назв. Інструкції в цьому уроці будуть використовувати нову систему назв, за винятком випадків, коли назви пінів використовуються в коді.

1. Тепер ви можете підключити Wio Terminal до вашого комп'ютера.

## Програмування пристрою для підключення до камери

Тепер Wio Terminal можна запрограмувати для використання підключеної камери ArduCAM.

### Завдання - програмування пристрою для підключення до камери

1. Створіть новий проект для Wio Terminal за допомогою PlatformIO. Назвіть цей проект `fruit-quality-detector`. Додайте код у функцію `setup` для налаштування серійного порту.

1. Додайте код для підключення до WiFi, використовуючи ваші WiFi-дані у файлі `config.h`. Не забудьте додати необхідні бібліотеки до файлу `platformio.ini`.

1. Бібліотека ArduCam недоступна як бібліотека Arduino, яку можна встановити через файл `platformio.ini`. Натомість її потрібно встановити з вихідного коду з їхньої сторінки GitHub. Ви можете отримати її, або:

    * Клонуючи репозиторій з [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Перейшовши до репозиторію на GitHub за адресою [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) і завантаживши код як zip-файл через кнопку **Code**

1. Вам потрібна лише папка `ArduCAM` з цього коду. Скопіюйте всю папку до папки `lib` у вашому проекті.

    > ⚠️ Потрібно скопіювати всю папку, щоб код знаходився у `lib/ArduCam`. Не копіюйте лише вміст папки `ArduCam` до папки `lib`, скопіюйте всю папку.

1. Код бібліотеки ArduCam працює для кількох типів камер. Тип камери, яку ви хочете використовувати, налаштовується за допомогою прапорців компілятора — це дозволяє зменшити розмір бібліотеки, видаляючи код для камер, які ви не використовуєте. Щоб налаштувати бібліотеку для камери OV2640, додайте наступне до кінця файлу `platformio.ini`:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Це встановлює 2 прапорці компілятора:

      * `ARDUCAM_SHIELD_V2` для повідомлення бібліотеці, що камера знаходиться на платі Arduino, відомій як щит.
      * `OV2640_CAM` для повідомлення бібліотеці включити лише код для камери OV2640.

1. Додайте заголовковий файл до папки `src`, назвавши його `camera.h`. У цьому файлі буде код для взаємодії з камерою. Додайте наступний код до цього файлу:

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

    Це низькорівневий код, який налаштовує камеру за допомогою бібліотек ArduCam і витягує зображення, коли це необхідно, використовуючи SPI-шину. Цей код дуже специфічний для ArduCam, тому вам не потрібно турбуватися про те, як він працює на даному етапі.

1. У `main.cpp` додайте наступний код під іншими `include`-висловами, щоб включити цей новий файл і створити екземпляр класу камери:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Це створює `Camera`, яка зберігає зображення у форматі JPEG з роздільною здатністю 640x480. Хоча підтримуються вищі роздільні здатності (до 3280x2464), класифікатор зображень працює з набагато меншими зображеннями (227x227), тому немає потреби захоплювати та надсилати більші зображення.

1. Додайте наступний код нижче, щоб визначити функцію для налаштування камери:

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

    Функція `setupCamera` починає з налаштування піну вибору чіпа SPI (`PIN_SPI_SS`) як високого, роблячи Wio Terminal контролером SPI. Потім вона запускає шини I2C і SPI. Нарешті, вона ініціалізує клас камери, який налаштовує параметри сенсора камери та перевіряє правильність підключення.

1. Викличте цю функцію в кінці функції `setup`:

    ```cpp
    setupCamera();
    ```

1. Зберіть і завантажте цей код, і перевірте вихідні дані з серійного монітора. Якщо ви бачите `Error setting up the camera!`, перевірте проводку, щоб переконатися, що всі кабелі підключені до правильних пінів на ArduCam і правильних GPIO-пінів на Wio Terminal, а також що всі з'єднувальні дроти правильно закріплені.

## Захоплення зображення

Тепер Wio Terminal можна запрограмувати для захоплення зображення при натисканні кнопки.

### Завдання - захоплення зображення

1. Мікроконтролери виконують ваш код безперервно, тому не так просто викликати щось, наприклад, зробити фото, без реакції на датчик. Wio Terminal має кнопки, тому камеру можна налаштувати для активації однією з кнопок. Додайте наступний код до кінця функції `setup`, щоб налаштувати кнопку C (одну з трьох кнопок зверху, найближчу до перемикача живлення).

    ![Кнопка C зверху, найближча до перемикача живлення](../../../../../translated_images/uk/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    Режим `INPUT_PULLUP` фактично інвертує вхід. Наприклад, зазвичай кнопка надсилає низький сигнал, коли не натиснута, і високий сигнал, коли натиснута. При налаштуванні на `INPUT_PULLUP` вона надсилає високий сигнал, коли не натиснута, і низький сигнал, коли натиснута.

1. Додайте порожню функцію для реагування на натискання кнопки перед функцією `loop`:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Викличте цю функцію в методі `loop`, коли кнопка натиснута:

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

    Цей ключ перевіряє, чи кнопка натиснута. Якщо вона натиснута, викликається функція `buttonPressed`, і цикл затримується на 2 секунди. Це дозволяє кнопці бути відпущеною, щоб довге натискання не реєструвалося двічі.

    > 💁 Кнопка на Wio Terminal налаштована на `INPUT_PULLUP`, тому надсилає високий сигнал, коли не натиснута, і низький сигнал, коли натиснута.

1. Додайте наступний код до функції `buttonPressed`:

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

    Цей код починає захоплення зображення, викликаючи `startCapture`. Апаратне забезпечення камери не працює, повертаючи дані, коли ви їх запитуєте, натомість ви надсилаєте інструкцію для початку захоплення, і камера працює у фоновому режимі, щоб захопити зображення, перетворити його на JPEG і зберегти в локальному буфері на самій камері. Виклик `captureReady` потім перевіряє, чи завершено захоплення зображення.

    Після завершення захоплення дані зображення копіюються з буфера на камері в локальний буфер (масив байтів) за допомогою виклику `readImageToBuffer`. Довжина буфера потім надсилається до серійного монітора.

1. Зберіть і завантажте цей код, і перевірте вихідні дані на серійному моніторі. Кожного разу, коли ви натискаєте кнопку C, зображення буде захоплено, і ви побачите розмір зображення, надісланий до серійного монітора.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Різні зображення матимуть різні розміри. Вони стискаються як JPEG, і розмір файлу JPEG для заданої роздільної здатності залежить від того, що знаходиться на зображенні.

> 💁 Ви можете знайти цей код у папці [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Ви успішно захопили зображення за допомогою вашого Wio Terminal.

## Додатково - перевірка зображень камери за допомогою SD-карти

Найпростіший спосіб побачити зображення, захоплені камерою, — це записати їх на SD-карту в Wio Terminal, а потім переглянути їх на вашому комп'ютері. Виконайте цей крок, якщо у вас є запасна microSD-карта і роз'єм для microSD-карти на вашому комп'ютері або адаптер.

Wio Terminal підтримує лише microSD-карти об'ємом до 16 ГБ. Якщо у вас є більша SD-карта, вона не працюватиме.

### Завдання - перевірка зображень камери за допомогою SD-карти

1. Відформатуйте microSD-карту як FAT32 або exFAT, використовуючи відповідні програми на вашому комп'ютері (Disk Utility на macOS, File Explorer на Windows або командні інструменти в Linux).

1. Вставте microSD-карту в роз'єм трохи нижче перемикача живлення. Переконайтеся, що вона вставлена до кінця, поки не клацне і не залишиться на місці. Можливо, вам доведеться натиснути її за допомогою нігтя або тонкого інструмента.

1. Додайте наступні вислови `include` на початку файлу `main.cpp`:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Додайте наступну функцію перед функцією `setup`:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Це налаштовує SD-карту за допомогою SPI-шини.

1. Викличте це з функції `setup`:

    ```cpp
    setupSDCard();
    ```

1. Додайте наступний код над функцією `buttonPressed`:

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

    Це визначає глобальну змінну для підрахунку файлів. Вона використовується для імен файлів зображень, щоб можна було захоплювати кілька зображень з інкрементними іменами файлів — `1.jpg`, `2.jpg` і так далі.

    Потім визначається функція `saveToSDCard`, яка приймає буфер даних байтів і довжину буфера. Ім'я файлу створюється за допомогою підрахунку файлів, і підрахунок файлів збільшується, готуючись до наступного файлу. Двійкові дані з буфера потім записуються у файл.

1. Викличте функцію `saveToSDCard` з функції `buttonPressed`. Виклик має бути **перед** видаленням буфера:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Зберіть і завантажте цей код, і перевірте вихідні дані на серійному моніторі. Кожного разу, коли ви натискаєте кнопку C, зображення буде захоплено і збережено на SD-карту.

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

1. Вимкніть живлення microSD-карти і витягніть її, трохи натиснувши і відпустивши, і вона вискочить. Можливо, вам доведеться використовувати тонкий інструмент для цього. Підключіть microSD-карту до вашого комп'ютера, щоб переглянути зображення.

    ![Зображення банана, захоплене за допомогою ArduCam](../../../../../translated_images/uk/banana-arducam.be1b32d4267a8194.webp)
💁 Може знадобитися кілька зображень, щоб баланс білого камери налаштувався. Ви помітите це за кольором захоплених зображень, перші кілька можуть виглядати з неправильним кольором. Ви завжди можете обійти це, змінивши код для захоплення кількох зображень, які ігноруються у функції `setup`.


---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.