<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T10:14:15+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "ro"
}
-->
# Controlează lumina de noapte prin Internet - Wio Terminal

În această parte a lecției, vei trimite telemetrie cu nivelurile de lumină de la Wio Terminal către brokerul MQTT.

## Instalează bibliotecile JSON pentru Arduino

O metodă populară de a trimite mesaje prin MQTT este utilizarea JSON. Există o bibliotecă Arduino pentru JSON care face mai ușoară citirea și scrierea documentelor JSON.

### Sarcină

Instalează biblioteca Arduino JSON.

1. Deschide proiectul pentru lumina de noapte în VS Code.

1. Adaugă următoarea linie suplimentară în lista `lib_deps` din fișierul `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Aceasta importă [ArduinoJson](https://arduinojson.org), o bibliotecă JSON pentru Arduino.

## Publică telemetria

Următorul pas este să creezi un document JSON cu telemetria și să-l trimiți către brokerul MQTT.

### Sarcină - publică telemetria

Publică telemetria către brokerul MQTT.

1. Adaugă următorul cod la sfârșitul fișierului `config.h` pentru a defini numele subiectului de telemetrie pentru brokerul MQTT:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` este subiectul pe care dispozitivul va publica nivelurile de lumină.

1. Deschide fișierul `main.cpp`.

1. Adaugă următoarea directivă `#include` în partea de sus a fișierului:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Adaugă următorul cod în interiorul funcției `loop`, chiar înainte de `delay`:

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

    Acest cod citește nivelul de lumină și creează un document JSON folosind ArduinoJson care conține acest nivel. Documentul este apoi serializat într-un șir și publicat pe subiectul de telemetrie MQTT de către clientul MQTT.

1. Încarcă codul pe Wio Terminal și folosește Serial Monitor pentru a vedea nivelurile de lumină trimise către brokerul MQTT.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Poți găsi acest cod în folderul [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Ai trimis cu succes telemetria de pe dispozitivul tău.

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.