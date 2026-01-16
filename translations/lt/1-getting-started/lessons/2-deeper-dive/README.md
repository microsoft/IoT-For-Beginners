<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9dd7f645ad1c6f20b72fee512987f772",
  "translation_date": "2025-08-28T19:51:12+00:00",
  "source_file": "1-getting-started/lessons/2-deeper-dive/README.md",
  "language_code": "lt"
}
-->
# Gilesnis IoT pažinimas

![Šios pamokos apžvalga piešinyje](../../../../../translated_images/lt/lesson-2.324b0580d620c25e0a24fb7fddfc0b29a846dd4b82c08e7a9466d580ee78ce51.jpg)

> Piešinys sukurtas [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

Ši pamoka buvo dėstoma kaip [Hello IoT serijos](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) dalis, organizuota [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Pamoka buvo suskirstyta į dvi dalis: 1 valandos trukmės pamoką ir 1 valandos konsultaciją, kurioje gilintasi į pamokos temas bei atsakyta į klausimus.

[![2 pamoka: Gilesnis IoT pažinimas](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![2 pamoka: Gilesnis IoT pažinimas - Konsultacija](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Spustelėkite paveikslėlius aukščiau, kad peržiūrėtumėte vaizdo įrašus

## Klausimynas prieš pamoką

[Klausimynas prieš pamoką](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Įvadas

Šioje pamokoje gilinamės į kai kurias temas, aptartas ankstesnėje pamokoje.

Šioje pamokoje aptarsime:

* [IoT programos komponentai](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Gilesnis mikrovaldiklių pažinimas](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Gilesnis vienos plokštės kompiuterių pažinimas](../../../../../1-getting-started/lessons/2-deeper-dive)

## IoT programos komponentai

IoT programą sudaro du pagrindiniai komponentai: *Internetas* ir *daiktas*. Pažvelkime į šiuos komponentus detaliau.

### Daiktas

![Raspberry Pi 4](../../../../../translated_images/lt/raspberry-pi-4.fd4590d308c3d456.webp)

**Daikto** dalis IoT reiškia įrenginį, kuris gali sąveikauti su fiziniu pasauliu. Šie įrenginiai paprastai yra maži, nebrangūs kompiuteriai, veikiantys lėtu greičiu ir naudojantys mažai energijos – pavyzdžiui, paprasti mikrovaldikliai su keliais kilobaitais RAM (palyginimui, asmeniniuose kompiuteriuose RAM matuojama gigabaitais), veikiantys tik kelių šimtų megahercų dažniu (palyginimui, asmeniniuose kompiuteriuose dažnis matuojamas gigahercais), tačiau sunaudojantys tiek mažai energijos, kad gali veikti savaites, mėnesius ar net metus su baterijomis.

Šie įrenginiai sąveikauja su fiziniu pasauliu, naudodami jutiklius duomenų rinkimui iš aplinkos arba valdiklius ir aktuatorius fiziniams pokyčiams atlikti. Tipiškas pavyzdys – išmanusis termostatas, turintis temperatūros jutiklį, priemonę norimai temperatūrai nustatyti, pvz., ratuką ar jutiklinį ekraną, ir jungtį su šildymo ar vėsinimo sistema, kurią galima įjungti, kai aptikta temperatūra yra už norimo diapazono ribų. Temperatūros jutiklis aptinka, kad kambarys yra per šaltas, ir aktuatorius įjungia šildymą.

![Diagrama, rodanti temperatūrą ir ratuką kaip IoT įrenginio įvestis, o šildytuvo valdymą kaip išvestį](../../../../../translated_images/lt/basic-thermostat.a923217fd1f37e5a6f3390396a65c22a387419ea2dd17e518ec24315ba6ae9a8.png)

Yra daugybė įvairių daiktų, kurie gali veikti kaip IoT įrenginiai – nuo specializuotos įrangos, kuri aptinka vieną dalyką, iki universalių įrenginių, net jūsų išmaniojo telefono! Išmanusis telefonas gali naudoti jutiklius, kad aptiktų aplinką, ir aktuatorius, kad sąveikautų su pasauliu – pavyzdžiui, naudodamas GPS jutiklį jūsų buvimo vietai nustatyti ir garsiakalbį navigacijos instrukcijoms pateikti.

✅ Pagalvokite apie kitus įrenginius aplink jus, kurie renka duomenis iš jutiklių ir naudoja juos sprendimams priimti. Vienas pavyzdys galėtų būti orkaitės termostatas. Ar galite rasti daugiau?

### Internetas

**Interneto** dalis IoT programoje apima programas, prie kurių IoT įrenginys gali prisijungti, kad siųstų ir gautų duomenis, taip pat kitas programas, kurios gali apdoroti duomenis iš IoT įrenginio ir padėti priimti sprendimus, kokias užklausas siųsti IoT įrenginio aktuatoriams.

Tipiška konfigūracija būtų debesų paslauga, prie kurios jungiasi IoT įrenginys. Ši paslauga tvarko tokius dalykus kaip saugumas, taip pat gauna pranešimus iš IoT įrenginio ir siunčia pranešimus atgal į įrenginį. Ši debesų paslauga jungiasi su kitomis programomis, kurios gali apdoroti ar saugoti jutiklių duomenis arba naudoti šiuos duomenis kartu su kitų sistemų duomenimis sprendimams priimti.

Įrenginiai ne visada jungiasi tiesiogiai prie interneto per WiFi ar laidinius ryšius. Kai kurie įrenginiai naudoja tinklo tinklą (mesh networking), kad bendrautų tarpusavyje per tokias technologijas kaip „Bluetooth“, jungdamiesi per centrinį įrenginį, turintį interneto ryšį.

Pavyzdžiui, išmanusis termostatas jungiasi prie debesų paslaugos per namų WiFi. Jis siunčia temperatūros duomenis į šią paslaugą, o iš ten jie įrašomi į duomenų bazę, leidžiančią namų savininkui peržiūrėti dabartinę ir praeities temperatūrą naudojant telefono programėlę. Kita debesų paslauga žino, kokios temperatūros nori savininkas, ir siunčia pranešimus atgal į IoT įrenginį per debesų paslaugą, kad įjungtų arba išjungtų šildymo sistemą.

![Diagrama, rodanti temperatūrą ir ratuką kaip IoT įrenginio įvestis, IoT įrenginį su dvikrypčiu ryšiu su debesimi, kuris savo ruožtu turi dvikryptį ryšį su telefonu, ir šildytuvo valdymą kaip išvestį iš IoT įrenginio](../../../../../translated_images/lt/mobile-controlled-thermostat.4a994010473d8d6a52ba68c67e5f02dc8928c717e93ca4b9bc55525aa75bbb60.png)

Dar išmanesnė versija galėtų naudoti dirbtinį intelektą debesyje, kartu su duomenimis iš kitų jutiklių, prijungtų prie kitų IoT įrenginių, pvz., judesio jutiklių, aptinkančių, kurie kambariai naudojami, taip pat duomenis apie orą ar net jūsų kalendorių, kad išmaniai nustatytų temperatūrą. Pavyzdžiui, ji galėtų išjungti šildymą, jei iš jūsų kalendoriaus matyti, kad esate atostogose, arba išjungti šildymą atskiruose kambariuose, priklausomai nuo to, kuriuos kambarius naudojate, mokydamasi iš duomenų, kad laikui bėgant taptų vis tikslesnė.

![Diagrama, rodanti kelis temperatūros jutiklius ir ratuką kaip IoT įrenginio įvestis, IoT įrenginį su dvikrypčiu ryšiu su debesimi, kuris savo ruožtu turi dvikryptį ryšį su telefonu, kalendoriumi ir orų paslauga, ir šildytuvo valdymą kaip išvestį iš IoT įrenginio](../../../../../translated_images/lt/smarter-thermostat.a75855f15d2d9e63.webp)

✅ Kokie kiti duomenys galėtų padėti padaryti interneto prijungtą termostatą išmanesnį?

### IoT krašte

Nors IoT reiškia „daiktų internetas“, šie įrenginiai nebūtinai turi jungtis prie interneto. Kai kuriais atvejais įrenginiai gali jungtis prie „krašto“ įrenginių – vartų įrenginių, veikiančių jūsų vietiniame tinkle, leidžiančių apdoroti duomenis be interneto ryšio. Tai gali būti greičiau, kai turite daug duomenų arba lėtą interneto ryšį, leidžia veikti neprisijungus, kai interneto ryšys neįmanomas, pvz., laive ar humanitarinės krizės metu, ir leidžia išlaikyti duomenų privatumą. Kai kurie įrenginiai turės apdorojimo kodą, sukurtą naudojant debesų įrankius, ir vykdys jį vietoje, kad surinktų ir reaguotų į duomenis be interneto ryšio.

Vienas pavyzdys – išmanieji namų įrenginiai, tokie kaip „Apple HomePod“, „Amazon Alexa“ ar „Google Home“, kurie klausosi jūsų balso naudodami debesyje apmokytus AI modelius, tačiau veikia vietoje įrenginyje. Šie įrenginiai „atsibunda“, kai ištariamas tam tikras žodis ar frazė, ir tik tada siunčia jūsų kalbą internetu apdorojimui. Įrenginys nustoja siųsti kalbą tinkamu momentu, pvz., kai aptinka pauzę jūsų kalboje. Viskas, ką sakote prieš pažadinant įrenginį su pažadinimo žodžiu, ir viskas, ką sakote po to, kai įrenginys nustoja klausytis, nebus siunčiama internetu paslaugos teikėjui, todėl išliks privatu.

✅ Pagalvokite apie kitus scenarijus, kur privatumas yra svarbus, todėl duomenų apdorojimas būtų geriau atliekamas krašte, o ne debesyje. Užuomina – pagalvokite apie IoT įrenginius su kameromis ar kitais vaizdo įrenginiais.

### IoT saugumas

Bet koks interneto ryšys reikalauja rimto dėmesio saugumui. Yra senas pokštas, kad „S IoT reiškia saugumą“ – tačiau IoT neturi „S“, kas reiškia, kad jis nėra saugus.

IoT įrenginiai jungiasi prie debesų paslaugos, todėl jų saugumas priklauso nuo šios paslaugos saugumo – jei jūsų debesų paslauga leidžia prisijungti bet kokiam įrenginiui, gali būti siunčiami kenkėjiški duomenys arba vykdomos virusų atakos. Tai gali turėti labai realių pasekmių, nes IoT įrenginiai sąveikauja ir valdo kitus įrenginius. Pavyzdžiui, [Stuxnet kirminas](https://wikipedia.org/wiki/Stuxnet) manipuliavo centrifugų vožtuvais, kad juos sugadintų. Taip pat įsilaužėliai pasinaudojo [prastu saugumu, kad pasiektų kūdikių stebėjimo įrenginius](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) ir kitus namų stebėjimo įrenginius.

> 💁 Kartais IoT įrenginiai ir krašto įrenginiai veikia tinkle, visiškai izoliuotame nuo interneto, kad duomenys išliktų privatūs ir saugūs. Tai vadinama [oro tarpu](https://wikipedia.org/wiki/Air_gap_(networking)).

## Gilesnis mikrovaldiklių pažinimas

Ankstesnėje pamokoje pristatėme mikrovaldiklius. Dabar pažvelkime į juos giliau.

### CPU

CPU yra mikrovaldiklio „smegenys“. Tai procesorius, kuris vykdo jūsų kodą ir gali siųsti bei gauti duomenis iš prijungtų įrenginių. CPU gali turėti vieną ar daugiau branduolių – iš esmės vieną ar daugiau procesorių, kurie gali dirbti kartu vykdant jūsų kodą.

CPU remiasi laikrodžiu, kuris tiksėdamas milijonus ar milijardus kartų per sekundę sinchronizuoja veiksmus, kuriuos CPU gali atlikti. Kiekvieno tiksėjimo metu CPU gali vykdyti programos instrukciją, pvz., gauti duomenis iš išorinio įrenginio arba atlikti matematinį skaičiavimą. Šis reguliarus ciklas leidžia užbaigti visus veiksmus prieš apdorojant kitą instrukciją.

Kuo greitesnis laikrodžio ciklas, tuo daugiau instrukcijų galima apdoroti per sekundę, todėl CPU veikia greičiau. CPU greitis matuojamas [hercais (Hz)](https://wikipedia.org/wiki/Hertz), standartiniu vienetu, kur 1 Hz reiškia vieną ciklą arba laikrodžio tiksėjimą per sekundę.

> 🎓 CPU greitis dažnai nurodomas MHz arba GHz. 1 MHz yra 1 milijonas Hz, 1 GHz yra 1 milijardas Hz.

> 💁 CPU vykdo programas naudodamas [gavimo-dekodavimo-vykdymo ciklą](https://wikipedia.org/wiki/Instruction_cycle). Kiekvieno laikrodžio tiksėjimo metu CPU gauna kitą instrukciją iš atminties, ją dekoduoja ir vykdo, pvz., naudodamas aritmetinį loginį įrenginį (ALU), kad sudėtų du skaičius. Kai kurios vykdymo operacijos užtrunka kelis tiksėjimus, todėl kitas ciklas prasidės tik po to, kai instrukcija bus užbaigta.

![Gavimo-dekodavimo-vykdymo ciklai, rodantys, kaip instrukcija gaunama iš RAM, dekoduojama ir vykdoma CPU](../../../../../translated_images/lt/fetch-decode-execute.2fd6f150f6280392807f4475382319abd0cee0b90058e1735444d6baa6f2078c.png)

Mikrovaldikliai turi daug mažesnį laikrodžio greitį nei stalinių ar nešiojamųjų kompiuterių procesoriai ar net dauguma išmaniųjų telefonų. Pavyzdžiui, Wio Terminal CPU veikia 120 MHz arba 120 000 000 ciklų per sekundę greičiu.

✅ Vidutinis asmeninis kompiuteris ar „Mac“ turi CPU su keliais branduoliais, veikiančiais kelių gigahercų greičiu, o tai reiškia, kad laikrodis tiksėja milijardus kartų per sekundę. Ištirkite savo kompiuterio laikrodžio greitį ir palyginkite, kiek kartų jis greitesnis už Wio Terminal.

Kiekvienas laikrodžio ciklas sunaudoja energiją ir generuoja šilumą. Kuo greitesni tiksėjimai, tuo daugiau energijos sunaudojama ir daugiau šilumos generuojama. Kompiuteriai turi aušinimo sistemas ir ventiliatorius šilumai pašalinti, be kurių jie per kelias sekundes perkaistų ir išsijungtų. Mikrovaldikliai dažnai neturi nei vieno, nei kito, nes jie veikia daug vėsiau ir todėl daug lėčiau. Kompiuteriai veikia iš elektros tinklo arba didelių baterijų kelias valandas, o mikrovaldikliai gali veikti dienas, mėnesius ar net metus su mažomis baterijomis. Mikrovaldikliai taip pat gali turėti branduolius, veikiančius skirtingais greičiais, pereinant prie lėtesnių mažos galios branduolių, kai CPU apkrova yra maža, kad sumažintų energijos suvartojimą.

> 💁 Kai kurie kompiuteriai ir „Mac“ taip pat pradeda naudoti tą patį greitų didelės galios branduolių ir lėtesnių mažos galios branduolių derinį, kad optimizuotų baterijos veikimo laiką arba greitį, priklausomai nuo vykdomos užduoties. Pavyzdžiui, naujausias „Apple“ M1 lustas gali perjungti 4 našumo branduolius ir 4 efektyvumo branduolius, kad optimizuotų baterijos veikimo laiką arba greitį.

✅ Šiek tiek pasidomėkite: Perskaitykite apie CPU [Wikipedia CPU straipsnyje](https://wikipedia.org/wiki/Central_processing_unit).

#### Užduotis

Ištirkite Wio Terminal.

Jei naudojate Wio Terminal šiose pamokose, pabandykite rasti CPU. Suraskite *Aparatinės į
🎓 Programos atmintis saugo jūsų kodą ir išlieka net tada, kai nėra elektros.
> 🎓 RAM naudojama programoms vykdyti ir išvaloma, kai nėra elektros tiekimo

Kaip ir su CPU, mikrovaldiklio atmintis yra daug mažesnė nei PC ar Mac kompiuteryje. Tipinis PC gali turėti 8 gigabaitus (GB) RAM, arba 8,000,000,000 baitų, kur kiekvienas baitas gali saugoti vieną raidę arba skaičių nuo 0 iki 255. Mikrovaldiklis paprastai turi tik kilobaitus (KB) RAM, kur kilobaitas yra 1,000 baitų. Aukščiau minėtas Wio terminalas turi 192KB RAM, arba 192,000 baitų – daugiau nei 40,000 kartų mažiau nei vidutinis PC!

Žemiau pateikta diagrama parodo santykinį dydžio skirtumą tarp 192KB ir 8GB – mažas taškas centre atspindi 192KB.

![Palyginimas tarp 192KB ir 8GB – daugiau nei 40,000 kartų didesnis](../../../../../translated_images/lt/ram-comparison.6beb73541b42ac6f.webp)

Programų saugykla taip pat yra mažesnė nei PC. Tipinis PC gali turėti 500GB kietąjį diską programų saugojimui, tuo tarpu mikrovaldiklis gali turėti tik kelis kilobaitus arba galbūt kelis megabaitus (MB) saugyklos (1MB yra 1,000KB, arba 1,000,000 baitų). Wio terminalas turi 4MB programų saugyklos.

✅ Atlikite nedidelį tyrimą: Kiek RAM ir saugyklos turi kompiuteris, kurį naudojate šiam tekstui skaityti? Kaip tai palyginama su mikrovaldikliu?

### Įvestis/Išvestis

Mikrovaldikliams reikia įvesties ir išvesties (I/O) jungčių, kad galėtų skaityti duomenis iš jutiklių ir siųsti valdymo signalus į aktuatorius. Jie paprastai turi keletą universalių įvesties/išvesties (GPIO) pinų. Šiuos pinus galima sukonfigūruoti programinėje įrangoje kaip įvestį (jie gauna signalą) arba išvestį (jie siunčia signalą).

🧠⬅️ Įvesties pinai naudojami reikšmėms skaityti iš jutiklių

🧠➡️ Išvesties pinai siunčia instrukcijas aktuatoriams

✅ Apie tai sužinosite daugiau kitoje pamokoje.

#### Užduotis

Ištirkite Wio Terminalą.

Jei naudojate Wio Terminalą šioms pamokoms, suraskite GPIO pinus. Suraskite *Pinout diagramą* [Wio Terminal produkto puslapyje](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), kad sužinotumėte, kurie pinai yra kurie. Wio Terminal komplekte yra lipdukas, kurį galite pritvirtinti ant nugarėlės su pinų numeriais, todėl pridėkite jį dabar, jei dar to nepadarėte.

### Fizinis dydis

Mikrovaldikliai paprastai yra maži, o mažiausias, [Freescale Kinetis KL03 MCU, yra pakankamai mažas, kad tilptų golfo kamuoliuko įdubime](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). Vien tik PC CPU gali būti 40mm x 40mm dydžio, ir tai neįskaitant aušintuvų ir ventiliatorių, reikalingų, kad CPU veiktų ilgiau nei kelias sekundes neperkaistant – tai yra žymiai didesnis nei visas mikrovaldiklis. Wio terminalo kūrėjų rinkinys su mikrovaldikliu, korpusu, ekranu ir įvairiomis jungtimis bei komponentais nėra daug didesnis nei plikas Intel i9 CPU, ir žymiai mažesnis nei CPU su aušintuvu ir ventiliatoriumi!

| Įrenginys                       | Dydis                 |
| ------------------------------- | --------------------- |
| Freescale Kinetis KL03          | 1.6mm x 2mm x 1mm     |
| Wio terminalas                  | 72mm x 57mm x 12mm    |
| Intel i9 CPU, aušintuvas ir ventiliatorius | 136mm x 145mm x 103mm |

### Karkasai ir operacinės sistemos

Dėl mažo greičio ir atminties dydžio mikrovaldikliai neveikia su operacine sistema (OS) tradicine prasme. Operacinė sistema, kuri leidžia veikti jūsų kompiuteriui (Windows, Linux ar macOS), reikalauja daug atminties ir apdorojimo galios, kad galėtų vykdyti užduotis, kurios mikrovaldikliui visiškai nereikalingos. Atminkite, kad mikrovaldikliai paprastai yra programuojami atlikti vieną ar kelias labai specifines užduotis, skirtingai nei bendros paskirties kompiuteris, kaip PC ar Mac, kuris turi palaikyti vartotojo sąsają, leisti muziką ar filmus, suteikti įrankius dokumentams ar kodui rašyti, žaisti žaidimus ar naršyti internete.

Norint programuoti mikrovaldiklį be OS, jums reikia tam tikrų įrankių, leidžiančių sukurti kodą taip, kad mikrovaldiklis galėtų jį vykdyti, naudojant API, kurie gali bendrauti su bet kokiais periferiniais įrenginiais. Kiekvienas mikrovaldiklis yra skirtingas, todėl gamintojai paprastai palaiko standartinius karkasus, kurie leidžia laikytis standartinio „recepto“, kad sukurtumėte savo kodą ir jis veiktų bet kuriame mikrovaldiklyje, palaikančiame tą karkasą.

Mikrovaldiklius galima programuoti naudojant OS – dažnai vadinamą realaus laiko operacine sistema (RTOS), nes jos yra sukurtos duomenų siuntimui į periferinius įrenginius ir gavimui iš jų realiuoju laiku. Šios operacinės sistemos yra labai lengvos ir suteikia tokias funkcijas kaip:

* Daugiasriegis veikimas, leidžiantis jūsų kodui vykdyti daugiau nei vieną kodo bloką vienu metu, arba keliuose branduoliuose, arba paeiliui viename branduolyje
* Tinklo funkcijos, leidžiančios saugiai bendrauti internetu
* Grafinės vartotojo sąsajos (GUI) komponentai, skirti kurti vartotojo sąsajas (UI) įrenginiuose su ekranais.

✅ Pasidomėkite skirtingomis RTOS: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Arduino logotipas](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) tikriausiai yra populiariausias mikrovaldiklių karkasas, ypač tarp studentų, entuziastų ir kūrėjų. Arduino yra atvirojo kodo elektronikos platforma, apjungianti programinę ir techninę įrangą. Galite įsigyti Arduino suderinamas plokštes iš pačių Arduino arba kitų gamintojų, tada programuoti naudodami Arduino karkasą.

Arduino plokštės programuojamos C arba C++ kalbomis. Naudojant C/C++ jūsų kodas gali būti kompiliuojamas labai mažas ir veikti greitai, kas yra būtina ribotų išteklių įrenginyje, kaip mikrovaldiklis. Arduino programos pagrindas vadinamas eskizu ir yra C/C++ kodas su 2 funkcijomis – `setup` ir `loop`. Kai plokštė įsijungia, Arduino karkaso kodas vieną kartą vykdo `setup` funkciją, o tada nuolat vykdo `loop` funkciją, kol įrenginys išjungiamas.

`Setup` funkcijoje rašytumėte pradinį kodą, pvz., prisijungimą prie WiFi ir debesų paslaugų arba pinų inicializavimą įvesties ir išvesties funkcijoms. `Loop` funkcijoje būtų apdorojimo kodas, pvz., jutiklio reikšmės skaitymas ir siuntimas į debesį. Paprastai pridėtumėte uždelsimą kiekvieno ciklo pabaigoje, pavyzdžiui, jei norite, kad jutiklio duomenys būtų siunčiami kas 10 sekundžių, pridėtumėte 10 sekundžių uždelsimą ciklo pabaigoje, kad mikrovaldiklis galėtų miegoti, taupydamas energiją, ir vėl vykdytų ciklą po 10 sekundžių.

![Arduino eskizas, pirmiausia vykdantis setup, tada nuolat vykdantis loop](../../../../../translated_images/lt/arduino-sketch.79590cb837ff7a7c6a68d1afda6cab83fd53d3bb1bd9a8bf2eaf8d693a4d3ea6.png)

✅ Ši programos architektūra vadinama *įvykių ciklu* arba *pranešimų ciklu*. Daugelis programų naudoja šį modelį, ir tai yra standartas daugumai darbalaukio programų, veikiančių OS, kaip Windows, macOS ar Linux. `Loop` stebi pranešimus iš vartotojo sąsajos komponentų, pvz., mygtukų, arba įrenginių, kaip klaviatūra, ir į juos reaguoja. Daugiau galite perskaityti šiame [straipsnyje apie įvykių ciklą](https://wikipedia.org/wiki/Event_loop).

Arduino teikia standartines bibliotekas mikrovaldiklių ir I/O pinų valdymui, su skirtingomis įgyvendinimo detalėmis, kad veiktų skirtinguose mikrovaldikliuose. Pavyzdžiui, [`delay` funkcija](https://www.arduino.cc/reference/en/language/functions/time/delay/) sustabdys programą tam tikram laikotarpiui, [`digitalRead` funkcija](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) skaitys `HIGH` arba `LOW` reikšmę iš nurodyto pino, nepriklausomai nuo to, kurioje plokštėje kodas vykdomas. Šios standartinės bibliotekos reiškia, kad Arduino kodas, parašytas vienai plokštei, gali būti perkompiliuotas kitai Arduino plokštei ir veiks, jei pinai yra tie patys ir plokštės palaiko tas pačias funkcijas.

Yra didelė trečiųjų šalių Arduino bibliotekų ekosistema, leidžianti pridėti papildomų funkcijų prie jūsų Arduino projektų, pvz., naudoti jutiklius ir aktuatorius arba prisijungti prie debesų IoT paslaugų.

##### Užduotis

Ištirkite Wio Terminalą.

Jei naudojate Wio Terminalą šioms pamokoms, perskaitykite kodą, kurį parašėte paskutinėje pamokoje. Suraskite `setup` ir `loop` funkcijas. Stebėkite serijinį išvestį, kad pamatytumėte, kaip `loop` funkcija yra nuolat kviečiama. Pabandykite pridėti kodą į `setup` funkciją, kad rašytumėte į serijinį prievadą, ir stebėkite, kad šis kodas yra kviečiamas tik vieną kartą kiekvieną kartą, kai įrenginys paleidžiamas iš naujo. Pabandykite iš naujo paleisti įrenginį naudodami šoninį maitinimo jungiklį, kad parodytumėte, jog šis kodas kviečiamas kiekvieną kartą, kai įrenginys paleidžiamas iš naujo.

## Gilesnis žvilgsnis į vienos plokštės kompiuterius

Paskutinėje pamokoje pristatėme vienos plokštės kompiuterius. Dabar pažvelkime į juos giliau.

### Raspberry Pi

![Raspberry Pi logotipas](../../../../../translated_images/lt/raspberry-pi-logo.4efaa16605cee054.webp)

[Raspberry Pi Foundation](https://www.raspberrypi.org) yra JK labdaros organizacija, įkurta 2009 m., siekiant skatinti kompiuterių mokslo studijas, ypač mokyklose. Kaip šios misijos dalį, jie sukūrė vienos plokštės kompiuterį, vadinamą Raspberry Pi. Raspberry Pi šiuo metu yra prieinami 3 variantais – pilno dydžio versija, mažesnė Pi Zero ir kompiuterio modulis, kurį galima integruoti į galutinį IoT įrenginį.

![Raspberry Pi 4](../../../../../translated_images/lt/raspberry-pi-4.fd4590d308c3d456.webp)

Naujausia pilno dydžio Raspberry Pi versija yra Raspberry Pi 4B. Ji turi keturių branduolių (4 branduoliai) CPU, veikiantį 1.5GHz dažniu, 2, 4 arba 8GB RAM, gigabitinį Ethernet, WiFi, 2 HDMI prievadus, palaikančius 4k ekranus, garso ir kompozitinio vaizdo išvesties prievadą, USB prievadus (2 USB 2.0, 2 USB 3.0), 40 GPIO pinų, kameros jungtį Raspberry Pi kameros moduliui ir SD kortelės lizdą. Visa tai ant plokštės, kurios dydis yra 88mm x 58mm x 19.5mm, ir kurią maitina 3A USB-C maitinimo šaltinis. Šios plokštės kainuoja nuo 35 JAV dolerių, žymiai pigiau nei PC ar Mac.

> 💁 Taip pat yra Pi400 – viskas viename kompiuteris su Pi4, integruotu į klaviatūrą.

![Raspberry Pi Zero](../../../../../translated_images/lt/raspberry-pi-zero.f7a4133e1e7d54bb.webp)

Pi Zero yra daug mažesnis ir mažiau galingas. Jis turi vieno branduolio 1GHz CPU, 512MB RAM, WiFi (Zero W modelyje), vieną HDMI prievadą, mikro-USB prievadą, 40 GPIO pinų, kameros jungtį Raspberry Pi kameros moduliui ir SD kortelės lizdą. Jo matmenys yra 65mm x 30mm x 5mm, ir jis sunaudoja labai mažai energijos. Zero kainuoja 5 JAV dolerius, o W versija su WiFi – 10 JAV dolerių.

> 🎓 Abiejų šių įrenginių CPU yra ARM procesoriai, skirtingai nei Intel/AMD x86 ar x64 procesoriai, kuriuos rasite daugumoje PC ir Mac kompiuterių. Jie yra panašūs į procesorius, kuriuos rasite kai kuriuose mikrovaldikliuose, taip pat beveik visuose mobiliuosiuose telefonuose, Microsoft Surface X ir naujuose Apple Silicon pagrindu veikiančiuose Apple Mac kompiuteriuose.

Visi Raspberry Pi variantai veikia su Debian Linux versija, vadinama Raspberry Pi OS. Ji yra prieinama kaip lengvoji versija be darbalaukio, kuri puikiai tinka „be galvos“ projektams, kur nereikia ekrano, arba pilna versija su pilna darbalaukio aplinka, įskaitant interneto naršyklę, biuro programas, kodavimo įrankius ir žaidimus. Kadangi OS yra Debian Linux versija, galite įdiegti bet kokią programą ar įrankį, kuris veikia Debian ir yra sukurtas ARM procesoriui, esančiam Pi.

#### Užduotis

Ištirkite Raspberry Pi.

Jei naudojate Raspberry Pi šioms pamokoms, perskaitykite apie skirtingus plokštės komponentus.

* Galite rasti informacijos apie procesorius [Raspberry Pi techninės įrangos dokumentacijos puslapyje](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Perskaitykite apie procesorių, naudojamą jūsų Pi.
* Suraskite GPIO pinus. Daugiau apie juos skaitykite [Raspberry Pi GPIO dokumentacijoje](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Naudokite [GPIO Pin Usage guide](https://www.raspberrypi.org/documentation/usage/gpio/README.md), kad identifikuotumėte skirtingus savo Pi pinus.

### Vienos plokštės kompiuterių programavimas

Vienos plokštės kompiuteriai yra pilnaverčiai kompiuteriai, veikiantys su pilna OS. Tai reiškia, kad yra platus programavimo kalbų, karkasų ir įrankių pasirinkimas, kuriuos galite naudoti jiems programuoti, skirtingai nei mikrovaldikliai, kurie priklauso nuo plokštės palaikymo tokiuose karkasuose kaip Arduino. Dauguma programavimo kalbų turi bibliotekas, leidžiančias pasiekti GPIO pinus, kad būtų galima siųsti ir gauti duomenis iš jutiklių ir aktuatorių.

✅ Kokias programavimo kalbas mokate? Ar jos palaikomos Linux?

Dažniausia programavimo kalba, naudojama IoT programoms kurti Raspberry Pi, yra Python. Yra didžiulė aparatūros ekosistema, sukurta Pi, ir beveik visa ši aparatūra turi atitinkamą kodą, reikalingą jai naudoti kaip Python bibliotekoms.
### Vieno plokštės kompiuterių naudojimas profesionaliuose IoT diegimuose

Vieno plokštės kompiuteriai naudojami ne tik kaip kūrėjų rinkiniai, bet ir profesionaliuose IoT diegimuose. Jie gali būti galinga priemonė aparatūrai valdyti ir sudėtingoms užduotims, tokioms kaip mašininio mokymosi modelių vykdymas, atlikti. Pavyzdžiui, yra [Raspberry Pi 4 Compute Module](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/), kuris suteikia visą Raspberry Pi 4 galią, tačiau kompaktiškesnėje ir pigesnėje formoje, be daugumos jungčių, skirtas montuoti į pritaikytą aparatūrą.

---

## 🚀 Iššūkis

Paskutinės pamokos iššūkis buvo išvardinti kuo daugiau IoT įrenginių, esančių jūsų namuose, mokykloje ar darbo vietoje. Kiekvienam įrenginiui iš šio sąrašo pagalvokite, ar jie sukurti naudojant mikrovaldiklius, vieno plokštės kompiuterius, ar net abiejų derinį?

## Klausimynas po paskaitos

[Klausimynas po paskaitos](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Peržiūra ir savarankiškas mokymasis

* Perskaitykite [Arduino pradžios vadovą](https://www.arduino.cc/en/Guide/Introduction), kad geriau suprastumėte Arduino platformą.
* Perskaitykite [įvadą į Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/), kad sužinotumėte daugiau apie Raspberry Pi.
* Sužinokite daugiau apie kai kurias sąvokas ir akronimus straipsnyje [Kas yra CPU, MPU, MCU ir GPU?](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/) Elektroninės inžinerijos žurnale.

✅ Naudokitės šiais vadovais kartu su kainomis, pateiktomis sekant nuorodas [aparatinės įrangos vadove](../../../hardware.md), kad nuspręstumėte, kokią aparatinės įrangos platformą norite naudoti, arba ar verčiau naudotumėte virtualų įrenginį.

## Užduotis

[Palyginkite ir kontrastuokite mikrovaldiklius ir vieno plokštės kompiuterius](assignment.md)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.