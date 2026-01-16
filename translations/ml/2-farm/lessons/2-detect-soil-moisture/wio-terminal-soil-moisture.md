<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2026-01-07T05:02:54+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "ml"
}
-->
# മണ്ണിലെ ഈർപ്പം അളക്കുക - Wio ടെർമിനൽ

പാഠത്തിന്റെ ഈ ഭാഗത്തിൽ, നിങ്ങൾ നിങ്ങളുടെ Wio ടെർമിനലിൽ ഒരു capacitive മണ്ണ് ഈർപ്പം സെൻസർ ചേർക്കും, അതിൽ നിന്ന് മൂല്യം വായിക്കും.

## ഹാർഡ്‌വെയർ

Wio ടെർമിനലിന് ഒരു capacitive മണ്ണ് ഈർപ്പം സെൻസർ ആവശ്യമുണ്ട്.

നിങ്ങൾ ഉപയോഗിക്കാൻ പോകുന്നത് ഒരു [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html) ആണ്, ഇത് മണ്ണിന്റെ ക്രോപകവൽത്തനം കണ്ടെത്തി മണ്ണിന്റെ ഈർപ്പം അളക്കുന്നു, മണ്ണിന്റെ ഈർപ്പം മാറുമ്പോൾ ഇത് മാറ്റം വരുത്തുന്ന സ്വഭാവമാണ്. മണ്ണിലെ ഈർപ്പം വർദ്ധിക്കുമ്പോൾ, വോൾട്ടേജ് കുറയുന്നു.

ഇത് ഒരു അനലോഗ് സെൻസർ ആണ്, അതുകൊണ്ട് Wio ടെർമിനലിലെ അനലോഗ് പിനുകളിൽ ബന്ധിപ്പിക്കുന്നു, ബോർഡിലുള്ള ADC ഉപയോഗിച്ച് 0-1,023 ഇടയ്ക്ക് മൂല്യം സൃഷ്ടിക്കുന്നു.

### മണ്ണ് ഈർപ്പം സെൻസർ ബന്ധിപ്പിക്കുക

Grove മണ്ണ് ഈർപ്പം സെൻസർ Wio ടെർമിനലിന്റെ കൺഫിഗർ ചെയ്യാവുന്ന അനലോഗ്/ഡിജിറ്റൽ പോർട്ടിലേക്ക് ബന്ധിപ്പിക്കാം.

#### നിർദ്ദേശം - മണ്ണ് ഈർപ്പം സെൻസർ ബന്ധിപ്പിക്കുക

മണ്ണ് ഈർപ്പം സെൻസർ ബന്ധിപ്പിക്കുക.

![A grove soil moisture sensor](../../../../../translated_images/ml/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.png)

1. Grove കേബിളിന്റെ ഒരു ആخيൾ മണ്ണ് ഈർപ്പം സെൻസറിലെ സോക്കറ്റിലേക്ക് സെർത്ത് കൊള്ളുക. ഇത് ഒരു ദിശയിൽ മാത്രമേ പോയിപ്പോകൂ.

1. Wio ടെർമിനൽ നിങ്ങളുടെ കമ്പ്യൂട്ടറിലോ മറ്റേതെങ്കിലും പവർ സപ്ലൈയിലോ നിന്ന് വേർപെടുത്തിയിരിക്കുമ്പോൾ, Grove കേബിളിന്റെ മറുപുറം Wio ടെർമിനലിന്റെ സ്ക്രീനിനെ കാണുമ്പോൾ വലത് വശത്തുള്ള Grove സോക്കറ്റിലേക്ക് ബന്ധിപ്പിക്കുക. ഇത് പവർ ബട്ടണിൽനിന്ന് ഏറ്റവും ദൂരത്തുള്ള സോക്കറ്റാണ്.

![The grove soil moisture sensor connected to the right hand socket](../../../../../translated_images/ml/wio-soil-moisture-sensor.46919b61c3f6cb74.png)

1. മണ്ണിൽ സെൻസർ ചേർക്കുക. അതിനൊരു 'ഉയർന്ന സ്ഥാനം രേഖ' ഉണ്ട് - സെൻസറിനാകെയുള്ള വെളുപ്പുള്ള ഒരു രേഖ. ഈ രേഖയ്ക്ക് മുകളിൽ അല്ലാതെ രേഖ വരെ മാത്രം സെൻസർ ചേർക്കുക.

![The grove soil moisture sensor in soil](../../../../../translated_images/ml/soil-moisture-sensor-in-soil.bfad91002bda5e96.png)

1. ഇപ്പോൾ Wio ടെർമിനൽ നിങ്ങളുടെ കമ്പ്യൂട്ടറിലേക്ക് ബന്ധിപ്പിക്കാം.

## മണ്ണ് ഈർപ്പം സെൻസർ പ്രോഗ്രാം ചെയ്യുക

---

Wio ടെർമിനൽ ഇപ്പോൾ ബന്ധിപ്പിച്ചിരിക്കുന്ന മണ്ണ് ഈർപ്പം സെൻസർ ഉപയോഗിക്കുന്നതിന് പ്രോഗ്രാം ചെയ്യാവുന്നതാണ്.

### നിർദ്ദേശം - മണ്ണ് ഈർപ്പം സെൻസർ പ്രോഗ്രാം ചെയ്യുക

ഡിവൈസ് പ്രോഗ്രാം ചെയ്യുക.

