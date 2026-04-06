# Conecta tu dispositivo a Internet

![Un resumen visual de esta lección](../../../../../translated_images/es/lesson-4.7344e074ea68fa54.webp)

> Resumen visual por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para verla en tamaño completo.

Esta lección fue impartida como parte de la serie [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) del [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). La lección se presentó en 2 videos: una clase de 1 hora y una sesión de preguntas y respuestas de 1 hora para profundizar en partes de la lección y responder preguntas.

[![Lección 4: Conecta tu dispositivo a Internet](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Lección 4: Conecta tu dispositivo a Internet - Sesión de preguntas](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Haz clic en las imágenes de arriba para ver los videos

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Introducción

La **I** en IoT significa **Internet**: la conectividad en la nube y los servicios que habilitan muchas de las funciones de los dispositivos IoT, desde recopilar mediciones de los sensores conectados al dispositivo hasta enviar mensajes para controlar los actuadores. Los dispositivos IoT suelen conectarse a un único servicio IoT en la nube utilizando un protocolo de comunicación estándar, y ese servicio está conectado al resto de tu aplicación IoT, desde servicios de inteligencia artificial para tomar decisiones inteligentes basadas en tus datos, hasta aplicaciones web para control o generación de informes.

> 🎓 Los datos recopilados de los sensores y enviados a la nube se llaman telemetría.

Los dispositivos IoT pueden recibir mensajes desde la nube. A menudo, estos mensajes contienen comandos, es decir, instrucciones para realizar una acción, ya sea internamente (como reiniciar o actualizar el firmware) o utilizando un actuador (como encender una luz).

Esta lección introduce algunos de los protocolos de comunicación que los dispositivos IoT pueden usar para conectarse a la nube y los tipos de datos que podrían enviar o recibir. También tendrás la oportunidad de trabajar con ellos, añadiendo control por Internet a tu luz nocturna y moviendo la lógica de control del LED al código 'servidor' que se ejecuta localmente.

En esta lección cubriremos:

* [Protocolos de comunicación](../../../../../1-getting-started/lessons/4-connect-internet)
* [Transporte de Telemetría en Cola de Mensajes (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetría](../../../../../1-getting-started/lessons/4-connect-internet)
* [Comandos](../../../../../1-getting-started/lessons/4-connect-internet)

## Protocolos de comunicación

Existen varios protocolos de comunicación populares que los dispositivos IoT utilizan para comunicarse con Internet. Los más comunes se basan en la mensajería de publicación/suscripción a través de algún tipo de intermediario. Los dispositivos IoT se conectan al intermediario, publican telemetría y se suscriben a comandos. Los servicios en la nube también se conectan al intermediario, se suscriben a todos los mensajes de telemetría y publican comandos, ya sea para dispositivos específicos o para grupos de dispositivos.

![Los dispositivos IoT se conectan a un intermediario, publican telemetría y se suscriben a comandos. Los servicios en la nube se conectan al intermediario, se suscriben a toda la telemetría y envían comandos a dispositivos específicos.](../../../../../translated_images/es/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT es el protocolo de comunicación más popular para dispositivos IoT y se cubre en esta lección. Otros protocolos incluyen AMQP y HTTP/HTTPS.

## Transporte de Telemetría en Cola de Mensajes (MQTT)

[MQTT](http://mqtt.org) es un protocolo de mensajería ligero y de estándar abierto que puede enviar mensajes entre dispositivos. Fue diseñado en 1999 para monitorear oleoductos, antes de ser liberado como estándar abierto 15 años después por IBM.

MQTT tiene un único intermediario y múltiples clientes. Todos los clientes se conectan al intermediario, y este enruta los mensajes a los clientes relevantes. Los mensajes se enrutan utilizando temas nombrados, en lugar de enviarse directamente a un cliente individual. Un cliente puede publicar en un tema, y cualquier cliente que se suscriba a ese tema recibirá el mensaje.

![Dispositivo IoT publicando telemetría en el tema /telemetry, y el servicio en la nube suscribiéndose a ese tema](../../../../../translated_images/es/mqtt.cbf7f21d9adc3e17.webp)

✅ Investiga. Si tienes muchos dispositivos IoT, ¿cómo puedes asegurarte de que tu intermediario MQTT pueda manejar todos los mensajes?

### Conecta tu dispositivo IoT a MQTT

La primera parte para añadir control por Internet a tu luz nocturna es conectarla a un intermediario MQTT.

#### Tarea

Conecta tu dispositivo a un intermediario MQTT.

En esta parte de la lección, conectarás tu luz nocturna IoT a Internet para permitir que sea controlada de forma remota. Más adelante en esta lección, tu dispositivo IoT enviará un mensaje de telemetría a través de MQTT a un intermediario MQTT público con el nivel de luz, donde será recogido por un código de servidor que escribirás. Este código verificará el nivel de luz y enviará un mensaje de comando de vuelta al dispositivo indicándole que encienda o apague el LED.

El caso de uso real para una configuración como esta podría ser recopilar datos de múltiples sensores de luz antes de decidir encender las luces en un lugar con muchas luces, como un estadio. Esto podría evitar que las luces se enciendan si solo un sensor está cubierto por nubes o un pájaro, pero los otros sensores detectan suficiente luz.

✅ ¿Qué otras situaciones requerirían evaluar datos de múltiples sensores antes de enviar comandos?

En lugar de lidiar con las complejidades de configurar un intermediario MQTT como parte de esta tarea, puedes usar un servidor de prueba público que ejecuta [Eclipse Mosquitto](https://www.mosquitto.org), un intermediario MQTT de código abierto. Este intermediario de prueba está disponible públicamente en [test.mosquitto.org](https://test.mosquitto.org) y no requiere configurar una cuenta, lo que lo convierte en una excelente herramienta para probar clientes y servidores MQTT.

> 💁 Este intermediario de prueba es público y no seguro. Cualquiera podría estar escuchando lo que publicas, por lo que no debe usarse con datos que necesiten mantenerse privados.

![Un diagrama de flujo de la tarea mostrando los niveles de luz siendo leídos y verificados, y el LED siendo controlado](../../../../../translated_images/es/assignment-1-internet-flow.3256feab5f052fd2.webp)

Sigue el paso relevante a continuación para conectar tu dispositivo al intermediario MQTT:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Computadora de placa única - Raspberry Pi/Dispositivo IoT virtual](single-board-computer-mqtt.md)

### Una mirada más profunda a MQTT

Los temas pueden tener una jerarquía, y los clientes pueden suscribirse a diferentes niveles de la jerarquía utilizando comodines. Por ejemplo, puedes enviar mensajes de telemetría de temperatura al tema `/telemetry/temperature` y mensajes de humedad al tema `/telemetry/humidity`, luego en tu aplicación en la nube suscribirte al tema `/telemetry/*` para recibir tanto los mensajes de telemetría de temperatura como los de humedad.

Los mensajes pueden enviarse con una calidad de servicio (QoS), que determina la garantía de que el mensaje sea recibido.

* Una vez como máximo: el mensaje se envía solo una vez y el cliente y el intermediario no toman medidas adicionales para confirmar la entrega (enviar y olvidar).
* Al menos una vez: el mensaje se reintenta varias veces por el remitente hasta que se recibe una confirmación (entrega confirmada).
* Exactamente una vez: el remitente y el receptor realizan un proceso de dos niveles para garantizar que solo se reciba una copia del mensaje (entrega asegurada).

✅ ¿Qué situaciones podrían requerir un mensaje de entrega asegurada en lugar de un mensaje de enviar y olvidar?

Aunque el nombre es Transporte de Telemetría en Cola de Mensajes (MQTT), en realidad no admite colas de mensajes. Esto significa que si un cliente se desconecta y luego se vuelve a conectar, no recibirá mensajes enviados durante la desconexión, excepto aquellos mensajes que ya había comenzado a procesar utilizando el proceso de QoS. Los mensajes pueden tener una bandera de retención configurada. Si esta está configurada, el intermediario MQTT almacenará el último mensaje enviado en un tema con esta bandera y lo enviará a cualquier cliente que se suscriba posteriormente al tema. De esta manera, los clientes siempre recibirán el último mensaje.

MQTT también admite una función de mantener vivo que verifica si la conexión sigue activa durante largos intervalos entre mensajes.

> 🦟 [Mosquitto de la Fundación Eclipse](https://mosquitto.org) tiene un intermediario MQTT gratuito que puedes ejecutar tú mismo para experimentar con MQTT, junto con un intermediario MQTT público que puedes usar para probar tu código, alojado en [test.mosquitto.org](https://test.mosquitto.org).

Las conexiones MQTT pueden ser públicas y abiertas, o encriptadas y seguras utilizando nombres de usuario y contraseñas, o certificados.

> 💁 MQTT se comunica sobre TCP/IP, el mismo protocolo de red subyacente que HTTP, pero en un puerto diferente. También puedes usar MQTT sobre websockets para comunicarte con aplicaciones web que se ejecutan en un navegador, o en situaciones donde los firewalls u otras reglas de red bloquean las conexiones MQTT estándar.

## Telemetría

La palabra telemetría proviene de raíces griegas que significan medir de forma remota. La telemetría es el acto de recopilar datos de sensores y enviarlos a la nube.

> 💁 Uno de los primeros dispositivos de telemetría fue inventado en Francia en 1874 y enviaba datos en tiempo real sobre el clima y la profundidad de la nieve desde Mont Blanc a París. Utilizaba cables físicos, ya que las tecnologías inalámbricas no estaban disponibles en ese momento.

Volvamos al ejemplo del termostato inteligente de la Lección 1.

![Un termostato conectado a Internet utilizando múltiples sensores de habitación](../../../../../translated_images/es/telemetry.21e5d8b97649d2eb.webp)

El termostato tiene sensores de temperatura para recopilar telemetría. Lo más probable es que tenga un sensor de temperatura incorporado, y podría conectarse a múltiples sensores de temperatura externos a través de un protocolo inalámbrico como [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Un ejemplo de los datos de telemetría que enviaría podría ser:

| Nombre | Valor | Descripción |
| ------ | ----- | ----------- |
| `thermostat_temperature` | 18°C | La temperatura medida por el sensor de temperatura incorporado del termostato |
| `livingroom_temperature` | 19°C | La temperatura medida por un sensor de temperatura remoto que ha sido nombrado `livingroom` para identificar la habitación en la que se encuentra |
| `bedroom_temperature` | 21°C | La temperatura medida por un sensor de temperatura remoto que ha sido nombrado `bedroom` para identificar la habitación en la que se encuentra |

El servicio en la nube puede usar estos datos de telemetría para tomar decisiones sobre qué comandos enviar para controlar la calefacción.

### Envía telemetría desde tu dispositivo IoT

La siguiente parte para añadir control por Internet a tu luz nocturna es enviar la telemetría del nivel de luz al intermediario MQTT en un tema de telemetría.

#### Tarea - envía telemetría desde tu dispositivo IoT

Envía telemetría del nivel de luz al intermediario MQTT.

Los datos se envían codificados como JSON, abreviatura de JavaScript Object Notation, un estándar para codificar datos en texto utilizando pares clave/valor.

✅ Si no has trabajado con JSON antes, puedes aprender más sobre él en la [documentación de JSON.org](https://www.json.org/).

Sigue el paso relevante a continuación para enviar telemetría desde tu dispositivo al intermediario MQTT:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Computadora de placa única - Raspberry Pi/Dispositivo IoT virtual](single-board-computer-telemetry.md)

### Recibe telemetría del intermediario MQTT

No tiene sentido enviar telemetría si no hay nada en el otro extremo para escucharla. La telemetría del nivel de luz necesita algo que la escuche para procesar los datos. Este código 'servidor' es el tipo de código que implementarás en un servicio en la nube como parte de una aplicación IoT más grande, pero aquí vas a ejecutar este código localmente en tu computadora (o en tu Pi si estás programando directamente allí). El código del servidor consiste en una aplicación Python que escucha mensajes de telemetría a través de MQTT con niveles de luz. Más adelante en esta lección, harás que responda con un mensaje de comando con instrucciones para encender o apagar el LED.

✅ Investiga: ¿Qué sucede con los mensajes MQTT si no hay un receptor?

#### Instala Python y VS Code

Si no tienes Python y VS Code instalados localmente, necesitarás instalarlos ambos para programar el servidor. Si estás utilizando un dispositivo IoT virtual o estás trabajando en tu Raspberry Pi, puedes omitir este paso, ya que deberías tener esto instalado y configurado.

##### Tarea - instala Python y VS Code

Instala Python y VS Code.

1. Instala Python. Consulta la [página de descargas de Python](https://www.python.org/downloads/) para obtener instrucciones sobre cómo instalar la última versión de Python.

1. Instala Visual Studio Code (VS Code). Este es el editor que usarás para escribir tu código de dispositivo virtual en Python. Consulta la [documentación de VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) para obtener instrucciones sobre cómo instalar VS Code.
💁 Eres libre de usar cualquier IDE o editor de Python para estas lecciones si tienes una herramienta preferida, pero las lecciones darán instrucciones basadas en el uso de VS Code.
1. Instala la extensión Pylance de VS Code. Esta es una extensión para VS Code que proporciona soporte para el lenguaje Python. Consulta la [documentación de la extensión Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) para obtener instrucciones sobre cómo instalar esta extensión en VS Code.

#### Configura un entorno virtual de Python

Una de las características más potentes de Python es la capacidad de instalar [paquetes pip](https://pypi.org), que son paquetes de código escritos por otras personas y publicados en Internet. Puedes instalar un paquete pip en tu computadora con un solo comando y luego usar ese paquete en tu código. Usarás pip para instalar un paquete que permita la comunicación a través de MQTT.

Por defecto, cuando instalas un paquete, este está disponible en toda tu computadora, lo que puede generar problemas con las versiones de los paquetes, como que una aplicación dependa de una versión específica de un paquete que se rompe al instalar una nueva versión para otra aplicación. Para evitar este problema, puedes usar un [entorno virtual de Python](https://docs.python.org/3/library/venv.html), que es esencialmente una copia de Python en una carpeta dedicada. Cuando instalas paquetes pip, estos se instalan solo en esa carpeta.

##### Tarea - Configura un entorno virtual de Python

Configura un entorno virtual de Python e instala los paquetes pip para MQTT.

1. Desde tu terminal o línea de comandos, ejecuta lo siguiente en una ubicación de tu elección para crear y navegar a un nuevo directorio:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Ahora ejecuta lo siguiente para crear un entorno virtual en la carpeta `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Debes llamar explícitamente a `python3` para crear el entorno virtual en caso de que tengas Python 2 instalado además de Python 3 (la última versión). Si tienes Python 2 instalado, al llamar a `python` se usará Python 2 en lugar de Python 3.

1. Activa el entorno virtual:

    * En Windows:
        * Si estás usando el Command Prompt o el Command Prompt a través de Windows Terminal, ejecuta:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Si estás usando PowerShell, ejecuta:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * En macOS o Linux, ejecuta:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Estos comandos deben ejecutarse desde la misma ubicación donde ejecutaste el comando para crear el entorno virtual. Nunca necesitarás navegar dentro de la carpeta `.venv`; siempre debes ejecutar el comando de activación y cualquier comando para instalar paquetes o ejecutar código desde la carpeta en la que estabas cuando creaste el entorno virtual.

1. Una vez que el entorno virtual esté activado, el comando `python` por defecto ejecutará la versión de Python que se usó para crear el entorno virtual. Ejecuta lo siguiente para obtener la versión:

    ```sh
    python --version
    ```

    La salida será similar a la siguiente:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Tu versión de Python puede ser diferente; mientras sea la versión 3.6 o superior, está bien. Si no, elimina esta carpeta, instala una versión más reciente de Python e inténtalo de nuevo.

1. Ejecuta los siguientes comandos para instalar el paquete pip para [Paho-MQTT](https://pypi.org/project/paho-mqtt/), una biblioteca popular de MQTT.

    ```sh
    pip install paho-mqtt
    ```

    Este paquete pip solo se instalará en el entorno virtual y no estará disponible fuera de este.

#### Escribe el código del servidor

Ahora se puede escribir el código del servidor en Python.

##### Tarea - Escribe el código del servidor

Escribe el código del servidor.

1. Desde tu terminal o línea de comandos, ejecuta lo siguiente dentro del entorno virtual para crear un archivo Python llamado `app.py`:

    * En Windows, ejecuta:

        ```cmd
        type nul > app.py
        ```

    * En macOS o Linux, ejecuta:

        ```cmd
        touch app.py
        ```

1. Abre la carpeta actual en VS Code:

    ```sh
    code .
    ```

1. Cuando VS Code se inicie, activará el entorno virtual de Python. Esto se mostrará en la barra de estado inferior:

    ![VS Code mostrando el entorno virtual seleccionado](../../../../../translated_images/es/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Si el terminal de VS Code ya está ejecutándose cuando VS Code se inicia, no tendrá el entorno virtual activado. Lo más fácil es cerrar el terminal usando el botón **Kill the active terminal instance**:

    ![Botón de cerrar terminal activo en VS Code](../../../../../translated_images/es/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Lanza un nuevo terminal en VS Code seleccionando *Terminal -> New Terminal*, o presionando `` CTRL+` ``. El nuevo terminal cargará el entorno virtual, con la llamada para activarlo apareciendo en el terminal. El nombre del entorno virtual (`.venv`) también estará en el prompt:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Abre el archivo `app.py` desde el explorador de VS Code y agrega el siguiente código:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Reemplaza `<ID>` en la línea 6 con el ID único que usaste al crear el código de tu dispositivo.

    ⚠️ Este **debe** ser el mismo ID que usaste en tu dispositivo, o el código del servidor no se suscribirá ni publicará en el tema correcto.

    Este código crea un cliente MQTT con un nombre único y se conecta al broker *test.mosquitto.org*. Luego inicia un bucle de procesamiento que se ejecuta en un hilo en segundo plano escuchando mensajes en cualquier tema suscrito.

    El cliente se suscribe a mensajes en el tema de telemetría y define una función que se llama cuando se recibe un mensaje. Cuando se recibe un mensaje de telemetría, se llama a la función `handle_telemetry`, que imprime el mensaje recibido en la consola.

    Finalmente, un bucle infinito mantiene la aplicación en ejecución. El cliente MQTT está escuchando mensajes en un hilo en segundo plano y funciona todo el tiempo que la aplicación principal esté en ejecución.

1. Desde el terminal de VS Code, ejecuta lo siguiente para ejecutar tu aplicación Python:

    ```sh
    python app.py
    ```

    La aplicación comenzará a escuchar mensajes del dispositivo IoT.

1. Asegúrate de que tu dispositivo esté funcionando y enviando mensajes de telemetría. Ajusta los niveles de luz detectados por tu dispositivo físico o virtual. Los mensajes recibidos se imprimirán en el terminal.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    El archivo `app.py` en el entorno virtual del nightlight debe estar ejecutándose para que el archivo `app.py` en el entorno virtual del nightlight-server reciba los mensajes enviados.

> 💁 Puedes encontrar este código en la carpeta [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server).

### ¿Con qué frecuencia se debe enviar telemetría?

Una consideración importante con la telemetría es con qué frecuencia medir y enviar los datos. La respuesta es: depende. Si mides con frecuencia, puedes responder más rápido a los cambios en las mediciones, pero usas más energía, más ancho de banda, generas más datos y necesitas más recursos en la nube para procesarlos. Debes medir con la frecuencia suficiente, pero no demasiado.

Para un termostato, medir cada pocos minutos probablemente sea más que suficiente, ya que las temperaturas no cambian tan rápido. Si solo mides una vez al día, podrías terminar calentando tu casa para temperaturas nocturnas en medio de un día soleado, mientras que si mides cada segundo tendrás miles de mediciones de temperatura innecesariamente duplicadas que consumirán la velocidad y el ancho de banda de Internet del usuario (un problema para personas con planes de ancho de banda limitado), usarán más energía, lo que puede ser un problema para dispositivos alimentados por batería como sensores remotos, y aumentarán el costo de los recursos de computación en la nube del proveedor para procesarlos y almacenarlos.

Si estás monitoreando datos de una máquina en una fábrica que, si falla, podría causar daños catastróficos y millones de dólares en pérdidas, entonces medir varias veces por segundo podría ser necesario. Es mejor desperdiciar ancho de banda que perder telemetría que indique que una máquina necesita detenerse y repararse antes de que se rompa.

> 💁 En esta situación, podrías considerar tener un dispositivo de borde para procesar primero la telemetría y reducir la dependencia de Internet.

### Pérdida de conectividad

Las conexiones a Internet pueden ser poco confiables, con cortes comunes. ¿Qué debería hacer un dispositivo IoT en estas circunstancias: perder los datos o almacenarlos hasta que se restablezca la conectividad? Nuevamente, la respuesta es: depende.

Para un termostato, los datos probablemente puedan perderse tan pronto como se tome una nueva medición de temperatura. Al sistema de calefacción no le importa que hace 20 minutos la temperatura fuera de 20.5°C si ahora es de 19°C; es la temperatura actual la que determina si la calefacción debe estar encendida o apagada.

Para maquinaria, podrías querer conservar los datos, especialmente si se usan para buscar tendencias. Hay modelos de aprendizaje automático que pueden detectar anomalías en flujos de datos observando datos de un período de tiempo definido (como la última hora) y detectando datos anómalos. Esto se usa a menudo para mantenimiento predictivo, buscando indicios de que algo podría romperse pronto para que puedas repararlo o reemplazarlo antes de que eso ocurra. Podrías querer que se envíe cada bit de telemetría de una máquina para que pueda procesarse para la detección de anomalías, por lo que una vez que el dispositivo IoT pueda reconectarse, enviará toda la telemetría generada durante el corte de Internet.

Los diseñadores de dispositivos IoT también deberían considerar si el dispositivo IoT puede usarse durante un corte de Internet o pérdida de señal causada por la ubicación. Un termostato inteligente debería poder tomar algunas decisiones limitadas para controlar la calefacción si no puede enviar telemetría a la nube debido a un corte.

[![Este Ferrari quedó inutilizado porque alguien intentó actualizarlo bajo tierra donde no hay recepción celular](../../../../../translated_images/es/bricked-car.dc38f8efadc6c59d.webp)](https://twitter.com/internetofshit/status/1315736960082808832)

Para que MQTT maneje una pérdida de conectividad, el código del dispositivo y del servidor deberá ser responsable de garantizar la entrega de mensajes si es necesario, por ejemplo, exigiendo que todos los mensajes enviados sean respondidos con mensajes adicionales en un tema de respuesta, y si no lo son, se coloquen en cola manualmente para reproducirlos más tarde.

## Comandos

Los comandos son mensajes enviados desde la nube a un dispositivo, instruyéndolo para que haga algo. La mayoría de las veces esto implica dar algún tipo de salida a través de un actuador, pero también puede ser una instrucción para el propio dispositivo, como reiniciarse o recopilar telemetría adicional y devolverla como respuesta al comando.

![Un termostato conectado a Internet recibiendo un comando para encender la calefacción](../../../../../translated_images/es/commands.d6c06bbbb3a02cce.webp)

Un termostato podría recibir un comando desde la nube para encender la calefacción. Basándose en los datos de telemetría de todos los sensores, si el servicio en la nube ha decidido que la calefacción debe estar encendida, enviará el comando correspondiente.

### Enviar comandos al broker MQTT

El siguiente paso para nuestra luz nocturna controlada por Internet es que el código del servidor envíe un comando de vuelta al dispositivo IoT para controlar la luz según los niveles de luz que detecte.

1. Abre el código del servidor en VS Code.

1. Agrega la siguiente línea después de la declaración de `client_telemetry_topic` para definir en qué tema enviar comandos:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Agrega el siguiente código al final de la función `handle_telemetry`:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Esto envía un mensaje JSON al tema de comandos con el valor de `led_on` configurado en true o false dependiendo de si la luz es menor a 300 o no. Si la luz es menor a 300, se envía true para instruir al dispositivo que encienda el LED.

1. Ejecuta el código como antes.

1. Ajusta los niveles de luz detectados por tu dispositivo físico o virtual. Los mensajes recibidos y los comandos enviados se escribirán en el terminal:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 La telemetría y los comandos se están enviando en un único tema cada uno. Esto significa que la telemetría de múltiples dispositivos aparecerá en el mismo tema de telemetría, y los comandos para múltiples dispositivos aparecerán en el mismo tema de comandos. Si quisieras enviar un comando a un dispositivo específico, podrías usar múltiples temas, nombrados con un ID único de dispositivo, como `/commands/device1`, `/commands/device2`. De esa manera, un dispositivo puede escuchar mensajes destinados solo a ese dispositivo.

> 💁 Puedes encontrar este código en la carpeta [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server).

### Manejar comandos en el dispositivo IoT

Ahora que se están enviando comandos desde el servidor, puedes agregar código al dispositivo IoT para manejarlos y controlar el LED.

Sigue el paso relevante a continuación para escuchar comandos desde el broker MQTT:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Computadora de placa única - Raspberry Pi/Dispositivo IoT virtual](single-board-computer-commands.md)

Una vez que este código esté escrito y en ejecución, experimenta cambiando los niveles de luz. Observa la salida del servidor y del dispositivo, y observa el LED mientras cambias los niveles de luz.

### Pérdida de conectividad

¿Qué debería hacer un servicio en la nube si necesita enviar un comando a un dispositivo IoT que está desconectado? Nuevamente, la respuesta es: depende.

Si el último comando anula uno anterior, entonces probablemente se puedan ignorar los anteriores. Si un servicio en la nube envía un comando para encender la calefacción y luego envía un comando para apagarla, entonces el comando de encendido puede ignorarse y no reenviarse.

Si los comandos necesitan procesarse en secuencia, como mover un brazo robótico hacia arriba y luego cerrar un agarrador, entonces deben enviarse en orden una vez que se restablezca la conectividad.

✅ ¿Cómo podría el código del dispositivo o del servidor garantizar que los comandos siempre se envíen y manejen en orden a través de MQTT si es necesario?

---

## 🚀 Desafío

El desafío en las últimas tres lecciones fue listar tantos dispositivos IoT como puedas que estén en tu hogar, escuela o lugar de trabajo, y decidir si están construidos alrededor de microcontroladores o computadoras de placa única, o incluso una mezcla de ambos, y pensar en qué sensores y actuadores están utilizando.
Para estos dispositivos, piensa en qué mensajes podrían estar enviando o recibiendo. ¿Qué telemetría envían? ¿Qué mensajes o comandos podrían recibir? ¿Crees que son seguros?

## Cuestionario posterior a la clase

[Cuestionario posterior a la clase](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Revisión y estudio autónomo

Lee más sobre MQTT en la [página de Wikipedia de MQTT](https://wikipedia.org/wiki/MQTT).

Intenta ejecutar un broker MQTT tú mismo usando [Mosquitto](https://www.mosquitto.org) y conéctalo desde tu dispositivo IoT y código de servidor.

> 💁 Consejo - por defecto, Mosquitto no permite conexiones anónimas (es decir, conectarse sin un nombre de usuario y contraseña), y no permite conexiones desde fuera del ordenador en el que se está ejecutando.  
> Puedes solucionar esto con un [archivo de configuración `mosquitto.conf`](https://www.mosquitto.org/man/mosquitto-conf-5.html) con lo siguiente:  
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Tarea

[Compara y contrasta MQTT con otros protocolos de comunicación](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.