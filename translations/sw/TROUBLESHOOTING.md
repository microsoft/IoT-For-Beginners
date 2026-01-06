<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T15:47:14+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "sw"
}
-->
# Mwongozo wa Utatuzi wa Matatizo

Mwongozo huu utakusaidia kutatua matatizo yanayojitokeza mara kwa mara unapotumia mitaala ya IoT kwa Waanzishu. Masuala yamepangwa kwa makundi ili kurahisisha urambazaji.

## Jedwali la Maudhui

- [Matatizo ya Usanifu](../..)
  - [Usanifu wa Python](../..)
  - [VS Code na Viongezeo](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Maktaba za Grove](../..)
- [Matatizo ya Vifaa](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Kifaa Halisi (CounterFit)](../..)
- [Matatizo ya Muunganisho](../..)
  - [Muunganisho wa WiFi](../..)
  - [Huduma za Wingu](../..)
  - [MQTT](../..)
- [Matatizo ya Sensor na Kifanyavyo](../..)
  - [Sensor za Grove](../..)
  - [Kamera](../..)
  - [Maikrofoni na Spika](../..)
- [Matatizo ya Mazingira ya Maendeleo](../..)
  - [VS Code](../..)
  - [Mazingira ya Virtual ya Python](../..)
  - [Tegemezi](../..)
- [Matatizo ya Utendaji](../..)
- [Ujumbe wa Makosa wa Kawaida](../..)
- [Kupata Msaada](../..)

---

## Matatizo ya Usanifu

### Usanifu wa Python

#### Tatizo: Toleo la Python ni la zamani mno
**Kosa:** `Python 3.6 au zaidi inahitajika`

