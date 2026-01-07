<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9dd7f645ad1c6f20b72fee512987f772",
  "translation_date": "2025-08-28T13:39:17+00:00",
  "source_file": "1-getting-started/lessons/2-deeper-dive/README.md",
  "language_code": "hr"
}
-->
# Dublje istraživanje IoT-a

![Sketchnote pregled ove lekcije](../../../../../translated_images/lesson-2.324b0580d620c25e0a24fb7fddfc0b29a846dd4b82c08e7a9466d580ee78ce51.hr.jpg)

> Sketchnote autorice [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

Ova lekcija je dio serije [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) iz [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekcija je podijeljena u 2 videa - jednosatnu lekciju i jednosatni uredski sat za dublje istraživanje dijelova lekcije i odgovaranje na pitanja.

[![Lekcija 2: Dublje istraživanje IoT-a](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Lekcija 2: Dublje istraživanje IoT-a - Uredski sat](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Kliknite na slike iznad za gledanje videa

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Uvod

Ova lekcija dublje istražuje neke od koncepata obrađenih u prethodnoj lekciji.

U ovoj lekciji obradit ćemo:

* [Komponente IoT aplikacije](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Dublje istraživanje mikrokontrolera](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Dublje istraživanje jednopločnih računala](../../../../../1-getting-started/lessons/2-deeper-dive)

## Komponente IoT aplikacije

Dvije glavne komponente IoT aplikacije su *Internet* i *stvar*. Pogledajmo ove dvije komponente detaljnije.

### Stvar

![Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.hr.jpg)

**Stvar** u IoT-u odnosi se na uređaj koji može komunicirati s fizičkim svijetom. Ovi uređaji su obično mali, jeftini računari, koji rade pri niskim brzinama i koriste malo energije - na primjer, jednostavni mikrokontroleri s kilobajtima RAM-a (za razliku od gigabajta u PC-ju) koji rade na samo nekoliko stotina megaherca (za razliku od gigaherca u PC-ju), ali troše toliko malo energije da mogu raditi tjednima, mjesecima ili čak godinama na baterijama.

Ovi uređaji komuniciraju s fizičkim svijetom, bilo pomoću senzora za prikupljanje podataka iz okoline ili kontroliranjem izlaza ili aktuatora za fizičke promjene. Tipičan primjer je pametni termostat - uređaj koji ima senzor temperature, način za postavljanje željene temperature poput kotačića ili zaslona osjetljivog na dodir, i vezu s grijanjem ili hlađenjem koje se može uključiti kada je detektirana temperatura izvan željenog raspona. Senzor temperature detektira da je prostorija prehladna, a aktuator uključuje grijanje.

![Dijagram koji prikazuje temperaturu i kotačić kao ulaze u IoT uređaj, te kontrolu grijalice kao izlaz](../../../../../translated_images/basic-thermostat.a923217fd1f37e5a6f3390396a65c22a387419ea2dd17e518ec24315ba6ae9a8.hr.png)

Postoji ogroman raspon različitih stvari koje mogu djelovati kao IoT uređaji, od specijaliziranog hardvera koji detektira jednu stvar, do uređaja opće namjene, pa čak i vašeg pametnog telefona! Pametni telefon može koristiti senzore za detekciju svijeta oko sebe i aktuatora za interakciju sa svijetom - na primjer, koristeći GPS senzor za detekciju vaše lokacije i zvučnik za davanje uputa za navigaciju do odredišta.

✅ Razmislite o drugim sustavima koje imate oko sebe koji čitaju podatke sa senzora i koriste ih za donošenje odluka. Jedan primjer bio bi termostat u pećnici. Možete li pronaći još primjera?

### Internet

**Internet** strana IoT aplikacije sastoji se od aplikacija na koje se IoT uređaj može povezati za slanje i primanje podataka, kao i drugih aplikacija koje mogu obrađivati podatke s IoT uređaja i pomoći u donošenju odluka o tome koje zahtjeve poslati aktuatorima IoT uređaja.

Jedna tipična postavka bila bi neka vrsta cloud servisa na koji se IoT uređaj povezuje, a taj cloud servis upravlja stvarima poput sigurnosti, primanja poruka od IoT uređaja i slanja poruka natrag uređaju. Taj cloud servis bi se zatim povezao s drugim aplikacijama koje mogu obrađivati ili pohranjivati podatke senzora, ili koristiti podatke senzora zajedno s podacima iz drugih sustava za donošenje odluka.

Uređaji također ne moraju uvijek izravno povezivati na Internet putem WiFi-a ili žičnih veza. Neki uređaji koriste mrežno umrežavanje za međusobnu komunikaciju putem tehnologija poput Bluetootha, povezujući se putem središnjeg uređaja koji ima internetsku vezu.

U primjeru pametnog termostata, termostat bi se povezao putem kućnog WiFi-a na cloud servis. Poslao bi podatke o temperaturi ovom cloud servisu, a odatle bi se ti podaci zapisali u neku vrstu baze podataka, omogućujući vlasniku kuće da provjeri trenutne i prošle temperature putem aplikacije na telefonu. Drugi servis u oblaku znao bi željenu temperaturu vlasnika kuće i slao poruke natrag IoT uređaju putem cloud servisa kako bi rekao sustavu grijanja da se uključi ili isključi.

![Dijagram koji prikazuje temperaturu i kotačić kao ulaze u IoT uređaj, IoT uređaj s dvosmjernom komunikacijom s oblakom, koji zauzvrat ima dvosmjernu komunikaciju s telefonom, te kontrolu grijalice kao izlaz iz IoT uređaja](../../../../../translated_images/mobile-controlled-thermostat.4a994010473d8d6a52ba68c67e5f02dc8928c717e93ca4b9bc55525aa75bbb60.hr.png)

Još pametnija verzija mogla bi koristiti AI u oblaku s podacima iz drugih senzora povezanih s drugim IoT uređajima, poput senzora prisutnosti koji detektiraju koje su prostorije u upotrebi, kao i podatke poput vremenske prognoze ili čak vašeg kalendara, za donošenje odluka o tome kako pametno postaviti temperaturu. Na primjer, mogla bi isključiti grijanje ako iz vašeg kalendara pročita da ste na odmoru, ili isključiti grijanje po sobama ovisno o tome koje prostorije koristite, učeći iz podataka kako bi s vremenom postajala sve preciznija.

![Dijagram koji prikazuje više senzora temperature i kotačić kao ulaze u IoT uređaj, IoT uređaj s dvosmjernom komunikacijom s oblakom, koji zauzvrat ima dvosmjernu komunikaciju s telefonom, kalendarom i vremenskom prognozom, te kontrolu grijalice kao izlaz iz IoT uređaja](../../../../../translated_images/smarter-thermostat.a75855f15d2d9e63.hr.png)

✅ Koji bi drugi podaci mogli pomoći da Internet povezani termostat postane pametniji?

### IoT na rubu

Iako I u IoT-u označava Internet, ovi uređaji ne moraju se nužno povezivati na Internet. U nekim slučajevima, uređaji se mogu povezati na 'edge' uređaje - gateway uređaje koji rade na vašoj lokalnoj mreži, omogućujući obradu podataka bez poziva preko Interneta. Ovo može biti brže kada imate puno podataka ili sporu internetsku vezu, omogućuje rad offline gdje internetska povezanost nije moguća, poput broda ili područja pogođenog katastrofom, i omogućuje zadržavanje podataka privatnima. Neki uređaji će sadržavati procesni kod kreiran pomoću cloud alata i pokretati ga lokalno kako bi prikupljali i odgovarali na podatke bez korištenja internetske veze za donošenje odluka.

Jedan primjer ovoga je pametni kućni uređaj poput Apple HomePod-a, Amazon Alexe ili Google Home-a, koji će slušati vaš glas koristeći AI modele trenirane u oblaku, ali koji se pokreću lokalno na uređaju. Ovi uređaji će se 'probuditi' kada se izgovori određena riječ ili fraza, i tek tada poslati vaš govor preko Interneta na obradu. Uređaj će prestati slati govor u odgovarajućem trenutku, poput kada detektira pauzu u vašem govoru. Sve što kažete prije buđenja uređaja s ključnom riječju i sve što kažete nakon što uređaj prestane slušati neće biti poslano preko Interneta pružatelju uređaja, i stoga će ostati privatno.

✅ Razmislite o drugim scenarijima gdje je privatnost važna, pa bi obrada podataka bila bolja na rubu nego u oblaku. Kao savjet - razmislite o IoT uređajima s kamerama ili drugim uređajima za snimanje slike.

### IoT sigurnost

Kod svake internetske veze, sigurnost je važan faktor. Postoji stara šala da 'S u IoT-u označava sigurnost' - nema 'S' u IoT-u, što implicira da nije siguran.

IoT uređaji se povezuju na cloud servis, i stoga su sigurni samo koliko i taj cloud servis - ako vaš cloud servis dopušta bilo kojem uređaju da se poveže, tada se mogu slati zlonamjerni podaci ili se mogu dogoditi virusni napadi. Ovo može imati vrlo stvarne posljedice jer IoT uređaji komuniciraju i kontroliraju druge uređaje. Na primjer, [Stuxnet crv](https://wikipedia.org/wiki/Stuxnet) manipulirao je ventilima u centrifugama kako bi ih oštetio. Hakeri su također iskoristili [slabu sigurnost za pristup baby monitorima](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) i drugim kućnim nadzornim uređajima.

> 💁 Ponekad IoT uređaji i edge uređaji rade na mreži potpuno izoliranoj od Interneta kako bi podaci ostali privatni i sigurni. Ovo je poznato kao [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)).

## Dublje istraživanje mikrokontrolera

U prethodnoj lekciji predstavili smo mikrokontrolere. Sada ćemo ih detaljnije istražiti.

### CPU

CPU je 'mozak' mikrokontrolera. To je procesor koji pokreće vaš kod i može slati podatke na i primati podatke s bilo kojih povezanih uređaja. CPU-ovi mogu sadržavati jednu ili više jezgri - u osnovi jedan ili više CPU-ova koji mogu zajedno raditi na pokretanju vašeg koda.

CPU-ovi se oslanjaju na sat koji otkucava milijune ili milijarde puta u sekundi. Svaki otkucaj, ili ciklus, sinkronizira radnje koje CPU može poduzeti. Sa svakim otkucajem, CPU može izvršiti instrukciju iz programa, poput dohvaćanja podataka s vanjskog uređaja ili izvođenja matematičkog izračuna. Ovaj redoviti ciklus omogućuje da se sve radnje dovrše prije nego što se obradi sljedeća instrukcija.

Što je brži ciklus sata, to se više instrukcija može obraditi svake sekunde, i stoga je CPU brži. Brzine CPU-a mjere se u [Hercima (Hz)](https://wikipedia.org/wiki/Hertz), standardnoj jedinici gdje 1 Hz znači jedan ciklus ili otkucaj sata u sekundi.

> 🎓 Brzine CPU-a često se izražavaju u MHz ili GHz. 1MHz je 1 milijun Hz, 1GHz je 1 milijarda Hz.

> 💁 CPU-ovi izvršavaju programe koristeći [ciklus dohvaćanja-dekodiranja-izvršavanja](https://wikipedia.org/wiki/Instruction_cycle). Za svaki otkucaj sata, CPU će dohvatiti sljedeću instrukciju iz memorije, dekodirati je, a zatim je izvršiti, poput korištenja aritmetičko-logičke jedinice (ALU) za zbrajanje 2 broja. Neka izvršenja će trajati više otkucaja, pa će sljedeći ciklus započeti nakon što se instrukcija dovrši.

![Ciklus dohvaćanja-dekodiranja-izvršavanja koji prikazuje dohvaćanje instrukcije iz programa pohranjenog u RAM-u, zatim dekodiranje i izvršavanje na CPU-u](../../../../../translated_images/fetch-decode-execute.2fd6f150f6280392807f4475382319abd0cee0b90058e1735444d6baa6f2078c.hr.png)

Mikrokontroleri imaju mnogo niže brzine sata od stolnih ili prijenosnih računala, pa čak i većine pametnih telefona. Na primjer, Wio Terminal ima CPU koji radi na 120MHz ili 120.000.000 ciklusa u sekundi.

✅ Prosječno PC ili Mac računalo ima CPU s više jezgri koje rade na više gigaherca, što znači da sat otkucava milijarde puta u sekundi. Istražite brzinu sata vašeg računala i usporedite koliko je puta brže od Wio Terminala.

Svaki ciklus sata troši energiju i generira toplinu. Što su otkucaji brži, to se više energije troši i više topline generira. PC-ovi imaju hladnjake i ventilatore za uklanjanje topline, bez kojih bi se pregrijali i isključili u roku od nekoliko sekundi. Mikrokontroleri često nemaju ni jedno ni drugo jer rade mnogo hladnije i stoga mnogo sporije. PC-ovi rade na mrežnom napajanju ili velikim baterijama nekoliko sati, dok mikrokontroleri mogu raditi danima, mjesecima ili čak godinama na malim baterijama. Mikrokontroleri također mogu imati jezgre koje rade na različitim brzinama, prebacujući se na sporije jezgre s niskom potrošnjom kada je opterećenje CPU-a nisko kako bi se smanjila potrošnja energije.

> 💁 Neka PC i Mac računala usvajaju isti miks brzih jezgri visokih performansi i sporijih jezgri niske potrošnje, prebacujući se kako bi optimizirali trajanje baterije ili brzinu ovisno o zadatku koji se izvodi. Na primjer, M1 čip u najnovijim Apple prijenosnicima može se prebacivati između 4 jezgre za performanse i 4 jezgre za učinkovitost kako bi optimizirao trajanje baterije ili brzinu.

✅ Malo istražite: Pročitajte o CPU-ovima na [Wikipedia članku o CPU-ovima](https://wikipedia.org/wiki/Central_processing_unit)

#### Zadatak

Istražite Wio Terminal.

Ako koristite Wio Terminal za ove lekcije, pokušajte pronaći CPU. Pronađite odjeljak *Pregled hardvera* na [stranici proizvoda Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) za sliku unutrašnjosti i pokušajte pronaći CPU kroz prozirni plastični prozor na stražnjoj strani.

### Memorija

Mikrokontroleri obično imaju dvije vrste memorije - memoriju programa i memoriju s nasumičnim pristupom (RAM).

Memorija programa je nevolatilna, što znači da sve što je zapisano u nju ostaje kada uređaj nema napajanja. Ovo je memorija koja pohranjuje vaš programski kod.

RAM je memorija koju program koristi za rad, sadrži varijable koje vaš program alocira i podatke prikupljene s perifernih uređaja. RAM je volatilna memorija, što znači da se njezin sadržaj gubi kada nestane napajanja, što u biti resetira vaš program.
🎓 Programska memorija pohranjuje vaš kod i ostaje čak i kad nema napajanja.
🎓 RAM se koristi za pokretanje vašeg programa i resetira se kada nema napajanja

Kao i kod CPU-a, memorija na mikrokontroleru je za nekoliko redova veličine manja nego na PC-u ili Macu. Tipično računalo može imati 8 gigabajta (GB) RAM-a, ili 8.000.000.000 bajtova, pri čemu svaki bajt ima dovoljno prostora za pohranu jednog slova ili broja od 0-255. Mikrokontroler bi imao samo kilobajte (KB) RAM-a, pri čemu je kilobajt 1.000 bajtova. Wio terminal spomenut gore ima 192KB RAM-a, ili 192.000 bajtova - više od 40.000 puta manje od prosječnog računala!

Dijagram ispod prikazuje relativnu razliku u veličini između 192KB i 8GB - mala točka u sredini predstavlja 192KB.

![Usporedba između 192KB i 8GB - više od 40.000 puta veće](../../../../../translated_images/ram-comparison.6beb73541b42ac6f.hr.png)

Prostor za pohranu programa također je manji nego na PC-u. Tipično računalo može imati tvrdi disk od 500GB za pohranu programa, dok mikrokontroler može imati samo kilobajte ili možda nekoliko megabajta (MB) prostora za pohranu (1MB je 1.000KB, ili 1.000.000 bajtova). Wio terminal ima 4MB prostora za pohranu programa.

✅ Istražite malo: Koliko RAM-a i prostora za pohranu ima računalo koje koristite za čitanje ovoga? Kako se to uspoređuje s mikrokontrolerom?

### Ulaz/Izlaz

Mikrokontrolerima su potrebne ulazne i izlazne (I/O) veze za čitanje podataka sa senzora i slanje kontrolnih signala aktuatorima. Obično sadrže određeni broj višenamjenskih ulazno/izlaznih (GPIO) pinova. Ovi pinovi mogu se konfigurirati putem softvera kao ulazni (primaju signal) ili izlazni (šalju signal).

🧠⬅️ Ulazni pinovi koriste se za čitanje vrijednosti sa senzora

🧠➡️ Izlazni pinovi šalju upute aktuatorima

✅ O ovome ćete naučiti više u sljedećoj lekciji.

#### Zadatak

Istražite Wio Terminal.

Ako koristite Wio Terminal za ove lekcije, pronađite GPIO pinove. Pronađite odjeljak *Pinout diagram* na [stranici proizvoda Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) kako biste saznali koji pinovi su koji. Wio Terminal dolazi s naljepnicom koju možete zalijepiti na stražnju stranu s brojevima pinova, pa je dodajte sada ako već niste.

### Fizička veličina

Mikrokontroleri su obično malih dimenzija, a najmanji, [Freescale Kinetis KL03 MCU, dovoljno je malen da stane u udubljenje golf loptice](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). Samo CPU u PC-u može mjeriti 40mm x 40mm, a to ne uključuje hladnjake i ventilatore potrebne da CPU radi dulje od nekoliko sekundi bez pregrijavanja, što je znatno veće od kompletnog mikrokontrolera. Wio terminal razvojni komplet s mikrokontrolerom, kućištem, zaslonom i nizom priključaka i komponenti nije puno veći od golog Intel i9 CPU-a, a znatno je manji od CPU-a s hladnjakom i ventilatorom!

| Uređaj                          | Veličina              |
| ------------------------------- | --------------------- |
| Freescale Kinetis KL03          | 1.6mm x 2mm x 1mm     |
| Wio terminal                    | 72mm x 57mm x 12mm    |
| Intel i9 CPU, hladnjak i ventilator | 136mm x 145mm x 103mm |

### Okviri i operativni sustavi

Zbog svoje male brzine i veličine memorije, mikrokontroleri ne koriste operativni sustav (OS) u smislu desktop računala. Operativni sustav koji pokreće vaše računalo (Windows, Linux ili macOS) zahtijeva puno memorije i procesorske snage za izvođenje zadataka koji su potpuno nepotrebni za mikrokontroler. Zapamtite da su mikrokontroleri obično programirani za obavljanje jednog ili više vrlo specifičnih zadataka, za razliku od računala opće namjene poput PC-a ili Maca koji mora podržavati korisničko sučelje, reproducirati glazbu ili filmove, pružati alate za pisanje dokumenata ili koda, igranje igara ili pregledavanje interneta.

Za programiranje mikrokontrolera bez OS-a potrebni su alati koji omogućuju izgradnju vašeg koda na način da ga mikrokontroler može pokrenuti, koristeći API-je koji mogu komunicirati s perifernim uređajima. Svaki mikrokontroler je drugačiji, pa proizvođači obično podržavaju standardne okvire koji vam omogućuju da slijedite standardni 'recept' za izgradnju vašeg koda i njegovo pokretanje na bilo kojem mikrokontroleru koji podržava taj okvir.

Mikrokontroleri se mogu programirati i s OS-om - često nazvanim operativni sustav u stvarnom vremenu (RTOS), jer su dizajnirani za rukovanje slanjem podataka perifernim uređajima u stvarnom vremenu. Ovi operativni sustavi su vrlo lagani i pružaju značajke poput:

* Višezadaćnosti, omogućujući vašem kodu da istovremeno pokreće više blokova koda, bilo na više jezgri ili naizmjenično na jednoj jezgri
* Umrežavanja za sigurnu komunikaciju putem interneta
* Komponenti grafičkog korisničkog sučelja (GUI) za izgradnju korisničkih sučelja (UI) na uređajima koji imaju zaslone.

✅ Pročitajte više o različitim RTOS-ima: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Arduino logo](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) je vjerojatno najpopularniji okvir za mikrokontrolere, posebno među studentima, hobistima i entuzijastima. Arduino je platforma za elektroniku otvorenog koda koja kombinira softver i hardver. Možete kupiti Arduino kompatibilne ploče od samog Arduina ili od drugih proizvođača, a zatim ih programirati koristeći Arduino okvir.

Arduino ploče programiraju se u C ili C++. Korištenje C/C++ omogućuje da vaš kod bude vrlo malen i brz, što je potrebno na uređaju s ograničenim resursima poput mikrokontrolera. Jezgra Arduino aplikacije naziva se skica i to je C/C++ kod s dvije funkcije - `setup` i `loop`. Kada se ploča pokrene, Arduino okvir će pokrenuti funkciju `setup` jednom, a zatim će funkciju `loop` pokretati iznova i iznova, kontinuirano dok se napajanje ne isključi.

U funkciji `setup` napisali biste kod za inicijalizaciju, poput povezivanja na WiFi i cloud usluge ili inicijalizacije pinova za ulaz i izlaz. Vaš kod u funkciji `loop` sadržavao bi obradu, poput čitanja sa senzora i slanja vrijednosti u oblak. Obično biste uključili odgodu u svaku petlju, na primjer, ako želite da se podaci senzora šalju svakih 10 sekundi, dodali biste odgodu od 10 sekundi na kraju petlje kako bi mikrokontroler mogao spavati, štedeći energiju, a zatim ponovno pokrenuti petlju kada je potrebno.

![Arduino skica koja prvo pokreće setup, a zatim kontinuirano pokreće loop](../../../../../translated_images/arduino-sketch.79590cb837ff7a7c6a68d1afda6cab83fd53d3bb1bd9a8bf2eaf8d693a4d3ea6.hr.png)

✅ Ova arhitektura programa poznata je kao *petlja događaja* ili *petlja poruka*. Mnoge aplikacije koriste ovo u pozadini i to je standard za većinu desktop aplikacija koje rade na OS-ima poput Windowsa, macOS-a ili Linuxa. `Loop` osluškuje poruke od korisničkih sučelja poput tipki ili uređaja poput tipkovnice i reagira na njih. Više možete pročitati u ovom [članku o petlji događaja](https://wikipedia.org/wiki/Event_loop).

Arduino pruža standardne biblioteke za interakciju s mikrokontrolerima i GPIO pinovima, s različitim implementacijama u pozadini za rad na različitim mikrokontrolerima. Na primjer, funkcija [`delay`](https://www.arduino.cc/reference/en/language/functions/time/delay/) zaustavit će program na određeno vrijeme, dok će funkcija [`digitalRead`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) očitati vrijednost `HIGH` ili `LOW` s određenog pina, bez obzira na to na kojoj ploči se kod pokreće. Ove standardne biblioteke znače da se Arduino kod napisan za jednu ploču može ponovno kompajlirati za bilo koju drugu Arduino ploču i radit će, pod uvjetom da su pinovi isti i da ploče podržavaju iste značajke.

Postoji veliki ekosustav Arduino biblioteka trećih strana koje omogućuju dodavanje dodatnih značajki vašim Arduino projektima, poput korištenja senzora i aktuatora ili povezivanja s cloud IoT uslugama.

##### Zadatak

Istražite Wio Terminal.

Ako koristite Wio Terminal za ove lekcije, ponovno pročitajte kod koji ste napisali u prošloj lekciji. Pronađite funkcije `setup` i `loop`. Pratite serijski izlaz za funkciju `loop` koja se poziva više puta. Pokušajte dodati kod u funkciju `setup` za pisanje na serijski port i promatrajte da se ovaj kod poziva samo jednom svaki put kada ponovno pokrenete uređaj. Pokušajte ponovno pokrenuti uređaj pomoću prekidača za napajanje sa strane kako biste pokazali da se ovo poziva svaki put kada se uređaj ponovno pokrene.

## Dublje istraživanje jednopločnih računala

U prošloj lekciji predstavili smo jednopločna računala. Sada ćemo ih detaljnije istražiti.

### Raspberry Pi

![Raspberry Pi logo](../../../../../translated_images/raspberry-pi-logo.4efaa16605cee054.hr.png)

[Raspberry Pi Foundation](https://www.raspberrypi.org) je dobrotvorna organizacija iz Ujedinjenog Kraljevstva osnovana 2009. godine s ciljem promicanja proučavanja računalnih znanosti, posebno na razini škola. Kao dio ove misije, razvili su jednopločno računalo nazvano Raspberry Pi. Raspberry Pi trenutno je dostupan u 3 varijante - punoj veličini, manjem Pi Zero i računalnom modulu koji se može ugraditi u vaš konačni IoT uređaj.

![Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.hr.jpg)

Najnovija iteracija Raspberry Pi-ja pune veličine je Raspberry Pi 4B. Ima četverojezgreni (4 jezgre) CPU koji radi na 1.5GHz, 2, 4 ili 8GB RAM-a, gigabitni ethernet, WiFi, 2 HDMI porta koji podržavaju 4k zaslone, audio i kompozitni video izlaz, USB portove (2 USB 2.0, 2 USB 3.0), 40 GPIO pinova, konektor za kameru za Raspberry Pi modul kamere i utor za SD karticu. Sve to na ploči dimenzija 88mm x 58mm x 19.5mm, napajanoj USB-C adapterom od 3A. Cijena počinje od 35 USD, što je znatno jeftinije od PC-a ili Maca.

> 💁 Postoji i Pi400, sve-u-jednom računalo s Pi4 ugrađenim u tipkovnicu.

![Raspberry Pi Zero](../../../../../translated_images/raspberry-pi-zero.f7a4133e1e7d54bb.hr.jpg)

Pi Zero je mnogo manji, s nižom snagom. Ima jednojezgreni CPU od 1GHz, 512MB RAM-a, WiFi (u modelu Zero W), jedan HDMI port, mikro-USB port, 40 GPIO pinova, konektor za kameru za Raspberry Pi modul kamere i utor za SD karticu. Dimenzije su mu 65mm x 30mm x 5mm, a troši vrlo malo energije. Zero košta 5 USD, dok verzija s WiFi-jem (Zero W) košta 10 USD.

> 🎓 CPU-i u oba ova uređaja su ARM procesori, za razliku od Intel/AMD x86 ili x64 procesora koji se nalaze u većini PC-a i Macova. Slični su procesorima koji se nalaze u nekim mikrokontrolerima, kao i u gotovo svim mobilnim telefonima, Microsoft Surface X-u i novim Apple Silicon Macovima.

Sve varijante Raspberry Pi-ja koriste verziju Debian Linuxa nazvanu Raspberry Pi OS. Dostupan je kao lagana verzija bez desktopa, što je savršeno za 'headless' projekte gdje vam ne treba zaslon, ili puna verzija s kompletnim desktop okruženjem, web preglednikom, uredskim aplikacijama, alatima za kodiranje i igrama. Budući da je OS verzija Debian Linuxa, možete instalirati bilo koju aplikaciju ili alat koji radi na Debianu i izgrađen je za ARM procesor unutar Pi-ja.

#### Zadatak

Istražite Raspberry Pi.

Ako koristite Raspberry Pi za ove lekcije, pročitajte više o različitim hardverskim komponentama na ploči.

* Možete pronaći detalje o procesorima korištenim na [stranici dokumentacije o hardveru Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Pročitajte više o procesoru korištenom u Pi-ju koji koristite.
* Pronađite GPIO pinove. Pročitajte više o njima na [dokumentaciji o GPIO pinovima Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Koristite [Vodič za korištenje GPIO pinova](https://www.raspberrypi.org/documentation/usage/gpio/README.md) kako biste identificirali različite pinove na svom Pi-ju.

### Programiranje jednopločnih računala

Jednopločna računala su puna računala koja koriste puni OS. To znači da postoji širok raspon programskih jezika, okvira i alata koje možete koristiti za njihovo programiranje, za razliku od mikrokontrolera koji ovise o podršci za ploču u okvirima poput Arduina. Većina programskih jezika ima biblioteke koje omogućuju pristup GPIO pinovima za slanje i primanje podataka sa senzora i aktuatora.

✅ Koje programske jezike poznajete? Jesu li podržani na Linuxu?

Najčešći programski jezik za izgradnju IoT aplikacija na Raspberry Pi-ju je Python. Postoji ogroman ekosustav hardvera dizajniranog za Pi, a gotovo svi uključuju relevantan kod potreban za njihovo korištenje kao Python biblioteke. Neki od ovih ekosustava temelje se na 'hatovima' - tako nazvanima jer sjede na vrhu Pi-ja poput šešira i povezuju se s velikim konektorom na 40 GPIO pinova. Ovi hatovi pružaju dodatne mogućnosti, poput zaslona, senzora, daljinski upravljanih automobila ili adaptera za spajanje senzora sa standardiziranim kabelima.
### Korištenje jednopločastih računala u profesionalnim IoT implementacijama

Jednopločasta računala koriste se za profesionalne IoT implementacije, a ne samo kao razvojni kompleti. Ona mogu pružiti snažan način za upravljanje hardverom i izvođenje složenih zadataka poput pokretanja modela strojnog učenja. Na primjer, postoji [Raspberry Pi 4 compute module](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/) koji nudi svu snagu Raspberry Pi 4, ali u kompaktnijem i jeftinijem obliku bez većine priključaka, dizajniran za ugradnju u prilagođeni hardver.

---

## 🚀 Izazov

Izazov u posljednjoj lekciji bio je nabrojati što više IoT uređaja koje možete pronaći u svom domu, školi ili na radnom mjestu. Za svaki uređaj na ovom popisu, mislite li da su izrađeni oko mikrokontrolera, jednopločastih računala ili čak kombinacije oboje?

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Pregled i samostalno učenje

* Pročitajte [Arduino vodič za početnike](https://www.arduino.cc/en/Guide/Introduction) kako biste bolje razumjeli Arduino platformu.
* Pročitajte [uvod u Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) kako biste saznali više o Raspberry Pi uređajima.
* Saznajte više o nekim konceptima i akronimima u članku [Što su zapravo CPU-i, MPU-i, MCU-i i GPU-i u časopisu Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Koristite ove vodiče, zajedno s troškovima prikazanim putem poveznica u [vodiču za hardver](../../../hardware.md), kako biste odlučili koju hardversku platformu želite koristiti ili biste radije koristili virtualni uređaj.

## Zadatak

[Usporedite i kontrastirajte mikrokontrolere i jednopločasta računala](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden korištenjem AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati mjerodavnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.