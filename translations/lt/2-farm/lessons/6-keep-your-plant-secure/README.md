# Saugokite savo augalą

![Šios pamokos eskizų užrašų apžvalga](../../../../../translated_images/lt/lesson-10.829c86b80b9403bb.webp)

> Eskizų užrašai: [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

## Klausimynas prieš paskaitą

[Klausimynas prieš paskaitą](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Įvadas

Paskutinėse pamokose sukūrėte dirvožemio stebėjimo IoT įrenginį ir prijungėte jį prie debesijos. Bet kas, jei įsilaužėliai, dirbantys konkurento ūkininko naudai, perimtų jūsų IoT įrenginių kontrolę? Kas, jei jie siųstų neteisingus dirvožemio drėgmės rodmenis, kad jūsų augalai niekada nebūtų laistomi, arba įjungtų laistymo sistemą, kad ji veiktų nuolat, taip perlaistydami augalus ir sukeldami dideles vandens sąnaudas?

Šioje pamokoje sužinosite, kaip apsaugoti IoT įrenginius. Kadangi tai yra paskutinė šio projekto pamoka, taip pat sužinosite, kaip išvalyti debesijos išteklius, kad sumažintumėte galimas išlaidas.

Šioje pamokoje aptarsime:

* [Kodėl reikia apsaugoti IoT įrenginius?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Kriptografija](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Kaip apsaugoti savo IoT įrenginius](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Kaip sugeneruoti ir naudoti X.509 sertifikatą](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 Tai yra paskutinė šio projekto pamoka, todėl, baigę šią pamoką ir užduotį, nepamirškite išvalyti savo debesijos paslaugų. Jums reikės šių paslaugų užduočiai atlikti, todėl įsitikinkite, kad pirmiausia ją užbaigėte.
>
> Jei reikia, vadovaukitės [projekto išvalymo vadovu](../../../clean-up.md), kad gautumėte instrukcijas, kaip tai padaryti.

## Kodėl reikia apsaugoti IoT įrenginius?

IoT saugumas reiškia užtikrinimą, kad tik numatyti įrenginiai galėtų prisijungti prie jūsų debesijos IoT paslaugos ir siųsti jai telemetriją, o tik jūsų debesijos paslauga galėtų siųsti komandas jūsų įrenginiams. IoT duomenys taip pat gali būti asmeniniai, įskaitant medicininius ar intymius duomenis, todėl visa jūsų programa turi atsižvelgti į saugumą, kad šie duomenys nebūtų nutekinti.

Jei jūsų IoT programa nėra saugi, kyla daugybė rizikų:

* Netikras įrenginys galėtų siųsti neteisingus duomenis, dėl kurių jūsų programa reaguotų netinkamai. Pavyzdžiui, jie galėtų siųsti nuolat aukštus dirvožemio drėgmės rodmenis, todėl jūsų laistymo sistema niekada neįsijungtų, o augalai išdžiūtų.
* Neįgalioti vartotojai galėtų skaityti IoT įrenginių duomenis, įskaitant asmeninius ar verslui svarbius duomenis.
* Įsilaužėliai galėtų siųsti komandas, kad valdyti įrenginį taip, jog tai galėtų sugadinti įrenginį ar prijungtą aparatūrą.
* Prisijungę prie IoT įrenginio, įsilaužėliai galėtų naudoti tai kaip priemonę patekti į kitus tinklus ir gauti prieigą prie privačių sistemų.
* Piktavališki vartotojai galėtų pasiekti asmeninius duomenis ir naudoti juos šantažui.

Tai yra realūs scenarijai, kurie vyksta nuolat. Kai kurie pavyzdžiai buvo pateikti ankstesnėse pamokose, tačiau čia yra dar keletas:

* 2018 m. įsilaužėliai pasinaudojo atviru WiFi prieigos tašku žuvų bako termostate, kad gautų prieigą prie kazino tinklo ir pavogtų duomenis. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* 2016 m. Mirai Botnet surengė paslaugų trikdymo ataką prieš Dyn, interneto paslaugų teikėją, išjungdamas didelę dalį interneto. Šis botnetas naudojo kenkėjišką programinę įrangą, kad prisijungtų prie IoT įrenginių, tokių kaip DVR ir kameros, kurios naudojo numatytuosius vartotojo vardus ir slaptažodžius, ir iš ten pradėjo ataką. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys turėjo viešai prieinamą duomenų bazę su jų CloudPets prijungtų žaislų vartotojų duomenimis. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava pažymėjo bėgikus, kuriuos pralenkėte, ir parodė jų maršrutus, leisdama nepažįstamiems žmonėms efektyviai pamatyti, kur gyvenate. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Atlikite tyrimą: Ieškokite daugiau IoT įsilaužimų ir duomenų pažeidimų pavyzdžių, ypač susijusių su asmeniniais daiktais, tokiais kaip interneto prijungti dantų šepetėliai ar svarstyklės. Pagalvokite apie šių įsilaužimų poveikį aukoms ar klientams.

> 💁 Saugumas yra labai plati tema, ir ši pamoka apims tik pagrindus, susijusius su jūsų įrenginio prijungimu prie debesijos. Kitos temos, kurios nebus aptartos, apima duomenų pokyčių stebėjimą perdavimo metu, tiesioginį įrenginių įsilaužimą ar įrenginių konfigūracijų keitimą. IoT įsilaužimai yra tokia grėsmė, kad buvo sukurtos tokios priemonės kaip [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn). Šios priemonės yra panašios į antivirusines ir saugumo priemones, kurias galite turėti savo kompiuteryje, tačiau jos skirtos mažiems, mažos galios IoT įrenginiams.

## Kriptografija

Kai įrenginys jungiasi prie IoT paslaugos, jis naudoja ID, kad save identifikuotų. Problema ta, kad šį ID galima nukopijuoti – įsilaužėlis galėtų nustatyti kenkėjišką įrenginį, kuris naudoja tą patį ID kaip ir tikras įrenginys, bet siunčia neteisingus duomenis.

![Tiek tikri, tiek kenkėjiški įrenginiai gali naudoti tą patį ID, kad siųstų telemetriją](../../../../../translated_images/lt/iot-device-and-hacked-device-connecting.e0671675df74d6d9.webp)

Sprendimas yra paversti siunčiamus duomenis užkoduotu formatu, naudojant tam tikrą vertę, žinomą tik įrenginiui ir debesijai. Šis procesas vadinamas *šifravimu*, o vertė, naudojama duomenims užšifruoti, vadinama *šifravimo raktu*.

![Jei naudojamas šifravimas, priimami tik užšifruoti pranešimai, kiti atmetami](../../../../../translated_images/lt/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f.webp)

Debesijos paslauga gali tada konvertuoti duomenis atgal į skaitomą formatą, naudodama procesą, vadinamą *iššifravimu*, naudodama tą patį šifravimo raktą arba *iššifravimo raktą*. Jei užšifruoto pranešimo negalima iššifruoti naudojant raktą, įrenginys buvo nulaužtas, ir pranešimas atmetamas.

Ši technika, naudojama šifravimui ir iššifravimui, vadinama *kriptografija*. 

### Ankstyvoji kriptografija

Ankstyviausi kriptografijos tipai buvo pakeitimo šifrai, kurie atsirado prieš 3 500 metų. Pakeitimo šifrai apima vienos raidės pakeitimą kita. Pavyzdžiui, [Cezario šifras](https://wikipedia.org/wiki/Caesar_cipher) apima abėcėlės perstūmimą tam tikru kiekiu, kurį žino tik užšifruoto pranešimo siuntėjas ir numatytas gavėjas.

[Viženerio šifras](https://wikipedia.org/wiki/Vigenère_cipher) šį procesą patobulino, naudodamas žodžius tekstui užšifruoti, kad kiekviena originalaus teksto raidė būtų perstumta skirtingu kiekiu, o ne visada tuo pačiu raidžių skaičiumi.

Kriptografija buvo naudojama įvairiems tikslams, pavyzdžiui, apsaugoti puodžių glazūros receptą senovės Mesopotamijoje, rašyti slaptus meilės laiškus Indijoje ar laikyti senovės Egipto magiškus burtus paslaptyje.

### Šiuolaikinė kriptografija

Šiuolaikinė kriptografija yra daug pažangesnė, todėl ją sunkiau nulaužti nei ankstyvuosius metodus. Šiuolaikinė kriptografija naudoja sudėtingą matematiką duomenims užšifruoti, turėdama per daug galimų raktų, kad būtų įmanoma brutali jėgos ataka.

Kriptografija naudojama įvairiais būdais saugiam bendravimui. Jei skaitote šį puslapį GitHub, galite pastebėti, kad svetainės adresas prasideda *HTTPS*, o tai reiškia, kad ryšys tarp jūsų naršyklės ir GitHub serverių yra užšifruotas. Jei kas nors galėtų skaityti interneto srautą tarp jūsų naršyklės ir GitHub, jie negalėtų perskaityti duomenų, nes jie yra užšifruoti. Jūsų kompiuteris netgi gali užšifruoti visus duomenis kietajame diske, kad, jei kas nors jį pavogtų, jie negalėtų perskaityti jūsų duomenų be slaptažodžio.

> 🎓 HTTPS reiškia HyperText Transfer Protocol **Secure**

Deja, ne viskas yra saugu. Kai kurie įrenginiai neturi jokio saugumo, kiti yra apsaugoti lengvai nulaužiamais raktais arba kartais net visi to paties tipo įrenginiai naudoja tą patį raktą. Yra buvę atvejų, kai labai asmeniniai IoT įrenginiai turėjo tą patį slaptažodį prisijungimui per WiFi ar „Bluetooth“. Jei galite prisijungti prie savo įrenginio, galite prisijungti ir prie kito žmogaus įrenginio. Prisijungę galėtumėte pasiekti labai privačius duomenis arba valdyti jų įrenginį.

> 💁 Nepaisant šiuolaikinės kriptografijos sudėtingumo ir teiginių, kad šifravimo nulaužimas gali užtrukti milijardus metų, kvantinės kompiuterijos atsiradimas sukėlė galimybę nulaužti visus žinomus šifravimus per labai trumpą laiką!

### Simetriniai ir asimetriniai raktai

Šifravimas yra dviejų tipų – simetrinis ir asimetrinis.

**Simetrinis** šifravimas naudoja tą patį raktą duomenims užšifruoti ir iššifruoti. Tiek siuntėjas, tiek gavėjas turi žinoti tą patį raktą. Tai yra mažiausiai saugus tipas, nes raktą reikia kažkaip perduoti. Kad siuntėjas galėtų išsiųsti užšifruotą pranešimą gavėjui, siuntėjas pirmiausia gali turėti perduoti gavėjui raktą.

![Simetrinis raktas naudoja tą patį raktą pranešimui užšifruoti ir iššifruoti](../../../../../translated_images/lt/send-message-symmetric-key.a2e8ad0d495896ff.webp)

Jei raktas pavogiamas perdavimo metu arba siuntėjas ar gavėjas yra nulaužti ir raktas randamas, šifravimas gali būti nulaužtas.

![Simetrinis raktas yra saugus tik tuo atveju, jei įsilaužėlis negauna rakto – jei taip, jie gali perimti ir iššifruoti pranešimą](../../../../../translated_images/lt/send-message-symmetric-key-hacker.e7cb53db1707adfb.webp)

**Asimetrinis** šifravimas naudoja 2 raktus – šifravimo raktą ir iššifravimo raktą, vadinamus viešojo/privačiojo rakto pora. Viešasis raktas naudojamas pranešimui užšifruoti, tačiau negali būti naudojamas jo iššifruoti, o privatusis raktas naudojamas pranešimui iššifruoti, tačiau negali būti naudojamas jo užšifruoti.

![Asimetrinis šifravimas naudoja skirtingus raktus pranešimui užšifruoti ir iššifruoti. Šifravimo raktas siunčiamas bet kokiems pranešimų siuntėjams, kad jie galėtų užšifruoti pranešimą prieš jį išsiųsdami gavėjui, kuris turi raktus](../../../../../translated_images/lt/send-message-asymmetric.7abe327c62615b8c.webp)

Gavėjas dalijasi savo viešuoju raktu, o siuntėjas naudoja jį pranešimui užšifruoti. Kai pranešimas išsiunčiamas, gavėjas jį iššifruoja naudodamas savo privatųjį raktą. Asimetrinis šifravimas yra saugesnis, nes privatusis raktas yra laikomas privačiai gavėjo ir niekada nėra dalijamasi. Viešasis raktas gali būti prieinamas visiems, nes jis gali būti naudojamas tik pranešimams užšifruoti.

Simetrinis šifravimas yra greitesnis nei asimetrinis, tačiau asimetrinis yra saugesnis. Kai kurios sistemos naudoja abu – asimetrinį šifravimą, kad užšifruotų ir perduotų simetrinį raktą, o tada simetrinį raktą naudoja visiems duomenims užšifruoti. Tai leidžia saugiau perduoti simetrinį raktą tarp siuntėjo ir gavėjo bei greičiau užšifruoti ir iššifruoti duomenis.

## Kaip apsaugoti savo IoT įrenginius

IoT įrenginiai gali būti apsaugoti naudojant simetrinį arba asimetrinį šifravimą. Simetrinis yra paprastesnis, tačiau mažiau saugus.

### Simetriniai raktai

Kai nustatėte savo IoT įrenginį, kad jis sąveikautų su IoT Hub, naudojote prisijungimo eilutę. Pavyzdinė prisijungimo eilutė yra:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Ši prisijungimo eilutė susideda iš trijų dalių, atskirtų kabliataškiais, kur kiekviena dalis yra raktas ir reikšmė:

| Raktas | Reikšmė | Aprašymas |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | IoT Hub URL adresas |
| DeviceId | `soil-moisture-sensor` | Unikalus įrenginio ID |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | Simetrinis raktas, žinomas įrenginiui ir IoT Hub |

Paskutinė šios prisijungimo eilutės dalis, `SharedAccessKey`, yra sim
💁 Dėl galiojimo laiko jūsų IoT įrenginys turi žinoti tikslų laiką, kuris paprastai gaunamas iš [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) serverio. Jei laikas nėra tikslus, ryšys nepavyks.
Po prisijungimo visi duomenys, siunčiami į IoT Hub iš įrenginio arba iš IoT Hub į įrenginį, bus užšifruoti naudojant bendrą prieigos raktą.

✅ Ką manote, kas nutiks, jei keli įrenginiai naudos tą pačią prisijungimo eilutę?

> 💁 Bloga saugumo praktika yra saugoti šį raktą kode. Jei įsilaužėlis gauna jūsų šaltinio kodą, jis gali gauti ir jūsų raktą. Be to, tai apsunkina kodo išleidimą, nes kiekvienam įrenginiui reikėtų perkompiliuoti kodą su atnaujintu raktu. Geriau šį raktą įkelti iš aparatinės saugumo modulio – lusto IoT įrenginyje, kuris saugo užšifruotas reikšmes, kurias gali perskaityti jūsų kodas.
>
> Mokantis IoT dažnai lengviau įdėti raktą į kodą, kaip tai darėte ankstesnėje pamokoje, tačiau turite užtikrinti, kad šis raktas nebūtų patalpintas viešame šaltinio kodo valdyme.

Įrenginiai turi 2 raktus ir 2 atitinkamas prisijungimo eilutes. Tai leidžia keisti raktus – pereiti nuo vieno rakto prie kito, jei pirmasis yra pažeistas, ir sugeneruoti naują pirmąjį raktą.

### X.509 sertifikatai

Kai naudojate asimetrinį šifravimą su viešojo/privačiojo rakto pora, turite pateikti savo viešąjį raktą visiems, kurie nori jums siųsti duomenis. Problema yra ta, kaip gavėjas gali būti tikras, kad tai tikrai jūsų viešasis raktas, o ne kažkas apsimetantis jumis? Vietoj rakto galite pateikti savo viešąjį raktą sertifikate, kurį patvirtino patikima trečioji šalis, vadinama X.509 sertifikatu.

X.509 sertifikatai yra skaitmeniniai dokumentai, kuriuose yra viešojo/privačiojo rakto poros viešasis raktas. Juos paprastai išduoda viena iš daugelio patikimų organizacijų, vadinamų [Sertifikavimo institucijomis](https://wikipedia.org/wiki/Certificate_authority) (CAs), ir jie yra skaitmeniniu būdu pasirašyti CA, kad būtų nurodyta, jog raktas yra galiojantis ir priklauso jums. Jūs pasitikite sertifikatu ir tuo, kad viešasis raktas yra iš to, kas nurodyta sertifikate, nes pasitikite CA, panašiai kaip pasitikėtumėte pasu ar vairuotojo pažymėjimu, nes pasitikite šalimi, kuri jį išdavė. Sertifikatai kainuoja pinigus, todėl taip pat galite „pasirašyti patys“, tai yra, sukurti sertifikatą patys ir jį pasirašyti testavimo tikslais.

> 💁 Niekada nenaudokite savarankiškai pasirašyto sertifikato gamybos aplinkoje.

Šiuose sertifikatuose yra daug laukų, įskaitant informaciją, iš ko yra viešasis raktas, CA, kuris jį išdavė, duomenis, kiek laiko jis galioja, ir patį viešąjį raktą. Prieš naudojant sertifikatą, gera praktika yra jį patikrinti, įsitikinant, kad jis buvo pasirašytas pradinės CA.

✅ Visą sertifikato laukų sąrašą galite rasti [Microsoft vadove apie X.509 viešojo rakto sertifikatus](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields).

Naudojant X.509 sertifikatus, tiek siuntėjas, tiek gavėjas turės savo viešuosius ir privačius raktus, taip pat abu turės X.509 sertifikatus, kuriuose yra viešasis raktas. Jie tada kažkokiu būdu apsikeičia X.509 sertifikatais, naudodami vienas kito viešuosius raktus duomenims, kuriuos siunčia, užšifruoti, o savo privačius raktus – duomenims, kuriuos gauna, iššifruoti.

![Vietoj viešojo rakto galite dalintis sertifikatu. Sertifikato naudotojas gali patikrinti, ar jis yra iš jūsų, pasitikrindamas su sertifikavimo institucija, kuri jį pasirašė.](../../../../../translated_images/lt/send-message-certificate.9cc576ac1e46b76e.webp)

Didelis X.509 sertifikatų privalumas yra tas, kad jie gali būti dalijami tarp įrenginių. Galite sukurti vieną sertifikatą, įkelti jį į IoT Hub ir naudoti jį visiems savo įrenginiams. Kiekvienas įrenginys tada turi žinoti tik privatų raktą, kad iššifruotų pranešimus, kuriuos gauna iš IoT Hub.

Sertifikatas, kurį jūsų įrenginys naudoja pranešimams, siunčiamiems į IoT Hub, užšifruoti, yra paskelbtas „Microsoft“. Tai tas pats sertifikatas, kurį naudoja daugelis „Azure“ paslaugų, ir jis kartais yra integruotas į SDK.

> 💁 Atminkite, viešasis raktas yra tiesiog viešas. „Azure“ viešasis raktas gali būti naudojamas tik duomenims, siunčiamiems į „Azure“, užšifruoti, bet ne iššifruoti, todėl jis gali būti dalijamas visur, įskaitant šaltinio kodą. Pavyzdžiui, jį galite pamatyti [Azure IoT C SDK šaltinio kode](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c).

✅ Yra daug terminų, susijusių su X.509 sertifikatais. Kai kurių terminų apibrėžimus galite rasti [Paprastame X.509 sertifikatų terminų vadove](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn).

## Sukurkite ir naudokite X.509 sertifikatą

X.509 sertifikato sukūrimo žingsniai yra šie:

1. Sukurkite viešojo/privačiojo rakto porą. Vienas iš plačiausiai naudojamų algoritmų viešojo/privačiojo rakto porai generuoti yra [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem)) (RSA).

1. Pateikite viešąjį raktą su susijusiais duomenimis pasirašymui, arba CA, arba pasirašydami patys.

Azure CLI turi komandas, skirtas sukurti naują įrenginio tapatybę IoT Hub ir automatiškai sugeneruoti viešojo/privačiojo rakto porą bei sukurti savarankiškai pasirašytą sertifikatą.

> 💁 Jei norite pamatyti išsamius veiksmus, o ne naudoti Azure CLI, juos galite rasti [Microsoft IoT Hub dokumentacijoje apie savarankiškai pasirašytų sertifikatų kūrimą naudojant OpenSSL](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn).

### Užduotis – sukurkite įrenginio tapatybę naudodami X.509 sertifikatą

1. Paleiskite šią komandą, kad užregistruotumėte naują įrenginio tapatybę, automatiškai sugeneruodami raktus ir sertifikatus:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Pakeiskite `<hub_name>` į jūsų IoT Hub pavadinimą.

    Tai sukurs įrenginį su ID `soil-moisture-sensor-x509`, kad būtų atskirtas nuo įrenginio tapatybės, kurią sukūrėte ankstesnėje pamokoje. Ši komanda taip pat sukurs 2 failus dabartiniame kataloge:

    * `soil-moisture-sensor-x509-key.pem` – šis failas turi įrenginio privatų raktą.
    * `soil-moisture-sensor-x509-cert.pem` – tai įrenginio X.509 sertifikato failas.

    Laikykite šiuos failus saugiai! Privataus rakto failas neturėtų būti patalpintas viešame šaltinio kodo valdyme.

### Užduotis – naudokite X.509 sertifikatą savo įrenginio kode

Atlikite atitinkamą vadovą, kad prijungtumėte savo IoT įrenginį prie debesies naudodami X.509 sertifikatą:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Vienos plokštės kompiuteris - Raspberry Pi/Virtualus IoT įrenginys](single-board-computer-x509.md)

---

## 🚀 Iššūkis

Yra keli būdai kurti, valdyti ir ištrinti „Azure“ paslaugas, tokias kaip išteklių grupės ir IoT Hub. Vienas iš jų yra [Azure Portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) – internetinė sąsaja, suteikianti grafinę vartotojo sąsają jūsų „Azure“ paslaugoms valdyti.

Apsilankykite [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) ir ištyrinėkite portalą. Pabandykite sukurti IoT Hub naudodami portalą, o tada jį ištrinkite.

**Patarimas** – kuriant paslaugas per portalą, jums nereikia iš anksto kurti išteklių grupės, ją galima sukurti kuriant paslaugą. Įsitikinkite, kad ją ištrinate, kai baigiate!

Daug dokumentacijos, pamokų ir vadovų apie Azure Portal galite rasti [Azure portalo dokumentacijoje](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Po paskaitos testas

[Po paskaitos testas](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Apžvalga ir savarankiškas mokymasis

* Perskaitykite apie kriptografijos istoriją [Kriptografijos istorijos puslapyje Vikipedijoje](https://wikipedia.org/wiki/History_of_cryptography).
* Perskaitykite apie X.509 sertifikatus [X.509 puslapyje Vikipedijoje](https://wikipedia.org/wiki/X.509).

## Užduotis

[Sukurkite naują IoT įrenginį](assignment.md)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Dėl svarbios informacijos rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.