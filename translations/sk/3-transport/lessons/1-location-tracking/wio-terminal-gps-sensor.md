# Čítanie GPS údajov - Wio Terminal

V tejto časti lekcie pridáte k svojmu Wio Terminalu GPS senzor a prečítate z neho hodnoty.

## Hardvér

Wio Terminal potrebuje GPS senzor.

Senzor, ktorý budete používať, je [Grove GPS Air530 senzor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Tento senzor sa dokáže pripojiť k viacerým GPS systémom pre rýchle a presné určenie polohy. Senzor pozostáva z dvoch častí - základnej elektroniky senzora a externej antény pripojenej tenkým káblom, ktorá zachytáva rádiové vlny zo satelitov.

Ide o UART senzor, takže GPS údaje posiela cez UART.

### Pripojenie GPS senzora

Grove GPS senzor je možné pripojiť k Wio Terminalu.

#### Úloha - pripojte GPS senzor

Pripojte GPS senzor.

![Grove GPS senzor](../../../../../translated_images/sk/grove-gps-sensor.247943bf69b03f0d.webp)

1. Zasuňte jeden koniec Grove kábla do konektora na GPS senzore. Kábel sa dá zasunúť iba jedným spôsobom.

1. Keď je Wio Terminal odpojený od vášho počítača alebo iného zdroja napájania, pripojte druhý koniec Grove kábla do ľavého Grove konektora na Wio Terminale, keď sa pozeráte na obrazovku. Tento konektor je najbližšie k tlačidlu napájania.

    ![Grove GPS senzor pripojený k ľavému konektoru](../../../../../translated_images/sk/wio-gps-sensor.19fd52b81ce58095.webp)

1. Umiestnite GPS senzor tak, aby pripojená anténa mala výhľad na oblohu - ideálne pri otvorenom okne alebo vonku. Je jednoduchšie získať jasnejší signál, keď anténe nič neprekáža.

1. Teraz môžete pripojiť Wio Terminal k vášmu počítaču.

1. GPS senzor má 2 LED diódy - modrú LED, ktorá bliká, keď sa prenášajú údaje, a zelenú LED, ktorá bliká každú sekundu, keď prijíma údaje zo satelitov. Uistite sa, že modrá LED bliká, keď zapnete Wio Terminal. Po niekoľkých minútach začne blikať zelená LED - ak nie, možno budete musieť premiestniť anténu.

## Naprogramovanie GPS senzora

Wio Terminal je teraz možné naprogramovať na používanie pripojeného GPS senzora.

### Úloha - naprogramujte GPS senzor

Naprogramujte zariadenie.

1. Vytvorte nový projekt pre Wio Terminal pomocou PlatformIO. Nazvite tento projekt `gps-sensor`. Pridajte kód do funkcie `setup` na konfiguráciu sériového portu.

1. Pridajte nasledujúci príkaz `include` na začiatok súboru `main.cpp`. Tento príkaz zahrnie hlavičkový súbor s funkciami na konfiguráciu ľavého Grove portu pre UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Pod týmto príkazom pridajte nasledujúci riadok kódu na deklaráciu sériového portu pre pripojenie k UART portu:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Potrebujete pridať kód na presmerovanie niektorých interných signalizačných handlerov na tento sériový port. Pridajte nasledujúci kód pod deklaráciu `Serial3`:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. Vo funkcii `setup`, pod konfiguráciou portu `Serial`, nakonfigurujte UART sériový port pomocou nasledujúceho kódu:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Pod týmto kódom vo funkcii `setup` pridajte nasledujúci kód na pripojenie Grove pinu k sériovému portu:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Pred funkciou `loop` pridajte nasledujúcu funkciu na odosielanie GPS údajov do sériového monitora:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. Vo funkcii `loop` pridajte nasledujúci kód na čítanie z UART sériového portu a tlač výstupu do sériového monitora:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Tento kód číta z UART sériového portu. Funkcia `readStringUntil` číta až po terminátor, v tomto prípade nový riadok. Týmto spôsobom sa prečíta celá NMEA veta (NMEA vety sú ukončené znakom nového riadku). Počas čítania údajov z UART sériového portu sa tieto údaje odosielajú do sériového monitora prostredníctvom funkcie `printGPSData`. Keď už nie je možné čítať ďalšie údaje, funkcia `loop` sa oneskorí o 1 sekundu (1 000 ms).

1. Zostavte a nahrajte kód do Wio Terminalu.

1. Po nahraní môžete monitorovať GPS údaje pomocou sériového monitora.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 Tento kód nájdete v priečinku [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Program pre váš GPS senzor bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.