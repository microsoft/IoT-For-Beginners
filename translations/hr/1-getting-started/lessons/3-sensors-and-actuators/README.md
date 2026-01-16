<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e9ee00eb5fc55922a73762acc542166b",
  "translation_date": "2025-08-28T14:09:42+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/README.md",
  "language_code": "hr"
}
-->
# Interakcija s fizičkim svijetom pomoću senzora i aktuatora

![Pregled lekcije u obliku sketchnotea](../../../../../translated_images/hr/lesson-3.cc3b7b4cd646de598698cce043c0393fd62ef42bac2eaf60e61272cd844250f4.jpg)

> Sketchnote autorice [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

Ova lekcija je dio serije [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) iz [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekcija je podijeljena u dva videa - jedan sat predavanja i jedan sat dodatnih pitanja i dubljeg objašnjavanja dijelova lekcije.

[![Lekcija 3: Interakcija s fizičkim svijetom pomoću senzora i aktuatora](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Lekcija 3: Interakcija s fizičkim svijetom pomoću senzora i aktuatora - Dodatni sat](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Kliknite na slike iznad za gledanje videa

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Uvod

Ova lekcija uvodi dva važna koncepta za vaš IoT uređaj - senzore i aktuatore. Također ćete praktično raditi s njima, dodajući senzor svjetla svom IoT projektu, a zatim LED koji se kontrolira razinom svjetla, čime ćete efektivno izraditi noćno svjetlo.

U ovoj lekciji obradit ćemo:

* [Što su senzori?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Korištenje senzora](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Vrste senzora](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Što su aktuatori?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Korištenje aktuatora](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Vrste aktuatora](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Što su senzori?

Senzori su hardverski uređaji koji opažaju fizički svijet - mjere jedno ili više svojstava oko sebe i šalju informacije IoT uređaju. Senzori pokrivaju širok raspon uređaja jer postoji mnogo stvari koje se mogu mjeriti, od prirodnih svojstava poput temperature zraka do fizičkih interakcija poput pokreta.

Neki uobičajeni senzori uključuju:

* Senzori temperature - mjere temperaturu zraka ili temperaturu objekta u kojem se nalaze. Za hobiste i programere često su kombinirani s mjerenjem tlaka zraka i vlage u jednom senzoru.
* Tipke - detektiraju kada su pritisnute.
* Senzori svjetla - detektiraju razinu svjetla i mogu biti specifični za određene boje, UV svjetlo, IR svjetlo ili općenito vidljivo svjetlo.
* Kamere - opažaju vizualnu reprezentaciju svijeta snimanjem fotografija ili video streamova.
* Akcelerometri - detektiraju pokret u više smjerova.
* Mikrofoni - detektiraju zvuk, bilo opću razinu zvuka ili usmjereni zvuk.

✅ Istražite. Koje senzore ima vaš telefon?

Svi senzori imaju jednu zajedničku stvar - pretvaraju ono što opažaju u električni signal koji IoT uređaj može interpretirati. Način na koji se taj električni signal interpretira ovisi o senzoru, kao i o komunikacijskom protokolu koji se koristi za komunikaciju s IoT uređajem.

## Korištenje senzora

Slijedite odgovarajući vodič kako biste dodali senzor svom IoT uređaju:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Jednoplani računalo - Raspberry Pi](pi-sensor.md)
* [Jednoplani računalo - Virtualni uređaj](virtual-device-sensor.md)

## Vrste senzora

Senzori mogu biti analogni ili digitalni.

### Analogni senzori

Neki od najosnovnijih senzora su analogni senzori. Ovi senzori primaju napon od IoT uređaja, komponente senzora prilagođavaju taj napon, a napon koji se vraća iz senzora mjeri se kako bi se dobila vrijednost senzora.

> 🎓 Napon je mjera koliko "guranja" postoji za premještanje električne energije s jednog mjesta na drugo, poput premještanja s pozitivnog terminala baterije na negativni terminal. Na primjer, standardna AA baterija ima 1,5V (V je simbol za volt) i može gurati električnu energiju silom od 1,5V s pozitivnog terminala na negativni terminal. Različiti električni hardver zahtijeva različite napone za rad, na primjer, LED može svijetliti s između 2-3V, ali žarulja od 100W trebala bi 240V. Više o naponu možete pročitati na [stranici o naponu na Wikipediji](https://wikipedia.org/wiki/Voltage).

Jedan primjer je potenciometar. To je kotačić koji možete rotirati između dvije pozicije, a senzor mjeri rotaciju.

![Potenciometar postavljen na srednju točku, primajući 5 volti i vraćajući 3,8 volti](../../../../../translated_images/hr/potentiometer.35a348b9ce22f6ec.webp)

IoT uređaj šalje električni signal potenciometru na određenom naponu, poput 5 volti (5V). Kako se potenciometar prilagođava, mijenja napon koji izlazi s druge strane. Zamislite da imate potenciometar označen kao kotačić koji ide od 0 do [11](https://wikipedia.org/wiki/Up_to_eleven), poput gumba za glasnoću na pojačalu. Kada je potenciometar u potpuno isključenom položaju (0), izlazi 0V (0 volti). Kada je u potpuno uključenom položaju (11), izlazi 5V (5 volti).

> 🎓 Ovo je pojednostavljenje, a više možete pročitati o potenciometrima i promjenjivim otpornicima na [stranici o potenciometrima na Wikipediji](https://wikipedia.org/wiki/Potentiometer).

Napon koji izlazi iz senzora zatim čita IoT uređaj, a uređaj može reagirati na njega. Ovisno o senzoru, ovaj napon može biti proizvoljna vrijednost ili može odgovarati standardnoj jedinici. Na primjer, analogni senzor temperature baziran na [termistoru](https://wikipedia.org/wiki/Thermistor) mijenja svoj otpor ovisno o temperaturi. Izlazni napon može se zatim pretvoriti u temperaturu u Kelvinima, a odgovarajuće u °C ili °F, pomoću izračuna u kodu.

✅ Što mislite da se događa ako senzor vrati viši napon nego što je poslan (na primjer, dolazi iz vanjskog izvora napajanja)? ⛔️ NEMOJTE testirati ovo.

#### Pretvorba analognog u digitalno

IoT uređaji su digitalni - ne mogu raditi s analognim vrijednostima, već samo s 0 i 1. To znači da analogne vrijednosti senzora trebaju biti pretvorene u digitalni signal prije nego što se mogu obraditi. Mnogi IoT uređaji imaju pretvarače analognog u digitalno (ADC) za pretvaranje analognih ulaza u digitalne reprezentacije njihovih vrijednosti. Senzori također mogu raditi s ADC-ovima putem konektorske ploče. Na primjer, u Seeed Grove ekosustavu s Raspberry Pi-jem, analogni senzori se povezuju na specifične portove na 'hat-u' koji se postavlja na Pi povezan s GPIO pinovima Pi-ja, a ovaj hat ima ADC za pretvaranje napona u digitalni signal koji se može poslati s GPIO pinova Pi-ja.

Zamislite da imate analogni senzor svjetla povezan s IoT uređajem koji koristi 3,3V i vraća vrijednost od 1V. Taj 1V ne znači ništa u digitalnom svijetu, pa ga treba pretvoriti. Napon će se pretvoriti u analognu vrijednost koristeći ljestvicu ovisno o uređaju i senzoru. Jedan primjer je Seeed Grove senzor svjetla koji daje vrijednosti od 0 do 1.023. Za ovaj senzor koji radi na 3,3V, izlaz od 1V bio bi vrijednost od 300. IoT uređaj ne može raditi s 300 kao analognom vrijednošću, pa bi vrijednost bila pretvorena u `0000000100101100`, binarnu reprezentaciju 300 od strane Grove hat-a. Ovo bi zatim obradio IoT uređaj.

✅ Ako ne znate binarni sustav, istražite kako se brojevi predstavljaju pomoću 0 i 1. [BBC Bitesize uvod u binarni sustav](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) je odlično mjesto za početak.

S programerske strane, sve ovo obično se rješava pomoću biblioteka koje dolaze sa senzorima, tako da se ne morate brinuti o ovoj pretvorbi sami. Za Grove senzor svjetla koristili biste Python biblioteku i pozvali svojstvo `light`, ili koristili Arduino biblioteku i pozvali `analogRead` kako biste dobili vrijednost od 300.

### Digitalni senzori

Digitalni senzori, poput analognih senzora, opažaju svijet oko sebe koristeći promjene u električnom naponu. Razlika je u tome što oni izlaz daju kao digitalni signal, bilo mjerenjem samo dva stanja ili korištenjem ugrađenog ADC-a. Digitalni senzori postaju sve češći kako bi se izbjegla potreba za korištenjem ADC-a bilo na konektorskoj ploči ili na samom IoT uređaju.

Najjednostavniji digitalni senzor je tipka ili prekidač. To je senzor s dva stanja, uključen ili isključen.

![Tipka prima 5 volti. Kada nije pritisnuta vraća 0 volti, kada je pritisnuta vraća 5 volti](../../../../../translated_images/hr/button.eadb560b77ac45e56f523d9d8876e40444f63b419e33eb820082d461fa79490b.png)

Pinovi na IoT uređajima poput GPIO pinova mogu izravno mjeriti ovaj signal kao 0 ili 1. Ako je napon poslan isti kao napon vraćen, očitana vrijednost je 1, inače je očitana vrijednost 0. Nema potrebe za pretvorbom signala, može biti samo 1 ili 0.

> 💁 Naponi nikada nisu potpuno točni, posebno jer komponente u senzoru imaju određeni otpor, pa obično postoji tolerancija. Na primjer, GPIO pinovi na Raspberry Pi-ju rade na 3,3V i očitavaju povratni signal iznad 1,8V kao 1, ispod 1,8V kao 0.

* 3,3V ulazi u tipku. Tipka je isključena pa izlazi 0V, dajući vrijednost 0
* 3,3V ulazi u tipku. Tipka je uključena pa izlazi 3,3V, dajući vrijednost 1

Napredniji digitalni senzori očitavaju analogne vrijednosti, a zatim ih pretvaraju pomoću ugrađenih ADC-a u digitalne signale. Na primjer, digitalni senzor temperature i dalje koristi termoelement na isti način kao analogni senzor, i dalje mjeri promjenu napona uzrokovanu otporom termoelementa na trenutnoj temperaturi. Umjesto da vraća analognu vrijednost i oslanja se na uređaj ili konektorsku ploču za pretvorbu u digitalni signal, ADC ugrađen u senzor pretvara vrijednost i šalje je kao niz 0 i 1 IoT uređaju. Ovi 0 i 1 šalju se na isti način kao digitalni signal za tipku, pri čemu je 1 puni napon, a 0 je 0V.

![Digitalni senzor temperature pretvara analogno očitanje u binarne podatke s 0 kao 0 volti i 1 kao 5 volti prije slanja IoT uređaju](../../../../../translated_images/hr/temperature-as-digital.85004491b977bae1.webp)

Slanje digitalnih podataka omogućuje senzorima da postanu složeniji i šalju detaljnije podatke, čak i šifrirane podatke za sigurne senzore. Jedan primjer je kamera. To je senzor koji snima sliku i šalje je kao digitalne podatke koji sadrže tu sliku, obično u komprimiranom formatu poput JPEG-a, kako bi ih pročitao IoT uređaj. Može čak i streamati video snimanjem slika i slanjem ili kompletne slike okvir po okvir ili komprimiranog video streama.

## Što su aktuatori?

Aktuatori su suprotnost senzorima - oni pretvaraju električni signal iz vašeg IoT uređaja u interakciju s fizičkim svijetom, poput emitiranja svjetla ili zvuka, ili pokretanja motora.

Neki uobičajeni aktuatori uključuju:

* LED - emitira svjetlo kada se uključi
* Zvučnik - emitira zvuk na temelju signala koji mu se šalje, od osnovnog zujalice do audio zvučnika koji može reproducirati glazbu
* Stepper motor - pretvara signal u definiranu količinu rotacije, poput okretanja kotačića za 90°
* Relej - prekidači koji se mogu uključiti ili isključiti električnim signalom. Omogućuju malom naponu iz IoT uređaja da uključi veće napone.
* Ekrani - složeniji aktuatori koji prikazuju informacije na višesegmentnom zaslonu. Ekrani variraju od jednostavnih LED prikaza do visokorezolucijskih video monitora.

✅ Istražite. Koje aktuatore ima vaš telefon?

## Korištenje aktuatora

Slijedite odgovarajući vodič kako biste dodali aktuator svom IoT uređaju, kontroliran senzorom, za izradu IoT noćnog svjetla. Ono će prikupljati razine svjetla iz senzora svjetla i koristiti aktuator u obliku LED-a za emitiranje svjetla kada je detektirana razina svjetla preniska.

![Dijagram toka zadatka koji prikazuje očitavanje i provjeru razina svjetla te kontrolu LED-a](../../../../../translated_images/hr/assignment-1-flow.7552a51acb1a5ec858dca6e855cdbb44206434006df8ba3799a25afcdab1665d.png)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Jednoplani računalo - Raspberry Pi](pi-actuator.md)
* [Jednoplani računalo - Virtualni uređaj](virtual-device-actuator.md)

## Vrste aktuatora

Kao i senzori, aktuatori mogu biti analogni ili digitalni.

### Analogni aktuatori

Analogni aktuatori uzimaju analogni signal i pretvaraju ga u neku vrstu interakcije, gdje se interakcija mijenja ovisno o naponu koji se isporučuje.

Jedan primjer je svjetlo koje se može prigušiti, poput onih koje možda imate u svom domu. Količina napona isporučena svjetlu određuje koliko jako svijetli.
![Svjetlo prigušeno na niskom naponu i svjetlije na višem naponu](../../../../../translated_images/hr/dimmable-light.9ceffeb195dec1a849da718b2d71b32c35171ff7dfea9c07bbf82646a67acf6b.png)

Kao i kod senzora, stvarni IoT uređaj radi na digitalnim signalima, a ne analognim. To znači da za slanje analognog signala IoT uređaj treba digitalno-analogni pretvarač (DAC), bilo direktno na IoT uređaju ili na priključnoj ploči. Ovo će pretvoriti 0 i 1 iz IoT uređaja u analogni napon koji aktuator može koristiti.

✅ Što mislite da se događa ako IoT uređaj pošalje viši napon nego što aktuator može podnijeti?  
⛔️ NEMOJTE ovo testirati.

#### Modulacija širine impulsa

Druga opcija za pretvaranje digitalnih signala iz IoT uređaja u analogni signal je modulacija širine impulsa (PWM). Ovo uključuje slanje puno kratkih digitalnih impulsa koji djeluju kao analogni signal.

Na primjer, PWM možete koristiti za kontrolu brzine motora.

Zamislite da kontrolirate motor s napajanjem od 5V. Pošaljete kratki impuls svom motoru, prebacujući napon na visoki (5V) na dvije stotinke sekunde (0,02s). U tom vremenu vaš motor može napraviti jednu desetinu okreta, ili 36°. Signal se zatim pauzira na dvije stotinke sekunde (0,02s), šaljući niski signal (0V). Svaki ciklus uključivanja i isključivanja traje 0,04s. Ciklus se zatim ponavlja.

![Modulacija širine impulsa rotacija motora na 150 RPM](../../../../../translated_images/hr/pwm-motor-150rpm.83347ac04ca38482.webp)

To znači da u jednoj sekundi imate 25 impulsa od 5V koji traju 0,02s i rotiraju motor, svaki praćen pauzom od 0,02s na 0V kada motor ne rotira. Svaki impuls rotira motor za jednu desetinu okreta, što znači da motor završi 2,5 okreta u sekundi. Koristili ste digitalni signal za rotaciju motora na 2,5 okreta u sekundi, ili 150 [okreta u minuti](https://wikipedia.org/wiki/Revolutions_per_minute) (ne-standardna mjera brzine rotacije).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Kada je PWM signal uključen pola vremena, a isključen pola vremena, to se naziva [radni ciklus od 50%](https://wikipedia.org/wiki/Duty_cycle). Radni ciklusi se mjere kao postotak vremena kada je signal u stanju uključen u odnosu na stanje isključen.

![Modulacija širine impulsa rotacija motora na 75 RPM](../../../../../translated_images/hr/pwm-motor-75rpm.a5e4c939934b6e14.webp)

Brzinu motora možete promijeniti promjenom veličine impulsa. Na primjer, s istim motorom možete zadržati isto vrijeme ciklusa od 0,04s, s impulsom uključenim prepolovljenim na 0,01s, dok se impuls isključen povećava na 0,03s. Imate isti broj impulsa po sekundi (25), ali svaki impuls uključen je upola kraći. Impuls upola kraći okreće motor za jednu dvadesetinu okreta, a pri 25 impulsa u sekundi motor će završiti 1,25 okreta u sekundi ili 75 okreta u minuti. Promjenom brzine impulsa digitalnog signala prepolovili ste brzinu analognog motora.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Kako biste održali glatku rotaciju motora, posebno pri niskim brzinama? Biste li koristili mali broj dugih impulsa s dugim pauzama ili puno vrlo kratkih impulsa s vrlo kratkim pauzama?

> 💁 Neki senzori također koriste PWM za pretvaranje analognih signala u digitalne signale.

> 🎓 Više o modulaciji širine impulsa možete pročitati na [stranici o modulaciji širine impulsa na Wikipediji](https://wikipedia.org/wiki/Pulse-width_modulation).

### Digitalni aktuatori

Digitalni aktuatori, poput digitalnih senzora, imaju ili dva stanja koja se kontroliraju visokim ili niskim naponom ili imaju ugrađen DAC koji može pretvoriti digitalni signal u analogni.

Jedan jednostavan digitalni aktuator je LED. Kada uređaj pošalje digitalni signal 1, šalje se visoki napon koji pali LED. Kada se pošalje digitalni signal 0, napon pada na 0V i LED se gasi.

![LED je ugašen na 0 volti i upaljen na 5V](../../../../../translated_images/hr/led.ec6d94f66676a174ad06d9fa9ea49c2ee89beb18b312d5c6476467c66375b07f.png)

✅ Koje druge jednostavne aktuatore s 2 stanja možete zamisliti? Jedan primjer je solenoid, koji je elektromagnet koji se može aktivirati za obavljanje stvari poput pomicanja zasuna vrata za zaključavanje/otključavanje vrata.

Napredniji digitalni aktuatori, poput ekrana, zahtijevaju da se digitalni podaci šalju u određenim formatima. Obično dolaze s bibliotekama koje olakšavaju slanje ispravnih podataka za njihovu kontrolu.

---

## 🚀 Izazov

Izazov u posljednje dvije lekcije bio je nabrojati što više IoT uređaja koje možete pronaći u svom domu, školi ili radnom mjestu i odlučiti jesu li izgrađeni oko mikrokontrolera ili jednopločnih računala, ili čak mješavine oboje.

Za svaki uređaj koji ste nabrojali, koji su senzori i aktuatori povezani s njim? Koja je svrha svakog senzora i aktuatora povezanog s tim uređajima?

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Pregled i samostalno učenje

* Pročitajte o električnoj energiji i krugovima na [ThingLearn](http://thinglearn.jenlooper.com/curriculum/).  
* Pročitajte o različitim vrstama temperaturnih senzora na [Seeed Studios vodiču za temperaturne senzore](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/)  
* Pročitajte o LED diodama na [Wikipedijinoj stranici o LED diodama](https://wikipedia.org/wiki/Light-emitting_diode)  

## Zadatak

[Istražite senzore i aktuatore](assignment.md)  

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.