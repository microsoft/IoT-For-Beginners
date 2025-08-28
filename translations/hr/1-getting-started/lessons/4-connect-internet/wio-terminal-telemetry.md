<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T13:53:21+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "hr"
}
-->
# Kontrolirajte svoju noćnu lampu putem Interneta - Wio Terminal

U ovom dijelu lekcije, slat ćete telemetriju s razinama svjetlosti s vašeg Wio Terminala na MQTT posrednika.

## Instalirajte JSON Arduino biblioteke

Popularan način za slanje poruka putem MQTT-a je korištenje JSON-a. Postoji Arduino biblioteka za JSON koja olakšava čitanje i pisanje JSON dokumenata.

### Zadatak

Instalirajte Arduino JSON biblioteku.

1. Otvorite projekt noćne lampe u VS Code-u.

1. Dodajte sljedeći redak kao dodatnu stavku u popis `lib_deps` u datoteci `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Ovo uvozi [ArduinoJson](https://arduinojson.org), Arduino biblioteku za JSON.

## Objavite telemetriju

Sljedeći korak je kreiranje JSON dokumenta s telemetrijom i slanje istog na MQTT posrednika.

### Zadatak - objavite telemetriju

Objavite telemetriju na MQTT posrednika.

1. Dodajte sljedeći kod na dno datoteke `config.h` kako biste definirali naziv teme za telemetriju za MQTT posrednika:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` je tema na koju će uređaj objavljivati razine svjetlosti.

1. Otvorite datoteku `main.cpp`.

1. Dodajte sljedeću `#include` direktivu na vrh datoteke:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Dodajte sljedeći kod unutar funkcije `loop`, neposredno prije `delay`:

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

    Ovaj kod očitava razinu svjetlosti i kreira JSON dokument koristeći ArduinoJson koji sadrži tu razinu. Zatim se taj dokument serijalizira u string i objavljuje na MQTT temi za telemetriju putem MQTT klijenta.

1. Prenesite kod na svoj Wio Terminal i koristite Serijski Monitor kako biste vidjeli razine svjetlosti koje se šalju na MQTT posrednika.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Uspješno ste poslali telemetriju s vašeg uređaja.

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za kritične informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.