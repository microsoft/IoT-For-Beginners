<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-25T00:54:12+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "ko"
}
-->
# GPS 데이터 읽기 - 라즈베리 파이

이 수업의 이 부분에서는 라즈베리 파이에 GPS 센서를 추가하고 데이터를 읽는 방법을 배웁니다.

## 하드웨어

라즈베리 파이에는 GPS 센서가 필요합니다.

사용할 센서는 [Grove GPS Air530 센서](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)입니다. 이 센서는 여러 GPS 시스템에 연결하여 빠르고 정확한 위치를 제공합니다. 센서는 두 부분으로 구성되어 있습니다 - 센서의 핵심 전자 부품과 위성에서 오는 전파를 수신하기 위해 얇은 선으로 연결된 외부 안테나.

이 센서는 UART 센서로, UART를 통해 GPS 데이터를 전송합니다.

## GPS 센서 연결하기

Grove GPS 센서를 라즈베리 파이에 연결할 수 있습니다.

### 작업 - GPS 센서 연결하기

GPS 센서를 연결하세요.

![Grove GPS 센서](../../../../../translated_images/ko/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Grove 케이블의 한쪽 끝을 GPS 센서의 소켓에 삽입하세요. 케이블은 한 방향으로만 들어갑니다.

1. 라즈베리 파이의 전원이 꺼진 상태에서 Grove 케이블의 다른 끝을 Pi에 부착된 Grove Base Hat의 **UART**로 표시된 UART 소켓에 연결하세요. 이 소켓은 SD 카드 슬롯 쪽, USB 포트와 이더넷 소켓 반대쪽에 있는 중간 줄에 위치합니다.

    ![UART 소켓에 연결된 Grove GPS 센서](../../../../../translated_images/ko/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. GPS 센서를 배치하여 연결된 안테나가 하늘을 볼 수 있도록 하세요 - 이상적으로는 열린 창 옆이나 야외에 배치하세요. 안테나에 장애물이 없을수록 신호가 더 잘 수신됩니다.

## GPS 센서 프로그래밍하기

이제 라즈베리 파이를 프로그래밍하여 연결된 GPS 센서를 사용할 수 있습니다.

### 작업 - GPS 센서 프로그래밍하기

장치를 프로그래밍하세요.

1. Pi의 전원을 켜고 부팅을 기다리세요.

1. GPS 센서에는 두 개의 LED가 있습니다 - 데이터가 전송될 때 깜빡이는 파란색 LED와 위성에서 데이터를 수신할 때 매초 깜빡이는 녹색 LED. Pi의 전원을 켰을 때 파란색 LED가 깜빡이는지 확인하세요. 몇 분 후 녹색 LED가 깜빡일 것입니다 - 그렇지 않다면 안테나를 재배치해야 할 수도 있습니다.

1. VS Code를 실행하세요. Pi에서 직접 실행하거나 Remote SSH 확장을 통해 연결하세요.

    > ⚠️ 필요하면 [수업 1에서 VS Code 설정 및 실행 지침](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)을 참조하세요.

1. 블루투스를 지원하는 최신 버전의 라즈베리 파이에서는 블루투스에 사용되는 시리얼 포트와 Grove UART 포트에 사용되는 포트 간에 충돌이 발생합니다. 이를 해결하려면 다음을 수행하세요:

    1. VS Code 터미널에서 `nano`를 사용하여 `/boot/config.txt` 파일을 편집하세요. 이는 내장된 터미널 텍스트 편집기입니다. 다음 명령을 사용하세요:

        ```sh
        sudo nano /boot/config.txt
        ```

        > 이 파일은 `sudo` 권한, 즉 높은 권한으로 편집해야 하므로 VS Code에서는 편집할 수 없습니다. VS Code는 이러한 권한으로 실행되지 않습니다.

    1. 커서 키를 사용하여 파일 끝으로 이동한 다음 아래 코드를 복사하여 파일 끝에 붙여넣으세요:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        일반적인 키보드 단축키를 사용하여 붙여넣을 수 있습니다 (`Ctrl+v`는 Windows, Linux 또는 Raspberry Pi OS에서, `Cmd+v`는 macOS에서 사용).

    1. `Ctrl+x`를 눌러 파일을 저장하고 nano를 종료하세요. 수정된 버퍼를 저장할지 묻는 메시지가 나타나면 `y`를 누르고, `/boot/config.txt`를 덮어쓸지 확인하려면 `enter`를 누르세요.

        > 실수한 경우 저장하지 않고 종료한 다음 이 단계를 반복할 수 있습니다.

    1. nano를 사용하여 `/boot/cmdline.txt` 파일을 편집하세요. 다음 명령을 사용하세요:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. 이 파일에는 공백으로 구분된 여러 키/값 쌍이 있습니다. `console` 키에 대한 키/값 쌍을 제거하세요. 이는 다음과 같을 것입니다:

        ```output
        console=serial0,115200 console=tty1 
        ```

        커서 키를 사용하여 이러한 항목으로 이동한 다음 일반적인 `del` 또는 `backspace` 키를 사용하여 삭제하세요.

        예를 들어, 원래 파일이 다음과 같다면:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        새 버전은 다음과 같을 것입니다:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. 위 단계를 따라 이 파일을 저장하고 nano를 종료하세요.

    1. Pi를 재부팅한 다음 Pi가 재부팅되면 VS Code에 다시 연결하세요.

1. 터미널에서 `pi` 사용자 홈 디렉토리에 `gps-sensor`라는 새 폴더를 만드세요. 이 폴더에 `app.py`라는 파일을 만드세요.

1. VS Code에서 이 폴더를 여세요.

1. GPS 모듈은 시리얼 포트를 통해 UART 데이터를 전송합니다. Python 코드에서 시리얼 포트와 통신하기 위해 `pyserial` Pip 패키지를 설치하세요:

    ```sh
    pip3 install pyserial
    ```

1. `app.py` 파일에 다음 코드를 추가하세요:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    이 코드는 `pyserial` Pip 패키지에서 `serial` 모듈을 가져옵니다. 그런 다음 Grove Pi Base Hat이 UART 포트에 사용하는 시리얼 포트 주소인 `/dev/ttyAMA0`에 연결합니다. 이 시리얼 연결에서 기존 데이터를 모두 지웁니다.

    다음으로 `print_gps_data`라는 함수가 정의되며, 전달된 줄을 콘솔에 출력합니다.

    이후 코드가 무한 루프를 실행하며, 각 루프에서 시리얼 포트에서 가능한 많은 텍스트 줄을 읽습니다. 각 줄에 대해 `print_gps_data` 함수를 호출합니다.

    모든 데이터를 읽은 후 루프는 1초 동안 대기한 다음 다시 시도합니다.

1. 이 코드를 실행하세요. GPS 센서에서 나오는 원시 출력이 다음과 비슷하게 표시됩니다:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > 코드를 중지하고 다시 시작할 때 다음 오류 중 하나가 발생하면, while 루프에 `try - except` 블록을 추가하세요.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 이 코드는 [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi) 폴더에서 찾을 수 있습니다.

😀 GPS 센서 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.