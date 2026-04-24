# Aparatūra

**T** IoT reiškia **Daiktus** ir nurodo įrenginius, kurie sąveikauja su aplinka aplink mus. Kiekvienas projektas yra pagrįstas realia aparatūra, prieinama studentams ir entuziastams. Turime du IoT aparatūros pasirinkimus, priklausomai nuo asmeninių pageidavimų, programavimo kalbos žinių ar prioritetų, mokymosi tikslų ir prieinamumo. Taip pat pateikėme „virtualios aparatūros“ versiją tiems, kurie neturi prieigos prie fizinės aparatūros arba nori daugiau sužinoti prieš įsigydami.

> 💁 Jums nereikia pirkti jokios IoT aparatūros, kad atliktumėte užduotis. Viską galite atlikti naudodami virtualią IoT aparatūrą.

Fizinės aparatūros pasirinkimai yra Arduino arba Raspberry Pi. Kiekviena platforma turi savo privalumų ir trūkumų, kurie aptariami vienoje iš pradinės pamokos dalių. Jei dar neapsisprendėte dėl aparatūros platformos, galite peržiūrėti [antrąją pirmojo projekto pamoką](./1-getting-started/lessons/2-deeper-dive/README.md), kad nuspręstumėte, kuri platforma jus labiausiai domina.

Konkreti aparatūra buvo pasirinkta siekiant sumažinti pamokų ir užduočių sudėtingumą. Nors kita aparatūra gali veikti, negalime garantuoti, kad visos užduotys bus palaikomos jūsų įrenginyje be papildomos aparatūros. Pavyzdžiui, daugelis Arduino įrenginių neturi WiFi, kuris reikalingas prisijungimui prie debesies – Wio terminalas buvo pasirinktas, nes turi integruotą WiFi.

Jums taip pat reikės kelių ne techninių daiktų, tokių kaip dirvožemis ar vazoninis augalas, vaisiai ar daržovės.

## Įsigykite rinkinius

![Seeed Studios logotipas](../../translated_images/lt/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios labai maloniai pateikė visą aparatūrą kaip lengvai įsigyjamus rinkinius:

### Arduino - Wio Terminal

**[IoT pradedantiesiems su Seeed ir Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio Terminal aparatūros rinkinys](../../translated_images/lt/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT pradedantiesiems su Seeed ir Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi Terminal aparatūros rinkinys](../../translated_images/lt/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Visa Arduino įrenginių kodas yra parašytas C++. Norėdami atlikti visas užduotis, jums reikės šių dalykų:

### Arduino aparatūra

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Pasirinktinai* - USB-C kabelis arba USB-A į USB-C adapteris. Wio terminalas turi USB-C jungtį ir yra komplektuojamas su USB-C į USB-A kabeliu. Jei jūsų kompiuteryje ar Mac'e yra tik USB-C jungtys, jums reikės USB-C kabelio arba USB-A į USB-C adapterio.

### Arduino specifiniai jutikliai ir aktuatoriai

Šie komponentai yra specifiniai naudojant Wio terminalą su Arduino ir nėra aktualūs naudojant Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Ausinės arba kiti garsiakalbiai su 3.5mm jungtimi, arba JST garsiakalbis, pvz.:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD kortelė iki 16GB, kartu su jungtimi kortelės naudojimui kompiuteryje, jei neturite integruotos jungties. **PASTABA** - Wio Terminal palaiko tik SD korteles iki 16GB, didesnės talpos kortelės nepalaikomos.

## Raspberry Pi

Visa Raspberry Pi įrenginių kodas yra parašytas Python. Norėdami atlikti visas užduotis, jums reikės šių dalykų:

### Raspberry Pi aparatūra

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Versijos nuo Pi 2B ir naujesnės turėtų veikti su užduotimis šiose pamokose. Jei planuojate naudoti VS Code tiesiogiai Pi įrenginyje, tada reikalingas Pi 4 su 2GB ar daugiau RAM. Jei ketinate pasiekti Pi nuotoliniu būdu, bet kuris Pi 2B ir naujesnis veiks.
* microSD kortelė (Galite įsigyti Raspberry Pi rinkinius, kurie jau turi microSD kortelę), kartu su jungtimi kortelės naudojimui kompiuteryje, jei neturite integruotos jungties.
* USB maitinimo šaltinis (Galite įsigyti Raspberry Pi 4 rinkinius, kurie jau turi maitinimo šaltinį). Jei naudojate Raspberry Pi 4, jums reikės USB-C maitinimo šaltinio, ankstesniems įrenginiams reikalingas micro-USB maitinimo šaltinis.

### Raspberry Pi specifiniai jutikliai ir aktuatoriai

Šie komponentai yra specifiniai naudojant Raspberry Pi ir nėra aktualūs naudojant Arduino įrenginį.

* [Grove Pi bazinis HAT](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi kameros modulis](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofonas ir garsiakalbis:

  Naudokite vieną iš šių (arba ekvivalentą):
  * Bet kuris USB mikrofonas su bet kuriuo USB garsiakalbiu arba garsiakalbiu su 3.5mm jungtimi, arba HDMI garso išvestimi, jei jūsų Raspberry Pi prijungtas prie monitoriaus ar televizoriaus su garsiakalbiais
  * Bet kurios USB ausinės su integruotu mikrofonu
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) su
    * Ausinėmis arba kitais garsiakalbiais su 3.5mm jungtimi, arba JST garsiakalbiu, pvz.:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove šviesos jutiklis](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove mygtukas](https://www.seeedstudio.com/Grove-Button.html)

## Jutikliai ir aktuatoriai

Dauguma jutiklių ir aktuatorių, reikalingų, yra naudojami tiek Arduino, tiek Raspberry Pi mokymosi keliuose:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove drėgmės ir temperatūros jutiklis](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove talpinis dirvožemio drėgmės jutiklis](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove relė](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove atstumo jutiklis](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Pasirinktinė aparatūra

Pamokos apie automatizuotą laistymą veikia naudojant relę. Kaip pasirinkimą, galite prijungti šią relę prie USB maitinamo vandens siurblio, naudodami žemiau išvardytą aparatūrą.

* [6V vandens siurblys](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB terminalas](https://www.adafruit.com/product/3628)
* Silikoniniai vamzdeliai
* Raudoni ir juodi laidai
* Mažas plokščias atsuktuvas

## Virtuali aparatūra

Virtualios aparatūros maršrutas suteiks jutiklių ir aktuatorių simuliatorius, įgyvendintus Python. Priklausomai nuo jūsų aparatūros prieinamumo, galite tai paleisti savo įprastame kūrimo įrenginyje, pvz., Mac, PC, arba paleisti Raspberry Pi ir simuliuoti tik tą aparatūrą, kurios neturite. Pavyzdžiui, jei turite Raspberry Pi kamerą, bet neturite Grove jutiklių, galėsite paleisti virtualų įrenginio kodą savo Pi ir simuliuoti Grove jutiklius, bet naudoti fizinę kamerą.

Virtuali aparatūra naudos [CounterFit projektą](https://github.com/CounterFit-IoT/CounterFit).

Norėdami atlikti šias pamokas, jums reikės internetinės kameros, mikrofono ir garso išvesties, pvz., garsiakalbių ar ausinių. Jie gali būti integruoti arba išoriniai ir turi būti sukonfigūruoti veikti su jūsų operacine sistema bei būti prieinami visoms programoms.

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.