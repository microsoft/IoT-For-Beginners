<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T20:51:29+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "sw"
}
-->
# Tambua picha ukitumia kifaa cha IoT Edge kinachotegemea kionyeshi picha - Vifaa vya Kawaida vya IoT na Raspberry Pi

Katika sehemu hii ya somo, utatumia Kionyeshi Picha kinachoendesha kwenye kifaa cha IoT Edge.

## Tumia kionyeshi cha IoT Edge

Kifaa cha IoT kinaweza kuelekezwa kutumia kionyeshi cha picha cha IoT Edge. URL ya Kionyeshi Picha ni `http://<IP address or name>/image`, ukibadilisha `<IP address or name>` na anwani ya IP au jina la mwenyeji wa kompyuta inayoendesha IoT Edge.

Maktaba ya Python ya Custom Vision inafanya kazi tu na mifano inayohifadhiwa kwenye wingu, si mifano inayohifadhiwa kwenye IoT Edge. Hii inamaanisha utahitaji kutumia REST API kuita kionyeshi.

### Kazi - tumia kionyeshi cha IoT Edge

1. Fungua mradi wa `fruit-quality-detector` kwenye VS Code ikiwa haujafunguliwa tayari. Ikiwa unatumia kifaa cha kawaida cha IoT, hakikisha mazingira ya kawaida yamewezeshwa.

1. Fungua faili ya `app.py`, na uondoe kauli za kuingiza kutoka `azure.cognitiveservices.vision.customvision.prediction` na `msrest.authentication`.

1. Ongeza uingizaji ufuatao juu ya faili:

    ```python
    import requests
    ```

1. Futa msimbo wote baada ya picha kuhifadhiwa kwenye faili, kuanzia `image_file.write(image.read())` hadi mwisho wa faili.

1. Ongeza msimbo ufuatao mwisho wa faili:

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

    Badilisha `<URL>` na URL ya kionyeshi chako.

    Msimbo huu unafanya ombi la REST POST kwa kionyeshi, ukituma picha kama mwili wa ombi. Matokeo yanarudi kama JSON, na haya yanatolewa ili kuonyesha uwezekano.

1. Endesha msimbo wako, ukiwa na kamera yako ikielekea kwenye matunda fulani, au seti sahihi ya picha, au matunda yanayoonekana kwenye kamera ya wavuti ikiwa unatumia vifaa vya kawaida vya IoT. Utaona matokeo kwenye koni:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) au [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Programu yako ya kutambua ubora wa matunda imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.