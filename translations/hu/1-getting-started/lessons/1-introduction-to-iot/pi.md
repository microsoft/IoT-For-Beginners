<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-27T22:21:53+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "hu"
}
-->
# Raspberry Pi

A [Raspberry Pi](https://raspberrypi.org) egy egykártyás számítógép. Számos eszköz és ökoszisztéma segítségével érzékelőket és működtetőket adhat hozzá, és ezekhez a leckékhez egy [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html) nevű hardver ökoszisztémát fogunk használni. A Pi-t Python segítségével fogja programozni, és hozzáférhet a Grove érzékelőkhöz.

![Egy Raspberry Pi 4](../../../../../translated_images/hu/raspberry-pi-4.fd4590d308c3d456.jpg)

## Beállítás

Ha Raspberry Pi-t használ IoT hardverként, két lehetősége van - végigmehet az összes leckén és közvetlenül a Pi-n programozhat, vagy távolról csatlakozhat egy „fej nélküli” Pi-hez, és a számítógépéről programozhat.

Mielőtt elkezdené, csatlakoztatnia kell a Grove Base Hat-t a Pi-hez.

### Feladat - beállítás

Telepítse a Grove Base Hat-t a Pi-re, és konfigurálja a Pi-t.

1. Csatlakoztassa a Grove Base Hat-t a Pi-hez. A sapka csatlakozója illeszkedik a Pi összes GPIO tűjére, és teljesen lecsúszik a tűkön, hogy szilárdan üljön az alapra. A sapka lefedi a Pi-t.

    ![A Grove sapka illesztése](../../../../../images/pi-grove-hat-fitting.gif)

1. Döntse el, hogyan szeretné programozni a Pi-t, és lépjen a megfelelő szakaszra az alábbiak közül:

    * [Közvetlen munka a Pi-n](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Távoli hozzáférés a Pi programozásához](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Közvetlen munka a Pi-n

Ha közvetlenül a Pi-n szeretne dolgozni, használhatja a Raspberry Pi OS asztali verzióját, és telepítheti az összes szükséges eszközt.

#### Feladat - közvetlen munka a Pi-n

Állítsa be a Pi-t fejlesztéshez.

1. Kövesse a [Raspberry Pi beállítási útmutatóban](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) található utasításokat a Pi beállításához, csatlakoztassa billentyűzethez/egérhez/monitorhoz, csatlakoztassa WiFi-hez vagy ethernet hálózathoz, és frissítse a szoftvert.

A Pi programozásához a Grove érzékelők és működtetők segítségével telepítenie kell egy szerkesztőt, amely lehetővé teszi az eszközkód írását, valamint különféle könyvtárakat és eszközöket, amelyek a Grove hardverrel működnek.

1. Miután a Pi újraindult, indítsa el a Terminált a **Terminal** ikonra kattintva a felső menüsorban, vagy válassza a *Menu -> Accessories -> Terminal* lehetőséget.

1. Futtassa a következő parancsot, hogy megbizonyosodjon arról, hogy az operációs rendszer és a telepített szoftver naprakész:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Futtassa a következő parancsokat az összes szükséges könyvtár telepítéséhez a Grove hardverhez:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Ez először telepíti a Git-et, valamint a Pip-et Python csomagok telepítéséhez.

    A Python egyik erőteljes funkciója a [Pip csomagok](https://pypi.org) telepítésének képessége - ezek olyan kódcsomagok, amelyeket mások írtak és publikáltak az interneten. Egy Pip csomagot egyetlen parancs segítségével telepíthet a számítógépére, majd használhatja azt a kódjában.

    A Seeed Grove Python csomagokat forrásból kell telepíteni. Ezek a parancsok klónozzák a csomag forráskódját tartalmazó repót, majd helyben telepítik.

    > 💁 Alapértelmezés szerint, amikor telepít egy csomagot, az mindenhol elérhető a számítógépén, és ez problémákat okozhat a csomagverziókkal - például egy alkalmazás egy csomag egyik verziójától függ, amely megszakad, amikor egy másik alkalmazáshoz új verziót telepít. Ennek a problémának a megoldására használhat [Python virtuális környezetet](https://docs.python.org/3/library/venv.html), lényegében egy Python másolatot egy dedikált mappában, és amikor Pip csomagokat telepít, azok csak abba a mappába kerülnek telepítésre. A Pi használatakor nem fog virtuális környezeteket használni. A Grove telepítési szkript globálisan telepíti a Grove Python csomagokat, így ha virtuális környezetet szeretne használni, be kell állítania egy virtuális környezetet, majd manuálisan újra kell telepítenie a Grove csomagokat abban a környezetben. Könnyebb egyszerűen globális csomagokat használni, különösen, mivel sok Pi fejlesztő minden projekthez újraír egy tiszta SD kártyát.

    Végül ez engedélyezi az I<sup>2</sup>C interfészt.

1. Indítsa újra a Pi-t a menü használatával vagy a következő parancs futtatásával a Terminálban:

    ```sh
    sudo reboot
    ```

1. Miután a Pi újraindult, indítsa újra a Terminált, és futtassa a következő parancsot a [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) telepítéséhez - ez az a szerkesztő, amelyet az eszközkód Pythonban történő írásához fog használni.

    ```sh
    sudo apt install code
    ```

    Miután ez telepítve van, a VS Code elérhető lesz a felső menüből.

    > 💁 Szabadon használhat bármilyen Python IDE-t vagy szerkesztőt ezekhez a leckékhez, ha van kedvenc eszköze, de a leckék a VS Code használatára vonatkozó utasításokat adnak.

1. Telepítse a Pylance-t. Ez egy VS Code kiegészítő, amely Python nyelvi támogatást nyújt. Tekintse meg a [Pylance kiegészítő dokumentációját](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) a kiegészítő telepítésére vonatkozó utasításokért a VS Code-ban.

### Távoli hozzáférés a Pi programozásához

Ahelyett, hogy közvetlenül a Pi-n programozna, az „fej nélküli” módban futtatható, azaz nem csatlakozik billentyűzethez/egérhez/monitorhoz, és a számítógépéről konfigurálható és programozható a Visual Studio Code segítségével.

#### Állítsa be a Pi OS-t

A távoli programozáshoz a Pi OS-t telepíteni kell egy SD kártyára.

##### Feladat - állítsa be a Pi OS-t

Állítsa be a fej nélküli Pi OS-t.

1. Töltse le a **Raspberry Pi Imager**-t a [Raspberry Pi OS szoftveroldalról](https://www.raspberrypi.org/software/), és telepítse

1. Helyezzen be egy SD kártyát a számítógépébe, szükség esetén adapter segítségével

1. Indítsa el a Raspberry Pi Imager-t

1. A Raspberry Pi Imager-ben válassza ki a **CHOOSE OS** gombot, majd válassza a *Raspberry Pi OS (Other)*, majd a *Raspberry Pi OS Lite (32-bit)* lehetőséget

    ![A Raspberry Pi Imager a Raspberry Pi OS Lite kiválasztásával](../../../../../translated_images/hu/raspberry-pi-imager.24aedeab9e233d84.png)

    > 💁 A Raspberry Pi OS Lite a Raspberry Pi OS egy olyan verziója, amely nem tartalmazza az asztali felhasználói felületet vagy a felhasználói felület alapú eszközöket. Ezek nem szükségesek egy fej nélküli Pi-hez, és kisebb telepítést, valamint gyorsabb indítási időt biztosítanak.

1. Válassza ki a **CHOOSE STORAGE** gombot, majd válassza ki az SD kártyáját

1. Indítsa el a **Advanced Options**-t a `Ctrl+Shift+X` billentyűkombinációval. Ezek az opciók lehetővé teszik a Raspberry Pi OS előzetes konfigurálását, mielőtt az SD kártyára kerülne.

    1. Jelölje be az **Enable SSH** jelölőnégyzetet, és állítson be egy jelszót a `pi` felhasználóhoz. Ez lesz az a jelszó, amelyet később a Pi-be való bejelentkezéshez használ.

    1. Ha WiFi-n keresztül szeretne csatlakozni a Pi-hez, jelölje be a **Configure WiFi** jelölőnégyzetet, és adja meg a WiFi SSID-t és jelszót, valamint válassza ki a WiFi országát. Ha ethernet kábelt használ, erre nincs szükség. Győződjön meg róla, hogy az a hálózat, amelyhez csatlakozik, ugyanaz, amelyen a számítógépe van.

    1. Jelölje be a **Set locale settings** jelölőnégyzetet, és állítsa be az országát és időzónáját

    1. Válassza ki a **SAVE** gombot

1. Válassza ki a **WRITE** gombot az operációs rendszer SD kártyára írásához. Ha macOS-t használ, meg kell adnia a jelszavát, mivel a lemezképek írásához szükséges eszköz rendszergazdai hozzáférést igényel.

Az operációs rendszer az SD kártyára kerül, és a folyamat befejezése után az operációs rendszer kiadja a kártyát, és értesítést kap. Távolítsa el az SD kártyát a számítógépéből, helyezze be a Pi-be, kapcsolja be a Pi-t, és várjon körülbelül 2 percet, hogy megfelelően elinduljon.

#### Csatlakozás a Pi-hez

A következő lépés a Pi távoli elérése. Ezt `ssh` segítségével teheti meg, amely elérhető macOS, Linux és Windows újabb verzióin.

##### Feladat - csatlakozás a Pi-hez

Távolról érje el a Pi-t.

1. Indítson el egy Terminált vagy Parancssort, és írja be a következő parancsot a Pi-hez való csatlakozáshoz:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Ha régebbi Windows verziót használ, amelyen nincs telepítve `ssh`, használhatja az OpenSSH-t. A telepítési utasításokat megtalálja az [OpenSSH telepítési dokumentációban](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Ez csatlakozik a Pi-hez, és kéri a jelszót.

    Az, hogy a számítógépeket a hálózaton `<hostname>.local` segítségével találja meg, viszonylag új funkció Linux és Windows rendszeren. Ha Linuxot vagy Windowst használ, és bármilyen hibát kap arról, hogy a Hostname nem található, további szoftvert kell telepítenie a ZeroConf hálózat engedélyezéséhez (amelyet az Apple Bonjour néven is emleget):

    1. Ha Linuxot használ, telepítse az Avahi-t a következő parancs segítségével:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Ha Windowst használ, a ZeroConf engedélyezésének legegyszerűbb módja a [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999) telepítése. Telepítheti az [iTunes for Windows](https://www.apple.com/itunes/download/) alkalmazást is, hogy újabb verziót kapjon az eszközről (amely nem érhető el önállóan).

    > 💁 Ha nem tud csatlakozni `raspberrypi.local` segítségével, akkor használhatja a Pi IP-címét. Tekintse meg a [Raspberry Pi IP-cím dokumentációját](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) az IP-cím megszerzésének különböző módjairól.

1. Adja meg a jelszót, amelyet a Raspberry Pi Imager Advanced Options-ban állított be.

#### Szoftver konfigurálása a Pi-n

Miután csatlakozott a Pi-hez, meg kell győződnie arról, hogy az operációs rendszer naprakész, és telepítenie kell különféle könyvtárakat és eszközöket, amelyek a Grove hardverrel működnek.

##### Feladat - szoftver konfigurálása a Pi-n

Konfigurálja a telepített Pi szoftvert, és telepítse a Grove könyvtárakat.

1. Az `ssh` munkamenetből futtassa a következő parancsot a frissítéshez, majd indítsa újra a Pi-t:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    A Pi frissül és újraindul. Az `ssh` munkamenet megszakad, amikor a Pi újraindul, ezért hagyja körülbelül 30 másodpercig, majd csatlakozzon újra.

1. Az újracsatlakozott `ssh` munkamenetből futtassa a következő parancsokat az összes szükséges könyvtár telepítéséhez a Grove hardverhez:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Ez először telepíti a Git-et, valamint a Pip-et Python csomagok telepítéséhez.

    A Python egyik erőteljes funkciója a [Pip csomagok](https://pypi.org) telepítésének képessége - ezek olyan kódcsomagok, amelyeket mások írtak és publikáltak az interneten. Egy Pip csomagot egyetlen parancs segítségével telepíthet a számítógépére, majd használhatja azt a kódjában.

    A Seeed Grove Python csomagokat forrásból kell telepíteni. Ezek a parancsok klónozzák a csomag forráskódját tartalmazó repót, majd helyben telepítik.

    > 💁 Alapértelmezés szerint, amikor telepít egy csomagot, az mindenhol elérhető a számítógépén, és ez problémákat okozhat a csomagverziókkal - például egy alkalmazás egy csomag egyik verziójától függ, amely megszakad, amikor egy másik alkalmazáshoz új verziót telepít. Ennek a problémának a megoldására használhat [Python virtuális környezetet](https://docs.python.org/3/library/venv.html), lényegében egy Python másolatot egy dedikált mappában, és amikor Pip csomagokat telepít, azok csak abba a mappába kerülnek telepítésre. A Pi használatakor nem fog virtuális környezeteket használni. A Grove telepítési szkript globálisan telepíti a Grove Python csomagokat, így ha virtuális környezetet szeretne használni, be kell állítania egy virtuális környezetet, majd manuálisan újra kell telepítenie a Grove csomagokat abban a környezetben. Könnyebb egyszerűen globális csomagokat használni, különösen, mivel sok Pi fejlesztő minden projekthez újraír egy tiszta SD kártyát.

    Végül ez engedélyezi az I<sup>2</sup>C interfészt.

1. Indítsa újra a Pi-t a következő parancs futtatásával:

    ```sh
    sudo reboot
    ```

    Az `ssh` munkamenet megszakad, amikor a Pi újraindul. Nincs szükség újracsatlakozásra.

#### VS Code konfigurálása távoli hozzáféréshez

Miután a Pi konfigurálva van, csatlakozhat hozzá a számítógépéről a Visual Studio Code (VS Code) segítségével - ez egy ingyenes fejlesztői szövegszerkesztő, amelyet az eszközkód Pythonban történő írásához fog használni.

##### Feladat - VS Code konfigurálása távoli hozzáféréshez

Telepítse a
Hagyomány, hogy amikor egy új programozási nyelvvel vagy technológiával kezdünk ismerkedni, létrehozunk egy 'Hello World' alkalmazást – egy kis alkalmazást, amely például a `"Hello World"` szöveget írja ki, hogy megbizonyosodjunk arról, hogy minden eszköz megfelelően van beállítva.

A Pi-hez készült Hello World alkalmazás biztosítja, hogy a Python és a Visual Studio Code helyesen legyen telepítve.

Ez az alkalmazás egy `nightlight` nevű mappában lesz, és a feladat későbbi részeiben újra felhasználjuk különböző kódokkal, hogy megépítsük a nightlight alkalmazást.

### Feladat - hello world

Hozd létre a Hello World alkalmazást.

1. Indítsd el a VS Code-ot, akár közvetlenül a Pi-n, akár a számítógépeden, és csatlakozz a Pi-hez a Remote SSH kiterjesztés segítségével.

1. Nyisd meg a VS Code terminált a *Terminal -> New Terminal* kiválasztásával, vagy a `` CTRL+` `` billentyűkombinációval. Ez a `pi` felhasználó kezdőkönyvtárában fog megnyílni.

1. Futtasd a következő parancsokat, hogy létrehozz egy könyvtárat a kódod számára, és hozz létre egy `app.py` nevű Python fájlt ebben a könyvtárban:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Nyisd meg ezt a mappát a VS Code-ban a *File -> Open...* kiválasztásával, majd válaszd ki a *nightlight* mappát, és kattints a **OK** gombra.

    ![A VS Code megnyitási párbeszédablaka, amely a nightlight mappát mutatja](../../../../../translated_images/hu/vscode-open-nightlight-remote.d3d2a4011e30d535.png)

1. Nyisd meg az `app.py` fájlt a VS Code felfedezőjéből, és add hozzá a következő kódot:

    ```python
    print('Hello World!')
    ```

    A `print` függvény kiírja a konzolra azt, amit átadunk neki.

1. A VS Code termináljából futtasd a következőt, hogy elindítsd a Python alkalmazásodat:

    ```sh
    python app.py
    ```

    > 💁 Előfordulhat, hogy kifejezetten a `python3`-at kell meghívnod a kód futtatásához, ha Python 2 is telepítve van a Python 3 mellett (ami a legújabb verzió). Ha Python 2 is telepítve van, akkor a `python` hívása a Python 2-t fogja használni a Python 3 helyett. Alapértelmezés szerint a legújabb Raspberry Pi OS verziók csak Python 3-at tartalmaznak.

    A következő kimenet fog megjelenni a terminálban:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Ezt a kódot megtalálod a [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi) mappában.

😀 A 'Hello World' programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az [Co-op Translator](https://github.com/Azure/co-op-translator) AI fordítási szolgáltatás segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.