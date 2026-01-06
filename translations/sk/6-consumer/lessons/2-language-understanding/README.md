<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-28T08:50:41+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "sk"
}
-->
# Pochopiť jazyk

![Prehľad tejto lekcie vo forme sketchnote](../../../../../translated_images/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.sk.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre väčšiu verziu.

## Kvíz pred prednáškou

[Kvíz pred prednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Úvod

V predchádzajúcej lekcii ste previedli reč na text. Aby sa to dalo použiť na programovanie inteligentného časovača, váš kód bude musieť pochopiť, čo bolo povedané. Mohli by ste predpokladať, že používateľ povie pevne stanovenú frázu, ako napríklad „Nastav 3-minútový časovač“, a analyzovať tento výraz, aby ste zistili, ako dlho má časovač trvať, ale to nie je veľmi užívateľsky prívetivé. Ak by používateľ povedal „Nastav časovač na 3 minúty“, vy alebo ja by sme pochopili, čo tým myslí, ale váš kód by to nepochopil, pretože by očakával pevne stanovenú frázu.

Tu prichádza na rad porozumenie jazyka, ktoré využíva AI modely na interpretáciu textu a vrátenie potrebných detailov, napríklad schopnosť pochopiť „Nastav 3-minútový časovač“ aj „Nastav časovač na 3 minúty“ a rozpoznať, že je potrebný časovač na 3 minúty.

V tejto lekcii sa naučíte o modeloch na porozumenie jazyka, ako ich vytvoriť, trénovať a používať vo svojom kóde.

V tejto lekcii sa budeme venovať:

* [Porozumenie jazyka](../../../../../6-consumer/lessons/2-language-understanding)
* [Vytvorenie modelu na porozumenie jazyka](../../../../../6-consumer/lessons/2-language-understanding)
* [Zámery a entity](../../../../../6-consumer/lessons/2-language-understanding)
* [Použitie modelu na porozumenie jazyka](../../../../../6-consumer/lessons/2-language-understanding)

## Porozumenie jazyka

Ľudia používajú jazyk na komunikáciu už stovky tisíc rokov. Komunikujeme slovami, zvukmi alebo činmi a rozumieme tomu, čo je povedané – nielen významu slov, zvukov alebo činov, ale aj ich kontextu. Rozumieme úprimnosti a sarkazmu, čo umožňuje, aby rovnaké slová znamenali rôzne veci v závislosti od tónu nášho hlasu.

✅ Zamyslite sa nad niektorými rozhovormi, ktoré ste nedávno viedli. Koľko z týchto rozhovorov by bolo pre počítač ťažké pochopiť, pretože by potreboval kontext?

Porozumenie jazyka, nazývané aj porozumenie prirodzeného jazyka, je súčasťou oblasti umelej inteligencie nazývanej spracovanie prirodzeného jazyka (NLP) a zaoberá sa čítaním a porozumením, pričom sa snaží pochopiť detaily slov alebo viet. Ak používate hlasového asistenta, ako je Alexa alebo Siri, už ste použili služby na porozumenie jazyka. Tieto služby na pozadí premieňajú „Alexa, prehraj najnovší album od Taylor Swift“ na moju dcéru tancujúcu v obývačke na svoje obľúbené piesne.

> 💁 Počítače, napriek všetkým svojim pokrokom, majú ešte dlhú cestu k tomu, aby skutočne pochopili text. Keď hovoríme o porozumení jazyka počítačmi, nemáme na mysli nič, čo by sa blížilo ľudskej komunikácii. Hovoríme o tom, že počítač vezme niekoľko slov a extrahuje kľúčové detaily.

Ako ľudia rozumieme jazyku bez toho, aby sme o tom museli premýšľať. Ak by som požiadal iného človeka, aby „prehral najnovší album od Taylor Swift“, inštinktívne by vedel, čo tým myslím. Pre počítač je to však ťažšie. Musel by vziať slová, ktoré boli prevedené z reči na text, a zistiť nasledujúce informácie:

* Treba prehrať hudbu
* Hudba je od umelca Taylor Swift
* Ide o konkrétny album, ktorý obsahuje viacero skladieb v poradí
* Taylor Swift má mnoho albumov, takže ich treba zoradiť chronologicky a vybrať ten najnovší

✅ Zamyslite sa nad niektorými vetami, ktoré ste povedali pri žiadostiach, napríklad pri objednávaní kávy alebo žiadaní člena rodiny, aby vám niečo podal. Skúste ich rozložiť na informácie, ktoré by počítač potreboval extrahovať, aby vetu pochopil.

Modely na porozumenie jazyka sú AI modely, ktoré sú trénované na extrahovanie určitých detailov z jazyka a následne sú trénované na konkrétne úlohy pomocou transferového učenia, podobne ako ste trénovali model Custom Vision pomocou malej sady obrázkov. Môžete vziať model a trénovať ho pomocou textu, ktorému chcete, aby rozumel.

## Vytvorenie modelu na porozumenie jazyka

![Logo LUIS](../../../../../translated_images/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.sk.png)

Modely na porozumenie jazyka môžete vytvárať pomocou LUIS, služby na porozumenie jazyka od Microsoftu, ktorá je súčasťou Cognitive Services.

### Úloha – vytvorenie autorizačného zdroja

Na používanie LUIS potrebujete vytvoriť autorizačný zdroj.

1. Použite nasledujúci príkaz na vytvorenie autorizačného zdroja v skupine zdrojov `smart-timer`:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Nahraďte `<location>` lokalitou, ktorú ste použili pri vytváraní skupiny zdrojov.

    > ⚠️ LUIS nie je dostupný vo všetkých regiónoch, takže ak dostanete nasledujúcu chybu:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > vyberte iný región.

    Týmto sa vytvorí bezplatný autorizačný zdroj LUIS.

### Úloha – vytvorenie aplikácie na porozumenie jazyka

1. Otvorte portál LUIS na [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) vo svojom prehliadači a prihláste sa pomocou rovnakého účtu, ktorý ste používali pre Azure.

1. Postupujte podľa pokynov v dialógovom okne na výber svojho Azure predplatného a potom vyberte zdroj `smart-timer-luis-authoring`, ktorý ste práve vytvorili.

1. Z *Zoznamu konverzačných aplikácií* vyberte tlačidlo **Nová aplikácia** na vytvorenie novej aplikácie. Novú aplikáciu pomenujte `smart-timer` a nastavte *Kultúru* na svoj jazyk.

    > 💁 Existuje pole pre predikčný zdroj. Môžete vytvoriť druhý zdroj len na predikciu, ale bezplatný autorizačný zdroj umožňuje 1 000 predikcií mesačne, čo by malo byť dostatočné na vývoj, takže toto pole môžete nechať prázdne.

1. Prečítajte si sprievodcu, ktorý sa zobrazí po vytvorení aplikácie, aby ste pochopili kroky potrebné na trénovanie modelu na porozumenie jazyka. Po prečítaní sprievodcu ho zatvorte.

## Zámery a entity

Porozumenie jazyka je založené na *zámeroch* a *entitách*. Zámery sú to, čo slová vyjadrujú, napríklad prehrávanie hudby, nastavenie časovača alebo objednávanie jedla. Entity sú to, na čo sa zámer vzťahuje, napríklad album, dĺžka časovača alebo typ jedla. Každá veta, ktorú model interpretuje, by mala mať aspoň jeden zámer a voliteľne jednu alebo viac entít.

Niekoľko príkladov:

| Veta                                              | Zámer            | Entity                                    |
| ------------------------------------------------- | ---------------- | ----------------------------------------- |
| „Prehraj najnovší album od Taylor Swift“          | *prehrať hudbu*  | *najnovší album od Taylor Swift*          |
| „Nastav 3-minútový časovač“                       | *nastaviť časovač* | *3 minúty*                                |
| „Zruš môj časovač“                                | *zrušiť časovač* | Žiadne                                    |
| „Objednaj 3 veľké pizze s ananásom a Caesar šalát“ | *objednať jedlo* | *3 veľké pizze s ananásom*, *Caesar šalát* |

✅ Pri vetách, nad ktorými ste sa zamýšľali skôr, aký by bol zámer a aké entity by sa v nich nachádzali?

Na trénovanie LUIS najprv nastavíte entity. Tie môžu byť pevne stanoveným zoznamom termínov alebo sa môžu učiť z textu. Napríklad môžete poskytnúť pevný zoznam jedál dostupných vo vašom menu s variáciami (alebo synonymami) každého slova, ako napríklad *baklažán* a *aubergine* ako variácie *aubergine*. LUIS má tiež preddefinované entity, ktoré je možné použiť, ako napríklad čísla a lokality.

Pre nastavenie časovača by ste mohli mať jednu entitu využívajúcu preddefinované čísla pre čas a druhú pre jednotky, ako sú minúty a sekundy. Každá jednotka by mala viacero variácií na pokrytie jednotného a množného čísla – napríklad minúta a minúty.

Keď sú entity definované, vytvoríte zámery. Tie sa model učí na základe príkladových viet, ktoré poskytnete (známe ako výrazy). Napríklad pre zámer *nastaviť časovač* by ste mohli poskytnúť nasledujúce vety:

* `nastav 1-sekundový časovač`
* `nastav časovač na 1 minútu a 12 sekúnd`
* `nastav časovač na 3 minúty`
* `nastav 9-minútový 30-sekundový časovač`

Potom LUISu poviete, ktoré časti týchto viet zodpovedajú entitám:

![Veta „nastav časovač na 1 minútu a 12 sekúnd“ rozdelená na entity](../../../../../translated_images/sentence-as-intent-entities.301401696f992259.sk.png)

Veta `nastav časovač na 1 minútu a 12 sekúnd` má zámer `nastaviť časovač`. Má tiež 2 entity s 2 hodnotami každá:

|            | čas | jednotka   |
| ---------- | ---: | ---------- |
| 1 minúta   | 1    | minúta     |
| 12 sekúnd  | 12   | sekunda    |

Na trénovanie dobrého modelu potrebujete rôzne príkladové vety, ktoré pokryjú mnoho rôznych spôsobov, akými by niekto mohol požiadať o to isté.

> 💁 Ako pri každom AI modeli, čím viac údajov a čím presnejšie údaje použijete na trénovanie, tým lepší bude model.

✅ Zamyslite sa nad rôznymi spôsobmi, akými by ste mohli požiadať o to isté a očakávať, že človek to pochopí.

### Úloha – pridanie entít do modelov na porozumenie jazyka

Pre časovač potrebujete pridať 2 entity – jednu pre jednotku času (minúty alebo sekundy) a jednu pre počet minút alebo sekúnd.

Pokyny na používanie portálu LUIS nájdete v [dokumentácii Quickstart: Build your app in LUIS portal na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Na portáli LUIS vyberte kartu *Entities* a pridajte preddefinovanú entitu *number* výberom tlačidla **Add prebuilt entity** a následným výberom *number* zo zoznamu.

1. Vytvorte novú entitu pre jednotku času pomocou tlačidla **Create**. Pomenujte entitu `time unit` a nastavte typ na *List*. Pridajte hodnoty pre `minúta` a `sekunda` do zoznamu *Normalized values*, pričom do zoznamu *synonyms* pridajte jednotné a množné formy. Po pridaní každého synonyma stlačte `return`, aby ste ho pridali do zoznamu.

    | Normalizovaná hodnota | Synonymá         |
    | --------------------- | ---------------- |
    | minúta               | minúta, minúty   |
    | sekunda              | sekunda, sekundy |

### Úloha – pridanie zámerov do modelov na porozumenie jazyka

1. Na karte *Intents* vyberte tlačidlo **Create** na vytvorenie nového zámeru. Pomenujte tento zámer `set timer`.

1. Do príkladov zadajte rôzne spôsoby nastavenia časovača pomocou minút, sekúnd a kombinácie minút a sekúnd. Príklady môžu byť:

    * `nastav 1-sekundový časovač`
    * `nastav 4-minútový časovač`
    * `nastav štvorminútový šesťsekundový časovač`
    * `nastav 9-minútový 30-sekundový časovač`
    * `nastav časovač na 1 minútu a 12 sekúnd`
    * `nastav časovač na 3 minúty`
    * `nastav časovač na 3 minúty a 1 sekundu`
    * `nastav časovač na tri minúty a jednu sekundu`
    * `nastav časovač na 1 minútu a 1 sekundu`
    * `nastav časovač na 30 sekúnd`
    * `nastav časovač na 1 sekundu`

    Kombinujte čísla ako slová a číslice, aby sa model naučil pracovať s oboma.

1. Pri zadávaní každého príkladu začne LUIS detekovať entity a podčiarkne a označí tie, ktoré nájde.

    ![Príklady s podčiarknutými číslami a jednotkami času detekovanými LUIS](../../../../../translated_images/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.sk.png)

### Úloha – trénovanie a testovanie modelu

1. Keď sú entity a zámery nakonfigurované, môžete model trénovať pomocou tlačidla **Train** v hornom menu. Vyberte toto tlačidlo a model by sa mal vytrénovať za pár sekúnd. Tlačidlo bude počas trénovania sivé a po dokončení sa opäť sprístupní.

1. Vyberte tlačidlo **Test** z horného menu na otestovanie modelu na porozumenie jazyka. Zadajte text, ako napríklad `nastav časovač na 5 minút a 4 sekundy`, a stlačte return. Veta sa zobrazí v poli pod textovým poľom, do ktorého ste ju zadali, a pod tým sa zobrazí *top intent*, teda zámer, ktorý bol detekovaný s najvyššou pravdepodobnosťou. Tento by mal byť `set timer`. Názov zámeru bude nasledovaný pravdepodobnosťou, že detekovaný zámer je správny.

1. Vyberte možnosť **Inspect**, aby ste videli rozpis výsledkov. Uvidíte najvyššie skórovaný zámer s jeho percentuálnou pravdepodobnosťou spolu so zoznamami detekovaných entít.

1. Po dokončení testovania zatvorte panel *Test*.

### Úloha – publikovanie modelu

Aby ste mohli tento model používať z kódu, musíte ho publikovať. Pri publikovaní z LUIS môžete publikovať buď do testovacieho prostredia (staging), alebo do produkčného prostredia (production). Pre túto lekciu je testovacie prostredie postačujúce.

1. Na portáli LUIS vyberte tlačidlo **Publish** z horného menu.

1. Uistite sa, že je vybraná možnosť *Staging slot*, a potom vyberte **Done**. Po publikovaní aplikácie sa zobrazí notifikácia.

1. Toto môžete otestovať pomocou curl. Na vytvorenie curl príkazu potrebujete tri hodnoty – endpoint, ID aplikácie (App ID) a API kľúč. Tieto hodnoty nájdete na karte **MANAGE**, ktorú môžete vybrať z horného menu.

    1. Z časti *Settings* skopírujte App ID.
1. V sekcii *Azure Resources* vyberte *Authoring Resource* a skopírujte *Primary Key* a *Endpoint URL*.

1. Spustite nasledujúci príkaz curl vo vašom príkazovom riadku alebo termináli:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Nahraďte `<endpoint url>` hodnotou Endpoint URL zo sekcie *Azure Resources*.

    Nahraďte `<app id>` hodnotou App ID zo sekcie *Settings*.

    Nahraďte `<primary key>` hodnotou Primary Key zo sekcie *Azure Resources*.

    Nahraďte `<sentence>` vetou, ktorú chcete otestovať.

1. Výstup tohto volania bude JSON dokument, ktorý obsahuje podrobnosti o dotaze, najvyšší zámer a zoznam entít rozdelených podľa typu.

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

    Vyššie uvedený JSON pochádza z dotazu s vetou `set a timer for 45 minutes and 12 seconds`:

    * `set timer` bol najvyšší zámer s pravdepodobnosťou 97 %.
    * Boli detekované dve *number* entity: `45` a `12`.
    * Boli detekované dve *time-unit* entity: `minute` a `second`.

## Použitie modelu na porozumenie jazyka

Po publikovaní je možné model LUIS volať z kódu. V predchádzajúcich lekciách ste používali IoT Hub na komunikáciu s cloudovými službami, odosielanie telemetrie a prijímanie príkazov. Toto je veľmi asynchrónne - keď sa telemetria odošle, váš kód nečaká na odpoveď, a ak je cloudová služba nedostupná, nebudete o tom vedieť.

Pre inteligentný časovač chceme okamžitú odpoveď, aby sme mohli používateľovi oznámiť, že časovač je nastavený, alebo ho upozorniť, že cloudové služby nie sú dostupné. Na tento účel bude naše IoT zariadenie priamo volať webový endpoint namiesto spoliehania sa na IoT Hub.

Namiesto volania LUIS z IoT zariadenia môžete použiť serverless kód s iným typom triggeru - HTTP trigger. To umožňuje vašej funkcii počúvať REST požiadavky a odpovedať na ne. Táto funkcia bude REST endpoint, ktorý vaše zariadenie môže volať.

> 💁 Aj keď môžete volať LUIS priamo z vášho IoT zariadenia, je lepšie použiť niečo ako serverless kód. Týmto spôsobom, keď budete chcieť zmeniť LUIS aplikáciu, ktorú voláte, napríklad keď vytrénujete lepší model alebo model v inom jazyku, stačí aktualizovať váš cloudový kód, a nie znovu nasadzovať kód na potenciálne tisíce alebo milióny IoT zariadení.

### Úloha - vytvorte aplikáciu serverless funkcií

1. Vytvorte Azure Functions aplikáciu nazvanú `smart-timer-trigger` a otvorte ju vo VS Code.

1. Pridajte HTTP trigger do tejto aplikácie nazvaný `speech-trigger` pomocou nasledujúceho príkazu vo VS Code termináli:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Týmto sa vytvorí HTTP trigger nazvaný `text-to-timer`.

1. Otestujte HTTP trigger spustením aplikácie funkcií. Po spustení uvidíte endpoint uvedený vo výstupe:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Otestujte to načítaním URL [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) vo vašom prehliadači.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Úloha - použite model na porozumenie jazyka

1. SDK pre LUIS je dostupné cez Pip balíček. Pridajte nasledujúci riadok do súboru `requirements.txt`, aby ste pridali závislosť na tomto balíčku:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Uistite sa, že terminál vo VS Code má aktivované virtuálne prostredie, a spustite nasledujúci príkaz na inštaláciu Pip balíčkov:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Ak narazíte na chyby, možno budete musieť aktualizovať pip pomocou nasledujúceho príkazu:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Pridajte nové položky do súboru `local.settings.json` pre váš LUIS API Key, Endpoint URL a App ID zo sekcie **MANAGE** v LUIS portáli:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Nahraďte `<endpoint url>` hodnotou Endpoint URL zo sekcie *Azure Resources* v záložke **MANAGE**. Toto bude `https://<location>.api.cognitive.microsoft.com/`.

    Nahraďte `<app id>` hodnotou App ID zo sekcie *Settings* v záložke **MANAGE**.

    Nahraďte `<primary key>` hodnotou Primary Key zo sekcie *Azure Resources* v záložke **MANAGE**.

1. Pridajte nasledujúce importy do súboru `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Týmto sa importujú niektoré systémové knižnice, ako aj knižnice na interakciu s LUIS.

1. Vymažte obsah metódy `main` a pridajte nasledujúci kód:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Tento kód načíta hodnoty, ktoré ste pridali do súboru `local.settings.json` pre vašu LUIS aplikáciu, vytvorí objekt credentials s vaším API kľúčom a potom vytvorí LUIS klienta na interakciu s vašou LUIS aplikáciou.

1. Tento HTTP trigger bude volaný s textom na porozumenie ako JSON, kde text bude v vlastnosti nazvanej `text`. Nasledujúci kód extrahuje hodnotu z tela HTTP požiadavky a zapisuje ju do konzoly. Pridajte tento kód do funkcie `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Predikcie sú požadované od LUIS zaslaním požiadavky na predikciu - JSON dokumentu obsahujúceho text na predikciu. Vytvorte ho pomocou nasledujúceho kódu:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Táto požiadavka môže byť potom zaslaná LUIS, pričom sa použije staging slot, do ktorého bola vaša aplikácia publikovaná:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Odpoveď na predikciu obsahuje najvyšší zámer - zámer s najvyšším skóre predikcie, spolu s entitami. Ak je najvyšší zámer `set timer`, potom je možné čítať entity na získanie času potrebného pre časovač:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    `number` entity budú pole čísel. Napríklad, ak poviete *"Set a four minute 17 second timer."*, potom pole `number` bude obsahovať 2 celé čísla - 4 a 17.

    `time unit` entity budú pole polí reťazcov, pričom každá časová jednotka bude pole reťazcov vo vnútri poľa. Napríklad, ak poviete *"Set a four minute 17 second timer."*, potom pole `time unit` bude obsahovať 2 polia s jednou hodnotou každé - `['minute']` a `['second']`.

    JSON verzia týchto entít pre *"Set a four minute 17 second timer."* je:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Tento kód tiež definuje počet pre celkový čas pre časovač v sekundách. Tento bude naplnený hodnotami z entít.

1. Entity nie sú prepojené, ale môžeme urobiť niektoré predpoklady o nich. Budú v poradí, v akom boli vyslovené, takže pozícia v poli môže byť použitá na určenie, ktoré číslo zodpovedá ktorej časovej jednotke. Napríklad:

    * *"Set a 30 second timer"* - toto bude mať jedno číslo, `30`, a jednu časovú jednotku, `second`, takže jediné číslo bude zodpovedať jedinej časovej jednotke.
    * *"Set a 2 minute and 30 second timer"* - toto bude mať dve čísla, `2` a `30`, a dve časové jednotky, `minute` a `second`, takže prvé číslo bude pre prvú časovú jednotku (2 minúty) a druhé číslo pre druhú časovú jednotku (30 sekúnd).

    Nasledujúci kód získa počet položiek v `number` entitách a použije ho na extrakciu prvej položky z každého poľa, potom druhej a tak ďalej. Pridajte toto do bloku `if`.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Pre *"Set a four minute 17 second timer."* toto bude prechádzať dvakrát, pričom dá nasledujúce hodnoty:

    | počet cyklov | `number` | `time_unit` |
    | ------------: | -------: | ----------- |
    | 0             | 4        | minute      |
    | 1             | 17       | second      |

1. Vo vnútri tohto cyklu použite číslo a časovú jednotku na výpočet celkového času pre časovač, pričom pridajte 60 sekúnd za každú minútu a počet sekúnd za akékoľvek sekundy.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Mimo tohto cyklu cez entity zapíšte celkový čas pre časovač:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Počet sekúnd je potrebné vrátiť z funkcie ako HTTP odpoveď. Na konci bloku `if` pridajte nasledujúce:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Tento kód vytvorí payload obsahujúci celkový počet sekúnd pre časovač, konvertuje ho na JSON reťazec a vráti ho ako HTTP výsledok so status kódom 200, čo znamená, že volanie bolo úspešné.

1. Nakoniec, mimo bloku `if`, spracujte situáciu, keď zámer nebol rozpoznaný, vrátením chybového kódu:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 je status kód pre *not found*.

1. Spustite aplikáciu funkcií a otestujte ju pomocou curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Nahraďte `<text>` textom vašej požiadavky, napríklad `set a 2 minutes 27 second timer`.

    Uvidíte nasledujúci výstup z aplikácie funkcií:

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

    Volanie curl vráti nasledujúce:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Počet sekúnd pre časovač je v hodnote `"seconds"`.

> 💁 Tento kód nájdete v priečinku [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Úloha - sprístupnite svoju funkciu pre vaše IoT zariadenie

1. Aby vaše IoT zariadenie mohlo volať váš REST endpoint, bude potrebovať poznať URL. Keď ste k nemu pristupovali skôr, použili ste `localhost`, čo je skratka na prístup k REST endpointom na vašom lokálnom počítači. Aby vaše IoT zariadenie mohlo získať prístup, musíte buď publikovať do cloudu, alebo získať vašu IP adresu na lokálny prístup.

    > ⚠️ Ak používate Wio Terminal, je jednoduchšie spustiť aplikáciu funkcií lokálne, pretože bude existovať závislosť na knižniciach, ktorá znamená, že nemôžete nasadiť aplikáciu funkcií rovnakým spôsobom ako predtým. Spustite aplikáciu funkcií lokálne a pristupujte k nej cez IP adresu vášho počítača. Ak chcete nasadiť do cloudu, informácie budú poskytnuté v neskoršej lekcii o tom, ako to urobiť.

    * Publikujte aplikáciu funkcií - postupujte podľa pokynov v predchádzajúcich lekciách na publikovanie vašej aplikácie funkcií do cloudu. Po publikovaní bude URL `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, kde `<APP_NAME>` bude názov vašej aplikácie funkcií. Uistite sa, že ste tiež publikovali vaše lokálne nastavenia.

      Pri práci s HTTP triggermi sú predvolene zabezpečené kľúčom aplikácie funkcií. Na získanie tohto kľúča spustite nasledujúci príkaz:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Skopírujte hodnotu položky `default` zo sekcie `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Tento kľúč bude potrebné pridať ako query parameter do URL, takže konečné URL bude `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, kde `<APP_NAME>` bude názov vašej aplikácie funkcií a `<FUNCTION_KEY>` bude váš predvolený kľúč funkcie.

      > 💁 Môžete zmeniť typ autorizácie HTTP triggeru pomocou nastavenia `authlevel` v súbore `function.json`. Viac o tom si môžete prečítať v [konfiguračnej sekcii dokumentácie Azure Functions HTTP trigger na Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Spustite aplikáciu funkcií lokálne a pristupujte k nej pomocou IP adresy - môžete získať IP adresu vášho počítača na lokálnej sieti a použiť ju na vytvorenie URL.

      Nájdite vašu IP adresu:

      * Na Windows 10, postupujte podľa [návodu na nájdenie IP adresy](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Na macOS, postupujte podľa [návodu na nájdenie IP adresy na Macu](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Na Linuxe, postupujte podľa sekcie o nájdení súkromnej IP adresy v [návode na nájdenie IP adresy v Linuxe](https://opensource.com/article/18/5/how-find-ip-address-linux).

      Keď získate vašu IP adresu, budete môcť pristupovať k funkcii na `http://`.

:7071/api/text-to-timer`, kde `<IP_ADDRESS>` bude vaša IP adresa, napríklad `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Upozornenie: Používa sa port 7071, takže po IP adrese budete musieť pridať `:7071`.

      > 💁 Toto bude fungovať iba v prípade, že vaše IoT zariadenie je na rovnakej sieti ako váš počítač.

1. Otestujte endpoint pomocou prístupu cez curl.

---

## 🚀 Výzva

Existuje mnoho spôsobov, ako požiadať o tú istú vec, napríklad nastavenie časovača. Premyslite si rôzne spôsoby, ako to urobiť, a použite ich ako príklady vo vašej LUIS aplikácii. Otestujte ich, aby ste zistili, ako dobre váš model zvláda rôzne spôsoby požiadania o časovač.

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Prehľad & Samoštúdium

* Prečítajte si viac o LUIS a jeho schopnostiach na [stránke dokumentácie Language Understanding (LUIS) na Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Prečítajte si viac o porozumení jazyka na [stránke o porozumení prirodzeného jazyka na Wikipédii](https://wikipedia.org/wiki/Natural-language_understanding)
* Prečítajte si viac o HTTP triggroch v [dokumentácii Azure Functions HTTP trigger na Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Zadanie

[Zrušiť časovač](assignment.md)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.