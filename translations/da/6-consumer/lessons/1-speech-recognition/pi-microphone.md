<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-27T21:07:02+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "da"
}
-->
# Konfigurer din mikrofon og dine højttalere - Raspberry Pi

I denne del af lektionen vil du tilføje en mikrofon og højttalere til din Raspberry Pi.

## Hardware

Raspberry Pi har brug for en mikrofon.

Pi'en har ikke en indbygget mikrofon, så du skal tilføje en ekstern mikrofon. Der er flere måder at gøre dette på:

* USB-mikrofon
* USB-headset
* USB alt-i-en speakerphone
* USB-lydadapter og mikrofon med en 3,5 mm jack
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Bluetooth-mikrofoner understøttes ikke alle på Raspberry Pi, så hvis du har en Bluetooth-mikrofon eller et headset, kan du opleve problemer med at parre eller optage lyd.

Raspberry Pi'er har en 3,5 mm hovedtelefonudgang. Du kan bruge denne til at tilslutte hovedtelefoner, et headset eller en højttaler. Du kan også tilføje højttalere ved hjælp af:

* HDMI-lyd via en skærm eller et TV
* USB-højttalere
* USB-headset
* USB alt-i-en speakerphone
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) med en tilsluttet højttaler, enten til 3,5 mm jackstikket eller JST-porten

## Tilslut og konfigurer mikrofonen og højttalerne

Mikrofonen og højttalerne skal tilsluttes og konfigureres.

### Opgave - tilslut og konfigurer mikrofonen

1. Tilslut mikrofonen ved hjælp af den passende metode. For eksempel, tilslut den via en af USB-portene.

1. Hvis du bruger ReSpeaker 2-Mics Pi HAT, kan du fjerne Grove-basen og derefter montere ReSpeaker-hatten i stedet.

    ![En Raspberry Pi med en ReSpeaker-hat](../../../../../translated_images/da/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Du får brug for en Grove-knap senere i denne lektion, men en er indbygget i denne hat, så Grove-basen er ikke nødvendig.

    Når hatten er monteret, skal du installere nogle drivere. Se [Seeeds introduktionsvejledning](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) for instruktioner om installation af drivere.

    > ⚠️ Instruktionerne bruger `git` til at klone et repository. Hvis du ikke har `git` installeret på din Pi, kan du installere det ved at køre følgende kommando:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Kør følgende kommando i din Terminal enten på Pi'en eller via en fjern-SSH-session i VS Code for at se information om den tilsluttede mikrofon:

    ```sh
    arecord -l
    ```

    Du vil se en liste over tilsluttede mikrofoner. Det vil se nogenlunde sådan ud:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Hvis du kun har én mikrofon, bør du kun se én post. Konfiguration af mikrofoner kan være kompliceret på Linux, så det er nemmest kun at bruge én mikrofon og frakoble eventuelle andre.

    Notér kortnummeret, da du får brug for det senere. I outputtet ovenfor er kortnummeret 1.

### Opgave - tilslut og konfigurer højttaleren

1. Tilslut højttalerne ved hjælp af den passende metode.

1. Kør følgende kommando i din Terminal enten på Pi'en eller via en fjern-SSH-session i VS Code for at se information om de tilsluttede højttalere:

    ```sh
    aplay -l
    ```

    Du vil se en liste over tilsluttede højttalere. Det vil se nogenlunde sådan ud:

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

    Du vil altid se `card 0: Headphones`, da dette er den indbyggede hovedtelefonudgang. Hvis du har tilføjet ekstra højttalere, såsom en USB-højttaler, vil dette også blive vist.

1. Hvis du bruger en ekstra højttaler og ikke en højttaler eller hovedtelefoner tilsluttet den indbyggede hovedtelefonudgang, skal du konfigurere den som standard. For at gøre dette skal du køre følgende kommando:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Dette åbner en konfigurationsfil i `nano`, en terminalbaseret teksteditor. Rul ned ved hjælp af piletasterne på dit tastatur, indtil du finder følgende linje:

    ```output
    defaults.pcm.card 0
    ```

    Ændr værdien fra `0` til kortnummeret for det kort, du vil bruge, fra listen, der kom tilbage fra kaldet til `aplay -l`. For eksempel, i outputtet ovenfor er der et andet lydkort kaldet `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, som bruger kort 1. For at bruge dette ville jeg opdatere linjen til:

    ```output
    defaults.pcm.card 1
    ```

    Indstil denne værdi til det passende kortnummer. Du kan navigere til nummeret ved hjælp af piletasterne på dit tastatur og derefter slette og skrive det nye nummer som normalt, når du redigerer tekstfiler.

1. Gem ændringerne og luk filen ved at trykke på `Ctrl+x`. Tryk på `y` for at gemme filen, og derefter `return` for at vælge filnavnet.

### Opgave - test mikrofonen og højttaleren

1. Kør følgende kommando for at optage 5 sekunders lyd gennem mikrofonen:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Mens denne kommando kører, skal du lave støj i mikrofonen, f.eks. ved at tale, synge, beatboxe, spille et instrument eller hvad du nu har lyst til.

1. Efter 5 sekunder stopper optagelsen. Kør følgende kommando for at afspille lyden:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Du vil høre lyden blive afspillet gennem højttalerne. Juster lydstyrken på din højttaler efter behov.

1. Hvis du har brug for at justere lydstyrken på den indbyggede mikrofonport eller justere mikrofonens forstærkning, kan du bruge værktøjet `alsamixer`. Du kan læse mere om dette værktøj på [Linux alsamixer man-siden](https://linux.die.net/man/1/alsamixer).

1. Hvis du får fejl ved afspilning af lyden, skal du kontrollere det kort, du har indstillet som `defaults.pcm.card` i `alsa.conf`-filen.

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.