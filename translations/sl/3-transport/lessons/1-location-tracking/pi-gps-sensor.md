# Branje GPS podatkov - Raspberry Pi

V tem delu lekcije boste dodali GPS senzor na vaš Raspberry Pi in prebrali vrednosti iz njega.

## Strojna oprema

Raspberry Pi potrebuje GPS senzor.

Senzor, ki ga boste uporabili, je [Grove GPS Air530 senzor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Ta senzor se lahko poveže z več GPS sistemi za hitro in natančno določanje lokacije. Senzor je sestavljen iz dveh delov - osnovne elektronike senzorja in zunanje antene, ki je povezana s tanko žico za sprejem radijskih valov s satelitov.

To je UART senzor, ki pošilja GPS podatke prek UART.

## Povezava GPS senzorja

Grove GPS senzor se lahko poveže z Raspberry Pi.

### Naloga - povežite GPS senzor

Povežite GPS senzor.

![Grove GPS senzor](../../../../../translated_images/sl/grove-gps-sensor.247943bf69b03f0d.webp)

1. Vstavite en konec Grove kabla v vtičnico na GPS senzorju. Kabel bo šel noter samo v eno smer.

1. Ko je Raspberry Pi izklopljen, povežite drugi konec Grove kabla z UART vtičnico, označeno **UART**, na Grove Base hat, ki je pritrjen na Pi. Ta vtičnica je v srednji vrsti, na strani, ki je najbližje reži za SD kartico, na nasprotni strani od USB priključkov in ethernet vtičnice.

    ![Grove GPS senzor povezan z UART vtičnico](../../../../../translated_images/sl/pi-gps-sensor.1f99ee2b2f652891.webp)

1. Postavite GPS senzor tako, da ima pritrjena antena vidljivost do neba - idealno ob odprtem oknu ali zunaj. Lažje je dobiti jasen signal, če anteni nič ne ovira.

## Programiranje GPS senzorja

Raspberry Pi je zdaj pripravljen za programiranje, da uporablja pritrjen GPS senzor.

### Naloga - programirajte GPS senzor

Programirajte napravo.

1. Vklopite Pi in počakajte, da se zažene.

1. GPS senzor ima 2 LED lučki - modro LED lučko, ki utripa, ko se prenašajo podatki, in zeleno LED lučko, ki utripa vsako sekundo, ko prejema podatke s satelitov. Prepričajte se, da modra LED lučka utripa, ko vklopite Pi. Po nekaj minutah bo začela utripati zelena LED lučka - če ne, boste morda morali premakniti anteno.

1. Zaženite VS Code, bodisi neposredno na Pi, bodisi se povežite prek razširitve Remote SSH.

    > ⚠️ Če potrebujete, si lahko ogledate [navodila za nastavitev in zagon VS Code v lekciji 1](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Pri novejših različicah Raspberry Pi, ki podpirajo Bluetooth, obstaja konflikt med serijskim priključkom, ki se uporablja za Bluetooth, in tistim, ki ga uporablja Grove UART priključek. Da to odpravite, naredite naslednje:

    1. Iz terminala v VS Code uredite datoteko `/boot/config.txt` z uporabo `nano`, vgrajenega urejevalnika besedila v terminalu, z naslednjim ukazom:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Te datoteke ni mogoče urejati z VS Code, saj jo morate urejati z dovoljenji `sudo`, kar pomeni povišana dovoljenja. VS Code ne deluje s temi dovoljenji.

    1. S puščičnimi tipkami se pomaknite na konec datoteke, nato kopirajte spodnjo kodo in jo prilepite na konec datoteke:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Kodo lahko prilepite z običajnimi bližnjicami na tipkovnici za vašo napravo (`Ctrl+v` na Windows, Linux ali Raspberry Pi OS, `Cmd+v` na macOS).

    1. Shranite datoteko in zapustite nano s pritiskom na `Ctrl+x`. Ko vas vpraša, ali želite shraniti spremenjeni medpomnilnik, pritisnite `y`, nato pritisnite `enter`, da potrdite, da želite prepisati `/boot/config.txt`.

        > Če naredite napako, lahko zapustite brez shranjevanja in nato ponovite te korake.

    1. Uredite datoteko `/boot/cmdline.txt` v nano z naslednjim ukazom:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Ta datoteka vsebuje več parov ključ/vrednost, ločenih s presledki. Odstranite vse pare ključ/vrednost za ključ `console`. Verjetno bodo videti nekako takole:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Do teh vnosov se lahko pomaknete s puščičnimi tipkami, nato pa jih izbrišete z običajnimi tipkami `del` ali `backspace`.

        Na primer, če vaša izvirna datoteka izgleda takole:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Nova različica bo:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Sledite zgornjim korakom, da shranite to datoteko in zapustite nano.

    1. Znova zaženite Pi, nato se znova povežite v VS Code, ko se Pi ponovno zažene.

1. Iz terminala ustvarite novo mapo v domačem imeniku uporabnika `pi`, imenovano `gps-sensor`. Ustvarite datoteko v tej mapi, imenovano `app.py`.

1. Odprite to mapo v VS Code.

1. GPS modul pošilja UART podatke prek serijskega priključka. Namestite Pip paket `pyserial`, da komunicirate s serijskim priključkom iz vaše Python kode:

    ```sh
    pip3 install pyserial
    ```

1. Dodajte naslednjo kodo v vašo datoteko `app.py`:

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

    Ta koda uvozi modul `serial` iz Pip paketa `pyserial`. Nato se poveže s serijskim priključkom `/dev/ttyAMA0` - to je naslov serijskega priključka, ki ga Grove Pi Base Hat uporablja za svoj UART priključek. Nato počisti vse obstoječe podatke iz te serijske povezave.

    Nato je definirana funkcija `print_gps_data`, ki izpiše vrstico, ki ji je poslana, na konzolo.

    Nato koda neskončno zanka, bere toliko vrstic besedila, kot jih lahko, iz serijskega priključka v vsaki zanki. Za vsako vrstico pokliče funkcijo `print_gps_data`.

    Ko so vsi podatki prebrani, zanka počiva 1 sekundo, nato poskusi znova.

1. Zaženite to kodo. Videli boste surov izhod iz GPS senzorja, nekaj takega:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Če dobite eno od naslednjih napak pri ustavitvi in ponovnem zagonu kode, dodajte blok `try - except` v vašo zanko while.

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

> 💁 To kodo lahko najdete v mapi [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Vaš program za GPS senzor je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za strojno prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo strokovno človeško prevajanje. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki izhajajo iz uporabe tega prevoda.