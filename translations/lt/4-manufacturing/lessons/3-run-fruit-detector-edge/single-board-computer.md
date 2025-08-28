<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-28T19:07:57+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "lt"
}
-->
# Klasifikuokite vaizdą naudodami IoT Edge pagrįstą vaizdų klasifikatorių – virtuali IoT įranga ir Raspberry Pi

Šioje pamokos dalyje naudosite vaizdų klasifikatorių, veikiantį IoT Edge įrenginyje.

## Naudokite IoT Edge klasifikatorių

IoT įrenginį galima peradresuoti naudoti IoT Edge vaizdų klasifikatorių. Vaizdų klasifikatoriaus URL yra `http://<IP adresas arba pavadinimas>/image`, kur `<IP adresas arba pavadinimas>` pakeičiamas į kompiuterio, kuriame veikia IoT Edge, IP adresą arba pagrindinį vardą.

Python biblioteka Custom Vision veikia tik su debesyje talpinamais modeliais, o ne su modeliais, talpinamais IoT Edge. Tai reiškia, kad turėsite naudoti REST API, kad galėtumėte iškviesti klasifikatorių.

### Užduotis – naudoti IoT Edge klasifikatorių

1. Atidarykite `fruit-quality-detector` projektą VS Code, jei jis dar neatidarytas. Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad virtuali aplinka yra aktyvuota.

1. Atidarykite `app.py` failą ir pašalinkite importo eilutes iš `azure.cognitiveservices.vision.customvision.prediction` ir `msrest.authentication`.

1. Pridėkite šį importą failo viršuje:

    ```python
    import requests
    ```

1. Ištrinkite visą kodą po to, kai vaizdas išsaugomas faile, pradedant nuo `image_file.write(image.read())` iki failo pabaigos.

1. Pridėkite šį kodą failo pabaigoje:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Pakeiskite `<URL>` į savo klasifikatoriaus URL.

    Šis kodas atlieka REST POST užklausą klasifikatoriui, siunčiant vaizdą kaip užklausos turinį. Rezultatai grįžta JSON formatu, kuris yra dekoduojamas ir išspausdinamas su tikimybėmis.

1. Paleiskite savo kodą, nukreipę kamerą į vaisius, tinkamą vaizdų rinkinį arba vaisius, matomus jūsų internetinėje kameroje, jei naudojate virtualią IoT įrangą. Konsolėje pamatysite išvestį:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Šį kodą galite rasti aplankuose [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) arba [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Jūsų vaisių kokybės klasifikatoriaus programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipkite dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus aiškinimus, kylančius dėl šio vertimo naudojimo.