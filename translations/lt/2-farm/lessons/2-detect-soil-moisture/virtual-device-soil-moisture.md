# Matuokite dirvožemio drėgmę - Virtuali IoT įranga

Šioje pamokos dalyje pridėsite talpinį dirvožemio drėgmės jutiklį prie savo virtualaus IoT įrenginio ir nuskaitysite jo vertes.

## Virtuali įranga

Virtualus IoT įrenginys naudos simuliuotą Grove talpinį dirvožemio drėgmės jutiklį. Tai leidžia šį praktinį darbą atlikti taip pat, kaip naudojant Raspberry Pi su fiziniu Grove talpiniu dirvožemio drėgmės jutikliu.

Fiziniame IoT įrenginyje dirvožemio drėgmės jutiklis būtų talpinis jutiklis, kuris matuoja dirvožemio drėgmę aptikdamas dirvožemio talpą – savybę, kuri keičiasi priklausomai nuo drėgmės kiekio dirvožemyje. Didėjant dirvožemio drėgmei, įtampa mažėja.

Tai yra analoginis jutiklis, todėl jis naudoja simuliuotą 10 bitų ADC, kad praneštų vertę nuo 1 iki 1,023.

### Pridėkite dirvožemio drėgmės jutiklį į CounterFit

Norėdami naudoti virtualų dirvožemio drėgmės jutiklį, turite jį pridėti prie CounterFit programos.

#### Užduotis - Pridėkite dirvožemio drėgmės jutiklį į CounterFit

Pridėkite dirvožemio drėgmės jutiklį į CounterFit programą.

1. Sukurkite naują Python programą savo kompiuteryje aplanke `soil-moisture-sensor` su vienu failu, pavadintu `app.py`, ir Python virtualią aplinką, tada pridėkite CounterFit pip paketus.

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip sukurti ir nustatyti CounterFit Python projektą 1 pamokoje](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Įsitikinkite, kad CounterFit internetinė programa veikia.

1. Sukurkite dirvožemio drėgmės jutiklį:

    1. *Create sensor* laukelyje, esančiame *Sensors* skydelyje, išskleidžiamajame *Sensor type* laukelyje pasirinkite *Soil Moisture*.

    1. Palikite *Units* nustatytą kaip *NoUnits*.

    1. Įsitikinkite, kad *Pin* nustatytas kaip *0*.

    1. Paspauskite **Add** mygtuką, kad sukurtumėte *Soil Moisture* jutiklį ant Pin 0.

    ![Dirvožemio drėgmės jutiklio nustatymai](../../../../../translated_images/lt/counterfit-create-soil-moisture-sensor.35266135a5e0ae68.webp)

    Dirvožemio drėgmės jutiklis bus sukurtas ir pasirodys jutiklių sąraše.

    ![Sukurtas dirvožemio drėgmės jutiklis](../../../../../translated_images/lt/counterfit-soil-moisture-sensor.81742b2de0e9de60.webp)

## Programuokite dirvožemio drėgmės jutiklio programą

Dabar dirvožemio drėgmės jutiklio programa gali būti programuojama naudojant CounterFit jutiklius.

### Užduotis - Programuokite dirvožemio drėgmės jutiklio programą

Programuokite dirvožemio drėgmės jutiklio programą.

1. Įsitikinkite, kad `soil-moisture-sensor` programa atidaryta VS Code.

1. Atidarykite `app.py` failą.

1. Pridėkite šį kodą į `app.py` viršų, kad prijungtumėte programą prie CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Pridėkite šį kodą į `app.py` failą, kad importuotumėte reikalingas bibliotekas:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    `import time` komanda importuoja `time` modulį, kuris bus naudojamas vėliau šiame užduotyje.

    `from counterfit_shims_grove.adc import ADC` komanda importuoja `ADC` klasę, kad galėtumėte sąveikauti su virtualiu analoginiu skaitmeniniu keitikliu, kuris gali prisijungti prie CounterFit jutiklio.

1. Pridėkite šį kodą žemiau, kad sukurtumėte `ADC` klasės egzempliorių:

    ```python
    adc = ADC()
    ```

1. Sukurkite begalinį ciklą, kuris nuskaito ADC vertę iš Pin 0 ir rašo rezultatą į konsolę. Šis ciklas gali miegoti 10 sekundžių tarp nuskaitymų.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. CounterFit programoje pakeiskite dirvožemio drėgmės jutiklio vertę, kurią programa nuskaitys. Tai galite padaryti dviem būdais:

    * Įveskite skaičių į *Value* laukelį dirvožemio drėgmės jutikliui, tada paspauskite **Set** mygtuką. Skaičius, kurį įvedėte, bus vertė, kurią grąžins jutiklis.

    * Pažymėkite *Random* žymės langelį ir įveskite *Min* bei *Max* vertes, tada paspauskite **Set** mygtuką. Kiekvieną kartą, kai jutiklis nuskaito vertę, jis grąžins atsitiktinį skaičių tarp *Min* ir *Max*.

1. Paleiskite Python programą. Matysite dirvožemio drėgmės matavimus, parašytus konsolėje. Pakeiskite *Value* arba *Random* nustatymus, kad pamatytumėte, kaip keičiasi vertė.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Šį kodą galite rasti [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device) aplanke.

😀 Jūsų dirvožemio drėgmės jutiklio programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.