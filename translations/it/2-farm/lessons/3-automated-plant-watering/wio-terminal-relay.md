<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-25T16:52:16+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "it"
}
-->
# Controllare un relè - Wio Terminal

In questa parte della lezione, aggiungerai un relè al tuo Wio Terminal, oltre al sensore di umidità del suolo, e lo controllerai in base al livello di umidità del suolo.

## Hardware

Il Wio Terminal necessita di un relè.

Il relè che utilizzerai è un [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), un relè normalmente aperto (ciò significa che il circuito di uscita è aperto, o disconnesso, quando non viene inviato alcun segnale al relè) che può gestire circuiti di uscita fino a 250V e 10A.

Questo è un attuatore digitale, quindi si collega ai pin digitali del Wio Terminal. La porta combinata analogica/digitale è già in uso con il sensore di umidità del suolo, quindi questo si collega all'altra porta, che è una porta combinata I²C e digitale.

### Collegare il relè

Il Grove relay può essere collegato alla porta digitale del Wio Terminal.

#### Attività

Collega il relè.

![Un Grove relay](../../../../../translated_images/it/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Inserisci un'estremità di un cavo Grove nella presa del relè. Può essere inserito solo in un modo.

1. Con il Wio Terminal scollegato dal computer o da un'altra fonte di alimentazione, collega l'altra estremità del cavo Grove alla presa Grove sul lato sinistro del Wio Terminal, guardando lo schermo. Lascia il sensore di umidità del suolo collegato alla presa destra.

![Il Grove relay collegato alla presa sinistra e il sensore di umidità del suolo collegato alla presa destra](../../../../../translated_images/it/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.webp)

1. Inserisci il sensore di umidità del suolo nel terreno, se non è già stato fatto nella lezione precedente.

## Programmare il relè

Ora il Wio Terminal può essere programmato per utilizzare il relè collegato.

### Attività

Programma il dispositivo.

1. Apri il progetto `soil-moisture-sensor` dalla lezione precedente in VS Code, se non è già aperto. Aggiungerai codice a questo progetto.

2. Non esiste una libreria per questo attuatore: è un attuatore digitale controllato da un segnale alto o basso. Per accenderlo, invii un segnale alto al pin (3.3V), per spegnerlo invii un segnale basso (0V). Puoi farlo utilizzando la funzione [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/) integrata di Arduino. Inizia aggiungendo il seguente codice alla fine della funzione `setup` per configurare la porta combinata I²C/digitale come pin di uscita per inviare una tensione al relè:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` è il numero di porta per la porta combinata I²C/digitale.

1. Per testare che il relè funzioni, aggiungi il seguente codice alla funzione `loop`, sotto l'ultimo `delay`:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    Il codice invia un segnale alto al pin a cui è collegato il relè per accenderlo, attende 500ms (mezzo secondo), quindi invia un segnale basso per spegnerlo.

1. Compila e carica il codice sul Wio Terminal.

1. Una volta caricato, il relè si accenderà e spegnerà ogni 10 secondi, con un ritardo di mezzo secondo tra accensione e spegnimento. Sentirai il relè fare clic quando si accende e spegne. Un LED sulla scheda Grove si illuminerà quando il relè è acceso e si spegnerà quando il relè è spento.

    ![Il relè che si accende e spegne](../../../../../images/relay-turn-on-off.gif)

## Controllare il relè in base all'umidità del suolo

Ora che il relè funziona, può essere controllato in risposta alle letture del sensore di umidità del suolo.

### Attività

Controlla il relè.

1. Elimina le 3 righe di codice che hai aggiunto per testare il relè. Sostituiscile con il seguente codice:

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    Questo codice controlla il livello di umidità del suolo dal sensore di umidità. Se è superiore a 450, accende il relè, e lo spegne quando scende sotto 450.

    > 💁 Ricorda che il sensore capacitivo di umidità del suolo legge: più basso è il livello di umidità, maggiore è l'umidità nel terreno e viceversa.

1. Compila e carica il codice sul Wio Terminal.

1. Monitora il dispositivo tramite il monitor seriale. Vedrai il relè accendersi o spegnersi a seconda del livello di umidità del suolo. Prova con terreno asciutto, poi aggiungi acqua.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Puoi trovare questo codice nella cartella [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal).

😀 Il tuo programma per controllare un relè con il sensore di umidità del suolo è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di tenere presente che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.