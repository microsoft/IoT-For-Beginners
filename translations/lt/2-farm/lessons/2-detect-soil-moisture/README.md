C, tariamas *I-squared-C*, yra daugiavaldis, daugiaperiferinis protokolas, kuriame bet kuris prijungtas įrenginys gali veikti kaip valdiklis arba periferinis įrenginys, bendraujantis per I²C magistralę (taip vadinama duomenų perdavimo sistema). Duomenys siunčiami kaip adresuoti paketai, kuriuose kiekviename pakete yra prijungto įrenginio adresas, kuriam jie skirti.

> 💁 Šis modelis anksčiau buvo vadinamas "master/slave", tačiau šios terminologijos atsisakoma dėl jos sąsajų su vergove. [Atvirojo kodo aparatūros asociacija priėmė terminus valdiklis/periferinis įrenginys](https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/), tačiau vis dar galite rasti nuorodų į senąją terminologiją.

Įrenginiai turi adresą, kuris naudojamas prisijungiant prie I²C magistralės, ir paprastai jis yra užprogramuotas įrenginyje. Pavyzdžiui, kiekvienas Grove jutiklis iš Seeed turi tą patį adresą, todėl visi šviesos jutikliai turi tą patį adresą, visi mygtukai turi tą patį adresą, kuris skiriasi nuo šviesos jutiklio adreso. Kai kurie įrenginiai turi galimybę pakeisti adresą, keičiant džemperių nustatymus arba lituojant kontaktus.

I²C magistralė turi 2 pagrindinius laidus, kartu su 2 maitinimo laidais:

| Laidas | Pavadinimas | Aprašymas |
| ---- | --------- | ----------- |
| SDA | Serijiniai duomenys | Šis laidas skirtas duomenų siuntimui tarp įrenginių. |
| SCL | Serijinis laikrodis | Šis laidas siunčia laikrodžio signalą, kurio greitį nustato valdiklis. |
| VCC | Bendras įtampos kolektorius | Maitinimo šaltinis įrenginiams. Jis prijungtas prie SDA ir SCL laidų, kad suteiktų jų maitinimą per traukimo rezistorių, kuris išjungia signalą, kai nė vienas įrenginys nėra valdiklis. |
| GND | Įžeminimas | Užtikrina bendrą įžeminimą elektrinei grandinei. |

![I2C magistralė su 3 įrenginiais, prijungtais prie SDA ir SCL laidų, dalijantis bendru įžeminimo laidu](../../../../../translated_images/lt/i2c.83da845dde02256b.webp)

Norint siųsti duomenis, vienas įrenginys išduoda pradžios sąlygą, nurodydamas, kad yra pasiruošęs siųsti duomenis. Tada jis tampa valdikliu. Valdiklis siunčia įrenginio adresą, su kuriuo nori bendrauti, kartu su informacija, ar jis nori skaityti, ar rašyti duomenis. Po duomenų perdavimo valdiklis siunčia pabaigos sąlygą, nurodydamas, kad baigė. Po to kitas įrenginys gali tapti valdikliu ir siųsti arba gauti duomenis.

2<sup>C turi greičio apribojimus, su trimis skirtingais režimais, veikiančiais fiksuotais greičiais. Greičiausias yra didelio greičio režimas, kurio maksimalus greitis siekia 3,4 Mbps (megabitai per sekundę), nors labai nedaug įrenginių palaiko tokį greitį. Pavyzdžiui, „Raspberry Pi“ yra apribotas greituoju režimu, kurio greitis yra 400 Kbps (kilobitai per sekundę). Standartinis režimas veikia 100 Kbps greičiu.

> 💁 Jei naudojate „Raspberry Pi“ su „Grove Base“ plokšte kaip savo IoT įrenginį, ant plokštės matysite keletą I<sup>2</sup>C lizdų, kuriuos galite naudoti bendraujant su I<sup>2</sup>C jutikliais. Analoginiai „Grove“ jutikliai taip pat naudoja I<sup>2</sup>C su ADC, kad analogines reikšmes perduotų kaip skaitmeninius duomenis, todėl šviesos jutiklis, kurį naudojote, imitavo analoginį kontaktą, o reikšmė buvo perduodama per I<sup>2</sup>C, nes „Raspberry Pi“ palaiko tik skaitmeninius kontaktus.

### Universalus asinchroninis siųstuvas-imtuvas (UART)

UART apima fizinę grandinę, leidžiančią dviem įrenginiams bendrauti. Kiekvienas įrenginys turi 2 ryšio kontaktus – siuntimo (Tx) ir priėmimo (Rx), kur pirmojo įrenginio Tx kontaktas prijungtas prie antrojo įrenginio Rx kontakto, o antrojo įrenginio Tx kontaktas prijungtas prie pirmojo įrenginio Rx kontakto. Tai leidžia duomenis siųsti abiem kryptimis.

