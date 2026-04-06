## Növényi növekedés előrejelzése IoT segítségével

![A lecke áttekintése sketchnote formában](../../../../../translated_images/hu/lesson-5.42b234299279d263.webp)

> Sketchnote készítette: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

## Előadás előtti kvíz

[Előadás előtti kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Bevezetés

A növényeknek bizonyos dolgokra van szükségük a növekedéshez - vízre, szén-dioxidra, tápanyagokra, fényre és hőre. Ebben a leckében megtanulod, hogyan számíthatod ki a növények növekedési és érési ütemét a levegő hőmérsékletének mérésével.

Ebben a leckében az alábbiakat tárgyaljuk:

* [Digitális mezőgazdaság](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Miért fontos a hőmérséklet a mezőgazdaságban?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Környezeti hőmérséklet mérése](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Növekedési foknapok (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [GDD kiszámítása hőmérséklet-érzékelő adatok alapján](../../../../../2-farm/lessons/1-predict-plant-growth)

## Digitális mezőgazdaság

A digitális mezőgazdaság átalakítja a gazdálkodás módját, eszközöket használva az adatok gyűjtésére, tárolására és elemzésére. Jelenleg a Világgazdasági Fórum által "Negyedik ipari forradalomként" leírt időszakban vagyunk, és a digitális mezőgazdaság térnyerését "Negyedik mezőgazdasági forradalomnak" vagy "Mezőgazdaság 4.0"-nak nevezik.

> 🎓 A digitális mezőgazdaság kifejezés magában foglalja az egész "mezőgazdasági értékláncot", vagyis az utat a termőföldtől az asztalig. Ez magában foglalja az élelmiszer minőségének nyomon követését szállítás és feldolgozás során, raktár- és e-kereskedelmi rendszereket, sőt még traktorbérlési alkalmazásokat is!

Ezek a változások lehetővé teszik a gazdák számára, hogy növeljék a terméshozamot, kevesebb műtrágyát és növényvédő szert használjanak, valamint hatékonyabban öntözzék a növényeket. Bár elsősorban gazdagabb országokban használják, az érzékelők és más eszközök ára lassan csökken, így elérhetőbbé válnak a fejlődő országokban is.

A digitális mezőgazdaság által lehetővé tett technikák közé tartoznak:

* Hőmérséklet mérése - a hőmérséklet mérése lehetővé teszi a gazdák számára, hogy előre jelezzék a növények növekedését és érését.
* Automatikus öntözés - a talaj nedvességtartalmának mérése és az öntözőrendszerek bekapcsolása, amikor a talaj túl száraz, ahelyett, hogy időzített öntözést alkalmaznának. Az időzített öntözés forró, száraz időszakban alulöntözést, esőben pedig túlöntözést eredményezhet. Ha csak akkor öntöznek, amikor a talajnak szüksége van rá, a gazdák optimalizálhatják a vízfelhasználást.
* Kártevőirtás - a gazdák kamerákat használhatnak automatizált robotokon vagy drónokon a kártevők ellenőrzésére, majd csak ott alkalmazhatnak növényvédő szereket, ahol szükséges, csökkentve a felhasznált növényvédő szerek mennyiségét és a helyi vízkészletekbe történő növényvédőszer-kimosódást.

✅ Kutass egy kicsit! Milyen más technikákat használnak a mezőgazdasági terméshozam javítására?

> 🎓 A "Precíziós mezőgazdaság" kifejezés a növények megfigyelését, mérését és reagálását jelenti mezőnként, vagy akár mezőrészenként. Ez magában foglalja a víz-, tápanyag- és kártevőszintek mérését és pontos reagálást, például csak egy kis mezőrész öntözését.

## Miért fontos a hőmérséklet a mezőgazdaságban?

Amikor a növényekről tanulunk, a legtöbb diákot megtanítják a víz, fény, szén-dioxid és tápanyagok szükségességére. A növényeknek azonban melegre is szükségük van a növekedéshez - ezért virágoznak a növények tavasszal, amikor a hőmérséklet emelkedik, ezért hajtanak ki a hóvirágok vagy nárciszok egy rövid meleg időszak után, és ezért olyan hatékonyak a melegházak és üvegházak a növények növekedésének elősegítésében.

> 🎓 A melegházak és üvegházak hasonló munkát végeznek, de van egy fontos különbség. A melegházakat mesterségesen fűtik, és lehetővé teszik a gazdák számára, hogy pontosabban szabályozzák a hőmérsékletet, míg az üvegházak a nap melegére támaszkodnak, és általában csak ablakok vagy más nyílások vannak, hogy kiengedjék a hőt.

A növényeknek van egy alap- vagy minimális hőmérséklete, optimális hőmérséklete és maximális hőmérséklete, amelyek mind a napi átlaghőmérsékleteken alapulnak.

* Alap hőmérséklet - ez az a minimális napi átlaghőmérséklet, amelyre a növénynek szüksége van a növekedéshez.
* Optimális hőmérséklet - ez a legjobb napi átlaghőmérséklet a legnagyobb növekedés eléréséhez.
* Maximális hőmérséklet - ez az a maximális hőmérséklet, amelyet a növény elvisel. E fölött a növény leállítja a növekedést, hogy vizet takarítson meg és életben maradjon.

> 💁 Ezek átlaghőmérsékletek, amelyek a napi és éjszakai hőmérsékletek átlagából származnak. A növényeknek napközben és éjszaka is különböző hőmérsékletekre van szükségük, hogy hatékonyabban fotoszintetizáljanak és éjszaka energiát takarítsanak meg.

Minden növényfajnak különböző értékei vannak az alap-, optimális és maximális hőmérsékletre. Ezért virágzik néhány növény forró országokban, míg mások hidegebb országokban.

✅ Kutass egy kicsit! A kertedben, iskoládban vagy helyi parkodban található növények esetében próbáld meg megtalálni az alap hőmérsékletet.

![Egy grafikon, amely a növekedési ütemet mutatja a hőmérséklet emelkedésével, majd csökkenésével, amikor a hőmérséklet túl magas lesz](../../../../../translated_images/hu/plant-growth-temp-graph.c6d69c9478e6ca83.webp)

A fenti grafikon egy példát mutat a növekedési ütem és a hőmérséklet közötti összefüggésre. Az alap hőmérsékletig nincs növekedés. A növekedési ütem az optimális hőmérsékletig növekszik, majd a csúcs elérése után csökken. 

Ennek a grafikonformának a növényfajtól függően változik. Néhány növény esetében az optimális hőmérséklet felett élesebb csökkenés tapasztalható, míg másoknál az alap és az optimális hőmérséklet közötti növekedés lassabb.

> 💁 Ahhoz, hogy a gazda a legjobb növekedést érje el, ismernie kell a három hőmérsékleti értéket, és meg kell értenie a grafikonok formáját az általa termesztett növények esetében.

Ha egy gazda szabályozni tudja a hőmérsékletet, például egy kereskedelmi melegházban, akkor optimalizálhatja a növényei számára. Egy kereskedelmi melegházban például paradicsomot termesztenek, a hőmérsékletet nappal körülbelül 25°C-ra, éjszaka pedig 20°C-ra állítják be, hogy a leggyorsabb növekedést érjék el.

> 🍅 Ezeket a hőmérsékleteket mesterséges fényekkel, műtrágyákkal és szabályozott CO
Ez a kód megnyitja a CSV fájlt, majd hozzáfűz egy új sort a végéhez. A sor tartalmazza az aktuális dátumot és időt ember által olvasható formátumban, valamint az IoT eszköztől kapott hőmérsékletet. Az adatokat [ISO 8601 formátumban](https://wikipedia.org/wiki/ISO_8601) tároljuk időzónával, de mikroszekundumok nélkül.

1. Futtassa a kódot ugyanúgy, mint korábban, ügyelve arra, hogy az IoT eszköz adatokat küldjön. Egy `temperature.csv` nevű CSV fájl jön létre ugyanabban a mappában. Ha megnyitja, látni fogja a dátumokat/időket és a hőmérsékleti méréseket:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Futtassa a kódot egy ideig, hogy adatokat gyűjtsön. Ideális esetben egy teljes napig futtassa, hogy elegendő adatot gyűjtsön a GDD számításokhoz.

    
> 💁 Ha Virtuális IoT Eszközt használ, jelölje be a véletlenszerű jelölőnégyzetet, és állítson be egy tartományt, hogy elkerülje ugyanazon hőmérséklet visszatérését minden alkalommal, amikor a hőmérsékleti érték megjelenik.
    ![Jelölje be a véletlenszerű jelölőnégyzetet, és állítson be egy tartományt](../../../../../translated_images/hu/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.webp) 

    > 💁 Ha egy teljes napig szeretné futtatni, akkor győződjön meg arról, hogy a számítógép, amelyen a szerver kódja fut, nem megy alvó módba, akár az energia-beállítások megváltoztatásával, akár valami hasonló futtatásával, mint [ez a Python script, amely aktívan tartja a rendszert](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Ezt a kódot megtalálja a [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server) mappában.

### Feladat - GDD kiszámítása a tárolt adatok alapján

Miután a szerver rögzítette a hőmérsékleti adatokat, kiszámítható a növény GDD értéke.

A lépések ehhez manuálisan:

1. Keresse meg a növény alap hőmérsékletét. Például az eper esetében az alap hőmérséklet 10°C.

1. A `temperature.csv` fájlból keresse meg a napi legmagasabb és legalacsonyabb hőmérsékleteket.

1. Használja a korábban megadott GDD számítást a GDD kiszámításához.

Például, ha a napi legmagasabb hőmérséklet 25°C, a legalacsonyabb pedig 12°C:

![GDD = 25 + 12 osztva 2-vel, majd az eredményből kivonva 10, ami 8.5](../../../../../translated_images/hu/gdd-calculation-strawberries.59f57db94b22adb8.webp)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Ezért az eper **8.5** GDD-t kapott. Az epernek körülbelül 250 GDD-re van szüksége ahhoz, hogy termést hozzon, tehát még van idő.

---

## 🚀 Kihívás

A növényeknek nem csak hőre van szükségük a növekedéshez. Milyen más tényezők szükségesek?

Ezekhez keressen olyan szenzorokat, amelyek mérni tudják őket. Mi a helyzet az aktuátorokkal, amelyek szabályozni tudják ezeket a szinteket? Hogyan állítana össze egy vagy több IoT eszközt a növények növekedésének optimalizálására?

## Előadás utáni kvíz

[Előadás utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Áttekintés és önálló tanulás

* Olvasson többet a digitális mezőgazdaságról a [Digitális Mezőgazdaság Wikipedia oldalon](https://wikipedia.org/wiki/Digital_agriculture). Olvasson többet a precíziós mezőgazdaságról is a [Precíziós Mezőgazdaság Wikipedia oldalon](https://wikipedia.org/wiki/Precision_agriculture).
* A teljes növekedési foknapok számítása bonyolultabb, mint az itt megadott egyszerűsített verzió. Olvasson többet a bonyolultabb egyenletről és arról, hogyan kezelje az alapérték alatti hőmérsékleteket a [Növekedési Foknap Wikipedia oldalon](https://wikipedia.org/wiki/Growing_degree-day).
* Az élelmiszer jövőben szűkös lehet, ha továbbra is ugyanazokat a módszereket használjuk a gazdálkodásban. Tudjon meg többet a csúcstechnológiás gazdálkodási technikákról ebben a [Jövő Csúcstechnológiás Farmjai videóban a YouTube-on](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Feladat

[Vizualizálja a GDD adatokat egy Jupyter Notebook segítségével](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.