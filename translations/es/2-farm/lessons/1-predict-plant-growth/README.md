<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d105b44deae539165855c976dcdeca99",
  "translation_date": "2025-08-26T14:27:56+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/README.md",
  "language_code": "es"
}
-->
## Pre-lecture quiz

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Introducción

Las plantas necesitan ciertos elementos para crecer: agua, dióxido de carbono, nutrientes, luz y calor. En esta lección, aprenderás cómo calcular las tasas de crecimiento y madurez de las plantas midiendo la temperatura del aire.

En esta lección cubriremos:

* [Agricultura digital](../../../../../2-farm/lessons/1-predict-plant-growth)
* [¿Por qué es importante la temperatura en la agricultura?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Medir la temperatura ambiente](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Días grado de crecimiento (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Calcular GDD usando datos de sensores de temperatura](../../../../../2-farm/lessons/1-predict-plant-growth)

## Agricultura digital

La agricultura digital está transformando la forma en que cultivamos, utilizando herramientas para recopilar, almacenar y analizar datos agrícolas. Actualmente estamos en un período descrito como la 'Cuarta Revolución Industrial' por el Foro Económico Mundial, y el auge de la agricultura digital ha sido denominado la 'Cuarta Revolución Agrícola' o 'Agricultura 4.0'.

> 🎓 El término Agricultura Digital también incluye toda la 'cadena de valor agrícola', es decir, todo el recorrido desde la granja hasta la mesa. Incluye el seguimiento de la calidad de los productos mientras se transportan y procesan, sistemas de almacén y comercio electrónico, e incluso aplicaciones para alquilar tractores.

Estos cambios permiten a los agricultores aumentar los rendimientos, usar menos fertilizantes y pesticidas, y optimizar el uso del agua. Aunque principalmente se utiliza en países más ricos, los sensores y otros dispositivos están reduciendo lentamente su precio, haciéndolos más accesibles en países en desarrollo.

Algunas técnicas habilitadas por la agricultura digital son:

* Medición de temperatura: medir la temperatura permite a los agricultores predecir el crecimiento y la madurez de las plantas.
* Riego automatizado: medir la humedad del suelo y activar los sistemas de riego cuando el suelo está demasiado seco, en lugar de regar según un horario. El riego programado puede llevar a que los cultivos reciban poca agua durante una ola de calor y sequía, o demasiada agua durante la lluvia. Al regar solo cuando el suelo lo necesita, los agricultores pueden optimizar el uso del agua.
* Control de plagas: los agricultores pueden usar cámaras en robots automatizados o drones para buscar plagas y luego aplicar pesticidas solo donde sea necesario, reduciendo la cantidad de pesticidas utilizados y minimizando el impacto en los suministros de agua locales.

✅ Investiga. ¿Qué otras técnicas se utilizan para mejorar los rendimientos agrícolas?

> 🎓 El término 'Agricultura de Precisión' se utiliza para definir la observación, medición y respuesta a los cultivos en función de cada campo, o incluso de partes de un campo. Esto incluye medir niveles de agua, nutrientes y plagas y responder con precisión, como regar solo una pequeña parte de un campo.

## ¿Por qué es importante la temperatura en la agricultura?

Cuando aprendemos sobre las plantas, la mayoría de los estudiantes son enseñados sobre la necesidad de agua, luz, dióxido de carbono y nutrientes. Las plantas también necesitan calor para crecer; por eso florecen en primavera cuando la temperatura aumenta, por qué los narcisos o campanillas pueden brotar temprano debido a un breve período cálido, y por qué los invernaderos son tan efectivos para hacer crecer las plantas.

> 🎓 Los invernaderos y los hothouses hacen un trabajo similar, pero con una diferencia importante. Los hothouses se calientan artificialmente y permiten a los agricultores controlar las temperaturas con mayor precisión, mientras que los invernaderos dependen del sol para el calor y generalmente solo tienen ventanas u otras aperturas para dejar salir el calor.

Las plantas tienen una temperatura base o mínima, una temperatura óptima y una temperatura máxima, todas basadas en temperaturas promedio diarias.

* Temperatura base: es la temperatura promedio diaria mínima necesaria para que una planta crezca.
* Temperatura óptima: es la mejor temperatura promedio diaria para obtener el mayor crecimiento.
* Temperatura máxima: es la temperatura máxima que una planta puede soportar. Por encima de esta, la planta detendrá su crecimiento para conservar agua y sobrevivir.

> 💁 Estas son temperaturas promedio, calculadas a partir de las temperaturas diurnas y nocturnas. Las plantas también necesitan diferentes temperaturas durante el día y la noche para fotosintetizar de manera más eficiente y ahorrar energía por la noche.

Cada especie de planta tiene valores diferentes para su temperatura base, óptima y máxima. Por eso algunas plantas prosperan en países cálidos y otras en países fríos.

✅ Investiga. Para las plantas que tengas en tu jardín, escuela o parque local, ¿puedes encontrar la temperatura base?

![Un gráfico que muestra la tasa de crecimiento aumentando a medida que la temperatura sube, y luego disminuyendo cuando la temperatura es demasiado alta](../../../../../translated_images/plant-growth-temp-graph.c6d69c9478e6ca83.es.png)

El gráfico anterior muestra un ejemplo de la relación entre la tasa de crecimiento y la temperatura. Hasta la temperatura base no hay crecimiento. La tasa de crecimiento aumenta hasta la temperatura óptima y luego disminuye después de alcanzar este pico. A la temperatura máxima, el crecimiento se detiene.

La forma de este gráfico varía según la especie de planta. Algunas tienen caídas más pronunciadas por encima de la temperatura óptima, otras tienen aumentos más lentos desde la base hasta la óptima.

> 💁 Para que un agricultor obtenga el mejor crecimiento, necesitará conocer los tres valores de temperatura y entender la forma de los gráficos para las plantas que está cultivando.

Si un agricultor tiene control de la temperatura, por ejemplo, en un hothouse comercial, entonces puede optimizar para sus plantas. Un hothouse comercial que cultiva tomates, por ejemplo, tendrá la temperatura configurada alrededor de 25°C durante el día y 20°C por la noche para obtener el crecimiento más rápido.

> 🍅 Combinando estas temperaturas con luces artificiales, fertilizantes y niveles controlados de dióxido de carbono, los productores comerciales pueden cultivar y cosechar durante todo el año.

## Medir la temperatura ambiente

Los sensores de temperatura pueden usarse con dispositivos IoT para medir la temperatura ambiente.

### Tarea - medir la temperatura

Sigue la guía correspondiente para monitorear temperaturas usando tu dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-temp.md)
* [Computadora de placa única - Raspberry Pi](pi-temp.md)
* [Computadora de placa única - Dispositivo virtual](virtual-device-temp.md)

