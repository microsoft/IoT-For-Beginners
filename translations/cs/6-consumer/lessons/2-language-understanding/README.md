# Porozumění jazyku

![Přehled lekce ve formě sketchnote](../../../../../translated_images/cs/lesson-22.6148ea28500d9e00.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

## Kvíz před přednáškou

[Kvíz před přednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Úvod

V minulé lekci jste převáděli řeč na text. Aby bylo možné tento výstup použít k naprogramování chytrého časovače, váš kód bude muset pochopit, co bylo řečeno. Můžete předpokládat, že uživatel vysloví pevnou frázi, například „Nastav časovač na 3 minuty“, a tuto frázi analyzovat, abyste zjistili, jak dlouho má časovač běžet. To však není příliš uživatelsky přívětivé. Pokud by uživatel řekl „Nastav časovač na 3 minuty“, vy nebo já bychom pochopili, co tím myslí, ale váš kód by to nepochopil, protože by očekával pevnou frázi.

Tady přichází na řadu porozumění jazyku, které využívá AI modely k interpretaci textu a vrácení potřebných detailů. Například dokáže pochopit jak „Nastav časovač na 3 minuty“, tak „Nastav časovač na 3 minuty“ a rozpoznat, že je potřeba nastavit časovač na 3 minuty.

V této lekci se naučíte o modelech pro porozumění jazyku, jak je vytvořit, trénovat a používat ve svém kódu.

V této lekci se zaměříme na:

* [Porozumění jazyku](../../../../../6-consumer/lessons/2-language-understanding)
* [Vytvoření modelu pro porozumění jazyku](../../../../../6-consumer/lessons/2-language-understanding)
* [Záměry a entity](../../../../../6-consumer/lessons/2-language-understanding)
* [Použití modelu pro porozumění jazyku](../../../../../6-consumer/lessons/2-language-understanding)

## Porozumění jazyku

Lidé používají jazyk ke komunikaci stovky tisíc let. Komunikujeme slovy, zvuky nebo činy a rozumíme tomu, co je řečeno – nejen významu slov, zvuků nebo činů, ale také jejich kontextu. Rozumíme upřímnosti a sarkasmu, což umožňuje, aby stejná slova znamenala různé věci v závislosti na tónu hlasu.

✅ Zamyslete se nad některými nedávnými konverzacemi, které jste vedli. Kolik z těchto rozhovorů by bylo pro počítač obtížné pochopit, protože by potřeboval kontext?

Porozumění jazyku, také nazývané porozumění přirozenému jazyku, je součástí oblasti umělé inteligence zvané zpracování přirozeného jazyka (NLP) a zabývá se čtením a porozuměním textu, snahou pochopit detaily slov nebo vět. Pokud používáte hlasového asistenta, jako je Alexa nebo Siri, už jste využili služby pro porozumění jazyku. Tyto služby jsou v pozadí a převádějí například „Alexo, přehraj nejnovější album od Taylor Swift“ na mou dceru tančící v obýváku na své oblíbené písničky.

> 💁 Počítače, navzdory všem svým pokrokům, mají stále daleko k tomu, aby skutečně rozuměly textu. Když mluvíme o porozumění jazyku u počítačů, nemáme na mysli nic, co by se blížilo lidské komunikaci. Mluvíme o schopnosti vzít slova a extrahovat klíčové detaily.

Jako lidé rozumíme jazyku, aniž bychom o tom museli přemýšlet. Pokud bych požádal jiného člověka, aby „přehrál nejnovější album od Taylor Swift“, instinktivně by věděl, co mám na mysli. Pro počítač je to však složitější. Musel by vzít slova, která byla převedena z řeči na text, a zjistit následující informace:

* Je potřeba přehrát hudbu
* Hudba je od umělce Taylor Swift
* Konkrétní hudba je celé album s více skladbami v pořadí
* Taylor Swift má mnoho alb, takže je potřeba je seřadit chronologicky a vybrat to nejnovější

✅ Zamyslete se nad dalšími větami, které jste řekli při zadávání požadavků, například při objednávání kávy nebo žádosti o podání něčeho od člena rodiny. Zkuste je rozdělit na informace, které by počítač musel extrahovat, aby větě porozuměl.

Modely pro porozumění jazyku jsou AI modely, které jsou trénovány na extrakci určitých detailů z jazyka a poté jsou trénovány pro specifické úkoly pomocí transferového učení, podobně jako jste trénovali model Custom Vision s malou sadou obrázků. Můžete vzít model a poté ho trénovat pomocí textu, kterému chcete, aby rozuměl.

## Vytvoření modelu pro porozumění jazyku

![Logo LUIS](../../../../../translated_images/cs/luis-logo.5cb4f3e88c020ee6.webp)

Modely pro porozumění jazyku můžete vytvářet pomocí LUIS, služby pro porozumění jazyku od Microsoftu, která je součástí Cognitive Services.

### Úkol – vytvoření autorizačního prostředku

Pro použití LUIS musíte vytvořit autorizační prostředek.

1. Použijte následující příkaz k vytvoření autorizačního prostředku ve vaší skupině prostředků `smart-timer`:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Nahraďte `<location>` umístěním, které jste použili při vytváření skupiny prostředků.

    > ⚠️ LUIS není dostupný ve všech regionech, takže pokud obdržíte následující chybu:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > vyberte jiný region.

    Tím vytvoříte bezplatný autorizační prostředek LUIS.

### Úkol – vytvoření aplikace pro porozumění jazyku

1. Otevřete portál LUIS na [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) ve svém prohlížeči a přihlaste se pomocí stejného účtu, který používáte pro Azure.

1. Postupujte podle pokynů v dialogovém okně a vyberte své předplatné Azure, poté vyberte prostředek `smart-timer-luis-authoring`, který jste právě vytvořili.

1. Z nabídky *Conversation apps* vyberte tlačítko **New app** pro vytvoření nové aplikace. Pojmenujte novou aplikaci `smart-timer` a nastavte *Culture* na svůj jazyk.

    > 💁 Existuje pole pro predikční prostředek. Můžete vytvořit druhý prostředek pouze pro predikci, ale bezplatný autorizační prostředek umožňuje 1 000 predikcí měsíčně, což by mělo být pro vývoj dostatečné, takže toto pole můžete nechat prázdné.

1. Projděte si průvodce, který se zobrazí po vytvoření aplikace, abyste pochopili kroky potřebné k trénování modelu pro porozumění jazyku. Po přečtení průvodce jej zavřete.

## Záměry a entity

Porozumění jazyku je založeno na *záměrech* a *entitách*. Záměry představují, co je úmyslem slov, například přehrání hudby, nastavení časovače nebo objednání jídla. Entity představují, na co se záměr vztahuje, například album, délka časovače nebo typ jídla. Každá věta, kterou model interpretuje, by měla mít alespoň jeden záměr a volitelně jednu nebo více entit.

Několik příkladů:

| Věta                                              | Záměr            | Entity                                    |
| ------------------------------------------------- | ---------------- | ----------------------------------------- |
| „Přehraj nejnovější album od Taylor Swift“        | *přehrát hudbu*  | *nejnovější album od Taylor Swift*        |
| „Nastav časovač na 3 minuty“                      | *nastavit časovač* | *3 minuty*                               |
| „Zruš můj časovač“                                | *zrušit časovač* | Žádné                                    |
| „Objednej 3 velké pizzy s ananasem a caesar salát“| *objednat jídlo* | *3 velké pizzy s ananasem*, *caesar salát* |

✅ U vět, které jste si dříve promysleli, jaký by byl záměr a jaké entity by v nich byly?

Pro trénování LUIS nejprve nastavíte entity. Ty mohou být pevně daným seznamem termínů nebo se mohou učit z textu. Například můžete poskytnout pevný seznam jídel dostupných na vašem menu s variantami (nebo synonymy) každého slova, například *lilek* a *baklažán* jako varianty *baklažánu*. LUIS také obsahuje předem připravené entity, které lze použít, například čísla a lokace.

Pro nastavení časovače byste mohli mít jednu entitu využívající předem připravené entity pro čísla (čas) a druhou pro jednotky, jako jsou minuty a sekundy. Každá jednotka by měla více variant, aby pokryla jednotné i množné číslo – například minuta a minuty.

Jakmile jsou entity definovány, vytvoříte záměry. Ty se model učí na základě příkladových vět, které poskytnete (tzv. *utterances*). Například pro záměr *nastavit časovač* byste mohli poskytnout následující věty:

* `nastav časovač na 1 sekundu`
* `nastav časovač na 1 minutu a 12 sekund`
* `nastav časovač na 3 minuty`
* `nastav časovač na 9 minut a 30 sekund`

Poté LUISu označíte, které části těchto vět odpovídají entitám:

![Věta „nastav časovač na 1 minutu a 12 sekund“ rozdělená na entity](../../../../../translated_images/cs/sentence-as-intent-entities.301401696f992259.webp)

Věta `nastav časovač na 1 minutu a 12 sekund` má záměr `nastavit časovač`. Obsahuje také 2 entity, každou se 2 hodnotami:

|            | čas | jednotka   |
| ---------- | ---: | ---------- |
| 1 minuta   | 1    | minuta     |
| 12 sekund  | 12   | sekunda    |

Pro trénování kvalitního modelu potřebujete různé příkladové věty, které pokryjí mnoho různých způsobů, jak by někdo mohl požádat o totéž.

> 💁 Stejně jako u jakéhokoliv AI modelu platí, že čím více dat a čím přesnější data použijete pro trénování, tím lepší bude model.

✅ Zamyslete se nad různými způsoby, jak byste mohli požádat o totéž a očekávali, že tomu člověk porozumí.

### Úkol – přidání entit do modelu pro porozumění jazyku

Pro časovač potřebujete přidat 2 entity – jednu pro jednotku času (minuty nebo sekundy) a jednu pro počet minut nebo sekund.

Pokyny pro použití portálu LUIS najdete v [dokumentaci Quickstart: Build your app in LUIS portal na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Na portálu LUIS vyberte kartu *Entities* a přidejte předem připravenou entitu *number* pomocí tlačítka **Add prebuilt entity**, poté vyberte *number* ze seznamu.

1. Vytvořte novou entitu pro jednotku času pomocí tlačítka **Create**. Pojmenujte entitu `time unit` a nastavte typ na *List*. Přidejte hodnoty `minute` a `second` do seznamu *Normalized values* a přidejte jednotné i množné formy do seznamu *synonyms*. Po přidání každého synonyma stiskněte `return`, aby se přidalo do seznamu.

    | Normalizovaná hodnota | Synonyma        |
    | ---------------------- | --------------- |
    | minuta                | minuta, minuty  |
    | sekunda               | sekunda, sekundy|

### Úkol – přidání záměrů do modelu pro porozumění jazyku

1. Na kartě *Intents* vyberte tlačítko **Create** pro vytvoření nového záměru. Pojmenujte tento záměr `set timer`.

1. Do příkladů zadejte různé způsoby, jak nastavit časovač, a to jak s minutami, sekundami, tak kombinací minut a sekund. Příklady mohou být:

    * `nastav časovač na 1 sekundu`
    * `nastav časovač na 4 minuty`
    * `nastav časovač na čtyři minuty a šest sekund`
    * `nastav časovač na 9 minut a 30 sekund`
    * `nastav časovač na 1 minutu a 12 sekund`
    * `nastav časovač na 3 minuty`
    * `nastav časovač na 3 minuty a 1 sekundu`
    * `nastav časovač na tři minuty a jednu sekundu`
    * `nastav časovač na 1 minutu a 1 sekundu`
    * `nastav časovač na 30 sekund`
    * `nastav časovač na 1 sekundu`

    Kombinujte čísla jako slova i číslice, aby se model naučil pracovat s oběma formami.

1. Jakmile zadáte každý příklad, LUIS začne detekovat entity a podtrhne a označí ty, které najde.

    ![Příklady s podtrženými čísly a jednotkami času detekovanými LUIS](../../../../../translated_images/cs/luis-intent-examples.25716580b2d2723c.webp)

### Úkol – trénování a testování modelu

1. Jakmile jsou entity a záměry nakonfigurovány, můžete model trénovat pomocí tlačítka **Train** v horním menu. Vyberte toto tlačítko a model by se měl během několika sekund natrénovat. Tlačítko bude během trénování šedé a po dokončení bude znovu aktivní.

1. Vyberte tlačítko **Test** v horním menu pro testování modelu pro porozumění jazyku. Zadejte text, například `nastav časovač na 5 minut a 4 sekundy`, a stiskněte Enter. Věta se zobrazí v rámečku pod textovým polem, do kterého jste ji zadali, a pod tím bude *top intent*, tedy záměr, který byl detekován s nejvyšší pravděpodobností. Tento záměr by měl být `set timer`. Název záměru bude následován pravděpodobností, že detekovaný záměr je správný.

1. Vyberte možnost **Inspect**, abyste viděli podrobný rozbor výsledků. Uvidíte záměr s nejvyšším skóre a jeho procentuální pravděpodobnost spolu se seznamy detekovaných entit.

1. Po dokončení testování zavřete panel *Test*.

### Úkol – publikování modelu

Abyste mohli tento model používat z kódu, musíte jej publikovat. Při publikování z LUIS můžete publikovat buď do testovacího prostředí (staging), nebo do produkčního prostředí (production). Pro tuto lekci je testovací prostředí dostačující.

1. Na portálu LUIS vyberte tlačítko **Publish** v horním menu.

1. Ujistěte se, že je vybrána možnost *Staging slot*, a poté vyberte **Done**. Po publikování aplikace se zobrazí oznámení.

1. Můžete to otestovat pomocí curl. Pro sestavení příkazu curl potřebujete tři hodnoty – endpoint, ID aplikace (App ID) a API klíč. Tyto hodnoty najdete na kartě **MANAGE**, kterou můžete vybrat z horního menu.

    1. Z části *Settings* zkopírujte App ID.
1. V sekci *Azure Resources* vyberte *Authoring Resource* a zkopírujte *Primary Key* a *Endpoint URL*.

1. Spusťte následující příkaz curl ve svém příkazovém řádku nebo terminálu:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Nahraďte `<endpoint url>` hodnotou Endpoint URL ze sekce *Azure Resources*.

    Nahraďte `<app id>` hodnotou App ID ze sekce *Settings*.

    Nahraďte `<primary key>` hodnotou Primary Key ze sekce *Azure Resources*.

    Nahraďte `<sentence>` větou, kterou chcete otestovat.

1. Výstup tohoto volání bude JSON dokument, který obsahuje podrobnosti o dotazu, nejpravděpodobnější záměr a seznam entit rozdělených podle typu.

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

    Výše uvedený JSON pochází z dotazu „nastav časovač na 45 minut a 12 sekund“:

    * `set timer` byl nejpravděpodobnější záměr s pravděpodobností 97 %.
    * Byly detekovány dvě entity typu *number*, `45` a `12`.
    * Byly detekovány dvě entity typu *time-unit*, `minute` a `second`.

## Použití modelu porozumění jazyku

Jakmile je model LUIS publikován, může být volán z kódu. V předchozích lekcích jste používali IoT Hub pro komunikaci s cloudovými službami, odesílání telemetrie a přijímání příkazů. Tento proces je velmi asynchronní – jakmile je telemetrie odeslána, váš kód nečeká na odpověď, a pokud je cloudová služba nedostupná, nebudete o tom vědět.

Pro chytrý časovač chceme okamžitou odpověď, abychom mohli uživateli sdělit, že časovač byl nastaven, nebo ho upozornit, že cloudové služby nejsou dostupné. K tomu bude naše IoT zařízení volat webový endpoint přímo, místo spoléhání na IoT Hub.

Namísto volání LUIS z IoT zařízení můžete použít serverless kód s jiným typem triggeru – HTTP trigger. To umožní vaší funkci naslouchat REST požadavkům a reagovat na ně. Tato funkce bude REST endpoint, který vaše zařízení může volat.

> 💁 Ačkoliv můžete volat LUIS přímo z IoT zařízení, je lepší použít něco jako serverless kód. Tímto způsobem, když budete chtít změnit LUIS aplikaci, kterou voláte, například když vytrénujete lepší model nebo model v jiném jazyce, stačí aktualizovat váš cloudový kód, místo přeinstalace kódu na potenciálně tisíce nebo miliony IoT zařízení.

### Úkol – vytvoření serverless funkce

1. Vytvořte Azure Functions aplikaci nazvanou `smart-timer-trigger` a otevřete ji ve VS Code.

1. Přidejte HTTP trigger do této aplikace nazvaný `speech-trigger` pomocí následujícího příkazu v terminálu VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Tím se vytvoří HTTP trigger nazvaný `text-to-timer`.

1. Otestujte HTTP trigger spuštěním aplikace funkcí. Po spuštění uvidíte endpoint uvedený ve výstupu:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Otestujte to načtením URL [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) ve vašem prohlížeči.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Úkol – použití modelu porozumění jazyku

1. SDK pro LUIS je dostupné prostřednictvím balíčku Pip. Přidejte následující řádek do souboru `requirements.txt`, abyste přidali závislost na tomto balíčku:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Ujistěte se, že terminál VS Code má aktivované virtuální prostředí, a spusťte následující příkaz pro instalaci balíčků Pip:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Pokud narazíte na chyby, možná budete muset aktualizovat pip pomocí následujícího příkazu:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Přidejte nové položky do souboru `local.settings.json` pro váš LUIS API Key, Endpoint URL a App ID ze záložky **MANAGE** portálu LUIS:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Nahraďte `<endpoint url>` hodnotou Endpoint URL ze sekce *Azure Resources* záložky **MANAGE**. Toto bude `https://<location>.api.cognitive.microsoft.com/`.

    Nahraďte `<app id>` hodnotou App ID ze sekce *Settings* záložky **MANAGE**.

    Nahraďte `<primary key>` hodnotou Primary Key ze sekce *Azure Resources* záložky **MANAGE**.

1. Přidejte následující importy do souboru `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Tím se importují některé systémové knihovny, stejně jako knihovny pro interakci s LUIS.

1. Smažte obsah metody `main` a přidejte následující kód:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Tento kód načte hodnoty, které jste přidali do souboru `local.settings.json` pro vaši LUIS aplikaci, vytvoří objekt credentials s vaším API klíčem a poté vytvoří LUIS klientský objekt pro interakci s vaší LUIS aplikací.

1. Tento HTTP trigger bude volán s textem k porozumění jako JSON, kde text bude v atributu `text`. Následující kód extrahuje hodnotu z těla HTTP požadavku a zapíše ji do konzole. Přidejte tento kód do funkce `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Predikce jsou požadovány od LUIS odesláním požadavku na predikci – JSON dokumentu obsahujícího text k predikci. Vytvořte tento požadavek následujícím kódem:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Tento požadavek může být poté odeslán do LUIS, pomocí staging slotu, do kterého byla vaše aplikace publikována:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Odpověď na predikci obsahuje nejpravděpodobnější záměr – záměr s nejvyšším skóre predikce, spolu s entitami. Pokud je nejpravděpodobnější záměr `set timer`, pak lze entity přečíst pro získání času potřebného pro časovač:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    Entity typu `number` budou pole čísel. Například pokud řeknete *„Nastav čtyřminutový časovač na 17 sekund“*, pak pole `number` bude obsahovat 2 celá čísla – 4 a 17.

    Entity typu `time unit` budou pole polí řetězců, kde každá časová jednotka bude pole řetězců uvnitř pole. Například pokud řeknete *„Nastav čtyřminutový časovač na 17 sekund“*, pak pole `time unit` bude obsahovat 2 pole s jednou hodnotou každé – `['minute']` a `['second']`.

    JSON verze těchto entit pro *„Nastav čtyřminutový časovač na 17 sekund“* je:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Tento kód také definuje proměnnou pro celkový čas časovače v sekundách. Tato proměnná bude naplněna hodnotami z entit.

1. Entity nejsou propojené, ale můžeme udělat některé předpoklady o jejich pořadí. Budou v pořadí, v jakém byly vysloveny, takže pozice v poli může být použita k určení, které číslo odpovídá které časové jednotce. Například:

    * *„Nastav třicetisekundový časovač“* – bude mít jedno číslo, `30`, a jednu časovou jednotku, `second`, takže jediné číslo bude odpovídat jediné časové jednotce.
    * *„Nastav dvouminutový a třicetisekundový časovač“* – bude mít dvě čísla, `2` a `30`, a dvě časové jednotky, `minute` a `second`, takže první číslo bude pro první časovou jednotku (2 minuty) a druhé číslo pro druhou časovou jednotku (30 sekund).

    Následující kód získá počet položek v entitách typu number a použije to k extrakci první položky z každého pole, poté druhé a tak dále. Přidejte tento kód do bloku `if`.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Pro *„Nastav čtyřminutový časovač na 17 sekund“* bude tento cyklus probíhat dvakrát, což dá následující hodnoty:

    | počet cyklů | `number` | `time_unit` |
    | -----------: | -------: | ----------- |
    | 0            | 4        | minute      |
    | 1            | 17       | second      |

1. Uvnitř tohoto cyklu použijte číslo a časovou jednotku k výpočtu celkového času pro časovač, přičemž přidáte 60 sekund za každou minutu a počet sekund za každé sekundy.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Mimo tento cyklus přes entity zapište celkový čas pro časovač:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Počet sekund musí být vrácen z funkce jako HTTP odpověď. Na konci bloku `if` přidejte následující:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Tento kód vytvoří payload obsahující celkový počet sekund pro časovač, převede ho na JSON řetězec a vrátí ho jako HTTP výsledek se status kódem 200, což znamená, že volání bylo úspěšné.

1. Nakonec, mimo blok `if`, ošetřete případ, kdy záměr nebyl rozpoznán, vrácením chybového kódu:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 je status kód pro *not found*.

1. Spusťte aplikaci funkcí a otestujte ji pomocí curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Nahraďte `<text>` textem vašeho požadavku, například `nastav dvouminutový a 27sekundový časovač`.

    Uvidíte následující výstup z aplikace funkcí:

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

    Volání curl vrátí následující:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Počet sekund pro časovač je v hodnotě `"seconds"`.

> 💁 Tento kód najdete ve složce [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Úkol – zpřístupnění vaší funkce IoT zařízení

1. Aby vaše IoT zařízení mohlo volat váš REST endpoint, bude potřebovat znát URL. Když jste k němu přistupovali dříve, použili jste `localhost`, což je zkratka pro přístup k REST endpointům na vašem lokálním počítači. Abyste umožnili přístup IoT zařízení, musíte buď publikovat do cloudu, nebo získat IP adresu pro lokální přístup.

    > ⚠️ Pokud používáte Wio Terminal, je jednodušší spustit aplikaci funkcí lokálně, protože existuje závislost na knihovnách, která znamená, že nemůžete aplikaci funkcí nasadit stejným způsobem jako dříve. Spusťte aplikaci funkcí lokálně a přistupujte k ní přes IP adresu vašeho počítače. Pokud chcete nasadit do cloudu, informace o tom budou poskytnuty v pozdější lekci.

    * Publikujte aplikaci funkcí – postupujte podle pokynů z předchozích lekcí pro publikování vaší aplikace funkcí do cloudu. Po publikování bude URL `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, kde `<APP_NAME>` bude název vaší aplikace funkcí. Ujistěte se, že také publikujete vaše lokální nastavení.

      Při práci s HTTP triggery jsou tyto ve výchozím nastavení zabezpečeny klíčem aplikace funkcí. Pro získání tohoto klíče spusťte následující příkaz:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Zkopírujte hodnotu položky `default` ze sekce `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Tento klíč bude potřeba přidat jako query parametr do URL, takže finální URL bude `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, kde `<APP_NAME>` bude název vaší aplikace funkcí a `<FUNCTION_KEY>` bude váš výchozí klíč funkce.

      > 💁 Můžete změnit typ autorizace HTTP triggeru pomocí nastavení `authlevel` v souboru `function.json`. Více o tom si můžete přečíst v [konfigurační sekci dokumentace Azure Functions HTTP trigger na Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Spusťte aplikaci funkcí lokálně a přistupujte k ní pomocí IP adresy – můžete získat IP adresu vašeho počítače na lokální síti a použít ji k vytvoření URL.

      Najděte vaši IP adresu:

      * Na Windows 10 postupujte podle [návodu na nalezení IP adresy](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Na macOS postupujte podle [návodu na nalezení IP adresy na Macu](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Na Linuxu postupujte podle sekce o nalezení privátní IP adresy v [návodu na nalezení IP adresy v Linuxu](https://opensource.com/article/18/5/how-find-ip-address-linux).

      Jakmile máte IP adresu, budete schopni přistupovat k funkci na `http://`.

:7071/api/text-to-timer`, kde `<IP_ADDRESS>` bude vaše IP adresa, například `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Upozornění: Používá se port 7071, takže za IP adresou budete muset přidat `:7071`.

      > 💁 Toto bude fungovat pouze v případě, že vaše IoT zařízení je na stejné síti jako váš počítač.

1. Otestujte endpoint pomocí curl.

---

## 🚀 Výzva

Existuje mnoho způsobů, jak požádat o stejnou věc, například nastavení časovače. Přemýšlejte o různých způsobech, jak to udělat, a použijte je jako příklady ve své aplikaci LUIS. Otestujte je, abyste zjistili, jak dobře váš model zvládá různé způsoby požadavků na časovač.

## Kvíz po přednášce

[Kvíz po přednášce](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Přehled & Samostudium

* Přečtěte si více o LUIS a jeho schopnostech na [stránce dokumentace Language Understanding (LUIS) na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Přečtěte si více o porozumění jazyku na [stránce o porozumění přirozenému jazyku na Wikipedii](https://wikipedia.org/wiki/Natural-language_understanding)
* Přečtěte si více o HTTP triggerech v [dokumentaci Azure Functions HTTP trigger na Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Zadání

[Zrušit časovač](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.