# Gyümölcsminőség-ellenőrzés indítása egy érzékelő segítségével

![A leckéről készült vázlatos áttekintés](../../../../../translated_images/hu/lesson-18.92c32ed1d354caa5.webp)

> Vázlat készítette: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

## Előadás előtti kvíz

[Előadás előtti kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Bevezetés

Egy IoT-alkalmazás nem csupán egyetlen eszköz, amely adatokat gyűjt és küld a felhőbe, hanem gyakran több eszköz együttműködése, amelyek érzékelők segítségével adatokat gyűjtenek a fizikai világból, döntéseket hoznak az adatok alapján, és visszahatnak a fizikai világra aktuátorok vagy vizualizációk révén.

Ebben a leckében többet fogsz megtudni a komplex IoT-alkalmazások tervezéséről, több érzékelő és felhőszolgáltatás integrálásáról az adatok elemzéséhez és tárolásához, valamint az aktuátorokon keresztüli válaszok megjelenítéséről. Megtanulod, hogyan tervezz meg egy gyümölcsminőség-ellenőrző rendszer prototípusát, beleértve a közelségérzékelők használatát az IoT-alkalmazás indításához, és megismered a prototípus architektúráját.

Ebben a leckében az alábbiakat fogjuk áttekinteni:

* [Komplex IoT-alkalmazások tervezése](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Gyümölcsminőség-ellenőrző rendszer tervezése](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Gyümölcsminőség-ellenőrzés indítása egy érzékelő segítségével](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Adatok a gyümölcsminőség-ellenőrzőhöz](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Fejlesztői eszközök használata több IoT-eszköz szimulálásához](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Áttérés a gyártásra](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Ez a projekt utolsó leckéje, így a lecke és a feladat befejezése után ne felejtsd el törölni a felhőszolgáltatásokat. A feladat elvégzéséhez szükséged lesz ezekre a szolgáltatásokra, ezért győződj meg róla, hogy először befejezed azt.
>
> Szükség esetén tekintsd meg [a projekt törlésének útmutatóját](../../../clean-up.md) az utasításokért.

## Komplex IoT-alkalmazások tervezése

Az IoT-alkalmazások számos komponensből állnak. Ezek különféle eszközöket és internetes szolgáltatásokat foglalnak magukban.

Az IoT-alkalmazások leírhatók úgy, mint *eszközök* (dolgok), amelyek adatokat küldenek, hogy *információkat* generáljanak. Ezek az *információk* *cselekvéseket* váltanak ki, amelyek javítják az üzleti folyamatokat. Például egy motor (a dolog) hőmérsékleti adatokat küld. Ezeket az adatokat arra használják, hogy értékeljék, megfelelően működik-e a motor (az információ). Az információ alapján proaktívan prioritást adnak a motor karbantartási ütemezésének (a cselekvés).

* Különböző dolgok különböző adatokat gyűjtenek.
* Az IoT-szolgáltatások információkat nyújtanak az adatok alapján, néha további forrásokból származó adatokkal kiegészítve.
* Ezek az információk cselekvéseket váltanak ki, például aktuátorok vezérlését az eszközökben, vagy adatok vizualizálását.

### Referencia IoT-architektúra

![Egy referencia IoT-architektúra](../../../../../translated_images/hu/iot-reference-architecture.2278b98b55c6d4e8.webp)

A fenti diagram egy referencia IoT-architektúrát mutat.

> 🎓 A *referencia architektúra* egy példa architektúra, amelyet referenciaként használhatsz új rendszerek tervezésekor. Ebben az esetben, ha új IoT-rendszert építesz, követheted a referencia architektúrát, és helyettesítheted a saját eszközeidet és szolgáltatásaidat, ahol szükséges.

* **Dolgok**: Eszközök, amelyek adatokat gyűjtenek érzékelőkből, esetleg edge-szolgáltatásokkal együttműködve értelmezik az adatokat, például képosztályozókkal. Az eszközök adatai egy IoT-szolgáltatásba kerülnek.
* **Információk**: Szerver nélküli alkalmazásokból vagy tárolt adatok elemzéséből származnak.
* **Cselekvések**: Parancsok küldése eszközöknek, vagy adatok vizualizálása, amely lehetővé teszi az emberek számára a döntéshozatalt.

![Egy referencia IoT-architektúra](../../../../../translated_images/hu/iot-reference-architecture-azure.0b8d2161af924cb1.webp)

A fenti diagram az eddig tárgyalt komponenseket és szolgáltatásokat mutatja, valamint azt, hogyan kapcsolódnak össze egy referencia IoT-architektúrában.

* **Dolgok**: Eszközkódot írtál érzékelőkből származó adatok gyűjtésére, és képeket elemeztél Custom Vision segítségével, mind a felhőben, mind edge-eszközön. Ezeket az adatokat IoT Hubba küldték.
* **Információk**: Azure Functions-t használtál az IoT Hubba küldött üzenetekre való reagáláshoz, és adatokat tároltál későbbi elemzésre Azure Storage-ban.
* **Cselekvések**: Aktuátorokat vezéreltél a felhőben hozott döntések alapján, és parancsokat küldtél az eszközöknek, valamint vizualizáltad az adatokat Azure Maps segítségével.

✅ Gondolj más IoT-eszközökre, amelyeket használtál, például okosotthoni készülékekre. Melyek a dolgok, információk és cselekvések az adott eszköz és szoftver esetében?

Ez a minta tetszőlegesen nagyra vagy kicsire skálázható, több eszközt és szolgáltatást hozzáadva.

### Adatok és biztonság

Amikor a rendszered architektúráját definiálod, folyamatosan figyelembe kell venned az adatokat és a biztonságot.

* Milyen adatokat küld és fogad az eszközöd?
* Hogyan kell ezeket az adatokat védeni és biztosítani?
* Hogyan kell az eszköz és a felhőszolgáltatás hozzáférését szabályozni?

✅ Gondolj az általad birtokolt IoT-eszközök adatbiztonságára. Mennyire személyesek ezek az adatok, és hogyan kell őket privát módon kezelni, mind az átvitel során, mind a tároláskor? Milyen adatokat nem szabad tárolni?

## Gyümölcsminőség-ellenőrző rendszer tervezése

Most alkalmazzuk a dolgok, információk és cselekvések ötletét a gyümölcsminőség-ellenőrző rendszerünkre, hogy megtervezzünk egy nagyobb, teljes körű alkalmazást.

Képzeld el, hogy az a feladatod, hogy építs egy gyümölcsminőség-ellenőrzőt, amelyet egy feldolgozóüzemben használnak. A gyümölcs egy szállítószalag rendszeren halad, ahol jelenleg alkalmazottak kézzel ellenőrzik a gyümölcsöt, és eltávolítják az éretlen darabokat. Az üzem tulajdonosa költségcsökkentés érdekében automatizált rendszert szeretne.

✅ Az IoT (és általában a technológia) térnyerésével egyre több manuális munkahelyet váltanak ki gépek. Kutass utána: Hány munkahelyet becsülnek elveszni az IoT miatt? Hány új munkahely jön létre IoT-eszközök építésével?

Olyan rendszert kell építened, amely érzékeli a gyümölcs érkezését a szállítószalagon, lefotózza és ellenőrzi egy AI-modell segítségével, amely az edge-en fut. Az eredményeket elküldik a felhőbe tárolás céljából, és ha a gyümölcs éretlen, értesítést küldenek, hogy az éretlen gyümölcs eltávolítható legyen.

|   |   |
| - | - |
| **Dolgok** | Érzékelő a gyümölcs érkezésének észlelésére<br>Kamera a gyümölcs lefotózására és osztályozására<br>Edge-eszköz az osztályozó futtatására<br>Eszköz az éretlen gyümölcs jelzésére |
| **Információk** | Döntés a gyümölcs érettségének ellenőrzéséről<br>Az osztályozás eredményeinek tárolása<br>Az éretlen gyümölcs jelzésének szükségességének meghatározása |
| **Cselekvések** | Parancs küldése az eszköznek a gyümölcs lefotózására és képosztályozóval való ellenőrzésére<br>Parancs küldése az eszköznek az éretlen gyümölcs jelzésére |

### Az alkalmazás prototípusának elkészítése

![Egy referencia IoT-architektúra a gyümölcsminőség-ellenőrzéshez](../../../../../translated_images/hu/iot-reference-architecture-fruit-quality.cc705f121c3b6fa7.webp)

A fenti diagram egy referencia architektúrát mutat be ehhez a prototípus alkalmazáshoz.

* Egy IoT-eszköz közelségérzékelővel érzékeli a gyümölcs érkezését. Ez üzenetet küld a felhőbe, hogy gyümölcs érkezett.
* Egy szerver nélküli alkalmazás a felhőben parancsot küld egy másik eszköznek, hogy készítsen fényképet és osztályozza a képet.
* Egy IoT-eszköz kamerával készít egy képet, és elküldi egy edge-en futó képosztályozónak. Az eredményeket elküldi a felhőbe.
* Egy szerver nélküli alkalmazás a felhőben tárolja ezeket az információkat későbbi elemzés céljából, hogy megállapítsa, hány százalékban éretlen a gyümölcs. Ha a gyümölcs éretlen, parancsot küld egy másik IoT-eszköznek, hogy LED-en keresztül értesítse a gyár dolgozóit.

> 💁 Ez az egész IoT-alkalmazás megvalósítható lenne egyetlen eszközként, amely tartalmazza az összes logikát a képosztályozás indításához és a LED vezérléséhez. IoT Hubot csak az éretlen gyümölcsök számának nyomon követésére és az eszköz konfigurálására használhatnánk. Ebben a leckében kibővítjük, hogy bemutassuk a nagy léptékű IoT-alkalmazások koncepcióit.

A prototípushoz mindezt egyetlen eszközön fogod megvalósítani. Ha mikrokontrollert használsz, akkor külön edge-eszközt fogsz használni a képosztályozó futtatásához. Már megtanultad a szükséges dolgok nagy részét, hogy ezt megépítsd.

## Gyümölcsminőség-ellenőrzés indítása egy érzékelő segítségével

Az IoT-eszköznek szüksége van valamilyen indítóra, amely jelzi, hogy a gyümölcs készen áll az osztályozásra. Egy ilyen indító lehet például a gyümölcs helyzetének mérése a szállítószalagon egy érzékelő távolságának mérésével.

![A közelségérzékelők lézersugarakat küldenek tárgyakra, például banánokra, és mérik, mennyi idő alatt verődik vissza a sugár](../../../../../translated_images/hu/proximity-sensor.f5cd752c77fb62fe.webp)

A közelségérzékelők használhatók az érzékelő és egy tárgy közötti távolság mérésére. Általában elektromágneses sugárzást, például lézersugarat vagy infravörös fényt bocsátanak ki, majd érzékelik a tárgyról visszaverődő sugárzást. A lézersugár kibocsátása és a jel visszaverődése közötti idő alapján kiszámítható az érzékelő távolsága.

> 💁 Valószínűleg már használtál közelségérzékelőket anélkül, hogy tudtál volna róla. A legtöbb okostelefon kikapcsolja a képernyőt, amikor a füledhez tartod, hogy megakadályozza, hogy véletlenül megszakítsd a hívást a fülcimpáddal. Ez közelségérzékelővel működik, amely érzékeli a képernyő közelében lévő tárgyat a hívás során, és letiltja az érintési funkciókat, amíg a telefon egy bizonyos távolságra nem kerül.

### Feladat - gyümölcsminőség-ellenőrzés indítása távolságérzékelővel

Dolgozd végig a megfelelő útmutatót, hogy közelségérzékelőt használj tárgyak érzékelésére az IoT-eszközöd segítségével:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Egylapos számítógép - Raspberry Pi](pi-proximity.md)
* [Egylapos számítógép - Virtuális eszköz](virtual-device-proximity.md)

## Adatok a gyümölcsminőség-ellenőrzőhöz

A prototípus gyümölcsérzékelő több komponensből áll, amelyek egymással kommunikálnak.

![A komponensek kommunikációja egymással](../../../../../translated_images/hu/fruit-quality-detector-message-flow.adf2a65da8fd8741.webp)

* Egy közelségérzékelő, amely méri a gyümölcs távolságát, és elküldi ezt az IoT Hubnak
* A kamera vezérlésére szolgáló parancs az IoT Hubból érkezik a kamera eszközéhez
* Az osztályozás eredményei az IoT Hubba kerülnek
* Az éretlen gyümölcs jelzésére szolgáló LED vezérlésére szolgáló parancs az IoT Hubból érkezik az eszközhöz

Jó, ha előre meghatározod ezeknek az üzeneteknek a struktúráját, mielőtt megépíted az alkalmazást.

> 💁 Szinte minden tapasztalt fejlesztő karrierje során töltött már órákat, napokat vagy akár heteket olyan hibák keresésével, amelyeket az okozott, hogy az elküldött adatok eltértek a vártaktól.

Például - ha hőmérsékleti információkat küldesz, hogyan definiálnád a JSON-t? Lehetne egy mező, amelyet `temperature`-nek nevezel, vagy használhatnád a gyakori rövidítést, `temp`.

```json
{
    "temperature": 20.7
}
```

szemben:

```json
{
    "temp": 20.7
}
```

Figyelembe kell venned az egységeket is - a hőmérséklet °C-ban vagy °F-ban van? Ha fogyasztói eszközt használsz, és megváltoztatják a kijelző egységeit, biztosítanod kell, hogy a felhőbe küldött egységek következetesek maradjanak.

✅ Kutass utána: Hogyan okozott egységprobléma a 125 millió dolláros Mars Climate Orbiter összeomlását?

Gondolj a gyümölcsminőség-ellenőrző által küldött adatokra. Hogyan definiálnád az egyes üzeneteket? Hol elemeznéd az adatokat, és hoznál döntéseket arról, hogy milyen adatokat küldj?

Például - a közelségérzékelővel történő képosztályozás indítása. Az IoT-eszköz méri a távolságot, de hol történik a döntés?
💁 Legyen tisztában azzal, hogy bizonyos hardverek nem működnek, ha egyszerre több alkalmazás próbál hozzáférni.
### Több eszköz szimulálása egy mikrokontrolleren

Mikrokontrollereken nehezebb több eszközt szimulálni. Ellentétben az egykártyás számítógépekkel, nem lehet egyszerre több alkalmazást futtatni, minden különálló IoT eszköz logikáját egyetlen alkalmazásba kell integrálni.

Néhány javaslat, hogy megkönnyítsd ezt a folyamatot:

* Hozz létre egy vagy több osztályt IoT eszközönként – például `DistanceSensor`, `ClassifierCamera`, `LEDController` nevű osztályokat. Mindegyiknek lehet saját `setup` és `loop` metódusa, amelyeket a fő `setup` és `loop` függvények hívnak meg.
* Kezeld a parancsokat egy központi helyen, és irányítsd őket a megfelelő eszközosztályhoz, ahogy szükséges.
* A fő `loop` függvényben figyelembe kell venned az egyes eszközök időzítését. Például, ha van egy eszközosztály, amelynek 10 másodpercenként kell feldolgoznia, és egy másik, amelynek 1 másodpercenként, akkor a fő `loop` függvényben használj 1 másodperces késleltetést. Minden `loop` hívás elindítja a releváns kódot az eszközhöz, amelynek másodpercenként kell feldolgoznia, és használj egy számlálót, amely minden ciklust számol, majd a másik eszközt akkor dolgozza fel, amikor a számláló eléri a 10-et (utána nullázd a számlálót).

## Átállás a gyártásra

A prototípus képezi a végleges gyártási rendszer alapját. Néhány különbség, amikor a gyártásra váltasz:

* Strapabíró alkatrészek – olyan hardverek használata, amelyek ellenállnak a zajnak, hőnek, rezgésnek és stressznek egy gyárban.
* Belső kommunikáció használata – néhány alkatrész közvetlenül kommunikál, elkerülve a felhőbe való ugrást, csak adatokat küldve a felhőbe tárolás céljából. Ennek módja a gyár beállításától függ, lehet közvetlen kommunikációval vagy az IoT szolgáltatás egy részének futtatásával az edge-en egy gateway eszköz segítségével.
* Konfigurációs lehetőségek – minden gyár és felhasználási eset különböző, így a hardvernek konfigurálhatónak kell lennie. Például a közelségérzékelőnek különböző gyümölcsöket kell érzékelnie különböző távolságokon. Ahelyett, hogy a távolságot kódolnád a klasszifikáció aktiválásához, szeretnéd, ha ez konfigurálható lenne a felhőn keresztül, például egy eszköz iker segítségével.
* Automatikus gyümölcseltávolítás – ahelyett, hogy egy LED jelezné, hogy a gyümölcs éretlen, automatikus eszközök eltávolítanák azt.

✅ Kutass egy kicsit: Milyen más módokon különböznek a gyártási eszközök a fejlesztői készletektől?

---

## 🚀 Kihívás

Ebben a leckében megtanultál néhány alapfogalmat arról, hogyan kell megtervezni egy IoT rendszert. Gondolj vissza az előző projektekre. Hogyan illeszkednek a fent bemutatott referenciaarchitektúrába?

Válassz ki egyet az eddigi projektek közül, és gondold át egy bonyolultabb megoldás tervezését, amely több képességet hoz össze, mint amit a projektekben lefedtünk. Rajzold le az architektúrát, és gondold át az összes szükséges eszközt és szolgáltatást.

Például – egy járműkövető eszköz, amely GPS-t kombinál szenzorokkal, hogy monitorozza például a hűtött teherautó hőmérsékletét, a motor be- és kikapcsolási idejét, valamint a sofőr személyazonosságát. Milyen eszközök és szolgáltatások szükségesek, milyen adatokat továbbítanak, és milyen biztonsági és adatvédelmi szempontokat kell figyelembe venni?

## Utólagos kvíz

[Utólagos kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Áttekintés és önálló tanulás

* Olvass többet az IoT architektúráról az [Azure IoT referenciaarchitektúra dokumentációjában a Microsoft Docs-on](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Olvass többet az eszköz ikrekről az [IoT Hub dokumentációjában a Microsoft Docs-on](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Olvass az OPC-UA-ról, egy gép-gép kommunikációs protokollról, amelyet az ipari automatizálásban használnak, az [OPC-UA Wikipedia oldalán](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Feladat

[Építs egy gyümölcsminőség-érzékelőt](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.