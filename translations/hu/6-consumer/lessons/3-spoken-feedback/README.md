# Állíts be egy időzítőt és adj szóbeli visszajelzést

![A leckéről készült sketchnote áttekintése](../../../../../translated_images/hu/lesson-23.f38483e1d4df4828.webp)

> Sketchnote készítette: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

## Előadás előtti kvíz

[Előadás előtti kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/45)

## Bevezetés

Az okos asszisztensek nem egyirányú kommunikációs eszközök. Beszélsz hozzájuk, és válaszolnak:

"Alexa, állíts be egy 3 perces időzítőt"

"Rendben, az időzítőd be van állítva 3 percre"

Az előző két leckében megtanultad, hogyan lehet beszédet szöveggé alakítani, majd hogyan lehet az időzítő beállítására vonatkozó kérést kinyerni a szövegből. Ebben a leckében megtanulod, hogyan állítsd be az időzítőt az IoT eszközön, hogyan válaszolj a felhasználónak szóbeli visszaigazolással az időzítőről, és hogyan értesítsd őket, amikor az időzítő lejár.

Ebben a leckében az alábbiakat fogjuk áttekinteni:

* [Szöveg beszéddé alakítása](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Időzítő beállítása](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Szöveg beszéddé konvertálása](../../../../../6-consumer/lessons/3-spoken-feedback)

## Szöveg beszéddé alakítása

A szöveg beszéddé alakítása, ahogy a neve is sugallja, a szöveg hanggá alakításának folyamata, amely tartalmazza a szöveget kimondott szavakként. Az alapelv az, hogy a szövegben lévő szavakat alkotó hangokra (fonémákra) bontjuk, és ezekhez a hangokhoz hanganyagot illesztünk, akár előre rögzített hangokkal, akár mesterséges intelligencia modellek által generált hangokkal.

![A tipikus szöveg-beszéd rendszerek három szakasza](../../../../../translated_images/hu/tts-overview.193843cf3f5ee09f.webp)

A szöveg-beszéd rendszerek általában 3 szakaszból állnak:

* Szövegelemzés
* Nyelvészeti elemzés
* Hullámforma generálás

### Szövegelemzés

A szövegelemzés során a megadott szöveget olyan szavakká alakítjuk, amelyek beszéddé konvertálhatók. Például, ha "Hello world"-ot konvertálunk, nincs szükség szövegelemzésre, a két szó közvetlenül beszéddé alakítható. Ha viszont "1234"-et konvertálunk, akkor ezt a kontextustól függően "Ezer kétszáz harmincnégy"-ként vagy "Egy, kettő, három, négy"-ként kell átalakítani. Például "Van 1234 almám" esetén "Ezer kétszáz harmincnégy", míg "A gyerek megszámolta 1234"-nél "Egy, kettő, három, négy".

A létrehozott szavak nemcsak a nyelvtől, hanem annak helyi változatától is függnek. Például amerikai angolban a 120 "One hundred twenty", míg brit angolban "One hundred and twenty", ahol az "and" használata jellemző a százak után.

✅ Néhány más példa, amely szövegelemzést igényel: az "in" rövidítése inch-nek, és az "st" rövidítése saint-nek vagy street-nek. Tudsz más példákat mondani a saját nyelveden, ahol a szavak kontextus nélkül kétértelműek?

Miután a szavakat meghatároztuk, nyelvészeti elemzésre küldjük őket.

### Nyelvészeti elemzés

A nyelvészeti elemzés során a szavakat fonémákra bontjuk. A fonémák nemcsak a használt betűkön alapulnak, hanem a szóban lévő többi betűn is. Például angolban a 'a' hang a 'car' és 'care' szavakban különböző. Az angol nyelvben 44 különböző fonéma van a 26 betűhöz, néhányat több betű is megoszt, például ugyanazt a fonémát használják a 'circle' és 'serpent' szavak elején.

✅ Kutass utána: Melyek a fonémák a saját nyelveden?

Miután a szavakat fonémákra bontottuk, ezekhez további adatokat kell hozzáadni az intonáció támogatásához, például a hangszín vagy időtartam módosításához a kontextustól függően. Egy példa erre angolban, hogy a hangmagasság növelésével egy mondat kérdéssé alakítható, a mondat utolsó szavának emelkedő hangmagassága kérdést jelez.

Például - a "You have an apple" mondat kijelentésként azt jelenti, hogy van egy almád. Ha a hangmagasság emelkedik a végén, az "apple" szónál, akkor kérdéssé válik: "You have an apple?", azaz van-e almád. A nyelvészeti elemzésnek a kérdőjelet kell használnia a végén, hogy eldöntse, növelje-e a hangmagasságot.

Miután a fonémák létrejöttek, hullámforma generálásra küldhetők, hogy hangkimenetet állítsanak elő.

### Hullámforma generálás

Az első elektronikus szöveg-beszéd rendszerek minden fonémához egyetlen hangfelvételt használtak, ami nagyon monoton, robotikus hangzású hangokat eredményezett. A nyelvészeti elemzés fonémákat állított elő, ezeket egy hangadatbázisból töltötték be, és összefűzték, hogy létrehozzák a hangot.

✅ Kutass utána: Keress hangfelvételeket korai beszédszintézis rendszerekből. Hasonlítsd össze a modern beszédszintézissel, például az okos asszisztensek által használt rendszerekkel.

