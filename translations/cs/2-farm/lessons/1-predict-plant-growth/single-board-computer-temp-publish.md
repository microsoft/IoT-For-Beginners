<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-27T23:21:44+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "cs"
}
-->
# Publikování teploty - Virtuální IoT hardware a Raspberry Pi

V této části lekce budete publikovat hodnoty teploty detekované Raspberry Pi nebo Virtuálním IoT zařízením přes MQTT, aby mohly být později použity k výpočtu GDD.

## Publikování teploty

Jakmile je teplota přečtena, může být publikována přes MQTT do nějakého "serverového" kódu, který hodnoty přečte a uloží je, aby mohly být použity pro výpočet GDD.

### Úkol - publikování teploty

Naprogramujte zařízení tak, aby publikovalo data o teplotě.

1. Otevřete projekt aplikace `temperature-sensor`, pokud již není otevřený.

1. Opakujte kroky, které jste provedli v lekci 4, pro připojení k MQTT a odesílání telemetrie. Budete používat stejný veřejný Mosquitto broker.

    Kroky jsou následující:

    - Přidejte balíček pip pro MQTT
    - Přidejte kód pro připojení k MQTT brokeru
    - Přidejte kód pro publikování telemetrie

    > ⚠️ Podívejte se na [pokyny pro připojení k MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) a [pokyny pro odesílání telemetrie](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) z lekce 4, pokud je to potřeba.

1. Ujistěte se, že `client_name` odráží název tohoto projektu:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Pro telemetrii místo odesílání hodnoty světla odešlete hodnotu teploty přečtenou ze senzoru DHT v atributu JSON dokumentu nazvaném `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Hodnotu teploty není třeba číst příliš často - v krátkém časovém úseku se příliš nemění, proto nastavte `time.sleep` na 10 minut:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Funkce `sleep` bere čas v sekundách, takže pro snadnější čtení je hodnota předána jako výsledek výpočtu. 60 sekund je v minutě, takže 10 x (60 sekund v minutě) dává 10minutové zpoždění.

1. Spusťte kód stejným způsobem, jako jste spustili kód z předchozí části úkolu. Pokud používáte virtuální IoT zařízení, ujistěte se, že aplikace CounterFit běží a senzory vlhkosti a teploty byly vytvořeny na správných pinech.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Tento kód najdete ve složce [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) nebo ve složce [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Úspěšně jste publikovali teplotu jako telemetrii z vašeho zařízení.

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.