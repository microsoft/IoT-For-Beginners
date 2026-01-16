<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-25T16:18:16+00:00",
  "source_file": "hardware.md",
  "language_code": "it"
}
-->
# Hardware

La **T** in IoT sta per **Things** e si riferisce ai dispositivi che interagiscono con il mondo che ci circonda. Ogni progetto si basa su hardware reale disponibile per studenti e appassionati. Abbiamo due opzioni di hardware IoT da utilizzare, a seconda delle preferenze personali, della conoscenza o preferenza del linguaggio di programmazione, degli obiettivi di apprendimento e della disponibilità. Abbiamo anche fornito una versione di 'hardware virtuale' per coloro che non hanno accesso all'hardware o vogliono imparare di più prima di impegnarsi in un acquisto.

> 💁 Non è necessario acquistare hardware IoT per completare gli esercizi. Puoi fare tutto utilizzando hardware IoT virtuale.

Le opzioni di hardware fisico sono Arduino o Raspberry Pi. Ogni piattaforma ha i suoi vantaggi e svantaggi, e questi sono tutti trattati in una delle lezioni iniziali. Se non hai ancora deciso quale piattaforma hardware utilizzare, puoi consultare [la lezione due del primo progetto](./1-getting-started/lessons/2-deeper-dive/README.md) per decidere quale piattaforma hardware ti interessa di più.

L'hardware specifico è stato scelto per ridurre la complessità delle lezioni e degli esercizi. Sebbene altri hardware possano funzionare, non possiamo garantire che tutti gli esercizi saranno supportati sul tuo dispositivo senza hardware aggiuntivo. Ad esempio, molti dispositivi Arduino non hanno il WiFi, che è necessario per connettersi al cloud - il terminale Wio è stato scelto perché ha il WiFi integrato.

Avrai anche bisogno di alcuni oggetti non tecnici, come terra o una pianta in vaso, e frutta o verdura.

## Acquista i kit

![Il logo di Seeed Studios](../../translated_images/it/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios ha gentilmente reso tutto l'hardware disponibile come kit facili da acquistare:

### Arduino - Wio Terminal

**[IoT per principianti con Seeed e Microsoft - Kit iniziale Wio Terminal](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Il kit hardware Wio Terminal](../../translated_images/it/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT per principianti con Seeed e Microsoft - Kit iniziale Raspberry Pi 4](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Il kit hardware Raspberry Pi Terminal](../../translated_images/it/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Tutto il codice per i dispositivi Arduino è scritto in C++. Per completare tutti gli esercizi avrai bisogno di quanto segue:

### Hardware Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Opzionale* - Cavo USB-C o adattatore USB-A a USB-C. Il terminale Wio ha una porta USB-C e viene fornito con un cavo USB-C a USB-A. Se il tuo PC o Mac ha solo porte USB-C, avrai bisogno di un cavo USB-C o di un adattatore USB-A a USB-C.

### Sensori e attuatori specifici per Arduino

Questi sono specifici per l'utilizzo del dispositivo Arduino Wio Terminal e non sono rilevanti per l'utilizzo del Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Cuffie o altro altoparlante con jack da 3,5 mm, o un altoparlante JST come:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* Scheda microSD da 16GB o meno, insieme a un connettore per utilizzare la scheda SD con il tuo computer se non ne hai uno integrato. **NOTA** - il terminale Wio supporta solo schede SD fino a 16GB, non supporta capacità superiori.

## Raspberry Pi

Tutto il codice per i dispositivi Raspberry Pi è scritto in Python. Per completare tutti gli esercizi avrai bisogno di quanto segue:

### Hardware Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Le versioni dal Pi 2B in poi dovrebbero funzionare con gli esercizi di queste lezioni. Se hai intenzione di eseguire VS Code direttamente sul Pi, allora è necessario un Pi 4 con 2GB o più di RAM. Se hai intenzione di accedere al Pi da remoto, qualsiasi Pi 2B e successivi funzioneranno.
* Scheda microSD (Puoi acquistare kit Raspberry Pi che includono una scheda microSD), insieme a un connettore per utilizzare la scheda SD con il tuo computer se non ne hai uno integrato.
* Alimentatore USB (Puoi acquistare kit Raspberry Pi 4 che includono un alimentatore). Se stai utilizzando un Raspberry Pi 4, hai bisogno di un alimentatore USB-C, mentre i dispositivi precedenti necessitano di un alimentatore micro-USB.

### Sensori e attuatori specifici per Raspberry Pi

Questi sono specifici per l'utilizzo del Raspberry Pi e non sono rilevanti per l'utilizzo del dispositivo Arduino.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Modulo fotocamera Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* Microfono e altoparlante:

  Usa uno dei seguenti (o equivalenti):
  * Qualsiasi microfono USB con qualsiasi altoparlante USB, o altoparlante con cavo jack da 3,5 mm, o utilizzo dell'uscita audio HDMI se il tuo Raspberry Pi è collegato a un monitor o TV con altoparlanti
  * Qualsiasi cuffia USB con microfono integrato
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) con
    * Cuffie o altro altoparlante con jack da 3,5 mm, o un altoparlante JST come:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Sensore di luce Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Pulsante Grove](https://www.seeedstudio.com/Grove-Button.html)

## Sensori e attuatori

La maggior parte dei sensori e attuatori necessari sono utilizzati sia dai percorsi di apprendimento Arduino che Raspberry Pi:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Sensore di umidità e temperatura Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Sensore capacitivo di umidità del suolo Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Relè Grove](https://www.seeedstudio.com/Grove-Relay.html)
* [GPS Grove (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Sensore di distanza Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Hardware opzionale

Le lezioni sull'irrigazione automatizzata funzionano utilizzando un relè. Come opzione, puoi collegare questo relè a una pompa dell'acqua alimentata tramite USB utilizzando l'hardware elencato di seguito.

* [Pompa dell'acqua 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [Terminale USB](https://www.adafruit.com/product/3628)
* Tubi in silicone
* Fili rossi e neri
* Cacciavite a testa piatta piccolo

## Hardware virtuale

Il percorso hardware virtuale fornirà simulatori per i sensori e gli attuatori, implementati in Python. A seconda della disponibilità del tuo hardware, puoi eseguirlo sul tuo normale dispositivo di sviluppo, come un Mac, PC, o eseguirlo su un Raspberry Pi e simulare solo l'hardware che non possiedi. Ad esempio, se hai la fotocamera Raspberry Pi ma non i sensori Grove, sarai in grado di eseguire il codice del dispositivo virtuale sul tuo Pi e simulare i sensori Grove, ma utilizzare una fotocamera fisica.

L'hardware virtuale utilizzerà il progetto [CounterFit](https://github.com/CounterFit-IoT/CounterFit).

Per completare queste lezioni, avrai bisogno di una webcam, un microfono e un'uscita audio come altoparlanti o cuffie. Questi possono essere integrati o esterni e devono essere configurati per funzionare con il tuo sistema operativo e disponibili per l'uso da tutte le applicazioni.

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale eseguita da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.