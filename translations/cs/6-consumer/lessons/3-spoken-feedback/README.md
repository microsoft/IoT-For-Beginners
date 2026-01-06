<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b73fe10ec6b580fba2affb6f6e0a5c4d",
  "translation_date": "2025-08-27T21:09:46+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/README.md",
  "language_code": "cs"
}
-->
# Nastavte časovač a poskytněte hlasovou zpětnou vazbu

![Přehled této lekce ve formě sketchnote](../../../../../translated_images/lesson-23.f38483e1d4df4828990d3f02d60e46c978b075d384ae7cb4f7bab738e107c850.cs.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

## Kvíz před přednáškou

[Kvíz před přednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/45)

## Úvod

Chytré asistenty nejsou zařízení pro jednosměrnou komunikaci. Mluvíte s nimi a oni odpovídají:

„Alexo, nastav časovač na 3 minuty.“

„Ok, váš časovač je nastaven na 3 minuty.“

V posledních dvou lekcích jste se naučili, jak převést řeč na text a poté z textu extrahovat požadavek na nastavení časovače. V této lekci se naučíte, jak nastavit časovač na IoT zařízení, odpovědět uživateli mluvenými slovy potvrzujícími jeho časovač a upozornit ho, když časovač skončí.

V této lekci se zaměříme na:

* [Převod textu na řeč](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Nastavení časovače](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Převod textu na řeč](../../../../../6-consumer/lessons/3-spoken-feedback)

## Převod textu na řeč

Převod textu na řeč, jak název napovídá, je proces převodu textu na zvuk obsahující text jako mluvená slova. Základní princip spočívá v rozložení slov v textu na jejich základní zvuky (známé jako fonémy) a spojení zvuků dohromady, buď pomocí předem nahraného zvuku, nebo zvuku generovaného modely AI.

![Tři fáze typických systémů pro převod textu na řeč](../../../../../translated_images/tts-overview.193843cf3f5ee09f.cs.png)

Systémy pro převod textu na řeč obvykle zahrnují 3 fáze:

* Analýza textu
* Lingvistická analýza
* Generování zvukové vlny

### Analýza textu

Analýza textu zahrnuje převod poskytnutého textu na slova, která lze použít k vytvoření řeči. Například pokud převádíte „Hello world“, není potřeba žádná analýza textu, dvě slova lze přímo převést na řeč. Pokud máte „1234“, může být nutné převést to buď na slova „Jedentisíc dvěstě třicet čtyři“ nebo „Jedna, dva, tři, čtyři“ v závislosti na kontextu. Pro „Mám 1234 jablek“ by to bylo „Jedentisíc dvěstě třicet čtyři“, ale pro „Dítě počítalo 1234“ by to bylo „Jedna, dva, tři, čtyři“.

Slova se liší nejen podle jazyka, ale i podle lokality daného jazyka. Například v americké angličtině by 120 bylo „One hundred twenty“, zatímco v britské angličtině „One hundred and twenty“, s použitím „and“ po stovkách.

✅ Některé další příklady, které vyžadují analýzu textu, zahrnují „in“ jako zkratku pro palec a „st“ jako zkratku pro svatého nebo ulici. Dokážete najít další příklady ve vašem jazyce, kde jsou slova bez kontextu nejednoznačná?

Jakmile jsou slova definována, jsou odeslána k lingvistické analýze.

### Lingvistická analýza

Lingvistická analýza rozkládá slova na fonémy. Fonémy jsou založeny nejen na použitých písmenech, ale i na dalších písmenech ve slově. Například v angličtině je zvuk „a“ ve slovech „car“ a „care“ odlišný. Anglický jazyk má 44 různých fonémů pro 26 písmen abecedy, některé sdílené různými písmeny, například stejný foném použitý na začátku slov „circle“ a „serpent“.

✅ Udělejte si průzkum: Jaké jsou fonémy ve vašem jazyce?

Jakmile jsou slova převedena na fonémy, tyto fonémy potřebují další data pro podporu intonace, úpravu tónu nebo délky v závislosti na kontextu. Jeden příklad je v angličtině, kde zvýšení tónu může změnit větu na otázku, zvýšený tón u posledního slova naznačuje otázku.

Například věta „You have an apple“ je tvrzení, že máte jablko. Pokud se tón na konci zvýší, zvýšením u slova „apple“, stane se z toho otázka „You have an apple?“, ptající se, zda máte jablko. Lingvistická analýza musí použít otazník na konci, aby rozhodla o zvýšení tónu.

Jakmile jsou fonémy vygenerovány, mohou být odeslány ke generování zvukové vlny pro vytvoření zvukového výstupu.

### Generování zvukové vlny

První elektronické systémy pro převod textu na řeč používaly jednotlivé zvukové nahrávky pro každý foném, což vedlo k velmi monotónním, roboticky znějícím hlasům. Lingvistická analýza by vytvořila fonémy, ty by byly načteny z databáze zvuků a spojeny dohromady, aby vytvořily zvuk.

✅ Udělejte si průzkum: Najděte zvukové nahrávky z raných systémů syntézy řeči. Porovnejte je s moderní syntézou řeči, například tou, kterou používají chytré asistenty.

Modernější generování zvukové vlny používá modely strojového učení postavené na hlubokém učení (velmi velké neuronové sítě, které fungují podobně jako neurony v mozku) k vytvoření přirozeněji znějících hlasů, které mohou být nerozeznatelné od lidských.

> 💁 Některé z těchto modelů strojového učení mohou být přeškoleny pomocí transferového učení, aby zněly jako skuteční lidé. To znamená, že použití hlasu jako bezpečnostního systému, což banky stále častěji zkoušejí, již není dobrý nápad, protože kdokoli s nahrávkou několika minut vašeho hlasu vás může napodobit.

Tyto velké modely strojového učení jsou trénovány tak, aby kombinovaly všechny tři kroky do end-to-end syntetizátorů řeči.

## Nastavení časovače

Pro nastavení časovače musí vaše IoT zařízení zavolat REST endpoint, který jste vytvořili pomocí serverless kódu, a poté použít výsledný počet sekund k nastavení časovače.

### Úkol - zavolejte serverless funkci pro získání času časovače

Postupujte podle příslušného průvodce, jak zavolat REST endpoint z vašeho IoT zařízení a nastavit časovač na požadovaný čas:

* [Arduino - Wio Terminal](wio-terminal-set-timer.md)
* [Jednodeskový počítač - Raspberry Pi/Virtual IoT device](single-board-computer-set-timer.md)

## Převod textu na řeč

Stejná služba řeči, kterou jste použili k převodu řeči na text, může být použita k převodu textu zpět na řeč, a tento zvuk může být přehrán přes reproduktor na vašem IoT zařízení. Text k převodu je odeslán do služby řeči spolu s typem požadovaného zvuku (například vzorkovací frekvence) a binární data obsahující zvuk jsou vrácena.

Když odešlete tento požadavek, použijete *Speech Synthesis Markup Language* (SSML), značkovací jazyk založený na XML pro aplikace syntézy řeči. Tento jazyk definuje nejen text k převodu, ale i jazyk textu, hlas k použití, a může dokonce definovat rychlost, hlasitost a tón pro některá nebo všechna slova v textu.

Například tento SSML definuje požadavek na převod textu „Váš časovač na 3 minuty a 5 sekund byl nastaven“ na řeč pomocí britského anglického hlasu nazvaného `en-GB-MiaNeural`.

```xml
<speak version='1.0' xml:lang='en-GB'>
    <voice xml:lang='en-GB' name='en-GB-MiaNeural'>
        Your 3 minute 5 second time has been set
    </voice>
</speak>
```

> 💁 Většina systémů pro převod textu na řeč má více hlasů pro různé jazyky, s relevantními přízvuky, jako je britský anglický hlas s anglickým přízvukem a novozélandský anglický hlas s novozélandským přízvukem.

### Úkol - převod textu na řeč

Projděte si příslušného průvodce, jak převést text na řeč pomocí vašeho IoT zařízení:

* [Arduino - Wio Terminal](wio-terminal-text-to-speech.md)
* [Jednodeskový počítač - Raspberry Pi](pi-text-to-speech.md)
* [Jednodeskový počítač - Virtuální zařízení](virtual-device-text-to-speech.md)

---

## 🚀 Výzva

SSML má způsoby, jak změnit způsob, jakým jsou slova vyslovována, například přidáním důrazu na určitá slova, přidáním pauz nebo změnou tónu. Vyzkoušejte některé z těchto možností, odešlete různé SSML z vašeho IoT zařízení a porovnejte výstup. Více o SSML, včetně toho, jak změnit způsob, jakým jsou slova vyslovována, si můžete přečíst ve [specifikaci Speech Synthesis Markup Language (SSML) verze 1.1 od World Wide Web konsorcia](https://www.w3.org/TR/speech-synthesis11/).

## Kvíz po přednášce

[Kvíz po přednášce](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/46)

## Přehled & Samostudium

* Přečtěte si více o syntéze řeči na [stránce o syntéze řeči na Wikipedii](https://wikipedia.org/wiki/Speech_synthesis)
* Přečtěte si více o způsobech, jakými zločinci využívají syntézu řeči k podvodům, na [příběhu o falešných hlasech „pomáhajících kybernetickým zločincům krást peníze“ na BBC News](https://www.bbc.com/news/technology-48908736)
* Zjistěte více o rizicích pro dabéry kvůli syntetizovaným verzím jejich hlasů v [článku na Vice „Tato žaloba na TikTok ukazuje, jak AI škodí dabérům“](https://www.vice.com/en/article/z3xqwj/this-tiktok-lawsuit-is-highlighting-how-ai-is-screwing-over-voice-actors)

## Zadání

[Zrušte časovač](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby AI pro překlady [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatizované překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.