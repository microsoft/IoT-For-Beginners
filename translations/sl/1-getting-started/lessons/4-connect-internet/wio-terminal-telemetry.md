<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T13:53:32+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "sl"
}
-->
# Nadzorujte svojo nočno lučko prek interneta - Wio Terminal

V tem delu lekcije boste pošiljali telemetrijo z ravnmi svetlobe iz svojega Wio Terminala na MQTT strežnik.

## Namestite knjižnice JSON za Arduino

Priljubljen način pošiljanja sporočil prek MQTT je uporaba JSON. Obstaja knjižnica za Arduino, ki olajša branje in pisanje JSON dokumentov.

### Naloga

Namestite knjižnico Arduino JSON.

1. Odprite projekt nočne lučke v VS Code.

1. Dodajte naslednjo vrstico v seznam `lib_deps` v datoteki `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    To uvozi [ArduinoJson](https://arduinojson.org), knjižnico JSON za Arduino.

## Objavite telemetrijo

Naslednji korak je ustvariti JSON dokument s telemetrijo in ga poslati na MQTT strežnik.

### Naloga - objavite telemetrijo

Objavite telemetrijo na MQTT strežnik.

1. Dodajte naslednjo kodo na dno datoteke `config.h`, da določite ime teme za telemetrijo na MQTT strežniku:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` je tema, na katero bo naprava objavljala ravni svetlobe.

1. Odprite datoteko `main.cpp`.

1. Dodajte naslednjo direktivo `#include` na vrh datoteke:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Dodajte naslednjo kodo znotraj funkcije `loop`, tik pred `delay`:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    Ta koda prebere raven svetlobe in ustvari JSON dokument z uporabo ArduinoJson, ki vsebuje to raven. Nato se dokument serializira v niz in objavi na telemetrijski MQTT temi prek MQTT odjemalca.

1. Naložite kodo na svoj Wio Terminal in uporabite Serial Monitor, da vidite ravni svetlobe, ki se pošiljajo na MQTT strežnik.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 To kodo lahko najdete v mapi [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Uspešno ste poslali telemetrijo iz svoje naprave.

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za strojno prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo strokovno človeško prevajanje. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki izhajajo iz uporabe tega prevoda.