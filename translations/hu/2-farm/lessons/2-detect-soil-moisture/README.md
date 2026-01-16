<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4fb20273d299dc8d07a8f06c9cd0cdd9",
  "translation_date": "2025-08-27T22:51:23+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/README.md",
  "language_code": "hu"
}
-->
C, amelyet *I-négyzet-C*-nek ejtenek, egy több vezérlőt és több perifériát támogató protokoll, amelyben bármely csatlakoztatott eszköz vezérlőként vagy perifériaként működhet, és kommunikálhat az I

A 2<sup>2</sup>C sebességkorlátokkal rendelkezik, három különböző üzemmódban, amelyek fix sebességgel működnek. A leggyorsabb a High Speed mód, amelynek maximális sebessége 3,4 Mbps (megabit per másodperc), bár nagyon kevés eszköz támogatja ezt a sebességet. Például a Raspberry Pi csak a gyors módot támogatja, amely 400 Kbps (kilobit per másodperc). A standard mód 100 Kbps sebességgel működik.

> 💁 Ha Raspberry Pi-t használ Grove Base hat-tal IoT hardverként, akkor a táblán több I<sup>2</sup>C aljzatot is láthat, amelyeket I<sup>2</sup>C szenzorokkal való kommunikációra használhat. Az analóg Grove szenzorok szintén I<sup>2</sup>C-t használnak egy ADC-vel, hogy az analóg értékeket digitális adatként küldjék, így a fényérzékelő, amelyet használt, egy analóg tűt szimulált, az értéket pedig I<sup>2</sup>C-n keresztül küldte, mivel a Raspberry Pi csak digitális tűket támogat.

### Univerzális aszinkron vevő-adó (UART)

Az UART fizikai áramköröket használ, amelyek lehetővé teszik két eszköz közötti kommunikációt. Minden eszköznek 2 kommunikációs tűje van - adó (Tx) és vevő (Rx), az első eszköz Tx tűje a második eszköz Rx tűjéhez van csatlakoztatva, és fordítva. Ez lehetővé teszi az adatok kétirányú küldését.

* Az 1. eszköz az adatokat az Tx tűjén keresztül küldi, amelyet a 2. eszköz az Rx tűjén fogad
* Az 1. eszköz az Rx tűjén keresztül fogadja az adatokat, amelyeket a 2. eszköz az Tx tűjén keresztül küld

![UART az egyik chip Tx tűje a másik chip Rx tűjéhez csatlakozik, és fordítva](../../../../../translated_images/hu/uart.d0dbd3fb9e3728c6.webp)

> 🎓 Az adatokat egy bitenként küldik, ezt *soros* kommunikációnak nevezik. A legtöbb operációs rendszer és mikrokontroller rendelkezik *soros portokkal*, amelyek olyan csatlakozások, amelyek soros adatokat tudnak küldeni és fogadni, és elérhetők a kód számára.