## Días grado de crecimiento

Los días grado de crecimiento (también conocidos como unidades grado de crecimiento) son una forma de medir el crecimiento de las plantas en función de la temperatura. Suponiendo que una planta tiene suficiente agua, nutrientes y dióxido de carbono, la temperatura determina la tasa de crecimiento.

Los días grado de crecimiento, o GDD, se calculan por día como la temperatura promedio en Celsius de un día por encima de la temperatura base de la planta. Cada planta necesita un cierto número de GDD para crecer, florecer o producir y madurar un cultivo. Cuantos más GDD por día, más rápido crecerá la planta.

> 🇺🇸 Para los estadounidenses, los días grado de crecimiento también pueden calcularse usando Fahrenheit. 5 GDD (en Celsius) equivalen a 9 GDD (en Fahrenheit).

La fórmula completa para calcular GDD es un poco complicada, pero hay una ecuación simplificada que a menudo se utiliza como una buena aproximación:

![GDD = T max + T min dividido por 2, todo menos T base](../../../../../translated_images/gdd-calculation.79b3660f9c5757aa92dc2dd2cdde75344e2d2c1565c4b3151640f7887edc0275.es.png)

* **GDD** - este es el número de días grado de crecimiento
* **T max** - esta es la temperatura máxima diaria en grados Celsius
* **T min** - esta es la temperatura mínima diaria en grados Celsius
* **T base** - esta es la temperatura base de la planta en grados Celsius

> 💁 Hay variaciones que consideran T max por encima de 30°C o T min por debajo de T base, pero las ignoraremos por ahora.

### Ejemplo - Maíz 🌽

Dependiendo de la variedad, el maíz necesita entre 800 y 2,700 GDD para madurar, con una temperatura base de 10°C.

En el primer día por encima de la temperatura base, se midieron las siguientes temperaturas:

| Medición    | Temp °C |
| :---------- | :-----: |
| Máxima      | 16      |
| Mínima      | 12      |

Usando estos números en nuestra fórmula:

* T max = 16
* T min = 12
* T base = 10

Esto da un cálculo de:

![GDD = 16 + 12 dividido por 2, todo menos 10, dando un resultado de 4](../../../../../translated_images/gdd-calculation-corn.64a58b7a7afcd0dfd46ff733996d939f17f4f3feac9f0d1c632be3523e51ebd9.es.png)

El maíz recibió 4 GDD ese día. Suponiendo una variedad de maíz que necesita 800 GDD para madurar, necesitará otros 796 GDD para alcanzar la madurez.

