<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T22:34:41+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "cs"
}
-->
# Přidání senzoru - Wio Terminal

V této části lekce použijete světelný senzor na vašem Wio Terminalu.

## Hardware

Senzor pro tuto lekci je **světelný senzor**, který využívá [fotodiodu](https://wikipedia.org/wiki/Photodiode) k převodu světla na elektrický signál. Jedná se o analogový senzor, který posílá celočíselnou hodnotu od 0 do 1 023, což představuje relativní množství světla, které není převedeno na žádnou standardní jednotku měření, jako je například [lux](https://wikipedia.org/wiki/Lux).

Světelný senzor je zabudován do Wio Terminalu a je viditelný skrz průhledné plastové okénko na zadní straně.

![Světelný senzor na zadní straně Wio Terminalu](../../../../../translated_images/cs/wio-light-sensor.b1f529f3c95f5165.webp)

## Naprogramování světelného senzoru

Zařízení nyní může být naprogramováno tak, aby využívalo zabudovaný světelný senzor.

### Úkol

Naprogramujte zařízení.

1. Otevřete projekt nočního světla ve VS Code, který jste vytvořili v předchozí části tohoto úkolu.

1. Přidejte následující řádek na konec funkce `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Tento řádek konfiguruje piny používané ke komunikaci s hardwarovým senzorem.

    Pin `WIO_LIGHT` je číslo GPIO pinu připojeného k vestavěnému světelnému senzoru. Tento pin je nastaven na `INPUT`, což znamená, že je připojen k senzoru a data budou z pinu čtena.

1. Smažte obsah funkce `loop`.

1. Přidejte následující kód do nyní prázdné funkce `loop`.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Tento kód čte analogovou hodnotu z pinu `WIO_LIGHT`. Čte hodnotu od 0 do 1 023 z vestavěného světelného senzoru. Tato hodnota je poté odeslána na sériový port, takže ji můžete přečíst v Serial Monitoru, když tento kód běží. `Serial.print` zapisuje text bez nového řádku na konci, takže každý řádek začne s `Light value:` a skončí skutečnou hodnotou světla.

1. Přidejte malou prodlevu jedné sekundy (1 000 ms) na konec funkce `loop`, protože úroveň světla není třeba kontrolovat nepřetržitě. Prodleva snižuje spotřebu energie zařízení.

    ```cpp
    delay(1000);
    ```

1. Znovu připojte Wio Terminal k vašemu počítači a nahrajte nový kód stejným způsobem jako předtím.

1. Připojte Serial Monitor. Hodnoty světla budou vypsány na terminál. Zakryjte a odkryjte světelný senzor na zadní straně Wio Terminalu a hodnoty se budou měnit.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 Tento kód najdete ve složce [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Přidání senzoru do vašeho programu nočního světla bylo úspěšné!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby AI pro překlady [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatizované překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.