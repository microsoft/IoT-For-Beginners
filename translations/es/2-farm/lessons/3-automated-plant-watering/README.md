<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f7bb24ba53fb627ddb38a8b24a05e594",
  "translation_date": "2025-08-26T14:33:40+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/README.md",
  "language_code": "es"
}
-->
# Riego automatizado de plantas

![Una vista general en sketchnote de esta lección](../../../../../translated_images/lesson-7.30b5f577d3cb8e031238751475cb519c7d6dbaea261b5df4643d086ffb2a03bb.es.jpg)

> Sketchnote por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

Esta lección fue impartida como parte de la serie [IoT para principiantes Proyecto 2 - Agricultura digital](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) del [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Riego automatizado de plantas impulsado por IoT](https://img.youtube.com/vi/g9FfZwv9R58/0.jpg)](https://youtu.be/g9FfZwv9R58)

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/13)

## Introducción

En la última lección, aprendiste cómo monitorear la humedad del suelo. En esta lección aprenderás a construir los componentes principales de un sistema de riego automatizado que responde a la humedad del suelo. También aprenderás sobre el tiempo de respuesta: cómo los sensores pueden tardar en reaccionar a los cambios y cómo los actuadores pueden tardar en modificar las propiedades que los sensores están midiendo.

En esta lección cubriremos:

* [Controlar dispositivos de alta potencia desde un dispositivo IoT de baja potencia](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Controlar un relé](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Controlar tu planta mediante MQTT](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Tiempo de respuesta de sensores y actuadores](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Agregar temporización al servidor de control de tu planta](../../../../../2-farm/lessons/3-automated-plant-watering)

## Controlar dispositivos de alta potencia desde un dispositivo IoT de baja potencia

Los dispositivos IoT utilizan un voltaje bajo. Aunque esto es suficiente para sensores y actuadores de baja potencia como LEDs, es demasiado bajo para controlar hardware más grande, como una bomba de agua utilizada para riego. Incluso las bombas pequeñas que podrías usar para plantas de interior consumen demasiada corriente para un kit de desarrollo IoT y podrían dañar la placa.

