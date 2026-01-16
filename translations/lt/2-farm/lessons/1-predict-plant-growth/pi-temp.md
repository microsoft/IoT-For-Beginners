<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-28T20:35:35+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "lt"
}
-->
# Matuokite temperatūrą - Raspberry Pi

Šioje pamokos dalyje pridėsite temperatūros jutiklį prie savo Raspberry Pi.

## Aparatinė įranga

Jutiklis, kurį naudosite, yra [DHT11 drėgmės ir temperatūros jutiklis](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), kuris sujungia 2 jutiklius viename korpuse. Tai gana populiarus jutiklis, nes daugelis komerciškai prieinamų jutiklių sujungia temperatūros, drėgmės ir kartais atmosferos slėgio matavimus. Temperatūros jutiklio komponentas yra neigiamo temperatūros koeficiento (NTC) termistorius – termistorius, kurio varža mažėja, kai temperatūra didėja.

Tai yra skaitmeninis jutiklis, todėl jis turi integruotą ADC, kuris sukuria skaitmeninį signalą su temperatūros ir drėgmės duomenimis, kuriuos gali nuskaityti mikrovaldiklis.

### Prijunkite temperatūros jutiklį

Grove temperatūros jutiklį galima prijungti prie Raspberry Pi.

#### Užduotis

Prijunkite temperatūros jutiklį

![Grove temperatūros jutiklis](../../../../../translated_images/lt/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Įstatykite vieną Grove kabelio galą į lizdą ant drėgmės ir temperatūros jutiklio. Jis įsistatys tik viena kryptimi.

1. Išjungę Raspberry Pi, prijunkite kitą Grove kabelio galą prie skaitmeninio lizdo, pažymėto **D5**, esančio ant Grove Base hat, prijungto prie Pi. Šis lizdas yra antras iš kairės, eilėje šalia GPIO pinų.

![Grove temperatūros jutiklis prijungtas prie lizdo A0](../../../../../translated_images/lt/pi-temperature-sensor.3ff82fff672c8e56.webp)

## Užprogramuokite temperatūros jutiklį

Dabar įrenginį galima užprogramuoti naudoti prijungtą temperatūros jutiklį.

### Užduotis

Užprogramuokite įrenginį.

1. Įjunkite Pi ir palaukite, kol jis įsijungs.

1. Paleiskite VS Code tiesiogiai Pi įrenginyje arba prisijunkite per Remote SSH plėtinį.

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip nustatyti ir paleisti VS Code 1-oje pamokoje](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Terminale sukurkite naują aplanką `pi` naudotojo pagrindiniame kataloge, pavadintą `temperature-sensor`. Sukurkite šiame aplanke failą, pavadintą `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Atidarykite šį aplanką VS Code.

1. Norint naudoti temperatūros ir drėgmės jutiklį, reikia įdiegti papildomą Pip paketą. VS Code terminale vykdykite šią komandą, kad įdiegtumėte šį Pip paketą Pi įrenginyje:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Pridėkite šį kodą į `app.py` failą, kad importuotumėte reikalingas bibliotekas:

    ```python
    import time
    from seeed_dht import DHT
    ```

    `from seeed_dht import DHT` eilutė importuoja `DHT` jutiklio klasę, skirtą sąveikai su Grove temperatūros jutikliu iš `seeed_dht` modulio.

1. Pridėkite šį kodą po aukščiau esančio kodo, kad sukurtumėte klasės egzempliorių, kuris valdo temperatūros jutiklį:

    ```python
    sensor = DHT("11", 5)
    ```

    Tai deklaruoja `DHT` klasės egzempliorių, kuris valdo **D**igital **H**umidity ir **T**emperature jutiklį. Pirmasis parametras nurodo, kad naudojamas *DHT11* jutiklis – biblioteka palaiko ir kitus šio jutiklio variantus. Antrasis parametras nurodo, kad jutiklis prijungtas prie skaitmeninio lizdo `D5` ant Grove Base hat.

    > ✅ Atminkite, kad visi lizdai turi unikalius pinų numerius. Pinai 0, 2, 4 ir 6 yra analoginiai, o pinai 5, 16, 18, 22, 24 ir 26 yra skaitmeniniai.

1. Pridėkite begalinę kilpą po aukščiau esančiu kodu, kad nuskaitytumėte temperatūros jutiklio reikšmę ir atspausdintumėte ją konsolėje:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    `sensor.read()` iškvietimas grąžina drėgmės ir temperatūros duomenų porą. Jums reikia tik temperatūros reikšmės, todėl drėgmė ignoruojama. Temperatūros reikšmė tada atspausdinama konsolėje.

1. Pridėkite trumpą dešimties sekundžių pauzę kilpos pabaigoje, nes temperatūros lygiai neturi būti tikrinami nuolat. Pauzė sumažina įrenginio energijos suvartojimą.

    ```python
    time.sleep(10)
    ```

1. VS Code terminale vykdykite šią komandą, kad paleistumėte savo Python programą:

    ```sh
    python3 app.py
    ```

    Turėtumėte matyti temperatūros reikšmes, rodomas konsolėje. Naudokite ką nors, kad sušildytumėte jutiklį, pavyzdžiui, prispauskite jį nykščiu arba naudokite ventiliatorių, kad pamatytumėte, kaip reikšmės keičiasi:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Šį kodą galite rasti [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi) aplanke.

😀 Jūsų temperatūros jutiklio programa pavyko!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus aiškinimus, kylančius dėl šio vertimo naudojimo.