# Sledenje lokaciji

![Skica pregleda te lekcije](../../../../../translated_images/sl/lesson-11.9fddbac4b664c6d5.webp)

> Skico je pripravila [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliko za večjo različico.

## Kviz pred predavanjem

[Kviz pred predavanjem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Uvod

Glavni proces dostave hrane od kmeta do potrošnika vključuje nalaganje zabojev s pridelki na tovornjake, ladje, letala ali druga komercialna transportna vozila ter dostavo hrane na določeno mesto – bodisi neposredno stranki bodisi v centralno skladišče za nadaljnjo obdelavo. Celoten proces od kmetije do potrošnika je del procesa, imenovanega *oskrbovalna veriga*. Spodnji video iz W. P. Carey School of Business na Univerzi Arizona State podrobneje razlaga koncept oskrbovalne verige in njenega upravljanja.

[![Kaj je upravljanje oskrbovalne verige? Video iz W. P. Carey School of Business na Univerzi Arizona State](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Kliknite na zgornjo sliko za ogled videa

Dodajanje IoT naprav lahko bistveno izboljša vašo oskrbovalno verigo, saj omogoča boljše upravljanje lokacije predmetov, načrtovanje transporta in ravnanja z blagom ter hitrejše odzivanje na težave.

Pri upravljanju flote vozil, kot so tovornjaki, je koristno vedeti, kje se posamezno vozilo nahaja v določenem trenutku. Vozila lahko opremimo z GPS senzorji, ki pošiljajo svojo lokacijo v IoT sisteme, kar omogoča lastnikom, da natančno določijo njihovo lokacijo, vidijo prevoženo pot in vedo, kdaj bodo prispela na cilj. Večina vozil deluje zunaj območja WiFi omrežij, zato za pošiljanje teh podatkov uporabljajo mobilna omrežja. Včasih je GPS senzor vgrajen v bolj kompleksne IoT naprave, kot so elektronske knjige voženj. Te naprave spremljajo, kako dolgo je tovornjak na poti, da zagotovijo skladnost voznikov z lokalnimi zakoni o delovnem času.

V tej lekciji se boste naučili, kako slediti lokaciji vozila z uporabo senzorja Globalnega sistema za določanje položaja (GPS).

V tej lekciji bomo obravnavali:

* [Povezana vozila](../../../../../3-transport/lessons/1-location-tracking)
* [Geoprostorske koordinate](../../../../../3-transport/lessons/1-location-tracking)
* [Globalni sistemi za določanje položaja (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [Branje podatkov GPS senzorja](../../../../../3-transport/lessons/1-location-tracking)
* [NMEA GPS podatki](../../../../../3-transport/lessons/1-location-tracking)
* [Dekodiranje podatkov GPS senzorja](../../../../../3-transport/lessons/1-location-tracking)

## Povezana vozila

IoT spreminja način prevoza blaga z ustvarjanjem flot *povezanih vozil*. Ta vozila so povezana s centralnimi IT sistemi, ki poročajo o njihovi lokaciji in drugih podatkih senzorjev. Imeti floto povezanih vozil prinaša številne prednosti:

* Sledenje lokaciji – omogoča natančno določitev, kje se vozilo nahaja v vsakem trenutku, kar omogoča:

  * Prejemanje obvestil, ko je vozilo tik pred prihodom na cilj, da se pripravi ekipa za razkladanje
  * Iskanje ukradenih vozil
  * Kombiniranje podatkov o lokaciji in poti s prometnimi težavami za preusmeritev vozil med potjo
  * Skladnost z davki. Nekatere države zaračunavajo vozilom glede na prevožene kilometre po javnih cestah (na primer [novozelandski RUC](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), zato je poznavanje, kdaj je vozilo na javnih cestah v primerjavi z zasebnimi, koristno za izračun dolžnega davka.
  * Pošiljanje vzdrževalnih ekip na pravo mesto v primeru okvare

* Telemetrija voznika – zagotavljanje, da vozniki upoštevajo omejitve hitrosti, zavijajo pri ustreznih hitrostih, zavirajo pravočasno in učinkovito ter vozijo varno. Povezana vozila lahko vključujejo tudi kamere za snemanje incidentov. To je lahko povezano z zavarovanjem, kar omogoča nižje premije za dobre voznike.

* Skladnost z delovnimi urami voznikov – zagotavljanje, da vozniki vozijo le v zakonsko dovoljenem času glede na čas, ko vklopijo in izklopijo motor.

Te prednosti je mogoče kombinirati – na primer, kombiniranje skladnosti z delovnimi urami voznikov in sledenja lokaciji za preusmeritev voznikov, če ne morejo doseči cilja v dovoljenem času vožnje. To je mogoče kombinirati tudi z drugimi specifičnimi telemetrijskimi podatki vozila, kot so podatki o temperaturi iz tovornjakov s temperaturnim nadzorom, kar omogoča preusmeritev vozil, če trenutna pot pomeni, da blaga ni mogoče ohraniti pri ustrezni temperaturi.

> 🎓 Logistika je proces prevoza blaga z enega kraja na drugega, na primer s kmetije v supermarket prek enega ali več skladišč. Kmet zapakira zaboje s paradižniki, ki jih naložijo na tovornjak, dostavijo v centralno skladišče in nato naložijo na drugi tovornjak, ki lahko vsebuje mešanico različnih vrst pridelkov, ki jih nato dostavijo v supermarket.

Osrednja komponenta sledenja vozilom je GPS – senzorji, ki lahko določijo svojo lokacijo kjerkoli na Zemlji. V tej lekciji se boste naučili uporabljati GPS senzor, začenši z učenjem, kako definirati lokacijo na Zemlji.

## Geoprostorske koordinate

Geoprostorske koordinate se uporabljajo za določanje točk na površju Zemlje, podobno kot se koordinate uporabljajo za risanje piksla na računalniškem zaslonu ali pozicioniranje šivov pri vezenju. Za eno točko imate par koordinat. Na primer, Microsoftov kampus v Redmondu, Washington, ZDA, se nahaja na 47.6423109, -122.1390293.

### Geografska širina in dolžina

Zemlja je krogla – tridimenzionalni krog. Zaradi tega so točke definirane z delitvijo na 360 stopinj, kar ustreza geometriji krogov. Geografska širina meri število stopinj od severa proti jugu, geografska dolžina pa meri število stopinj od vzhoda proti zahodu.

> 💁 Nihče ne ve natančno, zakaj so krogi razdeljeni na 360 stopinj. [Stran o stopinjah (kot) na Wikipediji](https://wikipedia.org/wiki/Degree_(angle)) pokriva nekaj možnih razlogov.

![Črte geografske širine od 90° na severnem polu, 45° na polovici med severnim polom in ekvatorjem, 0° na ekvatorju, -45° na polovici med ekvatorjem in južnim polom ter -90° na južnem polu](../../../../../translated_images/sl/latitude-lines.11d8d91dfb2014a5.webp)

Geografska širina se meri z linijami, ki obkrožajo Zemljo in tečejo vzporedno z ekvatorjem, delijo severno in južno poloblo na po 90°. Ekvator je na 0°, severni pol na 90°, znan tudi kot 90° severno, južni pol pa na -90°, ali 90° južno.

Geografska dolžina se meri kot število stopinj vzhodno in zahodno. Izvor 0° geografske dolžine se imenuje *prvi poldnevnik* in je bil leta 1884 določen kot črta od severnega do južnega pola, ki poteka skozi [Kraljevi observatorij v Greenwichu, Anglija](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Črte geografske dolžine, ki segajo od -180° zahodno od prvega poldnevnika, do 0° na prvem poldnevniku, do 180° vzhodno od prvega poldnevnika](../../../../../translated_images/sl/longitude-meridians.ab4ef1c91c064586.webp)

> 🎓 Poldnevnik je namišljena ravna črta, ki poteka od severnega do južnega pola in tvori polkrog.

Za merjenje geografske dolžine točke izmerite število stopinj okoli ekvatorja od prvega poldnevnika do poldnevnika, ki prehaja skozi to točko. Geografska dolžina sega od -180°, ali 180° zahodno, skozi 0° na prvem poldnevniku, do 180°, ali 180° vzhodno. 180° in -180° se nanašata na isto točko, antimeridian ali 180. poldnevnik. To je poldnevnik na nasprotni strani Zemlje od prvega poldnevnika.

> 💁 Antimeridian ne smemo zamenjevati z mednarodno datumsko mejo, ki je približno na istem mestu, vendar ni ravna črta in se prilagaja geopolitičnim mejam.

✅ Raziskujte: Poskusite najti geografsko širino in dolžino svoje trenutne lokacije.

### Stopinje, minute in sekunde proti decimalnim stopinjam

Tradicionalno so se meritve stopinj geografske širine in dolžine izvajale s seksagezimalnim številčenjem ali osnovo 60, številčnim sistemom, ki so ga uporabljali stari Babilonci, ki so prvi merili in beležili čas in razdaljo. Seksagezimalni sistem uporabljate vsak dan, verjetno ne da bi se tega zavedali – delitev ur na 60 minut in minut na 60 sekund.

Geografska dolžina in širina se merita v stopinjah, minutah in sekundah, pri čemer je ena minuta 1/60 stopinje, ena sekunda pa 1/60 minute.

Na primer, na ekvatorju:

* 1° geografske širine je **111,3 kilometra**
* 1 minuta geografske širine je 111,3/60 = **1,855 kilometra**
* 1 sekunda geografske širine je 1,855/60 = **0,031 kilometra**

Simbol za minuto je enojni narekovaj, za sekundo pa dvojni narekovaj. Na primer, 2 stopinji, 17 minut in 43 sekund bi zapisali kot 2°17'43". Deli sekund so podani kot decimalke, na primer pol sekunde je 0°0'0,5".

Računalniki ne delujejo v osnovi 60, zato so te koordinate podane kot decimalne stopinje pri uporabi GPS podatkov v večini računalniških sistemov. Na primer, 2°17'43" je 2,295277. Simbol za stopinje je običajno izpuščen.

Koordinate za točko so vedno podane kot `geografska širina, geografska dolžina`, tako da ima prej omenjeni primer Microsoftovega kampusa na 47.6423109,-122.117198:

* Geografsko širino 47.6423109 (47.6423109 stopinj severno od ekvatorja)
* Geografsko dolžino -122.1390293 (122.1390293 stopinj zahodno od prvega poldnevnika).

![Microsoftov kampus na 47.6423109,-122.117198](../../../../../translated_images/sl/microsoft-gps-location-world.a321d481b010f6ad.webp)

## Globalni sistemi za določanje položaja (GPS)

GPS sistemi uporabljajo več satelitov, ki krožijo okoli Zemlje, za določanje vaše lokacije. Verjetno ste že uporabljali GPS sisteme, ne da bi se tega zavedali – za iskanje svoje lokacije v aplikaciji za zemljevide na telefonu, kot sta Apple Maps ali Google Maps, za spremljanje, kje je vaše naročeno prevozno sredstvo v aplikaciji, kot je Uber, ali pri uporabi satelitske navigacije (sat-nav) v avtomobilu.

> 🎓 Sateliti v 'satelitski navigaciji' so GPS sateliti!

GPS sistemi delujejo tako, da imajo več satelitov, ki pošiljajo signal s trenutno lokacijo vsakega satelita in natančnim časovnim žigom. Ti signali se pošiljajo prek radijskih valov in jih zazna antena v GPS senzorju. GPS senzor zazna te signale in z uporabo trenutnega časa izmeri, koliko časa je trajalo, da je signal prišel od satelita do senzorja. Ker je hitrost radijskih valov konstantna, lahko GPS senzor uporabi poslani časovni žig za izračun, kako daleč je senzor od satelita. Z združevanjem podatkov vsaj treh satelitov in njihovih poslanih lokacij lahko GPS senzor natančno določi svojo lokacijo na Zemlji.

> 💁 GPS senzorji potrebujejo antene za zaznavanje radijskih valov. Antene, vgrajene v tovornjake in avtomobile z vgrajenim GPS-om, so nameščene tako, da dobijo dober signal, običajno na vetrobranskem steklu ali strehi. Če uporabljate ločen GPS sistem, kot je pametni telefon ali IoT naprava, morate zagotoviti, da ima antena, vgrajena v GPS sistem ali telefon, jasen pogled na nebo, na primer, da je nameščena na vetrobranskem steklu.

![Z poznavanjem razdalje od senzorja do več satelitov je mogoče izračunati lokacijo](../../../../../translated_images/sl/gps-satellites.04acf1148fe25fbf.webp)

GPS sateliti krožijo okoli Zemlje in niso na fiksni točki nad senzorjem, zato podatki o lokaciji vključujejo tudi nadmorsko višino poleg geografske širine in dolžine.

GPS je imel v preteklosti omejitve natančnosti, ki jih je uvedla ameriška vojska, kar je omejevalo natančnost na približno 5 metrov. Ta omejitev je bila leta 2000 odstranjena, kar omogoča natančnost do 30 centimetrov. Doseganje te natančnosti ni vedno mogoče zaradi motenj signalov.

✅ Če imate pametni telefon, odprite aplikacijo za zemljevide in preverite, kako natančna je vaša lokacija. Morda bo trajalo nekaj časa, da vaš telefon zazna več satelitov za bolj natančno lokacijo.
💁 Sateliti vsebujejo atomske ure, ki so izjemno natančne, vendar se v primerjavi z atomskimi urami na Zemlji vsak dan odmikajo za 38 mikrosekund (0,0000038 sekunde). To je posledica upočasnjevanja časa, ko se hitrost povečuje, kot napovedujejo Einsteinove teorije posebne in splošne relativnosti – sateliti se gibljejo hitreje kot rotacija Zemlje. Ta odmik je bil uporabljen za potrditev napovedi posebne in splošne relativnosti in ga je treba upoštevati pri načrtovanju GPS sistemov. Dobesedno čas na GPS satelitu teče počasneje.
GPS sistemi so bili razviti in uvedeni v številnih državah in političnih unijah, vključno z ZDA, Rusijo, Japonsko, Indijo, EU in Kitajsko. Sodobni GPS senzorji se lahko povežejo z večino teh sistemov, da pridobijo hitrejše in natančnejše podatke.

> 🎓 Skupine satelitov v posameznih sistemih se imenujejo konstelacije.

## Branje podatkov GPS senzorja

Večina GPS senzorjev pošilja podatke prek UART.

> ⚠️ UART je bil obravnavan v [projektu 2, lekcija 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Po potrebi se vrnite k tej lekciji.

GPS senzor lahko uporabite na svoji IoT napravi za pridobivanje GPS podatkov.

### Naloga - povežite GPS senzor in preberite GPS podatke

Sledite ustreznemu vodiču za branje GPS podatkov z vašo IoT napravo:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Enočipni računalnik - Raspberry Pi](pi-gps-sensor.md)
* [Enočipni računalnik - Virtualna naprava](virtual-device-gps-sensor.md)

## NMEA GPS podatki

Ko zaženete svojo kodo, boste morda opazili, da se v izhodu pojavi nekaj, kar na prvi pogled izgleda kot nesmisel. To so pravzaprav standardni GPS podatki, ki imajo svoj pomen.

GPS senzorji pošiljajo podatke z uporabo NMEA sporočil, skladno s standardom NMEA 0183. NMEA je kratica za [National Marine Electronics Association](https://www.nmea.org), ameriško trgovsko organizacijo, ki določa standarde za komunikacijo med pomorskimi elektronskimi napravami.

> 💁 Ta standard je lastniški in stane vsaj 2.000 USD, vendar je dovolj informacij o njem v javni domeni, da je bil večji del standarda razčlenjen in se lahko uporablja v odprtokodni in drugi nekomercialni kodi.

Ta sporočila so besedilna. Vsako sporočilo je sestavljeno iz *stavka*, ki se začne z znakom `$`, sledi 2 znaka za označitev vira sporočila (npr. GP za ameriški GPS sistem, GN za GLONASS, ruski GPS sistem) in 3 znaki za označitev vrste sporočila. Preostanek sporočila so polja, ločena z vejicami, ki se končajo z znakom za novo vrstico.

Nekatere vrste sporočil, ki jih lahko prejmete, so:

| Vrsta | Opis |
| ---- | ----------- |
| GGA | Podatki o GPS lokaciji, vključno z zemljepisno širino, dolžino in nadmorsko višino GPS senzorja ter številom satelitov, ki so na voljo za izračun te lokacije. |
| ZDA | Trenutni datum in čas, vključno z lokalnim časovnim pasom. |
| GSV | Podrobnosti o satelitih, ki so vidni - definirani kot sateliti, od katerih GPS senzor lahko zazna signale. |

> 💁 GPS podatki vključujejo časovne žige, zato lahko vaša IoT naprava pridobi čas iz GPS senzorja, namesto da se zanaša na NTP strežnik ali notranjo realno-časovno uro.

Sporočilo GGA vključuje trenutno lokacijo v formatu `(dd)dmm.mmmm`, skupaj z enim znakom za označitev smeri. `d` v formatu predstavlja stopinje, `m` minute, sekunde pa so podane kot decimalke minut. Na primer, 2°17'43" bi bilo 217.716666667 - 2 stopinji, 17.716666667 minut.

Znak za smer je lahko `N` ali `S` za zemljepisno širino, kar označuje sever ali jug, ter `E` ali `W` za zemljepisno dolžino, kar označuje vzhod ali zahod. Na primer, zemljepisna širina 2°17'43" bi imela znak za smer `N`, -2°17'43" pa znak `S`.

Na primer - NMEA stavek `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* Del za zemljepisno širino je `4738.538654,N`, kar se pretvori v 47.6423109 v decimalnih stopinjah. `4738.538654` je 47.6423109, smer pa je `N` (sever), kar pomeni pozitivno zemljepisno širino.

* Del za zemljepisno dolžino je `12208.341758,W`, kar se pretvori v -122.1390293 v decimalnih stopinjah. `12208.341758` je 122.1390293°, smer pa je `W` (zahod), kar pomeni negativno zemljepisno dolžino.

## Dekodiranje podatkov GPS senzorja

Namesto uporabe surovih NMEA podatkov je bolje, da jih dekodirate v bolj uporaben format. Obstaja več odprtokodnih knjižnic, ki vam lahko pomagajo pri pridobivanju uporabnih podatkov iz surovih NMEA sporočil.

### Naloga - dekodirajte podatke GPS senzorja

Sledite ustreznemu vodiču za dekodiranje podatkov GPS senzorja z vašo IoT napravo:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Enočipni računalnik - Raspberry Pi/Virtualna IoT naprava](single-board-computer-gps-decode.md)

---

## 🚀 Izziv

Napišite svoj NMEA dekoder! Namesto da se zanašate na knjižnice tretjih oseb za dekodiranje NMEA stavkov, ali lahko napišete svoj dekoder za pridobivanje zemljepisne širine in dolžine iz NMEA stavkov?

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Pregled in samostojno učenje

* Preberite več o geolokacijskih koordinatah na [strani o geografskem koordinatnem sistemu na Wikipediji](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Preberite o glavnih poldnevnikih na drugih nebesnih telesih poleg Zemlje na [strani o glavnem poldnevniku na Wikipediji](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies).
* Raziskujte različne GPS sisteme različnih svetovnih vlad in političnih unij, kot so EU, Japonska, Rusija, Indija in ZDA.

## Naloga

[Raziskujte druge GPS podatke](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni prevod s strani človeka. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.