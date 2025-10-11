<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-10-11T11:43:30+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "et"
}
-->
# Klassifitseeri pilt IoT Edge-põhise pildiklassifikaatoriga - Virtuaalne IoT riistvara ja Raspberry Pi

Selles õppetunni osas kasutate IoT Edge seadmel töötavat pildiklassifikaatorit.

## Kasuta IoT Edge klassifikaatorit

IoT seadet saab suunata kasutama IoT Edge pildiklassifikaatorit. Pildiklassifikaatori URL on `http://<IP aadress või nimi>/image`, kus `<IP aadress või nimi>` asendatakse IoT Edge'i käitava arvuti IP-aadressi või hostinimega.

Python'i teek Custom Vision töötab ainult pilves hostitud mudelitega, mitte IoT Edge'il hostitud mudelitega. See tähendab, et peate klassifikaatori kutsumiseks kasutama REST API-d.

### Ülesanne - kasuta IoT Edge klassifikaatorit

1. Ava projekt `fruit-quality-detector` VS Code'is, kui see pole juba avatud. Kui kasutate virtuaalset IoT seadet, veenduge, et virtuaalne keskkond on aktiveeritud.

1. Ava fail `app.py` ja eemaldage import-lauseid `azure.cognitiveservices.vision.customvision.prediction` ja `msrest.authentication`.

1. Lisage faili algusesse järgmine import-lause:

    ```python
    import requests
    ```

1. Kustutage kogu kood pärast seda, kui pilt on salvestatud faili, alates `image_file.write(image.read())` kuni faili lõpuni.

1. Lisage faili lõppu järgmine kood:

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

    Asendage `<URL>` oma klassifikaatori URL-iga.

    See kood teeb REST POST-päringu klassifikaatorile, saates pildi päringu kehana. Tulemused tagastatakse JSON-vormingus, mis dekodeeritakse tõenäosuste kuvamiseks.

1. Käivitage oma kood, suunates kaamera mõnele puuviljale, sobivale pildikomplektile või puuviljadele, mis on nähtavad teie veebikaameras, kui kasutate virtuaalset IoT riistvara. Näete väljundit konsoolis:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Selle koodi leiate kaustast [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) või [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Teie puuviljade kvaliteedi klassifikaatori programm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.