# Csatlakoztassa eszközét az internethez

![A lecke vázlatos áttekintése](../../../../../translated_images/hu/lesson-4.7344e074ea68fa54.webp)

> Vázlatrajz: [Nitya Narasimhan](https://github.com/nitya). Kattintson a képre a nagyobb verzióért.

Ezt a leckét a [Hello IoT sorozat](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) részeként tanították a [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) keretében. A lecke két videóból állt: egy 1 órás tanórából és egy 1 órás konzultációból, amely mélyebben belemerült a lecke részeibe és válaszolt a kérdésekre.

[![4. lecke: Csatlakoztassa eszközét az internethez](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![4. lecke: Csatlakoztassa eszközét az internethez - Konzultáció](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Kattintson a fenti képekre a videók megtekintéséhez

## Előzetes kvíz

[Előzetes kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Bevezetés

Az IoT-ban az **I** az **Internetet** jelenti – a felhőkapcsolatot és szolgáltatásokat, amelyek lehetővé teszik az IoT-eszközök számos funkcióját, az eszközhöz csatlakoztatott érzékelőktől származó mérések gyűjtésétől kezdve az aktuátorok vezérlésére szolgáló üzenetek küldéséig. Az IoT-eszközök általában egyetlen felhőalapú IoT-szolgáltatáshoz csatlakoznak egy szabványos kommunikációs protokoll segítségével, és ez a szolgáltatás kapcsolódik az IoT-alkalmazás többi részéhez, az AI-szolgáltatásoktól kezdve, amelyek okos döntéseket hoznak az adatok alapján, egészen a vezérlésre vagy jelentéskészítésre szolgáló webalkalmazásokig.

> 🎓 Az érzékelőktől gyűjtött és a felhőbe küldött adatokat telemetriának nevezzük.

Az IoT-eszközök üzeneteket is kaphatnak a felhőből. Ezek az üzenetek gyakran parancsokat tartalmaznak – azaz utasításokat egy művelet végrehajtására, akár belsőleg (például újraindítás vagy firmware-frissítés), akár egy aktuátor segítségével (például egy lámpa bekapcsolása).

Ez a lecke bemutatja azokat a kommunikációs protokollokat, amelyeket az IoT-eszközök használhatnak a felhőhöz való csatlakozáshoz, valamint azokat az adatokat, amelyeket küldhetnek vagy fogadhatnak. Gyakorlatban is kipróbálhatja ezeket, internetes vezérlést adva az éjszakai lámpájához, és az LED vezérlési logikáját a helyben futó „szerver” kódba helyezve át.

Ebben a leckében a következő témákat tárgyaljuk:

* [Kommunikációs protokollok](../../../../../1-getting-started/lessons/4-connect-internet)
* [Üzenetsor Telemetria Szállítás (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetria](../../../../../1-getting-started/lessons/4-connect-internet)
* [Parancsok](../../../../../1-getting-started/lessons/4-connect-internet)

## Kommunikációs protokollok

Számos népszerű kommunikációs protokoll létezik, amelyeket az IoT-eszközök használnak az internetes kommunikációhoz. A legnépszerűbbek a publikálás/feliratkozás üzenetküldésen alapulnak valamilyen közvetítőn keresztül. Az IoT-eszközök csatlakoznak a közvetítőhöz, és telemetriát publikálnak, valamint parancsokra iratkoznak fel. A felhőszolgáltatások szintén csatlakoznak a közvetítőhöz, és feliratkoznak az összes telemetriai üzenetre, valamint parancsokat publikálnak, akár konkrét eszközökre, akár eszközcsoportokra.

![Az IoT-eszközök egy közvetítőhöz csatlakoznak, telemetriát publikálnak és parancsokra iratkoznak fel. A felhőszolgáltatások szintén csatlakoznak a közvetítőhöz, feliratkoznak az összes telemetriára, és parancsokat küldenek konkrét eszközökre.](../../../../../translated_images/hu/pub-sub.7c7ed43fe9fd15d4.webp)

Az MQTT a legnépszerűbb kommunikációs protokoll az IoT-eszközök számára, és ezt a leckében tárgyaljuk. Egyéb protokollok közé tartozik az AMQP és a HTTP/HTTPS.

## Üzenetsor Telemetria Szállítás (MQTT)

Az [MQTT](http://mqtt.org) egy könnyű, nyílt szabványú üzenetküldési protokoll, amely üzeneteket tud küldeni eszközök között. 1999-ben tervezték olajvezetékek megfigyelésére, majd 15 évvel később az IBM nyílt szabványként tette közzé.

Az MQTT egyetlen közvetítőt és több klienst használ. Minden kliens csatlakozik a közvetítőhöz, amely az üzeneteket a megfelelő kliensekhez irányítja. Az üzeneteket elnevezett témák segítségével irányítják, nem pedig közvetlenül egy adott klienshez küldik. Egy kliens publikálhat egy témára, és bármelyik kliens, amely feliratkozott erre a témára, megkapja az üzenetet.

![Az IoT-eszköz telemetriát publikál a /telemetry témára, és a felhőszolgáltatás feliratkozik erre a témára](../../../../../translated_images/hu/mqtt.cbf7f21d9adc3e17.webp)

✅ Kutasson egy kicsit! Ha sok IoT-eszköze van, hogyan biztosíthatja, hogy az MQTT közvetítője képes legyen kezelni az összes üzenetet?

### Csatlakoztassa IoT-eszközét az MQTT-hez

Az első lépés az internetes vezérlés hozzáadásához az éjszakai lámpájához, hogy csatlakoztassa azt egy MQTT közvetítőhöz.

#### Feladat

Csatlakoztassa eszközét egy MQTT közvetítőhöz.

Ebben a lecke részben az IoT éjszakai lámpáját csatlakoztatja az internethez, hogy távolról vezérelhető legyen. Később ebben a leckében az IoT-eszköze egy telemetriai üzenetet küld az MQTT-n keresztül egy nyilvános MQTT közvetítőnek a fényerősséggel, amelyet egy szerver kód fog feldolgozni, amelyet Ön ír. Ez a kód ellenőrzi a fényerősséget, és egy parancsüzenetet küld vissza az eszköznek, amely megmondja, hogy kapcsolja be vagy ki az LED-et.

Egy ilyen beállítás valós példája lehet, hogy több fényérzékelőtől gyűjt adatokat, mielőtt eldöntené, hogy bekapcsolja-e a lámpákat egy olyan helyen, ahol sok lámpa van, például egy stadionban. Ez megakadályozhatja, hogy a lámpák bekapcsoljanak, ha csak egy érzékelőt takar el egy felhő vagy egy madár, de a többi érzékelő elegendő fényt érzékel.

✅ Milyen más helyzetekben lenne szükség több érzékelő adatainak kiértékelésére, mielőtt parancsokat küldenének?

Ahelyett, hogy az MQTT közvetítő beállításának bonyolultságával foglalkozna ebben a feladatban, használhat egy nyilvános tesztszervert, amely az [Eclipse Mosquitto](https://www.mosquitto.org) nevű nyílt forráskódú MQTT közvetítőt futtatja. Ez a teszt közvetítő nyilvánosan elérhető a [test.mosquitto.org](https://test.mosquitto.org) címen, és nem igényel fiók létrehozását, így kiváló eszköz az MQTT kliensek és szerverek tesztelésére.

> 💁 Ez a teszt közvetítő nyilvános és nem biztonságos. Bárki hallgathatja, amit publikál, ezért nem szabad olyan adatokkal használni, amelyeket titokban kell tartani.

![A feladat folyamatábrája, amely a fényerősség leolvasását és ellenőrzését, valamint az LED vezérlését mutatja](../../../../../translated_images/hu/assignment-1-internet-flow.3256feab5f052fd2.webp)

Kövesse az alábbi lépéseket, hogy csatlakoztassa eszközét az MQTT közvetítőhöz:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Egylapkás számítógép - Raspberry Pi/Virtuális IoT eszköz](single-board-computer-mqtt.md)

### Mélyebb betekintés az MQTT-be

A témák hierarchiával rendelkezhetnek, és a kliensek különböző szintekre iratkozhatnak fel helyettesítő karakterek használatával. Például küldhet hőmérsékleti telemetriai üzeneteket a `/telemetry/temperature` témára és páratartalom-üzeneteket a `/telemetry/humidity` témára, majd a felhőalkalmazásában feliratkozhat a `/telemetry/*` témára, hogy mindkét típusú telemetriai üzenetet megkapja.

Az üzenetek minőségi szolgáltatással (QoS) küldhetők, amely meghatározza az üzenet kézbesítésének garanciáját.

* Legfeljebb egyszer – az üzenet csak egyszer kerül elküldésre, és a kliens és a közvetítő nem tesz további lépéseket a kézbesítés visszaigazolására (tűz és felejtsd el).
* Legalább egyszer – az üzenetet a küldő többször újraküldi, amíg visszaigazolást nem kap (visszaigazolt kézbesítés).
* Pontosan egyszer – a küldő és a fogadó kétlépcsős kézfogást végez, hogy biztosítsa, hogy az üzenetből csak egy példány érkezzen meg (biztosított kézbesítés).

✅ Milyen helyzetekben lenne szükség biztosított kézbesítésre a „tűz és felejtsd el” üzenet helyett?

Bár az MQTT nevében szerepel az Üzenetsor (Message Queueing), valójában nem támogatja az üzenetsorokat. Ez azt jelenti, hogy ha egy kliens megszakad, majd újracsatlakozik, nem kapja meg azokat az üzeneteket, amelyeket a megszakítás alatt küldtek, kivéve azokat, amelyeket már elkezdett feldolgozni a QoS folyamat során. Az üzenetek rendelkezhetnek egy megőrzési jelzővel. Ha ez be van állítva, az MQTT közvetítő tárolja az utolsó üzenetet, amelyet erre a témára küldtek ezzel a jelzővel, és elküldi ezt minden olyan kliensnek, amely később feliratkozik a témára. Így a kliensek mindig megkapják a legfrissebb üzenetet.

Az MQTT támogat egy életben tartási funkciót is, amely ellenőrzi, hogy a kapcsolat még él-e a hosszú üzenetküldési szünetek alatt.

> 🦟 [Mosquitto az Eclipse Alapítványtól](https://mosquitto.org) egy ingyenes MQTT közvetítőt kínál, amelyet saját maga futtathat az MQTT kísérletezéséhez, valamint egy nyilvános MQTT közvetítőt, amelyet kódja teszteléséhez használhat, a [test.mosquitto.org](https://test.mosquitto.org) címen.

Az MQTT kapcsolatok lehetnek nyilvánosak és nyitottak, vagy titkosítottak és felhasználónévvel és jelszóval, illetve tanúsítványokkal védettek.

> 💁 Az MQTT a TCP/IP-n keresztül kommunikál, ugyanazon hálózati protokollon, mint a HTTP, de más porton. Az MQTT-t webszervereken keresztül is használhatja webalkalmazásokkal való kommunikációhoz, vagy olyan helyzetekben, ahol tűzfalak vagy más hálózati szabályok blokkolják a szabványos MQTT kapcsolatokat.

## Telemetria

A telemetria szó görög gyökerekből származik, jelentése távoli mérés. A telemetria az adatok gyűjtése az érzékelőktől és azok felhőbe küldése.

> 💁 Az egyik legkorábbi telemetriai eszközt Franciaországban találták fel 1874-ben, és valós idejű időjárási és hóvastagsági adatokat küldött a Mont Blanc-ról Párizsba. Fizikai vezetékeket használt, mivel akkoriban nem álltak rendelkezésre vezeték nélküli technológiák.

Nézzük vissza az 1. leckében bemutatott okos termosztát példáját.

![Egy internethez csatlakoztatott termosztát több szobai érzékelővel](../../../../../translated_images/hu/telemetry.21e5d8b97649d2eb.webp)

A termosztát hőmérséklet-érzékelőkkel gyűjti a telemetriát. Valószínűleg egy beépített hőmérséklet-érzékelővel rendelkezik, és több külső hőmérséklet-érzékelőhöz is csatlakozhat egy vezeték nélküli protokoll, például [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE) segítségével.

A telemetriai adatok példája, amelyeket küldhet:

| Név | Érték | Leírás |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | A termosztát beépített hőmérséklet-érzékelője által mért hőmérséklet |
| `livingroom_temperature` | 19°C | Egy távoli hőmérséklet-érzékelő által mért hőmérséklet, amelyet `livingroom` névvel azonosítottak a szoba megjelölésére |
| `bedroom_temperature` | 21°C | Egy távoli hőmérséklet-érzékelő által mért hőmérséklet, amelyet `bedroom` névvel azonosítottak a szoba megjelölésére |

A felhőszolgáltatás ezután felhasználhatja ezeket a telemetriai adatokat a fűtés vezérlésére vonatkozó parancsok küldésére.

### Telemetria küldése az IoT-eszközéről

A következő lépés az internetes vezérlés hozzáadásában az éjszakai lámpájához, hogy a fényerősség telemetriát küldje az MQTT közvetítőnek egy telemetriai témára.

#### Feladat - telemetria küldése az IoT-eszközéről

Küldjön fényerősség telemetriát az MQTT közvetítőnek.

Az adatokat JSON formátumban küldik – a JavaScript Object Notation rövidítése, amely egy szabvány az adatok szöveges kódolására kulcs/érték párok használatával.

✅ Ha még nem találkozott a JSON-nal, többet megtudhat róla a [JSON.org dokumentációjában](https://www.json.org/).

Kövesse az alábbi lépéseket, hogy telemetriát küldjön az eszközéről az MQTT közvetítőnek:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Egylapkás számítógép - Raspberry Pi/Virtuális IoT eszköz](single-board-computer-telemetry.md)

### Telemetria fogadása az MQTT közvetítőtől

Nincs értelme telemetriát küldeni, ha nincs, aki fogadja azt. A fényerősség telemetriának szüksége van valamire, ami figyeli és feldolgozza az adatokat. Ez a „szerver” kód az a fajta kód, amelyet egy nagyobb IoT
💁 Szabadon használhatsz bármilyen Python IDE-t vagy szerkesztőt ezekhez a leckékhez, ha van kedvenc eszközöd, de a leckék a VS Code használatára vonatkozó utasításokat fognak adni.
1. Telepítse a VS Code Pylance bővítményt. Ez egy olyan bővítmény a VS Code-hoz, amely Python nyelvi támogatást nyújt. A bővítmény telepítéséhez olvassa el a [Pylance bővítmény dokumentációját](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance).

#### Python virtuális környezet konfigurálása

A Python egyik erőteljes funkciója a [pip csomagok](https://pypi.org) telepítésének lehetősége – ezek mások által írt és az interneten közzétett kódcsoportok. Egy pip csomagot egyetlen paranccsal telepíthet a számítógépére, majd használhatja azt a kódjában. A pip segítségével telepíteni fog egy csomagot, amely az MQTT-n keresztüli kommunikációt teszi lehetővé.

Alapértelmezés szerint, amikor telepít egy csomagot, az a számítógépén mindenhol elérhetővé válik, ami problémákat okozhat a csomagverziókkal – például egy alkalmazás egy csomag egy adott verziójától függ, amely megszakadhat, ha egy másik alkalmazáshoz új verziót telepít. Ennek a problémának a megoldására használhat egy [Python virtuális környezetet](https://docs.python.org/3/library/venv.html), amely lényegében a Python egy másolata egy dedikált mappában. Amikor pip csomagokat telepít, azok csak ebbe a mappába kerülnek.

##### Feladat - Python virtuális környezet konfigurálása

Konfiguráljon egy Python virtuális környezetet, és telepítse az MQTT pip csomagokat.

1. A termináljában vagy parancssorában futtassa a következő parancsokat egy Ön által választott helyen, hogy létrehozzon és belépjen egy új könyvtárba:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Most futtassa a következőt, hogy létrehozzon egy virtuális környezetet a `.venv` mappában:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Kifejezetten a `python3`-at kell meghívnia a virtuális környezet létrehozásához, arra az esetre, ha Python 2 is telepítve van a Python 3 mellett (a legújabb verzió). Ha Python 2 van telepítve, akkor a `python` meghívása a Python 2-t fogja használni a Python 3 helyett.

1. Aktiválja a virtuális környezetet:

    * Windows rendszeren:
        * Ha a Parancssort vagy a Windows Terminálon keresztüli Parancssort használja, futtassa:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Ha PowerShellt használ, futtassa:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS vagy Linux rendszeren futtassa:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Ezeket a parancsokat ugyanabból a helyről kell futtatni, ahol a virtuális környezet létrehozására szolgáló parancsot futtatta. Soha nem kell belépnie a `.venv` mappába, mindig az aktiváló parancsot és a csomagok telepítésére vagy kód futtatására szolgáló parancsokat kell futtatnia abból a mappából, ahol a virtuális környezetet létrehozta.

1. Miután a virtuális környezet aktiválva lett, az alapértelmezett `python` parancs a virtuális környezet létrehozásához használt Python verziót fogja futtatni. Futtassa a következőt a verzió ellenőrzéséhez:

    ```sh
    python --version
    ```

    A kimenet hasonló lesz a következőhöz:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 A Python verziója eltérő lehet – amíg az 3.6 vagy újabb, addig megfelelő. Ha nem, törölje ezt a mappát, telepítsen egy újabb Python verziót, és próbálja újra.

1. Futtassa a következő parancsokat a [Paho-MQTT](https://pypi.org/project/paho-mqtt/) pip csomag telepítéséhez, amely egy népszerű MQTT könyvtár.

    ```sh
    pip install paho-mqtt
    ```

    Ez a pip csomag csak a virtuális környezetben lesz telepítve, és azon kívül nem lesz elérhető.

#### Írja meg a szerver kódját

Most már megírhatja a szerver kódját Pythonban.

##### Feladat - szerver kód írása

Írja meg a szerver kódját.

1. A termináljában vagy parancssorában futtassa a következőt a virtuális környezeten belül, hogy létrehozzon egy `app.py` nevű Python fájlt:

    * Windows rendszeren futtassa:

        ```cmd
        type nul > app.py
        ```

    * macOS vagy Linux rendszeren futtassa:

        ```cmd
        touch app.py
        ```

1. Nyissa meg az aktuális mappát a VS Code-ban:

    ```sh
    code .
    ```

1. Amikor a VS Code elindul, aktiválni fogja a Python virtuális környezetet. Ezt az alsó állapotsorban fogja jelezni:

    ![A VS Code a kiválasztott virtuális környezetet mutatja](../../../../../translated_images/hu/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Ha a VS Code Terminál már fut, amikor a VS Code elindul, akkor nem lesz aktiválva benne a virtuális környezet. A legegyszerűbb megoldás az, ha bezárja a terminált az **Aktív terminálpéldány bezárása** gombbal:

    ![A VS Code Aktív terminálpéldány bezárása gomb](../../../../../translated_images/hu/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Indítson egy új VS Code Terminált a *Terminál -> Új terminál* menüpont kiválasztásával, vagy a `` CTRL+` `` billentyűkombináció megnyomásával. Az új terminál betölti a virtuális környezetet, és az aktiválás parancsa megjelenik a terminálban. A virtuális környezet neve (`.venv`) szintén megjelenik a promptban:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Nyissa meg az `app.py` fájlt a VS Code felfedezőjéből, és adja hozzá a következő kódot:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Cserélje ki a `<ID>`-t a 6. sorban arra az egyedi azonosítóra, amelyet az eszközkód létrehozásakor használt.

    ⚠️ Ez **kötelezően** ugyanaz az azonosító kell legyen, amelyet az eszközén használt, különben a szerver kód nem fog megfelelően feliratkozni vagy üzeneteket küldeni a megfelelő témára.

    Ez a kód létrehoz egy MQTT klienst egy egyedi névvel, és csatlakozik a *test.mosquitto.org* brokerhez. Ezután elindít egy feldolgozási ciklust, amely egy háttérszálon fut, és figyeli az üzeneteket az összes feliratkozott témán.

    A kliens ezután feliratkozik a telemetriai témára érkező üzenetekre, és definiál egy függvényt, amelyet akkor hív meg, amikor üzenetet kap. Amikor egy telemetriai üzenet érkezik, a `handle_telemetry` függvény hívódik meg, amely a konzolra írja a kapott üzenetet.

    Végül egy végtelen ciklus tartja az alkalmazást futásban. Az MQTT kliens a háttérszálon figyeli az üzeneteket, és mindaddig fut, amíg a fő alkalmazás fut.

1. A VS Code termináljából futtassa a következőt a Python alkalmazás futtatásához:

    ```sh
    python app.py
    ```

    Az alkalmazás elkezdi figyelni az IoT eszköztől érkező üzeneteket.

1. Győződjön meg róla, hogy az eszköze fut, és telemetriai üzeneteket küld. Állítsa be a fizikai vagy virtuális eszköz által érzékelt fényerősséget. Az érkező üzenetek megjelennek a terminálban.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    A nightlight virtuális környezetben futó app.py fájlnak futnia kell ahhoz, hogy a nightlight-server virtuális környezetben futó app.py fájl megkapja a küldött üzeneteket.

> 💁 Ezt a kódot megtalálja a [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server) mappában.

### Milyen gyakran kell telemetriát küldeni?

A telemetriai adatok mérésének és küldésének gyakorisága fontos kérdés. A válasz: attól függ. Ha gyakran mér, gyorsabban reagálhat a változásokra, de több energiát, sávszélességet használ, több adatot generál, és több felhőforrásra van szükség az adatok feldolgozásához. Olyan gyakran kell mérni, hogy az elegendő legyen, de ne túl gyakran.

Egy termosztát esetében valószínűleg elég néhány percenként mérni, mivel a hőmérséklet nem változik olyan gyorsan. Ha csak naponta egyszer mér, akkor előfordulhat, hogy egy napsütéses nap közepén az éjszakai hőmérséklet alapján fűti a házat, míg ha másodpercenként mér, akkor feleslegesen sok hőmérsékleti adatot duplikál, ami csökkenti az internet sebességét és sávszélességét (probléma lehet azok számára, akik korlátozott sávszélességű csomaggal rendelkeznek), több energiát használ, ami problémát jelenthet akkumulátoros eszközök, például távoli érzékelők esetében, és növeli a felhőalapú számítási erőforrások költségeit.

Ha egy gyárban egy gép körüli adatokat figyel, amelynek meghibásodása katasztrofális károkat és milliós bevételkiesést okozhat, akkor szükség lehet másodpercenként többszöri mérésre. Jobb, ha sávszélességet pazarol, mint ha elmulaszt egy telemetriai adatot, amely arra utal, hogy a gépet le kell állítani és meg kell javítani, mielőtt tönkremegy.

> 💁 Ilyen helyzetben érdemes lehet egy edge eszközt használni, amely először feldolgozza a telemetriát, hogy csökkentse az internetre való támaszkodást.

### Kapcsolatvesztés

Az internetkapcsolatok megbízhatatlanok lehetnek, gyakoriak a kimaradások. Mit tegyen egy IoT eszköz ilyen körülmények között – elveszítse az adatokat, vagy tárolja őket, amíg a kapcsolat helyre nem áll? Ismét: a válasz attól függ.

Egy termosztát esetében az adatok valószínűleg elveszhetnek, amint egy új hőmérsékleti mérés megtörtént. A fűtési rendszer nem törődik azzal, hogy 20 perccel ezelőtt 20,5°C volt, ha most 19°C van – a jelenlegi hőmérséklet határozza meg, hogy a fűtés be legyen-e kapcsolva vagy sem.

Gépek esetében érdemes lehet megtartani az adatokat, különösen, ha azokat trendek keresésére használják. Vannak gépi tanulási modellek, amelyek képesek anomáliákat észlelni adatfolyamokban, ha egy meghatározott időszak (például az elmúlt óra) adatait vizsgálják, és szokatlan adatokat találnak. Ezt gyakran használják prediktív karbantartásra, hogy jelezzék, ha valami hamarosan tönkremehet, így még azelőtt megjavítható vagy kicserélhető, hogy ez megtörténne. Ilyen esetben minden egyes telemetriai adatot el kell küldeni, hogy feldolgozható legyen az anomália-észleléshez, így amikor az IoT eszköz újra csatlakozni tud, elküldi az internetkimaradás alatt generált összes telemetriát.

Az IoT eszköz tervezőinek azt is figyelembe kell venniük, hogy az eszköz használható-e internetkimaradás vagy helyszíni jelvesztés esetén. Egy okos termosztátnak képesnek kell lennie arra, hogy korlátozott döntéseket hozzon a fűtés vezérlésére, ha nem tud telemetriát küldeni a felhőbe egy kimaradás miatt.

[![Ez a Ferrari használhatatlanná vált, mert valaki föld alatt próbálta frissíteni, ahol nincs mobiljel](../../../../../translated_images/hu/bricked-car.dc38f8efadc6c59d.webp)](https://twitter.com/internetofshit/status/1315736960082808832)

Az MQTT kezeléséhez kapcsolatvesztés esetén az eszköz- és szerverkódnak felelősséget kell vállalnia az üzenetek kézbesítésének biztosításáért, ha szükséges, például azáltal, hogy megköveteli, hogy minden elküldött üzenetre válasz érkezzen egy válasz témán, és ha nem, akkor manuálisan sorba állítják őket későbbi újrajátszásra.

## Parancsok

A parancsok olyan üzenetek, amelyeket a felhő küld egy eszköznek, hogy utasítsa valamilyen művelet végrehajtására. Ez legtöbbször valamilyen kimenet generálását jelenti egy aktuátor segítségével, de lehet az eszközre vonatkozó utasítás is, például újraindítás vagy további telemetria gyűjtése és válaszként való visszaküldése.

![Egy internetkapcsolattal rendelkező termosztát, amely parancsot kap a fűtés bekapcsolására](../../../../../translated_images/hu/commands.d6c06bbbb3a02cce.webp)

Egy termosztát például parancsot kaphat a felhőtől a fűtés bekapcsolására. Az összes érzékelő telemetriai adatai alapján a felhőszolgáltatás úgy döntött, hogy a fűtésnek be kell kapcsolnia, ezért elküldi a megfelelő parancsot.

### Parancsok küldése az MQTT brokernek

Az interneten keresztül vezérelt éjszakai fény következő lépése az, hogy a szerverkód parancsot küldjön vissza az IoT eszköznek, hogy a fényérzékelés alapján vezérelje a fényt.

1. Nyissa meg a szerver kódját a VS Code-ban.

1. Adja hozzá a következő sort a `client_telemetry_topic` deklarációja után, hogy meghatározza, melyik témára küldjön parancsokat:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Adja hozzá a következő kódot a `handle_telemetry` függvény végéhez:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Ez egy JSON üzenetet küld a parancs témára, amelyben az `led_on` értéke true vagy false, attól függően, hogy a fény kevesebb-e, mint 300. Ha a fény kevesebb, mint 300, akkor true értéket küld, hogy utasítsa az eszközt az LED bekapcsolására.

1. Futtassa a kódot, ahogy korábban.

1. Állítsa be a fizikai vagy virtuális eszköz által érzékelt fényerősséget. Az érkező üzenetek és a küldött parancsok megjelennek a terminálban:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 A telemetria és a parancsok egy-egy témán keresztül kerülnek küldésre. Ez azt jelenti, hogy több eszköz telemetriája ugyanazon a telemetriai témán jelenik meg, és több eszköz parancsai ugyanazon a parancs témán. Ha egy adott eszköznek szeretne parancsot küldeni, használhat több témát, amelyek egyedi eszközazonosítóval vannak elnevezve, például `/commands/device1`, `/commands/device2`. Így egy eszköz csak az adott eszköznek szánt üzeneteket hallgatja.

> 💁 Ezt a kódot megtalálja a [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server) mappában.

### Parancsok kezelése az IoT eszközön

Most, hogy a szerver parancsokat küld, hozzáadhat kódot az IoT eszközhöz, hogy kezelje ez
Gondolj arra, hogy ezek az eszközök milyen üzeneteket küldhetnek vagy fogadhatnak. Milyen telemetriát küldenek? Milyen üzeneteket vagy parancsokat kaphatnak? Szerinted biztonságosak?

## Előadás utáni kvíz

[Előadás utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Áttekintés és önálló tanulás

Olvass többet az MQTT-ről az [MQTT Wikipedia oldalán](https://wikipedia.org/wiki/MQTT).

Próbálj meg saját MQTT brokert futtatni a [Mosquitto](https://www.mosquitto.org) segítségével, és csatlakozz hozzá az IoT eszközöddel és a szerver kódoddal.

> 💁 Tipp - alapértelmezés szerint a Mosquitto nem engedélyezi az anonim kapcsolódásokat (azaz felhasználónév és jelszó nélküli csatlakozást), és nem engedélyezi a kapcsolódást azon a számítógépen kívül, amelyen fut.
> Ezt egy [`mosquitto.conf` konfigurációs fájl](https://www.mosquitto.org/man/mosquitto-conf-5.html) segítségével javíthatod, amely tartalmazza a következőt:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Feladat

[Hasonlítsd össze és állítsd szembe az MQTT-t más kommunikációs protokollokkal](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.