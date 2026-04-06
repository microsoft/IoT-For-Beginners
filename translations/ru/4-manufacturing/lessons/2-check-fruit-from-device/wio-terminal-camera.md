# Захват изображения - Wio Terminal

В этой части урока вы добавите камеру к вашему Wio Terminal и будете захватывать изображения с её помощью.

## Аппаратное обеспечение

Для Wio Terminal требуется камера.

Камера, которую вы будете использовать, — это [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Это 2-мегапиксельная камера на основе сенсора OV2640. Она передает изображения через интерфейс SPI и использует I2C для настройки сенсора.

## Подключение камеры

ArduCam не имеет разъема Grove, вместо этого она подключается к шинам SPI и I2C через GPIO-пины на Wio Terminal.

### Задание - подключите камеру

Подключите камеру.

![Сенсор ArduCam](../../../../../translated_images/ru/arducam.20e4e4cbb2682965.webp)

1. Пины на основании ArduCam нужно подключить к GPIO-пинам на Wio Terminal. Чтобы было проще найти нужные пины, прикрепите наклейку с обозначением GPIO-пинов, которая идет в комплекте с Wio Terminal:

    ![Wio Terminal с наклейкой GPIO-пинов](../../../../../translated_images/ru/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. Используя соединительные провода, выполните следующие подключения:

    | Пин ArduCAM | Пин Wio Terminal | Описание                                 |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | Выбор чипа SPI                          |
    | MOSI        | 19 (SPI_MOSI)    | Выход SPI-контроллера, вход периферии   |
    | MISO        | 21 (SPI_MISO)    | Вход SPI-контроллера, выход периферии   |
    | SCK         | 23 (SPI_SCLK)    | Последовательный тактовый сигнал SPI    |
    | GND         | 6 (GND)          | Земля - 0 В                             |
    | VCC         | 4 (5V)           | Питание 5 В                             |
    | SDA         | 3 (I2C1_SDA)     | Последовательные данные I2C             |
    | SCL         | 5 (I2C1_SCL)     | Последовательный тактовый сигнал I2C    |

    ![Wio Terminal, подключенный к ArduCam с помощью соединительных проводов](../../../../../translated_images/ru/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.webp)

    Соединения GND и VCC обеспечивают питание 5 В для ArduCam. Камера работает на 5 В, в отличие от датчиков Grove, которые работают на 3 В. Это питание поступает напрямую от USB-C подключения, которое питает устройство.

    > 💁 Для подключения SPI обозначения пинов на ArduCam и названия пинов Wio Terminal, используемые в коде, все еще используют старую нотацию. В этом уроке будет использоваться новая нотация, за исключением случаев, когда названия пинов используются в коде.

1. Теперь вы можете подключить Wio Terminal к вашему компьютеру.

## Программирование устройства для подключения к камере

Теперь Wio Terminal можно запрограммировать для работы с подключенной камерой ArduCAM.

### Задание - запрограммируйте устройство для подключения к камере

1. Создайте новый проект для Wio Terminal с использованием PlatformIO. Назовите проект `fruit-quality-detector`. Добавьте код в функцию `setup` для настройки последовательного порта.

1. Добавьте код для подключения к Wi-Fi, указав ваши учетные данные Wi-Fi в файле `config.h`. Не забудьте добавить необходимые библиотеки в файл `platformio.ini`.

1. Библиотека ArduCam недоступна как библиотека Arduino, которую можно установить через файл `platformio.ini`. Вместо этого её нужно установить из исходного кода с их страницы на GitHub. Вы можете сделать это, либо:

    * Клонировав репозиторий с [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Перейдя на репозиторий на GitHub по адресу [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) и скачав код в виде zip-архива через кнопку **Code**

1. Вам нужна только папка `ArduCAM` из этого кода. Скопируйте всю папку в папку `lib` вашего проекта.

    > ⚠️ Важно скопировать всю папку, чтобы код находился в `lib/ArduCam`. Не копируйте только содержимое папки `ArduCam` в папку `lib`, скопируйте всю папку целиком.

1. Код библиотеки ArduCam работает с несколькими типами камер. Тип камеры, который вы хотите использовать, настраивается с помощью флагов компилятора — это позволяет уменьшить размер библиотеки, исключив код для камер, которые вы не используете. Чтобы настроить библиотеку для камеры OV2640, добавьте следующее в конец файла `platformio.ini`:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Это задает два флага компилятора:

      * `ARDUCAM_SHIELD_V2` — указывает библиотеке, что камера подключена к плате Arduino, известной как shield.
      * `OV2640_CAM` — указывает библиотеке включить только код для камеры OV2640.

1. Добавьте заголовочный файл в папку `src` с именем `camera.h`. Этот файл будет содержать код для взаимодействия с камерой. Добавьте в этот файл следующий код:

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

    Это низкоуровневый код, который настраивает камеру с использованием библиотек ArduCam и извлекает изображения по мере необходимости через шину SPI. Этот код специфичен для ArduCam, поэтому вам не нужно беспокоиться о том, как он работает на данном этапе.

1. В `main.cpp` добавьте следующий код под другими инструкциями `include`, чтобы включить этот новый файл и создать экземпляр класса камеры:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Это создает объект `Camera`, который сохраняет изображения в формате JPEG с разрешением 640x480. Хотя поддерживаются более высокие разрешения (до 3280x2464), классификатор изображений работает с гораздо меньшими изображениями (227x227), поэтому нет необходимости захватывать и отправлять изображения большего размера.

1. Добавьте следующий код ниже, чтобы определить функцию настройки камеры:

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

    Функция `setupCamera` начинает с настройки пина выбора чипа SPI (`PIN_SPI_SS`) как высокого, делая Wio Terminal контроллером SPI. Затем она запускает шины I2C и SPI. Наконец, она инициализирует класс камеры, который настраивает параметры сенсора камеры и проверяет правильность подключения.

1. Вызовите эту функцию в конце функции `setup`:

    ```cpp
    setupCamera();
    ```

1. Соберите и загрузите этот код, а затем проверьте вывод в последовательном мониторе. Если вы видите сообщение `Error setting up the camera!`, проверьте проводку, чтобы убедиться, что все кабели подключены к правильным пинам на ArduCam и GPIO-пинам на Wio Terminal, а также что все соединительные провода надежно закреплены.

## Захват изображения

Теперь Wio Terminal можно запрограммировать для захвата изображения при нажатии кнопки.

### Задание - захватите изображение

1. Микроконтроллеры выполняют ваш код непрерывно, поэтому сложно инициировать такие действия, как съемка фото, без реакции на датчик. У Wio Terminal есть кнопки, поэтому камеру можно настроить на срабатывание при нажатии одной из кнопок. Добавьте следующий код в конец функции `setup`, чтобы настроить кнопку C (одну из трех кнопок сверху, ближайшую к выключателю питания).

    ![Кнопка C сверху, ближайшая к выключателю питания](../../../../../translated_images/ru/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    Режим `INPUT_PULLUP` по сути инвертирует вход. Например, обычно кнопка отправляет низкий сигнал, когда не нажата, и высокий сигнал, когда нажата. При установке в режим `INPUT_PULLUP` она отправляет высокий сигнал, когда не нажата, и низкий сигнал, когда нажата.

1. Добавьте пустую функцию для реакции на нажатие кнопки перед функцией `loop`:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Вызовите эту функцию в методе `loop`, когда кнопка нажата:

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

    Этот код проверяет, нажата ли кнопка. Если она нажата, вызывается функция `buttonPressed`, и цикл задерживается на 2 секунды. Это позволяет кнопке быть отпущенной, чтобы длительное нажатие не регистрировалось дважды.

    > 💁 Кнопка на Wio Terminal настроена как `INPUT_PULLUP`, поэтому она отправляет высокий сигнал, когда не нажата, и низкий сигнал, когда нажата.

1. Добавьте следующий код в функцию `buttonPressed`:

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

    Этот код начинает захват изображения, вызывая `startCapture`. Аппаратное обеспечение камеры не возвращает данные сразу, когда вы их запрашиваете. Вместо этого вы отправляете команду на начало захвата, и камера работает в фоновом режиме, чтобы захватить изображение, преобразовать его в JPEG и сохранить в локальном буфере на самой камере. Вызов `captureReady` затем проверяет, завершен ли захват изображения.

    После завершения захвата данные изображения копируются из буфера камеры в локальный буфер (массив байтов) с помощью вызова `readImageToBuffer`. Длина буфера затем отправляется в последовательный монитор.

1. Соберите и загрузите этот код, а затем проверьте вывод в последовательном мониторе. Каждый раз, когда вы нажимаете кнопку C, изображение будет захвачено, и вы увидите размер изображения, отправленный в последовательный монитор.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Размеры разных изображений будут различаться. Они сжаты в формате JPEG, и размер файла JPEG для заданного разрешения зависит от содержимого изображения.

> 💁 Вы можете найти этот код в папке [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Вы успешно захватили изображения с помощью вашего Wio Terminal.

## Дополнительно - проверьте изображения камеры с помощью SD-карты

Самый простой способ увидеть изображения, захваченные камерой, — записать их на SD-карту в Wio Terminal, а затем просмотреть их на вашем компьютере. Выполните этот шаг, если у вас есть свободная microSD-карта и разъем для microSD-карт на вашем компьютере или адаптер.

Wio Terminal поддерживает только microSD-карты объемом до 16 ГБ. Если у вас карта большего объема, она не будет работать.

### Задание - проверьте изображения камеры с помощью SD-карты

1. Отформатируйте microSD-карту в формате FAT32 или exFAT, используя соответствующие приложения на вашем компьютере (Disk Utility на macOS, Проводник на Windows или командные инструменты в Linux).

1. Вставьте microSD-карту в разъем чуть ниже выключателя питания. Убедитесь, что она вставлена до конца, пока не щелкнет и не останется на месте. Возможно, вам потребуется надавить на неё ногтем или тонким инструментом.

1. Добавьте следующие инструкции `include` в начало файла `main.cpp`:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Добавьте следующую функцию перед функцией `setup`:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Эта функция настраивает SD-карту с использованием шины SPI.

1. Вызовите её из функции `setup`:

    ```cpp
    setupSDCard();
    ```

1. Добавьте следующий код выше функции `buttonPressed`:

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

    Это определяет глобальную переменную для подсчета файлов. Она используется для имен файлов изображений, чтобы можно было захватывать несколько изображений с увеличивающимися именами файлов — `1.jpg`, `2.jpg` и так далее.

    Затем определяется функция `saveToSDCard`, которая принимает буфер данных в байтах и длину буфера. Создается имя файла с использованием счетчика файлов, и счетчик увеличивается для следующего файла. Двоичные данные из буфера затем записываются в файл.

1. Вызовите функцию `saveToSDCard` из функции `buttonPressed`. Вызов должен быть **до** удаления буфера:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Соберите и загрузите этот код, а затем проверьте вывод в последовательном мониторе. Каждый раз, когда вы нажимаете кнопку C, изображение будет захвачено и сохранено на SD-карту.

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

1. Выключите питание, а затем извлеките microSD-карту, слегка нажав на неё и отпустив, чтобы она выскочила. Возможно, вам потребуется использовать тонкий инструмент для этого. Подключите microSD-карту к вашему компьютеру, чтобы просмотреть изображения.

    ![Фотография банана, сделанная с помощью ArduCam](../../../../../translated_images/ru/banana-arducam.be1b32d4267a8194.webp)
💁 Может потребоваться несколько изображений, чтобы баланс белого камеры настроился. Вы заметите это по цвету захваченных изображений, первые несколько могут выглядеть с искажением цвета. Вы всегда можете обойти это, изменив код для захвата нескольких изображений, которые игнорируются в функции `setup`.


---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Хотя мы стремимся к точности, пожалуйста, учитывайте, что автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его родном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникающие в результате использования данного перевода.