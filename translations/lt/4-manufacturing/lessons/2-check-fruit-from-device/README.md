# Patikrinkite vaisių kokybę naudodami IoT įrenginį

![Šios pamokos eskizų apžvalga](../../../../../translated_images/lt/lesson-16.215daf18b00631fb.webp)

> Eskizą sukūrė [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

## Klausimynas prieš paskaitą

[Klausimynas prieš paskaitą](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Įvadas

Praeitoje pamokoje sužinojote apie vaizdų klasifikatorius ir kaip juos apmokyti, kad jie atpažintų gerus ir blogus vaisius. Norint naudoti šį vaizdų klasifikatorių IoT programoje, reikia turėti galimybę užfiksuoti vaizdą naudojant tam tikrą kamerą ir išsiųsti šį vaizdą į debesiją klasifikavimui.

Šioje pamokoje sužinosite apie kameros jutiklius ir kaip juos naudoti su IoT įrenginiu vaizdams užfiksuoti. Taip pat išmoksite, kaip iš savo IoT įrenginio iškviesti vaizdų klasifikatorių.

Šioje pamokoje aptarsime:

* [Kameros jutikliai](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Vaizdo užfiksavimas naudojant IoT įrenginį](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Vaizdų klasifikatoriaus publikavimas](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Vaizdų klasifikavimas iš IoT įrenginio](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Modelio tobulinimas](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Kameros jutikliai

Kameros jutikliai, kaip rodo pavadinimas, yra kameros, kurias galite prijungti prie savo IoT įrenginio. Jie gali užfiksuoti statinius vaizdus arba transliuoti vaizdo įrašus. Kai kurie pateikia neapdorotus vaizdo duomenis, kiti suspaudžia juos į vaizdo failus, tokius kaip JPEG ar PNG. Paprastai kameros, kurios veikia su IoT įrenginiais, yra daug mažesnės ir žemesnės raiškos nei tos, prie kurių esate įpratę, tačiau galite įsigyti aukštos raiškos kameras, kurios prilygsta aukščiausios klasės telefonams. Taip pat galite rasti įvairių keičiamų objektyvų, kelių kamerų rinkinių, infraraudonųjų spindulių terminių kamerų ar UV kamerų.

![Šviesa iš scenos praeina pro objektyvą ir fokusuojama į CMOS jutiklį](../../../../../translated_images/lt/cmos-sensor.75f9cd74decb1371.webp)

Dauguma kameros jutiklių naudoja vaizdo jutiklius, kuriuose kiekvienas pikselis yra fotodiodas. Objektyvas fokusuojasi į vaizdo jutiklį, o tūkstančiai ar milijonai fotodiodų aptinka šviesą, krentančią ant kiekvieno iš jų, ir įrašo tai kaip pikselių duomenis.

> 💁 Objektyvai apverčia vaizdus, o kameros jutiklis tada apverčia juos atgal į teisingą padėtį. Tas pats vyksta ir jūsų akyse – tai, ką matote, aptinkama aukštyn kojomis jūsų akies gale, o jūsų smegenys tai ištaiso.

> 🎓 Vaizdo jutiklis vadinamas aktyvaus pikselio jutikliu (APS), o populiariausias APS tipas yra papildomas metalo oksido puslaidininkių jutiklis, arba CMOS. Galbūt esate girdėję terminą CMOS jutiklis, naudojamą kameros jutikliams apibūdinti.

Kameros jutikliai yra skaitmeniniai jutikliai, siunčiantys vaizdo duomenis kaip skaitmeninius duomenis, dažniausiai naudojant biblioteką, kuri užtikrina ryšį. Kameros jungiasi naudodamos tokias protokolas kaip SPI, kad galėtų perduoti didelius duomenų kiekius – vaizdai yra žymiai didesni nei, pavyzdžiui, temperatūros jutiklio duomenys.

✅ Kokie yra vaizdo dydžio apribojimai naudojant IoT įrenginius? Pagalvokite apie apribojimus, ypač susijusius su mikrovaldiklių aparatine įranga.

## Vaizdo užfiksavimas naudojant IoT įrenginį

Galite naudoti savo IoT įrenginį, kad užfiksuotumėte vaizdą, kuris bus klasifikuojamas.

### Užduotis – užfiksuokite vaizdą naudodami IoT įrenginį

Atlikite atitinkamą vadovą, kad užfiksuotumėte vaizdą naudodami savo IoT įrenginį:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Vienos plokštės kompiuteris - Raspberry Pi](pi-camera.md)
* [Vienos plokštės kompiuteris - virtualus įrenginys](virtual-device-camera.md)

## Vaizdų klasifikatoriaus publikavimas

Praeitoje pamokoje apmokėte savo vaizdų klasifikatorių. Prieš naudodami jį iš savo IoT įrenginio, turite publikuoti modelį.

### Modelio iteracijos

Kai jūsų modelis buvo apmokomas praeitoje pamokoje, galėjote pastebėti, kad **Performance** skirtuke šone rodomos iteracijos. Kai pirmą kartą apmokėte modelį, matėte *Iteration 1*. Kai patobulinote modelį naudodami prognozavimo vaizdus, matėte *Iteration 2*.

Kiekvieną kartą apmokant modelį, sukuriama nauja iteracija. Tai leidžia sekti skirtingas modelio versijas, apmokytas naudojant skirtingus duomenų rinkinius. Atliekant **Quick Test**, yra išskleidžiamasis meniu, kuriame galite pasirinkti iteraciją ir palyginti rezultatus tarp kelių iteracijų.

Kai esate patenkinti iteracija, galite ją publikuoti, kad ji būtų prieinama išorės programoms. Tokiu būdu galite turėti publikuotą versiją, kurią naudoja jūsų įrenginiai, o tuo pačiu metu dirbti su nauja versija per kelias iteracijas ir publikuoti ją, kai būsite patenkinti.

### Užduotis – publikuokite iteraciją

Iteracijos publikuojamos iš Custom Vision portalo.

1. Atidarykite Custom Vision portalą adresu [CustomVision.ai](https://customvision.ai) ir prisijunkite, jei dar to nepadarėte. Tada atidarykite savo `fruit-quality-detector` projektą.

1. Pasirinkite **Performance** skirtuką iš viršuje esančių parinkčių.

1. Pasirinkite naujausią iteraciją iš *Iterations* sąrašo šone.

1. Paspauskite **Publish** mygtuką šalia iteracijos.

    ![Publikavimo mygtukas](../../../../../translated_images/lt/custom-vision-publish-button.b7174e1977b0c33b.webp)

1. *Publish Model* dialoge nustatykite *Prediction resource* į `fruit-quality-detector-prediction` resursą, kurį sukūrėte praeitoje pamokoje. Palikite pavadinimą kaip `Iteration2` ir paspauskite **Publish** mygtuką.

1. Publikavus, paspauskite **Prediction URL** mygtuką. Čia bus pateikta informacija apie prognozavimo API, kurią reikės naudoti iš jūsų IoT įrenginio. Apatinė dalis pažymėta *If you have an image file*, ir tai yra reikalinga informacija. Nukopijuokite rodomą URL, kuris atrodys maždaug taip:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Kur `<location>` bus vieta, kurią naudojote kurdami savo Custom Vision resursą, o `<id>` bus ilgas ID, sudarytas iš raidžių ir skaičių.

    Taip pat nukopijuokite *Prediction-Key* reikšmę. Tai yra saugus raktas, kurį turite perduoti, kai kviečiate modelį. Tik programos, kurios perduoda šį raktą, gali naudoti modelį, o kitos programos bus atmestos.

    ![Prognozavimo API dialogas, rodantis URL ir raktą](../../../../../translated_images/lt/custom-vision-prediction-key-endpoint.30c569ffd0338864.webp)

✅ Kai nauja iteracija publikuojama, ji turės kitą pavadinimą. Kaip manote, kaip pakeistumėte iteraciją, kurią naudoja IoT įrenginys?

## Vaizdų klasifikavimas iš IoT įrenginio

Dabar galite naudoti šiuos ryšio duomenis, kad iš savo IoT įrenginio iškviestumėte vaizdų klasifikatorių.

### Užduotis – klasifikuokite vaizdus iš savo IoT įrenginio

Atlikite atitinkamą vadovą, kad klasifikuotumėte vaizdus naudodami savo IoT įrenginį:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Vienos plokštės kompiuteris - Raspberry Pi/Virtualus IoT įrenginys](single-board-computer-classify-image.md)

## Modelio tobulinimas

Galbūt pastebėsite, kad rezultatai, kuriuos gaunate naudodami kamerą, prijungtą prie jūsų IoT įrenginio, neatitinka jūsų lūkesčių. Prognozės ne visada yra tokios tikslios, kaip naudojant vaizdus, įkeltus iš jūsų kompiuterio. Taip yra todėl, kad modelis buvo apmokytas naudojant kitokius duomenis nei tie, kurie naudojami prognozėms.

Norint gauti geriausius vaizdų klasifikatoriaus rezultatus, reikia apmokyti modelį naudojant vaizdus, kurie yra kuo panašesni į tuos, kurie naudojami prognozėms. Pavyzdžiui, jei mokymui naudojote telefono kamerą, vaizdo kokybė, ryškumas ir spalvos skirsis nuo kameros, prijungtos prie IoT įrenginio.

![2 bananų nuotraukos: žemos raiškos su prastu apšvietimu iš IoT įrenginio ir aukštos raiškos su geru apšvietimu iš telefono](../../../../../translated_images/lt/banana-picture-compare.174df164dc326a42.webp)

Aukščiau esančiame paveikslėlyje banano nuotrauka kairėje buvo padaryta naudojant Raspberry Pi kamerą, o dešinėje – naudojant iPhone tą patį bananą toje pačioje vietoje. Pastebimas kokybės skirtumas – iPhone nuotrauka yra ryškesnė, su ryškesnėmis spalvomis ir didesniu kontrastu.

✅ Kas dar galėtų lemti, kad IoT įrenginio užfiksuoti vaizdai pateikia neteisingas prognozes? Pagalvokite apie aplinką, kurioje gali būti naudojamas IoT įrenginys, kokie veiksniai gali paveikti užfiksuotą vaizdą?

Norėdami patobulinti modelį, galite jį pertreniruoti naudodami vaizdus, užfiksuotus iš IoT įrenginio.

### Užduotis – patobulinkite modelį

1. Klasifikuokite kelis prinokusių ir neprinokusių vaisių vaizdus naudodami savo IoT įrenginį.

1. Custom Vision portale pertreniruokite modelį naudodami vaizdus iš *Predictions* skirtuko.

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip pertreniruoti klasifikatorių 1 pamokoje](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Jei jūsų vaizdai labai skiriasi nuo originalių, naudotų mokymui, galite ištrinti visus originalius vaizdus pasirinkdami juos *Training Images* skirtuke ir paspausdami **Delete** mygtuką. Norėdami pasirinkti vaizdą, užveskite pelės žymeklį ant jo, ir pasirodys varnelė, kurią galite pažymėti arba nuimti.

1. Apmokykite naują modelio iteraciją ir publikuokite ją naudodami aukščiau aprašytus veiksmus.

1. Atnaujinkite URL savo kode ir paleiskite programą iš naujo.

1. Kartokite šiuos veiksmus, kol būsite patenkinti prognozių rezultatais.

---

## 🚀 Iššūkis

Kiek vaizdo raiška ar apšvietimas veikia prognozę?

Pabandykite pakeisti vaizdų raišką savo įrenginio kode ir pažiūrėkite, ar tai daro įtaką vaizdų kokybei. Taip pat pabandykite pakeisti apšvietimą.

Jei kurtumėte gamybinį įrenginį, skirtą parduoti ūkiams ar gamykloms, kaip užtikrintumėte, kad jis visada pateiktų nuoseklius rezultatus?

## Klausimynas po paskaitos

[Klausimynas po paskaitos](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Apžvalga ir savarankiškas mokymasis

Savo Custom Vision modelį apmokėte naudodami portalą. Tai priklauso nuo to, ar turite prieinamų vaizdų – realiame pasaulyje gali būti sunku gauti mokymo duomenis, kurie atitiktų tai, ką užfiksuoja jūsų įrenginio kamera. Galite apeiti šią problemą mokydami tiesiogiai iš savo įrenginio naudodami mokymo API, kad apmokytumėte modelį naudodami vaizdus, užfiksuotus iš jūsų IoT įrenginio.

* Perskaitykite apie mokymo API [naudojant Custom Vision SDK greitą pradžią](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Užduotis

[Atsakykite į klasifikavimo rezultatus](assignment.md)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus aiškinimus, atsiradusius dėl šio vertimo naudojimo.