<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-28T11:57:52+00:00",
  "source_file": "hardware.md",
  "language_code": "hr"
}
-->
# Hardver

**T** u IoT označava **Things** (stvari) i odnosi se na uređaje koji komuniciraju s okolinom. Svaki projekt temelji se na stvarnom hardveru koji je dostupan studentima i hobistima. Imamo dva izbora IoT hardvera, ovisno o osobnim preferencijama, znanju ili sklonostima prema programskim jezicima, ciljevima učenja i dostupnosti. Također smo osigurali verziju 'virtualnog hardvera' za one koji nemaju pristup fizičkom hardveru ili žele naučiti više prije nego što se odluče na kupnju.

> 💁 Nije potrebno kupiti IoT hardver za dovršavanje zadataka. Sve možete napraviti koristeći virtualni IoT hardver.

Fizički hardverski izbori su Arduino ili Raspberry Pi. Svaka platforma ima svoje prednosti i nedostatke, a sve su objašnjene u jednoj od početnih lekcija. Ako još niste odlučili koju hardversku platformu želite koristiti, možete pregledati [drugu lekciju prvog projekta](./1-getting-started/lessons/2-deeper-dive/README.md) kako biste odlučili koja vas platforma najviše zanima.

Odabrani hardver smanjuje složenost lekcija i zadataka. Iako bi drugi hardver mogao raditi, ne možemo jamčiti da će svi zadaci biti podržani na vašem uređaju bez dodatnog hardvera. Na primjer, mnogi Arduino uređaji nemaju WiFi, koji je potreban za povezivanje s oblakom - Wio terminal je odabran jer ima ugrađen WiFi.

Također će vam trebati nekoliko netehničkih predmeta, poput zemlje ili sobne biljke te voća ili povrća.

## Kupnja kompleta

![Logotip Seeed Studios](../../translated_images/hr/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios su vrlo ljubazno omogućili da sav hardver bude dostupan u obliku lako dostupnih kompleta:

### Arduino - Wio Terminal

**[IoT za početnike sa Seeed i Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Komplet hardvera Wio Terminal](../../translated_images/hr/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT za početnike sa Seeed i Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Komplet hardvera Raspberry Pi Terminal](../../translated_images/hr/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Sav kod za Arduino uređaje pisan je u C++. Za dovršavanje svih zadataka trebat će vam sljedeće:

### Arduino hardver

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Opcionalno* - USB-C kabel ili USB-A na USB-C adapter. Wio terminal ima USB-C priključak i dolazi s USB-C na USB-A kabelom. Ako vaše računalo ili Mac ima samo USB-C priključke, trebat će vam USB-C kabel ili USB-A na USB-C adapter.

### Specifični senzori i aktuatori za Arduino

Ovi su specifični za korištenje Wio terminala s Arduino uređajem i nisu relevantni za Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Žice za breadboard](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Slušalice ili drugi zvučnik s 3.5mm priključkom, ili JST zvučnik poput:
  * [Mono zatvoreni zvučnik - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD kartica od 16GB ili manje, zajedno s adapterom za korištenje SD kartice s računalom ako nemate ugrađeni čitač. **NAPOMENA** - Wio Terminal podržava samo SD kartice do 16GB, veći kapaciteti nisu podržani.

## Raspberry Pi

Sav kod za Raspberry Pi uređaje pisan je u Pythonu. Za dovršavanje svih zadataka trebat će vam sljedeće:

### Raspberry Pi hardver

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Verzije od Pi 2B i novije trebale bi raditi sa zadacima u ovim lekcijama. Ako planirate koristiti VS Code izravno na Pi-ju, tada je potreban Pi 4 s 2GB ili više RAM-a. Ako ćete pristupati Pi-ju na daljinu, tada će raditi bilo koji Pi 2B i noviji.
* microSD kartica (Možete nabaviti Raspberry Pi komplete koji dolaze s microSD karticom), zajedno s adapterom za korištenje SD kartice s računalom ako nemate ugrađeni čitač.
* USB napajanje (Možete nabaviti Raspberry Pi 4 komplete koji dolaze s napajanjem). Ako koristite Raspberry Pi 4, trebat će vam USB-C napajanje, dok stariji uređaji koriste micro-USB napajanje.

### Specifični senzori i aktuatori za Raspberry Pi

Ovi su specifični za korištenje Raspberry Pi uređaja i nisu relevantni za Arduino.

* [Grove Pi osnovni hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi kamera modul](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofon i zvučnik:

  Koristite jedno od sljedećeg (ili ekvivalentno):
  * Bilo koji USB mikrofon s bilo kojim USB zvučnikom, ili zvučnik s 3.5mm priključkom, ili korištenje HDMI audio izlaza ako je vaš Raspberry Pi povezan s monitorom ili TV-om sa zvučnicima
  * Bilo koji USB headset s ugrađenim mikrofonom
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) s
    * Slušalicama ili drugim zvučnikom s 3.5mm priključkom, ili JST zvučnikom poput:
    * [Mono zatvoreni zvučnik - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove senzor svjetla](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove gumb](https://www.seeedstudio.com/Grove-Button.html)

## Senzori i aktuatori

Većina senzora i aktuatora potrebnih za zadatke koristi se i za Arduino i za Raspberry Pi:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove senzor vlage i temperature](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove kapacitivni senzor vlažnosti tla](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove relej](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove senzor udaljenosti (Time of Flight)](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Opcionalni hardver

Lekcije o automatiziranom zalijevanju koriste relej. Kao opciju, možete spojiti ovaj relej na pumpu za vodu napajanu putem USB-a koristeći dolje navedeni hardver.

* [6V pumpa za vodu](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB terminal](https://www.adafruit.com/product/3628)
* Silikonske cijevi
* Crvene i crne žice
* Mali odvijač s ravnim vrhom

## Virtualni hardver

Virtualni hardverski pristup omogućit će simulatore za senzore i aktuatore, implementirane u Pythonu. Ovisno o dostupnosti vašeg hardvera, možete ga pokrenuti na svom uobičajenom razvojnom uređaju, poput Maca, PC-a, ili ga pokrenuti na Raspberry Pi-ju i simulirati samo hardver koji nemate. Na primjer, ako imate Raspberry Pi kameru, ali ne i Grove senzore, moći ćete pokrenuti virtualni uređaj na svom Pi-ju i simulirati Grove senzore, ali koristiti fizičku kameru.

Virtualni hardver koristit će [CounterFit projekt](https://github.com/CounterFit-IoT/CounterFit).

Za dovršavanje ovih lekcija trebat će vam web kamera, mikrofon i audio izlaz poput zvučnika ili slušalica. Oni mogu biti ugrađeni ili vanjski, i trebaju biti konfigurirani da rade s vašim operativnim sustavom te dostupni za korištenje u svim aplikacijama.

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.