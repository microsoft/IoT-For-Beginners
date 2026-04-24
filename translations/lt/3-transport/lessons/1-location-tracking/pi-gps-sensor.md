# Skaitykite GPS duomenis - Raspberry Pi

Šioje pamokos dalyje pridėsite GPS jutiklį prie savo Raspberry Pi ir skaitysite jo pateikiamas reikšmes.

## Aparatinė įranga

Raspberry Pi reikalingas GPS jutiklis.

Jutiklis, kurį naudosite, yra [Grove GPS Air530 jutiklis](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Šis jutiklis gali prisijungti prie kelių GPS sistemų, kad greitai ir tiksliai nustatytų vietą. Jutiklis susideda iš dviejų dalių – pagrindinės elektronikos ir išorinės antenos, prijungtos plonu laidu, kad galėtų priimti radijo bangas iš palydovų.

Tai yra UART jutiklis, todėl GPS duomenis perduoda per UART.

## Prijunkite GPS jutiklį

Grove GPS jutiklį galima prijungti prie Raspberry Pi.

### Užduotis - prijunkite GPS jutiklį

Prijunkite GPS jutiklį.

![Grove GPS jutiklis](../../../../../translated_images/lt/grove-gps-sensor.247943bf69b03f0d.webp)

1. Įstatykite vieną Grove kabelio galą į GPS jutiklio lizdą. Kabelis įsistatys tik viena kryptimi.

1. Išjungę Raspberry Pi, prijunkite kitą Grove kabelio galą prie UART lizdo, pažymėto **UART**, esančio Grove Base hat, prijungto prie Pi. Šis lizdas yra vidurinėje eilėje, šalia SD kortelės lizdo, priešingoje pusėje nei USB prievadai ir eterneto lizdas.

    ![Grove GPS jutiklis prijungtas prie UART lizdo](../../../../../translated_images/lt/pi-gps-sensor.1f99ee2b2f652891.webp)

1. Padėkite GPS jutiklį taip, kad prijungta antena turėtų matomumą į dangų – idealiai šalia atviro lango arba lauke. Antenai lengviau gauti aiškų signalą, kai niekas netrukdo.

## Užprogramuokite GPS jutiklį

Dabar Raspberry Pi galima užprogramuoti naudoti prijungtą GPS jutiklį.

### Užduotis - užprogramuokite GPS jutiklį

Užprogramuokite įrenginį.

1. Įjunkite Pi ir palaukite, kol jis įsijungs.

1. GPS jutiklis turi 2 LED lemputes – mėlyną LED, kuris mirksi, kai perduodami duomenys, ir žalią LED, kuris mirksi kas sekundę, kai gauna duomenis iš palydovų. Įsitikinkite, kad įjungus Pi mėlyna LED lemputė mirksi. Po kelių minučių turėtų pradėti mirksėti žalia LED lemputė – jei ne, gali reikėti perstatyti anteną.

1. Paleiskite VS Code tiesiogiai Pi arba prisijunkite per Remote SSH plėtinį.

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip nustatyti ir paleisti VS Code 1 pamokoje](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Naujesnėse Raspberry Pi versijose, kurios palaiko „Bluetooth“, yra konfliktas tarp serijinio prievado, naudojamo „Bluetooth“, ir to, kuris naudojamas Grove UART prievadui. Norėdami tai išspręsti, atlikite šiuos veiksmus:

    1. Iš VS Code terminalo redaguokite `/boot/config.txt` failą naudodami `nano`, įmontuotą terminalo teksto redaktorių, su šia komanda:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Šio failo negalima redaguoti per VS Code, nes reikia `sudo` leidimų, t. y. padidintų teisių. VS Code neveikia su šiais leidimais.

    1. Naudokite rodyklių klavišus, kad pereitumėte į failo pabaigą, tada nukopijuokite žemiau pateiktą kodą ir įklijuokite jį į failo pabaigą:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Galite įklijuoti naudodami įprastus klaviatūros sparčiuosius klavišus (`Ctrl+v` Windows, Linux ar Raspberry Pi OS, `Cmd+v` macOS).

    1. Išsaugokite šį failą ir išeikite iš nano paspausdami `Ctrl+x`. Paspauskite `y`, kai paklausiama, ar norite išsaugoti pakeistą buferį, tada paspauskite `enter`, kad patvirtintumėte, jog norite perrašyti `/boot/config.txt`.

        > Jei padarėte klaidą, galite išeiti neišsaugoję, tada pakartoti šiuos veiksmus.

    1. Redaguokite `/boot/cmdline.txt` failą nano redaktoriumi su šia komanda:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Šiame faile yra keletas raktų/vertės porų, atskirtų tarpais. Pašalinkite visas raktų/vertės poras, kurių raktas yra `console`. Jos greičiausiai atrodys taip:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Galite pereiti prie šių įrašų naudodami rodyklių klavišus, tada ištrinti naudodami įprastus `del` arba `backspace` klavišus.

        Pavyzdžiui, jei jūsų originalus failas atrodo taip:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Nauja versija atrodys taip:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Atlikite aukščiau nurodytus veiksmus, kad išsaugotumėte šį failą ir išeitumėte iš nano.

    1. Perkraukite savo Pi, tada vėl prisijunkite prie VS Code, kai Pi bus perkrautas.

1. Iš terminalo sukurkite naują aplanką `pi` naudotojo pagrindiniame kataloge, pavadintą `gps-sensor`. Sukurkite failą šiame aplanke, pavadintą `app.py`.

1. Atidarykite šį aplanką VS Code.

1. GPS modulis siunčia UART duomenis per serijinį prievadą. Įdiekite `pyserial` Pip paketą, kad galėtumėte bendrauti su serijiniu prievadu iš savo Python kodo:

    ```sh
    pip3 install pyserial
    ```

1. Pridėkite šį kodą į savo `app.py` failą:

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

    Šis kodas importuoja `serial` modulį iš `pyserial` Pip paketo. Tada jis prisijungia prie `/dev/ttyAMA0` serijinio prievado – tai yra serijinio prievado adresas, kurį Grove Pi Base Hat naudoja savo UART prievadui. Tada jis išvalo bet kokius esamus duomenis iš šio serijinio ryšio.

    Toliau apibrėžiama funkcija `print_gps_data`, kuri išveda perduotą eilutę į konsolę.

    Tada kodas vykdo begalinį ciklą, skaitydamas tiek eilučių teksto, kiek gali, iš serijinio prievado kiekviename cikle. Jis kviečia `print_gps_data` funkciją kiekvienai eilutei.

    Kai visi duomenys perskaityti, ciklas laukia 1 sekundę, tada bando dar kartą.

1. Paleiskite šį kodą. Pamatysite neapdorotą GPS jutiklio išvestį, panašią į šią:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Jei gaunate vieną iš šių klaidų, kai sustabdote ir paleidžiate kodą iš naujo, pridėkite `try - except` bloką prie savo while ciklo.

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

> 💁 Šį kodą galite rasti [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi) aplanke.

😀 Jūsų GPS jutiklio programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Dėl svarbios informacijos rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.