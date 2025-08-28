<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-28T15:12:47+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "hr"
}
-->
# Objavi temperaturu - Wio Terminal

U ovom dijelu lekcije objavit ćete vrijednosti temperature koje detektira Wio Terminal putem MQTT-a kako bi se kasnije mogle koristiti za izračun GDD-a.

## Objavi temperaturu

Nakon što se temperatura očita, može se objaviti putem MQTT-a na neki 'server' kod koji će očitati vrijednosti i spremiti ih za kasniju upotrebu u izračunu GDD-a. Mikrokontroleri ne očitavaju vrijeme s Interneta niti prate vrijeme pomoću realnog vremenskog sata automatski, uređaj mora biti programiran za to, pod uvjetom da ima potrebni hardver.

Kako bismo pojednostavili stvari u ovoj lekciji, vrijeme neće biti poslano s podacima senzora, već ga može dodati server kod kasnije kada primi poruke.

### Zadatak

Programirajte uređaj da objavi podatke o temperaturi.

1. Otvorite projekt `temperature-sensor` za Wio Terminal.

1. Ponovite korake koje ste radili u lekciji 4 za povezivanje na MQTT i slanje telemetrije. Koristit ćete isti javni Mosquitto broker.

    Koraci za ovo su:

    - Dodajte Seeed WiFi i MQTT biblioteke u `.ini` datoteku
    - Dodajte konfiguracijsku datoteku i kod za povezivanje na WiFi
    - Dodajte kod za povezivanje na MQTT broker
    - Dodajte kod za objavu telemetrije

    > ⚠️ Pogledajte [upute za povezivanje na MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) i [upute za slanje telemetrije](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) iz lekcije 4 ako je potrebno.

1. Provjerite da `CLIENT_NAME` u zaglavnoj datoteci `config.h` odražava ovaj projekt:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Za telemetriju, umjesto slanja vrijednosti svjetla, pošaljite vrijednost temperature očitanu s DHT senzora u svojstvu JSON dokumenta nazvanom `temperature` tako da promijenite funkciju `loop` u `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Vrijednost temperature ne treba se očitavati često - neće se značajno mijenjati u kratkom vremenskom razdoblju, pa postavite `delay` u funkciji `loop` na 10 minuta:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Funkcija `delay` uzima vrijeme u milisekundama, pa je radi lakšeg čitanja vrijednost proslijeđena kao rezultat izračuna. 1.000ms u sekundi, 60s u minuti, pa 10 x (60s u minuti) x (1000ms u sekundi) daje kašnjenje od 10 minuta.

1. Prenesite ovo na svoj Wio Terminal i koristite serijski monitor za pregled temperature koja se šalje na MQTT broker.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Uspješno ste objavili temperaturu kao telemetriju sa svog uređaja.

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden korištenjem AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati mjerodavnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije proizašle iz korištenja ovog prijevoda.