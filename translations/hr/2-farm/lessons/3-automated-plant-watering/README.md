<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f7bb24ba53fb627ddb38a8b24a05e594",
  "translation_date": "2025-08-28T15:18:54+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/README.md",
  "language_code": "hr"
}
-->
# Automatsko zalijevanje biljaka

![Sketchnote pregled ove lekcije](../../../../../translated_images/lesson-7.30b5f577d3cb8e031238751475cb519c7d6dbaea261b5df4643d086ffb2a03bb.hr.jpg)

> Sketchnote autorice [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

Ova lekcija je dio [IoT za početnike Projekt 2 - Digitalna poljoprivreda serije](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) iz [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![IoT pogonjeno automatsko zalijevanje biljaka](https://img.youtube.com/vi/g9FfZwv9R58/0.jpg)](https://youtu.be/g9FfZwv9R58)

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/13)

## Uvod

U prethodnoj lekciji naučili ste kako pratiti vlažnost tla. U ovoj lekciji naučit ćete kako izraditi osnovne komponente sustava za automatsko zalijevanje koji reagira na vlažnost tla. Također ćete naučiti o vremenskom aspektu - kako senzorima može trebati neko vrijeme da reagiraju na promjene i kako aktuatorima može trebati vremena da promijene svojstva koja senzori mjere.

U ovoj lekciji obradit ćemo:

* [Upravljanje uređajima visoke snage s IoT uređajem niske snage](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Upravljanje relejem](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Upravljanje biljkom putem MQTT-a](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Vremensko usklađivanje senzora i aktuatora](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Dodavanje vremenskog usklađivanja na vaš poslužitelj za upravljanje biljkama](../../../../../2-farm/lessons/3-automated-plant-watering)

## Upravljanje uređajima visoke snage s IoT uređajem niske snage

IoT uređaji koriste napon niske razine. Iako je to dovoljno za senzore i aktuatora niske snage poput LED-ica, to je premalo za upravljanje većim hardverom, poput pumpe za vodu koja se koristi za navodnjavanje. Čak i male pumpe koje biste mogli koristiti za sobne biljke troše previše struje za IoT razvojni komplet i mogle bi oštetiti ploču.

> 🎓 Struja, mjerena u amperima (A), predstavlja količinu električne energije koja prolazi kroz krug. Napon pruža potisak, dok struja pokazuje koliko se energije potiskuje. Više o struji možete pročitati na [stranici o električnoj struji na Wikipediji](https://wikipedia.org/wiki/Electric_current).

Rješenje za ovo je povezivanje pumpe na vanjski izvor napajanja i korištenje aktuatora za uključivanje pumpe, slično kao što biste uključili svjetlo. Potrebna je mala količina energije (u obliku energije vašeg tijela) da prstom pritisnete prekidač, čime se svjetlo povezuje s mrežnim napajanjem od 110V/240V.

![Prekidač uključuje napajanje za svjetlo](../../../../../translated_images/light-switch.760317ad6ab8bd6d611da5352dfe9c73a94a0822ccec7df3c8bae35da18e1658.hr.png)

> 🎓 [Mrežna struja](https://wikipedia.org/wiki/Mains_electricity) odnosi se na električnu energiju koja se isporučuje kućama i poslovnim prostorima putem nacionalne infrastrukture u mnogim dijelovima svijeta.

✅ IoT uređaji obično pružaju 3.3V ili 5V, s manje od 1 ampera (1A) struje. Usporedite to s mrežnom strujom koja je najčešće na 230V (120V u Sjevernoj Americi i 100V u Japanu) i može napajati uređaje koji troše 30A.

Postoji niz aktuatora koji to mogu učiniti, uključujući mehaničke uređaje koje možete pričvrstiti na postojeće prekidače i koji oponašaju prst koji ih uključuje. Najpopularniji je relej.

### Releji

Relej je elektromehanički prekidač koji pretvara električni signal u mehanički pokret koji uključuje prekidač. Osnova releja je elektromagnet.

> 🎓 [Elektromagneti](https://wikipedia.org/wiki/Electromagnet) su magneti koji se stvaraju prolaskom električne struje kroz zavojnicu žice. Kada je struja uključena, zavojnica postaje magnetizirana. Kada je struja isključena, zavojnica gubi magnetizam.

![Kada je uključen, elektromagnet stvara magnetsko polje, uključujući prekidač za izlazni krug](../../../../../translated_images/relay-on.4db16a0fd6b66926.hr.png)

U releju, kontrolni krug napaja elektromagnet. Kada je elektromagnet uključen, povlači polugu koja pomiče prekidač, zatvarajući par kontakata i dovršavajući izlazni krug.

![Kada je isključen, elektromagnet ne stvara magnetsko polje, isključujući prekidač za izlazni krug](../../../../../translated_images/relay-off.c34a178a2960fecd.hr.png)

Kada je kontrolni krug isključen, elektromagnet se isključuje, oslobađajući polugu i otvarajući kontakte, isključujući izlazni krug. Releji su digitalni aktuatori - visoki signal prema releju ga uključuje, niski signal ga isključuje.

Izlazni krug može se koristiti za napajanje dodatnog hardvera, poput sustava za navodnjavanje. IoT uređaj može uključiti relej, dovršavajući izlazni krug koji napaja sustav za navodnjavanje, i biljke se zalijevaju. IoT uređaj zatim može isključiti relej, prekidajući napajanje sustava za navodnjavanje, isključujući vodu.

![Relej se uključuje, uključujući pumpu koja šalje vodu biljci](../../../../../images/strawberry-pump.gif)

U videu iznad, relej se uključuje. LED na releju svijetli kako bi pokazao da je uključen (neke ploče releja imaju LED-ice koje pokazuju je li relej uključen ili isključen), a napajanje se šalje pumpi, uključujući je i pumpajući vodu u biljku.

> 💁 Releji se također mogu koristiti za prebacivanje između dva izlazna kruga umjesto uključivanja i isključivanja jednog. Kako se poluga pomiče, pomiče prekidač s dovršavanja jednog izlaznog kruga na dovršavanje drugog izlaznog kruga, obično dijeleći zajedničku vezu napajanja ili zajedničku uzemljenje.

✅ Istražite: Postoji više vrsta releja, s razlikama poput toga uključuje li kontrolni krug relej kada je napajanje primijenjeno ili ga isključuje, ili s više izlaznih krugova. Saznajte više o tim različitim vrstama.

Kada se poluga pomiče, obično možete čuti kako stvara kontakt s elektromagnetom uz jasno definiran zvuk klika.

> 💁 Relej se može spojiti tako da stvaranje veze zapravo prekida napajanje releja, isključujući relej, što zatim šalje napajanje natrag na relej ponovno ga uključujući, i tako dalje. To znači da će relej klikati nevjerojatno brzo stvarajući zujanje. Ovako su radila neka od prvih zvona na vratima.

### Snaga releja

Elektromagnetu nije potrebno puno energije za aktivaciju i povlačenje poluge, može se kontrolirati pomoću 3.3V ili 5V izlaza s IoT razvojnog kompleta. Izlazni krug može nositi puno više energije, ovisno o releju, uključujući mrežni napon ili čak veće razine snage za industrijsku upotrebu. Na taj način IoT razvojni komplet može kontrolirati sustav za navodnjavanje, od male pumpe za jednu biljku do masivnog industrijskog sustava za cijelu komercijalnu farmu.

![Grove relej s označenim kontrolnim krugom, izlaznim krugom i relejem](../../../../../translated_images/grove-relay-labelled.293e068f5c3c2a199bd7892f2661fdc9e10c920b535cfed317fbd6d1d4ae1168.hr.png)

Slika iznad prikazuje Grove relej. Kontrolni krug povezuje se s IoT uređajem i uključuje ili isključuje relej koristeći 3.3V ili 5V. Izlazni krug ima dva terminala, bilo koji može biti napajanje ili uzemljenje. Izlazni krug može podnijeti do 250V pri 10A, što je dovoljno za niz uređaja na mrežno napajanje. Možete nabaviti releje koji mogu podnijeti još veće razine snage.

![Pumpa spojena preko releja](../../../../../translated_images/pump-wired-to-relay.66c5cfc0d8918990.hr.png)

Na slici iznad, napajanje se isporučuje pumpi putem releja. Crvena žica povezuje +5V terminal USB napajanja s jednim terminalom izlaznog kruga releja, a druga crvena žica povezuje drugi terminal izlaznog kruga s pumpom. Crna žica povezuje pumpu s uzemljenjem na USB napajanju. Kada se relej uključi, dovršava krug, šaljući 5V na pumpu, uključujući pumpu.

## Upravljanje relejem

Možete upravljati relejem s vašeg IoT razvojnog kompleta.

### Zadatak - upravljanje relejem

Prođite kroz odgovarajući vodič za upravljanje relejem pomoću vašeg IoT uređaja:

* [Arduino - Wio Terminal](wio-terminal-relay.md)
* [Jednopločno računalo - Raspberry Pi](pi-relay.md)
* [Jednopločno računalo - Virtualni uređaj](virtual-device-relay.md)

## Upravljanje biljkom putem MQTT-a

Do sada je vaš relej kontroliran izravno od strane IoT uređaja na temelju jednog očitanja vlažnosti tla. U komercijalnom sustavu za navodnjavanje, logika upravljanja bit će centralizirana, omogućujući donošenje odluka o zalijevanju koristeći podatke s više senzora i omogućujući promjene konfiguracije na jednom mjestu. Kako biste to simulirali, možete upravljati relejem putem MQTT-a.

### Zadatak - upravljanje relejem putem MQTT-a

1. Dodajte odgovarajuće MQTT biblioteke/pip pakete i kod u svoj projekt `soil-moisture-sensor` za povezivanje s MQTT-om. Nazovite ID klijenta kao `soilmoisturesensor_client` s prefiksom vašeg ID-a.

    > ⚠️ Možete se referirati na [upute za povezivanje s MQTT-om u projektu 1, lekcija 4 ako je potrebno](../../../1-getting-started/lessons/4-connect-internet/README.md#connect-your-iot-device-to-mqtt).

1. Dodajte odgovarajući kod uređaja za slanje telemetrije s postavkama vlažnosti tla. Za poruku telemetrije, nazovite svojstvo `soil_moisture`.

    > ⚠️ Možete se referirati na [upute za slanje telemetrije na MQTT u projektu 1, lekcija 4 ako je potrebno](../../../1-getting-started/lessons/4-connect-internet/README.md#send-telemetry-from-your-iot-device).

1. Kreirajte lokalni poslužiteljski kod za pretplatu na telemetriju i slanje naredbe za upravljanje relejem u mapi nazvanoj `soil-moisture-sensor-server`. Nazovite svojstvo u poruci naredbe `relay_on`, i postavite ID klijenta kao `soilmoisturesensor_server` s prefiksom vašeg ID-a. Zadržite istu strukturu kao kod poslužitelja koji ste napisali za projekt 1, lekcija 4 jer ćete kasnije dodavati ovaj kod.

    > ⚠️ Možete se referirati na [upute za slanje telemetrije na MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#write-the-server-code) i [slanje naredbi putem MQTT-a](../../../1-getting-started/lessons/4-connect-internet/README.md#send-commands-to-the-mqtt-broker) u projektu 1, lekcija 4 ako je potrebno.

1. Dodajte odgovarajući kod uređaja za upravljanje relejem iz primljenih naredbi, koristeći svojstvo `relay_on` iz poruke. Pošaljite true za `relay_on` ako je `soil_moisture` veći od 450, inače pošaljite false, isto kao logika koju ste dodali za IoT uređaj ranije.

    > ⚠️ Možete se referirati na [upute za odgovaranje na naredbe iz MQTT-a u projektu 1, lekcija 4 ako je potrebno](../../../1-getting-started/lessons/4-connect-internet/README.md#handle-commands-on-the-iot-device).

> 💁 Ovaj kod možete pronaći u mapi [code-mqtt](../../../../../2-farm/lessons/3-automated-plant-watering/code-mqtt).

Provjerite je li kod pokrenut na vašem uređaju i lokalnom poslužitelju, i testirajte ga mijenjanjem razine vlažnosti tla, bilo promjenom vrijednosti koje šalje virtualni senzor ili promjenom razine vlage tla dodavanjem vode ili uklanjanjem senzora iz tla.

## Vremensko usklađivanje senzora i aktuatora

U lekciji 3 izradili ste noćno svjetlo - LED-icu koja se uključuje čim senzor svjetla detektira nisku razinu svjetlosti. Senzor svjetla detektirao je promjenu razine svjetlosti trenutno, a uređaj je mogao brzo reagirati, ograničen samo duljinom kašnjenja u funkciji `loop` ili `while True:` petlji. Kao IoT programer, ne možete uvijek računati na tako brz povratni ciklus.

### Vremensko usklađivanje za vlažnost tla

Ako ste radili prethodnu lekciju o vlažnosti tla koristeći fizički senzor, mogli ste primijetiti da je trebalo nekoliko sekundi da očitanje vlažnosti tla padne nakon što ste zalili biljku. Ovo nije zato što je senzor spor, već zato što vodi treba vremena da se upije kroz tlo.
💁 Ako ste zalijevali preblizu senzoru, možda ste primijetili da je očitanje brzo palo, a zatim se ponovno povećalo - to je uzrokovano time što se voda blizu senzora širi kroz ostatak tla, smanjujući vlagu tla u blizini senzora.
![Mjerenje vlažnosti tla od 658 ne mijenja se tijekom zalijevanja, već pada na 320 nakon zalijevanja kada voda prodre kroz tlo](../../../../../translated_images/soil-moisture-travel.a0e31af222cf1438.hr.png)

Na gornjem dijagramu očitanje vlažnosti tla pokazuje 658. Biljka se zalijeva, ali ovo očitanje se ne mijenja odmah jer voda još nije stigla do senzora. Zalijevanje može završiti prije nego što voda stigne do senzora, a vrijednost se smanji kako bi odražavala novu razinu vlažnosti.

Ako biste pisali kod za upravljanje sustavom navodnjavanja putem releja na temelju razine vlažnosti tla, trebali biste uzeti u obzir ovo kašnjenje i implementirati pametnije vremensko upravljanje u svoj IoT uređaj.

✅ Odvojite trenutak da razmislite kako biste to mogli učiniti.

### Upravljanje vremenom senzora i aktuatora

Zamislite da ste dobili zadatak izgraditi sustav navodnjavanja za farmu. Na temelju vrste tla, idealna razina vlažnosti tla za uzgojene biljke odgovara analognom očitanju napona od 400-450.

Mogli biste programirati uređaj na isti način kao noćno svjetlo - dok god senzor očitava iznad 450, uključite relej kako biste uključili pumpu. Problem je što vodi treba neko vrijeme da stigne od pumpe, kroz tlo, do senzora. Senzor će zaustaviti vodu kada otkrije razinu od 450, ali razina vode će nastaviti padati dok se pumpana voda upija kroz tlo. Krajnji rezultat je rasipanje vode i rizik od oštećenja korijena.

✅ Zapamtite - previše vode može biti jednako loše za biljke kao i premalo, a također troši dragocjeni resurs.

Bolje rješenje je razumjeti da postoji kašnjenje između uključivanja aktuatora i promjene svojstva koje senzor očitava. To znači da senzor ne samo da treba pričekati neko vrijeme prije nego što ponovno izmjeri vrijednost, već aktuator treba biti isključen neko vrijeme prije nego što se izvrši sljedeće mjerenje senzora.

Koliko dugo relej treba biti uključen svaki put? Bolje je biti oprezan i uključiti relej na kratko vrijeme, zatim pričekati da se voda upije, pa ponovno provjeriti razinu vlažnosti. Uostalom, uvijek možete ponovno uključiti pumpu kako biste dodali više vode, ali ne možete ukloniti vodu iz tla.

> 💁 Ovakva kontrola vremena vrlo je specifična za IoT uređaj koji gradite, svojstvo koje mjerite te senzore i aktuatore koji se koriste.

![Biljka jagode povezana s vodom putem pumpe, pri čemu je pumpa povezana s relejem. Relej i senzor vlažnosti tla u biljci povezani su s Raspberry Pi-jem](../../../../../translated_images/strawberry-with-pump.b410fc72ac6aabad.hr.png)

Na primjer, imam biljku jagode sa senzorom vlažnosti tla i pumpom kojom upravlja relej. Primijetio sam da kada dodam vodu, treba oko 20 sekundi da se očitanje vlažnosti tla stabilizira. To znači da moram isključiti relej i pričekati 20 sekundi prije nego što provjerim razinu vlažnosti. Radije bih imao premalo vode nego previše - uvijek mogu ponovno uključiti pumpu, ali ne mogu izvaditi vodu iz biljke.

![Korak 1, uzmi mjerenje. Korak 2, dodaj vodu. Korak 3, pričekaj da voda prodre kroz tlo. Korak 4, ponovno uzmi mjerenje](../../../../../translated_images/soil-moisture-delay.865f3fae206db01d.hr.png)

To znači da bi najbolji proces bio ciklus zalijevanja koji izgleda ovako:

* Uključite pumpu na 5 sekundi
* Pričekajte 20 sekundi
* Provjerite vlažnost tla
* Ako je razina još uvijek iznad potrebne, ponovite gore navedene korake

5 sekundi moglo bi biti predugo za pumpu, pogotovo ako su razine vlažnosti samo malo iznad potrebne razine. Najbolji način da saznate koje vrijeme koristiti je isprobati, zatim prilagoditi kada imate podatke senzora, uz stalnu povratnu petlju. To čak može dovesti do preciznijeg vremenskog upravljanja, poput uključivanja pumpe na 1 sekundu za svakih 100 iznad potrebne vlažnosti tla, umjesto fiksnih 5 sekundi.

✅ Istražite: Postoje li drugi vremenski čimbenici koje treba uzeti u obzir? Može li se biljka zalijevati bilo kada kada je vlažnost tla preniska, ili postoje određena doba dana koja su dobra i loša za zalijevanje biljaka?

> 💁 Prognoze vremena također se mogu uzeti u obzir pri upravljanju automatiziranim sustavima zalijevanja za vanjski uzgoj. Ako se očekuje kiša, zalijevanje se može odgoditi dok kiša ne završi. U tom trenutku tlo može biti dovoljno vlažno da ne treba zalijevanje, što je mnogo učinkovitije nego trošiti vodu zalijevanjem neposredno prije kiše.

## Dodajte vremensko upravljanje svom poslužitelju za kontrolu biljaka

Kod poslužitelja može se modificirati kako bi se dodala kontrola oko vremena ciklusa zalijevanja i čekanja da se razine vlažnosti tla promijene. Logika poslužitelja za upravljanje vremenom releja je:

1. Primljena telemetrijska poruka
1. Provjerite razinu vlažnosti tla
1. Ako je u redu, ne radite ništa. Ako je očitanje previsoko (što znači da je vlažnost tla preniska), onda:
    1. Pošaljite naredbu za uključivanje releja
    1. Pričekajte 5 sekundi
    1. Pošaljite naredbu za isključivanje releja
    1. Pričekajte 20 sekundi da se razine vlažnosti tla stabiliziraju

Ciklus zalijevanja, proces od primanja telemetrijske poruke do spremnosti za obradu razina vlažnosti tla ponovno, traje oko 25 sekundi. Telemetriju šaljemo svakih 10 sekundi, pa postoji preklapanje gdje se poruka prima dok poslužitelj čeka da se razine vlažnosti tla stabiliziraju, što bi moglo pokrenuti novi ciklus zalijevanja.

Postoje dvije opcije za rješavanje ovog problema:

* Promijenite kod IoT uređaja da šalje telemetriju samo svake minute, na taj način ciklus zalijevanja će biti dovršen prije nego što se pošalje sljedeća poruka
* Odjavite se s telemetrije tijekom ciklusa zalijevanja

Prva opcija nije uvijek dobro rješenje za velike farme. Poljoprivrednik možda želi zabilježiti razine vlažnosti tla dok se tlo zalijeva za kasniju analizu, na primjer kako bi bio svjestan protoka vode u različitim područjima na farmi i usmjerio ciljano zalijevanje. Druga opcija je bolja - kod jednostavno ignorira telemetriju kada je ne može koristiti, ali telemetrija je i dalje dostupna za druge usluge koje se mogu pretplatiti na nju.

> 💁 IoT podaci ne šalju se samo s jednog uređaja na jednu uslugu, već mnogi uređaji mogu slati podatke brokeru, a mnoge usluge mogu slušati podatke s brokera. Na primjer, jedna usluga može slušati podatke o vlažnosti tla i pohraniti ih u bazu podataka za kasniju analizu. Druga usluga također može slušati istu telemetriju kako bi upravljala sustavom navodnjavanja.

### Zadatak - dodajte vremensko upravljanje svom poslužitelju za kontrolu biljaka

Ažurirajte kod poslužitelja kako bi relej radio 5 sekundi, a zatim čekao 20 sekundi.

1. Otvorite mapu `soil-moisture-sensor-server` u VS Code-u ako već nije otvorena. Provjerite je li virtualno okruženje aktivirano.

1. Otvorite datoteku `app.py`

1. Dodajte sljedeći kod u datoteku `app.py` ispod postojećih uvoza:

    ```python
    import threading
    ```

    Ova naredba uvozi `threading` iz Python biblioteka, što omogućuje Pythonu da izvršava drugi kod dok čeka.

1. Dodajte sljedeći kod prije funkcije `handle_telemetry` koja obrađuje telemetrijske poruke primljene od koda poslužitelja:

    ```python
    water_time = 5
    wait_time = 20
    ```

    Ovo definira koliko dugo treba raditi relej (`water_time`) i koliko dugo treba čekati nakon toga da se provjeri vlažnost tla (`wait_time`).

1. Ispod ovog koda dodajte sljedeće:

    ```python
    def send_relay_command(client, state):
        command = { 'relay_on' : state }
        print("Sending message:", command)
        client.publish(server_command_topic, json.dumps(command))
    ```

    Ovaj kod definira funkciju nazvanu `send_relay_command` koja šalje naredbu putem MQTT-a za upravljanje relejem. Telemetrija se stvara kao rječnik, a zatim se pretvara u JSON string. Vrijednost proslijeđena u `state` određuje treba li relej biti uključen ili isključen.

1. Nakon funkcije `send_relay_code`, dodajte sljedeći kod:

    ```python
    def control_relay(client):
        print("Unsubscribing from telemetry")
        mqtt_client.unsubscribe(client_telemetry_topic)
    
        send_relay_command(client, True)
        time.sleep(water_time)
        send_relay_command(client, False)
    
        time.sleep(wait_time)
    
        print("Subscribing to telemetry")
        mqtt_client.subscribe(client_telemetry_topic)
    ```

    Ovo definira funkciju za upravljanje relejem na temelju potrebnog vremena. Počinje odjavljivanjem s telemetrije kako poruke o vlažnosti tla ne bi bile obrađene dok se zalijevanje odvija. Zatim šalje naredbu za uključivanje releja. Zatim čeka `water_time` prije nego što pošalje naredbu za isključivanje releja. Na kraju čeka da se razine vlažnosti tla stabiliziraju tijekom `wait_time` sekundi. Zatim se ponovno prijavljuje na telemetriju.

1. Promijenite funkciju `handle_telemetry` u sljedeće:

    ```python
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['soil_moisture'] > 450:
            threading.Thread(target=control_relay, args=(client,)).start()
    ```

    Ovaj kod provjerava razinu vlažnosti tla. Ako je veća od 450, tlu je potrebno zalijevanje, pa poziva funkciju `control_relay`. Ova funkcija se pokreće na zasebnom threadu, koji radi u pozadini.

1. Provjerite radi li vaš IoT uređaj, zatim pokrenite ovaj kod. Promijenite razine vlažnosti tla i promatrajte što se događa s relejem - trebao bi se uključiti na 5 sekundi, a zatim ostati isključen najmanje 20 sekundi, uključujući se samo ako razine vlažnosti tla nisu dovoljne.

    ```output
    (.venv) ➜  soil-moisture-sensor-server ✗ python app.py
    Message received: {'soil_moisture': 457}
    Unsubscribing from telemetry
    Sending message: {'relay_on': True}
    Sending message: {'relay_on': False}
    Subscribing to telemetry
    Message received: {'soil_moisture': 302}
    ```

    Dobar način za testiranje ovoga u simuliranom sustavu navodnjavanja je korištenje suhog tla, zatim ručno ulijevanje vode dok je relej uključen, prestajući ulijevati kada se relej isključi.

> 💁 Ovaj kod možete pronaći u mapi [code-timing](../../../../../2-farm/lessons/3-automated-plant-watering/code-timing).

> 💁 Ako želite koristiti pumpu za izgradnju stvarnog sustava navodnjavanja, možete koristiti [6V vodenu pumpu](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html) s [USB terminalnim napajanjem](https://www.adafruit.com/product/3628). Provjerite je li napajanje prema ili od pumpe povezano putem releja.

---

## 🚀 Izazov

Možete li smisliti druge IoT ili električne uređaje koji imaju sličan problem gdje treba neko vrijeme da rezultati aktuatora stignu do senzora? Vjerojatno imate nekoliko takvih uređaja u svojoj kući ili školi.

* Koja svojstva mjere?
* Koliko dugo traje promjena svojstva nakon što se aktuator koristi?
* Je li u redu da svojstvo promijeni vrijednost izvan potrebne?
* Kako se može vratiti na potrebnu vrijednost ako je potrebno?

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/14)

## Pregled i samostalno učenje

* Pročitajte više o relejima, uključujući njihovu povijesnu upotrebu u telefonskim centralama, na [Wikipedia stranici o relejima](https://wikipedia.org/wiki/Relay).

## Zadatak

[Izgradite učinkovitiji ciklus zalijevanja](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za kritične informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.