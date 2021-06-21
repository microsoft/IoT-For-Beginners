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

Your first step is to create an Azure Maps account. The easiest way to do this is in the [Azure portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn).

1. After logging in to the portal, click the "Create a resource" button and in the search box that appears, type "Azure Maps".

1. Select "Azure Maps" and click 'Create'.

1. On the Create Azure Maps Account page, enter:

   - Your subscription in the dropdown box.
   - A Resource group to use (create a new one if needed)
   - Add a name for your account
   - Choose a Pricing tier. The Pricing tier for this account. S0 will work for this small project.

1. Read and accept the terms of service, and click the 'Create' button.
   
1. The service will deploy and you can visit it by clicking 'Go to resource' in the next screen.

2. Navigate to your new Azure Maps Account Authentication screen. Here, you discover that you have two ways to authenticate your maps in a web app: using Active Directory (AD) or 'Shared Key Authentication', also known as Subscription Key. We'll use the latter, for simplicity. Copy the Primary Key value and make a note of it!

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
                center: [-122.33, 47.6],
                zoom: 12,
                authOptions: {
                    authType: "subscriptionKey",
                    subscriptionKey: "<your-key-here>",

                }
            });
        }
    </script>
```
If you open your index.html page in a web browser, you should see a map loaded, and focused on Seattle:

![map image](images/map-image.png)

✅ Experiment with the zoom and center parameters to change your map display.

> A better way to work with web apps locally is to install [http-server](https://www.npmjs.com/package/http-server). You will need [node.js](https://nodejs.org/) and [npm](https://www.npmjs.com/) installed before using this tool. Once those tools are installed, you can navigate to the location of your `index.html` file and type `http-server`. The web app will open on a local webserver http://127.0.0.1:8080/.

## The GeoJSON format

Now that you have your web app in place with the map displaying, you need to extract GPS data from your storage and display it in a layer of markers on top of the map. Before we do that, let's look at the [GeoJSON](https://wikipedia.org/wiki/GeoJSON) format that is required by Azure Maps. 

[GeoJSON](https://geojson.org/) is an open standard JSON specification with special formatting designed to hande geographic-specific data. You can learn about it by testing sample data using [geojson.io](geojson.io), which is also a useful tool to debug GeoJSON files. 

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

Of particular interest is the way the data is nested as a 'FeatureCollection'. Within that object can be found 'geometry' with the 'coordinates' indicating latitude and longitude. Geometry can have different 'types' designated to that a polygon could be drawn to a map; in this case, a point is drawn with two coordinates designated.

✅ Azure Maps supports standard GeoJSON plus some [enhanced features](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn) including the ability to draw circles and other geometries.
## Plot GPS data on a Map using GeoJSON

Now you are ready to consume data from the storage that you built in the previous lesson. As a reminder, it is stored as a number of files in blob storage so you will need to retrieve the files and parse them so that Azure Maps can use the data. 

---

## 🚀 Challenge

It's nice to be able to display static data on a map as markers. Can you enhance this web app to add animation and show the path of the markers over time, using the timestamped json files?

## Post-lecture quiz

[Post-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/26)

## Review & Self Study

## Assignment

[Deploy your app](assignment.md)
