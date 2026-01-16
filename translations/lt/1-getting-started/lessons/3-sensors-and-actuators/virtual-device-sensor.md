<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-28T20:10:09+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "lt"
}
-->
# Sukurkite naktinę lemputę - Virtuali IoT įranga

Šioje pamokos dalyje pridėsite šviesos jutiklį prie savo virtualaus IoT įrenginio.

## Virtuali įranga

Naktinei lemputei reikalingas vienas jutiklis, sukurtas CounterFit programėlėje.

Jutiklis yra **šviesos jutiklis**. Fizinėje IoT įrangoje tai būtų [fotodiodas](https://wikipedia.org/wiki/Photodiode), kuris šviesą paverčia elektriniu signalu. Šviesos jutikliai yra analoginiai jutikliai, kurie siunčia sveikojo skaičiaus reikšmę, nurodančią santykinį šviesos kiekį, tačiau ši reikšmė nėra susieta su jokiu standartiniu matavimo vienetu, pavyzdžiui, [liuksais](https://wikipedia.org/wiki/Lux).

### Pridėkite jutiklius į CounterFit

Norėdami naudoti virtualų šviesos jutiklį, turite jį pridėti prie CounterFit programėlės.

#### Užduotis - pridėkite jutiklius į CounterFit

Pridėkite šviesos jutiklį prie CounterFit programėlės.

1. Įsitikinkite, kad CounterFit internetinė programėlė veikia nuo ankstesnės šios užduoties dalies. Jei ne, paleiskite ją.

1. Sukurkite šviesos jutiklį:

    1. *Create sensor* laukelyje, esančiame *Sensors* skydelyje, išskleiskite *Sensor type* laukelį ir pasirinkite *Light*.

    1. Palikite *Units* nustatytą kaip *NoUnits*.

    1. Įsitikinkite, kad *Pin* nustatytas į *0*.

    1. Paspauskite **Add** mygtuką, kad sukurtumėte šviesos jutiklį ant Pin 0.

    ![Šviesos jutiklio nustatymai](../../../../../translated_images/lt/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    Šviesos jutiklis bus sukurtas ir pasirodys jutiklių sąraše.

    ![Sukurtas šviesos jutiklis](../../../../../translated_images/lt/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Užprogramuokite šviesos jutiklį

Dabar įrenginį galima užprogramuoti naudoti įmontuotą šviesos jutiklį.

### Užduotis - užprogramuokite šviesos jutiklį

Užprogramuokite įrenginį.

1. Atidarykite naktinės lemputės projektą VS Code, kurį sukūrėte ankstesnėje šios užduoties dalyje. Jei reikia, uždarykite ir iš naujo paleiskite terminalą, kad įsitikintumėte, jog jis veikia naudojant virtualią aplinką.

1. Atidarykite `app.py` failą.

1. Pridėkite šį kodą į `app.py` failo viršų kartu su kitais `import` teiginiais, kad importuotumėte reikalingas bibliotekas:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time` teiginys importuoja Python `time` modulį, kuris bus naudojamas vėliau šioje užduotyje.

    `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` teiginys importuoja `GroveLightSensor` iš CounterFit Grove shim Python bibliotekų. Ši biblioteka turi kodą, skirtą sąveikai su šviesos jutikliu, sukurtu CounterFit programėlėje.

1. Pridėkite šį kodą į failo apačią, kad sukurtumėte klasių egzempliorius, valdančius šviesos jutiklį:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Eilutė `light_sensor = GroveLightSensor(0)` sukuria `GroveLightSensor` klasės egzempliorių, prijungtą prie **0** pin'o - CounterFit Grove pin'o, prie kurio prijungtas šviesos jutiklis.

1. Pridėkite begalinę kilpą po aukščiau esančiu kodu, kad nuskaitytumėte šviesos jutiklio reikšmę ir išvestumėte ją į konsolę:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Tai nuskaitys dabartinį šviesos lygį naudojant `light` savybę iš `GroveLightSensor` klasės. Ši savybė nuskaito analoginę reikšmę iš pin'o. Ši reikšmė tada išvedama į konsolę.

1. Pridėkite vienos sekundės pauzę `while` kilpos pabaigoje, nes šviesos lygio nereikia tikrinti nuolat. Pauzė sumažina įrenginio energijos suvartojimą.

    ```python
    time.sleep(1)
    ```

1. Iš VS Code terminalo paleiskite šią komandą, kad paleistumėte savo Python programą:

    ```sh
    python3 app.py
    ```

    Šviesos reikšmės bus išvedamos į konsolę. Iš pradžių ši reikšmė bus 0.

1. CounterFit programėlėje pakeiskite šviesos jutiklio reikšmę, kurią programa nuskaitys. Tai galite padaryti dviem būdais:

    * Įveskite skaičių į *Value* laukelį šviesos jutikliui, tada paspauskite **Set** mygtuką. Skaičius, kurį įvesite, bus reikšmė, kurią grąžins jutiklis.

    * Pažymėkite *Random* žymimąjį laukelį ir įveskite *Min* bei *Max* reikšmes, tada paspauskite **Set** mygtuką. Kiekvieną kartą, kai jutiklis nuskaitys reikšmę, ji bus atsitiktinis skaičius tarp *Min* ir *Max*.

    Reikšmės, kurias nustatysite, bus išvedamos į konsolę. Keiskite *Value* arba *Random* nustatymus, kad reikšmė keistųsi.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Šį kodą galite rasti [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device) aplanke.

😀 Jūsų naktinės lemputės programa pavyko!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.