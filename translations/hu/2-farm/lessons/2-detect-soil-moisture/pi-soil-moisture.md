<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-27T22:48:27+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "hu"
}
-->
# Talajnedvesség mérése - Raspberry Pi

Ebben a leckében egy kapacitív talajnedvesség-érzékelőt fogsz hozzáadni a Raspberry Pi-hez, és értékeket olvasol le róla.

## Hardver

A Raspberry Pi-hez kapacitív talajnedvesség-érzékelőre van szükség.

Az érzékelő, amit használni fogsz, egy [Kapacitív Talajnedvesség Érzékelő](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), amely a talaj kapacitását méri. Ez egy olyan tulajdonság, amely változik a talaj nedvességtartalmának függvényében. Ahogy a talaj nedvessége nő, a feszültség csökken.

Ez egy analóg érzékelő, amely analóg csatlakozót használ, és a Pi Grove Base Hat 10 bites ADC-je alakítja át a feszültséget digitális jellé 1-1,023 között. Ezután a GPIO csatlakozókon keresztül továbbítja az adatokat a Pi-nek.

### Csatlakoztasd a talajnedvesség-érzékelőt

A Grove talajnedvesség-érzékelő csatlakoztatható a Raspberry Pi-hez.

#### Feladat - csatlakoztasd a talajnedvesség-érzékelőt

Csatlakoztasd a talajnedvesség-érzékelőt.

![Egy Grove talajnedvesség-érzékelő](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.hu.png)

1. Dugj be egy Grove kábelt az érzékelő csatlakozójába. Csak egy irányban illeszkedik.

1. Kapcsold ki a Raspberry Pi-t, majd csatlakoztasd a Grove kábel másik végét a Grove Base Hat analóg csatlakozójába, amely **A0** jelöléssel van ellátva. Ez a csatlakozó a GPIO csatlakozók melletti sorban, jobbról a második.

![A Grove talajnedvesség-érzékelő csatlakoztatva az A0 csatlakozóhoz](../../../../../translated_images/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.hu.png)

1. Helyezd az érzékelőt a talajba. Az érzékelőn van egy "legmagasabb pozíció vonal" - egy fehér vonal. Helyezd az érzékelőt a vonalig, de ne azon túl.

![A Grove talajnedvesség-érzékelő a talajban](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.hu.png)

## Programozd a talajnedvesség-érzékelőt

Most már programozhatod a Raspberry Pi-t, hogy használja a csatlakoztatott talajnedvesség-érzékelőt.

### Feladat - programozd a talajnedvesség-érzékelőt

Programozd az eszközt.

1. Kapcsold be a Pi-t, és várd meg, amíg elindul.

1. Indítsd el a VS Code-ot, akár közvetlenül a Pi-n, akár a Remote SSH bővítmény segítségével csatlakozva.

    > ⚠️ Ha szükséges, hivatkozhatsz [az éjszakai fény - 1. lecke VS Code beállítási és indítási útmutatójára](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. A terminálból hozz létre egy új mappát a `pi` felhasználó otthoni könyvtárában `soil-moisture-sensor` néven. Hozz létre egy fájlt ebben a mappában `app.py` néven.

1. Nyisd meg ezt a mappát a VS Code-ban.

1. Add hozzá a következő kódot az `app.py` fájlhoz, hogy importáld a szükséges könyvtárakat:

    ```python
    import time
    from grove.adc import ADC
    ```

    Az `import time` utasítás importálja a `time` modult, amelyet később fogsz használni ebben a feladatban.

    A `from grove.adc import ADC` utasítás importálja az `ADC`-t a Grove Python könyvtárakból. Ez a könyvtár tartalmazza a kódot, amely lehetővé teszi az analóg-digitális átalakítóval való kommunikációt a Pi Base Hat-on, és az analóg érzékelőkről érkező feszültségek olvasását.

1. Add hozzá a következő kódot az alá, hogy létrehozz egy példányt az `ADC` osztályból:

    ```python
    adc = ADC()
    ```

1. Adj hozzá egy végtelen ciklust, amely az A0 csatlakozón keresztül olvas az ADC-ről, és kiírja az eredményt a konzolra. Ez a ciklus 10 másodpercet várhat az olvasások között.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Futtasd a Python alkalmazást. Látni fogod a talajnedvesség méréseket a konzolon. Adj vizet a talajhoz, vagy vedd ki az érzékelőt a talajból, és figyeld meg, hogyan változik az érték.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    A fenti példakimenetben látható, hogy a feszültség csökken, ahogy vizet adsz hozzá.

> 💁 Ezt a kódot megtalálhatod a [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi) mappában.

😀 Sikeresen programoztad a talajnedvesség-érzékelőt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.