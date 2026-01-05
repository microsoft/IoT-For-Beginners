<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-26T15:55:02+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "es"
}
-->
# Datos de ubicación de la tienda

![Una vista general en sketchnote de esta lección](../../../../../translated_images/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.es.jpg)

> Sketchnote por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Introducción

En la última lección, aprendiste cómo usar un sensor GPS para capturar datos de ubicación. Para usar estos datos y visualizar la ubicación de un camión cargado de alimentos y su recorrido, es necesario enviarlos a un servicio IoT en la nube y luego almacenarlos en algún lugar.

En esta lección aprenderás sobre las diferentes formas de almacenar datos IoT y cómo guardar datos de tu servicio IoT utilizando código sin servidor.

En esta lección cubriremos:

* [Datos estructurados y no estructurados](../../../../../3-transport/lessons/2-store-location-data)
* [Enviar datos GPS a un IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [Rutas calientes, templadas y frías](../../../../../3-transport/lessons/2-store-location-data)
* [Manejar eventos GPS usando código sin servidor](../../../../../3-transport/lessons/2-store-location-data)
* [Cuentas de almacenamiento de Azure](../../../../../3-transport/lessons/2-store-location-data)
* [Conectar tu código sin servidor al almacenamiento](../../../../../3-transport/lessons/2-store-location-data)

## Datos estructurados y no estructurados

Los sistemas informáticos manejan datos, y estos datos vienen en diferentes formas y tamaños. Pueden variar desde números individuales, grandes cantidades de texto, videos e imágenes, hasta datos IoT. Los datos generalmente se dividen en una de dos categorías: *estructurados* y *no estructurados*.

* **Datos estructurados** son datos con una estructura bien definida y rígida que no cambia, y usualmente se mapean a tablas de datos con relaciones. Un ejemplo es la información de una persona, incluyendo su nombre, fecha de nacimiento y dirección.

* **Datos no estructurados** son datos sin una estructura bien definida y rígida, incluyendo datos que pueden cambiar de estructura frecuentemente. Un ejemplo son documentos como textos escritos o hojas de cálculo.

✅ Investiga: ¿Puedes pensar en otros ejemplos de datos estructurados y no estructurados?

> 💁 También existen datos semiestructurados que tienen estructura pero no encajan en tablas de datos fijas.

Los datos IoT generalmente se consideran datos no estructurados.

Imagina que estás añadiendo dispositivos IoT a una flota de vehículos para una gran granja comercial. Podrías querer usar diferentes dispositivos para diferentes tipos de vehículos. Por ejemplo:

* Para vehículos agrícolas como tractores, necesitas datos GPS para asegurarte de que están trabajando en los campos correctos.
* Para camiones de reparto que transportan alimentos a almacenes, necesitas datos GPS, así como datos de velocidad y aceleración para garantizar que el conductor maneje de forma segura, además de datos de identidad del conductor y de inicio/parada para cumplir con las leyes locales sobre horas de trabajo.
* Para camiones refrigerados, también necesitas datos de temperatura para asegurarte de que los alimentos no se calienten o enfríen demasiado y se echen a perder durante el transporte.

Estos datos pueden cambiar constantemente. Por ejemplo, si el dispositivo IoT está en la cabina de un camión, los datos que envía pueden cambiar según el remolque, por ejemplo, enviando datos de temperatura solo cuando se utiliza un remolque refrigerado.

✅ ¿Qué otros datos IoT podrían capturarse? Piensa en los tipos de cargas que los camiones pueden transportar, así como en datos de mantenimiento.

Estos datos varían de un vehículo a otro, pero todos se envían al mismo servicio IoT para su procesamiento. El servicio IoT necesita ser capaz de procesar estos datos no estructurados, almacenándolos de una manera que permita buscarlos o analizarlos, pero que funcione con diferentes estructuras de datos.

### Almacenamiento SQL vs NoSQL

Las bases de datos son servicios que permiten almacenar y consultar datos. Las bases de datos vienen en dos tipos: SQL y NoSQL.

#### Bases de datos SQL

Las primeras bases de datos fueron Sistemas de Gestión de Bases de Datos Relacionales (RDBMS), o bases de datos relacionales. También se conocen como bases de datos SQL debido al Lenguaje de Consulta Estructurado (SQL) utilizado para interactuar con ellas para agregar, eliminar, actualizar o consultar datos. Estas bases de datos consisten en un esquema: un conjunto bien definido de tablas de datos, similar a una hoja de cálculo. Cada tabla tiene múltiples columnas con nombres. Cuando insertas datos, agregas una fila a la tabla, colocando valores en cada una de las columnas. Esto mantiene los datos en una estructura muy rígida: aunque puedes dejar columnas vacías, si deseas agregar una nueva columna, debes hacerlo en la base de datos, rellenando valores para las filas existentes. Estas bases de datos son relacionales, en el sentido de que una tabla puede tener una relación con otra.

![Una base de datos relacional con el ID de la tabla de usuarios relacionado con la columna de ID de usuario de la tabla de compras, y el ID de la tabla de productos relacionado con el ID de producto de la tabla de compras](../../../../../translated_images/sql-database.be160f12bfccefd3.es.png)

Por ejemplo, si almacenas los detalles personales de un usuario en una tabla, tendrías algún tipo de ID único interno por usuario que se utiliza en una fila de una tabla que contiene el nombre y la dirección del usuario. Si luego quisieras almacenar otros detalles sobre ese usuario, como sus compras, en otra tabla, tendrías una columna en la nueva tabla para el ID de ese usuario. Cuando buscas un usuario, puedes usar su ID para obtener sus detalles personales de una tabla y sus compras de otra.

Las bases de datos SQL son ideales para almacenar datos estructurados y para cuando deseas asegurarte de que los datos coincidan con tu esquema.

✅ Si no has usado SQL antes, tómate un momento para leer sobre ello en la [página de SQL en Wikipedia](https://wikipedia.org/wiki/SQL).

Algunas bases de datos SQL conocidas son Microsoft SQL Server, MySQL y PostgreSQL.

✅ Investiga: Lee sobre algunas de estas bases de datos SQL y sus capacidades.

#### Bases de datos NoSQL

Las bases de datos NoSQL se llaman NoSQL porque no tienen la misma estructura rígida de las bases de datos SQL. También se conocen como bases de datos de documentos, ya que pueden almacenar datos no estructurados como documentos.

> 💁 A pesar de su nombre, algunas bases de datos NoSQL permiten usar SQL para consultar los datos.

![Documentos en carpetas en una base de datos NoSQL](../../../../../translated_images/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.es.png)

Las bases de datos NoSQL no tienen un esquema predefinido que limite cómo se almacenan los datos; en cambio, puedes insertar cualquier dato no estructurado, generalmente utilizando documentos JSON. Estos documentos pueden organizarse en carpetas, similar a los archivos en tu computadora. Cada documento puede tener diferentes campos en comparación con otros documentos. Por ejemplo, si estuvieras almacenando datos IoT de tus vehículos agrícolas, algunos podrían tener campos para datos de acelerómetro y velocidad, mientras que otros podrían tener campos para la temperatura en el remolque. Si agregaras un nuevo tipo de camión, como uno con básculas integradas para rastrear el peso de los productos transportados, entonces tu dispositivo IoT podría agregar este nuevo campo y podría almacenarse sin cambios en la base de datos.

Algunas bases de datos NoSQL conocidas incluyen Azure CosmosDB, MongoDB y CouchDB.

✅ Investiga: Lee sobre algunas de estas bases de datos NoSQL y sus capacidades.

En esta lección, usarás almacenamiento NoSQL para guardar datos IoT.

## Enviar datos GPS a un IoT Hub

En la última lección capturaste datos GPS de un sensor GPS conectado a tu dispositivo IoT. Para almacenar estos datos IoT en la nube, necesitas enviarlos a un servicio IoT. Una vez más, usarás Azure IoT Hub, el mismo servicio IoT en la nube que utilizaste en el proyecto anterior.

![Enviando telemetría GPS desde un dispositivo IoT a IoT Hub](../../../../../translated_images/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.es.png)

### Tarea - enviar datos GPS a un IoT Hub

1. Crea un nuevo IoT Hub utilizando el nivel gratuito.

    > ⚠️ Puedes consultar las [instrucciones para crear un IoT Hub del proyecto 2, lección 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud) si es necesario.

    Recuerda crear un nuevo Grupo de Recursos. Nombra el nuevo Grupo de Recursos `gps-sensor` y el nuevo IoT Hub con un nombre único basado en `gps-sensor`, como `gps-sensor-<tu nombre>`.

    > 💁 Si aún tienes tu IoT Hub del proyecto anterior, puedes reutilizarlo. Recuerda usar el nombre de este IoT Hub y el Grupo de Recursos en el que está al crear otros servicios.

1. Agrega un nuevo dispositivo al IoT Hub. Llama a este dispositivo `gps-sensor`. Obtén la cadena de conexión para el dispositivo.

1. Actualiza el código de tu dispositivo para enviar los datos GPS al nuevo IoT Hub utilizando la cadena de conexión del dispositivo obtenida en el paso anterior.

    > ⚠️ Puedes consultar las [instrucciones para conectar tu dispositivo a un IoT del proyecto 2, lección 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service) si es necesario.

1. Cuando envíes los datos GPS, hazlo en formato JSON con el siguiente formato:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Envía datos GPS cada minuto para no exceder tu asignación diaria de mensajes.

Si estás utilizando el Wio Terminal, recuerda agregar todas las bibliotecas necesarias y configurar la hora utilizando un servidor NTP. Tu código también debe asegurarse de haber leído todos los datos del puerto serial antes de enviar la ubicación GPS, utilizando el código existente de la última lección. Usa el siguiente código para construir el documento JSON:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Si estás utilizando un dispositivo IoT virtual, recuerda instalar todas las bibliotecas necesarias utilizando un entorno virtual.

Para tanto el Raspberry Pi como el dispositivo IoT virtual, utiliza el código existente de la última lección para obtener los valores de latitud y longitud, luego envíalos en el formato JSON correcto con el siguiente código:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 Puedes encontrar este código en la carpeta [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) o [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device).

Ejecuta el código de tu dispositivo y asegúrate de que los mensajes estén fluyendo hacia IoT Hub utilizando el comando CLI `az iot hub monitor-events`.

## Rutas calientes, templadas y frías

Los datos que fluyen desde un dispositivo IoT hacia la nube no siempre se procesan en tiempo real. Algunos datos necesitan procesamiento en tiempo real, otros pueden procesarse poco tiempo después, y otros pueden procesarse mucho más tarde. El flujo de datos hacia diferentes servicios que procesan los datos en diferentes momentos se conoce como rutas calientes, templadas y frías.

### Ruta caliente

La ruta caliente se refiere a los datos que necesitan ser procesados en tiempo real o casi en tiempo real. Usarías datos de ruta caliente para alertas, como recibir notificaciones de que un vehículo se está acercando a un depósito o que la temperatura en un camión refrigerado es demasiado alta.

Para usar datos de ruta caliente, tu código respondería a eventos tan pronto como sean recibidos por tus servicios en la nube.

### Ruta templada

La ruta templada se refiere a los datos que pueden procesarse poco tiempo después de ser recibidos, por ejemplo, para informes o análisis a corto plazo. Usarías datos de ruta templada para informes diarios sobre el kilometraje de los vehículos, utilizando datos recopilados el día anterior.

Los datos de ruta templada se almacenan una vez que son recibidos por el servicio en la nube dentro de algún tipo de almacenamiento que pueda ser accedido rápidamente.

### Ruta fría

La ruta fría se refiere a datos históricos, almacenando datos a largo plazo para ser procesados cuando sea necesario. Por ejemplo, podrías usar la ruta fría para obtener informes anuales de kilometraje de vehículos o realizar análisis de rutas para encontrar la ruta más óptima y reducir costos de combustible.

Los datos de ruta fría se almacenan en almacenes de datos: bases de datos diseñadas para almacenar grandes cantidades de datos que nunca cambiarán y que pueden ser consultados de manera rápida y sencilla. Normalmente tendrías un trabajo regular en tu aplicación en la nube que se ejecutaría a una hora regular cada día, semana o mes para mover datos del almacenamiento de ruta templada al almacén de datos.

✅ Piensa en los datos que has capturado hasta ahora en estas lecciones. ¿Son datos de ruta caliente, templada o fría?

## Manejar eventos GPS usando código sin servidor

Una vez que los datos están fluyendo hacia tu IoT Hub, puedes escribir código sin servidor para escuchar eventos publicados en el punto de conexión compatible con Event-Hub. Esta es la ruta templada: estos datos serán almacenados y utilizados en la próxima lección para informes sobre el recorrido.

![Enviando telemetría GPS desde un dispositivo IoT a IoT Hub, luego a Azure Functions mediante un disparador de Event Hub](../../../../../translated_images/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.es.png)

### Tarea - manejar eventos GPS usando código sin servidor

1. Crea una aplicación de Azure Functions utilizando la CLI de Azure Functions. Usa el runtime de Python y créala en una carpeta llamada `gps-trigger`, utilizando el mismo nombre para el proyecto de la aplicación de Functions. Asegúrate de crear un entorno virtual para esto.
> ⚠️ Puedes consultar las [instrucciones para crear un proyecto de Azure Functions del proyecto 2, lección 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application) si es necesario.
1. Agrega un desencadenador de eventos de IoT Hub que utilice el endpoint compatible con Event Hub del IoT Hub.

   > ⚠️ Puedes consultar las [instrucciones para crear un desencadenador de eventos de IoT Hub del proyecto 2, lección 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger) si es necesario.

1. Configura la cadena de conexión del endpoint compatible con Event Hub en el archivo `local.settings.json`, y utiliza la clave correspondiente en el archivo `function.json`.

1. Usa la aplicación Azurite como emulador de almacenamiento local.

1. Ejecuta tu aplicación de funciones para asegurarte de que está recibiendo eventos desde tu dispositivo GPS. Asegúrate de que tu dispositivo IoT también esté funcionando y enviando datos GPS.

   ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Cuentas de Almacenamiento de Azure

![El logotipo de Azure Storage](../../../../../translated_images/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.es.png)

Las Cuentas de Almacenamiento de Azure son un servicio de almacenamiento de propósito general que puede almacenar datos de diversas maneras. Puedes almacenar datos como blobs, en colas, en tablas o como archivos, y todo al mismo tiempo.

### Almacenamiento de blobs

La palabra *Blob* significa objetos binarios grandes, pero se ha convertido en el término para cualquier dato no estructurado. Puedes almacenar cualquier dato en el almacenamiento de blobs, desde documentos JSON que contienen datos de IoT, hasta archivos de imágenes y películas. El almacenamiento de blobs tiene el concepto de *contenedores*, que son como carpetas nombradas donde puedes almacenar datos, similar a las tablas en una base de datos relacional. Estos contenedores pueden tener una o más carpetas para almacenar blobs, y cada carpeta puede contener otras carpetas, similar a cómo se almacenan los archivos en el disco duro de tu computadora.

Usarás el almacenamiento de blobs en esta lección para almacenar datos de IoT.

✅ Investiga: Lee sobre el [Almacenamiento de Blobs de Azure](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Almacenamiento de tablas

El almacenamiento de tablas te permite almacenar datos semiestructurados. El almacenamiento de tablas es en realidad una base de datos NoSQL, por lo que no requiere un conjunto definido de tablas de antemano, pero está diseñado para almacenar datos en una o más tablas, con claves únicas para definir cada fila.

✅ Investiga: Lee sobre el [Almacenamiento de Tablas de Azure](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Almacenamiento de colas

El almacenamiento de colas te permite almacenar mensajes de hasta 64 KB de tamaño en una cola. Puedes agregar mensajes al final de la cola y leerlos desde el principio. Las colas almacenan mensajes indefinidamente mientras haya espacio de almacenamiento disponible, lo que permite que los mensajes se almacenen a largo plazo y se lean cuando sea necesario. Por ejemplo, si quisieras ejecutar un trabajo mensual para procesar datos GPS, podrías agregar mensajes a una cola todos los días durante un mes y luego, al final del mes, procesar todos los mensajes de la cola.

✅ Investiga: Lee sobre el [Almacenamiento de Colas de Azure](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### Almacenamiento de archivos

El almacenamiento de archivos es el almacenamiento de archivos en la nube, y cualquier aplicación o dispositivo puede conectarse utilizando protocolos estándar de la industria. Puedes escribir archivos en el almacenamiento de archivos y luego montarlo como una unidad en tu PC o Mac.

✅ Investiga: Lee sobre el [Almacenamiento de Archivos de Azure](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Conecta tu código sin servidor al almacenamiento

Tu aplicación de funciones ahora necesita conectarse al almacenamiento de blobs para almacenar los mensajes del IoT Hub. Hay dos maneras de hacerlo:

* Dentro del código de la función, conecta al almacenamiento de blobs utilizando el SDK de Python para blobs y escribe los datos como blobs.
* Usa un enlace de salida de función para vincular el valor de retorno de la función al almacenamiento de blobs y que el blob se guarde automáticamente.

En esta lección, usarás el SDK de Python para ver cómo interactuar con el almacenamiento de blobs.

![Enviando telemetría GPS desde un dispositivo IoT a IoT Hub, luego a Azure Functions a través de un desencadenador de Event Hub, y luego guardándolo en el almacenamiento de blobs](../../../../../translated_images/save-telemetry-to-storage-from-functions.ed3b1820980097f1.es.png)

Los datos se guardarán como un blob JSON con el siguiente formato:

```json
{
    "device_id": <device_id>,
    "timestamp" : <time>,
    "gps" :
    {
        "lat" : <latitude>,
        "lon" : <longitude>
    }
}
```

### Tarea - conecta tu código sin servidor al almacenamiento

1. Crea una cuenta de almacenamiento de Azure. Nómbrala algo como `gps<tu nombre>`.

   > ⚠️ Puedes consultar las [instrucciones para crear una cuenta de almacenamiento del proyecto 2, lección 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) si es necesario.

   Si aún tienes una cuenta de almacenamiento del proyecto anterior, puedes reutilizarla.

   > 💁 Podrás usar la misma cuenta de almacenamiento para implementar tu aplicación de Azure Functions más adelante en esta lección.

1. Ejecuta el siguiente comando para obtener la cadena de conexión de la cuenta de almacenamiento:

   ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

   Sustituye `<storage_name>` por el nombre de la cuenta de almacenamiento que creaste en el paso anterior.

1. Agrega una nueva entrada al archivo `local.settings.json` para la cadena de conexión de tu cuenta de almacenamiento, utilizando el valor del paso anterior. Nómbrala `STORAGE_CONNECTION_STRING`.

1. Agrega lo siguiente al archivo `requirements.txt` para instalar los paquetes Pip de almacenamiento de Azure:

   ```sh
    azure-storage-blob
    ```

   Instala los paquetes de este archivo en tu entorno virtual.

   > Si obtienes un error, actualiza tu versión de Pip en tu entorno virtual a la última versión con el siguiente comando, y luego intenta nuevamente:
   >
   > ```sh
    > pip install --upgrade pip
    > ```

1. En el archivo `__init__.py` para el `iot-hub-trigger`, agrega las siguientes declaraciones de importación:

   ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

   El módulo del sistema `json` se usará para leer y escribir JSON, el módulo del sistema `os` se usará para leer la cadena de conexión, y el módulo del sistema `uuid` se usará para generar un ID único para la lectura GPS.

   El paquete `azure.storage.blob` contiene el SDK de Python para trabajar con el almacenamiento de blobs.

1. Antes del método `main`, agrega la siguiente función auxiliar:

   ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

   El SDK de blobs de Python no tiene un método auxiliar para crear un contenedor si no existe. Este código cargará la cadena de conexión desde el archivo `local.settings.json` (o desde los Application Settings una vez implementado en la nube), luego creará una clase `BlobServiceClient` a partir de esta para interactuar con la cuenta de almacenamiento de blobs. Luego recorre todos los contenedores de la cuenta de almacenamiento de blobs, buscando uno con el nombre proporcionado; si encuentra uno, devolverá una clase `ContainerClient` que puede interactuar con el contenedor para crear blobs. Si no encuentra uno, se crea el contenedor y se devuelve el cliente para el nuevo contenedor.

   Cuando se crea el nuevo contenedor, se otorga acceso público para consultar los blobs en el contenedor. Esto se usará en la próxima lección para visualizar los datos GPS en un mapa.

1. A diferencia de la humedad del suelo, con este código queremos almacenar cada evento, así que agrega el siguiente código dentro del bucle `for event in events:` en la función `main`, debajo de la declaración `logging`:

   ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

   Este código obtiene el ID del dispositivo desde los metadatos del evento, y luego lo utiliza para crear un nombre de blob. Los blobs pueden almacenarse en carpetas, y el ID del dispositivo se usará como el nombre de la carpeta, por lo que cada dispositivo tendrá todos sus eventos GPS en una carpeta. El nombre del blob es esta carpeta, seguido de un nombre de documento, separados por barras diagonales, similar a las rutas en Linux y macOS (similar también a Windows, pero Windows usa barras invertidas). El nombre del documento es un ID único generado utilizando el módulo `uuid` de Python, con el tipo de archivo `json`.

   Por ejemplo, para el ID del dispositivo `gps-sensor`, el nombre del blob podría ser `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Agrega el siguiente código debajo de esto:

   ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

   Este código obtiene el cliente del contenedor utilizando la clase auxiliar `get_or_create_container`, y luego obtiene un objeto cliente de blob utilizando el nombre del blob. Estos clientes de blob pueden referirse a blobs existentes o, como en este caso, a un nuevo blob.

1. Agrega el siguiente código después de esto:

   ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

   Esto construye el cuerpo del blob que se escribirá en el almacenamiento de blobs. Es un documento JSON que contiene el ID del dispositivo, la hora en que se envió la telemetría al IoT Hub, y las coordenadas GPS de la telemetría.

   > 💁 Es importante usar la hora en que el mensaje fue encolado en lugar de la hora actual para obtener la hora en que se envió el mensaje. Podría estar en el hub por un tiempo antes de ser recogido si la aplicación de funciones no está en ejecución.

1. Agrega lo siguiente debajo de este código:

   ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

   Este código registra que un blob está a punto de ser escrito con sus detalles, y luego sube el cuerpo del blob como el contenido del nuevo blob.

1. Ejecuta la aplicación de funciones. Verás que se están escribiendo blobs para todos los eventos GPS en la salida:

   ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

   > 💁 Asegúrate de no estar ejecutando el monitor de eventos de IoT Hub al mismo tiempo.

> 💁 Puedes encontrar este código en la carpeta [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions).

### Tarea - verifica los blobs subidos

1. Para ver los blobs creados, puedes usar el [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), una herramienta gratuita que te permite ver y administrar tus cuentas de almacenamiento, o desde la CLI.

   1. Para usar la CLI, primero necesitarás una clave de cuenta. Ejecuta el siguiente comando para obtener esta clave:

      ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

      Sustituye `<storage_name>` por el nombre de la cuenta de almacenamiento.

      Copia el valor de `key1`.

   1. Ejecuta el siguiente comando para listar los blobs en el contenedor:

      ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

      Sustituye `<storage_name>` por el nombre de la cuenta de almacenamiento, y `<key1>` por el valor de `key1` que copiaste en el último paso.

      Esto listará todos los blobs en el contenedor:

      ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

   1. Descarga uno de los blobs utilizando el siguiente comando:

      ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

      Sustituye `<storage_name>` por el nombre de la cuenta de almacenamiento, y `<key1>` por el valor de `key1` que copiaste en el paso anterior.

      Sustituye `<blob_name>` por el nombre completo de la columna `Name` del resultado del último paso, incluyendo el nombre de la carpeta. Sustituye `<file_name>` por el nombre de un archivo local para guardar el blob.

   Una vez descargado, puedes abrir el archivo JSON en VS Code, y verás el blob que contiene los detalles de ubicación GPS:

   ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Tarea - implementa tu aplicación de funciones en la nube

Ahora que tu aplicación de funciones está funcionando, puedes implementarla en la nube.

1. Crea una nueva aplicación de Azure Functions, utilizando la cuenta de almacenamiento que creaste anteriormente. Nómbrala algo como `gps-sensor-` y agrega un identificador único al final, como algunas palabras aleatorias o tu nombre.

   > ⚠️ Puedes consultar las [instrucciones para crear una aplicación de funciones del proyecto 2, lección 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) si es necesario.

1. Sube los valores de `IOT_HUB_CONNECTION_STRING` y `STORAGE_CONNECTION_STRING` a los Application Settings.

   > ⚠️ Puedes consultar las [instrucciones para subir Application Settings del proyecto 2, lección 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings) si es necesario.

1. Implementa tu aplicación de funciones local en la nube.
> ⚠️ Puedes consultar las [instrucciones para implementar tu aplicación de funciones desde el proyecto 2, lección 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud) si es necesario.
---

## 🚀 Desafío

Los datos de GPS no son perfectamente precisos, y las ubicaciones detectadas pueden estar desviadas por unos pocos metros, o incluso más, especialmente en túneles y áreas con edificios altos.

¿Has pensado cómo la navegación por satélite podría superar esto? ¿Qué datos tiene tu sistema de navegación que podrían permitirle hacer mejores predicciones sobre tu ubicación?

## Cuestionario posterior a la clase

[Cuestionario posterior a la clase](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Revisión y estudio autónomo

* Lee sobre datos estructurados en la [página de modelo de datos en Wikipedia](https://wikipedia.org/wiki/Data_model)
* Lee sobre datos semiestructurados en la [página de datos semiestructurados en Wikipedia](https://wikipedia.org/wiki/Semi-structured_data)
* Lee sobre datos no estructurados en la [página de datos no estructurados en Wikipedia](https://wikipedia.org/wiki/Unstructured_data)
* Aprende más sobre Azure Storage y los diferentes tipos de almacenamiento en la [documentación de Azure Storage](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Tarea

[Investiga sobre enlaces de funciones](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.