<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52ed2bd997d08040f79a1a6ef2bac958",
  "translation_date": "2025-08-28T13:13:47+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/README.md",
  "language_code": "hr"
}
-->
# Praćenje lokacije

![Sketchnote pregled ove lekcije](../../../../../translated_images/hr/lesson-11.9fddbac4b664c6d50ab7ac9bb32f1fc3f945f03760e72f7f43938073762fb017.jpg)

> Sketchnote autorice [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Uvod

Glavni proces dostave hrane od poljoprivrednika do potrošača uključuje utovar kutija s proizvodima na kamione, brodove, avione ili druga komercijalna prijevozna sredstva te dostavu hrane na neko odredište – bilo izravno kupcu ili u centralno skladište za daljnju obradu. Cijeli proces od farme do potrošača dio je procesa koji se naziva *lanac opskrbe*. Videozapis u nastavku, koji dolazi sa Sveučilišta Arizona State, W. P. Carey School of Business, detaljnije objašnjava koncept lanca opskrbe i kako se njime upravlja.

[![Što je upravljanje lancem opskrbe? Video sa Sveučilišta Arizona State, W. P. Carey School of Business](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Kliknite na sliku iznad za gledanje videa

Dodavanje IoT uređaja može značajno unaprijediti vaš lanac opskrbe, omogućujući vam bolje upravljanje lokacijom predmeta, planiranje prijevoza i rukovanja robom te brže reagiranje na probleme.

Kada upravljate flotom vozila poput kamiona, korisno je znati gdje se svako vozilo nalazi u određenom trenutku. Vozila se mogu opremiti GPS senzorima koji šalju svoju lokaciju IoT sustavima, omogućujući vlasnicima da precizno odrede njihovu lokaciju, vide rutu kojom su se kretali i znaju kada će stići na odredište. Većina vozila radi izvan WiFi pokrivenosti, pa koriste mobilne mreže za slanje ovakvih podataka. Ponekad je GPS senzor ugrađen u složenije IoT uređaje poput elektroničkih dnevnika vožnje. Ovi uređaji prate koliko dugo je kamion bio u tranzitu kako bi se osiguralo da vozači poštuju lokalne zakone o radnim satima.

U ovoj lekciji naučit ćete kako pratiti lokaciju vozila koristeći senzor Globalnog pozicijskog sustava (GPS).

U ovoj lekciji obradit ćemo:

* [Povezana vozila](../../../../../3-transport/lessons/1-location-tracking)
* [Geoprostorne koordinate](../../../../../3-transport/lessons/1-location-tracking)
* [Globalni pozicijski sustavi (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [Čitanje podataka GPS senzora](../../../../../3-transport/lessons/1-location-tracking)
* [NMEA GPS podaci](../../../../../3-transport/lessons/1-location-tracking)
* [Dekodiranje podataka GPS senzora](../../../../../3-transport/lessons/1-location-tracking)

## Povezana vozila

IoT mijenja način na koji se roba prevozi stvaranjem flota *povezanih vozila*. Ova vozila su povezana s centralnim IT sustavima i šalju informacije o svojoj lokaciji te drugim podacima senzora. Imati flotu povezanih vozila donosi brojne prednosti:

* Praćenje lokacije - možete precizno odrediti gdje se vozilo nalazi u bilo kojem trenutku, što omogućuje:

  * Primanje obavijesti kada je vozilo blizu odredišta kako biste pripremili ekipu za istovar
  * Pronalaženje ukradenih vozila
  * Kombiniranje podataka o lokaciji i ruti s prometnim problemima kako biste preusmjerili vozila tijekom putovanja
  * Poštivanje poreznih propisa. Neke zemlje naplaćuju vozilima porez na temelju prijeđene kilometraže na javnim cestama (kao što je [novozelandski RUC](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), pa poznavanje trenutka kada je vozilo na javnim cestama u odnosu na privatne olakšava izračunavanje poreza.
  * Znanje gdje poslati ekipe za održavanje u slučaju kvara

* Telemetrija vozača - osiguravanje da vozači poštuju ograničenja brzine, voze sigurno i učinkovito koče. Povezana vozila također mogu imati kamere za snimanje incidenata. Ovo se može povezati s osiguranjem, omogućujući niže premije za dobre vozače.

* Poštivanje radnih sati vozača - osiguravanje da vozači voze samo unutar zakonski dopuštenih sati na temelju vremena kada pale i gase motor.

Ove se prednosti mogu kombinirati - na primjer, kombiniranje poštivanja radnih sati vozača s praćenjem lokacije kako bi se vozači preusmjerili ako ne mogu stići na odredište unutar dopuštenih sati vožnje. Također se mogu kombinirati s drugim telemetrijskim podacima specifičnim za vozilo, poput podataka o temperaturi iz kamiona s kontroliranom temperaturom, omogućujući preusmjeravanje vozila ako trenutna ruta znači da roba neće biti održavana na odgovarajućoj temperaturi.

> 🎓 Logistika je proces transporta robe s jednog mjesta na drugo, poput transporta s farme u supermarket preko jednog ili više skladišta. Poljoprivrednik pakira kutije s rajčicama koje se utovaruju na kamion, dostavljaju u centralno skladište i prebacuju na drugi kamion koji može sadržavati mješavinu različitih vrsta proizvoda, a zatim se dostavljaju u supermarket.

Ključna komponenta praćenja vozila je GPS - senzori koji mogu odrediti svoju lokaciju bilo gdje na Zemlji. U ovoj lekciji naučit ćete kako koristiti GPS senzor, počevši s učenjem o tome kako definirati lokaciju na Zemlji.

## Geoprostorne koordinate

Geoprostorne koordinate koriste se za definiranje točaka na Zemljinoj površini, slično kao što se koordinate koriste za crtanje piksela na ekranu računala ili pozicioniranje šavova u vezu. Za jednu točku imate par koordinata. Na primjer, Microsoftov kampus u Redmondu, Washington, SAD nalazi se na 47.6423109, -122.1390293.

### Geografska širina i dužina

Zemlja je sfera - trodimenzionalni krug. Zbog toga se točke definiraju dijeljenjem na 360 stupnjeva, isto kao i geometrija krugova. Geografska širina mjeri broj stupnjeva od sjevera prema jugu, a geografska dužina mjeri broj stupnjeva od istoka prema zapadu.

> 💁 Nitko zapravo ne zna izvorni razlog zašto su krugovi podijeljeni na 360 stupnjeva. [Stranica o stupnjevima (kut) na Wikipediji](https://wikipedia.org/wiki/Degree_(angle)) pokriva neke od mogućih razloga.

![Linije geografske širine od 90° na Sjevernom polu, 45° na pola puta između Sjevernog pola i ekvatora, 0° na ekvatoru, -45° na pola puta između ekvatora i Južnog pola, i -90° na Južnom polu](../../../../../translated_images/hr/latitude-lines.11d8d91dfb2014a57437272d7db7fd6607243098e8685f06e0c5f1ec984cb7eb.png)

Geografska širina mjeri se pomoću linija koje kruže Zemljom i paralelne su s ekvatorom, dijeleći sjevernu i južnu hemisferu na po 90°. Ekvator je na 0°, Sjeverni pol na 90°, također poznat kao 90° sjeverno, a Južni pol na -90°, ili 90° južno.

Geografska dužina mjeri se kao broj stupnjeva prema istoku i zapadu. Početna točka od 0° geografske dužine naziva se *Glavni meridijan* i definirana je 1884. godine kao linija od Sjevernog do Južnog pola koja prolazi kroz [Kraljevski opservatorij u Greenwichu, Engleska](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Linije geografske dužine koje idu od -180° zapadno od Glavnog meridijana, do 0° na Glavnom meridijanu, do 180° istočno od Glavnog meridijana](../../../../../translated_images/hr/longitude-meridians.ab4ef1c91c064586b0185a3c8d39e585903696c6a7d28c098a93a629cddb5d20.png)

> 🎓 Meridijan je zamišljena ravna linija koja ide od Sjevernog do Južnog pola, tvoreći polukrug.

Za mjerenje geografske dužine točke, mjeri se broj stupnjeva oko ekvatora od Glavnog meridijana do meridijana koji prolazi kroz tu točku. Geografska dužina ide od -180°, ili 180° zapadno, preko 0° na Glavnom meridijanu, do 180°, ili 180° istočno. 180° i -180° odnose se na istu točku, antimeridijan ili 180. meridijan. Ovo je meridijan na suprotnoj strani Zemlje od Glavnog meridijana.

> 💁 Antimeridijan se ne smije miješati s Međunarodnom datumska linijom, koja je otprilike na istom položaju, ali nije ravna linija i varira kako bi se prilagodila geopolitičkim granicama.

✅ Istražite: Pokušajte pronaći geografsku širinu i dužinu svoje trenutne lokacije.

### Stupnjevi, minute i sekunde naspram decimalnih stupnjeva

Tradicionalno, mjerenja stupnjeva geografske širine i dužine vršila su se koristeći šezdesetinski sustav, ili bazu-60, sustav numeriranja koji su koristili drevni Babilonci koji su prvi mjerili i bilježili vrijeme i udaljenost. Šezdesetinski sustav koristite svakodnevno, vjerojatno i ne shvaćajući to - dijeljenjem sati na 60 minuta i minuta na 60 sekundi.

Geografska dužina i širina mjere se u stupnjevima, minutama i sekundama, pri čemu jedna minuta iznosi 1/60 stupnja, a 1 sekunda 1/60 minute.

Na primjer, na ekvatoru:

* 1° geografske širine iznosi **111,3 kilometara**
* 1 minuta geografske širine iznosi 111,3/60 = **1,855 kilometara**
* 1 sekunda geografske širine iznosi 1,855/60 = **0,031 kilometara**

Simbol za minutu je jednostruki navodnik, za sekundu dvostruki navodnik. Na primjer, 2 stupnja, 17 minuta i 43 sekunde zapisuje se kao 2°17'43". Dijelovi sekundi daju se kao decimale, na primjer pola sekunde je 0°0'0.5".

Računala ne rade u bazi-60, pa se ove koordinate daju kao decimalni stupnjevi kada se koriste GPS podaci u većini računalnih sustava. Na primjer, 2°17'43" je 2.295277. Simbol stupnja obično se izostavlja.

Koordinate za točku uvijek se daju kao `geografska širina, geografska dužina`, pa primjer ranije za Microsoftov kampus na 47.6423109,-122.117198 ima:

* Geografsku širinu od 47.6423109 (47.6423109 stupnjeva sjeverno od ekvatora)
* Geografsku dužinu od -122.1390293 (122.1390293 stupnjeva zapadno od Glavnog meridijana).

![Microsoftov kampus na 47.6423109,-122.117198](../../../../../translated_images/hr/microsoft-gps-location-world.a321d481b010f6adfcca139b2ba0adc53b79f58a540495b8e2ce7f779ea64bfe.png)

## Globalni pozicijski sustavi (GPS)

GPS sustavi koriste više satelita koji kruže oko Zemlje kako bi odredili vašu lokaciju. Vjerojatno ste koristili GPS sustave, a da toga niste ni svjesni - za pronalaženje svoje lokacije u aplikaciji za karte na svom telefonu poput Apple Maps ili Google Maps, za praćenje gdje se nalazi vaše vozilo u aplikaciji za naručivanje prijevoza poput Ubera ili Lyfta, ili kada koristite satelitsku navigaciju (sat-nav) u svom automobilu.

> 🎓 Sateliti u 'satelitskoj navigaciji' su GPS sateliti!

GPS sustavi rade tako što imaju niz satelita koji šalju signal s trenutnom pozicijom svakog satelita i točnim vremenskim zapisom. Ovi signali se šalju putem radio valova i detektiraju antenom u GPS senzoru. GPS senzor detektira ove signale i, koristeći trenutno vrijeme, mjeri koliko je vremena trebalo da signal stigne od satelita do senzora. Budući da je brzina radio valova konstantna, GPS senzor može koristiti poslani vremenski zapis kako bi izračunao koliko je senzor udaljen od satelita. Kombiniranjem podataka s najmanje 3 satelita i njihovih pozicija, GPS senzor može precizno odrediti svoju lokaciju na Zemlji.

> 💁 GPS senzori trebaju antene za detekciju radio valova. Antene ugrađene u kamione i automobile s ugrađenim GPS-om postavljene su tako da imaju dobar signal, obično na vjetrobranskom staklu ili krovu. Ako koristite zaseban GPS sustav, poput pametnog telefona ili IoT uređaja, trebate osigurati da antena ugrađena u GPS sustav ili telefon ima jasan pogled na nebo, poput postavljanja na vjetrobransko staklo.

![Pozicija se može izračunati znajući udaljenost od senzora do više satelita](../../../../../translated_images/hr/gps-satellites.04acf1148fe25fbf1586bc2e8ba698e8d79b79a50c36824b38417dd13372b90f.png)

GPS sateliti kruže oko Zemlje, nisu na fiksnoj točki iznad senzora, pa podaci o lokaciji uključuju nadmorsku visinu iznad razine mora, kao i geografsku širinu i dužinu.

GPS je nekada imao ograničenja točnosti koja je nametnula američka vojska, ograničavajući točnost na oko 5 metara. Ovo ograničenje uklonjeno je 2000. godine, omogućujući točnost od 30 centimetara. Postizanje ove točnosti nije uvijek moguće zbog smetnji u signalima.

✅ Ako imate pametni telefon, pokrenite aplikaciju za karte i provjerite koliko je točna vaša lokacija. Možda će trebati kratko vrijeme da vaš telefon detektira više satelita kako bi dobio točniju lokaciju.
💁 Sateliti sadrže atomske satove koji su izuzetno precizni, ali odstupaju za 38 mikrosekundi (0,0000038 sekundi) dnevno u usporedbi s atomskim satovima na Zemlji, zbog usporavanja vremena kako se brzina povećava, što je predvidio Einstein u teorijama posebne i opće relativnosti - sateliti se kreću brže od rotacije Zemlje. Ovo odstupanje korišteno je za dokazivanje predviđanja posebne i opće relativnosti te se mora uzeti u obzir pri dizajnu GPS sustava. Doslovno, vrijeme sporije teče na GPS satelitu.
GPS sustavi razvijeni su i implementirani od strane nekoliko zemalja i političkih unija, uključujući SAD, Rusiju, Japan, Indiju, EU i Kinu. Moderni GPS senzori mogu se povezati s većinom ovih sustava kako bi dobili brže i preciznije podatke.

> 🎓 Skupine satelita u svakom sustavu nazivaju se konstelacijama.

## Čitanje podataka s GPS senzora

Većina GPS senzora šalje GPS podatke putem UART-a.

> ⚠️ UART je obrađen u [projektu 2, lekcija 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Vratite se na tu lekciju ako je potrebno.

Možete koristiti GPS senzor na svom IoT uređaju za dobivanje GPS podataka.

### Zadatak - povezivanje GPS senzora i čitanje GPS podataka

Prođite kroz odgovarajući vodič za čitanje GPS podataka pomoću vašeg IoT uređaja:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Jednoplatično računalo - Raspberry Pi](pi-gps-sensor.md)
* [Jednoplatično računalo - Virtualni uređaj](virtual-device-gps-sensor.md)

## NMEA GPS podaci

Kada pokrenete svoj kod, mogli biste vidjeti ono što na prvi pogled izgleda kao besmisleni tekst u izlazu. To su zapravo standardni GPS podaci, i svaki dio ima svoje značenje.

GPS senzori šalju podatke koristeći NMEA poruke, prema NMEA 0183 standardu. NMEA je akronim za [National Marine Electronics Association](https://www.nmea.org), američku trgovačku organizaciju koja postavlja standarde za komunikaciju između morske elektronike.

> 💁 Ovaj standard je vlasnički i prodaje se za najmanje 2.000 USD, ali dovoljno informacija o njemu dostupno je u javnoj domeni da je većina standarda reverzno inženjerirana i može se koristiti u otvorenom kodu i drugim nekomercijalnim aplikacijama.

Ove poruke su tekstualne. Svaka poruka sastoji se od *rečenice* koja počinje znakom `$`, nakon čega slijede 2 znaka koji označavaju izvor poruke (npr. GP za američki GPS sustav, GN za GLONASS, ruski GPS sustav), te 3 znaka koji označavaju tip poruke. Ostatak poruke su polja odvojena zarezima, završavajući znakom za novi redak.

Neki od tipova poruka koje se mogu primiti su:

| Tip | Opis |
| ---- | ----------- |
| GGA | Podaci o GPS lokaciji, uključujući geografsku širinu, dužinu i nadmorsku visinu GPS senzora, zajedno s brojem satelita u vidokrugu za izračunavanje lokacije. |
| ZDA | Trenutni datum i vrijeme, uključujući lokalnu vremensku zonu |
| GSV | Detalji o satelitima u vidokrugu - definirano kao sateliti od kojih GPS senzor može primiti signale |

> 💁 GPS podaci uključuju vremenske oznake, tako da vaš IoT uređaj može dobiti vrijeme ako je potrebno od GPS senzora, umjesto da se oslanja na NTP server ili unutarnji real-time sat.

Poruka GGA uključuje trenutnu lokaciju koristeći format `(dd)dmm.mmmm`, zajedno s jednim znakom koji označava smjer. `d` u formatu označava stupnjeve, `m` minute, dok su sekunde prikazane kao decimali minuta. Na primjer, 2°17'43" bi bilo 217.716666667 - 2 stupnja, 17.716666667 minuta.

Znak za smjer može biti `N` ili `S` za geografsku širinu, što označava sjever ili jug, te `E` ili `W` za geografsku dužinu, što označava istok ili zapad. Na primjer, geografska širina od 2°17'43" imala bi znak za smjer `N`, dok bi -2°17'43" imala znak `S`.

Primjer - NMEA rečenica `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* Dio za geografsku širinu je `4738.538654,N`, što se pretvara u 47.6423109 u decimalnim stupnjevima. `4738.538654` je 47.6423109, a smjer je `N` (sjever), pa je to pozitivna geografska širina.

* Dio za geografsku dužinu je `12208.341758,W`, što se pretvara u -122.1390293 u decimalnim stupnjevima. `12208.341758` je 122.1390293°, a smjer je `W` (zapad), pa je to negativna geografska dužina.

## Dekodiranje GPS podataka

Umjesto korištenja sirovih NMEA podataka, bolje je dekodirati ih u korisniji format. Postoji mnogo open-source biblioteka koje možete koristiti za izdvajanje korisnih podataka iz sirovih NMEA poruka.

### Zadatak - dekodiranje GPS podataka

Prođite kroz odgovarajući vodič za dekodiranje GPS podataka pomoću vašeg IoT uređaja:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Jednoplatično računalo - Raspberry Pi/Virtualni IoT uređaj](single-board-computer-gps-decode.md)

---

## 🚀 Izazov

Napišite vlastiti NMEA dekoder! Umjesto oslanjanja na biblioteke trećih strana za dekodiranje NMEA rečenica, možete li napisati vlastiti dekoder za izdvajanje geografske širine i dužine iz NMEA rečenica?

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Pregled i samostalno učenje

* Pročitajte više o geospacijalnim koordinatama na [stranici o geografskom koordinatnom sustavu na Wikipediji](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Informirajte se o početnim meridijanima na drugim nebeskim tijelima osim Zemlje na [stranici o početnom meridijanu na Wikipediji](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies).
* Istražite različite GPS sustave različitih svjetskih vlada i političkih unija poput EU, Japana, Rusije, Indije i SAD-a.

## Zadatak

[Istražite druge GPS podatke](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.