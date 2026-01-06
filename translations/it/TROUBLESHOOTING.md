<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T03:58:37+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "it"
}
-->
# Guida alla Risoluzione dei Problemi

Questa guida ti aiuta a risolvere problemi comuni quando lavori con il curriculum IoT for Beginners. I problemi sono organizzati per categoria per una facile navigazione.

## Sommario

- [Problemi di Installazione](../..)
  - [Installazione di Python](../..)
  - [VS Code e Estensioni](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Librerie Grove](../..)
- [Problemi Hardware](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Dispositivo Virtuale (CounterFit)](../..)
- [Problemi di Connettività](../..)
  - [Connessione WiFi](../..)
  - [Servizi Cloud](../..)
  - [MQTT](../..)
- [Problemi con Sensori e Attuatori](../..)
  - [Sensori Grove](../..)
  - [Fotocamera](../..)
  - [Microfono e Altoparlante](../..)
- [Problemi dell’Ambiente di Sviluppo](../..)
  - [VS Code](../..)
  - [Ambienti Virtuali Python](../..)
  - [Dipendenze](../..)
- [Problemi di Prestazioni](../..)
- [Messaggi di Errore Comuni](../..)
- [Ottenere Aiuto](../..)

---

## Problemi di Installazione

### Installazione di Python

#### Problema: versione di Python troppo vecchia  
**Errore:** `Python 3.6 o superiore è richiesto`

