# Úvod do IoT

![Prehľad tejto lekcie vo forme sketchnote](../../../../../translated_images/sk/lesson-1.2606670fa61ee904.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre väčšiu verziu.

Táto lekcia bola súčasťou série [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) od [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekcia bola prezentovaná vo forme dvoch videí – hodinovej lekcie a hodinovej konzultácie, kde sa podrobnejšie rozoberali časti lekcie a odpovedalo sa na otázky.

[![Lekcia 1: Úvod do IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Lekcia 1: Úvod do IoT - Konzultácie](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Kliknite na obrázky vyššie pre sledovanie videí

## Kvíz pred lekciou

[Kvíz pred lekciou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Úvod

Táto lekcia pokrýva niektoré základné témy týkajúce sa Internetu vecí (IoT) a pomôže vám začať s nastavovaním vášho hardvéru.

V tejto lekcii sa budeme venovať:

* [Čo je to 'Internet vecí'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT zariadenia](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Nastavenie vášho zariadenia](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Aplikácie IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Príklady IoT zariadení vo vašom okolí](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Čo je to 'Internet vecí'?

Termín 'Internet vecí' (Internet of Things) zaviedol [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) v roku 1999, aby označil prepojenie internetu s fyzickým svetom prostredníctvom senzorov. Odvtedy sa tento termín používa na opis akéhokoľvek zariadenia, ktoré interaguje s fyzickým svetom okolo seba, buď zhromažďovaním údajov zo senzorov, alebo poskytovaním interakcií v reálnom svete prostredníctvom aktuátorov (zariadení, ktoré vykonávajú činnosti, ako napríklad zapnutie vypínača alebo rozsvietenie LED), pričom sú zvyčajne pripojené k iným zariadeniam alebo internetu.

> **Senzory** zhromažďujú informácie zo sveta, napríklad merajú rýchlosť, teplotu alebo polohu.
>
> **Aktuátory** premieňajú elektrické signály na interakcie v reálnom svete, ako je spustenie vypínača, zapnutie svetiel, vydávanie zvukov alebo odosielanie riadiacich signálov inému hardvéru, napríklad na zapnutie elektrickej zásuvky.

IoT ako technologická oblasť zahŕňa viac než len zariadenia – zahŕňa aj cloudové služby, ktoré dokážu spracovávať údaje zo senzorov alebo odosielať požiadavky aktuátorom pripojeným k IoT zariadeniam. Zahŕňa tiež zariadenia, ktoré nemajú alebo nepotrebujú pripojenie na internet, často označované ako edge zariadenia. Tieto zariadenia dokážu samy spracovávať a reagovať na údaje zo senzorov, zvyčajne pomocou AI modelov trénovaných v cloude.

IoT je rýchlo rastúca technologická oblasť. Odhaduje sa, že do konca roku 2020 bolo nasadených a pripojených na internet 30 miliárd IoT zariadení. Do roku 2025 sa očakáva, že IoT zariadenia budú zhromažďovať takmer 80 zettabajtov údajov, čo je 80 biliónov gigabajtov. To je obrovské množstvo údajov!

![Graf zobrazujúci počet aktívnych IoT zariadení v čase, s rastúcim trendom z menej ako 5 miliárd v roku 2015 na viac ako 30 miliárd v roku 2025](../../../../../images/connected-iot-devices.svg)

✅ Urobte si malý prieskum: Koľko údajov generovaných IoT zariadeniami sa skutočne využíva a koľko sa ignoruje? Prečo sa toľko údajov nevyužíva?

Tieto údaje sú kľúčom k úspechu IoT. Aby ste boli úspešným IoT vývojárom, musíte pochopiť, aké údaje potrebujete zhromažďovať, ako ich zhromažďovať, ako na ich základe robiť rozhodnutia a ako tieto rozhodnutia použiť na interakciu s fyzickým svetom, ak je to potrebné.

## IoT zariadenia

**T** v IoT znamená **Things** (veci) – zariadenia, ktoré interagujú s fyzickým svetom okolo seba buď zhromažďovaním údajov zo senzorov, alebo poskytovaním interakcií v reálnom svete prostredníctvom aktuátorov.

Zariadenia určené na výrobu alebo komerčné použitie, ako napríklad spotrebiteľské fitness náramky alebo priemyselné riadiace jednotky strojov, sú zvyčajne vyrobené na mieru. Používajú vlastné obvodové dosky, možno aj vlastné procesory, navrhnuté tak, aby splnili požiadavky konkrétnej úlohy, či už ide o to, aby boli dostatočne malé na nosenie na zápästí, alebo dostatočne odolné na prácu vo vysokoteplotnom, vysoko namáhanom alebo vibračnom prostredí továrne.

Ako vývojár, ktorý sa učí o IoT alebo vytvára prototyp zariadenia, budete potrebovať vývojovú sadu. Tieto sady sú univerzálne IoT zariadenia navrhnuté pre vývojárov, často s funkciami, ktoré by ste na produkčnom zariadení nemali, ako napríklad sada externých pinov na pripojenie senzorov alebo aktuátorov, hardvér na podporu ladenia alebo ďalšie zdroje, ktoré by pri veľkovýrobe zbytočne zvyšovali náklady.

Tieto vývojové sady zvyčajne spadajú do dvoch kategórií – mikrokontroléry a jednodeskové počítače. Tieto budú predstavené tu a podrobnejšie sa im budeme venovať v ďalšej lekcii.

> 💁 Váš telefón možno tiež považovať za univerzálne IoT zariadenie, s integrovanými senzormi a aktuátormi, pričom rôzne aplikácie využívajú senzory a aktuátory rôznymi spôsobmi s rôznymi cloudovými službami. Nájdete dokonca aj niektoré IoT návody, ktoré používajú aplikáciu v telefóne ako IoT zariadenie.

### Mikrokontroléry

Mikrokontrolér (tiež označovaný ako MCU, skratka pre microcontroller unit) je malý počítač pozostávajúci z:

🧠 Jedného alebo viacerých centrálnych procesorových jednotiek (CPU) – „mozgu“ mikrokontroléra, ktorý spúšťa váš program

💾 Pamäte (RAM a pamäte programu) – kde sú uložené váš program, údaje a premenné

🔌 Programovateľných vstupno-výstupných (I/O) pripojení – na komunikáciu s externými perifériami (pripojenými zariadeniami), ako sú senzory a aktuátory

Mikrokontroléry sú zvyčajne lacné výpočtové zariadenia, pričom priemerné ceny tých, ktoré sa používajú vo vlastnom hardvéri, klesajú na približne 0,50 USD, a niektoré zariadenia sú lacné až 0,03 USD. Vývojové sady môžu začínať na cene 4 USD, pričom náklady rastú s pridaním ďalších funkcií. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), vývojová sada mikrokontroléra od [Seeed studios](https://www.seeedstudio.com), ktorá má senzory, aktuátory, WiFi a obrazovku, stojí približne 30 USD.

![Wio Terminal](../../../../../translated_images/sk/wio-terminal.b8299ee16587db9a.webp)

> 💁 Pri hľadaní mikrokontrolérov na internete buďte opatrní pri vyhľadávaní termínu **MCU**, pretože vám môže priniesť veľa výsledkov týkajúcich sa Marvel Cinematic Universe, nie mikrokontrolérov.

Mikrokontroléry sú navrhnuté tak, aby boli naprogramované na vykonávanie obmedzeného počtu veľmi špecifických úloh, namiesto toho, aby boli univerzálnymi počítačmi ako PC alebo Mac. Okrem veľmi špecifických scenárov k nim nemôžete pripojiť monitor, klávesnicu a myš a používať ich na všeobecné úlohy.

Vývojové sady mikrokontrolérov zvyčajne obsahujú ďalšie senzory a aktuátory na palube. Väčšina dosiek bude mať jeden alebo viac programovateľných LED, spolu s ďalšími zariadeniami, ako sú štandardné konektory na pridanie ďalších senzorov alebo aktuátorov pomocou rôznych ekosystémov výrobcov alebo vstavané senzory (zvyčajne tie najpopulárnejšie, ako sú teplotné senzory). Niektoré mikrokontroléry majú zabudovanú bezdrôtovú konektivitu, ako je Bluetooth alebo WiFi, alebo majú na doske ďalšie mikrokontroléry na pridanie tejto konektivity.

> 💁 Mikrokontroléry sa zvyčajne programujú v jazykoch C/C++.

### Jednodeskové počítače

Jednodeskový počítač je malé výpočtové zariadenie, ktoré obsahuje všetky prvky kompletného počítača na jednej malej doske. Tieto zariadenia majú špecifikácie blízke stolným alebo prenosným počítačom, bežia na plnohodnotnom operačnom systéme, ale sú malé, spotrebúvajú menej energie a sú podstatne lacnejšie.

![Raspberry Pi 4](../../../../../translated_images/sk/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi je jeden z najpopulárnejších jednodeskových počítačov.

Podobne ako mikrokontrolér, jednodeskové počítače majú CPU, pamäť a vstupno-výstupné piny, ale majú aj ďalšie funkcie, ako je grafický čip na pripojenie monitorov, zvukové výstupy a USB porty na pripojenie klávesníc, myší a ďalších štandardných USB zariadení, ako sú webkamery alebo externé úložiská. Programy sú uložené na SD kartách alebo pevných diskoch spolu s operačným systémom, namiesto pamäťového čipu zabudovaného do dosky.

> 🎓 Jednodeskový počítač si môžete predstaviť ako menšiu, lacnejšiu verziu PC alebo Macu, na ktorom čítate tento text, s pridaním GPIO (všeobecných vstupno-výstupných) pinov na interakciu so senzormi a aktuátormi.

Jednodeskové počítače sú plnohodnotné počítače, takže ich možno programovať v akomkoľvek jazyku. IoT zariadenia sa zvyčajne programujú v jazyku Python.

### Výber hardvéru pre ďalšie lekcie

Všetky nasledujúce lekcie obsahujú úlohy, ktoré využívajú IoT zariadenie na interakciu s fyzickým svetom a komunikáciu s cloudom. Každá lekcia podporuje 3 možnosti zariadení – Arduino (s použitím Seeed Studios Wio Terminal), alebo jednodeskový počítač, buď fyzické zariadenie (Raspberry Pi 4), alebo virtuálny jednodeskový počítač bežiaci na vašom PC alebo Macu.

Môžete si prečítať o hardvéri potrebnom na splnenie všetkých úloh v [hardvérovom sprievodcovi](../../../hardware.md).

> 💁 Na splnenie úloh si nemusíte kupovať žiadny IoT hardvér, všetko môžete urobiť pomocou virtuálneho jednodeskového počítača.

Výber hardvéru závisí od toho, čo máte k dispozícii doma alebo v škole, a aký programovací jazyk ovládate alebo sa plánujete naučiť. Obe hardvérové varianty budú používať rovnaký ekosystém senzorov, takže ak začnete s jednou cestou, môžete prejsť na druhú bez nutnosti výmeny väčšiny súpravy. Virtuálny jednodeskový počítač bude ekvivalentom učenia sa na Raspberry Pi, pričom väčšina kódu bude prenosná na Pi, ak si neskôr zaobstaráte zariadenie a senzory.

### Arduino vývojová sada

Ak máte záujem o vývoj mikrokontrolérov, môžete splniť úlohy pomocou zariadenia Arduino. Budete potrebovať základné znalosti programovania v jazykoch C/C++, pretože lekcie budú učiť iba kód relevantný pre Arduino framework, senzory a aktuátory, ktoré sa používajú, a knižnice, ktoré interagujú s cloudom.

Úlohy budú používať [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) s [PlatformIO rozšírením pre vývoj mikrokontrolérov](https://platformio.org). Ak máte skúsenosti s Arduino IDE, môžete ho použiť, ale inštrukcie nebudú poskytované.

### Vývojová sada jednodeskového počítača

Ak máte záujem o vývoj IoT pomocou jednodeskových počítačov, môžete splniť úlohy pomocou Raspberry Pi alebo virtuálneho zariadenia bežiaceho na vašom PC alebo Macu.

Budete potrebovať základné znalosti programovania v jazyku Python, pretože lekcie budú učiť iba kód relevantný pre senzory a aktuátory, ktoré sa používajú, a knižnice, ktoré interagujú s cloudom.

> 💁 Ak sa chcete naučiť programovať v jazyku Python, pozrite si nasledujúce dve video série:
>
> * [Python pre začiatočníkov](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Viac Pythonu pre začiatočníkov](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Úlohy budú používať [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Ak používate Raspberry Pi, môžete buď spustiť Pi s plnou desktopovou verziou Raspberry Pi OS a robiť všetko kódovanie priamo na Pi pomocou [verzie VS Code pre Raspberry Pi OS](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), alebo spustiť Pi ako zariadenie bez hlavy a kódovať z vášho PC alebo Macu pomocou VS Code s [Remote SSH rozšírením](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), ktoré vám umožní pripojiť sa k Pi a upravovať, ladiť a spúšťať kód, akoby ste kódovali priamo na ňom.

Ak použijete možnosť virtuálneho zariadenia, budete kódovať priamo na vašom počítači. Namiesto prístupu k senzorom a aktuátorom použijete nástroj na simuláciu tohto hardvéru, ktorý poskytuje hodnoty senzorov, ktoré môžete definovať, a zobrazuje výsledky aktuátorov na obrazovke.

## Nastavenie vášho zariadenia

Predtým, než začnete programovať vaše IoT zariadenie, budete musieť vykonať malé množstvo nastavení. Postupujte podľa príslušných pokynov nižšie v závislosti od toho, ktoré zariadenie budete používať.
💁 Ak ešte nemáte zariadenie, pozrite si [príručku k hardvéru](../../../hardware.md), ktorá vám pomôže rozhodnúť sa, ktoré zariadenie budete používať a aký ďalší hardvér je potrebné zakúpiť. Nemusíte kupovať hardvér, pretože všetky projekty je možné spustiť na virtuálnom hardvéri.
Tieto pokyny zahŕňajú odkazy na webové stránky tretích strán od tvorcov hardvéru alebo nástrojov, ktoré budete používať. Cieľom je zabezpečiť, aby ste vždy mali najaktuálnejšie pokyny pre rôzne nástroje a hardvér.

Prejdite si príslušného sprievodcu, nastavte svoje zariadenie a dokončite projekt „Hello World“. Toto bude prvý krok pri vytváraní IoT nočného svetla počas štyroch lekcií v tejto úvodnej časti.

* [Arduino - Wio Terminal](wio-terminal.md)  
* [Jednodoskový počítač - Raspberry Pi](pi.md)  
* [Jednodoskový počítač - Virtuálne zariadenie](virtual-device.md)  

✅ Budete používať VS Code pre Arduino aj jednodoskové počítače. Ak ste ho ešte nepoužívali, prečítajte si viac na [stránke VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## Aplikácie IoT

IoT pokrýva širokú škálu prípadov použitia, ktoré možno rozdeliť do niekoľkých hlavných skupín:

* Spotrebiteľský IoT  
* Komerčný IoT  
* Priemyselný IoT  
* IoT pre infraštruktúru  

✅ Urobte si malý prieskum: Pre každú z nižšie opísaných oblastí nájdite jeden konkrétny príklad, ktorý nie je uvedený v texte.

### Spotrebiteľský IoT

Spotrebiteľský IoT sa týka IoT zariadení, ktoré si spotrebitelia kupujú a používajú doma. Niektoré z týchto zariadení sú mimoriadne užitočné, ako napríklad inteligentné reproduktory, inteligentné vykurovacie systémy a robotické vysávače. Iné sú otázne, čo sa týka ich užitočnosti, napríklad hlasom ovládané vodovodné kohútiky, ktoré potom nemôžete vypnúť, pretože hlasové ovládanie vás nepočuje cez zvuk tečúcej vody.

Spotrebiteľské IoT zariadenia umožňujú ľuďom dosiahnuť viac vo svojom prostredí, najmä 1 miliarde ľudí so zdravotným postihnutím. Robotické vysávače môžu zabezpečiť čisté podlahy pre ľudí s obmedzenou pohyblivosťou, ktorí si nemôžu sami povysávať. Hlasom ovládané rúry umožňujú ľuďom s obmedzeným zrakom alebo motorickou kontrolou zapnúť rúru iba hlasom. Zdravotné monitory umožňujú pacientom sledovať chronické ochorenia s pravidelnejšími a podrobnejšími aktualizáciami ich stavu. Tieto zariadenia sa stávajú tak bežnými, že ich používajú aj malé deti ako súčasť svojho každodenného života, napríklad študenti počas virtuálneho vzdelávania počas pandémie COVID nastavovali časovače na inteligentných domácich zariadeniach na sledovanie školských úloh alebo budíky na pripomenutie nadchádzajúcich hodín.

✅ Aké spotrebiteľské IoT zariadenia máte pri sebe alebo doma?

### Komerčný IoT

Komerčný IoT zahŕňa použitie IoT v pracovnom prostredí. V kancelárii môžu byť senzory obsadenosti a pohybové detektory na riadenie osvetlenia a vykurovania, aby sa svetlá a kúrenie zapínali iba vtedy, keď je to potrebné, čím sa znižujú náklady a emisie uhlíka. Vo fabrike môžu IoT zariadenia monitorovať bezpečnostné riziká, ako napríklad pracovníkov bez ochranných prilieb alebo hluk, ktorý dosiahol nebezpečné úrovne. V maloobchode môžu IoT zariadenia merať teplotu chladiacich zariadení a upozorniť majiteľa obchodu, ak je chladnička alebo mraznička mimo požadovaného teplotného rozsahu, alebo môžu monitorovať položky na regáloch a nasmerovať zamestnancov na doplnenie vypredaného tovaru. Dopravný priemysel čoraz viac využíva IoT na monitorovanie polohy vozidiel, sledovanie najazdených kilometrov pre cestné poplatky, sledovanie dodržiavania pracovných hodín vodičov a prestávok alebo upozorňovanie personálu, keď sa vozidlo blíži k depu, aby sa pripravili na nakládku alebo vykládku.

✅ Aké komerčné IoT zariadenia máte vo svojej škole alebo na pracovisku?

### Priemyselný IoT (IIoT)

Priemyselný IoT, alebo IIoT, je použitie IoT zariadení na riadenie a správu strojov vo veľkom meradle. To zahŕňa širokú škálu prípadov použitia, od tovární po digitálne poľnohospodárstvo.

Továrne používajú IoT zariadenia rôznymi spôsobmi. Stroje môžu byť monitorované viacerými senzormi na sledovanie vecí, ako je teplota, vibrácie a rýchlosť otáčania. Tieto údaje môžu byť monitorované, aby sa umožnilo zastavenie stroja, ak sa dostane mimo určitých tolerancií – napríklad ak sa prehrieva, môže byť vypnutý. Tieto údaje môžu byť tiež zhromažďované a analyzované v priebehu času na prediktívnu údržbu, kde AI modely analyzujú údaje predchádzajúce poruche a používajú ich na predpovedanie ďalších porúch skôr, ako sa stanú.

Digitálne poľnohospodárstvo je dôležité, ak má planéta uživiť rastúcu populáciu, najmä pre 2 miliardy ľudí v 500 miliónoch domácností, ktoré prežívajú na [subsistenčnom poľnohospodárstve](https://wikipedia.org/wiki/Subsistence_agriculture). Digitálne poľnohospodárstvo môže zahŕňať od niekoľkých lacných senzorov až po obrovské komerčné systémy. Farmár môže začať monitorovaním teplôt a používaním [stupňov rastu](https://wikipedia.org/wiki/Growing_degree-day) na predpovedanie, kedy bude úroda pripravená na zber. Môžu pripojiť monitorovanie vlhkosti pôdy k automatizovaným zavlažovacím systémom, aby poskytli rastlinám toľko vody, koľko potrebujú, ale nie viac, čím zabezpečia, že ich plodiny nevyschnú a zároveň neplytvajú vodou. Farmári idú ešte ďalej a používajú drony, satelitné údaje a AI na monitorovanie rastu plodín, chorôb a kvality pôdy na obrovských plochách poľnohospodárskej pôdy.

✅ Aké ďalšie IoT zariadenia by mohli pomôcť farmárom?

### IoT pre infraštruktúru

IoT pre infraštruktúru monitoruje a riadi miestnu a globálnu infraštruktúru, ktorú ľudia používajú každý deň.

[Smart Cities](https://wikipedia.org/wiki/Smart_city) sú mestské oblasti, ktoré používajú IoT zariadenia na zhromažďovanie údajov o meste a ich využitie na zlepšenie fungovania mesta. Tieto mestá sú zvyčajne riadené spoluprácou medzi miestnymi vládami, akademickou obcou a miestnymi podnikmi, pričom sledujú a riadia rôzne aspekty, ako je doprava, parkovanie a znečistenie. Napríklad v Kodani, Dánsko, je znečistenie ovzdušia dôležité pre miestnych obyvateľov, takže sa meria a údaje sa používajú na poskytovanie informácií o najčistejších trasách pre cyklistov a bežcov.

[Inteligentné elektrické siete](https://wikipedia.org/wiki/Smart_grid) umožňujú lepšiu analýzu dopytu po elektrine zhromažďovaním údajov o spotrebe na úrovni jednotlivých domácností. Tieto údaje môžu usmerňovať rozhodnutia na úrovni krajiny, ako napríklad kde stavať nové elektrárne, a na osobnej úrovni poskytovaním prehľadov o tom, koľko elektriny používajú, kedy ju používajú a dokonca návrhy na zníženie nákladov, napríklad nabíjaním elektrických áut v noci.

✅ Ak by ste mohli pridať IoT zariadenia na meranie čohokoľvek vo vašom okolí, čo by to bolo?

## Príklady IoT zariadení, ktoré môžete mať okolo seba

Boli by ste prekvapení, koľko IoT zariadení máte okolo seba. Píšem toto z domu a mám nasledujúce zariadenia pripojené na internet s inteligentnými funkciami, ako je ovládanie cez aplikáciu, hlasové ovládanie alebo schopnosť posielať údaje na môj telefón:

* Viacero inteligentných reproduktorov  
* Chladnička, umývačka riadu, rúra a mikrovlnka  
* Monitor elektriny pre solárne panely  
* Inteligentné zásuvky  
* Videovrátnik a bezpečnostné kamery  
* Inteligentný termostat s viacerými senzormi pre miestnosti  
* Otvárač garážových dverí  
* Domáce zábavné systémy a hlasom ovládané televízory  
* Svetlá  
* Fitness a zdravotné trackery  

Všetky tieto typy zariadení majú senzory a/alebo akčné členy a komunikujú cez internet. Na telefóne môžem zistiť, či sú moje garážové dvere otvorené, a požiadať inteligentný reproduktor, aby ich zatvoril. Dokonca ich môžem nastaviť na časovač, aby sa v noci automaticky zatvorili, ak zostanú otvorené. Keď niekto zazvoní na zvonček, môžem cez telefón vidieť, kto je pri dverách, nech som kdekoľvek na svete, a rozprávať sa s nimi cez reproduktor a mikrofón zabudovaný v zvončeku. Môžem monitorovať svoju hladinu cukru v krvi, srdcovú frekvenciu a spánkové vzorce, hľadať vzory v údajoch na zlepšenie svojho zdravia. Môžem ovládať svetlá cez cloud a sedieť v tme, keď vypadne internetové pripojenie.

---

## 🚀 Výzva

Vypíšte čo najviac IoT zariadení, ktoré máte doma, v škole alebo na pracovisku – môže ich byť viac, než si myslíte!

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Prehľad a samoštúdium

Prečítajte si o výhodách a zlyhaniach spotrebiteľských IoT projektov. Prezrite si spravodajské stránky a hľadajte články o prípadoch, keď sa niečo pokazilo, ako napríklad problémy s ochranou súkromia, hardvérové problémy alebo problémy spôsobené nedostatkom konektivity.

Niekoľko príkladov:

* Pozrite si Twitter účet **[Internet of Sh*t](https://twitter.com/internetofshit)** *(upozornenie na vulgarizmy)* pre dobré príklady zlyhaní spotrebiteľského IoT.  
* [c|net - Môj Apple Watch mi zachránil život: 5 ľudí zdieľa svoje príbehy](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)  
* [c|net - Technik ADT sa priznal k špehovaniu zákazníckych kamier počas rokov](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(upozornenie na citlivý obsah - nežiaduce špehovanie)*  

## Zadanie

[Preskúmajte IoT projekt](assignment.md)  

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za záväzný zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.