✅ Investiga. Para las plantas que tengas en tu jardín, escuela o parque local, ¿puedes encontrar el número de GDD necesarios para alcanzar la madurez o producir cultivos?

## Calcular GDD usando datos de sensores de temperatura

Las plantas no crecen en fechas fijas; por ejemplo, no puedes plantar una semilla y saber que la planta dará frutos exactamente 100 días después. En cambio, como agricultor puedes tener una idea aproximada de cuánto tiempo tarda una planta en crecer y luego verificar diariamente para ver cuándo los cultivos están listos.

Esto tiene un gran impacto en la mano de obra en una granja y corre el riesgo de que el agricultor pase por alto cultivos que estén listos inesperadamente temprano. Al medir las temperaturas, el agricultor puede calcular los GDD que una planta ha recibido, permitiéndole verificar solo cerca de la madurez esperada.

Al recopilar datos de temperatura usando un dispositivo IoT, un agricultor puede ser notificado automáticamente cuando las plantas están cerca de la madurez. Una arquitectura típica para esto es que los dispositivos IoT midan la temperatura y luego publiquen estos datos de telemetría a través de Internet usando algo como MQTT. El código del servidor escucha estos datos y los guarda en algún lugar, como en una base de datos. Esto significa que los datos pueden analizarse más tarde, como un trabajo nocturno para calcular los GDD del día, sumar los GDD totales para cada cultivo hasta ahora y alertar si una planta está cerca de la madurez.

![Los datos de telemetría se envían a un servidor y luego se guardan en una base de datos](../../../../../translated_images/save-telemetry-database.ddc9c6bea0c5ba39.es.png)

El código del servidor también puede complementar los datos agregando información adicional. Por ejemplo, el dispositivo IoT puede publicar un identificador para indicar qué dispositivo es, y el código del servidor puede usar esto para buscar la ubicación del dispositivo y qué cultivos está monitoreando. También puede agregar datos básicos como la hora actual, ya que algunos dispositivos IoT no tienen el hardware necesario para llevar un registro preciso del tiempo o requieren código adicional para leer la hora actual a través de Internet.

✅ ¿Por qué crees que diferentes campos pueden tener diferentes temperaturas?

### Tarea - publicar información de temperatura

Sigue la guía correspondiente para publicar datos de temperatura a través de MQTT usando tu dispositivo IoT para que puedan analizarse más tarde:

* [Arduino - Wio Terminal](wio-terminal-temp-publish.md)
* [Computadora de placa única - Raspberry Pi/Dispositivo IoT virtual](single-board-computer-temp-publish.md)

### Tarea - capturar y almacenar la información de temperatura

Una vez que el dispositivo IoT esté publicando telemetría, se puede escribir el código del servidor para suscribirse a estos datos y almacenarlos. En lugar de guardarlos en una base de datos, el código del servidor los guardará en un archivo de valores separados por comas (CSV). Los archivos CSV almacenan datos como filas de valores en texto, con cada valor separado por una coma y cada registro en una nueva línea. Son una forma conveniente, legible y ampliamente compatible de guardar datos como archivo.

El archivo CSV tendrá dos columnas: *fecha* y *temperatura*. La columna *fecha* se establece como la fecha y hora actuales en que el mensaje fue recibido por el servidor, y la *temperatura* proviene del mensaje de telemetría.

