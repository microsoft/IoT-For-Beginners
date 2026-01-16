<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-28T10:12:14+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "bg"
}
-->
# Контролирайте нощната си лампа през Интернет - Wio Terminal

IoT устройството трябва да бъде програмирано да комуникира с *test.mosquitto.org* чрез MQTT, за да изпраща телеметрични стойности с показанията на светлинния сензор и да получава команди за управление на LED.

В тази част от урока ще свържете вашия Wio Terminal към MQTT брокер.

## Инсталирайте WiFi и MQTT Arduino библиотеки

За да комуникирате с MQTT брокера, трябва да инсталирате някои Arduino библиотеки, които да използват WiFi чипа в Wio Terminal и да комуникират с MQTT. При разработка за Arduino устройства можете да използвате широк набор от библиотеки, които съдържат отворен код и реализират огромен набор от функционалности. Seeed публикува библиотеки за Wio Terminal, които му позволяват да комуникира чрез WiFi. Други разработчици са публикували библиотеки за комуникация с MQTT брокери, и вие ще използвате тези библиотеки с вашето устройство.

Тези библиотеки се предоставят като изходен код, който може да бъде автоматично импортиран в PlatformIO и компилиран за вашето устройство. По този начин Arduino библиотеките ще работят на всяко устройство, което поддържа Arduino framework, при условие че устройството има специфичен хардуер, необходим за тази библиотека. Някои библиотеки, като Seeed WiFi библиотеките, са специфични за определен хардуер.

Библиотеките могат да бъдат инсталирани глобално и компилирани при нужда или в конкретен проект. За тази задача библиотеките ще бъдат инсталирани в проекта.

✅ Можете да научите повече за управлението на библиотеки и как да намерите и инсталирате библиотеки в [документацията за библиотечния мениджър на PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Задача - инсталирайте WiFi и MQTT Arduino библиотеки

Инсталирайте Arduino библиотеките.

1. Отворете проекта за нощната лампа в VS Code.

1. Добавете следното в края на файла `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Това импортира Seeed WiFi библиотеките. Синтаксисът `@ <number>` се отнася до конкретна версия на библиотеката.

    > 💁 Можете да премахнете `@ <number>`, за да използвате винаги най-новата версия на библиотеките, но няма гаранция, че по-късните версии ще работят с кода по-долу. Кодът тук е тестван с тази версия на библиотеките.

    Това е всичко, което трябва да направите, за да добавите библиотеките. Следващия път, когато PlatformIO компилира проекта, ще изтегли изходния код за тези библиотеки и ще го компилира в проекта ви.

1. Добавете следното към `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Това импортира [PubSubClient](https://github.com/knolleary/pubsubclient), Arduino MQTT клиент.

## Свързване към WiFi

Wio Terminal вече може да бъде свързан към WiFi.

### Задача - свържете се към WiFi

Свържете Wio Terminal към WiFi.

1. Създайте нов файл в папката `src`, наречен `config.h`. Можете да направите това, като изберете папката `src` или файла `main.cpp` вътре и натиснете бутона **New file** от explorer. Този бутон се появява само когато курсорът ви е върху explorer.

    ![Бутон за нов файл](../../../../../translated_images/bg/vscode-new-file-button.182702340fe6723c.png)

1. Добавете следния код в този файл, за да дефинирате константи за вашите WiFi идентификационни данни:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Заменете `<SSID>` с SSID на вашия WiFi. Заменете `<PASSWORD>` с паролата за вашия WiFi.

1. Отворете файла `main.cpp`.

1. Добавете следните `#include` директиви в горната част на файла:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Това включва header файлове за библиотеките, които добавихте по-рано, както и header файла за конфигурация. Тези header файлове са необходими, за да кажат на PlatformIO да включи кода от библиотеките. Без изрично включване на тези header файлове, част от кода няма да бъде компилиран и ще получите грешки при компилация.

1. Добавете следния код над функцията `setup`:

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

    Този код се изпълнява, докато устройството не е свързано към WiFi, и се опитва да се свърже, използвайки SSID и паролата от header файла за конфигурация.

1. Добавете извикване на тази функция в долната част на функцията `setup`, след като пиновете са конфигурирани.

    ```cpp
    connectWiFi();
    ```

1. Качете този код на вашето устройство, за да проверите дали WiFi връзката работи. Трябва да видите това в серийния монитор.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Свързване към MQTT

След като Wio Terminal е свързан към WiFi, той може да се свърже към MQTT брокера.

### Задача - свържете се към MQTT

Свържете се към MQTT брокера.

1. Добавете следния код в долната част на файла `config.h`, за да дефинирате детайлите за връзка с MQTT брокера:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Заменете `<ID>` с уникален идентификатор, който ще се използва като име на този клиент на устройството и по-късно за темите, които това устройство публикува и на които се абонира. Брокерът *test.mosquitto.org* е публичен и се използва от много хора, включително други студенти, които работят по това задание. Уникалното име на MQTT клиента и имената на темите гарантират, че вашият код няма да се сблъска с този на други хора. Ще ви е необходим този идентификатор и когато създавате сървърния код по-късно в това задание.

    > 💁 Можете да използвате уебсайт като [GUIDGen](https://www.guidgen.com), за да генерирате уникален идентификатор.

    `BROKER` е URL адресът на MQTT брокера.

    `CLIENT_NAME` е уникално име за този MQTT клиент на брокера.

1. Отворете файла `main.cpp` и добавете следния код под функцията `connectWiFi` и над функцията `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Този код създава WiFi клиент, използвайки WiFi библиотеките на Wio Terminal, и го използва за създаване на MQTT клиент.

1. Под този код добавете следното:

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

    Тази функция тества връзката с MQTT брокера и се свързва отново, ако не е свързана. Тя се изпълнява постоянно, докато не е свързана, и се опитва да се свърже, използвайки уникалното име на клиента, дефинирано в header файла за конфигурация.

    Ако връзката се провали, тя се опитва отново след 5 секунди.

1. Добавете следния код под функцията `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Този код задава MQTT брокера за клиента, както и настройва callback функцията, когато се получи съобщение. След това се опитва да се свърже с брокера.

1. Извикайте функцията `createMQTTClient` във функцията `setup`, след като WiFi е свързан.

1. Заменете цялата функция `loop` със следното:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Този код започва с повторно свързване към MQTT брокера. Тези връзки могат лесно да бъдат прекъснати, затова е добре редовно да се проверява и свързва отново, ако е необходимо. След това извиква метода `loop` на MQTT клиента, за да обработи всички съобщения, които идват на темата, на която е абониран. Това приложение е еднопоточково, така че съобщенията не могат да бъдат получени на фонов поток, затова трябва да се отдели време на основния поток за обработка на всички съобщения, които чакат на мрежовата връзка.

    Накрая, забавяне от 2 секунди гарантира, че нивата на светлина не се изпращат твърде често и намалява консумацията на енергия на устройството.

1. Качете кода на вашия Wio Terminal и използвайте серийния монитор, за да видите устройството, което се свързва към WiFi и MQTT.

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

> 💁 Можете да намерите този код в папката [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Успешно свързахте вашето устройство към MQTT брокер.

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия роден език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален човешки превод. Ние не носим отговорност за недоразумения или погрешни интерпретации, произтичащи от използването на този превод.