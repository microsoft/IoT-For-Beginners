<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-24T21:36:41+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "ja"
}
-->
# 画像をキャプチャする - Wio Terminal

このレッスンでは、Wio Terminalにカメラを追加し、画像をキャプチャします。

## ハードウェア

Wio Terminalにはカメラが必要です。

使用するカメラは[ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)です。このカメラはOV2640イメージセンサーをベースにした2メガピクセルのカメラで、SPIインターフェースを介して画像をキャプチャし、I2Cを使用してセンサーを設定します。

## カメラを接続する

ArduCamにはGroveソケットがありません。その代わり、GPIOピンを介してSPIとI2Cバスに接続します。

### タスク - カメラを接続する

カメラを接続します。

![ArduCamセンサー](../../../../../translated_images/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.ja.png)

1. ArduCamの底部のピンをWio TerminalのGPIOピンに接続する必要があります。正しいピンを見つけやすくするために、Wio Terminalに付属しているGPIOピンステッカーをピンの周りに貼り付けます：

    ![GPIOピンステッカーを貼ったWio Terminal](../../../../../translated_images/wio-terminal-pin-sticker.b90b1535937b84bd.ja.png)

1. ジャンパーワイヤーを使用して、以下の接続を行います：

    | ArduCAMピン | Wio Terminalピン | 説明                                   |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | SPIチップセレクト                       |
    | MOSI        | 19 (SPI_MOSI)    | SPIコントローラー出力、ペリフェラル入力 |
    | MISO        | 21 (SPI_MISO)    | SPIコントローラー入力、ペリフェラル出力 |
    | SCK         | 23 (SPI_SCLK)    | SPIシリアルクロック                     |
    | GND         | 6 (GND)          | グラウンド - 0V                         |
    | VCC         | 4 (5V)           | 5V電源供給                              |
    | SDA         | 3 (I2C1_SDA)     | I2Cシリアルデータ                       |
    | SCL         | 5 (I2C1_SCL)     | I2Cシリアルクロック                     |

    ![ジャンパーワイヤーでArduCamを接続したWio Terminal](../../../../../translated_images/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.ja.png)

    GNDとVCCの接続はArduCamに5Vの電源を供給します。ArduCamは5Vで動作しますが、Groveセンサーは3Vで動作します。この電源はデバイスを供給するUSB-C接続から直接供給されます。

    > 💁 SPI接続では、ArduCamのピンラベルとコードで使用されるWio Terminalのピン名は古い命名規則を使用しています。このレッスンでは新しい命名規則を使用しますが、コード内でピン名を使用する場合は例外です。

1. Wio Terminalをコンピュータに接続できます。

## デバイスをプログラムしてカメラに接続する

Wio Terminalをプログラムして、接続されたArduCAMカメラを使用できるようにします。

### タスク - デバイスをプログラムしてカメラに接続する

1. PlatformIOを使用して新しいWio Terminalプロジェクトを作成します。このプロジェクトを`fruit-quality-detector`と名付け、`setup`関数にシリアルポートを設定するコードを追加します。

1. WiFiに接続するコードを追加し、WiFiの認証情報を`config.h`というファイルに保存します。必要なライブラリを`platformio.ini`ファイルに追加するのを忘れないでください。

1. ArduCamライブラリはArduinoライブラリとして`platformio.ini`ファイルからインストールできません。代わりに、GitHubページからソースコードをインストールする必要があります。以下の方法で取得できます：

    * [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)からリポジトリをクローンする
    * GitHubのリポジトリページ[github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino)にアクセスし、**Code**ボタンからコードをzip形式でダウンロードする

1. このコードから`ArduCAM`フォルダのみが必要です。このフォルダ全体をプロジェクトの`lib`フォルダにコピーします。

    > ⚠️ フォルダ全体をコピーする必要があります。コードは`lib/ArduCam`に配置されるようにしてください。`ArduCam`フォルダの内容だけを`lib`フォルダにコピーするのではなく、フォルダ全体をコピーしてください。

