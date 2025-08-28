<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-28T00:24:48+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "tl"
}
-->
# Kontrolin ang Iyong Nightlight sa Internet - Wio Terminal

Kailangang i-code ang IoT device upang makipag-ugnayan sa *test.mosquitto.org* gamit ang MQTT para magpadala ng telemetry values mula sa light sensor reading, at tumanggap ng mga utos para kontrolin ang LED.

Sa bahaging ito ng aralin, ikokonekta mo ang iyong Wio Terminal sa isang MQTT broker.

## I-install ang WiFi at MQTT Arduino Libraries

Upang makipag-ugnayan sa MQTT broker, kailangan mong mag-install ng ilang Arduino libraries para magamit ang WiFi chip ng Wio Terminal at makipag-ugnayan gamit ang MQTT. Kapag nagde-develop para sa mga Arduino device, maaari kang gumamit ng malawak na hanay ng mga library na naglalaman ng open-source code at nag-aalok ng maraming kakayahan. Naglalathala ang Seeed ng mga library para sa Wio Terminal na nagbibigay-daan dito upang makipag-ugnayan gamit ang WiFi. May mga ibang developer din na naglalathala ng mga library para makipag-ugnayan sa MQTT brokers, at gagamitin mo ang mga ito sa iyong device.

Ang mga library na ito ay ibinibigay bilang source code na maaaring awtomatikong i-import sa PlatformIO at i-compile para sa iyong device. Sa ganitong paraan, gagana ang mga Arduino library sa anumang device na sumusuporta sa Arduino framework, basta't ang device ay may kinakailangang hardware para sa library na iyon. Ang ilang library, tulad ng Seeed WiFi libraries, ay partikular para sa ilang hardware.

Maaaring i-install ang mga library nang globally at i-compile kung kinakailangan, o para lamang sa isang partikular na proyekto. Para sa gawaing ito, ang mga library ay i-install sa proyekto.

