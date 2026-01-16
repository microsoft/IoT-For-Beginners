<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8df310a42f902139a01417dacb1ffbef",
  "translation_date": "2025-08-27T22:38:57+00:00",
  "source_file": "5-retail/lessons/1-train-stock-detector/README.md",
  "language_code": "hu"
}
-->
# Készíts egy készletérzékelőt

![A lecke vázlatos áttekintése](../../../../../translated_images/hu/lesson-19.cf6973cecadf080c4b526310620dc4d6f5994c80fb0139c6f378cc9ca2d435cd.jpg)

> Vázlatrajz: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

Ez a videó áttekintést nyújt az Azure Custom Vision szolgáltatásról, amelyet ebben a leckében fogunk tárgyalni.

[![Custom Vision 2 - Objektumfelismerés egyszerűen | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Kattints a fenti képre a videó megtekintéséhez

## Előadás előtti kvíz

[Előadás előtti kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Bevezetés

Az előző projektben mesterséges intelligenciát használtál egy képosztályozó modell betanítására, amely meg tudja mondani, hogy egy kép tartalmaz-e valamit, például érett vagy éretlen gyümölcsöt. Egy másik típusú AI modell, amely képekkel használható, az objektumfelismerés. Ezek a modellek nem címkékkel osztályozzák a képet, hanem arra vannak betanítva, hogy felismerjék az objektumokat, és megtalálják őket a képeken. Nemcsak azt érzékelik, hogy az objektum jelen van-e, hanem azt is, hogy hol található a képen. Ez lehetővé teszi az objektumok megszámlálását a képeken.

Ebben a leckében megismerkedsz az objektumfelismeréssel, beleértve annak kiskereskedelemben való alkalmazását. Megtanulod, hogyan lehet objektumérzékelőt betanítani a felhőben.

Ebben a leckében a következő témákat tárgyaljuk:

* [Objektumfelismerés](../../../../../5-retail/lessons/1-train-stock-detector)
* [Objektumfelismerés használata a kiskereskedelemben](../../../../../5-retail/lessons/1-train-stock-detector)
* [Objektumérzékelő betanítása](../../../../../5-retail/lessons/1-train-stock-detector)
* [Objektumérzékelő tesztelése](../../../../../5-retail/lessons/1-train-stock-detector)
* [Objektumérzékelő újratanítása](../../../../../5-retail/lessons/1-train-stock-detector)

## Objektumfelismerés

Az objektumfelismerés mesterséges intelligencia segítségével érzékeli az objektumokat a képeken. Az előző projektben betanított képosztályozóval ellentétben az objektumfelismerés nem az egész kép legjobb címkéjének előrejelzéséről szól, hanem egy vagy több objektum megtalálásáról a képen.

### Objektumfelismerés vs képosztályozás

A képosztályozás az egész kép osztályozásáról szól - milyen valószínűséggel felel meg az egész kép az egyes címkéknek. Az eredmény egy valószínűségi lista minden címkére, amelyet a modell betanításához használtak.

![Képosztályozás kesudióval és paradicsompürével](../../../../../translated_images/hu/image-classifier-cashews-tomato.bc2e16ab8f05cf9ac0f59f73e32efc4227f9a5b601b90b2c60f436694547a965.png)

A fenti példában két képet osztályoznak egy olyan modellel, amelyet kesudiótartók és paradicsompüré konzervdobozok osztályozására tanítottak be. Az első kép egy kesudiótartó, és az osztályozó két eredményt ad:

| Címke          | Valószínűség |
| -------------- | ----------: |
| `kesudió`      | 98.4%       |
| `paradicsompüré` | 1.6%        |

A második kép egy paradicsompüré konzervdoboz, és az eredmények:

| Címke          | Valószínűség |
| -------------- | ----------: |
| `kesudió`      | 0.7%        |
| `paradicsompüré` | 99.3%       |

Ezeket az értékeket egy küszöbértékkel használhatod az előrejelzéshez, hogy mi van a képen. De mi van akkor, ha egy képen több paradicsompüré konzervdoboz vagy mind kesudió, mind paradicsompüré van? Az eredmények valószínűleg nem azt adják, amit szeretnél. Itt jön képbe az objektumfelismerés.

Az objektumfelismerés során a modellt arra tanítják, hogy felismerje az objektumokat. Ahelyett, hogy képeket adnál neki, amelyek az objektumot tartalmazzák, és megmondanád, hogy az egyes képek egyik vagy másik címkéhez tartoznak, kiemeled a kép azon részét, amely az adott objektumot tartalmazza, és azt címkézed meg. Egy képen egyetlen objektumot vagy többet is megcímkézhetsz. Így a modell megtanulja, hogy maga az objektum hogyan néz ki, nem csak azt, hogy az objektumot tartalmazó képek hogyan néznek ki.

Amikor ezután előrejelzéseket készítesz képekkel, nem egy címkékből és százalékokból álló listát kapsz vissza, hanem egy listát a felismerhető objektumokról, azok határoló dobozával és azzal a valószínűséggel, hogy az objektum megfelel a hozzárendelt címkének.

> 🎓 *Határoló dobozok* azok a dobozok, amelyek az objektum körül helyezkednek el.

![Objektumfelismerés kesudióval és paradicsompürével](../../../../../translated_images/hu/object-detector-cashews-tomato.1af7c26686b4db0e709754aeb196f4e73271f54e2085db3bcccb70d4a0d84d97.png)

A fenti képen van egy kesudiótartó és három paradicsompüré konzervdoboz. Az objektumérzékelő felismerte a kesudiót, és visszaadta a határoló dobozt, amely tartalmazza a kesudiót, valamint a százalékos valószínűséget, hogy a határoló doboz tartalmazza az objektumot, ebben az esetben 97.6%. Az objektumérzékelő három paradicsompüré konzervdobozt is érzékelt, és három különálló határoló dobozt biztosít, egyet-egyet az érzékelt dobozokhoz, mindegyikhez százalékos valószínűséggel, hogy a határoló doboz paradicsompüré konzervdobozt tartalmaz.

✅ Gondolj néhány különböző forgatókönyvre, amelyekhez képalapú AI modelleket szeretnél használni. Melyek igényelnének osztályozást, és melyek igényelnének objektumfelismerést?

### Hogyan működik az objektumfelismerés

Az objektumfelismerés összetett gépi tanulási modelleket használ. Ezek a modellek úgy működnek, hogy a képet több cellára osztják, majd ellenőrzik, hogy a határoló doboz középpontja egy olyan kép középpontja-e, amely megfelel a modell betanításához használt képek egyikének. Ezt úgy képzelheted el, mintha egy képosztályozót futtatnál a kép különböző részein, hogy egyezéseket keress.

> 💁 Ez egy drasztikus leegyszerűsítés. Számos technika létezik az objektumfelismerésre, és többet olvashatsz róluk a [Wikipedia objektumfelismerés oldalán](https://wikipedia.org/wiki/Object_detection).

Számos különböző modell létezik, amelyek képesek objektumfelismerésre. Egy különösen híres modell a [YOLO (You Only Look Once)](https://pjreddie.com/darknet/yolo/), amely hihetetlenül gyors, és 20 különböző objektumosztályt képes felismerni, például embereket, kutyákat, palackokat és autókat.

✅ Olvass utána a YOLO modellnek a [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/) oldalon.

Az objektumfelismerő modellek újrataníthatók transzfer tanulás segítségével egyedi objektumok felismerésére.

## Objektumfelismerés használata a kiskereskedelemben

Az objektumfelismerésnek számos felhasználási módja van a kiskereskedelemben. Néhány példa:

* **Készletellenőrzés és számlálás** - felismeri, ha a polcokon alacsony a készlet. Ha a készlet túl alacsony, értesítéseket küldhet a személyzetnek vagy robotoknak a polcok feltöltésére.
* **Maszkérzékelés** - olyan üzletekben, ahol közegészségügyi események során maszkviselési szabályok vannak, az objektumfelismerés felismerheti a maszkot viselő és nem viselő embereket.
* **Automatizált számlázás** - felismeri a polcokról levett tárgyakat az automatizált üzletekben, és megfelelően számlázza az ügyfeleket.
* **Veszélyérzékelés** - felismeri a padlón lévő törött tárgyakat vagy kiömlött folyadékokat, és értesíti a takarító személyzetet.

✅ Kutass egy kicsit: Milyen további felhasználási lehetőségei vannak az objektumfelismerésnek a kiskereskedelemben?

## Objektumérzékelő betanítása

Az objektumérzékelőt a Custom Vision segítségével lehet betanítani, hasonlóan ahhoz, ahogy a képosztályozót betanítottad.

### Feladat - hozz létre egy objektumérzékelőt

1. Hozz létre egy erőforráscsoportot ehhez a projekthez `stock-detector` néven.

1. Hozz létre egy ingyenes Custom Vision tréning erőforrást és egy ingyenes Custom Vision előrejelzési erőforrást a `stock-detector` erőforráscsoportban. Nevezd el őket `stock-detector-training` és `stock-detector-prediction` néven.

    > 💁 Csak egy ingyenes tréning és előrejelzési erőforrásod lehet, ezért győződj meg róla, hogy az előző leckék projektjeit törölted.

    > ⚠️ Ha szükséges, hivatkozhatsz a [tréning és előrejelzési erőforrások létrehozására vonatkozó utasításokra a 4. projekt 1. leckéjéből](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. Indítsd el a Custom Vision portált a [CustomVision.ai](https://customvision.ai) oldalon, és jelentkezz be az Azure-fiókodhoz használt Microsoft-fiókkal.

1. Kövesd a [Hozz létre egy új projektet szakaszt a Microsoft dokumentációjában található Objektumérzékelő gyorsindításban](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project), hogy létrehozz egy új Custom Vision projektet. A felhasználói felület változhat, és ezek a dokumentumok mindig a legfrissebb referenciák.

    Nevezd el a projektedet `stock-detector` néven.

    Amikor létrehozod a projektet, győződj meg róla, hogy a korábban létrehozott `stock-detector-training` erőforrást használod. Használd az *Object Detection* projekt típust, és a *Products on Shelves* domaint.

    ![A Custom Vision projekt beállításai a névvel, leírás nélkül, az erőforrással, a projekt típussal és a domainnel](../../../../../translated_images/hu/custom-vision-create-object-detector-project.32d4fb9aa8e7e7375f8a799bfce517aca970f2cb65e42d4245c5e635c734ab29.png)

    ✅ A polcokon lévő termékek domainje kifejezetten a bolti polcokon lévő készletek érzékelésére van optimalizálva. Olvass többet a különböző domainekről a [Microsoft Docs Select a domain dokumentációjában](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection).

✅ Szánj időt arra, hogy felfedezd az objektumérzékelőd Custom Vision felhasználói felületét.

### Feladat - tanítsd be az objektumérzékelődet

Ahhoz, hogy betanítsd a modelledet, szükséged lesz egy képkészletre, amely tartalmazza az érzékelni kívánt objektumokat.

1. Gyűjts össze képeket, amelyek tartalmazzák az érzékelni kívánt objektumot. Legalább 15 képre lesz szükséged minden érzékelni kívánt objektumról, különböző szögekből és különböző fényviszonyok között, de minél több, annál jobb. Ez az objektumérzékelő a *Products on Shelves* domaint használja, ezért próbáld úgy elrendezni az objektumokat, mintha bolti polcon lennének. Szükséged lesz néhány képre a modell teszteléséhez is. Ha több objektumot érzékelsz, akkor olyan tesztképekre is szükséged lesz, amelyek tartalmazzák az összes objektumot.

    > 💁 A több különböző objektumot tartalmazó képek beleszámítanak a 15 képes minimumba az összes objektum esetében, amely a képen van.

    A képeidnek png vagy jpeg formátumúnak kell lenniük, és 6 MB-nál kisebbeknek. Ha például iPhone-nal készíted őket, akkor lehet, hogy nagy felbontású HEIC képek lesznek, amelyeket konvertálni és esetleg kicsinyíteni kell. Minél több kép, annál jobb, és hasonló számú érett és éretlen képre lesz szükséged.

    A modell termékek polcokon való érzékelésére van tervezve, ezért próbáld meg a tárgyakat polcokon fotózni.

    Találsz néhány példaképet, amelyeket használhatsz a [képek](../../../../../5-retail/lessons/1-train-stock-detector/images) mappában kesudióról és paradicsompüréről.

1. Kövesd a [Képek feltöltése és címkézése szakaszt a Microsoft dokumentációjában található Objektumérzékelő gyorsindításban](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images), hogy feltöltsd a tréningképeidet. Hozz létre releváns címkéket az érzékelni kívánt objektumtípusok alapján.

    ![A feltöltési párbeszédablakok érett és éretlen banán képeinek feltöltésével](../../../../../translated_images/hu/image-upload-object-detector.77c7892c3093cb59b79018edecd678749a75d71a099bc8a2d2f2f76320f88a5b.png)

    Amikor határoló dobozokat rajzolsz az objektumokhoz, tartsd őket szorosan az objektum körül. Időbe telhet az összes kép körvonalazása, de az eszköz érzékeli, hogy szerinte hol vannak a határoló dobozok, ami gyorsabbá teszi a folyamatot.

    ![Paradicsompüré címkézése](../../../../../translated_images/hu/object-detector-tag-tomato-paste.f47c362fb0f0eb582f3bc68cf3855fb43a805106395358d41896a269c210b7b4.png)

    > 💁 Ha több mint 15 képed van minden objektumhoz, akkor 15 után betaníthatod, majd használhatod a **Suggested tags** funkciót. Ez a betanított modellt használja az objektumok érzékelésére a címkézetlen képen. Ezután megerősítheted az érzékelt objektumokat, vagy elutasíthatod és újrarajzolhatod a határoló dobozokat. Ez rengeteg időt takaríthat meg.

1. Kövesd a [Detektor betanítása szakaszt a Microsoft dokumentációjában található Objektumérzékelő gyorsindításban](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector), hogy betanítsd az objektumérzékelőt a címkézett képeiden.

    A tréning típusának kiválasztásakor válaszd a **Quick Training** lehetőséget.

Az objektumérzékelő ezután betanul. A tréning befejezéséhez néhány percre lesz szükség.

## Teszteld az objektumérzé
[Előadás utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Áttekintés és önálló tanulás

* Amikor betanítottad az objektumdetektorodat, láthattál *Precízió*, *Visszahívás* és *mAP* értékeket, amelyek az elkészített modellt értékelik. Olvass utána, hogy ezek az értékek mit jelentenek a [Microsoft dokumentációjában található Objektumdetektor értékelése szakaszban, a Gyorsindítás: Objektumdetektor létrehozása című részben](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector)
* Tudj meg többet az objektumfelismerésről a [Wikipedia Objektumfelismerés oldalán](https://wikipedia.org/wiki/Object_detection)

## Feladat

[Domainok összehasonlítása](assignment.md)

---

**Felelősségkizárás**:  
Ez a dokumentum az [Co-op Translator](https://github.com/Azure/co-op-translator) AI fordítási szolgáltatás segítségével készült. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget a fordítás használatából eredő félreértésekért vagy téves értelmezésekért.