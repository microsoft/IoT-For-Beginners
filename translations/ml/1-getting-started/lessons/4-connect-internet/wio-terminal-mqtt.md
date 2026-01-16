<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2026-01-07T02:18:26+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "ml"
}
-->
# ഇന്റർനെറ്റിലൂടെ നിങ്ങളുടെ നൈറ്റ് ലൈറ്റ് നിയന്ത്രിക്കുക - Wio ടെർമിനൽ

IoT ഡിവൈസിന് *test.mosquitto.org* ഉപയോഗിച്ച് MQTT വഴി ലൈറ്റ് സെൻസർ വായനകളിൽ നിന്നുള്ള ടെലിമെട്രി മൂല്യങ്ങൾ അയയ്ക്കാനും LED നിയന്ത്രിക്കാൻ കമാൻഡുകൾ സ്വീകരിക്കാനും കോഡുചെയ്യാൻ ആവശ്യമാണ്.

പാഠത്തിന്റെ ഈ ഭാഗത്തിൽ, നിങ്ങൾ നിങ്ങളുടെ Wio ടെർമിനൽ MQTT ബ്രോക്കറുമായി കണക്ട് ചെയ്യും.

## WiFi, MQTT Arduino ലൈബ്രറികൾ ഇൻസ്റ്റാൾ ചെയ്യുക

MQTT ബ്രോക്കറുമായി കമ്യൂണിക്കേറ്റ് ചെയ്യാൻ, Wio ടെർമിനലിലെ WiFi ചിപ്പിനെ ഉപയോഗിച്ച് MQTT കമ്മ്യൂണിക്കേഷൻ നടത്താൻ Arduino ലൈബ്രറികൾ ഇൻസ്റ്റാൾ ചെയ്യേണ്ടതുണ്ട്. Arduino ഡിവൈസുകൾക്കുള്ള വികസനത്തിൽ, നിങ്ങൾക്ക് വിപുലമായ പൊതു സോഴ്സ് കോഡ് അടങ്ങിയ ലൈബ്രറികൾ ഉപയോഗിക്കാം, അവ വൻ തോതിലുള്ള കഴിവുകൾ നടപ്പിലാക്കുന്നു. Seeed Wio ടെർമിനലിന് WiFi വഴി കമ്യൂണിക്കേറ്റ് ചെയ്യാൻ ലൈബ്രറികൾ പ്രസിദ്ധീകരിച്ചു. മറ്റ് ഡവലപ്പർമാർ MQTT ബ്രോക്കറുകളുമായി കമ്യൂണിക്കേറ്റ് ചെയ്യാനുള്ള ലൈബ്രറികൾ പ്രസിദ്ധീകരിച്ചിട്ടുണ്ട്, നിങ്ങൾ നിങ്ങളുടെ ഡിവൈസുമായി അവ ഉപയോഗിക്കും.

ഈ ലൈബ്രറികൾ സോഴ്‌സ് കോഡായി നൽകുന്നു, അവ PlatformIO-യിൽ സ്വയമേവ ഇമ്പോർട്ട് ചെയ്ത് നിങ്ങളുടെ ഡിവൈസിന് കമ്പൈൽ ചെയ്യാവുന്നതാണ്. ഇത്തരം Arduino ലൈബ്രറികൾ Arduino ഫ്രെയിംവർക്ക് പിന്തുണയുള്ള ഏതൊരു ഡിവൈസിലും പ്രവർത്തിക്കും, ലائب്രറിയ്ക്ക് വേണ്ട പ്രത്യേക ഹാർഡ്‌വെയർ ഡിവൈസിന് ഉണ്ടായിരിക്കണം എന്നുവച്ചു. ചില ലൈബ്രറികൾ, Seeed WiFi ലൈബ്രറികൾ പോലുള്ളവ, പ്രത്യേക ഹാർഡ്‌വെയറിനാണ്.

