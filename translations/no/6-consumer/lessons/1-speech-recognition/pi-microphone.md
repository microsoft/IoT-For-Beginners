<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-27T21:07:25+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "no"
}
-->
# Konfigurer mikrofon og høyttalere - Raspberry Pi

I denne delen av leksjonen skal du legge til en mikrofon og høyttalere til din Raspberry Pi.

## Maskinvare

Raspberry Pi trenger en mikrofon.

Pi har ikke en innebygd mikrofon, så du må legge til en ekstern mikrofon. Det finnes flere måter å gjøre dette på:

* USB-mikrofon
* USB-headset
* USB alt-i-ett høyttalertelefon
* USB-lydadapter og mikrofon med 3,5 mm jack
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Bluetooth-mikrofoner støttes ikke fullt ut på Raspberry Pi, så hvis du har en Bluetooth-mikrofon eller et Bluetooth-headset, kan du oppleve problemer med paring eller lydopptak.

Raspberry Pi har en 3,5 mm hodetelefonutgang. Du kan bruke denne til å koble til hodetelefoner, et headset eller en høyttaler. Du kan også legge til høyttalere ved å bruke:

* HDMI-lyd gjennom en skjerm eller TV
* USB-høyttalere
* USB-headset
* USB alt-i-ett høyttalertelefon
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) med en høyttaler koblet til enten 3,5 mm jack eller JST-porten

## Koble til og konfigurer mikrofon og høyttalere

Mikrofonen og høyttalerne må kobles til og konfigureres.

### Oppgave - koble til og konfigurer mikrofonen

1. Koble til mikrofonen ved å bruke riktig metode. For eksempel, koble den til via en av USB-portene.

1. Hvis du bruker ReSpeaker 2-Mics Pi HAT, kan du fjerne Grove base-hatten og deretter sette ReSpeaker-hatten på plass.

    ![En Raspberry Pi med en ReSpeaker-hatt](../../../../../translated_images/no/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Du vil trenge en Grove-knapp senere i denne leksjonen, men en er innebygd i denne hatten, så Grove base-hatten er ikke nødvendig.

    Når hatten er montert, må du installere noen drivere. Se [Seeed sine oppstartsveiledninger](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) for instruksjoner om driverinstallasjon.

    > ⚠️ Instruksjonene bruker `git` for å klone et repository. Hvis du ikke har `git` installert på din Pi, kan du installere det ved å kjøre følgende kommando:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Kjør følgende kommando i Terminalen enten på Pi-en, eller koblet til via VS Code og en ekstern SSH-økt for å se informasjon om den tilkoblede mikrofonen:

    ```sh
    arecord -l
    ```

    Du vil se en liste over tilkoblede mikrofoner. Det vil se omtrent slik ut:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Forutsatt at du kun har én mikrofon, bør du bare se én oppføring. Konfigurasjon av mikrofoner kan være utfordrende på Linux, så det er enklest å bare bruke én mikrofon og koble fra eventuelle andre.

    Noter kortnummeret, da du vil trenge dette senere. I utdataene ovenfor er kortnummeret 1.

### Oppgave - koble til og konfigurer høyttaleren

1. Koble til høyttalerne ved å bruke riktig metode.

1. Kjør følgende kommando i Terminalen enten på Pi-en, eller koblet til via VS Code og en ekstern SSH-økt for å se informasjon om de tilkoblede høyttalerne:

    ```sh
    aplay -l
    ```

    Du vil se en liste over tilkoblede høyttalere. Det vil se omtrent slik ut:

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

    Du vil alltid se `card 0: Headphones`, da dette er den innebygde hodetelefonutgangen. Hvis du har lagt til ekstra høyttalere, som en USB-høyttaler, vil dette også vises i listen.

1. Hvis du bruker en ekstra høyttaler, og ikke en høyttaler eller hodetelefoner koblet til den innebygde hodetelefonutgangen, må du konfigurere den som standard. For å gjøre dette, kjør følgende kommando:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Dette vil åpne en konfigurasjonsfil i `nano`, en terminalbasert teksteditor. Rull nedover ved å bruke piltastene på tastaturet til du finner følgende linje:

    ```output
    defaults.pcm.card 0
    ```

    Endre verdien fra `0` til kortnummeret til kortet du vil bruke fra listen som kom tilbake fra kommandoen `aplay -l`. For eksempel, i utdataene ovenfor er det et andre lydkort kalt `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, som bruker kort 1. For å bruke dette, ville jeg oppdatert linjen til:

    ```output
    defaults.pcm.card 1
    ```

    Sett denne verdien til riktig kortnummer. Du kan navigere til nummeret ved å bruke piltastene på tastaturet, deretter slette og skrive inn det nye nummeret som normalt når du redigerer tekstfiler.

1. Lagre endringene og lukk filen ved å trykke `Ctrl+x`. Trykk `y` for å lagre filen, deretter `return` for å velge filnavnet.

### Oppgave - test mikrofonen og høyttaleren

1. Kjør følgende kommando for å ta opp 5 sekunder med lyd gjennom mikrofonen:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Mens denne kommandoen kjører, lag lyd inn i mikrofonen, for eksempel ved å snakke, synge, beatboxe, spille et instrument eller hva enn du føler for.

1. Etter 5 sekunder vil opptaket stoppe. Kjør følgende kommando for å spille av lyden:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Du vil høre lyden spilles av gjennom høyttalerne. Juster utgangsvolumet på høyttaleren etter behov.

1. Hvis du trenger å justere volumet på den innebygde mikrofonporten, eller justere forsterkningen på mikrofonen, kan du bruke verktøyet `alsamixer`. Du kan lese mer om dette verktøyet på [Linux alsamixer man-siden](https://linux.die.net/man/1/alsamixer).

1. Hvis du får feil ved avspilling av lyden, sjekk kortet du satte som `defaults.pcm.card` i `alsa.conf`-filen.

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.