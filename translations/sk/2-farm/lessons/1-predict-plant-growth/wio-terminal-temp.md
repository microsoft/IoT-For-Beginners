# Meranie teploty - Wio Terminal

V tejto časti lekcie pridáte k Wio Terminalu teplotný senzor a budete z neho čítať hodnoty teploty.

## Hardvér

Wio Terminal potrebuje teplotný senzor.

Senzor, ktorý budete používať, je [DHT11 senzor vlhkosti a teploty](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), ktorý kombinuje 2 senzory v jednom balení. Je pomerne populárny a existuje množstvo komerčne dostupných senzorov, ktoré kombinujú teplotu, vlhkosť a niekedy aj atmosférický tlak. Komponent teplotného senzora je termistor s negatívnym teplotným koeficientom (NTC), termistor, ktorého odpor klesá so zvyšujúcou sa teplotou.

Toto je digitálny senzor, takže má zabudovaný ADC, ktorý vytvára digitálny signál obsahujúci údaje o teplote a vlhkosti, ktoré môže mikrokontrolér čítať.

### Pripojenie teplotného senzora

Grove teplotný senzor môže byť pripojený k digitálnemu portu Wio Terminalu.

#### Úloha - pripojenie teplotného senzora

Pripojte teplotný senzor.

![Grove teplotný senzor](../../../../../translated_images/sk/grove-dht11.07f8eafceee17004.webp)

1. Zasuňte jeden koniec Grove kábla do zásuvky na senzore vlhkosti a teploty. Pôjde to iba jedným smerom.

1. S odpojeným Wio Terminalom od počítača alebo iného zdroja napájania pripojte druhý koniec Grove kábla do pravého Grove portu na Wio Terminale, keď sa pozeráte na obrazovku. Ide o port najvzdialenejší od tlačidla napájania.

![Grove teplotný senzor pripojený k pravému portu](../../../../../translated_images/sk/wio-temperature-sensor.2934928f38c7f79a.webp)

## Naprogramovanie teplotného senzora

Wio Terminal teraz môže byť naprogramovaný na používanie pripojeného teplotného senzora.

### Úloha - naprogramovanie teplotného senzora

Naprogramujte zariadenie.

1. Vytvorte úplne nový projekt pre Wio Terminal pomocou PlatformIO. Nazvite tento projekt `temperature-sensor`. Pridajte kód do funkcie `setup` na konfiguráciu sériového portu.

    > ⚠️ Môžete sa odvolať na [pokyny na vytvorenie projektu v PlatformIO v projekte 1, lekcii 1, ak je to potrebné](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Pridajte závislosť knižnice pre Seeed Grove Humidity and Temperature senzor do súboru `platformio.ini` projektu:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Môžete sa odvolať na [pokyny na pridanie knižníc do projektu v PlatformIO v projekte 1, lekcii 4, ak je to potrebné](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Pridajte nasledujúce direktívy `#include` na začiatok súboru, pod existujúce `#include <Arduino.h>`:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Tým sa importujú súbory potrebné na interakciu so senzorom. Hlavičkový súbor `DHT.h` obsahuje kód pre samotný senzor a pridanie hlavičkového súboru `SPI.h` zabezpečuje, že kód potrebný na komunikáciu so senzorom bude zahrnutý pri kompilácii aplikácie.

1. Pred funkciou `setup` deklarujte senzor DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Tým sa deklaruje inštancia triedy `DHT`, ktorá spravuje **D**igitálny **H**umidity a **T**emperature senzor. Tento senzor je pripojený k portu `D0`, pravému Grove portu na Wio Terminale. Druhý parameter informuje kód, že používaný senzor je *DHT11* - knižnica, ktorú používate, podporuje aj iné varianty tohto senzora.

1. Vo funkcii `setup` pridajte kód na nastavenie sériového pripojenia:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Na konci funkcie `setup`, po poslednom `delay`, pridajte volanie na spustenie senzora DHT:

    ```cpp
    dht.begin();
    ```

1. Vo funkcii `loop` pridajte kód na volanie senzora a tlač hodnoty teploty na sériový port:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Tento kód deklaruje prázdne pole 2 floatov a odovzdá ho volaniu `readTempAndHumidity` na inštancii `DHT`. Toto volanie naplní pole 2 hodnotami - vlhkosť sa uloží do 0-tej položky v poli (pamätajte, že v C++ sú polia 0-based, takže 0-tá položka je 'prvá' položka v poli) a teplota sa uloží do 1. položky.

    Teplota sa číta z 1. položky v poli a tlačí sa na sériový port.

    > 🇺🇸 Teplota sa číta v stupňoch Celzia. Pre Američanov, na konverziu na Fahrenheit, vydelte hodnotu v stupňoch Celzia číslom 5, potom vynásobte číslom 9 a pridajte 32. Napríklad, hodnota teploty 20°C sa prepočíta na ((20/5)*9) + 32 = 68°F.

1. Skompilujte a nahrajte kód do Wio Terminalu.

    > ⚠️ Môžete sa odvolať na [pokyny na vytvorenie projektu v PlatformIO v projekte 1, lekcii 1, ak je to potrebné](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Po nahraní môžete monitorovať teplotu pomocou sériového monitora:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Tento kód nájdete v priečinku [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Program pre váš teplotný senzor bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.