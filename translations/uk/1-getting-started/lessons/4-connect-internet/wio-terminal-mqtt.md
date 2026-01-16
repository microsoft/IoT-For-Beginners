<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-28T17:11:14+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "uk"
}
-->
# Керуйте нічником через Інтернет - Wio Terminal

Пристрій IoT потрібно запрограмувати для зв’язку з *test.mosquitto.org* за допомогою MQTT, щоб надсилати телеметричні дані зі значеннями датчика освітлення та отримувати команди для керування світлодіодом.

У цій частині уроку ви підключите свій Wio Terminal до брокера MQTT.

## Встановлення бібліотек WiFi та MQTT для Arduino

Для зв’язку з брокером MQTT необхідно встановити кілька бібліотек Arduino, щоб використовувати WiFi-чип у Wio Terminal і взаємодіяти з MQTT. Під час розробки для пристроїв Arduino ви можете використовувати широкий спектр бібліотек, які містять відкритий код і реалізують безліч функцій. Seeed публікує бібліотеки для Wio Terminal, які дозволяють йому працювати через WiFi. Інші розробники створили бібліотеки для зв’язку з брокерами MQTT, і ви будете використовувати їх із вашим пристроєм.

Ці бібліотеки надаються у вигляді вихідного коду, який можна автоматично імпортувати в PlatformIO і скомпілювати для вашого пристрою. Таким чином, бібліотеки Arduino працюватимуть на будь-якому пристрої, що підтримує фреймворк Arduino, за умови, що пристрій має необхідне апаратне забезпечення для цієї бібліотеки. Деякі бібліотеки, наприклад, бібліотеки Seeed WiFi, специфічні для певного обладнання.

Бібліотеки можна встановлювати глобально та компілювати за потреби або для конкретного проєкту. У цьому завданні бібліотеки будуть встановлені в проєкт.

✅ Ви можете дізнатися більше про керування бібліотеками та як знаходити й встановлювати їх у [документації PlatformIO щодо бібліотек](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Завдання - встановлення бібліотек WiFi та MQTT для Arduino

Встановіть бібліотеки Arduino.

1. Відкрийте проєкт нічника у VS Code.

1. Додайте наступне в кінець файлу `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Це імпортує бібліотеки Seeed WiFi. Синтаксис `@ <number>` вказує на конкретну версію бібліотеки.

    > 💁 Ви можете видалити `@ <number>`, щоб завжди використовувати останню версію бібліотек, але немає гарантії, що пізніші версії працюватимуть із кодом нижче. Код тут було протестовано з цією версією бібліотек.

    Це все, що потрібно зробити для додавання бібліотек. Наступного разу, коли PlatformIO збиратиме проєкт, він завантажить вихідний код цих бібліотек і скомпілює його у ваш проєкт.

1. Додайте наступне до `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Це імпортує [PubSubClient](https://github.com/knolleary/pubsubclient), клієнт MQTT для Arduino.

## Підключення до WiFi

Тепер Wio Terminal можна підключити до WiFi.

### Завдання - підключення до WiFi

Підключіть Wio Terminal до WiFi.

1. Створіть новий файл у папці `src` під назвою `config.h`. Ви можете зробити це, вибравши папку `src` або файл `main.cpp` всередині, і натиснувши кнопку **New file** в провіднику. Ця кнопка з’являється лише тоді, коли ваш курсор знаходиться над провідником.

    ![Кнопка створення нового файлу](../../../../../translated_images/uk/vscode-new-file-button.182702340fe6723c.png)

1. Додайте наступний код у цей файл, щоб визначити константи для ваших WiFi-облікових даних:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Замініть `<SSID>` на SSID вашої WiFi-мережі. Замініть `<PASSWORD>` на пароль вашої WiFi-мережі.

1. Відкрийте файл `main.cpp`.

1. Додайте наступні директиви `#include` у верхній частині файлу:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Це включає заголовкові файли для бібліотек, які ви додали раніше, а також файл конфігурації. Ці заголовкові файли потрібні, щоб PlatformIO підключив код із бібліотек. Без явного включення цих заголовкових файлів деякий код не буде скомпільовано, і ви отримаєте помилки компіляції.

1. Додайте наступний код вище функції `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Цей код виконує цикл, поки пристрій не підключиться до WiFi, і намагається підключитися, використовуючи SSID і пароль із заголовкового файлу конфігурації.

1. Додайте виклик цієї функції внизу функції `setup`, після налаштування пінів.

    ```cpp
    connectWiFi();
    ```

1. Завантажте цей код на ваш пристрій, щоб перевірити, чи працює підключення до WiFi. Ви повинні побачити це в серійному моніторі.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Підключення до MQTT

Після підключення Wio Terminal до WiFi він може підключитися до брокера MQTT.

### Завдання - підключення до MQTT

Підключіться до брокера MQTT.

1. Додайте наступний код у кінець файлу `config.h`, щоб визначити деталі підключення до брокера MQTT:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Замініть `<ID>` на унікальний ідентифікатор, який буде використовуватися як ім’я цього клієнта пристрою, а пізніше — для тем, які цей пристрій публікує та на які підписується. Брокер *test.mosquitto.org* є публічним і використовується багатьма людьми, включаючи інших студентів, які виконують це завдання. Наявність унікального імені клієнта MQTT і назв тем гарантує, що ваш код не конфліктуватиме з кодом інших.

    > 💁 Ви можете використовувати вебсайт, наприклад [GUIDGen](https://www.guidgen.com), щоб згенерувати унікальний ідентифікатор.

    `BROKER` — це URL брокера MQTT.

    `CLIENT_NAME` — унікальне ім’я для цього клієнта MQTT на брокері.

1. Відкрийте файл `main.cpp` і додайте наступний код нижче функції `connectWiFi` і вище функції `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Цей код створює WiFi-клієнт, використовуючи бібліотеки WiFi для Wio Terminal, і використовує його для створення клієнта MQTT.

1. Нижче цього коду додайте наступне:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Ця функція перевіряє підключення до брокера MQTT і повторно підключається, якщо з’єднання немає. Вона виконує цикл, поки з’єднання не буде встановлено, і намагається підключитися, використовуючи унікальне ім’я клієнта, визначене у файлі конфігурації.

    Якщо з’єднання не вдається, повторна спроба виконується через 5 секунд.

1. Додайте наступний код нижче функції `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Цей код встановлює брокера MQTT для клієнта, а також налаштовує зворотний виклик, коли отримується повідомлення. Потім він намагається підключитися до брокера.

1. Викличте функцію `createMQTTClient` у функції `setup` після підключення до WiFi.

1. Замініть весь вміст функції `loop` на наступний:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Цей код починає з повторного підключення до брокера MQTT. Такі з’єднання можуть легко перериватися, тому варто регулярно перевіряти та повторно підключатися за потреби. Потім викликається метод `loop` клієнта MQTT для обробки будь-яких повідомлень, які надходять у підписану тему. Цей застосунок є однопотоковим, тому повідомлення не можуть отримуватися у фоновому потоці, тому потрібно виділити час у головному потоці для обробки будь-яких повідомлень, які очікують на мережеве з’єднання.

    Нарешті, затримка в 2 секунди забезпечує, що рівні освітлення не надсилаються занадто часто, і зменшує споживання енергії пристроєм.

1. Завантажте код на ваш Wio Terminal і використовуйте серійний монітор, щоб побачити, як пристрій підключається до WiFi і MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Ви можете знайти цей код у папці [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Ви успішно підключили свій пристрій до брокера MQTT.

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.