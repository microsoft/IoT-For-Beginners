# Comprender el lenguaje

![Una vista general en sketchnote de esta lección](../../../../../translated_images/es/lesson-22.6148ea28500d9e00.webp)

> Sketchnote por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Introducción

En la última lección convertiste voz a texto. Para que esto se utilice en la programación de un temporizador inteligente, tu código necesitará comprender lo que se dijo. Podrías asumir que el usuario dirá una frase fija, como "Configura un temporizador de 3 minutos", y analizar esa expresión para determinar cuánto tiempo debe durar el temporizador, pero esto no es muy amigable para el usuario. Si un usuario dijera "Configura un temporizador para 3 minutos", tú o yo entenderíamos lo que significa, pero tu código no, ya que estaría esperando una frase fija.

Aquí es donde entra en juego la comprensión del lenguaje, utilizando modelos de inteligencia artificial para interpretar texto y devolver los detalles necesarios, por ejemplo, siendo capaz de entender tanto "Configura un temporizador de 3 minutos" como "Configura un temporizador para 3 minutos", y deducir que se requiere un temporizador de 3 minutos.

En esta lección aprenderás sobre los modelos de comprensión del lenguaje, cómo crearlos, entrenarlos y utilizarlos desde tu código.

En esta lección cubriremos:

* [Comprensión del lenguaje](../../../../../6-consumer/lessons/2-language-understanding)
* [Crear un modelo de comprensión del lenguaje](../../../../../6-consumer/lessons/2-language-understanding)
* [Intenciones y entidades](../../../../../6-consumer/lessons/2-language-understanding)
* [Usar el modelo de comprensión del lenguaje](../../../../../6-consumer/lessons/2-language-understanding)

## Comprensión del lenguaje

Los humanos han utilizado el lenguaje para comunicarse durante cientos de miles de años. Nos comunicamos con palabras, sonidos o acciones y entendemos lo que se dice, tanto el significado de las palabras, sonidos o acciones, como también su contexto. Entendemos la sinceridad y el sarcasmo, permitiendo que las mismas palabras signifiquen cosas diferentes dependiendo del tono de nuestra voz.

✅ Piensa en algunas de las conversaciones que has tenido recientemente. ¿Cuánto de la conversación sería difícil para una computadora entender porque necesita contexto?

La comprensión del lenguaje, también llamada comprensión del lenguaje natural, es parte de un campo de la inteligencia artificial llamado procesamiento del lenguaje natural (o NLP, por sus siglas en inglés), y se ocupa de la comprensión lectora, tratando de entender los detalles de las palabras o frases. Si utilizas un asistente de voz como Alexa o Siri, has usado servicios de comprensión del lenguaje. Estos son los servicios de inteligencia artificial detrás de escena que convierten "Alexa, reproduce el último álbum de Taylor Swift" en mi hija bailando por la sala al ritmo de sus canciones favoritas.

> 💁 Las computadoras, a pesar de todos sus avances, todavía tienen un largo camino por recorrer para comprender verdaderamente el texto. Cuando nos referimos a la comprensión del lenguaje con computadoras, no nos referimos a nada ni remotamente tan avanzado como la comunicación humana, sino a tomar algunas palabras y extraer detalles clave.

Como humanos, entendemos el lenguaje sin realmente pensar en ello. Si le pidiera a otro humano "reproduce el último álbum de Taylor Swift", entonces sabrían instintivamente lo que quiero decir. Para una computadora, esto es más difícil. Tendría que tomar las palabras, convertidas de voz a texto, y deducir las siguientes piezas de información:

* Se necesita reproducir música
* La música es del artista Taylor Swift
* La música específica es un álbum completo con múltiples pistas en orden
* Taylor Swift tiene muchos álbumes, por lo que deben ordenarse cronológicamente y el más recientemente publicado es el requerido

✅ Piensa en algunas otras frases que hayas dicho al hacer solicitudes, como pedir café o pedirle a un familiar que te pase algo. Intenta descomponerlas en las piezas de información que una computadora necesitaría extraer para entender la frase.

Los modelos de comprensión del lenguaje son modelos de inteligencia artificial que se entrenan para extraer ciertos detalles del lenguaje y luego se entrenan para tareas específicas utilizando aprendizaje por transferencia, de la misma manera que entrenaste un modelo de visión personalizada utilizando un pequeño conjunto de imágenes. Puedes tomar un modelo y entrenarlo utilizando el texto que deseas que entienda.

