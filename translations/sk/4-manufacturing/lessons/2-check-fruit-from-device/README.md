# Skontrolujte kvalitu ovocia pomocou IoT zariadenia

![Prehľad tejto lekcie vo forme sketchnote](../../../../../translated_images/sk/lesson-16.215daf18b00631fb.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre jeho zväčšenú verziu.

## Kvíz pred prednáškou

[Kvíz pred prednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Úvod

V predchádzajúcej lekcii ste sa naučili o klasifikátoroch obrázkov a o tom, ako ich trénovať na rozpoznávanie dobrého a zlého ovocia. Aby ste mohli tento klasifikátor obrázkov použiť v IoT aplikácii, potrebujete byť schopní zachytiť obrázok pomocou nejakej kamery a odoslať tento obrázok do cloudu na klasifikáciu.

V tejto lekcii sa naučíte o kamerových senzoroch a o tom, ako ich používať s IoT zariadením na zachytenie obrázku. Tiež sa naučíte, ako zavolať klasifikátor obrázkov z vášho IoT zariadenia.

V tejto lekcii sa budeme venovať:

* [Kamerovým senzorom](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Zachyteniu obrázku pomocou IoT zariadenia](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Publikovaniu vášho klasifikátora obrázkov](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Klasifikácii obrázkov z vášho IoT zariadenia](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Zlepšeniu modelu](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Kamerové senzory

Kamerové senzory, ako už názov napovedá, sú kamery, ktoré môžete pripojiť k vášmu IoT zariadeniu. Môžu zachytávať statické obrázky alebo streamovať video. Niektoré vracajú surové obrazové dáta, iné komprimujú obrazové dáta do súborov ako JPEG alebo PNG. Kamery, ktoré pracujú s IoT zariadeniami, sú zvyčajne oveľa menšie a majú nižšie rozlíšenie, než na aké ste zvyknutí, ale môžete získať aj kamery s vysokým rozlíšením, ktoré sa vyrovnajú špičkovým telefónom. K dispozícii sú rôzne vymeniteľné objektívy, viacnásobné kamerové zostavy, infračervené termokamery alebo UV kamery.

![Svetlo zo scény prechádza cez objektív a zaostruje sa na CMOS senzor](../../../../../translated_images/sk/cmos-sensor.75f9cd74decb1371.webp)

Väčšina kamerových senzorov používa obrazové senzory, kde každý pixel je fotodióda. Objektív zaostruje obraz na obrazový senzor a tisíce alebo milióny fotodiód detegujú svetlo dopadajúce na každú z nich a zaznamenávajú to ako obrazové dáta.

> 💁 Objektívy prevracajú obrazy, kamerový senzor ich potom otočí späť do správnej polohy. To isté sa deje vo vašich očiach – to, čo vidíte, je detegované hore nohami na zadnej strane vášho oka a váš mozog to opraví.

> 🎓 Obrazový senzor je známy ako senzor s aktívnym pixelom (APS) a najpopulárnejším typom APS je senzor na báze komplementárneho kovovo-oxidového polovodiča, alebo CMOS. Možno ste už počuli pojem CMOS senzor používaný pre kamerové senzory.

Kamerové senzory sú digitálne senzory, ktoré posielajú obrazové dáta ako digitálne dáta, zvyčajne s pomocou knižnice, ktorá poskytuje komunikáciu. Kamery sa pripájajú pomocou protokolov ako SPI, aby mohli posielať veľké množstvo dát – obrázky sú podstatne väčšie ako jednotlivé čísla zo senzora, ako je napríklad teplotný senzor.

✅ Aké sú obmedzenia týkajúce sa veľkosti obrázkov pri IoT zariadeniach? Zamyslite sa nad obmedzeniami, najmä na hardvéri mikrokontrolérov.

## Zachytenie obrázku pomocou IoT zariadenia

Svoje IoT zariadenie môžete použiť na zachytenie obrázku, ktorý bude klasifikovaný.

### Úloha – zachytenie obrázku pomocou IoT zariadenia

Prejdite si príslušný návod na zachytenie obrázku pomocou vášho IoT zariadenia:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Jednodoskový počítač - Raspberry Pi](pi-camera.md)
* [Jednodoskový počítač - Virtuálne zariadenie](virtual-device-camera.md)

## Publikovanie vášho klasifikátora obrázkov

V predchádzajúcej lekcii ste trénovali svoj klasifikátor obrázkov. Predtým, než ho budete môcť použiť z vášho IoT zariadenia, musíte model publikovať.

### Iterácie modelu

Keď sa váš model trénoval v predchádzajúcej lekcii, mohli ste si všimnúť, že na karte **Výkon** sa na strane zobrazujú iterácie. Keď ste model prvýkrát trénovali, videli ste *Iteráciu 1* počas tréningu. Keď ste model zlepšili pomocou predikčných obrázkov, videli ste *Iteráciu 2* počas tréningu.

Každýkrát, keď model trénujete, získate novú iteráciu. Toto je spôsob, ako sledovať rôzne verzie vášho modelu trénované na rôznych dátových sadách. Keď vykonáte **Rýchly test**, je tam rozbaľovacia ponuka, ktorú môžete použiť na výber iterácie, aby ste mohli porovnať výsledky medzi viacerými iteráciami.

Keď ste spokojní s iteráciou, môžete ju publikovať, aby bola dostupná na použitie z externých aplikácií. Týmto spôsobom môžete mať publikovanú verziu, ktorú používajú vaše zariadenia, a zároveň pracovať na novej verzii cez viacero iterácií, a potom ju publikovať, keď budete s ňou spokojní.

### Úloha – publikovanie iterácie

Iterácie sa publikujú z portálu Custom Vision.

1. Otvorte portál Custom Vision na [CustomVision.ai](https://customvision.ai) a prihláste sa, ak ho ešte nemáte otvorený. Potom otvorte svoj projekt `fruit-quality-detector`.

1. Vyberte kartu **Výkon** z možností v hornej časti.

1. Vyberte najnovšiu iteráciu zo zoznamu *Iterácie* na strane.

1. Kliknite na tlačidlo **Publikovať** pre danú iteráciu.

    ![Tlačidlo publikovať](../../../../../translated_images/sk/custom-vision-publish-button.b7174e1977b0c33b.webp)

1. V dialógovom okne *Publikovať model* nastavte *Predikčný zdroj* na zdroj `fruit-quality-detector-prediction`, ktorý ste vytvorili v predchádzajúcej lekcii. Nechajte názov ako `Iteration2` a kliknite na tlačidlo **Publikovať**.

1. Po publikovaní kliknite na tlačidlo **Predikčná URL adresa**. Toto zobrazí podrobnosti o predikčnom API, ktoré budete potrebovať na volanie modelu z vášho IoT zariadenia. Spodná časť je označená *Ak máte súbor s obrázkom*, a toto sú detaily, ktoré potrebujete. Skopírujte URL adresu, ktorá bude vyzerať nejako takto:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Kde `<location>` bude lokalita, ktorú ste použili pri vytváraní vášho zdroja Custom Vision, a `<id>` bude dlhé ID zložené z písmen a čísel.

    Tiež si skopírujte hodnotu *Prediction-Key*. Toto je bezpečnostný kľúč, ktorý musíte odoslať pri volaní modelu. Len aplikácie, ktoré odosielajú tento kľúč, môžu model používať, všetky ostatné aplikácie budú odmietnuté.

    ![Dialógové okno predikčného API zobrazujúce URL a kľúč](../../../../../translated_images/sk/custom-vision-prediction-key-endpoint.30c569ffd0338864.webp)

✅ Keď sa publikuje nová iterácia, bude mať iný názov. Ako si myslíte, že by ste zmenili iteráciu, ktorú používa IoT zariadenie?

## Klasifikácia obrázkov z vášho IoT zariadenia

Teraz môžete použiť tieto pripojovacie údaje na volanie klasifikátora obrázkov z vášho IoT zariadenia.

### Úloha – klasifikácia obrázkov z vášho IoT zariadenia

Prejdite si príslušný návod na klasifikáciu obrázkov pomocou vášho IoT zariadenia:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Jednodoskový počítač - Raspberry Pi/Virtuálne IoT zariadenie](single-board-computer-classify-image.md)

## Zlepšenie modelu

Môže sa stať, že výsledky, ktoré získate pri použití kamery pripojenej k vášmu IoT zariadeniu, nebudú zodpovedať tomu, čo by ste očakávali. Predikcie nie sú vždy také presné ako pri použití obrázkov nahraných z vášho počítača. Je to preto, že model bol trénovaný na iných dátach, než aké sa používajú na predikcie.

Aby ste dosiahli čo najlepšie výsledky pre klasifikátor obrázkov, chcete model trénovať s obrázkami, ktoré sú čo najpodobnejšie obrázkom použitým na predikcie. Ak ste napríklad použili kameru telefónu na zachytenie obrázkov na tréning, kvalita obrázkov, ostrosť a farby budú odlišné od kamery pripojenej k IoT zariadeniu.

![2 obrázky banánov, jeden s nízkym rozlíšením a zlým osvetlením z IoT zariadenia, druhý s vysokým rozlíšením a dobrým osvetlením z telefónu](../../../../../translated_images/sk/banana-picture-compare.174df164dc326a42.webp)

Na obrázku vyššie bol obrázok banánu naľavo zachytený pomocou kamery Raspberry Pi, zatiaľ čo obrázok napravo bol zachytený toho istého banánu na tom istom mieste pomocou iPhonu. Je viditeľný rozdiel v kvalite – obrázok z iPhonu je ostrejší, s jasnejšími farbami a väčším kontrastom.

✅ Čo iné by mohlo spôsobiť, že obrázky zachytené vaším IoT zariadením budú mať nesprávne predikcie? Zamyslite sa nad prostredím, v ktorom by mohlo byť IoT zariadenie použité, a aké faktory môžu ovplyvniť zachytený obrázok.

Na zlepšenie modelu ho môžete pretrénovať pomocou obrázkov zachytených z IoT zariadenia.

### Úloha – zlepšenie modelu

1. Klasifikujte viacero obrázkov zrelého a nezrelého ovocia pomocou vášho IoT zariadenia.

1. Na portáli Custom Vision pretrénujte model pomocou obrázkov na karte *Predikcie*.

    > ⚠️ Ak potrebujete, môžete sa odvolať na [pokyny na pretrénovanie vášho klasifikátora v lekcii 1](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Ak vaše obrázky vyzerajú veľmi odlišne od pôvodných použitých na tréning, môžete všetky pôvodné obrázky vymazať tak, že ich vyberiete na karte *Tréningové obrázky* a kliknete na tlačidlo **Vymazať**. Na výber obrázku presuňte kurzor nad obrázok a objaví sa zaškrtávacie políčko, ktoré môžete vybrať alebo zrušiť.

1. Vytrénujte novú iteráciu modelu a publikujte ju podľa vyššie uvedených krokov.

1. Aktualizujte URL adresu koncového bodu vo vašom kóde a znova spustite aplikáciu.

1. Opakujte tieto kroky, kým nebudete spokojní s výsledkami predikcií.

---

## 🚀 Výzva

Ako veľmi ovplyvňuje rozlíšenie obrázkov alebo osvetlenie predikciu?

Skúste zmeniť rozlíšenie obrázkov vo vašom kóde zariadenia a zistite, či to ovplyvní kvalitu obrázkov. Tiež skúste zmeniť osvetlenie.

Ak by ste mali vytvoriť produkčné zariadenie na predaj farmám alebo továrňam, ako by ste zabezpečili, že bude vždy poskytovať konzistentné výsledky?

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Prehľad a samoštúdium

Svoj model Custom Vision ste trénovali pomocou portálu. To závisí od dostupnosti obrázkov – a v reálnom svete nemusíte byť schopní získať tréningové dáta, ktoré zodpovedajú tomu, čo zachytáva kamera na vašom zariadení. Tento problém môžete obísť tým, že budete trénovať priamo z vášho zariadenia pomocou tréningového API, aby ste model trénovali pomocou obrázkov zachytených z vášho IoT zariadenia.

* Prečítajte si o tréningovom API v [rýchlom štarte používania Custom Vision SDK](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Zadanie

[Reagujte na výsledky klasifikácie](assignment.md)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.