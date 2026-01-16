<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-27T20:53:18+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "hu"
}
-->
# Ellenőrizd a gyümölcs minőségét egy IoT eszközzel

![Egy vázlatos áttekintés erről a leckéről](../../../../../translated_images/hu/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> Vázlat: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

## Előadás előtti kvíz

[Előadás előtti kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Bevezetés

Az előző leckében megismerkedtél a képosztályozókkal, és azzal, hogyan lehet őket betanítani jó és rossz gyümölcsök felismerésére. Ahhoz, hogy ezt a képosztályozót egy IoT alkalmazásban használd, képesnek kell lenned képet rögzíteni valamilyen kamerával, majd ezt a képet a felhőbe küldeni osztályozás céljából.

Ebben a leckében megismerkedsz a kamerás szenzorokkal, és azzal, hogyan használhatod őket egy IoT eszközzel képek rögzítésére. Megtanulod azt is, hogyan hívhatod meg a képosztályozót az IoT eszközödről.

Ebben a leckében a következőket tárgyaljuk:

* [Kamerás szenzorok](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Kép rögzítése IoT eszközzel](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Képosztályozó publikálása](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Képek osztályozása IoT eszközről](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [A modell fejlesztése](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Kamerás szenzorok

A kamerás szenzorok, ahogy a nevük is sugallja, olyan kamerák, amelyeket csatlakoztathatsz az IoT eszközödhöz. Ezek képesek állóképeket készíteni vagy folyamatos videót rögzíteni. Néhányuk nyers képadatokat ad vissza, míg mások tömörítik az adatokat egy képformátumba, például JPEG vagy PNG fájlba. Az IoT eszközökkel kompatibilis kamerák általában kisebbek és alacsonyabb felbontásúak, mint amit megszokhattál, de léteznek olyan nagy felbontású kamerák is, amelyek vetekednek a csúcskategóriás telefonokkal. Különféle cserélhető lencséket, többkamerás rendszereket, infravörös hőkamerákat vagy UV kamerákat is beszerezhetsz.

![A fény egy jelenetből áthalad egy lencsén, és a CMOS szenzorra fókuszálódik](../../../../../translated_images/hu/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

A legtöbb kamerás szenzor képszenzorokat használ, ahol minden pixel egy fotodióda. Egy lencse fókuszálja a képet a képszenzorra, és több ezer vagy millió fotodióda érzékeli a rájuk eső fényt, majd ezt pixeladatként rögzíti.

> 💁 A lencsék megfordítják a képeket, a kamerás szenzor pedig visszafordítja azokat. Ez ugyanígy működik a szemedben is – amit látsz, az fejjel lefelé érzékelődik a szemed hátsó részén, és az agyad korrigálja.

> 🎓 A képszenzort Aktív Pixel Szenzornak (APS) nevezik, és a legnépszerűbb APS típus a kiegészítő fém-oxid félvezető szenzor, vagy CMOS. Lehet, hogy hallottad már a CMOS szenzor kifejezést kamerás szenzorokkal kapcsolatban.

A kamerás szenzorok digitális szenzorok, amelyek digitális adatként küldik el a képadatokat, általában egy kommunikációt biztosító könyvtár segítségével. A kamerák olyan protokollokat használnak, mint az SPI, hogy nagy mennyiségű adatot tudjanak továbbítani – a képek lényegesen nagyobbak, mint például egy hőmérséklet-érzékelő által küldött egyetlen szám.

✅ Milyen korlátai vannak a képméretnek IoT eszközök esetében? Gondolj különösen a mikrokontroller hardverek korlátaira.

## Kép rögzítése IoT eszközzel

Az IoT eszközöddel képes vagy képet rögzíteni, amelyet osztályozni lehet.

### Feladat – kép rögzítése IoT eszközzel

Kövesd a megfelelő útmutatót, hogy képet rögzíts az IoT eszközöddel:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Egylapkás számítógép - Raspberry Pi](pi-camera.md)
* [Egylapkás számítógép - Virtuális eszköz](virtual-device-camera.md)

## Képosztályozó publikálása

Az előző leckében betanítottad a képosztályozódat. Mielőtt használhatnád az IoT eszközödről, publikálnod kell a modellt.

### Modell iterációk

Amikor az előző leckében a modelledet tanítottad, észrevehetted, hogy a **Teljesítmény** fülön az oldalsávon iterációk jelennek meg. Amikor először tanítottad a modellt, az *1. iteráció* volt látható. Amikor a predikciós képekkel javítottad a modellt, a *2. iteráció* jelent meg.

Minden alkalommal, amikor tanítod a modellt, egy új iteráció jön létre. Ez egy módja annak, hogy nyomon kövesd a modelled különböző verzióit, amelyeket különböző adathalmazokon tanítottál. Amikor **Gyors tesztet** végzel, egy legördülő menüben kiválaszthatod az iterációt, így összehasonlíthatod az eredményeket több iteráció között.

Amikor elégedett vagy egy iterációval, publikálhatod, hogy külső alkalmazások is használhassák. Így lehet egy publikált verziód, amelyet az eszközeid használnak, miközben egy új verzión dolgozol több iteráción keresztül, majd azt publikálod, amikor elégedett vagy vele.

### Feladat – iteráció publikálása

Az iterációkat a Custom Vision portálon lehet publikálni.

1. Nyisd meg a Custom Vision portált a [CustomVision.ai](https://customvision.ai) oldalon, és jelentkezz be, ha még nem tetted meg. Ezután nyisd meg a `fruit-quality-detector` projektedet.

1. Válaszd ki a **Teljesítmény** fület a felső menüből.

1. Az oldalsávon válaszd ki a legújabb iterációt az *Iterációk* listából.

1. Kattints az iteráció **Publikálás** gombjára.

    ![A publikálás gomb](../../../../../translated_images/hu/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. A *Modell publikálása* párbeszédablakban állítsd be a *Predikciós erőforrást* a `fruit-quality-detector-prediction` erőforrásra, amelyet az előző leckében hoztál létre. Hagyd meg a nevet `Iteration2`-ként, majd kattints a **Publikálás** gombra.

1. A publikálás után kattints a **Predikciós URL** gombra. Ez megjeleníti a predikciós API részleteit, amelyeket az IoT eszközödről kell majd meghívnod. Az alsó rész az *Ha van egy képfájlod* címkével van ellátva, és ezek az adatok szükségesek. Másold ki a megjelenített URL-t, amely valami ilyesmi lesz:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Ahol `<location>` az a hely, amelyet a Custom Vision erőforrás létrehozásakor használtál, és `<id>` egy hosszú, betűkből és számokból álló azonosító.

    Másold ki a *Predikciós kulcs* értékét is. Ez egy biztonsági kulcs, amelyet meg kell adnod, amikor meghívod a modellt. Csak azok az alkalmazások használhatják a modellt, amelyek megadják ezt a kulcsot, minden más alkalmazás elutasításra kerül.

    ![A predikciós API párbeszédablak, amely az URL-t és a kulcsot mutatja](../../../../../translated_images/hu/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Amikor egy új iterációt publikálnak, annak más neve lesz. Hogyan gondolod, hogy lehetne megváltoztatni az iterációt, amelyet egy IoT eszköz használ?

## Képek osztályozása IoT eszközről

Most már használhatod ezeket a kapcsolati adatokat, hogy meghívd a képosztályozót az IoT eszközödről.

### Feladat – képek osztályozása IoT eszközről

Kövesd a megfelelő útmutatót, hogy képeket osztályozz az IoT eszközödről:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Egylapkás számítógép - Raspberry Pi/Virtuális IoT eszköz](single-board-computer-classify-image.md)

## A modell fejlesztése

Előfordulhat, hogy az IoT eszközhöz csatlakoztatott kamerával készített képek eredményei nem felelnek meg az elvárásaidnak. A predikciók nem mindig olyan pontosak, mint a számítógépről feltöltött képek esetében. Ennek oka, hogy a modellt más adatokkal tanították, mint amilyeneket a predikciókhoz használnak.

Ahhoz, hogy a képosztályozó a legjobb eredményeket nyújtsa, olyan képekkel kell tanítani a modellt, amelyek a lehető legjobban hasonlítanak a predikciókhoz használt képekre. Ha például a telefonod kamerájával készítettél képeket a tanításhoz, a képminőség, az élesség és a színek eltérhetnek az IoT eszközhöz csatlakoztatott kamera által készített képektől.

![2 banán képe, az egyik alacsony felbontású és rossz megvilágítású IoT eszközről, a másik magas felbontású és jó megvilágítású telefonról](../../../../../translated_images/hu/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

A fenti képen a bal oldali banánképet egy Raspberry Pi kamerával készítették, a jobb oldalit pedig ugyanarról a banánról, ugyanazon a helyen egy iPhone-nal. Jól látható a minőségbeli különbség – az iPhone képe élesebb, élénkebb színekkel és nagyobb kontraszttal.

✅ Mi más okozhatja, hogy az IoT eszköz által rögzített képek predikciói helytelenek legyenek? Gondolj az IoT eszközök használati környezetére, milyen tényezők befolyásolhatják a rögzített képet?

A modell fejlesztéséhez újra kell tanítanod azt az IoT eszköz által rögzített képekkel.

### Feladat – a modell fejlesztése

1. Osztályozz több képet érett és éretlen gyümölcsökről az IoT eszközöddel.

1. A Custom Vision portálon tanítsd újra a modellt a *Predikciók* fülön található képekkel.

    > ⚠️ Ha szükséges, hivatkozhatsz [az 1. leckében található utasításokra a képosztályozó újratanításához](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Ha a képeid nagyon eltérnek az eredetileg használt képektől, törölheted az összes eredeti képet a *Tanító képek* fülön, a képek kijelölésével és a **Törlés** gomb megnyomásával. Egy kép kijelöléséhez vidd fölé az egeret, és megjelenik egy pipa, amelyre kattintva kijelölheted vagy törölheted a kijelölést.

1. Taníts egy új iterációt a modellből, és publikáld a fent leírt lépések szerint.

1. Frissítsd az URL-t a kódodban, és futtasd újra az alkalmazást.

1. Ismételd meg ezeket a lépéseket, amíg elégedett nem leszel a predikciók eredményeivel.

---

## 🚀 Kihívás

Mennyire befolyásolja a predikciót a kép felbontása vagy a megvilágítás?

Próbáld megváltoztatni a képek felbontását az eszközöd kódjában, és nézd meg, hogy ez hatással van-e a képek minőségére. Próbálj meg változtatni a megvilágításon is.

Ha egy gyártási eszközt hoznál létre, amelyet farmokon vagy gyárakban árulnál, hogyan biztosítanád, hogy mindig következetes eredményeket adjon?

## Előadás utáni kvíz

[Előadás utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Áttekintés és önálló tanulás

A Custom Vision portál segítségével tanítottad a modelledet. Ez feltételezi, hogy rendelkezésre állnak képek – a valóságban azonban előfordulhat, hogy nem tudsz olyan tanító adatokat szerezni, amelyek megegyeznek az eszközöd kamerája által rögzített képekkel. Ezt megkerülheted azzal, hogy közvetlenül az eszközödről tanítasz a tanító API segítségével, így az IoT eszköz által rögzített képekkel taníthatod a modellt.

* Olvass utána a tanító API-nak a [Custom Vision SDK gyorsindítójában](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python).

## Feladat

[Reagálj az osztályozási eredményekre](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.