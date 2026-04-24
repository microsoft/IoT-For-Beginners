# Ustvarite nočno lučko - Raspberry Pi

V tem delu lekcije boste na svoj Raspberry Pi dodali LED in ga uporabili za izdelavo nočne lučke.

## Strojna oprema

Nočna lučka zdaj potrebuje aktuator.

Aktuator je **LED**, [svetleča dioda](https://wikipedia.org/wiki/Light-emitting_diode), ki oddaja svetlobo, ko skozenj teče tok. To je digitalni aktuator, ki ima dva stanja: vklopljen in izklopljen. Pošiljanje vrednosti 1 vklopi LED, vrednost 0 pa ga izklopi. LED je zunanji Grove aktuator in ga je treba povezati z Grove Base hat na Raspberry Pi.

Logika nočne lučke v psevdo-kodi je:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Povežite LED

Grove LED je na voljo kot modul z izbiro LED diod, kar vam omogoča izbiro barve.

#### Naloga - povežite LED

Povežite LED.

![Grove LED](../../../../../translated_images/sl/grove-led.6c853be93f473cf2.webp)

1. Izberite svojo najljubšo LED in vstavite nogici v dve luknji na LED modulu.

    LED diode so svetleče diode, ki so elektronske naprave, skozi katere lahko tok teče le v eno smer. To pomeni, da mora biti LED povezan v pravilni smeri, sicer ne bo deloval.

    Ena od nogic LED je pozitivni pin, druga pa negativni pin. LED ni popolnoma okrogel in je na eni strani nekoliko bolj sploščen. Ta nekoliko bolj sploščen del je negativni pin. Ko LED povežete z modulom, poskrbite, da bo nogica na zaobljeni strani povezana z vtičnico, označeno z **+** na zunanji strani modula, sploščena stran pa z vtičnico bližje sredini modula.

1. LED modul ima vrtljiv gumb, ki omogoča nadzor svetlosti. Za začetek ga popolnoma privijte tako, da ga z majhnim križnim izvijačem zavrtite v nasprotni smeri urinega kazalca, kolikor gre.

1. En konec Grove kabla vstavite v vtičnico na LED modulu. Kabel bo šel noter le v eni smeri.

1. Ko je Raspberry Pi izklopljen, povežite drugi konec Grove kabla z digitalno vtičnico, označeno z **D5**, na Grove Base hat, ki je pritrjen na Pi. Ta vtičnica je druga z leve v vrsti vtičnic poleg GPIO pinov.

![Grove LED povezan z vtičnico D5](../../../../../translated_images/sl/pi-led.97f1d474981dc35d.webp)

## Programirajte nočno lučko

Nočno lučko lahko zdaj programirate z uporabo Grove svetlobnega senzorja in Grove LED.

### Naloga - programirajte nočno lučko

Programirajte nočno lučko.

1. Vklopite Pi in počakajte, da se zažene.

1. Odprite projekt nočne lučke v VS Code, ki ste ga ustvarili v prejšnjem delu te naloge, bodisi neposredno na Pi bodisi z uporabo razširitve Remote SSH.

1. Dodajte naslednjo kodo v datoteko `app.py`, da uvozite potrebno knjižnico. To je treba dodati na vrh, pod druge vrstice `import`.

    ```python
    from grove.grove_led import GroveLed
    ```

    Izjava `from grove.grove_led import GroveLed` uvozi `GroveLed` iz Grove Python knjižnic. Ta knjižnica vsebuje kodo za interakcijo z Grove LED.

1. Dodajte naslednjo kodo za deklaracijo `light_sensor`, da ustvarite instanco razreda, ki upravlja LED:

    ```python
    led = GroveLed(5)
    ```

    Vrstica `led = GroveLed(5)` ustvari instanco razreda `GroveLed`, ki se poveže s pinom **D5** - digitalnim Grove pinom, na katerega je povezan LED.

    > 💁 Vse vtičnice imajo edinstvene številke pinov. Pini 0, 2, 4 in 6 so analogni pini, pini 5, 16, 18, 22, 24 in 26 pa so digitalni pini.

1. Dodajte preverjanje znotraj zanke `while`, pred `time.sleep`, da preverite svetlobne ravni in vklopite ali izklopite LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Ta koda preveri vrednost `light`. Če je ta manjša od 300, pokliče metodo `on` razreda `GroveLed`, ki pošlje digitalno vrednost 1 LED, kar ga vklopi. Če je vrednost svetlobe večja ali enaka 300, pokliče metodo `off`, ki pošlje digitalno vrednost 0 LED, kar ga izklopi.

    > 💁 Ta koda mora biti zamaknjena na enako raven kot vrstica `print('Light level:', light)`, da bo znotraj zanke while!

    > 💁 Pri pošiljanju digitalnih vrednosti aktuatorjem je vrednost 0 enaka 0V, vrednost 1 pa največji napetosti naprave. Za Raspberry Pi z Grove senzorji in aktuatorji je napetost 1 enaka 3,3V.

1. V terminalu VS Code zaženite naslednje, da zaženete svojo Python aplikacijo:

    ```sh
    python3 app.py
    ```

    Vrednosti svetlobe bodo izpisane v konzoli.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Pokrijte in odkrijte svetlobni senzor. Opazili boste, kako se LED prižge, če je raven svetlobe 300 ali manj, in ugasne, ko je raven svetlobe večja od 300.

    > 💁 Če se LED ne prižge, preverite, ali je povezan v pravilni smeri, in ali je vrtljiv gumb nastavljen na polno moč.

![LED povezan z Pi, ki se prižiga in ugaša glede na spremembe svetlobne ravni](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 To kodo najdete v mapi [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Vaš program za nočno lučko je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki izhajajo iz uporabe tega prevoda.