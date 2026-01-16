<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T21:50:22+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "sv"
}
-->
# Styr din nattlampa över Internet - Wio Terminal

IoT-enheten behöver programmeras för att kommunicera med *test.mosquitto.org* via MQTT för att skicka telemetrivärden från ljussensorn och ta emot kommandon för att styra LED-lampan.

I den här delen av lektionen kommer du att ansluta din Wio Terminal till en MQTT-broker.

## Installera WiFi- och MQTT-bibliotek för Arduino

För att kommunicera med MQTT-brokern behöver du installera några Arduino-bibliotek för att använda WiFi-chippet i Wio Terminal och kommunicera med MQTT. När du utvecklar för Arduino-enheter kan du använda ett brett utbud av bibliotek som innehåller öppen källkod och implementerar en mängd olika funktioner. Seeed publicerar bibliotek för Wio Terminal som gör det möjligt att kommunicera via WiFi. Andra utvecklare har publicerat bibliotek för att kommunicera med MQTT-brokers, och du kommer att använda dessa med din enhet.

Dessa bibliotek tillhandahålls som källkod som kan importeras automatiskt till PlatformIO och kompileras för din enhet. På detta sätt fungerar Arduino-bibliotek på alla enheter som stöder Arduino-ramverket, förutsatt att enheten har den specifika hårdvara som biblioteket kräver. Vissa bibliotek, som Seeeds WiFi-bibliotek, är specifika för viss hårdvara.

Bibliotek kan installeras globalt och kompileras vid behov, eller i ett specifikt projekt. För denna uppgift kommer biblioteken att installeras i projektet.

✅ Du kan lära dig mer om bibliotekshantering och hur du hittar och installerar bibliotek i [PlatformIO:s biblioteksdokumentation](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Uppgift - installera WiFi- och MQTT-bibliotek för Arduino

Installera Arduino-biblioteken.

1. Öppna nattlampa-projektet i VS Code.

1. Lägg till följande i slutet av filen `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Detta importerar Seeeds WiFi-bibliotek. Syntaxen `@ <nummer>` hänvisar till ett specifikt versionsnummer av biblioteket.

    > 💁 Du kan ta bort `@ <nummer>` för att alltid använda den senaste versionen av biblioteken, men det finns inga garantier för att senare versioner fungerar med koden nedan. Koden här har testats med denna version av biblioteken.

    Detta är allt du behöver göra för att lägga till biblioteken. Nästa gång PlatformIO bygger projektet kommer det att ladda ner källkoden för dessa bibliotek och kompilera dem i ditt projekt.

1. Lägg till följande i `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Detta importerar [PubSubClient](https://github.com/knolleary/pubsubclient), en MQTT-klient för Arduino.

## Anslut till WiFi

Nu kan Wio Terminal anslutas till WiFi.

### Uppgift - anslut till WiFi

Anslut Wio Terminal till WiFi.

1. Skapa en ny fil i mappen `src` som heter `config.h`. Du kan göra detta genom att välja mappen `src` eller filen `main.cpp` inuti och klicka på knappen **New file** i utforskaren. Den här knappen visas bara när din markör är över utforskaren.

    ![Knappen för ny fil](../../../../../translated_images/sv/vscode-new-file-button.182702340fe6723c.webp)

1. Lägg till följande kod i den här filen för att definiera konstanter för dina WiFi-uppgifter:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Ersätt `<SSID>` med SSID för ditt WiFi. Ersätt `<PASSWORD>` med ditt WiFi-lösenord.

1. Öppna filen `main.cpp`.

1. Lägg till följande `#include`-direktiv högst upp i filen:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Detta inkluderar headerfiler för de bibliotek du lade till tidigare, samt config-headerfilen. Dessa headerfiler behövs för att tala om för PlatformIO att inkludera koden från biblioteken. Utan att uttryckligen inkludera dessa headerfiler kommer viss kod inte att kompileras och du får kompileringsfel.

1. Lägg till följande kod ovanför funktionen `setup`:

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

    Den här koden loopar medan enheten inte är ansluten till WiFi och försöker ansluta med SSID och lösenord från config-headerfilen.

1. Lägg till ett anrop till den här funktionen längst ner i funktionen `setup`, efter att pinnarna har konfigurerats.

    ```cpp
    connectWiFi();
    ```

1. Ladda upp den här koden till din enhet för att kontrollera att WiFi-anslutningen fungerar. Du bör se detta i seriemonitorn.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Anslut till MQTT

När Wio Terminal är ansluten till WiFi kan den ansluta till MQTT-brokern.

### Uppgift - anslut till MQTT

Anslut till MQTT-brokern.

1. Lägg till följande kod längst ner i filen `config.h` för att definiera anslutningsdetaljer för MQTT-brokern:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Ersätt `<ID>` med ett unikt ID som kommer att användas som namn för den här enhetsklienten och senare för de ämnen som den här enheten publicerar och prenumererar på. MQTT-brokern *test.mosquitto.org* är offentlig och används av många människor, inklusive andra studenter som arbetar med denna uppgift. Att ha ett unikt MQTT-klientnamn och ämnesnamn säkerställer att din kod inte krockar med någon annans. Du kommer också att behöva detta ID när du skapar serverkoden senare i uppgiften.

    > 💁 Du kan använda en webbplats som [GUIDGen](https://www.guidgen.com) för att generera ett unikt ID.

    `BROKER` är URL:en till MQTT-brokern.

    `CLIENT_NAME` är ett unikt namn för den här MQTT-klienten på brokern.

1. Öppna filen `main.cpp` och lägg till följande kod under funktionen `connectWiFi` och ovanför funktionen `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Den här koden skapar en WiFi-klient med hjälp av Wio Terminals WiFi-bibliotek och använder den för att skapa en MQTT-klient.

1. Lägg till följande kod under detta:

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

    Den här funktionen testar anslutningen till MQTT-brokern och återansluter om den inte är ansluten. Den loopar hela tiden medan den inte är ansluten och försöker ansluta med det unika klientnamnet som definierats i config-headerfilen.

    Om anslutningen misslyckas försöker den igen efter 5 sekunder.

1. Lägg till följande kod under funktionen `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Den här koden ställer in MQTT-brokern för klienten samt konfigurerar callback-funktionen när ett meddelande tas emot. Den försöker sedan ansluta till brokern.

1. Anropa funktionen `createMQTTClient` i funktionen `setup` efter att WiFi är anslutet.

1. Ersätt hela funktionen `loop` med följande:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Den här koden börjar med att återansluta till MQTT-brokern. Dessa anslutningar kan lätt brytas, så det är värt att regelbundet kontrollera och återansluta vid behov. Den anropar sedan metoden `loop` på MQTT-klienten för att bearbeta eventuella meddelanden som kommer in på det ämne som prenumereras på. Den här appen är enkeltrådad, så meddelanden kan inte tas emot i en bakgrundstråd, därför måste tid på huvudtråden avsättas för att bearbeta eventuella meddelanden som väntar på nätverksanslutningen.

    Slutligen säkerställer en fördröjning på 2 sekunder att ljusnivåerna inte skickas för ofta och minskar enhetens strömförbrukning.

1. Ladda upp koden till din Wio Terminal och använd seriemonitorn för att se enheten ansluta till WiFi och MQTT.

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

> 💁 Du kan hitta den här koden i mappen [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Du har framgångsrikt anslutit din enhet till en MQTT-broker.

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.