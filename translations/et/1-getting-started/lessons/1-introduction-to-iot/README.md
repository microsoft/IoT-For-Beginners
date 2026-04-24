# Sissejuhatus asjade internetti

![Selle õppetunni visandmärkmed](../../../../../translated_images/et/lesson-1.2606670fa61ee904.webp)

> Visandmärkmed: [Nitya Narasimhan](https://github.com/nitya). Suurema versiooni vaatamiseks klõpsake pildil.

See õppetund oli osa [Hello IoT sarjast](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-), mida korraldas [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Õppetund koosnes kahest videost - 1-tunnisest loengust ja 1-tunnisest küsimuste-vastuste sessioonist, kus käsitleti teemat süvitsi ja vastati küsimustele.

[![Õppetund 1: Sissejuhatus asjade internetti](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Õppetund 1: Sissejuhatus asjade internetti - Küsimuste-vastuste sessioon](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Klõpsake ülaltoodud piltidel, et vaadata videoid

## Loengu-eelne viktoriin

[Loengu-eelne viktoriin](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Sissejuhatus

Selles õppetükis käsitletakse asjade interneti (IoT) algteemasid ja alustatakse riistvara seadistamisega.

Selles õppetükis käsitleme:

* [Mis on "asjade internet"?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT seadmed](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Seadme seadistamine](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT rakendused](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Näiteid IoT seadmetest sinu ümber](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Mis on "asjade internet"?

Mõiste "asjade internet" (Internet of Things) võttis kasutusele [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) 1999. aastal, viidates interneti ühendamisele füüsilise maailmaga andurite kaudu. Sellest ajast alates on seda terminit kasutatud kirjeldamaks mis tahes seadet, mis suhtleb teda ümbritseva füüsilise maailmaga, kas andurite kaudu andmeid kogudes või aktuaatorite kaudu reaalseid toiminguid tehes (näiteks lüliti sisse lülitamine või LED-i süütamine), olles tavaliselt ühendatud teiste seadmete või internetiga.

> **Andurid** koguvad teavet maailmast, näiteks mõõdavad kiirust, temperatuuri või asukohta.
>
> **Aktuaatorid** muudavad elektrisignaalid reaalse maailma toiminguteks, näiteks lüliti käivitamiseks, tulede süütamiseks, helide tekitamiseks või juhtsignaalide saatmiseks teistele seadmetele, näiteks pistiku sisselülitamiseks.

IoT kui tehnoloogia valdkond hõlmab rohkemat kui ainult seadmeid - see hõlmab ka pilvepõhiseid teenuseid, mis töötlevad andurite andmeid või saadavad taotlusi IoT-seadmetega ühendatud aktuaatoritele. Samuti hõlmab see seadmeid, millel puudub või mis ei vaja internetiühendust, mida sageli nimetatakse servaseadmeteks. Need on seadmed, mis suudavad andurite andmeid ise töödelda ja neile reageerida, kasutades tavaliselt pilves treenitud tehisintellekti mudeleid.

IoT on kiiresti kasvav tehnoloogiavaldkond. Hinnanguliselt oli 2020. aasta lõpuks kasutusele võetud ja internetiga ühendatud 30 miljardit IoT-seadet. Tulevikku vaadates prognoositakse, et 2025. aastaks koguvad IoT-seadmed peaaegu 80 zettabaiti andmeid ehk 80 triljonit gigabaiti. See on tohutu hulk andmeid!

![Graafik, mis näitab aktiivsete IoT-seadmete arvu aja jooksul, tõusutrendiga alla 5 miljardist 2015. aastal kuni üle 30 miljardi 2025. aastal](../../../../../images/connected-iot-devices.svg)

✅ Tee väike uurimistöö: Kui suur osa IoT-seadmete genereeritud andmetest tegelikult kasutatakse ja kui palju läheb raisku? Miks nii palju andmeid ignoreeritakse?

Need andmed on IoT edu võti. Et olla edukas IoT arendaja, pead mõistma, milliseid andmeid on vaja koguda, kuidas neid koguda, kuidas nende põhjal otsuseid teha ja kuidas neid otsuseid vajadusel füüsilise maailmaga suhtlemiseks kasutada.

## IoT seadmed

IoT-s tähistab **T** sõna **Things** ehk seadmeid, mis suhtlevad neid ümbritseva füüsilise maailmaga, kas andurite kaudu andmeid kogudes või aktuaatorite kaudu reaalseid toiminguid tehes.

Tootmis- või kommertskasutuseks mõeldud seadmed, nagu näiteks tarbijate fitness-jälgijad või tööstuslikud masinajuhtimisseadmed, on tavaliselt eritellimusel valmistatud. Need kasutavad kohandatud trükkplaate, võib-olla isegi kohandatud protsessoreid, mis on loodud vastama konkreetse ülesande vajadustele, olgu selleks siis piisavalt väike suurus, et randmele mahtuda, või piisavalt vastupidavus, et töötada kõrge temperatuuri, suure koormuse või vibratsiooniga tehasekeskkonnas.

Arendajana, kes õpib IoT-d või loob seadme prototüüpi, pead alustama arenduskomplektiga. Need on üldotstarbelised IoT-seadmed, mis on mõeldud arendajatele kasutamiseks, sageli funktsioonidega, mida tootmisseadmel ei oleks, näiteks komplekt väliseid kontakte andurite või aktuaatorite ühendamiseks, riistvara silumiseks või täiendavad ressursid, mis suurendaksid masstootmise kulusid.

Need arenduskomplektid jagunevad tavaliselt kahte kategooriasse - mikrokontrollerid ja üheplaadiarvutid. Neid tutvustatakse siin ja järgmises õppetükis käsitletakse neid üksikasjalikumalt.

> 💁 Sinu telefon võib samuti olla üldotstarbeline IoT-seade, millel on sisseehitatud andurid ja aktuaatorid. Erinevad rakendused kasutavad neid andureid ja aktuaatoreid erinevatel viisidel koos erinevate pilveteenustega. Samuti on olemas IoT-õpetusi, mis kasutavad telefoni rakendust IoT-seadmena.

### Mikrokontrollerid

Mikrokontroller (tuntud ka kui MCU, mis on lühend sõnadest microcontroller unit) on väike arvuti, mis koosneb järgmistest osadest:

🧠 Üks või mitu keskprotsessorit (CPU-d) - mikrokontrolleri "aju", mis käitab sinu programmi

💾 Mälu (RAM ja programmimälu) - koht, kus hoitakse sinu programmi, andmeid ja muutujaid

🔌 Programmeeritavad sisend/väljund (I/O) ühendused - suhtlemiseks väliste seadmetega (ühendatud seadmed), nagu andurid ja aktuaatorid

Mikrokontrollerid on tavaliselt madala hinnaga arvutiseadmed, mille keskmine hind on umbes 0,50 USA dollarit, mõned seadmed maksavad isegi vaid 0,03 dollarit. Arenduskomplektid algavad umbes 4 dollarist, kuid hind tõuseb, kui lisada rohkem funktsioone. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), mikrokontrolleri arenduskomplekt [Seeed Studiosilt](https://www.seeedstudio.com), millel on andurid, aktuaatorid, WiFi ja ekraan, maksab umbes 30 dollarit.

![Wio Terminal](../../../../../translated_images/et/wio-terminal.b8299ee16587db9a.webp)

> 💁 Kui otsid internetist mikrokontrollereid, ole ettevaatlik otsingutermini **MCU** kasutamisel, kuna see võib tuua palju tulemusi Marveli Kinemaatilise Universumi kohta, mitte mikrokontrollerite kohta.

Mikrokontrollerid on loodud täitma piiratud arvu väga spetsiifilisi ülesandeid, mitte olema üldotstarbelised arvutid nagu PC-d või Macid. Välja arvatud väga spetsiifilistel juhtudel, ei saa neile ühendada monitori, klaviatuuri ega hiirt, et neid üldotstarbelisteks ülesanneteks kasutada.

Mikrokontrolleri arenduskomplektidel on tavaliselt lisatud andurid ja aktuaatorid. Enamikul plaatidel on üks või mitu programmeeritavat LED-i, samuti muid seadmeid, nagu standardsed pistikud täiendavate andurite või aktuaatorite lisamiseks erinevate tootjate ökosüsteemidest või sisseehitatud andurid (tavaliselt kõige populaarsemad, nagu temperatuuriandurid). Mõnel mikrokontrolleril on sisseehitatud traadita ühenduvus, näiteks Bluetooth või WiFi, või täiendavad mikrokontrollerid, mis lisavad selle ühenduvuse.

> 💁 Mikrokontrollereid programmeeritakse tavaliselt C/C++ keeles.

### Üheplaadiarvutid

Üheplaadiarvuti on väike arvutiseade, millel on kõik täisväärtusliku arvuti elemendid ühel väikesel plaadil. Need on seadmed, mille spetsifikatsioonid on sarnased lauaarvuti või sülearvutiga, töötavad täisväärtusliku operatsioonisüsteemiga, kuid on väiksemad, tarbivad vähem energiat ja on oluliselt odavamad.

![Raspberry Pi 4](../../../../../translated_images/et/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi on üks populaarsemaid üheplaadiarvuteid.

Nagu mikrokontrolleril, on ka üheplaadiarvutitel protsessor, mälu ja sisend/väljund kontaktid, kuid neil on täiendavad funktsioonid, nagu graafikakiip monitoride ühendamiseks, heliväljundid ja USB-pordid klaviatuuride, hiirte ja muude standardsete USB-seadmete, näiteks veebikaamerate või välise salvestusruumi ühendamiseks. Programmid salvestatakse SD-kaartidele või kõvaketastele koos operatsioonisüsteemiga, mitte plaadile sisseehitatud mälukiibile.

> 🎓 Võid mõelda üheplaadiarvutist kui väiksemast ja odavamast versioonist PC-st või Macist, millel on lisaks GPIO (üldotstarbelised sisend/väljund) kontaktid andurite ja aktuaatoritega suhtlemiseks.

Üheplaadiarvutid on täisväärtuslikud arvutid, seega saab neid programmeerida mis tahes keeles. IoT-seadmeid programmeeritakse tavaliselt Pythonis.

### Riistvara valikud edasisteks õppetundideks

Kõik järgnevad õppetunnid sisaldavad ülesandeid, kus kasutatakse IoT-seadet füüsilise maailmaga suhtlemiseks ja pilvega suhtlemiseks. Iga õppetund toetab kolme seadmevalikut - Arduino (kasutades Seeed Studios Wio Terminali) või üheplaadiarvutit, kas füüsilist seadet (näiteks Raspberry Pi 4) või virtuaalset üheplaadiarvutit, mis töötab sinu PC-s või Macis.

Võid lugeda kõigi ülesannete täitmiseks vajaliku riistvara kohta [riistvara juhendist](../../../hardware.md).

> 💁 Sul ei ole vaja IoT-riistvara osta, et ülesandeid täita, kõike saab teha virtuaalse üheplaadiarvutiga.

Millise riistvara valid, sõltub sinust - see oleneb sellest, mis sul kodus või koolis saadaval on, ja millist programmeerimiskeelt sa oskad või plaanid õppida. Mõlemad riistvaravariandid kasutavad sama andurite ökosüsteemi, seega kui alustad ühega, saad hiljem teisele üle minna ilma suuremat osa komplektist välja vahetamata. Virtuaalne üheplaadiarvuti on samaväärne Raspberry Pi-ga õppimisega, kusjuures enamik koodi on ülekantav, kui lõpuks seadme ja andurid soetad.

### Arduino arenduskomplekt

Kui oled huvitatud mikrokontrollerite arendamise õppimisest, saad ülesandeid täita Arduino seadme abil. Sul on vaja põhiteadmisi C/C++ programmeerimisest, kuna õppetundides õpetatakse ainult koodi, mis on seotud Arduino raamistikuga, kasutatavate andurite ja aktuaatoritega ning pilvega suhtlemiseks vajalike teekidega.

Ülesannete täitmiseks kasutatakse [Visual Studio Code'i](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) koos [PlatformIO laiendiga mikrokontrollerite arendamiseks](https://platformio.org). Kui oled kogenud Arduino IDE kasutaja, võid kasutada ka seda tööriista, kuid juhiseid ei esitata.

### Üheplaadiarvuti arenduskomplekt

Kui oled huvitatud IoT arendamise õppimisest üheplaadiarvutite abil, saad ülesandeid täita Raspberry Pi või virtuaalse seadme abil, mis töötab sinu PC-s või Macis.

Sul on vaja põhiteadmisi Python programmeerimisest, kuna õppetundides õpetatakse ainult koodi, mis on seotud kasutatavate andurite ja aktuaatoritega ning pilvega suhtlemiseks vajalike teekidega.

> 💁 Kui soovid õppida Pythonis programmeerimist, vaata järgmisi kahte videosarja:
>
> * [Python algajatele](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Veel Pythonit algajatele](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Ülesannete täitmiseks kasutatakse [Visual Studio Code'i](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Kui kasutad Raspberry Pi-d, saad oma Pi-d käivitada kas Raspberry Pi OS-i täisversiooniga ja teha kogu kodeerimise otse Pi-l, kasutades [Raspberry Pi OS-i versiooni VS Code'ist](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), või kasutada Pi-d peata seadmena ja kodeerida oma PC-st või Macist, kasutades VS Code'i koos [Remote SSH laiendiga](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), mis võimaldab sul Pi-ga ühenduda ja koodi redigeerida, siluda ja käivitada, justkui teeksid seda otse seadmel.

Kui kasutad virtuaalse seadme valikut, kodeerid otse oma arvutis. Andurite ja aktuaatorite asemel kasutad tööriista, mis simuleerib seda riistvara, pakkudes anduriväärtusi, mida saad määrata, ja näidates aktuaatorite tulemusi ekraanil.

## Seadme seadistamine

Enne kui saad alustada oma IoT-seadme programmeerimist, pead tegema väikese seadistuse. Järgi allolevaid juhiseid, sõltuvalt sellest, millist seadet kasutad.

> 💁 Kui sul veel seadet ei ole, vaata [riistvara juhendit](../../../hardware.md), et otsustada, millist seadet kasutada ja millist täiendavat riistvara osta. Riistvara ei ole vaja osta, kuna kõiki projekte saab käivitada virtuaalsel riistvaral.

Need juhised sisaldavad linke kolmandate osapoolte veebisaitidele, mis on seotud kasutatava riistvara või tööriistade loojatega. See tagab, et kasutad alati kõige ajakohasemaid juhiseid erinevate tööriistade ja riistvara jaoks.
Töötage läbi vastav juhend, et seadistada oma seade ja lõpetada "Hello World" projekt. See on esimene samm IoT öölambi loomisel nelja õppetunni jooksul selles alustamise osas.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Üheplaadiarvuti - Raspberry Pi](pi.md)
* [Üheplaadiarvuti - Virtuaalne seade](virtual-device.md)

✅ Kasutate VS Code'i nii Arduino kui ka üheplaadiarvutite jaoks. Kui te pole seda varem kasutanud, lugege selle kohta rohkem [VS Code'i veebisaidilt](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## IoT rakendused

IoT hõlmab väga laia valikut kasutusvõimalusi, mis jagunevad mitmesse üldisesse rühma:

* Tarbijate IoT
* Äri IoT
* Tööstuslik IoT
* Infrastruktuuri IoT

✅ Tehke veidi uurimistööd: Leidke iga allpool kirjeldatud valdkonna kohta üks konkreetne näide, mida tekstis ei ole mainitud.

### Tarbijate IoT

Tarbijate IoT viitab IoT-seadmetele, mida tarbijad ostavad ja kodus kasutavad. Mõned neist seadmetest on äärmiselt kasulikud, näiteks nutikõlarid, nutikad küttesüsteemid ja robot-tolmuimejad. Teised võivad olla kaheldava kasulikkusega, näiteks hääljuhtimisega kraanid, mida ei saa välja lülitada, kui hääljuhtimine ei kuule teid voolava vee müra tõttu.

Tarbijate IoT-seadmed aitavad inimestel oma keskkonnas rohkem saavutada, eriti 1 miljardil inimesel, kellel on puue. Robot-tolmuimejad aitavad hoida põrandaid puhtana inimestel, kellel on liikumisraskused ja kes ei saa ise tolmuimejaga koristada; hääljuhtimisega ahjud võimaldavad piiratud nägemise või motoorikaga inimestel ahju ainult häälega soojendada; tervisemonitorid võimaldavad patsientidel ise jälgida kroonilisi haigusi, saades regulaarseid ja üksikasjalikke värskendusi oma seisundi kohta. Need seadmed muutuvad nii tavaliseks, et isegi väikesed lapsed kasutavad neid igapäevaelus, näiteks COVID-pandeemia ajal virtuaalõppes osalevad õpilased, kes seadsid nutikodu seadmetele taimerid, et jälgida oma koolitöid või meeldetuletusi eelseisvate tundide kohta.

✅ Milliseid tarbijate IoT-seadmeid on teil kodus või kaasas?

### Äri IoT

Äri IoT hõlmab IoT kasutamist töökohal. Kontorikeskkonnas võivad olla hõivatussensorid ja liikumisandurid, mis haldavad valgustust ja kütet, et hoida tuled ja kütte ainult siis, kui neid vajatakse, vähendades kulusid ja süsinikuheitmeid. Tehases võivad IoT-seadmed jälgida ohutusriske, näiteks töötajaid, kes ei kanna kiivreid, või ohtlikult kõrgeid müratasemeid. Jaemüügis võivad IoT-seadmed mõõta külmhoonete temperatuuri, hoiatades poeomanikku, kui külmik või sügavkülmik on väljaspool nõutavat temperatuurivahemikku, või jälgida riiulitel olevaid tooteid, et suunata töötajaid täiendama müüdud kaupu. Transporditööstus tugineb üha enam IoT-le, et jälgida sõidukite asukohti, teekonda, juhi tööaega ja puhkepauside järgimist või teavitada töötajaid, kui sõiduk läheneb depoole, et valmistuda laadimiseks või mahalaadimiseks.

✅ Milliseid äri IoT-seadmeid on teie koolis või töökohal?

### Tööstuslik IoT (IIoT)

Tööstuslik IoT ehk IIoT viitab IoT-seadmete kasutamisele masinate juhtimiseks ja haldamiseks suurel skaalal. See hõlmab laia valikut kasutusvõimalusi, alates tehastest kuni digitaalse põllumajanduseni.

Tehased kasutavad IoT-seadmeid mitmel erineval viisil. Masinaid saab jälgida mitme anduriga, et jälgida näiteks temperatuuri, vibratsiooni ja pöörlemiskiirust. Neid andmeid saab jälgida, et masin peatada, kui see läheb teatud tolerantsidest välja - näiteks kui see muutub liiga kuumaks, siis see peatatakse. Neid andmeid saab koguda ja analüüsida aja jooksul, et teha ennustavat hooldust, kus AI-mudelid analüüsivad andmeid, mis viivad rikkeni, ja kasutavad seda teiste rikete ennustamiseks enne nende tekkimist.

Digitaalne põllumajandus on oluline, et planeet suudaks toita kasvavat rahvastikku, eriti 2 miljardit inimest 500 miljonis majapidamises, kes elavad [toimetulekupõllumajandusest](https://wikipedia.org/wiki/Subsistence_agriculture). Digitaalne põllumajandus võib ulatuda mõnest odavast andurist kuni massiivsete kommertslahendusteni. Põllumees võib alustada temperatuuri jälgimisest ja kasutada [kasvupäevade arvestust](https://wikipedia.org/wiki/Growing_degree-day), et ennustada, millal saak on koristamiseks valmis. Nad võivad ühendada mulla niiskuse jälgimise automaatsete kastmissüsteemidega, et anda taimedele täpselt nii palju vett, kui vaja, vältides samas vee raiskamist. Põllumehed lähevad isegi kaugemale, kasutades droone, satelliidiandmeid ja AI-d, et jälgida saagi kasvu, haigusi ja mulla kvaliteeti suurte põllumajanduspiirkondade ulatuses.

✅ Millised muud IoT-seadmed võiksid aidata põllumehi?

### Infrastruktuuri IoT

Infrastruktuuri IoT hõlmab igapäevaselt kasutatava kohaliku ja globaalse infrastruktuuri jälgimist ja juhtimist.

[Nutikad linnad](https://wikipedia.org/wiki/Smart_city) on linnapiirkonnad, mis kasutavad IoT-seadmeid, et koguda andmeid linna kohta ja kasutada neid linna toimimise parandamiseks. Need linnad on tavaliselt juhitud kohalike omavalitsuste, akadeemiliste ringkondade ja kohalike ettevõtete koostöös, jälgides ja hallates erinevaid aspekte, alates transpordist kuni parkimise ja saasteni. Näiteks Taanis Kopenhaagenis on õhusaaste kohalikele elanikele oluline, seega mõõdetakse seda ja andmeid kasutatakse puhtamate jalgratta- ja jooksuradade leidmiseks.

[Nutikad elektrivõrgud](https://wikipedia.org/wiki/Smart_grid) võimaldavad paremat analüüsi elektritarbimise kohta, kogudes kasutusandmeid üksikute kodude tasemel. Need andmed võivad suunata otsuseid riiklikul tasandil, sealhulgas kuhu ehitada uusi elektrijaamu, ja isiklikul tasandil, andes kasutajatele ülevaate nende elektritarbimisest, millal nad elektrit kasutavad ja isegi soovitusi kulude vähendamiseks, näiteks elektriautode laadimine öösel.

✅ Kui saaksite lisada IoT-seadmeid, et mõõta midagi oma elukohas, siis mida te mõõdaksite?

## Näited IoT-seadmetest, mis võivad teie ümber olla

Te oleksite üllatunud, kui palju IoT-seadmeid teie ümber on. Kirjutan seda kodus ja mul on järgmised seadmed, mis on Internetiga ühendatud ja millel on nutikad funktsioonid, nagu rakenduse juhtimine, hääljuhtimine või võime saata andmeid minu telefoni kaudu:

* Mitu nutikõlarit
* Külmkapp, nõudepesumasin, ahi ja mikrolaineahi
* Elektrimonitor päikesepaneelide jaoks
* Nutipistikud
* Videokell ja turvakaamerad
* Nutikas termostaat mitme nutika ruumianduriga
* Garažiukse avaja
* Kodused meelelahutussüsteemid ja hääljuhtimisega telerid
* Tuled
* Fitnessi- ja tervisemonitorid

Kõik need seadmed sisaldavad andureid ja/või täiturmehhanisme ning suhtlevad Interneti kaudu. Ma saan oma telefonist teada, kas mu garaažiuks on avatud, ja paluda oma nutikõlaril see sulgeda. Ma saan isegi seadistada taimeri, et kui see on öösel endiselt avatud, sulguks see automaatselt. Kui mu uksekell heliseb, saan oma telefonist näha, kes seal on, olenemata sellest, kus ma maailmas viibin, ja rääkida nendega uksekella sisse ehitatud kõlari ja mikrofoniga. Ma saan jälgida oma veresuhkru taset, südame löögisagedust ja unemustreid, otsides andmetes mustreid, et parandada oma tervist. Ma saan pilve kaudu oma tulesid juhtida ja istuda pimedas, kui minu Interneti-ühendus katkeb.

---

## 🚀 Väljakutse

Loetlege nii palju IoT-seadmeid kui võimalik, mis on teie kodus, koolis või töökohal - neid võib olla rohkem, kui arvate!

## Loengu järgne viktoriin

[Loengu järgne viktoriin](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Ülevaade ja iseseisev õppimine

Lugege tarbijate IoT-projektide eeliste ja ebaõnnestumiste kohta. Kontrollige uudiste saite, et leida artikleid, kus on midagi valesti läinud, näiteks privaatsusprobleemid, riistvaraprobleemid või probleemid, mis on põhjustatud ühenduse puudumisest.

Mõned näited:

* Vaadake Twitteri kontot **[Internet of Sh*t](https://twitter.com/internetofshit)** *(roppuste hoiatus)*, et leida häid näiteid tarbijate IoT ebaõnnestumistest.
* [c|net - Minu Apple Watch päästis mu elu: 5 inimest jagavad oma lugusid](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - ADT tehnik tunnistab end süüdi klientide kaameravoogude jälgimises aastaid](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(hoiatuse märkus - mitte konsensuslik vojeerism)*

## Ülesanne

[Uurige IoT-projekti](assignment.md)

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.