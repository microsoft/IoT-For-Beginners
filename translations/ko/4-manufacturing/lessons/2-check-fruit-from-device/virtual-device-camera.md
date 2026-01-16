<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-24T21:34:42+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "ko"
}
-->
# 이미지 캡처 - 가상 IoT 하드웨어

이 수업의 이 부분에서는 가상 IoT 장치에 카메라 센서를 추가하고 이미지를 읽는 방법을 배웁니다.

## 하드웨어

가상 IoT 장치는 파일에서 가져온 이미지 또는 웹캠에서 가져온 이미지를 전송하는 시뮬레이션된 카메라를 사용합니다.

### CounterFit에 카메라 추가하기

가상 카메라를 사용하려면 CounterFit 앱에 카메라를 추가해야 합니다.

#### 작업 - CounterFit에 카메라 추가하기

CounterFit 앱에 카메라를 추가하세요.

1. `fruit-quality-detector`라는 폴더에 단일 파일 `app.py`와 Python 가상 환경을 포함한 새 Python 앱을 컴퓨터에 생성하고 CounterFit pip 패키지를 추가하세요.

    > ⚠️ 필요하다면 [수업 1에서 CounterFit Python 프로젝트를 생성하고 설정하는 방법에 대한 지침](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)을 참조하세요.

1. 추가 Pip 패키지를 설치하여 일부 [Picamera Pip 패키지](https://pypi.org/project/picamera/)를 시뮬레이션하여 카메라 센서와 통신할 수 있는 CounterFit shim을 설치하세요. 가상 환경이 활성화된 터미널에서 설치해야 합니다.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. CounterFit 웹 앱이 실행 중인지 확인하세요.

1. 카메라를 생성하세요:

    1. *Sensors* 창의 *Create sensor* 상자에서 *Sensor type* 드롭다운을 열고 *Camera*를 선택하세요.

    1. *Name*을 `Picamera`로 설정하세요.

    1. **Add** 버튼을 선택하여 카메라를 생성하세요.

    ![카메라 설정](../../../../../translated_images/ko/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    카메라가 생성되어 센서 목록에 나타납니다.

    ![생성된 카메라](../../../../../translated_images/ko/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## 카메라 프로그래밍

가상 IoT 장치를 이제 가상 카메라를 사용하도록 프로그래밍할 수 있습니다.

### 작업 - 카메라 프로그래밍

장치를 프로그래밍하세요.

1. `fruit-quality-detector` 앱이 VS Code에서 열려 있는지 확인하세요.

1. `app.py` 파일을 엽니다.

1. CounterFit에 앱을 연결하기 위해 `app.py` 상단에 다음 코드를 추가하세요:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. `app.py` 파일에 다음 코드를 추가하세요:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    이 코드는 필요한 라이브러리를 포함하며, counterfit_shims_picamera 라이브러리에서 `PiCamera` 클래스를 가져옵니다.

1. 아래에 카메라를 초기화하는 코드를 추가하세요:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    이 코드는 PiCamera 객체를 생성하고 해상도를 640x480으로 설정합니다. 더 높은 해상도도 지원되지만, 이미지 분류기는 훨씬 작은 이미지(227x227)에서 작동하므로 더 큰 이미지를 캡처하거나 전송할 필요가 없습니다.

    `camera.rotation = 0` 줄은 이미지의 회전 각도를 설정합니다. 웹캠 또는 파일에서 이미지를 회전해야 할 경우 적절히 설정하세요. 예를 들어, 가로 모드의 웹캠에서 바나나 이미지를 세로 모드로 변경하려면 `camera.rotation = 90`으로 설정하세요.

1. 아래에 이미지를 바이너리 데이터로 캡처하는 코드를 추가하세요:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    이 코드는 바이너리 데이터를 저장하기 위한 `BytesIO` 객체를 생성합니다. 카메라에서 JPEG 파일로 이미지를 읽어 이 객체에 저장합니다. 이 객체는 데이터를 추가로 작성할 수 있는 끝 위치를 추적하는 위치 표시기를 가지고 있으므로, `image.seek(0)` 줄은 이 위치를 시작으로 되돌려 나중에 모든 데이터를 읽을 수 있도록 합니다.

1. 아래에 이미지를 파일로 저장하는 코드를 추가하세요:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    이 코드는 `image.jpg`라는 파일을 열어 쓰기 작업을 수행하며, `BytesIO` 객체에서 모든 데이터를 읽어 파일에 작성합니다.

    > 💁 이미지를 `BytesIO` 객체 대신 파일로 직접 캡처하려면 `camera.capture` 호출에 파일 이름을 전달하면 됩니다. 이 수업의 후반부에서 이미지를 이미지 분류기로 전송할 수 있도록 `BytesIO` 객체를 사용하는 이유입니다.

1. CounterFit에서 카메라가 캡처할 이미지를 설정하세요. *Source*를 *File*로 설정한 후 이미지 파일을 업로드하거나, *Source*를 *WebCam*으로 설정하여 웹캠에서 이미지를 캡처할 수 있습니다. 사진을 선택하거나 웹캠을 선택한 후 **Set** 버튼을 반드시 클릭하세요.

    ![파일을 이미지 소스로 설정한 CounterFit과 웹캠을 설정하여 바나나를 들고 있는 사람을 보여주는 웹캠 미리보기](../../../../../translated_images/ko/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. 이미지가 캡처되어 현재 폴더에 `image.jpg`로 저장됩니다. 이 파일은 VS Code 탐색기에서 확인할 수 있습니다. 파일을 선택하여 이미지를 확인하세요. 회전이 필요하다면 `camera.rotation = 0` 줄을 적절히 업데이트하고 다시 사진을 찍으세요.

> 💁 이 코드는 [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device) 폴더에서 찾을 수 있습니다.

😀 카메라 프로그램이 성공적으로 완료되었습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.