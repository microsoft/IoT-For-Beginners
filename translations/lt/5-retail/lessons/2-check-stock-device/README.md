# Patikrinkite atsargas naudodami IoT įrenginį

![Pamokos apžvalga piešiniu](../../../../../translated_images/lt/lesson-20.0211df9551a8abb3.webp)

> Piešinys sukurtas [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

## Klausimai prieš paskaitą

[Klausimai prieš paskaitą](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Įvadas

Ankstesnėje pamokoje sužinojote apie skirtingus objektų atpažinimo panaudojimo būdus mažmeninėje prekyboje. Taip pat išmokote apmokyti objektų atpažinimo modelį, kad jis galėtų identifikuoti atsargas. Šioje pamokoje sužinosite, kaip naudoti savo objektų atpažinimo modelį iš IoT įrenginio, kad galėtumėte skaičiuoti atsargas.

Šioje pamokoje aptarsime:

* [Atsargų skaičiavimas](../../../../../5-retail/lessons/2-check-stock-device)
* [Objektų atpažinimo modelio naudojimas iš IoT įrenginio](../../../../../5-retail/lessons/2-check-stock-device)
* [Ribojimo dėžutės](../../../../../5-retail/lessons/2-check-stock-device)
* [Modelio pertreniravimas](../../../../../5-retail/lessons/2-check-stock-device)
* [Atsargų skaičiavimas](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Tai paskutinė pamoka šiame projekte, todėl baigę pamoką ir užduotį nepamirškite išvalyti savo debesų paslaugų. Jums reikės paslaugų, kad užbaigtumėte užduotį, todėl pirmiausia įsitikinkite, kad ją atlikote.
>
> Jei reikia instrukcijų, kaip tai padaryti, kreipkitės į [projekto valymo vadovą](../../../clean-up.md).

## Atsargų skaičiavimas

Objektų atpažinimo modeliai gali būti naudojami atsargų tikrinimui – tiek skaičiuojant atsargas, tiek užtikrinant, kad jos yra ten, kur turėtų būti. IoT įrenginiai su kameromis gali būti išdėstyti visoje parduotuvėje, kad stebėtų atsargas, pradedant nuo svarbiausių vietų, kur būtina užtikrinti prekių papildymą, pavyzdžiui, vietų, kur laikomos nedidelės vertingų prekių atsargos.

Pavyzdžiui, jei kamera nukreipta į lentyną, kurioje telpa 8 pomidorų pastos skardinės, o objektų atpažinimo modelis aptinka tik 7 skardines, viena skardinė trūksta ir ją reikia papildyti.

![7 pomidorų pastos skardinės lentynoje, 4 viršutinėje eilėje, 3 apatinėje](../../../../../translated_images/lt/stock-7-cans-tomato-paste.f86059cc573d7bec.webp)

Aukščiau pateiktame paveikslėlyje objektų atpažinimo modelis aptiko 7 pomidorų pastos skardines lentynoje, kurioje telpa 8 skardinės. IoT įrenginys ne tik gali siųsti pranešimą apie poreikį papildyti atsargas, bet ir nurodyti trūkstamos prekės vietą, kas yra svarbi informacija, jei naudojate robotus lentynoms papildyti.

> 💁 Atsižvelgiant į parduotuvę ir prekės populiarumą, papildymas greičiausiai nebūtų atliekamas, jei trūksta tik 1 skardinės. Jums reikėtų sukurti algoritmą, kuris nustatytų, kada papildyti atsargas, remiantis jūsų produktais, klientais ir kitais kriterijais.

✅ Kokiose kitose situacijose galėtumėte derinti objektų atpažinimą ir robotus?

Kartais lentynose gali būti netinkamos atsargos. Tai gali būti žmogaus klaida papildant lentynas arba klientai, pakeitę savo sprendimą dėl pirkimo ir padėję prekę į pirmą pasitaikiusią vietą. Kai tai yra negreitai gendantis produktas, pavyzdžiui, konservai, tai yra nepatogumas. Jei tai yra greitai gendantis produktas, pavyzdžiui, šaldyti ar atvėsinti produktai, tai gali reikšti, kad prekės nebegalima parduoti, nes gali būti neįmanoma nustatyti, kiek laiko ji buvo išimta iš šaldiklio.

Objektų atpažinimo modeliai gali būti naudojami netikėtų prekių aptikimui, vėlgi įspėjant žmogų ar robotą, kad prekė būtų grąžinta, kai tik ji aptinkama.

![Netinkama kūdikių kukurūzų skardinė pomidorų pastos lentynoje](../../../../../translated_images/lt/stock-rogue-corn.be1f3ada8c457854.webp)

Aukščiau pateiktame paveikslėlyje kūdikių kukurūzų skardinė buvo padėta lentynoje šalia pomidorų pastos. Objektų atpažinimo modelis tai aptiko, leidžiant IoT įrenginiui pranešti žmogui ar robotui, kad skardinė būtų grąžinta į tinkamą vietą.

## Objektų atpažinimo modelio naudojimas iš IoT įrenginio

Objektų atpažinimo modelį, kurį apmokėte paskutinėje pamokoje, galima naudoti iš IoT įrenginio.

### Užduotis – paskelbti modelio iteraciją

Iteracijos skelbiamos iš „Custom Vision“ portalo.

1. Atidarykite „Custom Vision“ portalą [CustomVision.ai](https://customvision.ai) ir prisijunkite, jei dar neatidarėte. Tada atidarykite savo `stock-detector` projektą.

1. Pasirinkite **Performance** skirtuką iš viršuje esančių parinkčių.

1. Pasirinkite naujausią iteraciją iš *Iterations* sąrašo šone.

1. Pasirinkite **Publish** mygtuką šiai iteracijai.

    ![Skelbimo mygtukas](../../../../../translated_images/lt/custom-vision-object-detector-publish-button.34ee379fc650ccb9.webp)

1. *Publish Model* dialoge nustatykite *Prediction resource* į `stock-detector-prediction` resursą, kurį sukūrėte paskutinėje pamokoje. Palikite pavadinimą kaip `Iteration2` ir pasirinkite **Publish** mygtuką.

1. Kai iteracija bus paskelbta, pasirinkite **Prediction URL** mygtuką. Čia bus pateikta informacija apie prognozavimo API, kurią reikės naudoti modelio kvietimui iš IoT įrenginio. Apatinė dalis pažymėta *If you have an image file*, ir tai yra reikalinga informacija. Nukopijuokite pateiktą URL, kuris bus panašus į:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Kur `<location>` bus vieta, kurią naudojote kurdami „Custom Vision“ resursą, o `<id>` bus ilgas ID, sudarytas iš raidžių ir skaičių.

    Taip pat nukopijuokite *Prediction-Key* reikšmę. Tai yra saugus raktas, kurį reikia perduoti kviečiant modelį. Tik programos, kurios perduoda šį raktą, gali naudoti modelį, o kitos programos yra atmetamos.

    ![Prognozavimo API dialogas, rodantis URL ir raktą](../../../../../translated_images/lt/custom-vision-prediction-key-endpoint.30c569ffd0338864.webp)

✅ Kai paskelbiama nauja iteracija, ji turės kitokį pavadinimą. Kaip manote, kaip pakeistumėte iteraciją, kurią naudoja IoT įrenginys?

### Užduotis – naudoti objektų atpažinimo modelį iš IoT įrenginio

Sekite atitinkamą vadovą, kad naudotumėte objektų atpažinimo modelį iš savo IoT įrenginio:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Vieno plokštės kompiuteris - Raspberry Pi/Virtualus įrenginys](single-board-computer-object-detector.md)

## Ribojimo dėžutės

Naudojant objektų atpažinimo modelį, gaunate ne tik aptiktus objektus su jų žymomis ir tikimybėmis, bet ir ribojimo dėžutes. Jos apibrėžia, kur objektų atpažinimo modelis aptiko objektą su tam tikra tikimybe.

> 💁 Ribojimo dėžutė yra dėžutė, apibrėžianti sritį, kurioje aptiktas objektas, tai yra objektą ribojanti dėžutė.

Prognozavimo rezultatai **Predictions** skirtuke „Custom Vision“ turi ribojimo dėžutes, kurios yra uždėtos ant vaizdo, kuris buvo pateiktas prognozavimui.

![4 pomidorų pastos skardinės lentynoje su prognozėmis apie 4 aptikimus: 35.8%, 33.5%, 25.7% ir 16.6%](../../../../../translated_images/lt/custom-vision-stock-prediction.942266ab1bcca341.webp)

Aukščiau pateiktame paveikslėlyje aptiktos 4 pomidorų pastos skardinės. Rezultatuose kiekvienam aptiktam objektui vaizde uždėta raudona kvadratinė ribojimo dėžutė, nurodanti aptikimo ribas.

✅ Atidarykite prognozes „Custom Vision“ ir peržiūrėkite ribojimo dėžutes.

Ribojimo dėžutės apibrėžiamos 4 reikšmėmis – viršus, kairė, aukštis ir plotis. Šios reikšmės yra skalėje nuo 0 iki 1, nurodančios pozicijas kaip vaizdo dydžio procentą. Pradžia (0,0 pozicija) yra vaizdo viršutinis kairysis kampas, todėl viršutinė reikšmė yra atstumas nuo viršaus, o ribojimo dėžutės apačia yra viršus plius aukštis.

![Ribojimo dėžutė aplink pomidorų pastos skardinę](../../../../../translated_images/lt/bounding-box.1420a7ea0d3d15f7.webp)

Aukščiau pateiktas vaizdas yra 600 pikselių pločio ir 800 pikselių aukščio. Ribojimo dėžutė prasideda 320 pikselių žemyn, suteikiant viršutinę koordinatę 0.4 (800 x 0.4 = 320). Nuo kairės ribojimo dėžutė prasideda 240 pikselių į šoną, suteikiant kairę koordinatę 0.4 (600 x 0.4 = 240). Ribojimo dėžutės aukštis yra 240 pikselių, suteikiant aukščio reikšmę 0.3 (800 x 0.3 = 240). Ribojimo dėžutės plotis yra 120 pikselių, suteikiant pločio reikšmę 0.2 (600 x 0.2 = 120).

| Koordinatė | Reikšmė |
| ---------- | ----: |
| Viršus     | 0.4   |
| Kairė      | 0.4   |
| Aukštis    | 0.3   |
| Plotis     | 0.2   |

Naudojant procentines reikšmes nuo 0 iki 1, nesvarbu, kokio dydžio vaizdas yra keičiamas, ribojimo dėžutė prasideda 0.4 nuo viršaus ir šono, o jos aukštis yra 0.3, o plotis – 0.2.

Ribojimo dėžutes galima naudoti kartu su tikimybėmis, kad įvertintumėte aptikimo tikslumą. Pavyzdžiui, objektų atpažinimo modelis gali aptikti kelis objektus, kurie persidengia, pavyzdžiui, aptikti vieną skardinę kitoje. Jūsų kodas galėtų peržiūrėti ribojimo dėžutes, suprasti, kad tai neįmanoma, ir ignoruoti bet kokius objektus, kurie reikšmingai persidengia su kitais objektais.

![Dvi ribojimo dėžutės persidengia pomidorų pastos skardinę](../../../../../translated_images/lt/overlap-object-detection.d431e03cae75072a.webp)

Pavyzdyje aukščiau viena ribojimo dėžutė nurodo prognozuotą pomidorų pastos skardinę su 78.3% tikimybe. Antra ribojimo dėžutė yra šiek tiek mažesnė ir yra pirmosios ribojimo dėžutės viduje su 64.3% tikimybe. Jūsų kodas gali patikrinti ribojimo dėžutes, pamatyti, kad jos visiškai persidengia, ir ignoruoti mažesnę tikimybę, nes nėra galimybės, kad viena skardinė būtų kitos viduje.

✅ Ar galite sugalvoti situaciją, kurioje būtų galiojantis aptikimas vieno objekto kito viduje?

## Modelio pertreniravimas

Kaip ir su vaizdų klasifikatoriumi, galite pertreniruoti savo modelį naudodami duomenis, surinktus jūsų IoT įrenginiu. Naudojant šiuos realaus pasaulio duomenis užtikrinsite, kad jūsų modelis gerai veiktų, kai bus naudojamas iš IoT įrenginio.

Skirtingai nei su vaizdų klasifikatoriumi, negalite tiesiog pažymėti vaizdo. Vietoj to turite peržiūrėti kiekvieną ribojimo dėžutę, kurią aptiko modelis. Jei dėžutė yra aplink netinkamą objektą, ją reikia ištrinti, jei ji yra netinkamoje vietoje, ją reikia koreguoti.

### Užduotis – pertreniruoti modelį

1. Įsitikinkite, kad surinkote įvairius vaizdus naudodami savo IoT įrenginį.

1. Iš **Predictions** skirtuko pasirinkite vaizdą. Pamatysite raudonas dėžutes, nurodančias aptiktų objektų ribojimo dėžutes.

1. Peržiūrėkite kiekvieną ribojimo dėžutę. Pirmiausia pasirinkite ją ir pamatysite iššokantį langą su žyma. Naudokite rankenas ant ribojimo dėžutės kampų, kad prireikus koreguotumėte dydį. Jei žyma yra neteisinga, pašalinkite ją naudodami **X** mygtuką ir pridėkite tinkamą žymą. Jei ribojimo dėžutė neapima objekto, ištrinkite ją naudodami šiukšliadėžės mygtuką.

1. Baigę redagavimą uždarykite redaktorių, ir vaizdas bus perkeltas iš **Predictions** skirtuko į **Training Images** skirtuką. Pakartokite procesą visoms prognozėms.

1. Naudokite **Train** mygtuką, kad pertreniruotumėte savo modelį. Kai jis bus pertreniruotas, paskelbkite iteraciją ir atnaujinkite savo IoT įrenginį, kad naudotų naujos iteracijos URL.

1. Iš naujo įdiekite savo kodą ir išbandykite savo IoT įrenginį.

## Atsargų skaičiavimas

Naudodami aptiktų objektų skaičių ir ribojimo dėžutes, galite skaičiuoti atsargas lentynoje.

### Užduotis – skaičiuoti atsargas

Sekite atitinkamą vadovą, kad skaičiuotumėte atsargas naudodami objektų atpažinimo modelio rezultatus iš savo IoT įrenginio:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Vieno plokštės kompiuteris - Raspberry Pi/Virtualus įrenginys](single-board-computer-count-stock.md)

---

## 🚀 Iššūkis

Ar galite aptikti netinkamas atsargas? Apmokykite savo modelį keliems objektams, tada atnaujinkite savo programą, kad ji įspėtų jus, jei aptinkamos netinkamos atsargos.

Galbūt netgi išplėskite tai ir aptikite atsargas, esančias greta lentynoje, ir patikrinkite, ar kažkas buvo padėta netinkamoje vietoje, apibrėždami ribojimo dėžučių ribas.

## Klausimai po paskaitos

[Klausimai po paskaitos](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Apžvalga ir savarankiškas mokymasis

* Sužinokite daugiau apie tai, kaip sukurti pilną atsargų aptikimo sistemą, naudodami [„Out of stock detection at the edge“ modelio vadovą Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Sužinokite kitus būdus, kaip kurti pilnus mažmeninės prekybos sprendimus, derinant įvairias IoT ir debesų paslaugas, žiūrėdami

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.