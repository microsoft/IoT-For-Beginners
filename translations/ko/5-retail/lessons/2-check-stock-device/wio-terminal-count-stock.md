<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-24T21:12:00+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "ko"
}
-->
# IoT 기기 - Wio Terminal로 재고 계산하기

예측 결과와 경계 상자를 조합하여 이미지에서 재고를 계산할 수 있습니다.

## 재고 계산하기

![각 캔 주위에 경계 상자가 표시된 토마토 페이스트 캔 4개](../../../../../translated_images/ko/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

위 이미지에서 경계 상자들이 약간 겹쳐져 있습니다. 만약 이 겹침이 훨씬 더 크다면, 경계 상자가 동일한 객체를 나타낼 수 있습니다. 객체를 올바르게 계산하려면 겹침이 큰 상자는 무시해야 합니다.

### 작업 - 겹침을 무시하고 재고 계산하기

1. `stock-counter` 프로젝트를 열지 않았다면 열어주세요.

1. `processPredictions` 함수 위에 다음 코드를 추가하세요:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    이 코드는 경계 상자가 동일한 객체로 간주되기 전에 허용되는 겹침 비율을 정의합니다. 0.20은 20% 겹침을 정의합니다.

1. 그 아래, 그리고 `processPredictions` 함수 위에 두 사각형 간의 겹침을 계산하는 코드를 추가하세요:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    이 코드는 이미지를 나타내는 점을 저장하기 위한 `Point` 구조체와, 좌상단 및 우하단 좌표를 사용하여 사각형을 정의하는 `Rect` 구조체를 정의합니다. 그런 다음 좌상단 및 우하단 좌표를 사용하여 사각형의 면적을 계산하는 `area` 함수를 정의합니다.

    이후 두 사각형의 겹치는 면적을 계산하는 `overlappingArea` 함수를 정의합니다. 겹치지 않으면 0을 반환합니다.

1. `overlappingArea` 함수 아래에 경계 상자를 `Rect`로 변환하는 함수를 선언하세요:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    이 함수는 객체 감지기의 예측 결과를 받아 경계 상자를 추출하고, 경계 상자의 값을 사용하여 사각형을 정의합니다. 오른쪽은 왼쪽에 너비를 더한 값으로 계산됩니다. 아래쪽은 위쪽에 높이를 더한 값으로 계산됩니다.

1. 예측 결과를 서로 비교해야 하며, 두 예측 결과가 임계값 이상의 겹침을 가지면 하나를 삭제해야 합니다. 겹침 임계값은 백분율이므로, 가장 작은 경계 상자의 크기에 곱하여 겹침이 경계 상자의 주어진 백분율을 초과하는지 확인해야 합니다. `processPredictions` 함수의 내용을 삭제하세요.

1. 빈 `processPredictions` 함수에 다음 코드를 추가하세요:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    이 코드는 겹치지 않는 예측 결과를 저장할 벡터를 선언합니다. 그런 다음 모든 예측 결과를 반복하며 경계 상자에서 `Rect`를 생성합니다.

    이후 현재 예측 결과 이후의 나머지 예측 결과를 반복합니다. 이는 예측 결과가 여러 번 비교되지 않도록 합니다 - 예를 들어 1과 2를 비교한 후에는 2와 1을 다시 비교할 필요가 없으며, 3, 4 등과만 비교하면 됩니다.

    각 예측 결과 쌍에 대해 겹치는 면적을 계산합니다. 그런 다음 가장 작은 경계 상자의 면적과 비교합니다 - 겹침이 가장 작은 경계 상자의 임계값 백분율을 초과하면 해당 예측 결과는 통과하지 못한 것으로 표시됩니다. 모든 겹침을 비교한 후 예측 결과가 검사를 통과하면 `passed_predictions` 컬렉션에 추가됩니다.

    > 💁 이 방법은 겹침을 제거하는 매우 단순한 방식으로, 겹치는 쌍에서 첫 번째 것을 제거합니다. 실제 코드에서는 여러 객체 간의 겹침을 고려하거나 하나의 경계 상자가 다른 경계 상자에 포함되는 경우를 처리하는 등의 추가 논리를 넣어야 할 것입니다.

1. 이후, 통과된 예측 결과의 세부 정보를 시리얼 모니터에 보내는 코드를 추가하세요:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    이 코드는 통과된 예측 결과를 반복하며 시리얼 모니터에 세부 정보를 출력합니다.

1. 그 아래에 계산된 항목 수를 시리얼 모니터에 출력하는 코드를 추가하세요:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    이는 IoT 서비스로 전송되어 재고 수준이 낮을 경우 경고를 보낼 수 있습니다.

1. 코드를 업로드하고 실행하세요. 카메라를 선반 위의 물체에 맞추고 C 버튼을 누르세요. `overlap_threshold` 값을 조정하여 예측 결과가 무시되는 것을 확인해보세요.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 이 코드는 [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) 폴더에서 찾을 수 있습니다.

😀 재고 계산 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.