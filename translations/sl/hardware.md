<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-28T11:58:28+00:00",
  "source_file": "hardware.md",
  "language_code": "sl"
}
-->
# Strojna oprema

**T** v IoT pomeni **Things** (stvari) in se nanaša na naprave, ki komunicirajo z okolico. Vsak projekt temelji na resnični strojni opremi, ki je na voljo študentom in ljubiteljem. Na voljo imamo dve možnosti IoT strojne opreme, ki ju lahko uporabimo glede na osebne preference, znanje programskih jezikov, učne cilje in dostopnost. Za tiste, ki nimajo dostopa do strojne opreme ali želijo izvedeti več, preden se odločijo za nakup, smo pripravili tudi različico 'virtualne strojne opreme'.

> 💁 Za dokončanje nalog ni potrebno kupiti IoT strojne opreme. Vse lahko opravite z uporabo virtualne IoT strojne opreme.

Fizične možnosti strojne opreme so Arduino ali Raspberry Pi. Vsaka platforma ima svoje prednosti in slabosti, ki so obravnavane v eni od uvodnih lekcij. Če še niste izbrali strojne platforme, si lahko ogledate [drugo lekcijo prvega projekta](./1-getting-started/lessons/2-deeper-dive/README.md), da se odločite, katera platforma vas najbolj zanima.

Specifična strojna oprema je bila izbrana za zmanjšanje kompleksnosti lekcij in nalog. Čeprav lahko deluje tudi druga strojna oprema, ne moremo zagotoviti, da bodo vse naloge podprte na vaši napravi brez dodatne strojne opreme. Na primer, veliko naprav Arduino nima WiFi-ja, ki je potreben za povezavo v oblak - Wio terminal je bil izbran, ker ima vgrajen WiFi.

Poleg tega boste potrebovali nekaj netehničnih predmetov, kot so zemlja ali lončnica ter sadje ali zelenjava.

## Nakup kompletov

![Logotip Seeed Studios](../../translated_images/seeed-logo.74732b6b482b6e8e.sl.png)

Seeed Studios so prijazno omogočili nakup vse strojne opreme v obliki enostavnih kompletov:

### Arduino - Wio Terminal

**[IoT za začetnike s Seeed in Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Komplet strojne opreme Wio Terminal](../../translated_images/wio-hardware-kit.4c70c48b85e4283a.sl.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT za začetnike s Seeed in Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Komplet strojne opreme Raspberry Pi Terminal](../../translated_images/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.sl.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Vsa koda za naprave Arduino je napisana v C++. Za dokončanje vseh nalog boste potrebovali naslednje:

### Strojna oprema Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Opcijsko* - USB-C kabel ali USB-A na USB-C adapter. Wio terminal ima USB-C priključek in je priložen USB-C na USB-A kabel. Če vaš PC ali Mac ima samo USB-C priključke, boste potrebovali USB-C kabel ali USB-A na USB-C adapter.

### Specifični senzorji in aktuatorji za Arduino

Ti so specifični za uporabo naprave Wio terminal Arduino in niso relevantni za uporabo Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Slušalke ali drugi zvočnik s 3,5 mm priključkom ali JST zvočnik, kot je:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD kartica 16GB ali manj, skupaj s priključkom za uporabo SD kartice z računalnikom, če ga nimate vgrajenega. **NOTE** - Wio Terminal podpira le SD kartice do 16GB, večje kapacitete niso podprte.

## Raspberry Pi

Vsa koda za naprave Raspberry Pi je napisana v Pythonu. Za dokončanje vseh nalog boste potrebovali naslednje:

### Strojna oprema Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Verzije od Pi 2B naprej bi morale delovati z nalogami v teh lekcijah. Če nameravate uporabljati VS Code neposredno na Pi, potem potrebujete Pi 4 z 2GB ali več RAM-a. Če boste dostopali do Pi na daljavo, bo deloval kateri koli Pi 2B ali novejši.
* microSD kartica (Raspberry Pi kompleti pogosto vključujejo microSD kartico), skupaj s priključkom za uporabo SD kartice z računalnikom, če ga nimate vgrajenega.
* USB napajalnik (Raspberry Pi 4 kompleti pogosto vključujejo napajalnik). Če uporabljate Raspberry Pi 4, potrebujete USB-C napajalnik, starejše naprave pa potrebujejo micro-USB napajalnik.

### Specifični senzorji in aktuatorji za Raspberry Pi

Ti so specifični za uporabo Raspberry Pi in niso relevantni za uporabo naprave Arduino.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi Camera module](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofon in zvočnik:

  Uporabite eno od naslednjih možnosti (ali ekvivalent):
  * Kateri koli USB mikrofon z USB zvočnikom ali zvočnikom s 3,5 mm priključkom, ali HDMI avdio izhod, če je vaš Raspberry Pi povezan z monitorjem ali TV-jem z zvočniki
  * Kateri koli USB slušalke z vgrajenim mikrofonom
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) z
    * Slušalke ali drugi zvočnik s 3,5 mm priključkom ali JST zvočnik, kot je:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove Light sensor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove button](https://www.seeedstudio.com/Grove-Button.html)

## Senzorji in aktuatorji

Večina senzorjev in aktuatorjev, ki jih potrebujete, se uporablja tako pri Arduino kot Raspberry Pi učnih poteh:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove senzor vlage in temperature](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove kapacitivni senzor vlage v tleh](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove rele](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove senzor razdalje Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Opcijska strojna oprema

Lekcije o avtomatiziranem zalivanju delujejo z uporabo releja. Kot opcijo lahko ta rele povežete z vodno črpalko, ki jo napaja USB, z uporabo spodaj navedene strojne opreme.

* [6V vodna črpalka](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB terminal](https://www.adafruit.com/product/3628)
* Silikonske cevi
* Rdeče in črne žice
* Majhen izvijač z ravno glavo

## Virtualna strojna oprema

Virtualna strojna oprema bo zagotovila simulatorje za senzorje in aktuatorje, implementirane v Pythonu. Glede na vašo razpoložljivost strojne opreme lahko to zaženete na vaši običajni razvojni napravi, kot je Mac, PC, ali na Raspberry Pi in simulirate samo strojno opremo, ki je nimate. Na primer, če imate Raspberry Pi kamero, vendar ne Grove senzorjev, boste lahko zagnali kodo virtualne naprave na vašem Pi in simulirali Grove senzorje, medtem ko uporabljate fizično kamero.

Virtualna strojna oprema bo uporabljala [CounterFit projekt](https://github.com/CounterFit-IoT/CounterFit).

Za dokončanje teh lekcij boste potrebovali spletno kamero, mikrofon in avdio izhod, kot so zvočniki ali slušalke. Ti lahko bodo vgrajeni ali zunanji, in morajo biti konfigurirani za delovanje z vašim operacijskim sistemom ter na voljo za uporabo v vseh aplikacijah.

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.