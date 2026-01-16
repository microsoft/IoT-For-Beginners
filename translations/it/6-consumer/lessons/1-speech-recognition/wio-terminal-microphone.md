<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-25T17:57:42+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "it"
}
-->
# Configura il tuo microfono e altoparlanti - Wio Terminal

In questa parte della lezione, aggiungerai altoparlanti al tuo Wio Terminal. Il Wio Terminal ha già un microfono integrato, che può essere utilizzato per catturare la voce.

## Hardware

Il Wio Terminal ha già un microfono integrato, che può essere utilizzato per catturare audio per il riconoscimento vocale.

![Il microfono sul Wio Terminal](../../../../../translated_images/it/wio-mic.3f8c843dbe8ad917.webp)

Per aggiungere un altoparlante, puoi utilizzare il [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Si tratta di una scheda esterna che contiene 2 microfoni MEMS, oltre a un connettore per altoparlanti e una presa per cuffie.

![Il ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/it/respeaker.f5d19d1c6b14ab16.webp)

Avrai bisogno di aggiungere cuffie, un altoparlante con jack da 3,5 mm o un altoparlante con connessione JST come il [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Per collegare il ReSpeaker 2-Mics Pi Hat, avrai bisogno di cavi jumper pin-to-pin (anche chiamati maschio-maschio) a 40 pin.

> 💁 Se ti senti a tuo agio con la saldatura, puoi utilizzare il [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) per collegare il ReSpeaker.

Avrai anche bisogno di una scheda SD per scaricare e riprodurre audio. Il Wio Terminal supporta solo schede SD fino a 16GB di dimensione, che devono essere formattate come FAT32 o exFAT.

### Compito - collegare il ReSpeaker Pi Hat

1. Con il Wio Terminal spento, collega il ReSpeaker 2-Mics Pi Hat al Wio Terminal utilizzando i cavi jumper e i socket GPIO sul retro del Wio Terminal:

    I pin devono essere collegati in questo modo:

    ![Diagramma dei pin](../../../../../translated_images/it/wio-respeaker-wiring-0.767f80aa65081038.webp)

1. Posiziona il ReSpeaker e il Wio Terminal con i socket GPIO rivolti verso l'alto e sul lato sinistro.

1. Parti dal socket in alto a sinistra del socket GPIO sul ReSpeaker. Collega un cavo jumper pin-to-pin dal socket in alto a sinistra del ReSpeaker al socket in alto a sinistra del Wio Terminal.

1. Ripeti questa operazione lungo tutti i socket GPIO sul lato sinistro. Assicurati che i pin siano ben inseriti.

    ![Un ReSpeaker con i pin di sinistra collegati ai pin di sinistra del Wio Terminal](../../../../../translated_images/it/wio-respeaker-wiring-1.8d894727f2ba2400.webp)

    ![Un ReSpeaker con i pin di sinistra collegati ai pin di sinistra del Wio Terminal](../../../../../translated_images/it/wio-respeaker-wiring-2.329e1cbd306e754f.webp)

    > 💁 Se i tuoi cavi jumper sono collegati in nastri, tienili tutti insieme - questo rende più facile assicurarsi che tutti i cavi siano collegati nell'ordine corretto.

1. Ripeti il processo utilizzando i socket GPIO sul lato destro del ReSpeaker e del Wio Terminal. Questi cavi devono passare intorno ai cavi già collegati.

    ![Un ReSpeaker con i pin di destra collegati ai pin di destra del Wio Terminal](../../../../../translated_images/it/wio-respeaker-wiring-3.75b0be447e2fa930.webp)

    ![Un ReSpeaker con i pin di destra collegati ai pin di destra del Wio Terminal](../../../../../translated_images/it/wio-respeaker-wiring-4.aa9cd434d8779437.webp)

    > 💁 Se i tuoi cavi jumper sono collegati in nastri, dividili in due nastri. Passa uno su ciascun lato dei cavi esistenti.

    > 💁 Puoi utilizzare del nastro adesivo per tenere i pin in un blocco e impedire che si stacchino mentre li colleghi tutti.
    >
    > ![I pin fissati con nastro adesivo](../../../../../translated_images/it/wio-respeaker-wiring-5.af117c20acf622f3.webp)

1. Dovrai aggiungere un altoparlante.

    * Se stai utilizzando un altoparlante con un cavo JST, collegalo alla porta JST sul ReSpeaker.

      ![Un altoparlante collegato al ReSpeaker con un cavo JST](../../../../../translated_images/it/respeaker-jst-speaker.a441d177809df945.webp)

    * Se stai utilizzando un altoparlante con un jack da 3,5 mm o delle cuffie, inseriscili nella presa jack da 3,5 mm.

      ![Un altoparlante collegato al ReSpeaker tramite la presa jack da 3,5 mm](../../../../../translated_images/it/respeaker-35mm-speaker.ad79ef4f128c7751.webp)

### Compito - configurare la scheda SD

1. Collega la scheda SD al tuo computer, utilizzando un lettore esterno se non hai uno slot per schede SD.

1. Formatta la scheda SD utilizzando lo strumento appropriato sul tuo computer, assicurandoti di utilizzare un file system FAT32 o exFAT.

1. Inserisci la scheda SD nello slot per schede SD sul lato sinistro del Wio Terminal, appena sotto il pulsante di accensione. Assicurati che la scheda sia completamente inserita e faccia clic - potresti aver bisogno di uno strumento sottile o un'altra scheda SD per aiutarti a spingerla completamente.

    ![Inserimento della scheda SD nello slot per schede SD sotto l'interruttore di accensione](../../../../../translated_images/it/wio-sd-card.acdcbe322fa4ee7f.webp)

    > 💁 Per espellere la scheda SD, devi spingerla leggermente e verrà espulsa. Avrai bisogno di uno strumento sottile come un cacciavite a testa piatta o un'altra scheda SD.

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali malintesi o interpretazioni errate derivanti dall'uso di questa traduzione.