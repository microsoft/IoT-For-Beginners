<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T20:51:38+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "hu"
}
-->
# Kép osztályozása IoT Edge alapú képosztályozóval - Virtuális IoT Hardver és Raspberry Pi

A lecke ezen részében az IoT Edge eszközön futó képosztályozót fogod használni.

## Az IoT Edge osztályozó használata

Az IoT eszközt át lehet irányítani, hogy az IoT Edge képosztályozót használja. A Képosztályozó URL-je `http://<IP cím vagy név>/image`, ahol `<IP cím vagy név>` helyére az IoT Edge-et futtató számítógép IP címét vagy hosztnevét kell beírni.

A Custom Vision Python könyvtár csak felhőben hosztolt modellekkel működik, IoT Edge-en hosztolt modellekkel nem. Ez azt jelenti, hogy a REST API-t kell használnod az osztályozó meghívásához.

### Feladat - az IoT Edge osztályozó használata

1. Nyisd meg a `fruit-quality-detector` projektet a VS Code-ban, ha még nincs megnyitva. Ha virtuális IoT eszközt használsz, győződj meg róla, hogy a virtuális környezet aktiválva van.

1. Nyisd meg az `app.py` fájlt, és távolítsd el az `azure.cognitiveservices.vision.customvision.prediction` és `msrest.authentication` importálásokat.

1. Add hozzá a következő importálást a fájl tetejére:

    ```python
    import requests
    ```

1. Töröld ki az összes kódot, ami azután van, hogy a kép fájlba mentésre kerül, az `image_file.write(image.read())` sortól a fájl végéig.

1. Add hozzá a következő kódot a fájl végére:

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

    Cseréld ki a `<URL>` helyére az osztályozód URL-jét.

    Ez a kód egy REST POST kérést küld az osztályozónak, a képet a kérés törzseként küldve. Az eredmények JSON formátumban érkeznek vissza, amelyet dekódolva kiírja a valószínűségeket.

1. Futtasd a kódodat, miközben a kamerád valamilyen gyümölcsre, egy megfelelő képkészletre, vagy virtuális IoT hardver esetén a webkamerád által látható gyümölcsre irányul. Az eredményeket a konzolban fogod látni:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Ezt a kódot megtalálod a [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) vagy a [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) mappában.

😀 A gyümölcsminőség-osztályozó programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.