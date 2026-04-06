# Trénink detektoru kvality ovoce

![Přehled této lekce ve formě sketchnote](../../../../../translated_images/cs/lesson-15.843d21afdc6fb2bb.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

Toto video poskytuje přehled služby Azure Custom Vision, která bude pokryta v této lekci.

[![Custom Vision – Strojové učení snadno | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 Klikněte na obrázek výše pro zhlédnutí videa

## Kvíz před lekcí

[Kvíz před lekcí](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## Úvod

Nedávný rozmach umělé inteligence (AI) a strojového učení (ML) poskytuje dnešním vývojářům širokou škálu možností. Modely strojového učení mohou být trénovány k rozpoznávání různých objektů na obrázcích, včetně nezralého ovoce, což lze využít v IoT zařízeních k třídění plodin buď během sklizně, nebo při zpracování v továrnách či skladech.

V této lekci se naučíte o klasifikaci obrázků – použití modelů strojového učení k rozlišení mezi obrázky různých objektů. Naučíte se, jak trénovat klasifikátor obrázků, aby rozlišoval mezi dobrým a špatným ovocem, ať už nezralým, přezrálým, poškozeným nebo zkaženým.

V této lekci se zaměříme na:

* [Použití AI a ML k třídění potravin](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Klasifikace obrázků pomocí strojového učení](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Trénink klasifikátoru obrázků](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Testování vašeho klasifikátoru obrázků](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Přeškolení vašeho klasifikátoru obrázků](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## Použití AI a ML k třídění potravin

Nakrmit celosvětovou populaci je obtížné, zejména za cenu, která činí potraviny dostupné pro všechny. Jedním z největších nákladů je pracovní síla, a proto se farmáři stále více obracejí k automatizaci a nástrojům, jako je IoT, aby snížili náklady na práci. Ruční sklizeň je náročná na práci (a často fyzicky vyčerpávající), a proto je nahrazována stroji, zejména v bohatších zemích. Přestože použití strojů ke sklizni snižuje náklady, má to nevýhodu – schopnost třídit potraviny během sklizně.

Ne všechny plodiny dozrávají rovnoměrně. Například rajčata mohou mít na keři stále zelené plody, i když většina je připravena ke sklizni. Přestože je plýtváním sklízet je příliš brzy, je pro farmáře levnější a jednodušší sklidit vše pomocí strojů a později vyřadit nezralé plody.

✅ Podívejte se na různé druhy ovoce nebo zeleniny, ať už rostoucí na farmách, ve vaší zahradě nebo v obchodech. Jsou všechny stejně zralé, nebo vidíte rozdíly?

Rozmach automatizované sklizně přesunul třídění plodin ze sklizně do továren. Potraviny se pohybovaly na dlouhých dopravníkových pásech, kde týmy lidí vybíraly plodiny, které neodpovídaly požadovaným kvalitativním standardům. Sklizeň byla díky strojům levnější, ale stále zde byly náklady na ruční třídění potravin.

![Pokud je detekováno červené rajče, pokračuje na pásu. Pokud je detekováno zelené rajče, páka ho odhodí do odpadního koše.](../../../../../translated_images/cs/optical-tomato-sorting.61aa134bdda4e5b1.webp)

Další evolucí bylo použití strojů k třídění, buď zabudovaných do sklízecích strojů, nebo v zpracovatelských závodech. První generace těchto strojů používala optické senzory k detekci barev, ovládající akční členy, které zelená rajčata odhazovaly do odpadního koše pomocí pák nebo proudů vzduchu, zatímco červená rajčata pokračovala na síti dopravníkových pásů.

V tomto videu, když rajčata padají z jednoho dopravníkového pásu na druhý, zelená rajčata jsou detekována a odhozena do koše pomocí pák.

✅ Jaké podmínky byste potřebovali v továrně nebo na poli, aby tyto optické senzory správně fungovaly?

Nejnovější evoluce těchto třídicích strojů využívají AI a ML, používají modely trénované k rozlišení dobrých plodin od špatných, nejen podle zjevných barevných rozdílů, jako jsou zelená rajčata vs. červená, ale také podle jemnějších rozdílů ve vzhledu, které mohou naznačovat nemoc nebo poškození.

## Klasifikace obrázků pomocí strojového učení

Tradiční programování spočívá v tom, že vezmete data, aplikujete na ně algoritmus a získáte výstup. Například v posledním projektu jste vzali GPS souřadnice a geofenci, aplikovali algoritmus poskytovaný Azure Maps a získali výsledek, zda bod je uvnitř nebo vně geofence. Zadáte více dat, získáte více výstupů.

![Tradiční vývoj bere vstup a algoritmus a dává výstup. Strojové učení používá vstupní a výstupní data k trénování modelu, a tento model může brát nová vstupní data k vytvoření nových výstupů.](../../../../../translated_images/cs/traditional-vs-ml.5c20c169621fa539.webp)

Strojové učení to obrací – začínáte s daty a známými výstupy a algoritmus strojového učení se z dat učí. Poté můžete vzít tento trénovaný algoritmus, nazývaný *model strojového učení* nebo *model*, a zadat nová data a získat nové výstupy.

> 🎓 Proces, při kterém se algoritmus strojového učení učí z dat, se nazývá *trénink*. Vstupy a známé výstupy se nazývají *trénovací data*.

Například můžete modelu poskytnout miliony obrázků nezralých banánů jako vstupní trénovací data, s trénovacím výstupem nastaveným na `nezralý`, a miliony obrázků zralých banánů jako trénovací data s výstupem nastaveným na `zralý`. Algoritmus ML poté vytvoří model na základě těchto dat. Poté tomuto modelu poskytnete nový obrázek banánu a on předpoví, zda je nový obrázek zralý nebo nezralý.

> 🎓 Výsledky modelů ML se nazývají *predikce*.

![2 banány, jeden zralý s predikcí 99,7 % zralý, 0,3 % nezralý, a jeden nezralý s predikcí 1,4 % zralý, 98,6 % nezralý.](../../../../../translated_images/cs/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50e.webp)

Modely ML neposkytují binární odpověď, místo toho poskytují pravděpodobnosti. Například model může dostat obrázek banánu a předpovědět `zralý` s 99,7 % a `nezralý` s 0,3 %. Váš kód poté vybere nejlepší predikci a rozhodne, že banán je zralý.

Model ML používaný k detekci obrázků, jako je tento, se nazývá *klasifikátor obrázků* – je mu poskytnuto označené obrázky a poté klasifikuje nové obrázky na základě těchto označení.

> 💁 Toto je zjednodušení a existuje mnoho dalších způsobů, jak trénovat modely, které ne vždy potřebují označené výstupy, například neřízené učení. Pokud se chcete dozvědět více o ML, podívejte se na [ML pro začátečníky, 24lekční kurz o strojovém učení](https://aka.ms/ML-beginners).

## Trénink klasifikátoru obrázků

Pro úspěšný trénink klasifikátoru obrázků potřebujete miliony obrázků. Jak se ukazuje, jakmile máte klasifikátor obrázků trénovaný na milionech nebo miliardách různých obrázků, můžete ho znovu použít a přeškolit pomocí malé sady obrázků a dosáhnout skvělých výsledků pomocí procesu nazývaného *transfer learning*.

> 🎓 Transfer learning je proces, při kterém přenesete znalosti z existujícího modelu ML na nový model na základě nových dat.

Jakmile je klasifikátor obrázků trénován na širokou škálu obrázků, jeho vnitřní mechanismy jsou skvělé v rozpoznávání tvarů, barev a vzorů. Transfer learning umožňuje modelu využít to, co se již naučil při rozpoznávání částí obrázků, a použít to k rozpoznávání nových obrázků.

![Jakmile rozpoznáte tvary, mohou být uspořádány do různých konfigurací, aby vytvořily loď nebo kočku.](../../../../../translated_images/cs/shapes-to-images.1a309f0ea88dd66f.webp)

Můžete si to představit jako dětské knížky s tvary, kde jakmile rozpoznáte půlkruh, obdélník a trojúhelník, můžete rozpoznat plachetnici nebo kočku v závislosti na konfiguraci těchto tvarů. Klasifikátor obrázků dokáže rozpoznat tvary a transfer learning ho naučí, jaká kombinace tvoří loď nebo kočku – nebo zralý banán.

Existuje široká škála nástrojů, které vám s tím mohou pomoci, včetně cloudových služeb, které vám umožní trénovat váš model a poté ho používat prostřednictvím webových API.

> 💁 Trénink těchto modelů vyžaduje hodně výpočetního výkonu, obvykle prostřednictvím grafických procesorů (GPU). Stejný specializovaný hardware, který dělá hry na vašem Xboxu úžasnými, může být také použit k trénování modelů strojového učení. Použitím cloudu si můžete pronajmout čas na výkonných počítačích s GPU pro trénink těchto modelů, získat přístup k potřebnému výpočetnímu výkonu jen na dobu, kdy ho potřebujete.

## Custom Vision

Custom Vision je cloudový nástroj pro trénink klasifikátorů obrázků. Umožňuje vám trénovat klasifikátor pomocí pouze malého počtu obrázků. Obrázky můžete nahrávat prostřednictvím webového portálu, webového API nebo SDK, přičemž každému obrázku přiřadíte *tag*, který představuje klasifikaci daného obrázku. Poté model vytrénujete a otestujete, jak dobře funguje. Jakmile jste s modelem spokojeni, můžete publikovat jeho verze, které lze přistupovat prostřednictvím webového API nebo SDK.

![Logo Azure Custom Vision](../../../../../translated_images/cs/custom-vision-logo.d3d4e7c8a87ec9da.webp)

> 💁 Model Custom Vision můžete trénovat s pouhými 5 obrázky na klasifikaci, ale více je lepší. Lepších výsledků dosáhnete s alespoň 30 obrázky.

Custom Vision je součástí řady AI nástrojů od Microsoftu nazývaných Cognitive Services. Tyto AI nástroje lze používat buď bez jakéhokoliv tréninku, nebo s malým množstvím tréninku. Zahrnují rozpoznávání a překlad řeči, porozumění jazyku a analýzu obrázků. Jsou dostupné s bezplatnou úrovní jako služby v Azure.

> 💁 Bezplatná úroveň je více než dostatečná pro vytvoření modelu, jeho trénink a následné použití pro vývojové práce. O omezeních bezplatné úrovně si můžete přečíst na [stránce Omezení a kvóty Custom Vision na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn).

### Úkol – vytvoření zdroje kognitivních služeb

Pro použití Custom Vision musíte nejprve vytvořit dva zdroje kognitivních služeb v Azure pomocí Azure CLI, jeden pro trénink Custom Vision a druhý pro predikci Custom Vision.

1. Vytvořte skupinu prostředků pro tento projekt s názvem `fruit-quality-detector`.

1. Použijte následující příkaz k vytvoření bezplatného zdroje pro trénink Custom Vision:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Nahraďte `<location>` umístěním, které jste použili při vytváření skupiny prostředků.

    Tím vytvoříte zdroj pro trénink Custom Vision ve vaší skupině prostředků. Bude se jmenovat `fruit-quality-detector-training` a bude používat SKU `F0`, což je bezplatná úroveň. Možnost `--yes` znamená, že souhlasíte s podmínkami a pravidly kognitivních služeb.

> 💁 Použijte SKU `S0`, pokud již máte bezplatný účet využívající některou z kognitivních služeb.

1. Použijte následující příkaz k vytvoření bezplatného zdroje pro predikci Custom Vision:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Nahraďte `<location>` umístěním, které jste použili při vytváření skupiny prostředků.

    Tím vytvoříte zdroj pro predikci Custom Vision ve vaší skupině prostředků. Bude se jmenovat `fruit-quality-detector-prediction` a bude používat SKU `F0`, což je bezplatná úroveň. Možnost `--yes` znamená, že souhlasíte s podmínkami a pravidly kognitivních služeb.

### Úkol – vytvoření projektu klasifikátoru obrázků

1. Spusťte portál Custom Vision na [CustomVision.ai](https://customvision.ai) a přihlaste se pomocí účtu Microsoft, který jste použili pro váš účet Azure.

1. Postupujte podle [sekce vytvoření nového projektu v rychlém startu na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project) pro vytvoření nového projektu Custom Vision. Uživatelské rozhraní se může měnit a tyto dokumenty jsou vždy nejaktuálnějším referenčním zdrojem.

    Pojmenujte svůj projekt `fruit-quality-detector`.

    Při vytváření projektu se ujistěte, že používáte zdroj `fruit-quality-detector-training`, který jste vytvořili dříve. Použijte typ projektu *Classification*, typ klasifikace *Multiclass* a doménu *Food*.

    ![Nastavení projektu Custom Vision s názvem fruit-quality-detector, bez popisu, zdrojem nastaveným na fruit-quality-detector-training, typem projektu nastaveným na classification, typem klasifikace na multi class a doménou na food.](../../../../../translated_images/cs/custom-vision-create-project.cf46325b92d8b131.webp)

✅ Věnujte nějaký čas prozkoumání uživatelského rozhraní Custom Vision pro váš klasifikátor obrázků.

### Úkol – trénink vašeho projektu klasifikátoru obrázků

Pro trénink klasifikátoru obrázků budete potřebovat více obrázků ovoce, jak dobré, tak špatné kvality, které označíte jako dobré a špatné, například zralý a přezrálý banán.
💁 Tyto klasifikátory dokážou klasifikovat obrázky čehokoli, takže pokud nemáte po ruce ovoce různé kvality, můžete použít dva různé druhy ovoce, nebo třeba kočky a psy!
Ideálně by na každém obrázku měl být pouze samotný plod, buď s jednotným pozadím, nebo s různorodým pozadím. Ujistěte se, že na pozadí není nic, co by bylo specifické pro zralé nebo nezralé plody.

> 💁 Je důležité nemít specifická pozadí nebo předměty, které nesouvisí s klasifikovaným objektem pro každý štítek, jinak může klasifikátor klasifikovat pouze na základě pozadí. Například existoval klasifikátor pro rakovinu kůže, který byl trénován na znaménkách, normálních i rakovinných, přičemž u rakovinných byly vždy pravítka pro měření velikosti. Ukázalo se, že klasifikátor byl téměř 100% přesný při identifikaci pravítek na obrázcích, nikoli rakovinných znamének.

Klasifikátory obrázků pracují s velmi nízkým rozlišením. Například Custom Vision může přijímat trénovací a predikční obrázky až do velikosti 10240x10240, ale model trénuje a spouští na obrázcích o rozměrech 227x227. Větší obrázky jsou zmenšeny na tuto velikost, takže se ujistěte, že klasifikovaný objekt zabírá velkou část obrázku, jinak může být příliš malý na zmenšeném obrázku používaném klasifikátorem.

1. Shromážděte obrázky pro svůj klasifikátor. Budete potřebovat alespoň 5 obrázků pro každý štítek, abyste klasifikátor natrénovali, ale čím více, tím lépe. Budete také potřebovat několik dalších obrázků pro testování klasifikátoru. Tyto obrázky by měly být různé obrázky stejného objektu. Například:

    * Použijte 2 zralé banány, vyfoťte každý z nich z několika různých úhlů, pořiďte alespoň 7 obrázků (5 pro trénink, 2 pro testování), ale ideálně více.

        ![Fotografie 2 různých banánů](../../../../../translated_images/cs/banana-training-images.530eb203346d73bc.webp)

    * Opakujte stejný proces s 2 nezralými banány.

    Měli byste mít alespoň 10 trénovacích obrázků, z nichž alespoň 5 zralých a 5 nezralých, a 4 testovací obrázky, 2 zralé, 2 nezralé. Vaše obrázky by měly být ve formátu png nebo jpeg, menší než 6 MB. Pokud je například vytvoříte pomocí iPhonu, mohou být ve vysokém rozlišení ve formátu HEIC, takže je bude třeba převést a případně zmenšit. Čím více obrázků, tím lépe, a měli byste mít podobný počet zralých a nezralých.

    Pokud nemáte jak zralé, tak nezralé plody, můžete použít různé druhy ovoce nebo jakékoli dva dostupné objekty. Můžete také najít příkladové obrázky ve složce [images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images) zralých a nezralých banánů, které můžete použít.

1. Postupujte podle [sekce nahrání a označení obrázků v rychlém startu pro vytvoření klasifikátoru na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) a nahrajte své trénovací obrázky. Označte zralé ovoce jako `ripe` a nezralé ovoce jako `unripe`.

    ![Dialogy nahrávání ukazující nahrávání obrázků zralých a nezralých banánů](../../../../../translated_images/cs/image-upload-bananas.0751639f3815e0ec.webp)

1. Postupujte podle [sekce trénování klasifikátoru v rychlém startu pro vytvoření klasifikátoru na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier) a natrénujte klasifikátor obrázků na svých nahraných obrázcích.

    Budete mít na výběr typ trénování. Vyberte **Quick Training**.

Klasifikátor se poté začne trénovat. Trénování bude trvat několik minut.

> 🍌 Pokud se rozhodnete sníst své ovoce během trénování klasifikátoru, ujistěte se, že máte nejprve dostatek obrázků pro testování!

## Otestujte svůj klasifikátor obrázků

Jakmile je váš klasifikátor natrénován, můžete jej otestovat tím, že mu poskytnete nový obrázek k klasifikaci.

### Úkol - otestujte svůj klasifikátor obrázků

1. Postupujte podle [dokumentace testování modelu na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model) a otestujte svůj klasifikátor obrázků. Použijte testovací obrázky, které jste vytvořili dříve, nikoli žádné z obrázků, které jste použili pro trénování.

    ![Nezralý banán předpovězen jako nezralý s pravděpodobností 98,9 %, zralý s pravděpodobností 1,1 %](../../../../../translated_images/cs/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64.webp)

1. Vyzkoušejte všechny testovací obrázky, které máte k dispozici, a sledujte pravděpodobnosti.

## Znovu natrénujte svůj klasifikátor obrázků

Když testujete svůj klasifikátor, může se stát, že nedosáhnete očekávaných výsledků. Klasifikátory obrázků používají strojové učení k předpovědím o tom, co je na obrázku, na základě pravděpodobností, že určité rysy obrázku odpovídají určitému štítku. Nerozumí tomu, co je na obrázku - neví, co je banán, ani nerozumí tomu, co dělá banán banánem místo lodí. Svůj klasifikátor můžete zlepšit jeho opětovným trénováním s obrázky, které klasifikátor vyhodnotil špatně.

Pokaždé, když provedete předpověď pomocí možnosti rychlého testu, obrázek a výsledky se uloží. Tyto obrázky můžete použít k opětovnému trénování svého modelu.

### Úkol - znovu natrénujte svůj klasifikátor obrázků

1. Postupujte podle [dokumentace použití předpovězeného obrázku pro trénování na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training) a znovu natrénujte svůj model, přičemž použijte správný štítek pro každý obrázek.

1. Jakmile je váš model znovu natrénován, otestujte jej na nových obrázcích.

---

## 🚀 Výzva

Co si myslíte, že by se stalo, kdybyste použili obrázek jahody s modelem natrénovaným na banány, nebo obrázek nafukovacího banánu, nebo člověka v kostýmu banánu, nebo dokonce žlutou kreslenou postavičku, například někoho ze Simpsonových?

Vyzkoušejte to a podívejte se na předpovědi. Obrázky k vyzkoušení můžete najít pomocí [Bing Image search](https://www.bing.com/images/trending).

## Kvíz po přednášce

[Kvíz po přednášce](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## Přehled & Samostudium

* Když jste trénovali svůj klasifikátor, viděli jste hodnoty *Precision*, *Recall* a *AP*, které hodnotí vytvořený model. Přečtěte si, co tyto hodnoty znamenají, pomocí [sekce hodnocení klasifikátoru v rychlém startu pro vytvoření klasifikátoru na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)
* Přečtěte si, jak zlepšit svůj klasifikátor z [jak zlepšit svůj model Custom Vision na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)

## Zadání

[Natrénujte svůj klasifikátor pro více druhů ovoce a zeleniny](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.