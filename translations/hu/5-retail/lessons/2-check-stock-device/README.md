<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-27T22:41:52+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "hu"
}
-->
# Készletellenőrzés egy IoT eszközzel

![Egy vázlatos ábra a leckéről](../../../../../translated_images/hu/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.jpg)

> Vázlat: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

## Előadás előtti kvíz

[Előadás előtti kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Bevezetés

Az előző leckében megismerkedtél az objektumfelismerés különböző kiskereskedelmi felhasználási módjaival. Azt is megtanultad, hogyan képezz ki egy objektumfelismerőt a készlet azonosítására. Ebben a leckében megtanulod, hogyan használd az objektumfelismerőt az IoT eszközödről a készlet számlálására.

Ebben a leckében a következőket tárgyaljuk:

* [Készletszámlálás](../../../../../5-retail/lessons/2-check-stock-device)
* [Az objektumfelismerő hívása az IoT eszközödről](../../../../../5-retail/lessons/2-check-stock-device)
* [Határoló dobozok](../../../../../5-retail/lessons/2-check-stock-device)
* [A modell újratanítása](../../../../../5-retail/lessons/2-check-stock-device)
* [Készlet számlálása](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Ez a projekt utolsó leckéje, így a lecke és a feladat befejezése után ne felejtsd el törölni a felhőszolgáltatásokat. A feladat elvégzéséhez szükséged lesz ezekre a szolgáltatásokra, ezért először fejezd be a feladatot.
>
> Ha szükséges, nézd meg [a projekt törlésének útmutatóját](../../../clean-up.md) az utasításokért.

## Készletszámlálás

Az objektumfelismerők használhatók készletellenőrzésre, akár a készlet számlálására, akár annak biztosítására, hogy a készlet a megfelelő helyen legyen. Kamerával felszerelt IoT eszközöket lehet telepíteni az üzlet különböző pontjaira a készlet figyelésére, kezdve azokon a forró pontokon, ahol fontos az áruk újratöltése, például olyan területeken, ahol kis mennyiségű, nagy értékű árukat tárolnak.

Például, ha egy kamera egy olyan polcra néz, amelyen 8 paradicsompüré konzerv fér el, és az objektumfelismerő csak 7 konzervet észlel, akkor egy hiányzik, és újra kell tölteni.

![7 paradicsompüré konzerv egy polcon, 4 a felső sorban, 3 alatta](../../../../../translated_images/hu/stock-7-cans-tomato-paste.f86059cc573d7bec.webp)

A fenti képen az objektumfelismerő 7 paradicsompüré konzervet észlelt egy polcon, amelyen 8 konzerv fér el. Az IoT eszköz nemcsak értesítést küldhet az újratöltés szükségességéről, hanem még a hiányzó elem helyét is megadhatja, ami fontos adat, ha robotokat használsz a polcok újratöltésére.

> 💁 Az üzlettől és az áru népszerűségétől függően valószínűleg nem történik újratöltés, ha csak 1 konzerv hiányzik. Algoritmust kell készítened, amely meghatározza, mikor kell újratölteni az áruk, vásárlók és egyéb kritériumok alapján.

✅ Milyen más helyzetekben lehetne kombinálni az objektumfelismerést és a robotokat?

Néha rossz áruk kerülhetnek a polcokra. Ez lehet emberi hiba az újratöltés során, vagy vásárlók, akik meggondolják magukat, és az árut az első elérhető helyre teszik vissza. Ha ez nem romlandó áru, például konzerv, akkor ez bosszantó. Ha viszont romlandó áru, például fagyasztott vagy hűtött termék, akkor előfordulhat, hogy a terméket már nem lehet eladni, mivel lehetetlen megállapítani, mennyi ideig volt a fagyasztón kívül.

Az objektumfelismerés használható váratlan áruk észlelésére, és értesítheti az embert vagy a robotot, hogy az árut azonnal visszahelyezze.

![Egy eltévedt bébikukorica konzerv a paradicsompüré polcon](../../../../../translated_images/hu/stock-rogue-corn.be1f3ada8c457854.webp)

A fenti képen egy bébikukorica konzerv került a paradicsompüré polcra. Az objektumfelismerő ezt észlelte, lehetővé téve az IoT eszköz számára, hogy értesítse az embert vagy a robotot, hogy helyezze vissza a konzervet a megfelelő helyére.

## Az objektumfelismerő hívása az IoT eszközödről

Az előző leckében kiképzett objektumfelismerő hívható az IoT eszközödről.

### Feladat - az objektumfelismerő iterációjának közzététele

Az iterációkat a Custom Vision portálról lehet közzétenni.

1. Nyisd meg a Custom Vision portált a [CustomVision.ai](https://customvision.ai) oldalon, és jelentkezz be, ha még nincs nyitva. Ezután nyisd meg a `stock-detector` projektedet.

1. Válaszd ki a **Performance** fület a felső menüből.

1. Válaszd ki a legújabb iterációt az oldalsó *Iterations* listából.

1. Kattints az iteráció **Publish** gombjára.

    ![A közzététel gomb](../../../../../translated_images/hu/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.png)

1. A *Publish Model* párbeszédablakban állítsd be a *Prediction resource*-t az előző leckében létrehozott `stock-detector-prediction` erőforrásra. Hagyd meg a nevet `Iteration2`-ként, majd kattints a **Publish** gombra.

1. A közzététel után kattints a **Prediction URL** gombra. Ez megjeleníti az előrejelzési API részleteit, amelyeket az IoT eszközödről kell hívnod. Az alsó rész az *If you have an image file* címkével van ellátva, és ezek az adatok szükségesek. Másold ki a megjelenített URL-t, amely valami ilyesmi lesz:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Ahol `<location>` az a hely, amelyet a Custom Vision erőforrás létrehozásakor használtál, és `<id>` egy hosszú azonosító, amely betűkből és számokból áll.

    Másold ki a *Prediction-Key* értéket is. Ez egy biztonsági kulcs, amelyet meg kell adnod a modell hívásakor. Csak azok az alkalmazások használhatják a modellt, amelyek megadják ezt a kulcsot, minden más alkalmazást elutasítanak.

    ![Az előrejelzési API párbeszédablak az URL-lel és a kulccsal](../../../../../translated_images/hu/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Amikor egy új iterációt közzétesznek, annak más neve lesz. Hogyan gondolod, hogy megváltoztatnád az IoT eszköz által használt iterációt?

### Feladat - az objektumfelismerő hívása az IoT eszközödről

Kövesd az alábbi megfelelő útmutatót az objektumfelismerő használatához az IoT eszközödről:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Egylapkás számítógép - Raspberry Pi/Virtual device](single-board-computer-object-detector.md)

## Határoló dobozok

Amikor használod az objektumfelismerőt, nemcsak az észlelt objektumokat kapod vissza a címkéikkel és valószínűségeikkel, hanem az objektumok határoló dobozait is. Ezek határozzák meg, hogy az objektumfelismerő hol észlelte az adott valószínűséggel az objektumot.

> 💁 A határoló doboz egy olyan doboz, amely meghatározza az objektum által elfoglalt területet, az objektum határát.

A **Predictions** fülön az előrejelzés eredményei tartalmazzák a határoló dobozokat az előrejelzésre küldött képen.

![4 paradicsompüré konzerv egy polcon, az előrejelzések 35.8%, 33.5%, 25.7% és 16.6% valószínűséggel](../../../../../translated_images/hu/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

A fenti képen 4 paradicsompüré konzervet észleltek. Az eredményekben egy piros négyzet van ráhelyezve minden észlelt objektumra, jelezve a kép határoló dobozát.

✅ Nyisd meg az előrejelzéseket a Custom Vision-ben, és nézd meg a határoló dobozokat.

A határoló dobozokat 4 érték határozza meg: top, left, height és width. Ezek az értékek 0-1 skálán vannak, az értékek a kép méretének százalékos arányát képviselik. Az origó (a 0,0 pozíció) a kép bal felső sarka, így a top érték a távolság a tetejétől, az alsó érték pedig a top plusz a height.

![Egy határoló doboz egy paradicsompüré konzerv körül](../../../../../translated_images/hu/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.png)

A fenti kép 600 pixel széles és 800 pixel magas. A határoló doboz 320 pixellel lejjebb kezdődik, ami 0.4-es top koordinátát ad (800 x 0.4 = 320). A bal oldaltól a határoló doboz 240 pixellel kezdődik, ami 0.4-es left koordinátát ad (600 x 0.4 = 240). A határoló doboz magassága 240 pixel, ami 0.3-as height értéket ad (800 x 0.3 = 240). A határoló doboz szélessége 120 pixel, ami 0.2-es width értéket ad (600 x 0.2 = 120).

| Koordináta | Érték |
| ---------- | ----: |
| Top        | 0.4   |
| Left       | 0.4   |
| Height     | 0.3   |
| Width      | 0.2   |

A 0-1 közötti százalékos értékek használata azt jelenti, hogy függetlenül attól, hogy a kép milyen méretre van skálázva, a határoló doboz 0.4-gyel kezdődik mindkét irányban, és a magasság 0.3, a szélesség pedig 0.2.

A határoló dobozokat a valószínűségekkel kombinálva értékelheted az észlelés pontosságát. Például egy objektumfelismerő több, egymást átfedő objektumot is észlelhet, például egy konzervet egy másik belsejében. A kódod megvizsgálhatja a határoló dobozokat, megértheti, hogy ez lehetetlen, és figyelmen kívül hagyhatja azokat az objektumokat, amelyek jelentős átfedésben vannak más objektumokkal.

![Két átfedő határoló doboz egy paradicsompüré konzerv körül](../../../../../translated_images/hu/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.png)

A fenti példában az egyik határoló doboz egy paradicsompüré konzervet jelez 78.3%-os valószínűséggel. Egy másik határoló doboz valamivel kisebb, és az első határoló dobozon belül van, 64.3%-os valószínűséggel. A kódod ellenőrizheti a határoló dobozokat, láthatja, hogy teljesen átfedik egymást, és figyelmen kívül hagyhatja az alacsonyabb valószínűséget, mivel lehetetlen, hogy egy konzerv egy másik belsejében legyen.

✅ Tudsz olyan helyzetet elképzelni, amikor érvényes, hogy egy objektum egy másik belsejében legyen?

## A modell újratanítása

Az image classifierhez hasonlóan az IoT eszköz által rögzített adatokkal újra lehet tanítani a modellt. Ezeknek a valós adatoknak a használata biztosítja, hogy a modell jól működjön az IoT eszközről történő használat során.

Az image classifierrel ellentétben nem elég csak címkézni egy képet. Ehelyett minden, a modell által észlelt határoló dobozt át kell vizsgálni. Ha a doboz rossz dolgot fog körül, törölni kell, ha rossz helyen van, akkor módosítani kell.

### Feladat - a modell újratanítása

1. Győződj meg róla, hogy az IoT eszközöddel rögzítettél egy sor képet.

1. A **Predictions** fülön válassz ki egy képet. Piros dobozokat fogsz látni, amelyek az észlelt objektumok határoló dobozait jelzik.

1. Dolgozd át az összes határoló dobozt. Először válaszd ki, és egy felugró ablakban látni fogod a címkét. Használd a határoló doboz sarkain lévő fogantyúkat a méret módosításához, ha szükséges. Ha a címke rossz, távolítsd el az **X** gombbal, és add hozzá a helyes címkét. Ha a határoló doboz nem tartalmaz objektumot, töröld a kuka gombbal.

1. Zárd be a szerkesztőt, amikor kész vagy, és a kép átkerül a **Training Images** fülre. Ismételd meg a folyamatot az összes előrejelzésnél.

1. Használd a **Train** gombot a modell újratanításához. Miután a modell kiképződött, tedd közzé az iterációt, és frissítsd az IoT eszközödet az új iteráció URL-jének használatára.

1. Telepítsd újra a kódot, és teszteld az IoT eszközödet.

## Készlet számlálása

Az észlelt objektumok száma és a határoló dobozok kombinációjával megszámolhatod a polcon lévő készletet.

### Feladat - készlet számlálása

Kövesd az alábbi megfelelő útmutatót a készlet számlálásához az IoT eszközödről származó objektumfelismerő eredményei alapján:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Egylapkás számítógép - Raspberry Pi/Virtual device](single-board-computer-count-stock.md)

---

## 🚀 Kihívás

Tudsz helytelen készletet észlelni? Tanítsd a modelledet több objektumra, majd frissítsd az alkalmazásodat, hogy értesítsen, ha rossz készletet észlel.

Esetleg menj tovább, és észleld az egymás mellett lévő készleteket ugyanazon a polcon, és nézd meg, ha valami rossz helyre került, határoló dobozok korlátainak meghatározásával.

## Előadás utáni kvíz

[Előadás utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Áttekintés és önálló tanulás

* Tudj meg többet arról, hogyan lehet egy végponttól végpontig terjedő készletészlelési rendszert felépíteni a [Készlethiány észlelése az élvonalban mintázat útmutatóból a Microsoft Docs-on](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn).
* Ismerj meg más módszereket a végponttól végpontig terjedő kiskereskedelmi megoldások építésére, amelyek IoT és felhőszolgáltatások kombinációját használják, nézd meg ezt a [Behind the scenes of a retail solution - Hands On! videót a YouTube-on

---

**Felelősségkizárás**:  
Ez a dokumentum az [Co-op Translator](https://github.com/Azure/co-op-translator) AI fordítási szolgáltatás segítségével készült. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget a fordítás használatából eredő félreértésekért vagy téves értelmezésekért.