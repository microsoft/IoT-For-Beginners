# Meranie vlhkosti pôdy - Wio Terminal

V tejto časti lekcie pridáte kapacitný senzor vlhkosti pôdy k vášmu Wio Terminalu a budete z neho čítať hodnoty.

## Hardvér

Wio Terminal potrebuje kapacitný senzor vlhkosti pôdy.

Senzor, ktorý budete používať, je [Kapacitný senzor vlhkosti pôdy](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), ktorý meria vlhkosť pôdy detekovaním kapacity pôdy, vlastnosti, ktorá sa mení v závislosti od vlhkosti pôdy. Keď sa vlhkosť pôdy zvyšuje, napätie klesá.

Toto je analógový senzor, takže sa pripája k analógovým pinom na Wio Terminale, pričom používa zabudovaný ADC na vytvorenie hodnoty od 0 do 1 023.

### Pripojenie senzora vlhkosti pôdy

Grove senzor vlhkosti pôdy sa dá pripojiť k konfigurovateľnému analógovému/digitálnemu portu Wio Terminalu.

#### Úloha - pripojenie senzora vlhkosti pôdy

Pripojte senzor vlhkosti pôdy.

![Grove senzor vlhkosti pôdy](../../../../../translated_images/sk/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Zasuňte jeden koniec Grove kábla do zásuvky na senzore vlhkosti pôdy. Kábel sa dá zasunúť iba jedným spôsobom.

1. Keď je Wio Terminal odpojený od vášho počítača alebo iného zdroja napájania, pripojte druhý koniec Grove kábla do pravého Grove portu na Wio Terminale, keď sa pozeráte na obrazovku. Ide o port najvzdialenejší od tlačidla napájania.

![Grove senzor vlhkosti pôdy pripojený k pravému portu](../../../../../translated_images/sk/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Zasuňte senzor vlhkosti pôdy do pôdy. Má označenie „najvyššia pozícia“ - bielu čiaru cez senzor. Zasuňte senzor až po túto čiaru, ale nie za ňu.

![Grove senzor vlhkosti pôdy v pôde](../../../../../translated_images/sk/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. Teraz môžete pripojiť Wio Terminal k vášmu počítaču.

## Naprogramovanie senzora vlhkosti pôdy

Wio Terminal teraz môže byť naprogramovaný na používanie pripojeného senzora vlhkosti pôdy.

### Úloha - naprogramovanie senzora vlhkosti pôdy

Naprogramujte zariadenie.

1. Vytvorte úplne nový projekt pre Wio Terminal pomocou PlatformIO. Nazvite tento projekt `soil-moisture-sensor`. Pridajte kód do funkcie `setup` na konfiguráciu sériového portu.

    > ⚠️ Môžete sa odvolať na [pokyny na vytvorenie projektu PlatformIO v projekte 1, lekcii 1, ak je to potrebné](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Pre tento senzor neexistuje knižnica, namiesto toho môžete čítať z analógového pinu pomocou zabudovanej funkcie Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/). Začnite konfiguráciou analógového pinu na vstup, aby sa z neho dali čítať hodnoty, pridaním nasledujúceho kódu do funkcie `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Týmto nastavíte pin `A0`, kombinovaný analógový/digitálny pin, ako vstupný pin, z ktorého sa dá čítať napätie.

1. Pridajte nasledujúci kód do funkcie `loop` na čítanie napätia z tohto pinu:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Pod tento kód pridajte nasledujúci kód na výpis hodnoty do sériového portu:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Nakoniec pridajte oneskorenie na konci 10 sekúnd:

    ```cpp
    delay(10000);
    ```

1. Zostavte a nahrajte kód do Wio Terminalu.

    > ⚠️ Môžete sa odvolať na [pokyny na vytvorenie projektu PlatformIO v projekte 1, lekcii 1, ak je to potrebné](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Po nahraní môžete monitorovať vlhkosť pôdy pomocou sériového monitora. Pridajte trochu vody do pôdy alebo vyberte senzor z pôdy a sledujte, ako sa hodnota mení.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    V príklade výstupu vyššie môžete vidieť, ako napätie klesá, keď sa pridáva voda.

> 💁 Tento kód nájdete v priečinku [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 Program senzora vlhkosti pôdy bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.