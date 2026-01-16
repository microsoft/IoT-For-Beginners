<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-28T09:36:09+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "sk"
}
-->
# Čítanie GPS údajov - Raspberry Pi

V tejto časti lekcie pridáte k svojmu Raspberry Pi GPS senzor a budete z neho čítať údaje.

## Hardvér

Raspberry Pi potrebuje GPS senzor.

Senzor, ktorý budete používať, je [Grove GPS Air530 senzor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Tento senzor sa dokáže pripojiť k viacerým GPS systémom pre rýchle a presné určenie polohy. Senzor sa skladá z dvoch častí - hlavnej elektroniky senzora a externej antény pripojenej tenkým káblom, ktorá zachytáva rádiové vlny zo satelitov.

Ide o UART senzor, takže posiela GPS údaje cez UART.

## Pripojenie GPS senzora

Grove GPS senzor je možné pripojiť k Raspberry Pi.

### Úloha - pripojte GPS senzor

Pripojte GPS senzor.

![Grove GPS senzor](../../../../../translated_images/sk/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Zasuňte jeden koniec Grove kábla do konektora na GPS senzore. Kábel sa dá zasunúť iba jedným spôsobom.

1. S vypnutým Raspberry Pi pripojte druhý koniec Grove kábla do UART konektora označeného **UART** na Grove Base hat pripojenom k Pi. Tento konektor sa nachádza v strednom rade na strane najbližšej k SD karte, na opačnom konci od USB portov a ethernetového konektora.

    ![Grove GPS senzor pripojený k UART konektoru](../../../../../translated_images/sk/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. Umiestnite GPS senzor tak, aby pripojená anténa mala výhľad na oblohu - ideálne pri otvorenom okne alebo vonku. Čím menej prekážok je medzi anténou a oblohou, tým lepší signál získate.

## Programovanie GPS senzora

Raspberry Pi teraz môže byť naprogramované na používanie pripojeného GPS senzora.

### Úloha - naprogramujte GPS senzor

Naprogramujte zariadenie.

1. Zapnite Pi a počkajte, kým sa spustí.

1. GPS senzor má 2 LED diódy - modrú LED, ktorá bliká pri prenose údajov, a zelenú LED, ktorá bliká každú sekundu pri prijímaní údajov zo satelitov. Uistite sa, že modrá LED bliká po zapnutí Pi. Po niekoľkých minútach začne blikať zelená LED - ak nie, možno budete musieť premiestniť anténu.

1. Spustite VS Code, buď priamo na Pi, alebo sa pripojte cez rozšírenie Remote SSH.

    > ⚠️ Môžete sa odvolať na [pokyny na nastavenie a spustenie VS Code v lekcii 1, ak je to potrebné](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Pri novších verziách Raspberry Pi, ktoré podporujú Bluetooth, existuje konflikt medzi sériovým portom používaným pre Bluetooth a tým, ktorý používa Grove UART port. Na vyriešenie tohto problému postupujte nasledovne:

    1. Z terminálu VS Code upravte súbor `/boot/config.txt` pomocou `nano`, vstavaného textového editora terminálu, pomocou nasledujúceho príkazu:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Tento súbor nemôžete upravovať vo VS Code, pretože na to potrebujete oprávnenia `sudo`, teda zvýšené oprávnenia. VS Code nebeží s týmito oprávneniami.

    1. Pomocou kurzorových klávesov prejdite na koniec súboru, potom skopírujte nasledujúci kód a vložte ho na koniec súboru:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Vložiť môžete pomocou bežných klávesových skratiek pre vaše zariadenie (`Ctrl+v` na Windows, Linux alebo Raspberry Pi OS, `Cmd+v` na macOS).

    1. Uložte tento súbor a ukončite nano stlačením `Ctrl+x`. Stlačte `y`, keď sa vás opýta, či chcete uložiť upravený obsah, a potom stlačte `enter`, aby ste potvrdili, že chcete prepísať `/boot/config.txt`.

        > Ak urobíte chybu, môžete ukončiť bez uloženia a zopakovať tieto kroky.

    1. Upravte súbor `/boot/cmdline.txt` v nano pomocou nasledujúceho príkazu:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Tento súbor obsahuje niekoľko dvojíc kľúč/hodnota oddelených medzerami. Odstráňte všetky dvojice kľúč/hodnota pre kľúč `console`. Pravdepodobne budú vyzerať takto:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Pomocou kurzorových klávesov prejdite na tieto položky a potom ich odstráňte pomocou kláves `del` alebo `backspace`.

        Napríklad, ak váš pôvodný súbor vyzerá takto:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Nová verzia bude vyzerať takto:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Postupujte podľa vyššie uvedených krokov na uloženie tohto súboru a ukončenie nano.

    1. Reštartujte svoje Pi a po reštarte sa znova pripojte vo VS Code.

1. Z terminálu vytvorte nový priečinok v domovskom adresári používateľa `pi` s názvom `gps-sensor`. V tomto priečinku vytvorte súbor s názvom `app.py`.

1. Otvorte tento priečinok vo VS Code.

1. GPS modul posiela UART údaje cez sériový port. Nainštalujte balík `pyserial` cez Pip na komunikáciu so sériovým portom z vášho Python kódu:

    ```sh
    pip3 install pyserial
    ```

1. Pridajte nasledujúci kód do vášho súboru `app.py`:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Tento kód importuje modul `serial` z balíka `pyserial`. Potom sa pripojí k sériovému portu `/dev/ttyAMA0` - toto je adresa sériového portu, ktorý používa Grove Pi Base Hat pre svoj UART port. Následne vymaže všetky existujúce údaje z tohto sériového pripojenia.

    Ďalej je definovaná funkcia `print_gps_data`, ktorá vypisuje riadok odovzdaný ako parameter do konzoly.

    Potom kód beží v nekonečnej slučke, čítajúc čo najviac riadkov textu zo sériového portu v každej iterácii. Pre každý riadok volá funkciu `print_gps_data`.

    Po prečítaní všetkých údajov slučka spí 1 sekundu a potom to skúša znova.

1. Spustite tento kód. Uvidíte surový výstup z GPS senzora, niečo ako toto:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Ak dostanete jednu z nasledujúcich chýb pri zastavení a opätovnom spustení vášho kódu, pridajte blok `try - except` do vašej while slučky.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 Tento kód nájdete v priečinku [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Programovanie vášho GPS senzora bolo úspešné!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie odporúčame profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.