<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-26T14:48:32+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "es"
}
-->
# Migra tu planta a la nube

![Un resumen visual de esta lección](../../../../../translated_images/es/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.jpg)

> Resumen visual por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

Esta lección fue impartida como parte de la [serie de Agricultura Digital del Proyecto 2 de IoT para Principiantes](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) del [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Conecta tu dispositivo a la nube con Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Introducción

En la lección anterior, aprendiste a conectar tu planta a un broker MQTT y a controlar un relé desde un código de servidor que se ejecuta localmente. Esto constituye el núcleo de un sistema automatizado de riego conectado a internet, que puede usarse tanto para plantas individuales en casa como para granjas comerciales.

El dispositivo IoT se comunicaba con un broker MQTT público como una forma de demostrar los principios básicos, pero esta no es la manera más confiable ni segura. En esta lección, aprenderás sobre la nube y las capacidades de IoT que ofrecen los servicios públicos en la nube. También aprenderás cómo migrar tu planta de un broker MQTT público a uno de estos servicios en la nube.

En esta lección cubriremos:

* [¿Qué es la nube?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Crear una suscripción en la nube](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Servicios de IoT en la nube](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Crear un servicio IoT en la nube](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Comunicarte con IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Conectar tu dispositivo al servicio IoT](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## ¿Qué es la nube?

Antes de la nube, cuando una empresa quería proporcionar servicios a sus empleados (como bases de datos o almacenamiento de archivos) o al público (como sitios web), construía y operaba un centro de datos. Esto podía ir desde una sala con unos pocos ordenadores hasta un edificio con muchos. La empresa se encargaba de todo, incluyendo:

* Comprar ordenadores
* Mantenimiento del hardware
* Energía y refrigeración
* Redes
* Seguridad, tanto del edificio como del software en los ordenadores
* Instalación y actualización de software

Esto podía ser muy costoso, requerir una amplia gama de empleados especializados y ser muy lento para adaptarse a cambios. Por ejemplo, si una tienda en línea necesitaba prepararse para una temporada alta de ventas, tendría que planificar con meses de antelación para comprar más hardware, configurarlo, instalarlo e implementar el software necesario para gestionar las ventas. Después de la temporada alta, cuando las ventas disminuyeran, se quedarían con ordenadores que ya habían pagado pero que estarían inactivos hasta la próxima temporada.

✅ ¿Crees que esto permitiría a las empresas moverse rápidamente? Si una tienda de ropa en línea se volviera popular de repente porque una celebridad fue vista usando su ropa, ¿podrían aumentar su capacidad de cómputo lo suficientemente rápido para manejar el repentino aumento de pedidos?

### El ordenador de otra persona

La nube a menudo se describe en broma como "el ordenador de otra persona". La idea inicial era simple: en lugar de comprar ordenadores, alquilas los de otra persona. Un proveedor de computación en la nube se encargaría de gestionar enormes centros de datos. Ellos serían responsables de comprar e instalar el hardware, gestionar la energía y la refrigeración, las redes, la seguridad del edificio, las actualizaciones de hardware y software, todo. Como cliente, alquilas los ordenadores que necesitas, aumentando el alquiler cuando la demanda sube y reduciéndolo cuando la demanda baja. Estos centros de datos en la nube están distribuidos por todo el mundo.

![Un centro de datos en la nube de Microsoft](../../../../../translated_images/es/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.png)
![Expansión planificada de un centro de datos en la nube de Microsoft](../../../../../translated_images/es/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.png)

Estos centros de datos pueden tener varios kilómetros cuadrados de tamaño. Las imágenes anteriores fueron tomadas hace algunos años en un centro de datos en la nube de Microsoft y muestran el tamaño inicial, junto con una expansión planificada. El área despejada para la expansión tiene más de 5 kilómetros cuadrados.

> 💁 Estos centros de datos requieren cantidades tan grandes de energía que algunos tienen sus propias estaciones de energía. Debido a su tamaño y al nivel de inversión de los proveedores de la nube, suelen ser muy respetuosos con el medio ambiente. Son más eficientes que un gran número de pequeños centros de datos, funcionan principalmente con energía renovable y los proveedores de la nube trabajan arduamente para reducir los desechos, disminuir el uso de agua y reforestar las áreas taladas para construir los centros de datos. Puedes leer más sobre cómo un proveedor de la nube está trabajando en sostenibilidad en el [sitio de sostenibilidad de Azure](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Investiga: Lee sobre las principales nubes como [Azure de Microsoft](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) o [GCP de Google](https://cloud.google.com). ¿Cuántos centros de datos tienen y dónde están ubicados en el mundo?

Usar la nube reduce los costos para las empresas y les permite centrarse en lo que hacen mejor, dejando la experiencia en computación en la nube en manos del proveedor. Las empresas ya no necesitan alquilar o comprar espacio en centros de datos, pagar a diferentes proveedores por conectividad y energía, o emplear expertos. En su lugar, pueden pagar una factura mensual al proveedor de la nube para que se encargue de todo.

El proveedor de la nube puede entonces aprovechar las economías de escala para reducir costos, comprando ordenadores al por mayor a precios más bajos, invirtiendo en herramientas para reducir su carga de trabajo de mantenimiento, e incluso diseñando y construyendo su propio hardware para mejorar su oferta en la nube.

### Microsoft Azure

Azure es la nube para desarrolladores de Microsoft, y es la nube que usarás en estas lecciones. El siguiente video ofrece una breve descripción de Azure:

[![Video de introducción a Azure](../../../../../translated_images/es/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Crear una suscripción en la nube

Para usar servicios en la nube, necesitarás registrarte para obtener una suscripción con un proveedor de nube. En esta lección, te registrarás para obtener una suscripción de Microsoft Azure. Si ya tienes una suscripción de Azure, puedes omitir esta tarea. Los detalles de la suscripción descritos aquí son correctos al momento de escribir, pero pueden cambiar.

> 💁 Si estás accediendo a estas lecciones a través de tu escuela, es posible que ya tengas una suscripción de Azure disponible. Consulta con tu profesor.

Hay dos tipos diferentes de suscripción gratuita de Azure a las que puedes registrarte:

* **Azure para Estudiantes** - Esta es una suscripción diseñada para estudiantes mayores de 18 años. No necesitas una tarjeta de crédito para registrarte y usas tu correo electrónico escolar para validar que eres estudiante. Al registrarte, obtienes $100 USD para gastar en recursos en la nube, junto con servicios gratuitos, incluyendo una versión gratuita de un servicio IoT. Esto dura 12 meses y puedes renovarlo cada año mientras sigas siendo estudiante.

* **Suscripción gratuita de Azure** - Esta es una suscripción para cualquier persona que no sea estudiante. Necesitarás una tarjeta de crédito para registrarte, pero tu tarjeta no será cobrada, solo se usa para verificar que eres una persona real, no un bot. Obtienes $200 USD de crédito para usar en los primeros 30 días en cualquier servicio, junto con niveles gratuitos de servicios de Azure. Una vez que tu crédito se haya agotado, tu tarjeta no será cobrada a menos que conviertas tu cuenta a una suscripción de pago por uso.

> 💁 Microsoft también ofrece una suscripción Azure para Estudiantes Starter para estudiantes menores de 18 años, pero al momento de escribir esto, no admite servicios IoT.

### Tarea - registrarse para una suscripción gratuita en la nube

Si eres estudiante mayor de 18 años, puedes registrarte para una suscripción Azure para Estudiantes. Necesitarás validar con un correo electrónico escolar. Puedes hacerlo de dos maneras:

* Regístrate para un paquete de desarrollador estudiantil de GitHub en [education.github.com/pack](https://education.github.com/pack). Esto te da acceso a una variedad de herramientas y ofertas, incluyendo GitHub y Microsoft Azure. Una vez que te registres para el paquete de desarrollador, puedes activar la oferta de Azure para Estudiantes.

* Regístrate directamente para una cuenta Azure para Estudiantes en [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Si tu correo electrónico escolar no es reconocido, abre un [issue en este repositorio](https://github.com/Microsoft/IoT-For-Beginners/issues) y veremos si puede ser agregado a la lista de permitidos de Azure para Estudiantes.

Si no eres estudiante o no tienes un correo electrónico escolar válido, puedes registrarte para una suscripción gratuita de Azure.

* Regístrate para una suscripción gratuita de Azure en [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Servicios de IoT en la nube

El broker MQTT público de prueba que has estado utilizando es una gran herramienta para aprender, pero tiene varias desventajas como herramienta para un entorno comercial:

* Confiabilidad: es un servicio gratuito sin garantías, y puede ser desactivado en cualquier momento.
* Seguridad: es público, por lo que cualquiera podría escuchar tu telemetría o enviar comandos para controlar tu hardware.
* Rendimiento: está diseñado solo para unos pocos mensajes de prueba, por lo que no soportaría una gran cantidad de mensajes enviados.
* Descubrimiento: no hay forma de saber qué dispositivos están conectados.

Los servicios de IoT en la nube resuelven estos problemas. Son mantenidos por grandes proveedores de nube que invierten mucho en confiabilidad y están disponibles para solucionar cualquier problema que pueda surgir. Tienen seguridad integrada para evitar que los hackers lean tus datos o envíen comandos maliciosos. También tienen un alto rendimiento, siendo capaces de manejar millones de mensajes cada día, aprovechando la nube para escalar según sea necesario.

> 💁 Aunque pagas por estas ventajas con una tarifa mensual, la mayoría de los proveedores de nube ofrecen una versión gratuita de su servicio IoT con una cantidad limitada de mensajes por día o dispositivos que pueden conectarse. Esta versión gratuita suele ser más que suficiente para que un desarrollador aprenda sobre el servicio. En esta lección, usarás una versión gratuita.

Los dispositivos IoT se conectan a un servicio en la nube ya sea utilizando un SDK de dispositivo (una biblioteca que proporciona código para trabajar con las características del servicio) o directamente a través de un protocolo de comunicación como MQTT o HTTP. El SDK de dispositivo suele ser la ruta más fácil, ya que maneja todo por ti, como saber a qué temas publicar o suscribirse y cómo manejar la seguridad.

![Los dispositivos se conectan a un servicio usando un SDK de dispositivo. El código del servidor también se conecta al servicio a través de un SDK](../../../../../translated_images/es/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.png)

Tu dispositivo luego se comunica con otras partes de tu aplicación a través de este servicio, de manera similar a cómo enviaste telemetría y recibiste comandos a través de MQTT. Esto generalmente se hace utilizando un SDK de servicio o una biblioteca similar. Los mensajes van desde tu dispositivo al servicio, donde otros componentes de tu aplicación pueden leerlos, y los mensajes pueden enviarse de vuelta a tu dispositivo.

![Los dispositivos sin una clave secreta válida no pueden conectarse al servicio IoT](../../../../../translated_images/es/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.png)

Estos servicios implementan seguridad al conocer todos los dispositivos que pueden conectarse y enviar datos, ya sea registrando previamente los dispositivos en el servicio o proporcionando a los dispositivos claves secretas o certificados que pueden usar para registrarse en el servicio la primera vez que se conectan. Los dispositivos desconocidos no pueden conectarse; si lo intentan, el servicio rechaza la conexión e ignora los mensajes enviados por ellos.

✅ Investiga: ¿Cuál es la desventaja de tener un servicio IoT abierto donde cualquier dispositivo o código pueda conectarse? ¿Puedes encontrar ejemplos específicos de hackers aprovechándose de esto?

Otros componentes de tu aplicación pueden conectarse al servicio IoT y obtener información sobre todos los dispositivos que están conectados o registrados, y comunicarse con ellos directamente, ya sea de forma masiva o individual.
💁 Los servicios de IoT también implementan capacidades adicionales, y los proveedores de la nube tienen servicios y aplicaciones adicionales que se pueden conectar al servicio. Por ejemplo, si deseas almacenar todos los mensajes de telemetría enviados por todos los dispositivos en una base de datos, generalmente solo se necesitan unos pocos clics en la herramienta de configuración del proveedor de la nube para conectar el servicio a una base de datos y transmitir los datos.
## Crear un servicio IoT en la nube

Ahora que tienes una suscripción a Azure, puedes registrarte en un servicio IoT. El servicio IoT de Microsoft se llama Azure IoT Hub.

![El logo de Azure IoT Hub](../../../../../translated_images/es/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.png)

El siguiente video ofrece una breve descripción general de Azure IoT Hub:

[![Video de descripción general de Azure IoT Hub](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Haz clic en la imagen de arriba para ver el video

✅ Tómate un momento para investigar y leer la descripción general de IoT Hub en la [documentación de Microsoft IoT Hub](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

Los servicios en la nube disponibles en Azure se pueden configurar a través de un portal web o mediante una interfaz de línea de comandos (CLI). Para esta tarea, usarás la CLI.

### Tarea - instalar Azure CLI

Para usar Azure CLI, primero debes instalarla en tu PC o Mac.

1. Sigue las instrucciones en la [documentación de Azure CLI](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) para instalar la CLI.

1. Azure CLI admite una serie de extensiones que añaden capacidades para gestionar una amplia gama de servicios de Azure. Instala la extensión IoT ejecutando el siguiente comando desde tu línea de comandos o terminal:

    ```sh
    az extension add --name azure-iot
    ```

1. Desde tu línea de comandos o terminal, ejecuta el siguiente comando para iniciar sesión en tu suscripción de Azure desde Azure CLI.

    ```sh
    az login
    ```

    Se abrirá una página web en tu navegador predeterminado. Inicia sesión usando la cuenta que utilizaste para registrarte en tu suscripción de Azure. Una vez que hayas iniciado sesión, puedes cerrar la pestaña del navegador.

1. Si tienes varias suscripciones de Azure, como una proporcionada por tu escuela y tu propia suscripción de Azure para Estudiantes, necesitarás seleccionar la que deseas usar. Ejecuta el siguiente comando para listar todas las suscripciones a las que tienes acceso:

    ```sh
    az account list --output table
    ```

    En la salida, verás el nombre de cada suscripción junto con su `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Para seleccionar la suscripción que deseas usar, utiliza el siguiente comando:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Sustituye `<SubscriptionId>` por el Id de la suscripción que deseas usar. Después de ejecutar este comando, vuelve a ejecutar el comando para listar tus cuentas. Verás que la columna `IsDefault` estará marcada como `True` para la suscripción que acabas de configurar.

### Tarea - crear un grupo de recursos

Los servicios de Azure, como las instancias de IoT Hub, máquinas virtuales, bases de datos o servicios de IA, se denominan **recursos**. Cada recurso debe estar dentro de un **Grupo de Recursos**, que es una agrupación lógica de uno o más recursos.

> 💁 Usar grupos de recursos significa que puedes gestionar múltiples servicios a la vez. Por ejemplo, una vez que hayas terminado todas las lecciones de este proyecto, puedes eliminar el grupo de recursos, y todos los recursos en él se eliminarán automáticamente.

1. Hay múltiples centros de datos de Azure en todo el mundo, divididos en regiones. Cuando creas un recurso o grupo de recursos en Azure, debes especificar dónde deseas que se cree. Ejecuta el siguiente comando para obtener la lista de ubicaciones:

    ```sh
    az account list-locations --output table
    ```

    Verás una lista de ubicaciones. Esta lista será larga.

    > 💁 En el momento de escribir esto, hay 65 ubicaciones disponibles para desplegar.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Anota el valor de la columna `Name` de la región más cercana a ti. Puedes encontrar las regiones en un mapa en la [página de geografías de Azure](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Ejecuta el siguiente comando para crear un grupo de recursos llamado `soil-moisture-sensor`. Los nombres de los grupos de recursos deben ser únicos en tu suscripción.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Sustituye `<location>` por la ubicación que seleccionaste en el paso anterior.

### Tarea - crear un IoT Hub

Ahora puedes crear un recurso IoT Hub en tu grupo de recursos.

1. Usa el siguiente comando para crear tu recurso IoT Hub:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Sustituye `<hub_name>` por un nombre para tu hub. Este nombre debe ser único a nivel global, es decir, ningún otro IoT Hub creado por alguien más puede tener el mismo nombre. Este nombre se utiliza en una URL que apunta al hub, por lo que debe ser único. Usa algo como `soil-moisture-sensor-` y añade un identificador único al final, como algunas palabras aleatorias o tu nombre.

    La opción `--sku F1` indica que se usará un nivel gratuito. El nivel gratuito admite 8,000 mensajes al día junto con la mayoría de las características de los niveles de precio completo.

    > 🎓 Los diferentes niveles de precios de los servicios de Azure se denominan niveles. Cada nivel tiene un costo diferente y proporciona diferentes características o volúmenes de datos.

    > 💁 Si deseas aprender más sobre los precios, puedes consultar la [guía de precios de Azure IoT Hub](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    La opción `--partition-count 2` define cuántos flujos de datos admite el IoT Hub. Más particiones reducen el bloqueo de datos cuando múltiples dispositivos leen y escriben desde el IoT Hub. Las particiones están fuera del alcance de estas lecciones, pero este valor debe configurarse para crear un IoT Hub de nivel gratuito.

    > 💁 Solo puedes tener un IoT Hub de nivel gratuito por suscripción.

El IoT Hub se creará. Esto puede tardar un minuto o más en completarse.

## Comunicarte con IoT Hub

En la lección anterior, usaste MQTT y enviaste mensajes de ida y vuelta en diferentes temas, con diferentes propósitos. En lugar de enviar mensajes en diferentes temas, IoT Hub tiene varias formas definidas para que el dispositivo se comunique con el Hub, o para que el Hub se comunique con el dispositivo.

> 💁 En el fondo, esta comunicación entre IoT Hub y tu dispositivo puede usar MQTT, HTTPS o AMQP.

* Mensajes de dispositivo a nube (D2C) - estos son mensajes enviados desde un dispositivo a IoT Hub, como telemetría. Luego pueden ser leídos desde IoT Hub por tu código de aplicación.

    > 🎓 En el fondo, IoT Hub utiliza un servicio de Azure llamado [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Cuando escribes código para leer mensajes enviados al hub, a menudo se les llama eventos.

* Mensajes de nube a dispositivo (C2D) - estos son mensajes enviados desde el código de la aplicación, a través de un IoT Hub, a un dispositivo IoT.

* Solicitudes de métodos directos - estos son mensajes enviados desde el código de la aplicación a través de un IoT Hub a un dispositivo IoT para solicitar que el dispositivo haga algo, como controlar un actuador. Estos mensajes requieren una respuesta para que tu código de aplicación pueda saber si se procesaron correctamente.

* Gemelos de dispositivos - estos son documentos JSON sincronizados entre el dispositivo y IoT Hub, y se utilizan para almacenar configuraciones u otras propiedades informadas por el dispositivo, o que deben configurarse en el dispositivo (conocidas como deseadas) por IoT Hub.

IoT Hub puede almacenar mensajes y solicitudes de métodos directos durante un período de tiempo configurable (por defecto un día), por lo que si un dispositivo o el código de la aplicación pierde conexión, aún puede recuperar los mensajes enviados mientras estaba desconectado una vez que se reconecta. Los gemelos de dispositivos se mantienen permanentemente en IoT Hub, por lo que en cualquier momento un dispositivo puede reconectarse y obtener el gemelo de dispositivo más reciente.

✅ Investiga: Lee más sobre estos tipos de mensajes en la [guía de comunicaciones de dispositivo a nube](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) y la [guía de comunicaciones de nube a dispositivo](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) en la documentación de IoT Hub.

## Conecta tu dispositivo al servicio IoT

Una vez que el hub esté creado, tu dispositivo IoT puede conectarse a él. Solo los dispositivos registrados pueden conectarse a un servicio, por lo que primero deberás registrar tu dispositivo. Cuando lo registres, obtendrás una cadena de conexión que el dispositivo puede usar para conectarse. Esta cadena de conexión es específica del dispositivo e incluye información sobre el IoT Hub, el dispositivo y una clave secreta que permitirá que este dispositivo se conecte.

> 🎓 Una cadena de conexión es un término genérico para un texto que contiene detalles de conexión. Estas se usan al conectarse a IoT Hubs, bases de datos y muchos otros servicios. Generalmente consisten en un identificador para el servicio, como una URL, y datos de seguridad como una clave secreta. Estas se pasan a los SDKs para conectarse al servicio.

> ⚠️ ¡Las cadenas de conexión deben mantenerse seguras! La seguridad se cubrirá con más detalle en una lección futura.

### Tarea - registrar tu dispositivo IoT

El dispositivo IoT puede registrarse en tu IoT Hub usando Azure CLI.

1. Ejecuta el siguiente comando para registrar un dispositivo:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Sustituye `<hub_name>` por el nombre que usaste para tu IoT Hub.

    Esto creará un dispositivo con un ID de `soil-moisture-sensor`.

1. Cuando tu dispositivo IoT se conecte a tu IoT Hub usando el SDK, necesitará usar una cadena de conexión que proporcione la URL del hub, junto con una clave secreta. Ejecuta el siguiente comando para obtener la cadena de conexión:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Sustituye `<hub_name>` por el nombre que usaste para tu IoT Hub.

1. Guarda la cadena de conexión que aparece en la salida, ya que la necesitarás más adelante.

### Tarea - conectar tu dispositivo IoT a la nube

Sigue la guía correspondiente para conectar tu dispositivo IoT a la nube:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Computadora de placa única - Raspberry Pi/Dispositivo IoT virtual](single-board-computer-connect-hub.md)

### Tarea - monitorear eventos

Por ahora, no actualizarás tu código de servidor. En su lugar, puedes usar Azure CLI para monitorear eventos desde tu dispositivo IoT.

1. Asegúrate de que tu dispositivo IoT esté funcionando y enviando valores de telemetría de humedad del suelo.

1. Ejecuta el siguiente comando en tu terminal para monitorear los mensajes enviados a tu IoT Hub:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Sustituye `<hub_name>` por el nombre que usaste para tu IoT Hub.

    Verás mensajes aparecer en la salida de la consola a medida que son enviados por tu dispositivo IoT.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    El contenido del `payload` coincidirá con el mensaje enviado por tu dispositivo IoT.

    > En el momento de escribir esto, la extensión `az iot` no funciona completamente en dispositivos Apple Silicon. Si estás usando un dispositivo Apple Silicon, necesitarás monitorear los mensajes de otra manera, como usando las [herramientas de Azure IoT para Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Estos mensajes tienen una serie de propiedades adjuntas automáticamente, como la marca de tiempo en que fueron enviados. Estas se conocen como *anotaciones*. Para ver todas las anotaciones de los mensajes, usa el siguiente comando:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Sustituye `<hub_name>` por el nombre que usaste para tu IoT Hub.

    Verás mensajes aparecer en la salida de la consola a medida que son enviados por tu dispositivo IoT.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Los valores de tiempo en las anotaciones están en [tiempo UNIX](https://wikipedia.org/wiki/Unix_time), que representa el número de segundos desde la medianoche del 1<sup>er</sup> de enero de 1970.

    Sal del monitor de eventos cuando hayas terminado.

### Tarea - controlar tu dispositivo IoT

También puedes usar Azure CLI para llamar métodos directos en tu dispositivo IoT.

1. Ejecuta el siguiente comando en tu terminal para invocar el método `relay_on` en el dispositivo IoT:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Sustituye `
<hub_name>
` con el nombre que usaste para tu IoT Hub.

    Esto envía una solicitud de método directo para el método especificado por `method-name`. Los métodos directos pueden incluir un payload que contenga datos para el método, y esto se puede especificar en el parámetro `method-payload` como JSON.

    Verás que el relé se enciende y el correspondiente resultado de tu dispositivo IoT:

    ```output
    Direct method received -  relay_on
    ```

1. Repite el paso anterior, pero establece el `--method-name` en `relay_off`. Verás que el relé se apaga y el correspondiente resultado del dispositivo IoT.

---

## 🚀 Desafío

El nivel gratuito de IoT Hub permite 8,000 mensajes al día. El código que escribiste envía mensajes de telemetría cada 10 segundos. ¿Cuántos mensajes al día se generan si se envía un mensaje cada 10 segundos?

Piensa en la frecuencia con la que deberían enviarse las mediciones de humedad del suelo. ¿Cómo puedes cambiar tu código para permanecer dentro del nivel gratuito y verificar tan frecuentemente como sea necesario pero no demasiado? ¿Qué pasaría si quisieras agregar un segundo dispositivo?

## Cuestionario posterior a la clase

[Cuestionario posterior a la clase](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Revisión y autoestudio

El SDK de IoT Hub es de código abierto tanto para Arduino como para Python. En los repositorios de código en GitHub hay varios ejemplos que muestran cómo trabajar con diferentes características de IoT Hub.

* Si estás usando un Wio Terminal, revisa los [ejemplos de Arduino en GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Si estás usando un Raspberry Pi o un dispositivo virtual, revisa los [ejemplos de Python en GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Tarea

[Aprende sobre servicios en la nube](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.