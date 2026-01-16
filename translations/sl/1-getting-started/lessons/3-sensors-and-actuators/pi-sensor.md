<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-28T14:14:44+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "sl"
}
-->
# Izdelaj nočno lučko - Raspberry Pi

V tem delu lekcije boste dodali svetlobni senzor na vaš Raspberry Pi.

## Strojna oprema

Senzor za to lekcijo je **svetlobni senzor**, ki uporablja [fotodiodo](https://wikipedia.org/wiki/Photodiode) za pretvorbo svetlobe v električni signal. Gre za analogni senzor, ki pošilja celoštevilsko vrednost od 0 do 1.000, kar označuje relativno količino svetlobe, ki ne ustreza nobeni standardni enoti, kot je [lux](https://wikipedia.org/wiki/Lux).

Svetlobni senzor je zunanji Grove senzor in ga je treba povezati z Grove Base hat na Raspberry Pi.

### Povežite svetlobni senzor

Grove svetlobni senzor, ki se uporablja za zaznavanje ravni svetlobe, je treba povezati z Raspberry Pi.

#### Naloga - povežite svetlobni senzor

Povežite svetlobni senzor.

![Grove svetlobni senzor](../../../../../translated_images/sl/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Vstavite en konec Grove kabla v vtičnico na modulu svetlobnega senzorja. Kabel bo šel noter le na en način.

1. Ko je Raspberry Pi izklopljen, povežite drugi konec Grove kabla z analogno vtičnico, označeno **A0**, na Grove Base hat, ki je pritrjen na Pi. Ta vtičnica je druga z desne strani v vrsti vtičnic poleg GPIO pinov.

![Grove svetlobni senzor povezan z vtičnico A0](../../../../../translated_images/sl/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Programirajte svetlobni senzor

Napravo je zdaj mogoče programirati z uporabo Grove svetlobnega senzorja.

### Naloga - programirajte svetlobni senzor

Programirajte napravo.

1. Vklopite Pi in počakajte, da se zažene.

1. Odprite projekt nočne lučke v VS Code, ki ste ga ustvarili v prejšnjem delu naloge, bodisi neposredno na Pi bodisi prek povezave z Remote SSH razširitvijo.

1. Odprite datoteko `app.py` in odstranite vso kodo iz nje.

1. Dodajte naslednjo kodo v datoteko `app.py`, da uvozite potrebne knjižnice:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Ukaz `import time` uvozi modul `time`, ki bo uporabljen kasneje v tej nalogi.

    Ukaz `from grove.grove_light_sensor_v1_2 import GroveLightSensor` uvozi `GroveLightSensor` iz Grove Python knjižnic. Ta knjižnica vsebuje kodo za interakcijo z Grove svetlobnim senzorjem in je bila globalno nameščena med nastavitvijo Pi.

1. Dodajte naslednjo kodo za zgornjo kodo, da ustvarite instanco razreda, ki upravlja svetlobni senzor:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Vrstica `light_sensor = GroveLightSensor(0)` ustvari instanco razreda `GroveLightSensor`, ki se povezuje na pin **A0** - analogni Grove pin, na katerega je povezan svetlobni senzor.

1. Dodajte neskončno zanko za zgornjo kodo, da preverjate vrednost svetlobnega senzorja in jo izpišete v konzolo:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    To bo prebralo trenutno raven svetlobe na lestvici od 0-1.023 z uporabo lastnosti `light` razreda `GroveLightSensor`. Ta lastnost prebere analogno vrednost iz pina. Ta vrednost se nato izpiše v konzolo.

1. Na koncu zanke dodajte kratko pavzo eno sekundo, saj ni potrebno neprekinjeno preverjati ravni svetlobe. Pavza zmanjša porabo energije naprave.

    ```python
    time.sleep(1)
    ```

1. Iz terminala v VS Code zaženite naslednje, da zaženete vašo Python aplikacijo:

    ```sh
    python3 app.py
    ```

    Vrednosti svetlobe bodo izpisane v konzolo. Pokrijte in odkrijte svetlobni senzor, vrednosti pa se bodo spremenile:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 To kodo lahko najdete v mapi [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 Dodajanje senzorja v vaš program nočne lučke je bilo uspešno!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za strojno prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas opozarjamo, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo strokovno človeško prevajanje. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki izhajajo iz uporabe tega prevoda.