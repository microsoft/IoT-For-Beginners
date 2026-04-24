# Podpora viacerých jazykov

![Prehľad tejto lekcie vo forme sketchnote](../../../../../translated_images/sk/lesson-24.4246968ed058510a.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre väčšiu verziu.

Toto video poskytuje prehľad o službách Azure pre spracovanie reči, pokrývajúc prevod reči na text a textu na reč z predchádzajúcich lekcií, ako aj preklad reči, čo je téma tejto lekcie:

[![Rozpoznávanie reči s niekoľkými riadkami Pythonu z Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Kliknite na obrázok vyššie pre prehratie videa

## Kvíz pred prednáškou

[Kvíz pred prednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Úvod

V posledných troch lekciách ste sa naučili, ako prevádzať reč na text, porozumieť jazyku a prevádzať text na reč, všetko s využitím umelej inteligencie. Ďalšou oblasťou ľudskej komunikácie, kde môže AI pomôcť, je preklad jazykov – prevod z jedného jazyka do druhého, napríklad z angličtiny do francúzštiny.

V tejto lekcii sa naučíte, ako používať AI na preklad textu, čo umožní vášmu inteligentnému časovaču komunikovať s používateľmi vo viacerých jazykoch.

V tejto lekcii sa budeme venovať:

* [Prekladu textu](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Prekladateľským službám](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Vytvoreniu prekladateľského zdroja](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Podpore viacerých jazykov v aplikáciách pomocou prekladov](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Prekladu textu pomocou AI služby](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Toto je posledná lekcia v tomto projekte, takže po dokončení tejto lekcie a zadania nezabudnite vyčistiť svoje cloudové služby. Budete ich potrebovať na dokončenie zadania, takže sa uistite, že ho najprv dokončíte.
>
> Ak potrebujete pokyny, pozrite si [sprievodcu vyčistením projektu](../../../clean-up.md).

## Preklad textu

Preklad textu je problém informatiky, ktorý sa skúma už viac ako 70 rokov, a až vďaka pokrokom v AI a výpočtovom výkone sa blíži k riešeniu, ktoré je takmer rovnako dobré ako ľudskí prekladatelia.

> 💁 Pôvod tohto problému možno vystopovať ešte ďalej, až k [Al-Kindímu](https://wikipedia.org/wiki/Al-Kindi), arabskému kryptografovi z 9. storočia, ktorý vyvinul techniky pre preklad jazykov.

### Strojové preklady

Preklad textu začal ako technológia známa ako strojový preklad (Machine Translation, MT), ktorá dokáže prekladať medzi rôznymi jazykovými pármi. MT funguje nahrádzaním slov v jednom jazyku inými slovami, pričom používa techniky na výber správnych spôsobov prekladu fráz alebo častí viet, keď jednoduchý preklad slovo za slovom nedáva zmysel.

> 🎓 Keď prekladatelia podporujú preklad medzi jedným jazykom a druhým, tieto sa nazývajú *jazykové páry*. Rôzne nástroje podporujú rôzne jazykové páry, a tieto nemusia byť kompletné. Napríklad prekladateľ môže podporovať angličtinu do španielčiny ako jazykový pár a španielčinu do taliančiny ako jazykový pár, ale nie angličtinu do taliančiny.

Napríklad preklad „Hello world“ z angličtiny do francúzštiny možno vykonať nahradením – „Bonjour“ za „Hello“ a „le monde“ za „world“, čo vedie k správnemu prekladu „Bonjour le monde“.

Nahrádzanie však nefunguje, keď rôzne jazyky používajú odlišné spôsoby vyjadrenia tej istej veci. Napríklad anglická veta „My name is Jim“ sa prekladá do francúzštiny ako „Je m'appelle Jim“ – doslova „Volám sa Jim“. „Je“ je francúzske „ja“, „moi“ je „mňa“, ale je spojené so slovesom, pretože začína samohláskou, takže sa stáva „m'“, „appelle“ znamená volať a „Jim“ sa neprekladá, pretože je to meno, a nie slovo, ktoré možno preložiť. Problémom sa stáva aj poradie slov – jednoduché nahradenie „Je m'appelle Jim“ sa stáva „I myself call Jim“, s odlišným poradím slov ako v angličtine.

> 💁 Niektoré slová sa nikdy neprekladajú – moje meno je Jim bez ohľadu na to, aký jazyk sa použije na predstavenie. Pri preklade do jazykov, ktoré používajú odlišné abecedy alebo rôzne písmená pre rôzne zvuky, môžu byť slová *transliterované*, teda vybrané písmená alebo znaky, ktoré zodpovedajú zvuku daného slova.

Idiómy sú tiež problémom pre preklad. Ide o frázy, ktoré majú chápaný význam odlišný od priamej interpretácie slov. Napríklad v angličtine idióm „I've got ants in my pants“ neznamená doslova, že máte mravce v oblečení, ale že ste nepokojní. Ak by ste to preložili do nemčiny, poslucháča by ste zmiatli, pretože nemecká verzia je „Ich habe Hummeln im Hintern“ (Mám čmeliaky v zadku).

> 💁 Rôzne lokality pridávajú rôzne zložitosti. Pri idióme „ants in your pants“ v americkej angličtine „pants“ znamená vrchné oblečenie, v britskej angličtine „pants“ znamená spodnú bielizeň.

✅ Ak hovoríte viacerými jazykmi, zamyslite sa nad niektorými frázami, ktoré sa nedajú priamo preložiť.

Systémy strojového prekladu sa spoliehajú na veľké databázy pravidiel, ktoré popisujú, ako prekladať určité frázy a idiómy, spolu so štatistickými metódami na výber vhodných prekladov z možných možností. Tieto štatistické metódy využívajú obrovské databázy diel preložených ľuďmi do viacerých jazykov na výber najpravdepodobnejšieho prekladu, techniku nazývanú *štatistický strojový preklad*. Mnohé z nich používajú medzireprezentácie jazyka, čo umožňuje preklad z jedného jazyka do medzireprezentácie a potom z medzireprezentácie do iného jazyka. Týmto spôsobom pridanie ďalších jazykov zahŕňa preklady do a z medzireprezentácie, nie do a zo všetkých ostatných jazykov.

### Neurónové preklady

Neurónové preklady využívajú silu AI na preklad, zvyčajne prekladajú celé vety pomocou jedného modelu. Tieto modely sú trénované na obrovských dátových súboroch, ktoré boli preložené ľuďmi, ako sú webové stránky, knihy a dokumentácia OSN.

Modely neurónového prekladu sú zvyčajne menšie ako modely strojového prekladu, pretože nepotrebujú obrovské databázy fráz a idiómov. Moderné AI služby, ktoré poskytujú preklady, často kombinujú viaceré techniky, miešajúc štatistický strojový preklad a neurónový preklad.

Neexistuje 1:1 preklad pre žiadny jazykový pár. Rôzne prekladové modely budú produkovať mierne odlišné výsledky v závislosti od údajov použitých na trénovanie modelu. Preklady nie sú vždy symetrické – ak preložíte vetu z jedného jazyka do druhého a potom späť do prvého jazyka, môžete vidieť mierne odlišnú vetu ako výsledok.

✅ Vyskúšajte rôzne online prekladače, ako napríklad [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) alebo aplikáciu Apple Translate. Porovnajte preložené verzie niekoľkých viet. Skúste tiež preložiť v jednom a potom preložiť späť v inom.

## Prekladateľské služby

Existuje množstvo AI služieb, ktoré môžete použiť vo svojich aplikáciách na preklad reči a textu.

### Kognitívne služby – Služba reči

![Logo služby reči](../../../../../translated_images/sk/azure-speech-logo.a1f08c4befb0159f.webp)

Služba reči, ktorú ste používali v predchádzajúcich lekciách, má schopnosti prekladu pre rozpoznávanie reči. Keď rozpoznávate reč, môžete požiadať nielen o text reči v rovnakom jazyku, ale aj v iných jazykoch.

> 💁 Toto je dostupné iba prostredníctvom SDK služby reči, REST API nemá zabudované preklady.

### Kognitívne služby – Služba Translator

![Logo služby Translator](../../../../../translated_images/sk/azure-translator-logo.c6ed3a4a433edfd2.webp)

Služba Translator je špecializovaná prekladateľská služba, ktorá dokáže prekladať text z jedného jazyka do jedného alebo viacerých cieľových jazykov. Okrem prekladu podporuje širokú škálu ďalších funkcií, vrátane maskovania vulgarizmov. Umožňuje vám tiež poskytnúť konkrétny preklad pre určité slovo alebo vetu, aby ste mohli pracovať s termínmi, ktoré nechcete prekladať, alebo mať konkrétny, dobre známy preklad.

Napríklad pri preklade vety „I have a Raspberry Pi“, ktorá sa týka jednodeskového počítača, do iného jazyka, ako je francúzština, by ste chceli ponechať názov „Raspberry Pi“ nezmenený, a nie ho prekladať, čím by ste dostali „J’ai un Raspberry Pi“ namiesto „J’ai une pi aux framboises“.

## Vytvorenie prekladateľského zdroja

Pre túto lekciu budete potrebovať zdroj Translator. Na preklad textu použijete REST API.

### Úloha – vytvorenie prekladateľského zdroja

1. Vo svojom termináli alebo príkazovom riadku spustite nasledujúci príkaz na vytvorenie prekladateľského zdroja v skupine zdrojov `smart-timer`.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Nahraďte `<location>` miestom, ktoré ste použili pri vytváraní skupiny zdrojov.

1. Získajte kľúč pre službu Translator:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Skopírujte si jeden z kľúčov.

## Podpora viacerých jazykov v aplikáciách pomocou prekladov

V ideálnom svete by celá vaša aplikácia mala rozumieť čo najväčšiemu počtu rôznych jazykov, od počúvania reči, cez porozumenie jazyku, až po odpovedanie rečou. Toto je však veľa práce, takže prekladateľské služby môžu urýchliť čas dodania vašej aplikácie.

![Architektúra inteligentného časovača prekladajúca japončinu do angličtiny, spracovanie v angličtine a preklad späť do japončiny](../../../../../translated_images/sk/translated-smart-timer.08ac20057fdc5c37.webp)

Predstavte si, že vytvárate inteligentný časovač, ktorý používa angličtinu od začiatku do konca, rozumie hovorenému anglickému jazyku a prevádza ho na text, vykonáva porozumenie jazyka v angličtine, vytvára odpovede v angličtine a odpovedá hovorenou angličtinou. Ak by ste chceli pridať podporu pre japončinu, mohli by ste začať prekladom hovoreného japonského jazyka na anglický text, potom ponechať jadro aplikácie rovnaké a potom preložiť odpoveď na text do japončiny predtým, ako ju vyslovíte. To by vám umožnilo rýchlo pridať podporu pre japončinu a neskôr môžete rozšíriť aplikáciu na plnú podporu japončiny od začiatku do konca.

> 💁 Nevýhodou spoliehania sa na strojový preklad je, že rôzne jazyky a kultúry majú rôzne spôsoby vyjadrovania tých istých vecí, takže preklad nemusí zodpovedať výrazu, ktorý očakávate.

Strojové preklady tiež otvárajú možnosti pre aplikácie a zariadenia, ktoré dokážu prekladať obsah vytvorený používateľmi v reálnom čase. Vedecká fantastika často obsahuje „univerzálne prekladače“, zariadenia, ktoré dokážu prekladať z mimozemských jazykov do (zvyčajne) americkej angličtiny. Tieto zariadenia sú menej vedeckou fantastikou a viac vedeckým faktom, ak ignorujeme mimozemskú časť. Už existujú aplikácie a zariadenia, ktoré poskytujú preklad reči a písaného textu v reálnom čase, s využitím kombinácií služieb reči a prekladu.

Jedným z príkladov je mobilná aplikácia [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn), demonštrovaná v tomto videu:

[![Funkcia Microsoft Translator live v akcii](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Kliknite na obrázok vyššie pre prehratie videa

Predstavte si, že máte takéto zariadenie k dispozícii, najmä pri cestovaní alebo interakcii s ľuďmi, ktorých jazyk nepoznáte. Automatické prekladateľské zariadenia na letiskách alebo v nemocniciach by poskytli veľmi potrebné zlepšenia prístupnosti.

✅ Urobte si prieskum: Existujú nejaké komerčne dostupné IoT zariadenia na preklad? Čo tak prekladateľské schopnosti zabudované do inteligentných zariadení?

> 👽 Aj keď neexistujú skutočné univerzálne prekladače, ktoré by nám umožnili hovoriť s mimozemšťanmi, [Microsoft Translator podporuje klingončinu](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Preklad textu pomocou AI služby

Môžete použiť AI službu na pridanie tejto prekladateľskej schopnosti do vášho inteligentného časovača.

### Úloha – preklad textu pomocou AI služby

Postupujte podľa príslušného sprievodcu na preklad textu na vašom IoT zariadení:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Jednodeskový počítač - Raspberry Pi](pi-translate-speech.md)
* [Jednodeskový počítač - Virtuálne zariadenie](virtual-device-translate-speech.md)

---

## 🚀 Výzva

Ako môžu strojové preklady prospieť iným IoT aplikáciám okrem inteligentných zariadení? Zamyslite sa nad rôznymi spôsobmi, ako môžu preklady pomôcť, nielen pri hovorených slovách, ale aj pri texte.

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Prehľad a samostatné štúdium

* Prečítajte si viac o strojovom preklade na [stránke o strojovom preklade na Wikipédii](https://wikipedia.org/wiki/Machine_translation)
* Prečítajte si viac o neurónovom strojovom preklade na [stránke o neurónovom strojovom preklade na Wikipédii](https://wikipedia.org/wiki/Neural_machine_translation)
* Pozrite si zoznam podporovaných jazykov pre služby Microsoft reči v [dokumentácii o podpore jazykov a hlasov pre službu reči na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)



---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.