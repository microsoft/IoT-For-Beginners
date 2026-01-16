<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-25T17:56:59+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "it"
}
-->
# Configura il tuo microfono e altoparlanti - Raspberry Pi

In questa parte della lezione, aggiungerai un microfono e altoparlanti al tuo Raspberry Pi.

## Hardware

Il Raspberry Pi necessita di un microfono.

Il Pi non ha un microfono integrato, quindi dovrai aggiungere un microfono esterno. Ci sono diversi modi per farlo:

* Microfono USB
* Cuffie USB
* Speakerphone USB tutto in uno
* Adattatore audio USB e microfono con jack da 3,5 mm
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 I microfoni Bluetooth non sono tutti supportati sul Raspberry Pi, quindi se hai un microfono o cuffie Bluetooth, potresti riscontrare problemi di associazione o di acquisizione audio.

I Raspberry Pi sono dotati di un jack per cuffie da 3,5 mm. Puoi usarlo per collegare cuffie, un auricolare o un altoparlante. Puoi anche aggiungere altoparlanti utilizzando:

* Audio HDMI tramite un monitor o TV
* Altoparlanti USB
* Cuffie USB
* Speakerphone USB tutto in uno
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) con un altoparlante collegato, sia al jack da 3,5 mm che alla porta JST

## Collega e configura il microfono e gli altoparlanti

Il microfono e gli altoparlanti devono essere collegati e configurati.

### Attività - collega e configura il microfono

1. Collega il microfono utilizzando il metodo appropriato. Ad esempio, collegalo tramite una delle porte USB.

1. Se stai utilizzando il ReSpeaker 2-Mics Pi HAT, puoi rimuovere il Grove base hat e montare il ReSpeaker hat al suo posto.

    ![Un Raspberry Pi con un ReSpeaker hat](../../../../../translated_images/it/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Avrai bisogno di un pulsante Grove più avanti in questa lezione, ma uno è integrato in questo hat, quindi il Grove base hat non è necessario.

    Una volta montato l'hat, dovrai installare alcuni driver. Consulta le [istruzioni introduttive di Seeed](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) per le istruzioni sull'installazione dei driver.

    > ⚠️ Le istruzioni utilizzano `git` per clonare un repository. Se non hai `git` installato sul tuo Pi, puoi installarlo eseguendo il seguente comando:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Esegui il seguente comando nel tuo Terminale, sia sul Pi che connesso tramite VS Code e una sessione SSH remota, per vedere informazioni sul microfono collegato:

    ```sh
    arecord -l
    ```

    Vedrai un elenco di microfoni collegati. Sarà qualcosa di simile al seguente:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Supponendo che tu abbia solo un microfono, dovresti vedere solo una voce. La configurazione dei microfoni può essere complicata su Linux, quindi è più semplice utilizzare un solo microfono e scollegare eventuali altri.

    Prendi nota del numero della scheda, poiché ti servirà più avanti. Nell'output sopra il numero della scheda è 1.

### Attività - collega e configura l'altoparlante

1. Collega gli altoparlanti utilizzando il metodo appropriato.

1. Esegui il seguente comando nel tuo Terminale, sia sul Pi che connesso tramite VS Code e una sessione SSH remota, per vedere informazioni sugli altoparlanti collegati:

    ```sh
    aplay -l
    ```

    Vedrai un elenco di altoparlanti collegati. Sarà qualcosa di simile al seguente:

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

    Vedrai sempre `card 0: Headphones`, poiché questo è il jack per cuffie integrato. Se hai aggiunto altoparlanti aggiuntivi, come un altoparlante USB, vedrai anche questo elencato.

1. Se stai utilizzando un altoparlante aggiuntivo e non un altoparlante o cuffie collegati al jack per cuffie integrato, devi configurarlo come predefinito. Per farlo, esegui il seguente comando:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Questo aprirà un file di configurazione in `nano`, un editor di testo basato su terminale. Scorri verso il basso utilizzando i tasti freccia sulla tastiera fino a trovare la seguente riga:

    ```output
    defaults.pcm.card 0
    ```

    Cambia il valore da `0` al numero della scheda che desideri utilizzare dall'elenco restituito dalla chiamata a `aplay -l`. Ad esempio, nell'output sopra c'è una seconda scheda audio chiamata `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, utilizzando la scheda 1. Per utilizzarla, aggiornerei la riga in questo modo:

    ```output
    defaults.pcm.card 1
    ```

    Imposta questo valore sul numero della scheda appropriato. Puoi navigare fino al numero utilizzando i tasti freccia sulla tastiera, quindi eliminare e digitare il nuovo numero normalmente quando modifichi file di testo.

1. Salva le modifiche e chiudi il file premendo `Ctrl+x`. Premi `y` per salvare il file, quindi `invio` per selezionare il nome del file.

### Attività - testa il microfono e l'altoparlante

1. Esegui il seguente comando per registrare 5 secondi di audio tramite il microfono:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Mentre questo comando è in esecuzione, fai rumore nel microfono, ad esempio parlando, cantando, facendo beatbox, suonando uno strumento o qualsiasi altra cosa ti piaccia.

1. Dopo 5 secondi, la registrazione si fermerà. Esegui il seguente comando per riprodurre l'audio:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Sentirai l'audio riprodotto attraverso gli altoparlanti. Regola il volume di uscita sul tuo altoparlante, se necessario.

1. Se hai bisogno di regolare il volume della porta microfono integrata o di regolare il guadagno del microfono, puoi utilizzare l'utilità `alsamixer`. Puoi leggere di più su questa utilità nella [pagina man di alsamixer per Linux](https://linux.die.net/man/1/alsamixer).

1. Se riscontri errori nella riproduzione dell'audio, controlla la scheda che hai impostato come `defaults.pcm.card` nel file `alsa.conf`.

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si consiglia una traduzione professionale eseguita da un traduttore umano. Non siamo responsabili per eventuali fraintendimenti o interpretazioni errate derivanti dall'uso di questa traduzione.