# Introducción al IoT

![Un sketchnote de la información general de esta lección](../../../../sketchnotes/lesson-1.jpg)

> Sketchnote por [Nitya Narasimhan](https://github.com/nitya). Da Click en la imagen para ver en pantalla completa.

## Un cuestionario antes de empezar

[cuestionario antes de empezar](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/1)

## Introducción

Esta lección cubre algunos de los temas de introducción acerca del Internet de las cosas, y te permite comenzar a configurar tu hardware.

En esta lección vamos a cubrir:

* [¿Qué es el "Internet de las Cosas"?](#concepto-de-internet-de-las-cosas)
* [Dispositivos IoT](#dispositivos-iot)
* [Configura tu dispositivo](#configura-tu-dispositivo)
* [Aplicaciones del IoT](#aplicaciones-del-iot)
* [Ejemplos de dispositivos IoT a tu alrededor](#ejemplos-de-dispositivos-de-iot-que-puedes-tener-a-tu-alrededor)

## Concepto de Internet de las Cosas

El término "Internet de las cosas" fue acuñado por [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) en 1999, para referirse a conectar el internet con el mundo físico a través de sensores. Desde entonces, el término ha sido utilizado para describir cualquier dispositivo que interactúa con el mundo físico a su alrededor, ya sea por la adquisición de los datos de los sensores, o por proveer interacciones a través de actuadores (dispositivos que realizan acciones como encender un interruptor o encender un LED), generalmente conectado a otros dispositivos o al internet.

> **Sensores** recolectan información del mundo real, como medir la velocidad, temperatura o locación.
>
> **Actuadores** convierten señales eléctricas en interacciones con el mundo real como lo son el encender un interruptor, encender una lampara, hacer sonidos o enviando señales de control a otro hardware, por ejemplo, energizar una toma de electricidad.

IoT como área de tecnología es más que solo dispositivos - incluye servicios basados en la nube que pueden procesar los datos de los sensores o enviar solicitudes a los actuadores conectados a los dispositivos IoT. También incluye dispositivos que no tienen o no necesitan conexión a Internet, comúnmente llamados dispositivos perimetrales. Estos son dispositivos pueden procesar y responder a los datos de sensores por su propia cuenta, comúnmente utilizando modelos de AI entrenados en la nube.

IoT es un campo de la tecnología en rápido crecimiento. Es estimado que, para el final de 2020, 30 miles de millones de dispositivos fueron desplegados y conectados a internet. Viendo hacia el futuro, se estima que para 2025, los dispositivos IoT van a generar casi 80 zettabytes de datos o 80 billones de gigabytes. ¡Esos son muchos datos!

![Un gráfico que muestra los dispositivos IoT activos a través del tiempo, con una tendencia creciente de menos de 5 miles de millones en 2015 hasta más de 30 miles de millones en 2025](../../../../images/connected-iot-devices.svg)

✅ Haz una pequeña investigación: ¿Cuántos datos generados por los dispositivos IoT sí son utilizados?, ¿Qué tantos datos son desperdiciados? ¿Por qué son ignorados?

Estos datos son la clave del éxito del IoT. Para ser un desarrollador de IoT exitoso, tienes que entender los datos que tienes que recopilar, cómo recopilarlos, cómo tomar decisiones basadas en ellos, y cómo utilizar esas decisiones para interactuar con el mundo físico si es necesario.

## Dispositivos IoT

La **T** en IoT representa **Things** (cosas) - dispositivos que interactúan con el mundo físico a su alrededor a través de la recolección de datos de sensores o proporcionando interacciones en el mundo real a través de actuadores.

Dispositivos para producción o uso comercial, como lo son dispositivos de monitoreo de actividad física, o controladores de máquinas industriales, son usualmente hechos a medida. Utilizan placas de circuito impreso personalizadas, tal vez incluso procesadores personalizados, diseñados para satisfacer las necesidades de una tarea en particular, ya sea que sea lo suficientemente pequeña para caber en la muñeca del brazo o lo suficientemente resistente para trabajar en un entorno industrial de alta temperatura, alto estrés o alta vibración.

Como desarrollador, ya sea que estes aprendiendo sobre IoT o creando un  dispositivo de prototipo, deberas de comenzar con un kit de desarrollador. Estos son dispositivos  IoT de uso general diseñados para que los utilicen los desarrolladores, a menudo con características que no tendría en un dispositivo de producción, como un conjunto de pines externos para conectar sensores o actuadores, hardware para admitir la depuración o recursos adicionales que agregaría costos innecesarios al realizar una gran producción.  

Estos kits de desarrollo generalmente se dividen en dos categorías: microcontroladores y computadoras de una sola placa. Estos serán presentados en esta sección y entraremos en más detalles en la próxima lección.

> 💁 Tu teléfono también puede considerarse un dispositivo de IoT de uso general, con sensores y actuadores integrados, con diferentes aplicaciones que utilizan los sensores y actuadores de diferentes maneras con diferentes servicios en la nube. Incluso puede encontrar algunos tutoriales de IoT que utilizan una aplicación de teléfono como dispositivo de IoT.

### Microcontroladores

Un microcontrolador (también conocido como MCU, abreviatura de unidad de microcontrolador) es una pequeña computadora que consta de:

🧠 Una o más unidades centrales de procesamiento (CPU): el "cerebro" del microcontrolador que ejecuta tu programa

💾 Memoria (RAM y memoria de programa): donde se almacenan tu programa, datos y variables

🔌 Puertos de entrada / salida (E / S) programables: para comunicarse con periféricos externos (dispositivos conectados) como sensores y actuadores

Los microcontroladores suelen ser dispositivos de computación de bajo costo, con precios promedio de los que se utilizan en hardware personalizado que bajan hasta a alrededor de US $ 0,50, y algunos dispositivos tan baratos como US $ 0,03. Los kits para desarrolladores pueden comenzar desde US $ 4, y los costos aumentan a medida que agrega más funciones. La [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), un kit de desarrollo para microcontroladores de [Seeed studios](https://www.seeedstudio.com) que tiene sensores, actuadores, WiFi y una pantalla cuesta alrededor de US$30.

![Wio Terminal](../../../../images/wio-terminal.png)

> 💁 Cuando busques sobre microcontroladores en Internet, ten cuidado al buscar el término **MCU**, ya que esto te traerá muchos resultados del Marvel Cinematic Universe, no de los microcontroladores.

Los microcontroladores están diseñados para ser programados para realizar un número limitado de tareas muy específicas, en lugar de ser computadoras de uso general como una PC o un Mac. Excepto en escenarios muy específicos, no podrás conectar un monitor, teclado y ratón y usarlos para tareas de propósito general.

Los kits de desarrollo para microcontroladores generalmente vienen con sensores y actuadores adicionales en la placa. La mayoría de las placas tendrán uno o más LED que puedes programar, junto con otros dispositivos, como conectores estándar para agregar más sensores o actuadores utilizando estándares de varios fabricantes o sensores integrados (generalmente los más populares, como los sensores de temperatura). Algunos microcontroladores tienen conectividad inalámbrica incorporada como Bluetooth o WiFi o tienen microcontroladores adicionales en la placa para agregar esta conectividad.

> 💁 Los microcontroladores son usualmente programados en C/C++.

### Computadoras de una sola placa

Una computadora de una sola placa es un pequeño dispositivo computacional que tiene todos los elementos de una computadora completa, pero contenidos en una sola placa de circuito pequeña. Estos son dispositivos que tienen especificaciones similares a las de una computadora de escritorio o laptop o Mac, ejecutan un sistema operativo completo, pero son pequeños, consumen menos energía y son sustancialmente más baratos.

![Raspberry Pi 4](../../../../images/raspberry-pi-4.jpg)

***Raspberry Pi 4. Michael Henzler / [Wikimedia Commons](https://commons.wikimedia.org/wiki/Main_Page) / [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/)***

La Raspberry Pi es una de las computadoras de una sola placa populares.

Al igual que un microcontrolador, las computadoras de placa única tienen CPU, memoria y pines de entrada / salida, pero tienen características adicionales como un chip gráfico que les permite conectar monitores, salidas de audio y puertos USB para conectar teclados, ratones y otros dispositivos USB estándar. Dispositivos como cámaras web o almacenamiento externo. Los programas se almacenan en tarjetas SD o discos duros junto con un sistema operativo, en lugar de un chip de memoria integrado en la placa.

> 🎓 Puedes pensar en una computadora de una sola placa como una versión más pequeña y económica de la PC o Mac en la que estas leyendo esto, con la adición de pines GPIO (entrada / salida de propósito general) para interactuar con sensores y actuadores.

Las computadoras de placa única son computadoras con todas las funciones, por lo que se pueden programar en cualquier idioma. Los dispositivos de IoT generalmente se programan en Python.

### Opciones de hardware para el resto de las lecciones

Todas las lecciones posteriores incluyen tareas que utilizan un dispositivo de IoT para interactuar con el mundo físico y comunicarse con la nube. Cada lección admite 3 opciones de dispositivo: Arduino (usando una terminal Wio de Seeed Studios) o una computadora de una sola placa, ya sea un dispositivo físico (una Raspberry Pi 4) o una computadora virtual que se ejecuta en su PC o Mac.

Puedes leer sobre el hardware necesario para completar todas las asignaciones en la [Guía de hardware](../../../../hardware.md).

> 💁 No necesitas comprar ningún hardware de IoT para completar las lecciones, puede hacerlo todo con una computadora virtual simulada de una computadora de una sola placa.

El hardware que elijas depende de ti; depende de lo que tengas disponible en casa o en tu escuela y del lenguaje de programación que conozcas o planees aprender. Ambas variantes de hardware usarán el mismo ecosistema de sensores, por lo que si comienzas por un camino, puedes cambiar al otro sin tener que reemplazar la mayor parte del kit. La computadora virtual de la computadora de una sola placa será el equivalente a aprender en una Raspberry Pi, con la mayor parte del código transferible a la Raspberry Pi si finalmente obtienes un dispositivo y sensores.

### Kit de desarrollador Arduino

Si estas interesado en aprender sobre desarrollo en microcontroladores, puedes completar las lecciones utilizando un dispositivo Arduino. Necesitaras una comprensión básica de la programación C / C ++, ya que las lecciones solo enseñarán código que sea relevante para el marco de trabajo de Arduino, los sensores y actuadores que se utilizan y las bibliotecas que interactúan con la nube.

Las lecciones utilizarán [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) con la [extensión PlatformIO para desarrollo en microcontroladores](https://platformio.org). También puedes usar el IDE de Arduino si tienes experiencia con esta herramienta, ya que no se proporcionarán instrucciones de instalación.

### Kit de desarrollo de computadora de ubna sola placa 

Si estas interesado en aprender sobre el desarrollo de IoT utilizando computadoras de placa única, puedes completar las lecciones con una Raspberry Pi o un dispositivo virtual simulado que se ejecute en su PC o Mac.

Necesitaras una comprensión básica de la programación en Python, ya que las lecciones solo enseñarán el código que es relevante para los sensores y actuadores que se utilizan, y las bibliotecas que interactúan con la nube.

> 💁 Si deseas aprender a programar en Python, consulta las siguientes dos series de videos:
>
> * [Python para novatos](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Más Python para novatos](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

La lectura utilizará [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Si estas utilizando una Raspberry Pi, puedes utilizar tu Raspberry Pi utilizando la versión de escritorio completa del sistema operativo Raspberry Pi y hacer toda la programación directamente en la Pi utilizando [La versión del sistema operativo Raspberry Pi de VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), o utiliza tu Pi como un dispositivo sin interfaz gráfica y programa desde tu PC o Mac usando VS Code con el [Extensión SSH remoto](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) que te permite conectarte a tu Pi y editar, depurar y ejecutar código como si lo estuvieras programando directamente.

Si usas la opción de dispositivo virtual simulado, programarás directamente en tu computadora. En lugar de acceder a sensores y actuadores, utilizaras una herramienta para simular este hardware que proporciona valores de sensores que puedes definir y muestra los resultados de los actuadores en la pantalla.

## Configura tu dispositivo

Antes de que puedas comenzar a programar tu dispositivo IoT, deberás realizar una pequeña configuración. Sigue las instrucciones pertinentes a continuación según el dispositivo que vayas a utilizar.

> 💁 Si aún no tienes un dispositivo, consulta la [guía de hardware](../../../hardware.md) para ayudarte a decidir qué dispositivo vas a utilizar y qué hardware adicional necesitas comprar. No es necesario comprar hardware, ya que todos los proyectos se pueden ejecutar desde hardware virtual.

Estas instrucciones incluyen enlaces a sitios web de terceros, de los creadores del hardware o las herramientas que se utilizarán. Esto es para garantizar que siempre estés utilizando las instrucciones más actualizadas para las diversas herramientas y hardware.

Trabaja con la guía correspondiente para configurar tu dispositivo y completar un proyecto de "Hola mundo". Este será el primer paso para crear una luz nocturna con IoT de las 4 lecciones de esta parte de introducción.

* [Arduino - Wio Terminal](../wio-terminal.md)
* [Single-board computer - Raspberry Pi](../pi.md)
* [Single-board computer - Dispositivo virtual](../virtual-device.md)

✅ Utilizarás VS Code tanto para Arduino como para computadoras de placa única. Si no lo ha usado antes, lee más sobre él en el [sitio de VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

## Aplicaciones del IoT

IoT cubre una amplia gama de casos de uso, en unos pocos grupos amplios:

* IoT para el consumidor
* IoT comercial
* IoT industrial
* Infraestructura IoT

✅ Investiga un poco: para cada una de las áreas que se describen a continuación, busca un ejemplo concreto que no se encuentre en este texto.

### IoT para el consumidor

IoT para el consumidor se refiere a los dispositivos de IoT que los consumidores comprarán y usarán en el hogar. Algunos de estos dispositivos son increíblemente útiles, como altavoces inteligentes, sistemas de calefacción inteligentes y aspiradoras robóticas. Otros son cuestionables en su utilidad, como los grifos controlados por voz que significan que no puede apagarlos, ya que el control por voz no puede escucharlo por encima del sonido del agua corriente.

Los dispositivos de IoT para consumidores están habilitando a las personas para lograr más en su entorno, especialmente los mil millones que tienen una discapacidad. Las aspiradoras robóticas pueden proporcionar pisos limpios a las personas con problemas de movilidad que no pueden aspirar por sí mismas, los hornos controlados por voz permiten a las personas con visión limitada calentar sus hornos solo con la voz, los monitores de salud pueden permitir que los pacientes monitoreen sus condiciones crónicas por si mismos con más actualizaciones periódicas y más detalladas sobre sus condiciones. Estos dispositivos se están volviendo tan omnipresentes que incluso los niños pequeños los usan como parte de su vida diaria, por ejemplo, los estudiantes que realizan educación virtual durante la pandemia de COVID configuran temporizadores en dispositivos domésticos inteligentes para rastrear sus tareas escolares o alarmas para recordarles las próximas reuniones de clase. 

✅ ¿Qué dispositivos de IoT de consumo tienes sobre ti o en tu hogar?

### IoT comercial

IoT comercial cubre el uso de IoT en el lugar de trabajo. En un entorno de oficina, puede haber sensores de ocupación y detectores de movimiento para administrar la iluminación y la calefacción para mantener las luces y la calefacción apagadas cuando no se necesitan, lo que reduce los costos y las emisiones de carbono. En una fábrica, los dispositivos de IoT pueden monitorear los peligros de seguridad, como los trabajadores que no usan cascos o el ruido que ha alcanzado niveles peligrosos. En el comercio minorista, los dispositivos de IoT pueden medir la temperatura del almacenamiento en frío, alertando al propietario de la tienda si un refrigerador o congelador está fuera del rango de temperatura requerido, o pueden monitorear los artículos en los estantes para indicar a los empleados que rellenen los productos que se han vendido. La industria del transporte confía cada vez más en IoT para monitorear la ubicación de los vehículos, rastrear el kilometraje en la carretera para cobrar a los usuarios de la carretera, rastrear las horas del conductor y no cumplir, o notificar al personal cuando un vehículo se acerca a un depósito para prepararse para la carga o descarga.

✅ ¿Qué dispositivos comerciales de IoT tienes en tu escuela o lugar de trabajo?

### IoT Industrial  (IIoT)

IoT industrial, o IIoT, es el uso de dispositivos de IoT para controlar y gestionar maquinaria a gran escala. Esto cubre una amplia gama de casos de uso, desde fábricas hasta agricultura digital.

Las fábricas utilizan los dispositivos IoT de muchas formas diferentes. La maquinaria se puede monitorear con múltiples sensores para rastrear cosas como temperatura, vibración y velocidad de rotación. Luego, estos datos se pueden monitorear para permitir que la máquina se detenga si se sale de ciertas tolerancias; se calienta demasiado y se apaga. Por ejemplo, estos datos también se pueden recopilar y analizar a lo largo del tiempo para realizar un mantenimiento predictivo, donde los modelos de IA observarán los datos que conducen a una falla y los usarán para predecir otras fallas antes de que sucedan.

La agricultura digital es importante para que el planeta alimente a la creciente población, especialmente para los 2 mil millones de personas en 500 millones de hogares que sobreviven de [la agricultura de subsistencia](https://wikipedia.org/wiki/Subsistence_agriculture). La agricultura digital puede variar desde unos pocos sensores de bajo costo hasta configuraciones comerciales masivas. Un agricultor puede comenzar controlando las temperaturas y utilizando [growing degree days](https://wikipedia.org/wiki/Growing_degree-day) para predecir cuándo un cultivo estará listo para la cosecha. Pueden conectar el control de la humedad del suelo a sistemas de riego automatizados para dar a sus plantas tanta agua como sea necesaria, pero no más, para garantizar que sus cultivos no se sequen sin desperdiciar agua. Los agricultores incluso lo están llevando más allá y utilizan drones, datos satelitales e inteligencia artificial para monitorear el crecimiento de los cultivos, las enfermedades y la calidad del suelo en grandes áreas de tierras agrícolas.

✅ ¿Qué otros dispositivos de IoT podrían ayudar a los agricultores?

### Infraestructura IoT

"Infrastructure IoT" monitorea y controla la infraestructura local y global que la gente usa todos los días.

[Ciudades inteligentes](https://wikipedia.org/wiki/Smart_city) son áreas urbanas que utilizan dispositivos de IoT para recopilar datos sobre la ciudad y utilizarlos para mejorar el funcionamiento de la ciudad. Estas ciudades generalmente se gestionan con colaboraciones entre los gobiernos locales, la academia y las empresas locales, rastreando y administrando cosas que van desde el transporte hasta el estacionamiento y la contaminación. Por ejemplo, en Copenhague, Dinamarca, la contaminación del aire es importante para los residentes locales, por lo que se mide y los datos se utilizan para proporcionar información sobre las rutas de ciclismo y jogging más limpias.

[Red de energía inteligente](https://wikipedia.org/wiki/Smart_grid) permite un mejor análisis de la demanda de energía mediante la recopilación de datos de uso a nivel de hogares individuales. Estos datos pueden orientar las decisiones a nivel de país, incluido dónde construir nuevas centrales eléctricas, y a nivel personal, brindando a los usuarios información sobre cuánta energía están usando, cuándo la están usando e incluso sugerencias sobre cómo reducir costos, por ejemplo, como cargar coches eléctricos por la noche.

✅ Si pudieras agregar dispositivos de IoT para medir cualquier cosa en el lugar donde vives, ¿cuál sería?

## Ejemplos de dispositivos de IoT que puedes tener a tu alrededor

Te sorprenderá la cantidad de dispositivos de IoT que tienes a tu alrededor. Escribo esto desde casa y tengo los siguientes dispositivos conectados a Internet con funciones inteligentes como control mediante aplicaciones, control por voz o la capacidad de enviarme datos a través de mi teléfono:

* Varios altavoces inteligentes
* Nevera, lavavajillas, horno y microondas.
* Monitor de electricidad para paneles solares.
* Enchufes inteligentes
* Video timbre y cámaras de seguridad.
* Termostato inteligente con múltiples sensores de habitación inteligentes
* Puerta de garaje automática
* Sistemas de entretenimiento en el hogar y televisores controlados por voz.
* Luces
* Rastreadores de estado físico y salud

Todos estos tipos de dispositivos tienen sensores y / o actuadores y se comunican con Internet. Puedo saber desde mi teléfono si la puerta de mi garaje está abierta y pedirle a mi altavoz inteligente que la cierre por mí. Incluso puedo configurarlo con un temporizador, de modo que si todavía está abierto por la noche, se cerrará automáticamente. Cuando suena el timbre, puedo ver desde mi teléfono quién está allí en cualquier parte del mundo y hablar con ellos a través de un altavoz y un micrófono integrados en el timbre. Puedo controlar mi glucosa en sangre, frecuencia cardíaca y patrones de sueño, buscando patrones en los datos para mejorar mi salud. Puedo controlar mis luces a través de la nube y sentarme en la oscuridad cuando mi conexión a Internet se cae.

---

## 🚀 Desafío

Enumera todos los dispositivos de IoT que estén en tu hogar, escuela o lugar de trabajo; ¡puede haber más de los que crees!

## Cuestionario posterior a la lección

[Cuestionario posterior a la lección](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/2)

## Revisión y autoestudio

Obtén más información sobre los beneficios y los fracasos de los proyectos de IoT para consumidores. Consulte los sitios de noticias en busca de artículos sobre cuándo una idea sale mal, como problemas de privacidad, problemas de hardware o problemas causados ​​por la falta de conectividad.

Algunos ejemplos:

* Echa un vistazo a la cuenta de Twitter **[Internet of Sh*t](https://twitter.com/internetofshit)** *(advertencia contenido vulgar)* para ver algunos buenos ejemplos de fracasos en productos IoT para el consumidor.
* [c|net - My Apple Watch saved my life: 5 people share their stories](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - ADT technician pleads guilty to spying on customer camera feeds for years](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(advertencia - voyerismo no consensuado)*

## Tarea

[Investigar un proyecto de IoT](assignment.es.md)
