<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f74f4ccb61f00e5f7e9f49c3ed416e36",
  "translation_date": "2025-08-26T14:22:14+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/README.md",
  "language_code": "es"
}
-->
# Activar la detección de calidad de frutas desde un sensor

![Resumen visual de esta lección](../../../../../translated_images/es/lesson-18.92c32ed1d354caa5a54baa4032cf0b172d4655e8e326ad5d46c558a0def15365.jpg)

> Resumen visual por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Introducción

Una aplicación de IoT no es simplemente un dispositivo único que captura datos y los envía a la nube; más a menudo, implica múltiples dispositivos que trabajan juntos para capturar datos del mundo físico mediante sensores, tomar decisiones basadas en esos datos e interactuar con el mundo físico a través de actuadores o visualizaciones.

En esta lección aprenderás más sobre cómo diseñar aplicaciones complejas de IoT, incorporando múltiples sensores, varios servicios en la nube para analizar y almacenar datos, y mostrando una respuesta a través de un actuador. Aprenderás cómo diseñar un prototipo de sistema de control de calidad de frutas, incluyendo el uso de sensores de proximidad para activar la aplicación de IoT y cómo sería la arquitectura de este prototipo.

En esta lección cubriremos:

* [Diseñar aplicaciones complejas de IoT](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Diseñar un sistema de control de calidad de frutas](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Activar la comprobación de calidad de frutas desde un sensor](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Datos utilizados para un detector de calidad de frutas](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Usar dispositivos de desarrollo para simular múltiples dispositivos IoT](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Pasar a producción](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Esta es la última lección de este proyecto, así que después de completar esta lección y la tarea, no olvides limpiar tus servicios en la nube. Necesitarás los servicios para completar la tarea, así que asegúrate de terminarla primero.
>
> Consulta [la guía para limpiar tu proyecto](../../../clean-up.md) si necesitas instrucciones sobre cómo hacerlo.

## Diseñar aplicaciones complejas de IoT

Las aplicaciones de IoT están compuestas por muchos componentes, incluyendo una variedad de dispositivos y servicios en internet.

Las aplicaciones de IoT pueden describirse como *cosas* (dispositivos) que envían datos que generan *insights*. Estos *insights* generan *acciones* para mejorar un negocio o proceso. Un ejemplo es un motor (la cosa) que envía datos de temperatura. Estos datos se utilizan para evaluar si el motor está funcionando como se espera (el insight). El insight se utiliza para priorizar de manera proactiva el mantenimiento del motor (la acción).

* Diferentes cosas recopilan diferentes tipos de datos.
* Los servicios de IoT generan insights a partir de esos datos, a veces complementándolos con datos de fuentes adicionales.
* Estos insights impulsan acciones, como controlar actuadores en dispositivos o visualizar datos.

### Arquitectura de referencia de IoT

![Una arquitectura de referencia de IoT](../../../../../translated_images/es/iot-reference-architecture.2278b98b55c6d4e89bde18eada3688d893861d43507641804dd2f9d3079cfaa0.png)

El diagrama anterior muestra una arquitectura de referencia de IoT.

> 🎓 Una *arquitectura de referencia* es un ejemplo de arquitectura que puedes usar como referencia al diseñar nuevos sistemas. En este caso, si estuvieras construyendo un nuevo sistema de IoT, podrías seguir la arquitectura de referencia, sustituyendo tus propios dispositivos y servicios donde sea necesario.

* **Cosas** son dispositivos que recopilan datos de sensores, tal vez interactuando con servicios en el borde para interpretar esos datos, como clasificadores de imágenes para interpretar datos de imágenes. Los datos de los dispositivos se envían a un servicio de IoT.
* **Insights** provienen de aplicaciones sin servidor o de análisis realizados sobre datos almacenados.
* **Acciones** pueden ser comandos enviados a dispositivos o visualización de datos que permiten a los humanos tomar decisiones.

![Una arquitectura de referencia de IoT en Azure](../../../../../translated_images/es/iot-reference-architecture-azure.0b8d2161af924cb18ae48a8558a19541cca47f27264851b5b7e56d7b8bb372ac.png)

El diagrama anterior muestra algunos de los componentes y servicios cubiertos hasta ahora en estas lecciones y cómo se vinculan en una arquitectura de referencia de IoT.

* **Cosas** - has escrito código para dispositivos que capturan datos de sensores y analizan imágenes usando Custom Vision, tanto en la nube como en un dispositivo en el borde. Estos datos se enviaron a IoT Hub.
* **Insights** - has utilizado Azure Functions para responder a mensajes enviados a un IoT Hub y almacenado datos para análisis posterior en Azure Storage.
* **Acciones** - has controlado actuadores basándote en decisiones tomadas en la nube y comandos enviados a los dispositivos, y has visualizado datos usando Azure Maps.

✅ Piensa en otros dispositivos IoT que hayas usado, como electrodomésticos inteligentes. ¿Cuáles son las cosas, insights y acciones involucrados en ese dispositivo y su software?

Este patrón puede escalarse tanto como necesites, añadiendo más dispositivos y más servicios.

### Datos y seguridad

Al definir la arquitectura de tu sistema, necesitas considerar constantemente los datos y la seguridad.

* ¿Qué datos envía y recibe tu dispositivo?
* ¿Cómo deberían asegurarse y protegerse esos datos?
* ¿Cómo debería controlarse el acceso al dispositivo y al servicio en la nube?

✅ Reflexiona sobre la seguridad de los datos de cualquier dispositivo IoT que poseas. ¿Cuántos de esos datos son personales y deberían mantenerse privados, tanto en tránsito como cuando están almacenados? ¿Qué datos no deberían almacenarse?

## Diseñar un sistema de control de calidad de frutas

Ahora tomemos esta idea de cosas, insights y acciones y apliquémosla a nuestro detector de calidad de frutas para diseñar una aplicación más grande de extremo a extremo.

Imagina que te han asignado la tarea de construir un detector de calidad de frutas para ser utilizado en una planta de procesamiento. Las frutas viajan en un sistema de cinta transportadora donde actualmente los empleados dedican tiempo a inspeccionar las frutas manualmente y retirar las que no están maduras. Para reducir costos, el propietario de la planta quiere un sistema automatizado.

✅ Una de las tendencias con el auge del IoT (y la tecnología en general) es que los trabajos manuales están siendo reemplazados por máquinas. Investiga: ¿Cuántos trabajos se estima que se perderán debido al IoT? ¿Cuántos nuevos trabajos se crearán construyendo dispositivos IoT?

Necesitas construir un sistema donde las frutas sean detectadas a medida que llegan a la cinta transportadora, luego sean fotografiadas y verificadas usando un modelo de IA que se ejecuta en el borde. Los resultados se envían a la nube para ser almacenados, y si la fruta no está madura, se emite una notificación para que sea retirada.

|   |   |
| - | - |
| **Cosas** | Detector para frutas que llegan a la cinta transportadora<br>Cámara para fotografiar y clasificar las frutas<br>Dispositivo en el borde que ejecuta el clasificador<br>Dispositivo para notificar sobre frutas no maduras |
| **Insights** | Decidir verificar la madurez de la fruta<br>Almacenar los resultados de la clasificación de madurez<br>Determinar si es necesario alertar sobre frutas no maduras |
| **Acciones** | Enviar un comando a un dispositivo para fotografiar la fruta y verificarla con un clasificador de imágenes<br>Enviar un comando a un dispositivo para alertar que la fruta no está madura |

### Prototipar tu aplicación

![Una arquitectura de referencia de IoT para verificar la calidad de frutas](../../../../../translated_images/es/iot-reference-architecture-fruit-quality.cc705f121c3b6fa71c800d9630935ac34bc08223a04601e35f41d5e9b5dd5207.png)

El diagrama anterior muestra una arquitectura de referencia para esta aplicación prototipo.

* Un dispositivo IoT con un sensor de proximidad detecta la llegada de frutas. Esto envía un mensaje a la nube indicando que se ha detectado fruta.
* Una aplicación sin servidor en la nube envía un comando a otro dispositivo para tomar una fotografía y clasificar la imagen.
* Un dispositivo IoT con una cámara toma una foto y la envía a un clasificador de imágenes que se ejecuta en el borde. Los resultados se envían a la nube.
* Una aplicación sin servidor en la nube almacena esta información para ser analizada más tarde y determinar qué porcentaje de frutas no están maduras. Si la fruta no está madura, envía un comando a otro dispositivo IoT para alertar a los trabajadores de la fábrica mediante un LED.

> 💁 Toda esta aplicación de IoT podría implementarse como un único dispositivo, con toda la lógica para iniciar la clasificación de imágenes y controlar el LED integrada. Podría usar un IoT Hub solo para rastrear el número de frutas no maduras detectadas y configurar el dispositivo. En esta lección se expande para demostrar los conceptos de aplicaciones IoT a gran escala.

Para el prototipo, implementarás todo esto en un único dispositivo. Si estás usando un microcontrolador, entonces usarás un dispositivo en el borde separado para ejecutar el clasificador de imágenes. Ya has aprendido la mayoría de las cosas que necesitarás para construir esto.

## Activar la comprobación de calidad de frutas desde un sensor

El dispositivo IoT necesita algún tipo de activador para indicar cuándo la fruta está lista para ser clasificada. Un activador para esto sería medir cuándo la fruta está en la posición correcta en la cinta transportadora midiendo la distancia a un sensor.

![Los sensores de proximidad envían haces de láser a objetos como plátanos y miden el tiempo hasta que el haz rebota](../../../../../translated_images/es/proximity-sensor.f5cd752c77fb62fe.webp)

Los sensores de proximidad pueden usarse para medir la distancia desde el sensor hasta un objeto. Generalmente transmiten un haz de radiación electromagnética, como un láser o luz infrarroja, y luego detectan la radiación que rebota en un objeto. El tiempo entre el envío del haz y el rebote de la señal puede usarse para calcular la distancia al sensor.

> 💁 Probablemente has usado sensores de proximidad sin siquiera saberlo. La mayoría de los teléfonos inteligentes apagan la pantalla cuando los acercas a tu oído para evitar que termines accidentalmente una llamada con tu lóbulo, y esto funciona usando un sensor de proximidad que detecta un objeto cerca de la pantalla durante una llamada y desactiva las capacidades táctiles hasta que el teléfono está a cierta distancia.

### Tarea - activar la detección de calidad de frutas desde un sensor de distancia

Sigue la guía correspondiente para usar un sensor de proximidad y detectar un objeto con tu dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Computadora de placa única - Raspberry Pi](pi-proximity.md)
* [Computadora de placa única - Dispositivo virtual](virtual-device-proximity.md)

