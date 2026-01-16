<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-28T09:15:54+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "ro"
}
-->
# Configurează microfonul și difuzoarele - Raspberry Pi

În această parte a lecției, vei adăuga un microfon și difuzoare la Raspberry Pi-ul tău.

## Hardware

Raspberry Pi-ul are nevoie de un microfon.

Pi-ul nu are un microfon integrat, așa că va trebui să adaugi un microfon extern. Există mai multe moduri de a face acest lucru:

* Microfon USB
* Cască USB
* Difuzor USB all-in-one
* Adaptor audio USB și microfon cu mufă de 3,5 mm
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Microfoanele Bluetooth nu sunt toate compatibile cu Raspberry Pi, așa că, dacă ai un microfon sau o cască Bluetooth, este posibil să întâmpini probleme la asociere sau captarea sunetului.

Raspberry Pi-urile sunt echipate cu o mufă pentru căști de 3,5 mm. Poți folosi aceasta pentru a conecta căști, o cască cu microfon sau un difuzor. De asemenea, poți adăuga difuzoare utilizând:

* Audio HDMI printr-un monitor sau TV
* Difuzoare USB
* Cască USB
* Difuzor USB all-in-one
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) cu un difuzor atașat, fie la mufa de 3,5 mm, fie la portul JST

## Conectează și configurează microfonul și difuzoarele

Microfonul și difuzoarele trebuie conectate și configurate.

### Sarcină - conectează și configurează microfonul

1. Conectează microfonul utilizând metoda corespunzătoare. De exemplu, conectează-l printr-unul dintre porturile USB.

1. Dacă folosești ReSpeaker 2-Mics Pi HAT, poți scoate Grove base hat, apoi montează ReSpeaker hat în locul său.

    ![Un Raspberry Pi cu un ReSpeaker hat](../../../../../translated_images/ro/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Vei avea nevoie de un buton Grove mai târziu în această lecție, dar unul este integrat în acest hat, așa că Grove base hat nu este necesar.

    După ce hat-ul este montat, va trebui să instalezi câțiva driveri. Consultă [instrucțiunile de început de la Seeed](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) pentru detalii despre instalarea driverelor.

    > ⚠️ Instrucțiunile folosesc `git` pentru a clona un repository. Dacă nu ai `git` instalat pe Pi-ul tău, îl poți instala rulând următoarea comandă:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Rulează următoarea comandă în Terminal, fie pe Pi, fie conectat prin VS Code și o sesiune SSH remote, pentru a vedea informații despre microfonul conectat:

    ```sh
    arecord -l
    ```

    Vei vedea o listă cu microfoanele conectate. Aceasta va arăta ceva de genul:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Presupunând că ai un singur microfon, ar trebui să vezi o singură intrare. Configurarea microfoanelor poate fi complicată pe Linux, așa că este mai simplu să folosești un singur microfon și să deconectezi altele.

    Notează numărul cardului, deoarece vei avea nevoie de acesta mai târziu. În exemplul de mai sus, numărul cardului este 1.

### Sarcină - conectează și configurează difuzorul

1. Conectează difuzoarele utilizând metoda corespunzătoare.

1. Rulează următoarea comandă în Terminal, fie pe Pi, fie conectat prin VS Code și o sesiune SSH remote, pentru a vedea informații despre difuzoarele conectate:

    ```sh
    aplay -l
    ```

    Vei vedea o listă cu difuzoarele conectate. Aceasta va arăta ceva de genul:

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

    Vei vedea întotdeauna `card 0: Headphones`, deoarece aceasta este mufa de căști integrată. Dacă ai adăugat difuzoare suplimentare, cum ar fi un difuzor USB, acestea vor fi listate de asemenea.

1. Dacă folosești un difuzor suplimentar și nu un difuzor sau căști conectate la mufa de căști integrată, trebuie să îl configurezi ca implicit. Pentru a face acest lucru, rulează următoarea comandă:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Aceasta va deschide un fișier de configurare în `nano`, un editor de text bazat pe terminal. Derulează în jos folosind tastele săgeată de pe tastatură până găsești următoarea linie:

    ```output
    defaults.pcm.card 0
    ```

    Schimbă valoarea de la `0` la numărul cardului pe care vrei să-l folosești din lista returnată de comanda `aplay -l`. De exemplu, în exemplul de mai sus există un al doilea card de sunet numit `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, folosind cardul 1. Pentru a folosi acest card, aș actualiza linia astfel:

    ```output
    defaults.pcm.card 1
    ```

    Setează această valoare la numărul cardului corespunzător. Poți naviga la număr folosind tastele săgeată de pe tastatură, apoi șterge și tastează noul număr ca în mod normal când editezi fișiere text.

1. Salvează modificările și închide fișierul apăsând `Ctrl+x`. Apasă `y` pentru a salva fișierul, apoi `return` pentru a selecta numele fișierului.

### Sarcină - testează microfonul și difuzorul

1. Rulează următoarea comandă pentru a înregistra 5 secunde de audio prin microfon:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    În timp ce această comandă rulează, fă zgomot în microfon, cum ar fi vorbind, cântând, beatboxing, cântând la un instrument sau orice altceva îți place.

1. După 5 secunde, înregistrarea se va opri. Rulează următoarea comandă pentru a reda audio-ul:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Vei auzi audio-ul redat prin difuzoare. Ajustează volumul de ieșire pe difuzor, dacă este necesar.

1. Dacă trebuie să ajustezi volumul portului de microfon integrat sau să reglezi câștigul microfonului, poți folosi utilitarul `alsamixer`. Poți citi mai multe despre acest utilitar pe [pagina man alsamixer pentru Linux](https://linux.die.net/man/1/alsamixer).

1. Dacă întâmpini erori la redarea audio-ului, verifică cardul pe care l-ai setat ca `defaults.pcm.card` în fișierul `alsa.conf`.

---

**Declinarea responsabilității**:  
Acest document a fost tradus utilizând serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.