1. ArduCamライブラリコードは複数の種類のカメラに対応しています。使用するカメラの種類はコンパイラフラグを使用して設定します。これにより、使用しないカメラのコードを削除してライブラリをできるだけ小さく保つことができます。OV2640カメラ用にライブラリを設定するには、以下を`platformio.ini`ファイルの末尾に追加します：

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    これにより、2つのコンパイラフラグが設定されます：

      * `ARDUCAM_SHIELD_V2` - ライブラリにカメラがArduinoボード（シールド）上にあることを伝えます。
      * `OV2640_CAM` - ライブラリにOV2640カメラ用のコードのみを含めるよう指示します。

1. `src`フォルダに`camera.h`というヘッダーファイルを追加します。このファイルにはカメラと通信するコードが含まれます。このファイルに以下のコードを追加します：

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

    これはArduCamライブラリを使用してカメラを設定し、必要に応じてSPIバスを介して画像を抽出する低レベルコードです。このコードはArduCamに特化しているため、現時点ではその動作について心配する必要はありません。

1. `main.cpp`で、他の`include`ステートメントの下にこの新しいファイルを含めるコードを追加し、カメラクラスのインスタンスを作成します：

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    これにより、JPEG形式で640x480の解像度で画像を保存する`Camera`が作成されます。より高い解像度（最大3280x2464）もサポートされていますが、画像分類器ははるかに小さい画像（227x227）で動作するため、より大きな画像をキャプチャして送信する必要はありません。

1. 以下のコードを追加してカメラをセットアップする関数を定義します：

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

    この`setupCamera`関数は、SPIチップセレクトピン（`PIN_SPI_SS`）を高に設定してWio TerminalをSPIコントローラーとして構成することから始まります。その後、I2CとSPIバスを開始します。最後に、カメラクラスを初期化してカメラセンサーの設定を構成し、すべてが正しく配線されていることを確認します。

1. この関数を`setup`関数の最後で呼び出します：

    ```cpp
    setupCamera();
    ```

1. このコードをビルドしてアップロードし、シリアルモニターの出力を確認します。`Error setting up the camera!`というメッセージが表示された場合は、ArduCamのすべてのケーブルが正しいピンに接続されていること、ジャンパーケーブルが正しく接続されていることを確認してください。

## 画像をキャプチャする

Wio Terminalをプログラムして、ボタンが押されたときに画像をキャプチャできるようにします。

### タスク - 画像をキャプチャする

1. マイクロコントローラーはコードを継続的に実行するため、センサーに反応せずに写真を撮るような動作をトリガーするのは簡単ではありません。Wio Terminalにはボタンがあるため、カメラをボタンの1つでトリガーするように設定できます。以下のコードを`setup`関数の最後に追加して、Cボタン（3つのボタンのうち、電源スイッチに最も近いボタン）を設定します。

    ![電源スイッチに最も近いCボタン](../../../../../translated_images/wio-terminal-c-button.73df3cb1c1445ea0.ja.png)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    `INPUT_PULLUP`モードは入力を反転させるような動作をします。例えば、通常のボタンは押されていないときに低信号を送り、押されると高信号を送ります。`INPUT_PULLUP`に設定すると、押されていないときに高信号を送り、押されると低信号を送ります。

1. `loop`関数の前にボタン押下に応答する空の関数を追加します：

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. ボタンが押されたときにこの関数を`loop`メソッドで呼び出します：

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

    このキーはボタンが押されているかどうかを確認します。押されている場合は`buttonPressed`関数が呼び出され、ループは2秒間遅延します。これは、ボタンがリリースされる時間を確保し、長押しが2回登録されないようにするためです。

    > 💁 Wio Terminalのボタンは`INPUT_PULLUP`に設定されているため、押されていないときに高信号を送り、押されると低信号を送ります。

