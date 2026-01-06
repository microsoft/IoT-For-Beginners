<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-24T21:13:27+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "ko"
}
-->
# IoT 기기로 재고 계산하기 - 가상 IoT 하드웨어와 Raspberry Pi

예측 결과와 경계 상자를 조합하여 이미지에서 재고를 계산할 수 있습니다.

## 경계 상자 표시하기

디버깅을 돕기 위해 경계 상자를 출력하는 것뿐만 아니라, 이미지를 캡처하여 디스크에 저장했을 때 해당 이미지에 경계 상자를 그릴 수도 있습니다.

### 작업 - 경계 상자 출력하기

1. VS Code에서 `stock-counter` 프로젝트를 열고, 가상 IoT 기기를 사용하는 경우 가상 환경이 활성화되어 있는지 확인하세요.

1. `for` 루프의 `print` 문을 다음과 같이 변경하여 콘솔에 경계 상자를 출력하세요:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. 카메라를 선반 위의 재고를 향하게 하고 앱을 실행하세요. 경계 상자가 콘솔에 출력되며, 왼쪽, 위쪽, 너비, 높이 값이 0-1 범위로 표시됩니다.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### 작업 - 이미지에 경계 상자 그리기

1. [Pillow](https://pypi.org/project/Pillow/)라는 Pip 패키지를 사용하여 이미지에 그림을 그릴 수 있습니다. 다음 명령어로 설치하세요:

    ```sh
    pip3 install pillow
    ```

    가상 IoT 기기를 사용하는 경우, 활성화된 가상 환경 내에서 이 명령어를 실행하세요.

1. `app.py` 파일 상단에 다음 import 문을 추가하세요:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    이는 이미지를 편집하는 데 필요한 코드를 가져옵니다.

1. `app.py` 파일 끝에 다음 코드를 추가하세요:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    이 코드는 이전에 저장된 이미지를 열어 편집합니다. 그런 다음 예측을 반복하며 경계 상자를 가져오고, 경계 상자 값(0-1)을 사용하여 오른쪽 아래 좌표를 계산합니다. 이 값은 이미지의 관련 치수를 곱하여 이미지 좌표로 변환됩니다. 예를 들어, 이미지 너비가 600픽셀이고 왼쪽 값이 0.5라면, 이는 300으로 변환됩니다 (0.5 x 600 = 300).

    각 경계 상자는 빨간 선으로 이미지에 그려집니다. 마지막으로 편집된 이미지는 원본 이미지를 덮어쓰며 저장됩니다.

1. 카메라를 선반 위의 재고를 향하게 하고 앱을 실행하세요. VS Code 탐색기에서 `image.jpg` 파일을 확인할 수 있으며, 이를 선택하여 경계 상자를 볼 수 있습니다.

    ![4개의 토마토 페이스트 캔에 각각 경계 상자가 표시된 이미지](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.ko.jpg)

## 재고 계산하기

위 이미지에서 경계 상자가 약간 겹쳐져 있습니다. 만약 겹침이 훨씬 크다면, 경계 상자가 동일한 객체를 나타낼 수 있습니다. 객체를 올바르게 계산하려면 겹침이 큰 상자를 무시해야 합니다.

### 작업 - 겹침을 무시하고 재고 계산하기

1. [Shapely](https://pypi.org/project/Shapely/)라는 Pip 패키지를 사용하여 교차를 계산할 수 있습니다. Raspberry Pi를 사용하는 경우 먼저 라이브러리 종속성을 설치해야 합니다:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Shapely Pip 패키지를 설치하세요:

    ```sh
    pip3 install shapely
    ```

    가상 IoT 기기를 사용하는 경우, 활성화된 가상 환경 내에서 이 명령어를 실행하세요.

1. `app.py` 파일 상단에 다음 import 문을 추가하세요:

    ```python
    from shapely.geometry import Polygon
    ```

    이는 겹침을 계산하기 위해 다각형을 생성하는 데 필요한 코드를 가져옵니다.

1. 경계 상자를 그리는 코드 위에 다음 코드를 추가하세요:

    ```python
    overlap_threshold = 0.20
    ```

    이는 경계 상자가 동일한 객체로 간주되기 전에 허용되는 겹침 비율을 정의합니다. 0.20은 20% 겹침을 정의합니다.

1. Shapely를 사용하여 겹침을 계산하려면 경계 상자를 Shapely 다각형으로 변환해야 합니다. 이를 수행하는 다음 함수를 추가하세요:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    이는 예측의 경계 상자를 사용하여 다각형을 생성합니다.

1. 겹침이 있는 객체를 제거하는 논리는 모든 경계 상자를 비교하고, 예측 쌍 중 겹침이 임계값을 초과하는 경우 하나의 예측을 삭제하는 것입니다. 모든 예측을 비교하려면 예측 1을 2, 3, 4 등과 비교하고, 그런 다음 2를 3, 4 등과 비교합니다. 다음 코드는 이를 수행합니다:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    겹침은 Shapely의 `Polygon.intersection` 메서드를 사용하여 계산되며, 이는 겹침을 포함하는 다각형을 반환합니다. 그런 다음 이 다각형의 면적이 계산됩니다. 이 겹침 임계값은 절대값이 아니라, 경계 상자의 비율이어야 하므로 가장 작은 경계 상자를 찾고, 겹침 임계값을 사용하여 가장 작은 경계 상자의 비율 겹침 임계값을 초과하지 않는 면적을 계산합니다. 겹침이 이를 초과하면 예측이 삭제 대상으로 표시됩니다.

    예측이 삭제 대상으로 표시되면 다시 확인할 필요가 없으므로 내부 루프는 다음 예측을 확인하기 위해 중단됩니다. 리스트를 반복하면서 항목을 삭제할 수 없으므로, 겹침이 임계값을 초과하는 경계 상자는 `to_delete` 리스트에 추가된 후 마지막에 삭제됩니다.

    마지막으로 재고 수가 콘솔에 출력됩니다. 이는 재고 수준이 낮을 경우 IoT 서비스에 알림을 보내는 데 사용할 수 있습니다. 이 모든 코드는 경계 상자가 그려지기 전에 실행되므로, 생성된 이미지에서 겹침이 없는 재고 예측을 볼 수 있습니다.

    > 💁 이는 겹침을 제거하는 매우 단순한 방법으로, 겹침 쌍에서 첫 번째 것을 제거하는 방식입니다. 실제 코드에서는 여러 객체 간의 겹침을 고려하거나 하나의 경계 상자가 다른 경계 상자에 포함된 경우를 처리하는 등의 더 많은 논리를 추가해야 할 것입니다.

1. 카메라를 선반 위의 재고를 향하게 하고 앱을 실행하세요. 출력은 임계값을 초과하지 않는 겹침이 없는 경계 상자의 수를 나타냅니다. `overlap_threshold` 값을 조정하여 무시되는 예측을 확인해 보세요.

> 💁 이 코드는 [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) 또는 [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device) 폴더에서 찾을 수 있습니다.

😀 재고 계산 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.