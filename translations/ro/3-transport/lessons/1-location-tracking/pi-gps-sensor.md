<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-28T09:36:45+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "ro"
}
-->
# Citirea datelor GPS - Raspberry Pi

În această parte a lecției, vei adăuga un senzor GPS la Raspberry Pi și vei citi valorile de la acesta.

## Hardware

Raspberry Pi are nevoie de un senzor GPS.

Senzorul pe care îl vei folosi este [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Acest senzor se poate conecta la mai multe sisteme GPS pentru o localizare rapidă și precisă. Senzorul este format din 2 părți - componentele electronice de bază ale senzorului și o antenă externă conectată printr-un fir subțire pentru a recepționa undele radio de la sateliți.

Acesta este un senzor UART, deci transmite date GPS prin UART.

## Conectarea senzorului GPS

Senzorul Grove GPS poate fi conectat la Raspberry Pi.

### Sarcină - conectarea senzorului GPS

Conectează senzorul GPS.

![Un senzor Grove GPS](../../../../../translated_images/ro/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Introdu un capăt al cablului Grove în soclul senzorului GPS. Acesta va intra doar într-un singur mod.

1. Cu Raspberry Pi oprit, conectează celălalt capăt al cablului Grove la soclul UART marcat **UART** de pe Grove Base hat atașat la Pi. Acest soclu se află pe rândul din mijloc, pe partea cea mai apropiată de slotul pentru cardul SD, la capătul opus porturilor USB și soclului ethernet.

    ![Senzorul Grove GPS conectat la soclul UART](../../../../../translated_images/ro/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. Poziționează senzorul GPS astfel încât antena atașată să aibă vizibilitate către cer - ideal lângă o fereastră deschisă sau afară. Este mai ușor să obții un semnal clar fără obstacole în calea antenei.

## Programarea senzorului GPS

Raspberry Pi poate fi acum programat pentru a utiliza senzorul GPS atașat.

### Sarcină - programarea senzorului GPS

Programează dispozitivul.

1. Pornește Pi și așteaptă să se încarce.

1. Senzorul GPS are 2 LED-uri - un LED albastru care clipește când se transmit date și un LED verde care clipește la fiecare secundă când primește date de la sateliți. Asigură-te că LED-ul albastru clipește când pornești Pi. După câteva minute, LED-ul verde va începe să clipească - dacă nu, poate fi necesar să repoziționezi antena.

1. Lansează VS Code, fie direct pe Pi, fie conectându-te prin extensia Remote SSH.

    > ⚠️ Poți consulta [instrucțiunile pentru configurarea și lansarea VS Code din lecția 1, dacă este necesar](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Cu versiunile mai noi de Raspberry Pi care suportă Bluetooth, există un conflict între portul serial utilizat pentru Bluetooth și cel utilizat de portul Grove UART. Pentru a rezolva acest lucru, urmează pașii de mai jos:

    1. Din terminalul VS Code, editează fișierul `/boot/config.txt` folosind `nano`, un editor de text integrat în terminal, cu următoarea comandă:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Acest fișier nu poate fi editat direct din VS Code, deoarece trebuie să fie modificat cu permisiuni `sudo`, adică permisiuni elevate. VS Code nu rulează cu aceste permisiuni.

    1. Folosește tastele săgeată pentru a naviga la sfârșitul fișierului, apoi copiază codul de mai jos și lipește-l la sfârșitul fișierului:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Poți lipi folosind combinațiile normale de taste pentru dispozitivul tău (`Ctrl+v` pe Windows, Linux sau Raspberry Pi OS, `Cmd+v` pe macOS).

    1. Salvează fișierul și ieși din nano apăsând `Ctrl+x`. Apasă `y` când ți se cere să salvezi modificările, apoi apasă `enter` pentru a confirma că vrei să suprascrii `/boot/config.txt`.

        > Dacă faci o greșeală, poți ieși fără a salva, apoi repetă acești pași.

    1. Editează fișierul `/boot/cmdline.txt` în nano cu următoarea comandă:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Acest fișier conține mai multe perechi cheie/valoare separate prin spații. Elimină orice perechi cheie/valoare pentru cheia `console`. Acestea vor arăta probabil astfel:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Poți naviga la aceste intrări folosind tastele săgeată, apoi le poți șterge folosind tastele `del` sau `backspace`.

        De exemplu, dacă fișierul original arată astfel:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Noua versiune va fi:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Urmează pașii de mai sus pentru a salva acest fișier și a ieși din nano.

    1. Repornește Pi, apoi reconectează-te în VS Code după ce Pi s-a repornit.

1. Din terminal, creează un folder nou în directorul de acasă al utilizatorului `pi`, numit `gps-sensor`. Creează un fișier în acest folder numit `app.py`.

1. Deschide acest folder în VS Code.

1. Modulul GPS trimite date UART printr-un port serial. Instalează pachetul Pip `pyserial` pentru a comunica cu portul serial din codul Python:

    ```sh
    pip3 install pyserial
    ```

1. Adaugă următorul cod în fișierul `app.py`:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Acest cod importă modulul `serial` din pachetul Pip `pyserial`. Apoi se conectează la portul serial `/dev/ttyAMA0` - aceasta este adresa portului serial pe care Grove Pi Base Hat îl folosește pentru portul său UART. Apoi șterge orice date existente din această conexiune serială.

    Următorul pas definește o funcție numită `print_gps_data`, care afișează linia transmisă către ea în consolă.

    Apoi, codul intră într-un ciclu infinit, citind cât mai multe linii de text posibil de la portul serial în fiecare iterație. Apelează funcția `print_gps_data` pentru fiecare linie.

    După ce toate datele au fost citite, ciclul așteaptă 1 secundă, apoi încearcă din nou.

1. Rulează acest cod. Vei vedea ieșirea brută de la senzorul GPS, ceva de genul:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Dacă primești una dintre următoarele erori când oprești și repornești codul, adaugă un bloc `try - except` în bucla while.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 Poți găsi acest cod în folderul [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Programul senzorului GPS a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus utilizând serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să aveți în vedere că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.