* Įrenginys 1 siunčia duomenis iš savo Tx kontakto, kuriuos gauna įrenginys 2 per savo Rx kontaktą
* Įrenginys 1 gauna duomenis per savo Rx kontaktą, kuriuos siunčia įrenginys 2 iš savo Tx kontakto

![UART su Tx kontaktu viename luste, prijungtu prie Rx kontakto kitame, ir atvirkščiai](../../../../../translated_images/lt/uart.d0dbd3fb9e3728c6.webp)

> 🎓 Duomenys siunčiami po vieną bitą, ir tai vadinama *nuosekliuoju* ryšiu. Dauguma operacinių sistemų ir mikrovaldiklių turi *nuosekliuosius prievadus*, tai yra jungtis, kurios gali siųsti ir priimti nuoseklius duomenis, prieinamus jūsų kodui.

UART įrenginiai turi [baudų dažnį](https://wikipedia.org/wiki/Symbol_rate) (dar vadinamą simbolių dažniu), kuris nurodo, kokiu greičiu duomenys bus siunčiami ir priimami bitais per sekundę. Dažnas baudų dažnis yra 9 600, tai reiškia, kad kiekvieną sekundę siunčiama 9 600 bitų (0 ir 1) duomenų.

UART naudoja pradžios ir pabaigos bitus – tai yra, jis siunčia pradžios bitą, nurodantį, kad ketina siųsti baitą (8 bitus) duomenų, o po to siunčia pabaigos bitą.

UART greitis priklauso nuo aparatinės įrangos, tačiau net ir greičiausios implementacijos neviršija 6,5 Mbps (megabitų per sekundę, arba milijonų bitų, 0 arba 1, siunčiamų per sekundę).

UART galima naudoti per GPIO kontaktus – galite nustatyti vieną kontaktą kaip Tx ir kitą kaip Rx, tada prijungti juos prie kito įrenginio.

> 💁 Jei naudojate „Raspberry Pi“ su „Grove Base“ plokšte kaip savo IoT įrenginį, ant plokštės matysite UART lizdą, kurį galite naudoti bendraujant su jutikliais, naudojančiais UART protokolą.

### Nuoseklus periferinis sąsaja (SPI)

SPI yra sukurta bendrauti per trumpus atstumus, pavyzdžiui, mikrovaldiklyje, norint bendrauti su saugojimo įrenginiais, tokiais kaip „flash“ atmintis. Ji pagrįsta valdiklio/periferijos modeliu, kai vienas valdiklis (dažniausiai IoT įrenginio procesorius) sąveikauja su keliais periferiniais įrenginiais. Valdiklis valdo viską, pasirinkdamas periferinį įrenginį ir siųsdamas arba prašydamas duomenų.

> 💁 Kaip ir I<sup>2</sup>C, terminai valdiklis ir periferija yra neseniai įvesti pakeitimai, todėl galite matyti vis dar naudojamus senesnius terminus.

SPI valdikliai naudoja 3 laidus kartu su 1 papildomu laidu kiekvienam periferiniam įrenginiui. Periferiniai įrenginiai naudoja 4 laidus. Šie laidai yra:

| Laidas | Pavadinimas | Aprašymas |
| ---- | --------- | ----------- |
| COPI | Valdiklio išvestis, periferijos įvestis | Šis laidas skirtas duomenims siųsti iš valdiklio į periferiją. |
| CIPO | Valdiklio įvestis, periferijos išvestis | Šis laidas skirtas duomenims siųsti iš periferijos į valdiklį. |
| SCLK | Nuoseklus laikrodis | Šis laidas siunčia laikrodžio signalą, kurio dažnį nustato valdiklis. |
| CS   | Lustų pasirinkimas | Valdiklis turi kelis laidus, po vieną kiekvienam periferiniam įrenginiui, ir kiekvienas laidas jungiasi prie atitinkamo periferinio įrenginio CS laido. |

![SPI su vienu valdikliu ir dviem periferiniais įrenginiais](../../../../../translated_images/lt/spi.297431d6f98b386b.webp)

CS laidas naudojamas aktyvuoti vieną periferinį įrenginį vienu metu, bendraujant per COPI ir CIPO laidus. Kai valdikliui reikia pakeisti periferinį įrenginį, jis išjungia CS laidą, prijungtą prie šiuo metu aktyvaus periferinio įrenginio, tada įjungia laidą, prijungtą prie kito periferinio įrenginio, su kuriuo nori bendrauti.

SPI yra *pilno duplekso*, tai reiškia, kad valdiklis gali siųsti ir priimti duomenis tuo pačiu metu iš to paties periferinio įrenginio, naudodamas COPI ir CIPO laidus. SPI naudoja laikrodžio signalą SCLK laide, kad įrenginiai būtų sinchronizuoti, todėl, skirtingai nei siunčiant tiesiogiai per UART, jam nereikia pradžios ir pabaigos bitų.

SPI neturi apibrėžtų greičio apribojimų, o implementacijos dažnai gali perduoti kelis megabaitus duomenų per sekundę.

IoT kūrėjų rinkiniai dažnai palaiko SPI per kai kuriuos GPIO kontaktus. Pavyzdžiui, „Raspberry Pi“ galite naudoti GPIO kontaktus 19, 21, 23, 24 ir 26 SPI.

### Belaidis ryšys

Kai kurie jutikliai gali bendrauti naudodami standartinius belaidžius protokolus, tokius kaip „Bluetooth“ (daugiausia „Bluetooth Low Energy“ arba BLE), „LoRaWAN“ (ilgo nuotolio mažos galios tinklo protokolas) arba „WiFi“. Tai leidžia nuotoliniams jutikliams nebūti fiziškai prijungtiems prie IoT įrenginio.

Vienas tokių pavyzdžių yra komerciniai dirvožemio drėgmės jutikliai. Jie matuoja dirvožemio drėgmę lauke, tada siunčia duomenis per „LoRaWAN“ į centrinį įrenginį, kuris apdoroja duomenis arba siunčia juos internetu. Tai leidžia jutikliui būti toli nuo IoT įrenginio, kuris valdo duomenis, sumažinant energijos suvartojimą ir poreikį dideliems „WiFi“ tinklams ar ilgiems kabeliams.

BLE yra populiarus pažangiems jutikliams, tokiems kaip ant riešo dėvimi fitneso sekimo įrenginiai. Šie įrenginiai sujungia kelis jutiklius ir siunčia jų duomenis į IoT įrenginį, pavyzdžiui, jūsų telefoną, naudodami BLE.

✅ Ar turite kokių nors „Bluetooth“ jutiklių savo asmenyje, namuose ar mokykloje? Tai gali būti temperatūros jutikliai, užimtumo jutikliai, įrenginių sekimo įrenginiai ir fitneso įrenginiai.

Vienas populiarių būdų komerciniams įrenginiams jungtis yra „Zigbee“. „Zigbee“ naudoja „WiFi“, kad sudarytų tinklų tinklą tarp įrenginių, kur kiekvienas įrenginys jungiasi su kuo daugiau netoliese esančių įrenginių, sudarydamas daugybę jungčių kaip voratinklis. Kai vienas įrenginys nori siųsti pranešimą internetu, jis gali siųsti jį artimiausiems įrenginiams, kurie tada perduoda jį kitiems netoliese esantiems įrenginiams ir taip toliau, kol jis pasiekia koordinatorių ir gali būti išsiųstas internetu.

> 🐝 Pavadinimas „Zigbee“ reiškia medaus bičių šokį, kurį jos atlieka grįžusios į avilį.

## Išmatuokite dirvožemio drėgmės lygį

Galite išmatuoti dirvožemio drėgmės lygį naudodami dirvožemio drėgmės jutiklį, IoT įrenginį ir kambarinį augalą arba netoliese esančią dirvožemio vietą.

### Užduotis - išmatuokite dirvožemio drėgmę

Atlikite atitinkamą vadovą, kad išmatuotumėte dirvožemio drėgmę naudodami savo IoT įrenginį:

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Vienos plokštės kompiuteris - Raspberry Pi](pi-soil-moisture.md)
* [Vienos plokštės kompiuteris - virtualus įrenginys](virtual-device-soil-moisture.md)

