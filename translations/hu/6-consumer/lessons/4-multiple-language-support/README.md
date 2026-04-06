# Többnyelvű támogatás

![A leckéről készült vázlatrajz](../../../../../translated_images/hu/lesson-24.4246968ed058510a.webp)

> Vázlatrajz: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

Ez a videó áttekintést nyújt az Azure beszédfelismerési szolgáltatásairól, beleértve a beszéd szöveggé alakítását és a szöveg beszéddé alakítását, amelyeket korábbi leckékben tárgyaltunk, valamint a beszédfordítást, amely ennek a leckének a témája:

[![Beszédfelismerés néhány Python sorral a Microsoft Build 2020-ról](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Kattints a fenti képre a videó megtekintéséhez

## Előadás előtti kvíz

[Előadás előtti kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Bevezetés

Az elmúlt három leckében megtanultad, hogyan lehet a beszédet szöveggé alakítani, megérteni a nyelvet, és a szöveget beszéddé alakítani, mindezt mesterséges intelligencia segítségével. Az emberi kommunikáció egy másik területe, ahol az MI segíthet, a nyelvfordítás – az egyik nyelvről a másikra történő átalakítás, például angolról franciára.

Ebben a leckében megtanulod, hogyan használhatod az MI-t szöveg fordítására, lehetővé téve, hogy az okos időzítőd több nyelven is kommunikáljon a felhasználókkal.

Ebben a leckében a következő témákat érintjük:

* [Szöveg fordítása](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Fordítási szolgáltatások](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Fordító erőforrás létrehozása](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Több nyelv támogatása alkalmazásokban fordításokkal](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Szöveg fordítása MI szolgáltatással](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Ez a projekt utolsó leckéje, így a lecke és a feladat befejezése után ne felejtsd el törölni a felhőszolgáltatásaidat. A feladat elvégzéséhez szükséged lesz a szolgáltatásokra, ezért először fejezd be azt.
>
> Ha szükséges, nézd meg [a projekt törlésének útmutatóját](../../../clean-up.md) az utasításokért.

## Szöveg fordítása

A szövegfordítás több mint 70 éve a számítástechnika egyik kutatási problémája, és csak most, az MI és a számítógépes teljesítmény fejlődésének köszönhetően közelít ahhoz a ponthoz, ahol szinte olyan jó, mint az emberi fordítók.

> 💁 A gyökerek még régebbre nyúlnak vissza, egészen [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi)-ig, egy 9. századi arab kriptográfusig, aki nyelvfordítási technikákat fejlesztett ki.

### Gépi fordítások

A szövegfordítás egykor a Gépi Fordítás (Machine Translation, MT) néven ismert technológiaként indult, amely különböző nyelvpárok között tudott fordítani. Az MT úgy működik, hogy az egyik nyelv szavait helyettesíti egy másik nyelv szavaival, kiegészítve olyan technikákkal, amelyek kiválasztják a megfelelő fordítási módokat, amikor az egyszerű szó szerinti fordítás nem értelmezhető.

> 🎓 Amikor a fordítók egy nyelvről egy másikra történő fordítást támogatnak, ezeket *nyelvpároknak* nevezzük. Különböző eszközök különböző nyelvpárokat támogatnak, és ezek nem mindig teljesek. Például egy fordító támogathatja az angolról spanyolra történő fordítást, és a spanyolról olaszra történő fordítást, de nem feltétlenül az angolról olaszra történőt.

Például az "Hello world" angol kifejezés franciára fordítása helyettesítéssel történhet – "Bonjour" az "Hello" helyett, és "le monde" a "world" helyett, ami a helyes "Bonjour le monde" fordítást eredményezi.

A helyettesítések nem működnek, ha a különböző nyelvek eltérő módon fejezik ki ugyanazt a dolgot. Például az angol "My name is Jim" mondat franciára fordítva "Je m'appelle Jim" lesz – szó szerint "Magamat hívom Jimnek". A "Je" franciául "én", a "moi" jelentése "magam", de mivel magánhangzóval kezdődő igével kapcsolódik, "m'" lesz belőle, az "appelle" jelentése "hívni", és a "Jim" nem fordítandó, mivel név, nem pedig fordítható szó. A szórend is problémát jelenthet – az "Je m'appelle Jim" egyszerű helyettesítése "I myself call Jim" lenne, ami eltér az angol szórendtől.

> 💁 Egyes szavakat soha nem fordítanak le – a nevem Jim marad, függetlenül attól, hogy milyen nyelven mutatkozom be. Ha olyan nyelvekre fordítunk, amelyek eltérő ábécét használnak, vagy eltérő betűket különböző hangokhoz, akkor a szavakat *átírhatjuk*, azaz olyan betűket vagy karaktereket választunk, amelyek megfelelő hangzást adnak az adott szóhoz.

Az idiómák szintén problémát jelentenek a fordításban. Ezek olyan kifejezések, amelyeknek az értelmezése eltér a szavak közvetlen jelentésétől. Például az angol "I've got ants in my pants" idióma nem szó szerint azt jelenti, hogy hangyák vannak a ruhádban, hanem hogy nyugtalan vagy. Ha ezt németre fordítanád, összezavarnád a hallgatót, mivel a német változat "Ich habe Hummeln im Hintern" – szó szerint "Méhek vannak a fenekemben".

> 💁 Különböző helyi nyelvjárások további bonyodalmakat okoznak. Az "ants in your pants" idióma esetében az amerikai angolban a "pants" külső ruházatot jelent, míg a brit angolban a "pants" alsóneműt.

✅ Ha több nyelven beszélsz, gondolj néhány olyan kifejezésre, amelyek nem fordíthatók le közvetlenül.

A gépi fordítási rendszerek nagy szabályadatbázisokra támaszkodnak, amelyek leírják, hogyan kell bizonyos kifejezéseket és idiómákat fordítani, valamint statisztikai módszerekre, amelyek a lehetséges opciók közül a megfelelő fordításokat választják ki. Ezek a statisztikai módszerek hatalmas, emberek által több nyelvre fordított adatbázisokat használnak a legvalószínűbb fordítás kiválasztására, ezt a technikát *statisztikai gépi fordításnak* nevezik. Számos ilyen rendszer köztes nyelvi reprezentációkat használ, lehetővé téve, hogy az egyik nyelvet a köztes nyelvre, majd a köztes nyelvről egy másik nyelvre fordítsák. Így új nyelvek hozzáadása a köztes nyelvre és onnan történő fordítást igényli, nem pedig az összes többi nyelvre és onnan.

### Neurális fordítások

A neurális fordítások az MI erejét használják a fordításhoz, jellemzően teljes mondatokat fordítanak egyetlen modellel. Ezeket a modelleket hatalmas, emberek által fordított adathalmazokon képezik ki, például weboldalakon, könyveken és az Egyesült Nemzetek dokumentációján.

A neurális fordítási modellek általában kisebbek, mint a gépi fordítási modellek, mivel nincs szükségük hatalmas kifejezés- és idiómadatbázisokra. A modern MI szolgáltatások, amelyek fordítást nyújtanak, gyakran több technikát kevernek, ötvözve a statisztikai gépi fordítást és a neurális fordítást.

Nincs 1:1 fordítás bármely nyelvpár esetében. Különböző fordítási modellek kissé eltérő eredményeket adhatnak attól függően, hogy milyen adatokkal képezték őket. A fordítások nem mindig szimmetrikusak – azaz ha egy mondatot lefordítasz az egyik nyelvről a másikra, majd vissza az első nyelvre, előfordulhat, hogy kissé eltérő mondatot kapsz eredményül.

✅ Próbálj ki különböző online fordítókat, például a [Bing Translate](https://www.bing.com/translator), a [Google Translate](https://translate.google.com) vagy az Apple fordító alkalmazását. Hasonlítsd össze néhány mondat fordított verzióit. Próbáld meg az egyiket lefordítani, majd egy másikban visszafordítani.

## Fordítási szolgáltatások

Számos MI szolgáltatás érhető el, amelyeket alkalmazásaidból használhatsz beszéd és szöveg fordítására.

### Cognitive Services Beszédszolgáltatás

![A beszédszolgáltatás logója](../../../../../translated_images/hu/azure-speech-logo.a1f08c4befb0159f.webp)

Az elmúlt néhány leckében használt beszédszolgáltatás fordítási képességekkel is rendelkezik a beszédfelismeréshez. Amikor beszédet ismersz fel, nemcsak az adott nyelvű szöveget kérheted, hanem más nyelveken is.

> 💁 Ez csak a beszéd SDK-ból érhető el, a REST API nem tartalmaz beépített fordításokat.

### Cognitive Services Fordító szolgáltatás

![A fordító szolgáltatás logója](../../../../../translated_images/hu/azure-translator-logo.c6ed3a4a433edfd2.webp)

A Fordító szolgáltatás egy dedikált fordítási szolgáltatás, amely szöveget tud fordítani egyik nyelvről egy vagy több célnyelvre. A fordításon kívül számos extra funkciót is támogat, például a trágárság maszkolását. Lehetővé teszi továbbá, hogy egy adott szó vagy mondat számára konkrét fordítást adj meg, hogy olyan kifejezésekkel dolgozz, amelyeket nem akarsz lefordítani, vagy amelyeknek van egy jól ismert fordítása.

Például, amikor az "I have a Raspberry Pi" mondatot, amely az egylapkás számítógépre utal, egy másik nyelvre, például franciára fordítod, szeretnéd megtartani a "Raspberry Pi" nevet változatlanul, és nem lefordítani, így "J’ai un Raspberry Pi" lesz belőle, nem pedig "J’ai une pi aux framboises".

## Fordító erőforrás létrehozása

Ehhez a leckéhez szükséged lesz egy Fordító erőforrásra. A REST API-t fogod használni szöveg fordítására.

### Feladat - fordító erőforrás létrehozása

1. A terminálodban vagy parancssorodban futtasd az alábbi parancsot egy fordító erőforrás létrehozásához a `smart-timer` erőforráscsoportodban.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Cseréld ki a `<location>` helyet arra a helyre, amelyet az Erőforráscsoport létrehozásakor használtál.

1. Szerezd meg a fordító szolgáltatás kulcsát:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Másold ki az egyik kulcsot.

## Több nyelv támogatása alkalmazásokban fordításokkal

Egy ideális világban az egész alkalmazásodnak annyi különböző nyelvet kellene értenie, amennyit csak lehet, a beszéd felismerésétől kezdve a nyelv megértésén át a válaszadásig beszéd formájában. Ez rengeteg munka, ezért a fordítási szolgáltatások felgyorsíthatják az alkalmazásod szállítási idejét.

![Egy okos időzítő architektúrája, amely japánról angolra fordít, angolul dolgozik, majd visszafordít japánra](../../../../../translated_images/hu/translated-smart-timer.08ac20057fdc5c37.webp)

Képzeld el, hogy egy okos időzítőt építesz, amely angolul működik végig, felismeri az angol beszédet, szöveggé alakítja, angolul végzi a nyelv megértését, angolul építi fel a válaszokat, és angol beszéddel válaszol. Ha japán támogatást szeretnél hozzáadni, kezdheted azzal, hogy a japán beszédet angol szöveggé fordítod, majd az alkalmazás magját változatlanul hagyod, végül a válasz szövegét japánra fordítod, mielőtt beszéddé alakítanád. Ez lehetővé tenné, hogy gyorsan hozzáadd a japán támogatást, és később bővítheted a teljes végponttól végpontig tartó japán támogatással.

> 💁 A gépi fordításra való támaszkodás hátránya, hogy a különböző nyelvek és kultúrák eltérő módon fejezhetik ki ugyanazt a dolgot, így a fordítás nem biztos, hogy megfelel az elvárt kifejezésnek.

A gépi fordítások új lehetőségeket is nyitnak az alkalmazások és eszközök számára, amelyek a felhasználók által létrehozott tartalmat valós időben fordíthatják. A tudományos fantasztikum rendszeresen bemutat "univerzális fordítókat", olyan eszközöket, amelyek idegen nyelveket tudnak fordítani (általában) amerikai angolra. Ezek az eszközök kevésbé tudományos fantasztikum, inkább tudományos tények, ha az idegen részt figyelmen kívül hagyjuk. Már léteznek olyan alkalmazások és eszközök, amelyek valós idejű beszéd- és szövegfordítást biztosítanak, a beszéd- és fordítási szolgáltatások kombinációjával.

Egy példa erre a [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn) mobiltelefonos alkalmazás, amelyet ebben a videóban mutatnak be:

[![A Microsoft Translator élő funkciójának bemutatása](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Kattints a fenti képre a videó megtekintéséhez

Képzeld el, hogy egy ilyen eszköz áll rendelkezésedre, különösen utazáskor vagy olyan emberekkel való kommunikáció során, akiknek a nyelvét nem ismered. Az automatikus fordító eszközök repülőtereken vagy kórházakban való elérhetősége jelentős hozzáférhetőségi fejlesztéseket nyújtana.

✅ Kutass egy kicsit: Vannak kereskedelmi forgalomban kapható fordító IoT eszközök? Mi a helyzet a fordítási képességekkel, amelyek beépítettek okoseszközökbe?

> 👽 Bár nincsenek valódi univerzális fordítók, amelyek lehetővé teszik, hogy idegenekkel beszéljünk, a [Microsoft Translator támogatja a klingont](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Szöveg fordítása MI szolgáltatással

Egy MI szolgáltatást használhatsz, hogy ezt a fordítási képességet hozzáadd az okos időzítődhez.

### Feladat - szöveg fordítása MI szolgáltatással

Dolgozd végig a megfelelő útmutatót, hogy szöveget fordíts az IoT eszközödön:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Egylapkás számítógép - Raspberry Pi](pi-translate-speech.md)
* [Egylapkás számítógép - Virtuális eszköz](virtual-device-translate-speech.md)

---

## 🚀 Kihívás

Hogyan segíthetnek a gépi fordítások más IoT alkalmazásokban az ok

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.