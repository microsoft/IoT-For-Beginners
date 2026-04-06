# Úvod do IoT

![Přehled této lekce ve formě sketchnote](../../../../../translated_images/cs/lesson-1.2606670fa61ee904.webp)

> Sketchnote vytvořil [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

Tato lekce byla součástí série [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) od [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekce byla rozdělena do dvou videí - hodinové lekce a hodinového "office hour", kde se podrobněji probíraly části lekce a odpovídalo se na otázky.

[![Lekce 1: Úvod do IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Lekce 1: Úvod do IoT - Office hours](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Klikněte na obrázky výše pro zhlédnutí videí

## Kvíz před lekcí

[Kvíz před lekcí](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Úvod

Tato lekce pokrývá některá úvodní témata týkající se Internetu věcí (IoT) a pomůže vám začít s nastavením vašeho hardwaru.

V této lekci se zaměříme na:

* [Co je 'Internet věcí'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT zařízení](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Nastavení vašeho zařízení](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Aplikace IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Příklady IoT zařízení, která můžete mít kolem sebe](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Co je 'Internet věcí'?

Termín 'Internet věcí' byl poprvé použit [Kevinem Ashtonem](https://wikipedia.org/wiki/Kevin_Ashton) v roce 1999, aby popsal propojení internetu s fyzickým světem prostřednictvím senzorů. Od té doby se tento termín používá k označení jakéhokoliv zařízení, které interaguje s fyzickým světem kolem sebe, buď sběrem dat ze senzorů, nebo poskytováním reálných interakcí prostřednictvím aktuátorů (zařízení, která něco dělají, například zapínají spínač nebo rozsvěcují LED), obvykle připojených k jiným zařízením nebo internetu.

> **Senzory** shromažďují informace ze světa, například měří rychlost, teplotu nebo polohu.
>
> **Aktuátory** převádějí elektrické signály na reálné interakce, jako je aktivace spínače, rozsvícení světel, vydávání zvuků nebo odesílání řídicích signálů jinému hardwaru, například k zapnutí elektrické zásuvky.

IoT jako technologická oblast zahrnuje více než jen zařízení - zahrnuje cloudové služby, které mohou zpracovávat data ze senzorů nebo odesílat požadavky aktuátorům připojeným k IoT zařízením. Zahrnuje také zařízení, která nemají nebo nepotřebují připojení k internetu, často označovaná jako edge zařízení. Tato zařízení mohou sama zpracovávat a reagovat na data ze senzorů, obvykle pomocí AI modelů trénovaných v cloudu.

IoT je rychle rostoucí technologická oblast. Odhaduje se, že do konce roku 2020 bylo nasazeno a připojeno k internetu 30 miliard IoT zařízení. Do budoucna se odhaduje, že do roku 2025 budou IoT zařízení shromažďovat téměř 80 zettabytů dat, což je 80 bilionů gigabajtů. To je obrovské množství dat!

![Graf zobrazující aktivní IoT zařízení v průběhu času, s rostoucím trendem od méně než 5 miliard v roce 2015 až po více než 30 miliard v roce 2025](../../../../../images/connected-iot-devices.svg)

✅ Udělejte si malý průzkum: Kolik dat generovaných IoT zařízeními je skutečně využito a kolik je zbytečných? Proč je tolik dat ignorováno?

Tato data jsou klíčem k úspěchu IoT. Abyste byli úspěšným IoT vývojářem, musíte pochopit, jaká data potřebujete shromažďovat, jak je shromažďovat, jak na jejich základě činit rozhodnutí a jak tato rozhodnutí použít k interakci s fyzickým světem, pokud je to potřeba.

## IoT zařízení

**T** v IoT znamená **Things** - zařízení, která interagují s fyzickým světem kolem sebe buď sběrem dat ze senzorů, nebo poskytováním reálných interakcí prostřednictvím aktuátorů.

Zařízení pro produkční nebo komerční použití, jako jsou spotřebitelské fitness trackery nebo průmyslové řídicí jednotky strojů, jsou obvykle vyráběna na míru. Používají vlastní obvodové desky, možná i vlastní procesory, navržené tak, aby splňovaly požadavky konkrétního úkolu, ať už jde o dostatečně malou velikost, aby se vešla na zápěstí, nebo o odolnost vůči vysokým teplotám, stresu nebo vibracím v továrním prostředí.

Jako vývojář, který se učí o IoT nebo vytváří prototyp zařízení, budete potřebovat vývojářskou sadu. Tyto sady jsou univerzální IoT zařízení navržená pro vývojáře, často s funkcemi, které byste na produkčním zařízení neměli, jako jsou externí piny pro připojení senzorů nebo aktuátorů, hardware pro podporu ladění nebo další zdroje, které by při velké výrobní sérii zbytečně zvyšovaly náklady.

Tyto vývojářské sady obvykle spadají do dvou kategorií - mikrokontroléry a jednodeskové počítače. Ty budou představeny zde, a podrobněji se jim budeme věnovat v další lekci.

> 💁 Váš telefon může být také považován za univerzální IoT zařízení, s vestavěnými senzory a aktuátory, přičemž různé aplikace využívají senzory a aktuátory různými způsoby s různými cloudovými službami. Dokonce můžete najít některé IoT tutoriály, které používají aplikaci v telefonu jako IoT zařízení.

### Mikrokontroléry

Mikrokontrolér (také označovaný jako MCU, což je zkratka pro microcontroller unit) je malý počítač skládající se z:

🧠 Jednoho nebo více centrálních procesorových jednotek (CPU) - "mozku" mikrokontroléru, který spouští váš program

💾 Paměti (RAM a programové paměti) - kde je uložen váš program, data a proměnné

🔌 Programovatelných vstupních/výstupních (I/O) připojení - pro komunikaci s externími periferiemi (připojenými zařízeními), jako jsou senzory a aktuátory

Mikrokontroléry jsou obvykle nízkonákladová výpočetní zařízení, přičemž průměrné ceny těch, které se používají v zakázkovém hardwaru, klesají na přibližně 0,50 USD, a některá zařízení jsou tak levná jako 0,03 USD. Vývojářské sady mohou začínat na ceně 4 USD, přičemž náklady rostou s přidáváním dalších funkcí. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), vývojářská sada mikrokontroléru od [Seeed studios](https://www.seeedstudio.com), která má senzory, aktuátory, WiFi a obrazovku, stojí přibližně 30 USD.

![Wio Terminal](../../../../../translated_images/cs/wio-terminal.b8299ee16587db9a.webp)

> 💁 Při hledání mikrokontrolérů na internetu buďte opatrní při hledání termínu **MCU**, protože vám to může přinést mnoho výsledků týkajících se Marvel Cinematic Universe, nikoliv mikrokontrolérů.

Mikrokontroléry jsou navrženy tak, aby byly programovány pro omezený počet velmi specifických úkolů, spíše než aby byly univerzálními počítači jako PC nebo Mac. Kromě velmi specifických scénářů k nim nemůžete připojit monitor, klávesnici a myš a používat je pro obecné úkoly.

Vývojářské sady mikrokontrolérů obvykle přicházejí s dalšími vestavěnými senzory a aktuátory. Většina desek bude mít jeden nebo více LED diod, které můžete programovat, spolu s dalšími zařízeními, jako jsou standardní konektory pro přidávání dalších senzorů nebo aktuátorů pomocí různých ekosystémů výrobců nebo vestavěné senzory (obvykle ty nejoblíbenější, jako jsou teplotní senzory). Některé mikrokontroléry mají vestavěnou bezdrátovou konektivitu, jako je Bluetooth nebo WiFi, nebo mají na desce další mikrokontroléry, které tuto konektivitu přidávají.

> 💁 Mikrokontroléry se obvykle programují v jazyce C/C++.

### Jednodeskové počítače

Jednodeskový počítač je malé výpočetní zařízení, které má všechny prvky kompletního počítače obsažené na jedné malé desce. Tato zařízení mají specifikace blízké stolnímu nebo přenosnému PC nebo Macu, běží na plnohodnotném operačním systému, ale jsou malá, spotřebovávají méně energie a jsou podstatně levnější.

![Raspberry Pi 4](../../../../../translated_images/cs/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi je jedním z nejoblíbenějších jednodeskových počítačů.

Stejně jako mikrokontrolér mají jednodeskové počítače CPU, paměť a vstupní/výstupní piny, ale mají další funkce, jako je grafický čip umožňující připojení monitorů, audio výstupy a USB porty pro připojení klávesnic, myší a dalších standardních USB zařízení, jako jsou webkamery nebo externí úložiště. Programy jsou ukládány na SD karty nebo pevné disky spolu s operačním systémem, místo paměťového čipu vestavěného do desky.

> 🎓 Jednodeskový počítač si můžete představit jako menší, levnější verzi PC nebo Macu, na kterém právě čtete tento text, s přidanými GPIO (general-purpose input/output) piny pro interakci se senzory a aktuátory.

Jednodeskové počítače jsou plnohodnotné počítače, takže je lze programovat v jakémkoliv jazyce. IoT zařízení se obvykle programují v Pythonu.

### Výběr hardwaru pro další lekce

Všechny následující lekce zahrnují úkoly využívající IoT zařízení k interakci s fyzickým světem a komunikaci s cloudem. Každá lekce podporuje 3 možnosti zařízení - Arduino (s využitím Seeed Studios Wio Terminal), nebo jednodeskový počítač, buď fyzické zařízení (Raspberry Pi 4) nebo virtuální jednodeskový počítač běžící na vašem PC nebo Macu.

Můžete si přečíst o hardwaru potřebném k dokončení všech úkolů v [průvodci hardwarem](../../../hardware.md).

> 💁 Nemusíte si kupovat žádný IoT hardware, abyste mohli dokončit úkoly, vše můžete provést pomocí virtuálního jednodeskového počítače.

Výběr hardwaru závisí na vás - záleží na tom, co máte k dispozici doma nebo ve škole, a jaký programovací jazyk znáte nebo se plánujete naučit. Obě varianty hardwaru budou používat stejný ekosystém senzorů, takže pokud začnete jednou cestou, můžete přejít na druhou, aniž byste museli vyměnit většinu vybavení. Virtuální jednodeskový počítač bude ekvivalentem učení na Raspberry Pi, přičemž většina kódu bude přenositelná na Pi, pokud si nakonec pořídíte zařízení a senzory.

### Arduino vývojářská sada

Pokud vás zajímá vývoj mikrokontrolérů, můžete úkoly dokončit pomocí zařízení Arduino. Budete potřebovat základní znalosti programování v C/C++, protože lekce budou učit pouze kód relevantní pro Arduino framework, senzory a aktuátory, které se používají, a knihovny, které interagují s cloudem.

Úkoly budou využívat [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) s [PlatformIO rozšířením pro vývoj mikrokontrolérů](https://platformio.org). Můžete také použít Arduino IDE, pokud máte s tímto nástrojem zkušenosti, protože instrukce nebudou poskytovány.

### Jednodeskový počítač vývojářská sada

Pokud vás zajímá vývoj IoT pomocí jednodeskových počítačů, můžete úkoly dokončit pomocí Raspberry Pi nebo virtuálního zařízení běžícího na vašem PC nebo Macu.

Budete potřebovat základní znalosti programování v Pythonu, protože lekce budou učit pouze kód relevantní pro senzory a aktuátory, které se používají, a knihovny, které interagují s cloudem.

> 💁 Pokud se chcete naučit programovat v Pythonu, podívejte se na následující dvě série videí:
>
> * [Python pro začátečníky](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Více Pythonu pro začátečníky](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Úkoly budou využívat [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Pokud používáte Raspberry Pi, můžete buď spustit Pi pomocí plné desktopové verze Raspberry Pi OS a provádět veškeré kódování přímo na Pi pomocí [verze VS Code pro Raspberry Pi OS](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), nebo spustit Pi jako zařízení bez monitoru a kódovat z vašeho PC nebo Macu pomocí VS Code s [Remote SSH rozšířením](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), které vám umožní připojit se k Pi a upravovat, ladit a spouštět kód, jako byste kódovali přímo na něm.

Pokud použijete možnost virtuálního zařízení, budete kódovat přímo na vašem počítači. Místo přístupu k senzorům a aktuátorům budete používat nástroj k simulaci tohoto hardwaru, který poskytuje hodnoty senzorů, které můžete definovat, a zobrazuje výsledky aktuátorů na obrazovce.

## Nastavení vašeho zařízení

Než začnete programovat vaše IoT zařízení, budete muset provést malé množství nastavení. Postupujte podle relevantních instrukcí níže v závislosti na tom, které zařízení budete používat.
💁 Pokud ještě nemáte zařízení, podívejte se na [průvodce hardwarem](../../../hardware.md), který vám pomůže rozhodnout, jaké zařízení budete používat a jaký další hardware je třeba zakoupit. Není nutné kupovat hardware, protože všechny projekty lze spustit na virtuálním hardwaru.
Tyto pokyny zahrnují odkazy na webové stránky třetích stran od tvůrců hardwaru nebo nástrojů, které budete používat. To má zajistit, že vždy budete mít nejaktuálnější pokyny pro různé nástroje a hardware.

Projděte si příslušný průvodce, nastavte své zařízení a dokončete projekt „Hello World“. To bude první krok při vytváření IoT nočního světla během 4 lekcí v této úvodní části.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Jednodeskový počítač - Raspberry Pi](pi.md)
* [Jednodeskový počítač - Virtuální zařízení](virtual-device.md)

✅ Budete používat VS Code jak pro Arduino, tak pro jednodeskové počítače. Pokud jste ho dosud nepoužívali, přečtěte si více na [webu VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## Aplikace IoT

IoT pokrývá širokou škálu použití, rozdělených do několika hlavních skupin:

* Spotřebitelské IoT
* Komerční IoT
* Průmyslové IoT
* IoT pro infrastrukturu

✅ Udělejte si malý průzkum: Pro každou z níže popsaných oblastí najděte jeden konkrétní příklad, který není uveden v textu.

### Spotřebitelské IoT

Spotřebitelské IoT se týká IoT zařízení, která si spotřebitelé kupují a používají doma. Některá z těchto zařízení jsou neuvěřitelně užitečná, jako například chytré reproduktory, chytré topné systémy a robotické vysavače. Jiná jsou sporná, co se týče jejich užitečnosti, například hlasem ovládané kohoutky, které pak nelze vypnout, protože hlasové ovládání vás neslyší přes zvuk tekoucí vody.

Spotřebitelská IoT zařízení umožňují lidem dosáhnout více ve svém okolí, zejména 1 miliardě lidí, kteří mají nějaké postižení. Robotické vysavače mohou zajistit čisté podlahy lidem s omezenou pohyblivostí, kteří si nemohou sami vysávat. Hlasem ovládané trouby umožňují lidem s omezeným zrakem nebo motorickou kontrolou zapnout troubu pouze hlasem. Zdravotní monitory umožňují pacientům sledovat chronické stavy s pravidelnějšími a podrobnějšími aktualizacemi jejich zdravotního stavu. Tato zařízení se stávají tak běžnými, že je dokonce používají i malé děti jako součást svého každodenního života, například studenti, kteří během pandemie COVID využívali chytrá domácí zařízení k nastavování časovačů na školní úkoly nebo alarmů, aby si připomněli nadcházející online hodiny.

✅ Jaká spotřebitelská IoT zařízení máte u sebe nebo doma?

### Komerční IoT

Komerční IoT zahrnuje použití IoT na pracovišti. V kancelářském prostředí mohou být přítomnostní senzory a detektory pohybu využívány k řízení osvětlení a vytápění, aby se světla a topení zapínaly pouze tehdy, když jsou potřeba, což snižuje náklady a emise uhlíku. Ve výrobním závodě mohou IoT zařízení monitorovat bezpečnostní rizika, například pracovníky bez ochranných přileb nebo hluk, který dosáhl nebezpečné úrovně. V maloobchodě mohou IoT zařízení měřit teplotu chladicích zařízení a upozornit majitele obchodu, pokud lednice nebo mrazák překročí požadovaný teplotní rozsah, nebo mohou monitorovat položky na regálech a nasměrovat zaměstnance k doplnění vyprodaného zboží. Dopravní průmysl stále více spoléhá na IoT k monitorování polohy vozidel, sledování ujetých kilometrů na silnici pro účely zpoplatnění, sledování dodržování přestávek řidičů nebo upozorňování personálu, když se vozidlo blíží k depu, aby se připravilo na nakládku nebo vykládku.

✅ Jaká komerční IoT zařízení máte ve škole nebo na pracovišti?

### Průmyslové IoT (IIoT)

Průmyslové IoT, nebo IIoT, je použití IoT zařízení k řízení a správě strojů ve velkém měřítku. To zahrnuje širokou škálu použití, od továren po digitální zemědělství.

Továrny používají IoT zařízení mnoha různými způsoby. Stroje mohou být monitorovány pomocí více senzorů, které sledují například teplotu, vibrace a rychlost otáčení. Tato data mohou být sledována, aby bylo možné stroj zastavit, pokud překročí určité tolerance – například pokud se příliš zahřeje, může být automaticky vypnut. Tato data mohou být také shromažďována a analyzována v průběhu času pro prediktivní údržbu, kdy modely AI analyzují data vedoucí k poruše a používají je k předpovědi dalších poruch před jejich výskytem.

Digitální zemědělství je důležité, pokud má planeta uživit rostoucí populaci, zejména 2 miliardy lidí v 500 milionech domácností, které přežívají na [subsistenčním zemědělství](https://wikipedia.org/wiki/Subsistence_agriculture). Digitální zemědělství může zahrnovat od několika levných senzorů až po rozsáhlé komerční systémy. Farmář může začít sledováním teplot a využíváním [stupňů růstu](https://wikipedia.org/wiki/Growing_degree-day) k předpovědi, kdy bude plodina připravena ke sklizni. Může připojit monitorování vlhkosti půdy k automatizovaným zavlažovacím systémům, aby rostlinám dodal tolik vody, kolik potřebují, ale ne více, čímž zajistí, že plodiny nevyschnou, aniž by se plýtvalo vodou. Farmáři dokonce jdou ještě dál a používají drony, satelitní data a AI k monitorování růstu plodin, nemocí a kvality půdy na obrovských plochách zemědělské půdy.

✅ Jaká další IoT zařízení by mohla pomoci farmářům?

### IoT pro infrastrukturu

IoT pro infrastrukturu zahrnuje monitorování a řízení místní i globální infrastruktury, kterou lidé používají každý den.

[Chytrá města](https://wikipedia.org/wiki/Smart_city) jsou městské oblasti, které využívají IoT zařízení ke sběru dat o městě a jejich využití ke zlepšení fungování města. Tato města jsou obvykle řízena spoluprací mezi místními vládami, akademickou sférou a místními podniky, sledují a spravují různé aspekty od dopravy po parkování a znečištění. Například v Kodani, Dánsku, je znečištění ovzduší důležité pro místní obyvatele, takže se měří a data se používají k poskytování informací o nejčistších trasách pro cyklistiku a jogging.

[Chytré elektrické sítě](https://wikipedia.org/wiki/Smart_grid) umožňují lepší analýzu poptávky po elektřině díky sběru údajů o spotřebě na úrovni jednotlivých domácností. Tato data mohou vést k rozhodnutím na úrovni země, například kde postavit nové elektrárny, a na osobní úrovni poskytovat uživatelům přehled o tom, kolik energie spotřebovávají, kdy ji spotřebovávají, a dokonce návrhy, jak snížit náklady, například nabíjením elektrických aut v noci.

✅ Pokud byste mohli přidat IoT zařízení k měření čehokoli ve vašem okolí, co by to bylo?

## Příklady IoT zařízení, která můžete mít kolem sebe

Byli byste překvapeni, kolik IoT zařízení máte kolem sebe. Píšu to z domova a mám následující zařízení připojená k internetu s chytrými funkcemi, jako je ovládání aplikací, hlasové ovládání nebo schopnost posílat data na můj telefon:

* Více chytrých reproduktorů
* Lednice, myčka, trouba a mikrovlnná trouba
* Monitor elektřiny pro solární panely
* Chytré zásuvky
* Videozvonek a bezpečnostní kamery
* Chytrý termostat s více chytrými senzory v místnostech
* Otevírač garážových vrat
* Domácí zábavní systémy a hlasem ovládané televize
* Světla
* Fitness a zdravotní trackery

Všechna tato zařízení mají senzory a/nebo akční členy a komunikují s internetem. Mohu ze svého telefonu zjistit, zda jsou garážová vrata otevřená, a požádat chytrý reproduktor, aby je zavřel. Mohu je dokonce nastavit na časovač, aby se automaticky zavřela, pokud zůstanou otevřená přes noc. Když zazvoní zvonek, mohu ze svého telefonu vidět, kdo je u dveří, a mluvit s nimi prostřednictvím reproduktoru a mikrofonu zabudovaného do zvonku. Mohu sledovat hladinu glukózy v krvi, srdeční tep a spánkové vzorce, hledat vzorce v datech a zlepšovat své zdraví. Mohu ovládat světla přes cloud a sedět ve tmě, když mi vypadne internetové připojení.

---

## 🚀 Výzva

Vyjmenujte co nejvíce IoT zařízení, která máte doma, ve škole nebo na pracovišti – možná jich je více, než si myslíte!

## Kvíz po přednášce

[Kvíz po přednášce](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Přehled a samostudium

Přečtěte si o výhodách a neúspěších projektů spotřebitelského IoT. Projděte zpravodajské weby a najděte články o případech, kdy se něco pokazilo, například problémy s ochranou soukromí, hardwarové problémy nebo problémy způsobené nedostatkem konektivity.

Některé příklady:

* Podívejte se na Twitter účet **[Internet of Sh*t](https://twitter.com/internetofshit)** *(varování: vulgarity)* pro dobré příklady neúspěchů spotřebitelského IoT.
* [c|net - Můj Apple Watch mi zachránil život: 5 lidí sdílí své příběhy](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - Technik ADT se přiznal ke špehování zákaznických kamerových záznamů po celé roky](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(varování: nechtěné voyeurství)*

## Zadání

[Prozkoumejte IoT projekt](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.