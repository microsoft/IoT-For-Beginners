# Matuokite temperatūrą - Virtuali IoT Aparatūra

Šioje pamokos dalyje pridėsite temperatūros jutiklį prie savo virtualaus IoT įrenginio.

## Virtuali Aparatūra

Virtualus IoT įrenginys naudos simuliuotą Grove skaitmeninį drėgmės ir temperatūros jutiklį. Tai leidžia šį laboratorinį darbą atlikti taip pat, kaip naudojant Raspberry Pi su fiziniu Grove DHT11 jutikliu.

Jutiklis sujungia **temperatūros jutiklį** su **drėgmės jutikliu**, tačiau šioje laboratorijoje jus domina tik temperatūros jutiklio komponentas. Fizinėje IoT įrangoje temperatūros jutiklis būtų [termistorius](https://wikipedia.org/wiki/Thermistor), kuris matuoja temperatūrą, fiksuodamas varžos pokyčius keičiantis temperatūrai. Temperatūros jutikliai dažniausiai yra skaitmeniniai ir viduje konvertuoja išmatuotą varžą į temperatūrą Celsijaus (arba Kelvino, arba Farenheito) laipsniais.

### Pridėkite jutiklius prie CounterFit

Norėdami naudoti virtualų drėgmės ir temperatūros jutiklį, turite pridėti abu jutiklius prie CounterFit programos.

#### Užduotis - pridėkite jutiklius prie CounterFit

Pridėkite drėgmės ir temperatūros jutiklius prie CounterFit programos.

1. Sukurkite naują Python programą savo kompiuteryje aplanke `temperature-sensor` su vienu failu, pavadintu `app.py`, ir Python virtualią aplinką, tada pridėkite CounterFit pip paketus.

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip sukurti ir nustatyti CounterFit Python projektą 1-oje pamokoje](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Įdiekite papildomą Pip paketą, kad įdiegtumėte CounterFit shim DHT11 jutikliui. Įsitikinkite, kad tai darote terminale su aktyvuota virtualia aplinka.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Įsitikinkite, kad CounterFit žiniatinklio programa veikia.

1. Sukurkite drėgmės jutiklį:

    1. Laukelyje *Create sensor* skiltyje *Sensors* išskleidžiamajame meniu *Sensor type* pasirinkite *Humidity*.

    1. Palikite *Units* nustatytus kaip *Percentage*.

    1. Įsitikinkite, kad *Pin* nustatytas į *5*.

    1. Paspauskite mygtuką **Add**, kad sukurtumėte drėgmės jutiklį ant 5 kaiščio.

    ![Drėgmės jutiklio nustatymai](../../../../../translated_images/lt/counterfit-create-humidity-sensor.2750e27b6f30e09c.webp)

    Drėgmės jutiklis bus sukurtas ir pasirodys jutiklių sąraše.

    ![Sukurtas drėgmės jutiklis](../../../../../translated_images/lt/counterfit-humidity-sensor.7b12f7f339e430cb.webp)

1. Sukurkite temperatūros jutiklį:

    1. Laukelyje *Create sensor* skiltyje *Sensors* išskleidžiamajame meniu *Sensor type* pasirinkite *Temperature*.

    1. Palikite *Units* nustatytus kaip *Celsius*.

    1. Įsitikinkite, kad *Pin* nustatytas į *6*.

    1. Paspauskite mygtuką **Add**, kad sukurtumėte temperatūros jutiklį ant 6 kaiščio.

    ![Temperatūros jutiklio nustatymai](../../../../../translated_images/lt/counterfit-create-temperature-sensor.199350ed34f7343d.webp)

    Temperatūros jutiklis bus sukurtas ir pasirodys jutiklių sąraše.

    ![Sukurtas temperatūros jutiklis](../../../../../translated_images/lt/counterfit-temperature-sensor.f0560236c96a9016.webp)

## Programuokite temperatūros jutiklio programą

Dabar galima programuoti temperatūros jutiklio programą naudojant CounterFit jutiklius.

### Užduotis - programuokite temperatūros jutiklio programą

Programuokite temperatūros jutiklio programą.

1. Įsitikinkite, kad `temperature-sensor` programa atidaryta VS Code.

1. Atidarykite `app.py` failą.

1. Pridėkite šį kodą į `app.py` viršų, kad prijungtumėte programą prie CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Pridėkite šį kodą į `app.py` failą, kad importuotumėte reikalingas bibliotekas:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    `from seeed_dht import DHT` eilutė importuoja `DHT` jutiklio klasę, skirtą sąveikai su virtualiu Grove temperatūros jutikliu, naudojant shim iš `counterfit_shims_seeed_python_dht` modulio.

1. Pridėkite šį kodą po aukščiau esančio kodo, kad sukurtumėte klasės egzempliorių, kuris valdo virtualų drėgmės ir temperatūros jutiklį:

    ```python
    sensor = DHT("11", 5)
    ```

    Tai deklaruoja `DHT` klasės egzempliorių, kuris valdo virtualų **D**igital **H**umidity ir **T**emperature jutiklį. Pirmasis parametras nurodo, kad naudojamas virtualus *DHT11* jutiklis. Antrasis parametras nurodo, kad jutiklis prijungtas prie 5 prievado.

    > 💁 CounterFit simuliuoja šį kombinuotą drėgmės ir temperatūros jutiklį, prijungdamas prie 2 jutiklių: drėgmės jutiklio ant nurodyto kaiščio, kai `DHT` klasė sukuriama, ir temperatūros jutiklio, kuris veikia ant kito kaiščio. Jei drėgmės jutiklis yra ant 5 kaiščio, shim tikisi, kad temperatūros jutiklis bus ant 6 kaiščio.

1. Pridėkite begalinę kilpą po aukščiau esančio kodo, kad nuskaitytumėte temperatūros jutiklio reikšmę ir atspausdintumėte ją konsolėje:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    `sensor.read()` iškvietimas grąžina drėgmės ir temperatūros duomenų rinkinį. Jums reikia tik temperatūros reikšmės, todėl drėgmė ignoruojama. Temperatūros reikšmė tada atspausdinama konsolėje.

1. Pridėkite trumpą dešimties sekundžių pauzę kilpos pabaigoje, nes temperatūros lygiai neturi būti tikrinami nuolat. Pauzė sumažina įrenginio energijos suvartojimą.

    ```python
    time.sleep(10)
    ```

1. VS Code terminale su aktyvuota virtualia aplinka paleiskite šią komandą, kad paleistumėte savo Python programą:

    ```sh
    python app.py
    ```

1. CounterFit programoje pakeiskite temperatūros jutiklio reikšmę, kurią programa nuskaitys. Tai galite padaryti dviem būdais:

    * Įveskite skaičių į *Value* laukelį temperatūros jutikliui, tada paspauskite mygtuką **Set**. Įvestas skaičius bus reikšmė, kurią grąžins jutiklis.

    * Pažymėkite *Random* žymimąjį laukelį ir įveskite *Min* bei *Max* reikšmes, tada paspauskite mygtuką **Set**. Kiekvieną kartą, kai jutiklis nuskaitys reikšmę, ji bus atsitiktinis skaičius tarp *Min* ir *Max*.

    Konsolėje turėtumėte matyti jūsų nustatytas reikšmes. Pakeiskite *Value* arba *Random* nustatymus, kad pamatytumėte, kaip keičiasi reikšmės.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Šį kodą galite rasti [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device) aplanke.

😀 Jūsų temperatūros jutiklio programa pavyko!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.