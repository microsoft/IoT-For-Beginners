# Hardware

**T** din IoT reprezintă **Things** (Lucruri) și se referă la dispozitivele care interacționează cu lumea din jurul nostru. Fiecare proiect este bazat pe hardware real, disponibil pentru studenți și pasionați. Avem două opțiuni de hardware IoT pe care le putem folosi, în funcție de preferințele personale, cunoștințele sau preferințele legate de limbajul de programare, obiectivele de învățare și disponibilitate. De asemenea, am oferit o versiune de 'hardware virtual' pentru cei care nu au acces la hardware sau doresc să învețe mai multe înainte de a face o achiziție.

> 💁 Nu este necesar să achiziționați hardware IoT pentru a finaliza temele. Puteți face totul folosind hardware IoT virtual.

Opțiunile de hardware fizic sunt Arduino sau Raspberry Pi. Fiecare platformă are avantajele și dezavantajele sale, iar acestea sunt acoperite în una dintre lecțiile inițiale. Dacă nu ați decis deja asupra unei platforme hardware, puteți consulta [lecția a doua din primul proiect](./1-getting-started/lessons/2-deeper-dive/README.md) pentru a decide care platformă hardware vă interesează cel mai mult.

Hardware-ul specific a fost ales pentru a reduce complexitatea lecțiilor și temelor. Deși alte dispozitive hardware pot funcționa, nu putem garanta că toate temele vor fi compatibile cu dispozitivul dumneavoastră fără hardware suplimentar. De exemplu, multe dispozitive Arduino nu au WiFi, care este necesar pentru a se conecta la cloud - terminalul Wio a fost ales deoarece are WiFi integrat.

De asemenea, veți avea nevoie de câteva obiecte non-tehnice, cum ar fi sol sau o plantă în ghiveci, și fructe sau legume.

## Cumpărați kiturile

![Logo-ul Seeed Studios](../../translated_images/ro/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios a făcut foarte ușor accesibile toate componentele hardware, oferindu-le sub formă de kituri ușor de achiziționat:

### Arduino - Wio Terminal

**[IoT pentru începători cu Seeed și Microsoft - Kit de start Wio Terminal](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Kitul hardware Wio Terminal](../../translated_images/ro/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT pentru începători cu Seeed și Microsoft - Kit de start Raspberry Pi 4](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Kitul hardware Raspberry Pi Terminal](../../translated_images/ro/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Toate codurile pentru dispozitivele Arduino sunt scrise în C++. Pentru a finaliza toate temele, veți avea nevoie de următoarele:

### Hardware Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Opțional* - Cablu USB-C sau adaptor USB-A la USB-C. Terminalul Wio are un port USB-C și vine cu un cablu USB-C la USB-A. Dacă PC-ul sau Mac-ul dumneavoastră are doar porturi USB-C, veți avea nevoie de un cablu USB-C sau un adaptor USB-A la USB-C.

### Senzori și actuatori specifici pentru Arduino

Aceștia sunt specifici dispozitivului Arduino Wio Terminal și nu sunt relevanți pentru utilizarea Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Fire de conexiune pentru breadboard](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Căști sau alt difuzor cu mufă de 3,5 mm, sau un difuzor JST, cum ar fi:
  * [Difuzor mono închis - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* Card microSD de 16GB sau mai mic, împreună cu un conector pentru a utiliza cardul SD cu computerul, dacă acesta nu are unul integrat. **NOTĂ** - Terminalul Wio acceptă doar carduri SD de până la 16GB, nu acceptă capacități mai mari.

## Raspberry Pi

Toate codurile pentru dispozitivele Raspberry Pi sunt scrise în Python. Pentru a finaliza toate temele, veți avea nevoie de următoarele:

### Hardware Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Versiunile de la Pi 2B în sus ar trebui să funcționeze cu temele din aceste lecții. Dacă intenționați să rulați VS Code direct pe Pi, atunci este necesar un Pi 4 cu 2GB sau mai mult de RAM. Dacă veți accesa Pi-ul de la distanță, orice Pi 2B sau mai nou va funcționa.
* Card microSD (Puteți achiziționa kituri Raspberry Pi care includ un card microSD), împreună cu un conector pentru a utiliza cardul SD cu computerul, dacă acesta nu are unul integrat.
* Alimentare USB (Puteți achiziționa kituri Raspberry Pi 4 care includ o sursă de alimentare). Dacă utilizați un Raspberry Pi 4, aveți nevoie de o sursă de alimentare USB-C, iar dispozitivele mai vechi necesită o sursă de alimentare micro-USB.

### Senzori și actuatori specifici pentru Raspberry Pi

Aceștia sunt specifici utilizării Raspberry Pi și nu sunt relevanți pentru dispozitivul Arduino.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Modul cameră Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* Microfon și difuzor:

  Utilizați una dintre următoarele opțiuni (sau echivalente):
  * Orice microfon USB cu orice difuzor USB, sau difuzor cu cablu jack de 3,5 mm, sau utilizând ieșirea audio HDMI dacă Raspberry Pi-ul este conectat la un monitor sau TV cu difuzoare
  * Orice set de căști USB cu microfon integrat
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) cu
    * Căști sau alt difuzor cu mufă de 3,5 mm, sau un difuzor JST, cum ar fi:
    * [Difuzor mono închis - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [Difuzor USB pentru conferințe](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Senzor de lumină Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Buton Grove](https://www.seeedstudio.com/Grove-Button.html)

## Senzori și actuatori

Majoritatea senzorilor și actuatorilor necesari sunt utilizați atât pentru traseele de învățare Arduino, cât și pentru Raspberry Pi:

* [LED Grove](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Senzor de umiditate și temperatură Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Senzor capacitiv de umiditate a solului Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Releu Grove](https://www.seeedstudio.com/Grove-Relay.html)
* [GPS Grove (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Senzor de distanță Time of Flight Grove](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Hardware opțional

Lecțiile despre udarea automată funcționează utilizând un releu. Opțional, puteți conecta acest releu la o pompă de apă alimentată prin USB, utilizând hardware-ul listat mai jos.

* [Pompă de apă 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [Terminal USB](https://www.adafruit.com/product/3628)
* Tuburi de silicon
* Fire roșii și negre
* Șurubelniță mică cu cap plat

## Hardware virtual

Ruta hardware-ului virtual va oferi simulatoare pentru senzori și actuatori, implementate în Python. În funcție de disponibilitatea hardware-ului, puteți rula acest lucru pe dispozitivul dumneavoastră obișnuit de dezvoltare, cum ar fi un Mac, PC, sau îl puteți rula pe un Raspberry Pi și simula doar hardware-ul pe care nu îl aveți. De exemplu, dacă aveți camera Raspberry Pi, dar nu și senzorii Grove, veți putea rula codul dispozitivului virtual pe Pi și simula senzorii Grove, dar utiliza o cameră fizică.

Hardware-ul virtual va utiliza proiectul [CounterFit](https://github.com/CounterFit-IoT/CounterFit).

Pentru a finaliza aceste lecții, veți avea nevoie de o cameră web, microfon și ieșire audio, cum ar fi difuzoare sau căști. Acestea pot fi integrate sau externe și trebuie configurate pentru a funcționa cu sistemul de operare și disponibile pentru utilizare în toate aplicațiile.

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea realizată de un profesionist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.