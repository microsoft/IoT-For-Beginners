<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-24T21:02:49+00:00",
  "source_file": "hardware.md",
  "language_code": "ja"
}
-->
# ハードウェア

IoTの「T」は「Things（モノ）」を指し、私たちの周囲の世界とやり取りするデバイスを意味します。各プロジェクトは、学生や趣味で取り組む人々が利用できる実際のハードウェアに基づいています。使用するIoTハードウェアは、個人の好み、プログラミング言語の知識や好み、学習目標、利用可能性に応じて2つの選択肢があります。また、ハードウェアにアクセスできない場合や購入を決める前にもっと学びたい場合のために、「仮想ハードウェア」バージョンも提供しています。

> 💁 課題を完了するためにIoTハードウェアを購入する必要はありません。すべて仮想IoTハードウェアを使用して行うことができます。

物理的なハードウェアの選択肢は、ArduinoまたはRaspberry Piです。それぞれのプラットフォームには利点と欠点があり、これらは初期のレッスンの1つで説明されています。まだどのハードウェアプラットフォームを選ぶか決めていない場合は、[最初のプロジェクトのレッスン2](./1-getting-started/lessons/2-deeper-dive/README.md)を確認して、興味のあるプラットフォームを選んでください。

特定のハードウェアは、レッスンや課題の複雑さを軽減するために選ばれました。他のハードウェアでも動作する可能性はありますが、追加のハードウェアなしではすべての課題がサポートされる保証はありません。例えば、多くのArduinoデバイスにはWiFiが搭載されておらず、クラウドに接続するために必要です。そのため、WiFiが内蔵されているWio Terminalが選ばれました。

また、土や鉢植え、果物や野菜など、いくつかの技術的でないアイテムも必要です。

## キットを購入する

![Seeed Studiosのロゴ](../../translated_images/seeed-logo.74732b6b482b6e8e.ja.png)

Seeed Studiosは、すべてのハードウェアを簡単に購入できるキットとして提供してくれています。

### Arduino - Wio Terminal

**[SeeedとMicrosoftによる初心者向けIoT - Wio Terminalスターターキット](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio Terminalハードウェアキット](../../translated_images/wio-hardware-kit.4c70c48b85e4283a.ja.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[SeeedとMicrosoftによる初心者向けIoT - Raspberry Pi 4スターターキット](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi Terminalハードウェアキット](../../translated_images/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.ja.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Arduino用のデバイスコードはすべてC++で記述されています。すべての課題を完了するには以下が必要です。

### Arduinoハードウェア

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *オプション* - USB-CケーブルまたはUSB-A to USB-Cアダプター。Wio TerminalにはUSB-Cポートがあり、USB-C to USB-Aケーブルが付属しています。PCやMacにUSB-Cポートしかない場合は、USB-CケーブルまたはUSB-A to USB-Cアダプターが必要です。

### Arduino専用センサーとアクチュエーター

これらはWio Terminal Arduinoデバイスを使用する場合に特有のものであり、Raspberry Piを使用する場合には関連しません。

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [ブレッドボードジャンパーワイヤー](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* ヘッドホンまたは3.5mmジャック付きのスピーカー、または以下のようなJSTスピーカー：
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* 16GB以下のmicroSDカード、およびコンピュータでSDカードを使用するためのコネクタ（内蔵されていない場合）。**注意** - Wio Terminalは16GBまでのSDカードのみサポートしており、それ以上の容量はサポートしていません。

## Raspberry Pi

Raspberry Pi用のデバイスコードはすべてPythonで記述されています。すべての課題を完了するには以下が必要です。

### Raspberry Piハードウェア

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Pi 2B以降のバージョンはこれらのレッスンの課題で動作するはずです。VS CodeをPi上で直接実行する予定がある場合は、2GB以上のRAMを持つPi 4が必要です。Piにリモートでアクセスする場合は、Pi 2B以降のどのバージョンでも動作します。
* microSDカード（Raspberry PiキットにはmicroSDカードが付属している場合があります）、およびコンピュータでSDカードを使用するためのコネクタ（内蔵されていない場合）。
* USB電源アダプター（Raspberry Pi 4キットには電源アダプターが付属している場合があります）。Raspberry Pi 4を使用する場合はUSB-C電源アダプターが必要で、以前のデバイスではmicro-USB電源アダプターが必要です。

### Raspberry Pi専用センサーとアクチュエーター

これらはRaspberry Piを使用する場合に特有のものであり、Arduinoデバイスを使用する場合には関連しません。

* [Grove Piベースハット](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Piカメラモジュール](https://www.raspberrypi.org/products/camera-module-v2/)
* マイクとスピーカー：

  以下のいずれか（または同等品）を使用：
  * USBマイクとUSBスピーカー、または3.5mmジャックケーブル付きスピーカー、またはRaspberry Piがスピーカー付きのモニターやテレビに接続されている場合はHDMIオーディオ出力
  * マイク内蔵のUSBヘッドセット
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)と
    * ヘッドホンまたは3.5mmジャック付きのスピーカー、または以下のようなJSTスピーカー：
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USBスピーカーフォン](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Groveライトセンサー](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Groveボタン](https://www.seeedstudio.com/Grove-Button.html)

## センサーとアクチュエーター

必要なセンサーとアクチュエーターのほとんどは、ArduinoとRaspberry Piの両方の学習パスで使用されます：

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove湿度・温度センサー](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove静電容量式土壌湿度センサー](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Groveリレー](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove飛行時間距離センサー](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## オプションのハードウェア

自動灌漑に関するレッスンはリレーを使用して動作します。オプションとして、以下のハードウェアを使用してUSBで動作する水ポンプをこのリレーに接続することができます。

* [6V水ポンプ](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB端子](https://www.adafruit.com/product/3628)
* シリコンパイプ
* 赤と黒のワイヤー
* 小型のフラットヘッドドライバー

## 仮想ハードウェア

仮想ハードウェアルートでは、Pythonで実装されたセンサーとアクチュエーターのシミュレーターを提供します。ハードウェアの可用性に応じて、通常の開発デバイス（MacやPCなど）でこれを実行するか、Raspberry Piで実行して持っていないハードウェアのみをシミュレートすることができます。例えば、Raspberry Piカメラを持っているがGroveセンサーを持っていない場合、仮想デバイスコードをPi上で実行し、Groveセンサーをシミュレートしながら物理的なカメラを使用することができます。

仮想ハードウェアは[CounterFitプロジェクト](https://github.com/CounterFit-IoT/CounterFit)を使用します。

これらのレッスンを完了するには、ウェブカメラ、マイク、スピーカーやヘッドホンなどのオーディオ出力が必要です。これらは内蔵型でも外部接続型でも構いませんが、オペレーティングシステムで動作するように設定され、すべてのアプリケーションで使用可能である必要があります。

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解釈について、当社は責任を負いません。