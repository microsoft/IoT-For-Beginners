<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-28T12:57:08+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "sl"
}
-->
# Konfigurirajte mikrofon in zvočnike - Raspberry Pi

V tem delu lekcije boste na svoj Raspberry Pi dodali mikrofon in zvočnike.

## Strojna oprema

Raspberry Pi potrebuje mikrofon.

Pi nima vgrajenega mikrofona, zato boste morali dodati zunanji mikrofon. To lahko storite na več načinov:

* USB mikrofon
* USB slušalke z mikrofonom
* USB vse-v-enem zvočnik z mikrofonom
* USB avdio adapter in mikrofon s 3,5 mm priključkom
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Bluetooth mikrofoni niso vsi podprti na Raspberry Pi, zato lahko naletite na težave pri povezovanju ali zajemanju zvoka, če uporabljate bluetooth mikrofon ali slušalke.

Raspberry Pi ima 3,5 mm priključek za slušalke. Ta priključek lahko uporabite za povezavo slušalk, slušalk z mikrofonom ali zvočnika. Zvočnike lahko dodate tudi na naslednje načine:

* HDMI avdio prek monitorja ali televizorja
* USB zvočniki
* USB slušalke z mikrofonom
* USB vse-v-enem zvočnik z mikrofonom
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) z zvočnikom, priključenim bodisi na 3,5 mm priključek bodisi na JST priključek

## Povežite in konfigurirajte mikrofon in zvočnike

Mikrofon in zvočnike je treba povezati in konfigurirati.

### Naloga - povežite in konfigurirajte mikrofon

1. Povežite mikrofon z ustrezno metodo. Na primer, povežite ga prek enega od USB priključkov.

1. Če uporabljate ReSpeaker 2-Mics Pi HAT, lahko odstranite Grove osnovni hat in nato namestite ReSpeaker hat na njegovo mesto.

    ![Raspberry Pi z ReSpeaker hat](../../../../../translated_images/sl/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Kasneje v tej lekciji boste potrebovali gumb Grove, vendar je eden že vgrajen v ta hat, zato Grove osnovni hat ni potreben.

    Ko je hat nameščen, boste morali namestiti nekaj gonilnikov. Za navodila za namestitev gonilnikov si oglejte [Seeed navodila za začetek](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started).

    > ⚠️ Navodila uporabljajo `git` za kloniranje repozitorija. Če `git` ni nameščen na vašem Pi, ga lahko namestite z naslednjim ukazom:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Zaženite naslednji ukaz v Terminalu na Pi ali prek oddaljene SSH seje v VS Code, da si ogledate informacije o povezanem mikrofonu:

    ```sh
    arecord -l
    ```

    Prikazal se bo seznam povezanih mikrofonov. Videti bo nekaj takega:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Če imate le en mikrofon, bi morali videti samo en vnos. Konfiguracija mikrofonov je lahko na Linuxu zahtevna, zato je najlažje uporabljati samo en mikrofon in odklopiti vse druge.

    Zapišite si številko kartice, saj jo boste potrebovali kasneje. V zgornjem izpisu je številka kartice 1.

### Naloga - povežite in konfigurirajte zvočnik

1. Povežite zvočnike z ustrezno metodo.

1. Zaženite naslednji ukaz v Terminalu na Pi ali prek oddaljene SSH seje v VS Code, da si ogledate informacije o povezanih zvočnikih:

    ```sh
    aplay -l
    ```

    Prikazal se bo seznam povezanih zvočnikov. Videti bo nekaj takega:

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

    Vedno boste videli `card 0: Headphones`, saj je to vgrajen priključek za slušalke. Če ste dodali dodatne zvočnike, kot je USB zvočnik, bo ta prav tako naveden.

1. Če uporabljate dodatni zvočnik in ne zvočnika ali slušalk, povezanih na vgrajen priključek za slušalke, ga morate nastaviti kot privzetega. To storite z naslednjim ukazom:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Ta ukaz bo odprl konfiguracijsko datoteko v `nano`, terminalskem urejevalniku besedila. Pomaknite se navzdol s puščičnimi tipkami na tipkovnici, dokler ne najdete naslednje vrstice:

    ```output
    defaults.pcm.card 0
    ```

    Spremenite vrednost iz `0` v številko kartice, ki jo želite uporabiti, iz seznama, ki ste ga dobili z ukazom `aplay -l`. Na primer, v zgornjem izpisu je druga zvočna kartica `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, ki uporablja kartico 1. Če želite uporabiti to kartico, bi posodobil vrstico tako:

    ```output
    defaults.pcm.card 1
    ```

    Nastavite to vrednost na ustrezno številko kartice. Do številke se pomaknite s puščičnimi tipkami na tipkovnici, nato izbrišite in vnesite novo številko kot običajno pri urejanju besedilnih datotek.

1. Shranite spremembe in zaprite datoteko s pritiskom na `Ctrl+x`. Pritisnite `y` za shranjevanje datoteke, nato `return`, da potrdite ime datoteke.

### Naloga - preizkusite mikrofon in zvočnik

1. Zaženite naslednji ukaz za snemanje 5 sekund zvoka prek mikrofona:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Medtem ko ta ukaz teče, ustvarjajte zvok v mikrofon, na primer govorite, pojte, beatboxajte, igrajte na inštrument ali karkoli vam je všeč.

1. Po 5 sekundah se bo snemanje ustavilo. Zaženite naslednji ukaz za predvajanje posnetega zvoka:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Zvok boste slišali prek zvočnikov. Po potrebi prilagodite glasnost na zvočniku.

1. Če morate prilagoditi glasnost vgrajenega priključka za mikrofon ali ojačanje mikrofona, lahko uporabite orodje `alsamixer`. Več o tem orodju si lahko preberete na [Linux alsamixer man strani](https://linux.die.net/man/1/alsamixer).

1. Če naletite na napake pri predvajanju zvoka, preverite kartico, ki ste jo nastavili kot `defaults.pcm.card` v datoteki `alsa.conf`.

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.