# Interakce s fyzickým světem pomocí senzorů a akčních členů

![Přehled lekce ve formě sketchnote](../../../../../translated_images/cs/lesson-3.cc3b7b4cd646de59.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

Tato lekce byla součástí série [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) od [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekce byla rozdělena do dvou videí - hodinové lekce a hodinové konzultace, kde se podrobněji probíraly části lekce a odpovídalo se na otázky.

[![Lekce 3: Interakce s fyzickým světem pomocí senzorů a akčních členů](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Lekce 3: Interakce s fyzickým světem pomocí senzorů a akčních členů - Konzultace](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Klikněte na obrázky výše pro zhlédnutí videí

## Kvíz před lekcí

[Kvíz před lekcí](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Úvod

Tato lekce vás seznámí se dvěma důležitými koncepty pro vaše IoT zařízení - senzory a akčními členy. Prakticky si je vyzkoušíte, přidáte světelný senzor do svého IoT projektu a poté přidáte LED diodu, která bude ovládána úrovní světla, čímž vytvoříte noční světlo.

V této lekci se budeme zabývat:

* [Co jsou senzory?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Použití senzoru](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Typy senzorů](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Co jsou akční členy?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Použití akčního členu](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Typy akčních členů](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Co jsou senzory?

Senzory jsou hardwarová zařízení, která snímají fyzický svět - měří jednu nebo více vlastností svého okolí a posílají informace do IoT zařízení. Existuje obrovské množství senzorů, protože je možné měřit mnoho různých věcí, od přírodních vlastností, jako je teplota vzduchu, až po fyzické interakce, jako je pohyb.

Mezi běžné senzory patří:

* Teplotní senzory - měří teplotu vzduchu nebo teplotu prostředí, ve kterém se nacházejí. Pro hobby projekty a vývojáře jsou často kombinovány s měřením tlaku vzduchu a vlhkosti v jednom senzoru.
* Tlačítka - detekují, kdy jsou stisknuta.
* Světelné senzory - detekují úroveň světla a mohou být zaměřeny na konkrétní barvy, UV světlo, IR světlo nebo obecné viditelné světlo.
* Kamery - snímají vizuální reprezentaci světa prostřednictvím fotografií nebo streamování videa.
* Akcelerometry - detekují pohyb v několika směrech.
* Mikrofony - snímají zvuk, buď obecnou úroveň zvuku, nebo směrový zvuk.

✅ Udělejte si průzkum. Jaké senzory má váš telefon?

Všechny senzory mají jedno společné - převádějí to, co snímají, na elektrický signál, který může být interpretován IoT zařízením. Jak je tento elektrický signál interpretován, závisí na senzoru a také na komunikačním protokolu, který se používá k přenosu dat do IoT zařízení.

## Použití senzoru

Postupujte podle příslušného návodu níže a přidejte senzor do svého IoT zařízení:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Jednodeskový počítač - Raspberry Pi](pi-sensor.md)
* [Jednodeskový počítač - Virtuální zařízení](virtual-device-sensor.md)

## Typy senzorů

Senzory mohou být buď analogové, nebo digitální.

### Analogové senzory

Některé z nejzákladnějších senzorů jsou analogové. Tyto senzory přijímají napětí z IoT zařízení, senzorové komponenty toto napětí upravují a napětí, které senzor vrací, je měřeno pro získání hodnoty senzoru.

> 🎓 Napětí je měřítkem toho, jak velký "tah" je potřeba k přenosu elektřiny z jednoho místa na druhé, například z kladného pólu baterie na záporný pól. Například standardní AA baterie má 1,5V (V je symbol pro volty) a může tlačit elektřinu silou 1,5V z kladného pólu na záporný. Různé elektrické komponenty vyžadují různá napětí, například LED dioda může svítit při napětí mezi 2-3V, ale 100W žárovka by potřebovala 240V. Více o napětí si můžete přečíst na [stránce o napětí na Wikipedii](https://wikipedia.org/wiki/Voltage).

Jedním z příkladů je potenciometr. Jedná se o otočný knoflík, který můžete otáčet mezi dvěma polohami, a senzor měří úhel otočení.

![Potenciometr nastavený na střední hodnotu, přijímá 5 voltů a vrací 3,8 voltů](../../../../../translated_images/cs/potentiometer.35a348b9ce22f6ec.webp)

IoT zařízení pošle elektrický signál do potenciometru s napětím, například 5 voltů (5V). Jakmile je potenciometr nastaven, mění napětí, které vychází na druhé straně. Představte si potenciometr označený jako knoflík, který jde od 0 do [11](https://wikipedia.org/wiki/Up_to_eleven), například jako ovladač hlasitosti na zesilovači. Když je potenciometr v poloze úplně vypnuto (0), vychází 0V (0 voltů). Když je v poloze úplně zapnuto (11), vychází 5V (5 voltů).

> 🎓 Toto je zjednodušení, více o potenciometrech a proměnných odporech si můžete přečíst na [stránce o potenciometrech na Wikipedii](https://wikipedia.org/wiki/Potentiometer).

Napětí, které vychází ze senzoru, je poté čteno IoT zařízením a zařízení na něj může reagovat. V závislosti na senzoru může být toto napětí libovolná hodnota nebo může odpovídat standardní jednotce. Například analogový teplotní senzor založený na [termistoru](https://wikipedia.org/wiki/Thermistor) mění svůj odpor v závislosti na teplotě. Výstupní napětí může být poté převedeno na teplotu v Kelvinech a odpovídajícím způsobem na °C nebo °F pomocí výpočtů v kódu.

✅ Co si myslíte, že se stane, pokud senzor vrátí vyšší napětí, než bylo odesláno (například z externího zdroje napájení)? ⛔️ NEZKOUŠEJTE to.

#### Převod z analogu na digitál

IoT zařízení jsou digitální - nemohou pracovat s analogovými hodnotami, pouze s 0 a 1. To znamená, že analogové hodnoty senzorů musí být převedeny na digitální signál, než mohou být zpracovány. Mnoho IoT zařízení má převodníky z analogu na digitál (ADC), které převádějí analogové vstupy na digitální reprezentace jejich hodnot. Senzory mohou také pracovat s ADC prostřednictvím připojovací desky. Například v ekosystému Seeed Grove s Raspberry Pi se analogové senzory připojují ke specifickým portům na 'hat', který sedí na Pi a je připojen k GPIO pinům Pi. Tento hat má ADC, který převádí napětí na digitální signál, který může být odeslán z GPIO pinů Pi.

Představte si, že máte analogový světelný senzor připojený k IoT zařízení, které používá 3,3V a vrací hodnotu 1V. Tento 1V nemá v digitálním světě žádný význam, takže musí být převeden. Napětí bude převedeno na analogovou hodnotu pomocí stupnice v závislosti na zařízení a senzoru. Jedním z příkladů je světelný senzor Seeed Grove, který vrací hodnoty od 0 do 1 023. Pro tento senzor běžící na 3,3V by výstup 1V odpovídal hodnotě 300. IoT zařízení nemůže pracovat s hodnotou 300 jako s analogovou hodnotou, takže hodnota by byla převedena na `0000000100101100`, což je binární reprezentace čísla 300 vytvořená Grove hatem. Tato hodnota by pak byla zpracována IoT zařízením.

✅ Pokud neznáte binární soustavu, udělejte si malý průzkum a zjistěte, jak jsou čísla reprezentována pomocí 0 a 1. [Úvod do binární soustavy na BBC Bitesize](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) je skvělým místem, kde začít.

Z pohledu programování je toto obvykle řešeno knihovnami, které jsou dodávány se senzory, takže se o tento převod nemusíte starat sami. Pro světelný senzor Grove byste použili Python knihovnu a zavolali vlastnost `light`, nebo použili Arduino knihovnu a zavolali `analogRead` pro získání hodnoty 300.

### Digitální senzory

Digitální senzory, stejně jako analogové senzory, detekují svět kolem sebe pomocí změn elektrického napětí. Rozdíl je v tom, že vracejí digitální signál, buď měřením pouze dvou stavů, nebo použitím vestavěného ADC. Digitální senzory jsou stále běžnější, aby se předešlo nutnosti používat ADC buď na připojovací desce, nebo přímo na IoT zařízení.

Nejjednodušším digitálním senzorem je tlačítko nebo spínač. Jedná se o senzor se dvěma stavy, zapnuto nebo vypnuto.

![Tlačítko přijímá 5 voltů. Když není stisknuto, vrací 0 voltů, když je stisknuto, vrací 5 voltů](../../../../../translated_images/cs/button.eadb560b77ac45e5.webp)

Piny na IoT zařízeních, jako jsou GPIO piny, mohou tento signál přímo měřit jako 0 nebo 1. Pokud je napětí odeslané stejné jako napětí vrácené, hodnota je 1, jinak je hodnota 0. Není potřeba signál převádět, může být pouze 1 nebo 0.

> 💁 Napětí nikdy není přesné, zejména protože komponenty v senzoru mají určitý odpor, takže obvykle existuje tolerance. Například GPIO piny na Raspberry Pi pracují na 3,3V a čtou návratový signál nad 1,8V jako 1, pod 1,8V jako 0.

* 3,3V jde do tlačítka. Tlačítko je vypnuté, takže vychází 0V, což dává hodnotu 0.
* 3,3V jde do tlačítka. Tlačítko je zapnuté, takže vychází 3,3V, což dává hodnotu 1.

Pokročilejší digitální senzory čtou analogové hodnoty a poté je převádějí pomocí vestavěných ADC na digitální signály. Například digitální teplotní senzor stále používá termočlánek stejným způsobem jako analogový senzor a stále měří změnu napětí způsobenou odporem termočlánku při aktuální teplotě. Místo vrácení analogové hodnoty a spoléhání se na zařízení nebo připojovací desku pro převod na digitální signál, vestavěný ADC v senzoru hodnotu převede a odešle ji jako sérii 0 a 1 do IoT zařízení. Tyto 0 a 1 jsou odesílány stejným způsobem jako digitální signál pro tlačítko, kde 1 znamená plné napětí a 0 znamená 0V.

![Digitální teplotní senzor převádí analogové čtení na binární data s 0 jako 0 voltů a 1 jako 5 voltů před odesláním do IoT zařízení](../../../../../translated_images/cs/temperature-as-digital.85004491b977bae1.webp)

Odesílání digitálních dat umožňuje senzorům být složitější a odesílat podrobnější data, dokonce i šifrovaná data pro bezpečné senzory. Jedním z příkladů je kamera. Jedná se o senzor, který zachycuje obraz a odesílá jej jako digitální data obsahující tento obraz, obvykle v komprimovaném formátu, jako je JPEG, aby jej mohlo číst IoT zařízení. Může dokonce streamovat video zachycením obrazů a odesíláním buď kompletního obrazu snímek po snímku, nebo komprimovaného video streamu.

## Co jsou akční členy?

Akční členy jsou opakem senzorů - převádějí elektrický signál z vašeho IoT zařízení na interakci s fyzickým světem, jako je vyzařování světla nebo zvuku, nebo pohyb motoru.

Mezi běžné akční členy patří:

* LED - vyzařují světlo, když jsou zapnuté.
* Reproduktor - vyzařují zvuk na základě signálu, od jednoduchého bzučáku po reproduktor, který může přehrávat hudbu.
* Krokový motor - převádí signál na definované množství rotace, například otočení knoflíku o 90°.
* Relé - jedná se o spínače, které lze zapnout nebo vypnout elektrickým signálem. Umožňují malé napětí z IoT zařízení zapnout větší napětí.
* Obrazovky - jedná se o složitější akční členy, které zobrazují informace na více segmentovém displeji. Obrazovky se liší od jednoduchých LED displejů po vysokorozlišení video monitory.

✅ Udělejte si průzkum. Jaké akční členy má váš telefon?

## Použití akčního členu

Postupujte podle příslušného návodu níže a přidejte akční člen do svého IoT zařízení, který bude ovládán senzorem, abyste vytvořili IoT noční světlo. Bude shromažďovat úrovně světla ze světelného senzoru a používat akční člen ve formě LED diody k vyzařování světla, když je detekovaná úroveň světla příliš nízká.

![Diagram úkolu ukazující čtení a kontrolu úrovní světla a ovládání LED](../../../../../translated_images/cs/assignment-1-flow.7552a51acb1a5ec8.webp)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Jednodeskový počítač - Raspberry Pi](pi-actuator.md)
* [Jednodeskový počítač - Virtuální zařízení](virtual-device-actuator.md)

## Typy akčních členů

Stejně jako senzory, akční členy mohou být buď analogové, nebo digitální.

### Analogové akční členy

Analogové akční členy přijímají analogový signál a převádějí jej na nějakou formu interakce, kde se interakce mění na základě dodaného napětí.

Jedním z příkladů je stmívatelné světlo, například to, které můžete mít doma. Množství dodaného napětí určuje, jak jasně svítí.
![Světlo ztlumené při nízkém napětí a jasnější při vyšším napětí](../../../../../translated_images/cs/dimmable-light.9ceffeb195dec1a8.webp)

Stejně jako u senzorů, skutečné IoT zařízení pracuje s digitálními signály, nikoli analogovými. To znamená, že k odeslání analogového signálu potřebuje IoT zařízení převodník z digitálního na analogový signál (DAC), buď přímo na IoT zařízení, nebo na připojovací desce. Ten převede 0 a 1 z IoT zařízení na analogové napětí, které může aktuátor využít.

✅ Co si myslíte, že se stane, pokud IoT zařízení pošle vyšší napětí, než aktuátor zvládne?
⛔️ NEZKOUŠEJTE to.

#### Pulzně šířková modulace

Další možností, jak převést digitální signály z IoT zařízení na analogový signál, je pulzně šířková modulace (PWM). Ta zahrnuje odesílání mnoha krátkých digitálních impulsů, které se chovají jako analogový signál.

Například pomocí PWM můžete ovládat rychlost motoru.

Představte si, že ovládáte motor s napájením 5V. Pošlete krátký impuls do motoru, přepnete napětí na vysoké (5V) na dvě setiny sekundy (0,02s). Během této doby se motor může otočit o jednu desetinu otáčky, tedy o 36°. Signál se poté na dvě setiny sekundy (0,02s) přeruší, čímž se odešle nízký signál (0V). Každý cyklus zapnutí a vypnutí trvá 0,04s. Cyklus se poté opakuje.

![Pulzně šířková modulace otáčení motoru při 150 otáčkách za minutu](../../../../../translated_images/cs/pwm-motor-150rpm.83347ac04ca38482.webp)

To znamená, že za jednu sekundu máte 25 impulsů 5V o délce 0,02s, které otáčejí motorem, každý následovaný 0,02s pauzou 0V, kdy se motor neotáčí. Každý impuls otočí motor o jednu desetinu otáčky, což znamená, že motor dokončí 2,5 otáčky za sekundu. Použili jste digitální signál k otáčení motoru rychlostí 2,5 otáčky za sekundu, tedy 150 [otáček za minutu](https://wikipedia.org/wiki/Revolutions_per_minute) (nestandardní měření rychlosti otáčení).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Když je PWM signál zapnutý polovinu času a vypnutý polovinu času, označuje se to jako [50% pracovní cyklus](https://wikipedia.org/wiki/Duty_cycle). Pracovní cykly se měří jako procento času, kdy je signál ve stavu zapnuto ve srovnání se stavem vypnuto.

![Pulzně šířková modulace otáčení motoru při 75 otáčkách za minutu](../../../../../translated_images/cs/pwm-motor-75rpm.a5e4c939934b6e14.webp)

Rychlost motoru můžete změnit změnou délky impulsů. Například u stejného motoru můžete zachovat stejnou délku cyklu 0,04s, přičemž délku zapnutého impulsu zkrátíte na polovinu (0,01s) a délku vypnutého impulsu prodloužíte na 0,03s. Počet impulsů za sekundu (25) zůstává stejný, ale každý zapnutý impuls je poloviční. Poloviční impuls otočí motor o jednu dvacetinu otáčky, a při 25 impulsech za sekundu motor dokončí 1,25 otáčky za sekundu, tedy 75 otáček za minutu. Změnou délky impulsů digitálního signálu jste snížili rychlost analogového motoru na polovinu.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Jak byste zajistili plynulé otáčení motoru, zejména při nízkých rychlostech? Použili byste malý počet dlouhých impulsů s dlouhými pauzami, nebo mnoho velmi krátkých impulsů s velmi krátkými pauzami?

> 💁 Některé senzory také používají PWM k převodu analogových signálů na digitální.

> 🎓 Více o pulzně šířkové modulaci si můžete přečíst na [stránce o PWM na Wikipedii](https://wikipedia.org/wiki/Pulse-width_modulation).

### Digitální aktuátory

Digitální aktuátory, stejně jako digitální senzory, mají buď dva stavy ovládané vysokým nebo nízkým napětím, nebo mají vestavěný DAC, který dokáže převést digitální signál na analogový.

Jednoduchým digitálním aktuátorem je LED dioda. Když zařízení pošle digitální signál 1, odešle se vysoké napětí, které LED diodu rozsvítí. Když se pošle digitální signál 0, napětí klesne na 0V a LED dioda se vypne.

![LED dioda je vypnutá při 0 voltech a zapnutá při 5V](../../../../../translated_images/cs/led.ec6d94f66676a174.webp)

✅ Jaké další jednoduché dvoustavové aktuátory vás napadají? Jedním příkladem je solenoid, což je elektromagnet, který lze aktivovat k provádění úkonů, jako je pohyb závory dveří při zamykání/odemykání.

Pokročilejší digitální aktuátory, jako jsou obrazovky, vyžadují, aby digitální data byla odesílána v určitých formátech. Obvykle jsou dodávány s knihovnami, které usnadňují odesílání správných dat pro jejich ovládání.

---

## 🚀 Výzva

Výzva v posledních dvou lekcích byla sepsat co nejvíce IoT zařízení, která máte doma, ve škole nebo na pracovišti, a rozhodnout, zda jsou postavena na mikrokontrolérech, jednodeskových počítačích nebo dokonce na jejich kombinaci.

U každého zařízení, které jste uvedli, jaké senzory a aktuátory jsou k němu připojeny? Jaký je účel každého senzoru a aktuátoru připojeného k těmto zařízením?

## Kvíz po přednášce

[Kvíz po přednášce](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Přehled & Samostudium

* Přečtěte si o elektřině a obvodech na [ThingLearn](http://thinglearn.jenlooper.com/curriculum/).
* Přečtěte si o různých typech teplotních senzorů v [průvodci teplotními senzory od Seeed Studios](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/)
* Přečtěte si o LED diodách na [stránce o LED diodách na Wikipedii](https://wikipedia.org/wiki/Light-emitting_diode)

## Úkol

[Prozkoumejte senzory a aktuátory](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Nenese odpovědnost za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.