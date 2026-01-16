<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-28T12:37:19+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "sl"
}
-->
Razumeti jezik

![Skica pregleda te lekcije](../../../../../translated_images/sl/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.jpg)

> Skica avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite sliko za večjo različico.

## Kviz pred predavanjem

[Kviz pred predavanjem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Uvod

V prejšnji lekciji ste pretvorili govor v besedilo. Da bi to lahko uporabili za programiranje pametnega časovnika, mora vaša koda razumeti, kaj je bilo povedano. Lahko bi predpostavili, da bo uporabnik izrekel točno določen stavek, kot na primer "Nastavi časovnik za 3 minute", in analizirali ta izraz, da bi ugotovili, kako dolgo naj časovnik traja. Vendar to ni zelo uporabniku prijazno. Če bi uporabnik rekel "Nastavi časovnik za 3 minute", bi vi ali jaz razumeli, kaj to pomeni, vaša koda pa ne, saj bi pričakovala točno določen stavek.

Tu pride v poštev razumevanje jezika, kjer se uporabljajo AI modeli za interpretacijo besedila in vračanje potrebnih podrobnosti. Na primer, model bi lahko razumel tako "Nastavi časovnik za 3 minute" kot "Nastavi 3-minutni časovnik" in ugotovil, da je potreben časovnik za 3 minute.

V tej lekciji boste spoznali modele za razumevanje jezika, kako jih ustvariti, trenirati in uporabljati v svoji kodi.

V tej lekciji bomo obravnavali:

* [Razumevanje jezika](../../../../../6-consumer/lessons/2-language-understanding)
* [Ustvarjanje modela za razumevanje jezika](../../../../../6-consumer/lessons/2-language-understanding)
* [Nameni in entitete](../../../../../6-consumer/lessons/2-language-understanding)
* [Uporaba modela za razumevanje jezika](../../../../../6-consumer/lessons/2-language-understanding)

## Razumevanje jezika

Ljudje uporabljamo jezik za komunikacijo že stotisoče let. Komuniciramo z besedami, zvoki ali dejanji in razumemo, kaj je bilo povedano, tako pomen besed, zvokov ali dejanj kot tudi njihov kontekst. Razumemo iskrenost in sarkazem, kar omogoča, da iste besede pomenijo različne stvari glede na ton našega glasu.

✅ Razmislite o nekaterih pogovorih, ki ste jih imeli nedavno. Koliko teh pogovorov bi bilo težko razumeti računalniku, ker potrebujejo kontekst?

Razumevanje jezika, imenovano tudi razumevanje naravnega jezika, je del področja umetne inteligence, imenovanega obdelava naravnega jezika (NLP), in se ukvarja z razumevanjem besedil, poskuša razumeti podrobnosti besed ali stavkov. Če uporabljate glasovnega asistenta, kot sta Alexa ali Siri, ste že uporabljali storitve za razumevanje jezika. To so AI storitve v ozadju, ki na primer pretvorijo "Alexa, predvajaj najnovejši album Taylor Swift" v mojo hčerko, ki pleše po dnevni sobi ob svojih najljubših pesmih.

> 💁 Računalniki, kljub vsemu napredku, še vedno niso sposobni resnično razumeti besedila. Ko govorimo o razumevanju jezika pri računalnikih, ne mislimo na ničesar, kar bi bilo blizu človeški komunikaciji. Namesto tega mislimo na to, da vzamejo nekaj besed in izluščijo ključne podrobnosti.

Kot ljudje razumemo jezik, ne da bi o tem zares razmišljali. Če bi prosil drugega človeka, naj "predvaja najnovejši album Taylor Swift", bi ta instinktivno vedel, kaj mislim. Za računalnik je to težje. Moral bi vzeti besede, pretvorjene iz govora v besedilo, in ugotoviti naslednje informacije:

* Predvajati je treba glasbo
* Glasba je od izvajalke Taylor Swift
* Specifična glasba je celoten album z več skladbami v določenem vrstnem redu
* Taylor Swift ima veliko albumov, zato jih je treba razvrstiti po kronološkem vrstnem redu, pri čemer je najnovejši tisti, ki je potreben

✅ Pomislite na nekaj drugih stavkov, ki ste jih izrekli pri podajanju prošenj, na primer naročanje kave ali prošnja družinskemu članu, naj vam nekaj poda. Poskusite jih razčleniti na informacije, ki bi jih računalnik moral izluščiti, da bi razumel stavek.

Modeli za razumevanje jezika so AI modeli, ki so trenirani za izluščitev določenih podrobnosti iz jezika in so nato trenirani za specifične naloge z uporabo prenosa učenja, podobno kot ste trenirali model Custom Vision z majhnim naborom slik. Lahko vzamete model in ga nato trenirate z besedilom, ki ga želite, da razume.

## Ustvarjanje modela za razumevanje jezika

![Logotip LUIS](../../../../../translated_images/sl/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.png)

Modele za razumevanje jezika lahko ustvarite z LUIS, Microsoftovo storitvijo za razumevanje jezika, ki je del Cognitive Services.

### Naloga - ustvarjanje vira za avtorstvo

Za uporabo LUIS morate ustvariti vir za avtorstvo.

1. Uporabite naslednji ukaz za ustvarjanje vira za avtorstvo v svoji skupini virov `smart-timer`:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Zamenjajte `<location>` z lokacijo, ki ste jo uporabili pri ustvarjanju skupine virov.

    > ⚠️ LUIS ni na voljo v vseh regijah, zato če prejmete naslednjo napako:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > izberite drugo regijo.

    To bo ustvarilo brezplačen vir za avtorstvo LUIS.

### Naloga - ustvarjanje aplikacije za razumevanje jezika

1. Odprite portal LUIS na [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) v svojem brskalniku in se prijavite z istim računom, ki ste ga uporabljali za Azure.

1. Sledite navodilom v pogovornem oknu za izbiro svoje naročnine Azure, nato izberite vir `smart-timer-luis-authoring`, ki ste ga pravkar ustvarili.

1. Na seznamu *Conversation apps* izberite gumb **New app**, da ustvarite novo aplikacijo. Poimenujte novo aplikacijo `smart-timer` in nastavite *Culture* na svoj jezik.

    > 💁 Obstaja polje za napovedni vir. Lahko ustvarite drugi vir samo za napovedovanje, vendar brezplačen vir za avtorstvo omogoča 1.000 napovedi na mesec, kar bi moralo zadostovati za razvoj, zato lahko to polje pustite prazno.

1. Preberite vodnik, ki se prikaže, ko ustvarite aplikacijo, da dobite razumevanje korakov, ki jih morate opraviti za treniranje modela za razumevanje jezika. Ko končate, zaprite vodnik.

## Nameni in entitete

Razumevanje jezika temelji na *namenih* in *entitetah*. Nameni so tisto, kar besede želijo doseči, na primer predvajanje glasbe, nastavitev časovnika ali naročanje hrane. Entitete so tisto, na kar se namen nanaša, na primer album, dolžina časovnika ali vrsta hrane. Vsak stavek, ki ga model interpretira, mora imeti vsaj en namen in po želji eno ali več entitet.

Nekaj primerov:

| Stavek                                            | Namen           | Entitete                                   |
| ------------------------------------------------- | --------------- | ------------------------------------------ |
| "Predvajaj najnovejši album Taylor Swift"         | *predvajaj glasbo* | *najnovejši album Taylor Swift*           |
| "Nastavi časovnik za 3 minute"                   | *nastavi časovnik* | *3 minute*                                |
| "Prekliči moj časovnik"                          | *prekliči časovnik* | Nobena                                    |
| "Naroči 3 velike pice s šunko in solato Caesar"  | *naroči hrano*   | *3 velike pice s šunko*, *solata Caesar*  |

✅ Pri stavkih, o katerih ste razmišljali prej, kaj bi bil namen in katere entitete bi bile v tem stavku?

Za treniranje LUIS najprej nastavite entitete. Te so lahko fiksni seznam izrazov ali pa se učijo iz besedila. Na primer, lahko zagotovite fiksni seznam hrane, ki je na voljo v vašem meniju, z različicami (ali sopomenkami) vsake besede, kot sta *jajčevec* in *melancan* kot različici za *melancan*. LUIS ima tudi vnaprej pripravljene entitete, ki jih lahko uporabite, na primer številke in lokacije.

Za nastavitev časovnika bi lahko imeli eno entiteto, ki uporablja vnaprej pripravljene številčne entitete za čas, in drugo za enote, kot so minute in sekunde. Vsaka enota bi imela več različic za edninsko in množinsko obliko - na primer minuta in minute.

Ko so entitete definirane, ustvarite namene. Ti se učijo s pomočjo modela na podlagi primerov stavkov, ki jih zagotovite (imenovanih izreki). Na primer, za namen *nastavi časovnik* bi lahko zagotovili naslednje stavke:

* `nastavi časovnik za 1 sekundo`
* `nastavi časovnik za 1 minuto in 12 sekund`
* `nastavi časovnik za 3 minute`
* `nastavi časovnik za 9 minut in 30 sekund`

Nato LUIS-u poveste, kateri deli teh stavkov ustrezajo entitetam:

![Stavek "nastavi časovnik za 1 minuto in 12 sekund" razdeljen na entitete](../../../../../translated_images/sl/sentence-as-intent-entities.301401696f992259.webp)

Stavek `nastavi časovnik za 1 minuto in 12 sekund` ima namen `nastavi časovnik`. Ima tudi 2 entiteti z 2 vrednostma:

|            | čas | enota   |
| ---------- | ---: | ------- |
| 1 minuta   | 1    | minuta  |
| 12 sekund  | 12   | sekunda |

Za treniranje dobrega modela potrebujete različne primere stavkov, ki pokrivajo številne različne načine, kako bi nekdo lahko prosil za isto stvar.

> 💁 Kot pri vsakem AI modelu, več podatkov in bolj natančni kot so podatki, ki jih uporabite za treniranje, boljši bo model.

✅ Razmislite o različnih načinih, kako bi lahko prosili za isto stvar in pričakovali, da bi vas človek razumel.

### Naloga - dodajanje entitet modelom za razumevanje jezika

Za časovnik morate dodati 2 entiteti - eno za enoto časa (minute ali sekunde) in eno za število minut ali sekund.

Navodila za uporabo portala LUIS najdete v [Quickstart: Build your app in LUIS portal documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Na portalu LUIS izberite zavihek *Entities* in dodajte vnaprej pripravljeno entiteto *number* s klikom na gumb **Add prebuilt entity**, nato izberite *number* s seznama.

1. Ustvarite novo entiteto za časovno enoto z gumbom **Create**. Poimenujte entiteto `time unit` in nastavite tip na *List*. Dodajte vrednosti za `minute` in `second` na seznam *Normalized values*, dodajte edninske in množinske oblike na seznam *synonyms*. Po vsakem dodajanju sopomenke pritisnite `return`, da jo dodate na seznam.

    | Normalizirana vrednost | Sopomenke        |
    | ---------------------- | ---------------- |
    | minuta                 | minuta, minute   |
    | sekunda                | sekunda, sekunde |

### Naloga - dodajanje namenov modelom za razumevanje jezika

1. Na zavihku *Intents* izberite gumb **Create**, da ustvarite nov namen. Poimenujte ta namen `set timer`.

1. V primerih vnesite različne načine za nastavitev časovnika z minutami, sekundami ter kombinacijo minut in sekund. Primeri bi lahko bili:

    * `nastavi časovnik za 1 sekundo`
    * `nastavi časovnik za 4 minute`
    * `nastavi časovnik za štiri minute in šest sekund`
    * `nastavi časovnik za 9 minut in 30 sekund`
    * `nastavi časovnik za 1 minuto in 12 sekund`
    * `nastavi časovnik za 3 minute`
    * `nastavi časovnik za 3 minute in 1 sekundo`
    * `nastavi časovnik za tri minute in eno sekundo`
    * `nastavi časovnik za 1 minuto in 1 sekundo`
    * `nastavi časovnik za 30 sekund`
    * `nastavi časovnik za 1 sekundo`

    Mešajte številke kot besede in številčne vrednosti, da se model nauči obravnavati oboje.

1. Ko vnesete vsak primer, bo LUIS začel zaznavati entitete in podčrtal ter označil vse, ki jih najde.

    ![Primeri z označenimi številkami in časovnimi enotami](../../../../../translated_images/sl/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.png)

### Naloga - treniranje in testiranje modela

1. Ko so entitete in nameni konfigurirani, lahko model trenirate z gumbom **Train** v zgornjem meniju. Izberite ta gumb, model pa se bo treniral v nekaj sekundah. Gumb bo med treniranjem onemogočen in ponovno omogočen, ko bo končano.

1. Izberite gumb **Test** v zgornjem meniju, da preizkusite model za razumevanje jezika. Vnesite besedilo, na primer `nastavi časovnik za 5 minut in 4 sekunde`, in pritisnite return. Stavek se bo pojavil v polju pod besedilnim poljem, kamor ste ga vnesli, spodaj pa bo prikazan *top intent* ali namen, ki je bil zaznan z najvišjo verjetnostjo. To bi moralo biti `set timer`. Ime namena bo spremljala verjetnost, da je zaznani namen pravilen.

1. Izberite možnost **Inspect**, da si ogledate razčlenitev rezultatov. Videli boste namen z najvišjo oceno in njegovo odstotno verjetnost, skupaj s seznami zaznanih entitet.

1. Ko končate s testiranjem, zaprite okno *Test*.

### Naloga - objava modela

Da bi ta model uporabili v kodi, ga morate objaviti. Pri objavi iz LUIS lahko objavite v okolje za testiranje (staging) ali v produkcijsko okolje za polno izdajo. V tej lekciji je okolje za testiranje dovolj.

1. Na portalu LUIS izberite gumb **Publish** v zgornjem meniju.

1. Prepričajte se, da je izbrana možnost *Staging slot*, nato izberite **Done**. Obvestilo vas bo obvestilo, ko bo aplikacija objavljena.

1. To lahko preizkusite z uporabo ukaza curl. Za sestavo ukaza curl potrebujete tri vrednosti - končno točko (endpoint), ID aplikacije (App ID) in API ključ. Te vrednosti lahko pridobite na zavihku **MANAGE**, ki ga izberete v zgornjem meniju.

    1. Iz razdelka *Settings* kopirajte App ID.
1. V razdelku *Azure Resources* izberite *Authoring Resource* in kopirajte *Primary Key* ter *Endpoint URL*.

1. Zaženite naslednji ukaz curl v ukazni vrstici ali terminalu:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Zamenjajte `<endpoint url>` z Endpoint URL iz razdelka *Azure Resources*.

    Zamenjajte `<app id>` z App ID iz razdelka *Settings*.

    Zamenjajte `<primary key>` z Primary Key iz razdelka *Azure Resources*.

    Zamenjajte `<sentence>` z besedilom, ki ga želite testirati.

1. Rezultat tega klica bo JSON dokument, ki podrobno opisuje poizvedbo, glavni namen (top intent) in seznam entitet, razčlenjenih po tipih.

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    Zgornji JSON je rezultat poizvedbe z besedilom `set a timer for 45 minutes and 12 seconds`:

    * `set timer` je bil glavni namen z verjetnostjo 97 %.
    * Zaznani sta bili dve entiteti *number*, `45` in `12`.
    * Zaznani sta bili dve entiteti *time-unit*, `minute` in `second`.

## Uporaba modela za razumevanje jezika

Ko je model LUIS objavljen, ga lahko kličete iz kode. V prejšnjih lekcijah ste uporabljali IoT Hub za komunikacijo s storitvami v oblaku, pošiljanje telemetrije in poslušanje ukazov. To je zelo asinhrono - ko pošljete telemetrijo, vaša koda ne čaka na odgovor, in če storitev v oblaku ne deluje, tega ne boste vedeli.

Za pametni časovnik želimo takojšen odgovor, da lahko uporabniku povemo, da je časovnik nastavljen, ali ga opozorimo, da storitve v oblaku niso na voljo. Da to dosežemo, bo naša IoT naprava neposredno klicala spletni endpoint, namesto da bi se zanašala na IoT Hub.

Namesto da bi LUIS klicali neposredno iz IoT naprave, lahko uporabite strežniško kodo z drugačnim sprožilcem - HTTP sprožilec. To omogoča, da vaša funkcijska aplikacija posluša REST zahteve in nanje odgovarja. Ta funkcija bo REST endpoint, ki ga lahko pokliče vaša naprava.

> 💁 Čeprav lahko LUIS neposredno kličete iz svoje IoT naprave, je bolje uporabiti nekaj, kot je strežniška koda. Na ta način, ko želite spremeniti LUIS aplikacijo, ki jo kličete, na primer ko trenirate boljši model ali model v drugem jeziku, morate posodobiti samo kodo v oblaku, ne pa ponovno namestiti kode na potencialno tisoče ali milijone IoT naprav.

### Naloga - ustvarite aplikacijo za strežniške funkcije

1. Ustvarite Azure Functions aplikacijo z imenom `smart-timer-trigger` in jo odprite v VS Code.

1. Dodajte HTTP sprožilec tej aplikaciji z imenom `speech-trigger` z naslednjim ukazom znotraj terminala v VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    To bo ustvarilo HTTP sprožilec z imenom `text-to-timer`.

1. Testirajte HTTP sprožilec tako, da zaženete funkcijsko aplikacijo. Ko se zažene, boste v izhodu videli seznam endpointov:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Testirajte to tako, da naložite URL [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) v brskalniku.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Naloga - uporabite model za razumevanje jezika

1. SDK za LUIS je na voljo prek Pip paketa. Dodajte naslednjo vrstico v datoteko `requirements.txt`, da dodate odvisnost od tega paketa:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Prepričajte se, da je terminal v VS Code aktiviral virtualno okolje, in zaženite naslednji ukaz za namestitev Pip paketov:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Če naletite na napake, boste morda morali nadgraditi pip z naslednjim ukazom:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Dodajte nove vnose v datoteko `local.settings.json` za vaš LUIS API Key, Endpoint URL in App ID iz zavihka **MANAGE** v LUIS portalu:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Zamenjajte `<endpoint url>` z Endpoint URL iz razdelka *Azure Resources* zavihka **MANAGE**. To bo `https://<location>.api.cognitive.microsoft.com/`.

    Zamenjajte `<app id>` z App ID iz razdelka *Settings* zavihka **MANAGE**.

    Zamenjajte `<primary key>` z Primary Key iz razdelka *Azure Resources* zavihka **MANAGE**.

1. Dodajte naslednje uvoze v datoteko `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    To uvozi nekaj sistemskih knjižnic ter knjižnice za interakcijo z LUIS.

1. Izbrišite vsebino metode `main` in dodajte naslednjo kodo:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Ta koda naloži vrednosti, ki ste jih dodali v datoteko `local.settings.json` za vašo LUIS aplikacijo, ustvari objekt z poverilnicami z vašim API ključem, nato pa ustvari LUIS odjemalca za interakcijo z vašo LUIS aplikacijo.

1. Ta HTTP sprožilec bo poklican z besedilom za razumevanje, poslanim kot JSON, z besedilom v lastnosti `text`. Naslednja koda izvleče vrednost iz telesa HTTP zahteve in jo zapiše v konzolo. Dodajte to kodo v funkcijo `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Napovedi se zahtevajo od LUIS z pošiljanjem zahteve za napoved - JSON dokumenta, ki vsebuje besedilo za napoved. Ustvarite to z naslednjo kodo:

    ```python
    prediction_request = { 'query' : text }
    ```

1. To zahtevo lahko nato pošljete LUIS, pri čemer uporabite staging slot, na katerega je bila vaša aplikacija objavljena:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Odziv napovedi vsebuje glavni namen - namen z najvišjo oceno napovedi, skupaj z entitetami. Če je glavni namen `set timer`, lahko entitete preberete, da dobite čas, potreben za časovnik:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    Entitete `number` bodo polje števil. Na primer, če rečete *"Set a four minute 17 second timer."*, bo polje `number` vsebovalo 2 števili - 4 in 17.

    Entitete `time unit` bodo polje polj nizov, pri čemer je vsaka časovna enota polje nizov znotraj polja. Na primer, če rečete *"Set a four minute 17 second timer."*, bo polje `time unit` vsebovalo 2 polji z enim vrednostjo vsako - `['minute']` in `['second']`.

    JSON različica teh entitet za *"Set a four minute 17 second timer."* je:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Ta koda prav tako definira števec za skupni čas za časovnik v sekundah. Ta bo napolnjen z vrednostmi iz entitet.

1. Entitete niso povezane, vendar lahko naredimo nekaj predpostavk o njih. Bodo v vrstnem redu, kot so bile izgovorjene, zato lahko položaj v polju uporabimo za določitev, katera številka ustreza kateri časovni enoti. Na primer:

    * *"Set a 30 second timer"* - to bo imelo eno številko, `30`, in eno časovno enoto, `second`, zato bo ena številka ustrezala eni časovni enoti.
    * *"Set a 2 minute and 30 second timer"* - to bo imelo dve številki, `2` in `30`, ter dve časovni enoti, `minute` in `second`, zato bo prva številka za prvo časovno enoto (2 minuti), druga številka pa za drugo časovno enoto (30 sekund).

    Naslednja koda pridobi število elementov v entitetah `number` in uporabi to za izvlečenje prvega elementa iz vsakega polja, nato drugega in tako naprej. Dodajte to znotraj bloka `if`.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Za *"Set a four minute 17 second timer."* bo to zanko izvedlo dvakrat, kar bo dalo naslednje vrednosti:

    | št. zanke | `number` | `time_unit` |
    | ---------: | -------: | ----------- |
    | 0          | 4        | minute      |
    | 1          | 17       | second      |

1. Znotraj te zanke uporabite številko in časovno enoto za izračun skupnega časa za časovnik, pri čemer dodate 60 sekund za vsako minuto in število sekund za vsako sekundo.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Zunaj te zanke skozi entitete zapišite skupni čas za časovnik:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Število sekund je treba vrniti iz funkcije kot HTTP odgovor. Na koncu bloka `if` dodajte naslednje:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Ta koda ustvari vsebino, ki vsebuje skupno število sekund za časovnik, jo pretvori v JSON niz in jo vrne kot HTTP rezultat s statusno kodo 200, kar pomeni, da je klic uspešen.

1. Na koncu, zunaj bloka `if`, obravnavajte primer, ko namen ni bil prepoznan, tako da vrnete kodo napake:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 je statusna koda za *ni najdeno*.

1. Zaženite funkcijsko aplikacijo in jo preizkusite z uporabo curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Zamenjajte `<text>` z besedilom vaše zahteve, na primer `set a 2 minutes 27 second timer`.

    Videli boste naslednji izhod iz funkcijske aplikacije:

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    Klic curl bo vrnil naslednje:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Število sekund za časovnik je v vrednosti `"seconds"`.

> 💁 To kodo lahko najdete v mapi [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Naloga - omogočite dostop do vaše funkcije za vašo IoT napravo

1. Da bo vaša IoT naprava lahko klicala vaš REST endpoint, bo morala poznati URL. Ko ste ga prej dostopali, ste uporabili `localhost`, kar je bližnjica za dostop do REST endpointov na vašem lokalnem računalniku. Da omogočite dostop IoT napravi, morate aplikacijo objaviti v oblaku ali pridobiti vaš IP naslov za lokalni dostop.

    > ⚠️ Če uporabljate Wio Terminal, je lažje zagnati funkcijsko aplikacijo lokalno, saj bo odvisnost od knjižnic pomenila, da aplikacije ne morete namestiti na enak način, kot ste to storili prej. Zaženite funkcijsko aplikacijo lokalno in dostopajte do nje prek IP naslova vašega računalnika. Če jo želite objaviti v oblaku, bodo informacije o tem na voljo v kasnejši lekciji.

    * Objavite funkcijsko aplikacijo - sledite navodilom iz prejšnjih lekcij za objavo funkcijske aplikacije v oblaku. Ko je objavljena, bo URL `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, kjer `<APP_NAME>` predstavlja ime vaše funkcijske aplikacije. Poskrbite, da objavite tudi lokalne nastavitve.

      Pri delu z HTTP sprožilci so ti privzeto zaščiteni s ključem funkcijske aplikacije. Da pridobite ta ključ, zaženite naslednji ukaz:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Kopirajte vrednost vnosa `default` iz razdelka `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Ta ključ bo treba dodati kot parameter poizvedbe v URL, tako da bo končni URL `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, kjer `<APP_NAME>` predstavlja ime vaše funkcijske aplikacije, `<FUNCTION_KEY>` pa vaš privzeti funkcijski ključ.

      > 💁 Nastavitve avtorizacije HTTP sprožilca lahko spremenite z nastavitvijo `authlevel` v datoteki `function.json`. Več o tem lahko preberete v [razdelku o konfiguraciji dokumentacije Azure Functions HTTP trigger na Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Zaženite funkcijsko aplikacijo lokalno in dostopajte prek IP naslova - pridobite IP naslov vašega računalnika v lokalnem omrežju in ga uporabite za sestavo URL-ja.

      Poiščite vaš IP naslov:

      * Na Windows 10 sledite [navodilom za iskanje IP naslova](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn)
      * Na macOS sledite [navodilom za iskanje IP naslova na Macu](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac)
      * Na Linux sledite razdelku o iskanju zasebnega IP naslova v [navodilih za iskanje IP naslova v Linuxu](https://opensource.com/article/18/5/how-find-ip-address-linux)

      Ko pridobite vaš IP naslov, boste lahko dostopali do funkcije na `http://`.
<IP_NASLOV>
:7071/api/text-to-timer`, kjer bo `<IP_ADDRESS>` vaš IP naslov, na primer `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Upoštevajte, da uporablja vrata 7071, zato boste morali za IP naslovom dodati `:7071`.

      > 💁 To bo delovalo le, če je vaša IoT naprava v istem omrežju kot vaš računalnik.

1. Preizkusite končno točko tako, da jo dostopate z uporabo ukaza curl.

---

## 🚀 Izziv

Obstaja veliko načinov za zahtevo iste stvari, na primer nastavitev časovnika. Razmislite o različnih načinih, kako to storiti, in jih uporabite kot primere v svoji LUIS aplikaciji. Preizkusite jih, da vidite, kako dobro se vaš model spopada z različnimi načini zahteve za časovnik.

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Pregled in samostojno učenje

* Preberite več o LUIS in njegovih zmožnostih na [strani z dokumentacijo o razumevanju jezika (LUIS) na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Preberite več o razumevanju jezika na [strani o razumevanju naravnega jezika na Wikipediji](https://wikipedia.org/wiki/Natural-language_understanding)
* Preberite več o sprožilcih HTTP na [strani z dokumentacijo o sprožilcih HTTP za Azure Functions na Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Naloga

[Prekliči časovnik](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.