<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-27T21:06:43+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "sv"
}
-->
# Konfigurera din mikrofon och högtalare - Raspberry Pi

I denna del av lektionen kommer du att lägga till en mikrofon och högtalare till din Raspberry Pi.

## Hårdvara

Raspberry Pi behöver en mikrofon.

Pi har ingen inbyggd mikrofon, så du måste lägga till en extern mikrofon. Det finns flera sätt att göra detta:

* USB-mikrofon
* USB-headset
* USB allt-i-ett högtalartelefon
* USB-ljudadapter och mikrofon med 3,5 mm kontakt
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Bluetooth-mikrofoner stöds inte alltid på Raspberry Pi, så om du har en Bluetooth-mikrofon eller ett headset kan du stöta på problem med att ansluta eller spela in ljud.

Raspberry Pi har en 3,5 mm hörlursutgång. Du kan använda denna för att ansluta hörlurar, ett headset eller en högtalare. Du kan också lägga till högtalare med hjälp av:

* HDMI-ljud via en monitor eller TV
* USB-högtalare
* USB-headset
* USB allt-i-ett högtalartelefon
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) med en högtalare ansluten, antingen till 3,5 mm-utgången eller JST-porten

## Anslut och konfigurera mikrofonen och högtalarna

Mikrofonen och högtalarna måste anslutas och konfigureras.

### Uppgift - anslut och konfigurera mikrofonen

1. Anslut mikrofonen med lämplig metod. Till exempel, anslut den via en av USB-portarna.

1. Om du använder ReSpeaker 2-Mics Pi HAT kan du ta bort Grove-bas-hatten och sedan sätta ReSpeaker-hatten på plats.

    ![En Raspberry Pi med en ReSpeaker-hatt](../../../../../translated_images/sv/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Du kommer att behöva en Grove-knapp senare i denna lektion, men en sådan är inbyggd i denna hatt, så Grove-bas-hatten behövs inte.

    När hatten är monterad måste du installera några drivrutiner. Se [Seeeds kom igång-instruktioner](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) för instruktioner om drivrutinsinstallation.

    > ⚠️ Instruktionerna använder `git` för att klona ett repository. Om du inte har `git` installerat på din Pi kan du installera det genom att köra följande kommando:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Kör följande kommando i din terminal, antingen på Pi eller ansluten via VS Code och en fjärr-SSH-session, för att se information om den anslutna mikrofonen:

    ```sh
    arecord -l
    ```

    Du kommer att se en lista över anslutna mikrofoner. Det kommer att se ut ungefär så här:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Om du bara har en mikrofon bör du bara se en post. Konfiguration av mikrofoner kan vara knepigt på Linux, så det är enklast att bara använda en mikrofon och koppla bort eventuella andra.

    Notera kortnumret, eftersom du kommer att behöva detta senare. I ovanstående output är kortnumret 1.

### Uppgift - anslut och konfigurera högtalaren

1. Anslut högtalarna med lämplig metod.

1. Kör följande kommando i din terminal, antingen på Pi eller ansluten via VS Code och en fjärr-SSH-session, för att se information om de anslutna högtalarna:

    ```sh
    aplay -l
    ```

    Du kommer att se en lista över anslutna högtalare. Det kommer att se ut ungefär så här:

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

    Du kommer alltid att se `card 0: Headphones` eftersom detta är den inbyggda hörlursutgången. Om du har lagt till ytterligare högtalare, såsom en USB-högtalare, kommer detta också att listas.

1. Om du använder en extra högtalare och inte en högtalare eller hörlurar anslutna till den inbyggda hörlursutgången, måste du konfigurera den som standard. För att göra detta, kör följande kommando:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Detta öppnar en konfigurationsfil i `nano`, en terminalbaserad textredigerare. Scrolla ner med piltangenterna på ditt tangentbord tills du hittar följande rad:

    ```output
    defaults.pcm.card 0
    ```

    Ändra värdet från `0` till kortnumret för det kort du vill använda från listan som kom tillbaka från kommandot `aplay -l`. Till exempel, i ovanstående output finns det ett andra ljudkort kallat `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, som använder kort 1. För att använda detta skulle jag uppdatera raden till:

    ```output
    defaults.pcm.card 1
    ```

    Ställ in detta värde till det lämpliga kortnumret. Du kan navigera till numret med piltangenterna på ditt tangentbord, sedan radera och skriva det nya numret som vanligt när du redigerar textfiler.

1. Spara ändringarna och stäng filen genom att trycka på `Ctrl+x`. Tryck på `y` för att spara filen och sedan `return` för att välja filnamnet.

### Uppgift - testa mikrofonen och högtalaren

1. Kör följande kommando för att spela in 5 sekunder av ljud via mikrofonen:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Medan detta kommando körs, gör ljud i mikrofonen, till exempel genom att prata, sjunga, beatboxa, spela ett instrument eller vad du än känner för.

1. Efter 5 sekunder kommer inspelningen att stoppas. Kör följande kommando för att spela upp ljudet:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Du kommer att höra ljudet spelas upp via högtalarna. Justera volymen på din högtalare vid behov.

1. Om du behöver justera volymen på den inbyggda mikrofonporten eller justera mikrofonens förstärkning kan du använda verktyget `alsamixer`. Du kan läsa mer om detta verktyg på [Linux alsamixer man-sidan](https://linux.die.net/man/1/alsamixer).

1. Om du får fel vid uppspelning av ljudet, kontrollera kortet du ställde in som `defaults.pcm.card` i `alsa.conf`-filen.

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.