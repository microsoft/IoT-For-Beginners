# Introducción a IoT

![Un resumen visual de esta lección](../../../../../translated_images/es/lesson-1.2606670fa61ee904.webp)

> Sketchnote por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

Esta lección fue impartida como parte de la serie [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) del [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). La lección se presentó en 2 videos: una clase de 1 hora y una sesión de preguntas y respuestas de 1 hora para profundizar en partes de la lección y responder preguntas.

[![Lección 1: Introducción a IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Lección 1: Introducción a IoT - Horas de oficina](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Haz clic en las imágenes de arriba para ver los videos

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Introducción

Esta lección cubre algunos de los temas introductorios sobre el Internet de las Cosas (IoT) y te guía en la configuración de tu hardware.

En esta lección cubriremos:

* [¿Qué es el 'Internet de las Cosas'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Dispositivos IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Configura tu dispositivo](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Aplicaciones de IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Ejemplos de dispositivos IoT que podrías tener a tu alrededor](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## ¿Qué es el 'Internet de las Cosas'?

El término 'Internet de las Cosas' fue acuñado por [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) en 1999 para referirse a la conexión de Internet con el mundo físico a través de sensores. Desde entonces, el término se ha utilizado para describir cualquier dispositivo que interactúe con el mundo físico que lo rodea, ya sea recopilando datos de sensores o proporcionando interacciones en el mundo real a través de actuadores (dispositivos que hacen algo como encender un interruptor o iluminar un LED), generalmente conectados a otros dispositivos o a Internet.

> **Sensores** recopilan información del mundo, como medir velocidad, temperatura o ubicación.
>
> **Actuadores** convierten señales eléctricas en interacciones del mundo real, como activar un interruptor, encender luces, emitir sonidos o enviar señales de control a otro hardware, por ejemplo, para encender un enchufe.

IoT como área tecnológica abarca más que solo dispositivos: incluye servicios en la nube que pueden procesar los datos de los sensores o enviar solicitudes a actuadores conectados a dispositivos IoT. También incluye dispositivos que no tienen o no necesitan conectividad a Internet, a menudo denominados dispositivos de borde. Estos dispositivos pueden procesar y responder a datos de sensores por sí mismos, generalmente utilizando modelos de IA entrenados en la nube.

IoT es un campo tecnológico en rápido crecimiento. Se estima que para finales de 2020, había 30 mil millones de dispositivos IoT desplegados y conectados a Internet. Mirando al futuro, se estima que para 2025, los dispositivos IoT recopilarán casi 80 zettabytes de datos, o 80 billones de gigabytes. ¡Eso es una cantidad enorme de datos!

![Un gráfico que muestra dispositivos IoT activos a lo largo del tiempo, con una tendencia ascendente de menos de 5 mil millones en 2015 a más de 30 mil millones en 2025](../../../../../images/connected-iot-devices.svg)

✅ Investiga un poco: ¿Cuánta de la información generada por los dispositivos IoT se utiliza realmente y cuánta se desperdicia? ¿Por qué se ignora tanta información?

Estos datos son clave para el éxito de IoT. Para ser un desarrollador exitoso de IoT, necesitas entender qué datos necesitas recopilar, cómo recopilarlos, cómo tomar decisiones basadas en ellos y cómo usar esas decisiones para interactuar con el mundo físico si es necesario.

## Dispositivos IoT

La **T** en IoT significa **Things** (Cosas): dispositivos que interactúan con el mundo físico que los rodea, ya sea recopilando datos de sensores o proporcionando interacciones en el mundo real a través de actuadores.

Los dispositivos para uso comercial o de producción, como rastreadores de actividad física para consumidores o controladores de máquinas industriales, suelen ser hechos a medida. Utilizan placas de circuito personalizadas, tal vez incluso procesadores personalizados, diseñados para satisfacer las necesidades de una tarea específica, ya sea ser lo suficientemente pequeños para caber en una muñeca o lo suficientemente resistentes para trabajar en un entorno de fábrica con altas temperaturas, estrés o vibraciones.

Como desarrollador que aprende sobre IoT o crea un prototipo de dispositivo, necesitarás comenzar con un kit de desarrollo. Estos son dispositivos IoT de propósito general diseñados para desarrolladores, a menudo con características que no tendrías en un dispositivo de producción, como un conjunto de pines externos para conectar sensores o actuadores, hardware para depuración o recursos adicionales que agregarían costos innecesarios en una producción a gran escala.

Estos kits de desarrollo generalmente se dividen en dos categorías: microcontroladores y computadoras de placa única. Estos se presentarán aquí, y entraremos en más detalle en la próxima lección.

> 💁 Tu teléfono también puede considerarse un dispositivo IoT de propósito general, con sensores y actuadores integrados, y diferentes aplicaciones que utilizan los sensores y actuadores de diferentes maneras con diferentes servicios en la nube. Incluso puedes encontrar algunos tutoriales de IoT que usan una aplicación de teléfono como dispositivo IoT.

### Microcontroladores

Un microcontrolador (también conocido como MCU, por sus siglas en inglés de microcontroller unit) es una pequeña computadora que consta de:

🧠 Una o más unidades centrales de procesamiento (CPUs): el 'cerebro' del microcontrolador que ejecuta tu programa.

💾 Memoria (RAM y memoria de programa): donde se almacenan tu programa, datos y variables.

🔌 Conexiones de entrada/salida (I/O) programables: para comunicarse con periféricos externos (dispositivos conectados) como sensores y actuadores.

Los microcontroladores son dispositivos de computación de bajo costo, con precios promedio para los utilizados en hardware personalizado que bajan a alrededor de US$0.50, y algunos dispositivos tan baratos como US$0.03. Los kits de desarrollo pueden comenzar desde tan solo US$4, con costos que aumentan a medida que se agregan más características. El [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), un kit de desarrollo de microcontroladores de [Seeed studios](https://www.seeedstudio.com) que tiene sensores, actuadores, WiFi y una pantalla, cuesta alrededor de US$30.

![Un Wio Terminal](../../../../../translated_images/es/wio-terminal.b8299ee16587db9a.webp)

> 💁 Al buscar microcontroladores en Internet, ten cuidado al buscar el término **MCU**, ya que esto traerá muchos resultados relacionados con el Universo Cinematográfico de Marvel, no con microcontroladores.

Los microcontroladores están diseñados para ser programados para realizar un número limitado de tareas muy específicas, en lugar de ser computadoras de propósito general como las PC o Mac. Excepto en escenarios muy específicos, no puedes conectar un monitor, teclado y ratón y usarlos para tareas generales.

Los kits de desarrollo de microcontroladores generalmente vienen con sensores y actuadores adicionales integrados. La mayoría de las placas tendrán uno o más LEDs que puedes programar, junto con otros dispositivos como conectores estándar para agregar más sensores o actuadores utilizando los ecosistemas de varios fabricantes o sensores integrados (generalmente los más populares, como sensores de temperatura). Algunos microcontroladores tienen conectividad inalámbrica integrada, como Bluetooth o WiFi, o tienen microcontroladores adicionales en la placa para agregar esta conectividad.

> 💁 Los microcontroladores generalmente se programan en C/C++.

### Computadoras de placa única

Una computadora de placa única es un pequeño dispositivo de computación que tiene todos los elementos de una computadora completa contenidos en una sola placa pequeña. Estos son dispositivos con especificaciones cercanas a una PC o Mac de escritorio o portátil, ejecutan un sistema operativo completo, pero son pequeños, consumen menos energía y son sustancialmente más baratos.

![Una Raspberry Pi 4](../../../../../translated_images/es/raspberry-pi-4.fd4590d308c3d456.webp)

La Raspberry Pi es una de las computadoras de placa única más populares.

Al igual que un microcontrolador, las computadoras de placa única tienen una CPU, memoria y pines de entrada/salida, pero tienen características adicionales como un chip gráfico para permitirte conectar monitores, salidas de audio y puertos USB para conectar teclados, ratones y otros dispositivos USB estándar como cámaras web o almacenamiento externo. Los programas se almacenan en tarjetas SD o discos duros junto con un sistema operativo, en lugar de un chip de memoria integrado en la placa.

> 🎓 Puedes pensar en una computadora de placa única como una versión más pequeña y económica de la PC o Mac que estás usando, con la adición de pines GPIO (entrada/salida de propósito general) para interactuar con sensores y actuadores.

Las computadoras de placa única son computadoras completamente funcionales, por lo que pueden programarse en cualquier lenguaje. Los dispositivos IoT generalmente se programan en Python.

### Opciones de hardware para el resto de las lecciones

Todas las lecciones posteriores incluyen tareas que utilizan un dispositivo IoT para interactuar con el mundo físico y comunicarse con la nube. Cada lección admite 3 opciones de dispositivos: Arduino (usando un Seeed Studios Wio Terminal) o una computadora de placa única, ya sea un dispositivo físico (una Raspberry Pi 4) o una computadora de placa única virtual que se ejecuta en tu PC o Mac.

Puedes leer sobre el hardware necesario para completar todas las tareas en la [guía de hardware](../../../hardware.md).

> 💁 No necesitas comprar ningún hardware IoT para completar las tareas, puedes hacer todo utilizando una computadora de placa única virtual.

Qué hardware elijas depende de lo que tengas disponible en casa o en tu escuela, y del lenguaje de programación que conozcas o planees aprender. Ambas variantes de hardware usarán el mismo ecosistema de sensores, por lo que si comienzas con una opción, puedes cambiar a la otra sin tener que reemplazar la mayoría del kit. La computadora de placa única virtual será el equivalente a aprender en una Raspberry Pi, con la mayoría del código transferible a la Pi si eventualmente obtienes un dispositivo y sensores.

### Kit de desarrollo Arduino

Si estás interesado en aprender desarrollo de microcontroladores, puedes completar las tareas utilizando un dispositivo Arduino. Necesitarás un conocimiento básico de programación en C/C++, ya que las lecciones solo enseñarán el código relevante para el marco de Arduino, los sensores y actuadores que se utilizan, y las bibliotecas que interactúan con la nube.

Las tareas utilizarán [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) con la [extensión PlatformIO para desarrollo de microcontroladores](https://platformio.org). También puedes usar el IDE de Arduino si tienes experiencia con esta herramienta, ya que no se proporcionarán instrucciones.

### Kit de desarrollo de computadora de placa única

Si estás interesado en aprender desarrollo de IoT utilizando computadoras de placa única, puedes completar las tareas utilizando una Raspberry Pi o un dispositivo virtual que se ejecute en tu PC o Mac.

Necesitarás un conocimiento básico de programación en Python, ya que las lecciones solo enseñarán el código relevante para los sensores y actuadores que se utilizan, y las bibliotecas que interactúan con la nube.

> 💁 Si quieres aprender a programar en Python, consulta las siguientes dos series de videos:
>
> * [Python para principiantes](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Más Python para principiantes](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Las tareas utilizarán [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Si estás utilizando una Raspberry Pi, puedes ejecutar tu Pi utilizando la versión de escritorio completa de Raspberry Pi OS y hacer toda la programación directamente en la Pi utilizando [la versión de VS Code para Raspberry Pi OS](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), o ejecutar tu Pi como un dispositivo sin cabeza y programar desde tu PC o Mac utilizando VS Code con la [extensión Remote SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), que te permite conectarte a tu Pi y editar, depurar y ejecutar código como si estuvieras programando directamente en ella.

Si utilizas la opción de dispositivo virtual, programarás directamente en tu computadora. En lugar de acceder a sensores y actuadores, utilizarás una herramienta para simular este hardware, proporcionando valores de sensores que puedes definir y mostrando los resultados de los actuadores en pantalla.

## Configura tu dispositivo

Antes de que puedas comenzar a programar tu dispositivo IoT, necesitarás realizar una pequeña configuración. Sigue las instrucciones relevantes a continuación según el dispositivo que vayas a utilizar.
💁 Si aún no tienes un dispositivo, consulta la [guía de hardware](../../../hardware.md) para ayudarte a decidir qué dispositivo vas a usar y qué hardware adicional necesitas comprar. No es necesario que compres hardware, ya que todos los proyectos se pueden ejecutar en hardware virtual.
Estas instrucciones incluyen enlaces a sitios web de terceros de los creadores del hardware o herramientas que estarás utilizando. Esto es para garantizar que siempre tengas las instrucciones más actualizadas para las diversas herramientas y hardware.

Trabaja en la guía correspondiente para configurar tu dispositivo y completar un proyecto de 'Hola Mundo'. Este será el primer paso para crear una luz nocturna IoT a lo largo de las 4 lecciones de esta parte introductoria.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Computadora de placa única - Raspberry Pi](pi.md)
* [Computadora de placa única - Dispositivo virtual](virtual-device.md)

✅ Utilizarás VS Code tanto para Arduino como para computadoras de placa única. Si no lo has usado antes, lee más sobre ello en el [sitio de VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## Aplicaciones del IoT

El IoT abarca una amplia gama de casos de uso, divididos en algunos grupos principales:

* IoT para consumidores
* IoT comercial
* IoT industrial
* IoT para infraestructura

✅ Investiga un poco: Para cada una de las áreas descritas a continuación, encuentra un ejemplo concreto que no esté mencionado en el texto.

### IoT para consumidores

El IoT para consumidores se refiere a los dispositivos IoT que los consumidores compran y utilizan en el hogar. Algunos de estos dispositivos son increíblemente útiles, como los altavoces inteligentes, los sistemas de calefacción inteligentes y las aspiradoras robóticas. Otros son cuestionables en su utilidad, como los grifos controlados por voz que luego no puedes apagar porque el control por voz no te escucha debido al sonido del agua corriendo.

Los dispositivos IoT para consumidores están empoderando a las personas para lograr más en su entorno, especialmente los 1,000 millones que tienen alguna discapacidad. Las aspiradoras robóticas pueden proporcionar pisos limpios a personas con problemas de movilidad que no pueden aspirar por sí mismas, los hornos controlados por voz permiten a personas con visión limitada o problemas de motricidad calentar sus hornos solo con su voz, los monitores de salud permiten a los pacientes controlar condiciones crónicas con actualizaciones más regulares y detalladas sobre su estado. Estos dispositivos se están volviendo tan comunes que incluso los niños pequeños los utilizan como parte de su vida diaria, por ejemplo, estudiantes que hacen educación virtual durante la pandemia de COVID configurando temporizadores en dispositivos inteligentes para seguir su trabajo escolar o alarmas para recordarles reuniones de clase próximas.

✅ ¿Qué dispositivos IoT para consumidores tienes contigo o en tu hogar?

### IoT comercial

El IoT comercial abarca el uso de IoT en el lugar de trabajo. En un entorno de oficina, puede haber sensores de ocupación y detectores de movimiento para gestionar la iluminación y la calefacción, manteniendo las luces y el calor apagados cuando no se necesitan, reduciendo costos y emisiones de carbono. En una fábrica, los dispositivos IoT pueden monitorear peligros de seguridad como trabajadores que no usan cascos o niveles de ruido que han alcanzado niveles peligrosos. En el comercio minorista, los dispositivos IoT pueden medir la temperatura de almacenamiento en frío, alertando al propietario de la tienda si un refrigerador o congelador está fuera del rango de temperatura requerido, o pueden monitorear los artículos en los estantes para dirigir a los empleados a reponer productos que se han vendido. La industria del transporte depende cada vez más del IoT para monitorear la ubicación de los vehículos, rastrear el kilometraje en carretera para el cobro de peajes, verificar el cumplimiento de las horas de conducción y descansos, o notificar al personal cuando un vehículo se acerca a un depósito para prepararse para la carga o descarga.

✅ ¿Qué dispositivos IoT comerciales tienes en tu escuela o lugar de trabajo?

### IoT industrial (IIoT)

El IoT industrial, o IIoT, es el uso de dispositivos IoT para controlar y gestionar maquinaria a gran escala. Esto abarca una amplia gama de casos de uso, desde fábricas hasta agricultura digital.

Las fábricas utilizan dispositivos IoT de muchas maneras diferentes. La maquinaria puede ser monitoreada con múltiples sensores para rastrear cosas como temperatura, vibración y velocidad de rotación. Estos datos pueden ser monitoreados para permitir que la máquina se detenga si se sale de ciertos límites, por ejemplo, si se calienta demasiado y se apaga. Estos datos también pueden ser recopilados y analizados con el tiempo para realizar mantenimiento predictivo, donde los modelos de IA analizan los datos previos a una falla y los utilizan para predecir otras fallas antes de que ocurran.

La agricultura digital es importante si el planeta debe alimentar a la población en crecimiento, especialmente para los 2,000 millones de personas en 500 millones de hogares que dependen de la [agricultura de subsistencia](https://wikipedia.org/wiki/Subsistence_agriculture). La agricultura digital puede variar desde sensores de pocos dólares hasta configuraciones comerciales masivas. Un agricultor puede comenzar monitoreando temperaturas y utilizando [días grado de crecimiento](https://wikipedia.org/wiki/Growing_degree-day) para predecir cuándo una cosecha estará lista para la recolección. Pueden conectar el monitoreo de humedad del suelo a sistemas de riego automatizados para dar a sus plantas tanta agua como necesiten, pero no más, asegurando que sus cultivos no se sequen sin desperdiciar agua. Los agricultores incluso están llevando esto más lejos utilizando drones, datos satelitales y IA para monitorear el crecimiento de cultivos, enfermedades y calidad del suelo en grandes áreas de terreno agrícola.

✅ ¿Qué otros dispositivos IoT podrían ayudar a los agricultores?

### IoT para infraestructura

El IoT para infraestructura monitorea y controla la infraestructura local y global que las personas utilizan todos los días.

[Ciudades inteligentes](https://wikipedia.org/wiki/Smart_city) son áreas urbanas que utilizan dispositivos IoT para recopilar datos sobre la ciudad y usarlos para mejorar cómo funciona. Estas ciudades suelen ser gestionadas con colaboraciones entre gobiernos locales, academia y negocios locales, rastreando y gestionando cosas que varían desde transporte hasta estacionamiento y contaminación. Por ejemplo, en Copenhague, Dinamarca, la contaminación del aire es importante para los residentes locales, por lo que se mide y los datos se utilizan para proporcionar información sobre las rutas más limpias para andar en bicicleta o correr.

[Redes eléctricas inteligentes](https://wikipedia.org/wiki/Smart_grid) permiten mejores análisis de la demanda de energía al recopilar datos de uso a nivel de hogares individuales. Estos datos pueden guiar decisiones a nivel país, como dónde construir nuevas plantas de energía, y a nivel personal, proporcionando a los usuarios información sobre cuánto energía están utilizando, cuándo la están utilizando e incluso sugerencias para reducir costos, como cargar autos eléctricos por la noche.

✅ Si pudieras agregar dispositivos IoT para medir algo donde vives, ¿qué sería?

## Ejemplos de dispositivos IoT que podrías tener cerca de ti

Te sorprendería saber cuántos dispositivos IoT tienes cerca de ti. Estoy escribiendo esto desde casa y tengo los siguientes dispositivos conectados a Internet con funciones inteligentes como control por aplicación, control por voz o la capacidad de enviarme datos a través de mi teléfono:

* Múltiples altavoces inteligentes
* Refrigerador, lavavajillas, horno y microondas
* Monitor de electricidad para paneles solares
* Enchufes inteligentes
* Timbre con video y cámaras de seguridad
* Termostato inteligente con múltiples sensores inteligentes de habitación
* Abridor de puerta de garaje
* Sistemas de entretenimiento en el hogar y televisores controlados por voz
* Luces
* Rastreadores de salud y fitness

Todos estos tipos de dispositivos tienen sensores y/o actuadores y se conectan a Internet. Puedo saber desde mi teléfono si mi puerta de garaje está abierta y pedirle a mi altavoz inteligente que la cierre por mí. Incluso puedo configurarla con un temporizador para que, si sigue abierta por la noche, se cierre automáticamente. Cuando suena mi timbre, puedo ver desde mi teléfono quién está allí, donde sea que esté en el mundo, y hablar con ellos a través de un altavoz y micrófono integrados en el timbre. Puedo monitorear mi glucosa en sangre, ritmo cardíaco y patrones de sueño, buscando patrones en los datos para mejorar mi salud. Puedo controlar mis luces a través de la nube y quedarme en la oscuridad cuando mi conexión a Internet se cae.

---

## 🚀 Desafío

Haz una lista de tantos dispositivos IoT como puedas que estén en tu hogar, escuela o lugar de trabajo; puede que haya más de los que piensas.

## Cuestionario posterior a la clase

[Cuestionario posterior a la clase](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Revisión y autoestudio

Investiga sobre los beneficios y fracasos de los proyectos de IoT para consumidores. Consulta sitios de noticias para artículos sobre cuando han salido mal, como problemas de privacidad, problemas de hardware o problemas causados por la falta de conectividad.

Algunos ejemplos:

* Consulta la cuenta de Twitter **[Internet of Sh*t](https://twitter.com/internetofshit)** *(advertencia de lenguaje)* para algunos buenos ejemplos de fracasos con IoT para consumidores.
* [c|net - Mi Apple Watch salvó mi vida: 5 personas comparten sus historias](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - Técnico de ADT se declara culpable de espiar las cámaras de clientes durante años](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(advertencia de contenido - voyeurismo no consensuado)*

## Tarea

[Investiga un proyecto de IoT](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.