1. `buttonPressed`関数に以下のコードを追加します：

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

    このコードは`startCapture`を呼び出してカメラキャプチャを開始します。カメラハードウェアはデータを要求したときに返すのではなく、キャプチャを開始する指示を送信し、カメラはバックグラウンドで画像をキャプチャし、JPEGに変換し、カメラ自体のローカルバッファに保存します。その後、`captureReady`呼び出しで画像キャプチャが完了したかどうかを確認します。

    キャプチャが完了すると、`readImageToBuffer`呼び出しでカメラのバッファからローカルバッファ（バイト配列）に画像データがコピーされます。その後、バッファの長さがシリアルモニターに送信されます。

1. このコードをビルドしてアップロードし、シリアルモニターの出力を確認します。Cボタンを押すたびに画像がキャプチャされ、画像サイズがシリアルモニターに送信されます。

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    異なる画像は異なるサイズになります。JPEGとして圧縮されており、特定の解像度のJPEGファイルのサイズは画像内の内容によって異なります。

> 💁 このコードは[code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal)フォルダにあります。

😀 Wio Terminalで画像を正常にキャプチャできました。

## オプション - SDカードを使用してカメラ画像を確認する

カメラでキャプチャした画像を確認する最も簡単な方法は、Wio TerminalのSDカードに書き込み、それをコンピュータで表示することです。予備のmicroSDカードとコンピュータにmicroSDカードソケットまたはアダプタがある場合、このステップを実行してください。

Wio Terminalは最大16GBのmicroSDカードのみをサポートします。より大きなSDカードを使用している場合は動作しません。

### タスク - SDカードを使用してカメラ画像を確認する

1. コンピュータの関連アプリケーション（macOSではDisk Utility、WindowsではFile Explorer、Linuxではコマンドラインツール）を使用してmicroSDカードをFAT32またはexFATとしてフォーマットします。

1. microSDカードを電源スイッチのすぐ下にあるソケットに挿入します。クリックして固定されるまで完全に挿入してください。爪や薄いツールを使用して押し込む必要がある場合があります。

1. 以下のincludeステートメントを`main.cpp`ファイルの冒頭に追加します：

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. `setup`関数の前に以下の関数を追加します：

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    これにより、SPIバスを使用してSDカードが構成されます。

1. `setup`関数からこれを呼び出します：

    ```cpp
    setupSDCard();
    ```

1. `buttonPressed`関数の上に以下のコードを追加します：

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

    これにより、ファイルカウントのグローバル変数が定義されます。これは画像ファイル名に使用され、複数の画像をキャプチャしてインクリメントされたファイル名（`1.jpg`、`2.jpg`など）を持つことができます。

    次に、バイトデータのバッファとバッファの長さを受け取る`saveToSDCard`関数を定義します。ファイルカウントを使用してファイル名が作成され、次のファイルに備えてファイルカウントがインクリメントされます。その後、バッファのバイナリデータがファイルに書き込まれます。

1. `buttonPressed`関数から`saveToSDCard`関数を呼び出します。この呼び出しはバッファが削除される**前**である必要があります：

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. このコードをビルドしてアップロードし、シリアルモニターの出力を確認します。Cボタンを押すたびに画像がキャプチャされ、SDカードに保存されます。

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

1. microSDカードの電源をオフにして、少し押し込んでリリースすることで取り出します。カードがポップアウトします。これを行うには薄いツールを使用する必要がある場合があります。microSDカードをコンピュータに接続して画像を表示します。

    ![ArduCamで撮影されたバナナの写真](../../../../../translated_images/banana-arducam.be1b32d4267a8194b0fd042362e56faa431da9cd4af172051b37243ea9be0256.ja.jpg)
💁 カメラのホワイトバランスが調整されるまでに、数枚の画像が必要になる場合があります。これは、撮影された画像の色に基づいて気付くことができ、最初の数枚は色がずれて見えるかもしれません。この問題を回避するには、`setup`関数内で無視される数枚の画像を撮影するようにコードを変更することで対処できます。


**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された原文が正式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。