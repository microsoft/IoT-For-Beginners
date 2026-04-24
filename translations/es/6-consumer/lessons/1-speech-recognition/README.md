# Reconocer voz con un dispositivo IoT

![Una visión general ilustrada de esta lección](../../../../../translated_images/es/lesson-21.e34de51354d6606f.webp)

> Ilustración por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

Este video ofrece una visión general del servicio de voz de Azure, un tema que se cubrirá en esta lección:

[![Cómo empezar a usar tu recurso de Cognitive Services Speech desde el canal de YouTube de Microsoft Azure](https://img.youtube.com/vi/iW0Fw0l3mrA/0.jpg)](https://www.youtube.com/watch?v=iW0Fw0l3mrA)

> 🎥 Haz clic en la imagen de arriba para ver el video

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/41)

## Introducción

'Alexa, pon un temporizador de 12 minutos'

'Alexa, estado del temporizador'

'Alexa, pon un temporizador de 8 minutos llamado brócoli al vapor'

Los dispositivos inteligentes están volviéndose cada vez más comunes. No solo como altavoces inteligentes como HomePods, Echos y Google Homes, sino también integrados en nuestros teléfonos, relojes, e incluso en lámparas y termostatos.

> 💁 Tengo al menos 19 dispositivos en mi casa que tienen asistentes de voz, ¡y eso es solo los que conozco!

El control por voz aumenta la accesibilidad al permitir que personas con movilidad limitada interactúen con dispositivos. Ya sea una discapacidad permanente como haber nacido sin brazos, una discapacidad temporal como brazos rotos, o simplemente tener las manos ocupadas con compras o niños pequeños, poder controlar nuestra casa con la voz en lugar de las manos abre un mundo de posibilidades. Gritar 'Hey Siri, cierra la puerta del garaje' mientras lidias con un cambio de pañal y un niño inquieto puede ser una pequeña pero efectiva mejora en la vida.

Uno de los usos más populares de los asistentes de voz es configurar temporizadores, especialmente temporizadores de cocina. Poder configurar múltiples temporizadores solo con tu voz es de gran ayuda en la cocina: no necesitas detenerte a amasar masa, revolver sopa o limpiar tus manos llenas de relleno de dumplings para usar un temporizador físico.

En esta lección aprenderás a integrar el reconocimiento de voz en dispositivos IoT. Aprenderás sobre los micrófonos como sensores, cómo capturar audio desde un micrófono conectado a un dispositivo IoT, y cómo usar IA para convertir lo que se escucha en texto. A lo largo del resto de este proyecto construirás un temporizador de cocina inteligente, capaz de configurar temporizadores usando tu voz en múltiples idiomas.

En esta lección cubriremos:

* [Micrófonos](../../../../../6-consumer/lessons/1-speech-recognition)
* [Capturar audio desde tu dispositivo IoT](../../../../../6-consumer/lessons/1-speech-recognition)
* [De voz a texto](../../../../../6-consumer/lessons/1-speech-recognition)
* [Convertir voz a texto](../../../../../6-consumer/lessons/1-speech-recognition)

## Micrófonos

Los micrófonos son sensores analógicos que convierten las ondas sonoras en señales eléctricas. Las vibraciones en el aire hacen que los componentes del micrófono se muevan pequeñas cantidades, lo que provoca cambios minúsculos en las señales eléctricas. Estos cambios se amplifican para generar una salida eléctrica.

### Tipos de micrófonos

Los micrófonos vienen en una variedad de tipos:

* Dinámicos - Los micrófonos dinámicos tienen un imán unido a un diafragma móvil que se mueve en una bobina de alambre creando una corriente eléctrica. Esto es lo opuesto a la mayoría de los altavoces, que usan una corriente eléctrica para mover un imán en una bobina de alambre, moviendo un diafragma para crear sonido. Esto significa que los altavoces pueden usarse como micrófonos dinámicos, y los micrófonos dinámicos pueden usarse como altavoces. En dispositivos como intercomunicadores, donde un usuario está escuchando o hablando, pero no ambos, un dispositivo puede actuar como altavoz y micrófono.

    Los micrófonos dinámicos no necesitan energía para funcionar, la señal eléctrica se genera completamente desde el micrófono.

    ![Patti Smith cantando en un micrófono Shure SM58 (tipo cardioide dinámico)](../../../../../translated_images/es/dynamic-mic.8babac890a2d80df.webp)

* De cinta - Los micrófonos de cinta son similares a los dinámicos, excepto que tienen una cinta metálica en lugar de un diafragma. Esta cinta se mueve en un campo magnético generando una corriente eléctrica. Al igual que los micrófonos dinámicos, los de cinta no necesitan energía para funcionar.

    ![Edmund Lowe, actor estadounidense, de pie frente a un micrófono de radio (etiquetado para la Red Azul de NBC), sosteniendo un guion, 1942](../../../../../translated_images/es/ribbon-mic.eacc8e092c7441ca.webp)

* Condensador - Los micrófonos de condensador tienen un diafragma metálico delgado y una placa trasera metálica fija. Se aplica electricidad a ambos, y a medida que el diafragma vibra, la carga estática entre las placas cambia generando una señal. Los micrófonos de condensador necesitan energía para funcionar, llamada *Phantom power*.

    ![Micrófono de condensador de diafragma pequeño C451B de AKG Acoustics](../../../../../translated_images/es/condenser-mic.6f6ed5b76ca19e0e.webp)

* MEMS - Los micrófonos de sistemas microelectromecánicos, o MEMS, son micrófonos en un chip. Tienen un diafragma sensible a la presión grabado en un chip de silicio, y funcionan de manera similar a un micrófono de condensador. Estos micrófonos pueden ser diminutos e integrarse en circuitos.

    ![Un micrófono MEMS en una placa de circuito](../../../../../translated_images/es/mems-microphone.80574019e1f5e4d9.webp)

    En la imagen de arriba, el chip etiquetado como **LEFT** es un micrófono MEMS, con un diafragma diminuto de menos de un milímetro de ancho.

✅ Investiga: ¿Qué micrófonos tienes a tu alrededor, ya sea en tu computadora, tu teléfono, tus auriculares o en otros dispositivos? ¿Qué tipo de micrófonos son?

### Audio digital

El audio es una señal analógica que transporta información muy detallada. Para convertir esta señal en digital, el audio debe ser muestreado miles de veces por segundo.

> 🎓 Muestrear significa convertir la señal de audio en un valor digital que representa la señal en ese momento.

![Un gráfico de líneas que muestra una señal, con puntos discretos en intervalos fijos](../../../../../translated_images/es/sampling.6f4fadb3f2d9dfe7.webp)

El audio digital se muestrea utilizando Modulación por Código de Pulsos, o PCM. PCM implica leer el voltaje de la señal y seleccionar el valor discreto más cercano a ese voltaje utilizando un tamaño definido.

> 💁 Puedes pensar en PCM como la versión de sensor de la modulación por ancho de pulso, o PWM (PWM se cubrió en [la lección 3 del proyecto de introducción](../../../1-getting-started/lessons/3-sensors-and-actuators/README.md#pulse-width-modulation)). PCM implica convertir una señal analógica a digital, PWM implica convertir una señal digital a analógica.

Por ejemplo, la mayoría de los servicios de música en streaming ofrecen audio de 16 bits o 24 bits. Esto significa que convierten el voltaje en un valor que cabe en un entero de 16 bits o 24 bits. El audio de 16 bits ajusta el valor en un rango de -32,768 a 32,767, el de 24 bits en el rango −8,388,608 a 8,388,607. Cuantos más bits, más cerca estará la muestra de lo que realmente escuchan nuestros oídos.

> 💁 Tal vez hayas oído hablar del audio de 8 bits, a menudo referido como LoFi. Este es audio muestreado usando solo 8 bits, es decir, -128 a 127. El primer audio de computadora estaba limitado a 8 bits debido a limitaciones de hardware, por lo que a menudo se ve en juegos retro.

Estas muestras se toman miles de veces por segundo, utilizando tasas de muestreo bien definidas medidas en KHz (miles de lecturas por segundo). Los servicios de música en streaming usan 48KHz para la mayoría del audio, pero algunos audios 'sin pérdida' usan hasta 96KHz o incluso 192KHz. Cuanto mayor sea la tasa de muestreo, más cerca estará el audio del original, hasta cierto punto. Existe debate sobre si los humanos pueden notar la diferencia por encima de los 48KHz.

✅ Investiga: Si usas un servicio de música en streaming, ¿qué tasa de muestreo y tamaño utiliza? Si usas CDs, ¿cuál es la tasa de muestreo y tamaño del audio en CD?

Existen varios formatos diferentes para datos de audio. Probablemente hayas oído hablar de archivos mp3: datos de audio comprimidos para hacerlos más pequeños sin perder calidad. El audio sin comprimir a menudo se almacena como un archivo WAV: este es un archivo con 44 bytes de información de encabezado, seguido de datos de audio sin procesar. El encabezado contiene información como la tasa de muestreo (por ejemplo, 16000 para 16KHz) y el tamaño de la muestra (16 para 16 bits), y el número de canales. Después del encabezado, el archivo WAV contiene los datos de audio sin procesar.

> 🎓 Los canales se refieren a cuántos flujos de audio diferentes conforman el audio. Por ejemplo, para audio estéreo con izquierda y derecha, habría 2 canales. Para sonido envolvente 7.1 en un sistema de cine en casa, serían 8.

### Tamaño de los datos de audio

Los datos de audio son relativamente grandes. Por ejemplo, capturar audio sin comprimir de 16 bits a 16KHz (una tasa suficientemente buena para usar con un modelo de voz a texto) requiere 32KB de datos por cada segundo de audio:

* 16 bits significa 2 bytes por muestra (1 byte son 8 bits).
* 16KHz son 16,000 muestras por segundo.
* 16,000 x 2 bytes = 32,000 bytes por segundo.

Esto puede parecer una pequeña cantidad de datos, pero si estás usando un microcontrolador con memoria limitada, puede ser mucho. Por ejemplo, el Wio Terminal tiene 192KB de memoria, y esa memoria debe almacenar el código del programa y las variables. Incluso si tu código de programa fuera diminuto, no podrías capturar más de 5 segundos de audio.

Los microcontroladores pueden acceder a almacenamiento adicional, como tarjetas SD o memoria flash. Al construir un dispositivo IoT que capture audio, necesitarás asegurarte de que no solo tienes almacenamiento adicional, sino que tu código escribe el audio capturado desde tu micrófono directamente en ese almacenamiento, y al enviarlo a la nube, lo transmite desde el almacenamiento a la solicitud web. De esta manera, puedes evitar quedarte sin memoria al intentar mantener todo el bloque de datos de audio en la memoria a la vez.

## Capturar audio desde tu dispositivo IoT

Tu dispositivo IoT puede conectarse a un micrófono para capturar audio, listo para convertirlo en texto. También puede conectarse a altavoces para emitir audio. En lecciones posteriores, esto se usará para dar retroalimentación de audio, pero es útil configurar los altavoces ahora para probar el micrófono.

### Tarea - configurar tu micrófono y altavoces

Sigue la guía correspondiente para configurar el micrófono y los altavoces de tu dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-microphone.md)
* [Computadora de placa única - Raspberry Pi](pi-microphone.md)
* [Computadora de placa única - Dispositivo virtual](virtual-device-microphone.md)

### Tarea - capturar audio

Sigue la guía correspondiente para capturar audio en tu dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-audio.md)
* [Computadora de placa única - Raspberry Pi](pi-audio.md)
* [Computadora de placa única - Dispositivo virtual](virtual-device-audio.md)

## De voz a texto

De voz a texto, o reconocimiento de voz, implica usar IA para convertir palabras en una señal de audio a texto.

### Modelos de reconocimiento de voz

Para convertir voz a texto, las muestras de la señal de audio se agrupan y se alimentan a un modelo de aprendizaje automático basado en una red neuronal recurrente (RNN). Este es un tipo de modelo de aprendizaje automático que puede usar datos previos para tomar decisiones sobre datos entrantes. Por ejemplo, la RNN podría detectar un bloque de muestras de audio como el sonido 'Hel', y cuando recibe otro que cree que es el sonido 'lo', puede combinar esto con el sonido anterior, encontrar que 'Hello' es una palabra válida y seleccionarla como resultado.

Los modelos de aprendizaje automático siempre aceptan datos del mismo tamaño cada vez. El clasificador de imágenes que construiste en una lección anterior redimensiona las imágenes a un tamaño fijo y las procesa. Lo mismo ocurre con los modelos de voz, tienen que procesar bloques de audio de tamaño fijo. Los modelos de voz necesitan poder combinar los resultados de múltiples predicciones para obtener la respuesta, lo que les permite distinguir entre 'Hi' y 'Highway', o 'flock' y 'floccinaucinihilipilification'.

Los modelos de voz también son lo suficientemente avanzados como para entender el contexto y pueden corregir las palabras que detectan a medida que se procesan más sonidos. Por ejemplo, si dices "Fui a las tiendas a comprar dos plátanos y una manzana también", usarías tres palabras que suenan igual pero se escriben diferente: to, two y too. Los modelos de voz son capaces de entender el contexto y usar la ortografía adecuada de la palabra.
💁 Algunos servicios de voz permiten personalización para que funcionen mejor en entornos ruidosos como fábricas, o con palabras específicas de la industria, como nombres de productos químicos. Estas personalizaciones se entrenan proporcionando audio de muestra y una transcripción, y funcionan mediante aprendizaje por transferencia, de la misma manera que entrenaste un clasificador de imágenes utilizando solo unas pocas imágenes en una lección anterior.
### Privacidad

Cuando se utiliza la conversión de voz a texto en un dispositivo IoT para consumidores, la privacidad es increíblemente importante. Estos dispositivos escuchan audio de manera continua, por lo que, como consumidor, no quieres que todo lo que dices se envíe a la nube y se convierta en texto. Esto no solo consumiría mucho ancho de banda de Internet, sino que también tiene enormes implicaciones de privacidad, especialmente cuando algunos fabricantes de dispositivos inteligentes seleccionan aleatoriamente audio para [que humanos lo validen contra el texto generado para ayudar a mejorar su modelo](https://www.theverge.com/2019/4/10/18305378/amazon-alexa-ai-voice-assistant-annotation-listen-private-recordings).

Solo quieres que tu dispositivo inteligente envíe audio a la nube para su procesamiento cuando lo estás utilizando, no cuando escucha audio en tu hogar, audio que podría incluir reuniones privadas o interacciones íntimas. La forma en que la mayoría de los dispositivos inteligentes funcionan es con una *palabra de activación*, una frase clave como "Alexa", "Hey Siri" o "OK Google" que hace que el dispositivo 'despierte' y escuche lo que estás diciendo hasta que detecta una pausa en tu discurso, indicando que has terminado de hablar con el dispositivo.

> 🎓 La detección de palabras de activación también se conoce como *detección de palabras clave* o *reconocimiento de palabras clave*.

Estas palabras de activación se detectan en el dispositivo, no en la nube. Estos dispositivos inteligentes tienen pequeños modelos de IA que funcionan en el dispositivo y que escuchan la palabra de activación, y cuando se detecta, comienzan a transmitir el audio a la nube para su reconocimiento. Estos modelos están muy especializados y solo escuchan la palabra de activación.

> 💁 Algunas empresas tecnológicas están añadiendo más privacidad a sus dispositivos y realizando parte de la conversión de voz a texto en el propio dispositivo. Apple anunció que, como parte de sus actualizaciones de iOS y macOS en 2021, soportarán la conversión de voz a texto en el dispositivo y podrán manejar muchas solicitudes sin necesidad de usar la nube. Esto es posible gracias a los potentes procesadores en sus dispositivos que pueden ejecutar modelos de aprendizaje automático.

✅ ¿Cuáles crees que son las implicaciones éticas y de privacidad de almacenar el audio enviado a la nube? ¿Debería almacenarse este audio, y si es así, cómo? ¿Crees que el uso de grabaciones para la aplicación de la ley es un buen intercambio por la pérdida de privacidad?

La detección de palabras de activación generalmente utiliza una técnica conocida como TinyML, que consiste en convertir modelos de aprendizaje automático para que puedan ejecutarse en microcontroladores. Estos modelos son pequeños en tamaño y consumen muy poca energía para funcionar.

Para evitar la complejidad de entrenar y usar un modelo de palabras de activación, el temporizador inteligente que estás construyendo en esta lección utilizará un botón para activar el reconocimiento de voz.

> 💁 Si quieres intentar crear un modelo de detección de palabras de activación para ejecutarlo en el Wio Terminal o Raspberry Pi, consulta este [tutorial de respuesta a tu voz de Edge Impulse](https://docs.edgeimpulse.com/docs/responding-to-your-voice). Si deseas usar tu computadora para hacerlo, puedes probar el [inicio rápido de palabras clave personalizadas en la documentación de Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Convertir voz a texto

![Logotipo de servicios de voz](../../../../../translated_images/es/azure-speech-logo.a1f08c4befb0159f.webp)

Al igual que con la clasificación de imágenes en un proyecto anterior, existen servicios de IA preconstruidos que pueden tomar voz como archivo de audio y convertirla en texto. Uno de estos servicios es el Servicio de Voz, parte de los Servicios Cognitivos, servicios de IA preconstruidos que puedes usar en tus aplicaciones.

### Tarea - configurar un recurso de IA de voz

1. Crea un Grupo de Recursos para este proyecto llamado `smart-timer`.

1. Usa el siguiente comando para crear un recurso de voz gratuito:

    ```sh
    az cognitiveservices account create --name smart-timer \
                                        --resource-group smart-timer \
                                        --kind SpeechServices \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Sustituye `<location>` por la ubicación que utilizaste al crear el Grupo de Recursos.

1. Necesitarás una clave de API para acceder al recurso de voz desde tu código. Ejecuta el siguiente comando para obtener la clave:

    ```sh
    az cognitiveservices account keys list --name smart-timer \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Copia una de las claves.

### Tarea - convertir voz a texto

Sigue la guía correspondiente para convertir voz a texto en tu dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-speech-to-text.md)
* [Computadora de placa única - Raspberry Pi](pi-speech-to-text.md)
* [Computadora de placa única - Dispositivo virtual](virtual-device-speech-to-text.md)

---

## 🚀 Desafío

El reconocimiento de voz ha existido durante mucho tiempo y está mejorando continuamente. Investiga las capacidades actuales y compara cómo han evolucionado con el tiempo, incluyendo qué tan precisas son las transcripciones automáticas en comparación con las humanas.

¿Qué crees que depara el futuro para el reconocimiento de voz?

## Cuestionario posterior a la clase

[Cuestionario posterior a la clase](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/42)

## Revisión y autoestudio

* Lee sobre los diferentes tipos de micrófonos y cómo funcionan en el [artículo sobre las diferencias entre micrófonos dinámicos y de condensador en Musician's HQ](https://musicianshq.com/whats-the-difference-between-dynamic-and-condenser-microphones/).
* Lee más sobre el servicio de voz de los Servicios Cognitivos en la [documentación del servicio de voz en Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn).
* Lee sobre la detección de palabras clave en la [documentación de reconocimiento de palabras clave en Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Asignación

[](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.