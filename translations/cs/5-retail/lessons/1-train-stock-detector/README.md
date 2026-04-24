# Trénujte detektor zásob

![Přehled této lekce ve formě sketchnote](../../../../../translated_images/cs/lesson-19.cf6973cecadf080c.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

Toto video poskytuje přehled o detekci objektů pomocí služby Azure Custom Vision, která bude pokryta v této lekci.

[![Custom Vision 2 - Object Detection Made Easy | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Klikněte na obrázek výše pro zhlédnutí videa

## Kvíz před lekcí

[Kvíz před lekcí](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Úvod

V předchozím projektu jste použili AI k vytvoření klasifikátoru obrázků – modelu, který dokáže určit, zda obrázek obsahuje něco, například zralé nebo nezralé ovoce. Dalším typem AI modelu, který lze použít s obrázky, je detekce objektů. Tyto modely neklasifikují obrázek podle štítků, ale jsou trénovány na rozpoznávání objektů a dokážou je najít na obrázcích. Nejenže detekují, že objekt je na obrázku přítomen, ale také určují, kde se na obrázku nachází. To umožňuje počítat objekty na obrázcích.

V této lekci se naučíte o detekci objektů, včetně toho, jak ji lze využít v maloobchodě. Také se naučíte, jak trénovat detektor objektů v cloudu.

V této lekci se zaměříme na:

* [Detekce objektů](../../../../../5-retail/lessons/1-train-stock-detector)
* [Použití detekce objektů v maloobchodě](../../../../../5-retail/lessons/1-train-stock-detector)
* [Trénování detektoru objektů](../../../../../5-retail/lessons/1-train-stock-detector)
* [Testování vašeho detektoru objektů](../../../../../5-retail/lessons/1-train-stock-detector)
* [Opětovné trénování vašeho detektoru objektů](../../../../../5-retail/lessons/1-train-stock-detector)

## Detekce objektů

Detekce objektů zahrnuje rozpoznávání objektů na obrázcích pomocí AI. Na rozdíl od klasifikátoru obrázků, který jste trénovali v posledním projektu, detekce objektů není o předpovídání nejlepšího štítku pro celý obrázek, ale o nalezení jednoho nebo více objektů na obrázku.

### Detekce objektů vs klasifikace obrázků

Klasifikace obrázků se zaměřuje na klasifikaci celého obrázku – jaké jsou pravděpodobnosti, že celý obrázek odpovídá každému štítku. Získáte zpět pravděpodobnosti pro každý štítek použitý při trénování modelu.

![Klasifikace obrázků kešu ořechů a rajčatového protlaku](../../../../../translated_images/cs/image-classifier-cashews-tomato.bc2e16ab8f05cf9a.webp)

V příkladu výše jsou dva obrázky klasifikovány pomocí modelu trénovaného na klasifikaci kelímků kešu ořechů nebo plechovek rajčatového protlaku. První obrázek je kelímek kešu ořechů a má dva výsledky z klasifikátoru obrázků:

| Štítek         | Pravděpodobnost |
| -------------- | --------------: |
| `kešu ořechy`  | 98.4%           |
| `rajčatový protlak` | 1.6%       |

Druhý obrázek je plechovka rajčatového protlaku a výsledky jsou:

| Štítek         | Pravděpodobnost |
| -------------- | --------------: |
| `kešu ořechy`  | 0.7%            |
| `rajčatový protlak` | 99.3%       |

Tyto hodnoty byste mohli použít s prahovou procentní hodnotou k předpovědi, co je na obrázku. Ale co když obrázek obsahuje více plechovek rajčatového protlaku nebo jak kešu ořechy, tak rajčatový protlak? Výsledky by pravděpodobně nedaly to, co chcete. Zde přichází na řadu detekce objektů.

Detekce objektů zahrnuje trénování modelu na rozpoznávání objektů. Místo toho, abyste mu dali obrázky obsahující objekt a řekli mu, že každý obrázek je jeden štítek nebo jiný, zvýrazníte část obrázku, která obsahuje konkrétní objekt, a označíte ji. Můžete označit jeden objekt na obrázku nebo více. Tímto způsobem se model naučí, jak objekt sám vypadá, nejen jak vypadají obrázky, které objekt obsahují.

Když jej pak použijete k předpovědi obrázků, místo seznamu štítků a procent získáte seznam detekovaných objektů, jejich ohraničující rámeček a pravděpodobnost, že objekt odpovídá přiřazenému štítku.

> 🎓 *Ohraničující rámečky* jsou rámečky kolem objektu.

![Detekce objektů kešu ořechů a rajčatového protlaku](../../../../../translated_images/cs/object-detector-cashews-tomato.1af7c26686b4db0e.webp)

Obrázek výše obsahuje jak kelímek kešu ořechů, tak tři plechovky rajčatového protlaku. Detektor objektů detekoval kešu ořechy, vrací ohraničující rámeček, který obsahuje kešu ořechy, s procentní pravděpodobností, že ohraničující rámeček obsahuje objekt, v tomto případě 97.6%. Detektor objektů také detekoval tři plechovky rajčatového protlaku a poskytuje tři samostatné ohraničující rámečky, jeden pro každou detekovanou plechovku, a každá má procentní pravděpodobnost, že ohraničující rámeček obsahuje plechovku rajčatového protlaku.

✅ Zamyslete se nad různými scénáři, pro které byste mohli chtít použít AI modely založené na obrázcích. Které by potřebovaly klasifikaci a které detekci objektů?

### Jak funguje detekce objektů

Detekce objektů používá složité ML modely. Tyto modely fungují tak, že rozdělí obrázek na více buněk, poté zkontrolují, zda střed ohraničujícího rámečku odpovídá středu obrázku, který odpovídá jednomu z obrázků použitých při trénování modelu. Můžete si to představit jako spuštění klasifikátoru obrázků na různých částech obrázku, aby se hledaly shody.

> 💁 Toto je drastické zjednodušení. Existuje mnoho technik pro detekci objektů a více o nich si můžete přečíst na [stránce Detekce objektů na Wikipedii](https://wikipedia.org/wiki/Object_detection).

Existuje řada různých modelů, které mohou provádět detekci objektů. Jeden obzvláště známý model je [YOLO (You only look once)](https://pjreddie.com/darknet/yolo/), který je neuvěřitelně rychlý a dokáže detekovat 20 různých tříd objektů, jako jsou lidé, psi, lahve a auta.

✅ Přečtěte si o modelu YOLO na [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/)

Modely detekce objektů mohou být pře-trénovány pomocí transferového učení k detekci vlastních objektů.

## Použití detekce objektů v maloobchodě

Detekce objektů má mnoho využití v maloobchodě. Některé zahrnují:

* **Kontrola zásob a počítání** – rozpoznání, kdy je na regálech málo zásob. Pokud je zásob příliš málo, mohou být zaslány upozornění zaměstnancům nebo robotům, aby regály doplnili.
* **Detekce roušek** – v obchodech s politikou nošení roušek během veřejných zdravotních událostí může detekce objektů rozpoznat lidi s rouškami a bez nich.
* **Automatizované účtování** – detekce položek odebraných z regálů v automatizovaných obchodech a správné účtování zákazníkům.
* **Detekce nebezpečí** – rozpoznání rozbitých položek na podlaze nebo rozlitých tekutin, upozornění úklidových týmů.

✅ Proveďte výzkum: Jaké jsou další případy použití detekce objektů v maloobchodě?

## Trénování detektoru objektů

Detektor objektů můžete trénovat pomocí Custom Vision, podobně jako jste trénovali klasifikátor obrázků.

### Úkol – vytvořte detektor objektů

1. Vytvořte skupinu prostředků pro tento projekt s názvem `stock-detector`.

1. Vytvořte bezplatný trénovací prostředek Custom Vision a bezplatný predikční prostředek Custom Vision ve skupině prostředků `stock-detector`. Pojmenujte je `stock-detector-training` a `stock-detector-prediction`.

    > 💁 Můžete mít pouze jeden bezplatný trénovací a predikční prostředek, takže se ujistěte, že jste vyčistili svůj projekt z předchozích lekcí.

    > ⚠️ Můžete se odkazovat na [pokyny pro vytvoření trénovacích a predikčních prostředků z projektu 4, lekce 1, pokud je to potřeba](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. Spusťte portál Custom Vision na [CustomVision.ai](https://customvision.ai) a přihlaste se pomocí účtu Microsoft, který jste použili pro svůj Azure účet.

1. Postupujte podle [sekce Vytvoření nového projektu v rychlém startu Vytvoření detektoru objektů na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project) pro vytvoření nového projektu Custom Vision. Uživatelské rozhraní se může měnit a tyto dokumenty jsou vždy nejaktuálnější referencí.

    Pojmenujte svůj projekt `stock-detector`.

    Při vytváření projektu se ujistěte, že používáte trénovací prostředek `stock-detector-training`, který jste vytvořili dříve. Použijte typ projektu *Detekce objektů* a doménu *Produkty na regálech*.

    ![Nastavení projektu Custom Vision s názvem nastaveným na fruit-quality-detector, bez popisu, prostředek nastavený na fruit-quality-detector-training, typ projektu nastavený na klasifikaci, typy klasifikace nastavené na multi class a domény nastavené na food](../../../../../translated_images/cs/custom-vision-create-object-detector-project.32d4fb9aa8e7e737.webp)

    ✅ Doména produktů na regálech je specificky zaměřena na detekci zásob na regálech v obchodech. Přečtěte si více o různých doménách v [dokumentaci Výběr domény na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection)

✅ Věnujte nějaký čas prozkoumání uživatelského rozhraní Custom Vision pro váš detektor objektů.

### Úkol – trénujte svůj detektor objektů

K trénování modelu budete potřebovat sadu obrázků obsahujících objekty, které chcete detekovat.

1. Shromážděte obrázky obsahující objekt k detekci. Budete potřebovat alespoň 15 obrázků obsahujících každý objekt k detekci z různých úhlů a za různých světelných podmínek, ale čím více, tím lépe. Tento detektor objektů používá doménu *Produkty na regálech*, takže se pokuste nastavit objekty, jako by byly na regálu v obchodě. Budete také potřebovat několik obrázků k testování modelu. Pokud detekujete více než jeden objekt, budete chtít některé testovací obrázky, které obsahují všechny objekty.

    > 💁 Obrázky s více různými objekty se počítají do minimálního počtu 15 obrázků pro všechny objekty na obrázku.

    Vaše obrázky by měly být ve formátu png nebo jpeg, menší než 6 MB. Pokud je vytvoříte například pomocí iPhonu, mohou být ve vysokém rozlišení ve formátu HEIC, takže je bude potřeba převést a možná zmenšit. Čím více obrázků, tím lépe, a měli byste mít podobný počet zralých a nezralých.

    Model je navržen pro produkty na regálech, takže se pokuste pořídit fotografie objektů na regálech.

    Některé příkladové obrázky, které můžete použít, najdete ve složce [images](../../../../../5-retail/lessons/1-train-stock-detector/images) kešu ořechů a rajčatového protlaku, které můžete použít.

1. Postupujte podle [sekce Nahrání a označení obrázků v rychlém startu Vytvoření detektoru objektů na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) pro nahrání vašich trénovacích obrázků. Vytvořte relevantní štítky podle typů objektů, které chcete detekovat.

    ![Dialogy nahrávání ukazující nahrávání obrázků zralých a nezralých banánů](../../../../../translated_images/cs/image-upload-object-detector.77c7892c3093cb59.webp)

    Když kreslíte ohraničující rámečky pro objekty, udržujte je těsně kolem objektu. Může to chvíli trvat, než označíte všechny obrázky, ale nástroj detekuje, co považuje za ohraničující rámečky, což proces urychlí.

    ![Označování rajčatového protlaku](../../../../../translated_images/cs/object-detector-tag-tomato-paste.f47c362fb0f0eb58.webp)

    > 💁 Pokud máte více než 15 obrázků pro každý objekt, můžete trénovat po 15 a poté použít funkci **Navržené štítky**. Tato funkce použije trénovaný model k detekci objektů na neoznačených obrázcích. Poté můžete potvrdit detekované objekty nebo odmítnout a znovu nakreslit ohraničující rámečky. To může ušetřit *hodně* času.

1. Postupujte podle [sekce Trénování detektoru v rychlém startu Vytvoření detektoru objektů na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector) pro trénování detektoru objektů na vašich označených obrázcích.

    Budete mít na výběr typ trénování. Vyberte **Rychlé trénování**.

Detektor objektů se poté začne trénovat. Trénování bude trvat několik minut.

## Testování vašeho detektoru objektů

Jakmile je váš detektor objektů natrénován, můžete jej otestovat tím, že mu poskytnete nové obrázky k detekci objektů.

### Úkol – otestujte svůj detektor objektů

1. Použijte tlačítko **Rychlý test** k nahrání testovacích obrázků a ověření, že objekty jsou detekovány. Použijte testovací obrázky, které jste vytvořili dříve, ne žádné z obrázků, které jste použili pro trénování.

    ![Detekovány 3 plechovky rajčatového protlaku s pravděpodobnostmi 38%, 35.5% a 34.6%](../../../../../translated_images/cs/object-detector-detected-tomato-paste.52656fe87af4c37b.webp)

1. Vyzkoušejte všechny testovací obrázky, které máte k dispozici, a pozorujte pravděpodobnosti.

## Opětovné trénování vašeho detektoru objektů

Když testujete svůj detektor objektů, nemusí dávat očekávané výsledky, stejně jako u klasifikátorů obrázků v předchozím projektu. Svůj detektor objektů můžete zlepšit jeho opětovným trénováním s obrázky, které se mu nepovedly.

Pokaždé, když provedete predikci pomocí možnosti rychlého testu, obrázek a výsledky se uloží. Tyto obrázky můžete použít k opětovnému trénování svého modelu.

1. Použijte kartu **Predikce** k nalezení obrázků, které jste použili pro testování.

1. Potvrďte jakékoli přesné detekce, smažte nesprávné a přidejte chybějící objekty.

1. Opětovně trénujte a znovu otest
[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Přehled a samostudium

* Když jste trénovali svůj detektor objektů, viděli jste hodnoty *Precision*, *Recall* a *mAP*, které hodnotí vytvořený model. Přečtěte si, co tyto hodnoty znamenají, pomocí [sekce Vyhodnocení detektoru v rychlém startu Vytvoření detektoru objektů na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector)
* Přečtěte si více o detekci objektů na [stránce Detekce objektů na Wikipedii](https://wikipedia.org/wiki/Object_detection)

## Zadání

[Porovnejte domény](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.