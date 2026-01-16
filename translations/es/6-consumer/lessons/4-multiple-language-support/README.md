<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-26T15:21:46+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "es"
}
-->
# Soporte para múltiples idiomas

![Resumen visual de esta lección](../../../../../translated_images/es/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.jpg)

> Resumen visual por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

Este video ofrece una visión general de los servicios de voz de Azure, cubriendo la conversión de voz a texto y de texto a voz de lecciones anteriores, así como la traducción de voz, un tema tratado en esta lección:

[![Reconociendo voz con unas pocas líneas de Python desde Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Haz clic en la imagen de arriba para ver el video

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Introducción

En las últimas 3 lecciones aprendiste sobre la conversión de voz a texto, la comprensión del lenguaje y la conversión de texto a voz, todo impulsado por IA. Otra área de la comunicación humana en la que la IA puede ayudar es la traducción de idiomas: convertir de un idioma a otro, como del inglés al francés.

En esta lección aprenderás a usar IA para traducir texto, permitiendo que tu temporizador inteligente interactúe con usuarios en múltiples idiomas.

En esta lección cubriremos:

* [Traducir texto](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Servicios de traducción](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Crear un recurso de traductor](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Soporte para múltiples idiomas en aplicaciones con traducciones](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Traducir texto usando un servicio de IA](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Esta es la última lección de este proyecto, así que después de completar esta lección y la tarea, no olvides limpiar tus servicios en la nube. Necesitarás los servicios para completar la tarea, así que asegúrate de terminarla primero.
>
> Consulta [la guía para limpiar tu proyecto](../../../clean-up.md) si necesitas instrucciones sobre cómo hacerlo.

## Traducir texto

La traducción de texto ha sido un problema de la informática investigado durante más de 70 años, y solo ahora, gracias a los avances en IA y potencia computacional, está cerca de resolverse a un nivel casi tan bueno como el de los traductores humanos.

> 💁 Los orígenes se remontan aún más atrás, a [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), un criptógrafo árabe del siglo IX que desarrolló técnicas para la traducción de idiomas.

### Traducciones automáticas

La traducción de texto comenzó como una tecnología conocida como Traducción Automática (MT, por sus siglas en inglés), que puede traducir entre diferentes pares de idiomas. La MT funciona sustituyendo palabras en un idioma por otro, añadiendo técnicas para seleccionar las formas correctas de traducir frases o partes de oraciones cuando una simple traducción palabra por palabra no tiene sentido.

> 🎓 Cuando los traductores admiten la traducción entre un idioma y otro, se conocen como *pares de idiomas*. Diferentes herramientas admiten diferentes pares de idiomas, y estos pueden no ser completos. Por ejemplo, un traductor puede admitir inglés a español como un par de idiomas, y español a italiano como otro par, pero no inglés a italiano.

Por ejemplo, traducir "Hello world" del inglés al francés puede realizarse con una sustitución: "Bonjour" por "Hello" y "le monde" por "world", lo que lleva a la traducción correcta de "Bonjour le monde".

Las sustituciones no funcionan cuando diferentes idiomas usan formas distintas de expresar lo mismo. Por ejemplo, la oración en inglés "My name is Jim" se traduce como "Je m'appelle Jim" en francés, que literalmente significa "Me llamo Jim". "Je" es "yo" en francés, "moi" es "me", pero se concatena con el verbo porque comienza con una vocal, convirtiéndose en "m'", "appelle" significa "llamar", y "Jim" no se traduce porque es un nombre y no una palabra traducible. El orden de las palabras también se convierte en un problema: una simple sustitución de "Je m'appelle Jim" se convierte en "I myself call Jim", con un orden de palabras diferente al inglés.

> 💁 Algunas palabras nunca se traducen: mi nombre es Jim independientemente del idioma que se use para presentarme. Al traducir a idiomas que usan alfabetos diferentes o letras distintas para sonidos específicos, las palabras pueden ser *transliteradas*, es decir, se seleccionan letras o caracteres que producen el sonido adecuado para sonar igual que la palabra original.

Los modismos también son un problema para la traducción. Estas son frases cuyo significado entendido es diferente de una interpretación literal de las palabras. Por ejemplo, en inglés el modismo "I've got ants in my pants" no se refiere literalmente a tener hormigas en la ropa, sino a estar inquieto. Si traduces esto al alemán, confundirías al oyente, ya que la versión alemana es "Ich habe Hummeln im Hintern" (Tengo abejorros en el trasero).

> 💁 Diferentes regiones añaden complejidades adicionales. Con el modismo "ants in your pants", en inglés americano "pants" se refiere a ropa exterior, mientras que en inglés británico "pants" significa ropa interior.

✅ Si hablas varios idiomas, piensa en algunas frases que no se traduzcan directamente.

Los sistemas de traducción automática dependen de grandes bases de datos de reglas que describen cómo traducir ciertas frases y modismos, junto con métodos estadísticos para elegir las traducciones más apropiadas entre las opciones posibles. Estos métodos estadísticos utilizan enormes bases de datos de obras traducidas por humanos a múltiples idiomas para seleccionar la traducción más probable, una técnica llamada *traducción automática estadística*. Muchas de estas técnicas usan representaciones intermedias del idioma, permitiendo que un idioma se traduzca al intermedio y luego del intermedio a otro idioma. De esta manera, agregar más idiomas implica traducciones hacia y desde el intermedio, en lugar de hacia y desde todos los demás idiomas.

### Traducciones neuronales

Las traducciones neuronales utilizan el poder de la IA para traducir, generalmente traduciendo oraciones completas con un solo modelo. Estos modelos se entrenan con enormes conjuntos de datos traducidos por humanos, como páginas web, libros y documentación de las Naciones Unidas.

Los modelos de traducción neuronal suelen ser más pequeños que los modelos de traducción automática, ya que no necesitan grandes bases de datos de frases y modismos. Los servicios modernos de IA que ofrecen traducciones a menudo combinan múltiples técnicas, mezclando traducción automática estadística y traducción neuronal.

No existe una traducción 1:1 para ningún par de idiomas. Diferentes modelos de traducción producirán resultados ligeramente diferentes dependiendo de los datos utilizados para entrenar el modelo. Las traducciones no siempre son simétricas: si traduces una oración de un idioma a otro y luego de vuelta al idioma original, es posible que obtengas una oración ligeramente diferente como resultado.

✅ Prueba diferentes traductores en línea como [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) o la aplicación de traducción de Apple. Compara las versiones traducidas de algunas oraciones. También intenta traducir en uno y luego volver a traducir en otro.

## Servicios de traducción

Existen varios servicios de IA que puedes usar en tus aplicaciones para traducir voz y texto.

### Servicio de voz de Cognitive Services

![El logotipo del servicio de voz](../../../../../translated_images/es/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.png)

El servicio de voz que has estado utilizando en las últimas lecciones tiene capacidades de traducción para el reconocimiento de voz. Cuando reconoces voz, puedes solicitar no solo el texto de la voz en el mismo idioma, sino también en otros idiomas.

> 💁 Esto solo está disponible desde el SDK de voz; la API REST no tiene traducciones integradas.

### Servicio de traductor de Cognitive Services

![El logotipo del servicio de traductor](../../../../../translated_images/es/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.png)

El servicio de traductor es un servicio dedicado que puede traducir texto de un idioma a uno o más idiomas de destino. Además de traducir, admite una amplia gama de funciones adicionales, como enmascarar lenguaje ofensivo. También te permite proporcionar una traducción específica para una palabra o frase en particular, trabajar con términos que no deseas traducir o tener una traducción específica bien conocida.

Por ejemplo, al traducir la frase "I have a Raspberry Pi", refiriéndose a la computadora de placa única, a otro idioma como el francés, querrías mantener el nombre "Raspberry Pi" tal cual y no traducirlo, obteniendo "J’ai un Raspberry Pi" en lugar de "J’ai une pi aux framboises".

## Crear un recurso de traductor

Para esta lección necesitarás un recurso de traductor. Usarás la API REST para traducir texto.

### Tarea - crear un recurso de traductor

1. Desde tu terminal o línea de comandos, ejecuta el siguiente comando para crear un recurso de traductor en tu grupo de recursos `smart-timer`.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Sustituye `<location>` por la ubicación que usaste al crear el grupo de recursos.

1. Obtén la clave para el servicio de traductor:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Copia una de las claves.

## Soporte para múltiples idiomas en aplicaciones con traducciones

En un mundo ideal, toda tu aplicación debería entender tantos idiomas diferentes como sea posible, desde escuchar voz, hasta comprender el lenguaje y responder con voz. Esto implica mucho trabajo, por lo que los servicios de traducción pueden acelerar el tiempo de entrega de tu aplicación.

![Arquitectura de un temporizador inteligente traduciendo japonés a inglés, procesando en inglés y luego traduciendo de vuelta a japonés](../../../../../translated_images/es/translated-smart-timer.08ac20057fdc5c37.webp)

Imagina que estás construyendo un temporizador inteligente que usa inglés de principio a fin, comprendiendo inglés hablado y convirtiéndolo a texto, ejecutando la comprensión del lenguaje en inglés, creando respuestas en inglés y respondiendo con voz en inglés. Si quisieras agregar soporte para japonés, podrías comenzar traduciendo japonés hablado a texto en inglés, luego mantener el núcleo de la aplicación igual, y finalmente traducir el texto de respuesta al japonés antes de hablar la respuesta. Esto te permitiría agregar soporte para japonés rápidamente, y podrías expandirlo para proporcionar soporte completo de principio a fin en japonés más adelante.

> 💁 La desventaja de depender de la traducción automática es que diferentes idiomas y culturas tienen formas distintas de expresar lo mismo, por lo que la traducción puede no coincidir con la expresión que esperas.

Las traducciones automáticas también abren posibilidades para aplicaciones y dispositivos que pueden traducir contenido creado por los usuarios a medida que se crea. La ciencia ficción a menudo presenta "traductores universales", dispositivos que pueden traducir de idiomas alienígenas a (típicamente) inglés americano. Estos dispositivos son menos ciencia ficción y más ciencia real, si ignoramos la parte de los alienígenas. Ya existen aplicaciones y dispositivos que proporcionan traducción en tiempo real de voz y texto escrito, utilizando combinaciones de servicios de voz y traducción.

Un ejemplo es la aplicación para teléfonos móviles [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn), demostrada en este video:

[![Función en vivo de Microsoft Translator en acción](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Haz clic en la imagen de arriba para ver el video

Imagina tener un dispositivo así disponible, especialmente al viajar o interactuar con personas cuyo idioma no conoces. Tener dispositivos de traducción automática en aeropuertos u hospitales proporcionaría mejoras muy necesarias en accesibilidad.

✅ Investiga: ¿Existen dispositivos IoT de traducción disponibles comercialmente? ¿Qué hay de capacidades de traducción integradas en dispositivos inteligentes?

> 👽 Aunque no existen verdaderos traductores universales que nos permitan hablar con alienígenas, el [traductor de Microsoft admite klingon](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). ¡Qapla’!

## Traducir texto usando un servicio de IA

Puedes usar un servicio de IA para agregar esta capacidad de traducción a tu temporizador inteligente.

### Tarea - traducir texto usando un servicio de IA

Sigue la guía correspondiente para traducir texto en tu dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Computadora de placa única - Raspberry Pi](pi-translate-speech.md)
* [Computadora de placa única - Dispositivo virtual](virtual-device-translate-speech.md)

---

## 🚀 Desafío

¿Cómo pueden las traducciones automáticas beneficiar a otras aplicaciones de IoT más allá de los dispositivos inteligentes? Piensa en diferentes formas en que las traducciones pueden ayudar, no solo con palabras habladas, sino también con texto.

## Cuestionario posterior a la lección

[Cuestionario posterior a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Revisión y autoestudio

* Lee más sobre la traducción automática en la [página de traducción automática en Wikipedia](https://wikipedia.org/wiki/Machine_translation)
* Lee más sobre la traducción automática neuronal en la [página de traducción automática neuronal en Wikipedia](https://wikipedia.org/wiki/Neural_machine_translation)
* Consulta la lista de idiomas admitidos por los servicios de voz de Microsoft en la [documentación de soporte de idiomas y voces para el servicio de voz en Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Tarea

[Construye un traductor universal](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.