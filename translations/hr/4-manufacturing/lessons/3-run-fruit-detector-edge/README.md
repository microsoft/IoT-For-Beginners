# Pokrenite svoj detektor voća na rubu

![Pregled lekcije u obliku sketchnotea](../../../../../translated_images/hr/lesson-17.bc333c3c35ba8e42.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

Ovaj video daje pregled pokretanja klasifikatora slika na IoT uređajima, tema koja se obrađuje u ovoj lekciji.

[![Custom Vision AI na Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Uvod

U prošloj lekciji koristili ste svoj klasifikator slika za klasifikaciju zrelog i nezrelog voća, šaljući sliku snimljenu kamerom na vašem IoT uređaju putem interneta na uslugu u oblaku. Takvi pozivi zahtijevaju vrijeme, koštaju novac, a ovisno o vrsti podataka koje koristite, mogu imati implikacije na privatnost.

U ovoj lekciji naučit ćete kako pokretati modele strojnog učenja (ML) na rubu - na IoT uređajima koji rade na vašoj vlastitoj mreži, a ne u oblaku. Naučit ćete prednosti i nedostatke rubnog računalstva u usporedbi s računalstvom u oblaku, kako implementirati svoj AI model na rubu i kako mu pristupiti s vašeg IoT uređaja.

U ovoj lekciji obradit ćemo:

* [Rubno računalstvo](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Registracija IoT Edge uređaja](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Postavljanje IoT Edge uređaja](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Izvoz vašeg modela](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Priprema vašeg kontejnera za implementaciju](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Implementacija vašeg kontejnera](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Korištenje vašeg IoT Edge uređaja](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Rubno računalstvo

Rubno računalstvo uključuje korištenje računala koja obrađuju IoT podatke što bliže mjestu gdje se ti podaci generiraju. Umjesto da se obrada odvija u oblaku, ona se premješta na rub oblaka - vašu internu mrežu.

![Dijagram arhitekture koji prikazuje internetske usluge u oblaku i IoT uređaje na lokalnoj mreži](../../../../../translated_images/hr/cloud-without-edge.b4da641f6022c95e.webp)

U dosadašnjim lekcijama, imali ste uređaje koji prikupljaju podatke i šalju ih u oblak na analizu, pokrećući funkcije bez poslužitelja ili AI modele u oblaku.

![Dijagram arhitekture koji prikazuje IoT uređaje na lokalnoj mreži povezane s rubnim uređajima, a ti rubni uređaji povezani su s oblakom](../../../../../translated_images/hr/cloud-with-edge.1e26462c62c126fe.webp)

Rubno računalstvo uključuje premještanje nekih usluga iz oblaka na računala koja rade na istoj mreži kao i IoT uređaji, komunicirajući s oblakom samo kada je to potrebno. Na primjer, možete pokretati AI modele na rubnim uređajima za analizu zrelosti voća, a u oblak slati samo analitiku, poput broja zrelih i nezrelih komada voća.

✅ Razmislite o IoT aplikacijama koje ste dosad izgradili. Koji dijelovi njih bi se mogli premjestiti na rub?

### Prednosti

Prednosti rubnog računalstva su:

1. **Brzina** - rubno računalstvo idealno je za podatke osjetljive na vrijeme jer se radnje obavljaju na istoj mreži kao i uređaj, umjesto da se pozivi obavljaju putem interneta. To omogućuje veće brzine jer interne mreže mogu raditi znatno brže od internetskih veza, s podacima koji putuju mnogo kraće udaljenosti.

    > 💁 Iako se optički kablovi koriste za internetske veze omogućujući podatcima da putuju brzinom svjetlosti, podacima može trebati vremena da putuju diljem svijeta do pružatelja usluga u oblaku. Na primjer, ako šaljete podatke iz Europe u oblak u SAD-u, potrebno je najmanje 28 ms da podaci prijeđu Atlantik optičkim kabelom, a to ne uključuje vrijeme potrebno za prijenos podataka do transatlantskog kabela, pretvorbu iz električnih u svjetlosne signale i obrnuto na drugoj strani, te prijenos od optičkog kabela do pružatelja usluga u oblaku.

    Rubno računalstvo također zahtijeva manje mrežnog prometa, smanjujući rizik od usporavanja podataka zbog zagušenja na ograničenoj propusnosti dostupnoj za internetsku vezu.

1. **Pristup u udaljenim područjima** - rubno računalstvo funkcionira kada imate ograničenu ili nikakvu povezanost, ili kada je povezanost preskupa za kontinuirano korištenje. Na primjer, u humanitarnim kriznim područjima gdje je infrastruktura ograničena ili u zemljama u razvoju.

1. **Niži troškovi** - prikupljanje, pohrana, analiza podataka i pokretanje radnji na rubnim uređajima smanjuje korištenje usluga u oblaku, što može smanjiti ukupne troškove vaše IoT aplikacije. Nedavno je zabilježen porast uređaja dizajniranih za rubno računalstvo, poput AI akceleratorskih ploča kao što je [Jetson Nano od NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), koji mogu pokretati AI radne zadatke koristeći GPU hardver na uređajima koji koštaju manje od 100 USD.

1. **Privatnost i sigurnost** - s rubnim računalstvom, podaci ostaju na vašoj mreži i ne prenose se u oblak. To je često poželjno za osjetljive i osobno identificirajuće informacije, posebno jer podaci ne moraju biti pohranjeni nakon analize, što značajno smanjuje rizik od curenja podataka. Primjeri uključuju medicinske podatke i snimke sigurnosnih kamera.

1. **Rukovanje nesigurnim uređajima** - ako imate uređaje s poznatim sigurnosnim nedostacima koje ne želite izravno povezati s vašom mrežom ili internetom, možete ih povezati na zasebnu mrežu s gateway IoT Edge uređajem. Taj rubni uređaj može također imati vezu s vašom širim mrežom ili internetom i upravljati protokom podataka.

1. **Podrška za nekompatibilne uređaje** - ako imate uređaje koji se ne mogu povezati s IoT Hubom, na primjer uređaje koji se mogu povezati samo putem HTTP veza ili uređaje koji imaju samo Bluetooth za povezivanje, možete koristiti IoT Edge uređaj kao gateway uređaj koji prosljeđuje poruke IoT Hubu.

✅ Istražite: Koje bi još prednosti mogle postojati za rubno računalstvo?

### Nedostaci

Postoje nedostaci rubnog računalstva, gdje oblak može biti preferirana opcija:

1. **Skalabilnost i fleksibilnost** - računalstvo u oblaku može se prilagoditi mrežnim i podatkovnim potrebama u stvarnom vremenu dodavanjem ili smanjenjem poslužitelja i drugih resursa. Dodavanje više rubnih računala zahtijeva ručno dodavanje više uređaja.

1. **Pouzdanost i otpornost** - računalstvo u oblaku pruža više poslužitelja često na više lokacija za redundanciju i oporavak od katastrofa. Da biste imali istu razinu redundancije na rubu, potrebna su velika ulaganja i puno konfiguracijskog rada.

1. **Održavanje** - pružatelji usluga u oblaku pružaju održavanje sustava i ažuriranja.

✅ Istražite: Koji bi još nedostaci mogli postojati za rubno računalstvo?

Nedostaci su zapravo suprotnosti prednostima korištenja oblaka - morate sami izgraditi i upravljati tim uređajima, umjesto da se oslanjate na stručnost i skalabilnost pružatelja usluga u oblaku.

Neki od rizika ublaženi su samom prirodom rubnog računalstva. Na primjer, ako imate rubni uređaj koji radi u tvornici prikupljajući podatke s strojeva, ne morate razmišljati o nekim scenarijima oporavka od katastrofa. Ako nestane struje u tvornici, ne trebate rezervni rubni uređaj jer strojevi koji generiraju podatke koje rubni uređaj obrađuje također neće imati struju.

Za IoT sustave, često ćete željeti kombinaciju računalstva u oblaku i na rubu, koristeći svaku uslugu na temelju potreba sustava, njegovih korisnika i njegovih održavatelja.

## Azure IoT Edge

![Logotip Azure IoT Edge](../../../../../translated_images/hr/azure-iot-edge-logo.c1c076749b5cba2e.webp)

Azure IoT Edge je usluga koja vam može pomoći da premjestite radne zadatke iz oblaka na rub. Postavljate uređaj kao rubni uređaj, a iz oblaka možete implementirati kod na taj rubni uređaj. To vam omogućuje kombiniranje mogućnosti oblaka i ruba.

> 🎓 *Radni zadaci* je pojam za bilo koju uslugu koja obavlja neki posao, poput AI modela, aplikacija ili funkcija bez poslužitelja.

Na primjer, možete trenirati klasifikator slika u oblaku, a zatim ga iz oblaka implementirati na rubni uređaj. Vaš IoT uređaj tada šalje slike rubnom uređaju na klasifikaciju, umjesto da šalje slike putem interneta. Ako trebate implementirati novu iteraciju modela, možete ga trenirati u oblaku i koristiti IoT Edge za ažuriranje modela na rubnom uređaju na novu iteraciju.

> 🎓 Softver koji se implementira na IoT Edge poznat je kao *moduli*. Prema zadanim postavkama IoT Edge pokreće module koji komuniciraju s IoT Hubom, poput modula `edgeAgent` i `edgeHub`. Kada implementirate klasifikator slika, on se implementira kao dodatni modul.

IoT Edge je ugrađen u IoT Hub, tako da možete upravljati rubnim uređajima koristeći istu uslugu koju biste koristili za upravljanje IoT uređajima, s istom razinom sigurnosti.

IoT Edge pokreće kod iz *kontejnera* - samostalnih aplikacija koje se pokreću izolirano od ostatka aplikacija na vašem računalu. Kada pokrenete kontejner, on djeluje kao zasebno računalo koje radi unutar vašeg računala, sa svojim vlastitim softverom, uslugama i aplikacijama. Većinu vremena kontejneri ne mogu pristupiti ničemu na vašem računalu osim ako ne odlučite dijeliti stvari poput mape s kontejnerom. Kontejner tada izlaže usluge putem otvorenog porta kojem možete pristupiti ili ga izložiti svojoj mreži.

![Web zahtjev preusmjeren na kontejner](../../../../../translated_images/hr/container-web-browser.4ee81dd4f0d8838c.webp)

Na primjer, možete imati kontejner s web stranicom koja radi na portu 80, zadani HTTP port, i možete ga izložiti sa svog računala također na portu 80.

✅ Istražite: Pročitajte o kontejnerima i uslugama poput Dockera ili Mobyja.

Možete koristiti Custom Vision za preuzimanje klasifikatora slika i implementaciju kao kontejnera, bilo direktno na uređaj ili putem IoT Edgea. Kada se pokreću u kontejneru, mogu se pristupiti koristeći isti REST API kao i verziji u oblaku, ali s krajnjom točkom koja pokazuje na rubni uređaj koji pokreće kontejner.

## Registracija IoT Edge uređaja

Da biste koristili IoT Edge uređaj, potrebno ga je registrirati u IoT Hubu.

### Zadatak - registracija IoT Edge uređaja

1. Kreirajte IoT Hub u resursnoj grupi `fruit-quality-detector`. Dajte mu jedinstveno ime bazirano na `fruit-quality-detector`.

1. Registrirajte IoT Edge uređaj nazvan `fruit-quality-detector-edge` u svom IoT Hubu. Naredba za to je slična onoj koja se koristi za registraciju uređaja koji nije rubni, osim što dodajete zastavicu `--edge-enabled`.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Zamijenite `<hub_name>` imenom vašeg IoT Huba.

1. Dobijte vezni niz za svoj uređaj koristeći sljedeću naredbu:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Zamijenite `<hub_name>` imenom vašeg IoT Huba.

    Kopirajte vezni niz prikazan u izlazu.

## Postavljanje IoT Edge uređaja

Nakon što ste kreirali registraciju rubnog uređaja u svom IoT Hubu, možete postaviti rubni uređaj.

### Zadatak - Instalacija i pokretanje IoT Edge Runtimea

**IoT Edge Runtime pokreće samo Linux kontejnere.** Može se pokrenuti na Linuxu ili na Windowsu koristeći Linux virtualne strojeve.

* Ako koristite Raspberry Pi kao svoj IoT uređaj, on pokreće podržanu verziju Linuxa i može ugostiti IoT Edge Runtime. Slijedite [vodič za instalaciju Azure IoT Edge za Linux na Microsoft dokumentaciji](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) za instalaciju IoT Edgea i postavljanje veznog niza.

    > 💁 Zapamtite, Raspberry Pi OS je varijanta Debian Linuxa.

* Ako ne koristite Raspberry Pi, ali imate Linux računalo, možete pokrenuti IoT Edge Runtime. Slijedite [vodič za instalaciju Azure IoT Edge za Linux na Microsoft dokumentaciji](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) za instalaciju IoT Edgea i postavljanje veznog niza.

* Ako koristite Windows, možete instalirati IoT Edge Runtime u Linux virtualni stroj slijedeći [sekciju za instalaciju i pokretanje IoT Edge Runtimea u vodiču za brzo pokretanje na Microsoft dokumentaciji](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Možete stati kada dođete do sekcije *Implementacija modula*.

* Ako koristite macOS, možete kreirati virtualni stroj (VM) u oblaku za korištenje kao svoj IoT Edge uređaj. To su računala koja možete kreirati u oblaku i pristupiti im putem interneta. Možete kreirati Linux VM koji ima instaliran IoT Edge. Slijedite [vodič za kreiranje virtualnog stroja koji pokreće IoT Edge](vm-iotedge.md) za upute kako to učiniti.

## Izvoz vašeg modela

Da biste pokrenuli klasifikator na rubu, potrebno ga je izvesti iz Custom Visiona. Custom Vision može generirati dvije vrste modela - standardne modele i kompaktne modele. Kompaktni modeli koriste razne tehnike za smanjenje veličine modela, čineći ga dovoljno malim za preuzimanje i implementaciju na IoT uređajima.

Kada ste kreirali klasifikator slika, koristili ste *Food* domenu, verziju modela koja je optimizirana za treniranje na slikama hrane. U Custom Visionu, možete promijeniti domenu svog projekta, koristeći svoje podatke za treniranje novog modela s novom domenom. Sve domene koje podržava Custom Vision dostupne su kao standardne i kompaktne.

### Zadatak - treniranje vašeg modela koristeći Food (compact) domenu
1. Pokrenite Custom Vision portal na [CustomVision.ai](https://customvision.ai) i prijavite se ako već nije otvoren. Zatim otvorite svoj projekt `fruit-quality-detector`.

1. Odaberite gumb **Settings** (ikona ⚙).

1. Na popisu *Domains* odaberite *Food (compact)*.

1. Pod *Export Capabilities*, provjerite je li odabrano *Basic platforms (Tensorflow, CoreML, ONNX, ...)*.

1. Na dnu stranice Settings odaberite **Save Changes**.

1. Ponovno trenirajte model pomoću gumba **Train**, odabirom *Quick training*.

### Zadatak - izvoz modela

Nakon što je model treniran, potrebno ga je izvesti kao kontejner.

1. Odaberite karticu **Performance** i pronađite najnoviju iteraciju koja je trenirana koristeći compact domain.

1. Kliknite gumb **Export** na vrhu.

1. Odaberite **DockerFile**, zatim odaberite verziju koja odgovara vašem edge uređaju:

    * Ako koristite IoT Edge na Linux računalu, Windows računalu ili virtualnom stroju, odaberite verziju *Linux*.
    * Ako koristite IoT Edge na Raspberry Pi, odaberite verziju *ARM (Raspberry Pi 3)*.

> 🎓 Docker je jedan od najpopularnijih alata za upravljanje kontejnerima, a DockerFile je skup uputa za postavljanje kontejnera.

1. Kliknite **Export** kako bi Custom Vision kreirao relevantne datoteke, zatim **Download** za preuzimanje u zip datoteci.

1. Spremite datoteke na svoje računalo, zatim raspakirajte mapu.

## Priprema kontejnera za implementaciju

![Kontejneri se kreiraju, zatim šalju u registry kontejnera, a potom se implementiraju na edge uređaj koristeći IoT Edge](../../../../../translated_images/hr/container-edge-flow.c246050dd60ceefd.webp)

Nakon što ste preuzeli svoj model, potrebno ga je izgraditi u kontejner, a zatim poslati u registry kontejnera - online lokaciju za pohranu kontejnera. IoT Edge može zatim preuzeti kontejner iz registryja i poslati ga na vaš uređaj.

![Logo Azure Container Registry](../../../../../translated_images/hr/azure-container-registry-logo.09494206991d4b29.webp)

Registry kontejnera koji ćete koristiti za ovu lekciju je Azure Container Registry. Ovo nije besplatna usluga, pa kako biste uštedjeli novac, pobrinite se da [očistite svoj projekt](../../../clean-up.md) nakon što završite.

> 💁 Troškove korištenja Azure Container Registry možete vidjeti na [stranici s cijenama Azure Container Registry](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Zadatak - instalacija Dockera

Za izgradnju i implementaciju klasifikatora, možda ćete trebati instalirati [Docker](https://www.docker.com/).

To ćete trebati učiniti samo ako planirate izgraditi svoj kontejner na drugom uređaju od onog na kojem ste instalirali IoT Edge - kao dio instalacije IoT Edge, Docker se automatski instalira.

1. Ako gradite Docker kontejner na drugom uređaju od vašeg IoT Edge uređaja, slijedite upute za instalaciju Dockera na [stranici za instalaciju Dockera](https://www.docker.com/products/docker-desktop) kako biste instalirali Docker Desktop ili Docker engine. Provjerite da je pokrenut nakon instalacije.

### Zadatak - kreiranje resursa registryja kontejnera

1. Pokrenite sljedeću naredbu iz terminala ili command prompta kako biste kreirali resurs Azure Container Registry:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Zamijenite `<Container registry name>` jedinstvenim nazivom za vaš registry kontejnera, koristeći samo slova i brojeve. Bazirajte naziv na `fruitqualitydetector`. Ovaj naziv postaje dio URL-a za pristup registryju kontejnera, pa mora biti globalno jedinstven.

1. Prijavite se u Azure Container Registry pomoću sljedeće naredbe:

    ```sh
    az acr login --name <Container registry name>
    ```

    Zamijenite `<Container registry name>` nazivom koji ste koristili za vaš registry kontejnera.

1. Postavite registry kontejnera u admin način rada kako biste mogli generirati lozinku pomoću sljedeće naredbe:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Zamijenite `<Container registry name>` nazivom koji ste koristili za vaš registry kontejnera.

1. Generirajte lozinke za vaš registry kontejnera pomoću sljedeće naredbe:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Zamijenite `<Container registry name>` nazivom koji ste koristili za vaš registry kontejnera.

    Zabilježite vrijednost `PASSWORD`, jer će vam trebati kasnije.

### Zadatak - izgradnja kontejnera

Ono što ste preuzeli iz Custom Visiona bio je DockerFile koji sadrži upute o tome kako kontejner treba biti izgrađen, zajedno s aplikacijskim kodom koji će se pokrenuti unutar kontejnera za hostanje vašeg modela Custom Vision, zajedno s REST API-jem za pozivanje.

> 🎓 Kontejnerima se dodjeljuje oznaka koja definira naziv i verziju. Kada trebate ažurirati kontejner, možete ga izgraditi s istom oznakom, ali novijom verzijom.

1. Otvorite terminal ili command prompt i navigirajte do raspakiranog modela koji ste preuzeli iz Custom Visiona.

1. Pokrenite sljedeću naredbu za izgradnju i označavanje slike:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Zamijenite `<platform>` platformom na kojoj će ovaj kontejner biti pokrenut. Ako koristite IoT Edge na Raspberry Pi, postavite ovo na `linux/armhf`, inače postavite na `linux/amd64`.

    > 💁 Ako pokrećete ovu naredbu s uređaja na kojem koristite IoT Edge, kao što je Raspberry Pi, možete izostaviti dio `--platform <platform>` jer se automatski postavlja na trenutnu platformu.

    Zamijenite `<Container registry name>` nazivom koji ste koristili za vaš registry kontejnera.

    > 💁 Ako koristite Linux ili Raspberry Pi OS, možda ćete trebati koristiti `sudo` za pokretanje ove naredbe.

    Docker će izgraditi sliku, konfigurirajući sav potreban softver. Slika će zatim biti označena kao `classifier:v1`.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### Zadatak - slanje kontejnera u registry kontejnera

1. Koristite sljedeću naredbu za slanje vašeg kontejnera u registry kontejnera:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Zamijenite `<Container registry name>` nazivom koji ste koristili za vaš registry kontejnera.

    > 💁 Ako koristite Linux, možda ćete trebati koristiti `sudo` za pokretanje ove naredbe.

    Kontejner će biti poslan u registry kontejnera.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. Za provjeru slanja, možete popisati kontejnere u vašem registryju pomoću sljedeće naredbe:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Zamijenite `<Container registry name>` nazivom koji ste koristili za vaš registry kontejnera.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Vidjet ćete vaš klasifikator na popisu u izlazu.

## Implementacija kontejnera

Vaš kontejner sada može biti implementiran na vaš IoT Edge uređaj. Za implementaciju trebate definirati manifest implementacije - JSON dokument koji navodi module koji će biti implementirani na edge uređaj.

### Zadatak - kreiranje manifesta implementacije

1. Kreirajte novu datoteku nazvanu `deployment.json` negdje na vašem računalu.

1. Dodajte sljedeće u ovu datoteku:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 Ovu datoteku možete pronaći u mapi [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    Zamijenite tri instance `<Container registry name>` nazivom koji ste koristili za vaš registry kontejnera. Jedna je u sekciji `ImageClassifier` modula, a druge dvije su u sekciji `registryCredentials`.

    Zamijenite `<Container registry password>` u sekciji `registryCredentials` vašom lozinkom registryja kontejnera.

1. Iz mape koja sadrži vaš manifest implementacije, pokrenite sljedeću naredbu:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Zamijenite `<hub_name>` nazivom vašeg IoT Hub-a.

    Modul klasifikatora slika bit će implementiran na vaš edge uređaj.

### Zadatak - provjera rada klasifikatora

1. Povežite se s IoT Edge uređajem:

    * Ako koristite Raspberry Pi za pokretanje IoT Edge-a, povežite se putem ssh-a iz vašeg terminala ili putem udaljene SSH sesije u VS Code-u.
    * Ako pokrećete IoT Edge u Linux kontejneru na Windowsu, slijedite korake u [vodiču za provjeru uspješne konfiguracije](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) za povezivanje s IoT Edge uređajem.
    * Ako pokrećete IoT Edge na virtualnom stroju, možete se povezati putem SSH-a koristeći `adminUsername` i `password` koje ste postavili prilikom kreiranja VM-a, koristeći IP adresu ili DNS ime:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Ili:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Unesite svoju lozinku kada se to zatraži.

1. Kada ste povezani, pokrenite sljedeću naredbu za dobivanje popisa IoT Edge modula:

    ```sh
    iotedge list
    ```

    > 💁 Možda ćete trebati pokrenuti ovu naredbu s `sudo`.

    Vidjet ćete pokrenute module:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Provjerite logove za modul klasifikatora slika pomoću sljedeće naredbe:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Možda ćete trebati pokrenuti ovu naredbu s `sudo`.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### Zadatak - testiranje klasifikatora slika

1. Možete koristiti CURL za testiranje klasifikatora slika koristeći IP adresu ili naziv hosta računala koje pokreće IoT Edge agent. Pronađite IP adresu:

    * Ako ste na istom računalu na kojem se pokreće IoT Edge, možete koristiti `localhost` kao naziv hosta.
    * Ako koristite VM, možete koristiti IP adresu ili DNS ime VM-a.
    * Inače možete dobiti IP adresu računala koje pokreće IoT Edge:
      * Na Windows 10, slijedite [vodič za pronalaženje IP adrese](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Na macOS, slijedite [vodič za pronalaženje IP adrese na Macu](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Na Linuxu, slijedite sekciju o pronalaženju privatne IP adrese u [vodiču za pronalaženje IP adrese u Linuxu](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Možete testirati kontejner s lokalnom datotekom pokretanjem sljedeće CURL naredbe:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Zamijenite `<IP address or name>` IP adresom ili nazivom hosta računala koje pokreće IoT Edge. Zamijenite `<file_Name>` nazivom datoteke za testiranje.

    Vidjet ćete rezultate predikcije u izlazu:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 Ovdje nije potrebno pružiti ključ za predikciju, jer se ne koristi Azure resurs. Umjesto toga, sigurnost bi bila konfigurirana na internoj mreži na temelju internih sigurnosnih potreba, umjesto oslanjanja na javnu endpoint i API ključ.

## Korištenje vašeg IoT Edge uređaja

Sada kada je vaš klasifikator slika implementiran na IoT Edge uređaj, možete ga koristiti s vašeg IoT uređaja.

### Zadatak - korištenje vašeg IoT Edge uređaja

Prođite kroz relevantni vodič za klasifikaciju slika koristeći IoT Edge klasifikator:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Jednoplano računalo - Raspberry Pi/Virtualni IoT uređaj](single-board-computer.md)

### Ponovno treniranje modela

Jedan od nedostataka pokretanja klasifikatora slika na IoT Edge-u je taj što nisu povezani s vašim Custom Vision projektom. Ako pogledate karticu **Predictions** u Custom Visionu, nećete vidjeti slike koje su klasificirane koristeći klasifikator baziran na Edge-u.

Ovo je očekivano ponašanje - slike se ne šalju u cloud na klasifikaciju, pa neće biti dostupne u cloudu. Jedna od prednosti korištenja IoT Edge-a je privatnost, osiguravajući da slike ne napuštaju vašu mrežu, druga je mogućnost rada offline, bez oslanjanja na učitavanje slika kada uređaj nema internetsku vezu. Nedostatak je poboljšanje vašeg modela - trebali biste implementirati drugi način pohrane slika koje se mogu ručno re-klasificirati za poboljšanje i ponovno treniranje klasifikatora slika.

✅ Razmislite o načinima za učitavanje slika za ponovno treniranje klasifikatora.

---

## 🚀 Izazov

Pokretanje AI modela na edge uređajima može biti brže nego u cloudu - mrežni skok je kraći. Također može biti sporije jer hardver koji pokreće model možda nije tako moćan kao cloud.

Napravite mjerenja vremena i usporedite je li poziv vašem edge uređaju brži ili sporiji od poziva cloudu? Razmislite o razlozima za objašnjenje razlike ili nedostatka razlike. Istražite načine za brže pokretanje AI modela na edge-u koristeći specijalizirani hardver.

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Pregled i samostalno učenje

* Pročitajte više o kontejnerima na [stranici o virtualizaciji na razini OS-a na Wikipediji](https://wikipedia.org/wiki/OS-level_virtualization).
* Pročitajte više o edge računalstvu, s naglaskom na to kako 5G može pomoći u širenju edge računalstva u [članku "Što je edge računalstvo i zašto je važno?" na NetworkWorldu](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Saznajte više o pokretanju AI usluga na IoT Edgeu gledajući [epizodu "Naučite kako koristiti Azure IoT Edge na unaprijed izgrađenoj AI usluzi na Edgeu za detekciju jezika" serijala Learn Live na Microsoft Channel9](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Zadatak

[Pokrenite druge usluge na edgeu](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.