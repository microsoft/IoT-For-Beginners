<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52ed2bd997d08040f79a1a6ef2bac958",
  "translation_date": "2025-08-26T15:48:12+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/README.md",
  "language_code": "es"
}
-->
# Seguimiento de ubicación

![Una vista general ilustrada de esta lección](../../../../../translated_images/es/lesson-11.9fddbac4b664c6d50ab7ac9bb32f1fc3f945f03760e72f7f43938073762fb017.jpg)

> Ilustración por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Introducción

El proceso principal para llevar alimentos desde un agricultor hasta un consumidor implica cargar cajas de productos en camiones, barcos, aviones u otros vehículos de transporte comercial y entregar la comida en algún lugar, ya sea directamente a un cliente o a un centro o almacén para su procesamiento. Todo el proceso de principio a fin, desde la granja hasta el consumidor, forma parte de un proceso llamado *cadena de suministro*. El siguiente video de la Escuela de Negocios W. P. Carey de la Universidad Estatal de Arizona explica con más detalle el concepto de la cadena de suministro y cómo se gestiona.

[![¿Qué es la gestión de la cadena de suministro? Un video de la Escuela de Negocios W. P. Carey de la Universidad Estatal de Arizona](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Haz clic en la imagen de arriba para ver el video

Agregar dispositivos IoT puede mejorar drásticamente tu cadena de suministro, permitiéndote gestionar dónde están los artículos, planificar mejor el transporte y manejo de mercancías, y responder más rápido a los problemas.

Cuando se gestiona una flota de vehículos como camiones, es útil saber dónde está cada vehículo en un momento dado. Los vehículos pueden equiparse con sensores GPS que envían su ubicación a sistemas IoT, permitiendo a los propietarios localizar su posición, ver la ruta que han tomado y saber cuándo llegarán a su destino. La mayoría de los vehículos operan fuera de la cobertura WiFi, por lo que utilizan redes celulares para enviar este tipo de datos. A veces, el sensor GPS está integrado en dispositivos IoT más complejos, como libros de registro electrónicos. Estos dispositivos rastrean cuánto tiempo ha estado un camión en tránsito para garantizar que los conductores cumplan con las leyes locales sobre horas de trabajo.

En esta lección aprenderás cómo rastrear la ubicación de un vehículo utilizando un sensor del Sistema de Posicionamiento Global (GPS).

En esta lección cubriremos:

* [Vehículos conectados](../../../../../3-transport/lessons/1-location-tracking)
* [Coordenadas geoespaciales](../../../../../3-transport/lessons/1-location-tracking)
* [Sistemas de Posicionamiento Global (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [Leer datos de sensores GPS](../../../../../3-transport/lessons/1-location-tracking)
* [Datos GPS NMEA](../../../../../3-transport/lessons/1-location-tracking)
* [Decodificar datos de sensores GPS](../../../../../3-transport/lessons/1-location-tracking)

## Vehículos conectados

El IoT está transformando la forma en que se transportan los bienes al crear flotas de *vehículos conectados*. Estos vehículos están conectados a sistemas informáticos centrales que informan sobre su ubicación y otros datos de sensores. Tener una flota de vehículos conectados tiene una amplia gama de beneficios:

* Seguimiento de ubicación: puedes localizar dónde está un vehículo en cualquier momento, lo que te permite:

  * Recibir alertas cuando un vehículo está a punto de llegar a un destino para preparar al equipo para la descarga.
  * Localizar vehículos robados.
  * Combinar datos de ubicación y ruta con problemas de tráfico para permitirte redirigir vehículos en medio del trayecto.
  * Cumplir con impuestos. Algunos países cobran a los vehículos por la cantidad de kilómetros recorridos en carreteras públicas (como el [RUC de Nueva Zelanda](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), por lo que saber cuándo un vehículo está en carreteras públicas frente a privadas facilita el cálculo de los impuestos adeudados.
  * Saber dónde enviar equipos de mantenimiento en caso de avería.

* Telemetría del conductor: poder garantizar que los conductores respeten los límites de velocidad, tomen curvas a velocidades adecuadas, frenen temprano y eficientemente, y conduzcan de manera segura. Los vehículos conectados también pueden tener cámaras para grabar incidentes. Esto puede estar vinculado al seguro, ofreciendo tarifas reducidas para buenos conductores.

* Cumplimiento de horas de conducción: garantizar que los conductores solo conduzcan durante las horas legalmente permitidas según los momentos en que encienden y apagan el motor.

Estos beneficios pueden combinarse, por ejemplo, combinando el cumplimiento de horas de conducción con el seguimiento de ubicación para redirigir a los conductores si no pueden llegar a su destino dentro de sus horas de conducción permitidas. También pueden combinarse con otra telemetría específica del vehículo, como datos de temperatura de camiones con control de temperatura, permitiendo redirigir vehículos si su ruta actual significaría que los bienes no pueden mantenerse a la temperatura adecuada.

> 🎓 La logística es el proceso de transportar bienes de un lugar a otro, como de una granja a un supermercado a través de uno o más almacenes. Un agricultor empaca cajas de tomates que se cargan en un camión, se entregan en un almacén central y se colocan en un segundo camión que puede contener una mezcla de diferentes tipos de productos que luego se entregan en un supermercado.

El componente principal del seguimiento de vehículos es el GPS: sensores que pueden localizar su posición en cualquier lugar de la Tierra. En esta lección aprenderás cómo usar un sensor GPS, comenzando por aprender cómo definir una ubicación en la Tierra.

## Coordenadas geoespaciales

Las coordenadas geoespaciales se utilizan para definir puntos en la superficie de la Tierra, similar a cómo las coordenadas pueden usarse para dibujar un píxel en una pantalla de computadora o posicionar puntos en un bordado. Para un solo punto, tienes un par de coordenadas. Por ejemplo, el campus de Microsoft en Redmond, Washington, EE. UU., está ubicado en 47.6423109, -122.1390293.

### Latitud y longitud

La Tierra es una esfera, un círculo tridimensional. Debido a esto, los puntos se definen dividiéndola en 360 grados, igual que la geometría de los círculos. La latitud mide el número de grados de norte a sur, y la longitud mide el número de grados de este a oeste.

> 💁 Nadie sabe realmente la razón original por la cual los círculos se dividen en 360 grados. La [página de grados (ángulo) en Wikipedia](https://wikipedia.org/wiki/Degree_(angle)) cubre algunas de las posibles razones.

![Líneas de latitud desde 90° en el Polo Norte, 45° a mitad de camino entre el Polo Norte y el ecuador, 0° en el ecuador, -45° a mitad de camino entre el ecuador y el Polo Sur, y -90° en el Polo Sur](../../../../../translated_images/es/latitude-lines.11d8d91dfb2014a57437272d7db7fd6607243098e8685f06e0c5f1ec984cb7eb.png)

La latitud se mide utilizando líneas que rodean la Tierra y corren paralelas al ecuador, dividiendo los hemisferios norte y sur en 90° cada uno. El ecuador está en 0°, el Polo Norte está en 90°, también conocido como 90° Norte, y el Polo Sur está en -90°, o 90° Sur.

La longitud se mide como el número de grados hacia el este y el oeste. El origen de 0° de longitud se llama el *Meridiano de Greenwich*, y fue definido en 1884 como una línea desde el Polo Norte al Polo Sur que pasa por el [Observatorio Real Británico en Greenwich, Inglaterra](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Líneas de longitud que van desde -180° al oeste del Meridiano de Greenwich, hasta 0° en el Meridiano de Greenwich, hasta 180° al este del Meridiano de Greenwich](../../../../../translated_images/es/longitude-meridians.ab4ef1c91c064586b0185a3c8d39e585903696c6a7d28c098a93a629cddb5d20.png)

> 🎓 Un meridiano es una línea imaginaria recta que va desde el Polo Norte al Polo Sur, formando un semicírculo.

Para medir la longitud de un punto, se mide el número de grados alrededor del ecuador desde el Meridiano de Greenwich hasta un meridiano que pasa por ese punto. La longitud va desde -180°, o 180° Oeste, pasando por 0° en el Meridiano de Greenwich, hasta 180°, o 180° Este. 180° y -180° se refieren al mismo punto, el antimeridiano o meridiano 180. Este es un meridiano en el lado opuesto de la Tierra al Meridiano de Greenwich.

> 💁 El antimeridiano no debe confundirse con la Línea Internacional de Cambio de Fecha, que está aproximadamente en la misma posición, pero no es una línea recta y varía para ajustarse a las fronteras geopolíticas.

✅ Investiga: Intenta encontrar la latitud y longitud de tu ubicación actual.

### Grados, minutos y segundos vs grados decimales

Tradicionalmente, las mediciones de grados de latitud y longitud se hacían utilizando numeración sexagesimal, o base-60, un sistema de numeración utilizado por los antiguos babilonios que realizaron las primeras mediciones y registros de tiempo y distancia. Probablemente usas el sistema sexagesimal todos los días sin darte cuenta, dividiendo horas en 60 minutos y minutos en 60 segundos.

La longitud y la latitud se miden en grados, minutos y segundos, con un minuto siendo 1/60 de un grado, y 1 segundo siendo 1/60 de un minuto.

Por ejemplo, en el ecuador:

* 1° de latitud es **111.3 kilómetros**
* 1 minuto de latitud es 111.3/60 = **1.855 kilómetros**
* 1 segundo de latitud es 1.855/60 = **0.031 kilómetros**

El símbolo para un minuto es una comilla simple, para un segundo es una comilla doble. Por ejemplo, 2 grados, 17 minutos y 43 segundos se escribiría como 2°17'43". Las partes de segundos se dan como decimales, por ejemplo, medio segundo es 0°0'0.5".

Las computadoras no trabajan en base-60, por lo que estas coordenadas se dan como grados decimales al usar datos GPS en la mayoría de los sistemas informáticos. Por ejemplo, 2°17'43" es 2.295277. El símbolo de grado generalmente se omite.

Las coordenadas de un punto siempre se dan como `latitud, longitud`, por lo que el ejemplo anterior del campus de Microsoft en 47.6423109,-122.117198 tiene:

* Una latitud de 47.6423109 (47.6423109 grados al norte del ecuador)
* Una longitud de -122.1390293 (122.1390293 grados al oeste del Meridiano de Greenwich).

![El campus de Microsoft en 47.6423109,-122.117198](../../../../../translated_images/es/microsoft-gps-location-world.a321d481b010f6adfcca139b2ba0adc53b79f58a540495b8e2ce7f779ea64bfe.png)

## Sistemas de Posicionamiento Global (GPS)

Los sistemas GPS utilizan múltiples satélites que orbitan la Tierra para localizar tu posición. Probablemente has usado sistemas GPS sin siquiera saberlo: para encontrar tu ubicación en una aplicación de mapas en tu teléfono como Apple Maps o Google Maps, para ver dónde está tu transporte en una aplicación de viajes como Uber o Lyft, o al usar navegación satelital (sat-nav) en tu automóvil.

> 🎓 ¡Los satélites en la 'navegación satelital' son satélites GPS!

Los sistemas GPS funcionan al tener varios satélites que envían una señal con la posición actual de cada satélite y una marca de tiempo precisa. Estas señales se envían a través de ondas de radio y son detectadas por una antena en el sensor GPS. Un sensor GPS detectará estas señales y, utilizando la hora actual, medirá cuánto tiempo tardó la señal en llegar al sensor desde el satélite. Debido a que la velocidad de las ondas de radio es constante, el sensor GPS puede usar la marca de tiempo enviada para calcular qué tan lejos está el sensor del satélite. Al combinar los datos de al menos 3 satélites con las posiciones enviadas, el sensor GPS puede determinar su ubicación en la Tierra.

> 💁 Los sensores GPS necesitan antenas para detectar ondas de radio. Las antenas integradas en camiones y automóviles con GPS a bordo están posicionadas para obtener una buena señal, generalmente en el parabrisas o el techo. Si estás usando un sistema GPS separado, como un teléfono inteligente o un dispositivo IoT, entonces necesitas asegurarte de que la antena integrada en el sistema GPS o teléfono tenga una vista clara del cielo, como estar montada en tu parabrisas.

![Al conocer la distancia del sensor a múltiples satélites, se puede calcular la ubicación](../../../../../translated_images/es/gps-satellites.04acf1148fe25fbf1586bc2e8ba698e8d79b79a50c36824b38417dd13372b90f.png)

Los satélites GPS están orbitando la Tierra, no en un punto fijo sobre el sensor, por lo que los datos de ubicación incluyen la altitud sobre el nivel del mar además de la latitud y longitud.

El GPS solía tener limitaciones de precisión impuestas por el ejército de EE. UU., limitando la precisión a aproximadamente 5 metros. Esta limitación se eliminó en el año 2000, permitiendo una precisión de 30 centímetros. Obtener esta precisión no siempre es posible debido a interferencias con las señales.

✅ Si tienes un teléfono inteligente, abre la aplicación de mapas y observa qué tan precisa es tu ubicación. Puede tomar un breve período de tiempo para que tu teléfono detecte múltiples satélites y obtenga una ubicación más precisa.
💁 Los satélites contienen relojes atómicos que son increíblemente precisos, pero se desvían 38 microsegundos (0.0000038 segundos) al día en comparación con los relojes atómicos en la Tierra, debido a que el tiempo se ralentiza a medida que la velocidad aumenta, tal como lo predicen las teorías de la relatividad especial y general de Einstein. Los satélites viajan más rápido que la rotación de la Tierra. Este desvío se ha utilizado para confirmar las predicciones de la relatividad especial y general, y debe ajustarse en el diseño de los sistemas GPS. Literalmente, el tiempo transcurre más lento en un satélite GPS.
Los sistemas GPS han sido desarrollados y desplegados por varios países y uniones políticas, incluyendo EE. UU., Rusia, Japón, India, la UE y China. Los sensores GPS modernos pueden conectarse a la mayoría de estos sistemas para obtener ubicaciones más rápidas y precisas.

> 🎓 Los grupos de satélites en cada despliegue se denominan constelaciones.

## Leer datos del sensor GPS

La mayoría de los sensores GPS envían datos GPS a través de UART.

> ⚠️ UART se cubrió en [proyecto 2, lección 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Consulta esa lección si es necesario.

Puedes usar un sensor GPS en tu dispositivo IoT para obtener datos GPS.

### Tarea - conectar un sensor GPS y leer datos GPS

Sigue la guía correspondiente para leer datos GPS usando tu dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Computadora de placa única - Raspberry Pi](pi-gps-sensor.md)
* [Computadora de placa única - Dispositivo virtual](virtual-device-gps-sensor.md)

## Datos GPS en formato NMEA

Cuando ejecutaste tu código, probablemente viste lo que parecía ser un conjunto de caracteres sin sentido en la salida. En realidad, estos son datos GPS estándar, y todo tiene un significado.

Los sensores GPS generan datos utilizando mensajes NMEA, siguiendo el estándar NMEA 0183. NMEA es un acrónimo de la [National Marine Electronics Association](https://www.nmea.org), una organización comercial con sede en EE. UU. que establece estándares para la comunicación entre dispositivos electrónicos marinos.

> 💁 Este estándar es propietario y tiene un costo de al menos 2,000 USD, pero suficiente información sobre él está en el dominio público, lo que ha permitido que la mayor parte del estándar sea descifrada y utilizada en código abierto y otros proyectos no comerciales.

Estos mensajes están basados en texto. Cada mensaje consiste en una *oración* que comienza con un carácter `$`, seguido de 2 caracteres que indican la fuente del mensaje (por ejemplo, GP para el sistema GPS de EE. UU., GN para GLONASS, el sistema GPS ruso) y 3 caracteres que indican el tipo de mensaje. El resto del mensaje son campos separados por comas, terminando con un carácter de nueva línea.

Algunos de los tipos de mensajes que se pueden recibir son:

| Tipo | Descripción |
| ---- | ----------- |
| GGA | Datos de fijación GPS, incluyendo la latitud, longitud y altitud del sensor GPS, junto con el número de satélites en vista para calcular esta fijación. |
| ZDA | La fecha y hora actuales, incluyendo la zona horaria local. |
| GSV | Detalles de los satélites en vista, definidos como los satélites de los que el sensor GPS puede detectar señales. |

> 💁 Los datos GPS incluyen marcas de tiempo, por lo que tu dispositivo IoT puede obtener la hora si es necesario desde un sensor GPS, en lugar de depender de un servidor NTP o un reloj en tiempo real interno.

El mensaje GGA incluye la ubicación actual usando el formato `(dd)dmm.mmmm`, junto con un carácter único para indicar la dirección. La `d` en el formato representa grados, la `m` representa minutos, y los segundos se expresan como decimales de minutos. Por ejemplo, 2°17'43" sería 217.716666667 - 2 grados, 17.716666667 minutos.

El carácter de dirección puede ser `N` o `S` para latitud, indicando norte o sur, y `E` o `W` para longitud, indicando este u oeste. Por ejemplo, una latitud de 2°17'43" tendría un carácter de dirección `N`, mientras que -2°17'43" tendría un carácter de dirección `S`.

Por ejemplo, la oración NMEA `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* La parte de la latitud es `4738.538654,N`, que se convierte en 47.6423109 en grados decimales. `4738.538654` es 47.6423109, y la dirección es `N` (norte), por lo que es una latitud positiva.

* La parte de la longitud es `12208.341758,W`, que se convierte en -122.1390293 en grados decimales. `12208.341758` es 122.1390293°, y la dirección es `W` (oeste), por lo que es una longitud negativa.

## Decodificar datos del sensor GPS

En lugar de usar los datos NMEA en bruto, es mejor decodificarlos en un formato más útil. Existen múltiples bibliotecas de código abierto que puedes usar para extraer datos útiles de los mensajes NMEA en bruto.

### Tarea - decodificar datos del sensor GPS

Sigue la guía correspondiente para decodificar datos del sensor GPS usando tu dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Computadora de placa única - Raspberry Pi/Dispositivo IoT virtual](single-board-computer-gps-decode.md)

---

## 🚀 Desafío

¡Escribe tu propio decodificador NMEA! En lugar de depender de bibliotecas de terceros para decodificar oraciones NMEA, ¿puedes escribir tu propio decodificador para extraer latitud y longitud de las oraciones NMEA?

## Cuestionario posterior a la lección

[Cuestionario posterior a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Revisión y autoestudio

* Lee más sobre Coordenadas Geoespaciales en la [página del sistema de coordenadas geográficas en Wikipedia](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Investiga sobre los Meridianos de Origen en otros cuerpos celestes además de la Tierra en la [página del Meridiano de Origen en Wikipedia](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies).
* Investiga los diferentes sistemas GPS de varios gobiernos y uniones políticas como la UE, Japón, Rusia, India y EE. UU.

## Asignación

[Investiga otros datos GPS](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.