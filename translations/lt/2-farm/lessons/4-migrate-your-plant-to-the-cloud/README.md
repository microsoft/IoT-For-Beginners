# Perkelkite savo augalą į debesį

![Šios pamokos apžvalga piešiniu](../../../../../translated_images/lt/lesson-8.3f21f3c11159e6a0.webp)

> Piešinys sukurtas [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

Ši pamoka buvo dėstoma kaip dalis [IoT pradedantiesiems 2 projekto - Skaitmeninė žemdirbystė](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) iš [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Prijunkite savo įrenginį prie debesies su Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Klausimynas prieš paskaitą

[Klausimynas prieš paskaitą](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Įvadas

Paskutinėje pamokoje išmokote, kaip prijungti savo augalą prie MQTT brokerio ir valdyti relę iš serverio kodo, veikiančio vietoje. Tai yra pagrindas interneto prijungtos automatinės laistymo sistemos, kuri naudojama tiek namuose augalams, tiek komerciniuose ūkiuose.

IoT įrenginys bendravo su viešu MQTT brokeriu, kad būtų parodyti principai, tačiau tai nėra pats patikimiausias ar saugiausias būdas. Šioje pamokoje sužinosite apie debesį ir IoT galimybes, kurias teikia viešos debesų paslaugos. Taip pat išmoksite, kaip perkelti savo augalą į vieną iš šių debesų paslaugų iš viešo MQTT brokerio.

Šioje pamokoje aptarsime:

* [Kas yra debesis?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Sukurkite debesies prenumeratą](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Debesų IoT paslaugos](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Sukurkite IoT paslaugą debesyje](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Bendraukite su IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Prijunkite savo įrenginį prie IoT paslaugos](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Kas yra debesis?

Prieš atsirandant debesims, kai įmonė norėjo teikti paslaugas savo darbuotojams (pvz., duomenų bazes ar failų saugojimą) arba visuomenei (pvz., svetaines), ji turėjo kurti ir valdyti duomenų centrą. Tai galėjo būti nuo mažo kambario su keliais kompiuteriais iki pastato su daugybe kompiuterių. Įmonė turėjo valdyti viską, įskaitant:

* Kompiuterių pirkimą
* Aparatūros priežiūrą
* Energiją ir aušinimą
* Tinklų kūrimą
* Saugumą, įskaitant pastato ir programinės įrangos saugumą
* Programinės įrangos diegimą ir atnaujinimus

Tai galėjo būti labai brangu, reikalauti įvairių kvalifikuotų darbuotojų ir būti labai lėta, kai reikėjo pokyčių. Pavyzdžiui, jei internetinė parduotuvė turėjo pasiruošti užimtam šventiniam sezonui, ji turėjo planuoti mėnesiais iš anksto, kad įsigytų daugiau aparatinės įrangos, ją sukonfigūruotų, įdiegtų ir paleistų pardavimo procesą. Po šventinio sezono, kai pardavimai sumažėdavo, jie likdavo su kompiuteriais, už kuriuos sumokėjo, bet kurie stovėdavo nenaudojami iki kito užimto sezono.

✅ Ar manote, kad tai leistų įmonėms greitai prisitaikyti? Jei internetinė drabužių parduotuvė staiga išpopuliarėtų dėl to, kad įžymybė buvo pastebėta su jų drabužiais, ar jie galėtų greitai padidinti savo kompiuterinę galią, kad palaikytų staigų užsakymų antplūdį?

### Kito žmogaus kompiuteris

Debesis dažnai juokais vadinamas „kito žmogaus kompiuteriu“. Pradinė idėja buvo paprasta – vietoj kompiuterių pirkimo, jūs nuomojate kito žmogaus kompiuterį. Kitas žmogus, debesų kompiuterijos teikėjas, valdytų didžiulius duomenų centrus. Jie būtų atsakingi už aparatinės įrangos pirkimą ir diegimą, energijos ir aušinimo valdymą, tinklų kūrimą, pastato saugumą, aparatinės ir programinės įrangos atnaujinimus – viską. Kaip klientas, jūs nuomotumėte kompiuterius, kurių jums reikia, nuomodami daugiau, kai paklausa didėja, ir mažindami nuomą, kai paklausa mažėja. Šie debesų duomenų centrai yra visame pasaulyje.

![Microsoft debesų duomenų centras](../../../../../translated_images/lt/azure-region-existing.73f704604f2aa6cb.webp)
![Microsoft debesų duomenų centro planuojama plėtra](../../../../../translated_images/lt/azure-region-planned-expansion.a5074a1e8af74f15.webp)

Šie duomenų centrai gali būti kelių kvadratinių kilometrų dydžio. Aukščiau pateiktos nuotraukos buvo padarytos prieš keletą metų Microsoft debesų duomenų centre ir rodo pradinį dydį bei planuojamą plėtrą. Plėtrai išvalyta teritorija yra daugiau nei 5 kvadratinių kilometrų.

> 💁 Šiems duomenų centrams reikia tokio didelio energijos kiekio, kad kai kurie turi savo elektrines. Dėl savo dydžio ir debesų teikėjų investicijų jie paprastai yra labai ekologiški. Jie yra efektyvesni nei daugybė mažų duomenų centrų, veikia daugiausia naudojant atsinaujinančią energiją, o debesų teikėjai stengiasi mažinti atliekas, mažinti vandens naudojimą ir atsodinti miškus, kad kompensuotų tuos, kurie buvo iškirsti, kad būtų sukurta vieta duomenų centrams. Daugiau apie tai, kaip vienas debesų teikėjas dirba su tvarumu, galite perskaityti [Azure tvarumo svetainėje](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Atlikite tyrimą: Perskaitykite apie pagrindinius debesų teikėjus, tokius kaip [Microsoft Azure](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) arba [Google GCP](https://cloud.google.com). Kiek duomenų centrų jie turi ir kur jie yra pasaulyje?

Naudojant debesį, įmonės gali sumažinti išlaidas ir sutelkti dėmesį į tai, ką jos daro geriausiai, palikdamos debesų kompiuterijos ekspertizę teikėjui. Įmonėms nebereikia nuomotis ar pirkti duomenų centro vietos, mokėti skirtingiems teikėjams už ryšį ir energiją ar samdyti ekspertus. Vietoj to, jos gali mokėti vieną mėnesinį mokestį debesų teikėjui, kad viskas būtų pasirūpinta.

Debesų teikėjas gali naudoti masto ekonomiją, kad sumažintų išlaidas, pirkdamas kompiuterius dideliais kiekiais už mažesnę kainą, investuodamas į įrankius, kad sumažintų savo darbo krūvį priežiūrai, netgi kurdamas ir gamindamas savo aparatinę įrangą, kad pagerintų savo debesų pasiūlą.

### Microsoft Azure

Azure yra Microsoft debesų platforma, kurią naudosite šiose pamokose. Žemiau pateiktas trumpas Azure apžvalgos vaizdo įrašas:

[![Azure apžvalgos vaizdo įrašas](../../../../../translated_images/lt/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Sukurkite debesies prenumeratą

Norėdami naudotis debesų paslaugomis, turėsite užsiregistruoti debesų teikėjo prenumeratai. Šioje pamokoje užsiregistruosite Microsoft Azure prenumeratai. Jei jau turite Azure prenumeratą, galite praleisti šią užduotį. Prenumeratos detalės, aprašytos čia, yra teisingos rašymo metu, tačiau gali keistis.

> 💁 Jei šias pamokas pasiekiate per savo mokyklą, jums gali būti jau suteikta Azure prenumerata. Pasitarkite su savo mokytoju.

Yra du skirtingi nemokami Azure prenumeratos tipai, kuriuos galite užsiregistruoti:

* **Azure for Students** – Tai prenumerata, skirta studentams nuo 18 metų. Jums nereikia kredito kortelės, kad užsiregistruotumėte, ir naudojate savo mokyklos el. pašto adresą, kad patvirtintumėte, jog esate studentas. Užsiregistravę gaunate 100 USD, kuriuos galite išleisti debesų ištekliams, kartu su nemokamomis paslaugomis, įskaitant nemokamą IoT paslaugos versiją. Tai galioja 12 mėnesių, ir galite atnaujinti kiekvienais metais, kol esate studentas.

* **Azure nemokama prenumerata** – Tai prenumerata visiems, kurie nėra studentai. Jums reikės kredito kortelės, kad užsiregistruotumėte, tačiau jūsų kortelė nebus apmokestinta, ji naudojama tik tam, kad patvirtintumėte, jog esate tikras žmogus, o ne robotas. Pirmąsias 30 dienų gaunate 200 USD kreditą, kurį galite naudoti bet kuriai paslaugai, kartu su nemokamais Azure paslaugų lygiais. Kai jūsų kreditas bus išnaudotas, jūsų kortelė nebus apmokestinta, nebent konvertuosite į mokėjimo pagal naudojimą prenumeratą.

> 💁 Microsoft siūlo Azure for Students Starter prenumeratą studentams iki 18 metų, tačiau rašymo metu ji nepalaiko jokių IoT paslaugų.

### Užduotis – užsiregistruokite nemokamai debesies prenumeratai

Jei esate studentas nuo 18 metų, galite užsiregistruoti Azure for Students prenumeratai. Jums reikės patvirtinti mokyklos el. pašto adresą. Tai galite padaryti dviem būdais:

* Užsiregistruokite GitHub studentų kūrėjų pakete [education.github.com/pack](https://education.github.com/pack). Tai suteikia jums prieigą prie įvairių įrankių ir pasiūlymų, įskaitant GitHub ir Microsoft Azure. Užsiregistravę kūrėjų pakete, galite aktyvuoti Azure for Students pasiūlymą.

* Tiesiogiai užsiregistruokite Azure for Students paskyrai [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Jei jūsų mokyklos el. pašto adresas nėra atpažintas, pateikite [problemą šiame repo](https://github.com/Microsoft/IoT-For-Beginners/issues), ir mes pažiūrėsime, ar jis gali būti pridėtas prie Azure for Students leidžiamo sąrašo.

Jei nesate studentas arba neturite galiojančio mokyklos el. pašto adreso, galite užsiregistruoti Azure nemokamai prenumeratai.

* Užsiregistruokite Azure nemokamai prenumeratai [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Debesų IoT paslaugos

Viešas testinis MQTT brokeris, kurį naudojote, yra puikus įrankis mokantis, tačiau turi keletą trūkumų kaip įrankis, skirtas naudoti komercinėje aplinkoje:

* Patikimumas – tai nemokama paslauga be garantijų, kuri gali būti išjungta bet kuriuo metu
* Saugumas – ji yra vieša, todėl bet kas galėtų klausytis jūsų telemetrijos arba siųsti komandas jūsų įrangai valdyti
* Našumas – ji skirta tik keliems testiniams pranešimams, todėl nesusidorotų su dideliu pranešimų kiekiu
* Aptikimas – nėra būdo sužinoti, kokie įrenginiai yra prijungti

IoT paslaugos debesyje išsprendžia šias problemas. Jas prižiūri dideli debesų teikėjai, kurie daug investuoja į patikimumą ir yra pasiruošę spręsti bet kokias iškilusias problemas. Jos turi integruotą saugumą, kad užkirstų kelią įsilaužėliams skaityti jūsų duomenis ar siųsti netikras komandas. Jos taip pat yra labai našios, galinčios apdoroti milijonus pranešimų kasdien, pasinaudodamos debesies galimybėmis masto didinimui.

> 💁 Nors už šiuos privalumus mokate mėnesinį mokestį, dauguma debesų teikėjų siūlo nemokamą savo IoT paslaugos versiją su ribotu pranešimų per dieną ar prijungtų įrenginių skaičiumi. Ši nemokama versija paprastai yra daugiau nei pakankama, kad kūrėjas galėtų susipažinti su paslauga. Šioje pamokoje naudosite nemokamą versiją.

IoT įrenginiai prisijungia prie debesų paslaugos naudodami įrenginio SDK (biblioteką, kuri teikia kodą darbui su paslaugos funkcijomis) arba tiesiogiai per komunikacijos protokolą, pvz., MQTT arba HTTP. Įrenginio SDK paprastai yra lengviausias kelias, nes jis viską tvarko už jus, pvz., žino, kokias temas publikuoti ar prenumeruoti, ir kaip tvarkyti saugumą.

![Įrenginiai prisijungia prie paslaugos naudodami įrenginio SDK. Serverio kodas taip pat prisijungia prie paslaugos per SDK](../../../../../translated_images/lt/iot-service-connectivity.7e873847921a5d6f.webp)

Jūsų įrenginys tada bendrauja su kitomis jūsų programos dalimis per šią paslaugą – panašiai kaip jūs siuntėte telemetriją ir gavote komandas per MQTT. Tai paprastai vyksta naudojant paslaugos SDK arba panašią biblioteką. Pranešimai ateina iš jūsų įrenginio į paslaugą, kur kiti jūsų programos komponentai gali juos perskaityti, o pranešimai gali būti siunčiami atgal į jūsų įrenginį.

![Įrenginiai be galiojančio slapto rakto negali prisijungti prie IoT paslaugos](../../../../../translated_images/lt/iot-service-allowed-denied-connection.818b0063ac213fb8.webp)

Šios paslaugos įgyvendina saugumą, žinodamos apie visus įrenginius, kurie gali prisijungti ir siųsti duomenis, arba turėdamos iš anksto registruotus įrenginius, arba suteikdamos įrenginiams slaptus raktus ar sertifikatus, kuriuos jie gali naudoti registruodamiesi paslaugoje pirmą kartą prisijungdami. Nežinomi įrenginiai negali prisijungti – jei jie bando, paslauga atmeta prisijungimą ir ignoruoja jų siunčiamus pranešimus.

✅ Atlikite tyrimą: Koks yra atviro IoT paslaugos, kur bet kuris įrenginys ar kodas gali prisijungti, trūkumas? Ar galite rasti konkrečių pavyzdžių, kai įsilaužėliai pasinaudojo tokia situacija?

Kiti jūsų programos komponentai gali prisijungti prie IoT paslaugos ir sužinoti apie visus prijungtus ar registruotus įrenginius, taip pat bendrauti su jais tiesiogiai arba masiškai.
💁 IoT paslaugos taip pat įgyvendina papildomas funkcijas, o debesijos paslaugų teikėjai turi papildomas paslaugas ir programas, kurias galima prijungti prie paslaugos. Pavyzdžiui, jei norite saugoti visus telemetrijos pranešimus, kuriuos siunčia visi įrenginiai, duomenų bazėje, dažniausiai užtenka kelių paspaudimų debesijos paslaugų teikėjo konfigūracijos įrankyje, kad prijungtumėte paslaugą prie duomenų bazės ir pradėtumėte duomenų srautą.
## Sukurkite IoT paslaugą debesyje

Dabar, kai turite „Azure“ prenumeratą, galite užsiregistruoti IoT paslaugai. „Microsoft“ IoT paslauga vadinama „Azure IoT Hub“.

![Azure IoT Hub logotipas](../../../../../translated_images/lt/azure-iot-hub-logo.28a19de76d0a1932.webp)

Žemiau pateiktame vaizdo įraše rasite trumpą „Azure IoT Hub“ apžvalgą:

[![Azure IoT Hub apžvalgos vaizdo įrašas](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Spustelėkite paveikslėlį aukščiau, kad peržiūrėtumėte vaizdo įrašą

✅ Skirkite šiek tiek laiko tyrimams ir perskaitykite IoT Hub apžvalgą [Microsoft IoT Hub dokumentacijoje](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

„Azure“ debesų paslaugas galima konfigūruoti per internetinį portalą arba komandinės eilutės sąsają (CLI). Šiai užduočiai atlikti naudosite CLI.

### Užduotis - įdiekite „Azure CLI“

Norėdami naudoti „Azure CLI“, pirmiausia turite ją įdiegti savo kompiuteryje ar „Mac“.

1. Vadovaukitės instrukcijomis [Azure CLI dokumentacijoje](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn), kad įdiegtumėte CLI.

1. „Azure CLI“ palaiko daugybę plėtinių, kurie prideda galimybes valdyti įvairias „Azure“ paslaugas. Įdiekite IoT plėtinį, vykdydami šią komandą iš savo komandinės eilutės arba terminalo:

    ```sh
    az extension add --name azure-iot
    ```

1. Iš savo komandinės eilutės arba terminalo vykdykite šią komandą, kad prisijungtumėte prie savo „Azure“ prenumeratos per „Azure CLI“.

    ```sh
    az login
    ```

    Jūsų numatytoji naršyklė atidarys tinklalapį. Prisijunkite naudodami paskyrą, kurią naudojote registruodamiesi „Azure“ prenumeratai. Kai prisijungsite, galite uždaryti naršyklės skirtuką.

1. Jei turite kelias „Azure“ prenumeratas, pvz., mokyklos suteiktą ir savo „Azure for Students“ prenumeratą, turėsite pasirinkti, kurią norite naudoti. Vykdykite šią komandą, kad pamatytumėte visas prenumeratas, prie kurių turite prieigą:

    ```sh
    az account list --output table
    ```

    Rezultatuose matysite kiekvienos prenumeratos pavadinimą kartu su jos `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Norėdami pasirinkti norimą prenumeratą, naudokite šią komandą:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Pakeiskite `<SubscriptionId>` į prenumeratos ID, kurią norite naudoti. Po šios komandos vykdymo dar kartą paleiskite komandą, kad pamatytumėte savo paskyras. Matysite, kad `IsDefault` stulpelis bus pažymėtas kaip `True` prenumeratai, kurią ką tik nustatėte.

### Užduotis - sukurkite išteklių grupę

„Azure“ paslaugos, tokios kaip IoT Hub instancijos, virtualios mašinos, duomenų bazės ar AI paslaugos, vadinamos **ištekliais**. Kiekvienas išteklius turi būti priskirtas **išteklių grupei**, loginei vieno ar daugiau išteklių grupavimui.

> 💁 Naudojant išteklių grupes, galima valdyti kelias paslaugas vienu metu. Pavyzdžiui, baigus visas pamokas šiam projektui, galite ištrinti išteklių grupę, ir visi joje esantys ištekliai bus automatiškai ištrinti.

1. „Azure“ duomenų centrai yra išsidėstę visame pasaulyje, suskirstyti į regionus. Kai kuriate „Azure“ išteklius ar išteklių grupę, turite nurodyti, kur norite ją sukurti. Vykdykite šią komandą, kad gautumėte vietų sąrašą:

    ```sh
    az account list-locations --output table
    ```

    Matysite vietų sąrašą. Šis sąrašas bus ilgas.

    > 💁 Rašymo metu yra 65 vietos, kuriose galite diegti.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Užsirašykite vertę iš `Name` stulpelio regiono, kuris yra arčiausiai jūsų. Regionus galite rasti žemėlapyje [Azure geographies puslapyje](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Vykdykite šią komandą, kad sukurtumėte išteklių grupę, pavadintą `soil-moisture-sensor`. Išteklių grupės pavadinimai turi būti unikalūs jūsų prenumeratoje.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Pakeiskite `<location>` į vietą, kurią pasirinkote ankstesniame žingsnyje.

### Užduotis - sukurkite IoT Hub

Dabar galite sukurti IoT Hub išteklių savo išteklių grupėje.

1. Naudokite šią komandą, kad sukurtumėte savo IoT Hub išteklių:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Pakeiskite `<hub_name>` į savo hub pavadinimą. Šis pavadinimas turi būti globaliai unikalus - tai reiškia, kad jokio kito IoT Hub, sukurto bet kieno, negali turėti tokio paties pavadinimo. Šis pavadinimas naudojamas URL, kuris nukreipia į hub, todėl turi būti unikalus. Naudokite kažką panašaus į `soil-moisture-sensor-` ir pridėkite unikalų identifikatorių, pvz., keletą atsitiktinių žodžių ar savo vardą.

    `--sku F1` parinktis nurodo naudoti nemokamą planą. Nemokamas planas palaiko 8,000 pranešimų per dieną kartu su dauguma pilno kainos planų funkcijų.

    > 🎓 Skirtingi „Azure“ paslaugų kainų lygiai vadinami planais. Kiekvienas planas turi skirtingą kainą ir siūlo skirtingas funkcijas ar duomenų apimtis.

    > 💁 Jei norite sužinoti daugiau apie kainas, galite peržiūrėti [Azure IoT Hub kainų vadovą](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    `--partition-count 2` parinktis apibrėžia, kiek duomenų srautų palaiko IoT Hub, daugiau skaidinių sumažina duomenų blokavimą, kai keli dalykai skaito ir rašo iš IoT Hub. Skaidinių tema yra už šių pamokų ribų, tačiau ši vertė turi būti nustatyta, kad būtų sukurtas nemokamas IoT Hub planas.

    > 💁 Vienoje prenumeratoje galite turėti tik vieną nemokamą IoT Hub.

IoT Hub bus sukurtas. Tai gali užtrukti minutę ar dvi.

## Bendravimas su IoT Hub

Ankstesnėje pamokoje naudojote MQTT ir siuntėte pranešimus pirmyn ir atgal skirtingomis temomis, kurių kiekviena turėjo skirtingą paskirtį. Vietoj pranešimų siuntimo skirtingomis temomis, IoT Hub turi keletą apibrėžtų būdų, kaip įrenginys gali bendrauti su Hub arba kaip Hub gali bendrauti su įrenginiu.

> 💁 Viduje šis bendravimas tarp IoT Hub ir jūsų įrenginio gali naudoti MQTT, HTTPS arba AMQP.

* Pranešimai iš įrenginio į debesį (D2C) - tai pranešimai, siunčiami iš įrenginio į IoT Hub, pvz., telemetrija. Juos gali perskaityti jūsų programos kodas.

    > 🎓 Viduje IoT Hub naudoja „Azure“ paslaugą, vadinamą [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Kai rašote kodą, kad perskaitytumėte pranešimus, siunčiamus į hub, jie dažnai vadinami įvykiais.

* Pranešimai iš debesies į įrenginį (C2D) - tai pranešimai, siunčiami iš programos kodo per IoT Hub į IoT įrenginį.

* Tiesioginiai metodų užklausos - tai pranešimai, siunčiami iš programos kodo per IoT Hub į IoT įrenginį, kad būtų paprašyta, jog įrenginys atliktų tam tikrą veiksmą, pvz., valdyti aktuatorių. Šie pranešimai reikalauja atsakymo, kad jūsų programos kodas galėtų sužinoti, ar jie buvo sėkmingai apdoroti.

* Įrenginio dvyniai - tai JSON dokumentai, sinchronizuojami tarp įrenginio ir IoT Hub, ir naudojami nustatymams ar kitoms savybėms saugoti, kurias praneša įrenginys arba kurias turėtų nustatyti IoT Hub (vadinamos pageidaujamomis).

IoT Hub gali saugoti pranešimus ir tiesioginių metodų užklausas tam tikrą laiką (numatytasis laikotarpis yra viena diena), todėl jei įrenginys ar programos kodas praranda ryšį, jis vis tiek gali gauti pranešimus, kurie buvo išsiųsti, kol jis buvo neprisijungęs, kai vėl prisijungia. Įrenginio dvyniai saugomi IoT Hub nuolat, todėl bet kuriuo metu įrenginys gali prisijungti ir gauti naujausią įrenginio dvynį.

✅ Atlikite tyrimą: Skaitykite daugiau apie šių pranešimų tipus [Device-to-cloud communications guidance](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) ir [Cloud-to-device communications guidance](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) IoT Hub dokumentacijoje.

## Prijunkite savo įrenginį prie IoT paslaugos

Kai hub bus sukurtas, jūsų IoT įrenginys galės prie jo prisijungti. Tik registruoti įrenginiai gali prisijungti prie paslaugos, todėl pirmiausia turėsite užregistruoti savo įrenginį. Registruodami gausite prisijungimo eilutę, kurią įrenginys galės naudoti prisijungimui. Ši prisijungimo eilutė yra specifinė įrenginiui ir joje yra informacija apie IoT Hub, įrenginį ir slaptą raktą, kuris leis šiam įrenginiui prisijungti.

> 🎓 Prisijungimo eilutė yra bendras terminas tekstui, kuriame yra prisijungimo detalės. Jos naudojamos prisijungiant prie IoT Hub, duomenų bazių ir daugelio kitų paslaugų. Paprastai jos susideda iš paslaugos identifikatoriaus, pvz., URL, ir saugumo informacijos, pvz., slapto rakto. Jos perduodamos SDK, kad būtų galima prisijungti prie paslaugos.

> ⚠️ Prisijungimo eilutės turėtų būti laikomos saugiai! Saugumas bus aptartas išsamiau būsimoje pamokoje.

### Užduotis - užregistruokite savo IoT įrenginį

IoT įrenginį galima užregistruoti jūsų IoT Hub naudojant „Azure CLI“.

1. Vykdykite šią komandą, kad užregistruotumėte įrenginį:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Pakeiskite `<hub_name>` į pavadinimą, kurį naudojote savo IoT Hub.

    Tai sukurs įrenginį su ID `soil-moisture-sensor`.

1. Kai jūsų IoT įrenginys prisijungia prie jūsų IoT Hub naudodamas SDK, jis turi naudoti prisijungimo eilutę, kurioje yra hub URL ir slaptas raktas. Vykdykite šią komandą, kad gautumėte prisijungimo eilutę:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Pakeiskite `<hub_name>` į pavadinimą, kurį naudojote savo IoT Hub.

1. Išsaugokite prisijungimo eilutę, kuri bus rodoma rezultatuose, nes jums jos reikės vėliau.

### Užduotis - prijunkite savo IoT įrenginį prie debesies

Peržiūrėkite atitinkamą vadovą, kad prijungtumėte savo IoT įrenginį prie debesies:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Vieno plokštės kompiuteris - Raspberry Pi/Virtualus IoT įrenginys](single-board-computer-connect-hub.md)

### Užduotis - stebėkite įvykius

Kol kas neatnaujinsite savo serverio kodo. Vietoj to galite naudoti „Azure CLI“, kad stebėtumėte įvykius iš savo IoT įrenginio.

1. Įsitikinkite, kad jūsų IoT įrenginys veikia ir siunčia dirvožemio drėgmės telemetrijos reikšmes.

1. Vykdykite šią komandą savo komandinėje eilutėje arba terminale, kad stebėtumėte pranešimus, siunčiamus į jūsų IoT Hub:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Pakeiskite `<hub_name>` į pavadinimą, kurį naudojote savo IoT Hub.

    Matysite pranešimus, rodomus konsolės išvestyje, kai jie bus siunčiami jūsų IoT įrenginiu.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    `payload` turinys atitiks pranešimą, siunčiamą jūsų IoT įrenginiu.

    > Rašymo metu `az iot` plėtinys nėra visiškai suderinamas su „Apple Silicon“. Jei naudojate „Apple Silicon“ įrenginį, turėsite stebėti pranešimus kitu būdu, pvz., naudodami [Azure IoT Tools for Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Šie pranešimai turi keletą savybių, kurios automatiškai pridedamos, pvz., laiko žymą, kada jie buvo išsiųsti. Šios savybės vadinamos *anotacijomis*. Norėdami peržiūrėti visas pranešimų anotacijas, naudokite šią komandą:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Pakeiskite `<hub_name>` į pavadinimą, kurį naudojote savo IoT Hub.

    Matysite pranešimus, rodomus konsolės išvestyje, kai jie bus siunčiami jūsų IoT įrenginiu.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Laiko reikšmės anotacijose yra [UNIX laikas](https://wikipedia.org/wiki/Unix_time), kuris reiškia sekundžių skaičių nuo 1970 m. sausio 1 d. vidurnakčio.

    Baigę stebėti įvykius, išeikite iš stebėjimo režimo.

### Užduotis - valdykite savo IoT įrenginį

Taip pat galite naudoti „Azure CLI“, kad iškviestumėte tiesioginius metodus savo IoT įrenginyje.

1. Vykdykite šią komandą savo komandinėje eilutėje arba terminale, kad iškviestumėte `relay_on` metodą savo IoT įrenginyje:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Pakeiskite `
<hub_name>
` naudodami savo IoT Hub pavadinimą.

    Tai siunčia tiesioginį metodo užklausą nurodytam metodui, kurio pavadinimas yra `method-name`. Tiesioginiai metodai gali priimti naudingąją apkrovą su duomenimis metodui, kurią galima nurodyti `method-payload` parametru JSON formatu.

    Pamatysite, kaip įsijungia relė, ir atitinkamą išvestį iš jūsų IoT įrenginio:

    ```output
    Direct method received -  relay_on
    ```

1. Pakartokite aukščiau nurodytą veiksmą, tačiau nustatykite `--method-name` į `relay_off`. Pamatysite, kaip relė išsijungia, ir atitinkamą išvestį iš IoT įrenginio.

---

## 🚀 Iššūkis

Nemokamas IoT Hub planas leidžia siųsti 8 000 pranešimų per dieną. Jūsų parašytas kodas siunčia telemetrijos pranešimus kas 10 sekundžių. Kiek pranešimų per dieną sudaro vienas pranešimas kas 10 sekundžių?

Pagalvokite, kaip dažnai turėtų būti siunčiami dirvožemio drėgmės matavimai? Kaip galite pakeisti savo kodą, kad liktumėte nemokamame plane, tikrintumėte taip dažnai, kaip reikia, bet ne per dažnai? O kas, jei norėtumėte pridėti antrą įrenginį?

## Po paskaitos testas

[Po paskaitos testas](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Apžvalga ir savarankiškas mokymasis

IoT Hub SDK yra atvirojo kodo tiek Arduino, tiek Python platformoms. GitHub kodų saugyklose yra daugybė pavyzdžių, kaip dirbti su įvairiomis IoT Hub funkcijomis.

* Jei naudojate Wio Terminal, peržiūrėkite [Arduino pavyzdžius GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Jei naudojate Raspberry Pi arba virtualų įrenginį, peržiūrėkite [Python pavyzdžius GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Užduotis

[Sužinokite apie debesų paslaugas](assignment.md)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors stengiamės užtikrinti tikslumą, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.