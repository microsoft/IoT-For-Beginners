# Spustenie detekcie kvality ovocia zo senzora

![Prehľad lekcie v sketchnote](../../../../../translated_images/sk/lesson-18.92c32ed1d354caa5.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre väčšiu verziu.

## Kvíz pred prednáškou

[Kvíz pred prednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Úvod

IoT aplikácia nie je len jedno zariadenie, ktoré zachytáva dáta a posiela ich do cloudu. Často ide o viacero zariadení, ktoré spolupracujú na zachytávaní dát z fyzického sveta pomocou senzorov, rozhodujú na základe týchto dát a interagujú späť s fyzickým svetom prostredníctvom akčných členov alebo vizualizácií.

V tejto lekcii sa dozviete viac o navrhovaní komplexných IoT aplikácií, ktoré zahŕňajú viacero senzorov, cloudových služieb na analýzu a ukladanie dát, a odpoveď prostredníctvom akčného člena. Naučíte sa, ako navrhnúť prototyp systému kontroly kvality ovocia, vrátane použitia senzorov na spustenie IoT aplikácie a aká by bola architektúra tohto prototypu.

V tejto lekcii sa budeme venovať:

* [Navrhovanie komplexných IoT aplikácií](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Návrh systému kontroly kvality ovocia](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Spustenie kontroly kvality ovocia zo senzora](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Dáta používané na detekciu kvality ovocia](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Použitie vývojárskych zariadení na simuláciu viacerých IoT zariadení](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Prechod do produkcie](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Toto je posledná lekcia v tomto projekte, takže po dokončení tejto lekcie a úlohy nezabudnite vyčistiť svoje cloudové služby. Budete ich potrebovať na dokončenie úlohy, takže sa uistite, že ju najprv dokončíte.
>
> Ak je to potrebné, pozrite si [príručku na vyčistenie projektu](../../../clean-up.md) pre pokyny, ako to urobiť.

## Navrhovanie komplexných IoT aplikácií

IoT aplikácie pozostávajú z mnohých komponentov. To zahŕňa rôzne zariadenia a internetové služby.

IoT aplikácie môžeme opísať ako *zariadenia* (things), ktoré posielajú dáta, čím generujú *poznatky* (insights). Tieto *poznatky* generujú *akcie* (actions) na zlepšenie podnikania alebo procesu. Príkladom je motor (zariadenie), ktorý posiela údaje o teplote. Tieto údaje sa používajú na vyhodnotenie, či motor funguje podľa očakávaní (poznatok). Na základe poznatku sa proaktívne upravuje harmonogram údržby motora (akcia).

* Rôzne zariadenia zhromažďujú rôzne typy dát.
* IoT služby poskytujú poznatky na základe týchto dát, niekedy ich dopĺňajú dátami z ďalších zdrojov.
* Tieto poznatky vedú k akciám, vrátane ovládania akčných členov v zariadeniach alebo vizualizácie dát.

### Referenčná IoT architektúra

![Referenčná IoT architektúra](../../../../../translated_images/sk/iot-reference-architecture.2278b98b55c6d4e8.webp)

Vyššie uvedený diagram zobrazuje referenčnú IoT architektúru.

> 🎓 *Referenčná architektúra* je príklad architektúry, ktorú môžete použiť ako referenciu pri navrhovaní nových systémov. V tomto prípade, ak by ste budovali nový IoT systém, môžete sa riadiť referenčnou architektúrou a nahradiť vlastné zariadenia a služby tam, kde je to vhodné.

* **Zariadenia** sú zariadenia, ktoré zhromažďujú dáta zo senzorov, možno interagujú s edge službami na interpretáciu týchto dát, ako napríklad klasifikátory obrázkov na interpretáciu obrazových dát. Dáta zo zariadení sa posielajú do IoT služby.
* **Poznatky** pochádzajú zo serverless aplikácií alebo z analýz uložených dát.
* **Akcie** môžu byť príkazy poslané zariadeniam alebo vizualizácia dát, ktorá umožňuje ľuďom robiť rozhodnutia.

![Referenčná IoT architektúra](../../../../../translated_images/sk/iot-reference-architecture-azure.0b8d2161af924cb1.webp)

Vyššie uvedený diagram zobrazuje niektoré komponenty a služby, ktoré sme doteraz pokryli v týchto lekciách, a ako sa spájajú v referenčnej IoT architektúre.

* **Zariadenia** - napísali ste kód zariadenia na zachytávanie dát zo senzorov a analýzu obrázkov pomocou Custom Vision, ktorý beží v cloude aj na edge zariadení. Tieto dáta boli poslané do IoT Hub.
* **Poznatky** - použili ste Azure Functions na reakciu na správy poslané do IoT Hub a uložili dáta na neskoršiu analýzu do Azure Storage.
* **Akcie** - ovládali ste akčné členy na základe rozhodnutí urobených v cloude a príkazov poslaných zariadeniam, a vizualizovali ste dáta pomocou Azure Maps.

✅ Zamyslite sa nad inými IoT zariadeniami, ktoré ste používali, ako sú inteligentné domáce spotrebiče. Aké sú zariadenia, poznatky a akcie spojené s týmto zariadením a jeho softvérom?

Tento vzor môže byť rozšírený na takú veľkosť, akú potrebujete, pridávaním ďalších zariadení a služieb.

### Dáta a bezpečnosť

Pri definovaní architektúry vášho systému musíte neustále zvažovať dáta a bezpečnosť.

* Aké dáta vaše zariadenie posiela a prijíma?
* Ako by mali byť tieto dáta zabezpečené a chránené?
* Ako by mal byť kontrolovaný prístup k zariadeniu a cloudovej službe?

✅ Zamyslite sa nad bezpečnosťou dát akýchkoľvek IoT zariadení, ktoré vlastníte. Koľko z týchto dát je osobných a malo by byť uchovávaných v súkromí, či už počas prenosu alebo pri ukladaní? Aké dáta by nemali byť ukladané?

## Návrh systému kontroly kvality ovocia

Teraz si vezmime túto myšlienku zariadení, poznatkov a akcií a aplikujme ju na náš detektor kvality ovocia, aby sme navrhli väčšiu end-to-end aplikáciu.

Predstavte si, že vám bola zadaná úloha vybudovať detektor kvality ovocia, ktorý sa bude používať v spracovateľskom závode. Ovocie sa pohybuje na dopravníkovom páse, kde zamestnanci momentálne ručne kontrolujú ovocie a odstraňujú nezrelé ovocie, keď dorazí. Na zníženie nákladov chce majiteľ závodu automatizovaný systém.

✅ Jedným z trendov s rastom IoT (a technológie všeobecne) je, že manuálne práce sú nahrádzané strojmi. Urobte si prieskum: Koľko pracovných miest sa odhaduje, že bude stratených kvôli IoT? Koľko nových pracovných miest bude vytvorených pri budovaní IoT zariadení?

Musíte vybudovať systém, kde sa ovocie deteguje, keď dorazí na dopravníkový pás, následne sa fotografuje a kontroluje pomocou AI modelu bežiaceho na edge zariadení. Výsledky sa potom posielajú do cloudu na uloženie, a ak je ovocie nezrelé, je vydané upozornenie, aby sa nezrelé ovocie odstránilo.

|   |   |
| - | - |
| **Zariadenia** | Detektor príchodu ovocia na dopravníkový pás<br>Fotoaparát na fotografovanie a klasifikáciu ovocia<br>Edge zariadenie bežiace klasifikátor<br>Zariadenie na upozornenie na nezrelé ovocie |
| **Poznatky** | Rozhodnutie o kontrole zrelosti ovocia<br>Uloženie výsledkov klasifikácie zrelosti<br>Určenie potreby upozorniť na nezrelé ovocie |
| **Akcie** | Poslanie príkazu zariadeniu na fotografovanie ovocia a kontrolu pomocou klasifikátora obrázkov<br>Poslanie príkazu zariadeniu na upozornenie, že ovocie je nezrelé |

### Prototypovanie aplikácie

![Referenčná IoT architektúra pre kontrolu kvality ovocia](../../../../../translated_images/sk/iot-reference-architecture-fruit-quality.cc705f121c3b6fa7.webp)

Vyššie uvedený diagram zobrazuje referenčnú architektúru pre túto prototypovú aplikáciu.

* IoT zariadenie s proximity senzorom deteguje príchod ovocia. Posiela správu do cloudu, že ovocie bolo detegované.
* Serverless aplikácia v cloude posiela príkaz inému zariadeniu na fotografovanie a klasifikáciu obrázku.
* IoT zariadenie s fotoaparátom urobí fotografiu a pošle ju klasifikátoru obrázkov bežiacemu na edge zariadení. Výsledky sa potom posielajú do cloudu.
* Serverless aplikácia v cloude ukladá tieto informácie na neskoršiu analýzu, aby zistila, aké percento ovocia je nezrelé. Ak je ovocie nezrelé, posiela príkaz inému IoT zariadeniu na upozornenie pracovníkov závodu prostredníctvom LED.

> 💁 Celá táto IoT aplikácia by mohla byť implementovaná ako jedno zariadenie, s celou logikou na spustenie klasifikácie obrázkov a ovládanie LED zabudovanou. Mohla by používať IoT Hub len na sledovanie počtu detegovaných nezrelých plodov a konfiguráciu zariadenia. V tejto lekcii je rozšírená, aby demonštrovala koncepty pre veľké IoT aplikácie.

Pre prototyp budete implementovať všetko na jednom zariadení. Ak používate mikrokontrolér, použijete samostatné edge zariadenie na spustenie klasifikátora obrázkov.

## Spustenie kontroly kvality ovocia zo senzora

IoT zariadenie potrebuje nejaký druh spúšťača, ktorý indikuje, kedy je ovocie pripravené na klasifikáciu. Jedným zo spúšťačov by bolo meranie, keď je ovocie na správnom mieste na dopravníkovom páse, pomocou merania vzdialenosti k senzoru.

![Proximity senzory posielajú laserové lúče na objekty ako banány a merajú čas, kým sa lúč odrazí späť](../../../../../translated_images/sk/proximity-sensor.f5cd752c77fb62fe.webp)

Proximity senzory môžu byť použité na meranie vzdialenosti od senzora k objektu. Zvyčajne vysielajú lúč elektromagnetického žiarenia, ako je laserový lúč alebo infračervené svetlo, a potom detegujú žiarenie odrazené od objektu. Čas medzi vyslaním laserového lúča a signálom odrazeným späť môže byť použitý na výpočet vzdialenosti k senzoru.

> 💁 Pravdepodobne ste používali proximity senzory bez toho, aby ste o tom vedeli. Väčšina smartfónov vypne obrazovku, keď ich držíte pri uchu, aby ste náhodou neukončili hovor ušným lalokom. Toto funguje pomocou proximity senzora, ktorý deteguje objekt blízko obrazovky počas hovoru a deaktivuje dotykové funkcie, kým je telefón v určitej vzdialenosti.

### Úloha - spustenie detekcie kvality ovocia pomocou senzora vzdialenosti

Prejdite si relevantnú príručku na použitie proximity senzora na detekciu objektu pomocou vášho IoT zariadenia:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Jednodoskový počítač - Raspberry Pi](pi-proximity.md)
* [Jednodoskový počítač - Virtuálne zariadenie](virtual-device-proximity.md)

## Dáta používané na detekciu kvality ovocia

Prototyp detektora ovocia má viacero komponentov, ktoré medzi sebou komunikujú.

![Komponenty komunikujúce medzi sebou](../../../../../translated_images/sk/fruit-quality-detector-message-flow.adf2a65da8fd8741.webp)

* Proximity senzor meria vzdialenosť k ovociu a posiela ju do IoT Hub
* Príkaz na ovládanie fotoaparátu prichádza z IoT Hub do zariadenia s fotoaparátom
* Výsledky klasifikácie obrázkov sa posielajú do IoT Hub
* Príkaz na ovládanie LED na upozornenie, že ovocie je nezrelé, sa posiela z IoT Hub do zariadenia s LED

Je dobré definovať štruktúru týchto správ vopred, predtým než začnete budovať aplikáciu.

> 💁 Takmer každý skúsený vývojár sa niekedy vo svojej kariére stretol s problémami spôsobenými rozdielmi medzi dátami, ktoré sa posielajú, a tým, čo sa očakáva.

Napríklad - ak posielate informácie o teplote, ako by ste definovali JSON? Mohli by ste mať pole nazvané `temperature`, alebo by ste mohli použiť bežnú skratku `temp`.

```json
{
    "temperature": 20.7
}
```

v porovnaní s:

```json
{
    "temp": 20.7
}
```

Musíte tiež zvážiť jednotky - je teplota v °C alebo °F? Ak meriate teplotu pomocou spotrebiteľského zariadenia a používateľ zmení jednotky zobrazenia, musíte zabezpečiť, aby jednotky posielané do cloudu zostali konzistentné.

✅ Urobte si prieskum: Ako problémy s jednotkami spôsobili haváriu Mars Climate Orbiter v hodnote 125 miliónov dolárov?

Zamyslite sa nad dátami, ktoré sa posielajú pre detektor kvality ovocia. Ako by ste definovali každú správu? Kde by ste analyzovali dáta a robili rozhodnutia o tom, aké dáta poslať?

Napríklad - spustenie klasifikácie obrázkov pomocou proximity senzora. IoT zariadenie meria vzdialenosť, ale kde sa robí rozhodnutie? Rozhodne zariadenie, že ovocie je dostatočne blízko, a pošle správu IoT Hub na spustenie klasifikácie? Alebo posiela merania vzdialenosti a nechá IoT Hub rozhodnúť?

Odpoveď na otázky ako táto je - záleží. Každý prípad použitia je iný, preto ako IoT vývojár musíte pochopiť systém, ktorý budujete, ako sa používa a dáta, ktoré deteguje.

* Ak sa rozhodnutie robí IoT Hub, musíte posielať viacero meraní vzdialenosti.
* Ak posielate príliš veľa správ, zvyšuje to náklady na IoT Hub a množstvo šírky pásma potrebnej vašimi IoT zariadeniami (najmä vo fabrike s miliónmi zariadení). Môže to tiež spomaliť vaše zariadenie.
* Ak robíte rozhodnutie na zariadení, budete musieť poskytnúť spôsob konfigurácie zariadenia na jemné doladenie stroja.

## Použitie vývojárskych zariadení na simuláciu viacerých IoT zariadení

Na vytvorenie vášho prototypu budete potrebovať, aby váš IoT vývojársky kit fungoval ako viacero zariadení, posielal telemetriu a reagoval na príkazy.

### Simulácia viacerých IoT zariadení na Raspberry Pi alebo virtuálnom IoT hardvéri

Pri použití jednodoskového počítača, ako je Raspberry Pi, môžete spustiť viacero aplikácií naraz. To znamená, že môžete simulovať viacero IoT zariadení vytvorením viacerých aplikácií, jednej pre každé 'IoT zariadenie'. Napríklad, môžete implementovať každé zariadenie ako samostatný Python súbor a spustiť ich v rôznych terminálových reláciách.
> 💁 Uvedomte si, že niektorý hardvér nebude fungovať, ak k nemu pristupuje viacero aplikácií súčasne.
### Simulácia viacerých zariadení na mikrokontroléri

Mikrokontroléry sú zložitejšie na simuláciu viacerých zariadení. Na rozdiel od jednodeskových počítačov nemôžete spúšťať viacero aplikácií naraz, musíte zahrnúť všetku logiku pre všetky samostatné IoT zariadenia do jednej aplikácie.

Niekoľko návrhov, ako tento proces uľahčiť:

* Vytvorte jednu alebo viac tried pre každé IoT zariadenie – napríklad triedy nazvané `DistanceSensor`, `ClassifierCamera`, `LEDController`. Každá z nich môže mať svoje vlastné metódy `setup` a `loop`, ktoré sú volané hlavnými funkciami `setup` a `loop`.
* Spracovávajte príkazy na jednom mieste a presmerujte ich do relevantnej triedy zariadenia podľa potreby.
* V hlavnej funkcii `loop` budete musieť zvážiť načasovanie pre každé zariadenie. Napríklad, ak máte jednu triedu zariadenia, ktorá potrebuje spracovávať každých 10 sekúnd, a inú, ktorá potrebuje spracovávať každú 1 sekundu, potom v hlavnej funkcii `loop` použite oneskorenie 1 sekundu. Každé volanie `loop` spustí relevantný kód pre zariadenie, ktoré potrebuje spracovávať každú sekundu, a použite čítač na počítanie každého cyklu, pričom druhé zariadenie spracujete, keď čítač dosiahne hodnotu 10 (následne čítač resetujete).

## Prechod do produkcie

Prototyp bude základom finálneho produkčného systému. Niektoré rozdiely pri prechode do produkcie zahŕňajú:

* Odolné komponenty – použitie hardvéru navrhnutého na odolávanie hluku, teplu, vibráciám a stresu vo výrobnom prostredí.
* Použitie interných komunikácií – niektoré komponenty by komunikovali priamo, čím by sa vyhli prenosu do cloudu, pričom by do cloudu posielali iba údaje na uloženie. Ako sa to realizuje, závisí od nastavenia továrne, buď priamou komunikáciou, alebo spustením časti IoT služby na okraji pomocou bránového zariadenia.
* Možnosti konfigurácie – každá továreň a prípad použitia je iný, takže hardvér by mal byť konfigurovateľný. Napríklad senzor blízkosti môže potrebovať detekovať rôzne druhy ovocia na rôznych vzdialenostiach. Namiesto pevného kódovania vzdialenosti na spustenie klasifikácie by ste chceli, aby to bolo konfigurovateľné cez cloud, napríklad pomocou dvojníka zariadenia.
* Automatizované odstraňovanie ovocia – namiesto LED diódy, ktorá upozorňuje, že ovocie nie je zrelé, by automatizované zariadenia ovocie odstránili.

✅ Urobte si prieskum: Akými ďalšími spôsobmi by sa produkčné zariadenia líšili od vývojárskych súprav?

---

## 🚀 Výzva

V tejto lekcii ste sa naučili niektoré koncepty, ktoré potrebujete vedieť o tom, ako navrhnúť IoT systém. Spomeňte si na predchádzajúce projekty. Ako by zapadli do referenčnej architektúry uvedenej vyššie?

Vyberte si jeden z doterajších projektov a zamyslite sa nad návrhom zložitejšieho riešenia, ktoré spája viacero schopností nad rámec toho, čo bolo pokryté v projektoch. Nakreslite architektúru a premýšľajte o všetkých zariadeniach a službách, ktoré by ste potrebovali.

Napríklad – zariadenie na sledovanie vozidiel, ktoré kombinuje GPS so senzormi na monitorovanie vecí, ako sú teploty v chladiarenskom kamióne, časy zapnutia a vypnutia motora a identita vodiča. Aké zariadenia sú zapojené, aké služby sú zapojené, aké údaje sa prenášajú a aké sú bezpečnostné a súkromné aspekty?

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Prehľad a samostatné štúdium

* Prečítajte si viac o IoT architektúre v [dokumentácii referenčnej architektúry Azure IoT na Microsoft docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Prečítajte si viac o dvojníkoch zariadení v [dokumentácii IoT Hub na Microsoft docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Prečítajte si o OPC-UA, komunikačnom protokole medzi strojmi používanom v priemyselnej automatizácii na [stránke OPC-UA na Wikipédii](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Zadanie

[Postavte detektor kvality ovocia](assignment.md)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.