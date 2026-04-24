# Povežite svojo napravo z internetom

![Sketchnote pregled te lekcije](../../../../../translated_images/sl/lesson-4.7344e074ea68fa54.webp)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliko za večjo različico.

Ta lekcija je bila del serije [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) iz [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekcija je bila izvedena v dveh videih - enourni lekciji in enourni pisarniški uri, kjer so podrobneje obravnavali dele lekcije ter odgovarjali na vprašanja.

[![Lekcija 4: Povežite svojo napravo z internetom](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Lekcija 4: Povežite svojo napravo z internetom - Pisarniške ure](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Kliknite na zgornje slike za ogled videov

## Predhodni kviz

[Predhodni kviz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Uvod

Črka **I** v IoT pomeni **Internet** - povezljivost v oblaku in storitve, ki omogočajo številne funkcije IoT naprav, od zbiranja meritev s senzorjev, povezanih z napravo, do pošiljanja sporočil za nadzor aktuatorjev. IoT naprave se običajno povežejo z eno storitvijo v oblaku prek standardnega komunikacijskega protokola, ta storitev pa je povezana z ostalim delom vaše IoT aplikacije, od AI storitev za pametne odločitve na podlagi podatkov do spletnih aplikacij za nadzor ali poročanje.

> 🎓 Podatki, zbrani s senzorjev in poslani v oblak, se imenujejo telemetrija.

IoT naprave lahko prejemajo sporočila iz oblaka. Ta sporočila pogosto vsebujejo ukaze - navodila za izvedbo dejanja bodisi interno (npr. ponovni zagon ali posodobitev vdelane programske opreme) bodisi z aktuatorjem (npr. prižig luči).

Ta lekcija uvaja nekatere komunikacijske protokole, ki jih IoT naprave lahko uporabljajo za povezavo z oblakom, ter vrste podatkov, ki jih lahko pošiljajo ali prejemajo. Prav tako boste praktično preizkusili oboje, dodali internetni nadzor svoji nočni lučki ter premaknili logiko nadzora LED na 'strežniško' kodo, ki bo delovala lokalno.

V tej lekciji bomo obravnavali:

* [Komunikacijske protokole](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetrija](../../../../../1-getting-started/lessons/4-connect-internet)
* [Ukazi](../../../../../1-getting-started/lessons/4-connect-internet)

## Komunikacijski protokoli

Obstaja več priljubljenih komunikacijskih protokolov, ki jih IoT naprave uporabljajo za komunikacijo z internetom. Najbolj priljubljeni temeljijo na objavi/naročanju prek nekakšnega posrednika. IoT naprave se povežejo s posrednikom, objavljajo telemetrijo in se naročajo na ukaze. Tudi storitve v oblaku se povežejo s posrednikom, naročajo na vsa telemetrijska sporočila in objavljajo ukaze bodisi za določene naprave bodisi za skupine naprav.

![IoT naprave se povežejo s posrednikom, objavljajo telemetrijo in se naročajo na ukaze. Storitve v oblaku se povežejo s posrednikom, naročajo na vso telemetrijo in pošiljajo ukaze določenim napravam.](../../../../../translated_images/sl/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT je najbolj priljubljen komunikacijski protokol za IoT naprave in je obravnavan v tej lekciji. Drugi protokoli vključujejo AMQP in HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) je lahek, odprt standardni protokol za pošiljanje sporočil med napravami. Razvit je bil leta 1999 za nadzor naftovodov, nato pa ga je IBM 15 let kasneje izdal kot odprt standard.

MQTT ima enega posrednika in več odjemalcev. Vsi odjemalci se povežejo s posrednikom, posrednik pa usmerja sporočila ustreznim odjemalcem. Sporočila se usmerjajo prek poimenovanih tem, namesto da bi bila poslana neposredno posameznemu odjemalcu. Odjemalec lahko objavi na temo, vsi odjemalci, ki so naročeni na to temo, pa prejmejo sporočilo.

![IoT naprava objavlja telemetrijo na temi /telemetry, storitev v oblaku pa se naroča na to temo](../../../../../translated_images/sl/mqtt.cbf7f21d9adc3e17.webp)

✅ Raziskujte. Če imate veliko IoT naprav, kako lahko zagotovite, da vaš MQTT posrednik obvlada vsa sporočila?

### Povežite svojo IoT napravo z MQTT

Prvi korak pri dodajanju internetnega nadzora vaši nočni lučki je povezava z MQTT posrednikom.

#### Naloga

Povežite svojo napravo z MQTT posrednikom.

V tem delu lekcije boste svojo IoT nočno lučko povezali z internetom, da jo boste lahko nadzorovali na daljavo. Kasneje v tej lekciji bo vaša IoT naprava prek MQTT poslala telemetrijsko sporočilo o ravni svetlobe javnemu MQTT posredniku, kjer ga bo prevzela strežniška koda, ki jo boste napisali. Ta koda bo preverila raven svetlobe in poslala povratno sporočilo z ukazom napravi, naj vklopi ali izklopi LED.

Resnična uporaba takšne nastavitve bi lahko bila zbiranje podatkov iz več senzorjev svetlobe, preden se odločite za prižig luči na lokaciji z veliko lučmi, kot je stadion. To bi lahko preprečilo prižig luči, če bi bil le en senzor prekrit z oblaki ali ptico, medtem ko bi drugi senzorji zaznali dovolj svetlobe.

✅ Katere druge situacije bi zahtevale oceno podatkov iz več senzorjev, preden pošljete ukaze?

Namesto da bi se ukvarjali s kompleksnostjo nastavitve MQTT posrednika kot del te naloge, lahko uporabite javni testni strežnik, ki poganja [Eclipse Mosquitto](https://www.mosquitto.org), odprtokodni MQTT posrednik. Ta testni posrednik je javno dostopen na [test.mosquitto.org](https://test.mosquitto.org) in ne zahteva nastavitve računa, kar ga naredi odličnega za testiranje MQTT odjemalcev in strežnikov.

> 💁 Ta testni posrednik je javni in ni varen. Kdorkoli lahko posluša, kaj objavljate, zato ga ne uporabljajte za podatke, ki morajo ostati zasebni.

![Diagram naloge, ki prikazuje branje in preverjanje ravni svetlobe ter nadzor LED](../../../../../translated_images/sl/assignment-1-internet-flow.3256feab5f052fd2.webp)

Sledite ustreznemu koraku spodaj, da povežete svojo napravo z MQTT posrednikom:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Enočipni računalnik - Raspberry Pi/Virtualna IoT naprava](single-board-computer-mqtt.md)

### Globlji pogled v MQTT

Teme lahko imajo hierarhijo, odjemalci pa se lahko naročajo na različne ravni hierarhije z uporabo nadomestnih znakov. Na primer, lahko pošiljate telemetrijska sporočila o temperaturi na temo `/telemetry/temperature` in sporočila o vlažnosti na temo `/telemetry/humidity`, nato pa se v vaši aplikaciji v oblaku naročite na temo `/telemetry/*`, da prejmete tako temperaturna kot vlažnostna telemetrijska sporočila.

Sporočila se lahko pošiljajo z različnimi stopnjami kakovosti storitve (QoS), kar določa zagotovilo, da bo sporočilo prejeto.

* Največ enkrat - sporočilo se pošlje le enkrat, odjemalec in posrednik pa ne sprejmeta dodatnih ukrepov za potrditev dostave (pošlji in pozabi).
* Vsaj enkrat - sporočilo se večkrat pošlje, dokler ni prejeto potrdilo (potrjena dostava).
* Natanko enkrat - pošiljatelj in prejemnik izvedeta dvostopenjski postopek, da zagotovita, da je prejeto le eno kopijo sporočila (zagotovljena dostava).

✅ Katere situacije bi zahtevale zagotovljeno dostavo sporočila namesto pošlji in pozabi?

Čeprav ime vključuje Message Queueing (MQTT), dejansko ne podpira vrst sporočil. To pomeni, da če se odjemalec odklopi in nato ponovno poveže, ne bo prejel sporočil, poslanih med odklopom, razen tistih, ki jih je že začel obdelovati prek postopka QoS. Sporočila lahko imajo zastavico za ohranitev. Če je ta nastavljena, bo MQTT posrednik shranil zadnje sporočilo, poslano na temo s to zastavico, in ga poslal vsem odjemalcem, ki se kasneje naročijo na to temo. Na ta način bodo odjemalci vedno prejeli najnovejše sporočilo.

MQTT podpira tudi funkcijo ohranjanja povezave, ki preverja, ali je povezava še vedno aktivna med dolgimi presledki med sporočili.

> 🦟 [Mosquitto iz Eclipse Foundation](https://mosquitto.org) ponuja brezplačen MQTT posrednik, ki ga lahko sami zaženete za eksperimentiranje z MQTT, skupaj z javnim MQTT posrednikom, ki ga lahko uporabite za testiranje svoje kode, gostovanim na [test.mosquitto.org](https://test.mosquitto.org).

MQTT povezave so lahko javne in odprte ali pa šifrirane in zaščitene z uporabniškimi imeni in gesli ali certifikati.

> 💁 MQTT komunicira prek TCP/IP, istega osnovnega omrežnega protokola kot HTTP, vendar na drugem portu. MQTT lahko uporabljate tudi prek spletnih vtičnikov za komunikacijo s spletnimi aplikacijami, ki delujejo v brskalniku, ali v situacijah, kjer požarni zidovi ali druga omrežna pravila blokirajo standardne MQTT povezave.

## Telemetrija

Beseda telemetrija izhaja iz grških korenin, ki pomenijo merjenje na daljavo. Telemetrija je dejanje zbiranja podatkov s senzorjev in pošiljanja teh podatkov v oblak.

> 💁 Eden prvih telemetrijskih naprav je bil izumljen v Franciji leta 1874 in je v realnem času pošiljal podatke o vremenu in globini snega z Mont Blanca v Pariz. Uporabljal je fizične žice, saj brezžične tehnologije takrat še niso bile na voljo.

Poglejmo primer pametnega termostata iz Lekcije 1.

![Internetno povezan termostat z več senzorji v prostorih](../../../../../translated_images/sl/telemetry.21e5d8b97649d2eb.webp)

Termostat ima temperaturne senzorje za zbiranje telemetrije. Najverjetneje bi imel en temperaturni senzor vgrajen, poleg tega pa bi se lahko povezal z več zunanjimi temperaturnimi senzorji prek brezžičnega protokola, kot je [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Primer telemetrijskih podatkov, ki bi jih lahko poslal:

| Ime | Vrednost | Opis |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | Temperatura, izmerjena z vgrajenim temperaturnim senzorjem termostata |
| `livingroom_temperature` | 19°C | Temperatura, izmerjena z oddaljenim temperaturnim senzorjem, ki je bil poimenovan `livingroom`, da označuje prostor, v katerem se nahaja |
| `bedroom_temperature` | 21°C | Temperatura, izmerjena z oddaljenim temperaturnim senzorjem, ki je bil poimenovan `bedroom`, da označuje prostor, v katerem se nahaja |

Storitve v oblaku lahko nato uporabijo te telemetrijske podatke za sprejemanje odločitev o tem, katere ukaze poslati za nadzor ogrevanja.

### Pošiljanje telemetrije z vaše IoT naprave

Naslednji korak pri dodajanju internetnega nadzora vaši nočni lučki je pošiljanje telemetrijskih podatkov o ravni svetlobe MQTT posredniku na telemetrijsko temo.

#### Naloga - pošljite telemetrijo z vaše IoT naprave

Pošljite telemetrijo o ravni svetlobe MQTT posredniku.

Podatki se pošiljajo kodirani kot JSON - kratica za JavaScript Object Notation, standard za kodiranje podatkov v besedilu z uporabo parov ključ/vrednost.

✅ Če se še niste srečali z JSON, lahko več o njem izveste v [dokumentaciji JSON.org](https://www.json.org/).

Sledite ustreznemu koraku spodaj, da pošljete telemetrijo z vaše naprave MQTT posredniku:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Enočipni računalnik - Raspberry Pi/Virtualna IoT naprava](single-board-computer-telemetry.md)

### Sprejemanje telemetrije od MQTT posrednika

Ni smiselno pošiljati telemetrije, če na drugi strani ni nikogar, ki bi jo poslušal. Telemetrija o ravni svetlobe potrebuje nekaj, kar jo bo poslušalo in obdelalo podatke. Ta 'strežniška' koda je vrsta kode, ki jo boste namestili v storitev v oblaku kot del večje IoT aplikacije, tukaj pa boste to kodo zagnali lokalno na svojem računalniku (ali na svojem Pi, če tam neposredno kodirate). Strežniška koda je Python aplikacija, ki posluša telemetrijska sporočila prek MQTT o ravni svetlobe. Kasneje v tej lekciji jo boste nastavili, da bo odgovarjala z ukaznim sporočilom z navodili za vklop ali izklop LED.

✅ Raziskujte: Kaj se zgodi z MQTT sporočili, če ni poslušalca?

#### Namestite Python in VS Code

Če nimate nameščenega Python in VS Code lokalno, ju boste morali namestiti, da boste lahko kodirali strežnik. Če uporabljate virtualno IoT napravo ali delate na svojem Raspberry Pi, lahko ta korak preskočite, saj bi morali imeti to že nameščeno in konfigurirano.

##### Naloga - namestite Python in VS Code

Namestite Python in VS Code.

1. Namestite Python. Oglejte si [stran za prenose Python](https://www.python.org/downloads/) za navodila o namestitvi najnovejše različice Python.

1. Namestite Visual Studio Code (VS Code). To je urejevalnik, ki ga boste uporabljali za pisanje kode svoje virtualne naprave v Python. Oglejte si [dokumentacijo VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) za navodila o namestitvi VS Code.
💁 Prosto lahko uporabite katero koli Python IDE ali urejevalnik za te lekcije, če imate raje določeno orodje, vendar bodo navodila v lekcijah temeljila na uporabi VS Code.
1. Namestite razširitev Pylance za VS Code. To je razširitev za VS Code, ki omogoča podporo za programski jezik Python. Navodila za namestitev te razširitve v VS Code najdete v [dokumentaciji za razširitev Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance).

#### Konfiguracija virtualnega okolja za Python

Ena izmed močnih lastnosti Pythona je možnost nameščanja [pip paketov](https://pypi.org) – to so paketi kode, ki jih napišejo drugi in objavijo na internetu. Pip paket lahko namestite na svoj računalnik z enim ukazom in ga nato uporabite v svoji kodi. Pip boste uporabili za namestitev paketa za komunikacijo prek MQTT.

Privzeto so nameščeni paketi dostopni povsod na vašem računalniku, kar lahko povzroči težave z različicami paketov – na primer, ena aplikacija je odvisna od ene različice paketa, ki pa se pokvari, ko namestite novo različico za drugo aplikacijo. Da bi se izognili tej težavi, lahko uporabite [virtualno okolje za Python](https://docs.python.org/3/library/venv.html), kar je v bistvu kopija Pythona v namenski mapi. Ko nameščate pip pakete, se ti namestijo samo v to mapo.

##### Naloga – konfigurirajte virtualno okolje za Python

Konfigurirajte virtualno okolje za Python in namestite pip pakete za MQTT.

1. V terminalu ali ukazni vrstici zaženite naslednje ukaze na lokaciji po vaši izbiri, da ustvarite in se premaknete v novo mapo:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Nato zaženite naslednji ukaz, da ustvarite virtualno okolje v mapi `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Ukaz `python3` morate izrecno poklicati, da ustvarite virtualno okolje, saj imate morda nameščen Python 2 poleg Pythona 3 (zadnje različice). Če imate nameščen Python 2, bo ukaz `python` uporabil Python 2 namesto Pythona 3.

1. Aktivirajte virtualno okolje:

    * Na Windows:
        * Če uporabljate ukazno vrstico ali ukazno vrstico prek Windows Terminal, zaženite:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Če uporabljate PowerShell, zaženite:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Na macOS ali Linux zaženite:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Te ukaze morate zagnati na isti lokaciji, kjer ste zagnali ukaz za ustvarjanje virtualnega okolja. Nikoli vam ne bo treba vstopiti v mapo `.venv`, vedno morate zagnati ukaz za aktivacijo in vse ukaze za namestitev paketov ali zagon kode iz mape, kjer ste ustvarili virtualno okolje.

1. Ko je virtualno okolje aktivirano, bo privzeti ukaz `python` zagnal različico Pythona, ki je bila uporabljena za ustvarjanje virtualnega okolja. Zaženite naslednji ukaz, da preverite različico:

    ```sh
    python --version
    ```

    Izhod bo podoben naslednjemu:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Vaša različica Pythona je morda drugačna – dokler je različica 3.6 ali višja, je vse v redu. Če ni, izbrišite to mapo, namestite novejšo različico Pythona in poskusite znova.

1. Zaženite naslednje ukaze, da namestite pip paket za [Paho-MQTT](https://pypi.org/project/paho-mqtt/), priljubljeno knjižnico za MQTT.

    ```sh
    pip install paho-mqtt
    ```

    Ta pip paket bo nameščen samo v virtualnem okolju in ne bo dostopen zunaj njega.

#### Napišite strežniško kodo

Zdaj lahko napišete strežniško kodo v Pythonu.

##### Naloga – napišite strežniško kodo

Napišite strežniško kodo.

1. V terminalu ali ukazni vrstici zaženite naslednje ukaze znotraj virtualnega okolja, da ustvarite Python datoteko z imenom `app.py`:

    * Na Windows zaženite:

        ```cmd
        type nul > app.py
        ```

    * Na macOS ali Linux zaženite:

        ```cmd
        touch app.py
        ```

1. Odprite trenutno mapo v VS Code:

    ```sh
    code .
    ```

1. Ko se VS Code zažene, bo aktiviral virtualno okolje za Python. To bo prikazano v spodnji statusni vrstici:

    ![VS Code prikazuje izbrano virtualno okolje](../../../../../translated_images/sl/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Če je terminal v VS Code že odprt, ko se VS Code zažene, virtualno okolje v njem ne bo aktivirano. Najlažje je zapreti terminal s klikom na gumb **Kill the active terminal instance**:

    ![Gumb za zapiranje terminala v VS Code](../../../../../translated_images/sl/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Odprite nov terminal v VS Code z izbiro *Terminal -> New Terminal* ali s pritiskom na `` CTRL+` ``. Novi terminal bo naložil virtualno okolje, kar bo prikazano v terminalu. Ime virtualnega okolja (`.venv`) bo tudi v pozivu:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Odprite datoteko `app.py` iz raziskovalca v VS Code in dodajte naslednjo kodo:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Na vrstici 6 zamenjajte `<ID>` z unikatnim ID-jem, ki ste ga uporabili pri ustvarjanju kode za svojo napravo.

    ⚠️ Ta **mora** biti enak ID-ju, ki ste ga uporabili na svoji napravi, sicer se strežniška koda ne bo naročila ali objavila na pravi temi.

    Ta koda ustvari MQTT odjemalca z unikatnim imenom in se poveže z brokerjem *test.mosquitto.org*. Nato zažene obdelovalno zanko, ki teče v ozadju in posluša sporočila na vseh naročenih temah.

    Odjemalec se nato naroči na sporočila na temi za telemetrijo in definira funkcijo, ki se pokliče, ko je sporočilo prejeto. Ko je prejeto telemetrijsko sporočilo, se pokliče funkcija `handle_telemetry`, ki izpiše prejeto sporočilo v konzolo.

    Na koncu neskončna zanka ohranja aplikacijo aktivno. MQTT odjemalec posluša sporočila v ozadju in deluje ves čas, ko glavna aplikacija teče.

1. V terminalu v VS Code zaženite naslednji ukaz, da zaženete svojo Python aplikacijo:

    ```sh
    python app.py
    ```

    Aplikacija bo začela poslušati sporočila z IoT naprave.

1. Prepričajte se, da vaša naprava deluje in pošilja telemetrijska sporočila. Prilagodite nivoje svetlobe, ki jih zazna vaša fizična ali virtualna naprava. Prejeta sporočila bodo izpisana v terminalu.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Datoteka `app.py` v virtualnem okolju nightlight mora biti zagnana, da lahko datoteka `app.py` v virtualnem okolju nightlight-server prejme poslana sporočila.

> 💁 To kodo najdete v mapi [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server).

### Kako pogosto naj se pošilja telemetrija?

Pomembno vprašanje pri telemetriji je, kako pogosto meriti in pošiljati podatke? Odgovor je – odvisno. Če merite pogosto, lahko hitreje reagirate na spremembe, vendar porabite več energije, več pasovne širine, ustvarite več podatkov in potrebujete več oblačnih virov za obdelavo. Meriti morate dovolj pogosto, vendar ne preveč pogosto.

Za termostat je merjenje vsakih nekaj minut verjetno več kot dovolj, saj se temperature ne spreminjajo tako pogosto. Če merite le enkrat na dan, bi lahko ogrevali hišo za nočne temperature sredi sončnega dne, medtem ko bi z merjenjem vsako sekundo ustvarili na tisoče nepotrebno podvojenih meritev temperature, kar bi upočasnilo internetno hitrost in porabilo pasovno širino uporabnikov (težava za tiste z omejenimi podatkovnimi paketi), porabilo več energije, kar je lahko težava za naprave na baterije, in povečalo stroške oblačnih virov za obdelavo in shranjevanje.

Če spremljate podatke o stroju v tovarni, ki bi v primeru okvare lahko povzročil katastrofalno škodo in milijone evrov izgube, je morda potrebno merjenje večkrat na sekundo. Bolje je porabiti pasovno širino kot zamuditi telemetrijo, ki kaže, da je treba stroj ustaviti in popraviti, preden se pokvari.

> 💁 V takšni situaciji bi morda razmislili o uporabi robne naprave za obdelavo telemetrije, da zmanjšate odvisnost od interneta.

### Izguba povezljivosti

Internetne povezave so lahko nezanesljive, z izpadi, ki so pogosti. Kaj naj IoT naprava stori v teh okoliščinah – naj izgubi podatke ali jih shrani, dokler se povezljivost ne povrne? Spet je odgovor – odvisno.

Za termostat se podatki verjetno lahko izgubijo, takoj ko je narejena nova meritev temperature. Ogrevalni sistem ne zanima, da je bilo pred 20 minutami 20,5 °C, če je zdaj 19 °C – trenutna temperatura določa, ali naj bo ogrevanje vklopljeno ali izklopljeno.

Za stroje pa bi morda želeli obdržati podatke, še posebej, če se uporabljajo za iskanje trendov. Obstajajo modeli strojnega učenja, ki lahko zaznajo anomalije v tokovih podatkov, tako da pregledajo podatke za določeno časovno obdobje (na primer zadnjo uro) in zaznajo nenavadne podatke. To se pogosto uporablja za prediktivno vzdrževanje, kjer iščete znake, da bi se nekaj lahko kmalu pokvarilo, da lahko to popravite ali zamenjate, preden se to zgodi. Morda boste želeli, da se vsa telemetrija za stroj pošlje, da se lahko obdela za zaznavanje anomalij, zato bo IoT naprava, ko se lahko ponovno poveže, poslala vso telemetrijo, ustvarjeno med izpadom interneta.

Oblikovalci IoT naprav bi morali razmisliti tudi o tem, ali se lahko IoT naprava uporablja med izpadom interneta ali izgubo signala zaradi lokacije. Pametni termostat bi moral biti sposoben sprejeti nekaj omejenih odločitev za nadzor ogrevanja, če ne more poslati telemetrije v oblak zaradi izpada.

[![Ta ferrari je postal neuporaben, ker so ga poskušali nadgraditi pod zemljo, kjer ni mobilnega signala](../../../../../translated_images/sl/bricked-car.dc38f8efadc6c59d.webp)](https://twitter.com/internetofshit/status/1315736960082808832)

Za MQTT, da obvlada izgubo povezljivosti, morata biti naprava in strežniška koda odgovorni za zagotavljanje dostave sporočil, če je to potrebno, na primer z zahtevo, da se vsa poslana sporočila potrdijo z dodatnimi sporočili na odgovorni temi, in če ne, se ročno postavijo v čakalno vrsto za ponovno pošiljanje kasneje.

## Ukazi

Ukazi so sporočila, ki jih oblak pošlje napravi in ji naročijo, naj nekaj stori. Večinoma to vključuje podajanje nekega izhoda prek aktuatorja, lahko pa je tudi navodilo za samo napravo, na primer za ponovni zagon ali zbiranje dodatne telemetrije in njeno vračanje kot odgovor na ukaz.

![Internetno povezan termostat prejme ukaz za vklop ogrevanja](../../../../../translated_images/sl/commands.d6c06bbbb3a02cce.webp)

Termostat bi lahko prejel ukaz iz oblaka za vklop ogrevanja. Na podlagi telemetrijskih podatkov iz vseh senzorjev je oblačna storitev odločila, da mora biti ogrevanje vklopljeno, zato pošlje ustrezen ukaz.

### Pošiljanje ukazov MQTT brokerju

Naslednji korak za naš internetno nadzorovan nočni svetilnik je, da strežniška koda pošlje ukaz nazaj IoT napravi za nadzor svetlobe glede na zaznane nivoje svetlobe.

1. Odprite strežniško kodo v VS Code.

1. Dodajte naslednjo vrstico za deklaracijo `client_telemetry_topic`, da določite, na katero temo pošiljati ukaze:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Dodajte naslednjo kodo na konec funkcije `handle_telemetry`:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Ta koda pošlje JSON sporočilo na temo za ukaze z vrednostjo `led_on`, nastavljeno na true ali false, odvisno od tega, ali je svetloba manjša od 300 ali ne. Če je svetloba manjša od 300, se pošlje true, da napravi naroči, naj vklopi LED.

1. Zaženite kodo kot prej.

1. Prilagodite nivoje svetlobe, ki jih zazna vaša fizična ali virtualna naprava. Prejeta sporočila in poslani ukazi bodo zapisani v terminal:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 Telemetrija in ukazi se pošiljajo na eno temo. To pomeni, da se telemetrija iz več naprav pojavi na isti temi za telemetrijo, ukazi za več naprav pa na isti temi za ukaze. Če želite poslati ukaz določeni napravi, lahko uporabite več tem, poimenovanih z unikatnim ID-jem naprave, na primer `/commands/device1`, `/commands/device2`. Tako lahko naprava posluša sporočila, namenjena samo tej napravi.

> 💁 To kodo najdete v mapi [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server).

### Obdelava ukazov na IoT napravi

Zdaj, ko se ukazi pošiljajo s strežnika, lahko dodate kodo na IoT napravo za njihovo obdelavo in nadzor LED.

Sledite ustreznemu koraku spodaj, da poslušate ukaze iz MQTT brokerja:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Enokartični računalnik - Raspberry Pi/Virtualna IoT naprava](single-board-computer-commands.md)

Ko je ta koda napisana in deluje, eksperimentirajte s spreminjanjem nivojev svetlobe. Opazujte izhod strežnika in naprave ter LED, ko spreminjate nivoje svetlobe.

### Izguba povezljivosti

Kaj naj oblačna storitev stori, če mora poslati ukaz IoT napravi, ki je brez povezave? Spet je odgovor – odvisno.

Če zadnji ukaz preglasi prejšnjega, se prejšnji lahko verjetno ignorira. Če oblačna storitev pošlje ukaz za vklop ogrevanja, nato pa ukaz za izklop, se ukaz za vklop lahko ignorira in ne pošlje ponovno.

Če je treba ukaze obdelati po vrsti, na primer premik robotske roke navzgor, nato zapiranje prijemalke, jih je treba poslati po vrsti, ko se povezljivost povrne.

✅ Kako bi lahko naprava ali strežniška koda zagotovila, da se ukazi vedno pošljejo in obdelajo po vrsti prek MQTT, če je to potrebno?

---

## 🚀 Izziv

Izziv v zadnjih treh lekcijah je bil našteti čim več IoT naprav, ki jih imate doma, v šoli ali na delovnem mestu, in ugotoviti, ali so zgrajene okoli mikrokontrolerjev ali enokartičnih računalnikov, ali celo mešanice obojega, ter razmisliti, katere senzorje in aktuatorje uporabljajo.
Za te naprave razmislite, kakšna sporočila bi lahko pošiljale ali prejemale. Kakšno telemetrijo pošiljajo? Kakšna sporočila ali ukaze bi lahko prejemale? Ali menite, da so varne?

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Pregled in samostojno učenje

Preberite več o MQTT na [strani Wikipedia o MQTT](https://wikipedia.org/wiki/MQTT).

Poskusite sami zagnati MQTT strežnik z uporabo [Mosquitto](https://www.mosquitto.org) in se povežite nanj iz svoje IoT naprave ter strežniške kode.

> 💁 Nasvet - privzeto Mosquitto ne dovoljuje anonimnih povezav (torej povezav brez uporabniškega imena in gesla) ter ne dovoljuje povezav izven računalnika, na katerem deluje.
> To lahko popravite z [`mosquitto.conf` konfiguracijsko datoteko](https://www.mosquitto.org/man/mosquitto-conf-5.html) z naslednjim:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Naloga

[Primerjajte in primerjajte MQTT z drugimi komunikacijskimi protokoli](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitne nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.