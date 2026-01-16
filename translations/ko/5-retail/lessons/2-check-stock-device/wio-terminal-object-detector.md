<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-24T21:14:36+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "ko"
}
-->
# IoT 기기에서 객체 감지기 호출하기 - Wio Terminal

객체 감지기가 게시되면 IoT 기기에서 사용할 수 있습니다.

## 이미지 분류기 프로젝트 복사하기

대부분의 재고 감지기는 이전 강의에서 만든 이미지 분류기와 동일합니다.

### 작업 - 이미지 분류기 프로젝트 복사하기

1. [제조 프로젝트의 2강](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera)의 단계를 따라 ArduCam을 Wio Terminal에 연결하세요.

    카메라를 고정된 위치에 두고 싶을 수도 있습니다. 예를 들어, 케이블을 상자나 캔 위에 걸거나, 양면 테이프로 카메라를 상자에 고정하는 방법이 있습니다.

1. PlatformIO를 사용하여 새로운 Wio Terminal 프로젝트를 만드세요. 이 프로젝트의 이름을 `stock-counter`로 지정하세요.

1. [제조 프로젝트의 2강](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device)의 단계를 따라 카메라에서 이미지를 캡처하세요.

1. [제조 프로젝트의 2강](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device)의 단계를 따라 이미지 분류기를 호출하세요. 이 코드의 대부분은 객체를 감지하는 데 재사용됩니다.

## 분류기 코드를 이미지 감지기로 변경하기

이미지를 분류하는 데 사용한 코드는 객체를 감지하는 코드와 매우 유사합니다. 주요 차이점은 Custom Vision에서 얻은 URL과 호출 결과입니다.

### 작업 - 분류기 코드를 이미지 감지기로 변경하기

1. `main.cpp` 파일 상단에 다음 포함 지시문을 추가하세요:

    ```cpp
    #include <vector>
    ```

1. `classifyImage` 함수를 `detectStock`으로 이름을 변경하세요. 함수 이름과 `buttonPressed` 함수에서의 호출 모두 변경해야 합니다.

1. `detectStock` 함수 위에 낮은 확률의 감지를 필터링하기 위한 임계값을 선언하세요:

    ```cpp
    const float threshold = 0.3f;
    ```

    이미지 분류기는 태그당 하나의 결과만 반환하지만, 객체 감지기는 여러 결과를 반환하므로 낮은 확률의 결과는 필터링해야 합니다.

1. `detectStock` 함수 위에 예측을 처리하는 함수를 선언하세요:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    이 함수는 예측 목록을 받아 시리얼 모니터에 출력합니다.

1. `detectStock` 함수에서 예측을 반복하는 `for` 루프의 내용을 다음으로 교체하세요:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    이 코드는 예측을 반복하며 확률을 임계값과 비교합니다. 임계값보다 높은 확률을 가진 모든 예측은 `list`에 추가되고 `processPredictions` 함수로 전달됩니다.

1. 코드를 업로드하고 실행하세요. 카메라를 선반 위의 물체에 향하게 하고 C 버튼을 누르세요. 시리얼 모니터에서 출력을 확인할 수 있습니다:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 이미지에 적합한 값을 찾기 위해 `threshold`를 조정해야 할 수도 있습니다.

    촬영된 이미지를 확인할 수 있으며, Custom Vision의 **Predictions** 탭에서 이러한 값을 볼 수 있습니다.

    ![선반 위에 있는 4개의 토마토 페이스트 캔과 35.8%, 33.5%, 25.7%, 16.6%의 4개의 감지 결과](../../../../../translated_images/ko/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 이 코드는 [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 재고 카운터 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.