✅ Maaari kang matuto nang higit pa tungkol sa library management at kung paano maghanap at mag-install ng mga library sa [PlatformIO library documentation](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Gawain - I-install ang WiFi at MQTT Arduino Libraries

I-install ang Arduino libraries.

1. Buksan ang nightlight project sa VS Code.

1. Idagdag ang sumusunod sa dulo ng `platformio.ini` file:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Ini-import nito ang Seeed WiFi libraries. Ang `@ <number>` syntax ay tumutukoy sa isang partikular na bersyon ng library.

    > 💁 Maaari mong alisin ang `@ <number>` upang palaging gamitin ang pinakabagong bersyon ng mga library, ngunit walang garantiya na gagana ang mga mas bagong bersyon sa code sa ibaba. Ang code dito ay nasubukan gamit ang bersyon ng mga library na ito.

    Ito lang ang kailangan mong gawin upang idagdag ang mga library. Sa susunod na i-build ng PlatformIO ang proyekto, ida-download nito ang source code para sa mga library na ito at i-compile ito sa iyong proyekto.

1. Idagdag ang sumusunod sa `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Ini-import nito ang [PubSubClient](https://github.com/knolleary/pubsubclient), isang Arduino MQTT client.

## Kumonekta sa WiFi

Ngayon ay maaaring ikonekta ang Wio Terminal sa WiFi.

### Gawain - Kumonekta sa WiFi

Ikonekta ang Wio Terminal sa WiFi.

1. Gumawa ng bagong file sa `src` folder na tinatawag na `config.h`. Magagawa mo ito sa pamamagitan ng pagpili sa `src` folder, o sa `main.cpp` file sa loob nito, at pagpili sa **New file** button mula sa explorer. Ang button na ito ay lilitaw lamang kapag ang iyong cursor ay nasa explorer.

    ![Ang new file button](../../../../../translated_images/vscode-new-file-button.182702340fe6723c8cbb4cfa1a9a9fb0d0a5227643b4e46b91ff67b07a39a92f.tl.png)

1. Idagdag ang sumusunod na code sa file na ito upang tukuyin ang mga constant para sa iyong WiFi credentials:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Palitan ang `<SSID>` ng SSID ng iyong WiFi. Palitan ang `<PASSWORD>` ng iyong WiFi password.

1. Buksan ang `main.cpp` file.

1. Idagdag ang sumusunod na `#include` directives sa itaas ng file:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Kasama dito ang mga header file para sa mga library na idinagdag mo kanina, pati na rin ang config header file. Ang mga header file na ito ay kinakailangan upang sabihin sa PlatformIO na isama ang code mula sa mga library. Kung hindi mo tahasang isasama ang mga header file na ito, ang ilang code ay hindi mai-compile at magkakaroon ka ng compiler errors.

1. Idagdag ang sumusunod na code sa itaas ng `setup` function:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Ang code na ito ay umiikot habang ang device ay hindi nakakonekta sa WiFi, at sinusubukang kumonekta gamit ang SSID at password mula sa config header file.

1. Idagdag ang tawag sa function na ito sa ibaba ng `setup` function, pagkatapos ma-configure ang mga pins.

    ```cpp
    connectWiFi();
    ```

1. I-upload ang code na ito sa iyong device upang suriin kung gumagana ang WiFi connection. Makikita mo ito sa serial monitor.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Kumonekta sa MQTT

Kapag nakakonekta na ang Wio Terminal sa WiFi, maaari na itong kumonekta sa MQTT broker.

### Gawain - Kumonekta sa MQTT

Ikonekta ang Wio Terminal sa MQTT broker.

1. Idagdag ang sumusunod na code sa dulo ng `config.h` file upang tukuyin ang mga detalye ng koneksyon para sa MQTT broker:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Palitan ang `<ID>` ng isang natatanging ID na gagamitin bilang pangalan ng device client na ito, at sa kalaunan para sa mga topic na ipo-publish at susubaybayan ng device na ito. Ang *test.mosquitto.org* broker ay pampubliko at ginagamit ng maraming tao, kabilang ang ibang mga estudyante na gumagawa ng gawaing ito. Ang pagkakaroon ng natatanging MQTT client name at topic names ay nagsisiguro na ang iyong code ay hindi magka-clash sa iba.

    > 💁 Maaari kang gumamit ng website tulad ng [GUIDGen](https://www.guidgen.com) upang makabuo ng natatanging ID.

    Ang `BROKER` ay ang URL ng MQTT broker.

    Ang `CLIENT_NAME` ay isang natatanging pangalan para sa MQTT client na ito sa broker.

1. Buksan ang `main.cpp` file, at idagdag ang sumusunod na code sa ibaba ng `connectWiFi` function at sa itaas ng `setup` function:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Ang code na ito ay lumilikha ng WiFi client gamit ang Wio Terminal WiFi libraries at ginagamit ito upang lumikha ng MQTT client.

1. Sa ibaba ng code na ito, idagdag ang sumusunod:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Ang function na ito ay sumusubok sa koneksyon sa MQTT broker at muling kumokonekta kung hindi ito nakakonekta. Umiikot ito habang hindi nakakonekta at sinusubukang kumonekta gamit ang natatanging client name na tinukoy sa config header file.

    Kung nabigo ang koneksyon, susubukan ulit ito pagkatapos ng 5 segundo.

1. Idagdag ang sumusunod na code sa ibaba ng `reconnectMQTTClient` function:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Ang code na ito ay nagse-set ng MQTT broker para sa client, pati na rin ang pag-set up ng callback kapag may natanggap na mensahe. Pagkatapos ay sinusubukan nitong kumonekta sa broker.

1. Tawagin ang `createMQTTClient` function sa `setup` function pagkatapos makakonekta ang WiFi.

1. Palitan ang buong `loop` function ng sumusunod:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Ang code na ito ay nagsisimula sa pamamagitan ng muling pagkonekta sa MQTT broker. Ang mga koneksyon na ito ay madaling maputol, kaya't mahalagang regular na suriin at muling kumonekta kung kinakailangan. Pagkatapos ay tinatawag nito ang `loop` method sa MQTT client upang iproseso ang anumang mga mensahe na dumarating sa topic na sinusubaybayan. Ang app na ito ay single-threaded, kaya't ang mga mensahe ay hindi maaaring matanggap sa isang background thread, kaya't kailangang maglaan ng oras sa main thread upang iproseso ang anumang mga mensaheng naghihintay sa network connection.

    Sa wakas, ang delay na 2 segundo ay nagsisiguro na ang light levels ay hindi masyadong madalas na ipinapadala at binabawasan ang power consumption ng device.

1. I-upload ang code sa iyong Wio Terminal, at gamitin ang Serial Monitor upang makita ang device na kumokonekta sa WiFi at MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Maaari mong makita ang code na ito sa [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) folder.

😀 Matagumpay mong naikonekta ang iyong device sa isang MQTT broker.

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.