<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9dd7f645ad1c6f20b72fee512987f772",
  "translation_date": "2025-08-27T22:01:38+00:00",
  "source_file": "1-getting-started/lessons/2-deeper-dive/README.md",
  "language_code": "cs"
}
-->
# Hlubší pohled na IoT

![Přehled lekce ve formě sketchnotu](../../../../../translated_images/lesson-2.324b0580d620c25e0a24fb7fddfc0b29a846dd4b82c08e7a9466d580ee78ce51.cs.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

Tato lekce byla součástí série [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) od [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekce byla rozdělena do dvou videí – hodinové lekce a hodinové konzultace, kde se podrobněji probíraly části lekce a odpovídalo se na otázky.

[![Lekce 2: Hlubší pohled na IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Lekce 2: Hlubší pohled na IoT - Konzultace](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Klikněte na obrázky výše pro zhlédnutí videí

## Kvíz před lekcí

[Kvíz před lekcí](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Úvod

Tato lekce se podrobněji zabývá některými koncepty, které byly představeny v předchozí lekci.

V této lekci se budeme věnovat:

* [Komponentám IoT aplikace](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Hlubšímu pohledu na mikrokontroléry](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Hlubšímu pohledu na jednodeskové počítače](../../../../../1-getting-started/lessons/2-deeper-dive)

## Komponenty IoT aplikace

IoT aplikace se skládá ze dvou hlavních částí: *Internetu* a *zařízení*. Podívejme se na tyto dvě části podrobněji.

### Zařízení

![Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.cs.jpg)

**Zařízení** v IoT označuje zařízení, které dokáže interagovat s fyzickým světem. Tato zařízení jsou obvykle malá, cenově dostupná a mají nízkou spotřebu energie. Například jednoduché mikrokontroléry s několika kilobajty RAM (oproti gigabajtům v PC), běžící na několika stovkách megahertzů (oproti gigahertzům v PC), ale s tak nízkou spotřebou energie, že mohou fungovat týdny, měsíce nebo dokonce roky na baterie.

Tato zařízení interagují s fyzickým světem buď pomocí senzorů, které sbírají data z okolí, nebo pomocí výstupů či akčních členů, které provádějí fyzické změny. Typickým příkladem je chytrý termostat – zařízení, které má teplotní senzor, prostředek pro nastavení požadované teploty, jako je otočný knoflík nebo dotyková obrazovka, a připojení k topnému nebo chladicímu systému, který lze zapnout, když je detekovaná teplota mimo požadovaný rozsah. Teplotní senzor zjistí, že je v místnosti příliš chladno, a akční člen zapne topení.

![Schéma ukazující teplotu a otočný knoflík jako vstupy do IoT zařízení a ovládání topení jako výstup](../../../../../translated_images/basic-thermostat.a923217fd1f37e5a6f3390396a65c22a387419ea2dd17e518ec24315ba6ae9a8.cs.png)

Existuje obrovská škála různých zařízení, která mohou fungovat jako IoT zařízení, od specializovaného hardwaru, který snímá jednu věc, až po univerzální zařízení, dokonce i váš chytrý telefon! Chytrý telefon může pomocí senzorů detekovat okolní svět a pomocí akčních členů s ním interagovat – například pomocí GPS senzoru zjistit vaši polohu a pomocí reproduktoru vám poskytnout navigační pokyny k cíli.

✅ Zamyslete se nad dalšími systémy kolem vás, které čtou data ze senzoru a na jejich základě činí rozhodnutí. Jedním příkladem by mohl být termostat v troubě. Najdete další?

### Internet

**Internetová** část IoT aplikace zahrnuje aplikace, ke kterým se IoT zařízení může připojit za účelem odesílání a přijímání dat, stejně jako další aplikace, které mohou zpracovávat data ze zařízení a pomáhat rozhodovat, jaké požadavky poslat akčním členům IoT zařízení.

Typickým nastavením je použití nějaké cloudové služby, ke které se IoT zařízení připojuje. Tato cloudová služba se stará o věci jako zabezpečení, přijímání zpráv od IoT zařízení a odesílání zpráv zpět. Tato cloudová služba se pak připojuje k dalším aplikacím, které mohou zpracovávat nebo ukládat data ze senzorů, nebo tato data kombinovat s daty z jiných systémů pro rozhodování.

Zařízení se také nemusí vždy připojovat přímo k internetu přes WiFi nebo kabelové připojení. Některá zařízení používají síť typu mesh, aby mezi sebou komunikovala přes technologie jako Bluetooth, přičemž se připojují přes centrální zařízení, které má připojení k internetu.

V případě chytrého termostatu by se termostat připojil k domácí WiFi a následně ke cloudové službě. Odesílal by data o teplotě do této služby, kde by byla uložena do databáze, což by umožnilo majiteli domu kontrolovat aktuální a historické teploty pomocí aplikace na telefonu. Jiná služba v cloudu by věděla, jakou teplotu majitel domu požaduje, a posílala by zprávy zpět do IoT zařízení přes cloudovou službu, aby řídila topný systém.

![Schéma ukazující teplotu a otočný knoflík jako vstupy do IoT zařízení, obousměrnou komunikaci mezi IoT zařízením a cloudem, který dále komunikuje s telefonem, a ovládání topení jako výstup z IoT zařízení](../../../../../translated_images/mobile-controlled-thermostat.4a994010473d8d6a52ba68c67e5f02dc8928c717e93ca4b9bc55525aa75bbb60.cs.png)

Ještě chytřejší verze by mohla využívat AI v cloudu s daty z dalších senzorů připojených k jiným IoT zařízením, jako jsou senzory obsazenosti, které detekují, které místnosti jsou využívány, stejně jako data o počasí nebo váš kalendář, aby inteligentně nastavovala teplotu. Například by mohla vypnout topení, pokud zjistí z vašeho kalendáře, že jste na dovolené, nebo vypnout topení v jednotlivých místnostech podle toho, které místnosti používáte, a postupně se učit z dat, aby byla stále přesnější.

![Schéma ukazující více teplotních senzorů a otočný knoflík jako vstupy do IoT zařízení, obousměrnou komunikaci mezi IoT zařízením a cloudem, který dále komunikuje s telefonem, kalendářem a službou počasí, a ovládání topení jako výstup z IoT zařízení](../../../../../translated_images/smarter-thermostat.a75855f15d2d9e63.cs.png)

✅ Jaká další data by mohla pomoci udělat internetově připojený termostat chytřejším?

### IoT na okraji sítě (Edge)

Ačkoli písmeno I v IoT znamená Internet, tato zařízení se nemusí připojovat přímo k internetu. V některých případech se zařízení mohou připojit k tzv. 'edge' zařízením – bránám, které běží na vaší lokální síti, což umožňuje zpracovávat data bez nutnosti připojení k internetu. To může být rychlejší, pokud máte velké množství dat nebo pomalé připojení k internetu, umožňuje to provoz offline tam, kde není připojení k internetu možné, například na lodi nebo v oblastech postižených katastrofou, a umožňuje to uchovávat data v soukromí. Některá zařízení obsahují zpracovatelský kód vytvořený pomocí cloudových nástrojů a tento kód běží lokálně, aby shromažďoval a reagoval na data bez připojení k internetu.

Jedním příkladem je chytré domácí zařízení, jako je Apple HomePod, Amazon Alexa nebo Google Home, které poslouchá váš hlas pomocí AI modelů trénovaných v cloudu, ale běžících lokálně na zařízení. Tato zařízení se 'probudí', když je vysloveno určité slovo nebo fráze, a teprve poté odesílají váš hlas přes internet ke zpracování. Zařízení přestane odesílat hlas v okamžiku, kdy detekuje pauzu ve vašem projevu. Vše, co řeknete před probuzením zařízení klíčovým slovem, a vše, co řeknete poté, co zařízení přestane poslouchat, nebude odesláno přes internet poskytovateli zařízení, a tedy zůstane soukromé.

✅ Zamyslete se nad dalšími scénáři, kde je důležité zachovat soukromí, takže by bylo lepší zpracovávat data na okraji sítě než v cloudu. Napověda – přemýšlejte o IoT zařízeních s kamerami nebo jinými zobrazovacími zařízeními.

### Bezpečnost IoT

S jakýmkoli připojením k internetu je důležité myslet na bezpečnost. Existuje starý vtip, že 'S v IoT znamená Security' – v IoT žádné 'S' není, což naznačuje, že není bezpečné.

IoT zařízení se připojují ke cloudové službě, a proto jsou jen tak bezpečná, jak bezpečná je tato cloudová služba – pokud vaše cloudová služba umožňuje připojení jakémukoli zařízení, mohou být odesílána škodlivá data nebo může dojít k virovým útokům. To může mít velmi reálné důsledky, protože IoT zařízení interagují a ovládají jiná zařízení. Například [červ Stuxnet](https://wikipedia.org/wiki/Stuxnet) manipuloval s ventily v centrifugách, aby je poškodil. Hackeři také využili [špatného zabezpečení k přístupu k dětským chůvičkám](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) a dalším domácím sledovacím zařízením.

> 💁 Někdy IoT zařízení a edge zařízení běží na síti zcela izolované od internetu, aby byla data soukromá a bezpečná. Tomu se říká [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)).

## Hlubší pohled na mikrokontroléry

V předchozí lekci jsme představili mikrokontroléry. Nyní se na ně podíváme podrobněji.

### CPU

CPU je 'mozek' mikrokontroléru. Je to procesor, který spouští váš kód a může odesílat data do připojených zařízení nebo je od nich přijímat. CPU může obsahovat jedno nebo více jader – v podstatě jeden nebo více procesorů, které mohou spolupracovat na spuštění vašeho kódu.

CPU se spoléhá na hodiny, které tikají mnohokrát za sekundu. Každý tik, nebo cyklus, synchronizuje akce, které může CPU provádět. S každým tikem může CPU vykonat instrukci z programu, například načíst data z externího zařízení nebo provést matematický výpočet. Tento pravidelný cyklus umožňuje dokončit všechny akce před zpracováním další instrukce.

Rychlost hodin je měřena v [Hertzích (Hz)](https://wikipedia.org/wiki/Hertz), což je standardní jednotka, kde 1 Hz znamená jeden cyklus za sekundu.

> 🎓 Rychlosti CPU jsou často uváděny v MHz nebo GHz. 1 MHz je 1 milion Hz, 1 GHz je 1 miliarda Hz.

> 💁 CPU vykonávají programy pomocí [cyklu načtení-dekódování-vykonání](https://wikipedia.org/wiki/Instruction_cycle). Každý tik hodin CPU načte další instrukci z paměti, dekóduje ji a poté ji vykoná, například pomocí aritmeticko-logické jednotky (ALU) k sečtení dvou čísel. Některé instrukce trvají více tiků, takže další cyklus začne po dokončení předchozí instrukce.

![Cyklus načtení-dekódování-vykonání ukazující načtení instrukce z programu uloženého v RAM, její dekódování a vykonání na CPU](../../../../../translated_images/fetch-decode-execute.2fd6f150f6280392807f4475382319abd0cee0b90058e1735444d6baa6f2078c.cs.png)

Mikrokontroléry mají mnohem nižší rychlosti hodin než stolní nebo přenosné počítače, nebo dokonce většina chytrých telefonů. Například Wio Terminal má CPU, který běží na 120 MHz, tedy 120 000 000 cyklů za sekundu.

✅ Průměrný PC nebo Mac má CPU s více jádry běžícími na několika gigahertzích, což znamená, že hodiny tikají miliardkrát za sekundu. Zjistěte rychlost hodin vašeho počítače a porovnejte, kolikrát je rychlejší než Wio Terminal.

Každý cyklus hodin spotřebovává energii a generuje teplo. Čím rychleji tikají, tím více energie se spotřebuje a více tepla se vytvoří. Počítače mají chladiče a ventilátory pro odvod tepla, bez kterých by se přehřály a během několika sekund vypnuly. Mikrokontroléry často nemají ani jedno, protože běží mnohem chladněji a tedy pomaleji. Počítače běží na síťové napájení nebo velké baterie na několik hodin, mikrokontroléry mohou běžet dny, měsíce nebo dokonce roky na malé baterie. Mikrokontroléry mohou mít také jádra, která běží na různých rychlostech, a přepínat na pomalejší jádra s nízkou spotřebou, když je zatížení CPU nízké, aby se snížila spotřeba energie.

> 💁 Některé PC a Macy přijímají stejnou kombinaci rychlých jader s vysokým výkonem a pomalejších jader s nízkou spotřebou, aby šetřily baterii. Například čip M1 v nejnovějších noteboocích Apple může přepínat mezi 4 výkonnostními jádry a 4 efektivními jádry, aby optimalizoval výdrž baterie nebo rychlost v závislosti na úloze.

✅ Udělejte si malý průzkum: Přečtěte si o CPU na [Wikipedii](https://wikipedia.org/wiki/Central_processing_unit).

#### Úkol

Prozkoumejte Wio Terminal.

Pokud používáte Wio Terminal pro tyto lekce, zkuste najít CPU. Najděte sekci *Hardware Overview* na [produktové stránce Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) pro obrázek vnitřku zařízení a zkuste najít CPU přes průhledné plastové okénko na zadní straně.

### Paměť

Mikrokontroléry obvykle mají dva typy paměti – paměť pro programy a paměť s náhodným přístupem (RAM).

Paměť pro programy je nevolatilní, což znamená, že cokoli do ní zapíšete, zůstane i po vypnutí zařízení. Tato paměť ukládá váš programový kód.

RAM je paměť, kterou program používá při běhu, obsahující proměnné alokované vaším programem a data získaná z periferií. RAM je volatilní, což znamená, že při výpadku napájení se její obsah ztratí, což efektivně resetuje váš program.
🎓 Paměť programu uchovává váš kód a zůstává zachována i při výpadku napájení.
> 🎓 RAM se používá k provozu vašeho programu a je resetována, když není napájení

Stejně jako u CPU je paměť na mikrokontroléru o několik řádů menší než na PC nebo Macu. Typický počítač může mít 8 gigabajtů (GB) RAM, což je 8 000 000 000 bajtů, přičemž každý bajt má dostatek místa pro uložení jednoho písmene nebo čísla od 0 do 255. Mikrokontrolér by měl pouze kilobajty (KB) RAM, přičemž kilobajt je 1 000 bajtů. Wio terminál zmíněný výše má 192 KB RAM, což je 192 000 bajtů - více než 40 000krát méně než průměrný počítač!

Diagram níže ukazuje relativní rozdíl ve velikosti mezi 192 KB a 8 GB - malá tečka uprostřed představuje 192 KB.

![Porovnání mezi 192 KB a 8 GB - více než 40 000krát větší](../../../../../translated_images/ram-comparison.6beb73541b42ac6f.cs.png)

Úložiště pro programy je také menší než u PC. Typický počítač může mít 500GB pevný disk pro ukládání programů, zatímco mikrokontrolér může mít pouze kilobajty nebo možná několik megabajtů (MB) úložiště (1 MB je 1 000 KB, nebo 1 000 000 bajtů). Wio terminál má 4 MB úložiště pro programy.

✅ Udělejte si malý průzkum: Kolik RAM a úložiště má počítač, na kterém toto čtete? Jak to srovnáváte s mikrokontrolérem?

### Vstup/Výstup

Mikrokontroléry potřebují vstupní a výstupní (I/O) připojení, aby mohly číst data ze senzorů a posílat řídicí signály do akčních členů. Obvykle obsahují řadu univerzálních vstupně/výstupních (GPIO) pinů. Tyto piny lze v softwaru nakonfigurovat jako vstupní (tj. přijímají signál) nebo výstupní (posílají signál).

🧠⬅️ Vstupní piny se používají ke čtení hodnot ze senzorů

🧠➡️ Výstupní piny posílají instrukce do akčních členů

✅ O tom se dozvíte více v následující lekci.

#### Úkol

Prozkoumejte Wio terminál.

Pokud používáte Wio terminál pro tyto lekce, najděte GPIO piny. Najděte sekci *Pinout diagram* na [produktové stránce Wio terminálu](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), abyste zjistili, které piny jsou které. Wio terminál je dodáván s nálepkou, kterou můžete připevnit na zadní stranu s čísly pinů, takže ji nyní přidejte, pokud jste to ještě neudělali.

### Fyzická velikost

Mikrokontroléry jsou obvykle malé, přičemž nejmenší, [Freescale Kinetis KL03 MCU, je dostatečně malý, aby se vešel do důlku golfového míčku](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). Samotné CPU v PC může měřit 40 mm x 40 mm, a to nezahrnuje chladiče a ventilátory potřebné k tomu, aby CPU mohlo běžet déle než několik sekund bez přehřátí, což je podstatně větší než celý mikrokontrolér. Vývojářská sada Wio terminálu s mikrokontrolérem, krytem, obrazovkou a řadou připojení a komponent není o moc větší než samotné CPU Intel i9, a podstatně menší než CPU s chladičem a ventilátorem!

| Zařízení                         | Velikost              |
| -------------------------------- | --------------------- |
| Freescale Kinetis KL03           | 1,6 mm x 2 mm x 1 mm  |
| Wio terminál                     | 72 mm x 57 mm x 12 mm |
| Intel i9 CPU, chladič a ventilátor | 136 mm x 145 mm x 103 mm |

### Frameworky a operační systémy

Kvůli nízké rychlosti a velikosti paměti mikrokontroléry nespouštějí operační systém (OS) v běžném smyslu slova. Operační systém, který umožňuje běh vašeho počítače (Windows, Linux nebo macOS), potřebuje hodně paměti a výpočetního výkonu k provozování úkolů, které jsou pro mikrokontrolér zcela zbytečné. Pamatujte, že mikrokontroléry jsou obvykle naprogramovány tak, aby vykonávaly jeden nebo více velmi specifických úkolů, na rozdíl od univerzálního počítače, jako je PC nebo Mac, který musí podporovat uživatelské rozhraní, přehrávat hudbu nebo filmy, poskytovat nástroje pro psaní dokumentů nebo kódu, hrát hry nebo procházet internet.

Pro programování mikrokontroléru bez OS potřebujete nějaké nástroje, které vám umožní sestavit váš kód tak, aby mohl běžet na mikrokontroléru, a používat API, která mohou komunikovat s periferiemi. Každý mikrokontrolér je jiný, takže výrobci obvykle podporují standardní frameworky, které vám umožní sledovat standardní 'recept' pro sestavení vašeho kódu a jeho spuštění na jakémkoli mikrokontroléru, který tento framework podporuje.

Mikrokontroléry můžete programovat i s OS - často označovaným jako real-time operating system (RTOS), protože jsou navrženy tak, aby zvládaly odesílání dat do a z periferií v reálném čase. Tyto operační systémy jsou velmi lehké a poskytují funkce jako:

* Multithreading, který umožňuje vašemu kódu spouštět více bloků kódu současně, buď na více jádrech, nebo střídavě na jednom jádře
* Síťové funkce pro bezpečnou komunikaci přes internet
* Komponenty grafického uživatelského rozhraní (GUI) pro vytváření uživatelských rozhraní (UI) na zařízeních s obrazovkami.

✅ Přečtěte si o různých RTOS: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Logo Arduino](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) je pravděpodobně nejpopulárnější framework pro mikrokontroléry, zejména mezi studenty, nadšenci a tvůrci. Arduino je open source elektronická platforma kombinující software a hardware. Můžete si koupit desky kompatibilní s Arduinem přímo od Arduino nebo od jiných výrobců a poté je programovat pomocí frameworku Arduino.

Desky Arduino se programují v jazycích C nebo C++. Použití C/C++ umožňuje, aby byl váš kód kompilován velmi malý a běžel rychle, což je potřeba na omezeném zařízení, jako je mikrokontrolér. Jádro aplikace Arduino se nazývá sketch a je to C/C++ kód se dvěma funkcemi - `setup` a `loop`. Když se deska spustí, kód frameworku Arduino spustí funkci `setup` jednou, poté bude funkci `loop` spouštět znovu a znovu, dokud nebude vypnuto napájení.

Do funkce `setup` byste napsali svůj inicializační kód, například připojení k WiFi a cloudovým službám nebo inicializaci pinů pro vstup a výstup. Do funkce `loop` byste pak napsali zpracovatelský kód, například čtení ze senzoru a odesílání hodnoty do cloudu. Obvykle byste do každé smyčky přidali zpoždění, například pokud chcete, aby se data ze senzoru odesílala každých 10 sekund, přidali byste na konci smyčky zpoždění 10 sekund, aby mikrokontrolér mohl spát, šetřit energii, a poté spustit smyčku znovu, když je potřeba.

![Sketch Arduino spouštějící nejprve setup, poté opakovaně loop](../../../../../translated_images/arduino-sketch.79590cb837ff7a7c6a68d1afda6cab83fd53d3bb1bd9a8bf2eaf8d693a4d3ea6.cs.png)

✅ Tato architektura programu je známá jako *event loop* nebo *message loop*. Mnoho aplikací ji používá na pozadí a je standardem pro většinu desktopových aplikací, které běží na OS jako Windows, macOS nebo Linux. Funkce `loop` naslouchá zprávám z komponent uživatelského rozhraní, jako jsou tlačítka, nebo zařízení, jako je klávesnice, a na ně reaguje. Více si můžete přečíst v tomto [článku o event loop](https://wikipedia.org/wiki/Event_loop).

Arduino poskytuje standardní knihovny pro interakci s mikrokontroléry a GPIO piny, s různými implementacemi na pozadí pro běh na různých mikrokontrolérech. Například funkce [`delay`](https://www.arduino.cc/reference/en/language/functions/time/delay/) pozastaví program na danou dobu, funkce [`digitalRead`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) přečte hodnotu `HIGH` nebo `LOW` z daného pinu, bez ohledu na to, na které desce kód běží. Tyto standardní knihovny znamenají, že kód Arduino napsaný pro jednu desku lze rekompilovat pro jakoukoli jinou desku Arduino a bude fungovat, za předpokladu, že piny jsou stejné a desky podporují stejné funkce.

Existuje velký ekosystém knihoven třetích stran pro Arduino, které vám umožňují přidávat další funkce do vašich projektů Arduino, například použití senzorů a akčních členů nebo připojení ke cloudovým IoT službám.

##### Úkol

Prozkoumejte Wio terminál.

Pokud používáte Wio terminál pro tyto lekce, znovu si přečtěte kód, který jste napsali v minulé lekci. Najděte funkce `setup` a `loop`. Sledujte sériový výstup pro opakované volání funkce `loop`. Zkuste přidat kód do funkce `setup`, který zapisuje na sériový port, a pozorujte, že tento kód je volán pouze jednou při každém restartu. Zkuste restartovat zařízení pomocí vypínače na boku, abyste ukázali, že je tato funkce volána při každém restartu zařízení.

## Hlubší pohled na jednodeskové počítače

V minulé lekci jsme představili jednodeskové počítače. Nyní se na ně podíváme podrobněji.

### Raspberry Pi

![Logo Raspberry Pi](../../../../../translated_images/raspberry-pi-logo.4efaa16605cee054.cs.png)

[Nadace Raspberry Pi](https://www.raspberrypi.org) je charitativní organizace z Velké Británie založená v roce 2009 na podporu studia informatiky, zejména na školní úrovni. V rámci této mise vyvinuli jednodeskový počítač nazvaný Raspberry Pi. Raspberry Pi jsou aktuálně dostupné ve 3 variantách - plné velikosti, menší Pi Zero a výpočetní modul, který lze zabudovat do vašeho finálního IoT zařízení.

![Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.cs.jpg)

Nejnovější iterací plnohodnotného Raspberry Pi je Raspberry Pi 4B. Má čtyřjádrový (4 jádra) CPU běžící na 1,5 GHz, 2, 4 nebo 8 GB RAM, gigabitový ethernet, WiFi, 2 HDMI porty podporující 4k obrazovky, audio a kompozitní video výstupní port, USB porty (2 USB 2.0, 2 USB 3.0), 40 GPIO pinů, konektor pro kameru Raspberry Pi a slot na SD kartu. To vše na desce o rozměrech 88 mm x 58 mm x 19,5 mm, napájené 3A USB-C napájecím zdrojem. Tyto desky začínají na ceně 35 USD, což je mnohem levnější než PC nebo Mac.

> 💁 Existuje také Pi400, vše v jednom počítač s Pi4 zabudovaným do klávesnice.

![Raspberry Pi Zero](../../../../../translated_images/raspberry-pi-zero.f7a4133e1e7d54bb.cs.jpg)

Pi Zero je mnohem menší a má nižší výkon. Má jednojádrový 1GHz CPU, 512 MB RAM, WiFi (v modelu Zero W), jeden HDMI port, micro-USB port, 40 GPIO pinů, konektor pro kameru Raspberry Pi a slot na SD kartu. Měří 65 mm x 30 mm x 5 mm a spotřebovává velmi málo energie. Zero stojí 5 USD, verze W s WiFi 10 USD.

> 🎓 CPU v obou těchto zařízeních jsou procesory ARM, na rozdíl od procesorů Intel/AMD x86 nebo x64, které najdete ve většině PC a Maců. Tyto procesory jsou podobné těm, které najdete v některých mikrokontrolérech, stejně jako v téměř všech mobilních telefonech, Microsoft Surface X a nových Apple Silicon Macích.

Všechny varianty Raspberry Pi běží na verzi Debian Linuxu nazvané Raspberry Pi OS. Tento systém je dostupný ve verzi lite bez desktopu, což je ideální pro 'headless' projekty, kde nepotřebujete obrazovku, nebo ve verzi s plným desktopovým prostředím, s webovým prohlížečem, kancelářskými aplikacemi, nástroji pro programování a hrami. Protože OS je verzí Debian Linuxu, můžete nainstalovat jakoukoli aplikaci nebo nástroj, který běží na Debianu a je vytvořen pro procesor ARM uvnitř Pi.

#### Úkol

Prozkoumejte Raspberry Pi.

Pokud používáte Raspberry Pi pro tyto lekce, přečtěte si o různých hardwarových komponentech na desce.

* Podrobnosti o procesorech používaných na [stránce dokumentace hardwaru Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Přečtěte si o procesoru použitém ve vašem Pi.
* Najděte GPIO piny. Přečtěte si více o nich na [dokumentaci GPIO Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Použijte [průvodce použitím GPIO pinů](https://www.raspberrypi.org/documentation/usage/gpio/README.md) k identifikaci různých pinů na vašem Pi.

### Programování jednodeskových počítačů

Jednodeskové počítače jsou plnohodnotné počítače, které běží na plnohodnotném OS. To znamená, že existuje široká škála programovacích jazyků, frameworků a nástrojů, které můžete použít k jejich programování, na rozdíl od mikrokontrolérů, které spoléhají na podporu desky ve frameworcích jako Arduino. Většina programovacích jazyků má knihovny, které umožňují přístup k GPIO pinům pro odesílání a přijímání dat ze senzorů a akčních členů.

✅ Jaké programovací jazyky znáte? Jsou podporovány na Linuxu?

Nejčastějším programovacím jazykem pro vytváření IoT aplikací na Raspberry Pi je Python. Existuje obrovský ekosystém hardwaru navrženého pro Pi a téměř všechny tyto komponenty zahrnují příslušný kód potřebný k jejich použití jako knihovny Pythonu. Některé z těchto ekosystémů jsou založeny na 'hats' - takto nazývané, protože sedí na Pi jako klobouk a připojují se velkým konektorem k 40 GPIO pinům. Tyto hats poskytují další schopnosti, jako jsou obrazovky, senzory, dálkově ovládaná auta nebo adaptéry umožňující připojení senzorů se standardizovanými kabely.
### Použití jednodeskových počítačů v profesionálních IoT nasazeních

Jednodeskové počítače se používají v profesionálních IoT nasazeních, nejen jako vývojářské sady. Mohou poskytnout výkonný způsob ovládání hardwaru a provádění složitých úkolů, jako je například provozování modelů strojového učení. Například existuje [Raspberry Pi 4 Compute Module](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/), který nabízí veškerý výkon Raspberry Pi 4, ale v kompaktnější a levnější podobě bez většiny portů, navržený pro instalaci do vlastního hardwaru.

---

## 🚀 Výzva

Výzvou v poslední lekci bylo vyjmenovat co nejvíce IoT zařízení, která máte doma, ve škole nebo na pracovišti. U každého zařízení na tomto seznamu si zkuste odpovědět, zda jsou postavena na mikrokontrolérech, jednodeskových počítačích, nebo dokonce na kombinaci obou.

## Kvíz po přednášce

[Kvíz po přednášce](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Recenze a samostudium

* Přečtěte si [průvodce začátky s Arduinem](https://www.arduino.cc/en/Guide/Introduction), abyste lépe porozuměli platformě Arduino.
* Přečtěte si [úvod do Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/), abyste se dozvěděli více o Raspberry Pi.
* Zjistěte více o některých pojmech a zkratkách v článku [Co jsou vlastně CPU, MPU, MCU a GPU v Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Použijte tyto průvodce spolu s náklady uvedenými po kliknutí na odkazy v [průvodci hardwarem](../../../hardware.md), abyste se rozhodli, jakou hardwarovou platformu chcete použít, nebo zda raději použijete virtuální zařízení.

## Zadání

[Porovnejte a kontrastujte mikrokontroléry a jednodeskové počítače](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neneseme odpovědnost za jakékoli nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.