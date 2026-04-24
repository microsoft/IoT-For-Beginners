# Sukurkite vaisių kokybės detektorių

![Šios pamokos apžvalga pieštuku](../../../../../translated_images/lt/lesson-15.843d21afdc6fb2bb.webp)

> Piešinys sukurtas [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

Šiame vaizdo įraše pateikiama Azure Custom Vision paslaugos apžvalga, kuri bus aptarta šioje pamokoje.

[![Custom Vision – Mašininis mokymasis paprastai | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 Spustelėkite aukščiau esantį paveikslėlį, kad peržiūrėtumėte vaizdo įrašą

## Klausimynas prieš paskaitą

[Klausimynas prieš paskaitą](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## Įvadas

Pastaruoju metu dirbtinio intelekto (DI) ir mašininio mokymosi (MM) plėtra suteikia šiuolaikiniams kūrėjams daugybę galimybių. MM modeliai gali būti apmokyti atpažinti įvairius dalykus nuotraukose, įskaitant neprinokusius vaisius, ir tai gali būti naudojama IoT įrenginiuose, kad padėtų rūšiuoti derlių tiek jo nuėmimo metu, tiek perdirbant fabrikuose ar sandėliuose.

Šioje pamokoje sužinosite apie vaizdų klasifikavimą – kaip naudoti MM modelius, kad atskirtumėte skirtingų objektų nuotraukas. Sužinosite, kaip apmokyti vaizdų klasifikatorių atskirti gerus vaisius nuo blogų – pernokusių, neprinokusių, pažeistų ar supuvusių.

Šioje pamokoje aptarsime:

* [DI ir MM naudojimas maisto rūšiavimui](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Vaizdų klasifikavimas naudojant mašininį mokymąsi](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Kaip apmokyti vaizdų klasifikatorių](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Kaip išbandyti savo vaizdų klasifikatorių](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Kaip perapmokyti savo vaizdų klasifikatorių](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## DI ir MM naudojimas maisto rūšiavimui

Pamaitinti pasaulio gyventojus yra sudėtinga užduotis, ypač užtikrinant, kad maistas būtų prieinamas visiems. Viena didžiausių išlaidų yra darbo jėga, todėl ūkininkai vis dažniau renkasi automatizavimą ir IoT įrankius, kad sumažintų darbo sąnaudas. Rankinis derliaus nuėmimas yra labai darbo imlus (ir dažnai fiziškai sunkus darbas), todėl jis vis dažniau pakeičiamas technika, ypač turtingesnėse šalyse. Nepaisant mažesnių derliaus nuėmimo technikos sąnaudų, yra ir trūkumų – pavyzdžiui, maisto rūšiavimo galimybė derliaus nuėmimo metu.

Ne visi augalai sunoksta vienodai. Pavyzdžiui, pomidorai gali turėti dar žalių vaisių ant šakų, kai dauguma jau yra prinokę. Nors ankstyvas jų nuėmimas yra švaistymas, ūkininkui yra pigiau ir lengviau nuimti viską naudojant techniką ir vėliau atsikratyti neprinokusio derliaus.

✅ Pažvelkite į įvairius vaisius ar daržoves, augančius netoliese esančiuose ūkiuose, savo sode ar parduotuvėse. Ar jie visi vienodai prinokę, ar pastebite skirtumų?

Automatizuotas derliaus nuėmimas perkėlė maisto rūšiavimą iš lauko į fabriką. Maistas keliaudavo ilgais konvejeriais, o žmonių komandos rankomis pašalindavo viską, kas neatitiko kokybės standartų. Derliaus nuėmimas tapo pigesnis dėl technikos, tačiau maisto rūšiavimas rankomis vis dar kainavo.

![Jei aptinkamas raudonas pomidoras, jis keliauja toliau. Jei aptinkamas žalias pomidoras, jis svirtimi išmetamas į atliekų dėžę](../../../../../translated_images/lt/optical-tomato-sorting.61aa134bdda4e5b1.webp)

Kitas evoliucijos etapas buvo mašinų naudojimas rūšiavimui, įmontuotų į derliaus nuėmimo techniką arba naudojamų perdirbimo gamyklose. Pirmosios šių mašinų kartos naudojo optinius jutiklius spalvoms aptikti, valdančius svirtis ar oro pūtimo įrenginius, kad žali pomidorai būtų pašalinti į atliekų dėžę, o raudoni pomidorai tęstų kelionę konvejeriais.

Šiame vaizdo įraše, kai pomidorai krenta nuo vieno konvejerio ant kito, žali pomidorai aptinkami ir svirtimis pašalinami į dėžę.

✅ Kokios sąlygos būtų reikalingos fabrike ar lauke, kad šie optiniai jutikliai veiktų tinkamai?

Naujausios šių rūšiavimo mašinų evoliucijos pasitelkia DI ir MM, naudodamos modelius, apmokytus atskirti gerą derlių nuo blogo ne tik pagal akivaizdžius spalvų skirtumus, tokius kaip žali pomidorai prieš raudonus, bet ir pagal subtilesnius išvaizdos skirtumus, kurie gali rodyti ligas ar pažeidimus.

## Vaizdų klasifikavimas naudojant mašininį mokymąsi

Tradicinis programavimas yra tada, kai jūs imate duomenis, taikote jiems algoritmą ir gaunate rezultatą. Pavyzdžiui, ankstesniame projekte jūs naudojote GPS koordinates ir geografinę zoną, taikėte Azure Maps pateiktą algoritmą ir gavote rezultatą, ar taškas yra zonos viduje, ar išorėje. Įvedate daugiau duomenų, gaunate daugiau rezultatų.

![Tradicinis kūrimas naudoja įvestį ir algoritmą, kad gautų rezultatą. Mašininis mokymasis naudoja įvesties ir išvesties duomenis, kad apmokytų modelį, kuris gali naudoti naujus įvesties duomenis naujiems rezultatams generuoti](../../../../../translated_images/lt/traditional-vs-ml.5c20c169621fa539.webp)

Mašininis mokymasis tai apverčia – jūs pradedate nuo duomenų ir žinomų rezultatų, o mašininio mokymosi algoritmas mokosi iš duomenų. Tada galite naudoti šį apmokytą algoritmą, vadinamą *mašininio mokymosi modeliu* arba *modeliu*, ir įvesti naujus duomenis, kad gautumėte naujus rezultatus.

> 🎓 Procesas, kai mašininio mokymosi algoritmas mokosi iš duomenų, vadinamas *mokymu*. Įvesties ir žinomi rezultatai vadinami *mokymo duomenimis*.

Pavyzdžiui, galite pateikti modeliui milijonus neprinokusių bananų nuotraukų kaip mokymo duomenis, su mokymo rezultatu `neprinokęs`, ir milijonus prinokusių bananų nuotraukų su rezultatu `prinokęs`. MM algoritmas sukurs modelį pagal šiuos duomenis. Tada pateiksite šiam modeliui naują banano nuotrauką, ir jis prognozuos, ar nauja nuotrauka yra prinokęs, ar neprinokęs bananas.

> 🎓 MM modelių rezultatai vadinami *prognozėmis*

![2 bananai: prinokęs su prognoze 99,7% prinokęs, 0,3% neprinokęs, ir neprinokęs su prognoze 1,4% prinokęs, 98,6% neprinokęs](../../../../../translated_images/lt/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50e.webp)

MM modeliai nepateikia binarinio atsakymo, o pateikia tikimybes. Pavyzdžiui, modelis gali gauti banano nuotrauką ir prognozuoti `prinokęs` su 99,7% tikimybe ir `neprinokęs` su 0,3% tikimybe. Jūsų kodas tada pasirinktų geriausią prognozę ir nuspręstų, kad bananas yra prinokęs.

MM modelis, naudojamas tokiems vaizdams aptikti, vadinamas *vaizdų klasifikatoriumi* – jis gauna pažymėtas nuotraukas ir klasifikuoja naujas nuotraukas pagal šiuos žymėjimus.

> 💁 Tai yra supaprastinimas, ir yra daug kitų būdų apmokyti modelius, kurie ne visada reikalauja pažymėtų rezultatų, pavyzdžiui, nesupervizuotas mokymasis. Jei norite sužinoti daugiau apie MM, peržiūrėkite [ML pradedantiesiems – 24 pamokų mokymo programą apie mašininį mokymąsi](https://aka.ms/ML-beginners).

## Kaip apmokyti vaizdų klasifikatorių

Norint sėkmingai apmokyti vaizdų klasifikatorių, reikia milijonų nuotraukų. Tačiau, kai jau turite vaizdų klasifikatorių, apmokytą milijonais ar milijardais įvairių nuotraukų, galite jį pernaudoti ir perapmokyti naudodami nedidelį nuotraukų rinkinį, pasitelkdami procesą, vadinamą *perdavimo mokymusi*.

> 🎓 Perdavimo mokymasis yra procesas, kai jau egzistuojančio MM modelio mokymasis perkeliamas į naują modelį, pagrįstą naujais duomenimis.

Kai vaizdų klasifikatorius yra apmokytas atpažinti įvairias nuotraukas, jo vidiniai mechanizmai puikiai atpažįsta formas, spalvas ir raštus. Perdavimo mokymasis leidžia modeliui panaudoti jau įgytas žinias apie vaizdų dalis ir pritaikyti jas naujų vaizdų atpažinimui.

![Kai atpažįstate formas, jas galima sudėlioti į skirtingas konfigūracijas, kad sudarytumėte laivą arba katę](../../../../../translated_images/lt/shapes-to-images.1a309f0ea88dd66f.webp)

Galite tai įsivaizduoti kaip vaikų knygas apie formas, kur, kai jau atpažįstate puslankį, stačiakampį ir trikampį, galite atpažinti burlaivį arba katę, priklausomai nuo šių formų išdėstymo. Vaizdų klasifikatorius gali atpažinti formas, o perdavimo mokymasis moko, kokia kombinacija sudaro laivą ar katę – arba prinokusį bananą.

Yra daugybė įrankių, kurie gali padėti tai padaryti, įskaitant debesų paslaugas, kurios leidžia apmokyti modelį ir naudoti jį per žiniatinklio API.

> 💁 Šių modelių mokymas reikalauja daug kompiuterinės galios, dažniausiai naudojant grafikos procesorius (GPU). Ta pati specializuota įranga, kuri leidžia jūsų Xbox žaidimams atrodyti įspūdingai, taip pat gali būti naudojama mokyti mašininio mokymosi modelius. Naudodamiesi debesų paslaugomis, galite išsinuomoti galingus kompiuterius su GPU tik tam laikui, kurio jums reikia.

## Custom Vision

Custom Vision yra debesų įrankis, skirtas vaizdų klasifikatorių mokymui. Jis leidžia apmokyti klasifikatorių naudojant tik nedidelį nuotraukų kiekį. Galite įkelti nuotraukas per žiniatinklio portalą, API arba SDK, kiekvienai nuotraukai priskirdami *žymą*, kuri nurodo tos nuotraukos klasifikaciją. Tada galite apmokyti modelį ir išbandyti, kaip gerai jis veikia. Kai būsite patenkinti modeliu, galėsite jį publikuoti ir naudoti per žiniatinklio API arba SDK.

![Azure Custom Vision logotipas](../../../../../translated_images/lt/custom-vision-logo.d3d4e7c8a87ec9da.webp)

> 💁 Galite apmokyti Custom Vision modelį naudodami vos 5 nuotraukas kiekvienai klasifikacijai, tačiau daugiau nuotraukų duoda geresnius rezultatus. Geriausia turėti bent 30 nuotraukų.

Custom Vision yra dalis Microsoft DI įrankių rinkinio, vadinamo Cognitive Services. Tai DI įrankiai, kuriuos galima naudoti be jokio mokymo arba su nedideliu mokymu. Jie apima kalbos atpažinimą ir vertimą, kalbos supratimą ir vaizdų analizę. Šios paslaugos yra prieinamos su nemokamu planu Azure platformoje.

> 💁 Nemokamas planas yra pakankamas modelio kūrimui, mokymui ir naudojimui kūrimo darbams. Apie nemokamo plano apribojimus galite skaityti [Custom Vision Limits and quotas puslapyje Microsoft dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn).

### Užduotis – sukurkite Cognitive Services išteklių

Norėdami naudoti Custom Vision, pirmiausia turite sukurti du Cognitive Services išteklius Azure platformoje naudodami Azure CLI: vieną Custom Vision mokymui ir kitą Custom Vision prognozėms.

1. Sukurkite šiam projektui skirtą išteklių grupę, pavadintą `fruit-quality-detector`.

1. Naudokite šią komandą, kad sukurtumėte nemokamą Custom Vision mokymo išteklių:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Pakeiskite `<location>` vieta, kurią naudojote kurdami išteklių grupę.

    Tai sukurs Custom Vision mokymo išteklių jūsų išteklių grupėje. Jis bus pavadintas `fruit-quality-detector-training` ir naudos `F0` SKU, kuris yra nemokamas planas. `--yes` parinktis reiškia, kad sutinkate su Cognitive Services sąlygomis.

> 💁 Naudokite `S0` SKU, jei jau turite nemokamą paskyrą, naudojančią bet kurią Cognitive Services paslaugą.

1. Naudokite šią komandą, kad sukurtumėte nemokamą Custom Vision prognozės išteklių:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Pakeiskite `<location>` vieta, kurią naudojote kurdami išteklių grupę.

    Tai sukurs Custom Vision prognozės išteklių jūsų išteklių grupėje. Jis bus pavadintas `fruit-quality-detector-prediction` ir naudos `F0` SKU, kuris yra nemokamas planas. `--yes` parinktis reiškia, kad sutinkate su Cognitive Services sąlygomis.

### Užduotis – sukurkite vaizdų klasifikatoriaus projektą

1. Atidarykite Custom Vision portalą adresu [CustomVision.ai](https://customvision.ai) ir prisijunkite naudodami Microsoft paskyrą, kurią naudojote savo Azure paskyrai.

1. Sekite [naujo projekto kūrimo skyrių Microsoft dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project), kad sukurtumėte naują Custom Vision projektą. Sąsaja gali keistis, todėl šie dokumentai visada yra naujausias šaltinis.

    Pavadinkite savo projektą `fruit-quality-detector`.

    Kurdamas projektą, būtinai naudokite anksčiau sukurtą `fruit-quality-detector-training` išteklį. Pasirinkite *Klasifikacijos* projekto tipą, *Daugiaklasę* klasifikacijos tipą ir *Maisto* domeną.

    ![Custom Vision projekto nustatymai su pavadinimu fruit-quality-detector, be aprašymo, išteklius nustatytas į fruit-quality-detector-training, projekto tipas nustatytas į klasifikaciją, klasifikacijos tipas nustatytas į daugiaklasį, o domenas nustatytas į maistą](../../../../../translated_images/lt/custom-vision-create-project.cf46325b92d8b131.webp)

✅ Skirkite laiko susipažinti su Custom Vision sąsaja savo vaizdų klasifikatoriui.

### Užduotis – apmokykite savo vaizdų klasifikatoriaus projektą

Norėdami apmokyti vaizdų klasifikatorių, jums reikės kelių vaisių nuotraukų, tiek geros, tiek blogos kokybės, kurias galėtumėte pažymėti kaip geras arba blogas, pavyzdžiui, prinokusį ir pernokusią bananą.
💁 Šie klasifikatoriai gali klasifikuoti bet kokius vaizdus, todėl, jei neturite skirtingos kokybės vaisių, galite naudoti dviejų skirtingų rūšių vaisius arba kates ir šunis!
Idealiu atveju kiekvienoje nuotraukoje turėtų būti tik vaisius, su vienodu fonu arba įvairiais fonais. Užtikrinkite, kad fone nebūtų nieko, kas galėtų būti susiję su prinokusiu ar neprinokusiu vaisiumi.

> 💁 Svarbu, kad fone nebūtų specifinių elementų ar objektų, nesusijusių su klasifikuojamu objektu, kitaip klasifikatorius gali pradėti klasifikuoti pagal foną. Buvo atvejis, kai odos vėžio klasifikatorius buvo apmokytas naudoti nuotraukas su apgamais – tiek normaliais, tiek vėžiniais. Paaiškėjo, kad vėžiniai apgamai visada buvo matuojami liniuotėmis. Galiausiai klasifikatorius beveik 100% tikslumu atpažindavo liniuotę nuotraukoje, o ne vėžinius apgamus.

Vaizdų klasifikatoriai veikia labai maža raiška. Pavyzdžiui, „Custom Vision“ gali priimti mokymo ir prognozavimo vaizdus iki 10240x10240, tačiau modelis yra mokomas ir veikia su 227x227 dydžio vaizdais. Didesni vaizdai sumažinami iki šio dydžio, todėl užtikrinkite, kad klasifikuojamas objektas užimtų didelę vaizdo dalį, kitaip jis gali būti per mažas mažesniame vaizde, kurį naudoja klasifikatorius.

1. Surinkite nuotraukas savo klasifikatoriui. Jums reikės bent 5 nuotraukų kiekvienai žymai, kad apmokytumėte klasifikatorių, tačiau kuo daugiau, tuo geriau. Taip pat reikės kelių papildomų nuotraukų klasifikatoriaus testavimui. Šios nuotraukos turėtų būti skirtingos to paties objekto nuotraukos. Pavyzdžiui:

    * Naudodami 2 prinokusius bananus, padarykite keletą kiekvieno nuotraukų iš skirtingų kampų, padarydami bent 7 nuotraukas (5 mokymui, 2 testavimui), bet idealiu atveju daugiau.

        ![2 skirtingų bananų nuotraukos](../../../../../translated_images/lt/banana-training-images.530eb203346d73bc.webp)

    * Pakartokite tą patį procesą su 2 neprinokusiais bananais.

    Jūs turėtumėte turėti bent 10 mokymo nuotraukų: bent 5 prinokusių ir 5 neprinokusių, bei 4 testavimo nuotraukas: 2 prinokusių ir 2 neprinokusių. Jūsų nuotraukos turėtų būti png arba jpeg formato, mažesnės nei 6 MB. Jei jas kuriate, pavyzdžiui, su iPhone, jos gali būti aukštos raiškos HEIC formato, todėl reikės jas konvertuoti ir galbūt sumažinti. Kuo daugiau nuotraukų, tuo geriau, ir turėtumėte turėti panašų kiekį prinokusių ir neprinokusių.

    Jei neturite tiek prinokusių, tiek neprinokusių vaisių, galite naudoti skirtingus vaisius arba bet kokius du turimus objektus. Taip pat galite rasti pavyzdinių nuotraukų [images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images) aplanke su prinokusiais ir neprinokusiais bananais, kuriuos galite naudoti.

1. Sekite [nuotraukų įkėlimo ir žymėjimo skyrių klasifikatoriaus kūrimo greitos pradžios vadove Microsoft dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images), kad įkeltumėte savo mokymo nuotraukas. Žymėkite prinokusius vaisius kaip `ripe`, o neprinokusius kaip `unripe`.

    ![Prinokusių ir neprinokusių bananų nuotraukų įkėlimo dialogai](../../../../../translated_images/lt/image-upload-bananas.0751639f3815e0ec.webp)

1. Sekite [klasifikatoriaus mokymo skyrių klasifikatoriaus kūrimo greitos pradžios vadove Microsoft dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier), kad apmokytumėte vaizdų klasifikatorių naudodami savo įkeltas nuotraukas.

    Jums bus suteikta galimybė pasirinkti mokymo tipą. Pasirinkite **Quick Training**.

Klasifikatorius pradės mokytis. Mokymas užtruks kelias minutes.

> 🍌 Jei nuspręsite suvalgyti savo vaisius, kol klasifikatorius mokosi, įsitikinkite, kad turite pakankamai nuotraukų testavimui!

## Išbandykite savo vaizdų klasifikatorių

Kai jūsų klasifikatorius bus apmokytas, galėsite jį išbandyti, pateikdami naują vaizdą klasifikavimui.

### Užduotis – išbandykite savo vaizdų klasifikatorių

1. Sekite [savo modelio testavimo dokumentaciją Microsoft dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model), kad išbandytumėte savo vaizdų klasifikatorių. Naudokite anksčiau sukurtas testavimo nuotraukas, o ne tas, kurias naudojote mokymui.

    ![Neprinokęs bananas, klasifikuotas kaip neprinokęs su 98,9% tikimybe, prinokęs su 1,1% tikimybe](../../../../../translated_images/lt/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64.webp)

1. Išbandykite visas turimas testavimo nuotraukas ir stebėkite tikimybes.

## Pertraukite savo vaizdų klasifikatorių

Kai testuosite savo klasifikatorių, jis gali neduoti tikėtinų rezultatų. Vaizdų klasifikatoriai naudoja mašininį mokymąsi, kad prognozuotų, kas yra vaizde, remdamiesi tikimybėmis, jog tam tikros vaizdo savybės atitinka tam tikrą žymą. Jie nesupranta, kas yra vaizde – jie nežino, kas yra bananas, ar kuo bananas skiriasi nuo valties. Galite pagerinti savo klasifikatorių, pertraukdami jį su neteisingai klasifikuotais vaizdais.

Kiekvieną kartą, kai naudojate greito testavimo parinktį, vaizdas ir rezultatai yra saugomi. Galite naudoti šiuos vaizdus savo modelio pertraukymui.

### Užduotis – pertraukite savo vaizdų klasifikatorių

1. Sekite [numatytų vaizdų naudojimo mokymui dokumentaciją Microsoft dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training), kad pertrauktumėte savo modelį, naudodami teisingą žymą kiekvienam vaizdui.

1. Kai jūsų modelis bus pertrauktas, išbandykite jį su naujais vaizdais.

---

## 🚀 Iššūkis

Kaip manote, kas nutiktų, jei naudotumėte braškės nuotrauką su modeliu, apmokytu bananams, arba pripučiamo banano nuotrauką, arba žmogų su banano kostiumu, ar net geltoną animacinį personažą, pavyzdžiui, Simpsonų veikėją?

Išbandykite ir pažiūrėkite, kokios bus prognozės. Galite rasti nuotraukų, kurias išbandyti, naudodami [Bing vaizdų paiešką](https://www.bing.com/images/trending).

## Po paskaitos testas

[Po paskaitos testas](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## Peržiūra ir savarankiškas mokymasis

* Kai apmokėte savo klasifikatorių, matėte *Tikslumo* (Precision), *Atšaukimo* (Recall) ir *AP* reikšmes, kurios įvertina sukurtą modelį. Perskaitykite, kas tai yra, naudodami [klasifikatoriaus įvertinimo skyrių klasifikatoriaus kūrimo greitos pradžios vadove Microsoft dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier).
* Perskaitykite, kaip pagerinti savo klasifikatorių, naudodami [kaip pagerinti savo Custom Vision modelį Microsoft dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn).

## Užduotis

[Apmokykite savo klasifikatorių keliems vaisiams ir daržovėms](assignment.md)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.