**Soluzione:**
1. Scarica l’ultima versione di Python 3 da [python.org](https://www.python.org/downloads/)
2. Durante l’installazione su Windows, seleziona "Add Python to PATH"
3. Verifica l’installazione:  
   ```bash
   python3 --version
   ```
  
#### Problema: più versioni di Python causano conflitti  
**Sintomi:** viene eseguita la versione sbagliata di Python, pacchetti installati in posizione errata

**Soluzione:**
- **Windows:** usa `py -3` invece di `python` per chiamare esplicitamente Python 3
- **macOS/Linux:** usa `python3` invece di `python`
- Crea e usa sempre ambienti virtuali per i progetti

#### Problema: comando pip non trovato  
**Errore:** `'pip' non è riconosciuto come comando interno o esterno`

**Soluzione:**
1. Prova `pip3` invece di `pip`
2. Oppure usa `python -m pip` o `python3 -m pip`
3. Assicurati che Python sia aggiunto al PATH (reinstalla Python e seleziona l’opzione)

### VS Code e Estensioni

#### Problema: estensione Pylance non funziona  
**Sintomi:** nessun IntelliSense Python, completamento codice o controllo tipo

**Soluzione:**
1. Apri Command Palette di VS Code (`Ctrl+Shift+P` o `Cmd+Shift+P`)
2. Esegui "Python: Select Interpreter"
3. Scegli l’interprete Python corretto (ambiente virtuale se usato)
4. Ricarica la finestra di VS Code

#### Problema: VS Code non rileva ambiente virtuale  
**Sintomi:** interprete Python sbagliato selezionato

**Soluzione:**
1. Assicurati di aver attivato l’ambiente virtuale nel terminale
2. Apri Command Palette e esegui "Python: Select Interpreter"
3. Seleziona l’interprete dalla cartella `.venv`
4. Controlla nella barra di stato (in basso a sinistra) che venga mostrata la versione corretta di Python

### PlatformIO (Wio Terminal)

#### Problema: installazione di PlatformIO fallisce  
**Errore:** vari errori durante l’installazione di PlatformIO

**Soluzione:**
1. Assicurati che VS Code sia aggiornato
2. Installa prima l’estensione C/C++
3. Riavvia VS Code dopo aver installato PlatformIO
4. Controlla la connessione internet (PlatformIO scarica file di grandi dimensioni)

#### Problema: PlatformIO non rileva la scheda  
**Sintomi:** impossibile caricare il codice su Wio Terminal

**Soluzione:**
1. Prova un cavo USB diverso (alcuni cavi sono solo per la ricarica)
2. Controlla Gestione Dispositivi (Windows) o `ls /dev/tty*` (macOS/Linux)
3. Installa o aggiorna i driver USB
4. Prova una porta USB diversa
5. Scorri rapidamente due volte l’interruttore di accensione del Wio Terminal per entrare in modalità bootloader

#### Problema: errori di compilazione in PlatformIO  
**Errore:** `fatal error: Arduino.h: No such file or directory`

**Soluzione:**
1. Elimina la cartella `.pio` nel tuo progetto
2. Esegui "PlatformIO: Rebuild" da Command Palette
3. Assicurati che `platformio.ini` abbia la configurazione scheda corretta:  
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```
  
### Librerie Grove

#### Problema: import della libreria Grove fallisce su Raspberry Pi  
**Errore:** `ModuleNotFoundError: No module named 'grove'`

**Soluzione:**
1. Reinstalla le librerie Grove:  
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Se usi un ambiente virtuale, potrebbe essere necessario installarle globalmente o copiare le librerie  
3. Verifica che I2C sia abilitato: `sudo raspi-config nonint do_i2c 0`

#### Problema: sensore Grove non rilevato  
**Errore:** `IOError: [Errno 121] Remote I/O error`

**Soluzione:**
1. Controlla le connessioni fisiche (assicurati che il cavo Grove sia inserito completamente)
2. Verifica che il sensore sia collegato alla porta corretta (analogica, digitale, I2C, UART)
3. Esegui `i2cdetect -y 1` per vedere se il dispositivo appare sul bus I2C
4. Prova un cavo Grove diverso
5. Assicurati che la Grove Base Hat sia correttamente posizionata sui pin GPIO del Raspberry Pi

---

## Problemi Hardware

### Raspberry Pi

#### Problema: Raspberry Pi non si avvia  
**Sintomi:** nessun display, nessuna attività LED, o schermata arcobaleno

**Soluzione:**
1. **Controlla alimentatore:** usa alimentatore USB-C ufficiale 5V 3A per Pi 4
2. **Problemi con la scheda SD:**  
   - Riformatta la scheda SD e reinstalla Raspberry Pi OS  
   - Prova una scheda SD diversa (usa marche raccomandate)  
   - Assicurati che la scheda SD sia inserita correttamente  
3. **Controlla connessione HDMI:** prova entrambe le porte HDMI su Pi 4, usa la porta HDMI più vicina all’alimentazione

#### Problema: impossibile connettersi in SSH a Raspberry Pi  
**Sintomi:** connessione rifiutata o timeout

**Soluzione:**
1. Abilita SSH:
   - Quando scrivi la scheda SD con Raspberry Pi Imager, configura SSH nelle opzioni avanzate
   - Oppure crea un file vuoto chiamato `ssh` (senza estensione) nella partizione di boot
2. Trova l’indirizzo IP del Pi:
   - Controlla i dispositivi connessi al router
   - Usa `ping raspberrypi.local` (se mDNS funziona)
   - Usa strumenti di scansione come `nmap` o Angry IP Scanner
3. Controlla la rete:
   - Assicurati che il Pi sia nella stessa rete del tuo computer
   - Prova la connessione Ethernet invece del WiFi
4. Verifica username/password (default: nome utente `pi`, password `raspberry`)

#### Problema: Grove Base Hat non riconosciuto  
**Sintomi:** sensori non funzionanti, errori I2C

**Soluzione:**
1. Assicurati che la Base Hat sia correttamente inserita su tutti i pin GPIO
2. Controlla la presenza di pin piegati sul Pi o sulla Base Hat
3. Abilita l’interfaccia I2C:  
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Verifica che I2C funzioni: `i2cdetect -y 1`

#### Problema: Raspberry Pi lento  
**Sintomi:** interfaccia lenta, risposta ritardata

**Soluzione:**
1. Controlla la velocità della scheda SD (usa Class 10 o migliore, o SSD tramite USB)
2. Libera spazio su disco: `df -h` per controllo, elimina file non necessari
3. Riduci memoria GPU in `raspi-config` se non usi pesantemente fotocamera/display
4. Chiudi applicazioni non necessarie
5. Considera di passare a Pi 4 con più RAM se usi Pi 3 o precedente

### Wio Terminal

#### Problema: schermo Wio Terminal rimane nero  
**Sintomi:** nessun output video dopo il caricamento del codice

**Soluzione:**
1. Controlla se il codice inizializza il display (libreria TFT_eSPI)
2. Aggiorna il firmware del Wio Terminal da [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Aggiungi codice di inizializzazione display:  
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Prova a caricare uno sketch di esempio da PlatformIO per testare l’hardware

#### Problema: WiFi non funziona su Wio Terminal  
**Sintomi:** impossibile connettersi al WiFi, errori di rete

**Soluzione:**
1. **Aggiorna firmware WiFi:** segui la guida di aggiornamento firmware WiFi per Wio Terminal su [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Controlla credenziali WiFi:** assicurati che SSID e password siano corretti
3. **Banda WiFi:** Wio Terminal supporta solo WiFi 2.4GHz (non 5GHz)
4. **Forza segnale:** avvicinati al router
5. **Impostazioni router:** alcune reti aziendali/WPA-Enterprise potrebbero non funzionare

#### Problema: Wio Terminal non riconosciuto dal computer  
**Sintomi:** dispositivo USB non rilevato

**Soluzione:**
1. **Prova cavo USB diverso:** usa cavo dati, non solo carica
2. **Entra in modalità bootloader:** fai scorrere l’interruttore di accensione verso il basso due volte rapidamente  
   - Il LED blu dovrebbe lampeggiare, il dispositivo appare come "Arduino" in Gestione Dispositivi  
3. **Installa driver (Windows):**  
   - Scarica e installa [driver USB Seeed](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)  
4. **Prova porta USB diversa:** evita hub USB, usa connessione diretta  
5. **Aggiorna driver USB di sistema**

#### Problema: sensori non funzionano su Wio Terminal  
**Sintomi:** sensori Grove non leggono dati

**Soluzione:**
1. Controlla le connessioni dei cavi Grove
2. Verifica di usare la porta Grove corretta (sinistra o destra)
3. Includi le librerie corrette per il sensore
4. Controlla requisiti di alimentazione dei sensori
5. Testa il sensore con codice d’esempio dalla libreria

### Dispositivo Virtuale (CounterFit)

#### Problema: app CounterFit non si avvia  
**Errore:** vari errori Python all’avvio di CounterFit

**Soluzione:**
1. Assicurati che l’ambiente virtuale sia attivato
2. Installa o reinstalla CounterFit:  
   ```bash
   pip install CounterFit
   ```
3. Controlla che la porta 5000 non sia già in uso:  
   - Windows: `netstat -ano | findstr :5000`  
   - macOS/Linux: `lsof -i :5000`  
4. Termina il processo che usa la porta 5000 o usa una porta diversa:  
   ```bash
   counterfit --port 5001
   ```
  
#### Problema: impossibile connettersi a CounterFit dal codice  
**Errore:** connessione rifiutata o timeout

**Soluzione:**
1. Verifica che CounterFit sia avviato: apri browser su `http://127.0.0.1:5000`
2. Controlla che URL di connessione nel codice corrisponda all’indirizzo CounterFit
3. Assicurati che il firewall non blocchi la connessione
4. Prova a riavviare sia l’app CounterFit che il codice

#### Problema: sensori non appaiono in CounterFit  
**Sintomi:** i sensori creati non compaiono nell’interfaccia di CounterFit

**Soluzione:**
1. Crea i sensori nell’interfaccia di CounterFit prima di eseguire il codice
2. Aggiorna la pagina del browser
3. Controlla che il tipo di sensore corrisponda a quello previsto dal codice
4. Pulisci la cache del browser

---

## Problemi di Connettività

### Connessione WiFi

#### Problema: dispositivo non si connette al WiFi  
**Sintomi:** timeout connessione, autenticazione fallita

**Soluzione:**
1. **Verifica SSID e password:** controlla che le credenziali siano corrette
2. **Banda WiFi:** la maggior parte dei dispositivi IoT supporta solo 2.4GHz (non 5GHz)
3. **Impostazioni del router:**  
   - Disabilita AP isolation se attivata  
   - Usa sicurezza WPA2-PSK (evita WPA3, WEP o reti aperte)  
   - Verifica che DHCP sia abilitato  
4. **Reti nascoste:** se SSID è nascosto, potrebbe essere necessario configurarlo esplicitamente  
5. **Forza segnale:** avvicina il dispositivo al router  
6. **Interferenze:** altri dispositivi, microonde o pareti possono interferire

#### Problema: connessione WiFi cade frequentemente  
**Sintomi:** connettività intermittente

**Soluzione:**
1. Controlla stabilità del router e considera un riavvio
2. Aggiorna firmware del dispositivo
3. Usa IP statico invece di DHCP
4. Riduci distanza dal router o aggiungi un ripetitore WiFi
5. Controlla interferenze da altri dispositivi
6. Verifica che l’alimentazione sia adeguata (specialmente per Raspberry Pi)

### Servizi Cloud

#### Problema: impossibile connettersi a Azure IoT Hub  
**Errore:** autenticazione fallita, connessione rifiutata

**Soluzione:**
1. **Verifica credenziali:**  
   - Controlla che stringa di connessione sia corretta  
   - Assicurati che non ci siano spazi o interruzioni di linea nella stringa  
2. **Controlla registrazione dispositivo:** il dispositivo deve essere registrato nell’IoT Hub  
3. **Firewall/proxy:** assicurati che siano consentiti MQTT (porta 8883) o HTTPS (porta 443) in uscita  
4. **Regione IoT Hub:** verifica che IoT Hub sia attivo e non in regione diversa causando latenza  
5. **Limiti di quota:** controlla se il livello gratuito è stato superato  
6. **Test connessione:**  
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```
  
#### Problema: Azure Functions non si attiva  
**Sintomi:** messaggi inviati ma funzione non eseguita

**Soluzione:**
1. Controlla che la Function App sia in esecuzione (non ferma)
2. Verifica la stringa di connessione nelle impostazioni della Function App
3. Controlla i log della funzione nel Portale Azure
4. Assicurati che il punto di fine compatibile Event Hub sia configurato correttamente
5. Verifica che il formato del messaggio corrisponda a quanto atteso dalla funzione
6. Controlla il piano di servizio della Function App (consumo vs dedicato)

### MQTT
#### Problema: Connessione MQTT fallita
**Errore:** Connessione rifiutata, autenticazione fallita

**Soluzione:**
1. **Indirizzo broker:** Verificare che URL/IP del broker sia corretto
2. **Porta:** Controllare il numero di porta (1883 per non criptato, 8883 per TLS)
3. **Autenticazione:** Verificare username/password se richiesti
4. **TLS/SSL:** Assicurarsi che i certificati siano validi e attendibili
5. **Firewall:** Controllare che la porta non sia bloccata
6. **Test con client MQTT:** Usare MQTT Explorer o mosquitto_pub/sub per testare

#### Problema: Messaggi MQTT non ricevuti
**Sintomi:** Messaggi pubblicati ma non ricevuti dagli abbonati

**Soluzione:**
1. **Nomi topic:** Verificare che il topic dell’abbonato corrisponda esattamente a quello del publisher
2. **Livello QoS:** Provare QoS 1 o 2 invece di 0
3. **Wildcard:** Controllare che i caratteri jolly del topic siano usati correttamente (`+` per livello singolo, `#` per livelli multipli)
4. **Messaggi trattenuti:** Il publisher può impostare il flag retain per conservare l’ultimo messaggio
5. **Tempi di connessione:** Assicurarsi che l’abbonato si connetta prima che i messaggi siano pubblicati

---

## Problemi con Sensori e Attuatori

### Sensori Grove

#### Problema: Sensore fornisce valori errati
**Sintomi:** Letture a 0, -1, o valori insensati

**Soluzione:**
1. **Controllare connessioni:** Assicurarsi che il sensore sia collegato correttamente
2. **Porta corretta:** Verificare che il sensore sia nel tipo di porta adeguato:
   - Sensori analogici → Porte analogiche (A0, A2, A4)
   - Sensori digitali → Porte digitali (D5, D16, D18, ecc.)
   - Sensori I2C → Porte I2C
3. **Calibrazione:** Alcuni sensori necessitano calibrazione (umidità del suolo, luce)
4. **Riavvio:** Scollegare e ricollegare il sensore
5. **Datasheet sensore:** Verificare le specifiche e i requisiti del sensore

#### Problema: Il sensore capacitivo di umidità del suolo legge sempre bagnato
**Sintomi:** Sensore legge alta umidità anche da secco

**Soluzione:**
1. **Calibrazione necessaria:** I sensori del suolo richiedono calibrazione:
   - Leggere valore in aria (linea di base a secco)
   - Leggere valore in acqua (linea di base a bagnato)
   - Mappare le letture tra questi valori
2. **Controllare rivestimento sensore:** I sensori di umidità possono degradarsi se il rivestimento è danneggiato
3. **Posizionamento:** Assicurarsi che il sensore sia inserito completamente nel terreno

#### Problema: Letture errate di temperatura/umidità
**Sintomi:** DHT11/DHT22 mostra temperatura o umidità errata

**Soluzione:**
1. **Posizionamento sensore:** Evitare luce solare diretta, fonti di calore, o correnti d’aria
2. **Tempo di riscaldamento:** Lasciare 2 secondi dopo l’accensione prima di leggere
3. **Frequenza di lettura:** I sensori DHT necessitano tempo tra le letture (almeno 2 secondi)
4. **Controllare condensa:** La condensa può influenzare le letture
5. **Qualità sensore:** DHT11 è meno preciso di DHT22

### Fotocamera

#### Problema: Fotocamera non rilevata su Raspberry Pi
**Errore:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Soluzione:**
1. **Abilitare interfaccia fotocamera:**
   ```bash
   sudo raspi-config
   ```
   Vai in Interface Options → Camera → Enable
2. **Controllare cavo a nastro:** Assicurarsi che il cavo della fotocamera sia inserito correttamente
   - Lato blu rivolto verso le porte USB sul Pi Zero
   - Lato blu rivolto lontano dalle porte USB sul Pi 4
3. **Aggiornare firmware:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Testare fotocamera:**
   ```bash
   raspistill -o test.jpg
   ```

#### Problema: Immagini della fotocamera di scarsa qualità
**Sintomi:** Immagini sfocate, scure o sbiadite

**Soluzione:**
1. **Messa a fuoco:** Rimuovere pellicola protettiva dalla lente, regolare la messa a fuoco se possibile
2. **Illuminazione:** Assicurarsi che ci sia illuminazione adeguata
3. **Impostazioni fotocamera:** Regolare esposizione, ISO, bilanciamento del bianco nel codice
4. **Stabilità:** Mantenere la fotocamera ferma, usare un treppiede se necessario
5. **Risoluzione:** Non superare la massima risoluzione della fotocamera

### Microfono e Altoparlante

#### Problema: Nessun input/output audio
**Sintomi:** Microfono non registra, altoparlante non emette suono

**Soluzione:**
1. **Controllare connessioni:** Verificare che i dispositivi audio siano collegati correttamente
2. **Testare hardware:**
   - Altoparlante: `speaker-test -t wav -c 2`
   - Microfono: `arecord -l` per elencare, `arecord test.wav` per registrare
3. **Impostazioni volume:** Controllare e regolare il volume:
   ```bash
   alsamixer
   ```
4. **Selezionare dispositivo audio:** Specificare il dispositivo audio corretto nel codice
5. **Problemi driver:** Aggiornare ALSA o reinstallare driver audio

#### Problema: ReSpeaker hat non funziona
**Sintomi:** Dispositivo audio non rilevato

**Soluzione:**
1. **Installare driver:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Verifica installazione:** `arecord -l` dovrebbe elencare ReSpeaker
3. **Aggiornare firmware:** Alcune versioni di Pi OS necessitano aggiornamenti driver
4. **Controllare collegamento:** Assicurarsi che l’hat sia collegato correttamente ai pin GPIO

---

## Problemi con Ambiente di Sviluppo

### VS Code

#### Problema: Terminale non attiva automaticamente ambiente virtuale
**Sintomi:** Il terminale si apre ma venv non è attivato

**Soluzione:**
1. **Impostare interprete Python:** Palette comandi → "Python: Select Interpreter" → Scegliere venv
2. **Riavviare VS Code** dopo aver selezionato l’interprete
3. **Controllare impostazioni:** In `settings.json` aggiungere:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Problema: Codice non eseguito sul dispositivo
**Sintomi:** Codice eseguito ma niente succede sul dispositivo

**Soluzione:**
1. **Verificare che codice sia salvato** (controllare punto sulla scheda file)
2. **Controllare quale Python è in uso:** `which python` o `where python`
3. **Per Wio Terminal:** Assicurarsi che il codice sia caricato via PlatformIO (cliccare bottone upload)
4. **Per Raspberry Pi:** Collegarsi via SSH e eseguire il codice lì
5. **Controllare finestra output** per errori

#### Problema: IntelliSense non mostra funzioni della libreria
**Sintomi:** Nessun completamento automatico per moduli importati

**Soluzione:**
1. Assicurarsi che la libreria sia installata nell’ambiente corrente
2. Ricaricare la finestra di VS Code
3. Controllare che l’interprete Python sia corretto
4. Installare type stubs se disponibili: `pip install types-<nome-libreria>`

### Ambienti Virtuali Python

#### Problema: Impossibile creare ambiente virtuale
**Errore:** `The virtual environment was not created successfully`

**Soluzione:**
1. **Installare modulo venv:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Incluso con Python
   - Windows: Reinstallare Python con tutti i componenti
2. **Verificare installazione Python:** Accertarsi che Python sia installato correttamente
3. **Usare percorso completo:** Provare `python3 -m venv .venv` con invocazione esplicita python3

#### Problema: Pacchetti installati nella posizione sbagliata
**Sintomi:** Errore di import dopo installazione pacchetto

**Soluzione:**
1. **Verificare che venv sia attivato:** Il prompt dovrebbe mostrare `(.venv)`
2. **Controllare posizione pip:** `which pip` dovrebbe puntare a `.venv/bin/pip`
3. **Reinstallare in venv:** Attivare venv, quindi `pip install <pacchetto>`
4. **Non usare sudo con pip** in ambiente virtuale

#### Problema: Ambiente virtuale non portabile
**Sintomi:** Venv non funziona dopo spostamento o su computer diverso

**Soluzione:**
1. **Non spostare venv:** Eliminare e ricreare nella nuova posizione
2. **Usare requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Ricreare venv:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # oppure activate.bat su Windows
   pip install -r requirements.txt
   ```

### Dipendenze

#### Problema: Installazione pacchetto fallisce
**Errore:** Vari errori pip durante installazione

**Soluzione:**
1. **Aggiornare pip:**
   ```bash
   pip install --upgrade pip
   ```
2. **Installare strumenti di compilazione:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Installare Visual Studio Build Tools
3. **Controllare connessione internet**
4. **Provare indice pacchetti diverso:** `pip install --index-url https://pypi.org/simple/ <pacchetto>`
5. **Installare versione specifica:** `pip install <pacchetto>==<versione>`

#### Problema: Conflitti di dipendenze
**Errore:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Soluzione:**
1. **Usare ambiente virtuale nuovo** per ogni progetto
2. **Aggiornare pacchetti:** `pip install --upgrade <pacchetto>`
3. **Controllare requisiti:** Usare `pip check` per trovare conflitti
4. **Installare versioni compatibili:** Specificare intervalli di versioni in requirements.txt

---

## Problemi di Prestazioni

### Problema: Codice lento
**Sintomi:** Ritardi, timeout, comportamento non reattivo

**Soluzione:**
1. **Ridurre frequenza lettura sensori:** Non leggere i sensori troppo spesso
2. **Ottimizzare cicli:** Evitare busy-waiting, usare sleep() o ritardi
3. **Problemi di memoria:**
   - Chiudere applicazioni non necessarie
   - Liberare spazio di archiviazione
   - Monitorare con `top` o `htop` su Pi
4. **Velocità scheda SD:** Usare scheda SD più veloce o SSD per Raspberry Pi
5. **Ritardi di rete:** Usare operazioni async per chiamate di rete

### Problema: Errori di memoria esaurita
**Errore:** `MemoryError` o blocco del sistema

**Soluzione:**
1. **Per Raspberry Pi:**
   - Chiudere applicazioni non necessarie
   - Aumentare spazio swap
   - Usare OS più leggero (versione Lite)
   - Aggiornare RAM (Pi 4 ha opzioni 2/4/8GB)
2. **Per Wio Terminal:**
   - Ridurre dimensioni buffer
   - Usare immagini più piccole
   - Ottimizzare uso stringhe
   - Controllare perdite di memoria (memoria non liberata)

### Problema: Perdita o corruzione dati
**Sintomi:** Messaggi mancanti, file corrotti

**Soluzione:**
1. **Problemi con scheda SD:**
   - Usare schede SD di qualità (evitare economiche/fake)
   - Eseguire backup regolari
   - Spegnere correttamente (non staccare alimentazione)
2. **Overflow buffer:** Aumentare dimensioni buffer nel codice
3. **Affidabilità rete:** Implementare logica di retry e gestione errori
4. **Qualità del Servizio:** Usare QoS MQTT 1 o 2 per messaggi importanti

---

## Messaggi di Errore Comuni

### `ModuleNotFoundError: No module named 'X'`
**Causa:** Pacchetto non installato o ambiente virtuale non attivato

**Soluzione:**
```bash
pip install X
```
Assicurarsi prima che l’ambiente virtuale sia attivato.

### `Permission denied` su Linux/macOS
**Causa:** Necessarie autorizzazioni elevate o problema permessi file

**Soluzione:**
- Per operazioni di sistema: Usare `sudo`
- Per pip: NON usare sudo con venv, attivare prima venv
- Per porta seriale: Aggiungere utente al gruppo dialout: `sudo usermod -a -G dialout $USER`, poi logout/login

### `OSError: [Errno 98] Address already in use`
**Causa:** Porta già utilizzata da un altro processo

**Soluzione:**
1. Trovare processo che usa porta: `lsof -i :<port>` o `netstat -ano | findstr :<port>`
2. Terminare processo o usare porta diversa nel codice

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Causa:** Fallita la validazione del certificato SSL

**Soluzione:**
1. Aggiornare certificati: `pip install --upgrade certifi`
2. Controllare che l’ora di sistema sia corretta: `date`
3. Solo per sviluppo (non produzione): Disabilitare verifica nel codice

### `IndentationError: unexpected indent`
**Causa:** Problemi di indentazione in Python (misto tab/spazi)

**Soluzione:**
1. Usare indentazione coerente (4 spazi è lo standard Python)
2. Configurare editor per usare spazi al posto di tab
3. VS Code: Impostare `"editor.insertSpaces": true` e `"editor.tabSize": 4`

### `UnicodeDecodeError` o `UnicodeEncodeError`
**Causa:** Problemi di codifica caratteri

**Soluzione:**
```python
# Durante la lettura dei file
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Durante la scrittura dei file
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Richiedere Aiuto

Se hai provato questi passaggi di risoluzione problemi e riscontri ancora problemi:

### 1. Controlla Risorse Esistenti
- **Documentazione:** Consulta il [README](README.md) e le istruzioni delle lezioni
- **Guide hardware:** Controlla [hardware.md](hardware.md) per informazioni specifiche sull’hardware
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) per componenti Grove

### 2. Cerca Problemi Simili
- **GitHub Issues:** Cerca tra le [issue esistenti](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Cerca messaggi di errore
- **Forum dispositivi:** Consulta forum Raspberry Pi o Arduino

### 3. Crea un Issue su GitHub
Se non trovi una soluzione:
1. Vai su [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Clicca "New Issue"
3. Fornisci:
   - Chiara descrizione del problema
   - Passi per riprodurre
   - Messaggi di errore (testo completo)
   - Versioni hardware/software
   - Cosa hai già provato
   - Screenshot se rilevanti

### 4. Unisciti alla Comunità
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Fornisci Buoni Report di Bug
Un buon report di bug include:
- **Ambiente:** Sistema operativo, versione di Python, hardware utilizzato  
- **Passi per riprodurre:** Passi esatti che causano il problema  
- **Comportamento previsto:** Cosa dovrebbe succedere  
- **Comportamento effettivo:** Cosa succede realmente  
- **Messaggi di errore:** Testo completo dell'errore, non screenshot  
- **Codice:** Esempio minimo di codice che riproduce il problema  

---

## Consigli per la prevenzione

### Buone pratiche generali
1. **Fare backup:** Backup regolari di schede SD/codice funzionanti  
2. **Documentare le modifiche:** Annotare cosa funziona nei commenti  
3. **Controllo versione:** Usare git per tracciare le modifiche al codice  
4. **Testare incrementalmente:** Testare piccole modifiche prima di combinarle  
5. **Leggere i messaggi di errore:** Spesso indicano esattamente cosa non va  
6. **Aggiornare regolarmente:** Mantenere software/firmware aggiornati  
7. **Usare componenti di qualità:** Evitare cavi/alimentatori economici  
8. **Alimentazione stabile:** Usare alimentatore appropriato (soprattutto per Pi)  

### Flusso di lavoro per lo sviluppo
1. **Iniziare semplice:** Partire da codice di esempio che funziona  
2. **Una modifica alla volta:** Più facile trovare cosa rompe  
3. **Test frequenti:** Scoprire i problemi presto  
4. **Mantenere ordine:** Organizzare file e codice in modo logico  
5. **Commentare il codice:** Il te stesso futuro ti ringrazierà  

---

*Questa guida alla risoluzione dei problemi è mantenuta dalla comunità. Se trovi una soluzione a un problema non elencato qui, considera di [contribuire](CONTRIBUTING.md) per aiutare gli altri!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione AI [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per l’accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o inesattezze. Il documento originale nella sua lingua nativa deve essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale umana. Non siamo responsabili per eventuali malintesi o interpretazioni errate derivanti dall’uso di questa traduzione.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->