<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-26T14:17:09+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "es"
}
-->
# Ejecuta tu detector de frutas en el edge

![Resumen visual de esta lección](../../../../../translated_images/es/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.jpg)

> Resumen visual por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

Este video ofrece una visión general sobre cómo ejecutar clasificadores de imágenes en dispositivos IoT, el tema que se aborda en esta lección.

[![Custom Vision AI en Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Introducción

En la lección anterior utilizaste tu clasificador de imágenes para identificar frutas maduras e inmaduras, enviando una imagen capturada por la cámara de tu dispositivo IoT a un servicio en la nube a través de internet. Estas llamadas toman tiempo, generan costos y, dependiendo del tipo de datos de imagen que estés utilizando, podrían tener implicaciones de privacidad.

En esta lección aprenderás cómo ejecutar modelos de aprendizaje automático (ML) en el edge, es decir, en dispositivos IoT que operan en tu propia red en lugar de en la nube. Aprenderás los beneficios y desventajas de la computación en el edge frente a la computación en la nube, cómo implementar tu modelo de IA en el edge y cómo acceder a él desde tu dispositivo IoT.

En esta lección cubriremos:

* [Computación en el edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Registrar un dispositivo IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Configurar un dispositivo IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Exportar tu modelo](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Preparar tu contenedor para la implementación](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Implementar tu contenedor](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Usar tu dispositivo IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Computación en el edge

La computación en el edge implica tener computadoras que procesen datos de IoT lo más cerca posible de donde se generan. En lugar de realizar este procesamiento en la nube, se traslada al borde de la nube, es decir, a tu red interna.

![Diagrama de arquitectura que muestra servicios de internet en la nube y dispositivos IoT en una red local](../../../../../translated_images/es/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.png)

En las lecciones anteriores, tus dispositivos recopilaban datos y los enviaban a la nube para ser analizados, ejecutando funciones sin servidor o modelos de IA en la nube.

![Diagrama de arquitectura que muestra dispositivos IoT en una red local conectados a dispositivos edge, y estos dispositivos edge conectados a la nube](../../../../../translated_images/es/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.png)

La computación en el edge implica mover algunos de los servicios de la nube a computadoras que operan en la misma red que los dispositivos IoT, comunicándose con la nube solo cuando sea necesario. Por ejemplo, puedes ejecutar modelos de IA en dispositivos edge para analizar la madurez de las frutas y enviar solo análisis a la nube, como el número de frutas maduras frente a inmaduras.

✅ Reflexiona sobre las aplicaciones de IoT que has construido hasta ahora. ¿Qué partes de ellas podrían trasladarse al edge?

### Ventajas

Las ventajas de la computación en el edge son:

1. **Velocidad**: la computación en el edge es ideal para datos sensibles al tiempo, ya que las acciones se realizan en la misma red que el dispositivo, en lugar de hacer llamadas a través de internet. Esto permite mayores velocidades, ya que las redes internas pueden operar a velocidades sustancialmente más altas que las conexiones a internet, con los datos viajando distancias mucho más cortas.

    > 💁 Aunque los cables ópticos se utilizan para las conexiones a internet, permitiendo que los datos viajen a la velocidad de la luz, los datos pueden tardar en recorrer el mundo hasta los proveedores de la nube. Por ejemplo, si envías datos desde Europa a servicios en la nube en EE. UU., toma al menos 28 ms para que los datos crucen el Atlántico en un cable óptico, sin contar el tiempo necesario para llevar los datos al cable transatlántico, convertir señales eléctricas en señales de luz y viceversa, y luego desde el cable óptico al proveedor de la nube.

    La computación en el edge también requiere menos tráfico de red, reduciendo el riesgo de que tus datos se ralenticen debido a la congestión en el ancho de banda limitado disponible para una conexión a internet.

1. **Accesibilidad remota**: la computación en el edge funciona cuando tienes conectividad limitada o nula, o cuando la conectividad es demasiado costosa para usarse continuamente. Por ejemplo, en áreas de desastres humanitarios donde la infraestructura es limitada o en países en desarrollo.

1. **Costos más bajos**: realizar la recopilación, almacenamiento, análisis de datos y desencadenar acciones en dispositivos edge reduce el uso de servicios en la nube, lo que puede disminuir el costo total de tu aplicación IoT. Ha habido un aumento reciente en dispositivos diseñados para la computación en el edge, como las placas aceleradoras de IA, por ejemplo, la [Jetson Nano de NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), que pueden ejecutar cargas de trabajo de IA utilizando hardware basado en GPU en dispositivos que cuestan menos de 100 USD.

1. **Privacidad y seguridad**: con la computación en el edge, los datos permanecen en tu red y no se suben a la nube. Esto es preferido para información sensible y personalmente identificable, especialmente porque los datos no necesitan almacenarse después de ser analizados, lo que reduce significativamente el riesgo de fugas de datos. Ejemplos incluyen datos médicos y grabaciones de cámaras de seguridad.

1. **Manejo de dispositivos inseguros**: si tienes dispositivos con fallas de seguridad conocidas que no deseas conectar directamente a tu red o a internet, puedes conectarlos a una red separada a través de un dispositivo IoT Edge como puerta de enlace. Este dispositivo edge puede tener una conexión a tu red más amplia o a internet, y gestionar los flujos de datos de ida y vuelta.

1. **Soporte para dispositivos incompatibles**: si tienes dispositivos que no pueden conectarse a IoT Hub, por ejemplo, dispositivos que solo pueden conectarse mediante conexiones HTTP o dispositivos que solo tienen Bluetooth, puedes usar un dispositivo IoT Edge como dispositivo de puerta de enlace, reenviando mensajes a IoT Hub.

✅ Investiga: ¿Qué otras ventajas podría tener la computación en el edge?

### Desventajas

Existen desventajas en la computación en el edge, donde la nube podría ser una opción preferida:

1. **Escalabilidad y flexibilidad**: la computación en la nube puede ajustarse a las necesidades de red y datos en tiempo real añadiendo o reduciendo servidores y otros recursos. Para añadir más computadoras edge se requiere agregar dispositivos manualmente.

1. **Confiabilidad y resiliencia**: la computación en la nube proporciona múltiples servidores, a menudo en múltiples ubicaciones, para redundancia y recuperación ante desastres. Para tener el mismo nivel de redundancia en el edge se requieren grandes inversiones y mucho trabajo de configuración.

1. **Mantenimiento**: los proveedores de servicios en la nube se encargan del mantenimiento y las actualizaciones del sistema.

✅ Investiga: ¿Qué otras desventajas podría tener la computación en el edge?

Las desventajas son realmente lo opuesto a las ventajas de usar la nube: tienes que construir y gestionar estos dispositivos tú mismo, en lugar de depender de la experiencia y la escala de los proveedores de la nube.

Algunos de los riesgos se mitigan por la propia naturaleza de la computación en el edge. Por ejemplo, si tienes un dispositivo edge funcionando en una fábrica recopilando datos de maquinaria, no necesitas preocuparte por algunos escenarios de recuperación ante desastres. Si se corta la energía en la fábrica, no necesitas un dispositivo edge de respaldo, ya que las máquinas que generan los datos que el dispositivo edge procesa también estarán sin energía.

Para los sistemas IoT, a menudo querrás una combinación de computación en la nube y en el edge, aprovechando cada servicio según las necesidades del sistema, sus usuarios y sus mantenedores.

## Azure IoT Edge

![El logotipo de Azure IoT Edge](../../../../../translated_images/es/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.png)

Azure IoT Edge es un servicio que puede ayudarte a trasladar cargas de trabajo fuera de la nube hacia el edge. Configuras un dispositivo como un dispositivo edge y, desde la nube, puedes implementar código en ese dispositivo edge. Esto te permite combinar las capacidades de la nube y el edge.

> 🎓 *Cargas de trabajo* es un término que se refiere a cualquier servicio que realiza algún tipo de trabajo, como modelos de IA, aplicaciones o funciones sin servidor.

Por ejemplo, puedes entrenar un clasificador de imágenes en la nube y luego implementarlo desde la nube en un dispositivo edge. Tu dispositivo IoT enviará imágenes al dispositivo edge para su clasificación, en lugar de enviarlas a través de internet. Si necesitas implementar una nueva iteración del modelo, puedes entrenarlo en la nube y usar IoT Edge para actualizar el modelo en el dispositivo edge con la nueva iteración.

> 🎓 El software que se implementa en IoT Edge se conoce como *módulos*. Por defecto, IoT Edge ejecuta módulos que se comunican con IoT Hub, como los módulos `edgeAgent` y `edgeHub`. Cuando implementas un clasificador de imágenes, este se implementa como un módulo adicional.

IoT Edge está integrado en IoT Hub, por lo que puedes gestionar dispositivos edge utilizando el mismo servicio que usarías para gestionar dispositivos IoT, con el mismo nivel de seguridad.

IoT Edge ejecuta código desde *contenedores*: aplicaciones autónomas que se ejecutan de forma aislada del resto de las aplicaciones en tu computadora. Cuando ejecutas un contenedor, actúa como una computadora separada dentro de tu computadora, con su propio software, servicios y aplicaciones en ejecución. La mayoría de las veces, los contenedores no pueden acceder a nada en tu computadora a menos que elijas compartir cosas como una carpeta con el contenedor. El contenedor luego expone servicios a través de un puerto abierto al que puedes conectarte o exponer a tu red.

![Una solicitud web redirigida a un contenedor](../../../../../translated_images/es/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.png)

Por ejemplo, puedes tener un contenedor con un sitio web ejecutándose en el puerto 80, el puerto HTTP predeterminado, y puedes exponerlo desde tu computadora también en el puerto 80.

✅ Investiga: Lee sobre contenedores y servicios como Docker o Moby.

Puedes usar Custom Vision para descargar clasificadores de imágenes e implementarlos como contenedores, ya sea ejecutándolos directamente en un dispositivo o implementándolos a través de IoT Edge. Una vez que están en ejecución en un contenedor, se pueden acceder utilizando la misma API REST que la versión en la nube, pero con el endpoint apuntando al dispositivo Edge que ejecuta el contenedor.

## Registrar un dispositivo IoT Edge

Para usar un dispositivo IoT Edge, este debe registrarse en IoT Hub.

### Tarea - Registrar un dispositivo IoT Edge

1. Crea un IoT Hub en el grupo de recursos `fruit-quality-detector`. Asígnale un nombre único basado en `fruit-quality-detector`.

1. Registra un dispositivo IoT Edge llamado `fruit-quality-detector-edge` en tu IoT Hub. El comando para hacerlo es similar al que se usa para registrar un dispositivo no-edge, excepto que debes pasar el indicador `--edge-enabled`.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Sustituye `<hub_name>` por el nombre de tu IoT Hub.

1. Obtén la cadena de conexión para tu dispositivo utilizando el siguiente comando:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Sustituye `<hub_name>` por el nombre de tu IoT Hub.

    Copia la cadena de conexión que se muestra en la salida.

## Configurar un dispositivo IoT Edge

Una vez que hayas creado el registro del dispositivo edge en tu IoT Hub, puedes configurar el dispositivo edge.

### Tarea - Instalar e iniciar el runtime de IoT Edge

**El runtime de IoT Edge solo ejecuta contenedores Linux.** Puede ejecutarse en Linux o en Windows utilizando máquinas virtuales Linux.

* Si estás utilizando una Raspberry Pi como tu dispositivo IoT, esta ejecuta una versión compatible de Linux y puede alojar el runtime de IoT Edge. Sigue la [guía de instalación de Azure IoT Edge para Linux en la documentación de Microsoft](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) para instalar IoT Edge y configurar la cadena de conexión.

    > 💁 Recuerda, Raspberry Pi OS es una variante de Debian Linux.

* Si no estás utilizando una Raspberry Pi, pero tienes una computadora con Linux, puedes ejecutar el runtime de IoT Edge. Sigue la [guía de instalación de Azure IoT Edge para Linux en la documentación de Microsoft](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) para instalar IoT Edge y configurar la cadena de conexión.

* Si estás utilizando Windows, puedes instalar el runtime de IoT Edge en una máquina virtual Linux siguiendo la [sección de instalación e inicio del runtime de IoT Edge en la guía rápida para implementar tu primer módulo IoT Edge en un dispositivo Windows en la documentación de Microsoft](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Puedes detenerte cuando llegues a la sección *Implementar un módulo*.

* Si estás utilizando macOS, puedes crear una máquina virtual (VM) en la nube para usar como tu dispositivo IoT Edge. Estas son computadoras que puedes crear en la nube y acceder a través de internet. Puedes crear una VM Linux que tenga IoT Edge instalado. Sigue la [guía para crear una máquina virtual que ejecute IoT Edge](vm-iotedge.md) para obtener instrucciones sobre cómo hacerlo.

## Exportar tu modelo

Para ejecutar el clasificador en el edge, es necesario exportarlo desde Custom Vision. Custom Vision puede generar dos tipos de modelos: modelos estándar y modelos compactos. Los modelos compactos utilizan diversas técnicas para reducir el tamaño del modelo, haciéndolo lo suficientemente pequeño como para ser descargado e implementado en dispositivos IoT.

Cuando creaste el clasificador de imágenes, utilizaste el dominio *Food*, una versión del modelo optimizada para entrenar con imágenes de alimentos. En Custom Vision, puedes cambiar el dominio de tu proyecto, utilizando tus datos de entrenamiento para entrenar un nuevo modelo con el nuevo dominio. Todos los dominios compatibles con Custom Vision están disponibles como estándar y compacto.

### Tarea - Entrenar tu modelo utilizando el dominio Food (compact)
1. Abre el portal de Custom Vision en [CustomVision.ai](https://customvision.ai) e inicia sesión si aún no lo tienes abierto. Luego, abre tu proyecto `fruit-quality-detector`.

1. Selecciona el botón **Configuración** (el ícono ⚙).

1. En la lista de *Dominios*, selecciona *Food (compact)*.

1. En *Capacidades de exportación*, asegúrate de que esté seleccionada la opción *Plataformas básicas (Tensorflow, CoreML, ONNX, ...)*.

1. En la parte inferior de la página de Configuración, selecciona **Guardar cambios**.

1. Reentrena el modelo con el botón **Entrenar**, seleccionando *Entrenamiento rápido*.

### Tarea - exportar tu modelo

Una vez que el modelo haya sido entrenado, debe ser exportado como un contenedor.

1. Selecciona la pestaña **Rendimiento** y encuentra tu última iteración que fue entrenada usando el dominio compacto.

1. Selecciona el botón **Exportar** en la parte superior.

1. Selecciona **DockerFile**, luego elige una versión que coincida con tu dispositivo edge:

    * Si estás ejecutando IoT Edge en una computadora Linux, una computadora Windows o una máquina virtual, selecciona la versión *Linux*.
    * Si estás ejecutando IoT Edge en un Raspberry Pi, selecciona la versión *ARM (Raspberry Pi 3)*.

    
> 🎓 Docker es una de las herramientas más populares para gestionar contenedores, y un DockerFile es un conjunto de instrucciones sobre cómo configurar el contenedor.

1. Selecciona **Exportar** para que Custom Vision cree los archivos relevantes, luego **Descargar** para descargarlos en un archivo zip.

1. Guarda los archivos en tu computadora y descomprime la carpeta.

## Prepara tu contenedor para el despliegue

![Los contenedores se construyen, luego se envían a un registro de contenedores, y se despliegan desde el registro de contenedores a un dispositivo edge usando IoT Edge](../../../../../translated_images/es/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.png)

Una vez que hayas descargado tu modelo, debe ser construido en un contenedor y luego enviado a un registro de contenedores, que es una ubicación en línea donde puedes almacenar contenedores. IoT Edge puede descargar el contenedor desde el registro y enviarlo a tu dispositivo.

![Logo de Azure Container Registry](../../../../../translated_images/es/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.png)

El registro de contenedores que usarás para esta lección es Azure Container Registry. Este no es un servicio gratuito, así que para ahorrar dinero asegúrate de [limpiar tu proyecto](../../../clean-up.md) una vez que hayas terminado.

> 💁 Puedes ver los costos de usar un Azure Container Registry en la [página de precios de Azure Container Registry](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Tarea - instalar Docker

Para construir y desplegar el clasificador, es posible que necesites instalar [Docker](https://www.docker.com/).

Solo necesitarás hacerlo si planeas construir tu contenedor desde un dispositivo diferente al que instalaste IoT Edge; como parte de la instalación de IoT Edge, Docker se instala automáticamente.

1. Si estás construyendo el contenedor Docker en un dispositivo diferente al de IoT Edge, sigue las instrucciones de instalación de Docker en la [página de instalación de Docker](https://www.docker.com/products/docker-desktop) para instalar Docker Desktop o el motor Docker. Asegúrate de que esté funcionando después de la instalación.

### Tarea - crear un recurso de registro de contenedores

1. Ejecuta el siguiente comando desde tu Terminal o línea de comandos para crear un recurso de Azure Container Registry:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Reemplaza `<Container registry name>` con un nombre único para tu registro de contenedores, usando solo letras y números. Basa este nombre en `fruitqualitydetector`. Este nombre se convierte en parte de la URL para acceder al registro de contenedores, por lo que debe ser globalmente único.

1. Inicia sesión en el Azure Container Registry con el siguiente comando:

    ```sh
    az acr login --name <Container registry name>
    ```

    Reemplaza `<Container registry name>` con el nombre que usaste para tu registro de contenedores.

1. Activa el modo administrador en el registro de contenedores para que puedas generar una contraseña con el siguiente comando:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Reemplaza `<Container registry name>` con el nombre que usaste para tu registro de contenedores.

1. Genera contraseñas para tu registro de contenedores con el siguiente comando:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Reemplaza `<Container registry name>` con el nombre que usaste para tu registro de contenedores.

    Toma una copia del valor de `PASSWORD`, ya que lo necesitarás más adelante.

### Tarea - construir tu contenedor

Lo que descargaste de Custom Vision fue un DockerFile que contiene instrucciones sobre cómo debe construirse el contenedor, junto con el código de la aplicación que se ejecutará dentro del contenedor para alojar tu modelo de visión personalizada, junto con una API REST para llamarlo. Puedes usar Docker para construir un contenedor etiquetado desde el DockerFile y luego enviarlo a tu registro de contenedores.

> 🎓 Los contenedores se etiquetan con un nombre y una versión. Cuando necesites actualizar un contenedor, puedes construirlo con la misma etiqueta pero con una versión más reciente.

1. Abre tu terminal o línea de comandos y navega al modelo descomprimido que descargaste de Custom Vision.

1. Ejecuta el siguiente comando para construir y etiquetar la imagen:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Reemplaza `<platform>` con la plataforma en la que este contenedor se ejecutará. Si estás ejecutando IoT Edge en un Raspberry Pi, establece esto en `linux/armhf`, de lo contrario, establece esto en `linux/amd64`.

    > 💁 Si estás ejecutando este comando desde el dispositivo en el que estás ejecutando IoT Edge, como desde tu Raspberry Pi, puedes omitir la parte `--platform <platform>` ya que por defecto usa la plataforma actual.

    Reemplaza `<Container registry name>` con el nombre que usaste para tu registro de contenedores.

    > 💁 Si estás ejecutando en Linux o Raspberry Pi OS, es posible que necesites usar `sudo` para ejecutar este comando.

    Docker construirá la imagen, configurando todo el software necesario. La imagen será etiquetada como `classifier:v1`.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### Tarea - enviar tu contenedor a tu registro de contenedores

1. Usa el siguiente comando para enviar tu contenedor a tu registro de contenedores:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Reemplaza `<Container registry name>` con el nombre que usaste para tu registro de contenedores.

    > 💁 Si estás ejecutando en Linux, es posible que necesites usar `sudo` para ejecutar este comando.

    El contenedor será enviado al registro de contenedores.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. Para verificar el envío, puedes listar los contenedores en tu registro con el siguiente comando:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Reemplaza `<Container registry name>` con el nombre que usaste para tu registro de contenedores.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Verás tu clasificador listado en la salida.

## Despliega tu contenedor

Tu contenedor ahora puede ser desplegado en tu dispositivo IoT Edge. Para desplegarlo, necesitas definir un manifiesto de despliegue: un documento JSON que lista los módulos que serán desplegados en el dispositivo edge.

### Tarea - crear el manifiesto de despliegue

1. Crea un nuevo archivo llamado `deployment.json` en algún lugar de tu computadora.

1. Agrega lo siguiente a este archivo:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 Puedes encontrar este archivo en la carpeta [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    Reemplaza las tres instancias de `<Container registry name>` con el nombre que usaste para tu registro de contenedores. Una está en la sección del módulo `ImageClassifier`, las otras dos están en la sección `registryCredentials`.

    Reemplaza `<Container registry password>` en la sección `registryCredentials` con tu contraseña del registro de contenedores.

1. Desde la carpeta que contiene tu manifiesto de despliegue, ejecuta el siguiente comando:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Reemplaza `<hub_name>` con el nombre de tu IoT Hub.

    El módulo del clasificador de imágenes será desplegado en tu dispositivo edge.

### Tarea - verifica que el clasificador esté funcionando

1. Conéctate al dispositivo IoT Edge:

    * Si estás usando un Raspberry Pi para ejecutar IoT Edge, conéctate usando ssh desde tu terminal o mediante una sesión remota SSH en VS Code.
    * Si estás ejecutando IoT Edge en un contenedor Linux en Windows, sigue los pasos en la [guía de verificación de configuración exitosa](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) para conectarte al dispositivo IoT Edge.
    * Si estás ejecutando IoT Edge en una máquina virtual, puedes hacer ssh en la máquina usando el `adminUsername` y `password` que configuraste al crear la VM, y usando la dirección IP o el nombre DNS:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        O:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Ingresa tu contraseña cuando se te solicite.

1. Una vez conectado, ejecuta el siguiente comando para obtener la lista de módulos IoT Edge:

    ```sh
    iotedge list
    ```

    > 💁 Es posible que necesites ejecutar este comando con `sudo`.

    Verás los módulos en ejecución:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Revisa los registros del módulo del clasificador de imágenes con el siguiente comando:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Es posible que necesites ejecutar este comando con `sudo`.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### Tarea - prueba el clasificador de imágenes

1. Puedes usar CURL para probar el clasificador de imágenes utilizando la dirección IP o el nombre del host de la computadora que está ejecutando el agente IoT Edge. Encuentra la dirección IP:

    * Si estás en la misma máquina que ejecuta IoT Edge, puedes usar `localhost` como nombre del host.
    * Si estás usando una VM, puedes usar la dirección IP o el nombre DNS de la VM.
    * De lo contrario, puedes obtener la dirección IP de la máquina que ejecuta IoT Edge:
      * En Windows 10, sigue la [guía para encontrar tu dirección IP](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * En macOS, sigue la [guía para encontrar tu dirección IP en Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * En Linux, sigue la sección sobre cómo encontrar tu dirección IP privada en la [guía para encontrar tu dirección IP en Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Puedes probar el contenedor con un archivo local ejecutando el siguiente comando curl:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Reemplaza `<IP address or name>` con la dirección IP o el nombre del host de la computadora que ejecuta IoT Edge. Reemplaza `<file_Name>` con el nombre del archivo para probar.

    Verás los resultados de la predicción en la salida:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 No es necesario proporcionar una clave de predicción aquí, ya que no se está utilizando un recurso de Azure. En su lugar, la seguridad se configuraría en la red interna basada en necesidades de seguridad internas, en lugar de depender de un punto final público y una clave API.

## Usa tu dispositivo IoT Edge

Ahora que tu clasificador de imágenes ha sido desplegado en un dispositivo IoT Edge, puedes usarlo desde tu dispositivo IoT.

### Tarea - usa tu dispositivo IoT Edge

Sigue la guía relevante para clasificar imágenes usando el clasificador IoT Edge:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Computadora de placa única - Raspberry Pi/Dispositivo IoT virtual](single-board-computer.md)

### Reentrenamiento del modelo

Una de las desventajas de ejecutar clasificadores de imágenes en IoT Edge es que no están conectados a tu proyecto de Custom Vision. Si miras la pestaña **Predicciones** en Custom Vision, no verás las imágenes que fueron clasificadas usando el clasificador basado en Edge.

Este es el comportamiento esperado: las imágenes no se envían a la nube para su clasificación, por lo que no estarán disponibles en la nube. Una de las ventajas de usar IoT Edge es la privacidad, asegurando que las imágenes no salgan de tu red; otra es poder trabajar sin conexión, sin depender de subir imágenes cuando el dispositivo no tiene conexión a internet. La desventaja es mejorar tu modelo: necesitarías implementar otra forma de almacenar imágenes que puedan ser reclasificadas manualmente para mejorar y reentrenar el clasificador de imágenes.

✅ Piensa en formas de subir imágenes para reentrenar el clasificador.

---

## 🚀 Desafío

Ejecutar modelos de IA en dispositivos edge puede ser más rápido que en la nube: el salto de red es más corto. También pueden ser más lentos, ya que el hardware que ejecuta el modelo puede no ser tan potente como el de la nube.

Haz algunas mediciones y compara si la llamada a tu dispositivo edge es más rápida o más lenta que la llamada a la nube. Piensa en razones para explicar la diferencia, o la falta de diferencia. Investiga formas de ejecutar modelos de IA más rápido en el edge usando hardware especializado.

## Cuestionario post-lectura

[Cuestionario post-lectura](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Revisión y autoestudio

* Lee más sobre contenedores en la [página de virtualización a nivel de sistema operativo en Wikipedia](https://wikipedia.org/wiki/OS-level_virtualization).
* Lee más sobre la computación en el borde, con énfasis en cómo el 5G puede ayudar a expandir la computación en el borde en el [artículo sobre qué es la computación en el borde y por qué importa en NetworkWorld](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Aprende más sobre cómo ejecutar servicios de IA en IoT Edge viendo el [episodio de Learn Live en Microsoft Channel9 sobre cómo usar Azure IoT Edge en un servicio de IA preconstruido en el borde para realizar detección de lenguaje](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Tarea

[Ejecuta otros servicios en el borde](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.