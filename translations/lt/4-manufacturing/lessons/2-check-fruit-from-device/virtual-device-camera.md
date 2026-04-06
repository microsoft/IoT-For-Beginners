# Užfiksuokite vaizdą - Virtuali IoT aparatinė įranga

Šioje pamokos dalyje pridėsite kameros jutiklį prie savo virtualaus IoT įrenginio ir skaitysite vaizdus iš jo.

## Aparatinė įranga

Virtualus IoT įrenginys naudos imituotą kamerą, kuri siunčia vaizdus iš failų arba iš jūsų internetinės kameros.

### Pridėkite kamerą prie CounterFit

Norėdami naudoti virtualią kamerą, turite ją pridėti prie CounterFit programos.

#### Užduotis - pridėkite kamerą prie CounterFit

Pridėkite kamerą prie CounterFit programos.

1. Sukurkite naują Python programą savo kompiuteryje aplanke, pavadintame `fruit-quality-detector`, su vienu failu, pavadintu `app.py`, ir Python virtualią aplinką, tada pridėkite CounterFit pip paketus.

    > ⚠️ Jei reikia, galite peržiūrėti [instrukcijas, kaip sukurti ir nustatyti CounterFit Python projektą 1-oje pamokoje](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Įdiekite papildomą Pip paketą, kuris įdiegs CounterFit shim, galintį bendrauti su kameros jutikliais, imituojant kai kurias [Picamera Pip paketo](https://pypi.org/project/picamera/) funkcijas. Įsitikinkite, kad tai darote terminale su aktyvuota virtualia aplinka.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Įsitikinkite, kad CounterFit žiniatinklio programa veikia.

1. Sukurkite kamerą:

    1. Laukelyje *Create sensor* skiltyje *Sensors* išskleidžiamajame meniu *Sensor type* pasirinkite *Camera*.

    1. Nustatykite *Name* kaip `Picamera`.

    1. Pasirinkite mygtuką **Add**, kad sukurtumėte kamerą.

    ![Kameros nustatymai](../../../../../translated_images/lt/counterfit-create-camera.a5de97f59c0bd3cb.webp)

    Kamera bus sukurta ir pasirodys jutiklių sąraše.

    ![Sukurta kamera](../../../../../translated_images/lt/counterfit-camera.001ec52194c8ee5d.webp)

## Užprogramuokite kamerą

Dabar virtualus IoT įrenginys gali būti užprogramuotas naudoti virtualią kamerą.

### Užduotis - užprogramuokite kamerą

Užprogramuokite įrenginį.

1. Įsitikinkite, kad `fruit-quality-detector` programa yra atidaryta VS Code.

1. Atidarykite `app.py` failą.

1. Pridėkite šį kodą į `app.py` viršų, kad prijungtumėte programą prie CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Pridėkite šį kodą į savo `app.py` failą:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Šis kodas importuoja kai kurias reikalingas bibliotekas, įskaitant `PiCamera` klasę iš counterfit_shims_picamera bibliotekos.

1. Pridėkite šį kodą žemiau, kad inicializuotumėte kamerą:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Šis kodas sukuria PiCamera objektą, nustato raišką į 640x480. Nors palaikomos ir didesnės raiškos, vaizdų klasifikatorius veikia su daug mažesniais vaizdais (227x227), todėl nėra reikalo fiksuoti ir siųsti didesnių vaizdų.

    Eilutė `camera.rotation = 0` nustato vaizdo pasukimą laipsniais. Jei reikia pasukti vaizdą iš internetinės kameros ar failo, nustatykite tai pagal poreikį. Pavyzdžiui, jei norite pakeisti banano vaizdą iš internetinės kameros kraštovaizdžio režime į portretą, nustatykite `camera.rotation = 90`.

1. Pridėkite šį kodą žemiau, kad užfiksuotumėte vaizdą kaip dvejetainius duomenis:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Šis kodas sukuria `BytesIO` objektą dvejetainiams duomenims saugoti. Vaizdas nuskaitomas iš kameros kaip JPEG failas ir saugomas šiame objekte. Šis objektas turi pozicijos indikatorių, kuris nurodo, kurioje duomenų vietoje jis yra, kad prireikus būtų galima pridėti daugiau duomenų. Eilutė `image.seek(0)` perkelia šią poziciją atgal į pradžią, kad vėliau būtų galima perskaityti visus duomenis.

1. Po to pridėkite šį kodą, kad išsaugotumėte vaizdą faile:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Šis kodas atidaro failą, pavadintą `image.jpg`, rašymui, tada perskaito visus duomenis iš `BytesIO` objekto ir įrašo juos į failą.

    > 💁 Galite užfiksuoti vaizdą tiesiai į failą, o ne į `BytesIO` objektą, perduodami failo pavadinimą `camera.capture` kvietimui. Priežastis, kodėl naudojamas `BytesIO` objektas, yra ta, kad vėliau šioje pamokoje galėsite siųsti vaizdą į savo vaizdų klasifikatorių.

1. Sujunkite vaizdą, kurį CounterFit kamera užfiksuos. Galite nustatyti *Source* kaip *File*, tada įkelti vaizdo failą, arba nustatyti *Source* kaip *WebCam*, ir vaizdai bus užfiksuoti iš jūsų internetinės kameros. Įsitikinkite, kad paspaudėte mygtuką **Set** po paveikslėlio pasirinkimo arba internetinės kameros pasirinkimo.

    ![CounterFit su failu kaip vaizdo šaltiniu ir internetine kamera, rodančia asmenį, laikantį bananą, internetinės kameros peržiūroje](../../../../../translated_images/lt/counterfit-camera-options.eb3bd5150a8e7dff.webp)

1. Vaizdas bus užfiksuotas ir išsaugotas kaip `image.jpg` dabartiniame aplanke. Šį failą matysite VS Code naršyklėje. Pasirinkite failą, kad peržiūrėtumėte vaizdą. Jei reikia pasukti, atnaujinkite eilutę `camera.rotation = 0` pagal poreikį ir užfiksuokite kitą nuotrauką.

> 💁 Šį kodą galite rasti [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device) aplanke.

😀 Jūsų kameros programa pavyko!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant dirbtinio intelekto vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipkite dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus aiškinimus, kylančius dėl šio vertimo naudojimo.