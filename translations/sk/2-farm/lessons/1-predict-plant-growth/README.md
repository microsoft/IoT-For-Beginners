## Predpovedajte rast rastlín pomocou IoT

![Prehľad tejto lekcie v sketchnote](../../../../../translated_images/sk/lesson-5.42b234299279d263.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre väčšiu verziu.

## Kvíz pred prednáškou

[Kvíz pred prednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Úvod

Rastliny potrebujú na rast určité veci - vodu, oxid uhličitý, živiny, svetlo a teplo. V tejto lekcii sa naučíte, ako vypočítať rýchlosť rastu a zrelosti rastlín meraním teploty vzduchu.

V tejto lekcii sa budeme venovať:

* [Digitálne poľnohospodárstvo](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Prečo je teplota dôležitá pri farmárčení?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Meranie okolitej teploty](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Dni rastového stupňa (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Výpočet GDD pomocou údajov zo senzora teploty](../../../../../2-farm/lessons/1-predict-plant-growth)

## Digitálne poľnohospodárstvo

Digitálne poľnohospodárstvo mení spôsob, akým farmárime, pomocou nástrojov na zber, ukladanie a analýzu údajov z farmárčenia. Momentálne sa nachádzame v období, ktoré Svetové ekonomické fórum označuje ako „Štvrtá priemyselná revolúcia“, a vzostup digitálneho poľnohospodárstva je označovaný ako „Štvrtá poľnohospodárska revolúcia“ alebo „Poľnohospodárstvo 4.0“.

> 🎓 Termín Digitálne poľnohospodárstvo zahŕňa aj celý „hodnotový reťazec poľnohospodárstva“, teda celú cestu od farmy po stôl. Zahŕňa sledovanie kvality produktov počas prepravy a spracovania potravín, systémy skladovania a elektronického obchodu, dokonca aj aplikácie na prenájom traktorov!

Tieto zmeny umožňujú farmárom zvýšiť výnosy, používať menej hnojív a pesticídov a efektívnejšie využívať vodu. Hoci sa primárne používajú v bohatších krajinách, senzory a iné zariadenia postupne klesajú v cene, čím sa stávajú dostupnejšími aj v rozvojových krajinách.

Niektoré techniky umožnené digitálnym poľnohospodárstvom sú:

* Meranie teploty - meranie teploty umožňuje farmárom predpovedať rast a zrelosť rastlín.
* Automatické zavlažovanie - meranie vlhkosti pôdy a zapínanie zavlažovacích systémov, keď je pôda príliš suchá, namiesto časovo nastaveného zavlažovania. Časovo nastavené zavlažovanie môže viesť k nedostatočnému zavlažovaniu počas horúceho, suchého obdobia alebo k nadmernému zavlažovaniu počas dažďa. Zavlažovaním iba vtedy, keď to pôda potrebuje, môžu farmári optimalizovať využitie vody.
* Kontrola škodcov - farmári môžu používať kamery na automatizovaných robotoch alebo dronoch na kontrolu škodcov a aplikovať pesticídy iba tam, kde je to potrebné, čím sa znižuje množstvo použitých pesticídov a ich odtok do miestnych vodných zdrojov.

✅ Urobte si prieskum. Aké ďalšie techniky sa používajú na zlepšenie poľnohospodárskych výnosov?

> 🎓 Termín „Presné poľnohospodárstvo“ sa používa na definovanie pozorovania, merania a reakcie na plodiny na základe jednotlivých polí alebo dokonca častí polí. Zahŕňa meranie úrovní vody, živín a škodcov a presné reagovanie, napríklad zavlažovanie iba malej časti poľa.

## Prečo je teplota dôležitá pri farmárčení?

Pri učení o rastlinách sa väčšina študentov učí o nevyhnutnosti vody, svetla, oxidu uhličitého a živín. Rastliny však potrebujú aj teplo na rast - preto rastliny kvitnú na jar, keď sa teplota zvyšuje, prečo snežienky alebo narcisy môžu vyrásť skoro vďaka krátkemu teplému obdobiu a prečo sú skleníky a hothousy také dobré na podporu rastu rastlín.

> 🎓 Skleníky a hothousy robia podobnú prácu, ale s dôležitým rozdielom. Hothousy sú umelo vyhrievané a umožňujú farmárom presnejšie kontrolovať teploty, skleníky sa spoliehajú na slnko na teplo a zvyčajne jedinou kontrolou sú okná alebo iné otvory na vypúšťanie tepla.

Rastliny majú základnú alebo minimálnu teplotu, optimálnu teplotu a maximálnu teplotu, všetko na základe denných priemerných teplôt.

* Základná teplota - minimálna denná priemerná teplota potrebná na rast rastliny.
* Optimálna teplota - najlepšia denná priemerná teplota na dosiahnutie najväčšieho rastu.
* Maximálna teplota - maximálna teplota, ktorú rastlina dokáže vydržať. Nad touto teplotou rastlina zastaví svoj rast v snahe šetriť vodu a prežiť.

> 💁 Ide o priemerné teploty, priemerované z denných a nočných teplôt. Rastliny tiež potrebujú rôzne teploty počas dňa a noci, aby mohli efektívnejšie fotosyntetizovať a šetriť energiu v noci.

Každý druh rastliny má rôzne hodnoty pre svoju základnú, optimálnu a maximálnu teplotu. Preto niektoré rastliny prosperujú v horúcich krajinách a iné v chladnejších krajinách.

✅ Urobte si prieskum. Pre akékoľvek rastliny vo vašej záhrade, škole alebo miestnom parku zistite, či môžete nájsť ich základnú teplotu.

![Graf ukazujúci rýchlosť rastu, ktorá stúpa s teplotou, potom klesá, keď teplota stúpne príliš vysoko](../../../../../translated_images/sk/plant-growth-temp-graph.c6d69c9478e6ca83.webp)

Graf vyššie ukazuje príklad grafu rýchlosti rastu voči teplote. Až do základnej teploty nedochádza k rastu. Rýchlosť rastu sa zvyšuje až do optimálnej teploty, potom klesá po dosiahnutí tohto vrcholu. 

Tvar tohto grafu sa líši od druhu rastliny k druhu rastliny. Niektoré majú prudšie poklesy nad optimálnou teplotou, iné majú pomalšie nárasty od základnej teploty k optimálnej.

> 💁 Aby farmár dosiahol najlepší rast, musí poznať tri hodnoty teploty a pochopiť tvar grafov pre rastliny, ktoré pestuje.

Ak má farmár kontrolu nad teplotou, napríklad v komerčnom hothouse, môže optimalizovať podmienky pre svoje rastliny. Komerčný hothouse pestujúci paradajky napríklad nastaví teplotu na približne 25°C počas dňa a 20°C v noci, aby dosiahol najrýchlejší rast.

> 🍅 Kombináciou týchto teplôt s umelým osvetlením, hnojivami a kontrolovanými úrovňami CO
Tento kód otvorí súbor CSV a na jeho koniec pridá nový riadok. Riadok obsahuje aktuálny dátum a čas vo formáte čitateľnom pre človeka, nasledovaný teplotou prijatou z IoT zariadenia. Dáta sú uložené vo formáte [ISO 8601](https://wikipedia.org/wiki/ISO_8601) s časovou zónou, ale bez mikrosekúnd.

1. Spustite tento kód rovnako ako predtým, pričom sa uistite, že vaše IoT zariadenie posiela dáta. Súbor CSV s názvom `temperature.csv` bude vytvorený v rovnakom priečinku. Ak ho otvoríte, uvidíte dátumy/časy a merania teploty:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Spustite tento kód na určitý čas, aby ste zachytili dáta. Ideálne by ste ho mali spustiť počas celého dňa, aby ste nazbierali dostatok údajov na výpočet GDD.

    
> 💁 Ak používate virtuálne IoT zariadenie, zaškrtnite políčko náhodného výberu a nastavte rozsah, aby ste sa vyhli získaniu rovnakej teploty pri každom vrátení hodnoty teploty.
    ![Zaškrtnite políčko náhodného výberu a nastavte rozsah](../../../../../translated_images/sk/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.webp) 

    > 💁 Ak chcete tento kód spustiť počas celého dňa, musíte sa uistiť, že počítač, na ktorom beží váš serverový kód, neprejde do režimu spánku. Môžete to dosiahnuť zmenou nastavení napájania alebo spustením niečoho ako [tento Python skript na udržanie systému aktívneho](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Tento kód nájdete v priečinku [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Úloha - výpočet GDD pomocou uložených dát

Keď server zachytí údaje o teplote, GDD pre rastlinu môže byť vypočítané.

Kroky na manuálny výpočet sú:

1. Nájdite základnú teplotu pre rastlinu. Napríklad pre jahody je základná teplota 10°C.

1. Zo súboru `temperature.csv` nájdite najvyššiu a najnižšiu teplotu za deň.

1. Použite výpočet GDD uvedený skôr na výpočet GDD.

Napríklad, ak je najvyššia teplota za deň 25°C a najnižšia 12°C:

![GDD = 25 + 12 delené 2, potom od výsledku odčítajte 10, čo dáva 8.5](../../../../../translated_images/sk/gdd-calculation-strawberries.59f57db94b22adb8.webp)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Preto jahody získali **8.5** GDD. Jahody potrebujú približne 250 GDD na to, aby priniesli plody, takže ešte chvíľu potrvá.

---

## 🚀 Výzva

Rastliny potrebujú na rast viac než len teplo. Čo ďalšie je potrebné?

Pre tieto faktory zistite, či existujú senzory, ktoré ich dokážu merať. Čo tak aktory na kontrolu týchto úrovní? Ako by ste zostavili jedno alebo viac IoT zariadení na optimalizáciu rastu rastlín?

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Prehľad & Samoštúdium

* Prečítajte si viac o digitálnom poľnohospodárstve na [stránke Wikipedia o digitálnom poľnohospodárstve](https://wikipedia.org/wiki/Digital_agriculture). Tiež si prečítajte viac o presnom poľnohospodárstve na [stránke Wikipedia o presnom poľnohospodárstve](https://wikipedia.org/wiki/Precision_agriculture).
* Kompletný výpočet rastových stupňov (GDD) je zložitejší než zjednodušený uvedený tu. Prečítajte si viac o zložitejšej rovnici a o tom, ako sa vysporiadať s teplotami pod základnou hodnotou na [stránke Wikipedia o rastových stupňoch](https://wikipedia.org/wiki/Growing_degree-day).
* Jedlo môže byť v budúcnosti nedostatkové, ak budeme stále používať rovnaké metódy farmárčenia. Zistite viac o hi-tech farmárskych technikách v tomto [videu Hi-Tech Farms of Future na YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Zadanie

[Vizualizujte údaje GDD pomocou Jupyter Notebooku](assignment.md)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.