Az UART eszközöknek van egy [baud rate](https://wikipedia.org/wiki/Symbol_rate) (más néven szimbólumsebesség), amely az adatküldés és -fogadás sebessége bit/másodpercben. Egy gyakori baud rate 9,600, ami azt jelenti, hogy másodpercenként 9,600 bit (0 és 1) adatot küldenek.

Az UART start és stop biteket használ - azaz küld egy start bitet, hogy jelezze, hogy egy bájtot (8 bitet) adatot fog küldeni, majd egy stop bitet, miután elküldte a 8 bitet.

Az UART sebessége hardvertől függ, de még a leggyorsabb megvalósítások sem haladják meg a 6,5 Mbps-t (megabit per másodperc, vagyis millió bit, 0 vagy 1, küldve másodpercenként).

Az UART használható GPIO tűkön keresztül - beállíthat egy tűt Tx-nek és egy másikat Rx-nek, majd ezeket csatlakoztathatja egy másik eszközhöz.

> 💁 Ha Raspberry Pi-t használ Grove Base hat-tal IoT hardverként, akkor a táblán egy UART aljzatot is láthat, amelyet az UART protokollt használó szenzorokkal való kommunikációra használhat.

### Soros perifériás interfész (SPI)

Az SPI rövid távolságú kommunikációra lett tervezve, például egy mikrokontrolleren belül egy tárolóeszközzel, például flash memóriával való kommunikációra. Ez egy vezérlő/periféria modellre épül, ahol egyetlen vezérlő (általában az IoT eszköz processzora) több perifériával lép kapcsolatba. A vezérlő mindent irányít, kiválaszt egy perifériát, és adatokat küld vagy kér.

> 💁 Az I<sup>2</sup>C-hez hasonlóan a vezérlő és periféria kifejezések nemrégiben változtak, így előfordulhat, hogy még mindig találkozik a régebbi kifejezésekkel.

Az SPI vezérlők 3 vezetéket használnak, valamint perifériánként egy extra vezetéket. A perifériák 4 vezetéket használnak. Ezek a vezetékek:

| Vezeték | Név | Leírás |
| ---- | --------- | ----------- |
| COPI | Vezérlő kimenet, periféria bemenet | Ez a vezeték az adatküldésre szolgál a vezérlőtől a perifériához. |
| CIPO | Vezérlő bemenet, periféria kimenet | Ez a vezeték az adatküldésre szolgál a perifériától a vezérlőhöz. |
| SCLK | Soros órajel | Ez a vezeték órajelet küld a vezérlő által beállított sebességgel. |
| CS   | Chip kiválasztás | A vezérlőnek több vezetéke van, perifériánként egy, és minden vezeték a megfelelő periféria CS vezetékéhez csatlakozik. |

![SPI egy vezérlővel és két perifériával](../../../../../translated_images/hu/spi.297431d6f98b386b.webp)

A CS vezeték egy periféria aktiválására szolgál, amely a COPI és CIPO vezetékeken keresztül kommunikál. Amikor a vezérlő perifériát akar váltani, deaktiválja a jelenleg aktív perifériához csatlakozó CS vezetéket, majd aktiválja a következő perifériához csatlakozó vezetéket.

Az SPI *full-duplex*, ami azt jelenti, hogy a vezérlő egyszerre tud adatokat küldeni és fogadni ugyanazon perifériától a COPI és CIPO vezetékeken keresztül. Az SPI órajelet használ az SCLK vezetéken, hogy az eszközöket szinkronban tartsa, így nem szükségesek start és stop bitek, mint az UART esetében.

Az SPI sebességére nincsenek meghatározott korlátok, a megvalósítások gyakran több megabájt adatot tudnak továbbítani másodpercenként.

Az IoT fejlesztői készletek gyakran támogatják az SPI-t néhány GPIO tűn keresztül. Például egy Raspberry Pi-n használhatja a GPIO 19, 21, 23, 24 és 26 tűket SPI-hez.

### Vezeték nélküli

Néhány szenzor képes kommunikálni szabványos vezeték nélküli protokollokon keresztül, mint például Bluetooth (főként Bluetooth Low Energy, vagy BLE), LoRaWAN (egy **Lo**ng **Ra**nge alacsony energiafogyasztású hálózati protokoll), vagy WiFi. Ezek lehetővé teszik távoli szenzorok használatát, amelyek nincsenek fizikailag csatlakoztatva egy IoT eszközhöz.

Egy példa erre a kereskedelmi talajnedvesség-érzékelők. Ezek megmérik a talaj nedvességtartalmát egy mezőn, majd az adatokat LoRaWAN-on keresztül küldik egy központi eszköznek, amely feldolgozza az adatokat vagy továbbítja az internetre. Ez lehetővé teszi, hogy a szenzor távol legyen az IoT eszköztől, amely az adatokat kezeli, csökkentve az energiafogyasztást és a nagy WiFi hálózatok vagy hosszú kábelek szükségességét.

A BLE népszerű az olyan fejlett szenzorok esetében, mint például a csuklón viselt fitnesz nyomkövetők. Ezek több szenzort kombinálnak, és a szenzoradatokat BLE-n keresztül küldik egy IoT eszköznek, például a telefonjának.

✅ Van Bluetooth szenzor az ön személyén, otthonában vagy iskolájában? Ezek lehetnek például hőmérséklet-érzékelők, jelenlét-érzékelők, eszköznyomkövetők és fitnesz eszközök.

Egy népszerű módja a kereskedelmi eszközök csatlakoztatásának a Zigbee. A Zigbee WiFi-t használ, hogy hálózatokat hozzon létre az eszközök között, ahol minden eszköz a lehető legtöbb közeli eszközhöz csatlakozik, nagy számú kapcsolatot alkotva, mint egy pókháló. Amikor egy eszköz üzenetet akar küldeni az internetre, elküldi a legközelebbi eszközöknek, amelyek továbbítják a többi közeli eszköznek, és így tovább, amíg eléri a koordinátort, és elküldhető az internetre.

> 🐝 A Zigbee név a méhek táncára utal, amelyet a kaptárba való visszatérésük után végeznek.

## Mérje meg a talaj nedvességtartalmát

A talaj nedvességtartalmát egy talajnedvesség-érzékelő, egy IoT eszköz, és egy szobanövény vagy közeli talajfolt segítségével mérheti meg.

### Feladat - talajnedvesség mérése

Dolgozza végig a megfelelő útmutatót, hogy megmérje a talaj nedvességtartalmát az IoT eszközével:

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Egylapkás számítógép - Raspberry Pi](pi-soil-moisture.md)
* [Egylapkás számítógép - Virtuális eszköz](virtual-device-soil-moisture.md)

## Szenzor kalibráció

A szenzorok az elektromos tulajdonságok, például ellenállás vagy kapacitás mérésére támaszkodnak.