1. Repite los pasos de la lección 4 para crear el código del servidor que se suscriba a la telemetría. No necesitas agregar código para publicar comandos.

    Los pasos para esto son:

    * Configurar y activar un entorno virtual de Python

    * Instalar el paquete pip paho-mqtt

    * Escribir el código para escuchar mensajes MQTT publicados en el tema de telemetría

      > ⚠️ Puedes consultar [las instrucciones en la lección 4 para crear una aplicación Python que reciba telemetría si es necesario](../../../1-getting-started/lessons/4-connect-internet/README.md#receive-telemetry-from-the-mqtt-broker).

    Nombra la carpeta para este proyecto `temperature-sensor-server`.

1. Asegúrate de que el `client_name` refleje este proyecto:

    ```cpp
    client_name = id + 'temperature_sensor_server'
    ```

1. Agrega las siguientes importaciones al inicio del archivo, debajo de las importaciones existentes:

    ```python
    from os import path
    import csv
    from datetime import datetime
    ```

    Esto importa una biblioteca para leer archivos, una biblioteca para interactuar con archivos CSV y una biblioteca para trabajar con fechas y horas.

1. Agrega el siguiente código antes de la función `handle_telemetry`:

    ```python
    temperature_file_name = 'temperature.csv'
    fieldnames = ['date', 'temperature']
    
    if not path.exists(temperature_file_name):
        with open(temperature_file_name, mode='w') as csv_file:
            writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
            writer.writeheader()
    ```

    Este código declara algunas constantes para el nombre del archivo donde se escribirá y los nombres de las columnas del archivo CSV. La primera fila de un archivo CSV tradicionalmente contiene encabezados de columna separados por comas.

    Luego, el código verifica si el archivo CSV ya existe. Si no existe, se crea con los encabezados de columna en la primera fila.

1. Agrega el siguiente código al final de la función `handle_telemetry`:

    ```python
    with open(temperature_file_name, mode='a') as temperature_file:        
        temperature_writer = csv.DictWriter(temperature_file, fieldnames=fieldnames)
        temperature_writer.writerow({'date' : datetime.now().astimezone().replace(microsecond=0).isoformat(), 'temperature' : payload['temperature']})
    ```
Este código abre el archivo CSV y luego agrega una nueva fila al final. La fila contiene la fecha y hora actual formateadas en un formato legible para humanos, seguido de la temperatura recibida del dispositivo IoT. Los datos se almacenan en [formato ISO 8601](https://wikipedia.org/wiki/ISO_8601) con la zona horaria, pero sin microsegundos.

1. Ejecuta este código de la misma manera que antes, asegurándote de que tu dispositivo IoT esté enviando datos. Se creará un archivo CSV llamado `temperature.csv` en la misma carpeta. Si lo abres, verás fechas/horas y mediciones de temperatura:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Ejecuta este código durante un tiempo para capturar datos. Idealmente, deberías ejecutarlo durante todo un día para recopilar suficientes datos para los cálculos de GDD.

    
> 💁 Si estás utilizando un dispositivo IoT virtual, selecciona la casilla de aleatoriedad y establece un rango para evitar obtener la misma temperatura cada vez que se devuelva el valor de temperatura.
    ![Selecciona la casilla de aleatoriedad y establece un rango](../../../../../translated_images/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.es.png) 

    > 💁 Si deseas ejecutarlo durante todo un día, debes asegurarte de que la computadora donde se ejecuta tu código de servidor no entre en modo de suspensión, ya sea cambiando la configuración de energía o ejecutando algo como [este script de Python para mantener el sistema activo](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Puedes encontrar este código en la carpeta [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Tarea - calcular GDD usando los datos almacenados

Una vez que el servidor haya capturado los datos de temperatura, se puede calcular el GDD para una planta.

Los pasos para hacerlo manualmente son:

1. Encuentra la temperatura base para la planta. Por ejemplo, para las fresas la temperatura base es de 10°C.

1. En el archivo `temperature.csv`, encuentra las temperaturas más altas y más bajas del día.

1. Usa el cálculo de GDD dado anteriormente para calcular el GDD.

Por ejemplo, si la temperatura más alta del día es 25°C y la más baja es 12°C:

![GDD = 25 + 12 dividido por 2, luego resta 10 del resultado dando 8.5](../../../../../translated_images/gdd-calculation-strawberries.59f57db94b22adb8ff6efb951ace33af104a1c6ccca3ffb0f8169c14cb160c90.es.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Por lo tanto, las fresas han recibido **8.5** GDD. Las fresas necesitan alrededor de 250 GDD para dar fruto, así que aún falta un tiempo.

---

## 🚀 Desafío

Las plantas necesitan más que calor para crecer. ¿Qué otras cosas son necesarias?

Para estas, investiga si hay sensores que puedan medirlas. ¿Qué hay de los actuadores para controlar estos niveles? ¿Cómo podrías ensamblar uno o más dispositivos IoT para optimizar el crecimiento de las plantas?

## Cuestionario posterior a la clase

[Cuestionario posterior a la clase](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Revisión y autoestudio

* Lee más sobre agricultura digital en la [página de Wikipedia sobre Agricultura Digital](https://wikipedia.org/wiki/Digital_agriculture). También lee más sobre agricultura de precisión en la [página de Wikipedia sobre Agricultura de Precisión](https://wikipedia.org/wiki/Precision_agriculture).
* El cálculo completo de los grados día de crecimiento es más complicado que el simplificado dado aquí. Lee más sobre la ecuación más compleja y cómo manejar temperaturas por debajo del umbral en la [página de Wikipedia sobre Grados Día de Crecimiento](https://wikipedia.org/wiki/Growing_degree-day).
* Los alimentos podrían escasear en el futuro si seguimos utilizando los mismos métodos de cultivo. Aprende más sobre técnicas de agricultura de alta tecnología en este [video sobre Granjas de Alta Tecnología del Futuro en YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Asignación

[Visualiza los datos de GDD usando un Jupyter Notebook](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de ningún malentendido o interpretación errónea que surja del uso de esta traducción.