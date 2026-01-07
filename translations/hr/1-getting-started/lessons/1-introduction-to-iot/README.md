<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9bae08314d8487cb76ddf3d8797e1544",
  "translation_date": "2025-08-28T13:57:07+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/README.md",
  "language_code": "hr"
}
-->
# Uvod u IoT

![Pregled lekcije u obliku sketchnotea](../../../../../translated_images/lesson-1.2606670fa61ee904687da5d6fa4e726639d524d064c895117da1b95b9ff6251d.hr.jpg)

> Sketchnote autorice [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

Ova lekcija je dio serije [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) iz [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekcija je podijeljena u dva videa - jedan sat predavanja i jedan sat dodatnih pitanja i dubljeg objašnjavanja dijelova lekcije.

[![Lekcija 1: Uvod u IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Lekcija 1: Uvod u IoT - Dodatna pitanja](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Kliknite na slike iznad za gledanje videa

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Uvod

Ova lekcija pokriva osnovne teme vezane uz Internet stvari (IoT) i pomaže vam u postavljanju vašeg hardvera.

U ovoj lekciji obradit ćemo:

* [Što je 'Internet stvari'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT uređaji](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Postavljanje vašeg uređaja](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Primjene IoT-a](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Primjeri IoT uređaja oko vas](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Što je 'Internet stvari'?

Pojam 'Internet stvari' skovao je [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) 1999. godine, kako bi opisao povezivanje Interneta s fizičkim svijetom putem senzora. Od tada, ovaj pojam se koristi za opisivanje bilo kojeg uređaja koji komunicira s fizičkim svijetom oko sebe, bilo prikupljanjem podataka putem senzora ili pružanjem interakcija u stvarnom svijetu putem aktuatora (uređaja koji obavljaju radnje poput uključivanja prekidača ili paljenja LED svjetla), obično povezanih s drugim uređajima ili Internetom.

> **Senzori** prikupljaju informacije iz svijeta, poput mjerenja brzine, temperature ili lokacije.
>
> **Aktuatori** pretvaraju električne signale u interakcije u stvarnom svijetu, poput aktiviranja prekidača, paljenja svjetla, stvaranja zvukova ili slanja kontrolnih signala drugim hardverskim uređajima, na primjer, za uključivanje utičnice.

IoT kao tehnološko područje obuhvaća više od samih uređaja - uključuje usluge u oblaku koje mogu obrađivati podatke senzora ili slati zahtjeve aktuatorima povezanim s IoT uređajima. Također uključuje uređaje koji nemaju ili ne trebaju internetsku povezanost, često nazvane rubni uređaji. To su uređaji koji mogu sami obrađivati i reagirati na podatke senzora, obično koristeći AI modele trenirane u oblaku.

IoT je jedno od najbrže rastućih tehnoloških područja. Procjenjuje se da je do kraja 2020. godine bilo implementirano i povezano na Internet 30 milijardi IoT uređaja. Gledajući u budućnost, procjenjuje se da će do 2025. IoT uređaji prikupljati gotovo 80 zettabajta podataka, odnosno 80 trilijuna gigabajta. To je ogromna količina podataka!

![Graf koji prikazuje aktivne IoT uređaje tijekom vremena, s rastućim trendom od manje od 5 milijardi u 2015. do preko 30 milijardi u 2025.](../../../../../images/connected-iot-devices.svg)

✅ Malo istražite: Koliko podataka generiranih od strane IoT uređaja se zapravo koristi, a koliko se zanemaruje? Zašto se toliko podataka ignorira?

Ti podaci su ključ uspjeha IoT-a. Da biste postali uspješan IoT programer, morate razumjeti koje podatke trebate prikupljati, kako ih prikupljati, kako donositi odluke na temelju tih podataka i kako koristiti te odluke za interakciju s fizičkim svijetom, ako je potrebno.

## IoT uređaji

**T** u IoT-u označava **Things** (stvari) - uređaje koji komuniciraju s fizičkim svijetom oko sebe bilo prikupljanjem podataka putem senzora ili pružanjem interakcija u stvarnom svijetu putem aktuatora.

Uređaji za proizvodnju ili komercijalnu upotrebu, poput potrošačkih fitness narukvica ili industrijskih kontrolera strojeva, obično su izrađeni po narudžbi. Koriste prilagođene elektroničke ploče, možda čak i prilagođene procesore, dizajnirane da zadovolje potrebe određenog zadatka, bilo da su dovoljno mali da stanu na zapešće ili dovoljno izdržljivi da rade u visokotemperaturnom, stresnom ili vibracijskom okruženju tvornice.

Kao programer koji uči o IoT-u ili stvara prototip uređaja, trebat ćete započeti s razvojnim kompletom. To su univerzalni IoT uređaji dizajnirani za programere, često s funkcijama koje ne biste imali na proizvodnom uređaju, poput seta vanjskih pinova za povezivanje senzora ili aktuatora, hardvera za podršku otklanjanju grešaka ili dodatnih resursa koji bi dodali nepotrebne troškove pri velikoj proizvodnji.

Ovi razvojni kompleti obično spadaju u dvije kategorije - mikrokontrolere i jednopločne računala. Ovdje će biti predstavljeni, a u sljedećoj lekciji ćemo ih detaljnije obraditi.

> 💁 Vaš telefon također se može smatrati univerzalnim IoT uređajem, s ugrađenim senzorima i aktuatorima, pri čemu različite aplikacije koriste senzore i aktuatore na različite načine uz različite usluge u oblaku. Možete čak pronaći neke IoT tutorijale koji koriste aplikaciju na telefonu kao IoT uređaj.

### Mikrokontroleri

Mikrokontroler (također poznat kao MCU, skraćeno od microcontroller unit) je mali računalni uređaj koji se sastoji od:

🧠 Jednog ili više centralnih procesorskih jedinica (CPU-a) - 'mozga' mikrokontrolera koji pokreće vaš program

💾 Memorije (RAM i memorije programa) - gdje se pohranjuju vaš program, podaci i varijable

🔌 Programabilnih ulazno/izlaznih (I/O) priključaka - za komunikaciju s vanjskim perifernim uređajima (povezanim uređajima) poput senzora i aktuatora

Mikrokontroleri su obično jeftini računalni uređaji, s prosječnim cijenama za one koji se koriste u prilagođenom hardveru padajući na oko 0,50 USD, a neki uređaji su jeftini i do 0,03 USD. Razvojni kompleti mogu početi od 4 USD, a cijene rastu kako dodajete više funkcija. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), razvojni komplet mikrokontrolera iz [Seeed Studios](https://www.seeedstudio.com) koji ima senzore, aktuatore, WiFi i ekran, košta oko 30 USD.

![Wio Terminal](../../../../../translated_images/wio-terminal.b8299ee16587db9a.hr.png)

> 💁 Kada pretražujete Internet za mikrokontrolere, budite oprezni s pretraživanjem pojma **MCU**, jer će vam se vratiti puno rezultata vezanih uz Marvel Cinematic Universe, a ne mikrokontrolere.

Mikrokontroleri su dizajnirani da budu programirani za obavljanje ograničenog broja vrlo specifičnih zadataka, umjesto da budu univerzalna računala poput PC-a ili Maca. Osim u vrlo specifičnim scenarijima, ne možete povezati monitor, tipkovnicu i miš i koristiti ih za opće zadatke.

Razvojni kompleti mikrokontrolera obično dolaze s dodatnim senzorima i aktuatorima na ploči. Većina ploča će imati jedan ili više LED svjetala koje možete programirati, zajedno s drugim uređajima poput standardnih priključaka za dodavanje više senzora ili aktuatora koristeći ekosustave različitih proizvođača ili ugrađene senzore (obično najpopularnije poput senzora temperature). Neki mikrokontroleri imaju ugrađenu bežičnu povezanost poput Bluetootha ili WiFi-a ili imaju dodatne mikrokontrolere na ploči za dodavanje ove povezanosti.

> 💁 Mikrokontroleri se obično programiraju u C/C++.

### Jednopločna računala

Jednopločno računalo je mali računalni uređaj koji ima sve elemente kompletnog računala sadržane na jednoj maloj ploči. To su uređaji koji imaju specifikacije bliske stolnim ili prijenosnim računalima, pokreću puni operativni sustav, ali su mali, troše manje energije i znatno su jeftiniji.

![Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.hr.jpg)

Raspberry Pi je jedno od najpopularnijih jednopločnih računala.

Poput mikrokontrolera, jednopločna računala imaju CPU, memoriju i ulazno/izlazne pinove, ali imaju dodatne funkcije poput grafičkog čipa za povezivanje monitora, audio izlaza i USB priključaka za povezivanje tipkovnica, miševa i drugih standardnih USB uređaja poput web kamera ili vanjske pohrane. Programi se pohranjuju na SD kartice ili tvrde diskove zajedno s operativnim sustavom, umjesto na memorijski čip ugrađen u ploču.

> 🎓 Jednopločno računalo možete zamisliti kao manju, jeftiniju verziju PC-a ili Maca na kojem čitate ovaj tekst, s dodatkom GPIO (general-purpose input/output) pinova za interakciju sa senzorima i aktuatorima.

Jednopločna računala su potpuno funkcionalna računala, pa se mogu programirati u bilo kojem jeziku. IoT uređaji se obično programiraju u Pythonu.

### Izbor hardvera za ostatak lekcija

Sve sljedeće lekcije uključuju zadatke koji koriste IoT uređaj za interakciju s fizičkim svijetom i komunikaciju s oblakom. Svaka lekcija podržava 3 izbora uređaja - Arduino (koristeći Seeed Studios Wio Terminal), ili jednopločno računalo, bilo fizički uređaj (Raspberry Pi 4) ili virtualno jednopločno računalo koje radi na vašem PC-u ili Macu.

Možete pročitati o potrebnom hardveru za dovršavanje svih zadataka u [vodiču za hardver](../../../hardware.md).

> 💁 Ne trebate kupiti nikakav IoT hardver za dovršavanje zadataka, sve možete napraviti koristeći virtualno jednopločno računalo.

Koji hardver odaberete ovisi o tome što imate dostupno kod kuće ili u školi, te koji programski jezik poznajete ili planirate naučiti. Oba hardverska varijanta koristit će isti ekosustav senzora, pa ako započnete s jednim putem, možete se prebaciti na drugi bez potrebe za zamjenom većine opreme. Virtualno jednopločno računalo bit će ekvivalent učenju na Raspberry Pi-u, s većinom koda koji se može prenijeti na Pi ako ga kasnije nabavite zajedno sa senzorima.

### Arduino razvojni komplet

Ako ste zainteresirani za učenje razvoja mikrokontrolera, zadatke možete dovršiti koristeći Arduino uređaj. Trebat ćete osnovno razumijevanje programiranja u C/C++, jer lekcije će podučavati samo kod koji je relevantan za Arduino okvir, senzore i aktuatore koji se koriste, te biblioteke koje komuniciraju s oblakom.

Zadaci će koristiti [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) s [PlatformIO ekstenzijom za razvoj mikrokontrolera](https://platformio.org). Također možete koristiti Arduino IDE ako ste iskusni s ovim alatom, jer upute neće biti pružene.

### Razvojni komplet jednopločnog računala

Ako ste zainteresirani za učenje razvoja IoT-a koristeći jednopločna računala, zadatke možete dovršiti koristeći Raspberry Pi ili virtualni uređaj koji radi na vašem PC-u ili Macu.

Trebat ćete osnovno razumijevanje programiranja u Pythonu, jer lekcije će podučavati samo kod koji je relevantan za senzore i aktuatore koji se koriste, te biblioteke koje komuniciraju s oblakom.

> 💁 Ako želite naučiti programirati u Pythonu, pogledajte sljedeće dvije serije videa:
>
> * [Python za početnike](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Više o Pythonu za početnike](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Zadaci će koristiti [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Ako koristite Raspberry Pi, možete pokrenuti svoj Pi koristeći punu desktop verziju Raspberry Pi OS-a i raditi sav kod direktno na Pi-u koristeći [verziju VS Code-a za Raspberry Pi OS](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), ili pokrenuti svoj Pi kao uređaj bez monitora i kodirati s vašeg PC-a ili Maca koristeći VS Code s [Remote SSH ekstenzijom](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) koja vam omogućuje povezivanje s vašim Pi-jem i uređivanje, otklanjanje grešaka i pokretanje koda kao da ga direktno kodirate na njemu.

Ako koristite opciju virtualnog uređaja, kodirat ćete direktno na svom računalu. Umjesto pristupa senzorima i aktuatorima, koristit ćete alat za simulaciju ovog hardvera koji pruža vrijednosti senzora koje možete definirati i prikazuje rezultate aktuatora na ekranu.

## Postavljanje vašeg uređaja

Prije nego što započnete s programiranjem vašeg IoT uređaja, trebate napraviti malo postavljanja. Slijedite relevantne upute u nastavku ovisno o tome koji uređaj ćete koristiti.
💁 Ako još nemate uređaj, pogledajte [vodič za hardver](../../../hardware.md) kako biste odlučili koji uređaj ćete koristiti i koji dodatni hardver trebate kupiti. Nije potrebno kupovati hardver, jer se svi projekti mogu pokrenuti na virtualnom hardveru.
Ove upute uključuju poveznice na web stranice trećih strana koje su kreirali proizvođači hardvera ili alata koje ćete koristiti. Cilj je osigurati da uvijek koristite najnovije upute za različite alate i hardver.

Prođite kroz relevantni vodič kako biste postavili svoj uređaj i dovršili projekt 'Hello World'. Ovo će biti prvi korak u stvaranju IoT noćnog svjetla tijekom 4 lekcije u ovom uvodnom dijelu.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Jednoplano računalo - Raspberry Pi](pi.md)
* [Jednoplano računalo - Virtualni uređaj](virtual-device.md)

✅ Koristit ćete VS Code za Arduino i jednoplana računala. Ako ga dosad niste koristili, pročitajte više o njemu na [VS Code stranici](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## Primjene IoT-a

IoT pokriva širok raspon primjena, podijeljenih u nekoliko glavnih skupina:

* Potrošački IoT
* Komercijalni IoT
* Industrijski IoT
* Infrastrukturni IoT

✅ Malo istražite: Za svako od područja opisanih u nastavku pronađite jedan konkretan primjer koji nije naveden u tekstu.

### Potrošački IoT

Potrošački IoT odnosi se na IoT uređaje koje potrošači kupuju i koriste u kućanstvu. Neki od ovih uređaja su iznimno korisni, poput pametnih zvučnika, pametnih sustava grijanja i robotskih usisavača. Drugi su upitni u svojoj korisnosti, poput slavina koje se kontroliraju glasom, a koje se ne mogu isključiti jer glasovna kontrola ne čuje preko zvuka tekuće vode.

Potrošački IoT uređaji omogućuju ljudima da postignu više u svom okruženju, posebno milijardu ljudi koji imaju neku vrstu invaliditeta. Robotski usisavači mogu osigurati čiste podove osobama s poteškoćama u kretanju koje ne mogu sami usisavati, pećnice koje se kontroliraju glasom omogućuju osobama s ograničenim vidom ili motoričkom kontrolom da zagriju pećnicu samo glasom, a zdravstveni monitori omogućuju pacijentima praćenje kroničnih stanja s redovitijim i detaljnijim ažuriranjima o njihovom stanju. Ovi uređaji postaju toliko uobičajeni da ih čak i mala djeca koriste u svakodnevnom životu, primjerice učenici koji tijekom pandemije COVID-a postavljaju timere na pametnim kućnim uređajima kako bi pratili školske zadatke ili alarme za podsjetnike na nadolazeće sastanke razreda.

✅ Koje potrošačke IoT uređaje imate kod kuće ili na sebi?

### Komercijalni IoT

Komercijalni IoT obuhvaća upotrebu IoT-a na radnom mjestu. U uredskom okruženju mogu postojati senzori za prisutnost i detektori pokreta za upravljanje rasvjetom i grijanjem, kako bi se svjetla i grijanje uključivali samo kada su potrebni, smanjujući troškove i emisiju ugljika. U tvornici, IoT uređaji mogu pratiti sigurnosne opasnosti, poput radnika koji ne nose zaštitne kacige ili buke koja je dosegnula opasne razine. U maloprodaji, IoT uređaji mogu mjeriti temperaturu hladnog skladišta, upozoravajući vlasnika trgovine ako hladnjak ili zamrzivač izađu iz potrebnog temperaturnog raspona, ili mogu pratiti artikle na policama kako bi usmjerili zaposlenike da dopune proizvode koji su prodani. Transportna industrija sve više koristi IoT za praćenje lokacija vozila, praćenje kilometraže na cesti za naplatu korištenja cesta, praćenje sati vozača i poštivanje pauza, ili obavještavanje osoblja kada se vozilo približava skladištu kako bi se pripremilo za utovar ili istovar.

✅ Koje komercijalne IoT uređaje imate u školi ili na radnom mjestu?

### Industrijski IoT (IIoT)

Industrijski IoT, ili IIoT, odnosi se na upotrebu IoT uređaja za upravljanje i kontrolu strojeva na velikoj skali. Ovo pokriva širok raspon primjena, od tvornica do digitalne poljoprivrede.

Tvornice koriste IoT uređaje na mnogo različitih načina. Strojevi se mogu pratiti pomoću više senzora za praćenje stvari poput temperature, vibracija i brzine rotacije. Ovi podaci mogu se pratiti kako bi se omogućilo zaustavljanje stroja ako izađe iz određenih tolerancija - primjerice, ako se pregrije, može se automatski isključiti. Ovi podaci također se mogu prikupljati i analizirati tijekom vremena za prediktivno održavanje, gdje AI modeli analiziraju podatke koji prethode kvaru i koriste ih za predviđanje drugih kvarova prije nego što se dogode.

Digitalna poljoprivreda je važna ako planet želi nahraniti rastuću populaciju, posebno za 2 milijarde ljudi u 500 milijuna kućanstava koji ovise o [samoodrživoj poljoprivredi](https://wikipedia.org/wiki/Subsistence_agriculture). Digitalna poljoprivreda može se kretati od nekoliko senzora koji koštaju nekoliko dolara do velikih komercijalnih sustava. Poljoprivrednik može započeti praćenjem temperatura i korištenjem [dana rasta](https://wikipedia.org/wiki/Growing_degree-day) za predviđanje kada će usjev biti spreman za berbu. Mogu povezati praćenje vlažnosti tla s automatiziranim sustavima navodnjavanja kako bi svojim biljkama dali onoliko vode koliko im je potrebno, ali ne više, kako bi osigurali da njihovi usjevi ne presuše bez rasipanja vode. Poljoprivrednici idu i dalje koristeći dronove, satelitske podatke i AI za praćenje rasta usjeva, bolesti i kvalitete tla na velikim područjima poljoprivrednog zemljišta.

✅ Koji drugi IoT uređaji bi mogli pomoći poljoprivrednicima?

### Infrastrukturni IoT

Infrastrukturni IoT odnosi se na praćenje i upravljanje lokalnom i globalnom infrastrukturom koju ljudi koriste svakodnevno.

[Pametni gradovi](https://wikipedia.org/wiki/Smart_city) su urbane zone koje koriste IoT uređaje za prikupljanje podataka o gradu i korištenje tih podataka za poboljšanje funkcioniranja grada. Ovi gradovi obično se vode suradnjom lokalnih vlasti, akademske zajednice i lokalnih poduzeća, prateći i upravljajući stvarima poput transporta, parkiranja i zagađenja. Na primjer, u Kopenhagenu, Danska, zagađenje zraka je važno lokalnim stanovnicima, pa se mjeri i podaci se koriste za pružanje informacija o najčišćim rutama za bicikliranje i trčanje.

[Pametne električne mreže](https://wikipedia.org/wiki/Smart_grid) omogućuju bolje analize potražnje za električnom energijom prikupljanjem podataka o potrošnji na razini pojedinačnih kućanstava. Ovi podaci mogu voditi odluke na razini države, uključujući gdje izgraditi nove elektrane, i na osobnoj razini, dajući korisnicima uvid u to koliko energije koriste, kada je koriste, pa čak i prijedloge kako smanjiti troškove, poput punjenja električnih automobila noću.

✅ Kada biste mogli dodati IoT uređaje za mjerenje bilo čega u vašem mjestu, što bi to bilo?

## Primjeri IoT uređaja koje možda imate oko sebe

Iznenadili biste se koliko IoT uređaja imate oko sebe. Ovo pišem od kuće i imam sljedeće uređaje povezane na Internet s pametnim značajkama poput kontrole putem aplikacije, glasovne kontrole ili mogućnosti slanja podataka na moj telefon:

* Više pametnih zvučnika
* Hladnjak, perilica posuđa, pećnica i mikrovalna
* Monitor električne energije za solarne panele
* Pametne utičnice
* Video portafon i sigurnosne kamere
* Pametni termostat s više pametnih senzora za prostorije
* Otvarač garažnih vrata
* Kućni zabavni sustavi i televizori s glasovnom kontrolom
* Rasvjeta
* Fitness i zdravstveni monitori

Svi ovi uređaji imaju senzore i/ili aktuatore i komuniciraju s Internetom. Mogu saznati putem telefona je li moja garažna vrata otvorena i zamoliti pametni zvučnik da ih zatvori. Čak mogu postaviti timer tako da se, ako su još otvorena noću, automatski zatvore. Kada mi zvoni portafon, mogu vidjeti tko je tamo putem telefona, gdje god se nalazim u svijetu, i razgovarati s njima putem zvučnika i mikrofona ugrađenih u portafon. Mogu pratiti razinu glukoze u krvi, otkucaje srca i obrasce spavanja, tražeći obrasce u podacima kako bih poboljšao svoje zdravlje. Mogu upravljati rasvjetom putem oblaka i sjediti u mraku kada mi se prekine internetska veza.

---

## 🚀 Izazov

Nabrojite što više IoT uređaja koje imate kod kuće, u školi ili na radnom mjestu - možda ih ima više nego što mislite!

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Pregled i samostalno učenje

Pročitajte o prednostima i neuspjesima potrošačkih IoT projekata. Provjerite vijesti za članke o tome kada su stvari krenule po zlu, poput problema s privatnošću, hardverskih problema ili problema uzrokovanih nedostatkom povezivosti.

Neki primjeri:

* Pogledajte Twitter račun **[Internet of Sh*t](https://twitter.com/internetofshit)** *(upozorenje na nepristojan jezik)* za dobre primjere neuspjeha potrošačkog IoT-a.
* [c|net - Moj Apple Watch mi je spasio život: 5 ljudi dijeli svoje priče](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - ADT tehničar priznao krivnju za špijuniranje kamera kupaca godinama](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(upozorenje na osjetljiv sadržaj - neovlašteno voajerstvo)*

## Zadatak

[Istražite IoT projekt](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za kritične informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.