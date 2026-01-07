<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-28T14:43:17+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "sl"
}
-->
# Merjenje vlažnosti zemlje - Wio Terminal

V tem delu lekcije boste na Wio Terminal dodali kapacitivni senzor za merjenje vlažnosti zemlje in odčitali vrednosti z njega.

## Strojna oprema

Wio Terminal potrebuje kapacitivni senzor za merjenje vlažnosti zemlje.

Senzor, ki ga boste uporabili, je [Kapacitivni senzor za merjenje vlažnosti zemlje](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), ki meri vlažnost zemlje z zaznavanjem kapacitivnosti zemlje, lastnosti, ki se spreminja glede na vlažnost zemlje. Ko se vlažnost zemlje poveča, se napetost zmanjša.

To je analogni senzor, zato se poveže na analogne pine na Wio Terminalu, pri čemer uporablja vgrajeni ADC za ustvarjanje vrednosti od 0 do 1.023.

### Povežite senzor za merjenje vlažnosti zemlje

Grove senzor za merjenje vlažnosti zemlje se lahko poveže na konfigurabilni analogno/digitalni priključek Wio Terminala.

#### Naloga - povežite senzor za merjenje vlažnosti zemlje

Povežite senzor za merjenje vlažnosti zemlje.

![Grove senzor za merjenje vlažnosti zemlje](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.sl.png)

1. En konec Grove kabla vstavite v vtičnico na senzorju za merjenje vlažnosti zemlje. Kabel gre v vtičnico samo v eni smeri.

1. Ko je Wio Terminal odklopljen od računalnika ali drugega vira napajanja, povežite drugi konec Grove kabla z desno Grove vtičnico na Wio Terminalu, gledano s sprednje strani zaslona. To je vtičnica, ki je najbolj oddaljena od gumba za vklop.

![Grove senzor za merjenje vlažnosti zemlje povezan z desno vtičnico](../../../../../translated_images/wio-soil-moisture-sensor.46919b61c3f6cb74.sl.png)

1. Vstavite senzor za merjenje vlažnosti zemlje v zemljo. Na senzorju je označena 'najvišja linija pozicije' - bela črta čez senzor. Senzor vstavite do te črte, vendar ne čez njo.

![Grove senzor za merjenje vlažnosti zemlje v zemlji](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.sl.png)

1. Zdaj lahko Wio Terminal povežete z računalnikom.

## Programiranje senzorja za merjenje vlažnosti zemlje

Wio Terminal je zdaj pripravljen za programiranje, da uporablja priključeni senzor za merjenje vlažnosti zemlje.

### Naloga - programirajte senzor za merjenje vlažnosti zemlje

Programirajte napravo.

1. Ustvarite povsem nov projekt za Wio Terminal z uporabo PlatformIO. Projekt poimenujte `soil-moisture-sensor`. Dodajte kodo v funkcijo `setup`, da konfigurirate serijski priključek.

    > ⚠️ Navodila za ustvarjanje projekta PlatformIO najdete v [projektu 1, lekcija 1](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project), če jih potrebujete.

1. Za ta senzor ni knjižnice, zato lahko berete z analognega pina z uporabo vgrajene Arduino funkcije [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/). Začnite tako, da konfigurirate analogni pin za vhod, da lahko berete vrednosti z njega, tako da v funkcijo `setup` dodate naslednje:

    ```cpp
    pinMode(A0, INPUT);
    ```

    To nastavi pin `A0`, kombinirani analogno/digitalni pin, kot vhodni pin, s katerega lahko berete napetost.

1. V funkcijo `loop` dodajte naslednjo kodo za branje napetosti s tega pina:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Pod to kodo dodajte naslednjo kodo za izpis vrednosti na serijski priključek:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Na koncu dodajte zakasnitev 10 sekund:

    ```cpp
    delay(10000);
    ```

1. Sestavite in naložite kodo na Wio Terminal.

    > ⚠️ Navodila za ustvarjanje projekta PlatformIO najdete v [projektu 1, lekcija 1](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app), če jih potrebujete.

1. Ko je koda naložena, lahko spremljate vlažnost zemlje z uporabo serijskega monitorja. Dodajte nekaj vode v zemljo ali odstranite senzor iz zemlje in opazujte spremembo vrednosti.

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

    V zgornjem primeru izpisa lahko vidite, kako napetost pade, ko dodate vodo.

> 💁 To kodo najdete v mapi [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 Vaš program za senzor vlažnosti zemlje je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.