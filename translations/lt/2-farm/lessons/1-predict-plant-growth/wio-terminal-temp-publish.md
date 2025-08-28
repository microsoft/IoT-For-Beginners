<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-28T20:38:45+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "lt"
}
-->
# Publikuoti temperatūrą - Wio Terminal

Šioje pamokos dalyje publikuosite Wio Terminal aptiktas temperatūros reikšmes per MQTT, kad vėliau jos galėtų būti naudojamos GDD skaičiavimui.

## Publikuoti temperatūrą

Kai temperatūra yra nuskaityta, ją galima publikuoti per MQTT į tam tikrą „serverio“ kodą, kuris nuskaito reikšmes ir saugo jas, kad vėliau būtų galima naudoti GDD skaičiavimui. Mikrovaldikliai iš karto neskaito laiko iš interneto ir neturi realaus laiko laikrodžio, todėl įrenginį reikia užprogramuoti, jei jis turi reikiamą aparatinę įrangą.

Kad pamoka būtų paprastesnė, laikas nebus siunčiamas kartu su jutiklio duomenimis – vietoj to jis gali būti pridėtas serverio kode, kai gaunami pranešimai.

### Užduotis

Užprogramuokite įrenginį publikuoti temperatūros duomenis.

1. Atidarykite `temperature-sensor` Wio Terminal projektą.

1. Pakartokite veiksmus, kuriuos atlikote 4 pamokoje, kad prisijungtumėte prie MQTT ir siųstumėte telemetriją. Naudosite tą patį viešą Mosquitto brokerį.

    Veiksmai yra tokie:

    - Pridėkite Seeed WiFi ir MQTT bibliotekas į `.ini` failą
    - Pridėkite konfigūracijos failą ir kodą prisijungti prie WiFi
    - Pridėkite kodą prisijungti prie MQTT brokerio
    - Pridėkite kodą publikuoti telemetriją

    > ⚠️ Žr. [instrukcijas, kaip prisijungti prie MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) ir [instrukcijas, kaip siųsti telemetriją](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) iš 4 pamokos, jei reikia.

1. Įsitikinkite, kad `CLIENT_NAME` faile `config.h` atspindi šį projektą:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Telemetrijai, vietoj šviesos reikšmės siųskite temperatūros reikšmę, nuskaitytą iš DHT jutiklio, JSON dokumento savybėje, pavadintoje `temperature`, pakeisdami `loop` funkciją faile `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Temperatūros reikšmės nereikia skaityti labai dažnai – ji per trumpą laiką daug nesikeis, todėl nustatykite `delay` funkciją `loop` funkcijoje 10 minučių:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay` funkcija naudoja laiką milisekundėmis, todėl, kad būtų lengviau suprasti, reikšmė perduodama kaip skaičiavimo rezultatas. 1,000ms per sekundę, 60s per minutę, todėl 10 x (60s per minutę) x (1000ms per sekundę) suteikia 10 minučių vėlavimą.

1. Įkelkite tai į savo Wio Terminal ir naudokite serijinį monitorių, kad pamatytumėte, kaip temperatūra siunčiama į MQTT brokerį.

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

> 💁 Šį kodą galite rasti [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) aplanke.

😀 Jūs sėkmingai publikavote temperatūrą kaip telemetriją iš savo įrenginio.

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipkite dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.