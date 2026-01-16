<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-24T21:31:48+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "ko"
}
-->
# 이미지 분류하기 - 가상 IoT 하드웨어와 Raspberry Pi

이 강의의 이 부분에서는 카메라로 촬영한 이미지를 Custom Vision 서비스로 보내 분류합니다.

## 이미지를 Custom Vision으로 보내기

Custom Vision 서비스는 이미지를 분류하기 위해 사용할 수 있는 Python SDK를 제공합니다.

### 작업 - 이미지를 Custom Vision으로 보내기

1. VS Code에서 `fruit-quality-detector` 폴더를 엽니다. 가상 IoT 디바이스를 사용하는 경우, 터미널에서 가상 환경이 실행 중인지 확인하세요.

1. Custom Vision으로 이미지를 보내기 위한 Python SDK는 Pip 패키지로 제공됩니다. 다음 명령어로 설치하세요:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. `app.py` 파일 상단에 다음 import 문을 추가하세요:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    이는 Custom Vision 라이브러리에서 몇 가지 모듈을 가져옵니다. 하나는 예측 키로 인증하기 위한 것이고, 다른 하나는 Custom Vision을 호출할 수 있는 예측 클라이언트 클래스를 제공합니다.

1. 파일 끝에 다음 코드를 추가하세요:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    `<prediction_url>`을 이전 강의에서 *Prediction URL* 대화 상자에서 복사한 URL로 바꾸세요. `<prediction key>`는 동일한 대화 상자에서 복사한 예측 키로 바꾸세요.

1. *Prediction URL* 대화 상자에서 제공된 예측 URL은 REST 엔드포인트를 직접 호출할 때 사용하도록 설계되었습니다. Python SDK는 URL의 일부를 다른 위치에서 사용합니다. 다음 코드를 추가하여 이 URL을 필요한 부분으로 나누세요:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    이는 URL을 분리하여 `https://<location>.api.cognitive.microsoft.com`와 같은 엔드포인트, 프로젝트 ID, 게시된 반복(iteration)의 이름을 추출합니다.

1. 다음 코드를 사용하여 예측을 수행할 예측기 객체를 생성하세요:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials`는 예측 키를 래핑합니다. 그런 다음 이를 사용하여 엔드포인트를 가리키는 예측 클라이언트 객체를 생성합니다.

1. 다음 코드를 사용하여 이미지를 Custom Vision으로 보내세요:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    이는 이미지를 시작 지점으로 되감은 후, 예측 클라이언트로 보냅니다.

1. 마지막으로, 다음 코드를 사용하여 결과를 표시하세요:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    이는 반환된 모든 예측을 반복하며 터미널에 표시합니다. 반환된 확률은 0에서 1 사이의 부동 소수점 숫자이며, 0은 태그와 일치할 확률이 0%임을, 1은 100%임을 나타냅니다.

    > 💁 이미지 분류기는 사용된 모든 태그에 대한 확률을 반환합니다. 각 태그는 이미지가 해당 태그와 일치할 확률을 가집니다.

1. 카메라를 과일에 향하게 하거나 적절한 이미지 세트를 사용하거나, 가상 IoT 하드웨어를 사용하는 경우 웹캠에 과일이 보이도록 하여 코드를 실행하세요. 콘솔에서 출력을 확인할 수 있습니다:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    촬영된 이미지를 확인할 수 있으며, 이러한 값은 Custom Vision의 **Predictions** 탭에서도 볼 수 있습니다.

    ![Custom Vision에서 바나나가 익었을 확률 56.8%, 익지 않았을 확률 43.1%로 예측된 모습](../../../../../translated_images/ko/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 이 코드는 [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) 또는 [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) 폴더에서 찾을 수 있습니다.

😀 과일 품질 분류기 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.