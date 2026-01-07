<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d105b44deae539165855c976dcdeca99",
  "translation_date": "2025-08-28T20:37:42+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/README.md",
  "language_code": "lt"
}
-->
## Prognozuokite augalų augimą naudodami IoT

![Pamokos apžvalga piešiniu](../../../../../translated_images/lesson-5.42b234299279d263143148b88ab4583861a32ddb03110c6c1120e41bb88b2592.lt.jpg)

> Piešinys sukurtas [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

## Klausimynas prieš paskaitą

[Klausimynas prieš paskaitą](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Įvadas

Augalai augimui reikalauja tam tikrų sąlygų – vandens, anglies dioksido, maistinių medžiagų, šviesos ir šilumos. Šioje pamokoje sužinosite, kaip apskaičiuoti augalų augimo ir brendimo tempą, matuojant oro temperatūrą.

Šioje pamokoje aptarsime:

* [Skaitmeninė žemdirbystė](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Kodėl temperatūra svarbi ūkininkaujant?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Aplinkos temperatūros matavimas](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Augimo laipsnių dienos (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [GDD skaičiavimas naudojant temperatūros jutiklio duomenis](../../../../../2-farm/lessons/1-predict-plant-growth)

## Skaitmeninė žemdirbystė

Skaitmeninė žemdirbystė keičia ūkininkavimo būdus, naudojant įrankius duomenims rinkti, saugoti ir analizuoti. Šiuo metu gyvename laikotarpyje, kurį Pasaulio ekonomikos forumas apibūdina kaip „Ketvirtąją pramonės revoliuciją“, o skaitmeninės žemdirbystės plėtra vadinama „Ketvirtąja žemės ūkio revoliucija“ arba „Žemės ūkis 4.0“.

> 🎓 Terminas „Skaitmeninė žemdirbystė“ apima visą „žemės ūkio vertės grandinę“, tai yra visą kelionę nuo ūkio iki stalo. Tai apima produkcijos kokybės stebėjimą, kai maistas yra gabenamas ir perdirbamas, sandėliavimo ir e. prekybos sistemas, net traktorių nuomos programėles!

Šie pokyčiai leidžia ūkininkams padidinti derlių, naudoti mažiau trąšų ir pesticidų bei efektyviau naudoti vandenį. Nors iš pradžių šios technologijos buvo naudojamos turtingesnėse šalyse, jutikliai ir kiti įrenginiai palaipsniui pinga, todėl tampa prieinamesni besivystančiose šalyse.

Kai kurios skaitmeninės žemdirbystės leidžiamos technikos yra:

* Temperatūros matavimas – temperatūros matavimas leidžia ūkininkams prognozuoti augalų augimą ir brendimą.
* Automatinis laistymas – dirvožemio drėgmės matavimas ir drėkinimo sistemų įjungimas, kai dirvožemis per sausas, o ne laistymas pagal laiką. Laistymas pagal laiką gali lemti, kad augalai bus per mažai palaistyti karštu, sausu laikotarpiu arba per daug palaistyti lietaus metu. Laistant tik tada, kai dirvožemiui reikia, ūkininkai gali optimizuoti vandens naudojimą.
* Kenkėjų kontrolė – ūkininkai gali naudoti kameras ant automatizuotų robotų ar dronų, kad patikrintų kenkėjus, o pesticidus taikyti tik ten, kur reikia, taip sumažinant pesticidų naudojimą ir jų nutekėjimą į vietinius vandens telkinius.

✅ Atlikite tyrimą. Kokios kitos technikos naudojamos derliaus didinimui?

> 🎓 Terminas „Tikslusis žemės ūkis“ apibrėžia stebėjimą, matavimą ir reagavimą į pasėlius pagal lauką ar net jo dalis. Tai apima vandens, maistinių medžiagų ir kenkėjų lygio matavimą bei tikslų reagavimą, pavyzdžiui, laistant tik nedidelę lauko dalį.

## Kodėl temperatūra svarbi ūkininkaujant?

Mokantis apie augalus, dauguma mokinių sužino apie vandens, šviesos, anglies dioksido ir maistinių medžiagų svarbą. Augalai taip pat reikalauja šilumos augimui – dėl to augalai žydi pavasarį, kai temperatūra kyla, snieguolės ar narcizai gali išdygti anksti dėl trumpalaikio šilto laikotarpio, o šiltnamiai ir oranžerijos yra tokie efektyvūs augalų augimui.

> 🎓 Šiltnamiai ir oranžerijos atlieka panašią funkciją, tačiau yra svarbus skirtumas. Oranžerijos šildomos dirbtinai, leidžiant ūkininkams tiksliau kontroliuoti temperatūrą, o šiltnamiai pasikliauja saulės šiluma, dažniausiai kontroliuojami tik langais ar kitais angomis, kad išleistų šilumą.

Augalai turi bazinę arba minimalią temperatūrą, optimalią temperatūrą ir maksimalią temperatūrą, kurios visos yra pagrįstos dienos vidutinėmis temperatūromis.

* Bazinė temperatūra – tai minimali dienos vidutinė temperatūra, reikalinga augalui augti.
* Optimali temperatūra – tai geriausia dienos vidutinė temperatūra, kad augimas būtų maksimalus.
* Maksimali temperatūra – tai maksimali temperatūra, kurią augalas gali atlaikyti. Viršijus šią temperatūrą, augalas sustabdo augimą, bandydamas taupyti vandenį ir išlikti gyvas.

> 💁 Tai yra vidutinės temperatūros, apskaičiuotos pagal dienos ir nakties temperatūras. Augalai taip pat reikalauja skirtingų temperatūrų dieną ir naktį, kad efektyviau fotosintetintų ir taupytų energiją naktį.

Kiekviena augalų rūšis turi skirtingas bazinės, optimalios ir maksimalios temperatūros vertes. Dėl to kai kurie augalai klesti karštose šalyse, o kiti – šaltose.

✅ Atlikite tyrimą. Jei turite augalų savo sode, mokykloje ar vietiniame parke, pabandykite surasti jų bazinę temperatūrą.

![Grafikas, rodantis augimo tempą kylant temperatūrai, o vėliau mažėjant, kai temperatūra tampa per aukšta](../../../../../translated_images/plant-growth-temp-graph.c6d69c9478e6ca83.lt.png)

Aukščiau pateiktas grafikas rodo augimo tempo ir temperatūros ryšį. Iki bazinės temperatūros augimas nevyksta. Augimo tempas didėja iki optimalios temperatūros, o vėliau mažėja, pasiekus šį piką. Maksimalioje temperatūroje augimas sustoja.

Šio grafiko forma skiriasi priklausomai nuo augalų rūšies. Kai kurių augalų augimo tempas po optimalios temperatūros smarkiai krenta, kitų – lėtai kyla nuo bazinės iki optimalios temperatūros.

> 💁 Kad ūkininkas pasiektų geriausią augimą, jis turėtų žinoti tris temperatūros vertes ir suprasti grafiko formą augalams, kuriuos augina.

Jei ūkininkas gali kontroliuoti temperatūrą, pavyzdžiui, komercinėje oranžerijoje, jis gali optimizuoti sąlygas savo augalams. Komercinė oranžerija, kurioje auginami pomidorai, pavyzdžiui, dienos metu nustatys temperatūrą apie 25°C, o naktį – apie 20°C, kad augimas būtų greičiausias.

> 🍅 Derinant šias temperatūras su dirbtine šviesa, trąšomis ir kontroliuojamu anglies dioksido lygiu, komerciniai augintojai gali auginti ir nuimti derlių ištisus metus.

## Aplinkos temperatūros matavimas

Temperatūros jutikliai gali būti naudojami su IoT įrenginiais aplinkos temperatūrai matuoti.

### Užduotis – temperatūros matavimas

Atlikite atitinkamą vadovą, kad stebėtumėte temperatūrą naudodami savo IoT įrenginį:

* [Arduino - Wio Terminal](wio-terminal-temp.md)
* [Vieno plokštės kompiuteris - Raspberry Pi](pi-temp.md)
* [Vieno plokštės kompiuteris - virtualus įrenginys](virtual-device-temp.md)

## Augimo laipsnių dienos

Augimo laipsnių dienos (taip pat žinomos kaip augimo laipsnių vienetai) yra būdas matuoti augalų augimą pagal temperatūrą. Jei augalas turi pakankamai vandens, maistinių medžiagų ir anglies dioksido, temperatūra lemia augimo tempą.

Augimo laipsnių dienos, arba GDD, skaičiuojamos kiekvieną dieną kaip vidutinė dienos temperatūra Celsijaus laipsniais, viršijanti augalo bazinę temperatūrą. Kiekvienam augalui reikia tam tikro GDD skaičiaus, kad jis augtų, žydėtų arba subrandintų derlių. Kuo daugiau GDD per dieną, tuo greičiau augalas auga.

> 🇺🇸 Amerikiečiams augimo laipsnių dienos taip pat gali būti skaičiuojamos pagal Farenheito laipsnius. 5 GDD (Celsijaus) atitinka 9 GDD (Farenheito).
Šis kodas atidaro CSV failą ir prideda naują eilutę pabaigoje. Eilutėje yra dabartinė data ir laikas, suformatuoti taip, kad būtų lengvai suprantami žmogui, o po jų – temperatūra, gauta iš IoT įrenginio. Duomenys saugomi [ISO 8601 formatu](https://wikipedia.org/wiki/ISO_8601) su laiko juosta, bet be mikrosekundžių.

1. Paleiskite šį kodą taip pat, kaip ir anksčiau, įsitikindami, kad jūsų IoT įrenginys siunčia duomenis. Tame pačiame aplanke bus sukurtas CSV failas, pavadintas `temperature.csv`. Jei jį peržiūrėsite, pamatysite datas/laikus ir temperatūros matavimus:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Paleiskite šį kodą kurį laiką, kad surinktumėte duomenis. Idealiu atveju turėtumėte paleisti jį visą dieną, kad surinktumėte pakankamai duomenų GDD skaičiavimams.

    
> 💁 Jei naudojate virtualų IoT įrenginį, pažymėkite atsitiktinumo žymimąjį laukelį ir nustatykite diapazoną, kad išvengtumėte tos pačios temperatūros gavimo kiekvieną kartą, kai grąžinama temperatūros reikšmė.
    ![Pažymėkite atsitiktinumo žymimąjį laukelį ir nustatykite diapazoną](../../../../../translated_images/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.lt.png) 

    > 💁 Jei norite paleisti šį kodą visą dieną, turite įsitikinti, kad kompiuteris, kuriame veikia jūsų serverio kodas, neperjungs miego režimo – tai galite padaryti pakeisdami energijos nustatymus arba paleisdami kažką panašaus į [šį Python skriptą, kuris palaiko sistemą aktyvią](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Šį kodą galite rasti aplanke [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Užduotis – apskaičiuoti GDD naudojant saugomus duomenis

Kai serveris užfiksuos temperatūros duomenis, galima apskaičiuoti augalo GDD.

Rankiniu būdu tai atliekama šiais žingsniais:

1. Raskite bazinę augalo temperatūrą. Pavyzdžiui, braškėms bazinė temperatūra yra 10°C.

1. Iš `temperature.csv` failo raskite aukščiausią ir žemiausią dienos temperatūras.

1. Naudokite anksčiau pateiktą GDD skaičiavimo formulę, kad apskaičiuotumėte GDD.

Pavyzdžiui, jei aukščiausia dienos temperatūra yra 25°C, o žemiausia – 12°C:

![GDD = 25 + 12 padalinta iš 2, tada iš rezultato atimama 10, gaunant 8.5](../../../../../translated_images/gdd-calculation-strawberries.59f57db94b22adb8ff6efb951ace33af104a1c6ccca3ffb0f8169c14cb160c90.lt.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Taigi braškės gavo **8.5** GDD. Braškėms reikia apie 250 GDD, kad pradėtų derėti, todėl dar teks palaukti.

---

## 🚀 Iššūkis

Augalams reikia ne tik šilumos, kad augtų. Ko dar reikia?

Pasidomėkite, ar yra jutiklių, kurie galėtų tai išmatuoti. O kaip dėl aktuatorių, kurie galėtų reguliuoti šiuos lygius? Kaip sudėtumėte vieną ar daugiau IoT įrenginių, kad optimizuotumėte augalų augimą?

## Po paskaitos testas

[Po paskaitos testas](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Apžvalga ir savarankiškas mokymasis

* Skaitykite daugiau apie skaitmeninę žemdirbystę [Skaitmeninės žemdirbystės Vikipedijos puslapyje](https://wikipedia.org/wiki/Digital_agriculture). Taip pat skaitykite daugiau apie precizinę žemdirbystę [Precizinės žemdirbystės Vikipedijos puslapyje](https://wikipedia.org/wiki/Precision_agriculture).
* Pilnas augimo laipsnių dienų (GDD) skaičiavimas yra sudėtingesnis nei čia pateiktas supaprastintas variantas. Skaitykite daugiau apie sudėtingesnę lygtį ir kaip elgtis su temperatūromis, kurios yra žemiau bazinės, [Augimo laipsnių dienų Vikipedijos puslapyje](https://wikipedia.org/wiki/Growing_degree-day).
* Maisto gali trūkti ateityje, jei ir toliau naudosime tuos pačius ūkininkavimo metodus. Sužinokite daugiau apie aukštųjų technologijų ūkininkavimo metodus šiame [Ateities aukštųjų technologijų ūkių vaizdo įraše „YouTube“](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Užduotis

[Vizualizuokite GDD duomenis naudodami Jupyter Notebook](assignment.md)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.