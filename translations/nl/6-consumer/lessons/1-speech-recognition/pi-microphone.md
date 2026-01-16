<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-27T22:41:23+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "nl"
}
-->
# Configureer je microfoon en luidsprekers - Raspberry Pi

In dit deel van de les voeg je een microfoon en luidsprekers toe aan je Raspberry Pi.

## Hardware

De Raspberry Pi heeft een microfoon nodig.

De Pi heeft geen ingebouwde microfoon, dus je moet een externe microfoon toevoegen. Er zijn meerdere manieren om dit te doen:

* USB-microfoon  
* USB-headset  
* USB alles-in-één speakerphone  
* USB-audioadapter en microfoon met een 3,5mm jack  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)  

> 💁 Bluetooth-microfoons worden niet allemaal ondersteund op de Raspberry Pi. Als je een Bluetooth-microfoon of -headset hebt, kun je problemen ondervinden bij het koppelen of opnemen van audio.

Raspberry Pi's hebben een 3,5mm koptelefoonaansluiting. Je kunt deze gebruiken om een koptelefoon, headset of luidspreker aan te sluiten. Je kunt ook luidsprekers toevoegen via:

* HDMI-audio via een monitor of tv  
* USB-luidsprekers  
* USB-headset  
* USB alles-in-één speakerphone  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) met een aangesloten luidspreker, via de 3,5mm jack of de JST-poort  

## Verbind en configureer de microfoon en luidsprekers

De microfoon en luidsprekers moeten worden aangesloten en geconfigureerd.

### Taak - verbind en configureer de microfoon

1. Verbind de microfoon met de juiste methode. Bijvoorbeeld door deze aan te sluiten op een van de USB-poorten.

1. Als je de ReSpeaker 2-Mics Pi HAT gebruikt, kun je de Grove-basisplaat verwijderen en de ReSpeaker-plaat op zijn plaats zetten.

    ![Een Raspberry Pi met een ReSpeaker-plaat](../../../../../translated_images/nl/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Later in deze les heb je een Grove-knop nodig, maar er is er al een ingebouwd in deze plaat, dus de Grove-basisplaat is niet nodig.

    Zodra de plaat is bevestigd, moet je enkele stuurprogramma's installeren. Raadpleeg de [Seeed startgids](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) voor instructies over het installeren van de stuurprogramma's.

    > ⚠️ De instructies gebruiken `git` om een repository te klonen. Als je `git` niet op je Pi hebt geïnstalleerd, kun je dit doen door het volgende commando uit te voeren:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Voer het volgende commando uit in je Terminal, op de Pi of via een externe SSH-sessie met VS Code, om informatie te zien over de aangesloten microfoon:

    ```sh
    arecord -l
    ```

    Je ziet een lijst met aangesloten microfoons. Het zal er ongeveer zo uitzien:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Als je slechts één microfoon hebt, zou je maar één vermelding moeten zien. Het configureren van microfoons kan lastig zijn op Linux, dus het is het eenvoudigst om slechts één microfoon te gebruiken en eventuele andere los te koppelen.

    Noteer het kaartnummer, want je hebt dit later nodig. In de bovenstaande uitvoer is het kaartnummer 1.

### Taak - verbind en configureer de luidspreker

1. Verbind de luidsprekers met de juiste methode.

1. Voer het volgende commando uit in je Terminal, op de Pi of via een externe SSH-sessie met VS Code, om informatie te zien over de aangesloten luidsprekers:

    ```sh
    aplay -l
    ```

    Je ziet een lijst met aangesloten luidsprekers. Het zal er ongeveer zo uitzien:

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Je zult altijd `card 0: Headphones` zien, omdat dit de ingebouwde koptelefoonaansluiting is. Als je extra luidsprekers hebt toegevoegd, zoals een USB-luidspreker, wordt deze ook vermeld.

1. Als je een extra luidspreker gebruikt, en niet een luidspreker of koptelefoon die is aangesloten op de ingebouwde koptelefoonaansluiting, moet je deze als standaard instellen. Voer hiervoor het volgende commando uit:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Dit opent een configuratiebestand in `nano`, een terminalgebaseerde teksteditor. Scroll naar beneden met de pijltjestoetsen op je toetsenbord totdat je de volgende regel vindt:

    ```output
    defaults.pcm.card 0
    ```

    Verander de waarde van `0` naar het kaartnummer van de kaart die je wilt gebruiken uit de lijst die terugkwam van de oproep naar `aplay -l`. Bijvoorbeeld, in de bovenstaande uitvoer is er een tweede geluidskaart genaamd `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, die kaart 1 gebruikt. Om deze te gebruiken, zou ik de regel bijwerken naar:

    ```output
    defaults.pcm.card 1
    ```

    Stel deze waarde in op het juiste kaartnummer. Je kunt naar het nummer navigeren met de pijltjestoetsen op je toetsenbord, en vervolgens het oude nummer verwijderen en het nieuwe typen zoals je normaal tekstbestanden bewerkt.

1. Sla de wijzigingen op en sluit het bestand door `Ctrl+x` in te drukken. Druk op `y` om het bestand op te slaan, en vervolgens op `return` om de bestandsnaam te selecteren.

### Taak - test de microfoon en luidspreker

1. Voer het volgende commando uit om 5 seconden audio op te nemen via de microfoon:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Maak tijdens het uitvoeren van dit commando geluid in de microfoon, bijvoorbeeld door te praten, zingen, beatboxen, een instrument te spelen of wat je maar leuk vindt.

1. Na 5 seconden stopt de opname. Voer het volgende commando uit om de audio af te spelen:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Je hoort de audio die wordt afgespeeld via de luidsprekers. Pas het uitvoervolume van je luidspreker aan indien nodig.

1. Als je het volume van de ingebouwde microfoonaansluiting wilt aanpassen, of de versterking van de microfoon wilt wijzigen, kun je de `alsamixer`-hulpprogramma gebruiken. Je kunt meer lezen over dit hulpprogramma op de [Linux alsamixer man-pagina](https://linux.die.net/man/1/alsamixer).

1. Als je fouten krijgt bij het afspelen van de audio, controleer dan de kaart die je hebt ingesteld als `defaults.pcm.card` in het `alsa.conf`-bestand.

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor kritieke informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.