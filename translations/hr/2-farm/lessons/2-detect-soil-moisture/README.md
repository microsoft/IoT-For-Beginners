<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4fb20273d299dc8d07a8f06c9cd0cdd9",
  "translation_date": "2025-08-28T14:37:21+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/README.md",
  "language_code": "hr"
}
-->
C, izgovara se *I-kvadrat-C*, je protokol s više kontrolera i više perifernih uređaja, pri čemu svaki povezani uređaj može djelovati kao kontroler ili periferija koja komunicira putem I²C sabirnice (naziv za komunikacijski sustav koji prenosi podatke). Podaci se šalju u obliku adresiranih paketa, pri čemu svaki paket sadrži adresu povezanog uređaja kojemu su namijenjeni.

> 💁 Ovaj model se nekada nazivao master/slave, ali se ta terminologija napušta zbog povezanosti s ropstvom. [Open Source Hardware Association usvojila je termin kontroler/periferija](https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/), ali još uvijek možete naići na reference na staru terminologiju.

Uređaji imaju adresu koja se koristi kada se povezuju na I²C sabirnicu, a obično je unaprijed definirana na uređaju. Na primjer, svaka vrsta Grove senzora iz Seeeda ima istu adresu, pa svi senzori svjetlosti imaju istu adresu, svi gumbi imaju istu adresu koja se razlikuje od adrese senzora svjetlosti. Neki uređaji omogućuju promjenu adrese, mijenjanjem postavki skakača (jumpera) ili lemljenjem pinova.

I²C ima sabirnicu sastavljenu od 2 glavne žice, uz 2 žice za napajanje:

| Žica | Naziv | Opis |
| ---- | --------- | ----------- |
| SDA | Serijski podaci | Ova žica služi za slanje podataka između uređaja. |
| SCL | Serijski sat | Ova žica šalje signal sata brzinom koju postavlja kontroler. |
| VCC | Zajednički kolektor napona | Napajanje za uređaje. Ovo je povezano s SDA i SCL žicama kako bi im osiguralo napajanje putem pull-up otpornika koji isključuje signal kada nijedan uređaj nije kontroler. |
| GND | Zemlja | Ovo osigurava zajedničku zemlju za električni krug. |

![I2C sabirnica s 3 uređaja povezana na SDA i SCL žice, dijeleći zajedničku zemlju](../../../../../translated_images/i2c.83da845dde02256bdd462dbe0d5145461416b74930571b89d1ae142841eeb584.hr.png)

Za slanje podataka, jedan uređaj će izdati početni uvjet kako bi pokazao da je spreman za slanje podataka. Tada postaje kontroler. Kontroler zatim šalje adresu uređaja s kojim želi komunicirati, zajedno s informacijom želi li čitati ili pisati podatke. Nakon što su podaci preneseni, kontroler šalje završni uvjet kako bi naznačio da je završio. Nakon toga drugi uređaj može postati kontroler i slati ili primati podatke.

I<sup>2</sup>C ima ograničenja brzine, s tri različita načina rada koji rade na fiksnim brzinama. Najbrži je način rada High Speed s maksimalnom brzinom od 3,4 Mbps (megabita u sekundi), iako vrlo malo uređaja podržava tu brzinu. Na primjer, Raspberry Pi je ograničen na brzi način rada pri 400 Kbps (kilobita u sekundi). Standardni način rada radi pri 100 Kbps.

> 💁 Ako koristite Raspberry Pi s Grove Base hat kao svoj IoT hardver, moći ćete vidjeti nekoliko I<sup>2</sup>C priključaka na ploči koje možete koristiti za komunikaciju s I<sup>2</sup>C senzorima. Analogni Grove senzori također koriste I<sup>2</sup>C s ADC-om za slanje analognih vrijednosti kao digitalnih podataka, pa je senzor svjetlosti koji ste koristili simulirao analogni pin, s vrijednošću poslanom preko I<sup>2</sup>C jer Raspberry Pi podržava samo digitalne pinove.

### Univerzalni asinkroni prijemnik-predajnik (UART)

