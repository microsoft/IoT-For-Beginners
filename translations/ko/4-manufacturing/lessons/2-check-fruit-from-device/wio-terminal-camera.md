<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-24T21:37:17+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "ko"
}
-->
# 이미지 캡처 - Wio Terminal

이 레슨의 이 부분에서는 Wio Terminal에 카메라를 추가하고 이미지를 캡처합니다.

## 하드웨어

Wio Terminal에는 카메라가 필요합니다.

사용할 카메라는 [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)입니다. 이 카메라는 OV2640 이미지 센서를 기반으로 한 2메가픽셀 카메라입니다. SPI 인터페이스를 통해 이미지를 캡처하며, I2C를 사용하여 센서를 구성합니다.

## 카메라 연결하기

ArduCam은 Grove 소켓이 없으며, 대신 Wio Terminal의 GPIO 핀을 통해 SPI 및 I2C 버스에 연결됩니다.

### 작업 - 카메라 연결하기

카메라를 연결하세요.

![ArduCam 센서](../../../../../translated_images/ko/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.png)

1. ArduCam의 하단 핀을 Wio Terminal의 GPIO 핀에 연결해야 합니다. 올바른 핀을 쉽게 찾을 수 있도록 Wio Terminal에 제공된 GPIO 핀 스티커를 핀 주변에 붙이세요:

    ![GPIO 핀 스티커가 붙은 Wio Terminal](../../../../../translated_images/ko/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. 점퍼 와이어를 사용하여 다음 연결을 만드세요:

    | ArduCAM 핀 | Wio Terminal 핀 | 설명                                   |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | SPI 칩 선택                             |
    | MOSI        | 19 (SPI_MOSI)    | SPI 컨트롤러 출력, 주변 장치 입력       |
    | MISO        | 21 (SPI_MISO)    | SPI 컨트롤러 입력, 주변 장치 출력       |
    | SCK         | 23 (SPI_SCLK)    | SPI 직렬 클럭                          |
    | GND         | 6 (GND)          | 접지 - 0V                              |
    | VCC         | 4 (5V)           | 5V 전원 공급                           |
    | SDA         | 3 (I2C1_SDA)     | I2C 직렬 데이터                        |
    | SCL         | 5 (I2C1_SCL)     | I2C 직렬 클럭                          |

    ![점퍼 와이어로 ArduCam과 Wio Terminal을 연결한 모습](../../../../../translated_images/ko/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.png)

    GND와 VCC 연결은 ArduCam에 5V 전원을 공급합니다. 이 카메라는 Grove 센서와 달리 3V가 아닌 5V로 작동합니다. 이 전원은 장치를 구동하는 USB-C 연결에서 직접 공급됩니다.

    > 💁 SPI 연결의 경우 ArduCam과 Wio Terminal 핀 이름은 코드에서 여전히 이전 명명 규칙을 사용합니다. 이 레슨의 지침에서는 새로운 명명 규칙을 사용하지만, 코드에서 핀 이름을 사용할 때는 예외입니다.

1. 이제 Wio Terminal을 컴퓨터에 연결할 수 있습니다.

## 카메라 연결을 위한 장치 프로그래밍

이제 Wio Terminal을 프로그래밍하여 연결된 ArduCAM 카메라를 사용할 수 있습니다.

### 작업 - 카메라 연결을 위한 장치 프로그래밍

1. PlatformIO를 사용하여 새로운 Wio Terminal 프로젝트를 만드세요. 프로젝트 이름을 `fruit-quality-detector`로 설정하세요. `setup` 함수에 시리얼 포트를 구성하는 코드를 추가하세요.

1. WiFi에 연결하는 코드를 추가하세요. WiFi 자격 증명은 `config.h` 파일에 저장하세요. 필요한 라이브러리를 `platformio.ini` 파일에 추가하는 것을 잊지 마세요.

1. ArduCam 라이브러리는 Arduino 라이브러리로 제공되지 않으므로 `platformio.ini` 파일에서 설치할 수 없습니다. 대신 GitHub 페이지에서 소스를 통해 설치해야 합니다. 다음 방법 중 하나를 사용하세요:

    * [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)에서 리포를 클론하세요.
    * GitHub 페이지 [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino)로 이동하여 **Code** 버튼에서 zip 파일로 코드를 다운로드하세요.

1. 이 코드에서 `ArduCAM` 폴더만 필요합니다. 전체 폴더를 프로젝트의 `lib` 폴더에 복사하세요.

    > ⚠️ 전체 폴더를 복사해야 하며, 코드가 `lib/ArduCam`에 있어야 합니다. `ArduCam` 폴더의 내용만 `lib` 폴더에 복사하지 말고, 전체 폴더를 복사하세요.

1. ArduCam 라이브러리 코드는 여러 유형의 카메라에 대해 작동합니다. 사용하려는 카메라 유형은 컴파일러 플래그를 사용하여 구성됩니다. 이를 통해 사용하지 않는 카메라에 대한 코드를 제거하여 라이브러리 크기를 최소화합니다. OV2640 카메라를 위해 라이브러리를 구성하려면 `platformio.ini` 파일 끝에 다음을 추가하세요:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    여기서 두 가지 컴파일러 플래그가 설정됩니다:

      * `ARDUCAM_SHIELD_V2`: 라이브러리에 카메라가 Arduino 보드(Shield)에 있다는 것을 알립니다.
      * `OV2640_CAM`: 라이브러리에 OV2640 카메라에 대한 코드만 포함하도록 알립니다.

1. `src` 폴더에 `camera.h`라는 헤더 파일을 추가하세요. 이 파일은 카메라와 통신하는 코드를 포함합니다. 다음 코드를 이 파일에 추가하세요:

    ```cpp
    #pragma once
    
    #include <ArduCAM.h>
    #include <Wire.h>
    
    class Camera
    {
    public:
        Camera(int format, int image_size) : _arducam(OV2640, PIN_SPI_SS)
        {
            _format = format;
            _image_size = image_size;
        }
    
        bool init()
        {
            // Reset the CPLD
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // Check if the ArduCAM SPI bus is OK
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // Change MCU mode
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // Check if the camera module type is OV2640
            _arducam.wrSensorReg8_8(0xff, 0x01);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
            if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42)))
            {
                return false;
            }
            
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
            _arducam.OV2640_set_Light_Mode(Auto);
            _arducam.OV2640_set_Special_effects(Normal);
            delay(1000);
    
            return true;
        }
    
        void startCapture()
        {
            _arducam.flush_fifo();
            _arducam.clear_fifo_flag();
            _arducam.start_capture();
        }
    
        bool captureReady()
        {
            return _arducam.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK);
        }
    
        bool readImageToBuffer(byte **buffer, uint32_t &buffer_length)
        {
            if (!captureReady()) return false;
    
            // Get the image file length
            uint32_t length = _arducam.read_fifo_length();
            buffer_length = length;
    
            if (length >= MAX_FIFO_SIZE)
            {
                return false;
            }
            if (length == 0)
            {
                return false;
            }
    
            // create the buffer
            byte *buf = new byte[length];
    
            uint8_t temp = 0, temp_last = 0;
            int i = 0;
            uint32_t buffer_pos = 0;
            bool is_header = false;
    
            _arducam.CS_LOW();
            _arducam.set_fifo_burst();
            
            while (length--)
            {
                temp_last = temp;
                temp = SPI.transfer(0x00);
                //Read JPEG data from FIFO
                if ((temp == 0xD9) && (temp_last == 0xFF)) //If find the end ,break while,
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //Write image data to buffer if not full
                    if (i < 256)
                    {
                        buf[buffer_pos] = temp;
                        buffer_pos++;
                        i++;
                    }
                    else
                    {
                        _arducam.CS_HIGH();
    
                        i = 0;
                        buf[buffer_pos] = temp;
    
                        buffer_pos++;
                        i++;
    
                        _arducam.CS_LOW();
                        _arducam.set_fifo_burst();
                    }
                }
                else if ((temp == 0xD8) & (temp_last == 0xFF))
                {
                    is_header = true;
    
                    buf[buffer_pos] = temp_last;
                    buffer_pos++;
                    i++;
    
                    buf[buffer_pos] = temp;
                    buffer_pos++;
                    i++;
                }
            }
            
            _arducam.clear_fifo_flag();
    
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
    
            // return the buffer
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    이 코드는 ArduCam 라이브러리를 사용하여 카메라를 구성하고 필요할 때 SPI 버스를 통해 이미지를 추출하는 저수준 코드입니다. 이 코드는 ArduCam에 매우 특화되어 있으므로 작동 방식에 대해 걱정할 필요는 없습니다.

1. `main.cpp`에서 다른 `include` 문 아래에 이 새 파일을 포함하고 카메라 클래스의 인스턴스를 생성하는 코드를 추가하세요:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    이 코드는 JPEG 형식으로 640x480 해상도의 이미지를 저장하는 `Camera`를 생성합니다. 더 높은 해상도(최대 3280x2464)도 지원되지만, 이미지 분류기는 훨씬 작은 이미지(227x227)에서 작동하므로 더 큰 이미지를 캡처하고 전송할 필요가 없습니다.

1. 카메라를 설정하는 함수를 정의하는 다음 코드를 추가하세요:

    ```cpp
    void setupCamera()
    {
        pinMode(PIN_SPI_SS, OUTPUT);
        digitalWrite(PIN_SPI_SS, HIGH);
    
        Wire.begin();
        SPI.begin();
    
        if (!camera.init())
        {
            Serial.println("Error setting up the camera!");
        }
    }
    ```

    이 `setupCamera` 함수는 SPI 칩 선택 핀(`PIN_SPI_SS`)을 높게 설정하여 Wio Terminal을 SPI 컨트롤러로 구성하는 것으로 시작합니다. 그런 다음 I2C 및 SPI 버스를 시작합니다. 마지막으로 카메라 클래스가 초기화되어 카메라 센서 설정을 구성하고 모든 것이 올바르게 연결되었는지 확인합니다.

1. 이 함수를 `setup` 함수 끝에서 호출하세요:

    ```cpp
    setupCamera();
    ```

1. 코드를 빌드하고 업로드한 후 시리얼 모니터의 출력을 확인하세요. `Error setting up the camera!`라는 메시지가 표시되면 ArduCam의 모든 케이블이 Wio Terminal의 올바른 GPIO 핀에 연결되었는지, 점퍼 케이블이 제대로 연결되었는지 확인하세요.

## 이미지 캡처

이제 Wio Terminal을 프로그래밍하여 버튼이 눌렸을 때 이미지를 캡처할 수 있습니다.

### 작업 - 이미지 캡처

1. 마이크로컨트롤러는 코드를 지속적으로 실행하므로 센서에 반응하지 않고 사진을 찍는 것과 같은 작업을 트리거하기가 쉽지 않습니다. Wio Terminal에는 버튼이 있으므로 카메라를 버튼 중 하나로 트리거하도록 설정할 수 있습니다. `setup` 함수 끝에 다음 코드를 추가하여 C 버튼(세 개의 버튼 중 전원 스위치에 가장 가까운 버튼)을 구성하세요.

    ![전원 스위치에 가장 가까운 C 버튼](../../../../../translated_images/ko/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    `INPUT_PULLUP` 모드는 입력을 반전시킵니다. 예를 들어, 일반적으로 버튼은 눌리지 않았을 때 낮은 신호를 보내고 눌렸을 때 높은 신호를 보냅니다. `INPUT_PULLUP`으로 설정하면 눌리지 않았을 때 높은 신호를 보내고 눌렸을 때 낮은 신호를 보냅니다.

1. `loop` 함수 전에 버튼 누름에 반응하는 빈 함수를 추가하세요:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. 버튼이 눌렸을 때 `loop` 메서드에서 이 함수를 호출하세요:

    ```cpp
    void loop()
    {
        if (digitalRead(WIO_KEY_C) == LOW)
        {
            buttonPressed();
            delay(2000);
        }
    
        delay(200);
    }
    ```

    이 코드는 버튼이 눌렸는지 확인합니다. 버튼이 눌렸다면 `buttonPressed` 함수가 호출되고 루프는 2초 동안 지연됩니다. 이는 버튼이 두 번 등록되지 않도록 버튼이 릴리스될 시간을 허용하기 위함입니다.

    > 💁 Wio Terminal의 버튼은 `INPUT_PULLUP`으로 설정되어 있으므로 눌리지 않았을 때 높은 신호를 보내고 눌렸을 때 낮은 신호를 보냅니다.

1. `buttonPressed` 함수에 다음 코드를 추가하세요:

    ```cpp
    camera.startCapture();
 
    while (!camera.captureReady())
        delay(100);

    Serial.println("Image captured");

    byte *buffer;
    uint32_t length;

    if (camera.readImageToBuffer(&buffer, length))
    {
        Serial.print("Image read to buffer with length ");
        Serial.println(length);

        delete(buffer);
    }
    ```

    이 코드는 `startCapture`를 호출하여 카메라 캡처를 시작합니다. 카메라 하드웨어는 요청 시 데이터를 반환하는 방식으로 작동하지 않습니다. 대신 캡처를 시작하라는 명령을 보내면 카메라는 백그라운드에서 이미지를 캡처하고 JPEG로 변환하여 카메라 자체의 로컬 버퍼에 저장합니다. `captureReady` 호출은 이미지 캡처가 완료되었는지 확인합니다.

    캡처가 완료되면 `readImageToBuffer` 호출을 통해 카메라의 버퍼에서 로컬 버퍼(바이트 배열)로 이미지 데이터를 복사합니다. 그런 다음 버퍼의 길이가 시리얼 모니터로 전송됩니다.

1. 코드를 빌드하고 업로드한 후 시리얼 모니터의 출력을 확인하세요. C 버튼을 누를 때마다 이미지가 캡처되고 이미지 크기가 시리얼 모니터에 표시됩니다.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    이미지에 따라 크기가 다를 수 있습니다. 이미지는 JPEG로 압축되며 특정 해상도의 JPEG 파일 크기는 이미지 내용에 따라 달라집니다.

> 💁 이 코드는 [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal) 폴더에서 확인할 수 있습니다.

😀 Wio Terminal로 이미지를 성공적으로 캡처했습니다.

## 선택 사항 - SD 카드를 사용하여 카메라 이미지 확인

카메라로 캡처한 이미지를 확인하는 가장 쉬운 방법은 Wio Terminal의 SD 카드에 이미지를 저장한 후 컴퓨터에서 확인하는 것입니다. 여분의 microSD 카드와 컴퓨터에 microSD 카드 소켓 또는 어댑터가 있는 경우 이 단계를 수행하세요.

Wio Terminal은 최대 16GB 크기의 microSD 카드만 지원합니다. 더 큰 SD 카드는 작동하지 않습니다.

### 작업 - SD 카드를 사용하여 카메라 이미지 확인

1. 컴퓨터의 관련 애플리케이션(macOS의 Disk Utility, Windows의 File Explorer, Linux의 명령줄 도구)을 사용하여 microSD 카드를 FAT32 또는 exFAT으로 포맷하세요.

1. 전원 스위치 바로 아래의 소켓에 microSD 카드를 삽입하세요. 클릭 소리가 나고 제자리에 고정될 때까지 끝까지 삽입하세요. 손톱이나 얇은 도구를 사용해야 할 수도 있습니다.

1. `main.cpp` 파일 상단에 다음 포함 문을 추가하세요:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. `setup` 함수 전에 다음 함수를 추가하세요:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    이 함수는 SPI 버스를 사용하여 SD 카드를 구성합니다.

1. `setup` 함수에서 이 함수를 호출하세요:

    ```cpp
    setupSDCard();
    ```

1. `buttonPressed` 함수 위에 다음 코드를 추가하세요:

    ```cpp
    int fileNum = 1;

    void saveToSDCard(byte *buffer, uint32_t length)
    {
        char buff[16];
        sprintf(buff, "%d.jpg", fileNum);
        fileNum++;
    
        File outFile = SD.open(buff, FILE_WRITE );
        outFile.write(buffer, length);
        outFile.close();

        Serial.print("Image written to file ");
        Serial.println(buff);
    }
    ```

    이 코드는 파일 카운트를 위한 전역 변수를 정의합니다. 이는 이미지 파일 이름에 사용되며 여러 이미지를 캡처할 때 증가하는 파일 이름을 생성합니다 - `1.jpg`, `2.jpg` 등.

    그런 다음 바이트 데이터 버퍼와 버퍼 길이를 받는 `saveToSDCard`를 정의합니다. 파일 카운트를 사용하여 파일 이름을 생성하고, 다음 파일을 위해 파일 카운트를 증가시킵니다. 그런 다음 버퍼의 바이너리 데이터를 파일에 씁니다.

1. `buttonPressed` 함수에서 `saveToSDCard` 함수를 호출하세요. 호출은 버퍼가 삭제되기 **전에** 이루어져야 합니다:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. 코드를 빌드하고 업로드한 후 시리얼 모니터의 출력을 확인하세요. C 버튼을 누를 때마다 이미지가 캡처되고 SD 카드에 저장됩니다.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 16392
    Image written to file 1.jpg
    Image captured
    Image read to buffer with length 14344
    Image written to file 2.jpg
    ```

1. microSD 카드를 꺼내려면 전원을 끄고 약간 눌렀다가 놓으면 튀어나옵니다. 얇은 도구를 사용해야 할 수도 있습니다. microSD 카드를 컴퓨터에 연결하여 이미지를 확인하세요.

    ![ArduCam으로 캡처한 바나나 사진](../../../../../translated_images/ko/banana-arducam.be1b32d4267a8194b0fd042362e56faa431da9cd4af172051b37243ea9be0256.jpg)
💁 카메라의 화이트 밸런스가 조정되는 데 몇 장의 이미지가 필요할 수 있습니다. 캡처된 이미지의 색상을 기준으로 이를 알 수 있으며, 처음 몇 장은 색상이 이상해 보일 수 있습니다. `setup` 함수에서 무시되는 몇 장의 이미지를 캡처하도록 코드를 변경하여 이를 해결할 수 있습니다.


**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전을 권위 있는 출처로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 책임을 지지 않습니다.