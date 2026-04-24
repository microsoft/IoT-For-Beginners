# Uvod v IoT

![Sketchnote pregled te lekcije](../../../../../translated_images/sl/lesson-1.2606670fa61ee904.webp)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliko za večjo različico.

Ta lekcija je bila del serije [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) iz [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekcija je bila izvedena v dveh videih - enourni lekciji in enourni pisarniški uri, kjer so podrobneje obravnavali dele lekcije ter odgovarjali na vprašanja.

[![Lekcija 1: Uvod v IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Lekcija 1: Uvod v IoT - Pisarniške ure](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Kliknite na zgornje slike za ogled videov

## Kviz pred predavanjem

[Kviz pred predavanjem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Uvod

Ta lekcija obravnava nekatere uvodne teme o Internetu stvari (IoT) in vas vodi skozi postopek nastavitve vaše strojne opreme.

V tej lekciji bomo obravnavali:

* [Kaj je 'Internet stvari'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT naprave](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Nastavitev vaše naprave](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Uporaba IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Primeri IoT naprav okoli vas](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Kaj je 'Internet stvari'?

Izraz 'Internet stvari' je leta 1999 skoval [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton), da bi opisal povezovanje interneta s fizičnim svetom prek senzorjev. Od takrat se izraz uporablja za opis katere koli naprave, ki komunicira s fizičnim svetom okoli sebe, bodisi z zbiranjem podatkov prek senzorjev ali z zagotavljanjem interakcij v resničnem svetu prek aktuatorjev (naprav, ki izvajajo dejanja, kot so vklop stikala ali prižig LED luči), običajno povezanih z drugimi napravami ali internetom.

> **Senzorji** zbirajo informacije iz sveta, kot so merjenje hitrosti, temperature ali lokacije.
>
> **Aktuatorji** pretvarjajo električne signale v interakcije v resničnem svetu, kot so sprožitev stikala, prižiganje luči, ustvarjanje zvokov ali pošiljanje kontrolnih signalov drugim napravam, na primer za vklop električne vtičnice.

IoT kot tehnološko področje vključuje več kot le naprave - vključuje storitve v oblaku, ki lahko obdelujejo podatke senzorjev ali pošiljajo zahteve aktuatorjem, povezanim z IoT napravami. Vključuje tudi naprave, ki nimajo ali ne potrebujejo internetne povezljivosti, pogosto imenovane robne naprave. To so naprave, ki lahko same obdelujejo in se odzivajo na podatke senzorjev, običajno z uporabo AI modelov, usposobljenih v oblaku.

IoT je hitro rastoče tehnološko področje. Ocenjuje se, da je bilo do konca leta 2020 na internet povezanih 30 milijard IoT naprav. V prihodnosti se ocenjuje, da bodo do leta 2025 IoT naprave zbirale skoraj 80 zettabajtov podatkov ali 80 bilijonov gigabajtov. To je ogromno podatkov!

![Graf, ki prikazuje aktivne IoT naprave skozi čas, z naraščajočim trendom od manj kot 5 milijard v letu 2015 do več kot 30 milijard v letu 2025](../../../../../images/connected-iot-devices.svg)

✅ Raziskujte: Koliko podatkov, ki jih ustvarijo IoT naprave, se dejansko uporabi in koliko se jih zavrže? Zakaj se toliko podatkov ignorira?

Ti podatki so ključ do uspeha IoT. Da bi bili uspešen IoT razvijalec, morate razumeti, katere podatke morate zbrati, kako jih zbrati, kako sprejemati odločitve na podlagi teh podatkov in kako te odločitve uporabiti za interakcijo s fizičnim svetom, če je to potrebno.

## IoT naprave

**T** v IoT pomeni **Things** (stvari) - naprave, ki komunicirajo s fizičnim svetom okoli sebe bodisi z zbiranjem podatkov prek senzorjev bodisi z zagotavljanjem interakcij v resničnem svetu prek aktuatorjev.

Naprave za proizvodnjo ali komercialno uporabo, kot so potrošniške naprave za spremljanje telesne pripravljenosti ali industrijski krmilniki strojev, so običajno izdelane po meri. Uporabljajo prilagojene vezja, morda celo prilagojene procesorje, zasnovane za izpolnjevanje potreb določenega opravila, bodisi da so dovolj majhne, da se prilegajo na zapestje, bodisi dovolj robustne, da delujejo v visokotemperaturnem, stresnem ali vibracijskem okolju tovarne.

Kot razvijalec, ki se uči o IoT ali ustvarja prototip naprave, boste morali začeti z razvojnim kompletom. To so vsestranske IoT naprave, zasnovane za uporabo razvijalcev, pogosto z lastnostmi, ki jih ne bi imeli na proizvodni napravi, kot so zunanji priključki za povezovanje senzorjev ali aktuatorjev, strojna oprema za podporo odpravljanju napak ali dodatni viri, ki bi pri velikih proizvodnih serijah povzročili nepotrebne stroške.

Ti razvojni kompleti običajno spadajo v dve kategoriji - mikrokrmilniki in enobočne računalnike. Tukaj bodo predstavljeni, v naslednji lekciji pa bomo šli v podrobnosti.

> 💁 Vaš telefon lahko štejemo tudi za vsestransko IoT napravo, saj ima vgrajene senzorje in aktuatorje, različne aplikacije pa uporabljajo te senzorje in aktuatorje na različne načine z različnimi storitvami v oblaku. Najdete lahko celo nekaj IoT vaj, ki uporabljajo aplikacijo za telefon kot IoT napravo.

### Mikrokrmilniki

Mikrokrmilnik (pogosto imenovan MCU, kratica za mikrokrmilniško enoto) je majhen računalnik, ki vsebuje:

🧠 Enega ali več centralnih procesnih enot (CPU) - 'možgane' mikrokrmilnika, ki izvajajo vaš program

💾 Pomnilnik (RAM in programski pomnilnik) - kjer so shranjeni vaš program, podatki in spremenljivke

🔌 Programabilne vhodno/izhodne (I/O) povezave - za komunikacijo z zunanjimi napravami (povezanimi napravami), kot so senzorji in aktuatorji

Mikrokrmilniki so običajno nizkocenovne računalniške naprave, pri čemer povprečne cene tistih, ki se uporabljajo v prilagojeni strojni opremi, padajo na približno 0,50 USD, nekatere naprave pa so poceni kot 0,03 USD. Razvojni kompleti se začnejo pri približno 4 USD, stroški pa naraščajo z dodajanjem več funkcij. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), mikrokrmilniški razvojni komplet iz [Seeed studios](https://www.seeedstudio.com), ki ima senzorje, aktuatorje, WiFi in zaslon, stane približno 30 USD.

![Wio Terminal](../../../../../translated_images/sl/wio-terminal.b8299ee16587db9a.webp)

> 💁 Pri iskanju mikrokrmilnikov na internetu bodite previdni pri iskanju izraza **MCU**, saj bo to prineslo veliko rezultatov za Marvel Cinematic Universe, ne pa mikrokrmilnikov.

Mikrokrmilniki so zasnovani za programiranje za izvajanje omejenega števila zelo specifičnih nalog, namesto da bi bili vsestranski računalniki, kot so osebni računalniki ali Maci. Razen v zelo specifičnih scenarijih ne morete priključiti monitorja, tipkovnice in miške ter jih uporabljati za splošne naloge.

Razvojni kompleti mikrokrmilnikov običajno vključujejo dodatne senzorje in aktuatorje na plošči. Večina plošč ima enega ali več LED, ki jih lahko programirate, skupaj z drugimi napravami, kot so standardni priključki za dodajanje več senzorjev ali aktuatorjev z uporabo različnih ekosistemov proizvajalcev ali vgrajenih senzorjev (običajno najbolj priljubljenih, kot so temperaturni senzorji). Nekateri mikrokrmilniki imajo vgrajeno brezžično povezljivost, kot sta Bluetooth ali WiFi, ali pa imajo na plošči dodatne mikrokrmilnike za dodajanje te povezljivosti.

> 💁 Mikrokrmilniki se običajno programirajo v C/C++.

### Enobočni računalniki

Enobočni računalnik je majhna računalniška naprava, ki ima vse elemente popolnega računalnika na eni majhni plošči. To so naprave, ki imajo specifikacije, podobne namiznemu ali prenosnemu računalniku PC ali Mac, poganjajo celoten operacijski sistem, vendar so majhne, porabijo manj energije in so bistveno cenejše.

![Raspberry Pi 4](../../../../../translated_images/sl/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi je eden najbolj priljubljenih enobočnih računalnikov.

Tako kot mikrokrmilnik ima enobočni računalnik CPU, pomnilnik in vhodno/izhodne priključke, vendar ima dodatne funkcije, kot je grafični čip za povezovanje monitorjev, zvočne izhode in USB priključke za povezovanje tipkovnic, mišk in drugih standardnih USB naprav, kot so spletne kamere ali zunanji pomnilniki. Programi so shranjeni na SD karticah ali trdih diskih skupaj z operacijskim sistemom, namesto na pomnilniškem čipu, vgrajenem v ploščo.

> 🎓 Enobočni računalnik si lahko predstavljate kot manjšo, cenejšo različico osebnega računalnika ali Maca, na katerem to berete, z dodatkom GPIO (splošnih vhodno/izhodnih) priključkov za interakcijo s senzorji in aktuatorji.

Enobočni računalniki so popolnoma opremljeni računalniki, zato jih je mogoče programirati v katerem koli jeziku. IoT naprave so običajno programirane v Pythonu.

### Izbira strojne opreme za preostale lekcije

Vse nadaljnje lekcije vključujejo naloge z uporabo IoT naprave za interakcijo s fizičnim svetom in komunikacijo z oblakom. Vsaka lekcija podpira 3 izbire naprav - Arduino (z uporabo Seeed Studios Wio Terminal), ali enobočni računalnik, bodisi fizično napravo (Raspberry Pi 4) ali virtualni enobočni računalnik, ki deluje na vašem PC ali Macu.

O strojni opremi, potrebni za dokončanje vseh nalog, lahko preberete v [vodniku po strojni opremi](../../../hardware.md).

> 💁 Za dokončanje nalog vam ni treba kupiti nobene IoT strojne opreme, vse lahko opravite z uporabo virtualnega enobočnega računalnika.

Izbira strojne opreme je odvisna od tega, kaj imate na voljo doma ali v šoli, ter od programskega jezika, ki ga poznate ali se ga nameravate naučiti. Obe različici strojne opreme bosta uporabljali isti ekosistem senzorjev, zato lahko preklopite med njima, ne da bi morali zamenjati večino kompleta. Virtualni enobočni računalnik bo enakovreden učenju na Raspberry Pi, večina kode pa bo prenosljiva na Pi, če boste kasneje pridobili napravo in senzorje.

### Arduino razvojni komplet

Če vas zanima razvoj mikrokrmilnikov, lahko naloge dokončate z uporabo Arduino naprave. Potrebovali boste osnovno razumevanje programiranja v C/C++, saj bodo lekcije učile le kodo, ki je relevantna za Arduino okvir, uporabljene senzorje in aktuatorje ter knjižnice, ki komunicirajo z oblakom.

Naloge bodo uporabljale [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) z razširitvijo [PlatformIO za razvoj mikrokrmilnikov](https://platformio.org). Če ste izkušeni z Arduino IDE, ga lahko uporabite, saj navodila ne bodo podana.

### Razvojni komplet enobočnega računalnika

Če vas zanima razvoj IoT z uporabo enobočnih računalnikov, lahko naloge dokončate z uporabo Raspberry Pi ali virtualne naprave, ki deluje na vašem PC ali Macu.

Potrebovali boste osnovno razumevanje programiranja v Pythonu, saj bodo lekcije učile le kodo, ki je relevantna za uporabljene senzorje in aktuatorje ter knjižnice, ki komunicirajo z oblakom.

> 💁 Če se želite naučiti programiranja v Pythonu, si oglejte naslednji dve seriji videov:
>
> * [Python za začetnike](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Več Python za začetnike](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Naloge bodo uporabljale [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Če uporabljate Raspberry Pi, lahko svoj Pi zaženete z uporabo polne namizne različice Raspberry Pi OS in vso kodo napišete neposredno na Pi z uporabo [različice VS Code za Raspberry Pi OS](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), ali pa svoj Pi zaženete kot napravo brez zaslona in kodo napišete na svojem PC ali Macu z uporabo VS Code z razširitvijo [Remote SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), ki vam omogoča povezavo s Pi in urejanje, odpravljanje napak ter izvajanje kode, kot da bi jo pisali neposredno na njem.

Če uporabljate možnost virtualne naprave, boste kodo napisali neposredno na svojem računalniku. Namesto dostopa do senzorjev in aktuatorjev boste uporabili orodje za simulacijo te strojne opreme, ki omogoča določanje vrednosti senzorjev in prikaz rezultatov aktuatorjev na zaslonu.

## Nastavitev vaše naprave

Preden začnete s programiranjem svoje IoT naprave, boste morali opraviti nekaj osnovne nastavitve. Sledite ustreznim navodilom glede na napravo, ki jo boste uporabljali.
💁 Če še nimate naprave, si oglejte [vodnik za strojno opremo](../../../hardware.md), ki vam bo pomagal izbrati napravo, ki jo boste uporabljali, in dodatno strojno opremo, ki jo morate kupiti. Nakup strojne opreme ni potreben, saj lahko vse projekte izvajate na virtualni strojni opremi.
Te navodila vključujejo povezave do spletnih strani tretjih oseb, ki jih ustvarjalci strojne opreme ali orodij, ki jih boste uporabljali, zagotavljajo. To je zato, da zagotovimo, da vedno uporabljate najnovejša navodila za različna orodja in strojno opremo.

Sledite ustreznemu vodiču, da nastavite svojo napravo in dokončate projekt 'Hello World'. To bo prvi korak pri ustvarjanju IoT nočne lučke v štirih lekcijah tega uvodnega dela.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Enočipni računalnik - Raspberry Pi](pi.md)
* [Enočipni računalnik - Virtualna naprava](virtual-device.md)

✅ Za Arduino in enočipne računalnike boste uporabljali VS Code. Če ga še niste uporabljali, preberite več o njem na [spletni strani VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## Uporaba IoT

IoT pokriva širok spekter primerov uporabe, razdeljenih v nekaj glavnih skupin:

* Potrošniški IoT
* Komercialni IoT
* Industrijski IoT
* Infrastrukturni IoT

✅ Malo raziskujte: Za vsako od spodaj opisanih področij poiščite en konkreten primer, ki ni naveden v besedilu.

### Potrošniški IoT

Potrošniški IoT se nanaša na IoT naprave, ki jih potrošniki kupijo in uporabljajo doma. Nekatere od teh naprav so izjemno uporabne, kot so pametni zvočniki, pametni ogrevalni sistemi in robotski sesalniki. Druge pa so vprašljive glede svoje uporabnosti, kot so pipe na glasovno upravljanje, ki jih nato ne morete izklopiti, ker glasovno upravljanje ne sliši vašega ukaza zaradi zvoka tekoče vode.

Potrošniške IoT naprave omogočajo ljudem, da dosežejo več v svojem okolju, zlasti 1 milijardi ljudi z invalidnostjo. Robotski sesalniki lahko zagotovijo čista tla ljudem z omejeno mobilnostjo, ki sami ne morejo sesati, pečice na glasovno upravljanje omogočajo ljudem z omejenim vidom ali motoričnimi sposobnostmi, da segrejejo pečico samo z glasom, zdravstveni monitorji pa omogočajo pacientom, da sami spremljajo kronične bolezni z bolj rednimi in podrobnimi posodobitvami o svojem stanju. Te naprave postajajo tako razširjene, da jih uporabljajo celo majhni otroci kot del svojega vsakdanjega življenja, na primer učenci, ki med pandemijo COVID opravljajo virtualno šolanje, nastavijo časovnike na pametnih domačih napravah za spremljanje šolskih nalog ali alarme za opomnike na prihajajoče sestanke razreda.

✅ Katere potrošniške IoT naprave imate pri sebi ali doma?

### Komercialni IoT

Komercialni IoT zajema uporabo IoT v delovnem okolju. V pisarniškem okolju so lahko senzorji za zaznavanje prisotnosti in gibanja, ki upravljajo osvetlitev in ogrevanje, da so luči in toplota prižgani le takrat, ko so potrebni, kar zmanjšuje stroške in emisije ogljika. V tovarni lahko IoT naprave spremljajo varnostne nevarnosti, kot so delavci brez čelad ali hrup, ki doseže nevarne ravni. V trgovini lahko IoT naprave merijo temperaturo hladilnih naprav in opozarjajo lastnika trgovine, če hladilnik ali zamrzovalnik presega zahtevano temperaturno območje, ali pa spremljajo izdelke na policah in usmerjajo zaposlene, da dopolnijo prodane izdelke. Transportna industrija se vse bolj zanaša na IoT za spremljanje lokacij vozil, sledenje prevoženih kilometrov za cestne uporabniške takse, spremljanje delovnih ur voznikov in skladnosti z odmori ali obveščanje osebja, ko se vozilo približuje skladišču, da se pripravijo na nakladanje ali razkladanje.

✅ Katere komercialne IoT naprave imate v šoli ali na delovnem mestu?

### Industrijski IoT (IIoT)

Industrijski IoT ali IIoT je uporaba IoT naprav za nadzor in upravljanje strojev v velikem obsegu. To zajema širok spekter primerov uporabe, od tovarn do digitalnega kmetijstva.

Tovarne uporabljajo IoT naprave na različne načine. Stroji se lahko spremljajo z več senzorji za sledenje stvarem, kot so temperatura, vibracije in hitrost vrtenja. Te podatke je mogoče spremljati, da se stroj ustavi, če preseže določene tolerance - na primer, če se pregreje in se samodejno izklopi. Te podatke je mogoče zbirati in analizirati skozi čas za napovedno vzdrževanje, kjer modeli umetne inteligence analizirajo podatke, ki vodijo do okvare, in jih uporabijo za napovedovanje drugih okvar, preden se zgodijo.

Digitalno kmetijstvo je pomembno, če naj planet nahrani rastočo populacijo, zlasti za 2 milijardi ljudi v 500 milijonih gospodinjstev, ki preživljajo z [samooskrbnim kmetovanjem](https://wikipedia.org/wiki/Subsistence_agriculture). Digitalno kmetijstvo lahko sega od nekaj senzorjev za nekaj dolarjev do velikih komercialnih sistemov. Kmet lahko začne z merjenjem temperatur in uporabo [dnevov rasti](https://wikipedia.org/wiki/Growing_degree-day) za napoved, kdaj bo pridelek pripravljen za žetev. Lahko poveže spremljanje vlage v tleh z avtomatiziranimi namakalnimi sistemi, da svojim rastlinam zagotovi toliko vode, kot jo potrebujejo, vendar ne več, da zagotovi, da pridelki ne usahnejo, ne da bi zapravljali vodo. Kmetje gredo celo dlje in uporabljajo drone, satelitske podatke in umetno inteligenco za spremljanje rasti pridelkov, bolezni in kakovosti tal na velikih območjih kmetijskih zemljišč.

✅ Katere druge IoT naprave bi lahko pomagale kmetom?

### Infrastrukturni IoT

Infrastrukturni IoT spremlja in upravlja lokalno in globalno infrastrukturo, ki jo ljudje uporabljajo vsak dan.

[Pametna mesta](https://wikipedia.org/wiki/Smart_city) so urbana območja, ki uporabljajo IoT naprave za zbiranje podatkov o mestu in njihovo uporabo za izboljšanje delovanja mesta. Ta mesta običajno upravljajo v sodelovanju med lokalnimi vladami, akademskimi ustanovami in lokalnimi podjetji, spremljajo in upravljajo stvari, kot so transport, parkiranje in onesnaženje. Na primer, v Kopenhagnu na Danskem je onesnaženje zraka pomembno za lokalne prebivalce, zato se meri in podatki se uporabljajo za zagotavljanje informacij o najčistejših poteh za kolesarjenje in tek.

[Pametna električna omrežja](https://wikipedia.org/wiki/Smart_grid) omogočajo boljšo analitiko povpraševanja po električni energiji z zbiranjem podatkov o porabi na ravni posameznih domov. Ti podatki lahko usmerjajo odločitve na ravni države, vključno s tem, kje graditi nove elektrarne, in na osebni ravni, tako da uporabnikom ponujajo vpogled v to, koliko energije porabijo, kdaj jo porabijo, in celo predloge, kako zmanjšati stroške, na primer polnjenje električnih avtomobilov ponoči.

✅ Če bi lahko dodali IoT naprave za merjenje česar koli tam, kjer živite, kaj bi to bilo?

## Primeri IoT naprav, ki jih morda imate okoli sebe

Presenečeni boste, koliko IoT naprav imate okoli sebe. To pišem od doma in imam naslednje naprave povezane z internetom s pametnimi funkcijami, kot so upravljanje prek aplikacije, glasovno upravljanje ali možnost pošiljanja podatkov na moj telefon:

* Več pametnih zvočnikov
* Hladilnik, pomivalni stroj, pečica in mikrovalovna pečica
* Monitor električne energije za sončne panele
* Pametne vtičnice
* Video domofon in varnostne kamere
* Pametni termostat z več pametnimi senzorji za sobe
* Odpiralec garažnih vrat
* Sistemi za domačo zabavo in televizorji na glasovno upravljanje
* Luči
* Sledilniki za telesno pripravljenost in zdravje

Vse te vrste naprav imajo senzorje in/ali aktuatorje ter komunicirajo z internetom. Na telefonu lahko preverim, ali so garažna vrata odprta, in pametnemu zvočniku naročim, naj jih zapre. Lahko jih celo nastavim na časovnik, da se ponoči samodejno zaprejo, če so še odprta. Ko pozvoni domofon, lahko na telefonu vidim, kdo je tam, kjer koli sem na svetu, in se z njimi pogovarjam prek zvočnika in mikrofona, vgrajenega v domofon. Lahko spremljam svojo raven glukoze v krvi, srčni utrip in vzorce spanja ter iščem vzorce v podatkih za izboljšanje svojega zdravja. Luči lahko upravljam prek oblaka in sedim v temi, ko povezava z internetom odpove.

---

## 🚀 Izziv

Naštejte čim več IoT naprav, ki jih imate doma, v šoli ali na delovnem mestu - morda jih je več, kot si mislite!

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Pregled in samostojno učenje

Preberite o prednostih in neuspehih potrošniških IoT projektov. Preverite novice za članke o primerih, ko so šli narobe, kot so vprašanja zasebnosti, težave s strojno opremo ali težave, ki jih povzroča pomanjkanje povezljivosti.

Nekaj primerov:

* Oglejte si Twitter račun **[Internet of Sh*t](https://twitter.com/internetofshit)** *(opozorilo na neprimerno vsebino)* za nekaj dobrih primerov neuspehov pri potrošniškem IoT.
* [c|net - Moja Apple Watch mi je rešila življenje: 5 ljudi deli svoje zgodbe](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - Tehnik ADT priznal krivdo za vohunjenje prek kamer strank več let](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(opozorilo na neprimerno vsebino - neprostovoljno voajerstvo)*

## Naloga

[Raziščite IoT projekt](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne odgovarjamo za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.