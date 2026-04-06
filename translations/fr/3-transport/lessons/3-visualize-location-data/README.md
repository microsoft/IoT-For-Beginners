# Visualiser des données de localisation

![Un aperçu illustré de cette leçon](../../../../../translated_images/fr/lesson-13.a259db1485021be7.webp)

> Illustration par [Nitya Narasimhan](https://github.com/nitya). Cliquez sur l'image pour une version agrandie.

Cette vidéo donne un aperçu d'Azure Maps avec IoT, un service qui sera abordé dans cette leçon.

[![Azure Maps - La plateforme de localisation d'entreprise Microsoft Azure](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Cliquez sur l'image ci-dessus pour regarder la vidéo

## Quiz avant la leçon

[Quiz avant la leçon](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Introduction

Dans la dernière leçon, vous avez appris à obtenir des données GPS de vos capteurs pour les enregistrer dans le cloud dans un conteneur de stockage à l'aide de code sans serveur. Maintenant, vous allez découvrir comment visualiser ces points sur une carte Azure. Vous apprendrez à créer une carte sur une page web, à comprendre le format de données GeoJSON et à l'utiliser pour tracer tous les points GPS capturés sur votre carte.

Dans cette leçon, nous aborderons :

* [Qu'est-ce que la visualisation de données](../../../../../3-transport/lessons/3-visualize-location-data)
* [Services de cartographie](../../../../../3-transport/lessons/3-visualize-location-data)
* [Créer une ressource Azure Maps](../../../../../3-transport/lessons/3-visualize-location-data)
* [Afficher une carte sur une page web](../../../../../3-transport/lessons/3-visualize-location-data)
* [Le format GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)
* [Tracer des données GPS sur une carte avec GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Cette leçon impliquera une petite quantité de HTML et de JavaScript. Si vous souhaitez en savoir plus sur le développement web avec HTML et JavaScript, consultez [Développement web pour débutants](https://github.com/microsoft/Web-Dev-For-Beginners).

## Qu'est-ce que la visualisation de données

La visualisation de données, comme son nom l'indique, consiste à représenter visuellement des données de manière à les rendre plus compréhensibles pour les humains. Elle est généralement associée à des graphiques et des diagrammes, mais englobe toute méthode de représentation picturale des données pour aider les humains à mieux les comprendre et à prendre des décisions.

Prenons un exemple simple : dans le projet agricole, vous avez capturé des mesures d'humidité du sol. Un tableau des données d'humidité du sol capturées toutes les heures pour le 1er juin 2021 pourrait ressembler à ceci :

| Date             | Lecture |
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

Pour un humain, comprendre ces données peut être difficile. C'est une masse de chiffres sans signification apparente. Une première étape pour visualiser ces données consiste à les tracer sur un graphique en courbes :

![Un graphique en courbes des données ci-dessus](../../../../../translated_images/fr/chart-soil-moisture.fd6d9d0cdc0b5f75.webp)

Cela peut être encore amélioré en ajoutant une ligne indiquant quand le système d'arrosage automatique a été activé à une lecture d'humidité du sol de 450 :

![Un graphique en courbes de l'humidité du sol avec une ligne à 450](../../../../../translated_images/fr/chart-soil-moisture-relay.fbb391236d34a64d.webp)

Ce graphique montre très rapidement non seulement les niveaux d'humidité du sol, mais aussi les points où le système d'arrosage a été activé.

Les graphiques ne sont pas le seul outil pour visualiser des données. Les appareils IoT qui suivent les conditions météorologiques peuvent avoir des applications web ou mobiles qui visualisent les conditions météorologiques à l'aide de symboles, comme un nuage pour les jours nuageux, un nuage de pluie pour les jours pluvieux, etc. Il existe une multitude de façons de visualiser les données, certaines sérieuses, d'autres amusantes.

✅ Réfléchissez aux façons dont vous avez vu des données visualisées. Quelles méthodes ont été les plus claires et vous ont permis de prendre des décisions rapidement ?

Les meilleures visualisations permettent aux humains de prendre des décisions rapidement. Par exemple, avoir un mur de jauges montrant toutes sortes de lectures provenant de machines industrielles est difficile à traiter, mais une lumière rouge clignotante lorsqu'un problème survient permet à un humain de prendre une décision. Parfois, la meilleure visualisation est une lumière clignotante !

Lorsqu'on travaille avec des données GPS, la visualisation la plus claire peut être de tracer les données sur une carte. Une carte montrant des camions de livraison, par exemple, peut aider les travailleurs d'une usine de traitement à voir quand les camions arriveront. Si cette carte montre plus que de simples images de camions à leurs emplacements actuels, mais donne une idée du contenu d'un camion, alors les travailleurs de l'usine peuvent planifier en conséquence - s'ils voient un camion réfrigéré à proximité, ils savent qu'ils doivent préparer de l'espace dans un réfrigérateur.

## Services de cartographie

Travailler avec des cartes est un exercice intéressant, et il existe de nombreuses options comme Bing Maps, Leaflet, Open Street Maps et Google Maps. Dans cette leçon, vous apprendrez à utiliser [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) et comment ils peuvent afficher vos données GPS.

![Le logo Azure Maps](../../../../../translated_images/fr/azure-maps-logo.35d01dcfbd81fe61.webp)

Azure Maps est "une collection de services géospatiaux et de SDK qui utilisent des données cartographiques actualisées pour fournir un contexte géographique aux applications web et mobiles." Les développeurs disposent d'outils pour créer de belles cartes interactives capables de fournir des itinéraires recommandés, des informations sur les incidents de circulation, une navigation intérieure, des capacités de recherche, des informations sur l'altitude, des services météorologiques et bien plus encore.

✅ Expérimentez avec quelques [exemples de code de cartographie](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Vous pouvez afficher les cartes comme une toile vierge, des tuiles, des images satellites, des images satellites avec des routes superposées, divers types de cartes en niveaux de gris, des cartes avec relief ombré pour montrer l'altitude, des cartes de nuit et une carte à contraste élevé. Vous pouvez obtenir des mises à jour en temps réel sur vos cartes en les intégrant à [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn). Vous pouvez contrôler le comportement et l'apparence de vos cartes en activant divers contrôles permettant à la carte de réagir à des événements comme le pincement, le glissement et le clic. Pour contrôler l'apparence de votre carte, vous pouvez ajouter des couches comprenant des bulles, des lignes, des polygones, des cartes de chaleur, et plus encore. Le style de carte que vous implémentez dépend de votre choix de SDK.

Vous pouvez accéder aux API Azure Maps en utilisant son [API REST](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), son [SDK Web](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn), ou, si vous développez une application mobile, son [SDK Android](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android).

Dans cette leçon, vous utiliserez le SDK web pour dessiner une carte et afficher le chemin des localisations GPS de votre capteur.

## Créer une ressource Azure Maps

Votre première étape consiste à créer un compte Azure Maps.

### Tâche - créer une ressource Azure Maps

1. Exécutez la commande suivante depuis votre terminal ou invite de commande pour créer une ressource Azure Maps dans votre groupe de ressources `gps-sensor` :

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Cela créera une ressource Azure Maps appelée `gps-sensor`. Le niveau utilisé est `S1`, qui est un niveau payant incluant une gamme de fonctionnalités, mais avec un nombre généreux d'appels gratuits.

    > 💁 Pour voir le coût d'utilisation d'Azure Maps, consultez la [page de tarification Azure Maps](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Vous aurez besoin d'une clé API pour la ressource cartographique. Utilisez la commande suivante pour obtenir cette clé :

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Copiez la valeur de `PrimaryKey`.

## Afficher une carte sur une page web

Vous pouvez maintenant passer à l'étape suivante, qui consiste à afficher votre carte sur une page web. Nous utiliserons un seul fichier `html` pour votre petite application web ; gardez à l'esprit que dans un environnement de production ou d'équipe, votre application web aura probablement plus de composants.

### Tâche - afficher une carte sur une page web

1. Créez un fichier appelé index.html dans un dossier sur votre ordinateur local. Ajoutez une structure HTML pour contenir une carte :

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

    La carte se chargera dans le `div` nommé `myMap`. Quelques styles permettent à la carte de s'étendre sur toute la largeur et la hauteur de la page.

    > 🎓 un `div` est une section d'une page web qui peut être nommée et stylisée.

1. Sous la balise d'ouverture `<head>`, ajoutez une feuille de style externe pour contrôler l'affichage de la carte, ainsi qu'un script externe du SDK Web pour gérer son comportement :

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Cette feuille de style contient les paramètres pour l'apparence de la carte, et le fichier script contient le code pour charger la carte. Ajouter ce code est similaire à inclure des fichiers d'en-tête en C++ ou importer des modules en Python.

1. Sous ce script, ajoutez un bloc de script pour lancer la carte.

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

    Remplacez `<subscription_key>` par la clé API de votre compte Azure Maps.

    Si vous ouvrez votre page `index.html` dans un navigateur web, vous devriez voir une carte chargée, centrée sur la région de Seattle.

    ![Une carte montrant Seattle, une ville de l'État de Washington, aux États-Unis](../../../../../translated_images/fr/map-image.8fb2c53eb23ef39c.webp)

    ✅ Expérimentez avec les paramètres de zoom et de centre pour modifier l'affichage de votre carte. Vous pouvez ajouter différentes coordonnées correspondant à la latitude et à la longitude de vos données pour recentrer la carte.

> 💁 Une meilleure façon de travailler avec des applications web localement est d'installer [http-server](https://www.npmjs.com/package/http-server). Vous aurez besoin de [node.js](https://nodejs.org/) et de [npm](https://www.npmjs.com/) installés avant d'utiliser cet outil. Une fois ces outils installés, vous pouvez naviguer jusqu'à l'emplacement de votre fichier `index.html` et taper `http-server`. L'application web s'ouvrira sur un serveur web local [http://127.0.0.1:8080/](http://127.0.0.1:8080/).

## Le format GeoJSON

Maintenant que vous avez votre application web en place avec la carte affichée, vous devez extraire les données GPS de votre compte de stockage et les afficher dans une couche de marqueurs sur la carte. Avant de faire cela, examinons le format [GeoJSON](https://wikipedia.org/wiki/GeoJSON) requis par Azure Maps.

[GeoJSON](https://geojson.org/) est une norme ouverte de spécification JSON avec un formatage spécial conçu pour gérer des données spécifiques à la géographie. Vous pouvez en apprendre davantage en testant des données d'exemple à l'aide de [geojson.io](https://geojson.io), qui est également un outil utile pour déboguer des fichiers GeoJSON.

Un exemple de données GeoJSON ressemble à ceci :

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

Ce qui est particulièrement intéressant, c'est la manière dont les données sont imbriquées en tant que `Feature` dans une `FeatureCollection`. À l'intérieur de cet objet, on trouve `geometry` avec les `coordinates` indiquant la latitude et la longitude.

✅ Lorsque vous construisez votre GeoJSON, faites attention à l'ordre de `latitude` et `longitude` dans l'objet, sinon vos points n'apparaîtront pas au bon endroit ! GeoJSON attend des données dans l'ordre `lon,lat` pour les points, et non `lat,lon`.

`Geometry` peut avoir différents types, comme un point unique ou un polygone. Dans cet exemple, il s'agit d'un point avec deux coordonnées spécifiées, la longitude et la latitude.
✅ Azure Maps prend en charge le GeoJSON standard ainsi que certaines [fonctionnalités améliorées](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn), y compris la possibilité de dessiner des cercles et d'autres géométries.

## Tracer des données GPS sur une carte en utilisant GeoJSON

Vous êtes maintenant prêt à utiliser les données provenant du stockage que vous avez configuré dans la leçon précédente. Pour rappel, elles sont stockées sous forme de plusieurs fichiers dans un stockage blob, vous devrez donc récupérer ces fichiers et les analyser pour qu'Azure Maps puisse les utiliser.

### Tâche - configurer le stockage pour qu'il soit accessible depuis une page web

Si vous appelez votre stockage pour récupérer les données, vous pourriez être surpris de voir des erreurs apparaître dans la console de votre navigateur. Cela est dû au fait que vous devez définir des autorisations pour [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) sur ce stockage afin de permettre aux applications web externes de lire ses données.

> 🎓 CORS signifie "Cross-Origin Resource Sharing" (partage des ressources entre origines multiples) et doit généralement être configuré explicitement dans Azure pour des raisons de sécurité. Cela empêche des sites non autorisés d'accéder à vos données.

1. Exécutez la commande suivante pour activer CORS :

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Remplacez `<storage_name>` par le nom de votre compte de stockage. Remplacez `<key1>` par la clé de compte de votre compte de stockage.

    Cette commande permet à n'importe quel site web (le caractère générique `*` signifie n'importe quel site) d'effectuer une requête *GET*, c'est-à-dire de récupérer des données, depuis votre compte de stockage. L'option `--services b` signifie que ce paramètre s'applique uniquement aux blobs.

### Tâche - charger les données GPS depuis le stockage

1. Remplacez tout le contenu de la fonction `init` par le code suivant :

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

    Remplacez `<storage_name>` par le nom de votre compte de stockage. Remplacez `<subscription_key>` par la clé API de votre compte Azure Maps.

    Plusieurs choses se passent ici. Tout d'abord, le code récupère vos données GPS depuis votre conteneur blob en utilisant un point de terminaison URL construit avec le nom de votre compte de stockage. Cette URL récupère depuis `gps-data`, indiquant que le type de ressource est un conteneur (`restype=container`), et liste les informations sur tous les blobs. Cette liste ne renverra pas les blobs eux-mêmes, mais fournira une URL pour chaque blob qui peut être utilisée pour charger les données du blob.

    > 💁 Vous pouvez entrer cette URL dans votre navigateur pour voir les détails de tous les blobs dans votre conteneur. Chaque élément aura une propriété `Url` que vous pouvez également charger dans votre navigateur pour voir le contenu du blob.

    Ce code charge ensuite chaque blob, en appelant une fonction `loadJSON`, qui sera créée ensuite. Il crée ensuite le contrôle de la carte et ajoute du code à l'événement `ready`. Cet événement est déclenché lorsque la carte est affichée sur la page web.

    L'événement `ready` crée une source de données Azure Maps - un conteneur qui contient des données GeoJSON qui seront peuplées plus tard. Cette source de données est ensuite utilisée pour créer une couche de bulles - c'est-à-dire un ensemble de cercles sur la carte centrés sur chaque point du GeoJSON.

1. Ajoutez la fonction `loadJSON` à votre bloc de script, sous la fonction `init` :

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

    Cette fonction est appelée par la routine de récupération pour analyser les données JSON et les convertir en coordonnées de longitude et latitude au format GeoJSON. Une fois analysées, les données sont définies comme une `Feature` GeoJSON. La carte sera initialisée et de petites bulles apparaîtront le long du chemin tracé par vos données :

1. Chargez la page HTML dans votre navigateur. Elle chargera la carte, puis toutes les données GPS depuis le stockage et les tracera sur la carte.

    ![Une carte du parc d'État Saint Edward près de Seattle, avec des cercles montrant un chemin autour du parc](../../../../../translated_images/fr/map-path.896832e72dc696ff.webp)

> 💁 Vous pouvez trouver ce code dans le dossier [code](../../../../../3-transport/lessons/3-visualize-location-data/code).

---

## 🚀 Défi

C'est agréable de pouvoir afficher des données statiques sur une carte sous forme de marqueurs. Pouvez-vous améliorer cette application web pour ajouter une animation et montrer le chemin des marqueurs au fil du temps, en utilisant les fichiers JSON horodatés ? Voici [quelques exemples](https://azuremapscodesamples.azurewebsites.net/) d'utilisation de l'animation dans les cartes.

## Quiz post-lecture

[Quiz post-lecture](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Révision et auto-apprentissage

Azure Maps est particulièrement utile pour travailler avec des appareils IoT.

* Recherchez certaines des utilisations dans la [documentation Azure Maps sur Microsoft docs](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Approfondissez vos connaissances sur la création de cartes et les points de passage avec le [module d'apprentissage autonome "créez votre première application de recherche d'itinéraire avec Azure Maps" sur Microsoft Learn](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Devoir

[Déployez votre application](assignment.md)

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.