**Suluhisho:**
1. Pakua toleo jipya la Python 3 kutoka [python.org](https://www.python.org/downloads/)
2. Wakati wa usakinishaji kwenye Windows, hakikisha "Add Python to PATH" imechaguliwa
3. Thibitisha usakinishaji:
   ```bash
   python3 --version
   ```

#### Tatizo: Toleo nyingi za Python zinasababisha migongano
**Dalili:** Toleo baya la Python linaendesha, vifurushi vinaweka sehemu isiyo sahihi

**Suluhisho:**
- **Windows:** Tumia `py -3` badala ya `python` kwa mwito wa moja kwa moja wa Python 3
- **macOS/Linux:** Tumia `python3` badala ya `python`
- Daima tengeneza na tumia mazingira ya virtual kwa miradi

#### Tatizo: Amri ya pip haipatikani
**Kosa:** `'pip' haijatambuliwa kama amri ya ndani au ya nje`

**Suluhisho:**
1. Jaribu `pip3` badala ya `pip`
2. Au tumia `python -m pip` au `python3 -m pip`
3. Hakikisha Python imeongezwa kwenye PATH (weka upya Python na hakikisha chaguo limechaguliwa)

### VS Code na Viongezeo

#### Tatizo: Kiini cha Pylance hakifanyi kazi
**Dalili:** Hakuna IntelliSense ya Python, kukamilisha msimbo, au ukaguzi wa aina

**Suluhisho:**
1. Fungua Palette ya Amri ya VS Code (`Ctrl+Shift+P` au `Cmd+Shift+P`)
2. Endesha "Python: Select Interpreter"
3. Chagua tafsiri sahihi ya Python (mazingira ya virtual ukitumia moja)
4. Pindua dirisha la VS Code

#### Tatizo: VS Code haibaini mazingira ya virtual
**Dalili:** Tafsiri isiyo sahihi ya Python imechaguliwa

**Suluhisho:**
1. Hakikisha umewezesha mazingira ya virtual kwenye terminal
2. Fungua Palette ya Amri na endesha "Python: Select Interpreter"
3. Chagua tafsiri kutoka kwenye folda `.venv`
4. Angalia bar ya hali (kushoto chini) inaonyesha toleo sahihi la Python

### PlatformIO (Wio Terminal)

#### Tatizo: Usakinishaji wa PlatformIO unashindwa
**Kosa:** Makosa mbalimbali wakati wa usakinishaji wa PlatformIO

**Suluhisho:**
1. Hakikisha VS Code iko kwenye hali ya kisasa
2. Sakinisha kiini cha C/C++ kwanza
3. Anzisha upya VS Code baada ya kusakinisha PlatformIO
4. Kagua muunganisho wako wa intaneti (PlatformIO hupakua faili kubwa)

#### Tatizo: Bodi haibainiki na PlatformIO
**Dalili:** Huwezi kupakia msimbo kwenye Wio Terminal

**Suluhisho:**
1. Jaribu kebo nyingine ya USB (kabeli kadhaa ni za kuchaji tu)
2. Kagua Meneja Vifaa (Windows) au `ls /dev/tty*` (macOS/Linux)
3. Sakinisha au sasisha madereva ya USB
4. Jaribu tovuti tofauti ya USB
5. Sukuma swichi ya nguvu ya Wio Terminal mara mbili haraka kuingia hali ya bootloader

#### Tatizo: Makosa ya utengenezwaji kwenye PlatformIO
**Kosa:** `fatal error: Arduino.h: No such file or directory`

**Suluhisho:**
1. Futa folda `.pio` kwenye mradi wako
2. Endesha "PlatformIO: Rebuild" kutoka Palette ya Amri
3. Hakikisha `platformio.ini` ina usanifu sahihi wa bodi:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Maktaba za Grove

#### Tatizo: Ugani wa maktaba ya Grove hauna kazi kwenye Raspberry Pi
**Kosa:** `ModuleNotFoundError: No module named 'grove'`

**Suluhisho:**
1. Sakinisha tena maktaba za Grove:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Ikiwa unatumia mazingira ya virtual, unaweza kuhitaji kusakinisha kimataifa au kunakili maktaba
3. Hakikisha I2C imewezeshwa: `sudo raspi-config nonint do_i2c 0`

#### Tatizo: Sensor ya Grove haibainiki
**Kosa:** `IOError: [Errno 121] Remote I/O error`

**Suluhisho:**
1. Angalia muunganisho halisi (hakikisha kebo ya Grove imeingizwa kabisa)
2. Hakikisha sensor imeunganishwa kwenye bandari sahihi (analog, digital, I2C, UART)
3. Endesha `i2cdetect -y 1` kuona kama kifaa kinaonekana kwenye basi la I2C
4. Jaribu kebo nyingine ya Grove
5. Hakikisha Grove Base Hat imewekwa vizuri kwenye pini za GPIO za Raspberry Pi

---

## Matatizo ya Vifaa

### Raspberry Pi

#### Tatizo: Raspberry Pi haizimi
**Dalili:** Hakuna onyesho, hakuna shughuli za LED, au skrini ya rangi za mvua

**Suluhisho:**
1. **Kagua ugavi wa nguvu:** Tumia ugavi rasmi wa 5V 3A USB-C kwa Pi 4
2. **Matatizo ya kadi ya SD:** 
   - Fomati upya kadi ya SD na sanidua Raspberry Pi OS
   - Jaribu kadi nyingine ya SD (tumia chapa zilizopendekezwa)
   - Hakikisha kadi ya SD imeingizwa vizuri
3. **Kagua muunganisho wa HDMI:** Jaribu bandari zote za HDMI kwenye Pi 4, tumia bandari ya HDMI iliyo karibu na nguvu

#### Tatizo: Huwezi SSH kwenye Raspberry Pi
**Dalili:** Muunganisho unakataliwa au muda umemalizika

**Suluhisho:**
1. Wezesha SSH:
   - Wakati wa kumwaga kadi ya SD kwa kutumia Raspberry Pi Imager, sanifu SSH kwenye chaguo za hali ya juu
   - Au tengeneza faili tupu iitwayo `ssh` (bila kiambatisho) kwenye sehemu ya boot
2. Tafuta anwani ya IP ya Pi:
   - Angalia vifaa vilivyounganishwa kwenye routa yako
   - Tumia `ping raspberrypi.local` (ikiwa mDNS inafanya kazi)
   - Tumia zana za skanning ya mtandao kama `nmap` au Angry IP Scanner
3. Kagua mtandao:
   - Hakikisha Pi iko kwenye mtandao mmoja na kompyuta yako
   - Jaribu muunganisho wa ethernet badala ya WiFi
4. Thibitisha jina la mtumiaji/nenosiri (kawaida: mtumiaji `pi`, nenosiri `raspberry`)

#### Tatizo: Grove Base Hat haikutambuliwi
**Dalili:** Sensor hazifanyi kazi, makosa ya I2C

**Suluhisho:**
1. Hakikisha Base Hat imewekwa vizuri kwenye pini zote za GPIO
2. Angalia kama pini zimebendeka kwenye Pi au Base Hat
3. Wezesha kiolesura cha I2C:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Thibitisha I2C inafanya kazi: `i2cdetect -y 1`

#### Tatizo: Raspberry Pi inaendesha polepole
**Dalili:** UI inachelewa, majibu ni pole

**Suluhisho:**
1. Kagua kasi ya kadi ya SD (tumia Class 10 au bora zaidi, au SSD kupitia USB)
2. Toa nafasi ya hifadhi: `df -h` kukagua, futa faili zisizohitajika
3. Punguza kumbukumbu ya GPU kwenye `raspi-config` kama haujatumia kamera/onyesho sana
4. Funga programu zisizohitajika
5. Fikiria kuhamia Pi 4 yenye RAM zaidi ikiwa unatumia Pi 3 au za zamani

### Wio Terminal

#### Tatizo: Skrini ya Wio Terminal inabaki tupu
**Dalili:** Hakuna onyesho baada ya kupakia msimbo

**Suluhisho:**
1. Kagua kama msimbo unaanzisha onyesho (maktaba ya TFT_eSPI)
2. Sasisha firmware ya Wio Terminal kutoka [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Ongeza msimbo wa kuanzisha onyesho:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Jaribu kupakia mfano wa sketch kutoka PlatformIO kujaribu vifaa

#### Tatizo: WiFi haifanyi kazi kwenye Wio Terminal
**Dalili:** Huwezi kuungana na WiFi, makosa ya mtandao

**Suluhisho:**
1. **Sasisha firmware ya WiFi:** Fuata [mwongozo wa sasisho la firmware ya WiFi ya Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Kagua taarifa za WiFi:** Hakikisha SSID na nenosiri ni sahihi
3. **Bendi ya WiFi:** Wio Terminal inaunga mkono WiFi ya 2.4GHz tu (sio 5GHz)
4. **Nguvu ya ishara:** Mkaribishe kwa routa
5. **Miamala ya routa:** Mitandao ya chuo/kampuni/WPA-Enterprise inaweza isifanye kazi

#### Tatizo: Kompyuta haikutambua Wio Terminal
**Dalili:** Kifaa cha USB hakikugunduliwa

**Suluhisho:**
1. **Jaribu kebo nyingine ya USB:** Tumia kebo ya data, si kebo ya kuchaji tu
2. **Ingiza hali ya bootloader:** Sukuma swichi ya nguvu chini mara mbili haraka
   - LED ya buluu inapaswa kupenya, kifaa kinaonekana kama "Arduino" kwenye Meneja Vifaa
3. **Sakinisha madereva (Windows):**
   - Pakua na sakinisha [Dereva ya USB ya Seeed](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Jaribu bandari nyingine ya USB:** Epuka vituo vya USB, tumia muunganisho wa moja kwa moja
5. **Sasisha madereva ya USB ya mfumo**

#### Tatizo: Sensor hazifanyi kazi kwenye Wio Terminal
**Dalili:** Sensor za Grove hazisomi data

**Suluhisho:**
1. Kagua muunganisho wa kebo za Grove
2. Hakikisha unatumia bandari sahihi ya Grove (kushoto au kulia)
3. Jumuisha maktaba sahihi kwa sensor
4. Kagua mahitaji ya nguvu ya sensor
5. Jaribu sensor kwa msimbo wa mfano kutoka maktaba

### Kifaa Halisi (CounterFit)

#### Tatizo: Programu ya CounterFit haianzishi
**Kosa:** Makosa mbalimbali ya Python wakati wa kuanzisha CounterFit

**Suluhisho:**
1. Hakikisha mazingira ya virtual yamewezeshwa
2. Sakinisha/usakinishe upya CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Kagua kama bandari 5000 haijatumiwa tayari:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Funga mchakato unaotumia bandari 5000 au tumia bandari tofauti:
   ```bash
   counterfit --port 5001
   ```

#### Tatizo: Huwezi kuungana na CounterFit kutoka msimbo
**Kosa:** Muunganisho umekataliwa au muda umemalizika

**Suluhisho:**
1. Thibitisha CounterFit inaendesha: Fungua kivinjari `http://127.0.0.1:5000`
2. Kagua URL ya muunganisho kwenye msimbo inalingana na anwani ya CounterFit
3. Hakikisha firewall haizuizi muunganisho
4. Jaribu kutanzua tena programu ya CounterFit na msimbo wako

#### Tatizo: Sensor hazionekani katika CounterFit
**Dalili:** Sensor zilizoundwa hazionekani kwenye UI ya CounterFit

**Suluhisho:**
1. Unda sensor kwenye UI ya CounterFit kabla ya kuendesha msimbo
2. Fanyia upya ukurasa wa kivinjari
3. Kagua aina ya sensor inalingana na kile msimbo unachotarajia
4. Safisha cache ya kivinjari

---

## Matatizo ya Muunganisho

### Muunganisho wa WiFi

#### Tatizo: Kifaa hakiwezi kuunganishwa na WiFi
**Dalili:** Muunganisho umechelewa, uthibitisho umefungwa

**Suluhisho:**
1. **Kagua SSID na nenosiri:** Hakikisha taarifa ni sahihi
2. **Bendi ya WiFi:** Vifaa vingi vya IoT vinaunga mkono bendi ya 2.4GHz tu (si 5GHz)
3. **Mipangilio ya routa:**
   - Zima AP isolation ikiwa imewezeshwa
   - Tumia usalama wa WPA2-PSK (epuka WPA3, WEP, au mitandao wazi)
   - Hakikisha DHCP imewezeshwa
4. **Mitandao iliyofichwa:** Ikiwa SSID imelazwa, huenda ukahitaji kuisanifu waziwazi
5. **Nguvu ya ishara:** Karibu kifaa na routa
6. **Vishawishi:** Vifaa vingine, maeneo ya microwave, au kuta vinaweza kusababisha usumbufu

#### Tatizo: Muunganisho wa WiFi unakatika mara kwa mara
**Dalili:** Muunganisho wa kati na kati

**Suluhisho:**
1. Kagua utulivu wa routa na fikiria kuanzisha upya
2. Sasisha firmware ya kifaa
3. Tumia IP ya kila wakati badala ya DHCP
4. Punguza umbali hadi routa au ongeza kipanua WiFi
5. Kagua usumbufu kutoka kwa vifaa vingine
6. Hakikisha chanzo cha nguvu ni cha kutosha (hasa kwa Raspberry Pi)

### Huduma za Wingu

#### Tatizo: Huwezi kuungana na Azure IoT Hub
**Kosa:** Uthibitisho umefungwa, muunganisho umekataliwa

**Suluhisho:**
1. **Thibitisha taarifa:**
   - Kagua mnyororo wa muunganisho ni sahihi
   - Hakikisha hakuna nafasi za ziada au vipande vya mistari kwenye mnyororo wa muunganisho
2. **Kagua usajili wa kifaa:** Kifaa lazima kijiandikishe kwenye IoT Hub
3. **Firewall/proxy:** Hakikisha MQTT (bandari 8883) au HTTPS (bandari 443) zinaruhusiwa kutoka nje
4. **Eneo la IoT Hub:** Hakikisha IoT Hub inaendeshwa na sio katika eneo tofauti linalosababisha ucheleweshaji
5. **Mikwaju ya kipimo:** Kagua kama mipaka ya tier ya bure imezidiwa
6. **Jaribu muunganisho:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Tatizo: Azure Functions hazianza
**Dalili:** Ujumbe umetumwa lakini function haifanyi kazi

**Suluhisho:**
1. Kagua kama Function App inaendesha (haijasimama)
2. Thibitisha mnyororo wa muunganisho katika mipangilio ya Function App
3. Kagua logi za function kwenye Azure Portal
4. Hakikisha sehemu ya Event Hub sambamba imewekwa kwa usahihi
5. Thibitisha muundo wa ujumbe unalingana na matarajio ya function
6. Kagua mpango wa huduma wa Function App (kula vs. wa pekee)

### MQTT
#### Tatizo: Muunganisho wa MQTT hupoteza
**Hitilafu:** Muunganisho umekataliwa, uthibitishaji umefanikiwa

**Suluhisho:**
1. **Anwani ya mtoza:** Hakikisha URL/IP ya mtoza ni sahihi
2. **Bandari:** Angalia nambari ya bandari (1883 kwa isiyo na usimbaji, 8883 kwa TLS)
3. **Uthibitishaji:** Hakikisha jina la mtumiaji/nenosiri kama linahitajika
4. **TLS/SSL:** Hakikisha vyeti ni halali na vinaaminika
5. **Kuta za moto:** Angalia bandari haizuiwi
6. **Jaribu na mteja wa MQTT:** Tumia MQTT Explorer au mosquitto_pub/sub kwa jaribio

#### Tatizo: Ujumbe wa MQTT hauwekiwi
**Dalili:** Ujumbe umechapishwa lakini hauwekiwi na wafuasi

**Suluhisho:**
1. **Majina ya mada:** Hakikisha mada ya mfuasi inalingana kabisa na mada ya mchapishaji
2. **Kiwango cha QoS:** Jaribu QoS 1 au 2 badala ya 0
3. **Vibarua vya manjano:** Angalia matumizi sahihi ya vibarua vya mada (`+` kwa ngazi moja, `#` kwa ngazi nyingi)
4. **Ujumbe uliothibitishwa:** Mchapishaji anaweza kuweka bendera ya retain kuhifadhi ujumbe wa mwisho
5. **Muda wa muunganisho:** Hakikisha mfuasi anaunganishwa kabla ya ujumbe kuchapishwa

---

## Masuala ya Vihisi na Vitenda

### Vihisi vya Grove

#### Tatizo: Kihisi kinarejesha thamani zisizofaa
**Dalili:** Kusoma ni 0, -1, au thamani zisizoeleweka

**Suluhisho:**
1. **Angalia muunganisho:** Hakikisha kihisi kimeunganishwa kwa usahihi
2. **Bandari sahihi:** Hakikisha kihisi kiko katika aina sahihi ya bandari:
   - Vihisi vya analojia → Bandari za analojia (A0, A2, A4)
   - Vihisi vya kidijitali → Bandari za kidijitali (D5, D16, D18, nk)
   - Vihisi vya I2C → Bandari za I2C
3. **Kurekebisha:** Vihisi vingine vinahitaji kalibrishaji (unyevu wa udongo, mwanga)
4. **Zungusha nguvu:** Tekeleza kizima na kuwasha upya kihisi
5. **Kitabu cha data cha kihisi:** Angalia vipimo na mahitaji ya kihisi

#### Tatizo: Kihisi cha unyevu wa udongo wa capacitive husoma daima kuwa mvua
**Dalili:** Kihisi husoma unyevu mkubwa hata wakati kavu

**Suluhisho:**
1. **Kalibrishaji inahitajika:** Vihisi vya udongo vinahitaji kalibrishaji:
   - Soma thamani katika hewa (msingi wa kavu)
   - Soma thamani katika maji (msingi wa mvua)
   - Ramani ya kusoma kati ya hizi thamani
2. **Angalia rangi ya kihisi:** Vihisi vya unyevu vinaweza kuharibika kama rangi iliyofunikwa imedhoofika
3. **Mahali pa kuweka:** Hakikisha kihisi kimeingizwa kikamilifu katika udongo

#### Tatizo: Vipimo vya joto/unyevu havifai
**Dalili:** DHT11/DHT22 inaonyesha joto au unyevu usio sahihi

**Suluhisho:**
1. **Mahali pa kihisi:** Epuka jua moja kwa moja, vyanzo vya joto, au mtiririko wa hewa
2. **Muda wa kupasha:** Mruhusu kihisi sekunde 2 baada ya kuwashwa kabla ya kusoma
3. **Mara ya kusoma:** Vihisi vya DHT vinahitaji muda kati ya masomo (angalau sekunde 2)
4. **Angalia kondensheni:** Inaweza kuathiri vipimo
5. **Ubora wa kihisi:** DHT11 si sahihi kama DHT22

### Kamera

#### Tatizo: Kamera haipatikani kwenye Raspberry Pi
**Hitilafu:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Suluhisho:**
1. **Lezimisha kiolesura cha kamera:**
   ```bash
   sudo raspi-config
   ```
   Nenda Interface Options → Camera → Enable
2. **Angalia waya wa ribbon:** Hakikisha waya wa kamera umeingizwa kwa usahihi
   - Nguvu ya bluu inakabili bandari za USB kwenye Pi Zero
   - Nguvu ya bluu inakabili mbali na bandari za USB kwenye Pi 4
3. **Sasisha firmware:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Jaribu kamera:**
   ```bash
   raspistill -o test.jpg
   ```

#### Tatizo: Picha za kamera ni zenye ubora mdogo
**Dalili:** Picha zinazoachiwa, giza, au za kufifia

**Suluhisho:**
1. **Lenga:** Ondoa filamu ya kinga kwenye lensi, rekebisha kung'aa kama inavyoweza
2. **Mwangaza:** Hakikisha mwanga ni wa kutosha
3. **Mipangilio ya kamera:** Rekebisha mfiduo, ISO, uwiano wa nyeupe kwa programu
4. **Utulivu:** Weka kamera imetulia, tumia tripod kama inahitajika
5. **Azimio:** Usizidi azimio la juu kabisa la kamera

### Kipaza Sauti na Spika

#### Tatizo: Hakuna pembejeo/mazao ya sauti
**Dalili:** Kipaza sauti hakirekodi, spika hachezi

**Suluhisho:**
1. **Angalia muunganisho:** Hakikisha vifaa vya sauti vimeunganishwa sawasawa
2. **Jaribu vifaa:**
   - Spika: `speaker-test -t wav -c 2`
   - Kipaza sauti: `arecord -l` kuorodhesha, `arecord test.wav` kurekodi
3. **Mipangilio ya wigo:** Angalia na rekebisha wigo:
   ```bash
   alsamixer
   ```
4. **Chagua kifaa cha sauti:** Eleza kifaa sahihi cha sauti kwa msimbo
5. **Masuala ya dereva:** Sasisha ALSA au weka upya madereva ya sauti

#### Tatizo: ReSpeaker hat haifanyi kazi
**Dalili:** Kifaa cha sauti hakipatikani

**Suluhisho:**
1. **Sakinisha madereva:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Angalia usakinishaji:** `arecord -l` inapaswa kuorodhesha ReSpeaker
3. **Sasisha firmware:** Baadhi ya matoleo ya Pi OS yanahitaji masasisho ya dereva
4. **Angalia muunganisho:** Hakikisha hat imeunganishwa kwa usahihi kwenye pini za GPIO

---

## Masuala ya Mazingira ya Maendeleo

### VS Code

#### Tatizo: Terminal haizindui mazingira halisi ya virtual moja kwa moja
**Dalili:** Terminal inafunguka lakini venv haijazinduliwa

**Suluhisho:**
1. **Weka mkalimani wa Python:** Command Palette → "Python: Select Interpreter" → Chagua venv
2. **Wazindua tena VS Code** baada ya kuchagua mkalimani
3. **Angalia mipangilio:** Katika `settings.json`, ongeza:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Tatizo: Msimbo hauendi kwenye kifaa
**Dalili:** Msimbo unaendesha lakini hakuna kinachotokea kwenye kifaa

**Suluhisho:**
1. **Hakikisha msimbo umehifadhiwa** (angalia doa kwenye kichupo cha faili)
2. **Angalia Python inayotumiwa:** `which python` au `where python`
3. **Kwa Wio Terminal:** Hakikisha msimbo umewekwa kupitia PlatformIO (bonyeza kitufe cha upload)
4. **Kwa Raspberry Pi:** Ingia SSH kwenye Pi na endesha msimbo huko
5. **Angalia dirisha la mazao** kwa makosa

#### Tatizo: IntelliSense haionyeshi kazi za maktaba
**Dalili:** Hakuna kukamilishwa kwa moduli zilizoingizwa

**Suluhisho:**
1. Hakikisha maktaba imesakinishwa katika mazingira ya sasa
2. Reload dirisha la VS Code
3. Angalia mkalimani wa Python ni sahihi
4. Sakinisha type stubs kama zinapatikana: `pip install types-<library-name>`

### Mazingira Halisi ya Python Virtual

#### Tatizo: Haiwezi kuunda mazingira halisi ya virtual
**Hitilafu:** `The virtual environment was not created successfully`

**Suluhisho:**
1. **Sakinisha moduli ya venv:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Inapaswa kuwa pamoja na Python
   - Windows: Sakinisha upya Python na vipengele vyote
2. **Angalia usakinishaji wa Python:** Hakikisha Python imewekwa vizuri
3. **Tumia njia kamili:** Jaribu `python3 -m venv .venv` kwa kuitwa kwa python3 wazi

#### Tatizo: Mafaili yamesakinishwa mahali pasipofaa
**Dalili:** Hitilafu ya import baada ya kusakinisha kifurushi

**Suluhisho:**
1. **Hakikisha venv imewezeshwa:** Terminal inapaswa kuonyesha `(.venv)`
2. **Angalia mahali pa pip:** `which pip` inapaswa kuelekeza kwenye `.venv/bin/pip`
3. **Sakinisha tena ndani ya venv:** Wezesha venv, kisha `pip install <package>`
4. **Usitumie sudo na pip** ndani ya mazingira halisi ya virtual

#### Tatizo: Mazingira halisi ya virtual hayabadiliki kwa urahisi
**Dalili:** Venv haiendi baada ya kuhamishwa au kwenye kompyuta tofauti

**Suluhisho:**
1. **Usihamishe venv:** Futa na unda upya katika mahali mpya
2. **Tumia requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Unda upya venv:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # au activate.bat kwenye Windows
   pip install -r requirements.txt
   ```

### Mahitaji

#### Tatizo: Usakinishaji wa kifurushi unashindwa
**Hitilafu:** Makosa mbalimbali ya pip wakati wa usakinishaji

**Suluhisho:**
1. **Sasisha pip:**
   ```bash
   pip install --upgrade pip
   ```
2. **Sakinisha zana za ujenzi:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Sakinisha Visual Studio Build Tools
3. **Angalia muunganisho wa intaneti**
4. **Jaribu kipepeo tofauti cha kifurushi:** `pip install --index-url https://pypi.org/simple/ <package>`
5. **Sakinisha toleo maalum:** `pip install <package>==<version>`

#### Tatizo: Migongano ya utegemezi
**Hitilafu:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Suluhisho:**
1. **Tumia mazingira halisi safi ya virtual** kwa kila mradi
2. **Sasisha vifurushi:** `pip install --upgrade <package>`
3. **Angalia mahitaji:** Tumia `pip check` kutafuta migongano
4. **Sakinisha matoleo yanayolingana:** Eleza anuwai za toleo katika requirements.txt

---

## Masuala ya Utendaji

### Tatizo: Msimbo unaendesha polepole
**Dalili:** Kuchelewa, muda wa kusubiri, tabia isiyo responsive

**Suluhisho:**
1. **Punguza mara ya kusoma kihisi:** Usisome kihisi mara kwa mara sana
2. **Boreshaji za mizunguko:** Epuka kusubiri shughuli, tumia sleep() au ucheleweshaji
3. **Masuala ya kumbukumbu:**
   - Funga programu zisizohitajika
   - Panua nafasi ya kuhifadhi
   - Tazama matumizi na `top` au `htop` kwenye Pi
4. **Mwendo wa kadi ya SD:** Tumia kadi ya SD au SSD yenye kasi zaidi kwa Raspberry Pi
5. **Machelezo ya mtandao:** Tumia vitendo asynchronous kwa miito ya mtandao

### Tatizo: Makosa ya ukosefu wa kumbukumbu
**Hitilafu:** `MemoryError` au mfumo kujaa

**Suluhisho:**
1. **Kwa Raspberry Pi:**
   - Funga programu zisizohitajika
   - Panua nafasi ya swap
   - Tumia mfumo mwepesi (toleo la Lite)
   - Boresha RAM (Pi 4 ina chaguzi 2/4/8GB)
2. **Kwa Wio Terminal:**
   - Punguza ukubwa wa buffer
   - Tumia picha ndogo
   - Boreshaji matumizi ya mfuatano wa herufi
   - Angalia uvujaji wa kumbukumbu (kumbukumbu isiyorudishwa)

### Tatizo: Kupotea au uharibifu wa data
**Dalili:** Ujumbe unakosekana, faili zimeharibika

**Suluhisho:**
1. **Masuala ya kadi ya SD:**
   - Tumia kadi bora za SD (epuka za bei rahisi/bogl)
   - Fanya nakala za hifadhi mara kwa mara
   - Shut down vizuri (usizime ghafla)
2. **Buffer overflow:** Panua ukubwa wa buffer katika msimbo
3. **Amini mtandao:** Tekeleza mbinu za jaribio tena na kushughulikia makosa
4. **Ubora wa huduma:** Tumia QoS 1 au 2 kwa ujumbe muhimu wa MQTT

---

## Makosa Maarufu

### `ModuleNotFoundError: No module named 'X'`
**Sababu:** Kifurushi hakijasakinishwa au mazingira halisi hayajazinduliwa

**Suluhisho:**
```bash
pip install X
```
Hakikisha mazingira halisi ya virtual yamewezeshwa kwanza.

### `Permission denied` kwenye Linux/macOS
**Sababu:** Inahitaji ruhusa za juu au tatizo la ruhusa za faili

**Suluhisho:**
- Kwa shughuli za mfumo: Tumia `sudo`
- Kwa pip: USITUMIE sudo na venv, zindua venv kwanza
- Kwa bandari ya serial: Ongeza mtumiaji kwenye kundi la dialout: `sudo usermod -a -G dialout $USER`, kisha ingia/ondoka tena

### `OSError: [Errno 98] Address already in use`
**Sababu:** Bandari tayari inatumika na mchakato mwingine

**Suluhisho:**
1. Tafuta mchakato unaotumia bandari: `lsof -i :<port>` au `netstat -ano | findstr :<port>`
2. Funga mchakato au tumia bandari tofauti kwenye msimbo wako

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Sababu:** Uthibitishaji wa cheti cha SSL umeshindwa

**Suluhisho:**
1. Sasisha vyeti: `pip install --upgrade certifi`
2. Angalia saa ya mfumo ni sahihi: `date`
3. Kwa maendeleo tu (si kwa uzalishaji): Zima uthibitishaji kwenye msimbo

### `IndentationError: unexpected indent`
**Sababu:** Makosa ya usanifu wa Python (changanya tabs na spaces)

**Suluhisho:**
1. Tumia usanifu mmoja (nafasi 4 ni kiwango cha Python)
2. Sanidi mhariri kutumia nafasi badala ya tabs
3. VS Code: Weka `"editor.insertSpaces": true` na `"editor.tabSize": 4`

### `UnicodeDecodeError` au `UnicodeEncodeError`
**Sababu:** Masuala ya usimbaji tabia wa herufi

**Suluhisho:**
```python
# Wakati wa kusoma faili
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Wakati wa kuandika faili
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Kupata Msaada

Ukitumia hatua hizi za kutatua matatizo na bado kuna shida:

### 1. Angalia Rasilimali Zilizopo
- **Nyaraka:** Pitia [README](README.md) na maelekezo ya somo
- **Mwongozo wa vifaa:** Angalia [hardware.md](hardware.md) kwa maelezo ya vifaa
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) kwa sehemu za Grove

### 2. Tafuta Masuala Yanayofanana
- **Masuala ya GitHub:** Tafuta [masuala yaliyopo](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Tafuta ujumbe wa makosa
- **Mifumo ya majadiliano ya vifaa:** Angalia majukwaa ya Raspberry Pi au Arduino

### 3. Tengeneza Tatizo la GitHub
Ukishindwa kupata suluhisho:
1. Nenda [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Bonyeza "New Issue"
3. Toa:
   - Maelezo kamili ya tatizo
   - Hatua za kurudia tatizo
   - Ujumbe wa makosa (maandishi kamili)
   - Toleo la vifaa/programu
   - Nini umejaribu tayari
   - Picha za skrini ikiwa zinahitajika

### 4. Jiunge na Jamii
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Toa Ripoti Nzuri za Makosa
Ripoti nzuri ya tatizo ni pamoja na:
- **Mazingira:** OS, toleo la Python, vifaa vinavyotumika
- **Hatua za kuzalisha tatizo:** Hatua halisi zinazosababisha tatizo
- **Tabia inayotarajiwa:** Kile kinachopaswa kutokea
- **Tabia halisi:** Kile kinachotokea kweli
- **Ujumbe wa makosa:** Maandishi kamili ya kosa, si picha-skrini
- **Msimbo:** Mfano mdogo wa msimbo unaozalisha tatizo

---

## Vidokezo vya Kuzuia

### Mbinu Bora za Kawaida
1. **Hifadhi nakala:** Fanya nakala za mara kwa mara za kadi za SD zinazofanya kazi/kanzidata
2. **Andika mabadiliko:** Kumbuka kile kinachofanya kazi katika maelezo ya msimbo
3. **Dhibiti toleo:** Tumia git kufuatilia mabadiliko ya msimbo
4. **Jaribu kidogo kidogo:** Jaribu mabadiliko madogo kabla ya kuziunganisha
5. **Soma ujumbe wa makosa:** Mara nyingi huonyesha hasa kilichokosekana
6. **Sasisha mara kwa mara:** Weka programu/kifirmware kisasishwa
7. **Tumia vipengele vya ubora:** Epuka nyaya/vesi za nguvu zisizostahili
8. **Nguvu thabiti:** Tumia chanzo cha nguvu kinachofaa (hasa Pi)

### Mtiririko wa Maendeleo
1. **Anza kwa urahisi:** Anza na msimbo wa mfano unaofanya kazi
2. **Badiliko moja kwa wakati:** Rahisi kugundua kinachovunjika
3. **Jaribu mara kwa mara:** Gonga matatizo mapema
4. **Hifadhi usafi:** Panga faili na msimbo kwa njia ya mantiki
5. **Andika maelezo kwenye msimbo:** Wewe wa baadaye utathamini

---

*Mwongozo huu wa kutatua matatizo unahudumiwa na jamii. Ikiwa unapata suluhisho la tatizo lisilotajwa hapa, tafadhali fikiria [kuchangia](CONTRIBUTING.md) kusaidia wengine!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Kiarifa cha Kukwepa Majukumu**:
Nyaraka hii imetafsiriwa kwa kutumia huduma ya kutafsiri kwa AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kwa usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kasoro. Nyaraka ya awali katika lugha yake asilia inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inashauriwa. Hatuwajibiki kwa uelewa au tafsiri potofu zinazotokana na matumizi ya tafsiri hii.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->