<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-28T10:33:49+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "sk"
}
-->
# Vytvorte nočné svetlo - Raspberry Pi

V tejto časti lekcie pridáte LED diódu k svojmu Raspberry Pi a použijete ju na vytvorenie nočného svetla.

## Hardvér

Nočné svetlo teraz potrebuje akčný člen.

Akčný člen je **LED dióda**, [svetlo emitujúca dióda](https://wikipedia.org/wiki/Light-emitting_diode), ktorá vyžaruje svetlo, keď cez ňu preteká prúd. Ide o digitálny akčný člen, ktorý má dva stavy: zapnutý a vypnutý. Odoslanie hodnoty 1 zapne LED diódu, hodnota 0 ju vypne. LED dióda je externý Grove akčný člen a musí byť pripojená k Grove Base hat na Raspberry Pi.

Logika nočného svetla v pseudo-kóde je:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Pripojenie LED diódy

Grove LED dióda je dodávaná ako modul s výberom LED diód, čo vám umožňuje zvoliť si farbu.

#### Úloha - pripojte LED diódu

Pripojte LED diódu.

![Grove LED dióda](../../../../../translated_images/sk/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. Vyberte si svoju obľúbenú LED diódu a vložte jej nožičky do dvoch otvorov na module LED diódy.

    LED diódy sú svetlo emitujúce diódy a diódy sú elektronické zariadenia, ktoré môžu prenášať prúd iba jedným smerom. To znamená, že LED dióda musí byť pripojená správnym spôsobom, inak nebude fungovať.

    Jedna z nožičiek LED diódy je kladný pin, druhá je záporný pin. LED dióda nie je dokonale okrúhla a na jednej strane je mierne plochšia. Táto mierne plochšia strana je záporný pin. Keď pripojíte LED diódu k modulu, uistite sa, že pin na zaoblenej strane je pripojený k zásuvke označenej **+** na vonkajšej strane modulu a plochšia strana je pripojená k zásuvke bližšie k stredu modulu.

1. Modul LED diódy má otočný gombík, ktorý umožňuje ovládať jas. Na začiatok ho otočte úplne doľava proti smeru hodinových ručičiek pomocou malého krížového skrutkovača.

1. Vložte jeden koniec Grove kábla do zásuvky na module LED diódy. Pôjde to iba jedným smerom.

1. Pri vypnutom Raspberry Pi pripojte druhý koniec Grove kábla k digitálnej zásuvke označenej **D5** na Grove Base hat pripojenom k Pi. Táto zásuvka je druhá zľava v rade zásuviek vedľa GPIO pinov.

![Grove LED pripojená k zásuvke D5](../../../../../translated_images/sk/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## Naprogramujte nočné svetlo

Nočné svetlo teraz môžete naprogramovať pomocou Grove svetelného senzora a Grove LED diódy.

### Úloha - naprogramujte nočné svetlo

Naprogramujte nočné svetlo.

1. Zapnite Raspberry Pi a počkajte, kým sa spustí.

1. Otvorte projekt nočného svetla vo VS Code, ktorý ste vytvorili v predchádzajúcej časti tejto úlohy, buď priamo na Pi, alebo pripojením pomocou rozšírenia Remote SSH.

1. Pridajte nasledujúci kód do súboru `app.py`, aby ste importovali potrebnú knižnicu. Tento kód by mal byť pridaný na začiatok, pod ostatné riadky `import`.

    ```python
    from grove.grove_led import GroveLed
    ```

    Príkaz `from grove.grove_led import GroveLed` importuje `GroveLed` z Grove Python knižníc. Táto knižnica obsahuje kód na interakciu s Grove LED diódou.

1. Pridajte nasledujúci kód za deklaráciu `light_sensor`, aby ste vytvorili inštanciu triedy, ktorá spravuje LED diódu:

    ```python
    led = GroveLed(5)
    ```

    Riadok `led = GroveLed(5)` vytvára inštanciu triedy `GroveLed`, ktorá sa pripája k pinu **D5** - digitálnemu Grove pinu, ku ktorému je pripojená LED dióda.

    > 💁 Všetky zásuvky majú jedinečné čísla pinov. Piny 0, 2, 4 a 6 sú analógové piny, piny 5, 16, 18, 22, 24 a 26 sú digitálne piny.

1. Pridajte kontrolu do `while` cyklu, pred `time.sleep`, aby ste skontrolovali úroveň svetla a zapli alebo vypli LED diódu:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Tento kód kontroluje hodnotu `light`. Ak je táto hodnota menšia ako 300, zavolá metódu `on` triedy `GroveLed`, ktorá odošle digitálnu hodnotu 1 do LED diódy, čím ju zapne. Ak je hodnota svetla väčšia alebo rovná 300, zavolá metódu `off`, ktorá odošle digitálnu hodnotu 0 do LED diódy, čím ju vypne.

    > 💁 Tento kód by mal byť odsadený na rovnakú úroveň ako riadok `print('Light level:', light)`, aby bol vo vnútri `while` cyklu!

    > 💁 Pri odosielaní digitálnych hodnôt do akčných členov je hodnota 0 rovná 0V a hodnota 1 je maximálne napätie pre zariadenie. Pre Raspberry Pi s Grove senzormi a akčnými členmi je napätie 1 rovné 3,3V.

1. Z terminálu vo VS Code spustite nasledujúci príkaz na spustenie vášho Python programu:

    ```sh
    python3 app.py
    ```

    Hodnoty svetla budú vypisované do konzoly.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Zakryte a odkryte svetelný senzor. Všimnite si, ako sa LED dióda rozsvieti, ak je úroveň svetla 300 alebo menej, a zhasne, keď je úroveň svetla väčšia ako 300.

    > 💁 Ak sa LED dióda nerozsvieti, uistite sa, že je pripojená správnym spôsobom a otočný gombík je nastavený na maximum.

![LED pripojená k Pi sa zapína a vypína podľa zmeny úrovne svetla](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Tento kód nájdete v priečinku [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Váš program nočného svetla bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.