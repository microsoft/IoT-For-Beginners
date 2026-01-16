<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "71b5040e0b3472f1c0949c9b55f224c0",
  "translation_date": "2025-08-28T19:54:24+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/README.md",
  "language_code": "lt"
}
-->
# Prijunkite savo įrenginį prie interneto

![Pamokos apžvalga piešinyje](../../../../../translated_images/lt/lesson-4.7344e074ea68fa545fd320b12dce36d72dd62d28c3b4596cb26cf315f434b98f.jpg)

> Piešinys sukurtas [Nitya Narasimhan](https://github.com/nitya). Spustelėkite paveikslėlį, kad pamatytumėte didesnę versiją.

Ši pamoka buvo dėstoma kaip dalis [Hello IoT serijos](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) iš [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Pamoka buvo pateikta per 2 vaizdo įrašus – 1 valandos pamoka ir 1 valandos konsultacija, kurioje gilinamasi į pamokos dalis ir atsakoma į klausimus.

[![Pamoka 4: Prijunkite savo įrenginį prie interneto](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Pamoka 4: Prijunkite savo įrenginį prie interneto - Konsultacijos](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Spustelėkite aukščiau esančius paveikslėlius, kad peržiūrėtumėte vaizdo įrašus

## Klausimynas prieš pamoką

[Klausimynas prieš pamoką](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Įvadas

**I** IoT reiškia **Internetą** – debesų ryšį ir paslaugas, kurios leidžia daugumą IoT įrenginių funkcijų, nuo duomenų rinkimo iš jutiklių, prijungtų prie įrenginio, iki pranešimų siuntimo, skirtų valdyti aktuatorius. IoT įrenginiai paprastai jungiasi prie vienos debesų IoT paslaugos naudodami standartinį ryšio protokolą, o ši paslauga yra prijungta prie likusios jūsų IoT programos, nuo AI paslaugų, kurios priima išmanius sprendimus remiantis jūsų duomenimis, iki interneto programų, skirtų valdymui ar ataskaitoms.

> 🎓 Duomenys, surinkti iš jutiklių ir išsiųsti į debesį, vadinami telemetrija.

IoT įrenginiai gali gauti pranešimus iš debesies. Dažnai pranešimai yra komandos – tai instrukcijos atlikti veiksmą arba viduje (pvz., paleisti iš naujo ar atnaujinti programinę įrangą), arba naudojant aktuatorių (pvz., įjungti šviesą).

Šioje pamokoje pristatomi kai kurie ryšio protokolai, kuriuos IoT įrenginiai gali naudoti prisijungdami prie debesies, ir duomenų tipai, kuriuos jie gali siųsti ar gauti. Taip pat praktiškai susipažinsite su šiais protokolais, pridėdami interneto valdymą savo naktinei lempai, perkeldami LED valdymo logiką į „serverio“ kodą, kuris veiks lokaliai.

Šioje pamokoje aptarsime:

* [Ryšio protokolai](../../../../../1-getting-started/lessons/4-connect-internet)
* [Pranešimų eilės telemetrijos transportas (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetrija](../../../../../1-getting-started/lessons/4-connect-internet)
* [Komandos](../../../../../1-getting-started/lessons/4-connect-internet)

## Ryšio protokolai

Yra keletas populiarių ryšio protokolų, kuriuos IoT įrenginiai naudoja bendraudami su internetu. Populiariausi yra pagrįsti publikavimo/prenumeravimo pranešimais per tam tikrą brokerį. IoT įrenginiai jungiasi prie brokerio ir publikuoja telemetriją bei prenumeruoja komandas. Debesų paslaugos taip pat jungiasi prie brokerio, prenumeruoja visus telemetrijos pranešimus ir publikuoja komandas arba konkretiems įrenginiams, arba įrenginių grupėms.

![IoT įrenginiai jungiasi prie brokerio, publikuoja telemetriją ir prenumeruoja komandas. Debesų paslaugos jungiasi prie brokerio, prenumeruoja visą telemetriją ir siunčia komandas konkretiems įrenginiams.](../../../../../translated_images/lt/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT yra populiariausias ryšio protokolas IoT įrenginiams ir yra aptariamas šioje pamokoje. Kiti protokolai apima AMQP ir HTTP/HTTPS.

## Pranešimų eilės telemetrijos transportas (MQTT)

[MQTT](http://mqtt.org) yra lengvas, atviras standartinis pranešimų protokolas, kuris gali siųsti pranešimus tarp įrenginių. Jis buvo sukurtas 1999 m. naftos vamzdynų stebėjimui, o po 15 metų IBM jį išleido kaip atvirą standartą.

MQTT turi vieną brokerį ir kelis klientus. Visi klientai jungiasi prie brokerio, o brokeris nukreipia pranešimus atitinkamiems klientams. Pranešimai nukreipiami naudojant pavadintas temas, o ne siunčiami tiesiogiai konkrečiam klientui. Klientas gali publikuoti temą, o visi klientai, prenumeruojantys tą temą, gaus pranešimą.

![IoT įrenginys publikuoja telemetriją temoje /telemetry, o debesų paslauga prenumeruoja tą temą](../../../../../translated_images/lt/mqtt.cbf7f21d9adc3e17548b359444cc11bb4bf2010543e32ece9a47becf54438c23.png)

✅ Atlikite tyrimą. Jei turite daug IoT įrenginių, kaip galite užtikrinti, kad jūsų MQTT brokeris galėtų apdoroti visus pranešimus?

### Prijunkite savo IoT įrenginį prie MQTT

Pirmasis žingsnis pridedant interneto valdymą savo naktinei lempai yra prijungti ją prie MQTT brokerio.

#### Užduotis

Prijunkite savo įrenginį prie MQTT brokerio.

Šioje pamokos dalyje prijungsite savo IoT naktinę lempą prie interneto, kad ją būtų galima valdyti nuotoliniu būdu. Vėliau šioje pamokoje jūsų IoT įrenginys per MQTT siųs telemetrijos pranešimą viešam MQTT brokeriui su šviesos lygiu, kurį perims serverio kodas, kurį parašysite. Šis kodas patikrins šviesos lygį ir išsiųs komandą įrenginiui, nurodydamas įjungti arba išjungti LED.

Realiame pasaulyje tokia sistema galėtų būti naudojama duomenims rinkti iš kelių šviesos jutiklių prieš priimant sprendimą įjungti šviesas vietoje, kurioje yra daug šviesų, pvz., stadione. Tai galėtų užkirsti kelią šviesų įjungimui, jei tik vieną jutiklį uždengtų debesys ar paukštis, bet kiti jutikliai aptiktų pakankamai šviesos.

✅ Kokiose kitose situacijose reikėtų įvertinti duomenis iš kelių jutiklių prieš siunčiant komandas?

Užuot sprendę MQTT brokerio nustatymo sudėtingumą kaip šios užduoties dalį, galite naudoti viešą testavimo serverį, kuris naudoja [Eclipse Mosquitto](https://www.mosquitto.org), atvirojo kodo MQTT brokerį. Šis testavimo brokeris yra viešai prieinamas adresu [test.mosquitto.org](https://test.mosquitto.org) ir nereikalauja paskyros, todėl tai puikus įrankis MQTT klientų ir serverių testavimui.

> 💁 Šis testavimo brokeris yra viešas ir nesaugus. Bet kas galėtų klausytis, ką publikuojate, todėl jis neturėtų būti naudojamas su duomenimis, kuriuos reikia laikyti privačiais.

![Užduoties srauto diagrama, rodanti šviesos lygių skaitymą ir tikrinimą bei LED valdymą](../../../../../translated_images/lt/assignment-1-internet-flow.3256feab5f052fd273bf4e331157c574c2c3fa42e479836fc9c3586f41db35a5.png)

Sekite atitinkamą žingsnį žemiau, kad prijungtumėte savo įrenginį prie MQTT brokerio:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Vieno plokštės kompiuteris - Raspberry Pi/Virtualus IoT įrenginys](single-board-computer-mqtt.md)

### Gilesnis žvilgsnis į MQTT

Temos gali turėti hierarchiją, o klientai gali prenumeruoti skirtingus hierarchijos lygius naudodami pakaitos simbolius. Pavyzdžiui, galite siųsti temperatūros telemetrijos pranešimus į temą `/telemetry/temperature` ir drėgmės pranešimus į temą `/telemetry/humidity`, o tada savo debesų programoje prenumeruoti temą `/telemetry/*`, kad gautumėte tiek temperatūros, tiek drėgmės telemetrijos pranešimus.

Pranešimai gali būti siunčiami su kokybės užtikrinimo lygiu (QoS), kuris nustato pranešimo gavimo garantiją.

* Vieną kartą – pranešimas siunčiamas tik vieną kartą, o klientas ir brokeris nesiima papildomų veiksmų, kad patvirtintų pristatymą (siųsti ir pamiršti).
* Bent vieną kartą – pranešimas kelis kartus persiunčiamas siuntėjo, kol gaunamas patvirtinimas (patvirtintas pristatymas).
* Tiksliai vieną kartą – siuntėjas ir gavėjas vykdo dviejų lygių rankos paspaudimą, kad užtikrintų, jog pranešimas bus gautas tik vieną kartą (užtikrintas pristatymas).

✅ Kokiose situacijose reikėtų užtikrinto pristatymo pranešimo, o ne „siųsti ir pamiršti“ pranešimo?

Nors pavadinime yra „Message Queueing“ (MQTT inicialai), jis iš tikrųjų nepalaiko pranešimų eilių. Tai reiškia, kad jei klientas atsijungia, o vėliau vėl prisijungia, jis negaus pranešimų, išsiųstų atsijungimo metu, išskyrus tuos pranešimus, kuriuos jis jau pradėjo apdoroti naudodamas QoS procesą. Pranešimai gali turėti nustatytą „retained“ vėliavėlę. Jei ji nustatyta, MQTT brokeris saugos paskutinį pranešimą, išsiųstą temoje su šia vėliavėle, ir išsiųs jį bet kuriems klientams, kurie vėliau prenumeruos temą. Tokiu būdu klientai visada gaus naujausią pranešimą.

MQTT taip pat palaiko „keep alive“ funkciją, kuri tikrina, ar ryšys vis dar gyvas per ilgus tarpus tarp pranešimų.

> 🦟 [Mosquitto iš Eclipse Foundation](https://mosquitto.org) turi nemokamą MQTT brokerį, kurį galite paleisti patys, kad eksperimentuotumėte su MQTT, taip pat viešą MQTT brokerį, kurį galite naudoti savo kodo testavimui, talpinamą adresu [test.mosquitto.org](https://test.mosquitto.org).

MQTT ryšiai gali būti vieši ir atviri arba užšifruoti ir apsaugoti naudojant vartotojo vardus ir slaptažodžius arba sertifikatus.

> 💁 MQTT bendrauja per TCP/IP, tą patį pagrindinį tinklo protokolą kaip HTTP, bet per kitą prievadą. Taip pat galite naudoti MQTT per „websockets“, kad bendrautumėte su interneto programomis, veikiančiomis naršyklėje, arba situacijose, kai ugniasienės ar kitos tinklo taisyklės blokuoja standartinius MQTT ryšius.

## Telemetrija

Žodis telemetrija kilęs iš graikų kalbos šaknų, reiškiančių „matuoti nuotoliniu būdu“. Telemetrija – tai duomenų rinkimas iš jutiklių ir jų siuntimas į debesį.

> 💁 Vienas iš ankstyviausių telemetrijos įrenginių buvo išrastas Prancūzijoje 1874 m. ir realiu laiku siuntė orų ir sniego gylio duomenis iš Monblano į Paryžių. Jis naudojo fizinius laidus, nes tuo metu nebuvo belaidžių technologijų.

Pažvelkime atgal į išmaniojo termostato pavyzdį iš 1 pamokos.

![Interneto prijungtas termostatas, naudojantis kelis kambario jutiklius](../../../../../translated_images/lt/telemetry.21e5d8b97649d2eb.webp)

Termostatas turi temperatūros jutiklius telemetrijai rinkti. Labiausiai tikėtina, kad jis turės vieną įmontuotą temperatūros jutiklį, ir jis gali prisijungti prie kelių išorinių temperatūros jutiklių per belaidį protokolą, pvz., [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Telemetrijos duomenų, kuriuos jis galėtų siųsti, pavyzdys:

| Pavadinimas | Vertė | Aprašymas |
| ----------- | ----- | --------- |
| `thermostat_temperature` | 18°C | Temperatūra, išmatuota termostato įmontuotu temperatūros jutikliu |
| `livingroom_temperature` | 19°C | Temperatūra, išmatuota nuotoliniu temperatūros jutikliu, kuris buvo pavadintas `livingroom`, kad identifikuotų kambarį, kuriame jis yra |
| `bedroom_temperature` | 21°C | Temperatūra, išmatuota nuotoliniu temperatūros jutikliu, kuris buvo pavadintas `bedroom`, kad identifikuotų kambarį, kuriame jis yra |

Debesų paslauga gali naudoti šiuos telemetrijos duomenis, kad priimtų sprendimus dėl komandų siuntimo šildymo valdymui.

### Siųskite telemetriją iš savo IoT įrenginio

Kitas žingsnis pridedant interneto valdymą savo naktinei lempai yra šviesos lygio telemetrijos siuntimas MQTT brokeriui telemetrijos temoje.

#### Užduotis – siųskite telemetriją iš savo IoT įrenginio

Siųskite šviesos lygio telemetriją MQTT brokeriui.

Duomenys siunčiami užkoduoti kaip JSON – tai JavaScript objektų notacija, standartas duomenims užkoduoti tekstu naudojant raktų/vertės poras.

✅ Jei dar nesusidūrėte su JSON, galite sužinoti daugiau apie jį [JSON.org dokumentacijoje](https://www.json.org/).

Sekite atitinkamą žingsnį žemiau, kad išsiųstumėte telemetriją iš savo įrenginio į MQTT brokerį:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Vieno plokštės kompiuteris - Raspberry Pi/Virtualus IoT įrenginys](single-board-computer-telemetry.md)

### Gaukite telemetriją iš MQTT brokerio

Nėra prasmės siųsti telemetriją, jei niekas kitoje pusėje jos neklauso. Šviesos lygio telemetrijai reikia kažko, kas ją klausytų ir apdorotų duomenis. Šis „serverio“ kodas yra toks kodas, kurį diegsite debesų paslaugoje kaip didesnės IoT programos dalį, tačiau čia jūs ketinate paleisti šį kodą lokaliai savo kompiuteryje (arba savo Pi, jei koduojate tiesiogiai ten). Serverio kodas susideda iš Python programos, kuri klausosi telemetrijos pranešimų per MQTT su šviesos lygiais. Vėliau šioje pamokoje ji atsakys komandiniu pranešimu su instrukcijomis įjungti arba išjungti LED.

✅ Atlikite tyrimą: Kas nutinka MQTT pranešimams, jei nėra klausytojo?

#### Įdiekite Python ir VS Code

Jei neturite Python ir VS Code įdiegtų lokaliai, turėsite juos abu įdiegti, kad galėtumėte rašyti serverio kodą. Jei naudojate virtualų IoT įrenginį arba dirbate su Raspberry Pi, galite praleisti šį žingsnį, nes turėtumėte jau turėti tai įdiegta ir sukonfigūruota.

##### Užduotis – įdiekite Python ir VS Code

Įdiekite Python ir VS Code.

1. Įdiekite Python. Žr. [Python atsisiuntimų puslapį](https://www.python.org/downloads/), kad gautumėte instrukcijas, kaip įdiegti naujausią Python versiją.


💁 Galite naudoti bet kokį Python IDE ar redaktorių šioms pamokoms, jei turite mėgstamą įrankį, tačiau pamokose bus pateikiamos instrukcijos, remiantis VS Code.
1. Įdiekite VS Code Pylance plėtinį. Tai yra VS Code plėtinys, kuris suteikia Python kalbos palaikymą. Diegimo instrukcijas rasite [Pylance plėtinio dokumentacijoje](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance).

#### Python virtualios aplinkos konfigūravimas

Viena iš galingiausių Python funkcijų yra galimybė įdiegti [pip paketus](https://pypi.org) – tai yra kitų žmonių parašyti ir internete paskelbti kodo paketai. Viena komanda galite įdiegti pip paketą į savo kompiuterį ir naudoti jį savo kode. Naudosite pip, kad įdiegtumėte paketą, skirtą bendrauti per MQTT.

Pagal numatytuosius nustatymus, kai įdiegiate paketą, jis tampa prieinamas visame jūsų kompiuteryje, ir tai gali sukelti problemų su paketų versijomis – pavyzdžiui, viena programa gali priklausyti nuo vienos paketo versijos, kuri nustoja veikti, kai įdiegiate naują versiją kitai programai. Norėdami išspręsti šią problemą, galite naudoti [Python virtualią aplinką](https://docs.python.org/3/library/venv.html), kuri iš esmės yra Python kopija atskirame aplanke. Kai įdiegiate pip paketus, jie įdiegiami tik tame aplanke.

##### Užduotis – sukonfigūruoti Python virtualią aplinką

Sukonfigūruokite Python virtualią aplinką ir įdiekite MQTT pip paketus.

1. Terminale arba komandų eilutėje paleiskite šias komandas pasirinktoje vietoje, kad sukurtumėte ir pereitumėte į naują katalogą:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Dabar paleiskite šią komandą, kad sukurtumėte virtualią aplinką `.venv` aplanke:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Turite aiškiai nurodyti `python3`, kad sukurtumėte virtualią aplinką, nes gali būti, kad jūsų sistemoje įdiegta Python 2 versija kartu su Python 3 (naujausia versija). Jei turite Python 2, komanda `python` naudos Python 2 vietoj Python 3.

1. Aktyvuokite virtualią aplinką:

    * Windows sistemoje:
        * Jei naudojate Command Prompt arba Command Prompt per Windows Terminal, paleiskite:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Jei naudojate PowerShell, paleiskite:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS arba Linux sistemoje paleiskite:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Šias komandas reikia paleisti iš tos pačios vietos, kurioje paleidote komandą virtualiai aplinkai sukurti. Jums niekada nereikės pereiti į `.venv` aplanką – visada turėtumėte paleisti aktyvavimo komandą ir bet kokias komandas paketams įdiegti ar kodui vykdyti iš aplanko, kuriame sukūrėte virtualią aplinką.

1. Kai virtuali aplinka bus aktyvuota, numatytoji `python` komanda paleis Python versiją, kuri buvo naudojama virtualiai aplinkai sukurti. Paleiskite šią komandą, kad sužinotumėte versiją:

    ```sh
    python --version
    ```

    Rezultatas bus panašus į šį:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Jūsų Python versija gali skirtis – jei tik ji yra 3.6 ar naujesnė, viskas gerai. Jei ne, ištrinkite šį aplanką, įdiekite naujesnę Python versiją ir bandykite dar kartą.

1. Paleiskite šias komandas, kad įdiegtumėte pip paketą [Paho-MQTT](https://pypi.org/project/paho-mqtt/), populiarią MQTT biblioteką.

    ```sh
    pip install paho-mqtt
    ```

    Šis pip paketas bus įdiegtas tik virtualioje aplinkoje ir nebus prieinamas už jos ribų.

#### Parašykite serverio kodą

Dabar serverio kodą galima parašyti Python kalba.

##### Užduotis – parašyti serverio kodą

Parašykite serverio kodą.

1. Terminale arba komandų eilutėje, virtualioje aplinkoje, paleiskite šią komandą, kad sukurtumėte Python failą `app.py`:

    * Windows sistemoje paleiskite:

        ```cmd
        type nul > app.py
        ```

    * macOS arba Linux sistemoje paleiskite:

        ```cmd
        touch app.py
        ```

1. Atidarykite dabartinį aplanką VS Code:

    ```sh
    code .
    ```

1. Kai VS Code paleidžiamas, jis aktyvuos Python virtualią aplinką. Tai bus nurodyta apatinėje būsenos juostoje:

    ![VS Code rodo pasirinktą virtualią aplinką](../../../../../translated_images/lt/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Jei VS Code terminalas jau veikia, kai VS Code paleidžiamas, virtuali aplinka jame nebus aktyvuota. Paprasčiausia yra uždaryti terminalą naudojant mygtuką **Kill the active terminal instance**:

    ![VS Code mygtukas Kill the active terminal instance](../../../../../translated_images/lt/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Paleiskite naują VS Code terminalą pasirinkdami *Terminal -> New Terminal* arba paspausdami `` CTRL+` ``. Naujas terminalas įkels virtualią aplinką, o aktyvavimo komanda bus rodoma terminale. Virtualios aplinkos pavadinimas (`.venv`) taip pat bus matomas eilutėje:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Atidarykite `app.py` failą iš VS Code naršyklės ir pridėkite šį kodą:

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

    Pakeiskite `<ID>` 6 eilutėje į unikalų ID, kurį naudojote kurdami savo įrenginio kodą.

    ⚠️ Tai **privalo** būti tas pats ID, kurį naudojote savo įrenginyje, kitaip serverio kodas neprenumeruos ir nesiųs pranešimų į tinkamą temą.

    Šis kodas sukuria MQTT klientą su unikaliu pavadinimu ir prisijungia prie *test.mosquitto.org* brokerio. Tada jis pradeda apdorojimo ciklą, kuris veikia fone ir klausosi pranešimų iš prenumeruojamų temų.

    Klientas prenumeruoja pranešimus iš telemetrijos temos ir apibrėžia funkciją, kuri iškviečiama, kai gaunamas pranešimas. Kai gaunamas telemetrijos pranešimas, iškviečiama `handle_telemetry` funkcija, kuri atspausdina gautą pranešimą į konsolę.

    Galiausiai, begalinis ciklas palaiko programą veikiančią. MQTT klientas klausosi pranešimų fone ir veikia tol, kol veikia pagrindinė programa.

1. Iš VS Code terminalo paleiskite šią komandą, kad paleistumėte savo Python programą:

    ```sh
    python app.py
    ```

    Programa pradės klausytis pranešimų iš IoT įrenginio.

1. Įsitikinkite, kad jūsų įrenginys veikia ir siunčia telemetrijos pranešimus. Reguliuokite fizinio ar virtualaus įrenginio aptinkamą šviesos lygį. Gaunami pranešimai bus atspausdinti terminale.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    `app.py` failas naktinės lemputės virtualioje aplinkoje turi būti paleistas, kad `app.py` failas naktinės lemputės serverio virtualioje aplinkoje galėtų gauti siunčiamus pranešimus.

> 💁 Šį kodą galite rasti [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server) aplanke.

### Kaip dažnai turėtų būti siunčiama telemetrija?

Vienas svarbus aspektas, susijęs su telemetrija, yra tai, kaip dažnai reikia matuoti ir siųsti duomenis? Atsakymas – tai priklauso. Jei matuojate dažnai, galite greičiau reaguoti į pokyčius, tačiau sunaudojate daugiau energijos, daugiau pralaidumo, sugeneruojate daugiau duomenų ir reikia daugiau debesų išteklių jiems apdoroti. Turite matuoti pakankamai dažnai, bet ne per dažnai.

Pavyzdžiui, termostatui matuoti kas kelias minutes greičiausiai yra daugiau nei pakankamai, nes temperatūra nesikeičia taip dažnai. Jei matuosite tik kartą per dieną, galite šildyti namus nakties temperatūrai viduryje saulėtos dienos, o jei matuosite kas sekundę, turėsite tūkstančius nereikalingų temperatūros matavimų, kurie sumažins vartotojo interneto greitį ir pralaidumą (problema tiems, kurie turi ribotus pralaidumo planus), sunaudos daugiau energijos, kas gali būti problema baterijomis maitinamiems įrenginiams, ir padidins debesų kompiuterijos išteklių apdorojimo ir saugojimo išlaidas.

Jei stebite duomenis apie gamyklos įrenginį, kurio gedimas gali sukelti katastrofišką žalą ir milijonus dolerių nuostolių, tada gali būti būtina matuoti kelis kartus per sekundę. Geriau švaistyti pralaidumą nei praleisti telemetriją, kuri rodo, kad įrenginį reikia sustabdyti ir pataisyti prieš jam sugendant.

> 💁 Tokiu atveju galite apsvarstyti galimybę naudoti kraštinį įrenginį, kad pirmiausia apdorotumėte telemetriją ir sumažintumėte priklausomybę nuo interneto.

### Ryšio praradimas

Interneto ryšys gali būti nepatikimas, dažni nutrūkimai. Ką turėtų daryti IoT įrenginys tokiomis aplinkybėmis – prarasti duomenis ar juos saugoti, kol ryšys bus atkurtas? Vėlgi, atsakymas – tai priklauso.

Termostatui duomenys greičiausiai gali būti prarasti, kai tik gaunamas naujas temperatūros matavimas. Šildymo sistema nesirūpina, kad prieš 20 minučių buvo 20,5°C, jei dabar yra 19°C – dabartinė temperatūra lemia, ar šildymas turėtų būti įjungtas ar išjungtas.

Gamyklos įrenginiams galbūt norėsite išsaugoti duomenis, ypač jei jie naudojami tendencijoms stebėti. Yra mašininio mokymosi modelių, kurie gali aptikti anomalijas duomenų srautuose, analizuodami duomenis per tam tikrą laikotarpį (pvz., paskutinę valandą) ir ieškodami anomalijų. Tai dažnai naudojama prevencinei priežiūrai, ieškant požymių, kad kažkas gali greitai sugesti, kad galėtumėte tai pataisyti ar pakeisti prieš tai įvykstant. Galbūt norėsite, kad visi įrenginio telemetrijos duomenys būtų išsiųsti, kad jie galėtų būti apdoroti anomalijų aptikimui, todėl, kai IoT įrenginys vėl prisijungs, jis išsiųs visą telemetriją, sugeneruotą per interneto nutrūkimą.

IoT įrenginių kūrėjai taip pat turėtų apsvarstyti, ar IoT įrenginys gali būti naudojamas interneto nutrūkimo ar signalo praradimo dėl vietos sąlygų metu. Išmanusis termostatas turėtų galėti priimti ribotus sprendimus dėl šildymo valdymo, jei jis negali siųsti telemetrijos į debesį dėl nutrūkimo.

[![Šis Ferrari tapo neveiksnus, nes kažkas bandė jį atnaujinti po žeme, kur nėra mobiliojo ryšio](../../../../../translated_images/lt/bricked-car.dc38f8efadc6c59d76211f981a521efb300939283dee468f79503aae3ec67615.png)](https://twitter.com/internetofshit/status/1315736960082808832)

Kad MQTT galėtų susidoroti su ryšio praradimu, įrenginio ir serverio kodas turės būti atsakingas už pranešimų pristatymo užtikrinimą, jei to reikia, pavyzdžiui, reikalaujant, kad visi išsiųsti pranešimai būtų atsakyti papildomais pranešimais atsakymo temoje, o jei ne, jie būtų rankiniu būdu eilėje, kad būtų pakartoti vėliau.

## Komandos

Komandos yra pranešimai, siunčiami iš debesies į įrenginį, nurodantys jam atlikti tam tikrą veiksmą. Dažniausiai tai apima tam tikrą išvestį per pavarą, tačiau tai gali būti ir nurodymas pačiam įrenginiui, pavyzdžiui, paleisti iš naujo arba surinkti papildomą telemetriją ir grąžinti ją kaip atsakymą į komandą.

![Interneto prijungtas termostatas, gaunantis komandą įjungti šildymą](../../../../../translated_images/lt/commands.d6c06bbbb3a02cce95f2831a1c331daf6dedd4e470c4aa2b0ae54f332016e504.png)

Termostatas galėtų gauti komandą iš debesies įjungti šildymą. Remiantis visų jutiklių telemetrijos duomenimis, debesų paslauga nusprendė, kad šildymas turėtų būti įjungtas, todėl siunčia atitinkamą komandą.

### Siųsti komandas MQTT brokeriui

Kitas žingsnis mūsų interneto valdomai naktinei lemputei yra serverio kodo siuntimas komandos atgal į IoT įrenginį, kad būtų valdomas šviesos lygis, kurį jis aptinka.

1. Atidarykite serverio kodą VS Code

1. Pridėkite šią eilutę po `client_telemetry_topic` deklaracijos, kad apibrėžtumėte, į kurią temą siųsti komandas:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Pridėkite šį kodą į `handle_telemetry` funkcijos pabaigą:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Tai siunčia JSON pranešimą į komandų temą su `led_on` reikšme, nustatyta į true arba false, priklausomai nuo to, ar šviesa yra mažesnė nei 300. Jei šviesa yra mažesnė nei 300, siunčiama true, kad įrenginys įjungtų LED.

1. Paleiskite kodą kaip anksčiau

1. Reguliuokite fizinio ar virtualaus įrenginio aptinkamą šviesos lygį. Gaunami pranešimai ir siunčiamos komandos bus atspausdintos terminale:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 Telemetrija ir komandos siunčiamos vienoje temoje kiekviena. Tai reiškia, kad telemetrija iš kelių įrenginių bus rodoma toje pačioje telemetrijos temoje, o komandos keliems įrenginiams bus rodomos toje pačioje komandų temoje. Jei norėtumėte siųsti komandą konkrečiam įrenginiui, galėtumėte naudoti kelias temas, pavadintas unikaliu įrenginio ID, pvz., `/commands/device1`, `/commands/device2`. Tokiu būdu įrenginys galėtų klausytis tik jam skirtų pranešimų.

> 💁 Šį kodą galite rasti [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server) aplanke.

### Komandų apdorojimas IoT įrenginyje

Dabar, kai komandos siunčiamos iš serverio, galite pridėti kodą IoT įrenginyje, kad jas apdorotumėte ir valdytumėte LED.

Sekite atitinkamą žingsnį, kad klausytumėte komandų iš MQTT brokerio:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Vienos plokštės kompiuteris - Raspberry Pi/Virtualus IoT įrenginys](single-board-computer-commands.md)

Kai šis kodas bus parašytas ir paleistas, eksperimentuokite keisdami šviesos lygius. Stebėkite serverio ir įrenginio išvestį bei LED veikimą keičiant šviesos lygius.

### Ryšio praradimas

Ką turėtų daryti debesų paslauga, jei reikia siųsti komandą IoT įrenginiui, kuris yra neprisijungęs? Vėlgi, atsakymas – tai priklauso.

Jei naujausia komanda pakeičia ankstesnę, ankstesnės greičiausiai galima nepaisyti. Jei debesų paslauga siunčia komandą įjungti šildymą, tada siunčia komandą jį išjungti, tada įjungimo komandos galima nepaisyti ir jos neperduoti.

Jei komandos turi būti apdorotos eilės tvarka, pvz., pakelti roboto ranką, tada uždaryti griebtuvą, jos turi būti siunčiamos iš eil
Apie šiuos įrenginius pagalvokite, kokias žinutes jie gali siųsti ar gauti. Kokius telemetrijos duomenis jie siunčia? Kokias žinutes ar komandas jie gali gauti? Ar manote, kad jie yra saugūs?

## Klausimai po paskaitos

[Klausimai po paskaitos](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Apžvalga ir savarankiškas mokymasis

Skaitykite daugiau apie MQTT [MQTT Wikipedia puslapyje](https://wikipedia.org/wiki/MQTT).

Pabandykite patys paleisti MQTT brokerį naudodami [Mosquitto](https://www.mosquitto.org) ir prisijunkite prie jo iš savo IoT įrenginio bei serverio kodo.

> 💁 Patarimas - pagal numatytuosius nustatymus Mosquitto neleidžia anonimiškų prisijungimų (t. y. prisijungimų be vartotojo vardo ir slaptažodžio) ir neleidžia prisijungimų iš kitų kompiuterių, nei tas, kuriame jis veikia.  
> Tai galite išspręsti naudodami [`mosquitto.conf` konfigūracijos failą](https://www.mosquitto.org/man/mosquitto-conf-5.html) su šiuo turiniu:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Užduotis

[Palyginkite ir kontrastuokite MQTT su kitais komunikacijos protokolais](assignment.md)

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant dirbtinio intelekto vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipiame dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudotis profesionalių vertėjų paslaugomis. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus aiškinimus, kylančius dėl šio vertimo naudojimo.