UART uključuje fizičke sklopove koji omogućuju komunikaciju između dva uređaja. Svaki uređaj ima 2 komunikacijska pina - prijenos (Tx) i prijem (Rx), pri čemu je Tx pin prvog uređaja povezan s Rx pinom drugog, a Tx pin drugog uređaja povezan s Rx pinom prvog. To omogućuje slanje podataka u oba smjera.

* Uređaj 1 šalje podatke sa svog Tx pina, koje prima uređaj 2 na svom Rx pin
* Uređaj 1 prima podatke na svom Rx pin koje šalje uređaj 2 sa svog Tx pin

![UART s Tx pinom na jednom čipu povezan s Rx pinom na drugom, i obrnuto](../../../../../translated_images/uart.d0dbd3fb9e3728c6.hr.png)

> 🎓 Podaci se šalju jedan bit po jedan, što se naziva *serijska* komunikacija. Većina operativnih sustava i mikrokontrolera ima *serijske portove*, tj. veze koje mogu slati i primati serijske podatke dostupne vašem kodu.

UART uređaji imaju [baud rate](https://wikipedia.org/wiki/Symbol_rate) (poznat i kao simbolička brzina), što je brzina kojom će podaci biti poslani i primljeni u bitovima po sekundi. Uobičajena baud brzina je 9.600, što znači da se 9.600 bitova (0 i 1) podataka šalje svake sekunde.

UART koristi početne i završne bitove - šalje početni bit kako bi naznačio da će poslati bajt (8 bitova) podataka, a zatim završni bit nakon što pošalje 8 bitova.

Brzina UART-a ovisi o hardveru, ali čak i najbrže implementacije ne prelaze 6,5 Mbps (megabita u sekundi, ili milijuni bitova, 0 ili 1, poslanih u sekundi).

Možete koristiti UART preko GPIO pinova - možete postaviti jedan pin kao Tx, a drugi kao Rx, a zatim ih povezati s drugim uređajem.

> 💁 Ako koristite Raspberry Pi s Grove Base hat kao svoj IoT hardver, moći ćete vidjeti UART priključak na ploči koji možete koristiti za komunikaciju sa senzorima koji koriste UART protokol.

### Serijsko periferno sučelje (SPI)

SPI je dizajniran za komunikaciju na kratkim udaljenostima, poput komunikacije mikrokontrolera s uređajem za pohranu poput flash memorije. Temelji se na modelu kontroler/periferija s jednim kontrolerom (obično procesor IoT uređaja) koji komunicira s više perifernih uređaja. Kontroler upravlja svime odabirom periferije i slanjem ili zahtijevanjem podataka.

> 💁 Kao i kod I<sup>2</sup>C, pojmovi kontroler i periferija su nedavne promjene, pa ćete možda vidjeti da se još uvijek koriste stariji pojmovi.

SPI kontroleri koriste 3 žice, uz 1 dodatnu žicu po periferiji. Periferije koriste 4 žice. Te žice su:

| Žica | Naziv | Opis |
| ---- | --------- | ----------- |
| COPI | Izlaz kontrolera, ulaz periferije | Ova žica služi za slanje podataka od kontrolera do periferije. |
| CIPO | Ulaz kontrolera, izlaz periferije | Ova žica služi za slanje podataka od periferije do kontrolera. |
| SCLK | Serijski sat | Ova žica šalje signal sata brzinom koju postavlja kontroler. |
| CS   | Odabir čipa | Kontroler ima više žica, jednu po periferiji, i svaka žica povezuje se s CS žicom na odgovarajućoj periferiji. |

![SPI s jednim kontrolerom i dvije periferije](../../../../../translated_images/spi.297431d6f98b386b.hr.png)

CS žica se koristi za aktiviranje jedne periferije u isto vrijeme, komunicirajući preko COPI i CIPO žica. Kada kontroler treba promijeniti periferiju, deaktivira CS žicu povezanu s trenutno aktivnom periferijom, a zatim aktivira žicu povezanu s periferijom s kojom želi komunicirati sljedeće.

SPI je *full-duplex*, što znači da kontroler može istovremeno slati i primati podatke od iste periferije koristeći COPI i CIPO žice. SPI koristi signal sata na SCLK žici za održavanje sinkronizacije uređaja, pa za razliku od slanja izravno preko UART-a ne treba početne i završne bitove.

Za SPI ne postoje definirana ograničenja brzine, a implementacije često mogu prenositi više megabajta podataka u sekundi.

IoT razvojni kompleti često podržavaju SPI preko nekih GPIO pinova. Na primjer, na Raspberry Pi možete koristiti GPIO pinove 19, 21, 23, 24 i 26 za SPI.

### Bežična komunikacija

Neki senzori mogu komunicirati preko standardnih bežičnih protokola, poput Bluetootha (uglavnom Bluetooth Low Energy, ili BLE), LoRaWAN-a (niskopotrošni protokol za **Lo**ng **Ra**nge mreže), ili WiFi-a. To omogućuje udaljenim senzorima koji nisu fizički povezani s IoT uređajem.

Jedan takav primjer su komercijalni senzori za vlagu tla. Oni mjere vlagu tla na polju, a zatim šalju podatke preko LoRaWAN-a do središnjeg uređaja, koji obrađuje podatke ili ih šalje preko Interneta. To omogućuje senzoru da bude udaljen od IoT uređaja koji upravlja podacima, smanjujući potrošnju energije i potrebu za velikim WiFi mrežama ili dugim kablovima.

BLE je popularan za napredne senzore poput fitness narukvica koje se nose na zapešću. Oni kombiniraju više senzora i šalju podatke senzora na IoT uređaj, poput vašeg telefona, putem BLE-a.

✅ Imate li bluetooth senzore na sebi, u svojoj kući ili školi? To mogu uključivati senzore temperature, senzore prisutnosti, uređaje za praćenje i fitness uređaje.

Jedan popularan način povezivanja komercijalnih uređaja je Zigbee. Zigbee koristi WiFi za formiranje mreža između uređaja, gdje se svaki uređaj povezuje s što više obližnjih uređaja, formirajući veliki broj veza poput paukove mreže. Kada jedan uređaj želi poslati poruku na Internet, može je poslati najbližim uređajima, koji je zatim prosljeđuju drugim obližnjim uređajima i tako dalje, dok ne dođe do koordinatora i može se poslati na Internet.

> 🐝 Naziv Zigbee odnosi se na ples "waggle" medonosnih pčela nakon povratka u košnicu.

## Mjerenje razine vlage u tlu

Možete izmjeriti razinu vlage u tlu koristeći senzor vlage tla, IoT uređaj i kućnu biljku ili obližnji komad tla.

### Zadatak - mjerenje vlage tla

Prođite kroz odgovarajući vodič za mjerenje vlage tla koristeći svoj IoT uređaj:

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Jednopločni računar - Raspberry Pi](pi-soil-moisture.md)
* [Jednopločni računar - Virtualni uređaj](virtual-device-soil-moisture.md)

