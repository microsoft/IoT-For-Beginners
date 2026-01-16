<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9bae08314d8487cb76ddf3d8797e1544",
  "translation_date": "2025-08-27T22:16:36+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/README.md",
  "language_code": "hu"
}
-->
# Bevezetés az IoT világába

![A leckéről készült sketchnote áttekintése](../../../../../translated_images/hu/lesson-1.2606670fa61ee904687da5d6fa4e726639d524d064c895117da1b95b9ff6251d.jpg)

> Sketchnote készítette: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

Ez a lecke a [Hello IoT sorozat](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) részeként került bemutatásra a [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) keretében. A lecke két videóban került bemutatásra: egy 1 órás lecke, valamint egy 1 órás konzultáció, amely mélyebben foglalkozik a lecke egyes részeivel és válaszol a kérdésekre.

[![1. lecke: Bevezetés az IoT világába](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![1. lecke: Bevezetés az IoT világába - Konzultáció](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Kattints a fenti képekre a videók megtekintéséhez

## Előzetes kvíz

[Előzetes kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Bevezetés

Ez a lecke az Internet of Things (IoT) alapvető témáit tárgyalja, és segít elindulni a hardver beállításában.

A lecke során az alábbiakat fogjuk áttekinteni:

* [Mi az 'Internet of Things'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT eszközök](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Eszköz beállítása](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Az IoT alkalmazási területei](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT eszközök példái, amelyek körülötted lehetnek](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Mi az 'Internet of Things'?

Az 'Internet of Things' kifejezést [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) alkotta meg 1999-ben, hogy az internetet érzékelőkön keresztül összekapcsolja a fizikai világgal. Azóta a kifejezés minden olyan eszközt leír, amely kölcsönhatásba lép a körülötte lévő fizikai világgal, akár érzékelők által gyűjtött adatok révén, akár valós interakciók biztosításával aktuátorok segítségével (például kapcsolók bekapcsolása vagy LED-ek világítása), általában más eszközökhöz vagy az internethez csatlakozva.

> **Érzékelők** információt gyűjtenek a világból, például sebességet, hőmérsékletet vagy helyzetet mérnek.
>
> **Aktuátorok** elektromos jeleket alakítanak át valós interakciókká, például kapcsolók aktiválására, fények bekapcsolására, hangok létrehozására vagy vezérlőjelek küldésére más hardvereknek, például egy konnektor bekapcsolására.

Az IoT nem csupán eszközöket jelent - magában foglalja a felhőalapú szolgáltatásokat is, amelyek feldolgozhatják az érzékelők adatait, vagy kéréseket küldhetnek az IoT eszközökhöz csatlakoztatott aktuátoroknak. Ide tartoznak azok az eszközök is, amelyek nem rendelkeznek internetkapcsolattal, vagy nincs rá szükségük, ezeket gyakran edge eszközöknek nevezik. Ezek olyan eszközök, amelyek maguk képesek feldolgozni és reagálni az érzékelők adataira, általában a felhőben betanított AI modellek segítségével.

Az IoT egy gyorsan növekvő technológiai terület. Becslések szerint 2020 végére 30 milliárd IoT eszköz került telepítésre és csatlakoztatásra az internethez. A jövőre tekintve, 2025-re várhatóan az IoT eszközök közel 80 zettabájt adatot, azaz 80 trillió gigabájtot gyűjtenek majd. Ez rengeteg adat!

![Egy grafikon, amely az aktív IoT eszközök számát mutatja az idő múlásával, növekvő trendet jelezve 2015-ben kevesebb mint 5 milliárdról 2025-ben több mint 30 milliárdra](../../../../../images/connected-iot-devices.svg)

✅ Végezzen egy kis kutatást: Az IoT eszközök által generált adatok mekkora része kerül ténylegesen felhasználásra, és mennyi vész kárba? Miért hagynak figyelmen kívül ennyi adatot?

Ez az adat az IoT sikerének kulcsa. Ahhoz, hogy sikeres IoT fejlesztővé válj, meg kell értened, milyen adatokat kell gyűjtened, hogyan gyűjtsd őket, hogyan hozz döntéseket ezek alapján, és hogyan használd fel ezeket a döntéseket a fizikai világgal való interakcióra, ha szükséges.

## IoT eszközök

Az IoT-ban a **T** a **Things**-re, azaz dolgokra utal - olyan eszközökre, amelyek kölcsönhatásba lépnek a körülöttük lévő fizikai világgal, akár érzékelők által gyűjtött adatok révén, akár aktuátorok segítségével valós interakciókat biztosítva.

A gyártási vagy kereskedelmi célú eszközök, például fogyasztói fitneszkövetők vagy ipari gépvezérlők, általában egyedi tervezésűek. Egyedi áramköri lapokat, esetleg egyedi processzorokat használnak, amelyek megfelelnek egy adott feladat igényeinek, legyen az például elég kicsi ahhoz, hogy elférjen egy csuklón, vagy elég strapabíró ahhoz, hogy magas hőmérsékletű, nagy stresszű vagy erős vibrációjú gyári környezetben működjön.

Fejlesztőként, aki IoT-t tanul vagy eszköz prototípust készít, fejlesztői készlettel kell kezdened. Ezek általános célú IoT eszközök, amelyeket fejlesztők számára terveztek, gyakran olyan funkciókkal, amelyek nem lennének jelen egy gyártási eszközön, például külső csatlakozók érzékelők vagy aktuátorok csatlakoztatásához, hibakeresést támogató hardverek, vagy további erőforrások, amelyek felesleges költséget jelentenének nagy gyártási sorozat esetén.

Ezek a fejlesztői készletek általában két kategóriába sorolhatók - mikrokontrollerek és egykártyás számítógépek. Ezeket itt mutatjuk be, és a következő leckében részletesebben is foglalkozunk velük.

> 💁 A telefonodat is tekintheted általános célú IoT eszköznek, beépített érzékelőkkel és aktuátorokkal, amelyek különböző alkalmazások révén különböző módon használják az érzékelőket és aktuátorokat, különböző felhőszolgáltatásokkal együttműködve. Néhány IoT oktatóanyagban még telefonos alkalmazást is használnak IoT eszközként.

### Mikrokontrollerek

A mikrokontroller (MCU, azaz microcontroller unit) egy kis számítógép, amely a következőkből áll:

🧠 Egy vagy több központi feldolgozó egység (CPU) - a mikrokontroller "agya", amely futtatja a programodat

💾 Memória (RAM és program memória) - ahol a programod, adataid és változóid tárolódnak

🔌 Programozható bemeneti/kimeneti (I/O) csatlakozások - külső perifériák (csatlakoztatott eszközök), például érzékelők és aktuátorok kommunikációjához

A mikrokontrollerek általában alacsony költségű számítástechnikai eszközök, az egyedi hardverekben használtak átlagos ára körülbelül 0,50 USD, és néhány eszköz ára akár 0,03 USD is lehet. A fejlesztői készletek ára már 4 USD-tól kezdődik, és a funkciók bővítésével növekszik. A [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), egy mikrokontroller fejlesztői készlet a [Seeed Studios](https://www.seeedstudio.com) kínálatából, amely érzékelőkkel, aktuátorokkal, WiFi-vel és képernyővel rendelkezik, körülbelül 30 USD-ba kerül.

![Egy Wio Terminal](../../../../../translated_images/hu/wio-terminal.b8299ee16587db9a.webp)

> 💁 Az interneten mikrokontrollereket keresve légy óvatos az **MCU** kifejezés keresésével, mivel ez rengeteg találatot hoz a Marvel Cinematic Universe-re, nem pedig mikrokontrollerekre.

A mikrokontrollereket arra tervezték, hogy korlátozott számú, nagyon specifikus feladatot végezzenek, nem pedig általános célú számítógépként, mint a PC-k vagy Mac-ek. Kivéve nagyon specifikus eseteket, nem lehet hozzájuk monitort, billentyűzetet és egeret csatlakoztatni, és általános célú feladatokra használni őket.

A mikrokontroller fejlesztői készletek általában további érzékelőkkel és aktuátorokkal rendelkeznek. A legtöbb lapnak van egy vagy több programozható LED-je, valamint más eszközök, például szabványos csatlakozók további érzékelők vagy aktuátorok hozzáadásához különböző gyártók ökoszisztémájából, vagy beépített érzékelők (általában a legnépszerűbbek, például hőmérséklet-érzékelők). Néhány mikrokontroller beépített vezeték nélküli kapcsolattal, például Bluetooth vagy WiFi-vel rendelkezik, vagy további mikrokontrollerekkel a lapon, hogy hozzáadja ezt a kapcsolatot.

> 💁 A mikrokontrollereket általában C/C++ nyelven programozzák.

### Egykártyás számítógépek

Az egykártyás számítógép egy kis számítástechnikai eszköz, amely egy teljes számítógép minden elemét tartalmazza egyetlen kis lapon. Ezek olyan eszközök, amelyek specifikációi közel állnak egy asztali vagy laptop PC-hez vagy Mac-hez, teljes operációs rendszert futtatnak, de kicsik, kevesebb energiát használnak, és lényegesen olcsóbbak.

![Egy Raspberry Pi 4](../../../../../translated_images/hu/raspberry-pi-4.fd4590d308c3d456.webp)

A Raspberry Pi az egyik legnépszerűbb egykártyás számítógép.

A mikrokontrollerhez hasonlóan az egykártyás számítógépeknek is van CPU-ja, memóriája és bemeneti/kimeneti csatlakozói, de további funkciókkal rendelkeznek, például grafikus chippel, amely lehetővé teszi monitorok csatlakoztatását, audio kimeneteket és USB portokat billentyűzetek, egerek és más szabványos USB eszközök, például webkamerák vagy külső tárolók csatlakoztatásához. A programok SD kártyákon vagy merevlemezeken tárolódnak az operációs rendszerrel együtt, nem pedig a lapba épített memóriachipen.

> 🎓 Az egykártyás számítógépet úgy képzelheted el, mint a PC vagy Mac kisebb, olcsóbb verzióját, amelyen GPIO (általános célú bemeneti/kimeneti) csatlakozók vannak az érzékelőkkel és aktuátorokkal való interakcióhoz.

Az egykártyás számítógépek teljes értékű számítógépek, így bármilyen nyelven programozhatók. Az IoT eszközöket általában Python nyelven programozzák.

### Hardverválasztás a további leckékhez

A következő leckék mindegyike tartalmaz feladatokat, amelyekben egy IoT eszközt használsz a fizikai világgal való interakcióra és a felhővel való kommunikációra. Minden lecke három eszközválasztási lehetőséget támogat: Arduino (Seeed Studios Wio Terminal használatával), vagy egy egykártyás számítógép, akár fizikai eszköz (Raspberry Pi 4), akár virtuális egykártyás számítógép, amely a PC-d vagy Mac-ed futtatja.

A szükséges hardverről, amely az összes feladat elvégzéséhez szükséges, a [hardver útmutatóban](../../../hardware.md) olvashatsz.

> 💁 Nem szükséges IoT hardvert vásárolnod a feladatok elvégzéséhez, mindent megtehetsz egy virtuális egykártyás számítógép használatával.

Melyik hardvert választod, az rajtad múlik - attól függ, hogy mi áll rendelkezésedre otthon vagy az iskolában, és milyen programozási nyelvet ismersz vagy tervezel megtanulni. Mindkét hardverváltozat ugyanazt az érzékelő ökoszisztémát használja, így ha az egyik úton indulsz el, később átválthatsz a másikra anélkül, hogy a készlet nagy részét ki kellene cserélned. A virtuális egykártyás számítógép egy Raspberry Pi tanulásának megfelelője lesz, és a legtöbb kód átváltható a Pi-re, ha végül beszerzel egy eszközt és érzékelőket.

### Arduino fejlesztői készlet

Ha érdekel a mikrokontroller fejlesztés, a feladatokat egy Arduino eszközzel végezheted el. Alapvető C/C++ programozási ismeretekre lesz szükséged, mivel a leckék csak az Arduino keretrendszerhez, az érzékelőkhöz és aktuátorokhoz, valamint a felhővel való interakciót biztosító könyvtárakhoz kapcsolódó kódot tanítanak.

A feladatokhoz [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) és a [PlatformIO mikrokontroller fejlesztési bővítmény](https://platformio.org) használata szükséges. Ha tapasztalt vagy az Arduino IDE használatában, azt is használhatod, mivel ehhez nem lesznek instrukciók.

### Egykártyás számítógép fejlesztői készlet

Ha érdekel az IoT fejlesztés egykártyás számítógépek használatával, a feladatokat Raspberry Pi-vel vagy egy virtuális eszközzel végezheted el, amely a PC-d vagy Mac-ed futtatja.

Alapvető Python programozási ismeretekre lesz szükséged, mivel a leckék csak az érzékelőkhöz és aktuátorokhoz, valamint a felhővel való interakciót biztosító könyvtárakhoz kapcsolódó kódot tanítanak.

> 💁 Ha szeretnél Python programozást tanulni, nézd meg az alábbi két videósorozatot:
>
> * [Python kezdőknek](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [További Python kezdőknek](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

A feladatokhoz [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) használata szükséges.

Ha Raspberry Pi-t használsz, futtathatod a Pi-t a Raspberry Pi OS teljes asztali verziójával, és közvetlenül a Pi-n végezheted a kódolást a [Raspberry Pi OS verziójú VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn) használatával, vagy futtathatod a Pi-t fej nélküli eszközként, és a PC-d vagy Mac-ed segítségével kódolhatsz a VS Code [Remote SSH bővítményével](https://code.visualstudio.com
💁 Ha még nincs eszközöd, nézd meg a [hardver útmutatót](../../../hardware.md), hogy segítsen eldönteni, melyik eszközt fogod használni, és milyen további hardvert kell megvásárolnod. Nem szükséges hardvert vásárolnod, mivel az összes projekt futtatható virtuális hardveren.
Ezek az utasítások harmadik fél weboldalaira mutató hivatkozásokat tartalmaznak, amelyek a hardverek vagy eszközök készítőitől származnak. Ez azért van, hogy mindig a legfrissebb útmutatásokat használhasd az eszközökhöz és hardverekhez.

Dolgozd végig a megfelelő útmutatót, hogy beállítsd az eszközödet, és készíts egy "Hello World" projektet. Ez lesz az első lépés egy IoT éjszakai fény létrehozásában, amelyet a kezdő szakasz négy leckéje során fogsz elkészíteni.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Egylapkás számítógép - Raspberry Pi](pi.md)
* [Egylapkás számítógép - Virtuális eszköz](virtual-device.md)

✅ Az Arduino és az egylapkás számítógépek esetében is a VS Code-ot fogod használni. Ha még nem használtad korábban, olvass róla többet a [VS Code weboldalán](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## Az IoT alkalmazásai

Az IoT számos felhasználási területet ölel fel, néhány szélesebb kategóriába sorolva:

* Fogyasztói IoT
* Kereskedelmi IoT
* Ipari IoT
* Infrastruktúra IoT

✅ Végezz egy kis kutatást: Az alább leírt területek mindegyikéhez találj egy konkrét példát, amelyet a szöveg nem említ.

### Fogyasztói IoT

A fogyasztói IoT olyan IoT eszközökre utal, amelyeket a fogyasztók vásárolnak és otthonukban használnak. Néhány ilyen eszköz rendkívül hasznos, például okoshangszórók, okos fűtési rendszerek és robotporszívók. Mások hasznossága megkérdőjelezhető, például hangvezérelt csapok, amelyeket nem lehet kikapcsolni, ha a hangvezérlés nem hallja a futó víz zaját.

A fogyasztói IoT eszközök lehetővé teszik az emberek számára, hogy többet érjenek el környezetükben, különösen az 1 milliárd fogyatékossággal élő ember számára. A robotporszívók tiszta padlót biztosíthatnak azoknak, akik mozgáskorlátozottak és nem tudnak maguk porszívózni, a hangvezérelt sütők lehetővé teszik a gyengénlátó vagy motorikus problémákkal küzdő emberek számára, hogy csak hangjukkal melegítsék fel a sütőjüket, az egészségügyi monitorok pedig lehetővé teszik a betegek számára, hogy krónikus állapotukat rendszeresebb és részletesebb frissítésekkel kövessék nyomon. Ezek az eszközök annyira elterjedtek, hogy még a kisgyerekek is használják őket napi szinten, például a COVID-járvány alatt virtuális oktatásban részt vevő diákok okosotthoni eszközökön állítanak be időzítőket, hogy nyomon kövessék iskolai feladataikat, vagy riasztásokat állítsanak be a közelgő órákra.

✅ Milyen fogyasztói IoT eszközök vannak nálad vagy az otthonodban?

### Kereskedelmi IoT

A kereskedelmi IoT az IoT munkahelyi használatát foglalja magában. Egy irodai környezetben lehetnek jelenlétérzékelők és mozgásérzékelők, amelyek a világítást és a fűtést kezelik, hogy csak akkor legyenek bekapcsolva, amikor szükséges, csökkentve ezzel a költségeket és a szén-dioxid-kibocsátást. Egy gyárban az IoT eszközök biztonsági veszélyeket figyelhetnek, például azt, hogy a dolgozók nem viselnek védősisakot, vagy hogy a zajszint elérte a veszélyes szintet. A kiskereskedelemben az IoT eszközök mérhetik a hűtőtárolók hőmérsékletét, figyelmeztetve a bolt tulajdonosát, ha egy hűtő vagy fagyasztó a szükséges hőmérsékleti tartományon kívül esik, vagy figyelhetik a polcokon lévő árukat, hogy irányítsák az alkalmazottakat az eladott termékek pótlására. A közlekedési ipar egyre inkább támaszkodik az IoT-ra, hogy figyelje a járművek helyzetét, nyomon kövesse az úton megtett kilométereket az úthasználati díjhoz, ellenőrizze a sofőrök munkaidejét és pihenési szabályainak betartását, vagy értesítse a személyzetet, amikor egy jármű közeledik egy telephelyhez, hogy felkészüljenek a rakodásra vagy kirakodásra.

✅ Milyen kereskedelmi IoT eszközök vannak az iskoládban vagy munkahelyeden?

### Ipari IoT (IIoT)

Az ipari IoT, vagy IIoT, az IoT eszközök használatát jelenti a gépek nagy léptékű irányítására és kezelésére. Ez számos felhasználási területet ölel fel, a gyáraktól a digitális mezőgazdaságig.

A gyárak számos különböző módon használják az IoT eszközöket. A gépeket több érzékelővel lehet monitorozni, amelyek olyan adatokat gyűjtenek, mint a hőmérséklet, a rezgés és a forgási sebesség. Ezeket az adatokat figyelemmel lehet kísérni, hogy a gépet leállítsák, ha bizonyos tűréshatárokon kívül esik - például túlmelegszik, és ezért leállítják. Az adatokat idővel össze lehet gyűjteni és elemezni, hogy előrejelző karbantartást végezzenek, ahol az AI modellek elemzik az adatokat, amelyek egy meghibásodás előtt keletkeztek, és ezt felhasználják más meghibásodások előrejelzésére, mielőtt azok bekövetkeznének.

A digitális mezőgazdaság kulcsfontosságú, ha a bolygónak el kell látnia a növekvő népességet, különösen annak a 2 milliárd embernek, akik 500 millió háztartásban önellátó gazdálkodásból élnek. A digitális mezőgazdaság néhány dolláros érzékelőktől hatalmas kereskedelmi rendszerekig terjedhet. Egy gazda kezdheti a hőmérséklet monitorozásával, és a [növekedési foknapok](https://wikipedia.org/wiki/Growing_degree-day) segítségével megjósolhatja, mikor lesz egy termés betakarításra kész. Talajnedvesség-érzékelőket csatlakoztathat automatizált öntözőrendszerekhez, hogy növényeinek annyi vizet adjon, amennyire szükségük van, de ne többet, hogy biztosítsa, hogy termései ne száradjanak ki, miközben nem pazarolja a vizet. A gazdák még tovább mennek, és drónokat, műholdas adatokat és AI-t használnak, hogy hatalmas területeken figyeljék a növények növekedését, betegségeit és a talaj minőségét.

✅ Milyen más IoT eszközök segíthetnék a gazdákat?

### Infrastruktúra IoT

Az infrastruktúra IoT a helyi és globális infrastruktúra monitorozását és irányítását jelenti, amelyet az emberek nap mint nap használnak.

[Okos városok](https://wikipedia.org/wiki/Smart_city) olyan városi területek, amelyek IoT eszközöket használnak, hogy adatokat gyűjtsenek a városról, és ezeket az adatokat felhasználják a város működésének javítására. Ezeket a városokat általában helyi kormányzatok, akadémiai intézmények és helyi vállalkozások együttműködésével irányítják, és olyan dolgokat követnek nyomon és kezelnek, mint a közlekedés, parkolás és szennyezés. Például Koppenhágában, Dániában a levegőszennyezés fontos a helyi lakosok számára, ezért azt mérik, és az adatokat arra használják, hogy információt nyújtsanak a legtisztább kerékpáros és futó útvonalakról.

[Okos elektromos hálózatok](https://wikipedia.org/wiki/Smart_grid) lehetővé teszik a villamosenergia-igény jobb elemzését azáltal, hogy adatokat gyűjtenek az egyes otthonok szintjén. Ezek az adatok országos szinten irányíthatják a döntéseket, például hogy hol építsenek új erőműveket, és személyes szinten is, például betekintést nyújtanak a felhasználóknak abba, hogy mennyi energiát használnak, mikor használják, és még javaslatokat is adhatnak a költségek csökkentésére, például az elektromos autók éjszakai töltésére.

✅ Ha IoT eszközöket adhatnál hozzá, hogy bármit mérjenek ott, ahol élsz, mit mérnél?

## Példák IoT eszközökre, amelyek körülötted lehetnek

Meglepődnél, hogy mennyi IoT eszköz van körülötted. Én otthonról írom ezt, és a következő eszközök vannak csatlakoztatva az internethez, okos funkciókkal, például alkalmazásvezérléssel, hangvezérléssel vagy azzal a képességgel, hogy adatokat küldjenek nekem a telefonomra:

* Több okoshangszóró
* Hűtőszekrény, mosogatógép, sütő és mikrohullámú sütő
* Napelemekhez kapcsolódó elektromos monitor
* Okos konnektorok
* Videós kapucsengő és biztonsági kamerák
* Okos termosztát több okos szobai érzékelővel
* Garázskapu nyitó
* Otthoni szórakoztató rendszerek és hangvezérelt TV-k
* Világítás
* Fitnesz- és egészségügyi nyomkövetők

Ezek az eszközök mind érzékelőkkel és/vagy működtetőkkel rendelkeznek, és kommunikálnak az internettel. A telefonomról meg tudom mondani, hogy nyitva van-e a garázskapum, és megkérhetem az okoshangszórómat, hogy zárja be. Beállíthatok időzítőt is, hogy ha éjszaka még nyitva van, automatikusan bezáródjon. Amikor a kapucsengőm cseng, a telefonomról láthatom, ki van ott, bárhol is vagyok a világban, és beszélhetek velük a kapucsengőbe épített hangszórón és mikrofonon keresztül. Nyomon követhetem a vércukorszintemet, a szívritmusomat és az alvási mintáimat, keresve az adatmintákat, hogy javítsam az egészségemet. A világítást a felhőn keresztül vezérelhetem, és sötétben ülök, amikor az internetkapcsolatom megszakad.

---

## 🚀 Kihívás

Sorolj fel minél több IoT eszközt, amely az otthonodban, iskoládban vagy munkahelyeden található - lehet, hogy több van, mint gondolnád!

## Előadás utáni kvíz

[Előadás utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Áttekintés és önálló tanulás

Olvass utána a fogyasztói IoT projektek előnyeinek és kudarcainak. Nézz utána híroldalakon olyan cikkeknek, amelyek a problémákról szólnak, például adatvédelmi kérdésekről, hardverproblémákról vagy a kapcsolódás hiányából eredő problémákról.

Néhány példa:

* Nézd meg a Twitter fiókot **[Internet of Sh*t](https://twitter.com/internetofshit)** *(figyelmeztetés: trágár nyelvezet)*, ahol jó példákat találsz a fogyasztói IoT kudarcaira.
* [c|net - Az Apple Watch megmentette az életem: 5 ember osztja meg történetét](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - ADT technikus bűnösnek vallja magát, mert éveken át kémkedett ügyfelek kameráin keresztül](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(figyelmeztetés: nem beleegyezésen alapuló kukkolás)*

## Feladat

[Vizsgálj meg egy IoT projektet](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.