## Datos utilizados para un detector de calidad de frutas

El prototipo del detector de frutas tiene múltiples componentes que se comunican entre sí.

![Los componentes comunicándose entre sí](../../../../../translated_images/es/fruit-quality-detector-message-flow.adf2a65da8fd8741ac7af11361574de89adc126785d67606bb4d2ec00467e380.png)

* Un sensor de proximidad mide la distancia a una fruta y envía esta información a IoT Hub.
* El comando para controlar la cámara proviene de IoT Hub hacia el dispositivo con la cámara.
* Los resultados de la clasificación de imágenes se envían a IoT Hub.
* El comando para controlar un LED que alerta cuando la fruta no está madura se envía desde IoT Hub al dispositivo con el LED.

Es bueno definir la estructura de estos mensajes desde el principio, antes de construir la aplicación.

> 💁 Prácticamente todos los desarrolladores experimentados han pasado horas, días o incluso semanas persiguiendo errores causados por diferencias entre los datos enviados y lo que se esperaba.

Por ejemplo, si estás enviando información de temperatura, ¿cómo definirías el JSON? Podrías tener un campo llamado `temperature`, o podrías usar la abreviatura común `temp`.

```json
{
    "temperature": 20.7
}
```

comparado con:

```json
{
    "temp": 20.7
}
```

