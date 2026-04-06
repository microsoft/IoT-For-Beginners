# Ustvari nočno lučko - Wio Terminal

V tem delu lekcije boste dodali LED na vaš Wio Terminal in ga uporabili za ustvarjanje nočne lučke.

## Strojna oprema

Nočna lučka zdaj potrebuje aktuator.

Aktuator je **LED**, [svetleča dioda](https://wikipedia.org/wiki/Light-emitting_diode), ki oddaja svetlobo, ko skozi njo teče tok. To je digitalni aktuator, ki ima dva stanja: vklopljen in izklopljen. Pošiljanje vrednosti 1 vklopi LED, vrednost 0 pa jo izklopi. To je zunanji Grove aktuator, ki ga je treba povezati z Wio Terminalom.

Logika nočne lučke v psevdokodi je:

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

1. Izberite svojo najljubšo LED in vstavite nogice v dve luknji na LED modulu.

    LED diode so svetleče diode, dioda pa je elektronska naprava, ki lahko prenaša tok samo v eno smer. To pomeni, da mora biti LED povezan pravilno, sicer ne bo deloval.

    Ena od nogic LED je pozitivni pin, druga pa negativni pin. LED ni popolnoma okrogel in je na eni strani nekoliko bolj raven. Ta rahlo ravna stran je negativni pin. Ko povežete LED z modulom, poskrbite, da bo pin na zaobljeni strani povezan z vtičnico, označeno z **+** na zunanji strani modula, ravna stran pa z vtičnico bližje sredini modula.

1. LED modul ima vrtljiv gumb, ki omogoča nadzor svetlosti. Za začetek ga zavrtite povsem navzgor, tako da ga z majhnim križnim izvijačem zavrtite v nasprotni smeri urinega kazalca.

1. Vstavite en konec Grove kabla v vtičnico na LED modulu. Kabel bo šel noter samo v eni smeri.

1. Ko je Wio Terminal odklopljen od računalnika ali drugega napajalnika, povežite drugi konec Grove kabla z desno Grove vtičnico na Wio Terminalu, gledano na zaslon. To je vtičnica, ki je najbolj oddaljena od gumba za vklop.

    > 💁 Desna Grove vtičnica se lahko uporablja z analognimi ali digitalnimi senzorji in aktuatorji. Leva vtičnica je namenjena samo I2C in digitalnim senzorjem ter aktuatorjem.

![Grove LED povezan z desno vtičnico](../../../../../translated_images/sl/wio-led.265a1897e72d7f21.webp)

## Programirajte nočno lučko

Nočno lučko lahko zdaj programirate z vgrajenim senzorjem svetlobe in Grove LED.

### Naloga - programirajte nočno lučko

Programirajte nočno lučko.

1. Odprite projekt nočne lučke v VS Code, ki ste ga ustvarili v prejšnjem delu naloge.

1. Dodajte naslednjo vrstico na dno funkcije `setup`:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Ta vrstica konfigurira pin, ki se uporablja za komunikacijo z LED prek Grove vtičnice.

    Pin `D0` je digitalni pin za desno Grove vtičnico. Ta pin je nastavljen na `OUTPUT`, kar pomeni, da je povezan z aktuatorjem in podatki bodo zapisani na pin.

1. Dodajte naslednjo kodo takoj pred `delay` v funkciji zanke:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Ta koda preveri vrednost `light`. Če je ta manjša od 300, pošlje vrednost `HIGH` na digitalni pin `D0`. Ta `HIGH` je vrednost 1, ki vklopi LED. Če je svetloba večja ali enaka 300, se na pin pošlje vrednost `LOW`, ki izklopi LED.

    > 💁 Pri pošiljanju digitalnih vrednosti aktuatorjem je vrednost LOW 0v, vrednost HIGH pa največja napetost za napravo. Za Wio Terminal je napetost HIGH 3,3V.

1. Ponovno povežite Wio Terminal z računalnikom in naložite novo kodo, kot ste to storili prej.

1. Povežite Serial Monitor. Vrednosti svetlobe bodo izpisane na terminal.

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

1. Pokrijte in odkrijte senzor svetlobe. Opazili boste, kako se LED prižge, če je raven svetlobe 300 ali manj, in ugasne, ko je raven svetlobe večja od 300.

![LED povezan z WIO, ki se prižiga in ugaša glede na spremembe ravni svetlobe](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 To kodo najdete v mapi [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal).

😀 Vaš program za nočno lučko je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.