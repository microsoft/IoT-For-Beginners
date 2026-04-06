# گرفتن تصویر - Wio Terminal

در این بخش از درس، شما یک دوربین به Wio Terminal خود اضافه می‌کنید و تصاویر را از آن ثبت می‌کنید.

## سخت‌افزار

Wio Terminal به یک دوربین نیاز دارد.

دوربینی که استفاده می‌کنید [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/) است. این یک دوربین ۲ مگاپیکسلی است که بر اساس حسگر تصویر OV2640 ساخته شده است. این دوربین از طریق رابط SPI برای ثبت تصاویر ارتباط برقرار می‌کند و از I2C برای پیکربندی حسگر استفاده می‌کند.

## اتصال دوربین

ArduCam سوکت Grove ندارد و به جای آن از طریق پین‌های GPIO روی Wio Terminal به باس‌های SPI و I2C متصل می‌شود.

### وظیفه - اتصال دوربین

دوربین را متصل کنید.

![یک حسگر ArduCam](../../../../../translated_images/fa/arducam.20e4e4cbb2682965.webp)

1. پین‌های پایه ArduCam باید به پین‌های GPIO روی Wio Terminal متصل شوند. برای راحت‌تر پیدا کردن پین‌های درست، برچسب پین GPIO که همراه Wio Terminal است را دور پین‌ها بچسبانید:

    ![Wio Terminal با برچسب پین GPIO](../../../../../translated_images/fa/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. با استفاده از سیم‌های جامپر، اتصالات زیر را انجام دهید:

    | پین ArduCAM | پین Wio Terminal | توضیحات                                  |
    | ----------- | ---------------- | ---------------------------------------- |
    | CS          | 24 (SPI_CS)      | انتخاب تراشه SPI                         |
    | MOSI        | 19 (SPI_MOSI)    | خروجی کنترلر SPI، ورودی جانبی            |
    | MISO        | 21 (SPI_MISO)    | ورودی کنترلر SPI، خروجی جانبی            |
    | SCK         | 23 (SPI_SCLK)    | ساعت سریال SPI                           |
    | GND         | 6 (GND)          | زمین - ۰ ولت                             |
    | VCC         | 4 (5V)           | منبع تغذیه ۵ ولت                         |
    | SDA         | 3 (I2C1_SDA)     | داده سریال I2C                           |
    | SCL         | 5 (I2C1_SCL)     | ساعت سریال I2C                           |

    ![Wio Terminal متصل به ArduCam با سیم‌های جامپر](../../../../../translated_images/fa/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.webp)

    اتصالات GND و VCC منبع تغذیه ۵ ولت را به ArduCam ارائه می‌دهند. این دوربین با ۵ ولت کار می‌کند، برخلاف حسگرهای Grove که با ۳ ولت کار می‌کنند. این توان مستقیماً از اتصال USB-C که دستگاه را تغذیه می‌کند تأمین می‌شود.

    > 💁 برای اتصال SPI، برچسب‌های پین روی ArduCam و نام‌های پین Wio Terminal که در کد استفاده می‌شوند همچنان از نام‌گذاری قدیمی استفاده می‌کنند. دستورالعمل‌های این درس از نام‌گذاری جدید استفاده می‌کنند، مگر زمانی که نام پین‌ها در کد استفاده شوند.

1. اکنون می‌توانید Wio Terminal را به کامپیوتر خود متصل کنید.

## برنامه‌ریزی دستگاه برای اتصال به دوربین

اکنون می‌توانید Wio Terminal را برای استفاده از دوربین ArduCAM متصل شده برنامه‌ریزی کنید.

### وظیفه - برنامه‌ریزی دستگاه برای اتصال به دوربین

1. یک پروژه جدید Wio Terminal با استفاده از PlatformIO ایجاد کنید. این پروژه را `fruit-quality-detector` بنامید. کدی در تابع `setup` اضافه کنید تا پورت سریال را پیکربندی کند.

1. کدی برای اتصال به WiFi اضافه کنید، با اطلاعات WiFi خود در فایلی به نام `config.h`. فراموش نکنید که کتابخانه‌های مورد نیاز را به فایل `platformio.ini` اضافه کنید.

1. کتابخانه ArduCam به عنوان یک کتابخانه Arduino که می‌توان از فایل `platformio.ini` نصب کرد در دسترس نیست. در عوض باید از منبع آن در صفحه GitHub نصب شود. می‌توانید این کار را به یکی از روش‌های زیر انجام دهید:

    * کلون کردن مخزن از [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * رفتن به مخزن در GitHub در [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) و دانلود کد به صورت یک فایل zip از دکمه **Code**

1. شما فقط به پوشه `ArduCAM` از این کد نیاز دارید. کل پوشه را به پوشه `lib` در پروژه خود کپی کنید.

    > ⚠️ کل پوشه باید کپی شود، بنابراین کد در `lib/ArduCam` قرار گیرد. فقط محتوای پوشه `ArduCam` را به پوشه `lib` کپی نکنید، بلکه کل پوشه را منتقل کنید.

1. کد کتابخانه ArduCam برای انواع مختلف دوربین کار می‌کند. نوع دوربینی که می‌خواهید استفاده کنید با استفاده از فلگ‌های کامپایلر پیکربندی می‌شود - این کار باعث می‌شود کتابخانه ساخته شده تا حد ممکن کوچک باشد و کد مربوط به دوربین‌هایی که استفاده نمی‌کنید حذف شود. برای پیکربندی کتابخانه برای دوربین OV2640، موارد زیر را به انتهای فایل `platformio.ini` اضافه کنید:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    این دو فلگ کامپایلر را تنظیم می‌کند:

      * `ARDUCAM_SHIELD_V2` برای اطلاع دادن به کتابخانه که دوربین روی یک برد Arduino است، که به عنوان یک شیلد شناخته می‌شود.
      * `OV2640_CAM` برای اطلاع دادن به کتابخانه که فقط کد مربوط به دوربین OV2640 را شامل شود.

1. یک فایل هدر به نام `camera.h` به پوشه `src` اضافه کنید. این فایل شامل کدی برای ارتباط با دوربین خواهد بود. کد زیر را به این فایل اضافه کنید:

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

    این کد سطح پایین دوربین را با استفاده از کتابخانه‌های ArduCam پیکربندی می‌کند و تصاویر را در صورت نیاز با استفاده از باس SPI استخراج می‌کند. این کد بسیار خاص ArduCam است، بنابراین نیازی نیست در این مرحله نگران نحوه کار آن باشید.

1. در `main.cpp`، کد زیر را زیر سایر دستورات `include` اضافه کنید تا این فایل جدید را شامل شود و یک نمونه از کلاس دوربین ایجاد کنید:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    این یک `Camera` ایجاد می‌کند که تصاویر را به صورت JPEG با وضوح 640 در 480 ذخیره می‌کند. اگرچه وضوح‌های بالاتر پشتیبانی می‌شوند (تا 3280x2464)، اما طبقه‌بندی‌کننده تصویر روی تصاویر بسیار کوچک‌تر (227x227) کار می‌کند، بنابراین نیازی به ثبت و ارسال تصاویر بزرگ‌تر نیست.

1. کد زیر را زیر این بخش اضافه کنید تا یک تابع برای راه‌اندازی دوربین تعریف شود:

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

    این تابع `setupCamera` با پیکربندی پین انتخاب تراشه SPI (`PIN_SPI_SS`) به عنوان بالا شروع می‌شود و Wio Terminal را به عنوان کنترلر SPI تنظیم می‌کند. سپس باس‌های I2C و SPI را راه‌اندازی می‌کند. در نهایت کلاس دوربین را مقداردهی اولیه می‌کند که تنظیمات حسگر دوربین را پیکربندی کرده و اطمینان حاصل می‌کند که همه چیز به درستی متصل شده است.

1. این تابع را در انتهای تابع `setup` فراخوانی کنید:

    ```cpp
    setupCamera();
    ```

1. کد را بسازید و آپلود کنید و خروجی مانیتور سریال را بررسی کنید. اگر پیام `Error setting up the camera!` را مشاهده کردید، اتصالات را بررسی کنید تا مطمئن شوید همه کابل‌ها پین‌های درست روی ArduCam را به پین‌های درست GPIO روی Wio Terminal متصل کرده‌اند و همه سیم‌های جامپر به درستی جا افتاده‌اند.

## ثبت تصویر

اکنون می‌توانید Wio Terminal را برای ثبت تصویر هنگام فشار دادن یک دکمه برنامه‌ریزی کنید.

### وظیفه - ثبت تصویر

1. میکروکنترلرها کد شما را به طور مداوم اجرا می‌کنند، بنابراین راه آسانی برای انجام عملی مانند گرفتن عکس بدون واکنش به یک حسگر وجود ندارد. Wio Terminal دکمه‌هایی دارد، بنابراین می‌توان دوربین را طوری تنظیم کرد که با یکی از دکمه‌ها فعال شود. کد زیر را به انتهای تابع `setup` اضافه کنید تا دکمه C (یکی از سه دکمه بالایی، نزدیک‌ترین دکمه به کلید پاور) پیکربندی شود.

    ![دکمه C در بالای دستگاه نزدیک کلید پاور](../../../../../translated_images/fa/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    حالت `INPUT_PULLUP` اساساً یک ورودی را معکوس می‌کند. به عنوان مثال، به طور معمول یک دکمه وقتی فشار داده نمی‌شود سیگنال پایین ارسال می‌کند و وقتی فشار داده می‌شود سیگنال بالا ارسال می‌کند. وقتی به `INPUT_PULLUP` تنظیم شود، وقتی فشار داده نمی‌شود سیگنال بالا ارسال می‌کند و وقتی فشار داده می‌شود سیگنال پایین ارسال می‌کند.

1. یک تابع خالی برای پاسخ به فشار دکمه قبل از تابع `loop` اضافه کنید:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. این تابع را در متد `loop` زمانی که دکمه فشار داده می‌شود فراخوانی کنید:

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

    این کلید بررسی می‌کند که آیا دکمه فشار داده شده است یا خیر. اگر فشار داده شده باشد، تابع `buttonPressed` فراخوانی می‌شود و حلقه به مدت ۲ ثانیه تأخیر می‌اندازد. این کار برای این است که زمان کافی برای رها شدن دکمه وجود داشته باشد تا یک فشار طولانی دوبار ثبت نشود.

    > 💁 دکمه روی Wio Terminal به `INPUT_PULLUP` تنظیم شده است، بنابراین وقتی فشار داده نمی‌شود سیگنال بالا ارسال می‌کند و وقتی فشار داده می‌شود سیگنال پایین ارسال می‌کند.

1. کد زیر را به تابع `buttonPressed` اضافه کنید:

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

    این کد با فراخوانی `startCapture` ثبت تصویر را آغاز می‌کند. سخت‌افزار دوربین به این صورت کار نمی‌کند که داده‌ها را هنگام درخواست بازگرداند، بلکه شما دستوری برای شروع ثبت ارسال می‌کنید و دوربین در پس‌زمینه کار می‌کند تا تصویر را ثبت کند، آن را به JPEG تبدیل کند و در یک بافر محلی روی خود دوربین ذخیره کند. سپس فراخوانی `captureReady` بررسی می‌کند که آیا ثبت تصویر به پایان رسیده است یا خیر.

    پس از اتمام ثبت، داده‌های تصویر با فراخوانی `readImageToBuffer` از بافر روی دوربین به یک بافر محلی (آرایه‌ای از بایت‌ها) کپی می‌شوند. طول بافر سپس به مانیتور سریال ارسال می‌شود.

1. کد را بسازید و آپلود کنید و خروجی را روی مانیتور سریال بررسی کنید. هر بار که دکمه C را فشار دهید، یک تصویر ثبت می‌شود و اندازه تصویر به مانیتور سریال ارسال می‌شود.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    تصاویر مختلف اندازه‌های متفاوتی خواهند داشت. آن‌ها به صورت JPEG فشرده شده‌اند و اندازه یک فایل JPEG برای یک وضوح مشخص به محتوای تصویر بستگی دارد.

> 💁 می‌توانید این کد را در پوشه [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal) پیدا کنید.

😀 شما با موفقیت تصاویر را با Wio Terminal خود ثبت کردید.

## اختیاری - بررسی تصاویر دوربین با استفاده از کارت SD

ساده‌ترین راه برای مشاهده تصاویری که توسط دوربین ثبت شده‌اند، نوشتن آن‌ها روی یک کارت SD در Wio Terminal و سپس مشاهده آن‌ها روی کامپیوتر است. این مرحله را انجام دهید اگر یک کارت microSD اضافی و یک سوکت کارت microSD در کامپیوتر خود یا یک آداپتور دارید.

Wio Terminal فقط از کارت‌های microSD با حداکثر ظرفیت 16GB پشتیبانی می‌کند. اگر کارت SD بزرگ‌تری دارید، کار نخواهد کرد.

### وظیفه - بررسی تصاویر دوربین با استفاده از کارت SD

1. یک کارت microSD را به صورت FAT32 یا exFAT با استفاده از برنامه‌های مربوطه روی کامپیوتر خود (Disk Utility در macOS، File Explorer در ویندوز، یا استفاده از ابزارهای خط فرمان در لینوکس) فرمت کنید.

1. کارت microSD را در سوکت زیر کلید پاور قرار دهید. مطمئن شوید که تا انتها وارد شده و کلیک کرده و در جای خود باقی می‌ماند. ممکن است نیاز باشد با ناخن یا یک ابزار نازک آن را فشار دهید.

1. دستورات `include` زیر را به بالای فایل `main.cpp` اضافه کنید:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. تابع زیر را قبل از تابع `setup` اضافه کنید:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    این تابع کارت SD را با استفاده از باس SPI پیکربندی می‌کند.

1. این تابع را از داخل تابع `setup` فراخوانی کنید:

    ```cpp
    setupSDCard();
    ```

1. کد زیر را بالای تابع `buttonPressed` اضافه کنید:

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

    این کد یک متغیر سراسری برای شمارش فایل تعریف می‌کند. این متغیر برای نام فایل‌های تصویر استفاده می‌شود تا چندین تصویر با نام‌های افزایشی ثبت شوند - `1.jpg`، `2.jpg` و به همین ترتیب.

    سپس تابع `saveToSDCard` تعریف می‌شود که یک بافر از داده‌های بایت و طول بافر را می‌گیرد. یک نام فایل با استفاده از شمارش فایل ایجاد می‌شود و شمارش فایل برای فایل بعدی افزایش می‌یابد. داده‌های باینری از بافر به فایل نوشته می‌شوند.

1. تابع `saveToSDCard` را از داخل تابع `buttonPressed` فراخوانی کنید. این فراخوانی باید **قبل از** حذف بافر باشد:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. کد را بسازید و آپلود کنید و خروجی را روی مانیتور سریال بررسی کنید. هر بار که دکمه C را فشار دهید، یک تصویر ثبت شده و روی کارت SD ذخیره می‌شود.

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

1. کارت microSD را خاموش کرده و با فشار دادن کمی و رها کردن آن را خارج کنید، و کارت بیرون می‌آید. ممکن است نیاز باشد از یک ابزار نازک برای این کار استفاده کنید. کارت microSD را به کامپیوتر خود متصل کنید تا تصاویر را مشاهده کنید.

    ![تصویری از یک موز که با استفاده از ArduCam ثبت شده است](../../../../../translated_images/fa/banana-arducam.be1b32d4267a8194.webp)
💁 ممکن است چند تصویر طول بکشد تا تراز سفیدی دوربین تنظیم شود. شما این را بر اساس رنگ تصاویر گرفته شده متوجه خواهید شد، چند تصویر اول ممکن است رنگ غیرعادی داشته باشند. شما همیشه می‌توانید با تغییر کد برای گرفتن چند تصویر که در تابع `setup` نادیده گرفته می‌شوند، این مشکل را حل کنید.


**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.