## Kalibracija senzora

Senzori se oslanjaju na mjerenje električnih svojstava poput otpora ili kapaciteta.

> 🎓 Otpor, mjeren u ohmima (Ω), pokazuje koliko se električna struja opire prolasku kroz nešto. Kada se na materijal primijeni napon, količina struje koja prolazi kroz njega ovisi o otporu materijala. Više o tome možete pročitati na [stranici o električnom otporu na Wikipediji](https://wikipedia.org/wiki/Electrical_resistance_and_conductance).

> 🎓 Kapacitet, mjeren u faradima (F), pokazuje sposobnost komponente ili kruga da prikuplja i pohranjuje električnu energiju. Više o kapacitetu možete pročitati na [stranici o kapacitetu na Wikipediji](https://wikipedia.org/wiki/Capacitance).

Ova mjerenja nisu uvijek korisna - zamislite senzor temperature koji vam daje mjerenje od 22,5 kΩ! Umjesto toga, izmjerena vrijednost mora se pretvoriti u korisnu jedinicu kalibracijom - tj. povezivanjem izmjerenih vrijednosti s količinom koja se mjeri kako bi se omogućilo pretvaranje novih mjerenja u odgovarajuću jedinicu.

Neki senzori dolaze prethodno kalibrirani. Na primjer, senzor temperature koji ste koristili u prošloj lekciji već je bio kalibriran tako da može vratiti mjerenje temperature u °C. U tvornici bi prvi senzor bio izložen nizu poznatih temperatura, a izmjeren otpor. To bi se zatim koristilo za izradu izračuna koji može pretvoriti izmjerenu vrijednost u Ω (jedinica otpora) u °C.

> 💁 Formula za izračun otpora iz temperature naziva se [Steinhart–Hart jednadžba](https://wikipedia.org/wiki/Steinhart–Hart_equation).

### Kalibracija senzora vlage tla

Vlaga tla mjeri se pomoću gravimetrijskog ili volumetrijskog sadržaja vode.

* Gravimetrijski sadržaj je težina vode u jedinici težine tla, mjerena kao broj kilograma vode po kilogramu suhog tla
* Volumetrijski sadržaj je volumen vode u jedinici volumena tla, mjerena kao broj kubnih metara vode po kubnim metrima suhog tla

> 🇺🇸 Za Amerikance, zbog dosljednosti jedinica, ovo se može mjeriti u funtama umjesto kilograma ili kubnim stopama umjesto kubnih metara.

Senzori vlage tla mjere električni otpor ili kapacitet - to ne varira samo s vlagom tla, već i s vrstom tla jer komponente u tlu mogu promijeniti njegove električne karakteristike. Idealno bi bilo da se senzori kalibriraju - tj. uzimanje očitanja sa senzora i uspoređivanje s mjerenjima dobivenim znanstvenijim pristupom. Na primjer, laboratorij može izračunati gravimetrijsku vlagu tla koristeći uzorke specifičnog polja uzete nekoliko puta godišnje, a ti brojevi se koriste za kalibraciju senzora, povezujući očitanje senzora s gravimetrijskom vlagom tla.

![Graf napona u odnosu na sadržaj vlage tla](../../../../../translated_images/soil-moisture-to-voltage.df86d80cda158700.hr.png)

Gornji graf pokazuje kako kalibrirati senzor. Napon se bilježi za uzorak tla koji se zatim mjeri u laboratoriju uspoređivanjem težine vlažnog tla s težinom suhog tla (mjerenjem težine vlažnog tla, zatim sušenjem u pećnici i mjerenjem suhog tla). Nakon što se uzme nekoliko očitanja, to se može prikazati na grafu i linija se može prilagoditi točkama. Ova linija se zatim može koristiti za pretvaranje očitanja senzora vlage tla dobivenih IoT uređajem u stvarna mjerenja vlage tla.

💁 Kod rezistivnih senzora vlage tla, napon raste kako vlaga tla raste. Kod kapacitivnih senzora vlage tla, napon opada kako vlaga tla raste, pa bi grafovi za njih padali, a ne rasli.

![Vrijednost vlage tla interpolirana iz grafa](../../../../../translated_images/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.hr.png)

Gornji graf pokazuje očitanje napona sa senzora vlage tla, a praćenjem tog očitanja do linije na grafu može se izračunati stvarna vlaga tla.

Ovaj pristup znači da poljoprivrednik treba dobiti samo nekoliko laboratorijskih mjerenja za polje, a zatim može koristiti IoT uređaje za mjerenje vlage tla - drastično ubrzavajući vrijeme potrebno za mjerenje.

---

## 🚀 Izazov

Rezistivni i kapacitivni senzori vlage tla imaju niz razlika. Koje su te razlike i koji tip (ako postoji) je najbolji za poljoprivrednika? Mijenja li se odgovor između zemalja u razvoju i razvijenih zemalja?

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Pregled i samostalno učenje

Pročitajte o hardveru i protokolima koje koriste senzori i aktuatori:

* [GPIO Wikipedia stranica](https://wikipedia.org/wiki/General-purpose_input/output)
* [UART Wikipedia stranica](https://wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
* [SPI Wikipedia stranica](https://wikipedia.org/wiki/Serial_Peripheral_Interface)
* [I<sup>2</sup>C Wikipedia stranica](https://wikipedia.org/wiki/I²C)
* [Zigbee Wikipedia stranica](https://wikipedia.org/wiki/Zigbee)

## Zadatak

[Kalibrirajte svoj senzor](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.