ലൈബ്രറികൾ ഗ്ലോബൽ ആയി ഇൻസ്റ്റാൾ ചെയ്യാനോ தேவയുണ്ടെങ്കിൽ കമ്പൈൽ ചെയ്യാനോ പകരം ഒരു പ്രത്യേക പ്രോജക്ടിലേക്ക് ഇൻസ്റ്റാൾ ചെയ്യാനോ കഴിയും. ഈ അസൈന്മെന്റിനായി ലൈബ്രറികൾ പ്രോജക്ടിലേക്ക് ഇൻസ്റ്റാൾ ചെയ്യും.

✅ [PlatformIO ലൈബ്രറി മാനേജ്മെന്റ് ഡോക്യുമെന്റേഷൻ](https://docs.platformio.org/en/latest/librarymanager/index.html) ൽ നിങ്ങൾക്ക് ലൈബ്രറികൾ കണ്ടെത്താനും ഇൻസ്റ്റാൾ ചെയ്യാനും 관한 കൂടുതൽ അറിയാൻ കഴിയും.

### ടാസ്ക് - WiFi, MQTT Arduino ലൈബ്രറികൾ ഇൻസ്റ്റാൾ ചെയ്യുക

Arduino ലൈബ്രറികൾ ഇൻസ്റ്റാൾ ചെയ്യുക.

1. VS കോഡിൽ നൈറ്റ് ലൈറ്റ് പ്രോജക്ട് തുറക്കുക.

1. `platformio.ini` ഫയലിന്റെ അവസാനം താഴെ കാണിച്ചിരിക്കുന്നത് ചേർക്കുക:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```
  
    ഇത് Seeed WiFi ലൈബ്രറികൾ ഇംപോർട്ട് ചെയ്യുന്നു. `@ <number>` സിന്ടാക്സ് ലൈബ്രറിയുടെ ഒരു പ്രത്യേക പതിപ്പിനെയാണ് സൂചിപ്പിക്കുന്നത്.

    > 💁 `@ <number>` നീക്കം ചെയ്ത് ലൈബ്രറികളുടെ പുതിയ പതിപ്പുകൾ എല്ലായ്പ്പോഴും ഉപയോഗിക്കാം, പക്ഷേ താഴെ കൊടുത്ത കോഡിൽ പുതിയ പതിപ്പുകൾ പ്രവർത്തിക്കുമെന്ന ഉറപ്പ് ഇല്ല. കൊടുത്തിരിക്കുന്ന പതിപ്പിൽ കോഡ് ടെസ്റ്റ് ചെയ്തിട്ടുണ്ട്.

    ലൈബ്രറികൾ ചേർക്കാൻ ഇതുപുറം ചെയ്യേണ്ടതുണ്ട്. അടുത്ത തവണ PlatformIO പ്രോജക്ട് നിർമ്മിക്കുമ്പോൾ ഈ ലൈബ്രറികളുടെ സോഴ്‌സ് കോഡ് ഡൗൺലോഡ് ചെയ്ത് പ്രോജക്ടിലേയ്ക്ക് കമ്പൈൽ ചെയ്യും.

1. `lib_deps` സექ്ഷനിലേക്ക് താഴെ ചേർക്കുക:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```
  
    ഇത് [PubSubClient](https://github.com/knolleary/pubsubclient), Arduino MQTT ക്ലയന്റ് ഇംപോർട്ട് ചെയ്യുന്നു.

## WiFi-യിൽ കണക്ട് ചെയ്യുക

ഇപ്പോൾ Wio ടെർമിനൽ WiFi-യിൽ കണക്ട് ചെയ്യാം.

### ടാസ്ക് - WiFi-ിൽ കണക്ട് ചെയ്യുക

Wio ടെർമിനൽ WiFi-യിൽ കണക്ട് ചെയ്യുക.

1. `src` ഫോൾഡറിൽ `config.h` എന്ന പുതിയ ഫയൽ സൃഷ്ടിക്കുക. ഇത് ചെയ്യാൻ, `src` ഫോൾഡർ അല്ലെങ്കിൽ അതിനുള്ളിലെ `main.cpp` ഫയൽ തിരഞ്ഞെടുക്കുകയും എക്സ്പ്ലോററിലെ **New file** ബട്ടൺ ക്ലിക്ക് ചെയ്യുകയും ചെയ്യാം. ഇവ നിങ്ങളുടെ കർസർ എക്സ്പ്ലോററിന്മേൽ പാർക്കുചെയ്യുമ്പോഴാണ് കാണുക.

    ![The new file button](../../../../../translated_images/ml/vscode-new-file-button.182702340fe6723c.png)

1. ഈ ഫയലിലേക്ക് താഴെ കൃത്യമായ കോഡ് ചേർക്കുക, WiFi ക്രെഡൻഷ്യൽ നിർവചിക്കാൻ:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // വൈഫൈ സാക്ഷ്യപത്രങ്ങൾ
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```
  
    `<SSID>` എന്നത് നിങ്ങളുടെ WiFi SSID ആയി മാറ്റുക. `<PASSWORD>` എന്നത് നിങ്ങളുടെ WiFi പാസ്വേഡ് ആയി മാറ്റുക.

1. `main.cpp` ഫയൽ തുറക്കുക

1. ഫയലിന്റെ മുകളിലായി താഴെ കാണിച്ചിരിക്കുന്ന `#include` ഡയറക്ടീവുകൾ ചേർക്കുക:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```
  
    ഇതുവഴി നിങ്ങൾ മുമ്പ് ചേർത്ത ലൈബ്രറികൾക്കും, config ഹെഡർ ഫയലിനും വേണ്ട ഹെഡർ ഫയലുകൾ ഉൾക്കൊള്ളിച്ചിരിക്കുന്നു. PlatformIO ഈ ലൈബ്രറികളുടെ കോഡ് വന്നതിന് ഇവ ആവശ്യമാണ്. ഇവ നൽകിയില്ലെങ്കിൽ ചില കോഡ് കമ്പൈൽ ചെയ്യില്ല, എന്നിട്ട് കോമ്പൈലർ പിഴവുകൾ ഉണ്ടാകും.

1. `setup` ഫങ്ഷനിന്റെ മുകൾഭാഗത്ത് താഴെ കാണുന്നതുപോലെ കോഡ് ചേർക്കുക:

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
  
    WiFi-hez കണക്ട് ആകാതെ dispositivo ഒന്നും ചെയ്യാതെ കാത്തിരിക്കുന്നു, config ഹെഡർ ഫയലിൽ എടുത്ത SSID, പാസ്വേഡ് ഉപയോഗിച്ച് കണക്ട് ചെയ്യാൻ ശ്രമിക്കുന്നു.

1. `setup` ഫങ്ഷനിന്റെ അവസാനത്ത്, പിനുകൾ ക്രമീകരിച്ചതിന് ശേഷം ഈ ഫങ്ഷൻ വിളിക്കുക.

    ```cpp
    connectWiFi();
    ```
  
1. ഈ കോഡ് നിങ്ങളുടെ ഡിവൈസിലേക്ക് അപ്‌ലോഡ് ചെയ്ത് WiFi കണക്ഷൻ പ്രവർത്തിക്കുന്നതായി പരിശോധിക്കുക. സെറിയൽ മോണിറ്ററിൽ ഇത് കാണാവുന്നതാണ്.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```
  
## MQTT-യോട് കണക്ട് ചെയ്യുക

Wio ടെർമിനൽ WiFi-യിൽ കണക്ട് ചെയ്ത ശേഷം, MQTT ബ്രോക്കറുമായി കണക്ട് ചെയ്യാം.

### ടാസ്ക് - MQTT-യിൽ കണക്ട് ചെയ്യുക

MQTT ബ്രോക്കറുമായി കണക്ട് ചെയ്യുക.

1. `config.h` ഫയലിന്റെ അവസാനം MQTT ബ്രോക്കറിന്റെ കണക്ഷൻ വിശദാംശങ്ങൾ നിർവചിക്കാൻ താഴെ ചേർക്കുക:

    ```cpp
    // MQTT ക്രമീകരണങ്ങൾ
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```
  
    `<ID>` എന്നത് ഈ ഡിവൈസ് ക്ലയന്റിന്റെ യुनिकായ ID ആയി മാറ്റുക, പിന്നീട് ഈ ഡിവൈസ് പ്രസിദ്ധീകരിക്കുന്നയും സബ്സ്കൈബ് ചെയ്യുന്നടവും വിഷയങ്ങൾക്കും ഇത് ഉപയോഗിക്കും. *test.mosquitto.org* ബ്രോക്കർ പൊതു ആണ്, പലരും, ഈ അസൈന്മെന്റ് ചെയ്യുകയുള്ള മറ്റ് വിദ്യാർത്ഥികൾ ഉൾപ്പെടെ, ഇത് ഉപയോഗിക്കുന്നു. MQTT ക്ലയംറിന്റെയും വിഷയംകളും യുണിക് ആയിരിക്കണം കൂടാതെ മറ്റുള്ളവരുമായി കോഡ് കൂട്ടിക്കൊപിക്കുന്നതിനുള്ള അപകടം ഒഴിവാക്കാൻ. ഈ അസൈന്മെന്റിൽ സർവർ കോഡ് ഒരുക്കുമ്പോൾ ഈ ID ആവശ്യമാണ്.

    > 💁 [GUIDGen](https://www.guidgen.com) പോലുള്ള വെബ്സൈറ്റ് ഉപയോഗിച്ച് യുണിക് ID സൃഷ്ടിക്കാവുന്നതാണ്.

    `BROKER` MQTT ബ്രോക്കറിന്റെ URL ആണ്.

    `CLIENT_NAME` ഈ MQTT ക്ലയന്റിനുള്ള യുണിക് പേരാണ് ബ്രോക്കറിൽ.

1. `main.cpp` ഫയൽ തുറന്ന്, `connectWiFi` ഫങ്ഷനിന്റെ താഴെ, `setup` ഫങ്ഷനിനു മുകളിൽ താഴെ ക്യൂട്ട് ചെയ്യുക:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```
  
    Wio ടെർമിനലിന്റെ WiFi ലൈബ്രറുകൾ ഉപയോഗിച്ച് WiFi ക്ലയന്റ് സൃഷ്ടിക്കുന്നു, അതുപയോഗിച്ച് MQTT ക്ലയന്റ് സൃഷ്ടിക്കുന്നു.

1. ഈ കോഡിനു താഴെ ചേർക്കുക:

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
  
    MQTT ബ്രോക്കറുമായി കണക്ഷൻ പരിശോധിക്കുകയും ബന്ധമില്ലെങ്കിൽ പുനഃസൃഷ്ടിക്കുകയും ഈ ഫങ്ഷൻ ചെയ്യുന്നുണ്ട്. കണക്ട് ആകാത്തതിനാൽ തുടർച്ചയായി ലൂപ്പ് ചെയ്ത് config ഹെഡറിൽ നിർവചിച്ച യുണിക് ക്ലയന്റ് നാമം ഉപയോഗിച്ച് കണക്ഷൻ ശ്രമിക്കുന്നു.

    കണക്ഷൻ പരാജയപ്പെടുന്നപക്ഷം 5 സെക്കന്റിനു ശേഷം വീണ്ടും ശ്രമിക്കുന്നു.

1. `reconnectMQTTClient` ഫങ്ഷനിന് താഴെ താഴെ കാണുന്ന കോഡ് ചേർക്കുക:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```
  
    MQTT ബ്രോക്കറിനെ സെറ്റ് ചെയ്തു, സന്ദേശം എത്തിയപ്പോൾ ഉപയോഗിക്കുന്ന കോൾബാക്ക് ക്രമീകരിക്കുകയും, പിന്നീട് ബ്രോക്കറുമായി കണക്ട് ചെയ്യാൻ ശ്രമിക്കുന്നു.

1. WiFi കണക്ട് കഴിഞ്ഞു, `setup` ഫങ്ഷനിൽ `createMQTTClient` ഫങ്ഷൻ വിളിക്കുക.

1. മുഴുവൻ `loop` ഫങ്ഷൻ താഴെ കാണുന്ന കോഡിൽ മാറ്റുക:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```
  
    MQTT ബ്രോക്കറിലേക്ക് പുനഃകണക്ട് ചെയ്യുന്നത് തുടക്കത്തിലാണ്. ഈ കണക്ഷനുകൾ എളുപ്പം തകരാറിലാകാൻ സാധ്യതയുണ്ട്, അതുകൊണ്ട് സ്ഥിരം പരിശോധിച്ച് പുനഃകണക്ട് ചെയ്യുന്നത് ഉത്തമം. തുടർന്ന് MQTT ക്ലയന്റിന്റെ `loop` മെഥഡ് വിളിച്ച് സബ്സ്ക്രൈബ് ചെയ്ത വിഷയങ്ങളിൽ വരുന്ന സന്ദേശങ്ങൾ പ്രോസസ് ചെയ്യുന്നു. ഈ ആപ്പ് സിംഗിള് ത്രെഡാണ്, അതിനാൽ പശ്ചാത്തല ത്രെഡിൽ സന്ദേശങ്ങൾ സ്വീകരിക്കാൻ കഴിയില്ല, അതിനാൽ പ്രധാന ത്രെഡിൽ സമയം മാറ്റി സന്ദേശങ്ങൾ പ്രോസസ് ചെയ്യേണ്ടതുണ്ട്.

    അവസാനം 2 സെക്കന്റ് വൈകിപ്പിക്കുന്നത് ലൈറ്റ് ഡാറ്റ കൂടുതൽ പ്രയാസം കൂടാതെ അയക്കാതിരിക്കാനും ഡിവൈസിന്റെ വൈദ്യുതി ചെലവ് കുറക്കാനും സഹായിക്കും.

1. ഈ കോഡ് നിങ്ങളുടെ Wio ടെർമിനലിലേക്ക് അപ്‌ലോഡ് ചെയ്ത്, സെറിയൽ മോണിറ്റർ ഉപയോഗിച്ച് WiFi, MQTT-യിലേക്ക് കണക്ട് ആകുന്നത് കാണുക.

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
  
> 💁 ഈ കോഡ് [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) ഫോൾഡറിൽ കണ്ടെത്താം.

😀 നിങ്ങൾ വിജയകരമായി നിങ്ങളുടെ ഡിവൈസ് MQTT ബ്രോക്കറുമായി ബന്ധിപ്പിച്ചു.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**അസാധാറണം**:
ഈ രേഖ എ.ഐ. തർജ്ജമാ സേവനം [Co-op Translator](https://github.com/Azure/co-op-translator) ഉപയോഗിച്ച് അനുവദിച്ചിരിക്കുന്നതാണ്. കൃത്യതയ്ക്ക് ഞങ്ങൾ ശ്രമിക്കുന്നുവെങ്കിലും, യാന്ത്രിക തർജ്ജമകളിൽ പിഴവുകൾ അല്ലെങ്കിൽ അച്ചടക്ക തെറ്റുകൾ ഉണ്ടായിരിക്കാമെന്നു ദയവായി ശ്രദ്ധിക്കുക. സ്വതന്ത്ര ഭാഷയിലുള്ള അഭിഭാഷക രേഖയുടെ അവതാരക ഉറവിടമായി പരിഗണിക്കണമെന്ന് നിർദേശിക്കപ്പെടുന്നു. നിർണായക വിവരങ്ങൾക്കായി, പ്രൊфഷണൽ മനുഷ്യ അനുവാദം ശുപാർശ ചെയ്യപ്പെടുന്നു. ഈ തർജ്ജമ ഉപയോഗിക്കുന്നതിനാൽ സംഭവിക്കുന്ന യാതൊരു തെറ്റായ ധാരണകൾക്കും വ്യാഖ്യാനങ്ങൾക്കും ഞങ്ങൾ ഉത്തരവാദികളല്ല.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->