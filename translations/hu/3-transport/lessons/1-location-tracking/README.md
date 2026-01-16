<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52ed2bd997d08040f79a1a6ef2bac958",
  "translation_date": "2025-08-27T21:37:40+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/README.md",
  "language_code": "hu"
}
-->
# Helymeghatározás

![A leckéről készült sketchnote áttekintése](../../../../../translated_images/hu/lesson-11.9fddbac4b664c6d50ab7ac9bb32f1fc3f945f03760e72f7f43938073762fb017.jpg)

> Sketchnote készítette: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

## Előadás előtti kvíz

[Előadás előtti kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Bevezetés

Az élelmiszer eljuttatásának fő folyamata a termelőtől a fogyasztóig magában foglalja a termények dobozainak teherautókra, hajókra, repülőgépekre vagy más kereskedelmi szállítóeszközökre való felrakását, majd az élelmiszer kiszállítását valahová – akár közvetlenül a vásárlóhoz, akár egy központi elosztóhelyre vagy raktárba feldolgozás céljából. Az egész, a termelőtől a fogyasztóig tartó folyamatot *ellátási láncnak* nevezzük. Az alábbi videó az Arizona State University W. P. Carey School of Business-től részletesebben bemutatja az ellátási lánc fogalmát és annak kezelését.

[![Mi az ellátási lánc menedzsment? Videó az Arizona State University W. P. Carey School of Business-től](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Kattints a fenti képre a videó megtekintéséhez

Az IoT eszközök hozzáadása drasztikusan javíthatja az ellátási láncot, lehetővé téve az áruk helyének nyomon követését, a szállítás és árukezelés jobb megtervezését, valamint gyorsabb reagálást a problémákra.

Ha egy járműflottát, például teherautókat kezelünk, hasznos tudni, hogy egy adott időpontban hol tartózkodik az egyes járművek. A járműveket GPS érzékelőkkel lehet felszerelni, amelyek elküldik helyzetüket az IoT rendszereknek, lehetővé téve a tulajdonosok számára, hogy pontosan meghatározzák a helyzetüket, lássák az általuk megtett útvonalat, és tudják, mikor érkeznek meg a célállomásra. A legtöbb jármű WiFi lefedettségen kívül működik, ezért mobilhálózatokat használnak az ilyen típusú adatok továbbítására. Néha a GPS érzékelő összetettebb IoT eszközökbe, például elektronikus menetnaplókba van beépítve. Ezek az eszközök nyomon követik, hogy egy teherautó mennyi ideje van úton, hogy biztosítsák a sofőrök megfelelését a helyi munkaidőre vonatkozó törvényeknek.

Ebben a leckében megtanulod, hogyan lehet nyomon követni egy jármű helyzetét egy Globális Helymeghatározó Rendszer (GPS) érzékelő segítségével.

A lecke során az alábbi témákat érintjük:

* [Kapcsolt járművek](../../../../../3-transport/lessons/1-location-tracking)
* [Térbeli koordináták](../../../../../3-transport/lessons/1-location-tracking)
* [Globális Helymeghatározó Rendszerek (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [GPS érzékelő adatok olvasása](../../../../../3-transport/lessons/1-location-tracking)
* [NMEA GPS adatok](../../../../../3-transport/lessons/1-location-tracking)
* [GPS érzékelő adatok dekódolása](../../../../../3-transport/lessons/1-location-tracking)

## Kapcsolt járművek

Az IoT átalakítja az áruszállítás módját azáltal, hogy *kapcsolt járművek* flottáit hozza létre. Ezek a járművek kapcsolódnak központi IT rendszerekhez, amelyek információkat küldenek a helyzetükről és más érzékelő adataikról. A kapcsolt járművek flottájának számos előnye van:

* Helymeghatározás – bármikor pontosan meghatározható, hol tartózkodik egy jármű, lehetővé téve:

  * Értesítések fogadását, amikor egy jármű közel van a célállomáshoz, hogy felkészítsék a kirakodó csapatot
  * Ellopott járművek helyének meghatározását
  * Hely- és útvonaladatok kombinálását forgalmi problémákkal, hogy lehetővé tegye a járművek útvonalának módosítását az utazás közben
  * Adózási megfelelés biztosítását. Egyes országok díjat számítanak fel a közutakon megtett kilométerek alapján (például [Útdíj Új-Zélandon](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), így könnyebb kiszámítani a fizetendő adót, ha tudjuk, mikor van egy jármű közúton vagy magánúton.
  * Karbantartó csapatok küldését meghibásodás esetén a megfelelő helyre

* Sofőr telemetria – annak biztosítása, hogy a sofőrök betartsák a sebességkorlátozásokat, megfelelő sebességgel vegyék a kanyarokat, időben és hatékonyan fékezzenek, valamint biztonságosan vezessenek. A kapcsolt járművek kamerákkal is felszerelhetők, amelyek rögzítik az eseményeket. Ez összekapcsolható a biztosítással, kedvezményes díjakat biztosítva a jó sofőrök számára.

* Sofőr munkaidő megfelelés – annak biztosítása, hogy a sofőrök csak a jogilag megengedett munkaidőben vezessenek, az alapján, hogy mikor indítják be és állítják le a motort.

Ezek az előnyök kombinálhatók – például a sofőr munkaidő megfelelés kombinálása a helymeghatározással, hogy átirányítsák a sofőröket, ha nem érhetik el a célállomást a megengedett vezetési időn belül. Ezek kombinálhatók más járműspecifikus telemetriával is, például hőmérsékleti adatokkal hőmérséklet-szabályozott teherautók esetében, lehetővé téve a járművek átirányítását, ha az aktuális útvonaluk azt jelentené, hogy az áruk nem tarthatók megfelelő hőmérsékleten.

> 🎓 A logisztika az áruk egyik helyről a másikra történő szállításának folyamata, például egy farmról egy szupermarketbe egy vagy több raktáron keresztül. Egy gazda paradicsomos dobozokat csomagol, amelyeket teherautóra raknak, egy központi raktárba szállítanak, majd egy második teherautóra raknak, amely különböző típusú termékek keverékét tartalmazhatja, és végül a szupermarketbe szállítják.

A járműkövetés alapvető eleme a GPS – érzékelők, amelyek bárhol a Földön képesek meghatározni a helyzetüket. Ebben a leckében megtanulod, hogyan kell használni egy GPS érzékelőt, kezdve azzal, hogy megtanulod, hogyan lehet meghatározni egy helyet a Földön.

## Térbeli koordináták

A térbeli koordinátákat a Föld felszínén lévő pontok meghatározására használják, hasonlóan ahhoz, ahogyan a koordinátákat egy számítógép képernyőjén lévő pixel rajzolására vagy keresztszemes hímzés öltéseinek elhelyezésére használják. Egyetlen pont esetében egy koordinátapárra van szükség. Például a Microsoft Campus Redmondban, Washington államban, az USA-ban a 47.6423109, -122.1390293 helyen található.

### Szélesség és hosszúság

A Föld egy gömb – egy háromdimenziós kör. Emiatt a pontokat úgy határozzák meg, hogy 360 fokra osztják, ugyanúgy, mint a körök geometriáját. A szélesség az észak-déli irányú fokok számát méri, a hosszúság pedig a kelet-nyugati irányú fokok számát.

> 💁 Senki sem tudja pontosan, miért osztják a köröket 360 fokra. A [fok (szög) Wikipedia oldala](https://wikipedia.org/wiki/Degree_(angle)) néhány lehetséges okot ismertet.

![Szélességi vonalak: 90° az Északi-sarknál, 45° félúton az Északi-sark és az Egyenlítő között, 0° az Egyenlítőnél, -45° félúton az Egyenlítő és a Déli-sark között, és -90° a Déli-sarknál](../../../../../translated_images/hu/latitude-lines.11d8d91dfb2014a57437272d7db7fd6607243098e8685f06e0c5f1ec984cb7eb.png)

A szélességet az Egyenlítővel párhuzamosan futó vonalakkal mérik, amelyek az Északi és Déli féltekét 90°-ra osztják. Az Egyenlítő 0°-nál van, az Északi-sark 90°, más néven 90° Észak, a Déli-sark pedig -90°, vagy 90° Dél.

A hosszúságot a kelet-nyugati irányú fokok számával mérik. A hosszúság 0°-os kiindulópontját *Prime Meridian*-nek nevezik, amelyet 1884-ben határoztak meg, hogy az Északi-sarktól a Déli-sarkig húzódó vonal legyen, amely áthalad a [Brit Királyi Obszervatóriumon Greenwichben, Angliában](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Hosszúsági vonalak: -180° a Prime Meridian nyugati oldalán, 0° a Prime Meridianon, 180° a Prime Meridian keleti oldalán](../../../../../translated_images/hu/longitude-meridians.ab4ef1c91c064586b0185a3c8d39e585903696c6a7d28c098a93a629cddb5d20.png)

> 🎓 A meridián egy képzeletbeli egyenes vonal, amely az Északi-sarktól a Déli-sarkig húzódik, félkört alkotva.

Egy pont hosszúságának méréséhez meg kell mérni az Egyenlítő mentén a Prime Meridian-tól a ponton áthaladó meridiánig tartó fokok számát. A hosszúság -180°-tól, vagy 180° Nyugattól, 0°-on keresztül a Prime Meridianon, 180°-ig, vagy 180° Keletig terjed. A 180° és -180° ugyanarra a pontra utal, az antimeridiánra vagy 180. meridiánra. Ez egy meridián a Föld Prime Meridian-nal ellentétes oldalán.

> 💁 Az antimeridiánt nem szabad összekeverni a Nemzetközi Dátumvonallal, amely körülbelül ugyanazon a helyen van, de nem egyenes vonal, és a geopolitikai határok körül változik.

✅ Kutass egy kicsit: Próbáld meg megtalálni a jelenlegi helyed szélességi és hosszúsági koordinátáit.

### Fokok, percek és másodpercek vs decimális fokok

Hagyományosan a szélességi és hosszúsági fokok mérése szexageszimális számozással történt, vagyis 60-as alapú rendszerrel, amelyet az ókori babilóniaiak használtak, akik először végeztek idő- és távolságméréseket. Valószínűleg naponta használod a szexageszimális rendszert anélkül, hogy észrevennéd – például az órák 60 percre és a percek 60 másodpercre való osztásával.

A hosszúságot és szélességet fokokban, percekben és másodpercekben mérik, ahol egy perc 1/60 fok, egy másodperc pedig 1/60 perc.

Például az Egyenlítőnél:

* 1° szélesség **111,3 kilométer**
* 1 perc szélesség 111,3/60 = **1,855 kilométer**
* 1 másodperc szélesség 1,855/60 = **0,031 kilométer**

A perc szimbóluma egy aposztróf, a másodpercé pedig egy idézőjel. Például 2 fok, 17 perc és 43 másodperc így írandó: 2°17'43". A másodpercek töredékei decimálisan vannak megadva, például fél másodperc: 0°0'0.5".

A számítógépek nem működnek 60-as alapú rendszerben, ezért ezek a koordináták decimális fokokként vannak megadva a GPS adatokban a legtöbb számítógépes rendszerben. Például a 2°17'43" értéke 2,295277. A fok szimbólumot általában elhagyják.

Egy pont koordinátái mindig `szélesség, hosszúság` formában vannak megadva, így a korábbi Microsoft Campus példája, 47.6423109,-122.117198:

* Szélessége: 47.6423109 (47.6423109 fokkal északra az Egyenlítőtől)
* Hosszúsága: -122.1390293 (122.1390293 fokkal nyugatra a Prime Meridian-tól).

![A Microsoft Campus a 47.6423109,-122.117198 koordinátán](../../../../../translated_images/hu/microsoft-gps-location-world.a321d481b010f6adfcca139b2ba0adc53b79f58a540495b8e2ce7f779ea64bfe.png)

## Globális Helymeghatározó Rendszerek (GPS)

A GPS rendszerek több, a Föld körül keringő műholdat használnak a helyzeted meghatározásához. Valószínűleg már használtál GPS rendszereket anélkül, hogy tudtál volna róla – például a helyzeted meghatározására egy térképes alkalmazásban a telefonodon, mint az Apple Maps vagy a Google Maps, vagy hogy lásd, hol van az autód egy fuvarmegosztó alkalmazásban, mint az Uber vagy a Lyft, vagy amikor műholdas navigációt (sat-nav) használsz az autódban.

> 🎓 A "műholdas navigáció" műholdjai GPS műholdak!

A GPS rendszerek úgy működnek, hogy több műhold jelet küld a műholdak aktuális helyzetével és egy pontos időbélyeggel. Ezeket a jeleket rádióhullámokon keresztül küldik, amelyeket a GPS érzékelő antennája érzékel. Egy GPS érzékelő észleli ezeket a jeleket, és az aktuális időt használva megméri, mennyi időbe telt, hogy a jel elérje az érzékelőt a műholdtól. Mivel a rádióhullámok sebessége állandó, a GPS érzékelő az elküldött időbélyeg segítségével kiszámíthatja, milyen messze van az érzékelő a műholdtól. Legalább 3 műhold adatainak kombinálásával, az elküldött helyzetekkel együtt, a GPS érzékelő képes pontosan meghatározni a helyzetét a Földön.

> 💁 A GPS érzékelőknek antennára van szükségük a rádióhullámok érzékeléséhez. A teherautókba és autókba beépített GPS antennák úgy vannak elhelyezve, hogy jó jelet kapjanak, általában a szélvédőn vagy a tetőn. Ha külön GPS rendszert használsz, például okostelefont vagy IoT eszközt, akkor biztosítanod kell, hogy a GPS rendszerbe vagy telefonba beépített antenna tiszta rálátással rendelkezzen az égboltra, például a szélvédőn legyen elhelyezve.

![Az érzékelő és több műhold közötti távolság ismeretében a helyzet kiszámítható](../../../../../translated_images/hu/gps-satellites.04acf1148fe25fbf1586bc2e8ba698e8d79b79a50c36824b38417dd13372b90f.png)

A GPS műholdak a Föld körül keringenek, nem rögzített ponton az érzékelő felett, így a helyadatok a tengerszint feletti magasságot is tartalmazzák a szélesség és hosszúság mellett.

A GPS korábban korlátozott pontossággal működött, amelyet az amerikai hadsereg szabályozott, körülbelül 5 méteres pontosságot biztosítva. Ezt a korlátozást 2000-ben eltörölték, lehetővé téve a 30 centiméteres pontosságot. Ezt a pontosságot nem mindig lehet elérni a je
💁 A műholdak rendkívül pontos atomórákat tartalmaznak, de naponta 38 mikroszekundummal (0,0000038 másodperc) eltérnek a Földön lévő atomórákhoz képest, mivel az idő lassul, ahogy a sebesség növekszik, ahogyan azt Einstein speciális és általános relativitáselméletei megjósolták – a műholdak gyorsabban mozognak, mint a Föld forgása. Ez az eltérés bizonyította a speciális és általános relativitáselmélet előrejelzéseit, és figyelembe kell venni a GPS rendszerek tervezésénél. Szó szerint lassabban telik az idő egy GPS műholdon.
A GPS-rendszereket számos ország és politikai unió fejlesztette ki és telepítette, beleértve az Egyesült Államokat, Oroszországot, Japánt, Indiát, az EU-t és Kínát. A modern GPS-érzékelők a legtöbb ilyen rendszerhez tudnak csatlakozni, hogy gyorsabb és pontosabb helymeghatározást biztosítsanak.

> 🎓 Az egyes rendszerek műholdcsoportjait konstellációknak nevezik.

## GPS-érzékelő adatainak olvasása

A legtöbb GPS-érzékelő UART-on keresztül küldi az adatokat.

> ⚠️ Az UART-ot a [2. projekt, 2. lecke](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart) tárgyalta. Ha szükséges, nézd át újra azt a leckét.

Az IoT-eszközödön GPS-érzékelőt használhatsz GPS-adatok olvasására.

### Feladat - Csatlakoztass GPS-érzékelőt és olvass GPS-adatokat

Kövesd a megfelelő útmutatót, hogy GPS-adatokat olvass az IoT-eszközöddel:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Egylapkás számítógép - Raspberry Pi](pi-gps-sensor.md)
* [Egylapkás számítógép - Virtuális eszköz](virtual-device-gps-sensor.md)

## NMEA GPS-adatok

Amikor futtattad a kódodat, valószínűleg olyan kimenetet láttál, ami elsőre értelmetlennek tűnhetett. Ez valójában szabványos GPS-adat, amelynek minden része jelentéssel bír.

A GPS-érzékelők NMEA üzeneteket használnak az adatok továbbítására, az NMEA 0183 szabvány szerint. Az NMEA a [National Marine Electronics Association](https://www.nmea.org) (Nemzeti Tengerészeti Elektronikai Szövetség) rövidítése, amely egy amerikai kereskedelmi szervezet, amely szabványokat állít fel a tengeri elektronikai eszközök közötti kommunikációhoz.

> 💁 Ez a szabvány szabadalmaztatott, és legalább 2000 amerikai dollárba kerül, de elegendő információ érhető el róla a nyilvános domainben ahhoz, hogy a szabvány nagy részét visszafejtsék, és nyílt forráskódú vagy más nem kereskedelmi célú kódokban használják.

Ezek az üzenetek szöveges alapúak. Minden üzenet egy *mondatból* áll, amely egy `$` karakterrel kezdődik, majd 2 karakter jelzi az üzenet forrását (például GP az amerikai GPS-rendszerhez, GN a GLONASS-hoz, az orosz GPS-rendszerhez), és 3 karakter az üzenet típusát. Az üzenet többi része mezőkből áll, amelyeket vessző választ el, és egy új sor karakterrel zárul.

Néhány üzenettípus, amelyet fogadhatsz:

| Típus | Leírás |
| ---- | ------- |
| GGA | GPS Fix adatok, beleértve a GPS-érzékelő szélességi, hosszúsági és magassági adatait, valamint a helymeghatározáshoz használt műholdak számát. |
| ZDA | Az aktuális dátum és idő, beleértve a helyi időzónát |
| GSV | A látható műholdak részletei - azokat a műholdakat jelenti, amelyekről a GPS-érzékelő jeleket tud fogni |

> 💁 A GPS-adatok időbélyegeket is tartalmaznak, így az IoT-eszköz GPS-érzékelőből is megszerezheti az időt, nem kell NTP-szerverre vagy belső valós idejű órára támaszkodnia.

A GGA üzenet tartalmazza az aktuális helyet a `(dd)dmm.mmmm` formátumban, valamint egy karaktert az irány jelzésére. A `d` a formátumban a fokokat jelöli, az `m` a perceket, a másodpercek pedig a percek tizedeseként jelennek meg. Például 2°17'43" az 217.716666667 - 2 fok, 17.716666667 perc.

Az irány karakter lehet `N` vagy `S` a szélességhez, hogy jelezze az északi vagy déli irányt, és `E` vagy `W` a hosszúsághoz, hogy jelezze a keleti vagy nyugati irányt. Például egy 2°17'43" szélességhez az irány karakter `N`, míg -2°17'43" esetén az irány karakter `S`.

Példa - az NMEA mondat: `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* A szélesség része `4738.538654,N`, amely tizedes fokokra átszámítva 47.6423109. A `4738.538654` 47.6423109, és az irány `N` (észak), tehát pozitív szélesség.

* A hosszúság része `12208.341758,W`, amely tizedes fokokra átszámítva -122.1390293. A `12208.341758` 122.1390293°, és az irány `W` (nyugat), tehát negatív hosszúság.

## GPS-érzékelő adatok dekódolása

A nyers NMEA adatok helyett jobb, ha azokat egy hasznosabb formátumra dekódoljuk. Számos nyílt forráskódú könyvtár áll rendelkezésre, amelyek segítenek a nyers NMEA üzenetekből hasznos adatokat kinyerni.

### Feladat - GPS-érzékelő adatok dekódolása

Kövesd a megfelelő útmutatót, hogy dekódold a GPS-érzékelő adatait az IoT-eszközöddel:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Egylapkás számítógép - Raspberry Pi/Virtuális IoT-eszköz](single-board-computer-gps-decode.md)

---

## 🚀 Kihívás

Írj saját NMEA dekódolót! Harmadik féltől származó könyvtárak helyett tudsz-e saját dekódolót írni, amely az NMEA mondatokból kinyeri a szélességi és hosszúsági adatokat?

## Óra utáni kvíz

[Óra utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Áttekintés és önálló tanulás

* Olvass többet a földrajzi koordinátákról a [Geográfiai koordináta-rendszer Wikipedia oldalán](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Ismerd meg a Földön kívüli égitestek kezdő hosszúsági köreit a [Kezdő hosszúsági kör Wikipedia oldalán](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies).
* Kutass a különböző GPS-rendszerek után, amelyeket különböző kormányok és politikai uniók, például az EU, Japán, Oroszország, India és az Egyesült Államok fejlesztettek ki.

## Feladat

[Tanulmányozz más GPS-adatokat](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.