1. PlatformIO ഉപയോഗിച്ച് പുതിയ Wio Terminal പ്രോജക്റ്റ് സൃഷ്‌ടിക്കുക. ഈ പ്രോജക്റ്റിനെ `soil-moisture-sensor` എന്നാണ് പേരിട്ടുകൊള്ളുക. `setup` ഫംഗ്ഷനിൽ സീരിയൽ പോർട്ട് കോൺഫിഗർ ചെയ്യുന്നതിനുള്ള കോഡ് ചേർക്കുക.

    > ⚠️ ആവശ്യമെങ്കിൽ [project 1, lesson 1ൽ PlatformIO പ്രോജക്റ്റ് സൃഷ്ടിക്കുന്നതിനുള്ള നിർദ്ദേശങ്ങൾക്കു](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project) مراجعه ചെയ്യാവുന്നതാണ്.

1. ഈ സെൻസറിന് ലൈബ്രറി ഇല്ല, പക്ഷേ നിങ്ങൾ Arduino ന്റെ അകത്ത് അടങ്ങിയ [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) ഫംഗ്ഷൻ ഉപയോഗിച്ച് അനലോഗ് പിനിൽ നിന്നും വായിക്കാം. ആദ്യം അനലോഗ് പിനിനെ ഇൻപുട്ടായി കൺഫിഗർ ചെയ്ത് മൂല്യങ്ങൾ വായിക്കാൻ സഹിയും ആക്കുക, ഇതിനായി `setup` ഫംഗ്ഷനിൽ താഴെ കാണിക്കുന്നതാണ് ചേർക്കുക.

    ```cpp
    pinMode(A0, INPUT);
    ```

    ഇത് `A0` പിനിനെ, അനലോഗ്/ഡിജിറ്റൽ സംയുക്ത പിനിനെ, വോൾട്ടേജ് വായിക്കാവുന്ന ഇൻപുട്ട് പിനായി സജ്ജമാക്കുന്നു.

1. ഈ പിനിൽ നിന്നു വോൾട്ടേജ് വായിക്കാൻ `loop` ഫംഗ്ഷനിൽ താഴെ കാണുന്ന കോഡ് ചേർക്കുക:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. താഴെയുള്ള കോഡിനു താഴെ സീരിയൽ പോർട്ടിലേക്ക് മൂല്യം പ്രിന്റ് ചെയ്യാൻ താഴെക്കാണുന്ന കോഡ് ചേർക്കുക:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. അവസാനം 10 സെക്കൻഡ് ഡിലേ ചേർക്കുക:

    ```cpp
    delay(10000);
    ```

1. Wio ടെർമിനലിലേക്ക് കോഡ് ബിൽഡ് ചെയ്ത് അപ്‌ലോഡ് ചെയ്യുക.

    > ⚠️ ആവശ്യമെങ്കിൽ [project 1, lesson 1ൽ PlatformIO പ്രോജക്റ്റ് സൃഷ്ടിക്കുന്നതിനുള്ള നിർദ്ദേശങ്ങൾക്കു](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app) مراجعه ചെയ്യാവുന്നതാണ്.

1. അപ്‌ലോഡ് കഴിഞ്ഞാൽ, സീരിയൽ മോണിറ്റർ ഉപയോഗിച്ച് മണ്ണ് ഈർപ്പം നിരീക്ഷിക്കാനാകും. മണ്ണിലേക്ക് കുറുകു വെള്ളം ചേർക്കുക, അല്ലെങ്കിൽ സെൻസർ മണ്ണിൽ നിന്നു നീക്കം ചെയ്യുക, പിന്നെ മൂല്യമാറ്റം കാണുക.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    മുകളിലുള്ള ഉദാഹരണ ഫലത്തിൽ, വെള്ളം ചേർക്കുമ്പോൾ വോൾട്ടേജ് കുറഞ്ഞത് കാണുന്നുണ്ട്.

> 💁 നിങ്ങൾക്ക് ഈ കോഡ് [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) ഫോളഡറിൽ കണ്ടെത്താം.

😀 നിങ്ങളുടെ മണ്ണ് ഈർപ്പം സെൻസർ പ്രോഗ്രാം വിജയകരമായി പൂര്‍ത്തിയായി!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ഡിസ്ക്ലെയിമർ**:  
ഈ രേഖ AI പരിഭാഷ സേവനം [Co-op Translator](https://github.com/Azure/co-op-translator) ഉപയോഗിച്ച് പരിഭാഷ ചെയ്തത് ആണ്. നാം ശരിയായി വിവർത്തനം ചെയ്യാൻ ശ്രമിച്ചെങ്കിലും, ഓട്ടോമേറ്റഡ് പരിഭാഷകളിൽ പിശകുകൾ അല്ലെങ്കിൽ അബദ്ധങ്ങൾ ഉണ്ടായിരിക്കാവുന്ന സാധ്യതയുണ്ട്. പ്രമാണത്തിന്റെ യഥാർത്ഥ ഭാഷയിൽ ഉള്ള പ്രമാണം അധികാരമുള്ള സ്രോതസ്സ് ആയി കണക്കാക്കണം. ഇതിനോടകം ഗൗരവമുള്ള വിവരങ്ങൾക്കായി, പ്രൊഫഷണൽ മനുഷ്യ പരിഭാഷ ശ്രേഷ്ഠമാണ്. ഈ പരിഭാഷ ഉപയോഗിക്കുന്നതിനാൽ ഉണ്ടാകുന്ന ഏതെങ്കിലും തെറ്റിദ്ധാരണകൾക്കോ, വ്യാഖ്യാന പിശകുകൾക്കോ ഞങ്ങൾ ഉത്തരവാദികളല്ല.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->