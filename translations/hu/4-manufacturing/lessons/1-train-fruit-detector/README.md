# Gyümölcsminőség-ellenőrző betanítása

![A lecke áttekintése sketchnote formájában](../../../../../translated_images/hu/lesson-15.843d21afdc6fb2bb.webp)

> Sketchnote készítette: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

Ez a videó bemutatja az Azure Custom Vision szolgáltatást, amelyet ebben a leckében fogunk tárgyalni.

[![Custom Vision – Könnyen használható gépi tanulás | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 Kattints a fenti képre a videó megtekintéséhez

## Előadás előtti kvíz

[Előadás előtti kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## Bevezetés

A mesterséges intelligencia (AI) és a gépi tanulás (ML) közelmúltbeli fejlődése számos új lehetőséget kínál a mai fejlesztők számára. Az ML modellek képesek felismerni különböző dolgokat képeken, például éretlen gyümölcsöket, és ezeket az IoT eszközökben lehet használni a termények válogatására, akár a betakarítás során, akár a gyárakban vagy raktárakban történő feldolgozás közben.

Ebben a leckében megismerkedsz a képosztályozással – az ML modellek használatával különböző dolgok képeinek megkülönböztetésére. Megtanulod, hogyan lehet betanítani egy képosztályozót, amely megkülönbözteti a jó minőségű gyümölcsöket a rosszaktól, például az éretlen, túlérett, sérült vagy rothadt gyümölcsöktől.

A lecke során az alábbi témákat érintjük:

* [AI és ML használata az élelmiszerek válogatására](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Képosztályozás gépi tanulással](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Képosztályozó betanítása](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Képosztályozó tesztelése](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Képosztályozó újratanítása](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## AI és ML használata az élelmiszerek válogatására

A világ népességének élelmezése nehéz feladat, különösen olyan áron, amely mindenki számára megfizethető. Az egyik legnagyobb költség a munkaerő, ezért a gazdák egyre inkább az automatizálás és az IoT eszközök felé fordulnak, hogy csökkentsék a munkaerőköltségeket. A kézi betakarítás munkaigényes (és gyakran hátfájást okozó munka), ezért különösen a gazdagabb országokban gépekkel helyettesítik. Bár a gépi betakarítás költséghatékonyabb, van egy hátránya – a termény válogatásának képessége a betakarítás során.

Nem minden termény érik egyenletesen. Például a paradicsom esetében előfordulhat, hogy néhány zöld gyümölcs még a tőkén van, amikor a többség már érett. Bár ezek korai betakarítása pazarlás, a gazdák számára olcsóbb és egyszerűbb mindent géppel betakarítani, majd később kidobni az éretlen termést.

✅ Nézz meg különböző gyümölcsöket vagy zöldségeket, akár a környékeden lévő farmokon, a kertedben, vagy a boltokban. Mind egyforma érettségűek, vagy látsz eltéréseket?

Az automatizált betakarítás elterjedésével a termény válogatása a betakarítás helyett a gyárakba került. Az élelmiszerek hosszú szállítószalagokon haladtak, ahol emberek csoportjai válogatták ki a nem megfelelő minőségű terményeket. Bár a gépi betakarítás olcsóbbá tette a folyamatot, az élelmiszerek kézi válogatása továbbra is költséges volt.

![Ha egy piros paradicsomot észlelnek, az zavartalanul folytatja útját. Ha egy zöld paradicsomot észlelnek, egy kar vagy levegőfúvóka egy hulladéktartályba löki.](../../../../../translated_images/hu/optical-tomato-sorting.61aa134bdda4e5b1.webp)

A következő fejlődési lépés az volt, hogy gépeket használtak a válogatásra, akár a betakarítógépbe építve, akár a feldolgozóüzemekben. Az első generációs gépek optikai érzékelőket használtak a színek felismerésére, és karok vagy levegőfúvókák segítségével a zöld paradicsomokat egy hulladéktartályba lökték, míg a piros paradicsomok zavartalanul folytatták útjukat a szállítószalagokon.

Ebben a videóban, ahogy a paradicsomok egyik szállítószalagról a másikra esnek, a zöld paradicsomokat érzékelik, és karok segítségével egy tartályba lövik.

✅ Milyen feltételek szükségesek egy gyárban vagy a szántóföldön ahhoz, hogy ezek az optikai érzékelők megfelelően működjenek?

A legújabb válogatógépek az AI és az ML előnyeit használják ki, olyan modelleket alkalmazva, amelyek képesek megkülönböztetni a jó minőségű terményeket a rosszaktól, nemcsak az olyan nyilvánvaló színbeli különbségek alapján, mint a zöld és piros paradicsom, hanem az olyan finomabb megjelenésbeli eltérések alapján is, amelyek betegséget vagy sérülést jelezhetnek.

## Képosztályozás gépi tanulással

A hagyományos programozás során adatokat adsz meg, alkalmazol egy algoritmust, és eredményt kapsz. Például az előző projektben GPS koordinátákat és egy geokerítést adtál meg, alkalmaztál egy algoritmust, amelyet az Azure Maps biztosított, és eredményként megkaptad, hogy a pont a geokerítésen belül vagy kívül van. Több adatot adsz meg, több eredményt kapsz.

![A hagyományos fejlesztés bemenetet és algoritmust használ, hogy eredményt adjon. A gépi tanulás bemenetet és ismert eredményeket használ egy modell betanításához, amely új bemenetekből új eredményeket generál.](../../../../../translated_images/hu/traditional-vs-ml.5c20c169621fa539.webp)

A gépi tanulás ezt megfordítja – az adatokkal és az ismert eredményekkel kezded, és a gépi tanulási algoritmus az adatokból tanul. Ezután a betanított algoritmust, amelyet *gépi tanulási modellnek* vagy egyszerűen *modellnek* nevezünk, új adatokkal használhatod, hogy új eredményeket kapj.

> 🎓 A gépi tanulási algoritmus adatból való tanulási folyamata a *betanítás*. A bemenetek és az ismert eredmények a *betanítási adatok*.

Például adhatsz egy modellnek milliónyi képet éretlen banánokról bemeneti adatként, a betanítási eredményt pedig `éretlen`-re állítod, és milliónyi képet érett banánokról, az eredményt `érett`-re állítva. Az ML algoritmus ezután egy modellt hoz létre ezek alapján. Ezután adhatsz a modellnek egy új képet egy banánról, és az megjósolja, hogy az új kép érett vagy éretlen banánt ábrázol.

> 🎓 Az ML modellek eredményeit *előrejelzéseknek* nevezzük.

![2 banán: egy érett, amelyre az előrejelzés 99,7% érett és 0,3% éretlen, és egy éretlen, amelyre az előrejelzés 1,4% érett és 98,6% éretlen.](../../../../../translated_images/hu/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50e.webp)

Az ML modellek nem adnak bináris választ, hanem valószínűségeket. Például egy modell kaphat egy képet egy banánról, és előrejelzést adhat `érett` 99,7%-kal és `éretlen` 0,3%-kal. A kódod ezután kiválasztja a legjobb előrejelzést, és eldönti, hogy a banán érett.

Az ilyen képek felismerésére használt ML modellt *képosztályozónak* nevezzük – címkézett képeket kap, majd ezek alapján osztályozza az új képeket.

> 💁 Ez egy leegyszerűsítés, és számos más módja is van a modellek betanításának, amelyek nem mindig igényelnek címkézett eredményeket, például a felügyelet nélküli tanulás. Ha többet szeretnél megtudni az ML-ről, nézd meg a [ML kezdőknek, egy 24 leckés tananyagot a gépi tanulásról](https://aka.ms/ML-beginners).

## Képosztályozó betanítása

Egy képosztályozó sikeres betanításához milliónyi képre van szükség. Azonban, ha már van egy képosztályozód, amelyet milliónyi vagy milliárdnyi különféle képen betanítottak, újra felhasználhatod és újra betaníthatod egy kisebb képkészlettel, hogy nagyszerű eredményeket érj el, egy *transzfer tanulásnak* nevezett folyamat segítségével.

> 🎓 A transzfer tanulás azt jelenti, hogy egy meglévő ML modell tanulását átvisszük egy új modellre az új adatok alapján.

Ha egy képosztályozót már betanítottak különféle képek széles skáláján, a belső mechanizmusai kiválóan felismerik az alakzatokat, színeket és mintázatokat. A transzfer tanulás lehetővé teszi, hogy a modell az eddig megtanultakat felhasználja új képek felismerésére.

![Ha egyszer felismered az alakzatokat, különböző konfigurációkban felismerheted például egy hajót vagy egy macskát.](../../../../../translated_images/hu/shapes-to-images.1a309f0ea88dd66f.webp)

Ezt úgy képzelheted el, mint a gyerekek alakzatokat tanító könyveit, ahol ha egyszer felismered a félkört, a téglalapot és a háromszöget, felismerheted egy vitorlás hajót vagy egy macskát az alakzatok elrendezése alapján. A képosztályozó felismeri az alakzatokat, a transzfer tanulás pedig megtanítja, hogy melyik kombináció mit jelent – például egy érett banánt.

Számos eszköz áll rendelkezésre, amelyek segítenek ebben, beleértve a felhőalapú szolgáltatásokat, amelyek segítenek a modell betanításában, majd webes API-kon keresztül történő használatában.

> 💁 A modellek betanítása rengeteg számítógépes erőforrást igényel, általában grafikus feldolgozó egységeket (GPU-kat). Ugyanaz a speciális hardver, amely az Xbox játékaidat lenyűgözővé teszi, a gépi tanulási modellek betanítására is használható. A felhő használatával bérelhetsz időt nagy teljesítményű számítógépeken, amelyek GPU-kat használnak, így csak annyi számítási kapacitást veszel igénybe, amennyire szükséged van.

## Custom Vision

A Custom Vision egy felhőalapú eszköz képosztályozók betanítására. Lehetővé teszi, hogy egy osztályozót kis számú képpel betaníts. A képeket egy webes portálon, webes API-n vagy SDK-n keresztül töltheted fel, és minden képhez egy *címkét* adhatsz, amely az adott kép osztályozását jelöli. Ezután betaníthatod a modellt, és tesztelheted, hogy mennyire jól teljesít. Ha elégedett vagy a modellel, közzéteheted annak verzióit, amelyeket webes API-n vagy SDK-n keresztül érhetsz el.

![Az Azure Custom Vision logója](../../../../../translated_images/hu/custom-vision-logo.d3d4e7c8a87ec9da.webp)

> 💁 Egy Custom Vision modellt akár 5 kép osztályonkénti használatával is betaníthatsz, de a több jobb. Legalább 30 képpel jobb eredményeket érhetsz el.

A Custom Vision a Microsoft kognitív szolgáltatásainak része. Ezek olyan AI eszközök, amelyek vagy betanítás nélkül, vagy kis mennyiségű betanítással használhatók. Ide tartozik a beszédfelismerés és fordítás, a nyelvértés és a képelemzés. Ezek az Azure-ban ingyenes szinten is elérhetők.

> 💁 Az ingyenes szint bőven elegendő egy modell létrehozásához, betanításához, majd fejlesztési munkákhoz való használatához. Az ingyenes szint korlátairól a [Custom Vision korlátok és kvóták oldalán olvashatsz a Microsoft dokumentációjában](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn).

### Feladat – kognitív szolgáltatási erőforrás létrehozása

A Custom Vision használatához először két kognitív szolgáltatási erőforrást kell létrehoznod az Azure-ban az Azure CLI segítségével: egyet a Custom Vision betanításhoz, egyet pedig az előrejelzéshez.

1. Hozz létre egy erőforráscsoportot ehhez a projekthez `fruit-quality-detector` néven.

1. Használd az alábbi parancsot egy ingyenes Custom Vision betanítási erőforrás létrehozásához:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Cseréld ki a `<location>` helyet arra a helyre, amelyet az erőforráscsoport létrehozásakor használtál.

    Ez létrehoz egy Custom Vision betanítási erőforrást az erőforráscsoportodban. Az erőforrás neve `fruit-quality-detector-training` lesz, és az `F0` SKU-t használja, amely az ingyenes szint. A `--yes` opció azt jelenti, hogy elfogadod a kognitív szolgáltatások feltételeit.

> 💁 Használd az `S0` SKU-t, ha már van egy ingyenes fiókod, amely bármelyik kognitív szolgáltatást használja.

1. Használd az alábbi parancsot egy ingyenes Custom Vision előrejelzési erőforrás létrehozásához:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Cseréld ki a `<location>` helyet arra a helyre, amelyet az erőforráscsoport létrehozásakor használtál.

    Ez létrehoz egy Custom Vision előrejelzési erőforrást az erőforráscsoportodban. Az erőforrás neve `fruit-quality-detector-prediction` lesz, és az `F0` SKU-t használja, amely az ingyenes szint. A `--yes` opció azt jelenti, hogy elfogadod a kognitív szolgáltatások feltételeit.

### Feladat – képosztályozó projekt létrehozása

1. Nyisd meg a Custom Vision portált a [CustomVision.ai](https://customvision.ai) oldalon, és jelentkezz be az Azure-fiókodhoz tartozó Microsoft-fiókkal.

1. Kövesd a [Microsoft dokumentációjában található osztályozó gyorsindítás új projekt létrehozására vonatkozó szakaszát](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project), hogy létrehozz egy új Custom Vision projektet. A felhasználói felület változhat, ezért ezek a dokumentumok mindig a legfrissebb referenciát jelentik.

    Nevezd el a projektedet `fruit-quality-detector`-nek.

    A projekt létrehozásakor győződj meg róla, hogy az előzőleg létrehozott `fruit-quality-detector-training` erőforrást használod. Használj *
💁 Ezek a klasszifikátorok bármilyen képet képesek osztályozni, így ha nincs kéznél különböző minőségű gyümölcs, használhatsz két különböző típusú gyümölcsöt, vagy akár macskákat és kutyákat!
Ideális esetben minden képen csak a gyümölcs legyen látható, vagy egységes háttérrel, vagy különböző hátterekkel. Ügyelj arra, hogy a háttérben ne legyen semmi, ami a gyümölcs érett vagy éretlen állapotához kapcsolódik.

> 💁 Fontos, hogy ne legyenek specifikus hátterek vagy olyan tárgyak, amelyek nem kapcsolódnak az adott címkéhez, különben az osztályozó a háttér alapján dönthet. Volt egy bőrrákos osztályozó, amelyet normál és rákos anyajegyek képeivel tanítottak. A rákos anyajegyek mellett mindig volt egy vonalzó, amely a méretet mérte. Kiderült, hogy az osztályozó szinte 100%-os pontossággal azonosította a vonalzót a képeken, nem pedig a rákos anyajegyeket.

Az osztályozók nagyon alacsony felbontáson futnak. Például a Custom Vision akár 10240x10240 méretű képeket is képes feldolgozni, de a modell 227x227 méretű képeken tanul és fut. A nagyobb képeket erre a méretre zsugorítja, ezért ügyelj arra, hogy az osztályozni kívánt tárgy a kép nagy részét kitöltse, különben túl kicsi lehet az osztályozó által használt kisebb képen.

1. Gyűjts képeket az osztályozódhoz. Legalább 5 képre lesz szükséged minden címkéhez az osztályozó betanításához, de minél több, annál jobb. Ezen kívül néhány további képre lesz szükséged az osztályozó teszteléséhez. Ezeknek a képeknek ugyanarról a dologról kell készülnie, de különböző képeknek kell lenniük. Például:

    * Használj 2 érett banánt, és készíts róluk néhány képet különböző szögekből, legalább 7 képet (5 a tanításhoz, 2 a teszteléshez), de ideális esetben többet.

        ![Képek 2 különböző banánról](../../../../../translated_images/hu/banana-training-images.530eb203346d73bc.webp)

    * Ismételd meg ugyanezt a folyamatot 2 éretlen banánnal.

    Legalább 10 tanítóképednek kell lennie, legalább 5 érett és 5 éretlen, valamint 4 tesztképednek, 2 érett és 2 éretlen. A képeknek png vagy jpeg formátumúaknak kell lenniük, és 6 MB-nál kisebbeknek. Ha például iPhone-nal készíted őket, akkor lehet, hogy nagy felbontású HEIC képek lesznek, amelyeket át kell alakítani és esetleg le kell kicsinyíteni. Minél több kép, annál jobb, és hasonló számú érett és éretlen képed legyen.

    Ha nincs mind érett, mind éretlen gyümölcsöd, használhatsz különböző gyümölcsöket, vagy bármilyen két tárgyat, ami elérhető. Példaképeket is találhatsz az [images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images) mappában érett és éretlen banánokról, amelyeket használhatsz.

1. Kövesd a [képek feltöltése és címkézése szakaszt a Microsoft dokumentációjában az osztályozó gyorsindítójában](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images), hogy feltöltsd a tanítóképeidet. Címkézd az érett gyümölcsöt `ripe`-ként, az éretlent pedig `unripe`-ként.

    ![A feltöltési párbeszédablakok, amelyek érett és éretlen banánképek feltöltését mutatják](../../../../../translated_images/hu/image-upload-bananas.0751639f3815e0ec.webp)

1. Kövesd a [osztályozó betanítása szakaszt a Microsoft dokumentációjában az osztályozó gyorsindítójában](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier), hogy betanítsd az osztályozót a feltöltött képekkel.

    A betanítási típus kiválasztásakor válaszd a **Gyors betanítás** opciót.

Az osztályozó ezután elkezdi a tanulást. A betanítás néhány percet vesz igénybe.

> 🍌 Ha úgy döntesz, hogy megeszed a gyümölcsöt, amíg az osztályozó tanul, győződj meg róla, hogy van elég képed a teszteléshez!

## Teszteld az osztályozódat

Miután az osztályozó betanult, tesztelheted egy új képpel, hogy osztályozza.

### Feladat - teszteld az osztályozódat

1. Kövesd a [modell tesztelése szakaszt a Microsoft dokumentációjában](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model), hogy teszteld az osztályozódat. Használd azokat a tesztképeket, amelyeket korábban készítettél, ne azokat, amelyeket a tanításhoz használtál.

    ![Egy éretlen banán, amelyet 98,9%-os valószínűséggel éretlennek, és 1,1%-os valószínűséggel érettnek osztályozott](../../../../../translated_images/hu/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64.webp)

1. Próbáld ki az összes tesztképet, amelyhez hozzáférsz, és figyeld meg a valószínűségeket.

## Tanítsd újra az osztályozódat

Amikor teszteled az osztályozódat, előfordulhat, hogy nem a várt eredményeket kapod. Az osztályozók gépi tanulást használnak, hogy előrejelzéseket készítsenek arról, mi van egy képen, a kép bizonyos jellemzői alapján, amelyek valószínűleg megfelelnek egy adott címkének. Nem érti, mi van a képen - nem tudja, mi az a banán, és nem érti, mi teszi a banánt banánná, nem pedig hajóvá. Az osztályozódat javíthatod, ha újratanítod olyan képekkel, amelyeket rosszul osztályozott.

Minden alkalommal, amikor előrejelzést készítesz a gyors teszt opcióval, a kép és az eredmények elmentésre kerülnek. Ezeket a képeket felhasználhatod a modell újratanítására.

### Feladat - tanítsd újra az osztályozódat

1. Kövesd a [prediktált képek használata a tanításhoz szakaszt a Microsoft dokumentációjában](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training), hogy újratanítsd a modelledet, a helyes címkét használva minden képhez.

1. Miután a modelledet újratanítottad, teszteld új képeken.

---

## 🚀 Kihívás

Mit gondolsz, mi történne, ha egy eper képét használnád egy banánokra betanított modellel, vagy egy felfújható banán képét, vagy egy banánjelmezbe öltözött ember képét, vagy akár egy sárga rajzfilmfigurát, például valakit a Simpson családból?

Próbáld ki, és nézd meg, mik az előrejelzések. Képeket találhatsz a próbához a [Bing képkereső](https://www.bing.com/images/trending) segítségével.

## Előadás utáni kvíz

[Előadás utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## Áttekintés és önálló tanulás

* Amikor betanítottad az osztályozódat, láthattál értékeket a *Pontosság*, *Visszahívás* és *AP* mutatókra, amelyek értékelik a létrehozott modellt. Olvass utána, mik ezek az értékek a [osztályozó értékelése szakaszban az osztályozó gyorsindítójában a Microsoft dokumentációjában](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)
* Olvass utána, hogyan javíthatod az osztályozódat a [Custom Vision modell javítása szakaszban a Microsoft dokumentációjában](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)

## Feladat

[Tanítsd az osztályozódat több gyümölcsre és zöldségre](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.