> 🎓 La corriente, medida en amperios (A), es la cantidad de electricidad que fluye a través de un circuito. El voltaje proporciona el empuje, la corriente es cuánto se empuja. Puedes leer más sobre la corriente en la [página de corriente eléctrica en Wikipedia](https://wikipedia.org/wiki/Electric_current).

La solución a esto es conectar una bomba a una fuente de alimentación externa y usar un actuador para encender la bomba, similar a cómo encenderías una luz. Se necesita una pequeña cantidad de energía (en forma de energía en tu cuerpo) para que tu dedo accione un interruptor, y esto conecta la luz a la electricidad de red que funciona a 110v/240v.

![Un interruptor de luz enciende la luz](../../../../../translated_images/light-switch.760317ad6ab8bd6d611da5352dfe9c73a94a0822ccec7df3c8bae35da18e1658.es.png)

> 🎓 [Electricidad de red](https://wikipedia.org/wiki/Mains_electricity) se refiere a la electricidad entregada a hogares y negocios a través de infraestructura nacional en muchas partes del mundo.

✅ Los dispositivos IoT generalmente pueden proporcionar 3.3V o 5V, con menos de 1 amperio (1A) de corriente. Comparado con la electricidad de red, que suele ser de 230V (120V en América del Norte y 100V en Japón), y puede proporcionar energía para dispositivos que consumen hasta 30A.

Existen varios actuadores que pueden hacer esto, incluidos dispositivos mecánicos que puedes conectar a interruptores existentes para imitar un dedo encendiéndolos. El más popular es un relé.

### Relés

Un relé es un interruptor electromecánico que convierte una señal eléctrica en un movimiento mecánico que enciende un interruptor. El núcleo de un relé es un electroimán.

> 🎓 [Electroimanes](https://wikipedia.org/wiki/Electromagnet) son imanes que se crean al pasar electricidad a través de una bobina de alambre. Cuando la electricidad está encendida, la bobina se magnetiza. Cuando la electricidad está apagada, la bobina pierde su magnetismo.

![Cuando está encendido, el electroimán crea un campo magnético, activando el interruptor del circuito de salida](../../../../../translated_images/relay-on.4db16a0fd6b66926.es.png)

En un relé, un circuito de control alimenta el electroimán. Cuando el electroimán está encendido, tira de una palanca que mueve un interruptor, cerrando un par de contactos y completando un circuito de salida.

![Cuando está apagado, el electroimán no crea un campo magnético, desactivando el interruptor del circuito de salida](../../../../../translated_images/relay-off.c34a178a2960fecd.es.png)

Cuando el circuito de control está apagado, el electroimán se apaga, liberando la palanca y abriendo los contactos, apagando el circuito de salida. Los relés son actuadores digitales: una señal alta al relé lo enciende, una señal baja lo apaga.

El circuito de salida puede usarse para alimentar hardware adicional, como un sistema de riego. El dispositivo IoT puede encender el relé, completando el circuito de salida que alimenta el sistema de riego, y las plantas se riegan. Luego, el dispositivo IoT puede apagar el relé, cortando la energía al sistema de riego y deteniendo el agua.

![Un relé encendiéndose, activando una bomba que envía agua a una planta](../../../../../images/strawberry-pump.gif)

En el video anterior, se enciende un relé. Un LED en el relé se ilumina para indicar que está encendido (algunas placas de relé tienen LEDs para indicar si el relé está encendido o apagado), y se envía energía a la bomba, activándola y bombeando agua a una planta.

> 💁 Los relés también pueden usarse para alternar entre dos circuitos de salida en lugar de encender y apagar uno. A medida que la palanca se mueve, cambia un interruptor de completar un circuito de salida a completar un circuito de salida diferente, generalmente compartiendo una conexión de alimentación común o una conexión de tierra común.

✅ Investiga: Hay múltiples tipos de relés, con diferencias como si el circuito de control enciende o apaga el relé cuando se aplica energía, o múltiples circuitos de salida. Investiga sobre estos diferentes tipos.

Cuando la palanca se mueve, generalmente puedes escucharla hacer contacto con el electroimán con un ruido de clic bien definido.

> 💁 Un relé puede cablearse de manera que al hacer la conexión realmente interrumpa la energía al relé, apagándolo, lo que luego envía energía al relé encendiéndolo nuevamente, y así sucesivamente. Esto significa que el relé hará clic increíblemente rápido, produciendo un ruido de zumbido. Así es como funcionaban algunos de los primeros timbres eléctricos utilizados en puertas.

### Energía del relé

El electroimán no necesita mucha energía para activarse y tirar de la palanca, puede controlarse utilizando la salida de 3.3V o 5V de un kit de desarrollo IoT. El circuito de salida puede transportar mucha más energía, dependiendo del relé, incluyendo voltaje de red o incluso niveles de energía más altos para uso industrial. De esta manera, un kit de desarrollo IoT puede controlar un sistema de riego, desde una pequeña bomba para una sola planta, hasta un sistema industrial masivo para toda una granja comercial.

![Un relé Grove con el circuito de control, circuito de salida y relé etiquetados](../../../../../translated_images/grove-relay-labelled.293e068f5c3c2a199bd7892f2661fdc9e10c920b535cfed317fbd6d1d4ae1168.es.png)

La imagen anterior muestra un relé Grove. El circuito de control se conecta a un dispositivo IoT y enciende o apaga el relé utilizando 3.3V o 5V. El circuito de salida tiene dos terminales, cualquiera de ellos puede ser alimentación o tierra. El circuito de salida puede manejar hasta 250V a 10A, suficiente para una variedad de dispositivos alimentados por red. Puedes obtener relés que pueden manejar incluso niveles de energía más altos.

![Una bomba conectada a través de un relé](../../../../../translated_images/pump-wired-to-relay.66c5cfc0d8918990.es.png)

En la imagen anterior, la energía se suministra a una bomba a través de un relé. Hay un cable rojo que conecta el terminal +5V de una fuente de alimentación USB a un terminal del circuito de salida del relé, y otro cable rojo que conecta el otro terminal del circuito de salida a la bomba. Un cable negro conecta la bomba a la tierra de la fuente de alimentación USB. Cuando el relé se enciende, completa el circuito, enviando 5V a la bomba y activándola.

## Controlar un relé

Puedes controlar un relé desde tu kit de desarrollo IoT.

### Tarea - controlar un relé

Sigue la guía correspondiente para controlar un relé utilizando tu dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-relay.md)
* [Computadora de placa única - Raspberry Pi](pi-relay.md)
* [Computadora de placa única - Dispositivo virtual](virtual-device-relay.md)

## Controlar tu planta mediante MQTT

Hasta ahora, tu relé es controlado directamente por el dispositivo IoT basado en una sola lectura de humedad del suelo. En un sistema de riego comercial, la lógica de control estará centralizada, permitiendo tomar decisiones sobre el riego utilizando datos de múltiples sensores y permitiendo que cualquier configuración se cambie en un solo lugar. Para simular esto, puedes controlar el relé mediante MQTT.

### Tarea - controlar el relé mediante MQTT

1. Agrega las bibliotecas/pip packages y el código relevantes de MQTT a tu proyecto `soil-moisture-sensor` para conectarte a MQTT. Nombra el ID del cliente como `soilmoisturesensor_client` precedido por tu ID.

    > ⚠️ Puedes consultar [las instrucciones para conectarte a MQTT en el proyecto 1, lección 4 si es necesario](../../../1-getting-started/lessons/4-connect-internet/README.md#connect-your-iot-device-to-mqtt).

1. Agrega el código del dispositivo relevante para enviar telemetría con las configuraciones de humedad del suelo. Para el mensaje de telemetría, nombra la propiedad `soil_moisture`.

    > ⚠️ Puedes consultar [las instrucciones para enviar telemetría a MQTT en el proyecto 1, lección 4 si es necesario](../../../1-getting-started/lessons/4-connect-internet/README.md#send-telemetry-from-your-iot-device).

1. Crea un código de servidor local para suscribirte a la telemetría y enviar un comando para controlar el relé en una carpeta llamada `soil-moisture-sensor-server`. Nombra la propiedad en el mensaje de comando `relay_on`, y establece el ID del cliente como `soilmoisturesensor_server` precedido por tu ID. Mantén la misma estructura que el código del servidor que escribiste para el proyecto 1, lección 4, ya que agregarás más código a este más adelante en esta lección.

    > ⚠️ Puedes consultar [las instrucciones para enviar telemetría a MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#write-the-server-code) y [enviar comandos mediante MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#send-commands-to-the-mqtt-broker) en el proyecto 1, lección 4 si es necesario.

1. Agrega el código del dispositivo relevante para controlar el relé a partir de los comandos recibidos, utilizando la propiedad `relay_on` del mensaje. Envía true para `relay_on` si el `soil_moisture` es mayor que 450, de lo contrario envía false, igual que la lógica que agregaste para el dispositivo IoT anteriormente.

    > ⚠️ Puedes consultar [las instrucciones para responder a comandos de MQTT en el proyecto 1, lección 4 si es necesario](../../../1-getting-started/lessons/4-connect-internet/README.md#handle-commands-on-the-iot-device).

> 💁 Puedes encontrar este código en la carpeta [code-mqtt](../../../../../2-farm/lessons/3-automated-plant-watering/code-mqtt).

Asegúrate de que el código esté ejecutándose en tu dispositivo y servidor local, y pruébalo cambiando los niveles de humedad del suelo, ya sea modificando los valores enviados por el sensor virtual o cambiando los niveles de humedad del suelo agregando agua o retirando el sensor del suelo.

## Tiempo de respuesta de sensores y actuadores

En la lección 3 construiste una luz nocturna: un LED que se enciende tan pronto como un nivel bajo de luz es detectado por un sensor de luz. El sensor de luz detectó un cambio en los niveles de luz instantáneamente, y el dispositivo pudo responder rápidamente, limitado solo por la duración del retraso en la función `loop` o el bucle `while True:`. Como desarrollador de IoT, no siempre puedes confiar en un ciclo de retroalimentación tan rápido.

### Temporización para la humedad del suelo

Si realizaste la última lección sobre humedad del suelo utilizando un sensor físico, habrás notado que tomó unos segundos para que la lectura de humedad del suelo bajara después de regar tu planta. Esto no se debe a que el sensor sea lento, sino a que el agua tarda en filtrarse a través del suelo.
💁 Si regaste demasiado cerca del sensor, es posible que hayas notado que la lectura bajó rápidamente y luego volvió a subir. Esto ocurre porque el agua cerca del sensor se dispersa por el resto del suelo, reduciendo la humedad del suelo alrededor del sensor.
![Una medición de humedad del suelo de 658 no cambia durante el riego, solo baja a 320 después de que el agua ha empapado el suelo](../../../../../translated_images/soil-moisture-travel.a0e31af222cf1438.es.png)

En el diagrama anterior, una lectura de humedad del suelo muestra 658. La planta es regada, pero esta lectura no cambia inmediatamente, ya que el agua aún no ha llegado al sensor. Incluso el riego puede terminar antes de que el agua alcance el sensor y el valor baje para reflejar el nuevo nivel de humedad.

Si estuvieras escribiendo código para controlar un sistema de riego mediante un relé basado en los niveles de humedad del suelo, tendrías que tener en cuenta este retraso y construir un sistema de temporización más inteligente en tu dispositivo IoT.

✅ Tómate un momento para pensar cómo podrías hacer esto.

### Controlar la temporización del sensor y el actuador

Imagina que te han encargado construir un sistema de riego para una granja. Según el tipo de suelo, se ha determinado que el nivel ideal de humedad del suelo para las plantas corresponde a una lectura de voltaje analógico de 400-450.

Podrías programar el dispositivo de la misma manera que una luz nocturna: todo el tiempo que el sensor lea por encima de 450, encender un relé para activar una bomba. El problema es que el agua tarda un tiempo en llegar desde la bomba, atravesar el suelo y alcanzar el sensor. El sensor detendrá el agua cuando detecte un nivel de 450, pero el nivel de agua seguirá bajando mientras el agua bombeada sigue empapando el suelo. El resultado final es agua desperdiciada y el riesgo de dañar las raíces.

✅ Recuerda: demasiada agua puede ser tan perjudicial para las plantas como muy poca, y desperdicia un recurso valioso.

La mejor solución es entender que hay un retraso entre el momento en que el actuador se activa y el cambio en la propiedad que el sensor mide. Esto significa que no solo el sensor debe esperar un tiempo antes de medir el valor nuevamente, sino que el actuador debe apagarse por un tiempo antes de que se realice la siguiente medición del sensor.

¿Cuánto tiempo debe estar encendido el relé cada vez? Es mejor pecar de precavido y encender el relé solo por un corto tiempo, luego esperar a que el agua empape el suelo y volver a verificar los niveles de humedad. Después de todo, siempre puedes encenderlo nuevamente para agregar más agua, pero no puedes quitar agua del suelo.

> 💁 Este tipo de control de temporización es muy específico para el dispositivo IoT que estás construyendo, la propiedad que estás midiendo y los sensores y actuadores utilizados.

![Una planta de fresa conectada al agua mediante una bomba, con la bomba conectada a un relé. El relé y un sensor de humedad del suelo en la planta están conectados a un Raspberry Pi](../../../../../translated_images/strawberry-with-pump.b410fc72ac6aabad.es.png)

Por ejemplo, tengo una planta de fresa con un sensor de humedad del suelo y una bomba controlada por un relé. He observado que cuando agrego agua, tarda unos 20 segundos en estabilizarse la lectura de humedad del suelo. Esto significa que necesito apagar el relé y esperar 20 segundos antes de verificar los niveles de humedad. Prefiero tener poca agua que demasiada: siempre puedo encender la bomba nuevamente, pero no puedo quitar agua de la planta.

![Paso 1, tomar medición. Paso 2, agregar agua. Paso 3, esperar a que el agua empape el suelo. Paso 4, volver a tomar medición](../../../../../translated_images/soil-moisture-delay.865f3fae206db01d.es.png)

Esto significa que el mejor proceso sería un ciclo de riego que sea algo como:

* Encender la bomba durante 5 segundos
* Esperar 20 segundos
* Verificar la humedad del suelo
* Si el nivel sigue siendo superior al necesario, repetir los pasos anteriores

5 segundos podrían ser demasiado tiempo para la bomba, especialmente si los niveles de humedad están solo ligeramente por encima del nivel requerido. La mejor manera de saber qué temporización usar es probarla y luego ajustarla cuando tengas datos del sensor, con un bucle de retroalimentación constante. Esto incluso puede llevar a una temporización más granular, como encender la bomba durante 1 segundo por cada 100 por encima del nivel de humedad requerido, en lugar de un tiempo fijo de 5 segundos.

✅ Investiga: ¿Existen otras consideraciones de temporización? ¿Se puede regar la planta en cualquier momento que la humedad del suelo sea demasiado baja, o hay momentos específicos del día que son buenos y malos para regar las plantas?

> 💁 Las predicciones meteorológicas también pueden tomarse en cuenta al controlar sistemas de riego automatizados para cultivos al aire libre. Si se espera lluvia, entonces el riego puede posponerse hasta después de que termine la lluvia. En ese momento, el suelo podría estar lo suficientemente húmedo como para no necesitar riego, mucho más eficiente que desperdiciar agua regando justo antes de la lluvia.

## Agregar temporización a tu servidor de control de plantas

El código del servidor puede modificarse para agregar control alrededor de la temporización del ciclo de riego y esperar a que los niveles de humedad del suelo cambien. La lógica del servidor para controlar la temporización del relé es:

1. Mensaje de telemetría recibido
1. Verificar el nivel de humedad del suelo
1. Si está bien, no hacer nada. Si la lectura es demasiado alta (lo que significa que la humedad del suelo es demasiado baja), entonces:
    1. Enviar un comando para encender el relé
    1. Esperar 5 segundos
    1. Enviar un comando para apagar el relé
    1. Esperar 20 segundos para que los niveles de humedad del suelo se estabilicen

El ciclo de riego, el proceso desde recibir el mensaje de telemetría hasta estar listo para procesar nuevamente los niveles de humedad del suelo, toma aproximadamente 25 segundos. Estamos enviando niveles de humedad del suelo cada 10 segundos, por lo que hay un solapamiento donde se recibe un mensaje mientras el servidor está esperando que los niveles de humedad del suelo se estabilicen, lo que podría iniciar otro ciclo de riego.

Hay dos opciones para solucionar esto:

* Cambiar el código del dispositivo IoT para enviar telemetría solo cada minuto, de esta manera el ciclo de riego se completará antes de que se envíe el siguiente mensaje
* Cancelar la suscripción a la telemetría durante el ciclo de riego

La primera opción no siempre es una buena solución para grandes granjas. El agricultor podría querer capturar los niveles de humedad del suelo mientras se está regando para un análisis posterior, por ejemplo, para estar al tanto del flujo de agua en diferentes áreas de la granja y guiar un riego más específico. La segunda opción es mejor: el código simplemente ignora la telemetría cuando no puede usarla, pero la telemetría sigue estando disponible para otros servicios que puedan suscribirse a ella.

> 💁 Los datos de IoT no se envían desde un solo dispositivo a un solo servicio, en cambio, muchos dispositivos pueden enviar datos a un broker, y muchos servicios pueden escuchar los datos del broker. Por ejemplo, un servicio podría escuchar los datos de humedad del suelo y almacenarlos en una base de datos para análisis posterior. Otro servicio también puede escuchar la misma telemetría para controlar un sistema de riego.

### Tarea - agregar temporización a tu servidor de control de plantas

Actualiza tu código de servidor para ejecutar el relé durante 5 segundos y luego esperar 20 segundos.

1. Abre la carpeta `soil-moisture-sensor-server` en VS Code si aún no está abierta. Asegúrate de que el entorno virtual esté activado.

1. Abre el archivo `app.py`

1. Agrega el siguiente código al archivo `app.py` debajo de las importaciones existentes:

    ```python
    import threading
    ```

    Esta declaración importa `threading` de las bibliotecas de Python. Threading permite que Python ejecute otro código mientras espera.

1. Agrega el siguiente código antes de la función `handle_telemetry` que maneja los mensajes de telemetría recibidos por el código del servidor:

    ```python
    water_time = 5
    wait_time = 20
    ```

    Esto define cuánto tiempo ejecutar el relé (`water_time`) y cuánto tiempo esperar después para verificar la humedad del suelo (`wait_time`).

1. Debajo de este código, agrega lo siguiente:

    ```python
    def send_relay_command(client, state):
        command = { 'relay_on' : state }
        print("Sending message:", command)
        client.publish(server_command_topic, json.dumps(command))
    ```

    Este código define una función llamada `send_relay_command` que envía un comando a través de MQTT para controlar el relé. La telemetría se crea como un diccionario y luego se convierte en una cadena JSON. El valor pasado en `state` determina si el relé debe estar encendido o apagado.

1. Después de la función `send_relay_code`, agrega el siguiente código:

    ```python
    def control_relay(client):
        print("Unsubscribing from telemetry")
        mqtt_client.unsubscribe(client_telemetry_topic)
    
        send_relay_command(client, True)
        time.sleep(water_time)
        send_relay_command(client, False)
    
        time.sleep(wait_time)
    
        print("Subscribing to telemetry")
        mqtt_client.subscribe(client_telemetry_topic)
    ```

    Esto define una función para controlar el relé según la temporización requerida. Comienza cancelando la suscripción a la telemetría para que los mensajes de humedad del suelo no se procesen mientras se realiza el riego. Luego envía un comando para encender el relé. Después espera el tiempo definido en `water_time` antes de enviar un comando para apagar el relé. Finalmente, espera que los niveles de humedad del suelo se estabilicen durante el tiempo definido en `wait_time`. Luego vuelve a suscribirse a la telemetría.

1. Cambia la función `handle_telemetry` por la siguiente:

    ```python
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['soil_moisture'] > 450:
            threading.Thread(target=control_relay, args=(client,)).start()
    ```

    Este código verifica el nivel de humedad del suelo. Si es mayor que 450, el suelo necesita riego, por lo que llama a la función `control_relay`. Esta función se ejecuta en un hilo separado, funcionando en segundo plano.

1. Asegúrate de que tu dispositivo IoT esté funcionando, luego ejecuta este código. Cambia los niveles de humedad del suelo y observa qué sucede con el relé: debería encenderse durante 5 segundos y luego permanecer apagado al menos 20 segundos, encendiéndose solo si los niveles de humedad del suelo no son suficientes.

    ```output
    (.venv) ➜  soil-moisture-sensor-server ✗ python app.py
    Message received: {'soil_moisture': 457}
    Unsubscribing from telemetry
    Sending message: {'relay_on': True}
    Sending message: {'relay_on': False}
    Subscribing to telemetry
    Message received: {'soil_moisture': 302}
    ```

    Una buena manera de probar esto en un sistema de riego simulado es usar suelo seco y luego verter agua manualmente mientras el relé está encendido, deteniendo el vertido cuando el relé se apaga.

> 💁 Puedes encontrar este código en la carpeta [code-timing](../../../../../2-farm/lessons/3-automated-plant-watering/code-timing).

> 💁 Si deseas usar una bomba para construir un sistema de riego real, puedes usar una [bomba de agua de 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html) con una [fuente de alimentación USB](https://www.adafruit.com/product/3628). Asegúrate de que la alimentación hacia o desde la bomba esté conectada a través del relé.

---

## 🚀 Desafío

¿Puedes pensar en otros dispositivos IoT o eléctricos que tengan un problema similar donde los resultados del actuador tardan en llegar al sensor? Probablemente tengas algunos en tu casa o escuela.

* ¿Qué propiedades miden?
* ¿Cuánto tiempo tarda en cambiar la propiedad después de que se usa un actuador?
* ¿Está bien que la propiedad cambie más allá del valor requerido?
* ¿Cómo puede volver al valor requerido si es necesario?

## Cuestionario posterior a la clase

[Cuestionario posterior a la clase](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/14)

## Revisión y autoestudio

* Lee más sobre relés, incluyendo su uso histórico en centrales telefónicas, en la [página de Wikipedia sobre relés](https://wikipedia.org/wiki/Relay).

## Asignación

[Construir un ciclo de riego más eficiente](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.