<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T23:20:37+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "cs"
}
-->
# Publikování teploty - Wio Terminal

V této části lekce budete publikovat hodnoty teploty detekované Wio Terminalem přes MQTT, aby mohly být později použity k výpočtu GDD.

## Publikování teploty

Jakmile je teplota přečtena, může být publikována přes MQTT do nějakého "serverového" kódu, který hodnoty přečte a uloží je, aby mohly být použity pro výpočet GDD. Mikrokontroléry standardně nečtou čas z internetu a nesledují čas pomocí reálného časového modulu, zařízení musí být naprogramováno, aby to zvládlo, za předpokladu, že má potřebný hardware.

Abychom věci v této lekci zjednodušili, čas nebude odesílán spolu s daty ze senzoru, místo toho může být přidán serverovým kódem později, když přijme zprávy.

### Úkol

Naprogramujte zařízení tak, aby publikovalo data o teplotě.

1. Otevřete projekt `temperature-sensor` pro Wio Terminal.

1. Opakujte kroky, které jste provedli v lekci 4, abyste se připojili k MQTT a odeslali telemetrii. Budete používat stejný veřejný Mosquitto broker.

    Kroky jsou následující:

    - Přidejte knihovny Seeed WiFi a MQTT do souboru `.ini`.
    - Přidejte konfigurační soubor a kód pro připojení k WiFi.
    - Přidejte kód pro připojení k MQTT brokeru.
    - Přidejte kód pro publikování telemetrie.

    > ⚠️ Podívejte se na [instrukce pro připojení k MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) a [instrukce pro odesílání telemetrie](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) z lekce 4, pokud je to potřeba.

1. Ujistěte se, že `CLIENT_NAME` v hlavičkovém souboru `config.h` odpovídá tomuto projektu:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Pro telemetrii, místo odesílání hodnoty světla, odešlete hodnotu teploty přečtenou ze senzoru DHT jako vlastnost v JSON dokumentu nazvanou `temperature` změnou funkce `loop` v souboru `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Hodnota teploty nemusí být čtena příliš často - v krátkém časovém úseku se příliš nezmění, takže nastavte `delay` ve funkci `loop` na 10 minut:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Funkce `delay` bere čas v milisekundách, takže pro snadnější čtení je hodnota předána jako výsledek výpočtu. 1 000 ms je jedna sekunda, 60 sekund je jedna minuta, takže 10 x (60 sekund v minutě) x (1 000 ms v sekundě) dává zpoždění 10 minut.

1. Nahrajte tento kód do svého Wio Terminalu a použijte sériový monitor, abyste viděli, jak se teplota odesílá do MQTT brokeru.

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

> 💁 Tento kód najdete ve složce [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Úspěšně jste publikovali teplotu jako telemetrii ze svého zařízení.

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.