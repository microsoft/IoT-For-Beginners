<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-25T00:52:37+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "ko"
}
-->
# GPS 데이터 디코딩 - 가상 IoT 하드웨어와 Raspberry Pi

이 수업의 이 부분에서는 Raspberry Pi 또는 가상 IoT 장치의 GPS 센서에서 읽은 NMEA 메시지를 디코딩하고 위도와 경도를 추출합니다.

## GPS 데이터 디코딩

직렬 포트에서 읽은 원시 NMEA 데이터를 오픈 소스 NMEA 라이브러리를 사용하여 디코딩할 수 있습니다.

### 작업 - GPS 데이터 디코딩

장치를 프로그래밍하여 GPS 데이터를 디코딩하세요.

1. `gps-sensor` 앱 프로젝트를 열지 않았다면 열어주세요.

1. `pynmea2` Pip 패키지를 설치하세요. 이 패키지는 NMEA 메시지를 디코딩하는 코드를 포함하고 있습니다.

    ```sh
    pip3 install pynmea2
    ```

1. `app.py` 파일의 import 섹션에 다음 코드를 추가하여 `pynmea2` 모듈을 가져오세요:

    ```python
    import pynmea2
    ```

1. `print_gps_data` 함수의 내용을 다음 코드로 교체하세요:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    이 코드는 `pynmea2` 라이브러리를 사용하여 UART 직렬 포트에서 읽은 줄을 파싱합니다.

    메시지의 문장 유형이 `GGA`인 경우, 이는 위치 고정 메시지이며 처리됩니다. 위도와 경도 값은 메시지에서 읽어들여지고 NMEA `(d)ddmm.mmmm` 형식에서 소수점 형식으로 변환됩니다. `dm_to_sd` 함수가 이 변환을 수행합니다.

    그런 다음 위도의 방향을 확인하고, 위도가 남쪽인 경우 값을 음수로 변환합니다. 경도도 마찬가지로, 서쪽인 경우 음수로 변환됩니다.

    마지막으로 좌표와 위치를 얻는 데 사용된 위성 수를 콘솔에 출력합니다.

1. 코드를 실행하세요. 가상 IoT 장치를 사용하는 경우, CounterFit 앱이 실행 중이며 GPS 데이터가 전송되고 있는지 확인하세요.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 이 코드는 [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) 폴더 또는 [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi) 폴더에서 찾을 수 있습니다.

😀 GPS 센서 프로그램과 데이터 디코딩이 성공적으로 완료되었습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.