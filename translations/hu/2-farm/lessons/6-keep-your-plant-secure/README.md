<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "81c437c568eee1b0dda1f04e88150d37",
  "translation_date": "2025-08-27T23:04:17+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/README.md",
  "language_code": "hu"
}
-->
# Tartsd biztonságban a növényedet

![A lecke vázlatos áttekintése](../../../../../translated_images/hu/lesson-10.829c86b80b9403bb770929ee553a1d293afe50dc23121aaf9be144673ae012cc.jpg)

> Vázlatrajz: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

## Előadás előtti kvíz

[Előadás előtti kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Bevezetés

Az utóbbi leckékben létrehoztál egy talajfigyelő IoT eszközt, és csatlakoztattad a felhőhöz. De mi történik, ha egy rivális gazda által felbérelt hackerek átveszik az irányítást az IoT eszközeid felett? Mi van, ha hamis magas talajnedvesség-értékeket küldenek, így a növényeid sosem kapnak vizet, vagy folyamatosan működtetik az öntözőrendszert, ami túlöntözéssel elpusztítja a növényeidet, és jelentős vízköltségeket okoz?

Ebben a leckében megtanulod, hogyan biztosítsd az IoT eszközeidet. Mivel ez az utolsó lecke ebben a projektben, megtanulod azt is, hogyan tisztítsd meg a felhőalapú erőforrásaidat, csökkentve a potenciális költségeket.

Ebben a leckében az alábbiakat fogjuk áttekinteni:

* [Miért van szükség az IoT eszközök biztonságára?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Kriptográfia](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [IoT eszközök biztonságának megteremtése](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [X.509 tanúsítvány létrehozása és használata](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 Ez az utolsó lecke ebben a projektben, ezért a lecke és a feladat elvégzése után ne felejtsd el megtisztítani a felhőszolgáltatásaidat. A szolgáltatásokra szükséged lesz a feladat befejezéséhez, ezért győződj meg róla, hogy először azt teljesíted.
>
> Ha szükséges, nézd meg [a projekt tisztítási útmutatóját](../../../clean-up.md) az utasításokért.

## Miért van szükség az IoT eszközök biztonságára?

Az IoT biztonság azt jelenti, hogy csak a várt eszközök csatlakozhatnak a felhőalapú IoT szolgáltatásodhoz, és küldhetnek telemetriát, valamint csak a felhőszolgáltatásod küldhet parancsokat az eszközeidnek. Az IoT adatok személyesek is lehetnek, például orvosi vagy intim adatok, ezért az egész alkalmazásnak figyelembe kell vennie a biztonságot, hogy megakadályozza az adatok kiszivárgását.

Ha az IoT alkalmazásod nem biztonságos, számos kockázatot rejt magában:

* Egy hamis eszköz helytelen adatokat küldhet, ami miatt az alkalmazásod helytelenül reagál. Például folyamatosan magas talajnedvesség-értékeket küldhet, így az öntözőrendszer sosem kapcsol be, és a növényeid kiszáradnak.
* Jogosulatlan felhasználók hozzáférhetnek az IoT eszközök adataihoz, beleértve személyes vagy üzleti szempontból kritikus adatokat.
* Hackerek parancsokat küldhetnek, hogy az eszközt olyan módon irányítsák, ami kárt okozhat az eszközben vagy a kapcsolódó hardverben.
* Az IoT eszközhöz csatlakozva a hackerek további hálózatokhoz férhetnek hozzá, hogy privát rendszerekhez jussanak.
* Rosszindulatú felhasználók hozzáférhetnek személyes adatokhoz, és zsarolásra használhatják azokat.

Ezek valós életbeli forgatókönyvek, és gyakran előfordulnak. Néhány példát már korábbi leckékben bemutattunk, de itt van néhány további:

* 2018-ban hackerek egy halak tartályának termosztátján keresztül, amely nyitott WiFi hozzáférési pontot használt, hozzáfértek egy kaszinó hálózatához, hogy adatokat lopjanak. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* 2016-ban a Mirai Botnet szolgáltatásmegtagadási támadást indított a Dyn ellen, amely egy internetes szolgáltató, és ezzel nagy részeit bénította meg az internetnek. Ez a botnet DVR-eket és kamerákat használt, amelyek alapértelmezett felhasználóneveket és jelszavakat használtak, és innen indította a támadást. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* A Spiral Toys nyilvánosan elérhetővé tette a CloudPets kapcsolt játékok felhasználóinak adatbázisát az interneten. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* A Strava megjelölte a futókat, akiket elhaladtál, és megmutatta az útvonalaikat, lehetővé téve idegenek számára, hogy gyakorlatilag lássák, hol laksz. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Kutatás: Keress további példákat IoT hackekre és IoT adatok megsértésére, különösen személyes tárgyakkal, mint például internethez kapcsolt fogkefék vagy mérlegek. Gondold át, milyen hatással lehetnek ezek a hackek az áldozatokra vagy ügyfelekre.

> 💁 A biztonság hatalmas téma, és ez a lecke csak az alapokat érinti az eszközök felhőhöz való csatlakozásával kapcsolatban. Nem foglalkozunk olyan témákkal, mint az adatok változásának figyelése átvitel közben, eszközök közvetlen hackelése, vagy eszközkonfigurációk módosítása. Az IoT hackelés olyan fenyegetés, hogy olyan eszközöket fejlesztettek ki, mint az [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn). Ezek az eszközök hasonlóak a számítógépen található vírusirtó és biztonsági eszközökhöz, csak kifejezetten kis, alacsony teljesítményű IoT eszközökre tervezve.

## Kriptográfia

Amikor egy eszköz csatlakozik egy IoT szolgáltatáshoz, egy azonosítót használ, hogy azonosítsa magát. A probléma az, hogy ez az azonosító klónozható - egy hacker beállíthat egy rosszindulatú eszközt, amely ugyanazt az azonosítót használja, mint egy valódi eszköz, de hamis adatokat küld.

![Mind a valódi, mind a rosszindulatú eszköz ugyanazt az azonosítót használhatja telemetria küldésére](../../../../../translated_images/hu/iot-device-and-hacked-device-connecting.e0671675df74d6d99eb1dedb5a670e606f698efa6202b1ad4c8ae548db299cc6.png)

A megoldás az, hogy az elküldött adatokat egy kódolt formátumba alakítjuk, egy olyan érték segítségével, amelyet csak az eszköz és a felhő ismer. Ezt a folyamatot *titkosításnak* nevezzük, és az adat titkosításához használt értéket *titkosítási kulcsnak* hívjuk.

![Ha titkosítást használunk, akkor csak a titkosított üzeneteket fogadják el, a többit elutasítják](../../../../../translated_images/hu/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f979e46f2849b573564eeb4a4dc5b52f669f62745397492fb.png)

A felhőszolgáltatás ezután visszaalakítja az adatokat olvasható formátumba, egy *dekódolási kulcs* segítségével. Ha a titkosított üzenetet nem lehet dekódolni a kulccsal, az eszközt feltörték, és az üzenetet elutasítják.

A titkosítás és dekódolás technikáját *kriptográfiának* nevezzük.

### Korai kriptográfia

A legkorábbi kriptográfiai módszerek helyettesítési kódok voltak, amelyek 3500 évre nyúlnak vissza. A helyettesítési kódok egy betűt helyettesítenek egy másikkal. Például a [Caesar-kód](https://wikipedia.org/wiki/Caesar_cipher) az ábécét egy meghatározott mennyiséggel eltolja, és csak az üzenet küldője és a címzett tudja, hány betűt kell eltolni.

A [Vigenère-kód](https://wikipedia.org/wiki/Vigenère_cipher) továbbfejlesztette ezt, szavakat használva a szöveg titkosítására, így az eredeti szöveg minden betűjét más mennyiséggel tolta el, nem mindig ugyanazzal a számmal.

A kriptográfiát széles körben használták különböző célokra, például egy fazekas máz receptjének védelmére az ókori Mezopotámiában, titkos szerelmes levelek írására Indiában, vagy ókori egyiptomi mágikus varázslatok titokban tartására.

### Modern kriptográfia

A modern kriptográfia sokkal fejlettebb, és nehezebb feltörni, mint a korai módszereket. A modern kriptográfia bonyolult matematikát használ az adatok titkosítására, amely túl sok lehetséges kulcsot tartalmaz ahhoz, hogy erőszakos támadásokkal feltörhető legyen.

A kriptográfiát számos módon használják biztonságos kommunikációhoz. Ha ezt az oldalt a GitHubon olvasod, észreveheted, hogy a weboldal címe *HTTPS*-sel kezdődik, ami azt jelenti, hogy a böngésződ és a GitHub webszerverei közötti kommunikáció titkosított. Ha valaki képes lenne olvasni az internetes forgalmat a böngésződ és a GitHub között, nem tudná elolvasni az adatokat, mivel azok titkosítva vannak. A számítógéped akár az összes adatot is titkosíthatja a merevlemezeden, így ha valaki ellopja, nem tudja elolvasni az adataidat a jelszavad nélkül.

> 🎓 A HTTPS jelentése HyperText Transfer Protocol **Secure**

Sajnos nem minden biztonságos. Néhány eszköz nem rendelkezik biztonsággal, mások könnyen feltörhető kulcsokat használnak, vagy néha az összes azonos típusú eszköz ugyanazt a kulcsot használja. Voltak olyan esetek, amikor nagyon személyes IoT eszközök mind ugyanazt a jelszót használták a WiFi vagy Bluetooth kapcsolathoz. Ha csatlakozhatsz a saját eszközödhöz, csatlakozhatsz másokéhoz is. Miután csatlakoztál, hozzáférhetsz nagyon privát adatokhoz, vagy irányíthatod az eszközüket.

> 💁 A modern kriptográfia bonyolultsága és az állítások ellenére, hogy a titkosítás feltörése milliárd éveket vehet igénybe, a kvantumszámítógépek megjelenése lehetővé tette, hogy az összes ismert titkosítást nagyon rövid idő alatt feltörjék!

### Szimmetrikus és aszimmetrikus kulcsok

A titkosításnak két típusa van - szimmetrikus és aszimmetrikus.

**Szimmetrikus** titkosítás ugyanazt a kulcsot használja az adatok titkosítására és dekódolására. Mind a küldőnek, mind a fogadónak ismernie kell ugyanazt a kulcsot. Ez a legkevésbé biztonságos típus, mivel a kulcsot valahogy meg kell osztani. Ahhoz, hogy a küldő titkosított üzenetet küldjön a címzettnek, először el kell küldenie a címzettnek a kulcsot.

![A szimmetrikus kulcs titkosítás ugyanazt a kulcsot használja az üzenet titkosítására és dekódolására](../../../../../translated_images/hu/send-message-symmetric-key.a2e8ad0d495896ff.webp)

Ha a kulcsot ellopják az átvitel során, vagy a küldőt vagy a címzettet feltörik, és megtalálják a kulcsot, a titkosítás feltörhető.

![A szimmetrikus kulcs titkosítás csak akkor biztonságos, ha a hacker nem szerzi meg a kulcsot - ha igen, elfoghatja és dekódolhatja az üzenetet](../../../../../translated_images/hu/send-message-symmetric-key-hacker.e7cb53db1707adfb.webp)

**Aszimmetrikus** titkosítás 2 kulcsot használ - egy titkosítási kulcsot és egy dekódolási kulcsot, amelyeket nyilvános/privát kulcspárnak nevezünk. A nyilvános kulcsot az üzenet titkosítására használják, de nem lehet vele dekódolni, a privát kulcsot az üzenet dekódolására használják, de nem lehet vele titkosítani.

![Az aszimmetrikus titkosítás különböző kulcsot használ az üzenet titkosítására és dekódolására. A titkosítási kulcsot elküldik az üzenetküldőknek, hogy titkosítsák az üzenetet, mielőtt elküldik a címzettnek, aki birtokolja a kulcsokat](../../../../../translated_images/hu/send-message-asymmetric.7abe327c62615b8c.webp)

A címzett megosztja a nyilvános kulcsát, és a küldő ezt használja az üzenet titkosítására. Miután az üzenetet elküldték, a címzett a privát kulcsával dekódolja azt. Az aszimmetrikus titkosítás biztonságosabb, mivel a privát kulcsot a címzett titokban tartja, és sosem osztja meg. Bárki megkaphatja a nyilvános kulcsot, mivel az csak üzenetek titkosítására használható.

A szimmetrikus titkosítás gyorsabb, mint az aszimmetrikus, az aszimmetrikus viszont biztonságosabb. Néhány rendszer mindkettőt használja - az aszimmetrikus titkosítást használja a szimmetrikus kulcs titkosítására és megosztására, majd a szimmetrikus kulcsot használja az összes adat titkosítására. Ez biztonságosabbá teszi a szimmetrikus kulcs megosztását a küldő és a címzett között, és gyorsabbá az adatok titkosítását és dekódolását.

## IoT eszközök biztonságának megteremtése

Az IoT eszközök szimmetrikus vagy aszimmetrikus titkosítással biztosíthatók. A szimmetrikus egyszerűbb, de kevésbé biztonságos.

### Szimmetrikus kulcsok

Amikor beállítottad az IoT eszközödet, hogy kapcsolatba lépjen az IoT Hubbal, egy kapcsolati karakterláncot használtál. Egy példa kapcsolati karakterlánc:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Ez a kapcsolati karakterlánc három részből áll, amelyeket pontosvessző választ el, és minden rész egy kulcs és egy érték:

| Kulcs | Érték | Leírás |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | Az IoT Hub URL-je |
| DeviceId | `soil-moisture-sensor` | Az eszköz egyedi azonosítója |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | Egy szimmetrikus kulcs, amelyet az eszköz és az IoT Hub ismer |

A kapcsolati karakterlánc utolsó része, a `SharedAccessKey`, az a szimmetrikus kulcs, amelyet az eszköz és az IoT Hub ismer. Ez a kulcs sosem kerül elküldésre az eszk
💁 Az IoT eszközödnek pontos időre van szüksége a lejárati idő miatt, amit általában egy [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) szerverről olvas be. Ha az idő nem pontos, a kapcsolat sikertelen lesz.
Miután a kapcsolat létrejött, az IoT Hub és az eszköz között küldött összes adat titkosítva lesz a megosztott hozzáférési kulccsal.

✅ Mit gondolsz, mi történik, ha több eszköz ugyanazt a kapcsolatkarakterláncot használja?

> 💁 Nem jó biztonsági gyakorlat a kulcsot a kódban tárolni. Ha egy hacker hozzáfér a forráskódodhoz, megszerezheti a kulcsot. Emellett nehezebb a kód kiadása is, mivel minden eszközhöz újra kellene fordítani a kódot egy frissített kulccsal. Jobb megoldás, ha ezt a kulcsot egy hardveres biztonsági modulból töltöd be – egy olyan chipből az IoT eszközön, amely titkosított értékeket tárol, és amelyeket a kódod el tud olvasni.
>
> Az IoT tanulása során gyakran egyszerűbb a kulcsot a kódban elhelyezni, ahogy azt egy korábbi leckében tetted, de biztosítanod kell, hogy ez a kulcs ne kerüljön nyilvános forráskód-kezelésbe.

Az eszközöknek 2 kulcsuk és 2 hozzájuk tartozó kapcsolatkarakterláncuk van. Ez lehetővé teszi a kulcsok forgatását – azaz az egyik kulcsról a másikra való váltást, ha az első kompromittálódik, és az első kulcs újragenerálását.

### X.509 tanúsítványok

Amikor nyilvános/magánkulcs párral végzett aszimmetrikus titkosítást használsz, a nyilvános kulcsodat el kell juttatnod bárkinek, aki adatot szeretne küldeni neked. A probléma az, hogy a kulcs címzettje hogyan lehet biztos abban, hogy az valóban a te nyilvános kulcsod, és nem valaki másé, aki téged próbál megjátszani? Ahelyett, hogy egy kulcsot adnál meg, megadhatod a nyilvános kulcsodat egy olyan tanúsítványban, amelyet egy megbízható harmadik fél, az úgynevezett X.509 tanúsítvány, hitelesített.

Az X.509 tanúsítványok digitális dokumentumok, amelyek tartalmazzák a nyilvános/magánkulcs pár nyilvános kulcs részét. Ezeket általában egy megbízható szervezet, az úgynevezett [tanúsítványkiadó hatóságok](https://wikipedia.org/wiki/Certificate_authority) (CA-k) bocsátják ki, és a CA digitálisan aláírja őket, hogy jelezze, a kulcs érvényes és tőled származik. A tanúsítványban és abban, hogy a nyilvános kulcs attól származik, akitől a tanúsítvány állítja, hogy származik, azért bízol, mert bízol a CA-ban, hasonlóan ahhoz, ahogy egy útlevélben vagy jogosítványban bízol, mert bízol az azt kiállító országban. A tanúsítványok pénzbe kerülnek, de lehetőség van „önaláírásra” is, azaz saját magad által aláírt tanúsítvány létrehozására tesztelési célokra.

> 💁 Soha ne használj önaláírt tanúsítványt egy éles kiadásban.

Ezek a tanúsítványok számos mezőt tartalmaznak, például hogy kitől származik a nyilvános kulcs, a tanúsítványkiadó hatóság adatait, aki kiállította, meddig érvényes, és magát a nyilvános kulcsot. Mielőtt egy tanúsítványt használnál, jó gyakorlat ellenőrizni, hogy az eredeti CA írta-e alá.

✅ A tanúsítvány mezőinek teljes listáját elolvashatod a [Microsoft Understanding X.509 Public Key Certificates oktatóanyagában](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields).

X.509 tanúsítványok használatakor mind a küldőnek, mind a címzettnek megvan a saját nyilvános és magánkulcsa, valamint mindkettőjüknek van X.509 tanúsítványa, amely tartalmazza a nyilvános kulcsot. Ezután valamilyen módon kicserélik az X.509 tanúsítványaikat, egymás nyilvános kulcsait használva titkosítják az általuk küldött adatokat, és a saját magánkulcsukkal dekódolják a kapott adatokat.

![A nyilvános kulcs megosztása helyett megoszthatsz egy tanúsítványt. A tanúsítvány használója ellenőrizheti, hogy az tőled származik-e, a tanúsítványt aláíró tanúsítványkiadó hatóságnál.](../../../../../translated_images/hu/send-message-certificate.9cc576ac1e46b76e.webp)

Az X.509 tanúsítványok egyik nagy előnye, hogy megoszthatók az eszközök között. Létrehozhatsz egy tanúsítványt, feltöltheted az IoT Hubba, és ezt használhatod az összes eszközödhöz. Minden eszköznek csak a magánkulcsot kell ismernie, hogy dekódolhassa az IoT Hubtól kapott üzeneteket.

Az eszköz által az IoT Hubnak küldött üzenetek titkosítására használt tanúsítványt a Microsoft bocsátja ki. Ez ugyanaz a tanúsítvány, amelyet számos Azure-szolgáltatás használ, és néha be van építve az SDK-kba.

> 💁 Ne feledd, a nyilvános kulcs éppen az – nyilvános. Az Azure nyilvános kulcsa csak az Azure-nak küldött adatok titkosítására használható, nem azok dekódolására, így bárhol megosztható, beleértve a forráskódot is. Például megtekintheted a [Azure IoT C SDK forráskódjában](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c).

✅ Az X.509 tanúsítványokkal kapcsolatban sok szakkifejezés létezik. Elolvashatod néhány gyakran előforduló kifejezés definícióját a [The layman’s guide to X.509 certificate jargon](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn) című cikkben.

## X.509 tanúsítvány létrehozása és használata

Az X.509 tanúsítvány létrehozásának lépései:

1. Hozz létre egy nyilvános/magánkulcs párt. Az egyik legszélesebb körben használt algoritmus a nyilvános/magánkulcs pár létrehozására a [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem)) (RSA).

1. Nyújtsd be a nyilvános kulcsot a kapcsolódó adatokkal aláírásra, akár egy CA által, akár önaláírással.

Az Azure CLI parancsokat biztosít új eszközazonosság létrehozására az IoT Hubban, valamint a nyilvános/magánkulcs pár automatikus generálására és egy önaláírt tanúsítvány létrehozására.

> 💁 Ha részletesen szeretnéd látni a lépéseket az Azure CLI használata helyett, megtalálod a [Microsoft IoT Hub dokumentációjában az OpenSSL használatával történő önaláírt tanúsítványok létrehozásáról szóló oktatóanyagban](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn).

### Feladat – eszközazonosság létrehozása X.509 tanúsítvánnyal

1. Futtasd az alábbi parancsot egy új eszközazonosság regisztrálásához, amely automatikusan generálja a kulcsokat és a tanúsítványokat:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Cseréld ki a `<hub_name>` helyére az IoT Hub nevére, amelyet használsz.

    Ez létrehoz egy `soil-moisture-sensor-x509` azonosítójú eszközt, hogy megkülönböztesd a korábbi leckében létrehozott eszközazonosságtól. Ez a parancs két fájlt is létrehoz az aktuális könyvtárban:

    * `soil-moisture-sensor-x509-key.pem` – ez a fájl tartalmazza az eszköz magánkulcsát.
    * `soil-moisture-sensor-x509-cert.pem` – ez az eszköz X.509 tanúsítványfájlja.

    Tartsd ezeket a fájlokat biztonságban! A magánkulcs fájlt nem szabad nyilvános forráskód-kezelésbe feltölteni.

### Feladat – az X.509 tanúsítvány használata az eszközkódodban

Dolgozd végig a megfelelő útmutatót, hogy az IoT eszközödet az X.509 tanúsítvány használatával csatlakoztasd a felhőhöz:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Egylapkás számítógép - Raspberry Pi/Virtual IoT device](single-board-computer-x509.md)

---

## 🚀 Kihívás

Számos módja van az Azure-szolgáltatások, például az Erőforráscsoportok és az IoT Hubok létrehozásának, kezelésének és törlésének. Az egyik lehetőség az [Azure Portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) – egy webalapú felület, amely grafikus kezelőfelületet biztosít az Azure-szolgáltatások kezeléséhez.

Látogass el a [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) oldalra, és ismerkedj meg a portállal. Nézd meg, hogy tudsz-e létrehozni egy IoT Hubot a portálon keresztül, majd töröld azt.

**Tipp** – amikor a portálon keresztül hozol létre szolgáltatásokat, nem szükséges előre létrehozni egy Erőforráscsoportot, egyet létrehozhatsz a szolgáltatás létrehozásakor. Ügyelj arra, hogy töröld, amikor végeztél!

Rengeteg dokumentációt, oktatóanyagot és útmutatót találhatsz az Azure Portalról az [Azure Portal dokumentációjában](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Utólagos kvíz

[Utólagos kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Áttekintés és önálló tanulás

* Olvass utána a kriptográfia történetének a [Kriptográfia története Wikipedia oldalon](https://wikipedia.org/wiki/History_of_cryptography).
* Olvass utána az X.509 tanúsítványoknak az [X.509 Wikipedia oldalon](https://wikipedia.org/wiki/X.509).

## Feladat

[Építs egy új IoT eszközt](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.