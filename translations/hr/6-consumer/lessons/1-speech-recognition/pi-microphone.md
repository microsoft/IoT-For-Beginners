# Konfigurirajte mikrofon i zvučnike - Raspberry Pi

U ovom dijelu lekcije dodati ćete mikrofon i zvučnike na svoj Raspberry Pi.

## Hardver

Raspberry Pi treba mikrofon.

Pi nema ugrađeni mikrofon, pa ćete morati dodati vanjski mikrofon. Postoji nekoliko načina za to:

* USB mikrofon
* USB slušalice s mikrofonom
* USB zvučnik s mikrofonom
* USB audio adapter i mikrofon s 3.5mm priključkom
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Bluetooth mikrofoni nisu svi podržani na Raspberry Pi-u, pa ako imate bluetooth mikrofon ili slušalice, možda ćete imati problema s povezivanjem ili snimanjem zvuka.

Raspberry Pi dolazi s 3.5mm priključkom za slušalice. Možete ga koristiti za povezivanje slušalica, headseta ili zvučnika. Također možete dodati zvučnike koristeći:

* HDMI audio preko monitora ili TV-a
* USB zvučnike
* USB slušalice s mikrofonom
* USB zvučnik s mikrofonom
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) s priključenim zvučnikom, bilo na 3.5mm priključak ili na JST port

## Povežite i konfigurirajte mikrofon i zvučnike

Mikrofon i zvučnici moraju biti povezani i konfigurirani.

### Zadatak - povezivanje i konfiguracija mikrofona

1. Povežite mikrofon koristeći odgovarajući način. Na primjer, povežite ga putem jednog od USB portova.

1. Ako koristite ReSpeaker 2-Mics Pi HAT, možete ukloniti Grove osnovni hat, a zatim postaviti ReSpeaker hat na njegovo mjesto.

    ![Raspberry Pi s ReSpeaker hatom](../../../../../translated_images/hr/pi-respeaker-hat.f00fabe7dd039a93.webp)

    Kasnije u ovoj lekciji trebat će vam Grove gumb, ali jedan je ugrađen u ovaj hat, pa Grove osnovni hat nije potreban.

    Kada je hat postavljen, morat ćete instalirati neke upravljačke programe. Pogledajte [Seeed upute za početak](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) za upute o instalaciji upravljačkih programa.

    > ⚠️ Upute koriste `git` za kloniranje repozitorija. Ako nemate `git` instaliran na svom Pi-u, možete ga instalirati pokretanjem sljedeće naredbe:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Pokrenite sljedeću naredbu u svom Terminalu, bilo na Pi-u ili povezanom putem VS Code-a i udaljene SSH sesije, kako biste vidjeli informacije o povezanom mikrofonu:

    ```sh
    arecord -l
    ```

    Vidjet ćete popis povezanih mikrofona. Izgledat će otprilike ovako:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Ako imate samo jedan mikrofon, trebali biste vidjeti samo jedan unos. Konfiguracija mikrofona može biti složena na Linuxu, pa je najlakše koristiti samo jedan mikrofon i odspojiti sve ostale.

    Zabilježite broj kartice, jer će vam kasnije trebati. U gornjem izlazu broj kartice je 1.

### Zadatak - povezivanje i konfiguracija zvučnika

1. Povežite zvučnike koristeći odgovarajući način.

1. Pokrenite sljedeću naredbu u svom Terminalu, bilo na Pi-u ili povezanom putem VS Code-a i udaljene SSH sesije, kako biste vidjeli informacije o povezanom zvučniku:

    ```sh
    aplay -l
    ```

    Vidjet ćete popis povezanih zvučnika. Izgledat će otprilike ovako:

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

    Uvijek ćete vidjeti `card 0: Headphones` jer je to ugrađeni priključak za slušalice. Ako ste dodali dodatne zvučnike, poput USB zvučnika, oni će također biti navedeni.

1. Ako koristite dodatni zvučnik, a ne zvučnik ili slušalice povezane na ugrađeni priključak za slušalice, morate ga postaviti kao zadani. Da biste to učinili, pokrenite sljedeću naredbu:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Ovo će otvoriti konfiguracijsku datoteku u `nano`, terminalskom uređivaču teksta. Pomaknite se dolje pomoću strelica na tipkovnici dok ne pronađete sljedeći redak:

    ```output
    defaults.pcm.card 0
    ```

    Promijenite vrijednost s `0` na broj kartice koju želite koristiti iz popisa koji ste dobili pozivom na `aplay -l`. Na primjer, u gornjem izlazu postoji druga zvučna kartica nazvana `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, koristeći karticu 1. Da bih koristio ovu, ažurirao bih redak na:

    ```output
    defaults.pcm.card 1
    ```

    Postavite ovu vrijednost na odgovarajući broj kartice. Možete se kretati do broja pomoću strelica na tipkovnici, zatim obrisati i upisati novi broj kao što to obično radite prilikom uređivanja tekstualnih datoteka.

1. Spremite promjene i zatvorite datoteku pritiskom na `Ctrl+x`. Pritisnite `y` za spremanje datoteke, zatim `return` za odabir naziva datoteke.

### Zadatak - testiranje mikrofona i zvučnika

1. Pokrenite sljedeću naredbu za snimanje 5 sekundi zvuka putem mikrofona:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Dok se ova naredba izvodi, stvarajte zvuk u mikrofon, poput govora, pjevanja, beatboxanja, sviranja instrumenta ili bilo čega što vam odgovara.

1. Nakon 5 sekundi, snimanje će se zaustaviti. Pokrenite sljedeću naredbu za reprodukciju zvuka:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Čut ćete kako se zvuk reproducira kroz zvučnike. Po potrebi prilagodite glasnoću na zvučniku.

1. Ako trebate prilagoditi glasnoću ugrađenog priključka za mikrofon ili pojačanje mikrofona, možete koristiti alat `alsamixer`. Više o ovom alatu možete pročitati na [Linux alsamixer man stranici](https://linux.die.net/man/1/alsamixer).

1. Ako dobijete pogreške prilikom reprodukcije zvuka, provjerite karticu koju ste postavili kao `defaults.pcm.card` u datoteci `alsa.conf`.

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.