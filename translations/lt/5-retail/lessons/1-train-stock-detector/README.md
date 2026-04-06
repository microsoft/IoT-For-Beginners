# Sukurkite atsargų detektorių

![Pamokos apžvalga sketchnote formatu](../../../../../translated_images/lt/lesson-19.cf6973cecadf080c.webp)

> Sketchnote sukūrė [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

Šiame vaizdo įraše pateikiama objekto aptikimo ir Azure Custom Vision paslaugos apžvalga, kuri bus aptarta šioje pamokoje.

[![Custom Vision 2 - Objekto aptikimas paprastai | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Spustelėkite paveikslėlį aukščiau, kad peržiūrėtumėte vaizdo įrašą

## Klausimai prieš paskaitą

[Klausimai prieš paskaitą](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Įvadas

Ankstesniame projekte naudojote dirbtinį intelektą, kad sukurtumėte vaizdų klasifikatorių – modelį, kuris gali nustatyti, ar vaizde yra kažkas, pavyzdžiui, prinokusių ar neprinokusių vaisių. Kitas dirbtinio intelekto modelio tipas, kurį galima naudoti su vaizdais, yra objekto aptikimas. Šie modeliai neklasifikuoja vaizdo pagal žymes, o yra mokomi atpažinti objektus ir gali juos surasti vaizduose, ne tik aptikti, kad objektas yra vaizde, bet ir nustatyti, kurioje vaizdo vietoje jis yra. Tai leidžia skaičiuoti objektus vaizduose.

Šioje pamokoje sužinosite apie objekto aptikimą, įskaitant tai, kaip jis gali būti naudojamas mažmeninėje prekyboje. Taip pat sužinosite, kaip debesyje apmokyti objekto aptikimo modelį.

Šioje pamokoje aptarsime:

* [Objekto aptikimą](../../../../../5-retail/lessons/1-train-stock-detector)
* [Objekto aptikimo naudojimą mažmeninėje prekyboje](../../../../../5-retail/lessons/1-train-stock-detector)
* [Objekto aptikimo modelio mokymą](../../../../../5-retail/lessons/1-train-stock-detector)
* [Objekto aptikimo modelio testavimą](../../../../../5-retail/lessons/1-train-stock-detector)
* [Objekto aptikimo modelio per-mokymą](../../../../../5-retail/lessons/1-train-stock-detector)

## Objekto aptikimas

Objekto aptikimas apima objektų aptikimą vaizduose naudojant dirbtinį intelektą. Skirtingai nei vaizdų klasifikatorius, kurį apmokėte ankstesniame projekte, objekto aptikimas nėra susijęs su geriausios žymės numatymu visam vaizdui, o su vieno ar kelių objektų suradimu vaizde.

### Objekto aptikimas vs vaizdų klasifikavimas

Vaizdų klasifikavimas susijęs su viso vaizdo klasifikavimu – kokia tikimybė, kad visas vaizdas atitinka kiekvieną žymę. Jūs gaunate tikimybes kiekvienai žymei, kuri buvo naudojama modelio mokymui.

![Vaizdų klasifikavimas anakardžių riešutams ir pomidorų pastai](../../../../../translated_images/lt/image-classifier-cashews-tomato.bc2e16ab8f05cf9a.webp)

Pavyzdyje aukščiau du vaizdai klasifikuojami naudojant modelį, apmokytą klasifikuoti anakardžių riešutų indelius arba pomidorų pastos skardines. Pirmasis vaizdas yra anakardžių riešutų indelis, ir klasifikatorius pateikia du rezultatus:

| Žymė            | Tikimybė |
| ---------------- | --------: |
| `anakardžių riešutai`  | 98.4%       |
| `pomidorų pasta` | 1.6%        |

Antrasis vaizdas yra pomidorų pastos skardinė, ir rezultatai yra:

| Žymė            | Tikimybė |
| ---------------- | --------: |
| `anakardžių riešutai`  | 0.7%        |
| `pomidorų pasta` | 99.3%       |

Galėtumėte naudoti šias vertes su procentine riba, kad numatytumėte, kas yra vaizde. Bet kas, jei vaizde būtų kelios pomidorų pastos skardinės arba tiek anakardžių riešutų, tiek pomidorų pasta? Rezultatai greičiausiai neatitiktų jūsų lūkesčių. Čia praverčia objekto aptikimas.

Objekto aptikimas apima modelio mokymą atpažinti objektus. Vietoj to, kad pateiktumėte vaizdus su objektu ir nurodytumėte, kad kiekvienas vaizdas yra viena žymė ar kita, jūs pažymite vaizdo dalį, kurioje yra konkretus objektas, ir priskiriate žymę. Galite pažymėti vieną objektą vaizde arba kelis. Tokiu būdu modelis išmoksta, kaip atrodo pats objektas, o ne tik kaip atrodo vaizdai, kuriuose yra objektas.

Kai vėliau naudojate modelį vaizdų numatymui, vietoj žymių ir procentų sąrašo gaunate aptiktų objektų sąrašą su jų ribojančiais langeliais ir tikimybe, kad objektas atitinka priskirtą žymę.

> 🎓 *Ribojantys langeliai* yra langeliai aplink objektą.

![Objekto aptikimas anakardžių riešutams ir pomidorų pastai](../../../../../translated_images/lt/object-detector-cashews-tomato.1af7c26686b4db0e.webp)

Vaizde aukščiau yra tiek anakardžių riešutų indelis, tiek trys pomidorų pastos skardinės. Objekto aptikimo modelis aptiko anakardžių riešutus, pateikdamas ribojantį langelį, kuriame yra anakardžių riešutai, su procentine tikimybe, kad ribojantis langelis apima objektą, šiuo atveju 97.6%. Modelis taip pat aptiko tris pomidorų pastos skardines ir pateikia tris atskirus ribojančius langelius, po vieną kiekvienai aptiktai skardinei, ir kiekvienas langelis turi procentinę tikimybę, kad ribojantis langelis apima pomidorų pastos skardinę.

✅ Pagalvokite apie skirtingus scenarijus, kuriems galėtumėte naudoti vaizdais pagrįstus dirbtinio intelekto modelius. Kurie iš jų reikalautų klasifikavimo, o kurie – objekto aptikimo?

### Kaip veikia objekto aptikimas

Objekto aptikimas naudoja sudėtingus ML modelius. Šie modeliai veikia padalindami vaizdą į kelias ląsteles, tada tikrina, ar ribojančio langelio centras yra vaizdo dalis, kuri atitinka vieną iš vaizdų, naudotų modelio mokymui. Galite tai įsivaizduoti kaip vaizdų klasifikatoriaus paleidimą per skirtingas vaizdo dalis, ieškant atitikimų.

> 💁 Tai yra drastiškas supaprastinimas. Yra daug objekto aptikimo technikų, apie kurias galite daugiau sužinoti [Objekto aptikimo puslapyje Vikipedijoje](https://wikipedia.org/wiki/Object_detection).

Yra keletas skirtingų modelių, galinčių atlikti objekto aptikimą. Vienas ypač garsus modelis yra [YOLO (You only look once)](https://pjreddie.com/darknet/yolo/), kuris yra nepaprastai greitas ir gali aptikti 20 skirtingų objektų klasių, tokių kaip žmonės, šunys, buteliai ir automobiliai.

✅ Perskaitykite apie YOLO modelį [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/)

Objekto aptikimo modelius galima per-mokyti naudojant perkėlimo mokymą, kad aptiktų pasirinktinius objektus.

## Objekto aptikimo naudojimas mažmeninėje prekyboje

Objekto aptikimas turi daug panaudojimo galimybių mažmeninėje prekyboje. Kai kurios iš jų:

* **Atsargų tikrinimas ir skaičiavimas** – atpažįstant, kada lentynose trūksta atsargų. Jei atsargų per mažai, darbuotojams ar robotams gali būti siunčiami pranešimai, kad lentynos būtų papildytos.
* **Kaukės aptikimas** – parduotuvėse, kuriose galioja kaukių politika viešosios sveikatos įvykių metu, objekto aptikimas gali atpažinti žmones su kaukėmis ir be jų.
* **Automatinis atsiskaitymas** – aptinkant prekes, paimtas nuo lentynų automatizuotose parduotuvėse, ir tinkamai apmokestinant klientus.
* **Pavojų aptikimas** – atpažįstant sudužusius daiktus ant grindų ar išsiliejusius skysčius, pranešant valymo komandoms.

✅ Atlikite tyrimą: Kokie dar galėtų būti objekto aptikimo panaudojimo atvejai mažmeninėje prekyboje?

## Objekto aptikimo modelio mokymas

Galite apmokyti objekto aptikimo modelį naudodami Custom Vision, panašiai kaip mokėte vaizdų klasifikatorių.

### Užduotis – sukurkite objekto aptikimo modelį

1. Sukurkite šio projekto išteklių grupę, pavadintą `stock-detector`.

1. Sukurkite nemokamą Custom Vision mokymo išteklių ir nemokamą Custom Vision prognozavimo išteklių `stock-detector` išteklių grupėje. Pavadinkite juos `stock-detector-training` ir `stock-detector-prediction`.

    > 💁 Galite turėti tik vieną nemokamą mokymo ir prognozavimo išteklių, todėl įsitikinkite, kad išvalėte ankstesnių pamokų projektus.

    > ⚠️ Jei reikia, galite kreiptis į [instrukcijas, kaip sukurti mokymo ir prognozavimo išteklius iš 4 projekto, 1 pamokos](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. Paleiskite Custom Vision portalą adresu [CustomVision.ai](https://customvision.ai) ir prisijunkite naudodami Microsoft paskyrą, kurią naudojote savo Azure paskyrai.

1. Sekite [„Sukurti naują projektą“ skyrių „Sukurti objekto aptikimo modelį“ greitojoje pradžioje Microsoft dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project), kad sukurtumėte naują Custom Vision projektą. UI gali keistis, todėl šie dokumentai visada yra naujausias šaltinis.

    Savo projektą pavadinkite `stock-detector`.

    Kurdamas projektą, įsitikinkite, kad naudojate anksčiau sukurtą `stock-detector-training` išteklių. Naudokite *Objekto aptikimo* projekto tipą ir *Produktai lentynose* domeną.

    ![Custom Vision projekto nustatymai su pavadinimu fruit-quality-detector, be aprašymo, išteklius nustatytas į fruit-quality-detector-training, projekto tipas nustatytas į klasifikaciją, klasifikacijos tipai nustatyti į multi class ir domenai nustatyti į maistą](../../../../../translated_images/lt/custom-vision-create-object-detector-project.32d4fb9aa8e7e737.webp)

    ✅ Produktų lentynose domenas yra specialiai pritaikytas atsargų aptikimui parduotuvių lentynose. Daugiau apie skirtingus domenus skaitykite [„Pasirinkti domeną“ dokumentacijoje Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection)

✅ Skirkite šiek tiek laiko, kad išnagrinėtumėte Custom Vision UI savo objekto aptikimo modeliui.

### Užduotis – apmokykite savo objekto aptikimo modelį

Norėdami apmokyti savo modelį, jums reikės vaizdų rinkinio, kuriame yra objektai, kuriuos norite aptikti.

1. Surinkite vaizdus, kuriuose yra aptinkamas objektas. Jums reikės bent 15 vaizdų, kuriuose yra kiekvienas aptinkamas objektas, iš įvairių kampų ir skirtingomis apšvietimo sąlygomis, tačiau kuo daugiau, tuo geriau. Šis objekto aptikimo modelis naudoja *Produktai lentynose* domeną, todėl pabandykite objektus išdėstyti taip, tarsi jie būtų parduotuvės lentynoje. Jums taip pat reikės kelių vaizdų modelio testavimui. Jei aptinkate daugiau nei vieną objektą, norėsite turėti testavimo vaizdų, kuriuose yra visi objektai.

    > 💁 Vaizdai su keliais skirtingais objektais skaičiuojami į 15 vaizdų minimumą visiems vaizde esantiems objektams.

    Jūsų vaizdai turėtų būti png arba jpeg formatu, mažesni nei 6MB. Jei juos sukuriate, pavyzdžiui, su iPhone, jie gali būti aukštos raiškos HEIC formatu, todėl juos reikės konvertuoti ir galbūt sumažinti. Kuo daugiau vaizdų, tuo geriau, ir turėtumėte turėti panašų kiekį prinokusių ir neprinokusių.

    Modelis yra skirtas produktams lentynose, todėl pabandykite fotografuoti objektus lentynose.

    Galite rasti keletą pavyzdinių vaizdų, kuriuos galite naudoti [vaizdų](../../../../../5-retail/lessons/1-train-stock-detector/images) aplanke su anakardžių riešutais ir pomidorų pasta.

1. Sekite [„Įkelti ir pažymėti vaizdus“ skyrių „Sukurti objekto aptikimo modelį“ greitojoje pradžioje Microsoft dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images), kad įkeltumėte savo mokymo vaizdus. Sukurkite atitinkamas žymes, priklausomai nuo objektų tipų, kuriuos norite aptikti.

    ![Įkėlimo dialogai, rodantys prinokusių ir neprinokusių bananų vaizdų įkėlimą](../../../../../translated_images/lt/image-upload-object-detector.77c7892c3093cb59.webp)

    Kai piešiate ribojančius langelius objektams, laikykite juos glaudžiai aplink objektą. Gali užtrukti, kol pažymėsite visus vaizdus, tačiau įrankis aptiks, ką jis mano esant ribojančiais langeliais, todėl procesas bus greitesnis.

    ![Pomidorų pastos žymėjimas](../../../../../translated_images/lt/object-detector-tag-tomato-paste.f47c362fb0f0eb58.webp)

    > 💁 Jei turite daugiau nei 15 vaizdų kiekvienam objektui, galite mokyti po 15, tada naudoti **Siūlomos žymės** funkciją. Tai naudos apmokytą modelį objektų aptikimui nepažymėtuose vaizduose. Tada galite patvirtinti aptiktus objektus arba atmesti ir perpiešti ribojančius langelius. Tai gali sutaupyti *daug* laiko.

1. Sekite [„Apmokyti detektorių“ skyrių „Sukurti objekto aptikimo modelį“ greitojoje pradžioje Microsoft dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector), kad apmokytumėte objekto aptikimo modelį pagal pažymėtus vaizdus.

    Jums bus suteikta galimybė pasirinkti mokymo tipą. Pasirinkite **Greitas mokymas**.

Objekto aptikimo modelis pradės mokytis. Mokymas užtruks kelias minutes.

## Testuokite savo objekto aptikimo modelį

Kai jūsų objekto aptikimo modelis bus apmokytas, galite jį testuoti, pateikdami naujus vaizdus, kad aptiktumėte objektus.

### Užduotis – testuokite savo objekto aptikimo modelį

1. Naudokite **Greito testavimo** mygtuką, kad įkeltumėte testavimo vaizdus ir patikrintumėte, ar objektai aptinkami. Naudokite anksčiau sukurtus testavimo vaizdus, o ne tuos, kurie buvo naudojami mokymui.

    ![3 pomidorų pastos sk
[Po paskaitos viktorina](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Peržiūra ir savarankiškas mokymasis

* Kai treniravote savo objektų detektorių, turėjote matyti *Tikslumo* (Precision), *Atsiminimo* (Recall) ir *mAP* reikšmes, kurios įvertina sukurtą modelį. Pasidomėkite, ką šios reikšmės reiškia, naudodamiesi [„Įvertinkite detektorių“ skyriumi iš „Sukurkite objektų detektorių“ greitos pradžios vadovo Microsoft dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector)
* Skaitykite daugiau apie objektų atpažinimą [Vikipedijos puslapyje apie objektų atpažinimą](https://wikipedia.org/wiki/Object_detection)

## Užduotis

[Palyginkite domenus](assignment.md)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.