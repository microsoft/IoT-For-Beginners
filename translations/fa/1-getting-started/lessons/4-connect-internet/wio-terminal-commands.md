<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-25T22:01:49+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "fa"
}
-->
# کنترل چراغ خواب خود از طریق اینترنت - Wio Terminal

در این بخش از درس، شما به دستورات ارسال شده از یک MQTT broker به Wio Terminal خود اشتراک خواهید داد.

## اشتراک در دستورات

مرحله بعدی اشتراک در دستورات ارسال شده از MQTT broker و پاسخ دادن به آنها است.

### وظیفه

اشتراک در دستورات.

1. پروژه چراغ خواب را در VS Code باز کنید.

1. کد زیر را به انتهای فایل `config.h` اضافه کنید تا نام موضوع برای دستورات تعریف شود:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` موضوعی است که دستگاه برای دریافت دستورات LED به آن اشتراک خواهد داد.

1. خط زیر را به انتهای تابع `reconnectMQTTClient` اضافه کنید تا هنگام اتصال مجدد MQTT client به موضوع دستورات اشتراک داده شود:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. کد زیر را زیر تابع `reconnectMQTTClient` اضافه کنید.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    این تابع به عنوان callback توسط MQTT client فراخوانی می‌شود زمانی که پیامی از سرور دریافت می‌کند.

    پیام به صورت آرایه‌ای از اعداد صحیح ۸ بیتی بدون علامت دریافت می‌شود، بنابراین باید به آرایه‌ای از کاراکترها تبدیل شود تا به عنوان متن پردازش شود.

    پیام شامل یک سند JSON است و با استفاده از کتابخانه ArduinoJson رمزگشایی می‌شود. ویژگی `led_on` از سند JSON خوانده می‌شود و بسته به مقدار آن LED روشن یا خاموش می‌شود.

1. کد زیر را به تابع `createMQTTClient` اضافه کنید:

    ```cpp
    client.setCallback(clientCallback);
    ```

    این کد `clientCallback` را به عنوان callback تنظیم می‌کند تا زمانی که پیامی از MQTT broker دریافت شود فراخوانی شود.

    > 💁 هندلر `clientCallback` برای تمام موضوعاتی که به آنها اشتراک داده شده فراخوانی می‌شود. اگر بعداً کدی بنویسید که به چندین موضوع گوش دهد، می‌توانید موضوعی که پیام به آن ارسال شده را از پارامتر `topic` که به تابع callback ارسال می‌شود دریافت کنید.

1. کد را به Wio Terminal خود آپلود کنید و از Serial Monitor برای مشاهده سطح نور ارسال شده به MQTT broker استفاده کنید.

1. سطح نور تشخیص داده شده توسط دستگاه فیزیکی یا مجازی خود را تنظیم کنید. خواهید دید که پیام‌ها دریافت می‌شوند و دستورات در ترمینال ارسال می‌شوند. همچنین خواهید دید که LED بسته به سطح نور روشن و خاموش می‌شود.

> 💁 می‌توانید این کد را در پوشه [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) پیدا کنید.

😀 شما با موفقیت دستگاه خود را برای پاسخ دادن به دستورات از یک MQTT broker کدنویسی کردید.

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.