## Jutiklių kalibravimas

Jutikliai remiasi elektrinių savybių, tokių kaip varža ar talpa, matavimu.

> 🎓 Varža, matuojama omais (Ω), nurodo, kiek pasipriešinimo yra elektros srovei, keliaujančiai per medžiagą. Kai į medžiagą taikoma įtampa, srovės kiekis, praeinantis per ją, priklauso nuo medžiagos varžos. Daugiau apie tai galite perskaityti [elektrinės varžos puslapyje Vikipedijoje](https://wikipedia.org/wiki/Electrical_resistance_and_conductance).

> 🎓 Talpa, matuojama faradais (F), yra komponento ar grandinės gebėjimas kaupti ir saugoti elektros energiją. Daugiau apie tai galite perskaityti [talpos puslapyje Vikipedijoje](https://wikipedia.org/wiki/Capacitance).

Šie matavimai ne visada yra naudingi – įsivaizduokite temperatūros jutiklį, kuris pateikia matavimą 22,5 kΩ! Vietoj to, išmatuota reikšmė turi būti konvertuota į naudingą vienetą, kalibruojant – tai yra, suderinant išmatuotas reikšmes su matuojamu dydžiu, kad nauji matavimai galėtų būti konvertuoti į tinkamą vienetą.

Kai kurie jutikliai yra iš anksto kalibruoti. Pavyzdžiui, temperatūros jutiklis, kurį naudojote ankstesnėje pamokoje, jau buvo kalibruotas, kad galėtų pateikti temperatūros matavimą °C. Gamykloje pirmasis sukurtas jutiklis būtų veikiamas įvairiomis žinomomis temperatūromis, o varža būtų matuojama. Tai būtų naudojama kuriant skaičiavimą, kuris galėtų konvertuoti iš Ω (varžos vieneto) į °C.

> 💁 Formulė, skirta apskaičiuoti varžą pagal temperatūrą, vadinama [Steinhart–Hart lygtimi](https://wikipedia.org/wiki/Steinhart–Hart_equation).

### Dirvožemio drėgmės jutiklio kalibravimas

Dirvožemio drėgmė matuojama naudojant gravimetrinį arba tūrį matuojantį vandens kiekį.

* Gravimetrinis metodas matuoja vandens svorį viename dirvožemio svorio vienete, kaip kilogramų vandens kiekį vienam kilogramui sauso dirvožemio
* Tūrinis metodas matuoja vandens tūrį viename dirvožemio tūrio vienete, kaip kubinių metrų vandens kiekį vienam kubiniam metrui sauso dirvožemio

> 🇺🇸 Amerikiečiams, dėl vienetų nuoseklumo, šie matavimai gali būti atliekami svarais vietoj kilogramų arba kubiniais pėdomis vietoj kubinių metrų.

Dirvožemio drėgmės jutikliai matuoja elektrinę varžą arba talpą – tai ne tik priklauso nuo dirvožemio drėgmės, bet ir nuo dirvožemio tipo, nes dirvožemio sudedamosios dalys gali pakeisti jo elektrines savybes. Idealiu atveju jutikliai turėtų būti kalibruoti – tai yra, imant jutiklio rodmenis ir lyginant juos su matavimais, atliktais naudojant mokslinį metodą. Pavyzdžiui, laboratorija gali apskaičiuoti gravimetrinę dirvožemio drėgmę, naudodama konkretaus lauko mėginius, paimtus kelis kartus per metus, ir šie skaičiai gali būti naudojami jutiklio kalibravimui, suderinant jutiklio rodmenis su gravimetrine dirvožemio drėgme.

![Įtampa prieš dirvožemio drėgmės kiekį](../../../../../translated_images/lt/soil-moisture-to-voltage.df86d80cda158700.webp)

Aukščiau pateiktoje diagramoje parodyta, kaip kalibruoti jutiklį. Įtampa užfiksuojama dirvožemio mėginiui, kuris vėliau laboratorijoje matuojamas, lyginant drėgną svorį su sausu svoriu (matuojant svorį drėgną, tada džiovinant orkaitėje ir matuojant sausą). Kai keli matavimai yra atlikti, jie gali būti pavaizduoti diagramoje, o taškams pritaikyta linija. Ši linija gali būti naudojama konvertuoti dirvožemio drėgmės jutiklio rodmenis, gautus IoT įrenginiu, į faktinius dirvožemio drėgmės matavimus.

💁 Rezistyviniams dirvožemio drėgmės jutikliams įtampa didėja, kai dirvožemio drėgmė didėja. Kapacitiviniams dirvožemio drėgmės jutikliams įtampa mažėja, kai dirvožemio drėgmė didėja, todėl jų grafikai būtų nuolydžiai žemyn, o ne aukštyn.

![Dirvožemio drėgmės reikšmė, interpoliuota iš grafiko](../../../../../translated_images/lt/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.webp)

Aukščiau pateiktoje diagramoje parodytas dirvožemio drėgmės jutiklio įtampos rodmuo, ir sekant jį iki linijos diagramoje galima apskaičiuoti faktinę dirvožemio drėgmę.

Šis metodas reiškia, kad ūkininkui reikia tik kelių laboratorinių matavimų laukui, o tada jie gali naudoti IoT įrenginius dirvožemio drėgmei matuoti – tai žymiai pagreitina matavimų atlikimo laiką.

---

## 🚀 Iššūkis

Rezistyviniai ir kapacitiviniai dirvožemio drėgmės jutikliai turi keletą skirtumų. Kokie yra šie skirtumai ir kuris tipas (jei toks yra) yra geriausias ūkininkui? Ar atsakymas keičiasi tarp besivystančių ir išsivysčiusių šalių?

## Po paskaitos testas

[Po paskaitos testas](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Peržiūra ir savarankiškas mokymasis

Susipažinkite su aparatine įr

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.