<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6d6aa1be033625d201a190fc9c5cbfb4",
  "translation_date": "2025-08-27T21:18:36+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/README.md",
  "language_code": "cs"
}
-->
# Rozpoznávání řeči pomocí IoT zařízení

![Přehled této lekce ve formě sketchnote](../../../../../translated_images/cs/lesson-21.e34de51354d6606fb5ee08d8c89d0222eea0a2a7aaf744a8805ae847c4f69dc4.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

Toto video poskytuje přehled služby Azure Speech, která bude pokryta v této lekci:

[![Jak začít používat svůj Cognitive Services Speech zdroj z YouTube kanálu Microsoft Azure](https://img.youtube.com/vi/iW0Fw0l3mrA/0.jpg)](https://www.youtube.com/watch?v=iW0Fw0l3mrA)

> 🎥 Klikněte na obrázek výše pro zhlédnutí videa

## Kvíz před lekcí

[Kvíz před lekcí](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/41)

## Úvod

„Alexo, nastav časovač na 12 minut.“

„Alexo, jaký je stav časovače?“

„Alexo, nastav časovač na 8 minut s názvem napařit brokolici.“

Chytrá zařízení se stávají stále běžnějšími. Nejen jako chytré reproduktory, jako jsou HomePods, Echos a Google Homes, ale také jako součást našich telefonů, hodinek, světel nebo termostatů.

> 💁 Mám doma alespoň 19 zařízení s hlasovými asistenty, a to jsou jen ta, o kterých vím!

Hlasové ovládání zvyšuje přístupnost tím, že umožňuje lidem s omezenou pohyblivostí interagovat se zařízeními. Ať už jde o trvalé postižení, jako je narození bez rukou, dočasné postižení, například zlomené ruce, nebo situace, kdy máte plné ruce nákupů nebo malých dětí, možnost ovládat domácnost hlasem místo rukama otevírá svět nových možností. Křik „Hej Siri, zavři garážová vrata“ při přebalování dítěte a uklidňování neposedného batolete může být malým, ale účinným zlepšením života.

Jedním z nejoblíbenějších využití hlasových asistentů je nastavování časovačů, zejména kuchyňských. Možnost nastavit více časovačů pouze hlasem je velkou pomocí v kuchyni – není třeba přerušovat hnětení těsta, míchání polévky nebo čištění rukou od náplně na knedlíky, abyste použili fyzický časovač.

V této lekci se naučíte, jak integrovat rozpoznávání hlasu do IoT zařízení. Naučíte se o mikrofonech jako senzorech, jak zachytit zvuk z mikrofonu připojeného k IoT zařízení a jak použít AI k převodu slyšeného na text. V průběhu tohoto projektu vytvoříte chytrý kuchyňský časovač, který bude schopný nastavit časovače pomocí hlasu v několika jazycích.

V této lekci se zaměříme na:

* [Mikrofony](../../../../../6-consumer/lessons/1-speech-recognition)
* [Zachycení zvuku z vašeho IoT zařízení](../../../../../6-consumer/lessons/1-speech-recognition)
* [Převod řeči na text](../../../../../6-consumer/lessons/1-speech-recognition)
* [Konverze řeči na text](../../../../../6-consumer/lessons/1-speech-recognition)

## Mikrofony

Mikrofony jsou analogové senzory, které převádějí zvukové vlny na elektrické signály. Vibrace ve vzduchu způsobují drobné pohyby komponent mikrofonu, což vede k malým změnám elektrických signálů. Tyto změny jsou následně zesíleny, aby vytvořily elektrický výstup.

### Typy mikrofonů

Mikrofony existují v různých typech:

* Dynamické – Dynamické mikrofony mají magnet připojený k pohyblivé membráně, která se pohybuje v cívce drátu a vytváří elektrický proud. To je opak většiny reproduktorů, které používají elektrický proud k pohybu magnetu v cívce drátu, čímž pohybují membránou a vytvářejí zvuk. To znamená, že reproduktory mohou být použity jako dynamické mikrofony a dynamické mikrofony jako reproduktory. V zařízeních, jako jsou interkomy, kde uživatel buď poslouchá, nebo mluví, ale ne obojí, může jedno zařízení fungovat jako reproduktor i mikrofon.

    Dynamické mikrofony nepotřebují k práci napájení, elektrický signál je vytvářen výhradně mikrofonem.

    ![Patti Smith zpívající do mikrofonu Shure SM58 (dynamický typ kardioid)](../../../../../translated_images/cs/dynamic-mic.8babac890a2d80dfb0874b5bf37d4b851fe2aeb9da6fd72945746176978bf3bb.jpg)

* Páskové – Páskové mikrofony jsou podobné dynamickým mikrofonům, ale místo membrány mají kovovou pásku. Tato páska se pohybuje v magnetickém poli a generuje elektrický proud. Stejně jako dynamické mikrofony, páskové mikrofony nepotřebují napájení.

    ![Edmund Lowe, americký herec, stojící u rozhlasového mikrofonu (označeného jako (NBC) Blue Network), držící scénář, 1942](../../../../../translated_images/cs/ribbon-mic.eacc8e092c7441ca.webp)

* Kondenzátorové – Kondenzátorové mikrofony mají tenkou kovovou membránu a pevnou kovovou zadní desku. Elektrický proud je aplikován na obě tyto části a jak membrána vibruje, statický náboj mezi deskami se mění a generuje signál. Kondenzátorové mikrofony potřebují napájení – nazývané *Phantom power*.

    ![C451B malomembránový kondenzátorový mikrofon od AKG Acoustics](../../../../../translated_images/cs/condenser-mic.6f6ed5b76ca19e0ec3fd0c544601542d4479a6cb7565db336de49fbbf69f623e.jpg)

* MEMS – Mikroelektromechanické systémy mikrofonů, nebo MEMS, jsou mikrofony na čipu. Mají tlakově citlivou membránu vyrytou na křemíkovém čipu a fungují podobně jako kondenzátorové mikrofony. Tyto mikrofony mohou být velmi malé a integrované do obvodů.

    ![MEMS mikrofon na obvodové desce](../../../../../translated_images/cs/mems-microphone.80574019e1f5e4d9ee72fed720ecd25a39fc2969c91355d17ebb24ba4159e4c4.png)

    Na obrázku výše je čip označený **LEFT**, což je MEMS mikrofon s malou membránou o šířce méně než milimetr.

✅ Udělejte si průzkum: Jaké mikrofony máte kolem sebe – buď ve svém počítači, telefonu, náhlavní soupravě nebo jiných zařízeních? Jaké typy mikrofonů to jsou?

### Digitální zvuk

Zvuk je analogový signál nesoucí velmi jemné informace. Aby byl tento signál převeden na digitální, musí být vzorkován tisícekrát za sekundu.

> 🎓 Vzorkování je proces převodu zvukového signálu na digitální hodnotu, která reprezentuje signál v daném okamžiku.

![Graf zobrazující signál s diskrétními body v pevných intervalech](../../../../../translated_images/cs/sampling.6f4fadb3f2d9dfe7.webp)

Digitální zvuk je vzorkován pomocí Pulzní kódové modulace (PCM). PCM zahrnuje čtení napětí signálu a výběr nejbližší diskrétní hodnoty k tomuto napětí pomocí definované velikosti.

> 💁 PCM si můžete představit jako senzorovou verzi Pulzní šířkové modulace (PWM). PWM bylo pokryto v [lekci 3 projektu pro začátečníky](../../../1-getting-started/lessons/3-sensors-and-actuators/README.md#pulse-width-modulation). PCM převádí analogový signál na digitální, PWM převádí digitální signál na analogový.

Například většina streamovacích hudebních služeb nabízí 16bitový nebo 24bitový zvuk. To znamená, že převádějí napětí na hodnotu, která se vejde do 16bitového nebo 24bitového celého čísla. 16bitový zvuk se vejde do rozsahu -32,768 až 32,767, 24bitový do rozsahu −8,388,608 až 8,388,607. Čím více bitů, tím blíže je vzorek tomu, co naše uši skutečně slyší.

> 💁 Možná jste slyšeli o 8bitovém zvuku, často označovaném jako LoFi. Jedná se o zvuk vzorkovaný pouze pomocí 8 bitů, tedy -128 až 127. První počítačový zvuk byl omezen na 8 bitů kvůli hardwarovým omezením, takže se často objevuje v retro hrách.

Tyto vzorky jsou pořizovány tisícekrát za sekundu pomocí dobře definovaných vzorkovacích frekvencí měřených v kHz (tisíce čtení za sekundu). Streamovací hudební služby používají 48 kHz pro většinu zvuku, ale některé „bezztrátové“ zvuky používají až 96 kHz nebo dokonce 192 kHz. Čím vyšší vzorkovací frekvence, tím blíže originálu bude zvuk, až do určitého bodu. Existuje debata, zda lidé dokážou rozlišit rozdíl nad 48 kHz.

✅ Udělejte si průzkum: Pokud používáte streamovací hudební službu, jakou vzorkovací frekvenci a velikost používá? Pokud používáte CD, jaká je vzorkovací frekvence a velikost zvuku na CD?

Existuje řada různých formátů pro zvuková data. Pravděpodobně jste slyšeli o souborech mp3 – zvukových datech, která jsou komprimována, aby byla menší, aniž by ztratila kvalitu. Nezkomprimovaný zvuk je často uložen jako soubor WAV – jedná se o soubor s 44 bajty hlavičkových informací, následovaný surovými zvukovými daty. Hlavička obsahuje informace, jako je vzorkovací frekvence (například 16000 pro 16 kHz) a velikost vzorku (16 pro 16 bitů) a počet kanálů. Po hlavičce obsahuje soubor WAV surová zvuková data.

> 🎓 Kanály označují, kolik různých zvukových proudů tvoří zvuk. Například pro stereo zvuk s levým a pravým kanálem by byly 2 kanály. Pro 7.1 prostorový zvuk pro domácí kino by to bylo 8.

### Velikost zvukových dat

Zvuková data jsou relativně velká. Například zachycení nekomprimovaného 16bitového zvuku při 16 kHz (dostatečná kvalita pro použití s modelem převodu řeči na text) zabere 32 KB dat na každou sekundu zvuku:

* 16 bitů znamená 2 bajty na vzorek (1 bajt je 8 bitů).
* 16 kHz je 16 000 vzorků za sekundu.
* 16 000 x 2 bajty = 32 000 bajtů za sekundu.

To se může zdát jako malé množství dat, ale pokud používáte mikrokontrolér s omezenou pamětí, může to být hodně. Například Wio Terminal má 192 KB paměti, která musí uchovávat programový kód a proměnné. I kdyby byl váš programový kód velmi malý, nemohli byste zachytit více než 5 sekund zvuku.

Mikrokontroléry mohou přistupovat k dalšímu úložišti, jako jsou SD karty nebo flash paměť. Při vytváření IoT zařízení, které zachycuje zvuk, budete muset zajistit nejen to, že máte další úložiště, ale také že váš kód zapisuje zachycený zvuk z mikrofonu přímo do tohoto úložiště. Při odesílání do cloudu byste měli streamovat zvuk z úložiště do webového požadavku. Tím se vyhnete vyčerpání paměti tím, že byste se snažili držet celý blok zvukových dat v paměti najednou.

## Zachycení zvuku z vašeho IoT zařízení

Vaše IoT zařízení může být připojeno k mikrofonu pro zachycení zvuku, připraveného k převodu na text. Může být také připojeno k reproduktorům pro výstup zvuku. V pozdějších lekcích bude toto využito k poskytování zvukové zpětné vazby, ale je užitečné nastavit reproduktory nyní, abyste mohli otestovat mikrofon.

### Úkol – konfigurace mikrofonu a reproduktorů

Projděte si příslušný návod k nastavení mikrofonu a reproduktorů pro vaše IoT zařízení:

* [Arduino – Wio Terminal](wio-terminal-microphone.md)
* [Jednodeskový počítač – Raspberry Pi](pi-microphone.md)
* [Jednodeskový počítač – Virtuální zařízení](virtual-device-microphone.md)

### Úkol – zachycení zvuku

Projděte si příslušný návod k zachycení zvuku na vašem IoT zařízení:

* [Arduino – Wio Terminal](wio-terminal-audio.md)
* [Jednodeskový počítač – Raspberry Pi](pi-audio.md)
* [Jednodeskový počítač – Virtuální zařízení](virtual-device-audio.md)

## Převod řeči na text

Převod řeči na text, nebo rozpoznávání řeči, zahrnuje použití AI k převodu slov v zvukovém signálu na text.

### Modely rozpoznávání řeči

Pro převod řeči na text jsou vzorky zvukového signálu seskupeny a předány do modelu strojového učení založeného na Recurrent Neural Network (RNN). Jedná se o typ modelu strojového učení, který může použít předchozí data k rozhodnutí o příchozích datech. Například RNN může detekovat jeden blok zvukových vzorků jako zvuk „Hel“ a když obdrží další, který považuje za zvuk „lo“, může to spojit s předchozím zvukem, zjistit, že „Hello“ je platné slovo, a vybrat ho jako výsledek.

Modely strojového učení vždy přijímají data stejné velikosti pokaždé. Klasifikátor obrázků, který jste vytvořili v dřívější lekci, mění velikost obrázků na pevnou velikost a zpracovává je. Totéž platí pro modely řeči – musí zpracovávat zvukové bloky pevné velikosti. Modely řeči musí být schopny kombinovat výstupy z více předpovědí, aby získaly odpověď, což jim umožňuje rozlišovat mezi „Hi“ a „Highway“ nebo „flock“ a „floccinaucinihilipilification“.

Modely řeči jsou také dostatečně pokročilé, aby pochopily kontext a mohly opravit slova, která detekují, jakmile zpracují více zvuků. Například pokud řeknete „Šel jsem do obchodu koupit dvě banány a jedno jablko také“, použili byste tři slova, která znějí stejně, ale jsou napsána odlišně – to, dvě a také. Modely řeči jsou schopny pochopit kontext a použít správný pravopis slova.
💁 Některé služby pro rozpoznávání řeči umožňují přizpůsobení, aby lépe fungovaly v hlučném prostředí, jako jsou továrny, nebo s oborově specifickými výrazy, například chemickými názvy. Tato přizpůsobení se trénují pomocí vzorových zvukových nahrávek a jejich přepisů a fungují na principu transferového učení, stejně jako jste v předchozí lekci trénovali klasifikátor obrázků pomocí několika málo snímků.
### Soukromí

Při používání převodu řeči na text na spotřebitelském IoT zařízení je soukromí nesmírně důležité. Tato zařízení neustále poslouchají zvuk, takže jako spotřebitel nechcete, aby vše, co řeknete, bylo odesíláno do cloudu a převáděno na text. Nejenže by to spotřebovalo velkou šířku pásma internetu, ale má to také obrovské dopady na soukromí, zejména když někteří výrobci chytrých zařízení náhodně vybírají zvuk pro [lidské ověření proti generovanému textu za účelem zlepšení jejich modelu](https://www.theverge.com/2019/4/10/18305378/amazon-alexa-ai-voice-assistant-annotation-listen-private-recordings).

Chcete, aby vaše chytré zařízení odesílalo zvuk do cloudu k zpracování pouze tehdy, když ho používáte, ne když slyší zvuk ve vašem domě, zvuk, který může zahrnovat soukromé schůzky nebo intimní interakce. Většina chytrých zařízení funguje na principu *probudícího slova*, klíčové fráze jako "Alexa", "Hey Siri" nebo "OK Google", která způsobí, že se zařízení 'probudí' a poslouchá, co říkáte, dokud nezaznamená pauzu ve vašem projevu, což naznačuje, že jste dokončili mluvení k zařízení.

> 🎓 Detekce probouzejícího slova se také označuje jako *rozpoznávání klíčových slov* nebo *vyhledávání klíčových slov*.

Tato probouzející slova jsou detekována na zařízení, nikoli v cloudu. Tato chytrá zařízení mají malé AI modely, které běží na zařízení, poslouchají probouzející slovo a po jeho detekci začnou streamovat zvuk do cloudu k rozpoznání. Tyto modely jsou velmi specializované a poslouchají pouze probouzející slovo.

> 💁 Některé technologické společnosti přidávají do svých zařízení více soukromí a provádějí část převodu řeči na text přímo na zařízení. Apple oznámil, že v rámci svých aktualizací iOS a macOS pro rok 2021 bude podporovat převod řeči na text na zařízení a bude schopen zpracovat mnoho požadavků bez nutnosti použití cloudu. To je možné díky výkonným procesorům v jejich zařízeních, které dokážou provozovat ML modely.

✅ Jaké podle vás jsou dopady na soukromí a etiku při ukládání zvuku odeslaného do cloudu? Měl by být tento zvuk ukládán, a pokud ano, jak? Myslíte si, že použití nahrávek pro účely vymáhání práva je dobrým kompromisem za ztrátu soukromí?

Detekce probouzejícího slova obvykle využívá techniku známou jako TinyML, což je převod ML modelů tak, aby mohly běžet na mikrokontrolérech. Tyto modely jsou malé velikosti a spotřebovávají velmi málo energie.

Aby se předešlo složitosti trénování a používání modelu pro probouzející slovo, chytrý časovač, který v této lekci stavíte, bude používat tlačítko k zapnutí rozpoznávání řeči.

> 💁 Pokud chcete vyzkoušet vytvoření modelu pro detekci probouzejícího slova, který běží na Wio Terminal nebo Raspberry Pi, podívejte se na tento [návod na reagování na váš hlas od Edge Impulse](https://docs.edgeimpulse.com/docs/responding-to-your-voice). Pokud chcete použít svůj počítač, můžete vyzkoušet [rychlý start s vlastním klíčovým slovem na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Převod řeči na text

![Logo služeb řeči](../../../../../translated_images/cs/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.png)

Stejně jako u klasifikace obrázků v dřívějším projektu existují předem vytvořené AI služby, které mohou převést řeč jako zvukový soubor na text. Jednou z těchto služeb je Speech Service, součást Cognitive Services, předem vytvořených AI služeb, které můžete použít ve svých aplikacích.

### Úkol - konfigurace AI zdroje pro řeč

1. Vytvořte skupinu zdrojů pro tento projekt s názvem `smart-timer`.

1. Použijte následující příkaz k vytvoření bezplatného zdroje pro řeč:

    ```sh
    az cognitiveservices account create --name smart-timer \
                                        --resource-group smart-timer \
                                        --kind SpeechServices \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Nahraďte `<location>` místem, které jste použili při vytváření skupiny zdrojů.

1. Budete potřebovat API klíč pro přístup ke zdroji řeči z vašeho kódu. Spusťte následující příkaz pro získání klíče:

    ```sh
    az cognitiveservices account keys list --name smart-timer \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Zkopírujte jeden z klíčů.

### Úkol - převod řeči na text

Projděte si relevantní návod pro převod řeči na text na vašem IoT zařízení:

* [Arduino - Wio Terminal](wio-terminal-speech-to-text.md)
* [Jednodeskový počítač - Raspberry Pi](pi-speech-to-text.md)
* [Jednodeskový počítač - Virtuální zařízení](virtual-device-speech-to-text.md)

---

## 🚀 Výzva

Rozpoznávání řeči existuje již dlouho a neustále se zlepšuje. Prozkoumejte současné schopnosti a porovnejte, jak se vyvíjely v průběhu času, včetně toho, jak přesné jsou strojové přepisy ve srovnání s lidskými.

Co si myslíte, že přinese budoucnost rozpoznávání řeči?

## Kvíz po přednášce

[Kvíz po přednášce](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/42)

## Přehled & Samostudium

* Přečtěte si o různých typech mikrofonů a jak fungují v článku [jaký je rozdíl mezi dynamickými a kondenzátorovými mikrofony na Musician's HQ](https://musicianshq.com/whats-the-difference-between-dynamic-and-condenser-microphones/).
* Přečtěte si více o službě řeči v Cognitive Services v [dokumentaci služby řeči na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn).
* Přečtěte si o vyhledávání klíčových slov v [dokumentaci k rozpoznávání klíčových slov na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Zadání

[](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neneseme odpovědnost za jakékoli nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.