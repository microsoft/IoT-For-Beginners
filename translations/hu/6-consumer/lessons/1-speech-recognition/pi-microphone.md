# Mikrofon és hangszórók konfigurálása - Raspberry Pi

Ebben a leckében mikrofont és hangszórókat fogsz hozzáadni a Raspberry Pi-hez.

## Hardver

A Raspberry Pi-nek szüksége van egy mikrofonra.

A Pi nem rendelkezik beépített mikrofonnal, ezért külső mikrofont kell hozzáadnod. Többféle módon csatlakoztathatsz mikrofont:

* USB mikrofon
* USB headset
* USB egyben hangszóró-mikrofon
* USB audio adapter és mikrofon 3,5 mm-es jack csatlakozóval
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 A Bluetooth mikrofonok nem mind kompatibilisek a Raspberry Pi-vel, így ha Bluetooth mikrofont vagy headsetet használsz, problémák adódhatnak a párosítással vagy a hangrögzítéssel.

A Raspberry Pi-k 3,5 mm-es fejhallgató-csatlakozóval rendelkeznek. Ezt használhatod fejhallgató, headset vagy hangszóró csatlakoztatására. Hangszórókat a következő módokon is hozzáadhatsz:

* HDMI audio monitoron vagy TV-n keresztül
* USB hangszórók
* USB headset
* USB egyben hangszóró-mikrofon
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) hangszóróval csatlakoztatva, akár a 3,5 mm-es jack csatlakozón, akár a JST porton keresztül

## Mikrofon és hangszórók csatlakoztatása és konfigurálása

A mikrofont és a hangszórókat csatlakoztatni és konfigurálni kell.

### Feladat - mikrofon csatlakoztatása és konfigurálása

1. Csatlakoztasd a mikrofont a megfelelő módszerrel. Például csatlakoztasd az egyik USB porton keresztül.

1. Ha a ReSpeaker 2-Mics Pi HAT-et használod, eltávolíthatod a Grove alaplapot, majd helyére illesztheted a ReSpeaker HAT-et.

    ![Egy Raspberry Pi ReSpeaker HAT-tel](../../../../../translated_images/hu/pi-respeaker-hat.f00fabe7dd039a93.webp)

    Később szükséged lesz egy Grove gombra ebben a leckében, de ez a HAT már tartalmaz egy beépített gombot, így a Grove alaplap nem szükséges.

    Miután a HAT-et felszerelted, telepítened kell néhány illesztőprogramot. Az illesztőprogramok telepítéséhez lásd a [Seeed kezdő lépések útmutatóját](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started).

    > ⚠️ Az útmutató a `git` használatát javasolja egy tároló klónozásához. Ha a Pi-n nincs telepítve a `git`, a következő parancs futtatásával telepítheted:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Futtasd a következő parancsot a Terminálban, akár a Pi-n, akár a VS Code-on keresztül egy távoli SSH kapcsolattal, hogy információt kapj a csatlakoztatott mikrofonról:

    ```sh
    arecord -l
    ```

    A csatlakoztatott mikrofonok listáját fogod látni. Valami ilyesmi lesz:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Ha csak egy mikrofonod van, akkor csak egy bejegyzést kell látnod. A mikrofonok konfigurálása Linuxon bonyolult lehet, ezért a legegyszerűbb, ha csak egy mikrofont használsz, és eltávolítasz minden másikat.

    Jegyezd fel a kártyaszámot, mert később szükséged lesz rá. A fenti példában a kártyaszám 1.

### Feladat - hangszóró csatlakoztatása és konfigurálása

1. Csatlakoztasd a hangszórókat a megfelelő módszerrel.

1. Futtasd a következő parancsot a Terminálban, akár a Pi-n, akár a VS Code-on keresztül egy távoli SSH kapcsolattal, hogy információt kapj a csatlakoztatott hangszórókról:

    ```sh
    aplay -l
    ```

    A csatlakoztatott hangszórók listáját fogod látni. Valami ilyesmi lesz:

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

    Mindig látni fogod a `card 0: Headphones` bejegyzést, mivel ez a beépített fejhallgató-csatlakozó. Ha további hangszórókat adtál hozzá, például USB hangszórót, ez is megjelenik a listában.

1. Ha további hangszórót használsz, és nem a beépített fejhallgató-csatlakozóhoz csatlakoztatott hangszórót vagy fejhallgatót, akkor azt alapértelmezettként kell beállítanod. Ehhez futtasd a következő parancsot:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Ez megnyit egy konfigurációs fájlt a `nano` nevű terminál-alapú szövegszerkesztőben. Görgess le a billentyűzet nyílbillentyűivel, amíg meg nem találod a következő sort:

    ```output
    defaults.pcm.card 0
    ```

    Módosítsd az értéket `0`-ról arra a kártyaszámra, amelyet az `aplay -l` parancs visszaadott. Például a fenti kimenetben van egy második hangkártya `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]` néven, amely a 1-es kártyát használja. Ennek használatához a sort így kell frissítenem:

    ```output
    defaults.pcm.card 1
    ```

    Állítsd be ezt az értéket a megfelelő kártyaszámra. A nyílbillentyűkkel navigálhatsz a számhoz, majd törölheted és beírhatod az új számot, mint bármely szövegfájl szerkesztésekor.

1. Mentsd el a változtatásokat, és zárd be a fájlt a `Ctrl+x` billentyűkombinációval. Nyomd meg az `y` gombot a fájl mentéséhez, majd az `enter` gombot a fájlnév kiválasztásához.

### Feladat - mikrofon és hangszóró tesztelése

1. Futtasd a következő parancsot, hogy 5 másodpercnyi hangot rögzíts a mikrofonon keresztül:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Amíg ez a parancs fut, adj ki hangot a mikrofonba, például beszélj, énekelj, beatboxolj, játssz egy hangszeren, vagy bármi mást, amihez kedved van.

1. 5 másodperc elteltével a felvétel leáll. Futtasd a következő parancsot a hang lejátszásához:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Hallani fogod a hangot, ahogy a hangszórókon keresztül visszajátssza. Állítsd be a hangszóró kimeneti hangerejét szükség szerint.

1. Ha a beépített mikrofon port hangerejét vagy a mikrofon erősítését kell beállítanod, használhatod az `alsamixer` segédprogramot. Erről a segédprogramról többet olvashatsz a [Linux alsamixer kézikönyv oldalán](https://linux.die.net/man/1/alsamixer).

1. Ha hibát kapsz a hang lejátszásakor, ellenőrizd a `alsa.conf` fájlban beállított `defaults.pcm.card` értéket.

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.