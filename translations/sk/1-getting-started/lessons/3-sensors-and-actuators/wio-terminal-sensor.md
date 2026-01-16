<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-28T10:39:46+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "sk"
}
-->
# Pridanie senzora - Wio Terminal

V tejto časti lekcie použijete svetelný senzor na vašom Wio Terminal.

## Hardvér

Senzor pre túto lekciu je **svetelný senzor**, ktorý používa [fotodiódu](https://wikipedia.org/wiki/Photodiode) na konverziu svetla na elektrický signál. Ide o analógový senzor, ktorý posiela celočíselnú hodnotu od 0 do 1 023, čo indikuje relatívne množstvo svetla, ktoré sa neprekladá do žiadnej štandardnej jednotky merania, ako je napríklad [lux](https://wikipedia.org/wiki/Lux).

Svetelný senzor je zabudovaný do Wio Terminal a je viditeľný cez priehľadné plastové okienko na zadnej strane.

![Svetelný senzor na zadnej strane Wio Terminal](../../../../../translated_images/sk/wio-light-sensor.b1f529f3c95f5165.webp)

## Naprogramovanie svetelného senzora

Zariadenie teraz môže byť naprogramované na použitie zabudovaného svetelného senzora.

### Úloha

Naprogramujte zariadenie.

1. Otvorte projekt nočného svetla vo VS Code, ktorý ste vytvorili v predchádzajúcej časti tejto úlohy.

1. Pridajte nasledujúci riadok na koniec funkcie `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Tento riadok konfiguruje piny používané na komunikáciu s hardvérom senzora.

    Pin `WIO_LIGHT` je číslo GPIO pinu pripojeného k zabudovanému svetelnému senzoru. Tento pin je nastavený na `INPUT`, čo znamená, že je pripojený k senzoru a údaje budú čítané z pinu.

1. Vymažte obsah funkcie `loop`.

1. Pridajte nasledujúci kód do teraz prázdnej funkcie `loop`.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Tento kód číta analógovú hodnotu z pinu `WIO_LIGHT`. Táto hodnota je v rozsahu od 0 do 1 023 zo zabudovaného svetelného senzora. Hodnota je potom poslaná na sériový port, aby ste ju mohli čítať v Serial Monitor, keď tento kód beží. `Serial.print` zapisuje text bez nového riadku na konci, takže každý riadok začne s `Light value:` a skončí skutočnou hodnotou svetla.

1. Pridajte malú pauzu jednej sekundy (1 000 ms) na koniec funkcie `loop`, pretože úrovne svetla nie je potrebné kontrolovať nepretržite. Pauza znižuje spotrebu energie zariadenia.

    ```cpp
    delay(1000);
    ```

1. Znovu pripojte Wio Terminal k vášmu počítaču a nahrajte nový kód tak, ako ste to urobili predtým.

1. Pripojte Serial Monitor. Hodnoty svetla budú vypisované do terminálu. Zakryte a odkryte svetelný senzor na zadnej strane Wio Terminal a hodnoty sa budú meniť.

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

> 💁 Tento kód nájdete v priečinku [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Pridanie senzora do vášho programu nočného svetla bolo úspešné!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.