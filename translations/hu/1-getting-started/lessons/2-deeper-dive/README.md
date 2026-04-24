# Mélyebb betekintés az IoT világába

![A lecke vázlatos áttekintése](../../../../../translated_images/hu/lesson-2.324b0580d620c25e.webp)

> Vázlatrajz: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

Ez a lecke a [Hello IoT sorozat](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) részeként került bemutatásra a [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) keretében. A lecke két videóból állt - egy 1 órás tanórából és egy 1 órás konzultációból, amely mélyebben foglalkozott a lecke egyes részeivel és válaszolt a kérdésekre.

[![2. lecke: Mélyebb betekintés az IoT világába](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![2. lecke: Mélyebb betekintés az IoT világába - Konzultáció](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Kattints a fenti képekre a videók megtekintéséhez

## Előzetes kvíz

[Előzetes kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Bevezetés

Ez a lecke mélyebben foglalkozik néhány, az előző leckében tárgyalt fogalommal.

A lecke témái:

* [Egy IoT alkalmazás összetevői](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Mélyebb betekintés a mikrokontrollerekbe](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Mélyebb betekintés az egykártyás számítógépekbe](../../../../../1-getting-started/lessons/2-deeper-dive)

## Egy IoT alkalmazás összetevői

Egy IoT alkalmazás két fő összetevője az *Internet* és a *dolog*. Nézzük meg ezeket részletesebben.

### A Dolog

![Egy Raspberry Pi 4](../../../../../translated_images/hu/raspberry-pi-4.fd4590d308c3d456.webp)

Az IoT **Dolog** része egy olyan eszközt jelent, amely képes kölcsönhatásba lépni a fizikai világgal. Ezek az eszközök általában kicsi, alacsony árú számítógépek, amelyek alacsony sebességgel működnek és kevés energiát használnak - például egyszerű mikrokontrollerek, amelyek néhány kilobájt RAM-mal rendelkeznek (szemben a PC-k gigabájtjaival), és csak néhány száz megahertzen működnek (szemben a PC-k gigahertzes sebességével), de olyan kevés energiát fogyasztanak, hogy akár hetekig, hónapokig vagy évekig is működhetnek elemekkel.

Ezek az eszközök érzékelők segítségével adatokat gyűjtenek a környezetükből, vagy kimeneteket és működtetőket vezérelnek, hogy fizikai változásokat idézzenek elő. Egy tipikus példa erre az okos termosztát - egy olyan eszköz, amely hőmérséklet-érzékelővel rendelkezik, egy kívánt hőmérséklet beállítására szolgáló eszközzel, például egy tárcsával vagy érintőképernyővel, valamint egy fűtési vagy hűtési rendszerhez való csatlakozással, amely bekapcsol, ha a mért hőmérséklet kívül esik a kívánt tartományon. A hőmérséklet-érzékelő érzékeli, hogy a szoba túl hideg, és egy működtető bekapcsolja a fűtést.

![Egy diagram, amely bemutatja a hőmérsékletet és egy tárcsát, mint IoT eszköz bemeneteit, valamint egy fűtőberendezés vezérlését, mint kimenetet](../../../../../translated_images/hu/basic-thermostat.a923217fd1f37e5a.webp)

Számos különböző dolog működhet IoT eszközként, az egyetlen dolgot érzékelő dedikált hardvertől a többcélú eszközökig, például az okostelefonodig! Egy okostelefon érzékelőkkel képes érzékelni a környezetét, és működtetőkkel képes kölcsönhatásba lépni a világgal - például GPS-érzékelőt használva meghatározhatja a helyzetedet, és hangszórót használva navigációs utasításokat adhat egy célállomásra.

✅ Gondolj más rendszerekre, amelyek érzékelőkből olvasnak adatokat, és ezek alapján hoznak döntéseket. Egy példa lehet a sütő termosztátja. Találsz még többet?

### Az Internet

Az IoT alkalmazás **Internet** oldala olyan alkalmazásokból áll, amelyekhez az IoT eszköz csatlakozhat adatküldés és -fogadás céljából, valamint más alkalmazásokból, amelyek feldolgozhatják az IoT eszköz adatait, és segíthetnek döntéseket hozni arról, hogy milyen kéréseket küldjenek az IoT eszköz működtetőinek.

Egy tipikus felállásban lehet egy felhőszolgáltatás, amelyhez az IoT eszköz csatlakozik, és ez a felhőszolgáltatás kezeli például a biztonságot, valamint az IoT eszköztől érkező üzenetek fogadását és az eszköznek küldött üzeneteket. Ez a felhőszolgáltatás más alkalmazásokhoz is csatlakozhat, amelyek feldolgozhatják vagy tárolhatják az érzékelő adatait, vagy más rendszerek adataival együtt használhatják azokat döntéshozatalhoz.

Az eszközök nem mindig csatlakoznak közvetlenül az Internethez WiFi-n vagy vezetékes kapcsolaton keresztül. Egyes eszközök hálózati hálózatot használnak, hogy Bluetooth-hoz hasonló technológiákon keresztül kommunikáljanak egymással, és egy internetkapcsolattal rendelkező központi eszközön keresztül csatlakozzanak.

Az okos termosztát példájánál maradva, a termosztát otthoni WiFi-n keresztül csatlakozna egy felhőszolgáltatáshoz. Ez a felhőszolgáltatás fogadná a hőmérsékleti adatokat, amelyeket egy adatbázisba írna, lehetővé téve a háztulajdonos számára, hogy egy telefonos alkalmazáson keresztül ellenőrizze az aktuális és korábbi hőmérsékleteket. Egy másik szolgáltatás a felhőben tudná, hogy a háztulajdonos milyen hőmérsékletet szeretne, és üzeneteket küldene vissza az IoT eszköznek a felhőszolgáltatáson keresztül, hogy a fűtési rendszert be- vagy kikapcsolja.

![Egy diagram, amely bemutatja a hőmérsékletet és egy tárcsát, mint IoT eszköz bemeneteit, az IoT eszköz kétirányú kommunikációját a felhővel, amely szintén kétirányú kommunikációt folytat egy telefonnal, és a fűtőberendezés vezérlését, mint az IoT eszköz kimenetét](../../../../../translated_images/hu/mobile-controlled-thermostat.4a994010473d8d6a.webp)

Egy még okosabb verzió mesterséges intelligenciát használhatna a felhőben, más IoT eszközökhöz csatlakozó érzékelők, például jelenlétérzékelők adataival, valamint időjárási adatokkal és akár a naptáraddal együtt, hogy intelligens módon állítsa be a hőmérsékletet. Például kikapcsolhatná a fűtést, ha a naptárad szerint nyaralni mész, vagy szobánként kapcsolhatná ki a fűtést attól függően, hogy melyik szobákat használod, az adatokból tanulva egyre pontosabbá válva az idő múlásával.

![Egy diagram, amely bemutatja több hőmérséklet-érzékelőt és egy tárcsát, mint IoT eszköz bemeneteit, az IoT eszköz kétirányú kommunikációját a felhővel, amely szintén kétirányú kommunikációt folytat egy telefonnal, egy naptárral és egy időjárási szolgáltatással, valamint a fűtőberendezés vezérlését, mint az IoT eszköz kimenetét](../../../../../translated_images/hu/smarter-thermostat.a75855f15d2d9e63.webp)

✅ Milyen más adatok segíthetnének egy internethez csatlakozó termosztátot még okosabbá tenni?

### IoT az Edge-en

Bár az IoT-ban az "I" az Internetet jelenti, ezeknek az eszközöknek nem feltétlenül kell csatlakozniuk az Internethez. Bizonyos esetekben az eszközök "edge" eszközökhöz csatlakozhatnak - olyan átjáró eszközökhöz, amelyek a helyi hálózaton működnek, lehetővé téve az adatok feldolgozását anélkül, hogy az Interneten keresztül kellene kommunikálni. Ez gyorsabb lehet, ha sok adat van, vagy lassú az internetkapcsolat, lehetővé teszi az offline működést, ahol az internetkapcsolat nem lehetséges, például egy hajón vagy egy humanitárius válsághelyzetben, és lehetővé teszi az adatok magánéletének megőrzését. Egyes eszközök tartalmazhatnak felhőeszközökkel létrehozott feldolgozási kódot, amelyet helyben futtatnak, hogy adatokat gyűjtsenek és reagáljanak anélkül, hogy internetkapcsolatot használnának a döntéshozatalhoz.

Egy példa erre egy okos otthoni eszköz, például egy Apple HomePod, Amazon Alexa vagy Google Home, amely a hangodat hallgatja, felhőben betanított AI modelleket használva, de helyben futtatva az eszközön. Ezek az eszközök egy bizonyos szó vagy kifejezés elhangzásakor "ébrednek fel", és csak ekkor küldik el a beszédedet az interneten keresztül feldolgozásra. Az eszköz abbahagyja a beszéd küldését, amikor megfelelő pontot érzékel, például amikor szünetet tartasz a beszédben. Minden, amit az eszköz ébresztő szava előtt mondasz, és minden, amit az eszköz hallgatásának leállítása után mondasz, nem kerül elküldésre az interneten keresztül az eszköz szolgáltatójának, és így magánjellegű marad.

✅ Gondolj más olyan forgatókönyvekre, ahol a magánélet fontos, ezért az adatok feldolgozása jobb lenne az edge-en, mint a felhőben. Tipp: gondolj IoT eszközökre, amelyek kamerákat vagy más képalkotó eszközöket tartalmaznak.

### IoT biztonság

Bármilyen internetkapcsolat esetén a biztonság fontos szempont. Van egy régi vicc, miszerint "az IoT-ben az S a biztonságot jelenti" - az IoT-ban nincs "S", ami arra utal, hogy nem biztonságos.

Az IoT eszközök egy felhőszolgáltatáshoz csatlakoznak, és ezért csak annyira biztonságosak, amennyire az a felhőszolgáltatás - ha a felhőszolgáltatás bármilyen eszköz csatlakozását engedélyezi, akkor rosszindulatú adatok küldhetők, vagy vírusos támadások történhetnek. Ennek nagyon is valós következményei lehetnek, mivel az IoT eszközök más eszközökkel lépnek kölcsönhatásba és vezérlik azokat. Például a [Stuxnet féreg](https://wikipedia.org/wiki/Stuxnet) centrifugák szelepeit manipulálta, hogy károsítsa azokat. Hackerek [gyenge biztonságot kihasználva hozzáfértek babafigyelőkhöz](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) és más otthoni megfigyelő eszközökhöz.

> 💁 Néha az IoT eszközök és edge eszközök teljesen elszigetelt hálózaton működnek az adatok magánéletének és biztonságának megőrzése érdekében. Ezt [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)) néven ismerik.

## Mélyebb betekintés a mikrokontrollerekbe

Az előző leckében bemutattuk a mikrokontrollereket. Most nézzük meg őket részletesebben.

### CPU

A CPU a mikrokontroller "agya". Ez az a processzor, amely a kódodat futtatja, és adatokat küldhet vagy fogadhat a csatlakoztatott eszközöktől. A CPU-k egy vagy több magot tartalmazhatnak - lényegében egy vagy több CPU-t, amelyek együttműködve futtatják a kódodat.

A CPU-k egy órára támaszkodnak, amely másodpercenként több millió vagy milliárd alkalommal ketyeg. Minden ketyegés, vagy ciklus, szinkronizálja a CPU által végrehajtható műveleteket. Minden ketyegésnél a CPU végrehajthat egy utasítást egy programból, például adatokat kérhet le egy külső eszközről vagy matematikai számítást végezhet. Ez a rendszeres ciklus lehetővé teszi, hogy minden művelet befejeződjön, mielőtt a következő utasítás feldolgozásra kerül.

Minél gyorsabb az óra ciklusa, annál több utasítást lehet másodpercenként feldolgozni, és így annál gyorsabb a CPU. A CPU sebességét [Hertzben (Hz)](https://wikipedia.org/wiki/Hertz) mérik, amely egy szabványos egység, ahol 1 Hz egy ciklust vagy óra ketyegést jelent másodpercenként.

> 🎓 A CPU sebességét gyakran MHz-ben vagy GHz-ben adják meg. 1MHz 1 millió Hz, 1GHz 1 milliárd Hz.

> 💁 A CPU-k a programokat a [fetch-decode-execute ciklus](https://wikipedia.org/wiki/Instruction_cycle) segítségével hajtják végre. Minden óra ketyegésnél a CPU lekéri a következő utasítást a memóriából, dekódolja, majd végrehajtja, például egy aritmetikai logikai egység (ALU) segítségével két számot ad össze. Néhány végrehajtás több ketyegést is igénybe vehet, így a következő ciklus a következő ketyegésnél fut le, miután az utasítás befejeződött.

![A fetch-decode-execute ciklus, amely bemutatja, hogy a fetch a RAM-ban tárolt programból vesz utasítást, majd dekódolja és végrehajtja azt a CPU-n](../../../../../translated_images/hu/fetch-decode-execute.2fd6f150f6280392.webp)

A mikrokontrollerek órajele sokkal alacsonyabb, mint az asztali vagy laptop számítógépeké, vagy akár a legtöbb okostelefoné. Például a Wio Terminal CPU-ja 120MHz-en, azaz 120 000 000 ciklus másodpercenként működik.

✅ Egy átlagos PC vagy Mac CPU-ja több maggal rendelkezik, amelyek több gigahertzen futnak, ami azt jelenti, hogy az óra másodpercenként milliárdszor ketyeg. Kutass utána a számítógéped órajelének, és hasonlítsd össze, hogy hányszor gyorsabb, mint a Wio Terminal.

Minden óra ciklus energiát fogyaszt és hőt termel. Minél gyorsabb a ketyegés, annál több energiát fogyaszt és annál több hőt termel. A PC-k hűtőbordákkal és ventilátorokkal távolítják el a hőt, amelyek nélkül néhány másodpercen belül túlmelegednének és leállnának. A mikrokontroll
🎓 A programmemória tárolja a kódodat, és akkor is megmarad, ha nincs áram.
🎓 A RAM-ot a program futtatására használjuk, és az áramellátás megszűnésekor törlődik.

A CPU-hoz hasonlóan a mikrokontrollerek memóriája nagyságrendekkel kisebb, mint egy PC vagy Mac esetében. Egy tipikus PC például 8 gigabájt (GB) RAM-mal rendelkezik, ami 8 000 000 000 bájtnak felel meg, és minden bájt elegendő helyet biztosít egyetlen betű vagy egy 0-255 közötti szám tárolására. Egy mikrokontroller viszont csak kilobájt (KB) RAM-mal rendelkezik, ahol egy kilobájt 1 000 bájtnak felel meg. A fent említett Wio terminál például 192KB RAM-mal rendelkezik, ami 192 000 bájt - több mint 40 000-szer kevesebb, mint egy átlagos PC!

Az alábbi diagram szemlélteti a méretkülönbséget a 192KB és 8GB között - a középen lévő kis pont jelképezi a 192KB-ot.

![Összehasonlítás a 192KB és 8GB között - több mint 40 000-szer nagyobb](../../../../../translated_images/hu/ram-comparison.6beb73541b42ac6f.webp)

A programtároló mérete szintén kisebb, mint egy PC esetében. Egy tipikus PC például 500GB-os merevlemezzel rendelkezik a programok tárolására, míg egy mikrokontroller csak kilobájtokkal vagy esetleg néhány megabájttal (MB) rendelkezik (1MB = 1 000KB, vagy 1 000 000 bájt). A Wio terminál 4MB programtárolóval rendelkezik.

✅ Végezzen egy kis kutatást: Mennyi RAM-mal és tárolóval rendelkezik az a számítógép, amelyen ezt olvassa? Hogyan viszonyul ez egy mikrokontrollerhez?

### Bemenet/Kimenet

A mikrokontrollereknek bemeneti és kimeneti (I/O) csatlakozásokra van szükségük, hogy adatokat olvassanak be szenzorokból, és vezérlőjeleket küldjenek aktuátoroknak. Általában több általános célú bemeneti/kimeneti (GPIO) tűt tartalmaznak. Ezeket a tűket szoftveresen lehet konfigurálni bemenetként (azaz jelet fogadnak), vagy kimenetként (jelet küldenek).

🧠⬅️ A bemeneti tűk szenzorok értékeinek olvasására szolgálnak.

🧠➡️ A kimeneti tűk utasításokat küldenek aktuátoroknak.

✅ Erről többet fog tanulni egy későbbi leckében.

#### Feladat

Vizsgálja meg a Wio terminált.

Ha a Wio terminált használja ezekhez a leckékhez, keresse meg a GPIO tűket. Keresse meg a *Pinout diagram* szekciót a [Wio Terminal termékoldalon](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), hogy megtudja, melyik tűk melyek. A Wio terminálhoz tartozik egy matrica, amelyet a hátoldalára ragaszthat a tűszámokkal, így ha még nem tette meg, most tegye meg.

### Fizikai méret

A mikrokontrollerek általában kicsik, a legkisebbek, például a [Freescale Kinetis KL03 MCU, amely elfér egy golf labda mélyedésében](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). Egy PC CPU-ja akár 40mm x 40mm méretű is lehet, és ez nem tartalmazza a hűtőbordákat és ventilátorokat, amelyek szükségesek ahhoz, hogy a CPU néhány másodpercnél tovább működjön túlmelegedés nélkül, ami lényegesen nagyobb, mint egy teljes mikrokontroller. A Wio terminál fejlesztői készlet, amely mikrokontrollert, tokot, képernyőt és számos csatlakozót és komponenst tartalmaz, nem sokkal nagyobb, mint egy csupasz Intel i9 CPU, és lényegesen kisebb, mint a CPU hűtőbordával és ventilátorral.

| Eszköz                          | Méret                  |
| ------------------------------- | --------------------- |
| Freescale Kinetis KL03          | 1.6mm x 2mm x 1mm     |
| Wio terminál                    | 72mm x 57mm x 12mm    |
| Intel i9 CPU, hűtőborda és ventilátor | 136mm x 145mm x 103mm |

### Keretrendszerek és operációs rendszerek

Alacsony sebességük és memóriaméretük miatt a mikrokontrollerek nem futtatnak operációs rendszert (OS) a hagyományos értelemben. Az operációs rendszer, amely a számítógépét működteti (Windows, Linux vagy macOS), sok memóriát és feldolgozási teljesítményt igényel olyan feladatokhoz, amelyek teljesen feleslegesek egy mikrokontroller számára. Ne feledje, hogy a mikrokontrollereket általában egy vagy több nagyon specifikus feladat elvégzésére programozzák, ellentétben egy általános célú számítógéppel, mint például egy PC vagy Mac, amelynek támogatnia kell egy felhasználói felületet, zenét vagy filmeket lejátszani, dokumentumokat vagy kódot írni, játékokat futtatni, vagy böngészni az interneten.

Ahhoz, hogy egy mikrokontrollert operációs rendszer nélkül programozzon, szüksége van néhány eszközre, amelyek lehetővé teszik, hogy a kódját olyan módon építse fel, hogy a mikrokontroller futtathassa, API-kat használva, amelyek kommunikálni tudnak a perifériákkal. Minden mikrokontroller különböző, ezért a gyártók általában támogatják a szabványos keretrendszereket, amelyek lehetővé teszik, hogy egy szabványos "receptet" kövessen a kódja felépítéséhez, és az bármelyik keretrendszert támogató mikrokontrolleren fusson.

Mikrokontrollereket operációs rendszerrel is lehet programozni - ezeket gyakran valós idejű operációs rendszernek (RTOS) nevezik, mivel ezek úgy vannak kialakítva, hogy valós időben kezeljék az adatküldést és -fogadást a perifériák között. Ezek az operációs rendszerek nagyon könnyűek, és olyan funkciókat biztosítanak, mint:

* Többszálúság, amely lehetővé teszi, hogy a kódja egyszerre több kódrészletet futtasson, akár több magon, akár egy magon felváltva.
* Hálózatkezelés, amely lehetővé teszi az interneten keresztüli biztonságos kommunikációt.
* Grafikus felhasználói felület (GUI) komponensek a képernyővel rendelkező eszközökön történő felhasználói felületek (UI) létrehozásához.

✅ Olvasson utána néhány különböző RTOS-nek: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Az Arduino logója](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) valószínűleg a legnépszerűbb mikrokontroller keretrendszer, különösen diákok, hobbi programozók és barkácsolók körében. Az Arduino egy nyílt forráskódú elektronikai platform, amely szoftvert és hardvert kombinál. Arduino-kompatibilis lapokat vásárolhat közvetlenül az Arduinótól vagy más gyártóktól, majd az Arduino keretrendszer segítségével programozhatja őket.

Az Arduino lapokat C vagy C++ nyelven programozzák. A C/C++ használata lehetővé teszi, hogy a kódja nagyon kicsi legyen és gyorsan fusson, ami szükséges egy korlátozott eszközön, például egy mikrokontrolleren. Az Arduino alkalmazás magját vázlatnak nevezik, amely C/C++ kódot tartalmaz két funkcióval - `setup` és `loop`. Amikor a lap elindul, az Arduino keretrendszer kódja egyszer lefuttatja a `setup` funkciót, majd folyamatosan újra és újra futtatja a `loop` funkciót, amíg az eszköz ki nem kapcsol.

A `setup` funkcióban írná meg az inicializáló kódját, például a WiFi-hez és felhőszolgáltatásokhoz való csatlakozást, vagy a bemeneti és kimeneti tűk inicializálását. A `loop` funkcióban pedig a feldolgozó kódot, például egy szenzorból való olvasást és az érték felhőbe küldését. Általában késleltetést adna a ciklus végéhez, például ha csak 10 másodpercenként szeretne szenzoradatokat küldeni, akkor 10 másodperces késleltetést adna a ciklus végéhez, hogy a mikrokontroller aludjon, energiát takarítson meg, majd 10 másodperc múlva újra futtassa a ciklust.

![Egy Arduino vázlat, amely először a setup-ot futtatja, majd folyamatosan a loop-ot](../../../../../translated_images/hu/arduino-sketch.79590cb837ff7a7c.webp)

✅ Ezt a programarchitektúrát *eseményciklusnak* vagy *üzenetciklusnak* nevezik. Sok alkalmazás használja ezt a háttérben, és ez a szabvány a legtöbb asztali alkalmazás esetében, amelyek olyan operációs rendszereken futnak, mint a Windows, macOS vagy Linux. A `loop` figyeli az üzeneteket a felhasználói felület komponenseitől, például gomboktól, vagy eszközöktől, mint a billentyűzet, és reagál rájuk. Erről többet olvashat ebben a [cikkben az eseményciklusról](https://wikipedia.org/wiki/Event_loop).

Az Arduino szabványos könyvtárakat biztosít a mikrokontrollerek és az I/O tűk kezeléséhez, különböző implementációkkal a háttérben, hogy különböző mikrokontrollereken fusson. Például a [`delay` funkció](https://www.arduino.cc/reference/en/language/functions/time/delay/) szünetelteti a programot egy adott időtartamra, a [`digitalRead` funkció](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) pedig `HIGH` vagy `LOW` értéket olvas a megadott tűről, függetlenül attól, hogy melyik lapon fut a kód. Ezek a szabványos könyvtárak lehetővé teszik, hogy az egyik lapra írt Arduino kódot újrafordítsa bármely más Arduino lapra, és az fusson, feltéve, hogy a tűk azonosak, és a lapok támogatják ugyanazokat a funkciókat.

Az Arduino harmadik féltől származó könyvtárak széles ökoszisztémájával rendelkezik, amelyek lehetővé teszik, hogy extra funkciókat adjon hozzá Arduino projektjeihez, például szenzorok és aktuátorok használatát, vagy felhő IoT szolgáltatásokhoz való csatlakozást.

##### Feladat

Vizsgálja meg a Wio terminált.

Ha a Wio terminált használja ezekhez a leckékhez, olvassa újra az előző leckében írt kódot. Keresse meg a `setup` és `loop` funkciókat. Figyelje meg a soros kimenetet, hogy a `loop` funkció ismételten meghívásra kerül. Próbáljon meg kódot hozzáadni a `setup` funkcióhoz, hogy írjon a soros porthoz, és figyelje meg, hogy ez a kód csak egyszer kerül meghívásra minden újraindításkor. Próbálja meg újraindítani az eszközt az oldalsó bekapcsoló kapcsolóval, hogy lássa, hogy ez minden újraindításkor meghívásra kerül.

## Mélyebb betekintés az egylapos számítógépekbe

Az előző leckében bemutattuk az egylapos számítógépeket. Most nézzük meg őket részletesebben.

### Raspberry Pi

![A Raspberry Pi logója](../../../../../translated_images/hu/raspberry-pi-logo.4efaa16605cee054.webp)

A [Raspberry Pi Foundation](https://www.raspberrypi.org) egy brit jótékonysági szervezet, amelyet 2009-ben alapítottak az informatika tanulmányozásának előmozdítására, különösen iskolai szinten. Ennek a küldetésnek a részeként kifejlesztettek egy egylapos számítógépet, amelyet Raspberry Pi-nek neveztek el. A Raspberry Pi jelenleg 3 változatban érhető el - egy teljes méretű verzióban, a kisebb Pi Zero-ban, és egy számítási modulban, amely beépíthető a végső IoT eszközbe.

![Egy Raspberry Pi 4](../../../../../translated_images/hu/raspberry-pi-4.fd4590d308c3d456.webp)

A teljes méretű Raspberry Pi legújabb iterációja a Raspberry Pi 4B. Ez egy négymagos (4 magos) CPU-val rendelkezik, amely 1.5GHz-en fut, 2, 4 vagy 8GB RAM-mal, gigabites ethernettel, WiFi-vel, 2 HDMI porttal, amelyek 4k képernyőket támogatnak, egy audio- és kompozit videó kimeneti porttal, USB portokkal (2 USB 2.0, 2 USB 3.0), 40 GPIO tűvel, egy kamera csatlakozóval a Raspberry Pi kamera modulhoz, és egy SD kártya nyílással. Mindez egy 88mm x 58mm x 19.5mm méretű lapon, amelyet egy 3A USB-C tápegység működtet. Ezek ára 35 USD-tól kezdődik, ami sokkal olcsóbb, mint egy PC vagy Mac.

> 💁 Létezik egy Pi400 all-in-one számítógép, amely egy Pi4-et tartalmaz egy billentyűzetbe építve.

![Egy Raspberry Pi Zero](../../../../../translated_images/hu/raspberry-pi-zero.f7a4133e1e7d54bb.webp)

A Pi Zero sokkal kisebb, alacsonyabb teljesítményű. Egy egymagos 1GHz-es CPU-val, 512MB RAM-mal, WiFi-vel (a Zero W modellben), egyetlen HDMI porttal, egy micro-USB porttal, 40 GPIO tűvel, egy kamera csatlakozóval a Raspberry Pi kamera modulhoz, és egy SD kártya nyílással rendelkezik. Mérete 65mm x 30mm x 5mm, és nagyon kevés energiát fogyaszt. A Zero ára 5 USD, a WiFi-vel rendelkező W verzió pedig 10 USD.

> 🎓 Mindkét eszköz CPU-ja ARM processzor, szemben az Intel/AMD x86 vagy x64 processzorokkal, amelyeket a legtöbb PC-ben és Mac-ben talál. Ezek hasonlóak a mikrokontrollerekben található CPU-khoz, valamint szinte minden mobiltelefonban, a Microsoft Surface X-ben és az új Apple Silicon alapú Apple Mac-ekben.

A Raspberry Pi minden változata egy Debian Linux verziót futtat, amelyet Raspberry Pi OS-nek neveznek. Ez elérhető egy lite verzióban, amely nem tartalmaz asztali környezetet, ami tökéletes "fej nélküli" projektekhez, ahol nincs szükség képernyőre, vagy egy teljes verzióban, amely teljes asztali környezetet tartalmaz, webböngészővel, irodai alkalmazásokkal, kódolási eszközökkel és játékokkal. Mivel az operációs rendszer a Debian Linux egy verziója, bármilyen alkalmazást vagy eszközt telepíthet, amely Debianon fut, és az ARM processzorra van építve, amely a Pi-ben található.

#### Feladat

Vizsgálja meg a Raspberry Pi-t.

Ha Raspberry Pi-t használ ezekhez a leckékhez, olvasson utána a lap különböző hardverkomponenseinek.

* A Pi-ben használt processzorokról részleteket talál a [Raspberry Pi hardver dokumentációs oldalon](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Olvasson utána annak a processzornak, amelyet az Ön által használt Pi tartalmaz.
* Keresse meg a GPIO tűket. Olvasson többet róluk a [Raspberry Pi GPIO dokumentációban](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Használja a [GPIO Pin Usage guide](https://www.raspberry
### Az egykártyás számítógépek használata professzionális IoT telepítésekben

Az egykártyás számítógépeket nemcsak fejlesztői készletekként használják, hanem professzionális IoT telepítésekben is. Hatékony megoldást nyújthatnak hardverek vezérlésére és összetett feladatok végrehajtására, például gépi tanulási modellek futtatására. Például létezik egy [Raspberry Pi 4 compute module](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/), amely a Raspberry Pi 4 teljesítményét kínálja kompaktabb és olcsóbb formában, a legtöbb port nélkül, kifejezetten egyedi hardverekbe való beépítésre tervezve.

---

## 🚀 Kihívás

Az előző leckében az volt a kihívás, hogy sorolj fel minél több IoT eszközt, amelyeket otthonodban, iskoládban vagy munkahelyeden találsz. Minden eszköz esetében gondold át, hogy mikrovezérlőkre, egykártyás számítógépekre vagy akár ezek keverékére épülnek-e.

## Előadás utáni kvíz

[Előadás utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Áttekintés és önálló tanulás

* Olvasd el az [Arduino kezdő útmutatót](https://www.arduino.cc/en/Guide/Introduction), hogy többet megtudj az Arduino platformról.
* Olvasd el a [Raspberry Pi 4 bemutatását](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/), hogy többet megtudj a Raspberry Pi eszközökről.
* Ismerd meg jobban néhány fogalmat és rövidítést az [Electrical Engineering Journal "What the FAQ are CPUs, MPUs, MCUs, and GPUs" cikkében](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Használd ezeket az útmutatókat, valamint a költségeket, amelyeket a [hardver útmutatóban](../../../hardware.md) található linkek követésével láthatsz, hogy eldöntsd, melyik hardverplatformot szeretnéd használni, vagy inkább virtuális eszközt választanál.

## Feladat

[Hasonlítsd össze és állítsd szembe a mikrovezérlőket és az egykártyás számítógépeket](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.