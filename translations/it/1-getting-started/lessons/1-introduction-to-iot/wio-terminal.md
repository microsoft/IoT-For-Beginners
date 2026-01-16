<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-25T17:31:42+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "it"
}
-->
# Wio Terminal

Il [Wio Terminal di Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) è un microcontrollore compatibile con Arduino, dotato di WiFi e alcuni sensori e attuatori integrati, oltre a porte per aggiungere ulteriori sensori e attuatori utilizzando un ecosistema hardware chiamato [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![Un Wio Terminal di Seeed Studios](../../../../../translated_images/it/wio-terminal.b8299ee16587db9a.webp)

## Configurazione

Per utilizzare il tuo Wio Terminal, dovrai installare alcuni software gratuiti sul tuo computer. Inoltre, sarà necessario aggiornare il firmware del Wio Terminal prima di poterlo connettere al WiFi.

### Attività - configurazione

Installa il software richiesto e aggiorna il firmware.

1. Installa Visual Studio Code (VS Code). Questo sarà l'editor che utilizzerai per scrivere il codice del dispositivo in C/C++. Consulta la [documentazione di VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) per le istruzioni sull'installazione di VS Code.

    > 💁 Un altro IDE popolare per lo sviluppo con Arduino è l'[Arduino IDE](https://www.arduino.cc/en/software). Se hai già familiarità con questo strumento, puoi usarlo al posto di VS Code e PlatformIO, ma le lezioni forniranno istruzioni basate sull'uso di VS Code.

1. Installa l'estensione PlatformIO per VS Code. Questa è un'estensione per VS Code che supporta la programmazione di microcontrollori in C/C++. Consulta la [documentazione dell'estensione PlatformIO](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) per le istruzioni sull'installazione di questa estensione in VS Code. Questa estensione dipende dall'estensione Microsoft C/C++ per funzionare con il codice C e C++, e l'estensione C/C++ viene installata automaticamente quando installi PlatformIO.

1. Collega il tuo Wio Terminal al computer. Il Wio Terminal ha una porta USB-C nella parte inferiore, che deve essere collegata a una porta USB del tuo computer. Il Wio Terminal viene fornito con un cavo USB-C a USB-A, ma se il tuo computer ha solo porte USB-C, avrai bisogno di un cavo USB-C o di un adattatore USB-A a USB-C.

1. Segui le istruzioni nella [documentazione WiFi Overview del Wiki di Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) per configurare il tuo Wio Terminal e aggiornare il firmware.

## Hello World

È tradizione, quando si inizia con un nuovo linguaggio di programmazione o tecnologia, creare un'applicazione 'Hello World' - una piccola applicazione che mostra un testo come `"Hello World"` per verificare che tutti gli strumenti siano configurati correttamente.

L'app Hello World per il Wio Terminal ti assicurerà che Visual Studio Code sia installato correttamente con PlatformIO e configurato per lo sviluppo di microcontrollori.

### Creare un progetto PlatformIO

Il primo passo è creare un nuovo progetto utilizzando PlatformIO configurato per il Wio Terminal.

#### Attività - creare un progetto PlatformIO

Crea il progetto PlatformIO.

1. Collega il Wio Terminal al tuo computer.

1. Avvia VS Code.

1. L'icona di PlatformIO sarà nella barra del menu laterale:

    ![L'opzione di menu PlatformIO](../../../../../translated_images/it/vscode-platformio-menu.297be26b9733e5c4.webp)

    Seleziona questa voce di menu, quindi seleziona *PIO Home -> Open*.

    ![L'opzione di apertura PlatformIO](../../../../../translated_images/it/vscode-platformio-home-open.3f9a41bfd3f4da1c.webp)

1. Dalla schermata di benvenuto, seleziona il pulsante **+ New Project**.

    ![Il pulsante per creare un nuovo progetto](../../../../../translated_images/it/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.webp)

1. Configura il progetto nel *Project Wizard*:

    1. Dai un nome al tuo progetto: `nightlight`.

    1. Dal menu a tendina *Board*, digita `WIO` per filtrare le schede e seleziona *Seeeduino Wio Terminal*.

    1. Lascia il *Framework* su *Arduino*.

    1. Lascia la casella *Use default location* selezionata oppure deselezionala e scegli una posizione per il tuo progetto.

    1. Seleziona il pulsante **Finish**.

    ![Il wizard del progetto completato](../../../../../translated_images/it/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.webp)

    PlatformIO scaricherà i componenti necessari per compilare il codice per il Wio Terminal e creerà il tuo progetto. Questo processo potrebbe richiedere alcuni minuti.

### Esaminare il progetto PlatformIO

L'esploratore di VS Code mostrerà una serie di file e cartelle creati dal wizard di PlatformIO.

#### Cartelle

* `.pio` - questa cartella contiene dati temporanei necessari a PlatformIO, come librerie o codice compilato. Viene ricreata automaticamente se eliminata e non è necessario aggiungerla al controllo del codice sorgente se condividi il tuo progetto su siti come GitHub.
* `.vscode` - questa cartella contiene la configurazione utilizzata da PlatformIO e VS Code. Viene ricreata automaticamente se eliminata e non è necessario aggiungerla al controllo del codice sorgente se condividi il tuo progetto su siti come GitHub.
* `include` - questa cartella è per file header esterni necessari quando aggiungi librerie aggiuntive al tuo codice. Non utilizzerai questa cartella in nessuna di queste lezioni.
* `lib` - questa cartella è per librerie esterne che vuoi chiamare dal tuo codice. Non utilizzerai questa cartella in nessuna di queste lezioni.
* `src` - questa cartella contiene il codice sorgente principale della tua applicazione. Inizialmente, conterrà un unico file: `main.cpp`.
* `test` - questa cartella è dove metteresti eventuali test unitari per il tuo codice.

#### File

* `main.cpp` - questo file nella cartella `src` contiene il punto di ingresso per la tua applicazione. Apri questo file, e conterrà il seguente codice:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Quando il dispositivo si avvia, il framework Arduino eseguirà la funzione `setup` una volta, quindi eseguirà la funzione `loop` ripetutamente fino a quando il dispositivo non viene spento.

* `.gitignore` - questo file elenca i file e le directory da ignorare quando aggiungi il tuo codice al controllo del codice sorgente git, come il caricamento su un repository su GitHub.

* `platformio.ini` - questo file contiene la configurazione per il tuo dispositivo e app. Apri questo file, e conterrà il seguente codice:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    La sezione `[env:seeed_wio_terminal]` ha la configurazione per il Wio Terminal. Puoi avere più sezioni `env` in modo che il tuo codice possa essere compilato per più schede.

    Gli altri valori corrispondono alla configurazione del wizard del progetto:

  * `platform = atmelsam` definisce l'hardware utilizzato dal Wio Terminal (un microcontrollore basato su ATSAMD51).
  * `board = seeed_wio_terminal` definisce il tipo di scheda microcontrollore (il Wio Terminal).
  * `framework = arduino` definisce che questo progetto utilizza il framework Arduino.

### Scrivere l'app Hello World

Ora sei pronto per scrivere l'app Hello World.

#### Attività - scrivere l'app Hello World

Scrivi l'app Hello World.

1. Apri il file `main.cpp` in VS Code.

1. Modifica il codice per corrispondere al seguente:

    ```cpp
    #include <Arduino.h>

    void setup()
    {
        Serial.begin(9600);

        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    
    void loop()
    {
        Serial.println("Hello World");
        delay(5000);
    }
    ```

    La funzione `setup` inizializza una connessione alla porta seriale - in questo caso, la porta USB utilizzata per collegare il Wio Terminal al tuo computer. Il parametro `9600` è il [baud rate](https://wikipedia.org/wiki/Symbol_rate) (noto anche come Symbol rate), ovvero la velocità con cui i dati verranno inviati sulla porta seriale in bit al secondo. Questa impostazione significa che vengono inviati 9.600 bit (0 e 1) di dati ogni secondo. Successivamente, attende che la porta seriale sia pronta.

    La funzione `loop` invia la linea `Hello World!` alla porta seriale, quindi i caratteri di `Hello World!` insieme a un carattere di nuova linea. Successivamente, dorme per 5.000 millisecondi o 5 secondi. Dopo che il `loop` termina, viene eseguito di nuovo, e così via, per tutto il tempo in cui il microcontrollore è acceso.

1. Metti il tuo Wio Terminal in modalità upload. Dovrai farlo ogni volta che carichi nuovo codice sul dispositivo:

    1. Sposta rapidamente verso il basso due volte l'interruttore di accensione - tornerà automaticamente alla posizione di accensione ogni volta.

    1. Controlla il LED blu di stato sul lato destro della porta USB. Dovrebbe pulsare.
    
    [![Un video che mostra come mettere il Wio Terminal in modalità upload](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Clicca sull'immagine sopra per un video che mostra come fare.

1. Compila e carica il codice sul Wio Terminal.

    1. Apri il command palette di VS Code.

    1. Digita `PlatformIO Upload` per cercare l'opzione di upload e seleziona *PlatformIO: Upload*.

        ![L'opzione di upload di PlatformIO nel command palette](../../../../../translated_images/it/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.webp)

        PlatformIO compilerà automaticamente il codice se necessario prima di caricarlo.

    1. Il codice verrà compilato e caricato sul Wio Terminal.

        > 💁 Se stai usando macOS, apparirà una notifica su un *DISK NOT EJECTED PROPERLY*. Questo accade perché il Wio Terminal viene montato come un'unità durante il processo di flashing e viene disconnesso quando il codice compilato viene scritto sul dispositivo. Puoi ignorare questa notifica.

    ⚠️ Se ricevi errori riguardo alla porta di upload non disponibile, assicurati prima che il Wio Terminal sia collegato al tuo computer, acceso utilizzando l'interruttore sul lato sinistro dello schermo e impostato in modalità upload. La luce verde nella parte inferiore dovrebbe essere accesa e la luce blu dovrebbe pulsare. Se continui a ricevere l'errore, sposta rapidamente verso il basso l'interruttore di accensione due volte per forzare il Wio Terminal in modalità upload e prova di nuovo.

PlatformIO ha un Serial Monitor che può monitorare i dati inviati tramite il cavo USB dal Wio Terminal. Questo ti permette di monitorare i dati inviati dal comando `Serial.println("Hello World");`.

1. Apri il command palette di VS Code.

1. Digita `PlatformIO Serial` per cercare l'opzione Serial Monitor e seleziona *PlatformIO: Serial Monitor*.

    ![L'opzione Serial Monitor di PlatformIO nel command palette](../../../../../translated_images/it/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.webp)

    Si aprirà un nuovo terminale e i dati inviati sulla porta seriale verranno trasmessi in questo terminale:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` verrà stampato sul monitor seriale ogni 5 secondi.

> 💁 Puoi trovare questo codice nella cartella [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal).

😀 Il tuo programma 'Hello World' è stato un successo!

**Disclaimer (Avvertenza)**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatizzate possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.