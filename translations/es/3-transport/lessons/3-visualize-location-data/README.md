<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-26T15:52:17+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "es"
}
-->
# Visualizar datos de ubicación

![Resumen visual de esta lección](../../../../../translated_images/es/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> Dibujo por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para verla en mayor tamaño.

Este video ofrece una visión general de Azure Maps con IoT, un servicio que se cubrirá en esta lección.

[![Azure Maps - La plataforma de ubicación empresarial de Microsoft Azure](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Haz clic en la imagen de arriba para ver el video

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Introducción

En la lección anterior aprendiste cómo obtener datos GPS de tus sensores y guardarlos en la nube en un contenedor de almacenamiento utilizando código sin servidor. Ahora descubrirás cómo visualizar esos puntos en un mapa de Azure. Aprenderás a crear un mapa en una página web, conocer el formato de datos GeoJSON y cómo usarlo para trazar todos los puntos GPS capturados en tu mapa.

En esta lección cubriremos:

* [¿Qué es la visualización de datos?](../../../../../3-transport/lessons/3-visualize-location-data)
* [Servicios de mapas](../../../../../3-transport/lessons/3-visualize-location-data)
* [Crear un recurso de Azure Maps](../../../../../3-transport/lessons/3-visualize-location-data)
* [Mostrar un mapa en una página web](../../../../../3-transport/lessons/3-visualize-location-data)
* [El formato GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)
* [Trazar datos GPS en un mapa usando GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Esta lección incluirá una pequeña cantidad de HTML y JavaScript. Si deseas aprender más sobre desarrollo web con HTML y JavaScript, consulta [Desarrollo web para principiantes](https://github.com/microsoft/Web-Dev-For-Beginners).

## ¿Qué es la visualización de datos?

La visualización de datos, como su nombre lo indica, consiste en representar datos de manera visual para que sean más fáciles de entender para los humanos. Generalmente se asocia con gráficos y tablas, pero en realidad es cualquier forma de representar datos de manera pictórica para ayudar a las personas a comprenderlos mejor y tomar decisiones.

Tomemos un ejemplo simple: en el proyecto de la granja capturaste datos de humedad del suelo. Una tabla con los datos de humedad del suelo capturados cada hora el 1 de junio de 2021 podría verse así:

| Fecha            | Lectura |
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

Para un humano, entender estos datos puede ser complicado. Es una pared de números sin mucho significado. Como primer paso para visualizar estos datos, se pueden trazar en un gráfico de líneas:

![Un gráfico de líneas con los datos anteriores](../../../../../translated_images/es/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

Esto se puede mejorar aún más añadiendo una línea que indique cuándo se activó el sistema de riego automático al alcanzar una lectura de humedad del suelo de 450:

![Un gráfico de líneas de humedad del suelo con una línea en 450](../../../../../translated_images/es/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

Este gráfico muestra rápidamente no solo los niveles de humedad del suelo, sino también los puntos donde se activó el sistema de riego.

Los gráficos no son la única herramienta para visualizar datos. Los dispositivos IoT que rastrean el clima pueden tener aplicaciones web o móviles que visualizan las condiciones climáticas usando símbolos, como un ícono de nube para días nublados, un ícono de lluvia para días lluviosos, y así sucesivamente. Hay una gran variedad de formas de visualizar datos, algunas serias, otras divertidas.

✅ Piensa en las formas en que has visto datos visualizados. ¿Qué métodos te han parecido más claros y te han permitido tomar decisiones más rápidamente?

Las mejores visualizaciones permiten a los humanos tomar decisiones rápidamente. Por ejemplo, tener una pared llena de indicadores con todo tipo de lecturas de maquinaria industrial es difícil de procesar, pero una luz roja parpadeante cuando algo va mal permite a una persona tomar una decisión. ¡A veces la mejor visualización es una luz parpadeante!

Cuando se trabaja con datos GPS, la visualización más clara puede ser trazar los datos en un mapa. Un mapa que muestre camiones de reparto, por ejemplo, puede ayudar a los trabajadores de una planta de procesamiento a ver cuándo llegarán los camiones. Si este mapa muestra más que solo imágenes de camiones en sus ubicaciones actuales, como el contenido de un camión, los trabajadores pueden planificar en consecuencia. Por ejemplo, si ven un camión refrigerado cerca, saben que deben preparar espacio en un frigorífico.

## Servicios de mapas

Trabajar con mapas es un ejercicio interesante, y hay muchas opciones disponibles como Bing Maps, Leaflet, Open Street Maps y Google Maps. En esta lección, aprenderás sobre [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) y cómo pueden mostrar tus datos GPS.

![El logotipo de Azure Maps](../../../../../translated_images/es/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps es "una colección de servicios geoespaciales y SDKs que utilizan datos de mapas actualizados para proporcionar contexto geográfico a aplicaciones web y móviles". Los desarrolladores cuentan con herramientas para crear mapas hermosos e interactivos que pueden hacer cosas como proporcionar rutas de tráfico recomendadas, información sobre incidentes de tráfico, navegación en interiores, capacidades de búsqueda, información de elevación, servicios meteorológicos y más.

✅ Experimenta con algunos [ejemplos de código de mapas](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Puedes mostrar los mapas como un lienzo en blanco, mosaicos, imágenes satelitales, imágenes satelitales con carreteras superpuestas, varios tipos de mapas en escala de grises, mapas con relieve sombreado para mostrar elevaciones, mapas nocturnos y mapas de alto contraste. Puedes obtener actualizaciones en tiempo real en tus mapas integrándolos con [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn). Puedes controlar el comportamiento y la apariencia de tus mapas habilitando varios controles para que el mapa reaccione a eventos como pellizcar, arrastrar y hacer clic. Para controlar la apariencia de tu mapa, puedes agregar capas que incluyan burbujas, líneas, polígonos, mapas de calor y más. El estilo de mapa que implementes dependerá de tu elección de SDK.

Puedes acceder a las APIs de Azure Maps utilizando su [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), su [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn) o, si estás desarrollando una aplicación móvil, su [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android).

En esta lección, usarás el Web SDK para dibujar un mapa y mostrar la ruta de ubicación GPS de tu sensor.

## Crear un recurso de Azure Maps

El primer paso es crear una cuenta de Azure Maps.

### Tarea - crear un recurso de Azure Maps

1. Ejecuta el siguiente comando desde tu Terminal o Command Prompt para crear un recurso de Azure Maps en tu grupo de recursos `gps-sensor`:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Esto creará un recurso de Azure Maps llamado `gps-sensor`. El nivel utilizado es `S1`, que es un nivel de pago que incluye una variedad de características, pero con una cantidad generosa de llamadas gratuitas.

    > 💁 Para ver el costo de usar Azure Maps, consulta la [página de precios de Azure Maps](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Necesitarás una clave API para el recurso de mapas. Usa el siguiente comando para obtener esta clave:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Copia el valor de `PrimaryKey`.

## Mostrar un mapa en una página web

Ahora puedes dar el siguiente paso, que es mostrar tu mapa en una página web. Usaremos solo un archivo `html` para tu pequeña aplicación web; ten en cuenta que en un entorno de producción o en equipo, tu aplicación web probablemente tendrá más partes móviles.

### Tarea - mostrar un mapa en una página web

1. Crea un archivo llamado index.html en una carpeta en tu computadora local. Agrega el marcado HTML para contener un mapa:

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

    El mapa se cargará en el `div` llamado `myMap`. Algunos estilos permiten que ocupe el ancho y alto de la página.

    > 🎓 Un `div` es una sección de una página web que puede ser nombrada y estilizada.

1. Bajo la etiqueta de apertura `<head>`, agrega una hoja de estilo externa para controlar la visualización del mapa y un script externo del Web SDK para gestionar su comportamiento:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Esta hoja de estilo contiene las configuraciones de cómo se ve el mapa, y el archivo de script contiene el código para cargar el mapa. Agregar este código es similar a incluir archivos de cabecera en C++ o importar módulos en Python.

1. Bajo ese script, agrega un bloque de script para iniciar el mapa.

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

    Reemplaza `<subscription_key>` con la clave API de tu cuenta de Azure Maps.

    Si abres tu archivo `index.html` en un navegador web, deberías ver un mapa cargado y centrado en el área de Seattle.

    ![Un mapa que muestra Seattle, una ciudad en el estado de Washington, EE. UU.](../../../../../translated_images/es/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ Experimenta con los parámetros de zoom y centro para cambiar la visualización de tu mapa. Puedes agregar diferentes coordenadas correspondientes a la latitud y longitud de tus datos para re-centrar el mapa.

> 💁 Una mejor manera de trabajar con aplicaciones web localmente es instalar [http-server](https://www.npmjs.com/package/http-server). Necesitarás tener [node.js](https://nodejs.org/) y [npm](https://www.npmjs.com/) instalados antes de usar esta herramienta. Una vez que estas herramientas estén instaladas, puedes navegar a la ubicación de tu archivo `index.html` y escribir `http-server`. La aplicación web se abrirá en un servidor web local [http://127.0.0.1:8080/](http://127.0.0.1:8080/).

## El formato GeoJSON

Ahora que tienes tu aplicación web en funcionamiento con el mapa mostrado, necesitas extraer datos GPS de tu cuenta de almacenamiento y mostrarlos en una capa de marcadores sobre el mapa. Antes de hacer eso, echemos un vistazo al formato [GeoJSON](https://wikipedia.org/wiki/GeoJSON) que requiere Azure Maps.

[GeoJSON](https://geojson.org/) es un estándar abierto de especificación JSON con un formato especial diseñado para manejar datos específicos geográficos. Puedes aprender sobre él probando datos de ejemplo usando [geojson.io](https://geojson.io), que también es una herramienta útil para depurar archivos GeoJSON.

Los datos de ejemplo de GeoJSON se ven así:

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

De particular interés es la forma en que los datos están anidados como un `Feature` dentro de un `FeatureCollection`. Dentro de ese objeto se encuentra `geometry` con las `coordinates` que indican latitud y longitud.

✅ Al construir tu GeoJSON, presta atención al orden de `latitude` y `longitude` en el objeto, o tus puntos no aparecerán donde deberían. GeoJSON espera datos en el orden `lon,lat` para puntos, no `lat,lon`.

`Geometry` puede tener diferentes tipos, como un solo punto o un polígono. En este ejemplo, es un punto con dos coordenadas especificadas: la longitud y la latitud.
✅ Azure Maps admite GeoJSON estándar además de algunas [funciones mejoradas](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn), incluyendo la capacidad de dibujar círculos y otras geometrías.

## Representar datos GPS en un mapa usando GeoJSON

Ahora estás listo para consumir los datos del almacenamiento que creaste en la lección anterior. Como recordatorio, los datos están almacenados en varios archivos en un almacenamiento de blobs, por lo que necesitarás recuperar los archivos y analizarlos para que Azure Maps pueda utilizarlos.

### Tarea - configurar el almacenamiento para ser accesible desde una página web

Si haces una llamada a tu almacenamiento para obtener los datos, podrías sorprenderte al ver errores en la consola de tu navegador. Esto se debe a que necesitas configurar los permisos de [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) en este almacenamiento para permitir que aplicaciones web externas lean sus datos.

> 🎓 CORS significa "Intercambio de Recursos de Origen Cruzado" y generalmente necesita configurarse explícitamente en Azure por razones de seguridad. Esto evita que sitios no esperados puedan acceder a tus datos.

1. Ejecuta el siguiente comando para habilitar CORS:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Sustituye `<storage_name>` por el nombre de tu cuenta de almacenamiento. Sustituye `<key1>` por la clave de cuenta de tu almacenamiento.

    Este comando permite que cualquier sitio web (el comodín `*` significa cualquiera) realice una solicitud *GET*, es decir, obtenga datos de tu cuenta de almacenamiento. El parámetro `--services b` significa que esta configuración solo se aplica a los blobs.

### Tarea - cargar los datos GPS desde el almacenamiento

1. Sustituye todo el contenido de la función `init` con el siguiente código:

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

    Sustituye `<storage_name>` por el nombre de tu cuenta de almacenamiento. Sustituye `<subscription_key>` por la clave API de tu cuenta de Azure Maps.

    Aquí están ocurriendo varias cosas. Primero, el código recupera tus datos GPS desde tu contenedor de blobs utilizando un endpoint URL construido con el nombre de tu cuenta de almacenamiento. Esta URL recupera desde `gps-data`, indicando que el tipo de recurso es un contenedor (`restype=container`), y lista información sobre todos los blobs. Esta lista no devolverá los blobs en sí, pero proporcionará una URL para cada blob que puede ser utilizada para cargar los datos del blob.

    > 💁 Puedes poner esta URL en tu navegador para ver detalles de todos los blobs en tu contenedor. Cada elemento tendrá una propiedad `Url` que también puedes cargar en tu navegador para ver el contenido del blob.

    Este código luego carga cada blob, llamando a una función `loadJSON`, que será creada a continuación. Luego crea el control del mapa y agrega código al evento `ready`. Este evento se llama cuando el mapa se muestra en la página web.

    El evento `ready` crea una fuente de datos de Azure Maps: un contenedor que contiene datos GeoJSON que se poblarán más adelante. Esta fuente de datos luego se utiliza para crear una capa de burbujas, es decir, un conjunto de círculos en el mapa centrados en cada punto del GeoJSON.

1. Agrega la función `loadJSON` a tu bloque de script, debajo de la función `init`:

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

    Esta función es llamada por la rutina de recuperación para analizar los datos JSON y convertirlos en coordenadas de longitud y latitud como GeoJSON. 
    Una vez analizados, los datos se configuran como parte de una `Feature` de GeoJSON. El mapa se inicializará y aparecerán pequeñas burbujas alrededor del camino que tus datos están trazando:

1. Carga la página HTML en tu navegador. Se cargará el mapa, luego se cargarán todos los datos GPS desde el almacenamiento y se representarán en el mapa.

    ![Un mapa del parque estatal Saint Edward cerca de Seattle, con círculos mostrando un camino alrededor del borde del parque](../../../../../translated_images/es/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 Puedes encontrar este código en la [carpeta de código](../../../../../3-transport/lessons/3-visualize-location-data/code).

---

## 🚀 Desafío

Es genial poder mostrar datos estáticos en un mapa como marcadores. ¿Puedes mejorar esta aplicación web para agregar animación y mostrar el recorrido de los marcadores a lo largo del tiempo, utilizando los archivos JSON con marcas de tiempo? Aquí tienes [algunos ejemplos](https://azuremapscodesamples.azurewebsites.net/) de cómo usar animaciones en mapas.

## Cuestionario posterior a la lección

[Cuestionario posterior a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Revisión y autoestudio

Azure Maps es particularmente útil para trabajar con dispositivos IoT.

* Investiga algunos de los usos en la [documentación de Azure Maps en Microsoft docs](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Profundiza tu conocimiento sobre la creación de mapas y puntos de referencia con el [módulo de aprendizaje autodirigido sobre cómo crear tu primera aplicación de búsqueda de rutas con Azure Maps en Microsoft Learn](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Tarea

[Despliega tu aplicación](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.