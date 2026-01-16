<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-28T14:12:50+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "sl"
}
-->
# Ustvarite nočno lučko - Virtualna IoT strojna oprema

V tem delu lekcije boste dodali LED na svojo virtualno IoT napravo in jo uporabili za ustvarjanje nočne lučke.

## Virtualna strojna oprema

Nočna lučka potrebuje en aktuator, ustvarjen v aplikaciji CounterFit.

Aktuator je **LED**. Na fizični IoT napravi bi bil to [svetleča dioda](https://wikipedia.org/wiki/Light-emitting_diode), ki oddaja svetlobo, ko skozenj teče tok. To je digitalni aktuator, ki ima 2 stanja: vklopljeno in izklopljeno. Pošiljanje vrednosti 1 vklopi LED, vrednost 0 pa jo izklopi.

Logika nočne lučke v psevdokodi je:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Dodajte aktuator v CounterFit

Za uporabo virtualnega LED morate dodati aktuator v aplikacijo CounterFit.

#### Naloga - dodajte aktuator v CounterFit

Dodajte LED v aplikacijo CounterFit.

1. Prepričajte se, da spletna aplikacija CounterFit deluje iz prejšnjega dela naloge. Če ne, jo zaženite in ponovno dodajte senzor svetlobe.

1. Ustvarite LED:

    1. V polju *Create actuator* v podoknu *Actuator* odprite spustni meni *Actuator type* in izberite *LED*.

    1. Nastavite *Pin* na *5*.

    1. Izberite gumb **Add**, da ustvarite LED na pinu 5.

    ![Nastavitve LED](../../../../../translated_images/sl/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    LED bo ustvarjen in se bo pojavil na seznamu aktuatorjev.

    ![Ustvarjen LED](../../../../../translated_images/sl/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    Ko je LED ustvarjen, lahko spremenite barvo z izbiro *Color* pickerja. Izberite gumb **Set**, da spremenite barvo po izbiri.

### Programirajte nočno lučko

Nočno lučko lahko zdaj programirate z uporabo senzorja svetlobe in LED v aplikaciji CounterFit.

#### Naloga - programirajte nočno lučko

Programirajte nočno lučko.

1. Odprite projekt nočne lučke v VS Code, ki ste ga ustvarili v prejšnjem delu naloge. Če je potrebno, zaprite in ponovno ustvarite terminal, da zagotovite, da deluje z virtualnim okoljem.

1. Odprite datoteko `app.py`.

1. Dodajte naslednjo kodo v datoteko `app.py`, da uvozite potrebno knjižnico. To je treba dodati na vrh, pod ostalimi vrsticami `import`.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    Izjava `from counterfit_shims_grove.grove_led import GroveLed` uvozi `GroveLed` iz Python knjižnic CounterFit Grove shim. Ta knjižnica vsebuje kodo za interakcijo z LED, ustvarjenim v aplikaciji CounterFit.

1. Dodajte naslednjo kodo za deklaracijo `light_sensor`, da ustvarite instanco razreda, ki upravlja LED:

    ```python
    led = GroveLed(5)
    ```

    Vrstica `led = GroveLed(5)` ustvari instanco razreda `GroveLed`, ki se poveže na pin **5** - CounterFit Grove pin, na katerega je povezan LED.

1. Dodajte preverjanje znotraj zanke `while`, pred `time.sleep`, da preverite nivoje svetlobe in vklopite ali izklopite LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Ta koda preveri vrednost `light`. Če je ta manjša od 300, pokliče metodo `on` razreda `GroveLed`, ki pošlje digitalno vrednost 1 LED, da ga vklopi. Če je vrednost svetlobe večja ali enaka 300, pokliče metodo `off`, ki pošlje digitalno vrednost 0 LED, da ga izklopi.

    > 💁 Ta koda mora biti zamaknjena na enako raven kot vrstica `print('Light level:', light)`, da bo znotraj zanke `while`!

1. V terminalu VS Code zaženite naslednje, da zaženete svojo Python aplikacijo:

    ```sh
    python3 app.py
    ```

    Vrednosti svetlobe bodo prikazane v konzoli.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Spremenite nastavitve *Value* ali *Random*, da spreminjate nivo svetlobe nad in pod 300. LED se bo vklapljal in izklapljal.

![LED v aplikaciji CounterFit se vklaplja in izklaplja glede na spremembe nivoja svetlobe](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 To kodo lahko najdete v mapi [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Vaš program za nočno lučko je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.