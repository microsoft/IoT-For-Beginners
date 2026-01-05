<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-26T15:44:11+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "es"
}
-->
# Geocercas

![Una vista general de esta lección en formato sketchnote](../../../../../translated_images/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.es.jpg)

> Sketchnote por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

Este video ofrece una vista general de las geocercas y cómo utilizarlas en Azure Maps, temas que se cubrirán en esta lección:

[![Geocercas con Azure Maps en el programa Microsoft Developer IoT](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Haz clic en la imagen de arriba para ver el video

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Introducción

En las últimas 3 lecciones, has utilizado IoT para localizar los camiones que transportan tus productos desde tu granja hasta un centro de procesamiento. Has capturado datos GPS, los has enviado a la nube para almacenarlos y los has visualizado en un mapa. El siguiente paso para aumentar la eficiencia de tu cadena de suministro es recibir una alerta cuando un camión esté a punto de llegar al centro de procesamiento, de modo que el equipo necesario para descargar pueda estar listo con montacargas y otros equipos tan pronto como el vehículo llegue. De esta manera, pueden descargar rápidamente y no estarás pagando por un camión y conductor que estén esperando.

En esta lección aprenderás sobre las geocercas: regiones geoespaciales definidas, como un área dentro de un radio de 2 km alrededor de un centro de procesamiento, y cómo probar si las coordenadas GPS están dentro o fuera de una geocerca, para que puedas saber si tu sensor GPS ha llegado o salido de un área.

En esta lección cubriremos:

* [Qué son las geocercas](../../../../../3-transport/lessons/4-geofences)
* [Definir una geocerca](../../../../../3-transport/lessons/4-geofences)
* [Probar puntos contra una geocerca](../../../../../3-transport/lessons/4-geofences)
* [Usar geocercas desde código sin servidor](../../../../../3-transport/lessons/4-geofences)

> 🗑 Esta es la última lección de este proyecto, así que después de completar esta lección y la tarea, no olvides limpiar tus servicios en la nube. Necesitarás los servicios para completar la tarea, así que asegúrate de completar eso primero.
>
> Consulta [la guía para limpiar tu proyecto](../../../clean-up.md) si necesitas instrucciones sobre cómo hacerlo.

## Qué son las geocercas

Una geocerca es un perímetro virtual para una región geográfica del mundo real. Las geocercas pueden ser círculos definidos como un punto y un radio (por ejemplo, un círculo de 100m alrededor de un edificio), o un polígono que cubre un área como una zona escolar, límites de una ciudad, o un campus universitario o de oficinas.

![Algunos ejemplos de geocercas mostrando una geocerca circular alrededor de la tienda de Microsoft y una geocerca poligonal alrededor del campus oeste de Microsoft](../../../../../translated_images/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.es.png)

> 💁 Puede que ya hayas usado geocercas sin saberlo. Si has configurado un recordatorio usando la aplicación de recordatorios de iOS o Google Keep basado en una ubicación, has utilizado una geocerca. Estas aplicaciones configuran una geocerca basada en la ubicación dada y te alertan cuando tu teléfono entra en la geocerca.

Hay muchas razones por las que querrías saber si un vehículo está dentro o fuera de una geocerca:

* Preparación para la descarga: recibir una notificación de que un vehículo ha llegado al sitio permite que el equipo esté preparado para descargar el vehículo, reduciendo el tiempo de espera del vehículo. Esto puede permitir que un conductor haga más entregas en un día con menos tiempo de espera.
* Cumplimiento fiscal: algunos países, como Nueva Zelanda, cobran impuestos de carretera para vehículos diésel basados en el peso del vehículo cuando circulan solo por carreteras públicas. Usar geocercas permite rastrear el kilometraje recorrido en carreteras públicas en lugar de privadas, como granjas o áreas de tala.
* Monitoreo de robos: si un vehículo solo debe permanecer en un área específica, como una granja, y sale de la geocerca, podría haber sido robado.
* Cumplimiento de ubicación: algunas partes de un sitio de trabajo, granja o fábrica pueden estar fuera de los límites para ciertos vehículos, como mantener vehículos que transportan fertilizantes artificiales y pesticidas lejos de campos que cultivan productos orgánicos. Si se entra en una geocerca, entonces un vehículo está fuera de cumplimiento y se puede notificar al conductor.

✅ ¿Puedes pensar en otros usos para las geocercas?

Azure Maps, el servicio que utilizaste en la última lección para visualizar datos GPS, te permite definir geocercas y luego probar si un punto está dentro o fuera de la geocerca.

## Definir una geocerca

Las geocercas se definen utilizando GeoJSON, igual que los puntos que se agregaron al mapa en la lección anterior. En este caso, en lugar de ser una `FeatureCollection` de valores `Point`, es una `FeatureCollection` que contiene un `Polygon`.

```json
{
   "type": "FeatureCollection",
   "features": [
     {
       "type": "Feature",
       "geometry": {
         "type": "Polygon",
         "coordinates": [
           [
             [
               -122.13393688201903,
               47.63829579223815
             ],
             [
               -122.13389128446579,
               47.63782047131512
             ],
             [
               -122.13240802288054,
               47.63783312249837
             ],
             [
               -122.13238388299942,
               47.63829037035086
             ],
             [
               -122.13393688201903,
               47.63829579223815
             ]
           ]
         ]
       },
       "properties": {
         "geometryId": "1"
       }
     }
   ]
}
```

Cada punto en el polígono se define como un par de longitud y latitud en un arreglo, y estos puntos están en un arreglo que se establece como las `coordinates`. En un `Point` en la lección anterior, las `coordinates` eran un arreglo que contenía 2 valores, latitud y longitud. Para un `Polygon`, es un arreglo de arreglos que contiene 2 valores, longitud y latitud.

> 💁 Recuerda, GeoJSON utiliza `longitud, latitud` para los puntos, no `latitud, longitud`.

El arreglo de coordenadas del polígono siempre tiene 1 entrada más que el número de puntos en el polígono, siendo la última entrada igual a la primera, cerrando el polígono. Por ejemplo, para un rectángulo habría 5 puntos.

![Un rectángulo con coordenadas](../../../../../translated_images/polygon-points.302193da381cb415.es.png)

En la imagen de arriba, hay un rectángulo. Las coordenadas del polígono comienzan en la esquina superior izquierda en 47,-122, luego se mueven hacia la derecha a 47,-121, luego hacia abajo a 46,-121, luego hacia la izquierda a 46,-122, y finalmente de vuelta al punto inicial en 47,-122. Esto da al polígono 5 puntos: superior izquierda, superior derecha, inferior derecha, inferior izquierda y nuevamente superior izquierda para cerrarlo.

✅ Intenta crear un polígono GeoJSON alrededor de tu casa o escuela. Usa una herramienta como [GeoJSON.io](https://geojson.io/).

### Tarea - definir una geocerca

Para usar una geocerca en Azure Maps, primero debe cargarse en tu cuenta de Azure Maps. Una vez cargada, obtendrás un ID único que puedes usar para probar un punto contra la geocerca. Para cargar geocercas en Azure Maps, necesitas usar la API web de mapas. Puedes llamar a la API web de Azure Maps utilizando una herramienta llamada [curl](https://curl.se).

> 🎓 Curl es una herramienta de línea de comandos para realizar solicitudes contra puntos finales web.

1. Si estás usando Linux, macOS o una versión reciente de Windows 10, probablemente ya tengas curl instalado. Ejecuta lo siguiente desde tu terminal o línea de comandos para verificar:

    ```sh
    curl --version
    ```

    Si no ves información de versión para curl, necesitarás instalarlo desde la [página de descargas de curl](https://curl.se/download.html).

    > 💁 Si tienes experiencia con Postman, puedes usarlo en su lugar si lo prefieres.

1. Crea un archivo GeoJSON que contenga un polígono. Lo probarás utilizando tu sensor GPS, así que crea un polígono alrededor de tu ubicación actual. Puedes crearlo manualmente editando el ejemplo de GeoJSON dado arriba o usar una herramienta como [GeoJSON.io](https://geojson.io/).

    El GeoJSON necesitará contener una `FeatureCollection`, que contenga una `Feature` con una `geometry` de tipo `Polygon`.

    También **DEBES** agregar un elemento `properties` al mismo nivel que el elemento `geometry`, y este debe contener un `geometryId`:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Si usas [GeoJSON.io](https://geojson.io/), tendrás que agregar manualmente este elemento al elemento `properties` vacío, ya sea después de descargar el archivo JSON o en el editor JSON de la aplicación.

    Este `geometryId` debe ser único en este archivo. Puedes cargar múltiples geocercas como múltiples `Features` en la `FeatureCollection` en el mismo archivo GeoJSON, siempre que cada una tenga un `geometryId` diferente. Los polígonos pueden tener el mismo `geometryId` si se cargan desde un archivo diferente en un momento diferente.

1. Guarda este archivo como `geofence.json` y navega a donde está guardado en tu terminal o consola.

1. Ejecuta el siguiente comando curl para crear la geocerca:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Reemplaza `<subscription_key>` en la URL con la clave API de tu cuenta de Azure Maps.

    La URL se utiliza para cargar datos de mapas a través de la API `https://atlas.microsoft.com/mapData/upload`. La llamada incluye un parámetro `api-version` para especificar qué API de Azure Maps usar, esto es para permitir que la API cambie con el tiempo pero mantenga compatibilidad hacia atrás. El formato de datos que se carga se establece como `geojson`.

    Esto ejecutará la solicitud POST a la API de carga y devolverá una lista de encabezados de respuesta que incluye un encabezado llamado `location`.

    ```output
    content-type: application/json
    location: https://us.atlas.microsoft.com/mapData/operations/1560ced6-3a80-46f2-84b2-5b1531820eab?api-version=1.0
    x-ms-azuremaps-region: West US 2
    x-content-type-options: nosniff
    strict-transport-security: max-age=31536000; includeSubDomains
    x-cache: CONFIG_NOCACHE
    date: Sat, 22 May 2021 21:34:57 GMT
    content-length: 0
    ```

    > 🎓 Al llamar a un punto final web, puedes pasar parámetros a la llamada agregando un `?` seguido de pares clave-valor como `key=value`, separando los pares clave-valor con un `&`.

1. Azure Maps no procesa esto de inmediato, por lo que necesitarás verificar si la solicitud de carga ha terminado utilizando la URL dada en el encabezado `location`. Haz una solicitud GET a esta ubicación para ver el estado. Necesitarás agregar tu clave de suscripción al final de la URL `location` agregando `&subscription-key=<subscription_key>` al final, reemplazando `<subscription_key>` con la clave API de tu cuenta de Azure Maps. Ejecuta el siguiente comando:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Reemplaza `<location>` con el valor del encabezado `location` y `<subscription_key>` con la clave API de tu cuenta de Azure Maps.

1. Verifica el valor de `status` en la respuesta. Si no es `Succeeded`, espera un minuto e intenta nuevamente.

1. Una vez que el estado regrese como `Succeeded`, observa el `resourceLocation` de la respuesta. Esto contiene detalles sobre el ID único (conocido como UDID) para el objeto GeoJSON. El UDID es el valor después de `metadata/`, y no incluye el `api-version`. Por ejemplo, si el `resourceLocation` fuera:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    Entonces el UDID sería `7c3776eb-da87-4c52-ae83-caadf980323a`.

    Guarda una copia de este UDID ya que lo necesitarás para probar la geocerca.

## Probar puntos contra una geocerca

Una vez que el polígono se ha cargado en Azure Maps, puedes probar un punto para ver si está dentro o fuera de la geocerca. Esto se hace realizando una solicitud a la API web, pasando el UDID de la geocerca y la latitud y longitud del punto a probar.

Cuando realizas esta solicitud, también puedes pasar un valor llamado `searchBuffer`. Esto indica a la API de Maps qué tan precisa debe ser al devolver resultados. La razón de esto es que el GPS no es perfectamente preciso y, a veces, las ubicaciones pueden estar desviadas por metros o más. El valor predeterminado para el search buffer es de 50m, pero puedes establecer valores de 0m a 500m.

Cuando se devuelven los resultados de la llamada a la API, una de las partes del resultado es una `distance` medida al punto más cercano en el borde de la geocerca, con un valor positivo si el punto está fuera de la geocerca y negativo si está dentro de la geocerca. Si esta distancia es menor que el search buffer, se devuelve la distancia real en metros; de lo contrario, el valor es 999 o -999. 999 significa que el punto está fuera de la geocerca por más del search buffer, -999 significa que está dentro de la geocerca por más del search buffer.

![Una geocerca con un search buffer de 50m alrededor](../../../../../translated_images/search-buffer-and-distance.e6a79af3898183c7.es.png)

En la imagen de arriba, la geocerca tiene un search buffer de 50m.

* Un punto en el centro de la geocerca, bien dentro del search buffer, tiene una distancia de **-999**.
* Un punto bien fuera del search buffer tiene una distancia de **999**.
* Un punto dentro de la geocerca y dentro del search buffer, a 6m de la geocerca, tiene una distancia de **6m**.
* Un punto fuera de la geocerca y dentro del search buffer, a 39m de la geocerca, tiene una distancia de **39m**.

Es importante conocer la distancia al borde de la geocerca y combinar esto con otra información, como otras lecturas de GPS, velocidad y datos de carreteras, al tomar decisiones basadas en la ubicación de un vehículo.

Por ejemplo, imagina lecturas de GPS que muestran que un vehículo estaba conduciendo por una carretera que termina corriendo junto a una geocerca. Si un único valor de GPS es inexacto y coloca el vehículo dentro de la geocerca, a pesar de que no hay acceso vehicular, entonces puede ignorarse.

![Un rastro de GPS mostrando un vehículo pasando por el campus de Microsoft en la 520, con lecturas de GPS a lo largo de la carretera excepto una en el campus, dentro de una geocerca](../../../../../translated_images/geofence-crossing-inaccurate-gps.6a3ed911202ad9cabb66d3964888cec03a42c61d5b8f536ad5bdc99716b370f5.es.png)
En la imagen anterior, hay una geocerca sobre parte del campus de Microsoft. La línea roja muestra un camión conduciendo a lo largo de la 520, con círculos que representan las lecturas de GPS. La mayoría de estas son precisas y están a lo largo de la 520, con una lectura inexacta dentro de la geocerca. No hay forma de que esa lectura sea correcta: no hay carreteras para que el camión se desvíe repentinamente de la 520 hacia el campus y luego regrese a la 520. El código que verifica esta geocerca necesitará tomar en cuenta las lecturas previas antes de actuar sobre los resultados de la prueba de la geocerca.

✅ ¿Qué datos adicionales necesitarías verificar para determinar si una lectura de GPS puede considerarse correcta?

### Tarea - probar puntos contra una geocerca

1. Comienza construyendo la URL para la consulta de la API web. El formato es:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Reemplaza `<subscription_key>` con la clave de API de tu cuenta de Azure Maps.

    Reemplaza `<UDID>` con el UDID de la geocerca de la tarea anterior.

    Reemplaza `<lat>` y `<lon>` con la latitud y longitud que deseas probar.

    Esta URL utiliza la API `https://atlas.microsoft.com/spatial/geofence/json` para consultar una geocerca definida usando GeoJSON. Apunta a la versión de API `1.0`. El parámetro `deviceId` es obligatorio y debe ser el nombre del dispositivo del que provienen la latitud y longitud.

    El búfer de búsqueda predeterminado es de 50m, y puedes cambiarlo pasando un parámetro adicional de `searchBuffer=<distance>`, configurando `<distance>` como la distancia del búfer de búsqueda en metros, de 0 a 500.

1. Usa curl para realizar una solicitud GET a esta URL:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Si obtienes un código de respuesta de `BadRequest`, con un error de:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > entonces tu GeoJSON está perdiendo la sección `properties` con el `geometryId`. Necesitarás corregir tu GeoJSON, luego repetir los pasos anteriores para volver a cargarlo y obtener un nuevo UDID.

1. La respuesta contendrá una lista de `geometries`, una para cada polígono definido en el GeoJSON utilizado para crear la geocerca. Cada geometría tiene 3 campos de interés: `distance`, `nearestLat` y `nearestLon`.

    ```output
    {
        "geometries": [
            {
                "deviceId": "gps-sensor",
                "udId": "7c3776eb-da87-4c52-ae83-caadf980323a",
                "geometryId": "1",
                "distance": 999.0,
                "nearestLat": 47.645875,
                "nearestLon": -122.142713
            }
        ],
        "expiredGeofenceGeometryId": [],
        "invalidPeriodGeofenceGeometryId": []
    }
    ```

    * `nearestLat` y `nearestLon` son la latitud y longitud de un punto en el borde de la geocerca que está más cerca de la ubicación que se está probando.

    * `distance` es la distancia desde la ubicación que se está probando hasta el punto más cercano en el borde de la geocerca. Los números negativos significan dentro de la geocerca, los positivos fuera. Este valor será menor que 50 (el búfer de búsqueda predeterminado), o 999.

1. Repite esto varias veces con ubicaciones dentro y fuera de la geocerca.

## Usar geocercas desde código sin servidor

Ahora puedes agregar un nuevo disparador a tu aplicación de Functions para probar los datos de eventos GPS del IoT Hub contra la geocerca.

### Grupos de consumidores

Como recordarás de lecciones anteriores, el IoT Hub te permitirá reproducir eventos que han sido recibidos por el hub pero no procesados. Pero, ¿qué pasaría si se conectaran múltiples disparadores? ¿Cómo sabrá cuál ha procesado qué eventos?

La respuesta es que no puede. En su lugar, puedes definir múltiples conexiones separadas para leer eventos, y cada una puede gestionar la reproducción de mensajes no leídos. Estos se llaman *grupos de consumidores*. Cuando te conectas al punto de conexión, puedes especificar a qué grupo de consumidores deseas conectarte. Cada componente de tu aplicación se conectará a un grupo de consumidores diferente.

![Un IoT Hub con 3 grupos de consumidores distribuyendo los mismos mensajes a 3 diferentes aplicaciones de Functions](../../../../../translated_images/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.es.png)

En teoría, hasta 5 aplicaciones pueden conectarse a cada grupo de consumidores, y todas recibirán mensajes cuando lleguen. Es una buena práctica tener solo una aplicación accediendo a cada grupo de consumidores para evitar el procesamiento duplicado de mensajes y asegurarse de que, al reiniciar, todos los mensajes en cola se procesen correctamente. Por ejemplo, si lanzas tu aplicación de Functions localmente además de ejecutarla en la nube, ambas procesarían mensajes, lo que llevaría a blobs duplicados almacenados en la cuenta de almacenamiento.

Si revisas el archivo `function.json` para el disparador del IoT Hub que creaste en una lección anterior, verás el grupo de consumidores en la sección de enlace del disparador del Event Hub:

```json
"consumerGroup": "$Default"
```

Cuando creas un IoT Hub, obtienes el grupo de consumidores `$Default` creado por defecto. Si deseas agregar un disparador adicional, puedes hacerlo usando un nuevo grupo de consumidores.

> 💁 En esta lección, usarás una función diferente para probar la geocerca a la utilizada para almacenar los datos de GPS. Esto es para mostrar cómo usar grupos de consumidores y separar el código para hacerlo más fácil de leer y entender. En una aplicación de producción hay muchas formas en que podrías diseñar esto: poner ambos en una función, usar un disparador en la cuenta de almacenamiento para ejecutar una función para verificar la geocerca, o usar múltiples funciones. No hay una "forma correcta", depende del resto de tu aplicación y tus necesidades.

### Tarea - crear un nuevo grupo de consumidores

1. Ejecuta el siguiente comando para crear un nuevo grupo de consumidores llamado `geofence` para tu IoT Hub:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Reemplaza `<hub_name>` con el nombre que usaste para tu IoT Hub.

1. Si deseas ver todos los grupos de consumidores para un IoT Hub, ejecuta el siguiente comando:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Reemplaza `<hub_name>` con el nombre que usaste para tu IoT Hub. Esto listará todos los grupos de consumidores.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Cuando ejecutaste el monitor de eventos del IoT Hub en una lección anterior, se conectó al grupo de consumidores `$Default`. Por esta razón, no puedes ejecutar el monitor de eventos y un disparador de eventos. Si deseas ejecutar ambos, entonces puedes usar otros grupos de consumidores para todas tus aplicaciones de Functions y mantener `$Default` para el monitor de eventos.

### Tarea - crear un nuevo disparador del IoT Hub

1. Agrega un nuevo disparador de eventos del IoT Hub a tu aplicación de función `gps-trigger` que creaste en una lección anterior. Llama a esta función `geofence-trigger`.

    > ⚠️ Puedes consultar [las instrucciones para crear un disparador de eventos del IoT Hub del proyecto 2, lección 5 si es necesario](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Configura la cadena de conexión del IoT Hub en el archivo `function.json`. El archivo `local.settings.json` se comparte entre todos los disparadores en la aplicación de Functions.

1. Actualiza el valor de `consumerGroup` en el archivo `function.json` para referenciar el nuevo grupo de consumidores `geofence`:

    ```json
    "consumerGroup": "geofence"
    ```

1. Necesitarás usar la clave de suscripción para tu cuenta de Azure Maps en este disparador, así que agrega una nueva entrada al archivo `local.settings.json` llamada `MAPS_KEY`.

1. Ejecuta la aplicación de Functions para asegurarte de que se está conectando y procesando mensajes. El `iot-hub-trigger` de la lección anterior también se ejecutará y cargará blobs en el almacenamiento.

    > Para evitar lecturas duplicadas de GPS en el almacenamiento de blobs, puedes detener la aplicación de Functions que tienes ejecutándose en la nube. Para hacerlo, usa el siguiente comando:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Reemplaza `<functions_app_name>` con el nombre que usaste para tu aplicación de Functions.
    >
    > Puedes reiniciarla más tarde con el siguiente comando:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Reemplaza `<functions_app_name>` con el nombre que usaste para tu aplicación de Functions.

### Tarea - probar la geocerca desde el disparador

Anteriormente en esta lección usaste curl para consultar una geocerca y ver si un punto estaba dentro o fuera. Puedes hacer una solicitud web similar desde dentro de tu disparador.

1. Para consultar la geocerca, necesitas su UDID. Agrega una nueva entrada al archivo `local.settings.json` llamada `GEOFENCE_UDID` con este valor.

1. Abre el archivo `__init__.py` del nuevo disparador `geofence-trigger`.

1. Agrega la siguiente importación al inicio del archivo:

    ```python
    import json
    import os
    import requests
    ```

    El paquete `requests` te permite realizar llamadas a la API web. Azure Maps no tiene un SDK para Python, necesitas hacer llamadas a la API web para usarlo desde código Python.

1. Agrega las siguientes 2 líneas al inicio del método `main` para obtener la clave de suscripción de Maps:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. Dentro del bucle `for event in events`, agrega lo siguiente para obtener la latitud y longitud de cada evento:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Este código convierte el JSON del cuerpo del evento en un diccionario, luego extrae la `lat` y `lon` del campo `gps`.

1. Al usar `requests`, en lugar de construir una URL larga como hiciste con curl, puedes usar solo la parte de la URL y pasar los parámetros como un diccionario. Agrega el siguiente código para definir la URL a llamar y configurar los parámetros:

    ```python
    url = 'https://atlas.microsoft.com/spatial/geofence/json'

    params = {
        'api-version': 1.0,
        'deviceId': 'gps-sensor',
        'subscription-key': maps_key,
        'udid' : geofence_udid,
        'lat' : lat,
        'lon' : lon
    }
    ```

    Los elementos en el diccionario `params` coincidirán con los pares clave-valor que usaste al llamar a la API web mediante curl.

1. Agrega las siguientes líneas de código para llamar a la API web:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    Esto llama a la URL con los parámetros y obtiene un objeto de respuesta.

1. Agrega el siguiente código debajo de esto:

    ```python
    distance = response_body['geometries'][0]['distance']

    if distance == 999:
        logging.info('Point is outside geofence')
    elif distance > 0:
        logging.info(f'Point is just outside geofence by a distance of {distance}m')
    elif distance == -999:
        logging.info(f'Point is inside geofence')
    else:
        logging.info(f'Point is just inside geofence by a distance of {distance}m')
    ```

    Este código asume 1 geometría y extrae la distancia de esa única geometría. Luego registra diferentes mensajes según la distancia.

1. Ejecuta este código. Verás en la salida de registro si las coordenadas GPS están dentro o fuera de la geocerca, con una distancia si el punto está dentro de los 50m. Prueba este código con diferentes geocercas basadas en la ubicación de tu sensor GPS, intenta mover el sensor (por ejemplo, conectado a WiFi desde un teléfono móvil, o con diferentes coordenadas en el dispositivo IoT virtual) para ver este cambio.

1. Cuando estés listo, despliega este código en tu aplicación de Functions en la nube. No olvides desplegar las nuevas configuraciones de la aplicación.

    > ⚠️ Puedes consultar [las instrucciones para cargar configuraciones de la aplicación del proyecto 2, lección 5 si es necesario](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Puedes consultar [las instrucciones para desplegar tu aplicación de Functions del proyecto 2, lección 5 si es necesario](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Puedes encontrar este código en la carpeta [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions).

---

## 🚀 Desafío

En esta lección agregaste una geocerca usando un archivo GeoJSON con un único polígono. Puedes cargar múltiples polígonos al mismo tiempo, siempre que tengan diferentes valores de `geometryId` en la sección `properties`.

Intenta cargar un archivo GeoJSON con múltiples polígonos y ajusta tu código para encontrar a qué polígono están más cerca o dentro las coordenadas GPS.

## Cuestionario posterior a la lección

[Cuestionario posterior a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Revisión y autoestudio

* Lee más sobre geocercas y algunos de sus casos de uso en la [página de Geofencing en Wikipedia](https://en.wikipedia.org/wiki/Geo-fence).
* Lee más sobre la API de geocercas de Azure Maps en la [documentación de Microsoft Azure Maps Spatial - Get Geofence](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Lee más sobre grupos de consumidores en la [documentación de características y terminología en Azure Event Hubs - Event consumers en Microsoft docs](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers).

## Asignación

[Enviar notificaciones usando Twilio](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.