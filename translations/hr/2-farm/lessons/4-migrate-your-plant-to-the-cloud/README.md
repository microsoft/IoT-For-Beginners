<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-28T14:59:02+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "hr"
}
-->
# Premjestite svoju biljku u oblak

![Sketchnote pregled ove lekcije](../../../../../translated_images/hr/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.jpg)

> Sketchnote autorice [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

Ova lekcija je dio [IoT za početnike Projekt 2 - Digitalna poljoprivreda serije](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) iz [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Povežite svoj uređaj s oblakom pomoću Azure IoT Hub-a](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Uvod

U prethodnoj lekciji naučili ste kako povezati svoju biljku s MQTT brokerom i upravljati relejem pomoću koda na lokalnom serveru. Ovo je osnova za vrstu internetski povezanog automatiziranog sustava za zalijevanje koji se koristi od pojedinačnih biljaka kod kuće do komercijalnih farmi.

IoT uređaj je komunicirao s javnim MQTT brokerom kako bi se demonstrirali principi, ali to nije najpouzdaniji ni najsigurniji način. U ovoj lekciji naučit ćete o oblaku i IoT mogućnostima koje pružaju javne usluge u oblaku. Također ćete naučiti kako premjestiti svoju biljku na jednu od tih usluga u oblaku s javnog MQTT brokera.

U ovoj lekciji obradit ćemo:

* [Što je oblak?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Kreiranje pretplate na oblak](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [IoT usluge u oblaku](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Kreiranje IoT usluge u oblaku](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Komunikacija s IoT Hub-om](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Povezivanje uređaja s IoT uslugom](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Što je oblak?

Prije oblaka, kada je neka tvrtka željela pružiti usluge svojim zaposlenicima (poput baza podataka ili pohrane datoteka) ili javnosti (poput web stranica), morali su izgraditi i upravljati podatkovnim centrom. To je moglo biti od sobe s nekoliko računala do zgrade s mnogo računala. Tvrtka bi upravljala svime, uključujući:

* Kupnju računala
* Održavanje hardvera
* Napajanje i hlađenje
* Umrežavanje
* Sigurnost, uključujući osiguranje zgrade i softvera na računalima
* Instalaciju i ažuriranje softvera

Ovo je moglo biti vrlo skupo, zahtijevati širok spektar stručnih zaposlenika i biti vrlo sporo za promjene kada je to potrebno. Na primjer, ako je internetska trgovina trebala planirati za užurbanu blagdansku sezonu, morali bi planirati mjesecima unaprijed kako bi kupili više hardvera, konfigurirali ga, instalirali i postavili softver za prodajni proces. Nakon blagdanske sezone, kada bi se prodaja smanjila, ostali bi s računalima koja su plaćena, ali neiskorištena do sljedeće užurbane sezone.

✅ Mislite li da bi ovo omogućilo tvrtkama da brzo reagiraju? Ako bi internetski trgovac odjećom iznenada postao popularan jer je neka slavna osoba viđena u njihovoj odjeći, bi li mogli dovoljno brzo povećati računalnu snagu kako bi podržali iznenadni priljev narudžbi?

### Računalo nekog drugog

Oblak se često u šali naziva "računalom nekog drugog". Početna ideja bila je jednostavna - umjesto kupnje računala, unajmite računalo nekog drugog. Netko drugi, pružatelj usluga računalstva u oblaku, upravljao bi ogromnim podatkovnim centrima. Oni bi bili odgovorni za kupnju i instalaciju hardvera, upravljanje napajanjem i hlađenjem, umrežavanje, sigurnost zgrade, ažuriranja hardvera i softvera, sve. Kao korisnik, unajmljujete računala koja su vam potrebna, unajmljujete više kada potražnja raste, a smanjujete broj kada potražnja opada. Ovi podatkovni centri nalaze se diljem svijeta.

![Microsoftov podatkovni centar u oblaku](../../../../../translated_images/hr/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.png)
![Planirano proširenje Microsoftovog podatkovnog centra u oblaku](../../../../../translated_images/hr/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.png)

Ovi podatkovni centri mogu biti veličine nekoliko četvornih kilometara. Gornje slike snimljene su prije nekoliko godina u Microsoftovom podatkovnom centru u oblaku i prikazuju početnu veličinu, zajedno s planiranim proširenjem. Površina očišćena za proširenje veća je od 5 četvornih kilometara.

> 💁 Ovi podatkovni centri zahtijevaju toliko velike količine energije da neki imaju vlastite elektrane. Zbog svoje veličine i razine ulaganja pružatelja usluga u oblaku, obično su vrlo ekološki prihvatljivi. Učinkovitiji su od velikog broja malih podatkovnih centara, uglavnom koriste obnovljive izvore energije, a pružatelji usluga u oblaku ulažu napore u smanjenje otpada, smanjenje potrošnje vode i ponovno pošumljavanje područja iskrčenih za izgradnju podatkovnih centara. Više o održivosti jednog pružatelja usluga u oblaku možete pročitati na [Azure stranici o održivosti](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Istražite: Pročitajte o glavnim oblacima poput [Azure od Microsofta](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) ili [GCP od Googlea](https://cloud.google.com). Koliko podatkovnih centara imaju i gdje se nalaze u svijetu?

Korištenje oblaka smanjuje troškove za tvrtke i omogućuje im da se usredotoče na ono što najbolje rade, ostavljajući stručnost za računalstvo u oblaku pružatelju usluga. Tvrtke više ne moraju unajmljivati ili kupovati prostor u podatkovnim centrima, plaćati različitim pružateljima za povezivost i energiju ili zapošljavati stručnjake. Umjesto toga, mogu plaćati jedan mjesečni račun pružatelju usluga u oblaku koji se brine o svemu.

Pružatelj usluga u oblaku tada može koristiti ekonomiju razmjera kako bi smanjio troškove, kupujući računala na veliko po nižim cijenama, ulažući u alate za smanjenje radnog opterećenja održavanja, pa čak i dizajnirajući i gradeći vlastiti hardver kako bi poboljšao svoju ponudu u oblaku.

### Microsoft Azure

Azure je oblak za programere iz Microsofta, i to je oblak koji ćete koristiti u ovim lekcijama. Video ispod daje kratak pregled Azurea:

[![Pregled Azure videa](../../../../../translated_images/hr/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Kreiranje pretplate na oblak

Kako biste koristili usluge u oblaku, trebate se prijaviti za pretplatu kod pružatelja usluga u oblaku. Za ovu lekciju prijavit ćete se za Microsoft Azure pretplatu. Ako već imate Azure pretplatu, možete preskočiti ovaj zadatak. Detalji pretplate opisani ovdje su točni u trenutku pisanja, ali se mogu promijeniti.

> 💁 Ako pristupate ovim lekcijama putem svoje škole, možda već imate dostupnu Azure pretplatu. Provjerite sa svojim učiteljem.

Postoje dvije različite vrste besplatnih Azure pretplata na koje se možete prijaviti:

* **Azure za studente** - Ovo je pretplata namijenjena studentima starijima od 18 godina. Nije vam potrebna kreditna kartica za prijavu, a koristite svoju školsku e-mail adresu za potvrdu da ste student. Kada se prijavite, dobivate 100 USD za trošenje na resurse u oblaku, zajedno s besplatnim uslugama, uključujući besplatnu verziju IoT usluge. Ovo traje 12 mjeseci i možete obnoviti svake godine dok ste student.

* **Besplatna Azure pretplata** - Ovo je pretplata za sve koji nisu studenti. Trebat će vam kreditna kartica za prijavu, ali vaša kartica neće biti naplaćena, već se koristi samo za potvrdu da ste stvarna osoba, a ne bot. Dobivate 200 USD kredita za korištenje u prvih 30 dana na bilo kojoj usluzi, zajedno s besplatnim razinama Azure usluga. Nakon što potrošite kredit, vaša kartica neće biti naplaćena osim ako ne pretvorite pretplatu u model plaćanja po korištenju.

> 💁 Microsoft nudi Azure za Students Starter pretplatu za studente mlađe od 18 godina, ali u trenutku pisanja ovo ne podržava IoT usluge.

### Zadatak - prijavite se za besplatnu pretplatu na oblak

Ako ste student stariji od 18 godina, možete se prijaviti za Azure za Studente pretplatu. Trebat ćete potvrditi školskom e-mail adresom. To možete učiniti na dva načina:

* Prijavite se za GitHub studentski razvojni paket na [education.github.com/pack](https://education.github.com/pack). Ovo vam daje pristup nizu alata i ponuda, uključujući GitHub i Microsoft Azure. Nakon što se prijavite za razvojni paket, možete aktivirati Azure za Studente ponudu.

* Prijavite se izravno za Azure za Studente račun na [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Ako vaša školska e-mail adresa nije prepoznata, otvorite [problem u ovom repozitoriju](https://github.com/Microsoft/IoT-For-Beginners/issues) i provjerit ćemo može li se dodati na popis dopuštenih za Azure za Studente.

Ako niste student ili nemate valjanu školsku e-mail adresu, možete se prijaviti za besplatnu Azure pretplatu.

* Prijavite se za besplatnu Azure pretplatu na [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## IoT usluge u oblaku

Javni testni MQTT broker koji ste koristili odličan je alat za učenje, ali ima nekoliko nedostataka za korištenje u komercijalnom okruženju:

* Pouzdanost - to je besplatna usluga bez jamstava i može se isključiti u bilo kojem trenutku
* Sigurnost - javna je, pa svatko može slušati vašu telemetriju ili slati naredbe za upravljanje vašim hardverom
* Performanse - dizajniran je za samo nekoliko testnih poruka, pa ne bi mogao podnijeti veliku količinu poruka
* Otkriće - nema načina da se zna koji su uređaji povezani

IoT usluge u oblaku rješavaju ove probleme. Njima upravljaju veliki pružatelji usluga u oblaku koji ulažu velika sredstva u pouzdanost i spremni su riješiti sve probleme koji se mogu pojaviti. Imaju ugrađenu sigurnost kako bi spriječili hakere da čitaju vaše podatke ili šalju lažne naredbe. Također su visokih performansi, sposobni obraditi milijune poruka svaki dan, koristeći prednosti oblaka za skaliranje prema potrebi.

> 💁 Iako za ove prednosti plaćate mjesečnu naknadu, većina pružatelja usluga u oblaku nudi besplatnu verziju svoje IoT usluge s ograničenim brojem poruka dnevno ili uređaja koji se mogu povezati. Ova besplatna verzija obično je više nego dovoljna za programere koji žele učiti o usluzi. U ovoj lekciji koristit ćete besplatnu verziju.

IoT uređaji povezuju se s uslugom u oblaku ili pomoću SDK-a za uređaje (biblioteke koja pruža kod za rad s značajkama usluge) ili izravno putem komunikacijskog protokola poput MQTT-a ili HTTP-a. SDK za uređaje obično je najlakši put jer automatski upravlja svime, poput znanja o tome koje teme objaviti ili pretplatiti se, te kako upravljati sigurnošću.

![Uređaji se povezuju s uslugom pomoću SDK-a za uređaje. Serverski kod također se povezuje s uslugom putem SDK-a](../../../../../translated_images/hr/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.png)

Vaš uređaj tada komunicira s drugim dijelovima vaše aplikacije putem ove usluge - slično kao što ste slali telemetriju i primali naredbe putem MQTT-a. To se obično radi pomoću SDK-a za usluge ili slične biblioteke. Poruke dolaze s vašeg uređaja na uslugu gdje ih drugi dijelovi vaše aplikacije mogu pročitati, a poruke se mogu poslati natrag na vaš uređaj.

![Uređaji bez valjanog tajnog ključa ne mogu se povezati s IoT uslugom](../../../../../translated_images/hr/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.png)

Ove usluge implementiraju sigurnost tako što znaju za sve uređaje koji se mogu povezati i slati podatke, bilo da su uređaji unaprijed registrirani s uslugom ili im se daju tajni ključevi ili certifikati koje mogu koristiti za registraciju pri prvom povezivanju. Nepoznati uređaji ne mogu se povezati; ako pokušaju, usluga odbija vezu i ignorira poruke koje šalju.

✅ Istražite: Koji je nedostatak otvorene IoT usluge gdje se bilo koji uređaj ili kod može povezati? Možete li pronaći specifične primjere hakera koji su to iskoristili?

Ostali dijelovi vaše aplikacije mogu se povezati s IoT uslugom i saznati sve o uređajima koji su povezani ili registrirani te komunicirati s njima izravno, bilo pojedinačno ili u grupama.
💁 IoT usluge također implementiraju dodatne mogućnosti, a pružatelji usluga u oblaku imaju dodatne usluge i aplikacije koje se mogu povezati s uslugom. Na primjer, ako želite pohraniti sve telemetrijske poruke koje šalju svi uređaji u bazu podataka, obično je potrebno samo nekoliko klikova u alatu za konfiguraciju pružatelja usluga u oblaku kako biste povezali uslugu s bazom podataka i usmjerili podatke.
## Kreiranje IoT usluge u oblaku

Sada kada imate Azure pretplatu, možete se prijaviti za IoT uslugu. IoT usluga od Microsofta zove se Azure IoT Hub.

![Logotip Azure IoT Hub](../../../../../translated_images/hr/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.png)

Video ispod daje kratak pregled Azure IoT Hub-a:

[![Pregled videa Azure IoT Hub](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Kliknite na sliku iznad za gledanje videa

✅ Odvojite trenutak za istraživanje i pročitajte pregled IoT Hub-a u [Microsoft IoT Hub dokumentaciji](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

Cloud usluge dostupne u Azure-u mogu se konfigurirati putem web-portala ili putem sučelja naredbenog retka (CLI). Za ovaj zadatak koristit ćete CLI.

### Zadatak - instalacija Azure CLI-a

Da biste koristili Azure CLI, prvo ga morate instalirati na svoje računalo ili Mac.

1. Slijedite upute u [Azure CLI dokumentaciji](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) za instalaciju CLI-a.

1. Azure CLI podržava niz ekstenzija koje dodaju mogućnosti za upravljanje širokim rasponom Azure usluga. Instalirajte IoT ekstenziju pokretanjem sljedeće naredbe iz naredbenog retka ili terminala:

    ```sh
    az extension add --name azure-iot
    ```

1. Iz svog naredbenog retka ili terminala pokrenite sljedeću naredbu za prijavu na svoju Azure pretplatu putem Azure CLI-a.

    ```sh
    az login
    ```

    Web stranica će se otvoriti u vašem zadanom pregledniku. Prijavite se koristeći račun koji ste koristili za prijavu na svoju Azure pretplatu. Nakon što se prijavite, možete zatvoriti karticu preglednika.

1. Ako imate više Azure pretplata, poput one koju vam je osigurala škola i vlastite Azure for Students pretplate, morat ćete odabrati onu koju želite koristiti. Pokrenite sljedeću naredbu za popis svih pretplata kojima imate pristup:

    ```sh
    az account list --output table
    ```

    U izlazu ćete vidjeti naziv svake pretplate zajedno s njenim `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Za odabir pretplate koju želite koristiti, koristite sljedeću naredbu:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Zamijenite `<SubscriptionId>` s ID-jem pretplate koju želite koristiti. Nakon pokretanja ove naredbe, ponovno pokrenite naredbu za popis svojih računa. Vidjet ćete da je stupac `IsDefault` označen kao `True` za pretplatu koju ste upravo postavili.

### Zadatak - kreiranje grupe resursa

Azure usluge, poput IoT Hub instanci, virtualnih strojeva, baza podataka ili AI usluga, nazivaju se **resursima**. Svaki resurs mora biti smješten unutar **Grupe resursa**, logičke grupe jednog ili više resursa.

> 💁 Korištenje grupa resursa omogućuje upravljanje više usluga odjednom. Na primjer, nakon što završite sve lekcije za ovaj projekt, možete izbrisati grupu resursa, a svi resursi unutar nje bit će automatski izbrisani.

1. Postoji više Azure podatkovnih centara diljem svijeta, podijeljenih u regije. Kada kreirate Azure resurs ili grupu resursa, morate odrediti gdje želite da bude kreirana. Pokrenite sljedeću naredbu za dobivanje popisa lokacija:

    ```sh
    az account list-locations --output table
    ```

    Vidjet ćete popis lokacija. Ovaj popis će biti dug.

    > 💁 U trenutku pisanja, postoji 65 lokacija na koje možete implementirati resurse.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Zabilježite vrijednost iz stupca `Name` regije koja vam je najbliža. Regije možete pronaći na karti na [Azure geographies stranici](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Pokrenite sljedeću naredbu za kreiranje grupe resursa nazvane `soil-moisture-sensor`. Nazivi grupa resursa moraju biti jedinstveni unutar vaše pretplate.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Zamijenite `<location>` s lokacijom koju ste odabrali u prethodnom koraku.

### Zadatak - kreiranje IoT Hub-a

Sada možete kreirati IoT Hub resurs unutar svoje grupe resursa.

1. Koristite sljedeću naredbu za kreiranje IoT Hub resursa:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Zamijenite `<hub_name>` s nazivom za vaš hub. Ovaj naziv mora biti globalno jedinstven - to znači da nijedan drugi IoT Hub kreiran od strane bilo koga ne može imati isti naziv. Ovaj naziv se koristi u URL-u koji pokazuje na hub, pa mora biti jedinstven. Koristite nešto poput `soil-moisture-sensor-` i dodajte jedinstveni identifikator na kraju, poput nasumičnih riječi ili vašeg imena.

    Opcija `--sku F1` govori da se koristi besplatni nivo. Besplatni nivo podržava 8,000 poruka dnevno zajedno s većinom značajki punih nivoa.

    > 🎓 Različiti cjenovni nivoi Azure usluga nazivaju se tier-ovima. Svaki tier ima različite troškove i pruža različite značajke ili količine podataka.

    > 💁 Ako želite saznati više o cijenama, možete pogledati [Azure IoT Hub vodič za cijene](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    Opcija `--partition-count 2` definira koliko tokova podataka IoT Hub podržava, više particija smanjuje blokiranje podataka kada više stvari čita i piše iz IoT Hub-a. Particije su izvan opsega ovih lekcija, ali ova vrijednost mora biti postavljena za kreiranje besplatnog nivoa IoT Hub-a.

    > 💁 Možete imati samo jedan besplatni nivo IoT Hub-a po pretplati.

IoT Hub će biti kreiran. Može potrajati minutu ili dvije da se proces završi.

## Komunikacija s IoT Hub-om

U prethodnoj lekciji koristili ste MQTT i slali poruke naprijed-nazad na različitim temama, pri čemu su različite teme imale različite svrhe. Umjesto slanja poruka preko različitih tema, IoT Hub ima nekoliko definiranih načina za komunikaciju uređaja s Hub-om ili Hub-a s uređajem.

> 💁 U pozadini, ova komunikacija između IoT Hub-a i vašeg uređaja može koristiti MQTT, HTTPS ili AMQP.

* Poruke od uređaja prema oblaku (D2C) - to su poruke koje uređaj šalje IoT Hub-u, poput telemetrije. One se zatim mogu čitati iz IoT Hub-a pomoću vašeg aplikacijskog koda.

    > 🎓 U pozadini, IoT Hub koristi Azure uslugu zvanu [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Kada pišete kod za čitanje poruka poslanih na hub, one se često nazivaju događajima.

* Poruke od oblaka prema uređaju (C2D) - to su poruke koje aplikacijski kod šalje putem IoT Hub-a na IoT uređaj.

* Zahtjevi za direktne metode - to su poruke koje aplikacijski kod šalje putem IoT Hub-a na IoT uređaj kako bi zatražio da uređaj nešto učini, poput upravljanja aktuatorom. Ove poruke zahtijevaju odgovor kako bi vaš aplikacijski kod mogao znati je li uspješno obrađen.

* Device twins - to su JSON dokumenti koji se sinkroniziraju između uređaja i IoT Hub-a, a koriste se za pohranu postavki ili drugih svojstava koje uređaj prijavljuje ili koje bi trebale biti postavljene na uređaju (poznato kao željeno) od strane IoT Hub-a.

IoT Hub može pohraniti poruke i zahtjeve za direktne metode na konfigurabilno razdoblje (zadano je jedan dan), tako da ako uređaj ili aplikacijski kod izgubi vezu, može ponovno dohvatiti poruke poslane dok je bio offline nakon što se ponovno poveže. Device twins se trajno čuvaju u IoT Hub-u, tako da uređaj u bilo kojem trenutku može ponovno povezati i dobiti najnoviji device twin.

✅ Istražite: Pročitajte više o ovim vrstama poruka u [Vodiču za komunikaciju od uređaja prema oblaku](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) i [Vodiču za komunikaciju od oblaka prema uređaju](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) u IoT Hub dokumentaciji.

## Povezivanje vašeg uređaja s IoT uslugom

Nakon što je hub kreiran, vaš IoT uređaj može se povezati s njim. Samo registrirani uređaji mogu se povezati s uslugom, pa ćete prvo morati registrirati svoj uređaj. Kada se registrirate, možete dobiti natrag connection string koji uređaj može koristiti za povezivanje. Ovaj connection string je specifičan za uređaj i sadrži informacije o IoT Hub-u, uređaju i tajni ključ koji omogućuje ovom uređaju povezivanje.

> 🎓 Connection string je generički izraz za tekst koji sadrži detalje povezivanja. Koriste se pri povezivanju s IoT Hub-ovima, bazama podataka i mnogim drugim uslugama. Obično se sastoje od identifikatora za uslugu, poput URL-a, i sigurnosnih informacija poput tajnog ključa. Prosljeđuju se SDK-ovima za povezivanje s uslugom.

> ⚠️ Connection string-ovi trebaju se čuvati sigurnima! Sigurnost će biti detaljnije obrađena u budućoj lekciji.

### Zadatak - registracija vašeg IoT uređaja

IoT uređaj može se registrirati s vašim IoT Hub-om koristeći Azure CLI.

1. Pokrenite sljedeću naredbu za registraciju uređaja:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Zamijenite `<hub_name>` s nazivom koji ste koristili za svoj IoT Hub.

    Ovo će kreirati uređaj s ID-jem `soil-moisture-sensor`.

1. Kada se vaš IoT uređaj povezuje s vašim IoT Hub-om koristeći SDK, mora koristiti connection string koji daje URL hub-a, zajedno s tajnim ključem. Pokrenite sljedeću naredbu za dobivanje connection string-a:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Zamijenite `<hub_name>` s nazivom koji ste koristili za svoj IoT Hub.

1. Spremite connection string prikazan u izlazu jer će vam kasnije trebati.

### Zadatak - povezivanje vašeg IoT uređaja s oblakom

Prođite kroz odgovarajući vodič za povezivanje vašeg IoT uređaja s oblakom:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Jednoboardno računalo - Raspberry Pi/Virtualni IoT uređaj](single-board-computer-connect-hub.md)

### Zadatak - praćenje događaja

Za sada nećete ažurirati svoj server kod. Umjesto toga, možete koristiti Azure CLI za praćenje događaja s vašeg IoT uređaja.

1. Provjerite je li vaš IoT uređaj pokrenut i šalje telemetrijske vrijednosti vlažnosti tla.

1. Pokrenite sljedeću naredbu u svom naredbenom retku ili terminalu za praćenje poruka poslanih na vaš IoT Hub:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Zamijenite `<hub_name>` s nazivom koji ste koristili za svoj IoT Hub.

    Vidjet ćete poruke koje se pojavljuju u izlazu konzole dok ih vaš IoT uređaj šalje.

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

    Sadržaj `payload` će odgovarati poruci koju je poslao vaš IoT uređaj.

    > U trenutku pisanja, `az iot` ekstenzija ne radi u potpunosti na Apple Silicon-u. Ako koristite Apple Silicon uređaj, morat ćete pratiti poruke na drugačiji način, poput korištenja [Azure IoT Tools za Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Ove poruke imaju nekoliko svojstava automatski pridruženih, poput vremenske oznake kada su poslane. Ova svojstva poznata su kao *annotacije*. Za pregled svih annotacija poruka, koristite sljedeću naredbu:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Zamijenite `<hub_name>` s nazivom koji ste koristili za svoj IoT Hub.

    Vidjet ćete poruke koje se pojavljuju u izlazu konzole dok ih vaš IoT uređaj šalje.

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

    Vrijednosti vremena u annotacijama su u [UNIX vremenu](https://wikipedia.org/wiki/Unix_time), što predstavlja broj sekundi od ponoći 1. siječnja 1970.

    Izađite iz monitora događaja kada završite.

### Zadatak - upravljanje vašim IoT uređajem

Također možete koristiti Azure CLI za pozivanje direktnih metoda na vašem IoT uređaju.

1. Pokrenite sljedeću naredbu u svom naredbenom retku ili terminalu za pozivanje metode `relay_on` na IoT uređaju:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Zamijenite `
<hub_name>
` s imenom koje ste koristili za svoj IoT Hub.

    Ovo šalje zahtjev za izravnu metodu za metodu specificiranu pomoću `method-name`. Izravne metode mogu primiti podatke u obliku JSON-a koji se prosljeđuju kao `method-payload`.

    Vidjet ćete kako se relej uključuje i odgovarajući izlaz s vašeg IoT uređaja:

    ```output
    Direct method received -  relay_on
    ```

1. Ponovite gornji korak, ali postavite `--method-name` na `relay_off`. Vidjet ćete kako se relej isključuje i odgovarajući izlaz s IoT uređaja.

---

## 🚀 Izazov

Besplatni sloj IoT Huba omogućuje 8.000 poruka dnevno. Kod koji ste napisali šalje telemetrijske poruke svakih 10 sekundi. Koliko je to poruka dnevno ako se šalje jedna poruka svakih 10 sekundi?

Razmislite o tome koliko često bi se trebala slati mjerenja vlažnosti tla? Kako možete promijeniti svoj kod da ostanete unutar granica besplatnog sloja, a da i dalje provjeravate dovoljno često, ali ne prečesto? Što ako želite dodati drugi uređaj?

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Pregled i samostalno učenje

IoT Hub SDK je otvorenog koda za Arduino i Python. U repozitorijima koda na GitHubu nalazi se niz primjera koji pokazuju kako raditi s različitim značajkama IoT Huba.

* Ako koristite Wio Terminal, pogledajte [Arduino primjere na GitHubu](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Ako koristite Raspberry Pi ili virtualni uređaj, pogledajte [Python primjere na GitHubu](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Zadatak

[Saznajte više o cloud uslugama](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.