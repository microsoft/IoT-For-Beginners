<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-28T13:49:57+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "sr"
}
-->
# Контролишите своје ноћно светло преко интернета - Wio Terminal

IoT уређај треба да буде програмиран да комуницира са *test.mosquitto.org* користећи MQTT за слање телеметријских вредности са очитавањем сензора светлости и примање команди за контролу LED диоде.

У овом делу лекције, повезаћете свој Wio Terminal са MQTT брокером.

## Инсталирајте WiFi и MQTT Arduino библиотеке

Да бисте комуницирали са MQTT брокером, потребно је да инсталирате неке Arduino библиотеке које омогућавају коришћење WiFi чипа у Wio Terminal-у и комуникацију преко MQTT-а. Приликом развоја за Arduino уређаје, можете користити широк спектар библиотека које садрже отворени код и имплементирају велики број функционалности. Seeed објављује библиотеке за Wio Terminal које омогућавају комуникацију преко WiFi-а. Други програмери су објавили библиотеке за комуникацију са MQTT брокерима, и користићете их са својим уређајем.

Ове библиотеке су доступне као изворни код који се може аутоматски увозити у PlatformIO и компајлирати за ваш уређај. На овај начин Arduino библиотеке ће радити на било ком уређају који подржава Arduino оквир, под условом да уређај има специфичан хардвер који је потребан за ту библиотеку. Неке библиотеке, као што су Seeed WiFi библиотеке, специфичне су за одређени хардвер.

Библиотеке се могу инсталирати глобално и компајлирати ако је потребно, или у одређени пројекат. За овај задатак, библиотеке ће бити инсталиране у пројекат.

✅ Можете сазнати више о управљању библиотекама и како да пронађете и инсталирате библиотеке у [PlatformIO документацији о библиотекама](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Задатак - инсталирајте WiFi и MQTT Arduino библиотеке

Инсталирајте Arduino библиотеке.

1. Отворите пројекат ноћног светла у VS Code-у.

1. Додајте следеће на крај `platformio.ini` датотеке:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Ово увози Seeed WiFi библиотеке. Синтакса `@ <number>` се односи на одређени број верзије библиотеке.

    > 💁 Можете уклонити `@ <number>` да увек користите најновију верзију библиотека, али нема гаранција да ће новије верзије радити са кодом испод. Код овде је тестиран са овом верзијом библиотека.

    Ово је све што треба да урадите да бисте додали библиотеке. Следећи пут када PlatformIO компајлира пројекат, преузеће изворни код за ове библиотеке и компајлирати га у ваш пројекат.

1. Додајте следеће у `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Ово увози [PubSubClient](https://github.com/knolleary/pubsubclient), Arduino MQTT клијент.

## Повежите се на WiFi

Wio Terminal сада може бити повезан на WiFi.

### Задатак - повежите се на WiFi

Повежите Wio Terminal на WiFi.

1. Направите нову датотеку у `src` фолдеру под називом `config.h`. Можете то урадити тако што ћете изабрати `src` фолдер или `main.cpp` датотеку унутар њега, и изабрати дугме **New file** из експлорера. Ово дугме се појављује само када је ваш курсор изнад експлорера.

    ![Дугме за нову датотеку](../../../../../translated_images/sr/vscode-new-file-button.182702340fe6723c.png)

1. Додајте следећи код у ову датотеку да дефинишете константе за своје WiFi акредитиве:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Замените `<SSID>` са SSID-ом вашег WiFi-а. Замените `<PASSWORD>` са лозинком вашег WiFi-а.

1. Отворите `main.cpp` датотеку.

1. Додајте следеће `#include` директиве на врх датотеке:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Ово укључује хедер датотеке за библиотеке које сте раније додали, као и хедер датотеку за конфигурацију. Ове хедер датотеке су потребне да би PlatformIO увео код из библиотека. Без експлицитног укључивања ових хедер датотека, неки код неће бити компајлиран и добићете грешке компајлера.

1. Додајте следећи код изнад `setup` функције:

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

    Овај код петља док уређај није повезан на WiFi и покушава да се повеже користећи SSID и лозинку из хедер датотеке за конфигурацију.

1. Додајте позив овој функцији на крају `setup` функције, након што су пинови конфигурисани.

    ```cpp
    connectWiFi();
    ```

1. Учитајте овај код на свој уређај да проверите да ли WiFi веза ради. Требало би да видите ово у серијском монитору.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Повежите се на MQTT

Када је Wio Terminal повезан на WiFi, може се повезати на MQTT брокер.

### Задатак - повежите се на MQTT

Повежите се на MQTT брокер.

1. Додајте следећи код на крај `config.h` датотеке да дефинишете детаље везе за MQTT брокер:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Замените `<ID>` са јединственим ID-ом који ће се користити као име овог клијента уређаја, а касније и за теме које овај уређај објављује и на које се претплаћује. *test.mosquitto.org* брокер је јавни и користи га много људи, укључујући друге студенте који раде на овом задатку. Имање јединственог имена MQTT клијента и имена тема осигурава да ваш код неће бити у сукобу са кодом других.

    > 💁 Можете користити веб-сајт као што је [GUIDGen](https://www.guidgen.com) да генеришете јединствени ID.

    `BROKER` је URL MQTT брокера.

    `CLIENT_NAME` је јединствено име за овај MQTT клијент на брокеру.

1. Отворите `main.cpp` датотеку и додајте следећи код испод `connectWiFi` функције и изнад `setup` функције:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Овај код креира WiFi клијент користећи Wio Terminal WiFi библиотеке и користи га за креирање MQTT клијента.

1. Испод овог кода, додајте следеће:

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

    Ова функција тестира везу са MQTT брокером и поново се повезује ако није повезан. Петља све време док није повезан и покушава да се повеже користећи јединствено име клијента дефинисано у хедер датотеци за конфигурацију.

    Ако веза не успе, поново покушава након 5 секунди.

1. Додајте следећи код испод `reconnectMQTTClient` функције:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Овај код поставља MQTT брокер за клијента, као и подешавање callback-а када се порука прими. Затим покушава да се повеже на брокер.

1. Позовите `createMQTTClient` функцију у `setup` функцији након што је WiFi повезан.

1. Замените целу `loop` функцију следећим:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Овај код почиње поновним повезивањем на MQTT брокер. Ове везе се лако прекидају, па је вредно редовно проверавати и поново се повезивати ако је потребно. Затим позива `loop` метод на MQTT клијенту да обради све поруке које стижу на тему на коју је претплаћен. Ова апликација је једнонишка, па поруке не могу бити примљене у позадинском нишу, те је потребно одвојити време на главном нишу за обраду порука које чекају на мрежној вези.

    На крају, кашњење од 2 секунде осигурава да се нивои светлости не шаљу пречесто и смањује потрошњу енергије уређаја.

1. Учитајте код на свој Wio Terminal и користите серијски монитор да видите како се уређај повезује на WiFi и MQTT.

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

> 💁 Овај код можете пронаћи у [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) фолдеру.

😀 Успешно сте повезали свој уређај на MQTT брокер.

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.