También debes considerar las unidades: ¿la temperatura está en °C o °F? Si estás midiendo la temperatura con un dispositivo de consumo y cambian las unidades de visualización, necesitas asegurarte de que las unidades enviadas a la nube permanezcan consistentes.

✅ Investiga: ¿Cómo causaron problemas con las unidades que el Mars Climate Orbiter de $125 millones se estrellara?

Piensa en los datos que se envían para el detector de calidad de frutas. ¿Cómo definirías cada mensaje? ¿Dónde analizarías los datos y tomarías decisiones sobre qué datos enviar?

Por ejemplo, al activar la clasificación de imágenes usando el sensor de proximidad. El dispositivo IoT mide la distancia, pero ¿dónde se toma la decisión? ¿El dispositivo decide que la fruta está lo suficientemente cerca y envía un mensaje al IoT Hub para activar la clasificación? ¿O envía mediciones de proximidad y deja que el IoT Hub decida?

La respuesta a preguntas como esta es: depende. Cada caso de uso es diferente, por lo que como desarrollador de IoT necesitas entender el sistema que estás construyendo, cómo se utiliza y los datos que se detectan.

* Si la decisión se toma en el IoT Hub, necesitas enviar múltiples mediciones de distancia.
* Si envías demasiados mensajes, aumentas el costo del IoT Hub y la cantidad de ancho de banda necesario para tus dispositivos IoT (especialmente en una fábrica con millones de dispositivos). También puede ralentizar tu dispositivo.
* Si tomas la decisión en el dispositivo, necesitarás proporcionar una forma de configurar el dispositivo para ajustar la máquina.

## Usar dispositivos de desarrollo para simular múltiples dispositivos IoT