A modern hullámforma generálás ML modelleket használ, amelyeket mély tanulással (nagyon nagy neurális hálózatok, amelyek hasonlóan működnek az agy neuronjaival) képeztek ki, hogy természetesebb hangzású hangokat állítsanak elő, amelyek megkülönböztethetetlenek lehetnek az emberi hangoktól.

> 💁 Néhány ilyen ML modell újra képezhető átvitel tanulással, hogy valós emberek hangját utánozza. Ez azt jelenti, hogy a hangot biztonsági rendszerként használni, amit a bankok egyre inkább próbálnak, már nem jó ötlet, mivel bárki, aki néhány percnyi hangfelvételt szerez rólad, képes lehet téged utánozni.

Ezeket a nagy ML modelleket arra képezik, hogy mindhárom lépést kombinálják, és végponttól végpontig terjedő beszédszintetizátorokat hozzanak létre.

## Időzítő beállítása

Az időzítő beállításához az IoT eszközödnek hívnia kell a szerver nélküli kód segítségével létrehozott REST végpontot, majd az eredményül kapott másodpercek számát felhasználva be kell állítania az időzítőt.

### Feladat - hívja meg a szerver nélküli funkciót az időzítő idő beállításához

Kövesd a megfelelő útmutatót, hogy az IoT eszközödről meghívd a REST végpontot, és beállítsd az időzítőt a szükséges időre:

* [Arduino - Wio Terminal](wio-terminal-set-timer.md)
* [Egylapos számítógép - Raspberry Pi/Virtual IoT eszköz](single-board-computer-set-timer.md)

## Szöveg beszéddé konvertálása

Ugyanaz a beszédszolgáltatás, amelyet a beszéd szöveggé alakítására használtál, használható a szöveg visszaalakítására beszéddé, amelyet az IoT eszközöd hangszóróján keresztül lejátszhatsz. A konvertálandó szöveget elküldöd a beszédszolgáltatásnak, a szükséges hang típusával (például mintavételi frekvencia), és bináris adatként visszakapod a hangot.

Amikor ezt a kérést elküldöd, *Speech Synthesis Markup Language* (SSML) nyelvet használsz, amely egy XML-alapú jelölőnyelv beszédszintézis alkalmazásokhoz. Ez nemcsak a konvertálandó szöveget határozza meg, hanem a szöveg nyelvét, a használni kívánt hangot, és akár a sebességet, hangerőt és hangmagasságot is meghatározhatja a szöveg egyes vagy összes szavára.

Például ez az SSML azt határozza meg, hogy a "Your 3 minute 5 second time has been set" szöveget brit angol hanggal, `en-GB-MiaNeural` néven konvertálja beszéddé:

```xml
<speak version='1.0' xml:lang='en-GB'>
    <voice xml:lang='en-GB' name='en-GB-MiaNeural'>
        Your 3 minute 5 second time has been set
    </voice>
</speak>
```

> 💁 A legtöbb szöveg-beszéd rendszer több hangot kínál különböző nyelvekhez, releváns akcentusokkal, például brit angol hang angol akcentussal és új-zélandi angol hang új-zélandi akcentussal.

### Feladat - szöveg beszéddé konvertálása

Dolgozd végig a megfelelő útmutatót, hogy az IoT eszközöddel szöveget beszéddé konvertálj:

* [Arduino - Wio Terminal](wio-terminal-text-to-speech.md)
* [Egylapos számítógép - Raspberry Pi](pi-text-to-speech.md)
* [Egylapos számítógép - Virtuális eszköz](virtual-device-text-to-speech.md)

---

## 🚀 Kihívás

Az SSML lehetőséget kínál arra, hogy megváltoztasd, hogyan hangzanak a szavak, például hangsúlyt adj bizonyos szavaknak, szüneteket adj hozzá, vagy megváltoztasd a hangmagasságot. Próbáld ki ezeket, küldj különböző SSML-t az IoT eszközödről, és hasonlítsd össze az eredményt. További információt az SSML-ről, beleértve azt, hogyan lehet megváltoztatni a szavak kiejtését, a [Speech Synthesis Markup Language (SSML) Version 1.1 specifikációban a World Wide Web konzorciumtól](https://www.w3.org/TR/speech-synthesis11/) olvashatsz.

## Előadás utáni kvíz

[Előadás utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/46)

## Áttekintés és önálló tanulás

* Olvass többet a beszédszintézisről a [beszédszintézis Wikipedia oldalán](https://wikipedia.org/wiki/Speech_synthesis)
* Olvass többet arról, hogyan használják a bűnözők a beszédszintézist pénzlopásra a [hamis hangok segítenek a kiberbűnözőknek pénzt lopni történetben a BBC hírein](https://www.bbc.com/news/technology-48908736)
* Tudj meg többet a szinkronszínészeket érintő kockázatokról a hangjuk szintetizált verziói miatt a [TikTok per kiemeli, hogyan károsítja az AI a szinkronszínészeket cikkben a Vice-on](https://www.vice.com/en/article/z3xqwj/this-tiktok-lawsuit-is-highlighting-how-ai-is-screwing-over-voice-actors)

## Feladat

[Időzítő törlése](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.