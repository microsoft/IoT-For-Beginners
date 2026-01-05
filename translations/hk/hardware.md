<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-26T13:57:32+00:00",
  "source_file": "hardware.md",
  "language_code": "hk"
}
-->
# 硬件

在物聯網 (IoT) 中，**T** 代表 **Things**，指的是與周圍環境互動的設備。每個項目都基於學生和愛好者可用的實際硬件。我們提供了兩種物聯網硬件選擇，根據個人喜好、編程語言知識或偏好、學習目標和可用性進行選擇。此外，我們還提供了“虛擬硬件”版本，適合那些無法獲得硬件或希望在購買前進一步了解的人。

> 💁 您不需要購買任何物聯網硬件即可完成作業。您可以使用虛擬物聯網硬件完成所有內容。

實體硬件選擇包括 Arduino 或 Raspberry Pi。每個平台都有其優勢和劣勢，這些都會在初始課程中進行介紹。如果您尚未決定使用哪個硬件平台，可以查看[第一個項目的第二課](./1-getting-started/lessons/2-deeper-dive/README.md)，以選擇您最感興趣的硬件平台。

我們選擇的特定硬件旨在減少課程和作業的複雜性。雖然其他硬件可能也能使用，但我們無法保證所有作業都能在您的設備上支持，除非額外添加硬件。例如，許多 Arduino 設備不具備 WiFi 功能，而 WiFi 是連接到雲端所需的——因此選擇了內建 WiFi 的 Wio Terminal。

此外，您還需要一些非技術性物品，例如土壤或盆栽植物，以及水果或蔬菜。

## 購買套件

![Seeed Studios 標誌](../../translated_images/seeed-logo.74732b6b482b6e8e.hk.png)

Seeed Studios 非常友善地將所有硬件製作成易於購買的套件：

### Arduino - Wio Terminal

**[Seeed 和 Microsoft 的物聯網入門 - Wio Terminal 初學者套件](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio Terminal 硬件套件](../../translated_images/wio-hardware-kit.4c70c48b85e4283a.hk.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[Seeed 和 Microsoft 的物聯網入門 - Raspberry Pi 4 初學者套件](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi 硬件套件](../../translated_images/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.hk.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

所有 Arduino 的設備代碼均使用 C++ 編寫。要完成所有作業，您需要以下硬件：

### Arduino 硬件

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *可選* - USB-C 線或 USB-A 至 USB-C 轉接器。Wio Terminal 配備 USB-C 端口，並附帶 USB-C 至 USB-A 線。如果您的 PC 或 Mac 只有 USB-C 端口，您需要 USB-C 線或 USB-A 至 USB-C 轉接器。

### Arduino 特定的感測器和執行器

這些是專門用於 Wio Terminal Arduino 設備的，與 Raspberry Pi 無關。

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [麵包板跳線](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* 耳機或其他帶 3.5mm 插孔的揚聲器，或 JST 揚聲器，例如：
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD 卡（16GB 或以下），以及一個連接器，用於在您的電腦上使用 SD 卡（如果您的電腦沒有內建 SD 卡插槽）。**注意** - Wio Terminal 只支持最大 16GB 的 SD 卡，不支持更高容量。

## Raspberry Pi

所有 Raspberry Pi 的設備代碼均使用 Python 編寫。要完成所有作業，您需要以下硬件：

### Raspberry Pi 硬件

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 從 Pi 2B 及以上版本應該都能完成這些課程中的作業。如果您計劃直接在 Pi 上運行 VS Code，那麼需要 Pi 4 並配備 2GB 或以上的 RAM。如果您打算遠程訪問 Pi，那麼任何 Pi 2B 及以上版本都可以使用。
* microSD 卡（您可以購買附帶 microSD 卡的 Raspberry Pi 套件），以及一個連接器，用於在您的電腦上使用 SD 卡（如果您的電腦沒有內建 SD 卡插槽）。
* USB 電源供應器（您可以購買附帶電源供應器的 Raspberry Pi 4 套件）。如果您使用 Raspberry Pi 4，則需要 USB-C 電源供應器，早期設備則需要 micro-USB 電源供應器。

### Raspberry Pi 特定的感測器和執行器

這些是專門用於 Raspberry Pi 的，與 Arduino 設備無關。

* [Grove Pi 基座帽](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi 相機模組](https://www.raspberrypi.org/products/camera-module-v2/)
* 麥克風和揚聲器：

  使用以下任意一種（或同等設備）：
  * 任意 USB 麥克風搭配任意 USB 揚聲器，或帶 3.5mm 插孔的揚聲器，或使用 HDMI 音頻輸出（如果您的 Raspberry Pi 連接到帶揚聲器的顯示器或電視）
  * 任意內建麥克風的 USB 耳機
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) 搭配
    * 耳機或其他帶 3.5mm 插孔的揚聲器，或 JST 揚聲器，例如：
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove 光感測器](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove 按鈕](https://www.seeedstudio.com/Grove-Button.html)

## 感測器和執行器

大多數需要的感測器和執行器可用於 Arduino 和 Raspberry Pi 學習路徑：

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove 濕度和溫度感測器](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove 電容式土壤濕度感測器](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove 繼電器](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove 飛行時間距離感測器](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## 可選硬件

自動澆水課程使用繼電器作為工作原理。作為選項，您可以使用以下硬件將繼電器連接到 USB 供電的水泵。

* [6V 水泵](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB 端子](https://www.adafruit.com/product/3628)
* 矽膠管
* 紅色和黑色電線
* 小型平頭螺絲刀

## 虛擬硬件

虛擬硬件路徑提供了感測器和執行器的模擬器，使用 Python 實現。根據您的硬件可用性，您可以在普通開發設備（如 Mac、PC）上運行，或在 Raspberry Pi 上運行並僅模擬您沒有的硬件。例如，如果您有 Raspberry Pi 相機但沒有 Grove 感測器，您可以在 Pi 上運行虛擬設備代碼，模擬 Grove 感測器，但使用實體相機。

虛擬硬件將使用 [CounterFit 項目](https://github.com/CounterFit-IoT/CounterFit)。

要完成這些課程，您需要擁有網絡攝像頭、麥克風和音頻輸出設備（如揚聲器或耳機）。這些可以是內建或外接的，並需要配置為與您的操作系統兼容，並可供所有應用程序使用。

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。