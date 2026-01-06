<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T22:23:12+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "tl"
}
-->
# Kontrolin ang iyong nightlight sa Internet - Wio Terminal

Ang IoT device ay kailangang i-code upang makipag-ugnayan sa *test.mosquitto.org* gamit ang MQTT para magpadala ng telemetry values gamit ang light sensor reading, at tumanggap ng mga utos para kontrolin ang LED.

Sa bahaging ito ng aralin, ikokonekta mo ang iyong Wio Terminal sa isang MQTT broker.

## I-install ang WiFi at MQTT Arduino libraries

Upang makipag-ugnayan sa MQTT broker, kailangan mong mag-install ng ilang Arduino libraries para magamit ang WiFi chip sa Wio Terminal, at makipag-ugnayan gamit ang MQTT. Kapag nagde-develop para sa mga Arduino devices, maaari kang gumamit ng malawak na hanay ng libraries na naglalaman ng open-source code at nag-iimplementa ng maraming kakayahan. Ang Seeed ay naglalathala ng mga libraries para sa Wio Terminal na nagbibigay-daan dito upang makipag-ugnayan gamit ang WiFi. Ang ibang mga developer ay naglalathala ng mga libraries para makipag-ugnayan sa MQTT brokers, at gagamitin mo ang mga ito sa iyong device.

Ang mga libraries na ito ay ibinibigay bilang source code na maaaring awtomatikong i-import sa PlatformIO at i-compile para sa iyong device. Sa ganitong paraan, ang Arduino libraries ay gagana sa anumang device na sumusuporta sa Arduino framework, basta't ang device ay may partikular na hardware na kinakailangan ng library. Ang ilang libraries, tulad ng Seeed WiFi libraries, ay partikular sa ilang hardware.

Ang mga libraries ay maaaring i-install globally at i-compile kung kinakailangan, o sa isang partikular na proyekto. Para sa assignment na ito, ang mga libraries ay i-install sa proyekto.

✅ Maaari kang matuto pa tungkol sa library management at kung paano maghanap at mag-install ng libraries sa [PlatformIO library documentation](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Gawain - i-install ang WiFi at MQTT Arduino libraries

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

    Ina-import nito ang Seeed WiFi libraries. Ang `@ <number>` syntax ay tumutukoy sa isang partikular na bersyon ng library.

    > 💁 Maaari mong alisin ang `@ <number>` upang palaging gamitin ang pinakabagong bersyon ng libraries, ngunit walang garantiya na ang mga mas bagong bersyon ay gagana sa code sa ibaba. Ang code dito ay nasubukan gamit ang bersyon ng libraries na ito.

    Ito lang ang kailangan mong gawin upang idagdag ang libraries. Sa susunod na i-build ng PlatformIO ang proyekto, ida-download nito ang source code para sa mga libraries na ito at i-compile ito sa iyong proyekto.

1. Idagdag ang sumusunod sa `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Ina-import nito ang [PubSubClient](https://github.com/knolleary/pubsubclient), isang Arduino MQTT client.

## Kumonekta sa WiFi

Ang Wio Terminal ay maaari nang kumonekta sa WiFi.

### Gawain - kumonekta sa WiFi

Ikonekta ang Wio Terminal sa WiFi.

1. Gumawa ng bagong file sa `src` folder na tinatawag na `config.h`. Maaari mo itong gawin sa pamamagitan ng pagpili sa `src` folder, o sa `main.cpp` file sa loob, at pagpili sa **New file** button mula sa explorer. Ang button na ito ay lumalabas lamang kapag ang iyong cursor ay nasa explorer.

    ![Ang new file button](../../../../../translated_images/vscode-new-file-button.182702340fe6723c.tl.png)

1. Idagdag ang sumusunod na code sa file na ito upang magtakda ng constants para sa iyong WiFi credentials:

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

    Ina-import nito ang header files para sa mga libraries na idinagdag mo kanina, pati na rin ang config header file. Ang mga header files na ito ay kinakailangan upang sabihin sa PlatformIO na isama ang code mula sa libraries. Kung hindi mo tahasang isasama ang mga header files na ito, ang ilang code ay hindi mai-compile at makakakuha ka ng compiler errors.

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

    Ang code na ito ay nag-loop habang ang device ay hindi nakakonekta sa WiFi, at sinusubukang kumonekta gamit ang SSID at password mula sa config header file.

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

### Gawain - kumonekta sa MQTT

Ikonekta sa MQTT broker.

1. Idagdag ang sumusunod na code sa ibaba ng `config.h` file upang tukuyin ang connection details para sa MQTT broker:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Palitan ang `<ID>` ng isang unique ID na gagamitin bilang pangalan ng device client na ito, at sa kalaunan para sa mga topics na ipo-publish at susubscribe ng device na ito. Ang *test.mosquitto.org* broker ay pampubliko at ginagamit ng maraming tao, kabilang ang ibang mga estudyante na gumagawa ng assignment na ito. Ang pagkakaroon ng unique MQTT client name at topic names ay nagsisiguro na ang iyong code ay hindi magka-clash sa code ng iba. Kakailanganin mo rin ang ID na ito kapag gumagawa ka ng server code sa kalaunan sa assignment na ito.

    > 💁 Maaari kang gumamit ng website tulad ng [GUIDGen](https://www.guidgen.com) upang makabuo ng unique ID.

    Ang `BROKER` ay ang URL ng MQTT broker.

    Ang `CLIENT_NAME` ay isang unique name para sa MQTT client na ito sa broker.

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

    Ang function na ito ay sumusubok sa connection sa MQTT broker at muling kumokonekta kung hindi ito nakakonekta. Nag-loop ito habang hindi nakakonekta at sinusubukang kumonekta gamit ang unique client name na tinukoy sa config header file.

    Kung nabigo ang connection, magre-retry ito pagkatapos ng 5 segundo.

1. Idagdag ang sumusunod na code sa ibaba ng `reconnectMQTTClient` function:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Ang code na ito ay nagse-set ng MQTT broker para sa client, pati na rin ang pagse-set ng callback kapag may natanggap na mensahe. Pagkatapos ay sinusubukan nitong kumonekta sa broker.

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

    Ang code na ito ay nagsisimula sa pamamagitan ng muling pagkonekta sa MQTT broker. Ang mga koneksyon na ito ay madaling ma-disconnect, kaya't mahalagang regular na suriin at muling kumonekta kung kinakailangan. Pagkatapos ay tinatawag nito ang `loop` method sa MQTT client upang iproseso ang anumang mga mensahe na dumarating sa topic na sinubscribe. Ang app na ito ay single-threaded, kaya't ang mga mensahe ay hindi maaaring matanggap sa background thread, kaya't kailangang maglaan ng oras sa main thread upang iproseso ang anumang mga mensahe na naghihintay sa network connection.

    Sa wakas, ang delay na 2 segundo ay nagsisiguro na ang light levels ay hindi ipinapadala nang madalas at binabawasan ang power consumption ng device.

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
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.