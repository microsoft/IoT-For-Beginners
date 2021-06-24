# Visualize location data

Add a sketchnote if possible/appropriate
## Pre-lecture quiz

[Pre-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/25)

## Introduction

In the last lesson you learned how to get GPS data from your sensors to save to the cloud in a storage container using serverless code. Now you will discover how to visualize those points on an Azure map.

In this lesson we'll cover:

  - [What is Azure maps?](#what-is-azure-maps)
  - [Create an Azure Maps resource](#create-an-azure-maps-resource)
  - [Show a map on a web page](#show-a-map-on-a-web-page)
  - [The GeoJSON format](#the-geojson-format)
  - [Plot GPS data on a Map using GeoJSON](#plot-gps-data-on-a-map-using-geojson)

## What is Azure maps?

Working with maps is an interesting exercise, and there are many to choose from such as Bing Maps, Leaflet, Open Street Maps, and Google Maps. In this lesson, you will learn about [Azure Maps](https://azure.microsoft.com/services/azure-maps/#azuremaps-overview?WT.mc_id=academic-17441-jabenn) and how they can display your GPS data.

✅ Check out [this video](https://sec.ch9.ms/ch9/d498/3d435d2c-ac85-421b-b3a7-5e0c7630d498/IoT_AzureMaps_high.mp4) on using Azure Maps with IoT.

Azure Maps is "a collection of geospatial services and SDKs that use fresh mapping data to provide geographic context to web and mobile applications." Developers are provided with tools to create beautiful, interactive maps that can do things like provide recommended traffic routes, give information about traffic incidents, indoor navigation, search capabilities, elevation information, weather services and more. 

> ✅ Experiment with some [mapping code samples](https://docs.microsoft.com/samples/browse/?products=azure-maps?WT.mc_id=academic-17441-jabenn)

You can display the maps as a blank canvas, tiles, satellite images, satellite images with roads superimposed, various types of grayscale maps, maps with shaded relief to show elevation, night view maps, and a high contrast map. You can get real-time updates on your maps by integrating them with [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn). You can control the behavior and look of your maps by enabling various controls to allow the map to react to events like pinch, drag, and click. To control the look of your map, you can add layers that include bubbles, lines, polygons, heat maps, and more. Which style of map you implement depends on your choice of SDK.

You can access Azure Maps APIs by leveraging its [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?view=azure-maps-typescript-latest?WT.mc_id=academic-17441-jabenn), its [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn), or, if you are building a mobile app, its [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?pivots=programming-language-java-android?WT.mc_id=academic-17441-jabenn). 

In this lesson, you will use the web SDK to draw a map and display your sensor's GPS location's path.
## Create an Azure Maps resource

Your first step is to create an Azure Maps account. You can do this using the CLI or in the [Azure portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn).

Using the CLI, create a maps account:

```
az maps account create --name
                       --resource-group
                       [--accept-tos]
                       [--sku {S0, S1}]
                       [--subscription]
                       [--tags]
```

Use the `gps-service` resource group you've used in previous lessons. You can use the S0 subscription for this small task.

A sample call would look like this:

```
az maps account create --name MyMapsAccount --resource-group MyResourceGroup --sku S0 --subscription MySubscription
```
The service will deploy. Next, you need to get your Subscription Key. There are two ways to authenticate your maps in a web app: using Active Directory (AD) or 'Shared Key Authentication', also known as Subscription Key. We'll use the latter, for simplicity. 

In the CLI, find your keys:

```
az maps account keys list --name
                          --resource-group
                          [--query-examples]
                          [--subscription]
```
A sample call would look like this: 

```
az maps account keys list --name MyMapsAccount --resource-group MyResourceGroup
```

✅ You will be able to rotate and swap keys at will using the Shared Keys; switch your app to use the Secondary Key while rotating the Primary Key if needed.

## Show a map on a web page

Now you can take the next step which is to display your map on a web page. We will use just one .html file for your small web app; keep in mind that in a production or team environment, your web app will most likely have more moving parts!

1. Create a file called index.html in a folder somewhere on your local computer. Add HTML markup to hold a map:

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

The map will load in the 'myMap' `div`.  A few styles allow it so span the width and height of the page.

2. Under the opening `<head>` tag, add an external style sheet to control the map display, and an external script from the Web SDK to manage its behavior:

```
<link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
<script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
```

3. Under that script, add a script block to launch the map. Add your own subscriptionKey in the init() function:

```javascript
    <script type='text/javascript'>

        function init() {
            var map = new atlas.Map('myMap', {
                center: [-122.26473, 47.73444],
                zoom: 12,
                authOptions: {
                    authType: "subscriptionKey",
                    subscriptionKey: "<your-key-here>",

                }
            });
        }
    </script>
```
If you open your index.html page in a web browser, you should see a map loaded, and focused on the Seattle area. 

![map image](images/map-image.png)

✅ Experiment with the zoom and center parameters to change your map display. You can add different coordinates corresponding to your data's latitude and longitude to re-center the map.

> A better way to work with web apps locally is to install [http-server](https://www.npmjs.com/package/http-server). You will need [node.js](https://nodejs.org/) and [npm](https://www.npmjs.com/) installed before using this tool. Once those tools are installed, you can navigate to the location of your `index.html` file and type `http-server`. The web app will open on a local webserver http://127.0.0.1:8080/.
## The GeoJSON format

Now that you have your web app in place with the map displaying, you need to extract GPS data from your storage and display it in a layer of markers on top of the map. Before we do that, let's look at the [GeoJSON](https://wikipedia.org/wiki/GeoJSON) format that is required by Azure Maps. 

[GeoJSON](https://geojson.org/) is an open standard JSON specification with special formatting designed to handle geographic-specific data. You can learn about it by testing sample data using [geojson.io](geojson.io), which is also a useful tool to debug GeoJSON files. 

Sample GeoJSON data looks like this:

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

Of particular interest is the way the data is nested as a 'Feature' within a 'FeatureCollection'. Within that object can be found 'geometry' with the 'coordinates' indicating latitude and longitude. 

✅ When building your geoJSON, pay attention to the order of 'latitude' and 'longitude' in the object, or your points will not appear where they should! GeoJSON expects data in the order 'lon,lat' for points, not 'lat,lon'.

`Geometry` can have different 'types' designated to that a polygon could be drawn to a map; in this case, a point is drawn with two coordinates designated.

✅ Azure Maps supports standard GeoJSON plus some [enhanced features](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn) including the ability to draw circles and other geometries.
## Plot GPS data on a Map using GeoJSON

Now you are ready to consume data from the storage that you built in the previous lesson. As a reminder, it is stored as a number of files in blob storage so you will need to retrieve the files and parse them so that Azure Maps can use the data.

If you make a call to your storage to fetch the data you might be surprised to see errors occurring in your browser's console. That's because you need to set permissions for [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) on this storage to allow external web apps to read its data. CORS stands for "Cross-Origin Resource Sharing" and usually needs to be set explicitly in Azure for security reasons. Do this using the Azure CLI, adding the name of your storage container and its key. We only need to 'GET' data from this container:

```dotnetcli
az storage cors add --methods GET \
                    --origins "*" \
                    --services b \
                    --account-name <storage_name> \
                    --account-key <key1>
```

1. First, get the endpoint of your storage container. Using the Azure CLI, you can show its information:

```
az storage account blob-service-properties show --account-name
      [--query-examples]
      [--resource-group]
      [--subscription]
```

A typical query would look like:

```
az storage account blob-service-properties show -n mystorageaccount -g MyResourceGroup
```

1. Use that endpoint to build up your init() function. Overwrite the previous function by adding the ability to fetch data:

```javascript
      
      fetch("https://<your-storage-name>.blob.core.windows.net/gps-data/?restype=container&comp=list")
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
                    subscriptionKey: "<your-key>",

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

There are several things happening here. First, you fetch your data from your container using the endpoint you found using the Azure CLI. You parse each file in that blog storage to extract latitude and longitude. Then you initialize a map, adding a bubble layer with the data fetched and saved as source.

1. Add a loadJSON() function to your script block:

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
This function is called by the fetch routine to parse through the JSON data and convert it to be read as longitude and latitude coordinates as geoJSON.
Once parsed, the data is set as part of a geoJSON `Feature`. The map will be initialized and little bubbles will appear around the path your data is plotting:

![data path](images/path.png)

---

## 🚀 Challenge

It's nice to be able to display static data on a map as markers. Can you enhance this web app to add animation and show the path of the markers over time, using the timestamped json files? Here are [some samples](https://azuremapscodesamples.azurewebsites.net/) of using animation within maps.

## Post-lecture quiz

[Post-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/26)

## Review & Self Study

Azure Maps is particularly useful for working with IoT devices. Research some of the uses in the [documentation](https://docs.microsoft.com/en-us/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn). Deepen your knowledge of mapmaking and waypoints [with this Learn module](https://docs.microsoft.com/en-us/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Assignment

[Deploy your app](assignment.md)
