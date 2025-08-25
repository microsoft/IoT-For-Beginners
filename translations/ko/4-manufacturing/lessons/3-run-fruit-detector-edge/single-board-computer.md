<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-24T21:48:06+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "ko"
}
-->
# IoT Edge 기반 이미지 분류기를 사용하여 이미지 분류하기 - 가상 IoT 하드웨어와 Raspberry Pi

이 수업의 이 부분에서는 IoT Edge 장치에서 실행되는 이미지 분류기를 사용하게 됩니다.

## IoT Edge 분류기 사용하기

IoT 장치는 IoT Edge 이미지 분류기를 사용하도록 재설정할 수 있습니다. 이미지 분류기의 URL은 `http://<IP address or name>/image`이며, `<IP address or name>`을 IoT Edge를 실행 중인 컴퓨터의 IP 주소나 호스트 이름으로 대체하면 됩니다.

Custom Vision의 Python 라이브러리는 클라우드에 호스팅된 모델에서만 작동하며, IoT Edge에 호스팅된 모델에서는 작동하지 않습니다. 따라서 분류기를 호출하려면 REST API를 사용해야 합니다.

### 작업 - IoT Edge 분류기 사용하기

1. `fruit-quality-detector` 프로젝트를 VS Code에서 엽니다. 아직 열려 있지 않은 경우 열어주세요. 가상 IoT 장치를 사용하는 경우 가상 환경이 활성화되어 있는지 확인하세요.

1. `app.py` 파일을 열고, `azure.cognitiveservices.vision.customvision.prediction` 및 `msrest.authentication`에서 가져오는 import 문을 제거하세요.

1. 파일 상단에 다음 import 문을 추가하세요:

    ```python
    import requests
    ```

1. 이미지가 파일에 저장된 후의 모든 코드를 삭제하세요. 즉, `image_file.write(image.read())`부터 파일 끝까지의 코드를 삭제합니다.

1. 파일 끝에 다음 코드를 추가하세요:

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

    `<URL>`을 분류기의 URL로 대체하세요.

    이 코드는 분류기로 REST POST 요청을 보내며, 요청 본문에 이미지를 전송합니다. 결과는 JSON 형식으로 반환되며, 이를 디코딩하여 확률을 출력합니다.

1. 카메라를 과일에 맞추거나 적절한 이미지 세트를 사용하거나, 가상 IoT 하드웨어를 사용하는 경우 웹캠에 과일이 보이도록 하여 코드를 실행하세요. 콘솔에서 다음과 같은 출력 결과를 확인할 수 있습니다:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 이 코드는 [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) 또는 [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) 폴더에서 찾을 수 있습니다.

😀 과일 품질 분류기 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.