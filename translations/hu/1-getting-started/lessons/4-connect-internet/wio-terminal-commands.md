<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-27T22:11:05+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "hu"
}
-->
# Vezéreld az éjszakai fényedet az interneten keresztül - Wio Terminal

Ebben a leckében az MQTT broker által küldött parancsokra fogsz feliratkozni a Wio Terminal eszközödön.

## Parancsokra való feliratkozás

A következő lépés az, hogy feliratkozz az MQTT broker által küldött parancsokra, és reagálj rájuk.

### Feladat

Iratkozz fel a parancsokra.

1. Nyisd meg az éjszakai fény projektet a VS Code-ban.

1. Add hozzá az alábbi kódot a `config.h` fájl végéhez, hogy meghatározd a parancsokhoz tartozó témanevet:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    A `SERVER_COMMAND_TOPIC` az a téma, amelyre az eszköz feliratkozik, hogy LED parancsokat kapjon.

1. Add hozzá az alábbi sort a `reconnectMQTTClient` függvény végéhez, hogy feliratkozz a parancs témára, amikor az MQTT kliens újra csatlakozik:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Add hozzá az alábbi kódot a `reconnectMQTTClient` függvény alá.

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

    Ez a függvény lesz az a callback, amelyet az MQTT kliens hív meg, amikor üzenetet kap a szervertől.

    Az üzenet egy 8 bites egész számokból álló tömbként érkezik, ezért karaktertömbbé kell alakítani, hogy szövegként kezelhető legyen.

    Az üzenet egy JSON dokumentumot tartalmaz, amelyet az ArduinoJson könyvtár segítségével dekódolunk. A JSON dokumentum `led_on` tulajdonságát olvassuk ki, és az értéktől függően a LED bekapcsol vagy kikapcsol.

1. Add hozzá az alábbi kódot a `createMQTTClient` függvényhez:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Ez a kód beállítja a `clientCallback`-ot, mint azt a callback-et, amelyet az MQTT broker üzenet érkezésekor hív meg.

    > 💁 A `clientCallback` kezelő minden feliratkozott témához meghívásra kerül. Ha később olyan kódot írsz, amely több témát figyel, az üzenethez tartozó témát a callback függvény `topic` paraméteréből tudod lekérni.

1. Töltsd fel a kódot a Wio Terminal eszközödre, és használd a Serial Monitor-t, hogy lásd a fényerősség adatokat, amelyeket az MQTT brokernek küldesz.

1. Állítsd be a fizikai vagy virtuális eszközöd által érzékelt fényerősséget. Látni fogod, hogy üzenetek érkeznek és parancsok küldődnek a terminálban. A LED is bekapcsol vagy kikapcsol a fényerősségtől függően.

> 💁 Ezt a kódot megtalálod a [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) mappában.

😀 Sikeresen megírtad a kódot, amely lehetővé teszi az eszközöd számára, hogy reagáljon az MQTT broker parancsaira.

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.