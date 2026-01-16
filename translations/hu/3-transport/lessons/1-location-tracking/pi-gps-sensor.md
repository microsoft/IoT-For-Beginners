<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-27T21:40:17+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "hu"
}
-->
# GPS adatok olvasása - Raspberry Pi

Ebben a leckében hozzáadunk egy GPS szenzort a Raspberry Pi-hez, és kiolvassuk az értékeket.

## Hardver

A Raspberry Pi-hez szükség van egy GPS szenzorra.

Az általad használt szenzor a [Grove GPS Air530 szenzor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Ez a szenzor több GPS rendszerhez tud csatlakozni, hogy gyors és pontos helymeghatározást biztosítson. A szenzor két részből áll: a szenzor elektronikai magjából és egy vékony vezetékkel csatlakoztatott külső antennából, amely a műholdak rádióhullámait veszi.

Ez egy UART szenzor, amely UART-on keresztül küldi a GPS adatokat.

## Csatlakoztasd a GPS szenzort

A Grove GPS szenzort csatlakoztathatod a Raspberry Pi-hez.

### Feladat - csatlakoztasd a GPS szenzort

Csatlakoztasd a GPS szenzort.

![Egy Grove GPS szenzor](../../../../../translated_images/hu/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Dugj be egy Grove kábelt a GPS szenzor aljzatába. Csak egy irányban illeszkedik.

1. Kapcsold ki a Raspberry Pi-t, majd csatlakoztasd a Grove kábel másik végét a Grove Base hat **UART** jelzésű aljzatába, amely a Pi-hez van csatlakoztatva. Ez az aljzat a középső sorban található, az SD kártya nyílás közelében, a másik oldalon, mint az USB portok és az ethernet aljzat.

    ![A Grove GPS szenzor csatlakoztatva az UART aljzathoz](../../../../../translated_images/hu/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. Helyezd el a GPS szenzort úgy, hogy a csatlakoztatott antennája látható legyen az ég felé - ideális esetben egy nyitott ablak mellett vagy a szabadban. Az antenna akadálytalan elhelyezése segít tisztább jelet kapni.

## Programozd a GPS szenzort

Most már programozhatod a Raspberry Pi-t, hogy használja a csatlakoztatott GPS szenzort.

### Feladat - programozd a GPS szenzort

Programozd az eszközt.

1. Kapcsold be a Pi-t, és várd meg, amíg elindul.

1. A GPS szenzoron két LED található - egy kék LED, amely villog, amikor adatokat továbbít, és egy zöld LED, amely másodpercenként villog, amikor adatokat kap a műholdaktól. Győződj meg róla, hogy a kék LED villog, amikor bekapcsolod a Pi-t. Néhány perc múlva a zöld LED is villogni fog - ha nem, lehet, hogy újra kell pozícionálnod az antennát.

1. Indítsd el a VS Code-ot, akár közvetlenül a Pi-n, akár a Remote SSH bővítmény segítségével csatlakozva.

    > ⚠️ Ha szükséges, hivatkozhatsz [az 1. leckében található utasításokra a VS Code beállításáról és indításáról](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Az újabb Raspberry Pi modellek, amelyek támogatják a Bluetooth-t, konfliktust okozhatnak a Bluetooth által használt soros port és a Grove UART port által használt soros port között. Ennek megoldásához kövesd az alábbi lépéseket:

    1. A VS Code termináljából szerkeszd a `/boot/config.txt` fájlt a `nano` nevű beépített terminál szövegszerkesztővel az alábbi parancs segítségével:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Ezt a fájlt nem lehet a VS Code-ban szerkeszteni, mivel `sudo` jogosultságra van szükség, ami emelt jogosultságot jelent. A VS Code nem fut ilyen jogosultsággal.

    1. Használd a kurzor billentyűket, hogy a fájl végére navigálj, majd másold be az alábbi kódot a fájl végére:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        A beillesztéshez használd az eszközöd normál billentyűkombinációit (`Ctrl+v` Windows, Linux vagy Raspberry Pi OS esetén, `Cmd+v` macOS esetén).

    1. Mentsd el a fájlt, és lépj ki a nano-ból a `Ctrl+x` billentyűkombinációval. Nyomd meg az `y` gombot, amikor megkérdezi, hogy menteni szeretnéd-e a módosított tartalmat, majd nyomd meg az `enter` gombot, hogy megerősítsd a `/boot/config.txt` felülírását.

        > Ha hibát követsz el, kiléphetsz mentés nélkül, majd megismételheted ezeket a lépéseket.

    1. Szerkeszd a `/boot/cmdline.txt` fájlt a nano segítségével az alábbi parancs segítségével:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Ez a fájl kulcs/érték párokat tartalmaz, amelyek szóközzel vannak elválasztva. Távolítsd el a `console` kulcshoz tartozó kulcs/érték párokat. Ezek valószínűleg így néznek ki:

        ```output
        console=serial0,115200 console=tty1 
        ```

        A kurzor billentyűkkel navigálhatsz ezekhez a bejegyzésekhez, majd törölheted őket a normál `del` vagy `backspace` billentyűkkel.

        Például, ha az eredeti fájl így néz ki:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Az új verzió így fog kinézni:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Kövesd a fentieket a fájl mentéséhez és a nano-ból való kilépéshez.

    1. Indítsd újra a Pi-t, majd csatlakozz újra a VS Code-hoz, miután a Pi újraindult.

1. A terminálból hozz létre egy új mappát a `pi` felhasználó otthoni könyvtárában `gps-sensor` néven. Hozz létre egy fájlt ebben a mappában `app.py` néven.

1. Nyisd meg ezt a mappát a VS Code-ban.

1. A GPS modul UART adatokat küld egy soros porton keresztül. Telepítsd a `pyserial` Pip csomagot, hogy Python kódból kommunikálhass a soros porttal:

    ```sh
    pip3 install pyserial
    ```

1. Add hozzá az alábbi kódot az `app.py` fájlhoz:

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

    Ez a kód importálja a `serial` modult a `pyserial` Pip csomagból. Ezután csatlakozik a `/dev/ttyAMA0` soros porthoz - ez a Grove Pi Base Hat által használt UART port címe. Ezután törli az esetleges meglévő adatokat erről a soros kapcsolatról.

    Ezután definiál egy `print_gps_data` nevű függvényt, amely kiírja a neki átadott sort a konzolra.

    Ezután a kód végtelen ciklust futtat, amely minden ciklusban annyi szövegsort olvas be a soros portból, amennyit csak tud. Minden sorhoz meghívja a `print_gps_data` függvényt.

    Miután az összes adatot beolvasta, a ciklus 1 másodpercig várakozik, majd újra próbálkozik.

1. Futtasd a kódot. Látni fogod a GPS szenzor nyers kimenetét, valami ilyesmit:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Ha az alábbi hibák valamelyikét kapod, amikor leállítod és újraindítod a kódot, adj hozzá egy `try - except` blokkot a while ciklusodhoz.

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

> 💁 Ezt a kódot megtalálod a [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi) mappában.

😀 Sikeresen programoztad a GPS szenzort!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.