<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-25T17:29:42+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "it"
}
-->
# Raspberry Pi

Il [Raspberry Pi](https://raspberrypi.org) è un computer a scheda singola. Puoi aggiungere sensori e attuatori utilizzando una vasta gamma di dispositivi ed ecosistemi. Per queste lezioni utilizzeremo un ecosistema hardware chiamato [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Programmerai il tuo Pi e accederai ai sensori Grove utilizzando Python.

![Un Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.it.jpg)

## Configurazione

Se stai utilizzando un Raspberry Pi come hardware IoT, hai due opzioni: puoi seguire tutte queste lezioni e programmare direttamente sul Pi, oppure puoi connetterti da remoto a un Pi "headless" e programmare dal tuo computer.

Prima di iniziare, devi anche collegare il Grove Base Hat al tuo Pi.

### Attività - configurazione

Installa il Grove Base Hat sul tuo Pi e configura il Pi.

1. Collega il Grove Base Hat al tuo Pi. La presa sull'hat si adatta a tutti i pin GPIO del Pi, scivolando completamente sui pin per fissarsi saldamente alla base. Si posiziona sopra il Pi, coprendolo.

    ![Installazione del Grove Hat](../../../../../images/pi-grove-hat-fitting.gif)

1. Decidi come vuoi programmare il tuo Pi e vai alla sezione pertinente qui sotto:

    * [Lavora direttamente sul tuo Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Accesso remoto per programmare il Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Lavora direttamente sul tuo Pi

Se desideri lavorare direttamente sul tuo Pi, puoi utilizzare la versione desktop del sistema operativo Raspberry Pi OS e installare tutti gli strumenti necessari.

#### Attività - lavora direttamente sul tuo Pi

Configura il tuo Pi per lo sviluppo.

1. Segui le istruzioni nella [guida alla configurazione del Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) per configurare il tuo Pi, collegarlo a tastiera/mouse/monitor, connetterlo alla tua rete WiFi o Ethernet e aggiornare il software.

Per programmare il Pi utilizzando i sensori e gli attuatori Grove, sarà necessario installare un editor per scrivere il codice del dispositivo e varie librerie e strumenti per interagire con l'hardware Grove.

1. Una volta che il tuo Pi si è riavviato, avvia il Terminale cliccando sull'icona **Terminale** nella barra del menu superiore, oppure scegli *Menu -> Accessori -> Terminale*.

1. Esegui il seguente comando per assicurarti che il sistema operativo e il software installato siano aggiornati:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Esegui i seguenti comandi per installare tutte le librerie necessarie per l'hardware Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Questo inizia installando Git, insieme a Pip per installare i pacchetti Python.

    Una delle caratteristiche più potenti di Python è la possibilità di installare [pacchetti Pip](https://pypi.org): pacchetti di codice scritti da altre persone e pubblicati su Internet. Puoi installare un pacchetto Pip sul tuo computer con un solo comando e utilizzarlo nel tuo codice.

    I pacchetti Python di Seeed Grove devono essere installati dal codice sorgente. Questi comandi cloneranno il repository contenente il codice sorgente di questo pacchetto e lo installeranno localmente.

    > 💁 Per impostazione predefinita, quando installi un pacchetto, esso è disponibile ovunque sul tuo computer, e questo può causare problemi con le versioni dei pacchetti, ad esempio un'applicazione che dipende da una versione di un pacchetto che smette di funzionare quando installi una nuova versione per un'altra applicazione. Per risolvere questo problema, puoi utilizzare un [ambiente virtuale Python](https://docs.python.org/3/library/venv.html), essenzialmente una copia di Python in una cartella dedicata, e quando installi i pacchetti Pip, vengono installati solo in quella cartella. Non utilizzerai ambienti virtuali quando usi il tuo Pi. Lo script di installazione di Grove installa i pacchetti Python di Grove a livello globale, quindi per utilizzare un ambiente virtuale dovresti configurarlo e poi reinstallare manualmente i pacchetti Grove all'interno di quell'ambiente. È più semplice utilizzare i pacchetti globali, soprattutto perché molti sviluppatori Pi riflashano una scheda SD pulita per ogni progetto.

    Infine, questo abilita l'interfaccia I<sup>2</sup>C.

1. Riavvia il Pi utilizzando il menu o eseguendo il seguente comando nel Terminale:

    ```sh
    sudo reboot
    ```

1. Una volta che il Pi si è riavviato, riapri il Terminale ed esegui il seguente comando per installare [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn), l'editor che utilizzerai per scrivere il codice del dispositivo in Python.

    ```sh
    sudo apt install code
    ```

    Una volta installato, VS Code sarà disponibile dal menu superiore.

    > 💁 Sei libero di utilizzare qualsiasi IDE o editor Python per queste lezioni se hai uno strumento preferito, ma le istruzioni delle lezioni saranno basate sull'uso di VS Code.

1. Installa Pylance. Questa è un'estensione per VS Code che fornisce supporto per il linguaggio Python. Consulta la [documentazione dell'estensione Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) per istruzioni su come installare questa estensione in VS Code.

### Accesso remoto per programmare il Pi

Invece di programmare direttamente sul Pi, puoi farlo funzionare in modalità "headless", cioè senza essere collegato a tastiera/mouse/monitor, e configurarlo e programmarlo dal tuo computer utilizzando Visual Studio Code.

#### Configura il sistema operativo del Pi

Per programmare da remoto, il sistema operativo del Pi deve essere installato su una scheda SD.

##### Attività - configura il sistema operativo del Pi

Configura il sistema operativo headless del Pi.

1. Scarica il **Raspberry Pi Imager** dalla [pagina del software Raspberry Pi OS](https://www.raspberrypi.org/software/) e installalo.

1. Inserisci una scheda SD nel tuo computer, utilizzando un adattatore se necessario.

1. Avvia il Raspberry Pi Imager.

1. Dal Raspberry Pi Imager, seleziona il pulsante **CHOOSE OS**, quindi seleziona *Raspberry Pi OS (Other)*, seguito da *Raspberry Pi OS Lite (32-bit)*.

    ![Il Raspberry Pi Imager con Raspberry Pi OS Lite selezionato](../../../../../translated_images/raspberry-pi-imager.24aedeab9e233d84.it.png)

    > 💁 Raspberry Pi OS Lite è una versione di Raspberry Pi OS che non include l'interfaccia utente desktop o strumenti basati su interfaccia grafica. Questi non sono necessari per un Pi headless e rendono l'installazione più leggera e il tempo di avvio più rapido.

1. Seleziona il pulsante **CHOOSE STORAGE**, quindi seleziona la tua scheda SD.

1. Avvia le **Opzioni Avanzate** premendo `Ctrl+Shift+X`. Queste opzioni consentono una pre-configurazione del sistema operativo Raspberry Pi prima che venga scritto sulla scheda SD.

    1. Spunta la casella **Enable SSH** e imposta una password per l'utente `pi`. Questa sarà la password che utilizzerai per accedere al Pi in seguito.

    1. Se prevedi di connetterti al Pi tramite WiFi, spunta la casella **Configure WiFi** e inserisci il tuo SSID e la password WiFi, oltre a selezionare il tuo paese WiFi. Non è necessario farlo se utilizzerai un cavo Ethernet. Assicurati che la rete a cui ti connetti sia la stessa del tuo computer.

    1. Spunta la casella **Set locale settings** e imposta il tuo paese e fuso orario.

    1. Seleziona il pulsante **SAVE**.

1. Seleziona il pulsante **WRITE** per scrivere il sistema operativo sulla scheda SD. Se utilizzi macOS, ti verrà chiesto di inserire la tua password poiché lo strumento sottostante che scrive le immagini disco richiede privilegi di amministratore.

Il sistema operativo verrà scritto sulla scheda SD e, una volta completato, la scheda verrà espulsa dal sistema operativo e riceverai una notifica. Rimuovi la scheda SD dal tuo computer, inseriscila nel Pi, accendi il Pi e attendi circa 2 minuti affinché si avvii correttamente.

#### Connettiti al Pi

Il passo successivo è accedere al Pi da remoto. Puoi farlo utilizzando `ssh`, disponibile su macOS, Linux e versioni recenti di Windows.

##### Attività - connettiti al Pi

Accedi al Pi da remoto.

1. Avvia un Terminale o Prompt dei Comandi ed esegui il seguente comando per connetterti al Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Se utilizzi una versione di Windows più vecchia che non ha `ssh` installato, puoi utilizzare OpenSSH. Puoi trovare le istruzioni di installazione nella [documentazione di OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Questo dovrebbe connettersi al tuo Pi e chiederti la password.

    La possibilità di trovare computer sulla tua rete utilizzando `<hostname>.local` è una funzionalità abbastanza recente di Linux e Windows. Se utilizzi Linux o Windows e ricevi errori relativi al nome host non trovato, dovrai installare software aggiuntivo per abilitare il networking ZeroConf (anche chiamato Bonjour da Apple):

    1. Se utilizzi Linux, installa Avahi con il seguente comando:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Se utilizzi Windows, il modo più semplice per abilitare ZeroConf è installare [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Puoi anche installare [iTunes per Windows](https://www.apple.com/itunes/download/) per ottenere una versione più recente dell'utility (che non è disponibile separatamente).

    > 💁 Se non riesci a connetterti utilizzando `raspberrypi.local`, puoi utilizzare l'indirizzo IP del tuo Pi. Consulta la [documentazione sull'indirizzo IP del Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) per istruzioni su diversi modi per ottenere l'indirizzo IP.

1. Inserisci la password che hai impostato nelle Opzioni Avanzate del Raspberry Pi Imager.

#### Configura il software sul Pi

Una volta connesso al Pi, devi assicurarti che il sistema operativo sia aggiornato e installare varie librerie e strumenti per interagire con l'hardware Grove.

##### Attività - configura il software sul Pi

Configura il software installato sul Pi e installa le librerie Grove.

1. Dalla tua sessione `ssh`, esegui il seguente comando per aggiornare e poi riavviare il Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Il Pi verrà aggiornato e riavviato. La sessione `ssh` terminerà quando il Pi si riavvierà, quindi attendi circa 30 secondi e riconnettiti.

1. Dalla sessione `ssh` riconnessa, esegui i seguenti comandi per installare tutte le librerie necessarie per l'hardware Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Questo inizia installando Git, insieme a Pip per installare i pacchetti Python.

    Una delle caratteristiche più potenti di Python è la possibilità di installare [pacchetti Pip](https://pypi.org): pacchetti di codice scritti da altre persone e pubblicati su Internet. Puoi installare un pacchetto Pip sul tuo computer con un solo comando e utilizzarlo nel tuo codice.

    I pacchetti Python di Seeed Grove devono essere installati dal codice sorgente. Questi comandi cloneranno il repository contenente il codice sorgente di questo pacchetto e lo installeranno localmente.

    > 💁 Per impostazione predefinita, quando installi un pacchetto, esso è disponibile ovunque sul tuo computer, e questo può causare problemi con le versioni dei pacchetti, ad esempio un'applicazione che dipende da una versione di un pacchetto che smette di funzionare quando installi una nuova versione per un'altra applicazione. Per risolvere questo problema, puoi utilizzare un [ambiente virtuale Python](https://docs.python.org/3/library/venv.html), essenzialmente una copia di Python in una cartella dedicata, e quando installi i pacchetti Pip, vengono installati solo in quella cartella. Non utilizzerai ambienti virtuali quando usi il tuo Pi. Lo script di installazione di Grove installa i pacchetti Python di Grove a livello globale, quindi per utilizzare un ambiente virtuale dovresti configurarlo e poi reinstallare manualmente i pacchetti Grove all'interno di quell'ambiente. È più semplice utilizzare i pacchetti globali, soprattutto perché molti sviluppatori Pi riflashano una scheda SD pulita per ogni progetto.

    Infine, questo abilita l'interfaccia I<sup>2</sup>C.

1. Riavvia il Pi eseguendo il seguente comando:

    ```sh
    sudo reboot
    ```

    La sessione `ssh` terminerà quando il Pi si riavvierà. Non è necessario riconnettersi.

#### Configura VS Code per l'accesso remoto

Una volta configurato il Pi, puoi connetterti ad esso utilizzando Visual Studio Code (VS Code) dal tuo computer. Questo è un editor di testo gratuito per sviluppatori che utilizzerai per scrivere il codice del dispositivo in Python.

##### Attività - configura VS Code per l'accesso remoto

Installa il software richiesto e connettiti da remoto al tuo Pi.

1. Installa VS Code sul tuo computer seguendo la [documentazione di VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Segui le istruzioni nella [documentazione di sviluppo remoto di VS Code utilizzando SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) per installare i componenti necessari.

1. Seguendo le stesse istruzioni, connetti VS Code al Pi.

1. Una volta connesso, segui le istruzioni su [gestione delle estensioni](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) per installare l'[estensione Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) da remoto sul Pi.

## Hello world
È tradizionale, quando si inizia con un nuovo linguaggio di programmazione o tecnologia, creare un'applicazione 'Hello World' - una piccola applicazione che mostra un testo come `"Hello World"` per verificare che tutti gli strumenti siano configurati correttamente.

L'app Hello World per il Pi garantirà che Python e Visual Studio Code siano installati correttamente.

Questa app sarà contenuta in una cartella chiamata `nightlight`, e verrà riutilizzata con codice diverso nelle parti successive di questo incarico per costruire l'applicazione nightlight.

### Compito - hello world

Crea l'app Hello World.

1. Avvia VS Code, direttamente sul Pi o sul tuo computer, collegandoti al Pi tramite l'estensione Remote SSH.

1. Avvia il Terminale di VS Code selezionando *Terminale -> Nuovo Terminale*, oppure premendo `` CTRL+` ``. Si aprirà nella directory home dell'utente `pi`.

1. Esegui i seguenti comandi per creare una directory per il tuo codice e un file Python chiamato `app.py` all'interno di quella directory:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Apri questa cartella in VS Code selezionando *File -> Apri...* e scegliendo la cartella *nightlight*, quindi seleziona **OK**.

    ![La finestra di dialogo di apertura di VS Code che mostra la cartella nightlight](../../../../../translated_images/vscode-open-nightlight-remote.d3d2a4011e30d535.it.png)

1. Apri il file `app.py` dall'esploratore di VS Code e aggiungi il seguente codice:

    ```python
    print('Hello World!')
    ```

    La funzione `print` stampa sulla console qualsiasi cosa venga passata come argomento.

1. Dal Terminale di VS Code, esegui il seguente comando per avviare la tua app Python:

    ```sh
    python app.py
    ```

    > 💁 Potresti dover chiamare esplicitamente `python3` per eseguire questo codice se hai installato Python 2 oltre a Python 3 (l'ultima versione). Se hai Python 2 installato, chiamando `python` verrà utilizzato Python 2 invece di Python 3. Di default, le ultime versioni di Raspberry Pi OS hanno solo Python 3 installato.

    Il seguente output apparirà nel terminale:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Puoi trovare questo codice nella cartella [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 Il tuo programma 'Hello World' è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.