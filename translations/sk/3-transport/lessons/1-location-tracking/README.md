# Sledovanie polohy

![Prehľad tejto lekcie vo forme sketchnote](../../../../../translated_images/sk/lesson-11.9fddbac4b664c6d5.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre väčšiu verziu.

## Kvíz pred prednáškou

[Kvíz pred prednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Úvod

Hlavný proces získavania potravín od farmára k spotrebiteľovi zahŕňa nakladanie debien s produktmi na nákladné autá, lode, lietadlá alebo iné komerčné dopravné prostriedky a ich doručenie na určité miesto – buď priamo zákazníkovi, alebo do centrálneho skladu na spracovanie. Celý proces od farmy po spotrebiteľa je súčasťou procesu nazývaného *dodávateľský reťazec*. Video nižšie od W. P. Carey School of Business na Arizona State University podrobnejšie vysvetľuje koncept dodávateľského reťazca a jeho riadenie.

[![Čo je riadenie dodávateľského reťazca? Video od W. P. Carey School of Business na Arizona State University](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Kliknite na obrázok vyššie a pozrite si video

Pridanie IoT zariadení môže výrazne zlepšiť váš dodávateľský reťazec, umožniť vám lepšie spravovať, kde sa položky nachádzajú, plánovať prepravu a manipuláciu s tovarom a rýchlejšie reagovať na problémy.

Pri správe flotily vozidiel, ako sú nákladné autá, je užitočné vedieť, kde sa každé vozidlo v danom čase nachádza. Vozidlá môžu byť vybavené GPS senzormi, ktoré posielajú svoju polohu do IoT systémov, čo umožňuje majiteľom presne určiť ich polohu, vidieť trasu, ktorú prešli, a vedieť, kedy dorazia do cieľa. Väčšina vozidiel funguje mimo pokrytia WiFi, takže na odosielanie týchto údajov používajú mobilné siete. Niekedy je GPS senzor zabudovaný do zložitejších IoT zariadení, ako sú elektronické knihy jázd. Tieto zariadenia sledujú, ako dlho je nákladné auto na ceste, aby sa zabezpečilo, že vodiči dodržiavajú miestne zákony o pracovnom čase.

V tejto lekcii sa naučíte, ako sledovať polohu vozidla pomocou senzora globálneho polohového systému (GPS).

V tejto lekcii sa budeme venovať:

* [Prepojeným vozidlám](../../../../../3-transport/lessons/1-location-tracking)
* [Geopriestorovým súradniciam](../../../../../3-transport/lessons/1-location-tracking)
* [Globálnym polohovým systémom (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [Čítaniu údajov zo senzora GPS](../../../../../3-transport/lessons/1-location-tracking)
* [Údajom NMEA GPS](../../../../../3-transport/lessons/1-location-tracking)
* [Dekódovaniu údajov zo senzora GPS](../../../../../3-transport/lessons/1-location-tracking)

## Prepojené vozidlá

IoT mení spôsob prepravy tovaru vytváraním flotíl *prepojených vozidiel*. Tieto vozidlá sú pripojené k centrálnym IT systémom, ktoré hlásia informácie o ich polohe a iných údajoch zo senzorov. Mať flotilu prepojených vozidiel prináša širokú škálu výhod:

* Sledovanie polohy – môžete presne určiť, kde sa vozidlo nachádza v ktoromkoľvek čase, čo vám umožňuje:

  * Získať upozornenia, keď sa vozidlo blíži k cieľu, aby ste mohli pripraviť posádku na vykládku
  * Lokalizovať ukradnuté vozidlá
  * Kombinovať údaje o polohe a trase s dopravnými problémami, aby ste mohli vozidlá presmerovať počas cesty
  * Byť v súlade s daňovými predpismi. Niektoré krajiny účtujú vozidlám poplatky za prejdené kilometre na verejných cestách (napríklad [novozélandské RUC](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), takže vedieť, kedy je vozidlo na verejných cestách oproti súkromným, uľahčuje výpočet dlžnej dane.
  * Vedieť, kam poslať údržbárske tímy v prípade poruchy

* Telemetria vodiča – možnosť zabezpečiť, aby vodiči dodržiavali rýchlostné limity, zatáčali primeranou rýchlosťou, brzdili včas a efektívne a jazdili bezpečne. Prepojené vozidlá môžu mať aj kamery na zaznamenávanie incidentov. To môže byť prepojené s poistením, čo umožňuje zníženie sadzieb pre dobrých vodičov.

* Dodržiavanie pracovného času vodičov – zabezpečenie, že vodiči jazdia len počas zákonom povolených hodín na základe času, kedy zapnú a vypnú motor.

Tieto výhody je možné kombinovať – napríklad kombinovať dodržiavanie pracovného času vodičov so sledovaním polohy na presmerovanie vodičov, ak nemôžu dosiahnuť cieľ v rámci povoleného času jazdy. Tieto výhody je možné kombinovať aj s inou špecifickou telemetriou vozidla, ako sú údaje o teplote z chladiarenských nákladných áut, čo umožňuje presmerovanie vozidiel, ak by ich aktuálna trasa znamenala, že tovar nebude možné udržať v požadovanej teplote.

> 🎓 Logistika je proces prepravy tovaru z jedného miesta na druhé, napríklad z farmy do supermarketu cez jeden alebo viac skladov. Farmár zabalí debny s paradajkami, ktoré sa naložia na nákladné auto, doručia do centrálneho skladu a naložia na druhé nákladné auto, ktoré môže obsahovať zmes rôznych druhov produktov, ktoré sa potom doručia do supermarketu.

Hlavnou súčasťou sledovania vozidiel je GPS – senzory, ktoré dokážu určiť svoju polohu kdekoľvek na Zemi. V tejto lekcii sa naučíte, ako používať GPS senzor, začínajúc tým, ako definovať polohu na Zemi.

## Geopriestorové súradnice

Geopriestorové súradnice sa používajú na definovanie bodov na povrchu Zeme, podobne ako sa súradnice používajú na kreslenie pixelov na obrazovke počítača alebo na umiestnenie stehov pri vyšívaní. Pre jeden bod máte dvojicu súradníc. Napríklad Microsoft Campus v Redmonde, Washington, USA sa nachádza na 47.6423109, -122.1390293.

### Zemepisná šírka a dĺžka

Zem je guľa – trojrozmerný kruh. Z tohto dôvodu sú body definované rozdelením na 360 stupňov, rovnako ako geometria kruhov. Zemepisná šírka meria počet stupňov od severu na juh, zemepisná dĺžka meria počet stupňov od východu na západ.

> 💁 Nikto presne nevie, prečo sú kruhy rozdelené na 360 stupňov. [Stránka o stupňoch (uhloch) na Wikipédii](https://wikipedia.org/wiki/Degree_(angle)) pokrýva niektoré z možných dôvodov.

![Čiary zemepisnej šírky od 90° na severnom póle, 45° v polovici medzi severným pólom a rovníkom, 0° na rovníku, -45° v polovici medzi rovníkom a južným pólom a -90° na južnom póle](../../../../../translated_images/sk/latitude-lines.11d8d91dfb2014a5.webp)

Zemepisná šírka sa meria pomocou čiar, ktoré obiehajú Zem a sú rovnobežné s rovníkom, pričom rozdeľujú severnú a južnú pologuľu na 90° každú. Rovník je na 0°, severný pól je na 90°, tiež známy ako 90° severnej šírky, a južný pól je na -90°, alebo 90° južnej šírky.

Zemepisná dĺžka sa meria ako počet stupňov na východ a západ. Počiatočný bod 0° zemepisnej dĺžky sa nazýva *hlavný poludník* a bol definovaný v roku 1884 ako čiara od severného pólu po južný pól, ktorá prechádza cez [Britské kráľovské observatórium v Greenwichi, Anglicko](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Čiary zemepisnej dĺžky, ktoré idú od -180° na západ od hlavného poludníka, cez 0° na hlavnom poludníku, po 180° na východ od hlavného poludníka](../../../../../translated_images/sk/longitude-meridians.ab4ef1c91c064586.webp)

> 🎓 Poludník je imaginárna priamka, ktorá ide od severného pólu po južný pól a tvorí polkruh.

Na meranie zemepisnej dĺžky bodu sa meria počet stupňov okolo rovníka od hlavného poludníka po poludník, ktorý prechádza týmto bodom. Zemepisná dĺžka sa pohybuje od -180°, alebo 180° západnej dĺžky, cez 0° na hlavnom poludníku, po 180°, alebo 180° východnej dĺžky. 180° a -180° označujú rovnaký bod, antimeridián alebo 180. poludník. Toto je poludník na opačnej strane Zeme od hlavného poludníka.

> 💁 Antimeridián si netreba zamieňať s medzinárodnou dátovou hranicou, ktorá sa nachádza približne na rovnakom mieste, ale nie je to priamka a mení sa, aby sa prispôsobila geopolitickým hraniciam.

✅ Urobte si výskum: Skúste nájsť zemepisnú šírku a dĺžku vašej aktuálnej polohy.

### Stupne, minúty a sekundy vs desatinné stupne

Tradične sa merania stupňov zemepisnej šírky a dĺžky vykonávali pomocou šesťdesiatkovej sústavy, alebo základu 60, číselného systému používaného starovekými Babylončanmi, ktorí ako prví merali a zaznamenávali čas a vzdialenosť. Pravdepodobne používate šesťdesiatkovú sústavu každý deň bez toho, aby ste si to uvedomovali – delenie hodín na 60 minút a minút na 60 sekúnd.

Zemepisná dĺžka a šírka sa merajú v stupňoch, minútach a sekundách, pričom jedna minúta je 1/60 stupňa a 1 sekunda je 1/60 minúty.

Napríklad na rovníku:

* 1° zemepisnej šírky je **111,3 kilometra**
* 1 minúta zemepisnej šírky je 111,3/60 = **1,855 kilometra**
* 1 sekunda zemepisnej šírky je 1,855/60 = **0,031 kilometra**

Symbol pre minútu je jednoduchá úvodzovka, pre sekundu dvojitá úvodzovka. Napríklad 2 stupne, 17 minút a 43 sekúnd by sa zapísali ako 2°17'43". Časti sekúnd sa uvádzajú ako desatinné čísla, napríklad polovica sekundy je 0°0'0.5".

Počítače nepracujú v základe 60, takže tieto súradnice sa pri používaní údajov GPS vo väčšine počítačových systémov uvádzajú ako desatinné stupne. Napríklad 2°17'43" je 2,295277. Symbol stupňa sa zvyčajne vynecháva.

Súradnice pre bod sa vždy uvádzajú ako `zemepisná šírka, zemepisná dĺžka`, takže príklad uvedený skôr pre Microsoft Campus na 47.6423109,-122.117198 má:

* Zemepisnú šírku 47.6423109 (47.6423109 stupňa severne od rovníka)
* Zemepisnú dĺžku -122.1390293 (122.1390293 stupňa západne od hlavného poludníka).

![Microsoft Campus na 47.6423109,-122.117198](../../../../../translated_images/sk/microsoft-gps-location-world.a321d481b010f6ad.webp)

## Globálne polohové systémy (GPS)

GPS systémy používajú viacero satelitov obiehajúcich Zem na určenie vašej polohy. Pravdepodobne ste už používali GPS systémy bez toho, aby ste si to uvedomovali – na zistenie vašej polohy v mapovej aplikácii na vašom telefóne, ako sú Apple Maps alebo Google Maps, na zistenie, kde sa nachádza vaše vozidlo v aplikácii na privolanie jazdy, ako je Uber alebo Lyft, alebo pri používaní satelitnej navigácie (sat-nav) vo vašom aute.

> 🎓 Satelity v „satelitnej navigácii“ sú GPS satelity!

GPS systémy fungujú tak, že majú niekoľko satelitov, ktoré vysielajú signál s aktuálnou polohou každého satelitu a presným časovým údajom. Tieto signály sa vysielajú cez rádiové vlny a zachytáva ich anténa v GPS senzore. GPS senzor tieto signály deteguje a pomocou aktuálneho času meria, ako dlho trvalo, kým signál dorazil zo satelitu k senzoru. Keďže rýchlosť rádiových vĺn je konštantná, GPS senzor môže pomocou odoslaného časového údaja vypočítať, ako ďaleko je senzor od satelitu. Kombináciou údajov z minimálne 3 satelitov s odoslanými polohami dokáže GPS senzor určiť svoju polohu na Zemi.

> 💁 GPS senzory potrebujú antény na detekciu rádiových vĺn. Antény zabudované do nákladných áut a áut s palubným GPS sú umiestnené tak, aby získali dobrý signál, zvyčajne na čelnom skle alebo streche. Ak používate samostatný GPS systém, ako je smartfón alebo IoT zariadenie, musíte zabezpečiť, aby anténa zabudovaná do GPS systému alebo telefónu mala jasný výhľad na oblohu, napríklad bola namontovaná na čelnom skle.

![Určenie polohy na základe vzdialenosti od viacerých satelitov](../../../../../translated_images/sk/gps-satellites.04acf1148fe25fbf.webp)

GPS satelity obiehajú Zem, nie sú na pevnom bode nad senzorom, takže údaje o polohe zahŕňajú nadmorskú výšku nad hladinou mora, ako aj zemepisnú šírku a dĺžku.

GPS malo kedysi obmedzenia presnosti vynútené americkou armádou, ktoré obmedzovali presnosť na približne 5 metrov. Toto obmedzenie bolo odstránené v roku 2000, čo umožnilo presnosť 30 centimetrov. Dosiahnutie tejto presnosti však nie je vždy možné kvôli rušeniu signálov.

✅ Ak máte smartfón, spustite mapovú aplikáciu a zistite, aká presná je vaša poloha. Môže chvíľu trvať, kým váš telefón deteguje viacero satelitov na získanie presnejšej polohy.
💁 Satelity obsahujú atómové hodiny, ktoré sú neuveriteľne presné, ale každý deň sa odchýlia o 38 mikrosekúnd (0,0000038 sekundy) v porovnaní s atómovými hodinami na Zemi. Táto odchýlka je spôsobená spomalením času pri zvyšovaní rýchlosti, ako predpovedajú Einsteinove teórie špeciálnej a všeobecnej relativity – satelity sa pohybujú rýchlejšie ako rotácia Zeme. Táto odchýlka bola použitá na potvrdenie predpovedí špeciálnej a všeobecnej relativity a musí byť zohľadnená pri návrhu GPS systémov. Doslova čas na GPS satelite beží pomalšie.
GPS systémy boli vyvinuté a nasadené viacerými krajinami a politickými zoskupeniami vrátane USA, Ruska, Japonska, Indie, EÚ a Číny. Moderné GPS senzory sa dokážu pripojiť k väčšine z týchto systémov, aby získali rýchlejšie a presnejšie údaje.

> 🎓 Skupiny satelitov v každom nasadení sa označujú ako konštelácie.

## Čítanie údajov z GPS senzora

Väčšina GPS senzorov posiela údaje cez UART.

> ⚠️ UART bol pokrytý v [projekt 2, lekcia 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Ak je to potrebné, vráťte sa k tejto lekcii.

Na vašom IoT zariadení môžete použiť GPS senzor na získanie GPS údajov.

### Úloha - pripojenie GPS senzora a čítanie GPS údajov

Prejdite si relevantný návod na čítanie GPS údajov pomocou vášho IoT zariadenia:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Jednodoskový počítač - Raspberry Pi](pi-gps-sensor.md)
* [Jednodoskový počítač - Virtuálne zariadenie](virtual-device-gps-sensor.md)

## NMEA GPS údaje

Keď ste spustili svoj kód, mohli ste vidieť výstup, ktorý na prvý pohľad vyzerá ako nezmysel. V skutočnosti ide o štandardné GPS údaje, ktoré majú svoj význam.

GPS senzory posielajú údaje pomocou NMEA správ, ktoré využívajú štandard NMEA 0183. NMEA je skratka pre [National Marine Electronics Association](https://www.nmea.org), americkú obchodnú organizáciu, ktorá stanovuje štandardy pre komunikáciu medzi námornou elektronikou.

> 💁 Tento štandard je proprietárny a jeho cena je minimálne 2 000 USD, ale dostatok informácií o ňom je verejne dostupných, takže väčšina štandardu bola spätne analyzovaná a môže byť použitá v open-source a iných nekomerčných kódoch.

Tieto správy sú textové. Každá správa pozostáva z *veti*, ktorá začína znakom `$`, nasledujú 2 znaky označujúce zdroj správy (napr. GP pre americký GPS systém, GN pre GLONASS, ruský GPS systém) a 3 znaky označujúce typ správy. Zvyšok správy tvoria polia oddelené čiarkami, končiace znakom nového riadku.

Niektoré typy správ, ktoré je možné prijímať, sú:

| Typ | Popis |
| ---- | ----------- |
| GGA | Údaje o GPS fixácii, vrátane zemepisnej šírky, dĺžky a nadmorskej výšky GPS senzora, spolu s počtom satelitov v dosahu na výpočet tejto fixácie. |
| ZDA | Aktuálny dátum a čas, vrátane miestneho časového pásma |
| GSV | Podrobnosti o satelitoch v dosahu - definované ako satelity, z ktorých GPS senzor dokáže detekovať signály |

> 💁 GPS údaje obsahujú časové značky, takže vaše IoT zariadenie môže získať čas z GPS senzora, ak je to potrebné, namiesto spoliehania sa na NTP server alebo interné hodiny reálneho času.

Správa GGA obsahuje aktuálnu polohu vo formáte `(dd)dmm.mmmm`, spolu s jedným znakom označujúcim smer. `d` vo formáte sú stupne, `m` sú minúty, sekundy sú vyjadrené ako desatinné čísla minút. Napríklad 2°17'43" by bolo 217.716666667 - 2 stupne, 17.716666667 minút.

Znak smeru môže byť `N` alebo `S` pre zemepisnú šírku na označenie severu alebo juhu, a `E` alebo `W` pre zemepisnú dĺžku na označenie východu alebo západu. Napríklad zemepisná šírka 2°17'43" by mala znak smeru `N`, -2°17'43" by mala znak smeru `S`.

Príklad - NMEA veta `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* Časť zemepisnej šírky je `4738.538654,N`, čo sa konvertuje na 47.6423109 v desatinných stupňoch. `4738.538654` je 47.6423109, a smer je `N` (sever), takže ide o kladnú zemepisnú šírku.

* Časť zemepisnej dĺžky je `12208.341758,W`, čo sa konvertuje na -122.1390293 v desatinných stupňoch. `12208.341758` je 122.1390293°, a smer je `W` (západ), takže ide o zápornú zemepisnú dĺžku.

## Dekódovanie údajov z GPS senzora

Namiesto používania surových NMEA údajov je lepšie ich dekódovať do užitočnejšieho formátu. Existuje množstvo open-source knižníc, ktoré vám môžu pomôcť extrahovať užitočné údaje zo surových NMEA správ.

### Úloha - dekódovanie údajov z GPS senzora

Prejdite si relevantný návod na dekódovanie údajov z GPS senzora pomocou vášho IoT zariadenia:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Jednodoskový počítač - Raspberry Pi/Virtuálne IoT zariadenie](single-board-computer-gps-decode.md)

---

## 🚀 Výzva

Napíšte vlastný NMEA dekóder! Namiesto spoliehania sa na knižnice tretích strán na dekódovanie NMEA viet, dokážete napísať vlastný dekóder na extrahovanie zemepisnej šírky a dĺžky z NMEA viet?

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Prehľad & Samoštúdium

* Prečítajte si viac o geosprávnych súradniciach na [stránke o geografickom súradnicovom systéme na Wikipédii](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Prečítajte si o hlavných poludníkoch na iných nebeských telesách okrem Zeme na [stránke o hlavných poludníkoch na Wikipédii](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies).
* Preskúmajte rôzne GPS systémy od rôznych vlád a politických zoskupení, ako sú EÚ, Japonsko, Rusko, India a USA.

## Zadanie

[Preskúmajte ďalšie GPS údaje](assignment.md)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.