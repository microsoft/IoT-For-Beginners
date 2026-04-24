# Palaikykite kelias kalbas

![Šios pamokos apžvalga sketchnote formatu](../../../../../translated_images/lt/lesson-24.4246968ed058510a.webp)

> Sketchnote sukūrė [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

Šiame vaizdo įraše pateikiama „Azure“ kalbos paslaugų apžvalga, apimanti kalbos pavertimą tekstu ir teksto pavertimą kalba iš ankstesnių pamokų, taip pat kalbos vertimą – tema, aptariama šioje pamokoje:

[![Kalbos atpažinimas naudojant kelias „Python“ kodo eilutes iš „Microsoft Build 2020“](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Spustelėkite paveikslėlį aukščiau, kad peržiūrėtumėte vaizdo įrašą

## Prieš pamoką – testas

[Prieš pamoką – testas](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Įvadas

Per pastarąsias 3 pamokas sužinojote apie kalbos pavertimą tekstu, kalbos supratimą ir teksto pavertimą kalba, viskas paremta dirbtiniu intelektu. Kita žmogaus komunikacijos sritis, kurioje dirbtinis intelektas gali padėti, yra kalbos vertimas – pavertimas iš vienos kalbos į kitą, pavyzdžiui, iš anglų į prancūzų.

Šioje pamokoje sužinosite, kaip naudoti dirbtinį intelektą tekstui versti, leidžiant jūsų išmaniam laikmačiui bendrauti su vartotojais įvairiomis kalbomis.

Šioje pamokoje aptarsime:

* [Teksto vertimas](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Vertimo paslaugos](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Vertėjo resurso sukūrimas](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Palaikykite kelias kalbas programose su vertimais](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Teksto vertimas naudojant dirbtinio intelekto paslaugą](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Tai paskutinė pamoka šiame projekte, todėl baigę pamoką ir užduotį nepamirškite išvalyti savo debesų paslaugų. Jums reikės paslaugų užduočiai atlikti, todėl pirmiausia įsitikinkite, kad ją atlikote.
>
> Jei reikia, kreipkitės į [projekto valymo vadovą](../../../clean-up.md), kad gautumėte instrukcijas, kaip tai padaryti.

## Teksto vertimas

Teksto vertimas buvo kompiuterių mokslo problema, kuri buvo tyrinėjama daugiau nei 70 metų, ir tik dabar, dėka dirbtinio intelekto ir kompiuterių galios pažangos, jis yra beveik išspręstas iki tokio lygio, kad yra beveik toks pat geras kaip žmogaus vertėjų.

> 💁 Šaknys siekia dar toliau – iki [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), IX amžiaus arabų kriptografo, kuris sukūrė kalbos vertimo technikas.

### Mašininiai vertimai

Teksto vertimas prasidėjo kaip technologija, vadinama mašininiu vertimu (MT), kuri gali versti tarp skirtingų kalbų porų. MT veikia pakeičiant žodžius iš vienos kalbos į kitą, pridedant technikas, kurios parenka tinkamus būdus versti frazes ar sakinių dalis, kai paprastas žodis po žodžio vertimas neturi prasmės.

> 🎓 Kai vertėjai palaiko vertimą tarp vienos kalbos ir kitos, tai vadinama *kalbų poromis*. Skirtingi įrankiai palaiko skirtingas kalbų poras, ir jos gali būti ne pilnos. Pavyzdžiui, vertėjas gali palaikyti anglų į ispanų kaip kalbų porą, ir ispanų į italų kaip kalbų porą, bet ne anglų į italų.

Pavyzdžiui, verčiant „Hello world“ iš anglų į prancūzų kalbą galima atlikti pakeitimą – „Bonjour“ vietoj „Hello“ ir „le monde“ vietoj „world“, gaunant teisingą vertimą „Bonjour le monde“.

Pakeitimai neveikia, kai skirtingos kalbos naudoja skirtingus būdus pasakyti tą patį dalyką. Pavyzdžiui, angliškas sakinys „My name is Jim“ verčiamas į „Je m'appelle Jim“ prancūzų kalba – pažodžiui „Aš vadinuosi Jim“. „Je“ yra prancūziškai „aš“, „moi“ yra „mane“, bet yra sujungtas su veiksmažodžiu, nes prasideda balsiu, todėl tampa „m'“, „appelle“ reiškia „vadinti“, o „Jim“ nėra verčiamas, nes tai vardas, o ne žodis, kurį galima išversti. Žodžių tvarka taip pat tampa problema – paprastas „Je m'appelle Jim“ pakeitimas tampa „Aš save vadinu Jim“, su kitokia žodžių tvarka nei anglų kalboje.

> 💁 Kai kurie žodžiai niekada nėra verčiami – mano vardas yra Jim, nepriklausomai nuo to, kokia kalba aš prisistatau. Verčiant į kalbas, kurios naudoja skirtingus alfabetus arba skirtingas raides skirtingiems garsams, žodžiai gali būti *transliteruojami*, tai yra parenkami raidės ar simboliai, kurie suteikia tinkamą garsą, kad skambėtų taip pat kaip duotas žodis.

Idiomos taip pat yra problema vertimui. Tai frazės, kurios turi suprantamą reikšmę, skirtingą nuo tiesioginio žodžių interpretavimo. Pavyzdžiui, angliška idioma „I've got ants in my pants“ tiesiogiai nereiškia, kad jūsų drabužiuose yra skruzdėlių, bet kad esate neramus. Jei tai išverstumėte į vokiečių kalbą, klausytojas būtų sutrikęs, nes vokiečių versija yra „Aš turiu kamanes užpakalyje“.

> 💁 Skirtingi regionai prideda skirtingus sudėtingumus. Su idioma „ants in your pants“, amerikietiškoje anglų kalboje „pants“ reiškia viršutinius drabužius, britų anglų kalboje „pants“ yra apatiniai drabužiai.

✅ Jei kalbate keliomis kalbomis, pagalvokite apie frazes, kurios tiesiogiai neišverčiamos.

Mašininio vertimo sistemos remiasi didelėmis taisyklių duomenų bazėmis, kurios aprašo, kaip versti tam tikras frazes ir idiomas, kartu su statistiniais metodais, kurie parenka tinkamus vertimus iš galimų variantų. Šie statistiniai metodai naudoja didžiules žmonių išverstų darbų duomenų bazes į kelias kalbas, kad parinktų labiausiai tikėtiną vertimą, techniką, vadinamą *statistiniu mašininiu vertimu*. Kai kurie iš jų naudoja tarpinį kalbos atvaizdavimą, leidžiantį vieną kalbą išversti į tarpinę, o tada iš tarpinės į kitą kalbą. Tokiu būdu pridėti daugiau kalbų reiškia vertimus į ir iš tarpinės, o ne į ir iš visų kitų kalbų.

### Neuroniniai vertimai

Neuroniniai vertimai apima dirbtinio intelekto galią versti, paprastai verčiant visus sakinius naudojant vieną modelį. Šie modeliai yra mokomi naudojant didžiulius duomenų rinkinius, kuriuos išvertė žmonės, pavyzdžiui, tinklalapius, knygas ir Jungtinių Tautų dokumentus.

Neuroniniai vertimo modeliai paprastai yra mažesni nei mašininio vertimo modeliai, nes jiems nereikia didžiulių frazių ir idiomų duomenų bazių. Šiuolaikinės dirbtinio intelekto paslaugos, teikiančios vertimus, dažnai derina kelias technikas, maišydamos statistinį mašininį vertimą ir neuroninį vertimą.

Nėra 1:1 vertimo jokiai kalbų porai. Skirtingi vertimo modeliai pateiks šiek tiek skirtingus rezultatus, priklausomai nuo duomenų, naudotų modelio mokymui. Vertimai ne visada yra simetriški – tai reiškia, kad jei išversite sakinį iš vienos kalbos į kitą, o tada atgal į pirmąją kalbą, galite gauti šiek tiek kitokį sakinį kaip rezultatą.

✅ Išbandykite skirtingus internetinius vertėjus, tokius kaip [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) arba „Apple“ vertimo programėlę. Palyginkite kelių sakinių vertimo versijas. Taip pat pabandykite išversti viename, o tada kitame išversti atgal.

## Vertimo paslaugos

Yra keletas dirbtinio intelekto paslaugų, kurias galima naudoti jūsų programose kalbai ir tekstui versti.

### „Cognitive Services“ kalbos paslauga

![Kalbos paslaugos logotipas](../../../../../translated_images/lt/azure-speech-logo.a1f08c4befb0159f.webp)

Kalbos paslauga, kurią naudojote per pastarąsias pamokas, turi vertimo galimybes kalbos atpažinimui. Kai atpažįstate kalbą, galite prašyti ne tik kalbos teksto ta pačia kalba, bet ir kitomis kalbomis.

> 💁 Tai galima tik naudojant kalbos SDK, REST API neturi integruotų vertimų.

### „Cognitive Services“ vertėjo paslauga

![Vertėjo paslaugos logotipas](../../../../../translated_images/lt/azure-translator-logo.c6ed3a4a433edfd2.webp)

Vertėjo paslauga yra specializuota vertimo paslauga, kuri gali versti tekstą iš vienos kalbos į vieną ar daugiau tikslinių kalbų. Be vertimo, ji palaiko daugybę papildomų funkcijų, įskaitant keiksmažodžių maskavimą. Ji taip pat leidžia jums pateikti konkretų vertimą tam tikram žodžiui ar sakiniui, kad galėtumėte dirbti su terminais, kurių nenorite versti, arba turėti konkretų gerai žinomą vertimą.

Pavyzdžiui, verčiant sakinį „Aš turiu Raspberry Pi“, nurodant vieno plokštės kompiuterį, į kitą kalbą, pavyzdžiui, prancūzų, norėtumėte palikti pavadinimą „Raspberry Pi“ tokį, koks yra, ir neversti jo, gaunant „J’ai un Raspberry Pi“ vietoj „J’ai une pi aux framboises“.

## Vertėjo resurso sukūrimas

Šiai pamokai jums reikės vertėjo resurso. Naudosite REST API tekstui versti.

### Užduotis – sukurti vertėjo resursą

1. Iš savo terminalo arba komandų eilutės paleiskite šią komandą, kad sukurtumėte vertėjo resursą savo `smart-timer` resursų grupėje.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Pakeiskite `<location>` vieta, kurią naudojote kurdami resursų grupę.

1. Gaukite vertėjo paslaugos raktą:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Nukopijuokite vieną iš raktų.

## Palaikykite kelias kalbas programose su vertimais

Idealiame pasaulyje visa jūsų programa turėtų suprasti kuo daugiau skirtingų kalbų – nuo kalbos klausymo iki kalbos supratimo ir atsakymo kalba. Tai reikalauja daug darbo, todėl vertimo paslaugos gali pagreitinti jūsų programos pristatymo laiką.

![Išmaniojo laikmačio architektūra, verčianti japonų kalbą į anglų, apdorojanti anglų kalba, o tada verčianti atgal į japonų](../../../../../translated_images/lt/translated-smart-timer.08ac20057fdc5c37.webp)

Įsivaizduokite, kad kuriate išmanųjį laikmatį, kuris naudoja anglų kalbą nuo pradžios iki pabaigos, supranta sakomą anglų kalbą ir paverčia ją tekstu, vykdo kalbos supratimą anglų kalba, kuria atsakymus anglų kalba ir atsako anglų kalbos kalba. Jei norėtumėte pridėti japonų kalbos palaikymą, galėtumėte pradėti nuo sakomos japonų kalbos vertimo į anglų tekstą, tada palikti pagrindinę programos dalį tokią pačią, o tada išversti atsakymo tekstą į japonų kalbą prieš sakant atsakymą. Tai leistų greitai pridėti japonų kalbos palaikymą, o vėliau galėtumėte išplėsti iki pilno japonų kalbos palaikymo nuo pradžios iki pabaigos.

> 💁 Neigiama mašininio vertimo pusė yra ta, kad skirtingos kalbos ir kultūros turi skirtingus būdus pasakyti tuos pačius dalykus, todėl vertimas gali neatitikti jūsų tikėtinos išraiškos.

Mašininiai vertimai taip pat atveria galimybes programoms ir įrenginiams, kurie gali versti vartotojo sukurtą turinį, kai jis yra kuriamas. Mokslinė fantastika dažnai vaizduoja „universalius vertėjus“, įrenginius, kurie gali versti iš ateivių kalbų į (dažniausiai) amerikietišką anglų kalbą. Šie įrenginiai yra mažiau mokslinė fantastika, daugiau mokslinis faktas, jei ignoruosime ateivių dalį. Jau yra programų ir įrenginių, kurie teikia realaus laiko kalbos ir rašytinio teksto vertimą, naudojant kalbos ir vertimo paslaugų derinius.

Vienas pavyzdys yra [„Microsoft Translator“](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn) mobiliojo telefono programėlė, pademonstruota šiame vaizdo įraše:

[![„Microsoft Translator“ tiesioginio funkcionalumo demonstracija](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Spustelėkite paveikslėlį aukščiau, kad peržiūrėtumėte vaizdo įrašą

Įsivaizduokite, kad turite tokį įrenginį, ypač keliaudami ar bendraudami su žmonėmis, kurių kalbos nemokate. Automatinio vertimo įrenginiai oro uostuose ar ligoninėse suteiktų labai reikalingus prieinamumo patobulinimus.

✅ Atlikite tyrimą: Ar yra komerciškai prieinamų vertimo IoT įrenginių? O kaip dėl vertimo galimybių, integruotų į išmaniuosius įrenginius?

> 👽 Nors nėra tikrų universalių vertėjų, leidžiančių mums kalbėtis su ateiviais, [„Microsoft Translator“ palaiko klingonų kalbą](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Teksto vertimas naudojant dirbtinio intelekto paslaugą

Galite naudoti dirbtinio intelekto paslaugą, kad pridėtumėte šią vertimo funkciją prie savo išmaniojo laikmačio.

### Užduotis – teksto vertimas naudojant dirbtinio intelekto paslaugą

Atlikite atitinkamą vadovą, kad išmoktumėte versti tekstą savo IoT įrenginyje:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Vieno plokštės kompiuteris - Raspberry Pi](pi-translate-speech.md)
* [Vieno plokštės kompiuteris - Virtualus įrenginys](virtual-device-translate-speech.md)

---

## 🚀 Iššūkis

Kaip mašininiai vertimai gali būti naudingi kitoms IoT programoms, ne tik išmaniesiems įrenginiams? Pagalvokite apie skirtingus būdus, kaip vertimai gali padėti, ne tik su sakomais žodžiais, bet ir su tekstu.

## Po pamokos – testas

[Po pamokos – testas](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Apžvalga ir savarankiškas mokymasis

* Skaitykite daugiau apie mašininį vertimą [mašininio vertimo puslapyje „Wikipedia“](https://wikipedia.org/wiki/Machine_translation)
* Ska

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.