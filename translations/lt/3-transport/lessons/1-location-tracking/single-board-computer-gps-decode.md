<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-28T19:38:34+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "lt"
}
-->
# Dekoduokite GPS duomenis - Virtuali IoT įranga ir Raspberry Pi

Šioje pamokos dalyje jūs dekoduosite NMEA pranešimus, kuriuos iš GPS jutiklio perskaito Raspberry Pi arba virtualus IoT įrenginys, ir ištrauksite platumos bei ilgumos koordinates.

## Dekoduokite GPS duomenis

Kai neapdoroti NMEA duomenys yra perskaitomi iš nuosekliojo prievado, juos galima dekoduoti naudojant atvirojo kodo NMEA biblioteką.

### Užduotis - dekoduokite GPS duomenis

Užprogramuokite įrenginį, kad jis dekoduotų GPS duomenis.

1. Atidarykite `gps-sensor` programėlės projektą, jei jis dar neatidarytas.

1. Įdiekite `pynmea2` Pip paketą. Šis paketas turi kodą, skirtą NMEA pranešimams dekoduoti.

    ```sh
    pip3 install pynmea2
    ```

1. Pridėkite šį kodą prie `app.py` failo importų, kad importuotumėte `pynmea2` modulį:

    ```python
    import pynmea2
    ```

1. Pakeiskite `print_gps_data` funkcijos turinį šiuo kodu:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    Šis kodas naudos `pynmea2` biblioteką, kad išanalizuotų eilutę, perskaitytą iš UART nuosekliojo prievado.

    Jei pranešimo sakinio tipas yra `GGA`, tai yra pozicijos nustatymo pranešimas, kuris bus apdorotas. Platumos ir ilgumos reikšmės yra perskaitomos iš pranešimo ir konvertuojamos į dešimtainius laipsnius iš NMEA `(d)ddmm.mmmm` formato. Funkcija `dm_to_sd` atlieka šį konvertavimą.

    Tada patikrinama platumos kryptis, ir jei platuma yra pietų pusrutulyje, reikšmė konvertuojama į neigiamą skaičių. Tas pats taikoma ilgumai – jei ji yra vakarų pusrutulyje, ji taip pat konvertuojama į neigiamą skaičių.

    Galiausiai koordinatės yra atspausdinamos konsolėje kartu su palydovų, naudotų vietos nustatymui, skaičiumi.

1. Paleiskite kodą. Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad CounterFit programėlė veikia ir GPS duomenys yra siunčiami.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Šį kodą galite rasti [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) aplanke arba [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi) aplanke.

😀 Jūsų GPS jutiklio programa su duomenų dekodavimu buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.