Para construir tu prototipo, necesitarás que tu kit de desarrollo IoT actúe como múltiples dispositivos, enviando telemetría y respondiendo a comandos.

### Simular múltiples dispositivos IoT en una Raspberry Pi o hardware IoT virtual

Cuando usas una computadora de placa única como una Raspberry Pi, puedes ejecutar múltiples aplicaciones a la vez. Esto significa que puedes simular múltiples dispositivos IoT creando múltiples aplicaciones, una por cada 'dispositivo IoT'. Por ejemplo, puedes implementar cada dispositivo como un archivo Python separado y ejecutarlos en diferentes sesiones de terminal.
> 💁 Ten en cuenta que algunos dispositivos de hardware no funcionarán si son utilizados simultáneamente por varias aplicaciones.
### Simulando múltiples dispositivos en un microcontrolador

Los microcontroladores son más complicados para simular múltiples dispositivos. A diferencia de las computadoras de placa única, no puedes ejecutar múltiples aplicaciones a la vez; debes incluir toda la lógica para todos los dispositivos IoT en una sola aplicación.

Algunas sugerencias para facilitar este proceso son:

* Crea una o más clases por cada dispositivo IoT, por ejemplo, clases llamadas `DistanceSensor`, `ClassifierCamera`, `LEDController`. Cada una puede tener sus propios métodos `setup` y `loop`, que serán llamados por las funciones principales `setup` y `loop`.
* Maneja los comandos en un solo lugar y dirígelos a la clase de dispositivo correspondiente según sea necesario.
* En la función principal `loop`, deberás considerar el tiempo para cada dispositivo diferente. Por ejemplo, si tienes una clase de dispositivo que necesita procesar cada 10 segundos y otra que necesita procesar cada 1 segundo, entonces en tu función principal `loop` usa un retraso de 1 segundo. Cada llamada a `loop` activa el código relevante para el dispositivo que necesita procesar cada segundo, y utiliza un contador para contar cada iteración, procesando el otro dispositivo cuando el contador alcance 10 (reiniciando el contador después).

## Pasando a producción

El prototipo formará la base de un sistema de producción final. Algunas de las diferencias al pasar a producción serían:

* Componentes robustos: usar hardware diseñado para soportar el ruido, calor, vibración y estrés de una fábrica.
* Uso de comunicaciones internas: algunos de los componentes se comunicarían directamente, evitando el salto a la nube, enviando datos a la nube solo para ser almacenados. Cómo se haga esto depende de la configuración de la fábrica, ya sea mediante comunicaciones directas o ejecutando parte del servicio IoT en el borde utilizando un dispositivo gateway.
* Opciones de configuración: cada fábrica y caso de uso es diferente, por lo que el hardware necesitaría ser configurable. Por ejemplo, el sensor de proximidad podría necesitar detectar diferentes frutas a diferentes distancias. En lugar de codificar la distancia para activar la clasificación, querrías que esto sea configurable a través de la nube, por ejemplo, usando un gemelo de dispositivo.
* Eliminación automatizada de frutas: en lugar de usar un LED para alertar que la fruta está inmadura, dispositivos automatizados la eliminarían.

✅ Investiga: ¿De qué otras maneras diferirían los dispositivos de producción de los kits de desarrollo?

---

## 🚀 Desafío

En esta lección has aprendido algunos de los conceptos necesarios para diseñar un sistema IoT. Piensa en los proyectos anteriores. ¿Cómo encajarían en la arquitectura de referencia mostrada arriba?

Elige uno de los proyectos realizados hasta ahora y piensa en el diseño de una solución más complicada que combine múltiples capacidades más allá de lo que se cubrió en los proyectos. Dibuja la arquitectura y piensa en todos los dispositivos y servicios que necesitarías.

Por ejemplo: un dispositivo de seguimiento de vehículos que combine GPS con sensores para monitorear cosas como temperaturas en un camión refrigerado, los tiempos de encendido y apagado del motor, y la identidad del conductor. ¿Cuáles son los dispositivos involucrados, los servicios involucrados, los datos que se transmiten y las consideraciones de seguridad y privacidad?

## Cuestionario posterior a la clase

[Cuestionario posterior a la clase](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Revisión y autoestudio

* Lee más sobre arquitectura IoT en la [documentación de arquitectura de referencia de Azure IoT en Microsoft docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Lee más sobre gemelos de dispositivos en la [documentación sobre entender y usar gemelos de dispositivos en IoT Hub en Microsoft docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Lee sobre OPC-UA, un protocolo de comunicación máquina a máquina usado en automatización industrial en la [página de OPC-UA en Wikipedia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Tarea

[Construye un detector de calidad de frutas](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.