## Crear un modelo de comprensión del lenguaje

![El logo de LUIS](../../../../../translated_images/es/luis-logo.5cb4f3e88c020ee6.webp)

Puedes crear modelos de comprensión del lenguaje utilizando LUIS, un servicio de comprensión del lenguaje de Microsoft que forma parte de Cognitive Services.

### Tarea - crear un recurso de autoría

Para usar LUIS, necesitas crear un recurso de autoría.

1. Usa el siguiente comando para crear un recurso de autoría en tu grupo de recursos `smart-timer`:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Reemplaza `<location>` con la ubicación que utilizaste al crear el grupo de recursos.

    > ⚠️ LUIS no está disponible en todas las regiones, por lo que si obtienes el siguiente error:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > elige una región diferente.

    Esto creará un recurso de autoría de nivel gratuito.

### Tarea - crear una aplicación de comprensión del lenguaje

1. Abre el portal de LUIS en [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) en tu navegador y accede con la misma cuenta que has estado utilizando para Azure.

1. Sigue las instrucciones en el cuadro de diálogo para seleccionar tu suscripción de Azure, luego selecciona el recurso `smart-timer-luis-authoring` que acabas de crear.

1. Desde la lista de *Aplicaciones de conversación*, selecciona el botón **Nueva aplicación** para crear una nueva aplicación. Nombra la nueva aplicación `smart-timer` y establece la *Cultura* en tu idioma.

    > 💁 Hay un campo para un recurso de predicción. Puedes crear un segundo recurso solo para predicción, pero el recurso de autoría gratuito permite 1,000 predicciones al mes, lo cual debería ser suficiente para el desarrollo, así que puedes dejar este campo en blanco.

1. Lee la guía que aparece una vez que creas la aplicación para comprender los pasos que necesitas seguir para entrenar el modelo de comprensión del lenguaje. Cierra esta guía cuando hayas terminado.

## Intenciones y entidades

La comprensión del lenguaje se basa en *intenciones* y *entidades*. Las intenciones son el propósito de las palabras, por ejemplo, reproducir música, configurar un temporizador o pedir comida. Las entidades son a lo que se refiere la intención, como el álbum, la duración del temporizador o el tipo de comida. Cada frase que el modelo interprete debe tener al menos una intención y, opcionalmente, una o más entidades.

Algunos ejemplos:

| Frase                                              | Intención         | Entidades                                   |
| -------------------------------------------------- | ----------------- | ------------------------------------------ |
| "Reproduce el último álbum de Taylor Swift"        | *reproducir música* | *el último álbum de Taylor Swift*          |
| "Configura un temporizador de 3 minutos"           | *configurar temporizador* | *3 minutos*                                |
| "Cancela mi temporizador"                          | *cancelar temporizador* | Ninguna                                    |
| "Pide 3 pizzas grandes de piña y una ensalada César" | *pedir comida*    | *3 pizzas grandes de piña*, *ensalada César* |

✅ Con las frases que pensaste anteriormente, ¿cuál sería la intención y las entidades en esa frase?

Para entrenar LUIS, primero defines las entidades. Estas pueden ser una lista fija de términos o aprendidas del texto. Por ejemplo, podrías proporcionar una lista fija de alimentos disponibles en tu menú, con variaciones (o sinónimos) de cada palabra, como *berenjena* y *aubergine* como variaciones de *berenjena*. LUIS también tiene entidades predefinidas que pueden ser utilizadas, como números y ubicaciones.

Para configurar un temporizador, podrías tener una entidad utilizando las entidades predefinidas de números para el tiempo y otra para las unidades, como minutos y segundos. Cada unidad tendría múltiples variaciones para cubrir las formas singular y plural, como minuto y minutos.

Una vez que las entidades están definidas, creas intenciones. Estas se aprenden por el modelo basado en frases de ejemplo que proporcionas (conocidas como expresiones). Por ejemplo, para una intención de *configurar temporizador*, podrías proporcionar las siguientes frases:

* `configura un temporizador de 1 segundo`
* `configura un temporizador de 1 minuto y 12 segundos`
* `configura un temporizador de 3 minutos`
* `configura un temporizador de 9 minutos y 30 segundos`

Luego le indicas a LUIS qué partes de estas frases corresponden a las entidades:

