<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-27T23:29:14+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "hu"
}
-->
# Relé vezérlése - Raspberry Pi

A lecke ezen részében egy relét fogsz hozzáadni a Raspberry Pi-hez a talajnedvesség-érzékelő mellett, és a talajnedvesség szintje alapján vezérelni azt.

## Hardver

A Raspberry Pi-hez szükség van egy relére.

Az általad használt relé egy [Grove relé](https://www.seeedstudio.com/Grove-Relay.html), egy normálisan nyitott relé (ami azt jelenti, hogy a kimeneti áramkör nyitott, vagyis nincs összekapcsolva, amikor nincs jel küldve a relének), amely akár 250V és 10A kimeneti áramköröket is képes kezelni.

Ez egy digitális működtető, tehát a Grove Base Hat digitális csatlakozójához kell csatlakoztatni.

### Csatlakoztasd a relét

A Grove relé csatlakoztatható a Raspberry Pi-hez.

#### Feladat

Csatlakoztasd a relét.

![Egy Grove relé](../../../../../translated_images/hu/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Dugj be egy Grove kábelt a relé aljzatába. Csak egyféleképpen illeszkedik.

1. Kapcsold ki a Raspberry Pi-t, majd csatlakoztasd a Grove kábel másik végét a **D5** jelzésű digitális aljzathoz a Pi-hez csatlakoztatott Grove Base Hat-on. Ez az aljzat a második balról, a GPIO csatlakozók melletti aljzatsoron. Hagyd a talajnedvesség-érzékelőt az **A0** aljzathoz csatlakoztatva.

![A Grove relé a D5 aljzathoz csatlakoztatva, és a talajnedvesség-érzékelő az A0 aljzathoz csatlakoztatva](../../../../../translated_images/hu/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. Helyezd a talajnedvesség-érzékelőt a talajba, ha az előző leckéből még nem tetted meg.

## Programozd a relét

Most már programozhatod a Raspberry Pi-t, hogy használja a csatlakoztatott relét.

### Feladat

Programozd az eszközt.

1. Kapcsold be a Pi-t, és várd meg, amíg elindul.

1. Nyisd meg a `soil-moisture-sensor` projektet az előző leckéből a VS Code-ban, ha még nincs megnyitva. Ehhez a projekthez fogsz hozzáadni.

1. Add hozzá a következő kódot az `app.py` fájlhoz a meglévő importok alá:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Ez az utasítás importálja a `GroveRelay`-t a Grove Python könyvtárakból, hogy kapcsolatba léphess a Grove relével.

1. Add hozzá a következő kódot az `ADC` osztály deklarációja alá, hogy létrehozz egy `GroveRelay` példányt:

    ```python
    relay = GroveRelay(5)
    ```

    Ez létrehoz egy relét a **D5** csatlakozón, amelyhez a relét csatlakoztattad.

1. Hogy teszteld, működik-e a relé, add hozzá a következőt a `while True:` ciklushoz:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    A kód bekapcsolja a relét, vár 0,5 másodpercet, majd kikapcsolja a relét.

1. Futtasd a Python alkalmazást. A relé 10 másodpercenként be- és kikapcsol, fél másodperces késleltetéssel a bekapcsolás és kikapcsolás között. Hallani fogod, ahogy a relé bekapcsol, majd kikapcsol. A Grove panelen egy LED világít, amikor a relé be van kapcsolva, majd kialszik, amikor kikapcsol.

    ![A relé be- és kikapcsolása](../../../../../images/relay-turn-on-off.gif)

## A relé vezérlése a talajnedvesség alapján

Most, hogy a relé működik, vezérelheted a talajnedvesség-érzékelő olvasásai alapján.

### Feladat

Vezéreld a relét.

1. Töröld a relé tesztelésére hozzáadott 3 sor kódot. Helyettesítsd őket a következő kóddal:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Ez a kód ellenőrzi a talajnedvesség-érzékelő által mért talajnedvesség szintjét. Ha az érték 450 fölött van, bekapcsolja a relét, és kikapcsolja, amikor az 450 alá csökken.

    > 💁 Ne feledd, hogy a kapacitív talajnedvesség-érzékelő olvasásai szerint minél alacsonyabb a talajnedvesség szintje, annál nedvesebb a talaj, és fordítva.

1. Futtasd a Python alkalmazást. Látni fogod, hogy a relé be- vagy kikapcsol a talajnedvesség szintjétől függően. Próbáld ki száraz talajban, majd adj hozzá vizet.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Ezt a kódot megtalálod a [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi) mappában.

😀 Sikeresen elkészítetted a talajnedvesség-érzékelőt vezérlő relé programot!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.