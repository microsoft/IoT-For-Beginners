# Vietos sekimas

![Šios pamokos eskizų užrašų apžvalga](../../../../../translated_images/lt/lesson-11.9fddbac4b664c6d5.webp)

> Eskizų užrašai: [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

## Klausimynas prieš paskaitą

[Klausimynas prieš paskaitą](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Įvadas

Pagrindinis procesas, kaip maistas iš ūkininko pasiekia vartotoją, apima dėžių su produktais pakrovimą į sunkvežimius, laivus, lėktuvus ar kitus komercinius transporto priemones ir jų pristatymą - tiesiogiai klientui arba į centrinį centrą ar sandėlį perdirbimui. Visas procesas nuo ūkio iki vartotojo yra vadinamas *tiekimo grandine*. Žemiau pateiktame Arizonos valstybinio universiteto W. P. Carey verslo mokyklos vaizdo įraše išsamiau aptariama tiekimo grandinės idėja ir jos valdymas.

[![Kas yra tiekimo grandinės valdymas? Vaizdo įrašas iš Arizonos valstybinio universiteto W. P. Carey verslo mokyklos](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Spustelėkite paveikslėlį aukščiau, kad peržiūrėtumėte vaizdo įrašą

IoT įrenginių pridėjimas gali žymiai pagerinti jūsų tiekimo grandinę, leidžiant valdyti, kur yra prekės, geriau planuoti transportavimą ir prekių tvarkymą bei greičiau reaguoti į problemas.

Valdant transporto priemonių parką, pavyzdžiui, sunkvežimius, naudinga žinoti, kur tam tikru metu yra kiekviena transporto priemonė. Transporto priemonės gali būti aprūpintos GPS jutikliais, kurie siunčia savo buvimo vietą į IoT sistemas, leidžiančias savininkams nustatyti jų buvimo vietą, matyti jų maršrutą ir žinoti, kada jos atvyks į paskirties vietą. Dauguma transporto priemonių veikia už WiFi ryšio zonos ribų, todėl jos naudoja mobiliojo ryšio tinklus šiems duomenims siųsti. Kartais GPS jutiklis yra integruotas į sudėtingesnius IoT įrenginius, tokius kaip elektroniniai kelionės žurnalai. Šie įrenginiai seka, kiek laiko sunkvežimis buvo kelyje, kad vairuotojai laikytųsi vietinių darbo valandų įstatymų.

Šioje pamokoje sužinosite, kaip sekti transporto priemonės buvimo vietą naudojant pasaulinės padėties nustatymo sistemos (GPS) jutiklį.

Šioje pamokoje aptarsime:

* [Susietos transporto priemonės](../../../../../3-transport/lessons/1-location-tracking)
* [Geografinės koordinatės](../../../../../3-transport/lessons/1-location-tracking)
* [Pasaulinės padėties nustatymo sistemos (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [GPS jutiklio duomenų skaitymas](../../../../../3-transport/lessons/1-location-tracking)
* [NMEA GPS duomenys](../../../../../3-transport/lessons/1-location-tracking)
* [GPS jutiklio duomenų dekodavimas](../../../../../3-transport/lessons/1-location-tracking)

## Susietos transporto priemonės

IoT keičia prekių transportavimo būdą, sukuriant *susietų transporto priemonių* parkus. Šios transporto priemonės yra prijungtos prie centrinių IT sistemų, kurios praneša apie jų buvimo vietą ir kitus jutiklių duomenis. Turint susietų transporto priemonių parką, galima gauti daugybę privalumų:

* Vietos sekimas - galite tiksliai nustatyti, kur tam tikru metu yra transporto priemonė, leidžiant:

  * Gauti pranešimus, kai transporto priemonė artėja prie paskirties vietos, kad būtų galima pasiruošti iškrovimui
  * Rasti pavogtas transporto priemones
  * Derinti vietos ir maršruto duomenis su eismo problemomis, kad būtų galima perplanuoti maršrutus kelionės metu
  * Laikytis mokesčių reikalavimų. Kai kurios šalys apmokestina transporto priemones pagal nuvažiuotą atstumą viešaisiais keliais (pvz., [Naujosios Zelandijos RUC](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), todėl žinant, kada transporto priemonė yra viešuosiuose keliuose, o kada privačiuose, lengviau apskaičiuoti mokėtinus mokesčius.
  * Žinoti, kur siųsti techninės priežiūros komandas gedimo atveju

* Vairuotojo telemetrija - galimybė užtikrinti, kad vairuotojai laikosi greičio apribojimų, tinkamai įveikia posūkius, stabdo efektyviai ir vairuoja saugiai. Susietos transporto priemonės taip pat gali turėti kameras, kurios fiksuoja incidentus. Tai gali būti susieta su draudimu, suteikiant mažesnes įmokas geriems vairuotojams.

* Vairuotojo darbo valandų laikymasis - užtikrinant, kad vairuotojai vairuotų tik teisėtai leidžiamas valandas, remiantis variklio įjungimo ir išjungimo laikais.

Šiuos privalumus galima derinti - pavyzdžiui, derinant vairuotojo darbo valandų laikymąsi su vietos sekimu, kad būtų galima perplanuoti maršrutus, jei vairuotojas negali pasiekti paskirties vietos per leidžiamas vairavimo valandas. Tai taip pat galima derinti su kitais transporto priemonių telemetrijos duomenimis, pvz., temperatūros duomenimis iš temperatūros kontroliuojamų sunkvežimių, leidžiant perplanuoti maršrutus, jei dabartinis maršrutas reikštų, kad prekės negali būti laikomos tinkamoje temperatūroje.

> 🎓 Logistika - tai procesas, kai prekės transportuojamos iš vienos vietos į kitą, pavyzdžiui, iš ūkio į prekybos centrą per vieną ar kelis sandėlius. Ūkininkas supakuoja pomidorų dėžes, kurios pakraunamos į sunkvežimį, pristatomos į centrinį sandėlį ir perkraunamos į antrą sunkvežimį, kuriame gali būti įvairių rūšių produktų, kurie vėliau pristatomi į prekybos centrą.

Pagrindinis transporto priemonių sekimo komponentas yra GPS - jutikliai, kurie gali nustatyti savo buvimo vietą bet kurioje Žemės vietoje. Šioje pamokoje sužinosite, kaip naudoti GPS jutiklį, pradedant nuo to, kaip apibrėžti vietą Žemėje.

## Geografinės koordinatės

Geografinės koordinatės naudojamos taškams Žemės paviršiuje apibrėžti, panašiai kaip koordinatės naudojamos pikseliui kompiuterio ekrane nurodyti arba dygsniams kryželiu siuvinėjime išdėstyti. Vienam taškui apibrėžti naudojama koordinatų pora. Pavyzdžiui, „Microsoft“ būstinė Redmonde, Vašingtono valstijoje, JAV yra 47.6423109, -122.1390293.

### Platuma ir ilguma

Žemė yra sfera - trijų matmenų apskritimas. Dėl to taškai apibrėžiami padalijant ją į 360 laipsnių, kaip ir apskritimų geometrijoje. Platuma matuoja laipsnių skaičių iš šiaurės į pietus, o ilguma - iš rytų į vakarus.

> 💁 Niekas tiksliai nežino, kodėl apskritimai padalijami į 360 laipsnių. [Laipsnio (kampo) puslapis Vikipedijoje](https://wikipedia.org/wiki/Degree_(angle)) aptaria galimas priežastis.

![Platumos linijos nuo 90° Šiaurės ašigalyje, 45° pusiaukelėje tarp Šiaurės ašigalio ir pusiaujo, 0° pusiaujo, -45° pusiaukelėje tarp pusiaujo ir Pietų ašigalio, ir -90° Pietų ašigalyje](../../../../../translated_images/lt/latitude-lines.11d8d91dfb2014a5.webp)

Platuma matuojama naudojant linijas, kurios apsupa Žemę ir eina lygiagrečiai pusiaujo, padalijant Šiaurės ir Pietų pusrutulius į po 90°. Pusiaujo platuma yra 0°, Šiaurės ašigalis yra 90°, dar vadinamas 90° šiaurės, o Pietų ašigalis yra -90°, arba 90° pietų.

Ilguma matuojama kaip laipsnių skaičius į rytus ir vakarus. 0° ilgumos pradžia vadinama *Pagrindiniu meridianu*, kuris 1884 m. buvo apibrėžtas kaip linija nuo Šiaurės iki Pietų ašigalio, einanti per [Britų karališkąją observatoriją Grinviče, Anglijoje](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Ilgumos linijos nuo -180° į vakarus nuo Pagrindinio meridiano, iki 0° Pagrindiniame meridiane, iki 180° į rytus nuo Pagrindinio meridiano](../../../../../translated_images/lt/longitude-meridians.ab4ef1c91c064586.webp)

> 🎓 Meridianas yra įsivaizduojama tiesi linija, einanti nuo Šiaurės ašigalio iki Pietų ašigalio, sudaranti puslankį.

Norint išmatuoti taško ilgumą, matuojamas laipsnių skaičius aplink pusiaujo liniją nuo Pagrindinio meridiano iki meridiano, einančio per tą tašką. Ilguma svyruoja nuo -180°, arba 180° vakarų, per 0° Pagrindiniame meridiane, iki 180°, arba 180° rytų. 180° ir -180° reiškia tą patį tašką, vadinamą antimeridianu arba 180-uoju meridianu. Tai yra meridianas priešingoje Žemės pusėje nuo Pagrindinio meridiano.

> 💁 Antimeridianas neturėtų būti painiojamas su Tarptautine datos linija, kuri yra maždaug toje pačioje vietoje, tačiau nėra tiesi linija ir kinta, kad atitiktų geopolitines ribas.

✅ Atlikite tyrimą: pabandykite rasti savo dabartinės vietos platumą ir ilgumą.

### Laipsniai, minutės ir sekundės vs dešimtainiai laipsniai

Tradiciškai platumos ir ilgumos laipsniai buvo matuojami naudojant šešiasdešimtainę skaičiavimo sistemą, kurią naudojo senovės babiloniečiai, pirmieji matavę ir registravę laiką bei atstumą. Tikriausiai kasdien naudojate šešiasdešimtainę sistemą net to nesuvokdami - dalindami valandas į 60 minučių ir minutes į 60 sekundžių.

Ilguma ir platuma matuojamos laipsniais, minutėmis ir sekundėmis, kur viena minutė yra 1/60 laipsnio, o viena sekundė yra 1/60 minutės.

Pavyzdžiui, ties pusiauju:

* 1° platumos yra **111,3 kilometro**
* 1 minutė platumos yra 111,3/60 = **1,855 kilometro**
* 1 sekundė platumos yra 1,855/60 = **0,031 kilometro**

Minutės simbolis yra vienguba kabutė, sekundės - dviguba kabutė. Pavyzdžiui, 2 laipsniai, 17 minučių ir 43 sekundės būtų užrašyta kaip 2°17'43". Sekundžių dalys pateikiamos kaip dešimtainės, pavyzdžiui, pusė sekundės yra 0°0'0.5".

Kompiuteriai neveikia šešiasdešimtaine sistema, todėl šios koordinatės GPS duomenyse dažniausiai pateikiamos kaip dešimtainiai laipsniai. Pavyzdžiui, 2°17'43" yra 2,295277. Laipsnio simbolis paprastai praleidžiamas.

Taško koordinatės visada pateikiamos kaip `platuma, ilguma`, todėl ankstesniame pavyzdyje „Microsoft“ būstinė, kurios koordinatės yra 47.6423109,-122.117198, turi:

* Platuma: 47.6423109 (47.6423109 laipsnio į šiaurę nuo pusiaujo)
* Ilguma: -122.1390293 (122.1390293 laipsnio į vakarus nuo Pagrindinio meridiano).

![„Microsoft“ būstinė 47.6423109,-122.117198](../../../../../translated_images/lt/microsoft-gps-location-world.a321d481b010f6ad.webp)

## Pasaulinės padėties nustatymo sistemos (GPS)

GPS sistemos naudoja kelis palydovus, skriejančius aplink Žemę, kad nustatytų jūsų buvimo vietą. Tikriausiai naudojote GPS sistemas net to nesuvokdami - norėdami rasti savo vietą žemėlapių programėlėje telefone, pavyzdžiui, „Apple Maps“ ar „Google Maps“, arba norėdami pamatyti, kur yra jūsų užsakytas automobilis tokiose programėlėse kaip „Uber“ ar „Lyft“, arba naudodamiesi palydovine navigacija (sat-nav) automobilyje.

> 🎓 „Palydovinė navigacija“ naudoja GPS palydovus!

GPS sistemos veikia taip, kad keli palydovai siunčia signalą su kiekvieno palydovo dabartine padėtimi ir tiksliu laiko žymekliu. Šie signalai siunčiami radijo bangomis ir aptinkami GPS jutiklio antenos. GPS jutiklis aptinka šiuos signalus ir, naudodamas dabartinį laiką, matuoja, kiek laiko užtruko signalui pasiekti jutiklį nuo palydovo. Kadangi radijo bangų greitis yra pastovus, GPS jutiklis gali naudoti atsiųstą laiko žymeklį, kad apskaičiuotų atstumą nuo palydovo iki jutiklio. Derindamas duomenis iš bent 3 palydovų su jų atsiųstomis padėtimis, GPS jutiklis gali tiksliai nustatyti savo buvimo vietą Žemėje.

> 💁 GPS jutikliams reikia antenų, kad aptiktų radijo bangas. Antenos, įmontuotos sunkvežimiuose ir automobiliuose su įmontuotu GPS, yra išdėstytos taip, kad gautų gerą signalą, paprastai ant priekinio stiklo arba stogo. Jei naudojate atskirą GPS sistemą, pavyzdžiui, išmanųjį telefoną ar IoT įrenginį, turite užtikrinti, kad GPS sistemoje ar telefone įmontuota antena turėtų aiškų vaizdą į dangų, pavyzdžiui, būtų pritvirtinta prie priekinio stiklo.

![Žinant atstumą nuo jutiklio iki kelių palydovų, galima apskaičiuoti buvimo vietą](../../../../../translated_images/lt/gps-satellites.04acf1148fe25fbf.webp)

GPS palydovai skrieja aplink Žemę, nėra fiksuotoje vietoje virš jutiklio, todėl vietos duomenys apima aukštį virš jūros lygio, taip pat platumą ir ilgumą.

GPS anksčiau turėjo tikslumo apribojimų, kuriuos nustatė JAV kariuomenė, ribojant tikslumą iki maždaug 5 metrų. Šis apribojimas buvo panaikintas 2000 m., leidžiant pasiekti 30 centimetrų tikslumą. Tačiau tokio tikslumo ne visada galima pasiekti dėl signalų trikdžių.

✅ Jei turite išmanųjį telefoną, paleiskite žemėlapių programėlę ir pažiūrėkite, koks tikslus yra jūsų buvimo vietos nustatymas. Gali prireikti šiek tiek laiko, kol jūsų telefonas aptiks kelis palydovus, kad gautų tikslesnę vietą.
💁 Palydovai turi itin tikslius atominius laikrodžius, tačiau jie kasdien nukrypsta 38 mikrosekundėmis (0,0000038 sekundės) lyginant su atominiais laikrodžiais Žemėje. Tai vyksta dėl laiko sulėtėjimo, kai greitis didėja, kaip numatyta Einšteino specialiosios ir bendrosios reliatyvumo teorijose – palydovai juda greičiau nei Žemės sukimosi greitis. Šis nukrypimas buvo panaudotas specialiosios ir bendrosios reliatyvumo teorijų prognozėms patvirtinti ir turi būti koreguojamas GPS sistemų projektavime. Tiesiogine prasme, GPS palydove laikas eina lėčiau.
GPS sistemos buvo sukurtos ir įdiegtos daugelio šalių ir politinių sąjungų, įskaitant JAV, Rusiją, Japoniją, Indiją, ES ir Kiniją. Šiuolaikiniai GPS jutikliai gali prisijungti prie daugumos šių sistemų, kad gautų greitesnius ir tikslesnius duomenis.

> 🎓 Palydovų grupės kiekvienoje sistemoje vadinamos konstelacijomis.

## Skaitykite GPS jutiklio duomenis

Dauguma GPS jutiklių perduoda GPS duomenis per UART.

> ⚠️ UART buvo aptartas [projekto 2, pamokoje 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Jei reikia, grįžkite prie tos pamokos.

Galite naudoti GPS jutiklį savo IoT įrenginyje, kad gautumėte GPS duomenis.

### Užduotis - prijunkite GPS jutiklį ir skaitykite GPS duomenis

Sekite atitinkamą vadovą, kad galėtumėte skaityti GPS duomenis naudodami savo IoT įrenginį:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Vieno plokštės kompiuteris - Raspberry Pi](pi-gps-sensor.md)
* [Vieno plokštės kompiuteris - Virtualus įrenginys](virtual-device-gps-sensor.md)

## NMEA GPS duomenys

Kai paleidote savo kodą, galėjote pastebėti, kad išvestyje yra kažkas, kas atrodo kaip nesuprantamas tekstas. Tai iš tikrųjų yra standartiniai GPS duomenys, ir jie turi prasmę.

GPS jutikliai perduoda duomenis naudodami NMEA pranešimus, laikydamiesi NMEA 0183 standarto. NMEA yra akronimas, reiškiantis [National Marine Electronics Association](https://www.nmea.org), JAV prekybos organizaciją, nustatančią standartus ryšiui tarp jūrinių elektronikos prietaisų.

> 💁 Šis standartas yra patentuotas ir kainuoja bent 2 000 JAV dolerių, tačiau pakankamai informacijos apie jį yra viešoje erdvėje, kad dauguma standarto buvo atvirkščiai sukurta ir gali būti naudojama atvirojo kodo ir kitame nekomerciniame kode.

Šie pranešimai yra tekstiniai. Kiekvienas pranešimas susideda iš *sakinių*, kurie prasideda `$` simboliu, po kurio eina 2 simboliai, nurodantys pranešimo šaltinį (pvz., GP JAV GPS sistemai, GN GLONASS, Rusijos GPS sistemai), ir 3 simboliai, nurodantys pranešimo tipą. Likusi pranešimo dalis yra laukai, atskirti kableliais, baigiant naujos eilutės simboliu.

Kai kurie pranešimų tipai, kuriuos galima gauti, yra:

| Tipas | Aprašymas |
| ---- | ----------- |
| GGA | GPS fiksavimo duomenys, įskaitant GPS jutiklio platumą, ilgumą ir aukštį, kartu su palydovų skaičiumi, naudojamu šiam fiksavimui apskaičiuoti. |
| ZDA | Dabartinė data ir laikas, įskaitant vietos laiko zoną |
| GSV | Informacija apie matomus palydovus - apibrėžta kaip palydovai, kurių signalus GPS jutiklis gali aptikti |

> 💁 GPS duomenys apima laiko žymes, todėl jūsų IoT įrenginys gali gauti laiką iš GPS jutiklio, o ne pasikliauti NTP serveriu ar vidiniu realaus laiko laikrodžiu.

GGA pranešimas apima dabartinę vietą, naudojant `(dd)dmm.mmmm` formatą, kartu su vienu simboliu, nurodančiu kryptį. `d` formate reiškia laipsnius, `m` - minutes, o sekundės pateikiamos kaip dešimtainės minutės dalys. Pavyzdžiui, 2°17'43" būtų 217.716666667 - 2 laipsniai, 17.716666667 minutės.

Krypties simbolis gali būti `N` arba `S` platumai, nurodant šiaurę arba pietus, ir `E` arba `W` ilgumui, nurodant rytus arba vakarus. Pavyzdžiui, platuma 2°17'43" turėtų krypties simbolį `N`, -2°17'43" turėtų krypties simbolį `S`.

Pavyzdžiui - NMEA sakinys `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* Platumos dalis yra `4738.538654,N`, kuri konvertuojama į 47.6423109 dešimtainiais laipsniais. `4738.538654` yra 47.6423109, o kryptis yra `N` (šiaurė), todėl tai yra teigiama platuma.

* Ilgumos dalis yra `12208.341758,W`, kuri konvertuojama į -122.1390293 dešimtainiais laipsniais. `12208.341758` yra 122.1390293°, o kryptis yra `W` (vakarai), todėl tai yra neigiama ilguma.

## Dekoduokite GPS jutiklio duomenis

Užuot naudoję neapdorotus NMEA duomenis, geriau juos dekoduoti į naudingesnį formatą. Yra daugybė atvirojo kodo bibliotekų, kurias galite naudoti, kad padėtumėte išgauti naudingus duomenis iš neapdorotų NMEA pranešimų.

### Užduotis - dekoduokite GPS jutiklio duomenis

Sekite atitinkamą vadovą, kad dekoduotumėte GPS jutiklio duomenis naudodami savo IoT įrenginį:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Vieno plokštės kompiuteris - Raspberry Pi/Virtualus IoT įrenginys](single-board-computer-gps-decode.md)

---

## 🚀 Iššūkis

Parašykite savo NMEA dekoderį! Užuot pasikliovę trečiųjų šalių bibliotekomis, skirtomis NMEA sakinių dekodavimui, ar galite parašyti savo dekoderį, kad išgautumėte platumą ir ilgumą iš NMEA sakinių?

## Po paskaitos testas

[Po paskaitos testas](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Apžvalga ir savarankiškas mokymasis

* Skaitykite daugiau apie geografinės koordinatės [Geografinės koordinatės sistemos puslapyje Vikipedijoje](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Skaitykite apie pagrindinius meridianus kitose dangaus kūnuose, išskyrus Žemę, [Pagrindinio meridiano puslapyje Vikipedijoje](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies).
* Tyrinėkite įvairias GPS sistemas, sukurtas įvairių pasaulio vyriausybių ir politinių sąjungų, tokių kaip ES, Japonija, Rusija, Indija ir JAV.

## Užduotis

[Tyrinėkite kitus GPS duomenis](assignment.md)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.