<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "81c437c568eee1b0dda1f04e88150d37",
  "translation_date": "2025-08-26T14:53:39+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/README.md",
  "language_code": "es"
}
-->
# Mantén tu planta segura

![Un resumen visual de esta lección](../../../../../translated_images/lesson-10.829c86b80b9403bb770929ee553a1d293afe50dc23121aaf9be144673ae012cc.es.jpg)

> Dibujo por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para verla en mayor tamaño.

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Introducción

En las últimas lecciones has creado un dispositivo IoT para monitorear el suelo y lo has conectado a la nube. Pero, ¿qué pasaría si hackers que trabajan para un agricultor rival lograran tomar el control de tus dispositivos IoT? ¿Y si enviaran lecturas falsas de alta humedad del suelo para que tus plantas nunca se rieguen, o activaran tu sistema de riego constantemente, matando tus plantas por exceso de agua y generándote un gran gasto en agua?

En esta lección aprenderás sobre cómo proteger los dispositivos IoT. Como esta es la última lección de este proyecto, también aprenderás a limpiar tus recursos en la nube, reduciendo posibles costos.

En esta lección cubriremos:

* [¿Por qué necesitas proteger los dispositivos IoT?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Criptografía](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Protege tus dispositivos IoT](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Genera y utiliza un certificado X.509](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 Esta es la última lección de este proyecto, así que después de completar esta lección y la tarea, no olvides limpiar tus servicios en la nube. Necesitarás los servicios para completar la tarea, así que asegúrate de terminarla primero.
>
> Consulta [la guía para limpiar tu proyecto](../../../clean-up.md) si necesitas instrucciones sobre cómo hacerlo.

## ¿Por qué necesitas proteger los dispositivos IoT?

La seguridad en IoT implica garantizar que solo los dispositivos esperados puedan conectarse a tu servicio IoT en la nube y enviarle telemetría, y que solo tu servicio en la nube pueda enviar comandos a tus dispositivos. Los datos de IoT también pueden ser personales, incluyendo datos médicos o íntimos, por lo que toda tu aplicación debe considerar la seguridad para evitar que estos datos se filtren.

Si tu aplicación IoT no es segura, existen varios riesgos:

* Un dispositivo falso podría enviar datos incorrectos, haciendo que tu aplicación responda de manera incorrecta. Por ejemplo, podrían enviar lecturas constantes de alta humedad del suelo, lo que significaría que tu sistema de riego nunca se active y tus plantas mueran por falta de agua.
* Usuarios no autorizados podrían leer datos de los dispositivos IoT, incluyendo datos personales o críticos para el negocio.
* Hackers podrían enviar comandos para controlar un dispositivo de una manera que podría causar daños al dispositivo o al hardware conectado.
* Al conectarse a un dispositivo IoT, los hackers podrían usarlo para acceder a redes adicionales y obtener acceso a sistemas privados.
* Usuarios malintencionados podrían acceder a datos personales y utilizarlos para chantaje.

Estos son escenarios del mundo real y ocurren todo el tiempo. Algunos ejemplos se mencionaron en lecciones anteriores, pero aquí hay algunos más:

* En 2018, hackers usaron un punto de acceso WiFi abierto en un termostato de pecera para acceder a la red de un casino y robar datos. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* En 2016, el botnet Mirai lanzó un ataque de denegación de servicio contra Dyn, un proveedor de servicios de Internet, dejando fuera de servicio grandes partes de Internet. Este botnet utilizó malware para conectarse a dispositivos IoT como grabadoras de video y cámaras que usaban nombres de usuario y contraseñas predeterminados, y desde allí lanzó el ataque. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys tenía una base de datos de usuarios de sus juguetes conectados CloudPets disponible públicamente en Internet. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava etiquetaba a corredores que pasaban cerca y mostraba sus rutas, permitiendo a extraños ver dónde vivían. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Investiga: Busca más ejemplos de hacks y brechas de datos en IoT, especialmente con objetos personales como cepillos de dientes o básculas conectadas a Internet. Reflexiona sobre el impacto que estos hacks podrían tener en las víctimas o clientes.

> 💁 La seguridad es un tema enorme, y esta lección solo tocará algunos de los conceptos básicos sobre la conexión de tu dispositivo a la nube. Otros temas que no se cubrirán incluyen el monitoreo de cambios en los datos durante la transmisión, el hackeo directo de dispositivos o los cambios en las configuraciones de los dispositivos. El hackeo de IoT es una amenaza tan grande que se han desarrollado herramientas como [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn). Estas herramientas son similares a los antivirus y herramientas de seguridad que podrías tener en tu computadora, pero diseñadas para dispositivos IoT pequeños y de bajo consumo.

## Criptografía

Cuando un dispositivo se conecta a un servicio IoT, utiliza un ID para identificarse. El problema es que este ID puede ser clonado: un hacker podría configurar un dispositivo malicioso que use el mismo ID que un dispositivo real pero que envíe datos falsos.

![Tanto dispositivos válidos como maliciosos podrían usar el mismo ID para enviar telemetría](../../../../../translated_images/iot-device-and-hacked-device-connecting.e0671675df74d6d99eb1dedb5a670e606f698efa6202b1ad4c8ae548db299cc6.es.png)

La solución a esto es convertir los datos enviados en un formato codificado, utilizando un valor conocido solo por el dispositivo y la nube para codificar los datos. Este proceso se llama *encriptación*, y el valor utilizado para encriptar los datos se llama *clave de encriptación*.

![Si se usa encriptación, solo se aceptarán mensajes encriptados; los demás serán rechazados](../../../../../translated_images/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f979e46f2849b573564eeb4a4dc5b52f669f62745397492fb.es.png)

El servicio en la nube puede luego convertir los datos a un formato legible, utilizando un proceso llamado *desencriptación*, ya sea con la misma clave de encriptación o con una *clave de desencriptación*. Si el mensaje encriptado no puede ser desencriptado con la clave, el dispositivo ha sido hackeado y el mensaje es rechazado.

La técnica para realizar la encriptación y desencriptación se llama *criptografía*.

### Criptografía temprana

Los primeros tipos de criptografía fueron los cifrados por sustitución, que datan de hace 3,500 años. Estos cifrados implican sustituir una letra por otra. Por ejemplo, el [cifrado César](https://wikipedia.org/wiki/Caesar_cipher) implica desplazar el alfabeto por una cantidad definida, conocida solo por el remitente y el destinatario del mensaje encriptado.

El [cifrado Vigenère](https://wikipedia.org/wiki/Vigenère_cipher) llevó esto más allá al usar palabras para encriptar texto, de modo que cada letra en el texto original se desplazaba por una cantidad diferente, en lugar de siempre desplazarse por el mismo número de letras.

La criptografía se utilizó para una amplia gama de propósitos, como proteger recetas de esmaltes de cerámica en la antigua Mesopotamia, escribir notas de amor secretas en India o mantener en secreto hechizos mágicos en el antiguo Egipto.

### Criptografía moderna

La criptografía moderna es mucho más avanzada, lo que la hace más difícil de descifrar que los métodos antiguos. Utiliza matemáticas complejas para encriptar datos con demasiadas claves posibles como para que un ataque de fuerza bruta sea viable.

La criptografía se utiliza de muchas maneras para comunicaciones seguras. Si estás leyendo esta página en GitHub, notarás que la dirección del sitio web comienza con *HTTPS*, lo que significa que la comunicación entre tu navegador y los servidores web de GitHub está encriptada. Si alguien pudiera leer el tráfico de Internet entre tu navegador y GitHub, no podría entender los datos porque están encriptados. Incluso tu computadora podría encriptar todos los datos en tu disco duro para que, si alguien lo roba, no pueda leer tus datos sin tu contraseña.

> 🎓 HTTPS significa Protocolo de Transferencia de Hipertexto **Seguro**

Desafortunadamente, no todo es seguro. Algunos dispositivos no tienen seguridad, otros están protegidos con claves fáciles de descifrar, o incluso todos los dispositivos del mismo tipo usan la misma clave. Ha habido casos de dispositivos IoT muy personales que tienen la misma contraseña para conectarse a ellos a través de WiFi o Bluetooth. Si puedes conectarte a tu propio dispositivo, podrías conectarte al de otra persona. Una vez conectado, podrías acceder a datos muy privados o controlar su dispositivo.

> 💁 A pesar de las complejidades de la criptografía moderna y las afirmaciones de que romper la encriptación puede tomar miles de millones de años, el auge de la computación cuántica ha llevado a la posibilidad de romper toda la encriptación conocida en un tiempo muy corto.

### Claves simétricas y asimétricas

La encriptación puede ser de dos tipos: simétrica y asimétrica.

La encriptación **simétrica** utiliza la misma clave para encriptar y desencriptar los datos. Tanto el remitente como el receptor necesitan conocer la misma clave. Este es el tipo menos seguro, ya que la clave debe compartirse de alguna manera. Para que un remitente envíe un mensaje encriptado a un receptor, el remitente primero podría tener que enviarle la clave al receptor.

![La encriptación simétrica utiliza la misma clave para encriptar y desencriptar un mensaje](../../../../../translated_images/send-message-symmetric-key.a2e8ad0d495896ff.es.png)

Si la clave es robada durante la transmisión, o si el remitente o receptor son hackeados y la clave es encontrada, la encriptación puede ser descifrada.

![La encriptación simétrica solo es segura si un hacker no obtiene la clave; si lo hace, puede interceptar y desencriptar el mensaje](../../../../../translated_images/send-message-symmetric-key-hacker.e7cb53db1707adfb.es.png)

La encriptación **asimétrica** utiliza 2 claves: una clave de encriptación y una clave de desencriptación, conocidas como un par de claves pública/privada. La clave pública se utiliza para encriptar el mensaje, pero no puede usarse para desencriptarlo; la clave privada se utiliza para desencriptar el mensaje, pero no puede usarse para encriptarlo.

![La encriptación asimétrica utiliza una clave diferente para encriptar y desencriptar. La clave de encriptación se envía a los remitentes para que puedan encriptar un mensaje antes de enviarlo al receptor que posee las claves](../../../../../translated_images/send-message-asymmetric.7abe327c62615b8c.es.png)

El receptor comparte su clave pública, y el remitente la utiliza para encriptar el mensaje. Una vez enviado el mensaje, el receptor lo desencripta con su clave privada. La encriptación asimétrica es más segura porque la clave privada se mantiene privada por el receptor y nunca se comparte. Cualquiera puede tener la clave pública, ya que solo puede usarse para encriptar mensajes.

La encriptación simétrica es más rápida que la asimétrica, pero la asimétrica es más segura. Algunos sistemas utilizan ambas: usan encriptación asimétrica para encriptar y compartir la clave simétrica, y luego usan la clave simétrica para encriptar todos los datos. Esto hace que sea más seguro compartir la clave simétrica entre el remitente y el receptor, y más rápido al encriptar y desencriptar datos.

## Protege tus dispositivos IoT

Los dispositivos IoT pueden protegerse utilizando encriptación simétrica o asimétrica. La simétrica es más sencilla, pero menos segura.

### Claves simétricas

Cuando configuraste tu dispositivo IoT para interactuar con IoT Hub, utilizaste una cadena de conexión. Un ejemplo de cadena de conexión es:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Esta cadena de conexión está compuesta por tres partes separadas por punto y coma, con cada parte siendo una clave y un valor:

| Clave | Valor | Descripción |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | La URL del IoT Hub |
| DeviceId | `soil-moisture-sensor` | El ID único del dispositivo |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | Una clave simétrica conocida por el dispositivo y el IoT Hub |

La última parte de esta cadena de conexión, el `SharedAccessKey`, es la clave simétrica conocida tanto por el dispositivo como por el IoT Hub. Esta clave nunca se envía desde el dispositivo a la nube, ni de la nube al dispositivo. En su lugar, se utiliza para encriptar los datos que se envían o reciben.

✅ Haz un experimento. ¿Qué crees que pasará si cambias la parte `SharedAccessKey` de la cadena de conexión al conectar tu dispositivo IoT? Pruébalo.

Cuando el dispositivo intenta conectarse por primera vez, envía un token de firma de acceso compartido (SAS) que consiste en la URL del IoT Hub, una marca de tiempo que indica cuándo expirará la firma de acceso (generalmente 1 día desde el momento actual) y una firma. Esta firma consiste en la URL y el tiempo de expiración encriptados con la clave de acceso compartido de la cadena de conexión.

El IoT Hub desencripta esta firma con la clave de acceso compartido, y si el valor desencriptado coincide con la URL y la expiración, se permite que el dispositivo se conecte. También verifica que la hora actual sea anterior a la expiración, para evitar que un dispositivo malicioso capture el token SAS de un dispositivo real y lo use.

Esta es una forma elegante de verificar que el remitente es el dispositivo correcto. Al enviar algunos datos conocidos tanto en forma desencriptada como encriptada, el servidor puede verificar el dispositivo asegurándose de que, al desencriptar los datos encriptados, el resultado coincida con la versión desencriptada enviada. Si coincide, entonces tanto el remitente como el receptor tienen la misma clave de encriptación simétrica.
💁 Debido al tiempo de expiración, tu dispositivo IoT necesita conocer la hora exacta, que generalmente se obtiene de un servidor [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Si la hora no es precisa, la conexión fallará.
Después de la conexión, todos los datos enviados al IoT Hub desde el dispositivo, o al dispositivo desde el IoT Hub, estarán cifrados con la clave de acceso compartida.

✅ ¿Qué crees que pasará si varios dispositivos comparten la misma cadena de conexión?

> 💁 No es una buena práctica de seguridad almacenar esta clave en el código. Si un hacker obtiene tu código fuente, puede acceder a tu clave. Además, es más complicado al liberar el código, ya que necesitarías recompilar con una clave actualizada para cada dispositivo. Es mejor cargar esta clave desde un módulo de seguridad de hardware, un chip en el dispositivo IoT que almacena valores cifrados que tu código puede leer.
>
> Cuando estás aprendiendo sobre IoT, a menudo es más fácil poner la clave en el código, como hiciste en una lección anterior, pero debes asegurarte de que esta clave no se incluya en un control de código fuente público.

Los dispositivos tienen 2 claves y 2 cadenas de conexión correspondientes. Esto permite rotar las claves, es decir, cambiar de una clave a otra si la primera se ve comprometida, y regenerar la primera clave.

### Certificados X.509

Cuando utilizas cifrado asimétrico con un par de claves pública/privada, necesitas proporcionar tu clave pública a cualquiera que quiera enviarte datos. El problema es, ¿cómo puede el receptor de tu clave estar seguro de que realmente es tu clave pública y no alguien más haciéndose pasar por ti? En lugar de proporcionar una clave, puedes proporcionar tu clave pública dentro de un certificado que ha sido verificado por una tercera parte confiable, llamado certificado X.509.

Los certificados X.509 son documentos digitales que contienen la parte pública del par de claves pública/privada. Generalmente son emitidos por una de varias organizaciones confiables llamadas [Autoridades de Certificación](https://wikipedia.org/wiki/Certificate_authority) (CAs) y están firmados digitalmente por la CA para indicar que la clave es válida y proviene de ti. Confías en el certificado y en que la clave pública es de quien el certificado dice que es, porque confías en la CA, de manera similar a cómo confiarías en un pasaporte o licencia de conducir porque confías en el país que lo emite. Los certificados tienen un costo, pero también puedes "autofirmarlos", es decir, crear un certificado tú mismo que esté firmado por ti, para fines de prueba.

> 💁 Nunca deberías usar un certificado autofirmado para una versión de producción.

Estos certificados tienen varios campos, incluyendo quién es el propietario de la clave pública, los detalles de la CA que lo emitió, cuánto tiempo es válido y la propia clave pública. Antes de usar un certificado, es una buena práctica verificarlo comprobando que fue firmado por la CA original.

✅ Puedes leer una lista completa de los campos en el certificado en el [tutorial de Microsoft sobre certificados de clave pública X.509](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields).

Cuando usas certificados X.509, tanto el remitente como el receptor tendrán sus propias claves públicas y privadas, así como certificados X.509 que contienen la clave pública. Luego intercambian los certificados X.509 de alguna manera, utilizando las claves públicas del otro para cifrar los datos que envían y sus propias claves privadas para descifrar los datos que reciben.

![En lugar de compartir una clave pública, puedes compartir un certificado. El usuario del certificado puede verificar que proviene de ti comprobando con la autoridad de certificación que lo firmó.](../../../../../translated_images/send-message-certificate.9cc576ac1e46b76e.es.png)

Una gran ventaja de usar certificados X.509 es que pueden compartirse entre dispositivos. Puedes crear un certificado, subirlo al IoT Hub y usarlo para todos tus dispositivos. Cada dispositivo solo necesita conocer la clave privada para descifrar los mensajes que recibe del IoT Hub.

El certificado usado por tu dispositivo para cifrar los mensajes que envía al IoT Hub es publicado por Microsoft. Es el mismo certificado que usan muchos servicios de Azure y, a veces, está integrado en los SDKs.

> 💁 Recuerda, una clave pública es solo eso: pública. La clave pública de Azure solo puede usarse para cifrar datos enviados a Azure, no para descifrarlos, por lo que puede compartirse en cualquier lugar, incluso en el código fuente. Por ejemplo, puedes verla en el [código fuente del SDK de Azure IoT para C](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c).

✅ Hay mucho vocabulario técnico relacionado con los certificados X.509. Puedes leer las definiciones de algunos de los términos que podrías encontrar en [La guía para principiantes sobre la jerga de los certificados X.509](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn).

## Generar y usar un certificado X.509

Los pasos para generar un certificado X.509 son:

1. Crear un par de claves pública/privada. Uno de los algoritmos más utilizados para generar un par de claves pública/privada se llama [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem)) (RSA).

1. Enviar la clave pública con los datos asociados para su firma, ya sea por una CA o mediante autofirma.

La CLI de Azure tiene comandos para crear una nueva identidad de dispositivo en IoT Hub, generar automáticamente el par de claves pública/privada y crear un certificado autofirmado.

> 💁 Si quieres ver los pasos en detalle, en lugar de usar la CLI de Azure, puedes encontrarlos en el [tutorial sobre cómo usar OpenSSL para crear certificados autofirmados en la documentación de Microsoft IoT Hub](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn).

### Tarea - crear una identidad de dispositivo usando un certificado X.509

1. Ejecuta el siguiente comando para registrar la nueva identidad de dispositivo, generando automáticamente las claves y certificados:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Sustituye `<hub_name>` por el nombre que usaste para tu IoT Hub.

    Esto creará un dispositivo con un ID de `soil-moisture-sensor-x509` para distinguirlo de la identidad de dispositivo que creaste en la lección anterior. Este comando también creará 2 archivos en el directorio actual:

    * `soil-moisture-sensor-x509-key.pem` - este archivo contiene la clave privada del dispositivo.
    * `soil-moisture-sensor-x509-cert.pem` - este es el archivo de certificado X.509 del dispositivo.

    ¡Guarda estos archivos de forma segura! El archivo de clave privada no debe incluirse en un control de código fuente público.

### Tarea - usar el certificado X.509 en el código de tu dispositivo

Sigue la guía correspondiente para conectar tu dispositivo IoT a la nube usando el certificado X.509:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Computadora de placa única - Raspberry Pi/Dispositivo IoT virtual](single-board-computer-x509.md)

---

## 🚀 Desafío

Existen múltiples formas de crear, gestionar y eliminar servicios de Azure como Grupos de Recursos e IoT Hubs. Una de ellas es el [Portal de Azure](https://portal.azure.com?WT.mc_id=academic-17441-jabenn), una interfaz web que te proporciona una GUI para gestionar tus servicios de Azure.

Dirígete a [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) e investiga el portal. Intenta crear un IoT Hub usando el portal y luego elimínalo.

**Pista** - al crear servicios a través del portal, no necesitas crear un Grupo de Recursos por adelantado; puedes crear uno al mismo tiempo que el servicio. ¡Asegúrate de eliminarlo cuando termines!

Puedes encontrar mucha documentación, tutoriales y guías sobre el Portal de Azure en la [documentación del portal de Azure](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Cuestionario posterior a la lección

[Cuestionario posterior a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Revisión y autoestudio

* Lee sobre la historia de la criptografía en la [página de Historia de la criptografía en Wikipedia](https://wikipedia.org/wiki/History_of_cryptography).
* Lee sobre los certificados X.509 en la [página de X.509 en Wikipedia](https://wikipedia.org/wiki/X.509).

## Asignación

[Construye un nuevo dispositivo IoT](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.