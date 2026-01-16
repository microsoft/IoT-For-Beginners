<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-27T23:28:23+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "hu"
}
-->
# Relé vezérlése - Virtuális IoT hardver

A lecke ezen részében egy relét fogsz hozzáadni a virtuális IoT eszközödhöz a talajnedvesség-érzékelő mellett, és a talajnedvesség szintje alapján vezérled azt.

## Virtuális hardver

A virtuális IoT eszköz egy szimulált Grove relét fog használni. Ez a labor ugyanúgy működik, mintha egy Raspberry Pi-t használnál fizikai Grove relével.

Egy fizikai IoT eszközben a relé egy alapállapotban nyitott relé lenne (ami azt jelenti, hogy a kimeneti áramkör nyitott, vagyis nincs összekapcsolva, ha nem érkezik jel a reléhez). Egy ilyen relé akár 250V és 10A kimeneti áramköröket is képes kezelni.

### Relé hozzáadása a CounterFit-hez

Ahhoz, hogy virtuális relét használj, hozzá kell adnod azt a CounterFit alkalmazáshoz.

#### Feladat

Add hozzá a relét a CounterFit alkalmazáshoz.

1. Nyisd meg a `soil-moisture-sensor` projektet az előző leckéből a VS Code-ban, ha még nincs megnyitva. Ehhez a projekthez fogsz hozzáadni.

1. Győződj meg róla, hogy a CounterFit webalkalmazás fut.

1. Hozz létre egy relét:

    1. Az *Actuators* panel *Create actuator* mezőjében nyisd le az *Actuator type* mezőt, és válaszd ki a *Relay* opciót.

    1. Állítsd a *Pin* értékét *5*-re.

    1. Kattints az **Add** gombra, hogy létrehozd a relét az 5-ös lábon.

    ![A relé beállításai](../../../../../translated_images/hu/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    A relé létrejön, és megjelenik az aktuátorok listájában.

    ![A létrehozott relé](../../../../../translated_images/hu/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## A relé programozása

Most már programozhatod a talajnedvesség-érzékelő alkalmazást, hogy használja a virtuális relét.

### Feladat

Programozd a virtuális eszközt.

1. Nyisd meg a `soil-moisture-sensor` projektet az előző leckéből a VS Code-ban, ha még nincs megnyitva. Ehhez a projekthez fogsz hozzáadni.

1. Add hozzá a következő kódot az `app.py` fájlhoz a meglévő importok alá:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Ez az utasítás importálja a `GroveRelay` osztályt a Grove Python shim könyvtárakból, hogy kapcsolatba léphess a virtuális Grove relével.

1. Add hozzá a következő kódot az `ADC` osztály deklarációja alá, hogy létrehozz egy `GroveRelay` példányt:

    ```python
    relay = GroveRelay(5)
    ```

    Ez létrehoz egy relét az **5-ös** lábon, amelyhez a relét csatlakoztattad.

1. Annak teszteléséhez, hogy a relé működik-e, add hozzá a következő kódot a `while True:` ciklusba:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    A kód bekapcsolja a relét, vár 0,5 másodpercet, majd kikapcsolja.

1. Futtasd a Python alkalmazást. A relé 10 másodpercenként be- és kikapcsol, fél másodperces késleltetéssel a be- és kikapcsolás között. A CounterFit alkalmazásban látni fogod, ahogy a virtuális relé záródik és nyílik, amikor a relé be- és kikapcsol.

    ![A virtuális relé be- és kikapcsolása](../../../../../images/virtual-relay-turn-on-off.gif)

## A relé vezérlése a talajnedvesség alapján

Most, hogy a relé működik, vezérelheted azt a talajnedvesség-érzékelő mérései alapján.

### Feladat

Vezéreld a relét.

1. Töröld a 3 sort, amelyet a relé teszteléséhez adtál hozzá. Helyettesítsd őket a következő kóddal:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Ez a kód ellenőrzi a talajnedvesség-érzékelő által mért szintet. Ha az 450 fölé emelkedik, bekapcsolja a relét, és kikapcsolja, ha 450 alá csökken.

    > 💁 Ne feledd, hogy a kapacitív talajnedvesség-érzékelőnél minél alacsonyabb az érték, annál több nedvesség van a talajban, és fordítva.

1. Futtasd a Python alkalmazást. Látni fogod, hogy a relé be- vagy kikapcsol a talajnedvesség szintjétől függően. Módosítsd a talajnedvesség-érzékelő *Value* vagy *Random* beállításait, hogy lásd az érték változását.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Ezt a kódot megtalálod a [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device) mappában.

😀 A virtuális talajnedvesség-érzékelővel vezérelt relé programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget a fordítás használatából eredő félreértésekért vagy téves értelmezésekért.