> 🎓 Az ellenállás, amelyet ohmban (Ω) mérnek, azt mutatja meg, hogy mennyire ellenáll az elektromos áram áthaladásának egy anyag. Ha egy feszültséget alkalmaznak egy anyagra, az áthaladó áram mennyisége az anyag ellenállásától függ. További információt az [elektromos ellenállás Wikipedia oldalán](https://wikipedia.org/wiki/Electrical_resistance_and_conductance) talál.

> 🎓 A kapacitás, amelyet faradban (F) mérnek, egy komponens vagy áramkör képessége az elektromos energia gyűjtésére és tárolására. További információt a kapacitásról a [kapacitás Wikipedia oldalán](https://wikipedia.org/wiki/Capacitance) talál.

Ezek a mérések nem mindig hasznosak - képzeljen el egy hőmérséklet-érzékelőt, amely 22.5KΩ értéket adna! Ehelyett a mért értéket hasznos egységre kell átalakítani kalibrálással - azaz a mért értékek összehangolásával a mért mennyiséggel, hogy az új mérések megfelelő egységre legyenek átalakítva.

Néhány szenzor előre kalibrált. Például az előző leckében használt hőmérséklet-érzékelő már kalibrált volt, így °C-ban tudott hőmérsékletet visszaadni. A gyárban az első szenzort ismert hőmérsékleteknek tették ki, és az ellenállást mérték. Ezután egy számítást hoztak létre, amely átalakítja az Ω-ban (az ellenállás egysége) mért értéket °C-ra.

> 💁 Az ellenállás hőmérsékletből való kiszámításának képlete a [Steinhart–Hart egyenlet](https://wikipedia.org/wiki/Steinhart–Hart_equation).

### Talajnedvesség-érzékelő kalibráció

A talajnedvességet gravimetrikus vagy térfogati víztartalommal mérik.

* A gravimetrikus a talaj egységnyi súlyában lévő víz súlyát méri, kilogramm víz száraz talaj kilogrammonként
* A térfogati a talaj egységnyi térfogatában lévő víz térfogatát méri, köbméter víz száraz talaj köbméterenként

> 🇺🇸 Az amerikaiak számára, az egységek konzisztenciája miatt, ezek fontban vagy köblábban is mérhetők.

A talajnedvesség-érzékelők elektromos ellenállást vagy kapacitást mérnek - ez nemcsak a talajnedvességtől, hanem a talajtípustól is függ, mivel a talaj összetevői megváltoztathatják az elektromos tulajdonságait. Ideális esetben a szenzorokat kalibrálni kell - azaz a szenzor által mért értékeket össze kell hasonlítani tudományos módszerekkel kapott mérésekkel. Például egy laboratórium kiszámíthatja a gravimetrikus talajnedvességet egy adott mező mintáiból, amelyeket évente néhányszor vesznek, és ezek az értékek felhasználhatók a szenzor kalibrálására, a szenzor által mért értékek összehangolására a gravimetrikus talajnedvességgel.

![Feszültség vs talajnedvesség-tartalom grafikon](../../../../../translated_images/hu/soil-moisture-to-voltage.df86d80cda158700.webp)

A fenti grafikon bemutatja, hogyan lehet kalibrálni egy szenzort. A feszültséget rögzítik egy talajmintánál, amelyet aztán laboratóriumban mérnek, összehasonlítva a nedves súlyt a száraz súllyal (nedvesen mérve, majd sütőben szárítva és szárazon mérve). Miután néhány mérést elvégeztek, ezeket grafikonon ábrázolják, és egy vonalat illesztenek a pontokhoz. Ez a vonal használható arra, hogy az IoT eszköz által mért talajnedvesség-érzékelő értékeket tényleges talajnedvesség-mérésekké alakítsák.

💁 A rezisztív talajnedvesség-érzékelők esetében a feszültség növekszik, ahogy a talajnedvesség növekszik. A kapacitív talajnedvesség-érzékelők esetében a feszültség csökken, ahogy a talajnedvesség növekszik, így ezek grafikonjai lefelé lejtőek lennének, nem felfelé.

![Egy talajnedvesség-érték interpolálva a grafikonról](../../../../../translated_images/hu/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.webp)

A fenti grafikon egy talajnedvesség-érzékelő feszültségértékét mutatja, és követve azt a grafikon vonaláig, a tényleges talajnedvesség kiszámítható.

Ez a megközelítés azt jelenti, hogy a gazdának csak néhány laboratóriumi mérést kell elvégeznie egy mezőn, majd IoT eszközöket használhat a talajnedvesség mérésére - drasztikusan felgyorsítva a mérések elvégzésének idejét.

---

## 🚀 Kihívás

A rezisztív és kapacitív talajnedvesség-érzékelők számos különbséggel rendelkeznek. Mik ezek a különbségek, és melyik típus (ha van ilyen) a legjobb egy gazda számára? Változik-e ez a válasz a fejlődő és fejlett országok között?

## Utó-előadás kvíz

[Utó-előadás kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Áttekintés és önálló tanulás

Olvasson utána a szenzorok és aktuátorok által használt hardvereknek és protokolloknak:

* [GPIO Wikipedia oldal](https://wikipedia.org/wiki/General-purpose_input/output)
* [UART Wikipedia oldal](https://wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
* [SPI Wikipedia oldal](https://wikipedia.org/wiki/Serial_Peripheral_Interface)
* [I<sup>2</sup>C Wikipedia

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.