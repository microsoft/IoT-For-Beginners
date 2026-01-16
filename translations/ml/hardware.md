<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2026-01-07T01:23:33+00:00",
  "source_file": "hardware.md",
  "language_code": "ml"
}
-->
# ഹാർഡ്‌വെയർ

IoTയിലെ **T** യഥാർത്ഥത്തിൽ **Things** (വസ്തുക്കൾ) ആണ്, അതായത് നമ്മുടെ ചുറ്റുപാടുമായി ഇടപെടുന്ന ഉപകരണങ്ങൾ. ഓരോ പ്രോജക്റ്റും വിദ്യാർത്ഥികൾക്കും ഹോബിസ്റ്റുകൾക്കും ഉപയോഗിക്കാൻ ലഭ്യമായ യഥാർത്ഥ ലോക ഹാർഡ്‌വെയറിനെ ആസ്പദമാക്കി രൂപകൽപ്പന ചെയ്തിരിക്കുന്നു. വ്യക്തിഗത മുൻഗണന, പ്രോഗ്രാമിംഗ് ഭാഷാ അറിവ്, പഠന ലക്ഷ്യങ്ങൾ, ലഭ്യത എന്നിവയായുള്ള വ്യത്യാസത്തെ ആശ്രയിച്ച് ഉപയോഗിക്കാനുള്ള രണ്ട് ഐഒടി ഹാർഡ്‌വെയർ ഓപ്ഷനുകൾ لدينا. ഹാർഡ്‌വെയറിനെ ആക്രമിക്കാൻ സാധിക്കാത്തവർക്കും വാങ്ങുന്നതിനു മുമ്പ് കൂടുതൽ അറിയാൻ ആഗ്രഹിക്കുന്നവർക്കും 'വിർച്വൽ ഹാർഡ്‌വെയർ' പതിപ്പ് ഞങ്ങൾ നൽകിയിട്ടുണ്ട്.

> 💁 അസൈൻമെന്റുകൾ പൂർത്തിയാക്കാൻ നിങ്ങൾക്ക് ഏതെങ്കിലും ഐഒടി ഹാർഡ്‌വെയർ വാങ്ങേണ്ടതില്ല. നിങ്ങൾക്കു് എല്ലാം വിർച്ച്വൽ ഐഒടി ഹാർഡ്‌വെയർ ഉപയോഗിച്ചും ചെയ്യാം.

ഭൗതിക ഹാർഡ്‌വെയറുകളുടെ തിരഞ്ഞെടുപ്പുകൾ Arduino അല്ലെങ്കിൽ Raspberry Pi ആണ്. ഓരോ പ്ലാറ്റ്ഫോമിനും അതിന്റെ ഗുണവും ദോഷവും ഉണ്ട്, ഇവ ആദ്യപാഠങ്ങളിൽ ഒരെണ്ണം ആക്കിയിട്ടുണ്ട്. നിങ്ങൾക്കു് ഇതിനകം ഹാർഡ്‌വെയർ പ്ലാറ്റ്ഫോം തീരുമാനിച്ചിട്ടില്ലെങ്കിൽ, നിങ്ങൾക്ക് [ആദ്യ പ്രോജക്റ്റിന്റെ രണ്ടാം പാഠം](./1-getting-started/lessons/2-deeper-dive/README.md) പിന്തുടർന്ന് ഏത് ഹാർഡ്‌വെയർ പ്ലാറ്റ്ഫോമായി നിങ്ങൾക്ക് ഏറ്റവും കൂടുതൽ താൽപ്പര്യമുണ്ടെന്ന് മനസ്സിലാക്കാം.

പാഠങ്ങളും അസൈൻമെന്റുകളും ലളിതമാക്കുന്നതിനായി പ്രത്യേക ഹാർഡ്‌വെയർ തിരഞ്ഞെടുക്കപ്പെട്ടതാണ്. മറ്റ് ഹാർഡ്‌വെയറുകൾ പ്രവർത്തിച്ചേക്കാമെങ്കിലും നിങ്ങളുടെ ഉപകരണത്തിൽ എല്ലാ അസൈൻമെന്റുകളും കൂട്ടിയിണക്കാതെ പ്രവർത്തിക്കുമെന്ന് ഉറപ്പില്ല. ഉദാഹരണത്തിന്, കൂടുതൽ Arduino ഉപകരണങ്ങൾക്ക് WiFi ഇല്ല, ക്ലൗഡുമായി കണക്റ്റ് ചെയ്യാൻ WiFi ആവശ്യമുള്ളതിനാൽ Wio terminal അതിനായി തിരഞ്ഞെടുക്കപ്പെട്ടു.

