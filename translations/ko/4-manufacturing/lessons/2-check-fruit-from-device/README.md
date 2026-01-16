<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-24T21:27:56+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "ko"
}
-->
# IoT 기기를 사용한 과일 품질 확인

![이 강의의 스케치노트 개요](../../../../../translated_images/ko/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> 스케치노트: [Nitya Narasimhan](https://github.com/nitya). 이미지를 클릭하면 더 큰 버전을 볼 수 있습니다.

## 강의 전 퀴즈

[강의 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## 소개

지난 강의에서는 이미지 분류기에 대해 배우고, 이를 훈련시켜 좋은 과일과 나쁜 과일을 구분하는 방법을 익혔습니다. 이 이미지 분류기를 IoT 애플리케이션에서 사용하려면, 카메라를 사용해 이미지를 캡처하고 이를 클라우드로 전송하여 분류해야 합니다.

이번 강의에서는 카메라 센서와 이를 IoT 기기에서 사용해 이미지를 캡처하는 방법을 배웁니다. 또한 IoT 기기에서 이미지 분류기를 호출하는 방법도 학습합니다.

이번 강의에서 다룰 내용은 다음과 같습니다:

* [카메라 센서](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [IoT 기기를 사용해 이미지 캡처](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [이미지 분류기 게시](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [IoT 기기에서 이미지 분류](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [모델 개선](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## 카메라 센서

카메라 센서는 이름에서 알 수 있듯이 IoT 기기에 연결할 수 있는 카메라입니다. 정지 이미지를 촬영하거나 스트리밍 비디오를 캡처할 수 있습니다. 일부는 원시 이미지 데이터를 반환하고, 다른 일부는 JPEG 또는 PNG와 같은 이미지 파일로 데이터를 압축합니다. 일반적으로 IoT 기기와 함께 사용하는 카메라는 우리가 흔히 사용하는 카메라보다 작고 해상도가 낮지만, 고해상도 카메라도 구할 수 있으며 이는 고급 스마트폰과 견줄 만합니다. 교체 가능한 렌즈, 다중 카메라 설정, 적외선 열화상 카메라, 자외선 카메라 등 다양한 옵션이 있습니다.

![장면의 빛이 렌즈를 통과해 CMOS 센서에 초점이 맞춰지는 모습](../../../../../translated_images/ko/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

대부분의 카메라 센서는 각 픽셀이 포토다이오드인 이미지 센서를 사용합니다. 렌즈는 이미지를 이미지 센서에 초점 맞추고, 수천 또는 수백만 개의 포토다이오드가 각 픽셀에 떨어지는 빛을 감지하여 픽셀 데이터로 기록합니다.

> 💁 렌즈는 이미지를 뒤집습니다. 카메라 센서는 이미지를 다시 올바른 방향으로 뒤집습니다. 이는 우리의 눈에서도 동일합니다. 우리가 보는 것은 눈 뒤쪽에서 거꾸로 감지되며, 뇌가 이를 교정합니다.

> 🎓 이미지 센서는 Active-Pixel Sensor(APS)로 알려져 있으며, 가장 인기 있는 APS 유형은 상보성 금속 산화물 반도체 센서(CMOS)입니다. 카메라 센서에 대해 CMOS 센서라는 용어를 들어본 적이 있을 것입니다.

카메라 센서는 디지털 센서로, 일반적으로 통신을 제공하는 라이브러리의 도움을 받아 디지털 데이터로 이미지 데이터를 전송합니다. 카메라는 SPI와 같은 프로토콜을 사용해 대량의 데이터를 전송할 수 있습니다. 이미지는 온도 센서와 같은 센서에서 나오는 단일 숫자보다 훨씬 큽니다.

✅ IoT 기기에서 이미지 크기와 관련된 제한 사항은 무엇일까요? 특히 마이크로컨트롤러 하드웨어의 제약을 생각해 보세요.

## IoT 기기를 사용해 이미지 캡처

IoT 기기를 사용해 분류할 이미지를 캡처할 수 있습니다.

### 과제 - IoT 기기를 사용해 이미지 캡처

다음 가이드를 따라 IoT 기기를 사용해 이미지를 캡처하세요:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [싱글보드 컴퓨터 - Raspberry Pi](pi-camera.md)
* [싱글보드 컴퓨터 - 가상 기기](virtual-device-camera.md)

## 이미지 분류기 게시

지난 강의에서 이미지 분류기를 훈련시켰습니다. IoT 기기에서 이를 사용하려면 모델을 게시해야 합니다.

### 모델 반복

지난 강의에서 모델을 훈련시킬 때 **성능(Performance)** 탭에서 측면에 반복(iterations)이 표시되는 것을 보았을 것입니다. 처음 모델을 훈련시켰을 때는 *Iteration 1*이 표시되었을 것입니다. 예측 이미지를 사용해 모델을 개선했을 때는 *Iteration 2*가 표시되었을 것입니다.

모델을 훈련시킬 때마다 새로운 반복이 생성됩니다. 이는 서로 다른 데이터 세트로 훈련된 모델의 다양한 버전을 추적하는 방법입니다. **빠른 테스트(Quick Test)**를 수행할 때 드롭다운 메뉴를 사용해 반복을 선택하고, 여러 반복 간의 결과를 비교할 수 있습니다.

반복에 만족하면 이를 게시해 외부 애플리케이션에서 사용할 수 있도록 만듭니다. 이렇게 하면 기기에서 사용하는 게시된 버전을 유지하면서 새로운 버전을 여러 반복에 걸쳐 작업한 후 만족할 때 게시할 수 있습니다.

### 과제 - 반복 게시

반복은 Custom Vision 포털에서 게시됩니다.

1. [CustomVision.ai](https://customvision.ai)에서 Custom Vision 포털을 열고 로그인합니다. 이미 열려 있지 않다면 열어주세요. 그런 다음 `fruit-quality-detector` 프로젝트를 엽니다.

1. 상단 옵션에서 **성능(Performance)** 탭을 선택합니다.

1. 측면의 *Iterations* 목록에서 최신 반복을 선택합니다.

1. 해당 반복의 **게시(Publish)** 버튼을 선택합니다.

    ![게시 버튼](../../../../../translated_images/ko/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. *모델 게시(Publish Model)* 대화 상자에서 *예측 리소스(Prediction resource)*를 지난 강의에서 생성한 `fruit-quality-detector-prediction` 리소스로 설정합니다. 이름은 `Iteration2`로 유지하고 **게시(Publish)** 버튼을 선택합니다.

1. 게시가 완료되면 **예측 URL(Prediction URL)** 버튼을 선택합니다. 여기에는 예측 API의 세부 정보가 표시되며, IoT 기기에서 모델을 호출할 때 필요합니다. 하단 섹션은 *이미지 파일이 있는 경우(If you have an image file)*로 라벨링되어 있으며, 필요한 세부 정보가 여기에 있습니다. 다음과 같은 URL을 복사하세요:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    여기서 `<location>`은 Custom Vision 리소스를 생성할 때 사용한 위치이고, `<id>`는 문자와 숫자로 이루어진 긴 ID입니다.

    또한 *예측 키(Prediction-Key)* 값도 복사하세요. 이는 모델을 호출할 때 전달해야 하는 보안 키입니다. 이 키를 전달하는 애플리케이션만 모델을 사용할 수 있으며, 다른 애플리케이션은 거부됩니다.

    ![예측 API 대화 상자에 표시된 URL과 키](../../../../../translated_images/ko/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ 새로운 반복이 게시되면 다른 이름을 갖게 됩니다. IoT 기기가 사용하는 반복을 변경하려면 어떻게 해야 할까요?

## IoT 기기에서 이미지 분류

이제 이 연결 정보를 사용해 IoT 기기에서 이미지 분류기를 호출할 수 있습니다.

### 과제 - IoT 기기에서 이미지 분류

다음 가이드를 따라 IoT 기기를 사용해 이미지를 분류하세요:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [싱글보드 컴퓨터 - Raspberry Pi/가상 IoT 기기](single-board-computer-classify-image.md)

## 모델 개선

IoT 기기에 연결된 카메라를 사용할 때 얻는 결과가 기대와 다를 수 있습니다. 예측이 컴퓨터에서 업로드한 이미지를 사용할 때만큼 정확하지 않을 수 있습니다. 이는 모델이 예측에 사용되는 데이터와 다른 데이터로 훈련되었기 때문입니다.

이미지 분류기의 최상의 결과를 얻으려면 예측에 사용되는 이미지와 최대한 유사한 이미지로 모델을 훈련시키는 것이 중요합니다. 예를 들어, 휴대폰 카메라를 사용해 훈련용 이미지를 캡처했다면, 이미지 품질, 선명도, 색상이 IoT 기기에 연결된 카메라와 다를 것입니다.

![IoT 기기로 촬영한 저해상도 바나나 사진과 휴대폰으로 촬영한 고해상도 바나나 사진](../../../../../translated_images/ko/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

위 이미지에서 왼쪽 바나나 사진은 Raspberry Pi 카메라로 촬영한 것이고, 오른쪽 사진은 동일한 바나나를 동일한 위치에서 iPhone으로 촬영한 것입니다. 품질 차이가 뚜렷합니다. iPhone 사진은 더 선명하고, 색상이 밝으며, 대비가 더 큽니다.

✅ IoT 기기가 캡처한 이미지가 잘못된 예측을 초래할 수 있는 다른 요인은 무엇일까요? IoT 기기가 사용될 환경을 생각해 보고, 이미지 캡처에 영향을 미칠 수 있는 요소를 고려해 보세요.

모델을 개선하려면 IoT 기기에서 캡처한 이미지를 사용해 모델을 재훈련할 수 있습니다.

### 과제 - 모델 개선

1. IoT 기기를 사용해 익은 과일과 익지 않은 과일의 이미지를 여러 장 분류하세요.

1. Custom Vision 포털에서 *예측(Predictions)* 탭의 이미지를 사용해 모델을 재훈련하세요.

    > ⚠️ [1강에서 분류기를 재훈련하는 방법이 필요하다면 해당 지침을 참조하세요](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. 훈련에 사용된 원본 이미지와 현재 이미지가 매우 다르다면, *훈련 이미지(Training Images)* 탭에서 원본 이미지를 모두 선택한 후 **삭제(Delete)** 버튼을 눌러 삭제할 수 있습니다. 이미지를 선택하려면 커서를 이미지 위로 이동하면 체크 표시가 나타납니다. 이 체크 표시를 선택하거나 선택 해제하세요.

1. 모델의 새로운 반복을 훈련시키고 위의 단계를 따라 게시하세요.

1. 코드에서 엔드포인트 URL을 업데이트하고 앱을 다시 실행하세요.

1. 예측 결과에 만족할 때까지 이 단계를 반복하세요.

---

## 🚀 도전 과제

이미지 해상도나 조명이 예측에 얼마나 영향을 미칠까요?

기기 코드에서 이미지 해상도를 변경해 보고 이미지 품질에 차이가 있는지 확인하세요. 또한 조명을 변경해 보세요.

농장이나 공장에 판매할 생산 기기를 만든다면, 항상 일관된 결과를 제공하도록 어떻게 보장할 수 있을까요?

## 강의 후 퀴즈

[강의 후 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## 복습 및 자습

Custom Vision 포털을 사용해 사용자 정의 비전 모델을 훈련시켰습니다. 이는 이미지를 사용할 수 있다는 전제에 의존합니다. 그러나 실제 환경에서는 기기의 카메라가 캡처한 이미지와 일치하는 훈련 데이터를 얻을 수 없을 수도 있습니다. 이를 해결하기 위해 훈련 API를 사용해 기기에서 직접 모델을 훈련시킬 수 있습니다.

* [Custom Vision SDK 빠른 시작](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)에서 훈련 API에 대해 읽어보세요.

## 과제

[분류 결과에 응답하기](assignment.md)

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전을 권위 있는 출처로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 책임을 지지 않습니다.