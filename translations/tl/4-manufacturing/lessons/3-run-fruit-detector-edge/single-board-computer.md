<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T21:14:41+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "tl"
}
-->
# Mag-classify ng larawan gamit ang IoT Edge-based na image classifier - Virtual IoT Hardware at Raspberry Pi

Sa bahaging ito ng aralin, gagamitin mo ang Image Classifier na tumatakbo sa IoT Edge device.

## Gamitin ang IoT Edge classifier

Ang IoT device ay maaaring i-redirect upang gamitin ang IoT Edge image classifier. Ang URL para sa Image Classifier ay `http://<IP address o pangalan>/image`, palitan ang `<IP address o pangalan>` ng IP address o host name ng computer na nagpapatakbo ng IoT Edge.

Ang Python library para sa Custom Vision ay gumagana lamang sa mga modelong naka-host sa cloud, hindi sa mga modelong naka-host sa IoT Edge. Ibig sabihin, kailangan mong gamitin ang REST API upang tawagin ang classifier.

### Gawain - gamitin ang IoT Edge classifier

1. Buksan ang proyekto na `fruit-quality-detector` sa VS Code kung hindi pa ito nakabukas. Kung gumagamit ka ng virtual IoT device, siguraduhing naka-activate ang virtual environment.

1. Buksan ang file na `app.py`, at tanggalin ang mga import statement mula sa `azure.cognitiveservices.vision.customvision.prediction` at `msrest.authentication`.

1. Idagdag ang sumusunod na import sa itaas ng file:

    ```python
    import requests
    ```

1. Tanggalin ang lahat ng code pagkatapos ma-save ang larawan sa isang file, mula sa `image_file.write(image.read())` hanggang sa dulo ng file.

1. Idagdag ang sumusunod na code sa dulo ng file:

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

    Palitan ang `<URL>` ng URL para sa iyong classifier.

    Ang code na ito ay gumagawa ng REST POST request sa classifier, ipinapadala ang larawan bilang body ng request. Ang mga resulta ay bumabalik bilang JSON, at ito ay dine-decode upang ipakita ang mga probabilities.

1. Patakbuhin ang iyong code, gamit ang iyong camera na nakatutok sa ilang prutas, o isang angkop na set ng larawan, o prutas na nakikita sa iyong webcam kung gumagamit ng virtual IoT hardware. Makikita mo ang output sa console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Maaari mong mahanap ang code na ito sa [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) o [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) na folder.

😀 Tagumpay ang iyong fruit quality classifier program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.