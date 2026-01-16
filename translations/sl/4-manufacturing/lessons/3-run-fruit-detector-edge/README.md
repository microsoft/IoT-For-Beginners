<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-28T12:18:56+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "sl"
}
-->
# Zaženite vaš detektor sadja na robu

![Pregled lekcije v obliki sketchnote](../../../../../translated_images/sl/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.jpg)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliko za večjo različico.

Ta video ponuja pregled izvajanja klasifikatorjev slik na IoT napravah, kar je tema te lekcije.

[![Custom Vision AI na Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Predhodni kviz

[Predhodni kviz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Uvod

V prejšnji lekciji ste uporabili svoj klasifikator slik za razvrščanje zrelega in nezrelega sadja, pri čemer ste sliko, zajeto s kamero na vaši IoT napravi, poslali prek interneta v oblačno storitev. Takšni klici zahtevajo čas, stanejo denar in, odvisno od vrste slikovnih podatkov, ki jih uporabljate, lahko imajo posledice za zasebnost.

V tej lekciji se boste naučili, kako izvajati modele strojnega učenja (ML) na robu - na IoT napravah, ki delujejo v vašem omrežju, namesto v oblaku. Spoznali boste prednosti in slabosti robnega računalništva v primerjavi z oblačnim računalništvom, kako namestiti vaš AI model na rob in kako dostopati do njega z vaše IoT naprave.

V tej lekciji bomo obravnavali:

* [Robno računalništvo](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Registracija IoT Edge naprave](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Nastavitev IoT Edge naprave](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Izvoz vašega modela](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Priprava kontejnerja za namestitev](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Namestitev kontejnerja](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Uporaba vaše IoT Edge naprave](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Robno računalništvo

Robno računalništvo vključuje računalnike, ki obdelujejo podatke IoT čim bližje mestu, kjer so ti podatki ustvarjeni. Namesto da se ta obdelava izvaja v oblaku, se premakne na rob oblaka - vaše interno omrežje.

![Diagram arhitekture, ki prikazuje internetne storitve v oblaku in IoT naprave v lokalnem omrežju](../../../../../translated_images/sl/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.png)

V dosedanjih lekcijah ste imeli naprave, ki zbirajo podatke in jih pošiljajo v oblak za analizo, kjer se izvajajo brezstrežni funkciji ali AI modeli v oblaku.

![Diagram arhitekture, ki prikazuje IoT naprave v lokalnem omrežju, ki se povezujejo z robnimi napravami, te pa se povezujejo z oblakom](../../../../../translated_images/sl/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.png)

Robno računalništvo vključuje premik nekaterih oblačnih storitev iz oblaka na računalnike, ki delujejo v istem omrežju kot IoT naprave, in komunikacijo z oblakom le, če je to potrebno. Na primer, lahko izvajate AI modele na robnih napravah za analizo zrelosti sadja in v oblak pošiljate le analitiko, kot je število zrelih kosov sadja v primerjavi z nezrelimi.

✅ Razmislite o IoT aplikacijah, ki ste jih doslej zgradili. Katere dele bi lahko premaknili na rob?

### Prednosti

Prednosti robnega računalništva so:

1. **Hitrost** - robno računalništvo je idealno za podatke, občutljive na čas, saj se dejanja izvajajo v istem omrežju kot naprava, namesto da bi se klici izvajali prek interneta. To omogoča večje hitrosti, saj lahko interna omrežja delujejo bistveno hitreje kot internetne povezave, podatki pa potujejo na precej krajše razdalje.

    > 💁 Kljub temu, da se za internetne povezave uporabljajo optični kabli, ki omogočajo potovanje podatkov s hitrostjo svetlobe, lahko podatki potrebujejo čas za potovanje po svetu do oblačnih ponudnikov. Na primer, če pošiljate podatke iz Evrope v oblačne storitve v ZDA, traja vsaj 28 ms, da podatki prečkajo Atlantik po optičnem kablu, pri čemer je izključen čas, potreben za prenos podatkov do transatlantskega kabla, pretvorbo iz električnih v svetlobne signale in nazaj na drugi strani ter nato iz optičnega kabla do oblačnega ponudnika.

    Robno računalništvo zahteva tudi manj omrežnega prometa, kar zmanjšuje tveganje, da se vaši podatki upočasnijo zaradi zastojev na omejeni pasovni širini internetne povezave.

1. **Dostopnost na daljavo** - robno računalništvo deluje, ko imate omejeno ali brez povezljivosti, ali pa je povezljivost predraga za stalno uporabo. Na primer, pri delu na območjih humanitarnih katastrof, kjer je infrastruktura omejena, ali v državah v razvoju.

1. **Nižji stroški** - zbiranje, shranjevanje, analiza podatkov in sprožanje dejanj na robni napravi zmanjšuje uporabo oblačnih storitev, kar lahko zmanjša skupne stroške vaše IoT aplikacije. V zadnjem času se je povečalo število naprav, zasnovanih za robno računalništvo, kot so AI pospeševalne plošče, na primer [Jetson Nano od NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), ki lahko izvajajo AI delovne obremenitve z uporabo strojne opreme GPU na napravah, ki stanejo manj kot 100 USD.

1. **Zasebnost in varnost** - pri robnem računalništvu podatki ostanejo v vašem omrežju in se ne naložijo v oblak. To je pogosto prednostno za občutljive in osebno prepoznavne informacije, še posebej, ker podatkov ni treba shranjevati po analizi, kar močno zmanjša tveganje za uhajanje podatkov. Primeri vključujejo medicinske podatke in posnetke varnostnih kamer.

1. **Obravnava negotovih naprav** - če imate naprave z znanimi varnostnimi pomanjkljivostmi, ki jih ne želite neposredno povezati z vašim omrežjem ali internetom, jih lahko povežete z ločenim omrežjem na prehodno IoT Edge napravo. Ta robna naprava ima lahko nato tudi povezavo z vašim širšim omrežjem ali internetom in upravlja tokove podatkov naprej in nazaj.

1. **Podpora za nezdružljive naprave** - če imate naprave, ki se ne morejo povezati z IoT Hub, na primer naprave, ki se lahko povežejo le prek HTTP povezav ali naprave, ki imajo le Bluetooth za povezavo, lahko uporabite IoT Edge napravo kot prehodno napravo, ki posreduje sporočila v IoT Hub.

✅ Raziskujte: Katere druge prednosti bi lahko imelo robno računalništvo?

### Slabosti

Obstajajo slabosti robnega računalništva, kjer je oblak morda boljša izbira:

1. **Obseg in prilagodljivost** - oblačno računalništvo se lahko prilagodi potrebam omrežja in podatkov v realnem času z dodajanjem ali zmanjševanjem strežnikov in drugih virov. Dodajanje več robnih računalnikov zahteva ročno dodajanje več naprav.

1. **Zanesljivost in odpornost** - oblačno računalništvo zagotavlja več strežnikov, pogosto na več lokacijah, za redundanco in obnovo po katastrofi. Za dosego enake stopnje redundance na robu so potrebne velike naložbe in veliko konfiguracijskega dela.

1. **Vzdrževanje** - ponudniki oblačnih storitev zagotavljajo vzdrževanje sistema in posodobitve.

✅ Raziskujte: Katere druge slabosti bi lahko imelo robno računalništvo?

Slabosti so v bistvu nasprotje prednosti uporabe oblaka - naprave morate zgraditi in upravljati sami, namesto da bi se zanašali na strokovno znanje in obseg oblačnih ponudnikov.

Nekatera tveganja so ublažena že po naravi robnega računalništva. Na primer, če imate robno napravo, ki deluje v tovarni in zbira podatke iz strojev, vam ni treba razmišljati o nekaterih scenarijih obnovitve po katastrofi. Če v tovarni zmanjka elektrike, ne potrebujete rezervne robne naprave, saj bodo tudi stroji, ki ustvarjajo podatke, ki jih robna naprava obdeluje, brez elektrike.

Za IoT sisteme boste pogosto želeli kombinacijo oblačnega in robnega računalništva, pri čemer boste izkoristili vsako storitev glede na potrebe sistema, njegovih strank in vzdrževalcev.

## Azure IoT Edge

![Logotip Azure IoT Edge](../../../../../translated_images/sl/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.png)

Azure IoT Edge je storitev, ki vam lahko pomaga premakniti delovne obremenitve iz oblaka na rob. Napravo nastavite kot robno napravo, iz oblaka pa lahko na to robno napravo namestite kodo. To vam omogoča kombiniranje zmogljivosti oblaka in roba.

> 🎓 *Delovne obremenitve* je izraz za katero koli storitev, ki opravlja neko delo, kot so AI modeli, aplikacije ali brezstrežne funkcije.

Na primer, lahko v oblaku trenirate klasifikator slik, nato pa ga iz oblaka namestite na robno napravo. Vaša IoT naprava nato pošilja slike robni napravi za klasifikacijo, namesto da bi slike pošiljala prek interneta. Če morate namestiti novo iteracijo modela, jo lahko trenirate v oblaku in uporabite IoT Edge za posodobitev modela na robni napravi na novo iteracijo.

> 🎓 Programska oprema, ki je nameščena na IoT Edge, je znana kot *moduli*. Privzeto IoT Edge izvaja module, ki komunicirajo z IoT Hub, kot so moduli `edgeAgent` in `edgeHub`. Ko namestite klasifikator slik, je ta nameščen kot dodatni modul.

IoT Edge je vgrajen v IoT Hub, zato lahko upravljate robne naprave z isto storitvijo, ki jo uporabljate za upravljanje IoT naprav, z enako stopnjo varnosti.

IoT Edge izvaja kodo iz *kontejnerjev* - samostojnih aplikacij, ki se izvajajo ločeno od preostalih aplikacij na vašem računalniku. Ko zaženete kontejner, deluje kot ločen računalnik znotraj vašega računalnika, z lastno programsko opremo, storitvami in aplikacijami. Večinoma kontejnerji ne morejo dostopati do ničesar na vašem računalniku, razen če se odločite deliti stvari, kot je mapa, s kontejnerjem. Kontejner nato izpostavi storitve prek odprtega porta, do katerega lahko dostopate ali ga izpostavite svojemu omrežju.

![Spletna zahteva, preusmerjena v kontejner](../../../../../translated_images/sl/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.png)

Na primer, lahko imate kontejner z spletno stranjo, ki deluje na portu 80, privzetem HTTP portu, in ga nato izpostavite iz vašega računalnika tudi na portu 80.

✅ Raziskujte: Preberite več o kontejnerjih in storitvah, kot sta Docker ali Moby.

Custom Vision lahko uporabite za prenos klasifikatorjev slik in njihovo namestitev kot kontejnerje, bodisi neposredno na napravo bodisi prek IoT Edge. Ko se izvajajo v kontejnerju, so dostopni z istim REST API-jem kot oblačna različica, vendar z endpointom, ki kaže na robno napravo, ki izvaja kontejner.

## Registracija IoT Edge naprave

Za uporabo IoT Edge naprave jo je treba registrirati v IoT Hub.

### Naloga - registracija IoT Edge naprave

1. Ustvarite IoT Hub v skupini virov `fruit-quality-detector`. Dajte mu edinstveno ime, ki temelji na `fruit-quality-detector`.

1. Registrirajte IoT Edge napravo z imenom `fruit-quality-detector-edge` v vašem IoT Hub. Ukaz za to je podoben tistemu, ki se uporablja za registracijo ne-edge naprave, razen da dodate zastavico `--edge-enabled`.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Zamenjajte `<hub_name>` z imenom vašega IoT Hub.

1. Pridobite povezovalni niz za vašo napravo z naslednjim ukazom:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Zamenjajte `<hub_name>` z imenom vašega IoT Hub.

    Kopirajte povezovalni niz, ki je prikazan v izhodu.

## Nastavitev IoT Edge naprave

Ko ste ustvarili registracijo robne naprave v vašem IoT Hub, lahko nastavite robno napravo.

### Naloga - Namestitev in zagon IoT Edge Runtime

**IoT Edge Runtime izvaja samo Linux kontejnerje.** Lahko se izvaja na Linuxu ali na Windowsu z uporabo Linux virtualnih strojev.

* Če uporabljate Raspberry Pi kot svojo IoT napravo, ta izvaja podprto različico Linuxa in lahko gosti IoT Edge Runtime. Sledite [navodilom za namestitev Azure IoT Edge za Linux na Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn), da namestite IoT Edge in nastavite povezovalni niz.

    > 💁 Ne pozabite, Raspberry Pi OS je različica Debian Linuxa.

* Če ne uporabljate Raspberry Pi, ampak imate Linux računalnik, lahko zaženete IoT Edge Runtime. Sledite [navodilom za namestitev Azure IoT Edge za Linux na Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn), da namestite IoT Edge in nastavite povezovalni niz.

* Če uporabljate Windows, lahko IoT Edge Runtime namestite v Linux virtualni stroj, tako da sledite [oddelku za namestitev in zagon IoT Edge Runtime v hitrem začetku za namestitev prvega IoT Edge modula na Windows napravo na Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Ustavite se, ko pridete do oddelka *Namestitev modula*.

* Če uporabljate macOS, lahko ustvarite virtualni stroj (VM) v oblaku za uporabo kot vašo IoT Edge napravo. To so računalniki, ki jih lahko ustvarite v oblaku in dostopate do njih prek interneta. Ustvarite lahko Linux VM, ki ima nameščen IoT Edge. Sledite [navodilom za ustvarjanje virtualnega stroja z IoT Edge](vm-iotedge.md) za navodila, kako to storiti.

## Izvoz vašega modela

Za izvajanje klasifikatorja na robu ga je treba izvoziti iz Custom Vision. Custom Vision lahko ustvari dva tipa modelov - standardne modele in kompaktne modele. Kompaktni modeli uporabljajo različne tehnike za zmanjšanje velikosti modela, kar omogoča, da je model dovolj majhen za prenos in namestitev na IoT napravah.

Ko ste ustvarili klasifikator slik, ste uporabili *Food* domeno, različico modela, ki je optimizirana za treniranje na slikah hrane. V Custom Vision spremenite domeno vašega projekta in uporabite vaše podatke za treniranje novega modela z novo domeno. Vse domene, ki jih podpira Custom Vision, so na voljo kot standardne in kompaktne.

### Naloga - trenirajte vaš model z uporabo Food (compact) domene
1. Zaženite portal Custom Vision na [CustomVision.ai](https://customvision.ai) in se prijavite, če še niste prijavljeni. Nato odprite svoj projekt `fruit-quality-detector`.

1. Izberite gumb **Settings** (ikona ⚙).

1. Na seznamu *Domains* izberite *Food (compact)*.

1. Pod *Export Capabilities* preverite, da je izbrana možnost *Basic platforms (Tensorflow, CoreML, ONNX, ...)*.

1. Na dnu strani z nastavitvami izberite **Save Changes**.

1. Ponovno usposobite model z gumbom **Train**, pri čemer izberite možnost *Quick training*.

### Naloga - izvozite svoj model

Ko je model usposobljen, ga je treba izvoziti kot vsebnik.

1. Izberite zavihek **Performance** in poiščite najnovejšo iteracijo, ki je bila usposobljena z uporabo kompaktne domene.

1. Kliknite gumb **Export** na vrhu.

1. Izberite **DockerFile**, nato pa izberite različico, ki ustreza vaši napravi na robu:

    * Če uporabljate IoT Edge na računalniku z Linuxom, Windowsom ali virtualnem stroju, izberite različico *Linux*.
    * Če uporabljate IoT Edge na Raspberry Pi, izberite različico *ARM (Raspberry Pi 3)*.

> 🎓 Docker je eno izmed najbolj priljubljenih orodij za upravljanje vsebnikov, DockerFile pa je niz navodil za nastavitev vsebnika.

1. Kliknite **Export**, da Custom Vision ustvari ustrezne datoteke, nato pa **Download**, da jih prenesete v zip datoteki.

1. Shranite datoteke na svoj računalnik in razširite mapo.

## Pripravite svoj vsebnik za uvajanje

![Vsebnik se ustvari, nato potisne v register vsebnikov in se nato uvede na napravo na robu z uporabo IoT Edge](../../../../../translated_images/sl/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.png)

Ko prenesete svoj model, ga je treba sestaviti v vsebnik in potisniti v register vsebnikov - spletno mesto za shranjevanje vsebnikov. IoT Edge lahko nato prenese vsebnik iz registra in ga potisne na vašo napravo.

![Logotip Azure Container Registry](../../../../../translated_images/sl/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.png)

Register vsebnikov, ki ga boste uporabili za to lekcijo, je Azure Container Registry. Ta storitev ni brezplačna, zato za zmanjšanje stroškov poskrbite, da [počistite svoj projekt](../../../clean-up.md), ko končate.

> 💁 Stroške uporabe Azure Container Registry si lahko ogledate na [strani s cenami Azure Container Registry](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Naloga - namestite Docker

Za sestavljanje in uvajanje klasifikatorja boste morda morali namestiti [Docker](https://www.docker.com/).

To boste morali storiti le, če nameravate sestaviti svoj vsebnik na napravi, ki ni tista, na kateri ste namestili IoT Edge - pri namestitvi IoT Edge se Docker namesti samodejno.

1. Če sestavljate vsebnik na napravi, ki ni vaša naprava IoT Edge, sledite navodilom za namestitev Dockerja na [strani za namestitev Dockerja](https://www.docker.com/products/docker-desktop), da namestite Docker Desktop ali Docker engine. Po namestitvi poskrbite, da Docker deluje.

### Naloga - ustvarite vir za register vsebnikov

1. Zaženite naslednji ukaz v terminalu ali ukazni vrstici, da ustvarite vir Azure Container Registry:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Zamenjajte `<Container registry name>` z edinstvenim imenom za vaš register vsebnikov, pri čemer uporabite samo črke in številke. Ime naj temelji na `fruitqualitydetector`. To ime postane del URL-ja za dostop do registra vsebnikov, zato mora biti globalno edinstveno.

1. Prijavite se v Azure Container Registry z naslednjim ukazom:

    ```sh
    az acr login --name <Container registry name>
    ```

    Zamenjajte `<Container registry name>` z imenom, ki ste ga uporabili za svoj register vsebnikov.

1. Nastavite register vsebnikov v način skrbnika, da lahko ustvarite geslo z naslednjim ukazom:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Zamenjajte `<Container registry name>` z imenom, ki ste ga uporabili za svoj register vsebnikov.

1. Ustvarite gesla za svoj register vsebnikov z naslednjim ukazom:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Zamenjajte `<Container registry name>` z imenom, ki ste ga uporabili za svoj register vsebnikov.

    Shranite vrednost `PASSWORD`, saj jo boste potrebovali kasneje.

### Naloga - sestavite svoj vsebnik

Datoteka DockerFile, ki ste jo prenesli iz Custom Vision, vsebuje navodila za sestavljanje vsebnika, skupaj z aplikacijsko kodo, ki bo znotraj vsebnika gostila vaš model Custom Vision in REST API za klice. Z Dockerjem lahko sestavite označen vsebnik iz datoteke DockerFile in ga nato potisnete v svoj register vsebnikov.

> 🎓 Vsebnikom se dodeli oznaka, ki določa njihovo ime in različico. Ko morate posodobiti vsebnik, ga lahko sestavite z isto oznako, vendar z novejšo različico.

1. Odprite terminal ali ukazno vrstico in se pomaknite do razširjenega modela, ki ste ga prenesli iz Custom Vision.

1. Zaženite naslednji ukaz za sestavljanje in označevanje slike:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Zamenjajte `<platform>` s platformo, na kateri bo ta vsebnik deloval. Če uporabljate IoT Edge na Raspberry Pi, nastavite to na `linux/armhf`, sicer nastavite na `linux/amd64`.

    > 💁 Če ta ukaz izvajate na napravi, na kateri izvajate IoT Edge, na primer na Raspberry Pi, lahko izpustite del `--platform <platform>`, saj se privzeto uporabi trenutna platforma.

    Zamenjajte `<Container registry name>` z imenom, ki ste ga uporabili za svoj register vsebnikov.

    > 💁 Če uporabljate Linux ali Raspberry Pi OS, boste morda morali uporabiti `sudo` za zagon tega ukaza.

    Docker bo sestavil sliko in konfiguriral vso potrebno programsko opremo. Slika bo nato označena kot `classifier:v1`.

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

### Naloga - potisnite svoj vsebnik v register vsebnikov

1. Uporabite naslednji ukaz za potiskanje vsebnika v register vsebnikov:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Zamenjajte `<Container registry name>` z imenom, ki ste ga uporabili za svoj register vsebnikov.

    > 💁 Če uporabljate Linux, boste morda morali uporabiti `sudo` za zagon tega ukaza.

    Vsebnik bo potisnjen v register vsebnikov.

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

1. Za preverjanje potiska lahko seznam vsebnikov v registru prikažete z naslednjim ukazom:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Zamenjajte `<Container registry name>` z imenom, ki ste ga uporabili za svoj register vsebnikov.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    V izhodu boste videli svoj klasifikator.

## Uvedite svoj vsebnik

Vaš vsebnik je zdaj pripravljen za uvajanje na vašo napravo IoT Edge. Za uvajanje morate definirati manifest uvajanja - JSON dokument, ki navaja module, ki bodo uvedeni na napravo na robu.

### Naloga - ustvarite manifest uvajanja

1. Ustvarite novo datoteko z imenom `deployment.json` nekje na svojem računalniku.

1. Dodajte naslednje v to datoteko:

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

    > 💁 To datoteko lahko najdete v mapi [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    Zamenjajte tri primere `<Container registry name>` z imenom, ki ste ga uporabili za svoj register vsebnikov. Ena je v razdelku modula `ImageClassifier`, drugi dve pa v razdelku `registryCredentials`.

    Zamenjajte `<Container registry password>` v razdelku `registryCredentials` z geslom vašega registra vsebnikov.

1. Iz mape, ki vsebuje vaš manifest uvajanja, zaženite naslednji ukaz:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Zamenjajte `<hub_name>` z imenom svojega IoT Hub-a.

    Modul klasifikatorja slik bo uveden na vašo napravo na robu.

### Naloga - preverite, ali klasifikator deluje

1. Povežite se z napravo IoT Edge:

    * Če uporabljate Raspberry Pi za izvajanje IoT Edge, se povežite prek SSH bodisi iz terminala bodisi prek oddaljene SSH seje v VS Code.
    * Če izvajate IoT Edge v vsebniku Linux na Windowsu, sledite korakom v [vodniku za preverjanje uspešne konfiguracije](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration), da se povežete z napravo IoT Edge.
    * Če izvajate IoT Edge na virtualnem stroju, se lahko povežete prek SSH z uporabo `adminUsername` in `password`, ki ste ju nastavili ob ustvarjanju VM, ter z uporabo IP naslova ali DNS imena:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Ali:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Vnesite svoje geslo, ko boste pozvani.

1. Ko ste povezani, zaženite naslednji ukaz za pridobitev seznama modulov IoT Edge:

    ```sh
    iotedge list
    ```

    > 💁 Morda boste morali ta ukaz zagnati z `sudo`.

    Videli boste delujoče module:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Preverite dnevnike za modul klasifikatorja slik z naslednjim ukazom:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Morda boste morali ta ukaz zagnati z `sudo`.

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

### Naloga - preizkusite klasifikator slik

1. Za testiranje klasifikatorja slik lahko uporabite CURL z uporabo IP naslova ali imena gostitelja računalnika, ki izvaja IoT Edge agent. Poiščite IP naslov:

    * Če ste na istem računalniku, kjer se izvaja IoT Edge, lahko uporabite `localhost` kot ime gostitelja.
    * Če uporabljate VM, lahko uporabite bodisi IP naslov bodisi DNS ime VM-ja.
    * V nasprotnem primeru lahko pridobite IP naslov računalnika, ki izvaja IoT Edge:
      * Na Windows 10 sledite [vodniku za iskanje IP naslova](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Na macOS sledite [vodniku za iskanje IP naslova na Macu](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Na Linuxu sledite razdelku o iskanju zasebnega IP naslova v [vodniku za iskanje IP naslova v Linuxu](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Vsebnik lahko preizkusite z lokalno datoteko z naslednjim ukazom curl:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Zamenjajte `<IP address or name>` z IP naslovom ali imenom gostitelja računalnika, ki izvaja IoT Edge. Zamenjajte `<file_Name>` z imenom datoteke za testiranje.

    V izhodu boste videli rezultate napovedi:

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

    > 💁 Tukaj ni treba zagotoviti ključa za napovedovanje, saj to ne uporablja vira Azure. Namesto tega bi bila varnost konfigurirana na notranjem omrežju glede na notranje varnostne potrebe, namesto da bi se zanašali na javno končno točko in API ključ.

## Uporabite svojo napravo IoT Edge

Zdaj, ko je vaš klasifikator slik uveden na napravo IoT Edge, ga lahko uporabljate s svojo IoT napravo.

### Naloga - uporabite svojo napravo IoT Edge

Sledite ustreznemu vodniku za klasifikacijo slik z uporabo klasifikatorja IoT Edge:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Enokartični računalnik - Raspberry Pi/Virtual IoT naprava](single-board-computer.md)

### Ponovno usposabljanje modela

Ena od slabosti izvajanja klasifikatorjev slik na IoT Edge je, da niso povezani z vašim projektom Custom Vision. Če pogledate zavihek **Predictions** v Custom Vision, ne boste videli slik, ki so bile klasificirane z uporabo klasifikatorja na robu.

To je pričakovano vedenje - slike se ne pošiljajo v oblak za klasifikacijo, zato ne bodo na voljo v oblaku. Ena od prednosti uporabe IoT Edge je zasebnost, saj slike ne zapustijo vašega omrežja, druga pa je možnost dela brez povezave, brez zanašanja na nalaganje slik, ko naprava nima internetne povezave. Slabost je izboljšanje vašega modela - morali bi implementirati drug način shranjevanja slik, ki jih je mogoče ročno ponovno klasificirati za izboljšanje in ponovno usposabljanje klasifikatorja slik.

✅ Razmislite o načinih nalaganja slik za ponovno usposabljanje klasifikatorja.

---

## 🚀 Izziv

Zagon AI modelov na napravah na robu je lahko hitrejši kot v oblaku - omrežni skok je krajši. Lahko pa je tudi počasnejši, saj strojna oprema, ki izvaja model, morda ni tako zmogljiva kot oblak.

Izvedite nekaj meritev in primerjajte, ali je klic na vašo napravo na robu hitrejši ali počasnejši od klica v oblak? Razmislite o razlogih za razliko ali pomanjkanje razlike. Raziskujte načine za hitrejše izvajanje AI modelov na robu z uporabo specializirane strojne opreme.

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Pregled in samostojno učenje

* Preberite več o vsebnikih na [strani o virtualizaciji na ravni OS na Wikipediji](https://wikipedia.org/wiki/OS-level_virtualization).
* Preberite več o robnem računalništvu, s poudarkom na tem, kako lahko 5G pomaga razširiti robno računalništvo, v [članku Kaj je robno računalništvo in zakaj je pomembno? na NetworkWorld](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Naučite se več o izvajanju AI storitev na IoT Edge tako, da si ogledate [epizodo Naučite se uporabljati Azure IoT Edge na vnaprej pripravljeni AI storitvi na robu za zaznavanje jezika iz serije Learn Live na Microsoft Channel9](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Naloga

[Izvajajte druge storitve na robu](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.