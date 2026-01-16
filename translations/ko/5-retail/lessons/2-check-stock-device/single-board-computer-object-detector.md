<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-24T21:07:22+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "ko"
}
-->
# IoT 기기에서 객체 감지기 호출하기 - 가상 IoT 하드웨어와 Raspberry Pi

객체 감지기가 게시되면 IoT 기기에서 사용할 수 있습니다.

## 이미지 분류 프로젝트 복사하기

대부분의 재고 감지기는 이전 수업에서 만든 이미지 분류기와 동일합니다.

### 작업 - 이미지 분류 프로젝트 복사하기

1. `stock-counter`라는 폴더를 만드세요. 가상 IoT 기기를 사용하는 경우에는 컴퓨터에, Raspberry Pi를 사용하는 경우에는 Raspberry Pi에 폴더를 만드세요. 가상 IoT 기기를 사용하는 경우 가상 환경을 설정해야 합니다.

1. 카메라 하드웨어를 설정하세요.

    * Raspberry Pi를 사용하는 경우 PiCamera를 장착해야 합니다. 또한 카메라를 고정된 위치에 설치하는 것이 좋습니다. 예를 들어, 케이블을 상자나 캔 위에 걸거나, 양면 테이프로 카메라를 상자에 고정할 수 있습니다.
    * 가상 IoT 기기를 사용하는 경우 CounterFit과 CounterFit PyCamera shim을 설치해야 합니다. 정지 이미지를 사용할 경우 객체 감지기가 아직 보지 못한 이미지를 캡처하세요. 웹캠을 사용할 경우 감지하려는 재고를 볼 수 있는 위치에 웹캠을 배치하세요.

1. [제조 프로젝트의 2번째 수업](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device)의 단계를 복제하여 카메라에서 이미지를 캡처하세요.

1. [제조 프로젝트의 2번째 수업](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device)의 단계를 복제하여 이미지 분류기를 호출하세요. 이 코드의 대부분은 객체를 감지하는 데 재사용됩니다.

## 분류기 코드를 객체 감지기로 변경하기

이미지를 분류하는 데 사용한 코드는 객체를 감지하는 코드와 매우 유사합니다. 주요 차이점은 Custom Vision SDK에서 호출하는 메서드와 호출 결과입니다.

### 작업 - 분류기 코드를 객체 감지기로 변경하기

1. 이미지를 분류하고 예측을 처리하는 세 줄의 코드를 삭제하세요:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    이 세 줄을 제거하세요.

1. 이미지를 감지하는 다음 코드를 추가하세요:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    이 코드는 `detect_image` 메서드를 호출하여 객체 감지기를 실행합니다. 그런 다음 특정 임계값 이상의 확률을 가진 모든 예측을 수집하여 콘솔에 출력합니다.

    이미지 분류기는 태그당 하나의 결과만 반환하지만, 객체 감지기는 여러 결과를 반환하므로 확률이 낮은 결과는 필터링해야 합니다.

1. 이 코드를 실행하면 이미지를 캡처하고 객체 감지기에 이미지를 보내며 감지된 객체를 출력합니다. 가상 IoT 기기를 사용하는 경우 CounterFit에서 적절한 이미지를 설정하거나 웹캠이 선택되었는지 확인하세요. Raspberry Pi를 사용하는 경우 카메라가 선반 위의 객체를 가리키고 있는지 확인하세요.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 이미지에 적합한 `threshold` 값을 조정해야 할 수도 있습니다.

    캡처된 이미지를 확인할 수 있으며, Custom Vision의 **Predictions** 탭에서 이러한 값을 볼 수 있습니다.

    ![선반 위에 있는 4개의 토마토 페이스트 캔과 각각 35.8%, 33.5%, 25.7%, 16.6%의 감지 결과](../../../../../translated_images/ko/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 이 코드는 [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) 또는 [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device) 폴더에서 찾을 수 있습니다.

😀 재고 카운터 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전이 권위 있는 출처로 간주되어야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.