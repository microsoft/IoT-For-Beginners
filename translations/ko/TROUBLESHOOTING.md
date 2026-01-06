<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-05T21:53:58+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "ko"
}
-->
# 문제 해결 가이드

이 가이드는 IoT for Beginners 커리큘럼 작업 시 자주 발생하는 문제 해결을 돕습니다. 문제는 쉽게 탐색할 수 있도록 범주별로 정리되어 있습니다.

## 목차

- [설치 문제](../..)
  - [Python 설치](../..)
  - [VS Code 및 확장 기능](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Grove 라이브러리](../..)
- [하드웨어 문제](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [가상 장치 (CounterFit)](../..)
- [연결 문제](../..)
  - [WiFi 연결](../..)
  - [클라우드 서비스](../..)
  - [MQTT](../..)
- [센서 및 액추에이터 문제](../..)
  - [Grove 센서](../..)
  - [카메라](../..)
  - [마이크 및 스피커](../..)
- [개발 환경 문제](../..)
  - [VS Code](../..)
  - [Python 가상 환경](../..)
  - [종속성](../..)
- [성능 문제](../..)
- [일반 오류 메시지](../..)
- [도움 받기](../..)

---

## 설치 문제

### Python 설치

#### 문제: Python 버전이 너무 오래됨  
**오류:** `Python 3.6 이상이 필요합니다`

**해결 방법:**
1. [python.org](https://www.python.org/downloads/)에서 최신 Python 3 버전을 다운로드하세요.
2. Windows 설치 시 "Add Python to PATH" 옵션을 선택하세요.
3. 설치 확인:
   ```bash
   python3 --version
   ```

#### 문제: 여러 Python 버전 충돌  
**증상:** 잘못된 Python 버전 실행, 패키지가 잘못된 위치에 설치됨

**해결 방법:**
- **Windows:** Python 3을 명확히 호출하려면 `python` 대신 `py -3`를 사용하세요.
- **macOS/Linux:** `python` 대신 `python3`를 사용하세요.
- 항상 프로젝트마다 가상 환경을 만들어 사용하세요.

#### 문제: pip 명령어를 찾을 수 없음  
**오류:** `'pip'은(는) 내부 또는 외부 명령, 실행할 수 있는 프로그램 또는 배치 파일이 아닙니다`

**해결 방법:**
1. `pip` 대신 `pip3`를 사용해 보세요.
2. 혹은 `python -m pip` 또는 `python3 -m pip`를 사용하세요.
3. Python이 PATH에 추가되었는지 확인하세요 (Python을 재설치하며 옵션을 선택하세요).

### VS Code 및 확장 기능

#### 문제: Pylance 확장 기능이 작동하지 않음  
**증상:** Python IntelliSense, 코드 완성, 타입 검사 기능 없음

**해결 방법:**
1. VS Code 명령 팔레트 열기 (`Ctrl+Shift+P` 또는 `Cmd+Shift+P`)
2. "Python: Select Interpreter" 실행
3. 올바른 Python 인터프리터 (가상 환경 사용 중이면 가상 환경) 선택
4. VS Code 창 새로 고침

#### 문제: VS Code가 가상 환경을 인식하지 못함  
**증상:** 잘못된 Python 인터프리터 선택됨

**해결 방법:**
1. 터미널에서 가상 환경이 활성화되었는지 확인
2. 명령 팔레트 열고 "Python: Select Interpreter" 실행
3. `.venv` 폴더 내 인터프리터 선택
4. 상태 표시줄 (왼쪽 하단)에 올바른 Python 버전 표시 확인

### PlatformIO (Wio Terminal)

#### 문제: PlatformIO 설치 실패  
**오류:** 설치 중 다양한 오류 발생

**해결 방법:**
1. VS Code가 최신 버전인지 확인
2. 먼저 C/C++ 확장 기능 설치
3. PlatformIO 설치 후 VS Code 재시작
4. 인터넷 연결 상태 확인 (PlatformIO는 대용량 파일 다운로드)

#### 문제: PlatformIO가 보드를 인식하지 못함  
**증상:** Wio Terminal에 코드 업로드 불가

**해결 방법:**
1. 다른 USB 케이블 사용 (일부 케이블은 충전 전용임)
2. 장치 관리자(Windows) 또는 `ls /dev/tty*` (macOS/Linux)에서 장치 확인
3. USB 드라이버 설치 또는 업데이트
4. 다른 USB 포트 사용
5. Wio Terminal의 전원 스위치를 두 번 빠르게 밀어 부트로더 모드로 전환

#### 문제: PlatformIO 컴파일 오류  
**오류:** `fatal error: Arduino.h: No such file or directory`

**해결 방법:**
1. 프로젝트 내 `.pio` 폴더 삭제
2. 명령 팔레트에서 "PlatformIO: Rebuild" 실행
3. `platformio.ini`에 올바른 보드 설정이 있는지 확인:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove 라이브러리

#### 문제: Raspberry Pi에서 Grove 라이브러리 임포트 실패  
**오류:** `ModuleNotFoundError: No module named 'grove'`

**해결 방법:**
1. Grove 라이브러리 재설치:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. 가상 환경 사용 시에는 전역 설치하거나 라이브러리 복사가 필요할 수 있음  
3. I2C가 활성화되었는지 확인: `sudo raspi-config nonint do_i2c 0`

#### 문제: Grove 센서가 감지되지 않음  
**오류:** `IOError: [Errno 121] Remote I/O error`

**해결 방법:**
1. 물리적 연결 확인 (Grove 케이블이 완전히 꽂혔는지 확인)
2. 센서가 올바른 포트에 연결되었는지 확인 (아날로그, 디지털, I2C, UART)
3. `i2cdetect -y 1` 실행하여 I2C 버스에 장치가 나타나는지 확인
4. 다른 Grove 케이블 사용해 보기
5. Grove Base Hat이 Raspberry Pi GPIO 핀에 제대로 장착되었는지 확인

---

## 하드웨어 문제

### Raspberry Pi

#### 문제: Raspberry Pi가 부팅되지 않음  
**증상:** 화면 출력 없음, LED 동작 없음, 무지개 화면 출력

**해결 방법:**
1. **전원 공급 확인:** Pi 4용 공식 5V 3A USB-C 전원 어댑터 사용
2. **SD 카드 문제:** 
   - SD 카드 재포맷 후 Raspberry Pi OS 재설치
   - 다른 SD 카드 시도 (권장 브랜드 사용)
   - SD 카드가 제대로 삽입되었는지 확인
3. **HDMI 연결 확인:** Pi 4의 두 HDMI 포트 모두 시도, 전원 쪽에 가까운 HDMI 포트 사용

#### 문제: Raspberry Pi에 SSH 접속 불가  
**증상:** 연결 거부 또는 시간 초과

**해결 방법:**
1. SSH 활성화:
   - Raspberry Pi Imager로 SD 카드 플래시 시 고급 옵션에서 SSH 활성화
   - 또는 부팅 파티션에 확장자 없는 빈 파일 `ssh` 생성
2. Pi의 IP 주소 찾기:
   - 라우터의 연결된 장치 목록 확인
   - `ping raspberrypi.local` 사용 (mDNS가 동작하는 경우)
   - `nmap` 또는 Angry IP Scanner 같은 네트워크 스캔 도구 사용
3. 네트워크 확인:
   - Pi가 컴퓨터와 같은 네트워크에 연결되어 있는지 확인
   - WiFi 대신 이더넷 연결 시도
4. 사용자 이름/비밀번호 확인 (기본: 사용자 이름 `pi`, 비밀번호 `raspberry`)

#### 문제: Grove Base Hat이 인식되지 않음  
**증상:** 센서 작동 안 함, I2C 오류 발생

**해결 방법:**
1. Base Hat이 모든 GPIO 핀에 제대로 장착되었는지 확인
2. Pi 또는 Base Hat의 핀이 구부러지지 않았는지 확인
3. I2C 인터페이스 활성화:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. I2C 작동 확인: `i2cdetect -y 1`

#### 문제: Raspberry Pi 속도가 느림  
**증상:** UI 지연, 반응 느림

**해결 방법:**
1. SD 카드 속도 확인 (클래스 10 이상 또는 USB를 통한 SSD 사용)
2. 디스크 공간 확보: `df -h` 명령어로 확인 후 불필요한 파일 삭제
3. 카메라/디스플레이를 интенсив하게 사용하지 않는 경우 `raspi-config`에서 GPU 메모리 줄이기
4. 불필요한 애플리케이션 종료
5. Pi 3 이하 모델 사용 시 RAM이 더 많은 Pi 4로 업그레이드 고려

### Wio Terminal

#### 문제: Wio Terminal 화면이 빈 상태로 유지됨  
**증상:** 코드 업로드 후 화면 출력 없음

**해결 방법:**
1. 코드가 디스플레이 초기화를 하는지 확인 (TFT_eSPI 라이브러리)
2. [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)에서 Wio Terminal 펌웨어 업데이트
3. 디스플레이 초기화 코드 추가:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. PlatformIO에서 하드웨어 테스트를 위해 예제 스케치 업로드 시도

#### 문제: Wio Terminal에서 WiFi가 작동하지 않음  
**증상:** WiFi에 연결할 수 없음, 네트워크 오류 발생

**해결 방법:**
1. **WiFi 펌웨어 업데이트:** [Wio Terminal WiFi 펌웨어 업데이트 가이드](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) 참고
2. **WiFi 자격 증명 확인:** SSID 및 비밀번호가 정확한지 확인
3. **WiFi 대역:** Wio Terminal은 2.4GHz WiFi만 지원 (5GHz는 지원하지 않음)
4. **신호 세기:** 라우터에 더 가까이 이동
5. **라우터 설정:** 일부 기업용/WPA-Enterprise 네트워크는 작동하지 않을 수 있음

#### 문제: 컴퓨터가 Wio Terminal을 인식하지 못함  
**증상:** USB 장치 감지되지 않음

**해결 방법:**
1. **다른 USB 케이블 사용:** 충전 전용이 아닌 데이터 케이블 사용
2. **부트로더 모드 진입:** 전원 스위치를 두 번 빠르게 내리기
   - 파란 LED가 깜박이며 장치 관리자의 "Arduino"로 표시
3. **드라이버 설치 (Windows):**
   - [Seeed USB 드라이버](https://wiki.seeedstudio.com/Driver_for_Seeeduino/) 다운로드 및 설치
4. **다른 USB 포트 사용:** USB 허브 대신 직접 연결
5. **시스템 USB 드라이버 업데이트**

#### 문제: Wio Terminal 센서 작동 안 함  
**증상:** Grove 센서 데이터 읽기 실패

**해결 방법:**
1. Grove 케이블 연결 확인
2. 올바른 Grove 포트(왼쪽 또는 오른쪽) 사용 확인
3. 센서에 맞는 라이브러리 포함
4. 센서 전원 요구사항 확인
5. 라이브러리의 예제 코드로 센서 테스트

### 가상 장치 (CounterFit)

#### 문제: CounterFit 앱 실행 불가  
**오류:** CounterFit 시작 시 다양한 Python 오류 발생

**해결 방법:**
1. 가상 환경 활성화 여부 확인
2. CounterFit 설치 또는 재설치:
   ```bash
   pip install CounterFit
   ```
3. 포트 5000이 이미 사용 중인지 확인:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. 포트 5000을 사용 중인 프로세스 종료 또는 다른 포트 사용:
   ```bash
   counterfit --port 5001
   ```

#### 문제: 코드에서 CounterFit에 연결할 수 없음  
**오류:** 연결 거부 또는 시간 초과

**해결 방법:**
1. CounterFit이 실행 중인지 확인: 브라우저에서 `http://127.0.0.1:5000` 열기
2. 코드의 연결 URL이 CounterFit 주소와 일치하는지 확인
3. 방화벽이 연결을 차단하지 않는지 확인
4. CounterFit 앱과 코드를 모두 재시작해 보기

#### 문제: CounterFit에 센서가 나타나지 않음  
**증상:** 생성한 센서가 CounterFit UI에 표시되지 않음

**해결 방법:**
1. 코드 실행 전에 CounterFit UI에서 센서 생성
2. 브라우저 페이지 새로 고침
3. 센서 유형이 코드와 일치하는지 확인
4. 브라우저 캐시 삭제

---

## 연결 문제

### WiFi 연결

#### 문제: 장치가 WiFi에 연결할 수 없음  
**증상:** 연결 시간 초과, 인증 실패

**해결 방법:**
1. **SSID 및 비밀번호 확인:** 자격 증명이 정확한지 확인
2. **WiFi 대역:** 대부분 IoT 장치는 2.4GHz만 지원 (5GHz 미지원)
3. **라우터 설정:**
   - AP 격리 비활성화
   - WPA2-PSK 보안 사용 (WPA3, WEP, 또는 공개 네트워크는 피함)
   - DHCP 활성화 확인
4. **숨김 네트워크:** SSID가 숨겨져 있으면 명시적으로 설정 필요
5. **신호 세기:** 장치를 라우터에 더 가까이 이동
6. **간섭:** 다른 장치, 전자레인지, 벽 등이 간섭할 수 있음

#### 문제: WiFi 연결이 자주 끊어짐  
**증상:** 불규칙한 연결 상태

**해결 방법:**
1. 라우터 안정성 확인 및 재부팅 고려
2. 장치 펌웨어 업데이트
3. DHCP 대신 고정 IP 사용
4. 라우터와 거리 좁히거나 WiFi 확장기 추가
5. 다른 장치에 의한 간섭 확인
6. 전원 공급이 충분한지 확인 (특히 Raspberry Pi)

### 클라우드 서비스

#### 문제: Azure IoT Hub에 연결할 수 없음  
**오류:** 인증 실패, 연결 거부

**해결 방법:**
1. **자격 증명 확인:**
   - 연결 문자열이 정확한지 확인
   - 문자열에 여분의 공백이나 줄 바꿈이 없는지 확인
2. **장치 등록 확인:** 장치가 IoT Hub에 등록되어 있어야 함
3. **방화벽/프록시:** MQTT (포트 8883) 또는 HTTPS (포트 443) 아웃바운드 허용 여부 확인
4. **IoT Hub 지역:** IoT Hub가 정상적으로 실행 중인지, 지역 차이로 인한 지연 없는지 확인
5. **할당량 제한:** 무료 요금제 한도 초과 여부 확인
6. **연결 테스트:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### 문제: Azure Functions가 트리거되지 않음  
**증상:** 메시지는 전송되었으나 함수가 실행되지 않음

**해결 방법:**
1. Function App이 실행 중인지 확인 (중지 상태 아님)
2. Function App 설정에서 연결 문자열 확인
3. Azure Portal에서 함수 로그 확인
4. Event Hub 호환 엔드포인트가 올바르게 구성되었는지 확인
5. 메시지 형식이 함수 요구 사항과 일치하는지 확인
6. Function App 서비스 플랜 확인 (소비 계획 vs 전용 계획)

### MQTT
#### 문제: MQTT 연결 실패
**오류:** 연결 거부됨, 인증 실패

**해결책:**
1. **브로커 주소:** 브로커 URL/IP가 올바른지 확인
2. **포트:** 포트 번호 확인 (암호화 안된 경우 1883, TLS는 8883)
3. **인증:** 필요한 경우 사용자 이름/비밀번호 확인
4. **TLS/SSL:** 인증서가 유효하고 신뢰할 수 있는지 확인
5. **방화벽:** 포트가 차단되지 않았는지 확인
6. **MQTT 클라이언트로 테스트:** MQTT Explorer나 mosquitto_pub/sub 사용하여 테스트

#### 문제: MQTT 메시지 수신 안됨
**증상:** 메시지는 발행되나 구독자가 받지 못함

**해결책:**
1. **주제 이름:** 구독자 주제가 발행자 주제와 정확히 일치하는지 확인
2. **QoS 레벨:** 0 대신 QoS 1 또는 2 사용해보기
3. **와일드카드:** 주제 와일드카드가 올바르게 사용되는지 확인 (`+`는 단일 레벨, `#`는 다중 레벨)
4. **유지된 메시지:** 발행자가 마지막 메시지를 유지하도록 retain 플래그 설정 가능
5. **연결 타이밍:** 구독자가 메시지 발행 전에 연결되었는지 확인

---

## 센서 및 액추에이터 문제

### 그로브 센서

#### 문제: 센서가 잘못된 값 반환
**증상:** 읽기 값이 0, -1 또는 의미없는 값

**해결책:**
1. **연결 확인:** 센서가 제대로 연결되었는지 확인
2. **올바른 포트:** 센서가 올바른 포트 유형에 연결되었는지 확인:
   - 아날로그 센서 → 아날로그 포트 (A0, A2, A4)
   - 디지털 센서 → 디지털 포트 (D5, D16, D18 등)
   - I2C 센서 → I2C 포트
3. **보정:** 일부 센서는 보정 필요 (토양 수분, 조도)
4. **전원 재설정:** 센서 전원 분리 후 재연결
5. **센서 데이터시트:** 센서 사양 및 요구사항 확인

#### 문제: 정전용량 토양 수분 센서가 항상 젖음으로 판독
**증상:** 건조 상태에서도 센서가 높은 습도 판독

**해결책:**
1. **보정 필요:** 토양 센서는 보정이 필요함:
   - 공기 중(건조 상태) 값 읽기 (기준선)
   - 물 속(습윤 상태) 값 읽기 (기준선)
   - 이 사이 값을 매핑
2. **센서 코팅 확인:** 코팅이 손상되면 센서 성능 저하 가능
3. **배치:** 센서를 흙에 완전히 삽입했는지 확인

#### 문제: 온도/습도 센서 값이 올바르지 않음
**증상:** DHT11/DHT22가 틀린 온도 또는 습도 표시

**해결책:**
1. **센서 배치:** 직사광선, 열원, 공기 흐름 피하기
2. **예열 시간:** 전원 켠 후 센서가 2초 정도 안정화 되도록 대기
3. **읽기 빈도:** DHT 센서는 최소 2초 간격으로 읽기 필요
4. **결로 확인:** 결로가 측정에 영향 줄 수 있음
5. **센서 품질:** DHT11은 DHT22보다 정확도가 낮음

### 카메라

#### 문제: Raspberry Pi에서 카메라 감지 안됨
**오류:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**해결책:**
1. **카메라 인터페이스 활성화:**
   ```bash
   sudo raspi-config
   ```
   Interface Options → Camera → Enable로 이동
2. **리본 케이블 확인:** 카메라 케이블이 제대로 연결되었는지 확인
   - Pi Zero의 경우 파란색 면이 USB 포트 방향
   - Pi 4의 경우 파란색 면이 USB 포트 반대 방향
3. **펌웨어 업데이트:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **카메라 테스트:**
   ```bash
   raspistill -o test.jpg
   ```

#### 문제: 카메라 이미지 품질 저하
**증상:** 흐림, 어둡거나 색이 바랜 이미지

**해결책:**
1. **초점:** 렌즈 보호 필름 제거, 조절 가능하면 초점 조절
2. **조명:** 충분한 조명 확보
3. **카메라 설정:** 코드 내 노출, ISO, 화이트 밸런스 조정
4. **안정성:** 카메라 고정, 필요시 삼각대 사용
5. **해상도:** 카메라 최대 해상도 초과하지 않도록 주의

### 마이크와 스피커

#### 문제: 오디오 입력/출력 불가
**증상:** 마이크 녹음 안되고 스피커 소리 안남

**해결책:**
1. **연결 확인:** 오디오 장치가 제대로 연결되었는지 확인
2. **하드웨어 테스트:**
   - 스피커: `speaker-test -t wav -c 2`
   - 마이크: `arecord -l`로 목록 확인, `arecord test.wav`로 녹음
3. **볼륨 설정:** 볼륨 확인 및 조정:
   ```bash
   alsamixer
   ```
4. **오디오 장치 선택:** 코드 내 올바른 오디오 장치 지정
5. **드라이버 문제:** ALSA 업데이트 또는 오디오 드라이버 재설치

#### 문제: ReSpeaker HAT 작동 안함
**증상:** 오디오 장치 인식 불가

**해결책:**
1. **드라이버 설치:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```

- **환경:** OS, Python 버전, 사용된 하드웨어  
- **재현 단계:** 문제를 일으키는 구체적인 단계  
- **예상 동작:** 예상되는 동작  
- **실제 동작:** 실제 발생하는 동작  
- **오류 메시지:** 스크린샷이 아닌 전체 오류 텍스트  
- **코드:** 문제를 재현하는 최소 코드 예제  

---

## 예방을 위한 팁

### 일반 모범 사례  
1. **백업 유지:** 작동하는 SD 카드/코드의 정기 백업  
2. **변경 사항 문서화:** 주석에 작동하는 내용을 기록  
3. **버전 관리:** git 사용하여 코드 변경 사항 추적  
4. **점진적 테스트:** 결합하기 전에 작은 변경 사항 테스트  
5. **오류 메시지 읽기:** 오류 메시지가 문제를 정확히 알려주는 경우가 많음  
6. **정기 업데이트:** 소프트웨어/펌웨어를 최신 상태로 유지  
7. **품질 좋은 부품 사용:** 저렴한 케이블/전원 공급 장치 피하기  
8. **안정적인 전원 공급:** 적절한 전원 공급 장치 사용 (특히 Pi에서)  

### 개발 워크플로우  
1. **단순하게 시작:** 작동하는 예제 코드로 시작  
2. **한 번에 한 가지 변경:** 문제를 찾기 쉬움  
3. **자주 테스트:** 문제를 조기에 발견  
4. **깔끔하게 유지:** 파일과 코드를 논리적으로 정리  
5. **주석 작성:** 미래의 자신이 고마워함  

---

*이 문제 해결 가이드는 커뮤니티에서 관리합니다. 여기에 나와 있지 않은 문제에 대한 해결책을 찾으면, 다른 사람들을 돕기 위해 [기여](CONTRIBUTING.md)를 고려해 주세요!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역은 오류나 부정확성이 포함될 수 있음을 유념해 주시기 바랍니다. 원문은 해당 언어로 작성된 원본 문서를 권위 있는 출처로 간주해야 합니다. 중요 정보의 경우 전문적인 인간 번역을 권장합니다. 본 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해서는 당사가 책임지지 않습니다.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->