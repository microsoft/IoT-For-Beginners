# Čítanie GPS údajov - Virtuálny IoT hardvér

V tejto časti lekcie pridáte GPS senzor do vášho virtuálneho IoT zariadenia a prečítate z neho hodnoty.

## Virtuálny hardvér

Virtuálne IoT zariadenie bude používať simulovaný GPS senzor, ktorý je prístupný cez UART prostredníctvom sériového portu.

Fyzický GPS senzor má anténu na zachytávanie rádiových vĺn zo satelitov GPS a prevádza GPS signály na GPS údaje. Virtuálna verzia to simuluje tým, že vám umožňuje buď nastaviť zemepisnú šírku a dĺžku, posielať surové NMEA vety, alebo nahrať GPX súbor s viacerými lokalitami, ktoré sa môžu vracať postupne.

> 🎓 NMEA vety budú vysvetlené neskôr v tejto lekcii

### Pridanie senzora do CounterFit

Na použitie virtuálneho GPS senzora je potrebné pridať ho do aplikácie CounterFit.

#### Úloha - pridanie senzora do CounterFit

Pridajte GPS senzor do aplikácie CounterFit.

1. Vytvorte novú Python aplikáciu na vašom počítači v priečinku `gps-sensor` s jediným súborom `app.py` a Python virtuálnym prostredím, a pridajte CounterFit pip balíčky.

    > ⚠️ Môžete sa odvolať na [inštrukcie na vytvorenie a nastavenie CounterFit Python projektu v lekcii 1, ak je to potrebné](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Nainštalujte ďalší Pip balíček na inštaláciu CounterFit shim, ktorý dokáže komunikovať so senzormi na báze UART cez sériové pripojenie. Uistite sa, že inštalujete z terminálu s aktivovaným virtuálnym prostredím.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Uistite sa, že webová aplikácia CounterFit je spustená.

1. Vytvorte GPS senzor:

    1. V poli *Create sensor* v paneli *Sensors* rozbaľte pole *Sensor type* a vyberte *UART GPS*.

    1. Nechajte *Port* nastavený na */dev/ttyAMA0*.

    1. Kliknite na tlačidlo **Add**, aby ste vytvorili GPS senzor na porte `/dev/ttyAMA0`.

    ![Nastavenia GPS senzora](../../../../../translated_images/sk/counterfit-create-gps-sensor.6385dc9357d85ad1.webp)

    GPS senzor bude vytvorený a zobrazí sa v zozname senzorov.

    ![Vytvorený GPS senzor](../../../../../translated_images/sk/counterfit-gps-sensor.3fbb15af0a536756.webp)

## Naprogramovanie GPS senzora

Virtuálne IoT zariadenie je teraz pripravené na naprogramovanie pre použitie virtuálneho GPS senzora.

### Úloha - naprogramovanie GPS senzora

Naprogramujte aplikáciu pre GPS senzor.

1. Uistite sa, že aplikácia `gps-sensor` je otvorená vo VS Code.

1. Otvorte súbor `app.py`.

1. Pridajte nasledujúci kód na začiatok súboru `app.py`, aby ste pripojili aplikáciu k CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Pridajte nasledujúci kód pod tento, aby ste importovali potrebné knižnice, vrátane knižnice pre CounterFit sériový port:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Tento kód importuje modul `serial` z Pip balíčka `counterfit_shims_serial`. Potom sa pripojí k sériovému portu `/dev/ttyAMA0` - to je adresa sériového portu, ktorý používa virtuálny GPS senzor pre svoj UART port.

1. Pridajte nasledujúci kód pod tento, aby ste čítali zo sériového portu a vypisovali hodnoty do konzoly:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Funkcia `print_gps_data` je definovaná na vypisovanie riadku, ktorý jej bol odovzdaný, do konzoly.

    Následne kód beží v nekonečnej slučke, čítajúc čo najviac riadkov textu zo sériového portu v každej iterácii. Pre každý riadok volá funkciu `print_gps_data`.

    Po prečítaní všetkých údajov slučka spí 1 sekundu a potom sa pokúsi znova.

1. Spustite tento kód, pričom sa uistite, že používate iný terminál ako ten, v ktorom beží aplikácia CounterFit, aby aplikácia CounterFit zostala spustená.

1. V aplikácii CounterFit zmeňte hodnotu GPS senzora. Môžete to urobiť jedným z týchto spôsobov:

    * Nastavte **Source** na `Lat/Lon` a zadajte konkrétnu zemepisnú šírku, dĺžku a počet satelitov použitých na získanie GPS fixu. Táto hodnota bude odoslaná iba raz, takže zaškrtnite políčko **Repeat**, aby sa údaje opakovali každú sekundu.

      ![GPS senzor s nastavenou zemepisnou šírkou a dĺžkou](../../../../../translated_images/sk/counterfit-gps-sensor-latlon.008c867d75464fbe.webp)

    * Nastavte **Source** na `NMEA` a pridajte niekoľko NMEA viet do textového poľa. Všetky tieto hodnoty budú odoslané, s oneskorením 1 sekundy pred každou novou GGA (pozícia fixu) vetou.

      ![GPS senzor s nastavenými NMEA vetami](../../../../../translated_images/sk/counterfit-gps-sensor-nmea.c62eea442171e17e.webp)

      Môžete použiť nástroj ako [nmeagen.org](https://www.nmeagen.org) na generovanie týchto viet kreslením na mape. Tieto hodnoty budú odoslané iba raz, takže zaškrtnite políčko **Repeat**, aby sa údaje opakovali sekundu po ich odoslaní.

    * Nastavte **Source** na GPX súbor a nahrajte GPX súbor s trasovými lokalitami. GPX súbory môžete stiahnuť z viacerých populárnych máp a turistických stránok, ako napríklad [AllTrails](https://www.alltrails.com/). Tieto súbory obsahujú viacero GPS lokalít ako trasu a GPS senzor vráti každú novú lokalitu v intervale 1 sekundy.

      ![GPS senzor s nastaveným GPX súborom](../../../../../translated_images/sk/counterfit-gps-sensor-gpxfile.8310b063ce8a425c.webp)

      Tieto hodnoty budú odoslané iba raz, takže zaškrtnite políčko **Repeat**, aby sa údaje opakovali sekundu po ich odoslaní.

    Po nakonfigurovaní nastavení GPS kliknite na tlačidlo **Set**, aby ste tieto hodnoty uložili do senzora.

1. Uvidíte surový výstup z GPS senzora, niečo ako nasledujúce:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Tento kód nájdete v priečinku [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 Vaša aplikácia pre GPS senzor bola úspešne dokončená!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.