![La frase configura un temporizador de 1 minuto y 12 segundos dividida en entidades](../../../../../translated_images/es/sentence-as-intent-entities.301401696f992259.webp)

La frase `configura un temporizador de 1 minuto y 12 segundos` tiene la intención de `configurar temporizador`. También tiene 2 entidades con 2 valores cada una:

|            | tiempo | unidad   |
| ---------- | ------ | -------- |
| 1 minuto   | 1      | minuto   |
| 12 segundos | 12     | segundo  |

Para entrenar un buen modelo, necesitas una variedad de frases de ejemplo diferentes para cubrir las muchas formas en que alguien podría pedir lo mismo.

> 💁 Como con cualquier modelo de inteligencia artificial, mientras más datos y más precisos sean los datos que utilices para entrenar, mejor será el modelo.

✅ Piensa en las diferentes formas en que podrías pedir lo mismo y esperar que un humano lo entienda.

### Tarea - agregar entidades a los modelos de comprensión del lenguaje

Para el temporizador, necesitas agregar 2 entidades: una para la unidad de tiempo (minutos o segundos) y otra para el número de minutos o segundos.

Puedes encontrar instrucciones para usar el portal de LUIS en la [documentación de Microsoft sobre el inicio rápido: Crear tu aplicación en el portal de LUIS](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Desde el portal de LUIS, selecciona la pestaña *Entidades* y agrega la entidad predefinida *número* seleccionando el botón **Agregar entidad predefinida**, luego selecciona *número* de la lista.

1. Crea una nueva entidad para la unidad de tiempo utilizando el botón **Crear**. Nombra la entidad `unidad de tiempo` y establece el tipo en *Lista*. Agrega valores para `minuto` y `segundo` a la lista de *Valores normalizados*, agregando las formas singular y plural a la lista de *sinónimos*. Presiona `enter` después de agregar cada sinónimo para añadirlo a la lista.

    | Valor normalizado | Sinónimos        |
    | ----------------- | ---------------- |
    | minuto            | minuto, minutos  |
    | segundo           | segundo, segundos|

### Tarea - agregar intenciones a los modelos de comprensión del lenguaje

1. Desde la pestaña *Intenciones*, selecciona el botón **Crear** para crear una nueva intención. Nombra esta intención `configurar temporizador`.

1. En los ejemplos, ingresa diferentes formas de configurar un temporizador utilizando tanto minutos, segundos y combinaciones de minutos y segundos. Ejemplos podrían ser:

    * `configura un temporizador de 1 segundo`
    * `configura un temporizador de 4 minutos`
    * `configura un temporizador de cuatro minutos y seis segundos`
    * `configura un temporizador de 9 minutos y 30 segundos`
    * `configura un temporizador de 1 minuto y 12 segundos`
    * `configura un temporizador de 3 minutos`
    * `configura un temporizador de 3 minutos y 1 segundo`
    * `configura un temporizador de tres minutos y un segundo`
    * `configura un temporizador de 1 minuto y 1 segundo`
    * `configura un temporizador de 30 segundos`
    * `configura un temporizador de 1 segundo`

    Mezcla números como palabras y números para que el modelo aprenda a manejar ambos.

1. A medida que ingreses cada ejemplo, LUIS comenzará a detectar entidades y subrayará y etiquetará las que encuentre.

    ![Los ejemplos con los números y unidades de tiempo subrayados por LUIS](../../../../../translated_images/es/luis-intent-examples.25716580b2d2723c.webp)

### Tarea - entrenar y probar el modelo

1. Una vez que las entidades e intenciones estén configuradas, puedes entrenar el modelo utilizando el botón **Entrenar** en el menú superior. Selecciona este botón y el modelo debería entrenarse en unos segundos. El botón estará deshabilitado mientras se entrena y se habilitará nuevamente una vez que termine.

1. Selecciona el botón **Probar** en el menú superior para probar el modelo de comprensión del lenguaje. Ingresa texto como `configura un temporizador de 5 minutos y 4 segundos` y presiona enter. La frase aparecerá en un cuadro debajo del cuadro de texto en el que la escribiste, y debajo de eso estará la *intención principal*, o la intención que se detectó con la mayor probabilidad. Esto debería ser `configurar temporizador`. El nombre de la intención estará seguido por la probabilidad de que la intención detectada sea la correcta.

1. Selecciona la opción **Inspeccionar** para ver un desglose de los resultados. Verás la intención con mayor puntuación con su porcentaje de probabilidad, junto con listas de las entidades detectadas.

1. Cierra el panel *Probar* cuando hayas terminado de probar.

### Tarea - publicar el modelo

Para usar este modelo desde el código, necesitas publicarlo. Al publicar desde LUIS, puedes hacerlo en un entorno de prueba para pruebas o en un entorno de producción para un lanzamiento completo. En esta lección, un entorno de prueba es suficiente.

1. Desde el portal de LUIS, selecciona el botón **Publicar** en el menú superior.

1. Asegúrate de que esté seleccionada la opción *Staging slot*, luego selecciona **Listo**. Verás una notificación cuando la aplicación se haya publicado.

1. Puedes probar esto utilizando curl. Para construir el comando curl, necesitas tres valores: el endpoint, el ID de la aplicación (App ID) y una clave de API. Estos pueden ser accedidos desde la pestaña **ADMINISTRAR** que se puede seleccionar desde el menú superior.

    1. Desde la sección *Configuración*, copia el App ID.
1. Desde la sección *Azure Resources*, selecciona *Authoring Resource* y copia la *Primary Key* y la *Endpoint URL*.

1. Ejecuta el siguiente comando curl en tu terminal o línea de comandos:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Reemplaza `<endpoint url>` con la Endpoint URL de la sección *Azure Resources*.

    Reemplaza `<app id>` con el App ID de la sección *Settings*.

    Reemplaza `<primary key>` con la Primary Key de la sección *Azure Resources*.

    Reemplaza `<sentence>` con la frase que deseas probar.

1. El resultado de esta llamada será un documento JSON que detalla la consulta, la intención principal y una lista de entidades clasificadas por tipo.

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

    El JSON anterior proviene de una consulta con `set a timer for 45 minutes and 12 seconds`:

    * La intención principal fue `set timer` con una probabilidad del 97%.
    * Se detectaron dos entidades de tipo *number*, `45` y `12`.
    * Se detectaron dos entidades de tipo *time-unit*, `minute` y `second`.

## Usar el modelo de comprensión de lenguaje

Una vez publicado, el modelo LUIS puede ser llamado desde el código. En lecciones anteriores, has utilizado un IoT Hub para manejar la comunicación con servicios en la nube, enviando telemetría y escuchando comandos. Esto es muy asincrónico: una vez que se envía la telemetría, tu código no espera una respuesta, y si el servicio en la nube está caído, no lo sabrías.

Para un temporizador inteligente, queremos una respuesta inmediata, para poder informar al usuario que el temporizador está configurado o alertarlo de que los servicios en la nube no están disponibles. Para lograr esto, nuestro dispositivo IoT llamará directamente a un endpoint web, en lugar de depender de un IoT Hub.

En lugar de llamar a LUIS desde el dispositivo IoT, puedes usar código sin servidor con un tipo diferente de activador: un activador HTTP. Esto permite que tu aplicación de funciones escuche solicitudes REST y responda a ellas. Esta función será un endpoint REST que tu dispositivo podrá llamar.

> 💁 Aunque puedes llamar a LUIS directamente desde tu dispositivo IoT, es mejor usar algo como código sin servidor. De esta manera, cuando desees cambiar la aplicación LUIS que llamas, por ejemplo, cuando entrenes un mejor modelo o entrenes un modelo en otro idioma, solo tendrás que actualizar tu código en la nube, sin necesidad de volver a implementar el código en potencialmente miles o millones de dispositivos IoT.

### Tarea - crear una aplicación de funciones sin servidor

1. Crea una aplicación de funciones de Azure llamada `smart-timer-trigger` y ábrela en VS Code.

1. Agrega un activador HTTP a esta aplicación llamado `speech-trigger` usando el siguiente comando desde la terminal de VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Esto creará un activador HTTP llamado `text-to-timer`.

1. Prueba el activador HTTP ejecutando la aplicación de funciones. Cuando se ejecute, verás el endpoint listado en la salida:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Prueba esto cargando la URL [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) en tu navegador.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Tarea - usar el modelo de comprensión de lenguaje

1. El SDK para LUIS está disponible a través de un paquete Pip. Agrega la siguiente línea al archivo `requirements.txt` para agregar la dependencia de este paquete:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Asegúrate de que la terminal de VS Code tenga el entorno virtual activado y ejecuta el siguiente comando para instalar los paquetes de Pip:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Si obtienes errores, puede que necesites actualizar pip con el siguiente comando:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Agrega nuevas entradas al archivo `local.settings.json` para tu LUIS API Key, Endpoint URL y App ID desde la pestaña **MANAGE** del portal de LUIS:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Reemplaza `<endpoint url>` con la Endpoint URL de la sección *Azure Resources* de la pestaña **MANAGE**. Esto será `https://<location>.api.cognitive.microsoft.com/`.

    Reemplaza `<app id>` con el App ID de la sección *Settings* de la pestaña **MANAGE**.

    Reemplaza `<primary key>` con la Primary Key de la sección *Azure Resources* de la pestaña **MANAGE**.

1. Agrega las siguientes importaciones al archivo `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Esto importa algunas bibliotecas del sistema, así como las bibliotecas para interactuar con LUIS.

1. Elimina el contenido del método `main` y agrega el siguiente código:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Esto carga los valores que agregaste al archivo `local.settings.json` para tu aplicación LUIS, crea un objeto de credenciales con tu API key y luego crea un objeto cliente de LUIS para interactuar con tu aplicación LUIS.

1. Este activador HTTP será llamado pasando el texto a entender como JSON, con el texto en una propiedad llamada `text`. El siguiente código extrae el valor del cuerpo de la solicitud HTTP y lo registra en la consola. Agrega este código a la función `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Las predicciones se solicitan a LUIS enviando una solicitud de predicción: un documento JSON que contiene el texto a predecir. Crea esto con el siguiente código:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Esta solicitud puede ser enviada a LUIS, usando el slot de staging al que tu aplicación fue publicada:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. La respuesta de predicción contiene la intención principal, la intención con el puntaje de predicción más alto, junto con las entidades. Si la intención principal es `set timer`, entonces las entidades pueden ser leídas para obtener el tiempo necesario para el temporizador:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    Las entidades de tipo `number` serán un arreglo de números. Por ejemplo, si dijiste *"Set a four minute 17 second timer."*, entonces el arreglo `number` contendrá 2 enteros: 4 y 17.

    Las entidades de tipo `time unit` serán un arreglo de arreglos de cadenas, con cada unidad de tiempo como un arreglo de cadenas dentro del arreglo. Por ejemplo, si dijiste *"Set a four minute 17 second timer."*, entonces el arreglo `time unit` contendrá 2 arreglos con valores únicos cada uno: `['minute']` y `['second']`.

    La versión JSON de estas entidades para *"Set a four minute 17 second timer."* es:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Este código también define un contador para el tiempo total del temporizador en segundos. Esto será poblado por los valores de las entidades.

1. Las entidades no están vinculadas, pero podemos hacer algunas suposiciones sobre ellas. Estarán en el orden hablado, por lo que la posición en el arreglo puede ser usada para determinar qué número corresponde a qué unidad de tiempo. Por ejemplo:

    * *"Set a 30 second timer"* - esto tendrá un número, `30`, y una unidad de tiempo, `second`, por lo que el único número corresponderá a la única unidad de tiempo.
    * *"Set a 2 minute and 30 second timer"* - esto tendrá dos números, `2` y `30`, y dos unidades de tiempo, `minute` y `second`, por lo que el primer número será para la primera unidad de tiempo (2 minutos) y el segundo número para la segunda unidad de tiempo (30 segundos).

    El siguiente código obtiene el conteo de elementos en las entidades de tipo número y usa eso para extraer el primer elemento de cada arreglo, luego el segundo y así sucesivamente. Agrega esto dentro del bloque `if`.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Para *"Set a four minute 17 second timer."*, esto hará un bucle dos veces, dando los siguientes valores:

    | conteo de bucle | `number` | `time_unit` |
    | ---------------: | -------: | ----------- |
    | 0                | 4        | minute      |
    | 1                | 17       | second      |

1. Dentro de este bucle, usa el número y la unidad de tiempo para calcular el tiempo total del temporizador, agregando 60 segundos por cada minuto y el número de segundos por cualquier segundo.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Fuera de este bucle a través de las entidades, registra el tiempo total del temporizador:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. El número de segundos necesita ser devuelto desde la función como una respuesta HTTP. Al final del bloque `if`, agrega lo siguiente:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Este código crea un payload que contiene el número total de segundos para el temporizador, lo convierte en una cadena JSON y lo devuelve como un resultado HTTP con un código de estado 200, lo que significa que la llamada fue exitosa.

1. Finalmente, fuera del bloque `if`, maneja el caso en que la intención no fue reconocida devolviendo un código de error:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 es el código de estado para *no encontrado*.

1. Ejecuta la aplicación de funciones y pruébala usando curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Reemplaza `<text>` con el texto de tu solicitud, por ejemplo `set a 2 minutes 27 second timer`.

    Verás la siguiente salida de la aplicación de funciones:

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

    La llamada a curl devolverá lo siguiente:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    El número de segundos para el temporizador está en el valor `"seconds"`.

> 💁 Puedes encontrar este código en la carpeta [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Tarea - hacer que tu función esté disponible para tu dispositivo IoT

1. Para que tu dispositivo IoT llame a tu endpoint REST, necesitará conocer la URL. Cuando lo accediste anteriormente, usaste `localhost`, que es un atajo para acceder a endpoints REST en tu máquina local. Para permitir que tu dispositivo IoT tenga acceso, necesitas publicar en la nube o obtener tu dirección IP para acceder localmente.

    > ⚠️ Si estás usando un Wio Terminal, es más fácil ejecutar la aplicación de funciones localmente, ya que habrá una dependencia de bibliotecas que significa que no puedes implementar la aplicación de funciones de la misma manera que lo has hecho antes. Ejecuta la aplicación de funciones localmente y accede a ella a través de la dirección IP de tu computadora. Si deseas implementar en la nube, se proporcionará información en una lección posterior sobre cómo hacerlo.

    * Publica la aplicación de funciones - sigue las instrucciones de lecciones anteriores para publicar tu aplicación de funciones en la nube. Una vez publicada, la URL será `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, donde `<APP_NAME>` será el nombre de tu aplicación de funciones. Asegúrate también de publicar tus configuraciones locales.

      Cuando trabajes con activadores HTTP, estarán asegurados por defecto con una clave de aplicación de funciones. Para obtener esta clave, ejecuta el siguiente comando:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Copia el valor de la entrada `default` de la sección `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Esta clave deberá ser agregada como un parámetro de consulta a la URL, por lo que la URL final será `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, donde `<APP_NAME>` será el nombre de tu aplicación de funciones y `<FUNCTION_KEY>` será tu clave de función predeterminada.

      > 💁 Puedes cambiar el tipo de autorización del activador HTTP usando la configuración `authlevel` en el archivo `function.json`. Puedes leer más sobre esto en la [sección de configuración de la documentación del activador HTTP de Azure Functions en Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Ejecuta la aplicación de funciones localmente y accede usando la dirección IP - puedes obtener la dirección IP de tu computadora en tu red local y usarla para construir la URL.

      Encuentra tu dirección IP:

      * En Windows 10, sigue la [guía para encontrar tu dirección IP](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * En macOS, sigue la [guía para encontrar tu dirección IP en Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * En Linux, sigue la sección sobre cómo encontrar tu dirección IP privada en la [guía para encontrar tu dirección IP en Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

      Una vez que tengas tu dirección IP, podrás acceder a la función en `http://`.

:7071/api/text-to-timer`, donde `<IP_ADDRESS>` será tu dirección IP, por ejemplo `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Ten en cuenta que esto utiliza el puerto 7071, así que después de la dirección IP necesitarás incluir `:7071`.

      > 💁 Esto solo funcionará si tu dispositivo IoT está en la misma red que tu computadora.

1. Prueba el endpoint accediendo a él utilizando curl.

---

## 🚀 Desafío

Existen muchas formas de solicitar lo mismo, como configurar un temporizador. Piensa en diferentes maneras de hacerlo y utilízalas como ejemplos en tu aplicación LUIS. Ponlas a prueba para ver qué tan bien tu modelo puede manejar múltiples formas de solicitar un temporizador.

## Cuestionario posterior a la lección

[Cuestionario posterior a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Revisión y autoestudio

* Lee más sobre LUIS y sus capacidades en la [página de documentación de Language Understanding (LUIS) en Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Lee más sobre la comprensión del lenguaje en la [página de comprensión del lenguaje natural en Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* Lee más sobre los disparadores HTTP en la [documentación de Azure Functions HTTP trigger en Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Tarea

[Cancelar el temporizador](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.