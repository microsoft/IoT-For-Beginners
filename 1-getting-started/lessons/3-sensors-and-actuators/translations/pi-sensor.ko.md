# 야간 조명 만들기 - Raspberry Pi

이 강의에서 여러분의 라즈베리 파이에 광센서를 적용해봅시다

## 하드웨어

본 강의용 센서는 [광다이오드](https://wikipedia.org/wiki/Photodiode)를 사용하여 빛을 전기신호로 변환하는 **광센서** 입니다. 이는 [lux](https://wikipedia.org/wiki/Lux) 와 같은 표준 측정단위에 매핑되지 않는 0부터 1000까지의 빛의 상대적인 양을 나타내는 정수값을 보내는 아날로그 센서입니다.

광센서는 eternal Grove 센서이며 라즈베리 파이의 Grove base hat에 연결해야 합니다.

### 광센서와 연결해봅시다

광도를 감지하는데 사용되는 Grove 광센서는 라즈베리 파이에 연결해야 합니다.

#### 할 일 - 광센서와 연결 해 봅시다.

광센서와 연결해봅시다.

![Grove 광센서](../../../../images/grove-light-sensor.png)

1. Grove 케이블의 한쪽 끝을 광센서 모듈의 소켓에 삽입합니다. 그것은 한 방향으로만 돌아갈 것입니다.

1. Rasberry Pi 전원을 끈 상태에서 Grove 케이블의 다른 쪽 끝을 Pi에 부착된 Grove Base Hat의 **A0** 라고 표시된 아날로그 소켓에 연결합니다. 이 소켓은 오른쪽에서 두 번째, GPIO 핀 옆에 있는 소켓 열입니다.

![소켓 A0에 연결된 그로브 라이트 센서](../../../../images/pi-light-sensor.png)

## 광센서를 프로그래밍 해 봅시다.

이제 Grove light 센서를 사용하여 장치를 프로그래밍할 수 있습니다.

### 할 일 - 광센서를 프로그래밍한다.

구현 해 봅시다.

1. 라즈베리 파이의 전원은 켜고 부팅 될 때까지 기다립니다.

1. 이 과제의 이전 부분에서 생성한 VS Code에서 야간 조명 프로젝트를 Pi에서 직접 실행하거나 원격 SSH 확장을 사용하여 연결합니다.

1.  `app.py` 파일을 열고 이 파일의 모든 코드를 지웁니다.
 
1. 몇가지 라이브러리 파일을 요청하기 위해 `app.py` 파일에 아래 있는 코드를 추가합니다:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time` 은 이 과제 이후에 사용될 `time` 모듈을 import 합니다.
    
    `from grove.grove_light_sensor_v1_2 import GroveLightSensor` 는 Grove Python 라이브러리로부터 `GroveLightSensor` 를 import 합니다. 이 라이브러리는 Grove 광센서와 상호작용 할 수 있는 코드를 가지고 있으며 라즈베리 파이 설정 중에 전역으로 설치되었습니다.
    
1. 아래 코드를 위에서 작성한 코드 뒤에 추가하여 광센서를 관리하는 클래스의 인스턴스를 만듭니다.

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    `light_sensor = GroveLightSensor(0)`는  핀 **A0**(광센서와 연결되어있는 아날로그 Grove 핀)와 연결되어있는 `GroveLightSensor` class의 인스턴스를 생성합니다. 
    

1. 위에서 작성한 코드 뒤에 무한 루프를 추가하여 광 센서 값을 측정하고 콘솔에 출력합니다 :

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    이는 `GroveLightSensor` 클래스의 `light` 속성을 사용하여 0-1,023의 척도로 현재 빛의 밝기를 판독합니다. 이 속성은 핀에서 아날로그 값을 읽습니다. 이후 이 값이 콘솔에 출력됩니다.
    
1. 계속 밝기를 확인할 필요가 없으므로 `루프` 끝에 1초의 짧은 절전 시간을 추가한다. 절전 모드는 장치의 전력 소비를 줄여줍니다.

    ```python
    time.sleep(1)
    ```

1. VS Code의 터미널에서 아래 코드로 Python 앱을 실행 해 봅시다.

    ```sh
    python3 app.py
    ```

    밝기 값이 콘솔에 출력될 것이다. 광센서를 손으로 가려도 보면서 값이 어떻게 변하는지 확인 해 봅시다 :

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁  [code-sensor/pi](code-sensor/pi) 폴더에서 이 코드를 찾을 수 있습니다.

😀 여러분의 야간 조명 프로그렘에 성공적으로 센서를 적용했습니다!
