<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-27T21:51:35+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "cs"
}
-->
# Vizualizace dat o poloze

![Přehled této lekce ve formě sketchnote](../../../../../translated_images/cs/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

Toto video poskytuje přehled Azure Maps s IoT, služby, která bude pokryta v této lekci.

[![Azure Maps - Platforma pro lokalizační služby Microsoft Azure](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Klikněte na obrázek výše pro zhlédnutí videa

## Kvíz před lekcí

[Kvíz před lekcí](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Úvod

V minulé lekci jste se naučili, jak získat GPS data ze svých senzorů a uložit je do cloudu v úložišti pomocí serverless kódu. Nyní objevíte, jak tyto body vizualizovat na mapě Azure. Naučíte se, jak vytvořit mapu na webové stránce, seznámíte se s datovým formátem GeoJSON a zjistíte, jak jej použít k vykreslení všech zachycených GPS bodů na mapě.

V této lekci se zaměříme na:

* [Co je vizualizace dat](../../../../../3-transport/lessons/3-visualize-location-data)
* [Mapové služby](../../../../../3-transport/lessons/3-visualize-location-data)
* [Vytvoření zdroje Azure Maps](../../../../../3-transport/lessons/3-visualize-location-data)
* [Zobrazení mapy na webové stránce](../../../../../3-transport/lessons/3-visualize-location-data)
* [Formát GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)
* [Vykreslení GPS dat na mapě pomocí GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Tato lekce zahrnuje malé množství HTML a JavaScriptu. Pokud se chcete dozvědět více o vývoji webu pomocí HTML a JavaScriptu, podívejte se na [Web development for beginners](https://github.com/microsoft/Web-Dev-For-Beginners).

## Co je vizualizace dat

Vizualizace dat, jak název napovídá, je o zobrazování dat způsobem, který usnadňuje jejich pochopení lidem. Obvykle se spojuje s grafy a diagramy, ale zahrnuje jakýkoli způsob obrazového znázornění dat, který pomáhá lidem nejen lépe porozumět datům, ale také přijímat rozhodnutí.

Jednoduchý příklad - v projektu farmy jste zachytili údaje o vlhkosti půdy. Tabulka dat o vlhkosti půdy zachycených každou hodinu 1. června 2021 by mohla vypadat takto:

| Datum            | Hodnota |
| ---------------- | ------: |
| 01/06/2021 00:00 |     257 |
| 01/06/2021 01:00 |     268 |
| 01/06/2021 02:00 |     295 |
| 01/06/2021 03:00 |     305 |
| 01/06/2021 04:00 |     325 |
| 01/06/2021 05:00 |     359 |
| 01/06/2021 06:00 |     398 |
| 01/06/2021 07:00 |     410 |
| 01/06/2021 08:00 |     429 |
| 01/06/2021 09:00 |     451 |
| 01/06/2021 10:00 |     460 |
| 01/06/2021 11:00 |     452 |
| 01/06/2021 12:00 |     420 |
| 01/06/2021 13:00 |     408 |
| 01/06/2021 14:00 |     431 |
| 01/06/2021 15:00 |     462 |
| 01/06/2021 16:00 |     432 |
| 01/06/2021 17:00 |     402 |
| 01/06/2021 18:00 |     387 |
| 01/06/2021 19:00 |     360 |
| 01/06/2021 20:00 |     358 |
| 01/06/2021 21:00 |     354 |
| 01/06/2021 22:00 |     356 |
| 01/06/2021 23:00 |     362 |

Pro člověka může být pochopení těchto dat obtížné. Je to jen stěna čísel bez jakéhokoli významu. Jako první krok k vizualizaci těchto dat je možné je vykreslit na čárovém grafu:

![Čárový graf výše uvedených dat](../../../../../translated_images/cs/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

Tento graf lze dále vylepšit přidáním čáry, která označuje, kdy byl automatický zavlažovací systém zapnut při hodnotě vlhkosti půdy 450:

![Čárový graf vlhkosti půdy s čárou na hodnotě 450](../../../../../translated_images/cs/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

Tento graf velmi rychle ukazuje nejen úroveň vlhkosti půdy, ale také body, kdy byl zavlažovací systém zapnut.

Grafy nejsou jediným nástrojem pro vizualizaci dat. IoT zařízení, která sledují počasí, mohou mít webové nebo mobilní aplikace, které vizualizují povětrnostní podmínky pomocí symbolů, jako je symbol mraku pro zamračené dny, dešťový mrak pro deštivé dny a podobně. Existuje obrovské množství způsobů, jak vizualizovat data, některé vážné, jiné zábavné.

✅ Zamyslete se nad způsoby, jakými jste viděli data vizualizována. Které metody byly nejjasnější a umožnily vám nejrychleji přijímat rozhodnutí?

Nejlepší vizualizace umožňují lidem rychle se rozhodovat. Například mít stěnu ukazatelů zobrazujících různé hodnoty z průmyslových strojů je těžké zpracovat, ale blikající červené světlo, když se něco pokazí, umožňuje člověku rychle jednat. Někdy je nejlepší vizualizací blikající světlo!

Při práci s GPS daty může být nejjasnější vizualizací vykreslení dat na mapě. Mapa zobrazující například doručovací vozy může pomoci pracovníkům v zpracovatelském závodě vidět, kdy vozy dorazí. Pokud tato mapa ukazuje více než jen obrázky vozů na jejich aktuálních místech, ale také poskytuje představu o obsahu vozu, mohou pracovníci v závodě podle toho plánovat - pokud vidí blízko chladírenský vůz, vědí, že mají připravit místo v lednici.

## Mapové služby

Práce s mapami je zajímavé cvičení a existuje mnoho možností, jako jsou Bing Maps, Leaflet, Open Street Maps a Google Maps. V této lekci se naučíte o [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) a jak mohou zobrazovat vaše GPS data.

![Logo Azure Maps](../../../../../translated_images/cs/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps je "sbírka geospace služeb a SDK, které využívají aktuální mapová data k poskytování geografického kontextu webovým a mobilním aplikacím." Vývojáři mají k dispozici nástroje pro vytváření krásných, interaktivních map, které mohou například poskytovat doporučené trasy, informace o dopravních incidentech, navigaci uvnitř budov, vyhledávací funkce, informace o nadmořské výšce, povětrnostní služby a další.

✅ Vyzkoušejte některé [ukázky kódu pro mapování](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Mapy můžete zobrazit jako prázdné plátno, dlaždice, satelitní snímky, satelitní snímky s překrytými silnicemi, různé typy šedých map, mapy s odstíněným reliéfem pro zobrazení nadmořské výšky, noční mapy a mapy s vysokým kontrastem. Můžete získat aktualizace v reálném čase na svých mapách integrací s [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn). Můžete ovládat chování a vzhled svých map povolením různých ovládacích prvků, které umožňují mapě reagovat na události, jako je přiblížení, přetažení a kliknutí. Pro kontrolu vzhledu mapy můžete přidat vrstvy, které zahrnují bubliny, čáry, polygony, teplotní mapy a další. Styl mapy, který implementujete, závisí na vašem výběru SDK.

K API Azure Maps můžete přistupovat pomocí [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn) nebo, pokud vytváříte mobilní aplikaci, [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android).

V této lekci použijete Web SDK k vykreslení mapy a zobrazení cesty GPS polohy vašeho senzoru.

## Vytvoření zdroje Azure Maps

Prvním krokem je vytvoření účtu Azure Maps.

### Úkol - vytvoření zdroje Azure Maps

1. Spusťte následující příkaz z Terminálu nebo Příkazového řádku pro vytvoření zdroje Azure Maps ve vaší skupině zdrojů `gps-sensor`:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Tím se vytvoří zdroj Azure Maps s názvem `gps-sensor`. Použitá úroveň je `S1`, což je placená úroveň zahrnující řadu funkcí, ale s velkorysým množstvím volání zdarma.

    > 💁 Pro zjištění nákladů na používání Azure Maps se podívejte na [stránku s cenami Azure Maps](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Budete potřebovat API klíč pro mapový zdroj. Použijte následující příkaz k získání tohoto klíče:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Zkopírujte hodnotu `PrimaryKey`.

## Zobrazení mapy na webové stránce

Nyní můžete přejít k dalšímu kroku, kterým je zobrazení mapy na webové stránce. Použijeme pouze jeden soubor `html` pro vaši malou webovou aplikaci; mějte na paměti, že v produkčním nebo týmovém prostředí bude vaše webová aplikace pravděpodobně obsahovat více částí!

### Úkol - zobrazení mapy na webové stránce

1. Vytvořte soubor s názvem index.html v nějaké složce na vašem lokálním počítači. Přidejte HTML značky pro umístění mapy:

    ```html
    <html>
    <head>
        <style>
            #myMap {
                width:100%;
                height:100%;
            }
        </style>
    </head>
    
    <body onload="init()">
        <div id="myMap"></div>
    </body>
    </html>
    ```

    Mapa se načte do `div` s názvem `myMap`. Několik stylů umožní, aby se rozprostřela na šířku a výšku stránky.

    > 🎓 `div` je sekce webové stránky, kterou lze pojmenovat a stylovat.

1. Pod otevírací značku `<head>` přidejte externí stylový list pro ovládání zobrazení mapy a externí skript z Web SDK pro správu jejího chování:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Tento stylový list obsahuje nastavení vzhledu mapy a skriptový soubor obsahuje kód pro načtení mapy. Přidání tohoto kódu je podobné zahrnutí hlavičkových souborů v C++ nebo importování modulů v Pythonu.

1. Pod tento skript přidejte blok skriptu pro spuštění mapy.

    ```javascript
    <script type='text/javascript'>
        function init() {
            var map = new atlas.Map('myMap', {
                center: [-122.26473, 47.73444],
                zoom: 12,
                authOptions: {
                    authType: "subscriptionKey",
                    subscriptionKey: "<subscription_key>",

                }
            });
        }
    </script>
    ```

    Nahraďte `<subscription_key>` API klíčem pro váš účet Azure Maps.

    Pokud otevřete svůj soubor `index.html` v webovém prohlížeči, měli byste vidět načtenou mapu zaměřenou na oblast Seattlu.

    ![Mapa zobrazující Seattle, město ve státě Washington, USA](../../../../../translated_images/cs/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ Experimentujte s parametry zoomu a centra pro změnu zobrazení mapy. Můžete přidat různé souřadnice odpovídající zeměpisné šířce a délce vašich dat pro přemístění mapy.

> 💁 Lepší způsob práce s webovými aplikacemi lokálně je instalace [http-server](https://www.npmjs.com/package/http-server). Budete potřebovat [node.js](https://nodejs.org/) a [npm](https://www.npmjs.com/) nainstalované před použitím tohoto nástroje. Jakmile jsou tyto nástroje nainstalovány, můžete přejít do umístění vašeho souboru `index.html` a zadat `http-server`. Webová aplikace se otevře na lokálním webovém serveru [http://127.0.0.1:8080/](http://127.0.0.1:8080/).

## Formát GeoJSON

Nyní, když máte svou webovou aplikaci připravenou s mapou zobrazenou, potřebujete extrahovat GPS data z vašeho úložiště a zobrazit je ve vrstvě značek na mapě. Než to uděláme, podívejme se na [GeoJSON](https://wikipedia.org/wiki/GeoJSON) formát, který je vyžadován Azure Maps.

[GeoJSON](https://geojson.org/) je otevřený standard JSON specifikace se speciálním formátováním navrženým pro práci s geografickými daty. Můžete se o něm dozvědět více testováním ukázkových dat pomocí [geojson.io](https://geojson.io), což je také užitečný nástroj pro ladění GeoJSON souborů.

Ukázková data GeoJSON vypadají takto:

```json
{
  "type": "FeatureCollection",
  "features": [
    {
      "type": "Feature",
      "geometry": {
        "type": "Point",
        "coordinates": [
          -2.10237979888916,
          57.164918677004714
        ]
      }
    }
  ]
}
```

Zvláštní pozornost si zaslouží způsob, jakým jsou data zanořena jako `Feature` uvnitř `FeatureCollection`. Uvnitř tohoto objektu se nachází `geometry` s `coordinates`, které označují zeměpisnou šířku a délku.

✅ Při vytváření svého GeoJSON věnujte pozornost pořadí `latitude` a `longitude` v objektu, jinak se vaše body neobjeví tam, kde by měly! GeoJSON očekává data v pořadí `lon,lat` pro body, nikoli `lat,lon`.

`Geometry` může mít různé typy, jako je jeden bod nebo polygon. V tomto příkladu se jedná o bod se dvěma specifikovanými souřadnicemi, zeměpisnou délkou a šířkou.
✅ Azure Maps podporuje standardní GeoJSON a navíc některé [rozšířené funkce](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn), včetně možnosti kreslit kruhy a další geometrické tvary.

## Zobrazení GPS dat na mapě pomocí GeoJSON

Nyní jste připraveni využívat data z úložiště, které jste vytvořili v předchozí lekci. Připomínáme, že jsou uložena jako několik souborů v blobovém úložišti, takže budete muset tyto soubory načíst a zpracovat, aby je Azure Maps mohl použít.

### Úkol - konfigurace úložiště pro přístup z webové stránky

Pokud provedete požadavek na své úložiště, abyste získali data, můžete být překvapeni, když uvidíte chyby v konzoli vašeho prohlížeče. To je způsobeno tím, že je třeba nastavit oprávnění pro [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) na tomto úložišti, aby externí webové aplikace mohly číst jeho data.

> 🎓 CORS znamená "Cross-Origin Resource Sharing" (sdílení zdrojů mezi různými doménami) a obvykle je nutné jej explicitně nastavit v Azure z bezpečnostních důvodů. Zabraňuje tomu, aby neočekávané weby měly přístup k vašim datům.

1. Spusťte následující příkaz pro povolení CORS:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Nahraďte `<storage_name>` názvem vašeho úložiště. Nahraďte `<key1>` klíčem účtu pro vaše úložiště.

    Tento příkaz umožňuje jakémukoliv webu (zástupný znak `*` znamená jakýkoliv) provést požadavek typu *GET*, tedy získat data z vašeho úložiště. `--services b` znamená, že toto nastavení se aplikuje pouze na blobové úložiště.

### Úkol - načtení GPS dat z úložiště

1. Nahraďte celý obsah funkce `init` následujícím kódem:

    ```javascript
    fetch("https://<storage_name>.blob.core.windows.net/gps-data/?restype=container&comp=list")
        .then(response => response.text())
        .then(str => new window.DOMParser().parseFromString(str, "text/xml"))
        .then(xml => {
            let blobList = Array.from(xml.querySelectorAll("Url"));
                blobList.forEach(async blobUrl => {
                    loadJSON(blobUrl.innerHTML)                
        });
    })
    .then( response => {
        map = new atlas.Map('myMap', {
            center: [-122.26473, 47.73444],
            zoom: 14,
            authOptions: {
                authType: "subscriptionKey",
                subscriptionKey: "<subscription_key>",
    
            }
        });
        map.events.add('ready', function () {
            var source = new atlas.source.DataSource();
            map.sources.add(source);
            map.layers.add(new atlas.layer.BubbleLayer(source));
            source.add(features);
        })
    })
    ```

    Nahraďte `<storage_name>` názvem vašeho úložiště. Nahraďte `<subscription_key>` API klíčem pro váš účet Azure Maps.

    Zde se děje několik věcí. Nejprve kód načte vaše GPS data z blobového kontejneru pomocí URL endpointu vytvořeného na základě názvu vašeho úložiště. Tato URL načítá z `gps-data`, což označuje, že typ zdroje je kontejner (`restype=container`), a poskytuje informace o všech blobech. Tento seznam nevrátí samotné blobové soubory, ale vrátí URL pro každý blob, který lze použít k načtení dat blobu.

    > 💁 Tuto URL můžete vložit do svého prohlížeče, abyste viděli podrobnosti o všech blobech ve vašem kontejneru. Každá položka bude mít vlastnost `Url`, kterou můžete také načíst ve svém prohlížeči a zobrazit obsah blobu.

    Tento kód poté načte každý blob, volá funkci `loadJSON`, kterou vytvoříme dále. Poté vytvoří ovládací prvek mapy a přidá kód do události `ready`. Tato událost se volá, když je mapa zobrazena na webové stránce.

    Událost `ready` vytvoří datový zdroj Azure Maps - kontejner, který obsahuje GeoJSON data, která budou později naplněna. Tento datový zdroj se poté použije k vytvoření vrstvy bublin - tedy sady kruhů na mapě, které jsou umístěny nad každým bodem v GeoJSON.

1. Přidejte funkci `loadJSON` do svého skriptového bloku, pod funkci `init`:

    ```javascript
    var map, features;

    function loadJSON(file) {
        var xhr = new XMLHttpRequest();
        features = [];
        xhr.onreadystatechange = function () {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    gps = JSON.parse(xhr.responseText)
                    features.push(
                        new atlas.data.Feature(new atlas.data.Point([parseFloat(gps.gps.lon), parseFloat(gps.gps.lat)]))
                    )
                }
            }
        };
        xhr.open("GET", file, true);
        xhr.send();
    }    
    ```

    Tato funkce je volána rutinním načítáním, aby prošla JSON data a převedla je na čtení jako souřadnice zeměpisné délky a šířky ve formátu GeoJSON.
    Po zpracování jsou data nastavena jako součást GeoJSON `Feature`. Mapa bude inicializována a malé bubliny se objeví kolem cesty, kterou vaše data vykreslují:

1. Načtěte HTML stránku ve svém prohlížeči. Načte mapu, poté načte všechna GPS data z úložiště a vykreslí je na mapě.

    ![Mapa Saint Edward State Park poblíž Seattlu, s kruhy zobrazujícími cestu kolem okraje parku](../../../../../translated_images/cs/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 Tento kód najdete ve složce [code](../../../../../3-transport/lessons/3-visualize-location-data/code).

---

## 🚀 Výzva

Je hezké zobrazit statická data na mapě jako značky. Dokážete vylepšit tuto webovou aplikaci tak, aby přidala animaci a zobrazila cestu značek v průběhu času pomocí časově označených JSON souborů? Zde jsou [některé ukázky](https://azuremapscodesamples.azurewebsites.net/) použití animace v mapách.

## Kvíz po přednášce

[Kvíz po přednášce](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Přehled & Samostudium

Azure Maps je obzvláště užitečný pro práci s IoT zařízeními.

* Prozkoumejte některé z použití v [dokumentaci Azure Maps na Microsoft docs](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Prohlubte své znalosti o tvorbě map a trasových bodech pomocí [vytvoření vaší první aplikace pro hledání tras s Azure Maps v samostatném výukovém modulu na Microsoft Learn](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Zadání

[Nasazení vaší aplikace](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.