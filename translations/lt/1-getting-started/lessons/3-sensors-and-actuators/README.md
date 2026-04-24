# Sąveika su fiziniu pasauliu naudojant jutiklius ir pavaras

![Šios pamokos apžvalga pieštuku](../../../../../translated_images/lt/lesson-3.cc3b7b4cd646de59.webp)

> Piešinys sukurtas [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

Ši pamoka buvo dėstoma kaip [Hello IoT serijos](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) dalis, kurią organizavo [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Pamoka buvo pateikta per 2 vaizdo įrašus – 1 valandos trukmės pamoką ir 1 valandos klausimų-atsakymų sesiją, kurioje gilintasi į pamokos temas.

[![Pamoka 3: Sąveika su fiziniu pasauliu naudojant jutiklius ir pavaras](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Pamoka 3: Sąveika su fiziniu pasauliu naudojant jutiklius ir pavaras – Klausimų-atsakymų sesija](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Spustelėkite aukščiau esančius paveikslėlius, kad peržiūrėtumėte vaizdo įrašus

## Klausimynas prieš pamoką

[Klausimynas prieš pamoką](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Įvadas

Šioje pamokoje pristatomi du svarbūs jūsų IoT įrenginio komponentai – jutikliai ir pavaros. Taip pat praktiškai išbandysite abu šiuos komponentus, pridėdami šviesos jutiklį prie savo IoT projekto ir LED lemputę, kurią valdys šviesos lygiai, efektyviai sukurdami naktinę lemputę.

Šioje pamokoje aptarsime:

* [Kas yra jutikliai?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Kaip naudoti jutiklį](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Jutiklių tipai](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Kas yra pavaros?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Kaip naudoti pavarą](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Pavarų tipai](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Kas yra jutikliai?

Jutikliai yra aparatinės įrangos įrenginiai, kurie fiksuoja fizinį pasaulį – jie matuoja vieną ar daugiau aplinkos savybių ir perduoda informaciją IoT įrenginiui. Jutiklių įvairovė yra didžiulė, nes galima matuoti daugybę dalykų – nuo natūralių savybių, tokių kaip oro temperatūra, iki fizinių sąveikų, tokių kaip judėjimas.

Kai kurie dažni jutikliai:

* Temperatūros jutikliai – jie matuoja oro temperatūrą arba temperatūrą to, į ką jie yra panardinti. Mėgėjams ir kūrėjams šie jutikliai dažnai būna sujungti su oro slėgio ir drėgmės matavimu viename įrenginyje.
* Mygtukai – jie fiksuoja, kada yra paspausti.
* Šviesos jutikliai – jie aptinka šviesos lygius ir gali būti skirti konkrečioms spalvoms, UV šviesai, IR šviesai ar bendrai matomai šviesai.
* Kameros – jos fiksuoja vizualinį pasaulio vaizdą, fotografuodamos arba transliuodamos vaizdo įrašą.
* Akcelerometrai – jie fiksuoja judėjimą keliomis kryptimis.
* Mikrofonai – jie fiksuoja garsą, tiek bendrą garso lygį, tiek kryptinį garsą.

✅ Atlikite tyrimą. Kokius jutiklius turi jūsų telefonas?

Visi jutikliai turi vieną bendrą bruožą – jie konvertuoja tai, ką fiksuoja, į elektrinį signalą, kurį gali interpretuoti IoT įrenginys. Kaip šis signalas interpretuojamas, priklauso nuo jutiklio ir komunikacijos protokolo, naudojamo bendrauti su IoT įrenginiu.

## Kaip naudoti jutiklį

Vadovaukitės atitinkamu vadovu, kad pridėtumėte jutiklį prie savo IoT įrenginio:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Vienos plokštės kompiuteris - Raspberry Pi](pi-sensor.md)
* [Vienos plokštės kompiuteris - Virtualus įrenginys](virtual-device-sensor.md)

## Jutiklių tipai

Jutikliai gali būti analoginiai arba skaitmeniniai.

### Analoginiai jutikliai

Kai kurie paprasčiausi jutikliai yra analoginiai. Šie jutikliai gauna įtampą iš IoT įrenginio, jutiklio komponentai koreguoja šią įtampą, o grąžinama įtampa yra matuojama, kad būtų nustatyta jutiklio reikšmė.

> 🎓 Įtampa yra matas, rodantis, kiek stipriai elektros srovė stumiama iš vienos vietos į kitą, pavyzdžiui, iš teigiamo baterijos poliaus į neigiamą. Pavyzdžiui, standartinė AA baterija yra 1,5V (V yra voltų simbolis) ir gali stumti elektrą su 1,5V jėga. Skirtingai elektrinei įrangai reikia skirtingų įtampų, pavyzdžiui, LED lemputė gali šviesti su 2-3V, o 100W kaitrinė lemputė reikalautų 240V. Daugiau apie įtampą galite perskaityti [Wikipedia puslapyje apie įtampą](https://wikipedia.org/wiki/Voltage).

Vienas pavyzdys yra potenciometras. Tai yra ratukas, kurį galima pasukti tarp dviejų padėčių, o jutiklis matuoja pasukimo kampą.

![Potenciometras, nustatytas į vidurinę padėtį, gauna 5 voltus ir grąžina 3,8 voltus](../../../../../translated_images/lt/potentiometer.35a348b9ce22f6ec.webp)

IoT įrenginys siunčia elektrinį signalą į potenciometrą tam tikra įtampa, pavyzdžiui, 5 voltų (5V). Kai potenciometras reguliuojamas, jis keičia išėjimo įtampą. Įsivaizduokite, kad turite potenciometrą, pažymėtą kaip ratuką, kuris eina nuo 0 iki [11](https://wikipedia.org/wiki/Up_to_eleven), pavyzdžiui, stiprintuvo garsumo reguliatorių. Kai potenciometras yra visiškai išjungtas (0), išėjimo įtampa bus 0V (0 voltų). Kai jis yra visiškai įjungtas (11), išėjimo įtampa bus 5V (5 voltai).

> 🎓 Tai yra supaprastintas paaiškinimas, daugiau apie potenciometrus ir kintamuosius rezistorius galite perskaityti [Wikipedia puslapyje apie potenciometrus](https://wikipedia.org/wiki/Potentiometer).

Jutiklio išėjimo įtampa yra skaitoma IoT įrenginio, kuris gali į ją reaguoti. Priklausomai nuo jutiklio, ši įtampa gali būti savavališka reikšmė arba atitikti standartinį vienetą. Pavyzdžiui, analoginis temperatūros jutiklis, pagrįstas [termistoriumi](https://wikipedia.org/wiki/Thermistor), keičia savo varžą priklausomai nuo temperatūros. Išėjimo įtampa gali būti konvertuojama į temperatūrą Kelvinais, o atitinkamai į °C arba °F, naudojant kodą.

✅ Kaip manote, kas nutiktų, jei jutiklis grąžintų didesnę įtampą nei buvo siunčiama (pavyzdžiui, iš išorinio maitinimo šaltinio)? ⛔️ NEBANDYKITE to išbandyti.

#### Analoginio signalo konvertavimas į skaitmeninį

IoT įrenginiai yra skaitmeniniai – jie negali dirbti su analoginėmis reikšmėmis, tik su 0 ir 1. Tai reiškia, kad analoginės jutiklio reikšmės turi būti konvertuojamos į skaitmeninį signalą prieš jas apdorojant. Daugelyje IoT įrenginių yra analoginio į skaitmeninį keitikliai (ADC), kurie konvertuoja analoginius įėjimus į skaitmenines reikšmes. Jutikliai taip pat gali dirbti su ADC per jungčių plokštę. Pavyzdžiui, Seeed Grove ekosistemoje su Raspberry Pi analoginiai jutikliai jungiasi prie specifinių prievadų ant „hat“ plokštės, kuri yra prijungta prie Pi GPIO kaiščių, o ši plokštė turi ADC, kuris konvertuoja įtampą į skaitmeninį signalą, siunčiamą per GPIO kaiščius.

Įsivaizduokite, kad turite analoginį šviesos jutiklį, prijungtą prie IoT įrenginio, kuris naudoja 3,3V, ir jis grąžina 1V. Šis 1V nieko nereiškia skaitmeniniame pasaulyje, todėl reikia jį konvertuoti. Įtampa bus konvertuojama į analoginę reikšmę pagal skalę, priklausomai nuo įrenginio ir jutiklio. Pavyzdžiui, Seeed Grove šviesos jutiklis išveda reikšmes nuo 0 iki 1,023. Šiam jutikliui, veikiančiam su 3,3V, 1V išėjimas būtų reikšmė 300. IoT įrenginys negali apdoroti 300 kaip analoginės reikšmės, todėl ši reikšmė būtų konvertuojama į `0000000100101100`, tai yra dvejetainė 300 reikšmės reprezentacija, kurią pateikia Grove „hat“. Tada tai būtų apdorojama IoT įrenginyje.

✅ Jei nežinote, kas yra dvejetainė sistema, atlikite nedidelį tyrimą, kad sužinotumėte, kaip skaičiai yra reprezentuojami 0 ir 1. [BBC Bitesize įvadas į dvejetainę sistemą](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) yra puiki vieta pradėti.

Iš programavimo perspektyvos visa tai paprastai yra tvarkoma bibliotekų, kurios pateikiamos kartu su jutikliais, todėl jums nereikia rūpintis šia konversija patiems. Pavyzdžiui, naudojant Grove šviesos jutiklį, galite naudoti Python biblioteką ir iškviesti `light` savybę arba naudoti Arduino biblioteką ir iškviesti `analogRead`, kad gautumėte reikšmę 300.

### Skaitmeniniai jutikliai

Skaitmeniniai jutikliai, kaip ir analoginiai, fiksuoja aplinką naudodami elektrinės įtampos pokyčius. Skirtumas tas, kad jie išveda skaitmeninį signalą, arba matuodami tik dvi būsenas, arba naudodami įmontuotą ADC. Skaitmeniniai jutikliai tampa vis dažnesni, kad nereikėtų naudoti ADC jungčių plokštėje ar pačiame IoT įrenginyje.

Paprasčiausias skaitmeninis jutiklis yra mygtukas arba jungiklis. Tai jutiklis su dviem būsenomis – įjungta arba išjungta.

![Mygtukas gauna 5 voltus. Kai nepaspaustas, grąžina 0 voltų, kai paspaustas, grąžina 5 voltus](../../../../../translated_images/lt/button.eadb560b77ac45e5.webp)

IoT įrenginio kaiščiai, tokie kaip GPIO, gali tiesiogiai matuoti šį signalą kaip 0 arba 1. Jei siunčiama įtampa yra tokia pati kaip grąžinama, reikšmė yra 1, kitaip – 0. Nereikia konvertuoti signalo, jis gali būti tik 1 arba 0.

> 💁 Įtampos niekada nėra visiškai tikslios, ypač todėl, kad jutiklio komponentai turi tam tikrą varžą, todėl paprastai yra tolerancija. Pavyzdžiui, Raspberry Pi GPIO kaiščiai veikia su 3,3V ir skaito grąžinamą signalą virš 1,8V kaip 1, o žemiau 1,8V kaip 0.

* 3,3V siunčiama į mygtuką. Mygtukas išjungtas, todėl grąžinama 0V, reikšmė yra 0.
* 3,3V siunčiama į mygtuką. Mygtukas įjungtas, todėl grąžinama 3,3V, reikšmė yra 1.

Sudėtingesni skaitmeniniai jutikliai skaito analogines reikšmes, tada jas konvertuoja naudodami įmontuotus ADC į skaitmeninius signalus. Pavyzdžiui, skaitmeninis temperatūros jutiklis vis tiek naudos termoporą taip pat, kaip analoginis jutiklis, ir vis tiek matuos įtampos pokytį, kurį sukelia termoporos varža esant dabartinei temperatūrai. Vietoj to, kad grąžintų analoginę reikšmę ir pasikliautų įrenginiu ar jungčių plokšte, kad konvertuotų į skaitmeninį signalą, įmontuotas ADC konvertuos reikšmę ir išsiųs ją kaip 0 ir 1 seriją į IoT įrenginį. Šie 0 ir 1 siunčiami taip pat, kaip skaitmeninis signalas mygtukui, kur 1 yra pilna įtampa, o 0 yra 0V.

![Skaitmeninis temperatūros jutiklis konvertuoja analoginį matavimą į dvejetainius duomenis, kur 0 yra 0 voltų, o 1 yra 5 voltai, prieš siunčiant juos į IoT įrenginį](../../../../../translated_images/lt/temperature-as-digital.85004491b977bae1.webp)

Skaitmeninių duomenų siuntimas leidžia jutikliams tapti sudėtingesniems ir siųsti detalesnius duomenis, net užšifruotus duomenis saugiems jutikliams. Vienas pavyzdys yra kamera. Tai yra jutiklis, kuris fiksuoja vaizdą ir siunčia jį kaip skaitmeninius duomenis, kuriuose yra tas vaizdas, dažniausiai suspaustu formatu, pavyzdžiui, JPEG, kad būtų galima skaityti IoT įrenginyje. Ji netgi gali transliuoti vaizdo įrašą, fiksuodama vaizdus ir siųsdama arba visą vaizdo kadrą po kadro, arba suspaustą vaizdo srautą.

## Kas yra pavaros?

Pavaros yra priešingybė jutikliams – jos konvertuoja elektrinį signalą iš jūsų IoT įrenginio į sąveiką su fiziniu pasauliu, pavyzdžiui, skleidžia šviesą ar garsą arba judina variklį.

Kai kurios dažnos pavaros:

* LED – jos skleidžia šviesą, kai įjungiamos.
* Garsiakalbis – jis skleidžia garsą pagal siunčiamą signalą, nuo paprasto pyptelėjimo iki muzikos grojimo.
* Žingsninis variklis – jis konvertuoja signalą į tam tikrą sukimosi kampą, pavyzdžiui, pasuka ratuką 90°.
* Relė – tai jungikliai, kuriuos galima įjungti arba išjungti elektriniu signalu. Jie leidžia mažai IoT įrenginio įtampai įjungti didesnes įtampas.
* Ekranai – tai sudėtingesnės pavaros, kurios rodo informaciją kelių segmentų ekrane. Ekranai gali būti nuo paprastų LED ekranų iki aukštos raiškos vaizdo monitorių.

✅ Atlikite tyrimą. Kokias pavaras turi jūsų telefonas?

## Kaip naudoti pavarą

Vadovaukitės atitinkamu vadovu, kad pridėtumėte pavarą prie savo IoT įrenginio, kurią valdys jutiklis, kad sukurtumėte IoT naktinę lemputę. Ji rinks šviesos lygius iš šviesos jutiklio ir naudos pavarą – LED lemputę, kuri skleis šviesą, kai aptiktas šviesos lygis bus per žemas.

![Užduoties schema, rodanti šviesos lygių nuskaitym
![Šviesa, pritemdyta esant mažai įtampai ir ryškesnė esant didesnei įtampai](../../../../../translated_images/lt/dimmable-light.9ceffeb195dec1a8.webp)

Kaip ir su jutikliais, tikrasis IoT įrenginys veikia su skaitmeniniais signalais, o ne analoginiais. Tai reiškia, kad norint siųsti analoginį signalą, IoT įrenginiui reikia skaitmeninio-analoginio keitiklio (DAC), kuris gali būti tiesiogiai įrenginyje arba jungties plokštėje. Šis keitiklis paverčia 0 ir 1 iš IoT įrenginio į analoginę įtampą, kurią gali naudoti aktuatorius.

✅ Kas, jūsų manymu, nutiktų, jei IoT įrenginys siųstų didesnę įtampą, nei aktuatorius gali apdoroti?  
⛔️ NEBANDYKITE to išbandyti.

#### Impulsų pločio moduliacija

Kita galimybė konvertuoti skaitmeninius signalus iš IoT įrenginio į analoginį signalą yra impulsų pločio moduliacija (PWM). Tai apima daugybės trumpų skaitmeninių impulsų siuntimą, kurie veikia kaip analoginis signalas.

Pavyzdžiui, PWM galima naudoti variklio greičiui reguliuoti.

Įsivaizduokite, kad kontroliuojate variklį su 5V maitinimu. Jūs siunčiate trumpą impulsą į variklį, įjungdami aukštą įtampą (5V) dviem šimtosioms sekundės (0,02s). Per tą laiką variklis gali pasisukti vieną dešimtąją apsisukimo arba 36°. Signalas tada sustoja dviem šimtosioms sekundės (0,02s), siunčiant žemą signalą (0V). Kiekvienas įjungimo ir išjungimo ciklas trunka 0,04s. Ciklas kartojasi.

![Impulsų pločio moduliacija: variklio sukimas 150 RPM](../../../../../translated_images/lt/pwm-motor-150rpm.83347ac04ca38482.webp)

Tai reiškia, kad per vieną sekundę siunčiate 25 5V impulsus po 0,02s, kurie suka variklį, po kurių eina 0,02s pauzė su 0V, kai variklis nesisuka. Kiekvienas impulsas suka variklį vieną dešimtąją apsisukimo, o tai reiškia, kad variklis per sekundę atlieka 2,5 apsisukimo. Naudodami skaitmeninį signalą pasiekėte, kad variklis suktųsi 2,5 apsisukimo per sekundę arba 150 [apsisukimų per minutę](https://wikipedia.org/wiki/Revolutions_per_minute) (ne standartinis sukimosi greičio matas).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Kai PWM signalas yra įjungtas pusę laiko ir išjungtas kitą pusę, tai vadinama [50% darbo ciklu](https://wikipedia.org/wiki/Duty_cycle). Darbo ciklai matuojami kaip procentas laiko, kai signalas yra įjungtas, palyginti su išjungtu.

![Impulsų pločio moduliacija: variklio sukimas 75 RPM](../../../../../translated_images/lt/pwm-motor-75rpm.a5e4c939934b6e14.webp)

Variklio greitį galite keisti keisdami impulsų dydį. Pavyzdžiui, su tuo pačiu varikliu galite išlaikyti tą patį ciklo laiką 0,04s, tačiau įjungimo impulsą sumažinti perpus iki 0,01s, o išjungimo impulsą padidinti iki 0,03s. Turite tą patį impulsų skaičių per sekundę (25), tačiau kiekvienas įjungimo impulsas yra perpus trumpesnis. Pusės ilgio impulsas suka variklį vieną dvidešimtąją apsisukimo, o esant 25 impulsams per sekundę variklis atliks 1,25 apsisukimo per sekundę arba 75 RPM. Keisdami skaitmeninio signalo impulsų greitį, perpus sumažinote analoginio variklio greitį.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Kaip užtikrintumėte sklandų variklio sukimosi judėjimą, ypač esant mažiems greičiams? Ar naudotumėte nedaug ilgų impulsų su ilgomis pauzėmis, ar daug labai trumpų impulsų su trumpomis pauzėmis?

> 💁 Kai kurie jutikliai taip pat naudoja PWM, kad konvertuotų analoginius signalus į skaitmeninius.

> 🎓 Daugiau apie impulsų pločio moduliaciją galite perskaityti [Wikipedia PWM puslapyje](https://wikipedia.org/wiki/Pulse-width_modulation).

### Skaitmeniniai aktuatoriai

Skaitmeniniai aktuatoriai, kaip ir skaitmeniniai jutikliai, turi dvi būsenas, kurias kontroliuoja aukšta arba žema įtampa, arba turi integruotą DAC, kuris gali konvertuoti skaitmeninį signalą į analoginį.

Vienas paprastas skaitmeninis aktuatorius yra LED. Kai įrenginys siunčia skaitmeninį signalą „1“, siunčiama aukšta įtampa, kuri įjungia LED. Kai siunčiamas skaitmeninis signalas „0“, įtampa sumažėja iki 0V, ir LED išsijungia.

![LED išjungtas esant 0 voltų ir įjungtas esant 5V](../../../../../translated_images/lt/led.ec6d94f66676a174.webp)

✅ Kokius kitus paprastus dviejų būsenų aktuatorius galite sugalvoti? Vienas pavyzdys yra solenoidas – elektromagnetas, kurį galima aktyvuoti, kad atliktų veiksmus, pavyzdžiui, perstumtų durų skląstį, užrakindamas/atrakindamas duris.

Sudėtingesni skaitmeniniai aktuatoriai, tokie kaip ekranai, reikalauja, kad skaitmeniniai duomenys būtų siunčiami tam tikrais formatais. Jie dažniausiai turi bibliotekas, kurios palengvina tinkamų duomenų siuntimą jų valdymui.

---

## 🚀 Iššūkis

Paskutinių dviejų pamokų iššūkis buvo išvardyti kuo daugiau IoT įrenginių, esančių jūsų namuose, mokykloje ar darbo vietoje, ir nuspręsti, ar jie sukurti aplink mikrovaldiklius, vieno plokštės kompiuterius ar net jų mišinį.

Kiekvienam išvardytam įrenginiui, kokie jutikliai ir aktuatoriai prie jų prijungti? Kokia kiekvieno jutiklio ir aktuatoriaus paskirtis, prijungta prie šių įrenginių?

## Po paskaitos testas

[Po paskaitos testas](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Apžvalga ir savarankiškas mokymasis

* Skaitykite apie elektrą ir grandines [ThingLearn](http://thinglearn.jenlooper.com/curriculum/).  
* Skaitykite apie skirtingus temperatūros jutiklių tipus [Seeed Studios temperatūros jutiklių vadove](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/).  
* Skaitykite apie LED [Wikipedia LED puslapyje](https://wikipedia.org/wiki/Light-emitting_diode).  

## Užduotis

[Tyrinėkite jutiklius ir aktuatorius](assignment.md)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.