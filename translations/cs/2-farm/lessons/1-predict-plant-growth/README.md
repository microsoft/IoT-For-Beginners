<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d105b44deae539165855c976dcdeca99",
  "translation_date": "2025-08-27T23:19:32+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/README.md",
  "language_code": "cs"
}
-->
# Předpověď růstu rostlin pomocí IoT

![Přehled této lekce ve formě sketchnote](../../../../../translated_images/cs/lesson-5.42b234299279d263143148b88ab4583861a32ddb03110c6c1120e41bb88b2592.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

## Kvíz před lekcí

[Kvíz před lekcí](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Úvod

Rostliny potřebují k růstu určité podmínky – vodu, oxid uhličitý, živiny, světlo a teplo. V této lekci se naučíte, jak vypočítat rychlost růstu a zralosti rostlin měřením teploty vzduchu.

V této lekci se zaměříme na:

* [Digitální zemědělství](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Proč je teplota důležitá při zemědělství?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Měření okolní teploty](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Stupně růstu (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Výpočet GDD pomocí dat z teplotního senzoru](../../../../../2-farm/lessons/1-predict-plant-growth)

## Digitální zemědělství

Digitální zemědělství mění způsob, jakým hospodaříme, pomocí nástrojů pro sběr, ukládání a analýzu dat z farmářských činností. Nacházíme se v období, které Světové ekonomické fórum označuje jako „Čtvrtou průmyslovou revoluci“, a vzestup digitálního zemědělství je označován jako „Čtvrtá zemědělská revoluce“ nebo „Zemědělství 4.0“.

> 🎓 Termín digitální zemědělství zahrnuje také celý „zemědělský hodnotový řetězec“, tedy celou cestu od farmy až na stůl. Zahrnuje sledování kvality produktů během přepravy a zpracování, skladové a e-commerce systémy, dokonce i aplikace na pronájem traktorů!

Tyto změny umožňují farmářům zvýšit výnosy, používat méně hnojiv a pesticidů a efektivněji hospodařit s vodou. Ačkoli se tyto technologie primárně využívají v bohatších zemích, senzory a další zařízení postupně zlevňují, což je činí dostupnějšími i v rozvojových zemích.

Některé techniky umožněné digitálním zemědělstvím zahrnují:

* Měření teploty – měření teploty umožňuje farmářům předpovídat růst a zralost rostlin.
* Automatické zavlažování – měření vlhkosti půdy a zapínání zavlažovacích systémů, když je půda příliš suchá, místo zavlažování podle časového plánu. Zavlažování podle času může vést k nedostatečnému zavlažování během horkého a suchého období nebo k přemokření během deště. Zavlažováním pouze tehdy, když to půda potřebuje, mohou farmáři optimalizovat spotřebu vody.
* Ochrana proti škůdcům – farmáři mohou používat kamery na automatizovaných robotech nebo dronech k detekci škůdců a aplikovat pesticidy pouze tam, kde je to nutné, čímž se snižuje množství použitých pesticidů a jejich odtok do místních vodních zdrojů.

✅ Udělejte si průzkum. Jaké další techniky se používají ke zlepšení zemědělských výnosů?

> 🎓 Termín „precizní zemědělství“ označuje pozorování, měření a reakci na potřeby plodin na úrovni jednotlivých polí nebo dokonce jejich částí. To zahrnuje měření hladin vody, živin a škůdců a přesné reakce, například zavlažování pouze malé části pole.

## Proč je teplota důležitá při zemědělství?

Při studiu rostlin se většina studentů učí o nezbytnosti vody, světla, oxidu uhličitého a živin. Rostliny však také potřebují teplo k růstu – proto rostliny kvetou na jaře, když teplota stoupá, proč sněženky nebo narcisy mohou vyrašit brzy během krátkého teplého období, a proč jsou skleníky a pařeniště tak účinné pro růst rostlin.

> 🎓 Skleníky a pařeniště mají podobnou funkci, ale s důležitým rozdílem. Pařeniště jsou uměle vytápěná a umožňují farmářům přesněji kontrolovat teplotu, zatímco skleníky spoléhají na sluneční teplo a obvykle mají pouze okna nebo jiné otvory pro regulaci teploty.

Rostliny mají základní nebo minimální teplotu, optimální teplotu a maximální teplotu, vše založené na průměrných denních teplotách.

* Základní teplota – minimální průměrná denní teplota potřebná pro růst rostliny.
* Optimální teplota – nejlepší průměrná denní teplota pro maximální růst.
* Maximální teplota – maximální teplota, kterou rostlina snese. Nad touto teplotou rostlina zastaví růst, aby šetřila vodu a přežila.

> 💁 Tyto hodnoty jsou průměrné teploty, průměrované mezi denními a nočními teplotami. Rostliny také potřebují různé teploty ve dne a v noci, aby mohly efektivněji fotosyntetizovat a šetřit energii v noci.

Každý druh rostliny má různé hodnoty pro základní, optimální a maximální teplotu. Proto některé rostliny prospívají v horkých zemích a jiné v chladnějších oblastech.

✅ Udělejte si průzkum. Pro jakékoli rostliny ve vaší zahradě, škole nebo místním parku zkuste zjistit jejich základní teplotu.

![Graf ukazující rychlost růstu rostliny, která roste s teplotou, ale klesá, když teplota překročí určitou hranici](../../../../../translated_images/cs/plant-growth-temp-graph.c6d69c9478e6ca83.webp)

Výše uvedený graf ukazuje příklad závislosti rychlosti růstu na teplotě. Do základní teploty nedochází k žádnému růstu. Rychlost růstu se zvyšuje až do optimální teploty, poté klesá po dosažení vrcholu. Při maximální teplotě růst ustává.

Tvar tohoto grafu se liší podle druhu rostliny. Některé mají prudší pokles nad optimální teplotou, jiné mají pomalejší nárůst od základní k optimální teplotě.

> 💁 Aby farmář dosáhl nejlepšího růstu, musí znát tři teplotní hodnoty a pochopit tvar grafu pro rostliny, které pěstuje.

Pokud má farmář kontrolu nad teplotou, například v komerčním pařeništi, může optimalizovat podmínky pro své rostliny. Komerční pařeniště pěstující rajčata například nastaví teplotu na přibližně 25 °C během dne a 20 °C v noci, aby dosáhlo nejrychlejšího růstu.

> 🍅 Kombinace těchto teplot s umělým osvětlením, hnojivy a kontrolovanými úrovněmi CO
Tento kód otevře soubor CSV a na jeho konec přidá nový řádek. Řádek obsahuje aktuální datum a čas formátovaný do podoby čitelné pro člověka, následovaný teplotou získanou z IoT zařízení. Data jsou uložena ve [formátu ISO 8601](https://wikipedia.org/wiki/ISO_8601) s časovým pásmem, ale bez mikrosekund.

1. Spusťte tento kód stejným způsobem jako dříve, ujistěte se, že vaše IoT zařízení odesílá data. V téže složce bude vytvořen soubor CSV nazvaný `temperature.csv`. Pokud jej otevřete, uvidíte datum/čas a měření teploty:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Spusťte tento kód po určitou dobu, abyste zachytili data. Ideálně byste jej měli spustit po celý den, abyste získali dostatek dat pro výpočty GDD.

    
> 💁 Pokud používáte virtuální IoT zařízení, zaškrtněte políčko "náhodně" a nastavte rozsah, abyste se vyhnuli získávání stejné teploty pokaždé, když se vrátí hodnota teploty.
    ![Zaškrtněte políčko "náhodně" a nastavte rozsah](../../../../../translated_images/cs/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.webp) 

    > 💁 Pokud chcete tento kód spustit po celý den, musíte zajistit, aby počítač, na kterém běží váš serverový kód, nepřešel do režimu spánku. To můžete udělat buď změnou nastavení napájení, nebo spuštěním něčeho jako [tento Python skript pro udržení systému aktivního](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Tento kód najdete ve složce [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Úkol - výpočet GDD pomocí uložených dat

Jakmile server zachytí data o teplotě, lze vypočítat GDD pro rostlinu.

Postup, jak to udělat ručně, je následující:

1. Najděte základní teplotu pro rostlinu. Například pro jahody je základní teplota 10 °C.

1. Ze souboru `temperature.csv` najděte nejvyšší a nejnižší teploty za den.

1. Použijte výpočet GDD uvedený dříve k výpočtu GDD.

Například, pokud je nejvyšší teplota za den 25 °C a nejnižší 12 °C:

![GDD = 25 + 12 děleno 2, poté odečtěte 10 z výsledku, což dává 8.5](../../../../../translated_images/cs/gdd-calculation-strawberries.59f57db94b22adb8ff6efb951ace33af104a1c6ccca3ffb0f8169c14cb160c90.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Jahody tedy obdržely **8.5** GDD. Jahody potřebují asi 250 GDD, aby začaly plodit, takže je ještě čas.

---

## 🚀 Výzva

Rostliny potřebují k růstu více než jen teplo. Co dalšího je potřeba?

Pro tyto faktory zjistěte, zda existují senzory, které je mohou měřit. Co třeba akční členy pro kontrolu těchto úrovní? Jak byste sestavili jedno nebo více IoT zařízení pro optimalizaci růstu rostlin?

## Kvíz po přednášce

[Kvíz po přednášce](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Přehled & Samostudium

* Přečtěte si více o digitálním zemědělství na [stránce Wikipedie o digitálním zemědělství](https://wikipedia.org/wiki/Digital_agriculture). Také si přečtěte více o precizním zemědělství na [stránce Wikipedie o precizním zemědělství](https://wikipedia.org/wiki/Precision_agriculture).
* Úplný výpočet stupňů růstu (GDD) je složitější než zjednodušený uvedený zde. Přečtěte si více o složitější rovnici a o tom, jak se vypořádat s teplotami pod základní hodnotou na [stránce Wikipedie o stupních růstu](https://wikipedia.org/wiki/Growing_degree-day).
* Potraviny mohou být v budoucnu nedostatkové, pokud budeme stále používat stejné metody zemědělství. Zjistěte více o vysoce technologických zemědělských technikách v tomto [videu o hi-tech farmách budoucnosti na YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Zadání

[Vizualizujte data GDD pomocí Jupyter Notebooku](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.