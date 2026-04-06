# Automatikus növényöntözés

![A lecke vázlatos áttekintése](../../../../../translated_images/hu/lesson-7.30b5f577d3cb8e03.webp)

> Vázlatrajz: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

Ezt a leckét a [IoT for Beginners Project 2 - Digital Agriculture sorozat](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) részeként tanították a [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) keretében.

[![IoT által vezérelt automatikus növényöntözés](https://img.youtube.com/vi/g9FfZwv9R58/0.jpg)](https://youtu.be/g9FfZwv9R58)

## Előzetes kvíz

[Előzetes kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/13)

## Bevezetés

Az előző leckében megtanultad, hogyan figyeld a talajnedvességet. Ebben a leckében megtanulod, hogyan építsd meg egy automatikus öntözőrendszer alapvető elemeit, amely reagál a talajnedvességre. Emellett megismered az időzítést is – hogyan reagálnak az érzékelők a változásokra, és hogyan változtatják meg az aktuátorok az érzékelők által mért tulajdonságokat.

Ebben a leckében a következőket fogjuk tárgyalni:

* [Nagy teljesítményű eszközök vezérlése alacsony teljesítményű IoT eszközökről](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Relé vezérlése](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Növényed vezérlése MQTT-n keresztül](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Érzékelők és aktuátorok időzítése](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Időzítés hozzáadása a növényvezérlő szerveredhez](../../../../../2-farm/lessons/3-automated-plant-watering)

## Nagy teljesítményű eszközök vezérlése alacsony teljesítményű IoT eszközökről

Az IoT eszközök alacsony feszültséget használnak. Ez elegendő az érzékelők és alacsony teljesítményű aktuátorok, például LED-ek működtetéséhez, de túl alacsony a nagyobb hardverek, például öntözéshez használt vízpumpák vezérléséhez. Még a szobanövényekhez használt kis pumpák is túl sok áramot igényelnek egy IoT fejlesztői készlet számára, és tönkretennék az áramkört.

> 🎓 Az áramot, amelyet Amperben (A) mérünk, az elektromos áramkörön áthaladó elektromosság mennyiségeként határozzuk meg. A feszültség biztosítja a nyomást, az áram pedig azt mutatja meg, hogy mennyi elektromosságot nyomunk át. További információt az áramról a [Wikipedia elektromos áram oldalán](https://wikipedia.org/wiki/Electric_current) találhatsz.

A megoldás az, hogy a pumpát egy külső áramforráshoz csatlakoztatjuk, és egy aktuátort használunk a pumpa bekapcsolására, hasonlóan ahhoz, ahogy egy lámpát kapcsolnánk fel. Csak egy kis energia (például a tested energiája) szükséges ahhoz, hogy az ujjaddal felkapcsolj egy kapcsolót, amely összeköti a lámpát a 110V/240V-os hálózati árammal.

![Egy villanykapcsoló bekapcsolja a lámpát](../../../../../translated_images/hu/light-switch.760317ad6ab8bd6d.webp)

> 🎓 A [hálózati áram](https://wikipedia.org/wiki/Mains_electricity) az otthonokba és vállalkozásokba nemzeti infrastruktúrán keresztül szállított elektromosságot jelenti a világ számos részén.

✅ Az IoT eszközök általában 3,3V vagy 5V feszültséget tudnak biztosítani, kevesebb mint 1 amper (1A) áramerősséggel. Ezt hasonlítsd össze a hálózati árammal, amely leggyakrabban 230V (Észak-Amerikában 120V, Japánban pedig 100V), és akár 30A áramot is biztosíthat az eszközök számára.

Számos aktuátor létezik, amelyek ezt megtehetik, beleértve a mechanikus eszközöket, amelyeket meglévő kapcsolókhoz csatlakoztathatsz, hogy utánozzák az ujj mozgását. A legnépszerűbb ezek közül a relé.

### Relék

A relé egy elektromechanikus kapcsoló, amely egy elektromos jelet mechanikus mozgássá alakít, amely bekapcsol egy kapcsolót. A relé magja egy elektromágnes.

> 🎓 Az [elektromágnesek](https://wikipedia.org/wiki/Electromagnet) olyan mágnesek, amelyeket egy huzaltekercsen keresztül áramot vezetve hoznak létre. Amikor az áram bekapcsol, a tekercs mágnesessé válik. Amikor az áram kikapcsol, a tekercs elveszíti mágnesességét.

![Bekapcsolt állapotban az elektromágnes mágneses mezőt hoz létre, amely bekapcsolja a kimeneti áramkör kapcsolóját](../../../../../translated_images/hu/relay-on.4db16a0fd6b66926.webp)

Egy relében egy vezérlő áramkör táplálja az elektromágnest. Amikor az elektromágnes bekapcsol, egy kart húz meg, amely egy kapcsolót mozgat, és zárja a kimeneti áramkör érintkezőit.

![Kikapcsolt állapotban az elektromágnes nem hoz létre mágneses mezőt, amely kikapcsolja a kimeneti áramkör kapcsolóját](../../../../../translated_images/hu/relay-off.c34a178a2960fecd.webp)

Amikor a vezérlő áramkör kikapcsol, az elektromágnes kikapcsol, elengedve a kart, és megszakítva az érintkezőket, kikapcsolva a kimeneti áramkört. A relék digitális aktuátorok – egy magas jel bekapcsolja a relét, egy alacsony jel kikapcsolja.

A kimeneti áramkör további hardverek, például egy öntözőrendszer táplálására használható. Az IoT eszköz bekapcsolhatja a relét, amely zárja a kimeneti áramkört, amely táplálja az öntözőrendszert, és a növények vizet kapnak. Az IoT eszköz ezután kikapcsolhatja a relét, megszakítva az öntözőrendszer áramellátását, és elzárva a vizet.

![Egy relé bekapcsolása, amely bekapcsol egy pumpát, vizet juttatva egy növényhez](../../../../../images/strawberry-pump.gif)

A fenti videóban egy relé bekapcsol. Egy LED a relén világít, jelezve, hogy be van kapcsolva (néhány relépanelen LED-ek jelzik, hogy a relé be- vagy kikapcsolt állapotban van), és áramot küld a pumpának, amely bekapcsol és vizet pumpál egy növénybe.

> 💁 A relék arra is használhatók, hogy két kimeneti áramkör között váltsanak, ahelyett hogy egyet be- vagy kikapcsolnának. Ahogy a kar mozog, egy kapcsolót mozgat, amely az egyik kimeneti áramkör zárásától a másik zárásáig vált, általában közös áramforrás vagy közös földelés használatával.

✅ Kutass egy kicsit: Számos különböző típusú relé létezik, amelyek különböznek például abban, hogy a vezérlő áramkör bekapcsolja vagy kikapcsolja-e a relét, amikor áramot kap, vagy hogy több kimeneti áramkörrel rendelkeznek-e. Tudj meg többet ezekről a különböző típusokról.

Amikor a kar mozog, általában hallhatod, ahogy az elektromágnessel érintkezik, egy jól hallható kattanó hangot adva.

> 💁 Egy relé úgy is beköthető, hogy a kapcsolat létrehozása valójában megszakítja a relé áramellátását, kikapcsolva a relét, amely aztán újra áramot küld a relének, bekapcsolva azt, és így tovább. Ez azt jelenti, hogy a relé hihetetlenül gyorsan kattog, zümmögő hangot adva. Ez az első elektromos csengőkben használt zümmögők működési elve.

### Relé teljesítmény

Az elektromágnesnek nincs szüksége sok energiára ahhoz, hogy aktiválódjon és meghúzza a kart, vezérelhető a 3,3V vagy 5V kimenettel egy IoT fejlesztői készletről. A kimeneti áramkör sokkal nagyobb teljesítményt képes szállítani, a relétől függően, beleértve a hálózati feszültséget vagy akár ipari használatra szánt magasabb teljesítményszinteket is. Így egy IoT fejlesztői készlet vezérelhet egy öntözőrendszert, egyetlen növényhez használt kis pumpától kezdve egészen egy teljes kereskedelmi farm ipari rendszeréig.

![Egy Grove relé a vezérlő áramkörrel, kimeneti áramkörrel és relével megjelölve](../../../../../translated_images/hu/grove-relay-labelled.293e068f5c3c2a19.webp)

A fenti képen egy Grove relé látható. A vezérlő áramkör egy IoT eszközhöz csatlakozik, és 3,3V vagy 5V segítségével kapcsolja be vagy ki a relét. A kimeneti áramkör két terminállal rendelkezik, bármelyik lehet áramforrás vagy földelés. A kimeneti áramkör akár 250V-ot és 10A-t is képes kezelni, ami elegendő számos hálózati árammal működő eszközhöz. Léteznek még nagyobb teljesítményű relék is.

![Egy pumpa bekötve egy relébe](../../../../../translated_images/hu/pump-wired-to-relay.66c5cfc0d8918990.webp)

A fenti képen egy pumpa áramellátása egy relén keresztül történik. Egy piros vezeték köti össze az USB tápegység +5V terminálját a relé kimeneti áramkörének egyik termináljával, és egy másik piros vezeték köti össze a kimeneti áramkör másik terminálját a pumpával. Egy fekete vezeték köti össze a pumpát az USB tápegység földelésével. Amikor a relé bekapcsol, zárja az áramkört, 5V-ot küldve a pumpának, amely bekapcsol.

## Relé vezérlése

Egy relét vezérelhetsz az IoT fejlesztői készletedről.

### Feladat - relé vezérlése

Kövesd a megfelelő útmutatót, hogy vezérelj egy relét az IoT eszközöddel:

* [Arduino - Wio Terminal](wio-terminal-relay.md)
* [Egylapkás számítógép - Raspberry Pi](pi-relay.md)
* [Egylapkás számítógép - Virtuális eszköz](virtual-device-relay.md)

## Növényed vezérlése MQTT-n keresztül

Eddig a relét közvetlenül az IoT eszköz vezérelte egyetlen talajnedvesség-érzékelés alapján. Egy kereskedelmi öntözőrendszerben a vezérlési logika központosított, lehetővé téve, hogy több érzékelő adatai alapján hozzon döntéseket az öntözésről, és hogy bármilyen konfigurációt egyetlen helyen lehessen módosítani. Ennek szimulálására a relét MQTT-n keresztül vezérelheted.

### Feladat - relé vezérlése MQTT-n keresztül

1. Add hozzá a megfelelő MQTT könyvtárakat/pip csomagokat és kódot a `soil-moisture-sensor` projektedhez, hogy csatlakozz az MQTT-hez. Nevezd el az ügyfélazonosítót `soilmoisturesensor_client`-nek, az azonosítód előtagjával.

    > ⚠️ Hivatkozhatsz a [1. projekt, 4. lecke MQTT-hez való csatlakozásra vonatkozó utasításaira, ha szükséges](../../../1-getting-started/lessons/4-connect-internet/README.md#connect-your-iot-device-to-mqtt).

1. Add hozzá a megfelelő eszközkódot, hogy telemetriát küldj a talajnedvesség-beállításokkal. A telemetriaüzenetben nevezd el a tulajdonságot `soil_moisture`-nek.

    > ⚠️ Hivatkozhatsz a [1. projekt, 4. lecke telemetria küldésére vonatkozó utasításaira, ha szükséges](../../../1-getting-started/lessons/4-connect-internet/README.md#send-telemetry-from-your-iot-device).

1. Hozz létre egy helyi szerverkódot, amely feliratkozik a telemetriára, és parancsot küld a relé vezérlésére egy `soil-moisture-sensor-server` nevű mappában. Nevezd el a parancsüzenet tulajdonságát `relay_on`-nak, és állítsd be az ügyfélazonosítót `soilmoisturesensor_server`-nek az azonosítód előtagjával. Tartsd meg ugyanazt a szerkezeti felépítést, mint amit az 1. projekt, 4. leckében írtál, mivel később ebben a leckében hozzá fogsz adni ehhez a kódhoz.

    > ⚠️ Hivatkozhatsz a [telemetria küldésére vonatkozó utasításokra](../../../1-getting-started/lessons/4-connect-internet/README.md#write-the-server-code) és a [parancsok küldésére MQTT-n keresztül](../../../1-getting-started/lessons/4-connect-internet/README.md#send-commands-to-the-mqtt-broker) az 1. projekt, 4. leckében, ha szükséges.

1. Add hozzá a megfelelő eszközkódot, hogy a relét a fogadott parancsok alapján vezéreld, az üzenet `relay_on` tulajdonságát használva. Küldj `true` értéket a `relay_on`-hoz, ha a `soil_moisture` nagyobb, mint 450, különben küldj `false` értéket, ugyanazt a logikát követve, amit korábban az IoT eszközhöz adtál.

    > ⚠️ Hivatkozhatsz a [MQTT parancsokra való válaszadásra vonatkozó utasításokra az 1. projekt, 4. leckében, ha szükséges](../../../1-getting-started/lessons/4-connect-internet/README.md#handle-commands-on-the-iot-device).

> 💁 Ezt a kódot megtalálod a [code-mqtt](../../../../../2-farm/lessons/3-automated-plant-watering/code-mqtt) mappában.

Győződj meg róla, hogy a kód fut az eszközödön és a helyi szerveren, és teszteld a talajnedvesség-szintek változtatásával, akár a virtuális érzékelő által küldött értékek módosításával, akár a talaj nedvességtartalmának változtatásával, például víz hozzáadásával vagy az érzékelő eltávolításával a talajból.

## Érzékelők és aktuátorok időzítése

A 3. leckében építettél egy éjszakai fényt – egy LED-et, amely bekapcsol, amint az alacsony fényerősséget érzékelte a fényérzékelő. A fényérzékelő azonnal érzékelte a fényerősség változását, és az eszköz gyorsan tudott reagálni, csak a `loop` függvény vagy a `while True:` ciklus késleltetésének hosszúsága korlátozta. IoT fejlesztőként azonban nem mindig számíthatsz ilyen gyors visszacsatolási ciklusra.

### Talajnedvesség időzítése

Ha az előző leckében fizikai érzékelőt használtál a talajnedvesség mérésére, észrevehetted, hogy néhány másodpercbe telt, mire a talajnedvess
💁 Ha túl közel öntöztél az érzékelőhöz, előfordulhatott, hogy a mérés gyorsan leesett, majd visszaemelkedett – ezt az okozza, hogy az érzékelő közelében lévő víz szétterjed a talaj többi részében, csökkentve az érzékelő által mért talajnedvességet.
![A talajnedvesség-mérés 658-at mutat, amely öntözés közben nem változik, csak akkor csökken 320-ra, amikor a víz átszivárog a talajon](../../../../../translated_images/hu/soil-moisture-travel.a0e31af222cf1438.webp)

A fenti ábrán egy talajnedvesség-érzékelő 658-as értéket mutat. A növényt megöntözik, de ez az érték nem változik azonnal, mivel a víz még nem érte el az érzékelőt. Az öntözés akár be is fejeződhet, mielőtt a víz eléri az érzékelőt, és az érték csökken, hogy tükrözze az új nedvességszintet.

Ha kódot írnál egy relén alapuló öntözőrendszer vezérlésére a talajnedvesség szintje alapján, figyelembe kell venned ezt a késleltetést, és okosabb időzítést kell beépítened az IoT eszközödbe.

✅ Gondolkodj el egy pillanatra, hogyan oldanád meg ezt.

### Az érzékelő és az aktuátor időzítésének vezérlése

Képzeld el, hogy egy farm öntözőrendszerének megépítésével bíztak meg. A talajtípus alapján az ideális talajnedvesség szintje a növények számára egy 400-450 közötti analóg feszültségértéknek felel meg.

Az eszközt úgy is programozhatnád, mint az éjszakai fényt – amíg az érzékelő 450 feletti értéket mutat, kapcsold be a relét, hogy elindítsa a szivattyút. A probléma az, hogy a víznek időbe telik, míg a szivattyútól a talajon keresztül az érzékelőhöz ér. Az érzékelő leállítja a vizet, amikor 450-es szintet érzékel, de a vízszint tovább csökken, mivel a szivattyúzott víz tovább szivárog a talajon keresztül. Az eredmény pazarlás és a gyökerek károsodásának kockázata.

✅ Ne feledd – a túl sok víz ugyanolyan káros lehet a növények számára, mint a túl kevés, és egy értékes erőforrást pazarol.

A jobb megoldás az, ha megérted, hogy késleltetés van az aktuátor bekapcsolása és az érzékelő által mért tulajdonság változása között. Ez azt jelenti, hogy nemcsak az érzékelőnek kell várnia egy ideig, mielőtt újra mér, hanem az aktuátornak is ki kell kapcsolnia egy időre, mielőtt a következő érzékelési ciklus elkezdődik.

Mennyi ideig legyen bekapcsolva a relé minden alkalommal? Jobb óvatosnak lenni, és csak rövid időre bekapcsolni a relét, majd várni, hogy a víz átszivárogjon, és újra ellenőrizni a nedvességszintet. Végül is mindig újra bekapcsolhatod, hogy több vizet adj hozzá, de nem tudod eltávolítani a vizet a talajból.

> 💁 Az ilyen időzítésvezérlés nagyon specifikus az épített IoT eszközre, a mért tulajdonságra, valamint az érzékelőkre és aktuátorokra.

![Egy epernövény, amelyet egy szivattyún keresztül vízzel látnak el, a szivattyú egy reléhez csatlakozik. A relé és a talajnedvesség-érzékelő egy Raspberry Pi-hez van csatlakoztatva](../../../../../translated_images/hu/strawberry-with-pump.b410fc72ac6aabad.webp)

Például van egy epernövényem, amelyhez egy talajnedvesség-érzékelő és egy relével vezérelt szivattyú tartozik. Megfigyeltem, hogy amikor vizet adok hozzá, körülbelül 20 másodpercbe telik, mire a talajnedvesség-érték stabilizálódik. Ez azt jelenti, hogy ki kell kapcsolnom a relét, és 20 másodpercet kell várnom, mielőtt ellenőrzöm a nedvességszintet. Inkább legyen túl kevés víz, mint túl sok – mindig újra bekapcsolhatom a szivattyút, de nem tudom eltávolítani a vizet a növényből.

![1. lépés: mérés. 2. lépés: víz hozzáadása. 3. lépés: várakozás, hogy a víz átszivárogjon a talajon. 4. lépés: újramérés](../../../../../translated_images/hu/soil-moisture-delay.865f3fae206db01d.webp)

Ez azt jelenti, hogy a legjobb folyamat egy öntözési ciklushoz valami ilyesmi lenne:

* Kapcsold be a szivattyút 5 másodpercre
* Várj 20 másodpercet
* Ellenőrizd a talajnedvességet
* Ha a szint még mindig a szükséges érték felett van, ismételd meg a fenti lépéseket

Az 5 másodperc túl hosszú lehet a szivattyú számára, különösen, ha a nedvességszint csak kissé haladja meg a szükséges szintet. A legjobb módja annak, hogy megtudd, milyen időzítést használj, az, ha kipróbálod, majd az érzékelő adatai alapján állítasz rajta, egy folyamatos visszacsatolási ciklussal. Ez akár finomabb időzítéshez is vezethet, például a szivattyú 1 másodpercre történő bekapcsolásához minden 100-zal a szükséges talajnedvesség feletti érték esetén, ahelyett, hogy fix 5 másodpercet használnál.

✅ Kutass egy kicsit: Vannak más időzítési szempontok? Bármikor lehet öntözni, amikor a talajnedvesség túl alacsony, vagy vannak olyan napszakok, amelyek jók vagy rosszak a növények öntözésére?

> 💁 Az időjárás-előrejelzéseket is figyelembe lehet venni a kültéri termesztéshez használt automatikus öntözőrendszerek vezérlésekor. Ha eső várható, az öntözést el lehet halasztani az eső utánra. Ekkor a talaj már elég nedves lehet ahhoz, hogy ne legyen szükség öntözésre, ami sokkal hatékonyabb, mint közvetlenül az eső előtt öntözni és vizet pazarolni.

## Időzítés hozzáadása a növényvezérlő szerveredhez

A szerver kódját módosítani lehet, hogy hozzáadjuk az öntözési ciklus időzítésének vezérlését, és várjunk a talajnedvesség szintjének változására. A relé időzítésének vezérlésére szolgáló szerverlogika a következő:

1. Telemetriaüzenet érkezik
1. Ellenőrizd a talajnedvesség szintjét
1. Ha rendben van, ne csinálj semmit. Ha az érték túl magas (ami azt jelenti, hogy a talajnedvesség túl alacsony), akkor:
    1. Küldj egy parancsot a relé bekapcsolására
    1. Várj 5 másodpercet
    1. Küldj egy parancsot a relé kikapcsolására
    1. Várj 20 másodpercet, hogy a talajnedvesség szintje stabilizálódjon

Az öntözési ciklus, azaz a telemetriaüzenet fogadásától a talajnedvesség szintjének újbóli feldolgozására való készenlétig tartó folyamat körülbelül 25 másodpercet vesz igénybe. A talajnedvesség szintjét 10 másodpercenként küldjük, így van egy átfedés, amikor egy üzenet érkezik, miközben a szerver a talajnedvesség szintjének stabilizálódására vár, ami újabb öntözési ciklust indíthat el.

Két lehetőség van ennek megoldására:

* Módosítsd az IoT eszköz kódját, hogy csak percenként küldjön telemetriát, így az öntözési ciklus befejeződik, mielőtt a következő üzenet érkezik
* Iratkozz le a telemetriáról az öntözési ciklus alatt

Az első lehetőség nem mindig jó megoldás nagy farmok esetében. A gazda például szeretné rögzíteni a talajnedvesség szintjét az öntözés közben későbbi elemzés céljából, például hogy tisztában legyen a víz áramlásával a farm különböző területein, és célzottabb öntözést végezzen. A második lehetőség jobb – a kód egyszerűen figyelmen kívül hagyja a telemetriát, amikor nem tudja használni, de a telemetria továbbra is elérhető más szolgáltatások számára, amelyek feliratkozhatnak rá.

> 💁 Az IoT adatok nem csak egy eszközről egy szolgáltatásra kerülnek továbbításra, hanem sok eszköz küldhet adatokat egy közvetítőhöz, és sok szolgáltatás hallgathatja az adatokat a közvetítőről. Például egy szolgáltatás hallgathatja a talajnedvesség adatokat, és elmentheti azokat egy adatbázisba későbbi elemzés céljából. Egy másik szolgáltatás ugyanazt a telemetriát hallgathatja, hogy vezérelje az öntözőrendszert.

### Feladat – adj időzítést a növényvezérlő szerveredhez

Frissítsd a szerver kódját, hogy a relé 5 másodpercig működjön, majd 20 másodpercet várjon.

1. Nyisd meg a `soil-moisture-sensor-server` mappát a VS Code-ban, ha még nincs megnyitva. Győződj meg róla, hogy a virtuális környezet aktiválva van.

1. Nyisd meg az `app.py` fájlt

1. Add hozzá a következő kódot az `app.py` fájl meglévő importjai alá:

    ```python
    import threading
    ```

    Ez az utasítás importálja a `threading` modult a Python könyvtárakból, amely lehetővé teszi, hogy a Python más kódot is végrehajtson várakozás közben.

1. Add hozzá a következő kódot a telemetriaüzeneteket kezelő `handle_telemetry` függvény elé:

    ```python
    water_time = 5
    wait_time = 20
    ```

    Ez meghatározza, hogy mennyi ideig működjön a relé (`water_time`), és mennyi ideig várjon utána, hogy ellenőrizze a talajnedvességet (`wait_time`).

1. Ezután add hozzá a következő kódot:

    ```python
    def send_relay_command(client, state):
        command = { 'relay_on' : state }
        print("Sending message:", command)
        client.publish(server_command_topic, json.dumps(command))
    ```

    Ez a kód definiál egy `send_relay_command` nevű függvényt, amely egy parancsot küld az MQTT-n keresztül a relé vezérlésére. A telemetria egy szótárként jön létre, majd JSON karakterlánccá alakul. A `state`-be átadott érték határozza meg, hogy a relé be- vagy kikapcsoljon.

1. A `send_relay_code` függvény után add hozzá a következő kódot:

    ```python
    def control_relay(client):
        print("Unsubscribing from telemetry")
        mqtt_client.unsubscribe(client_telemetry_topic)
    
        send_relay_command(client, True)
        time.sleep(water_time)
        send_relay_command(client, False)
    
        time.sleep(wait_time)
    
        print("Subscribing to telemetry")
        mqtt_client.subscribe(client_telemetry_topic)
    ```

    Ez egy függvényt definiál a relé vezérlésére az előírt időzítés alapján. Először leiratkozik a telemetriáról, hogy a talajnedvesség üzeneteket ne dolgozza fel az öntözés alatt. Ezután küld egy parancsot a relé bekapcsolására. Ezután vár a `water_time` idejéig, mielőtt küld egy parancsot a relé kikapcsolására. Végül vár a talajnedvesség szintjének stabilizálódására `wait_time` másodpercig. Ezután újra feliratkozik a telemetriára.

1. Módosítsd a `handle_telemetry` függvényt a következőre:

    ```python
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['soil_moisture'] > 450:
            threading.Thread(target=control_relay, args=(client,)).start()
    ```

    Ez a kód ellenőrzi a talajnedvesség szintjét. Ha az 450 felett van, a talaj öntözést igényel, így meghívja a `control_relay` függvényt. Ez a függvény egy külön szálon fut, a háttérben.

1. Győződj meg róla, hogy az IoT eszközöd fut, majd futtasd ezt a kódot. Változtasd a talajnedvesség szintjét, és figyeld meg, mi történik a relével – 5 másodpercig be kell kapcsolnia, majd legalább 20 másodpercig kikapcsolva maradnia, csak akkor kapcsol be újra, ha a talajnedvesség szintje nem megfelelő.

    ```output
    (.venv) ➜  soil-moisture-sensor-server ✗ python app.py
    Message received: {'soil_moisture': 457}
    Unsubscribing from telemetry
    Sending message: {'relay_on': True}
    Sending message: {'relay_on': False}
    Subscribing to telemetry
    Message received: {'soil_moisture': 302}
    ```

    Egy szimulált öntözőrendszer tesztelésének jó módja, ha száraz talajt használsz, majd kézzel öntesz vizet, miközben a relé be van kapcsolva, és abbahagyod az öntést, amikor a relé kikapcsol.

> 💁 Ezt a kódot megtalálod a [code-timing](../../../../../2-farm/lessons/3-automated-plant-watering/code-timing) mappában.

> 💁 Ha egy szivattyút szeretnél használni egy valódi öntözőrendszer építéséhez, akkor használhatsz egy [6V-os vízszivattyút](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html) egy [USB terminál tápegységgel](https://www.adafruit.com/product/3628). Győződj meg róla, hogy a szivattyúhoz vezető vagy onnan érkező áram a relén keresztül van csatlakoztatva.

---

## 🚀 Kihívás

Tudsz más IoT vagy elektromos eszközöket említeni, amelyeknél hasonló probléma áll fenn, hogy az aktuátor hatása csak később érzékelhető az érzékelőn? Valószínűleg van néhány ilyen eszköz az otthonodban vagy az iskoládban.

* Milyen tulajdonságokat mérnek ezek az eszközök?
* Mennyi időbe telik, amíg a tulajdonság megváltozik az aktuátor használata után?
* Elfogadható-e, hogy a tulajdonság túllépi a kívánt értéket?
* Hogyan lehet visszaállítani a kívánt értékre, ha szükséges?

## Előadás utáni kvíz

[Előadás utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/14)

## Áttekintés és önálló tanulás

* Olvass többet a relékről, beleértve azok történelmi használatát a telefonközpontokban, a [relé Wikipédia oldalán](https://wikipedia.org/wiki/Relay).

## Feladat

[Hatékonyabb öntözési ciklus kialakítása](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.