പിന്നീട്, നിങ്ങൾക്ക് സാങ്കേതികമല്ലാത്ത ചില വസ്തുക്കളും വേണം, ഉച്ചണ്ണം മണ്ണ് അല്ലെങ്കിൽ മൂടിവെച്ചിട്ടുള്ള തോട്ടം, പഴം അല്ലെങ്കിൽ പച്ചക്കറികൾ പോലുള്ളവ.

## കിറ്റുകൾ വാങ്ങുക

![The Seeed studios logo](../../translated_images/ml/seeed-logo.74732b6b482b6e8e.png)

Seeed Studios എല്ലാവരും എളുപ്പത്തിൽ വാങ്ങാനുള്ള കിറ്റുകളായി എല്ലാ ഹാർഡ്‌വെയറുകളും kindly ആയി ഒരുക്കിയിട്ടുണ്ട്:

### Arduino - Wio Terminal

**[Seeed-ഉം Microsoft-ഉം ചേർന്ന് തുടങ്ങുന്നവർക്കുള്ള IoT - Wio Terminal സ്റ്റാർട്ടർ കിറ്റ്](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![The Wio Terminal hardware kit](../../translated_images/ml/wio-hardware-kit.4c70c48b85e4283a.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[Seeed-ഉം Microsoft-ഉം ചേർന്ന് തുടങ്ങുന്നവർക്കുള്ള IoT - Raspberry Pi 4 സ്റ്റാർട്ടർ കിറ്റ്](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![The Raspberry Pi Terminal hardware kit](../../translated_images/ml/pi-hardware-kit.26dbadaedb7dd44c.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Arduino ഉപകരണത്തിനുള്ള എല്ലാ കോഡും C++ ൽ ആണ്. എല്ലാ അസൈൻമെന്റുകളും പൂർത്തിയാക്കാനായി നിങ്ങൾക്ക് താഴെ പറയുന്നവ വേണം:

### Arduino ഹാർഡ്‌വെയർ

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *ഓപ്ഷണൽ* - USB-C ക്യാബിൾ അല്ലെങ്കിൽ USB-A-ഇൽ നിന്ന് USB-C അഡാപ്റ്റർ. Wio Terminal-ന് USB-C പോർട്ട് ഉണ്ട് കൂടാതെ USB-C થી USB-A ക്യാബിൾയും നൽകുന്നു. നിങ്ങളുടെ പിസി അല്ലെങ്കിൽ മാക്ക് USB-C പോർട്ടുകൾ മാത്രം ഉള്ളതായി അനുഭവപ്പെടുകയാണെങ്കിൽ USB-C ക്യാബിൾ അല്ലെങ്കിൽ USB-A മുതൽ USB-C അഡാപ്റ്റർ വേണം.

### Arduino നുള്ള പ്രത്യേക സെൻസറുകളും ആക്ചുവേറ്ററുകളും

ഇവ Wio Terminal Arduino ഉപകരണത്തിന് മാത്രമാണ് പ്രസക്തം, Raspberry Pi ഉപയോഗിക്കുന്നവക്ക് പ്രസക്തമല്ല.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [ബ്രെഡ്ബോർഡ് ജമ്പർ വയറുകൾ](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* ഹെഡ്‌ഫോൺ അല്ലെങ്കിൽ 3.5mm ജാക്ക് ഉള്ള മറ്റേതു Speker-ഉം അല്ലെങ്കിൽ JST സ്പീക്കറുകൾ അതായത്:
  * [മോണോ എന്‌ക്ലോസഡ് സ്പീക്കർ - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD കാർഡ് 16GB അല്ലെങ്കിൽ അതിലധികം അല്ല, നിങ്ങളുടെ കമ്പ്യൂട്ടറിന്റെ ഉപയോഗത്തിനായി സിഎം പകർപ്പുള്ള കണക്ടർ. **ഗൌരവമേറിയ കുറിപ്പ്** - Wio Terminal 16GB വരെ മാത്രമേ പിന്തുണയ്ക്കുള്ളൂ, കൂടുതൽ ശേഷി എന്നിവയെ പിന്തുണയ്ക്കുന്നില്ല.

## Raspberry Pi

Raspberry Pi ഉപകരണത്തിനുള്ള എല്ലാ കോഡ് Python-ലാണ്. എല്ലാ അസൈൻമെന്റുകളും പൂർത്തിയാക്കാനായി നിങ്ങൾക്ക് താഴെ പറയുന്നവ വേണം:

### Raspberry Pi ഹാർഡ്‌വെയർ

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Pi 2B മുതൽ മുകളിലുള്ള പതിപ്പുകൾ ഈ പാഠങ്ങളിലും അസൈൻമെന്റുകളിലും ഉപയോഗിക്കാൻ കഴിയും. നിങ്ങൾ Pi-ൽ നേരിട്ട് VS Code ഓടിക്കാൻ പദ്ധതിയിടുകയാണെങ്കിൽ, Pi 4 2GB അല്ലെങ്കിൽ അതിലധികം RAM ഉള്ളതായിരിക്കണം. Pi-നെ ദൂരസ്ഥമായി ആക്സസ് ചെയ്യാൻ പോകുകയാണെങ്കിൽ Pi 2B മുകളിലുള്ള ഏത് Pi-യും മതിയാകും.
* microSD കാർഡ് (microSD കാർഡ് ഉള്ള Raspberry Pi കിറ്റുകൾ നിങ്ങൾക്ക് കിട്ടും), നിങ്ങളുടെ കമ്പ്യൂട്ടറിനൊത്ത് ഉപയോഗിക്കാൻ ഒരു കണക്ടർ.
* USB പവർ സപ്ലൈ (പവർ സപ്ലൈ അടങ്ങിയ Raspberry Pi 4 കിറ്റുകൾ നിങ്ങൾക്ക് ലഭിക്കും). Raspberry Pi 4 ഉപയോക്താക്കൾക്ക് USB-C പവർ സപ്ലൈ വേണം, പഴയ ഉപകരണങ്ങൾക്ക് micro-USB പവർ സപ്ലൈ ആവശ്യമുണ്ട്.

### Raspberry Pi-നുള്ള പ്രത്യേക സെൻസറുകളും ആക്ചുവേറ്ററുകളും

ഇവ Raspberry Pi ഉപയോഗിക്കാൻ സാങ്കേതികമായി മാത്രം പ്രസക്തമാണ്, Arduino ഉപകരണത്തിൽ പ്രയോഗിക്കാൻ അല്ല.

* [Grove Pi ബെസ് ഹാറ്റ്](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi ക്യാമറ മോഡ്യൂൾ](https://www.raspberrypi.org/products/camera-module-v2/)
* മൈക്രോഫോൺ‌വും സ്പീക്കറുമായി:

  താഴെ പറയുന്നവയിൽ ഒന്ന് (അധികം അല്ലെങ്കിൽ സമാനമായത്) ഉപയോഗിക്കുക:
  * ഏതെന്തെങ്കിലും USB മൈക്രോഫോൺ, ഏതെങ്കിലും USB സ്പീക്കർ, 3.5mm ജാക്ക് യുഡ് സ്പീക്കർ, അല്ലെങ്കിൽ HDMI ഓഡിയോ ഔട്ട്പുട്ട് ഉപയോഗിച്ച് Raspberry Pi മോണിറ്ററോ ടിവിയിലോ കണക്ടുചെയ്താൽ
  * ഒരുപക്ഷേ മൈക്രോഫോൺ ഉൾക്കൊള്ളുന്ന USB ഹെഡ്‌സെറ്റ്
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) കൂടാതെ
    * 3.5mm ജാക്ക് ഉള്ള ഹെഡ്‌ഫോൺ അല്ലെങ്കിൽ മറ്റേതെങ്കിലും സ്പീക്കർ, അല്ലെങ്കിൽ ഇത്തരമൊരു JST സ്പീക്കർ:
    * [മോണോ എന്‍ക്ലോസഡ് സ്പീക്കർ - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB സ്പീക്കർഫോൺ](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove ലൈറ്റ് സെൻസർ](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove ബട്ടൺ](https://www.seeedstudio.com/Grove-Button.html)

## സെൻസറുകളും ആക്ചുവേറ്ററുകളും

അതിർത്തിയായും Arduino ഉം Raspberry Pi ഉം പഠന മാർഗങ്ങളിലുമുള്ള സെൻസറുകളും ആക്ചുവേറ്ററുകളും കൂടുതലായി ഉപയോഗിക്കുന്നു:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove ഹ്യుమിഡിറ്റിയും താപനിലാ സെൻസറുമായിരിക്കുന്നു](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove ക്യാപസിറ്റീവ് മണ്ണ് ഈർപ്പം സെൻസർ](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove റീലേ](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove ടൈം ഓഫ് ഫ്ലൈറ്റ് ഡിസ്റ്റൻസ് സെൻസർ](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## ഓപ്ഷണൽ ഹാർഡ്‌വെയർ

ആട്ടോമാറ്റഡ് വാട്ടറിങ്ങിൽ റീലേ ഉപയോഗിക്കുന്നു. നിർബന്ധമല്ല, എന്നാൽ നിങ്ങൾക്ക് താഴെ കാണിക്കുന്ന ഹാർഡ്‌വെയർ ഉപയോഗിച്ച് USB പവർ ഉപയോഗിച്ച് പമ്പിൽ റೀಲേ കണക്റ്റ് ചെയ്യാം:

* [6V വാട്ടർ പമ്പ്](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB ടർമിനൽ](https://www.adafruit.com/product/3628)
* സിലിക്കൺ പൈപ്പുകൾ
* ചുവന്നതും കറുത്തതുമായ വയറുകൾ
* ചെറിയ ഫ്ലാറ്റ് ഹെഡ് സ്ക്രൂഡ്രൈവർ

## വിർച്വൽ ഹാർഡ്‌വെയർ

വിർച്വൽ ഹാർഡ്‌വെയർ വഴി സെൻസറുകളും ആക്ചുവേറ്ററുകളും പൈത്തൺ-ൽ നടപ്പിലാക്കിയ സിമുലേറ്ററുകൾ ആയി ലഭ്യമാണ്. നിങ്ങളുടെ ഹാർഡ്‌വെയർ ലഭ്യത അനുസരിച്ച്, നിങ്ങൾ ഇത് നിങ്ങളുടെ സാധാരണ വികസന ഉപകരണത്തിൽ (മാക്ക്, പിസി) ഓടിക്കാം, അല്ലെങ്കിൽ Raspberry Pi-യിൽ ഓടിച്ച് ഉളള ഹാർഡ്‌വെയറുകൾ മാത്രമേ ഉപയോഗിക്കൂ, എല്ലാവിധ വസ്തുക്കളും ഇല്ലാത്തവ സിമുലേറ്റ് ചെയ്യാം. ഉദാഹരണത്തിന്, Raspberry Pi ക്യാമറ നിങ്ങൾക്കുണ്ടെങ്കിലും Grove സെൻസറുകൾ ഇല്ലെങ്കിൽ, വാഹനസിമുലേറ്റർ കോഡ് Raspberry Pi-യിൽ ഓടിച്ച് Grove സെൻസറുകൾ സിമുലേറ്റ് ചെയ്ത് ക്യാമറയെ യഥാർത്ഥമായി ഉപയോഗിക്കാവുന്നതാണ്.

വിർച്വൽ ഹാർഡ്‌വെയർ [CounterFit project](https://github.com/CounterFit-IoT/CounterFit) ഉപയോഗിക്കും.

ഈ പാഠങ്ങൾ പൂർത്തിയാക്കാൻ ഒരു വെബ് ക്യാമറ, മൈക്രോഫോൺ, ഓഡിയോ ഔട്ട്പുട്ട് (സ്പീക്കർസ് അല്ലെങ്കിൽ ഹെഡ്‌ഫോൺസ്) വേണം. ഇവ നിർമ്മിച്ചതോ പുറത്തുള്ളതോ ആയിരിക്കാം, നിങ്ങളുടെ ഓപ്പറേറ്റിംഗ് സിസ്റ്റം പിന്തുണച്ചും എല്ലാ ആപ്ലിക്കേഷനുകളും ഉപയോഗിക്കാനും സജ്ജമാക്കേണ്ടതുണ്ട്.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**അസംബന്ധിത കോറിൻറ്റ്**:  
ഈ ഡോക്യുമെന്റ് AI ഭാഷാ പരിഭാഷാ സേവനം [Co-op Translator](https://github.com/Azure/co-op-translator) ഉപയോഗിച്ച് പരിഭാഷപ്പെടുത്തിയതാണ്. ഞങ്ങൾ സത്യസന്ധതയ്ക്കായി ശ്രമിക്കുന്നുവെങ്കിലും, സ്വയമാറ്റം ചെയ്ത പരിഭാഷകൾക്ക് പിഴവുകൾ അല്ലെങ്കിൽ തെറ്റുകൾ ഉണ്ടായിരിക്കാമെന്ന് ശ്രദ്ധിക്കുക. പരിഭാഷ ചെയ്യാത്ത മാതൃഭാഷയിലെ ആസ്വതമായ ഡോക്യുമെന്റാണ് അംഗീകൃത ഉറവിടമായി കണക്കാക്കപ്പെടേണ്ടത്. നിർബന്ധമായും പ്രധാനപ്പെട്ട വിവരങ്ങൾക്ക് പ്രൊഫഷണൽ മനുഷ്യ പരിഭാഷ പരിഗണിക്കുന്നത് ഉചിതമാണ്. ഈ പരിഭാഷയുടെ ഉപയോഗത്തിൽ നിന്നുണ്ടാകുന്ന യാതൊരു തെറ്റിദ്ധാരണകൾക്കും ഞങ്ങൾ ഉത്തരവാദിത്വം വഹിക്കുന്നില്ല.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->