# Construir una luz nocturna - Raspberry Pi

En esta parte de la lección, agregarás un sensor de luz a tu Raspberry Pi.

## Hardware

El sensor para esta lección es un **sensor de luz** que utiliza un [fotodiodo](https://wikipedia.org/wiki/Photodiode) para convertir la luz en una señal eléctrica. Este es un sensor analógico que envía un valor entero de 0 a 1,000 indicando una cantidad relativa de luz que no se corresponde con ninguna unidad estándar de medida como el [lux](https://wikipedia.org/wiki/Lux).

El sensor de luz es un sensor Grove externo y necesita estar conectado al Grove Base hat en la Raspberry Pi.

### Conectar el sensor de luz

El sensor de luz Grove que se utiliza para detectar los niveles de luz debe estar conectado a la Raspberry Pi.

#### Tarea - conectar el sensor de luz

Conecta el sensor de luz.

![Un sensor de luz Grove](../../../../../translated_images/es/grove-light-sensor.b8127b7c434e632d.webp)

1. Inserta un extremo de un cable Grove en el conector del módulo del sensor de luz. Solo encajará de una manera.

1. Con la Raspberry Pi apagada, conecta el otro extremo del cable Grove al conector analógico marcado como **A0** en el Grove Base hat conectado a la Pi. Este conector es el segundo desde la derecha, en la fila de conectores junto a los pines GPIO.

![El sensor de luz Grove conectado al conector A0](../../../../../translated_images/es/pi-light-sensor.66cc1e31fa48cd7d.webp)

## Programar el sensor de luz

El dispositivo ahora puede ser programado utilizando el sensor de luz Grove.

### Tarea - programar el sensor de luz

Programa el dispositivo.

1. Enciende la Pi y espera a que arranque.

1. Abre el proyecto de luz nocturna en VS Code que creaste en la parte anterior de esta tarea, ya sea ejecutándolo directamente en la Pi o conectado mediante la extensión Remote SSH.

1. Abre el archivo `app.py` y elimina todo el código que contiene.

1. Agrega el siguiente código al archivo `app.py` para importar algunas bibliotecas necesarias:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    La declaración `import time` importa el módulo `time`, que se utilizará más adelante en esta tarea.

    La declaración `from grove.grove_light_sensor_v1_2 import GroveLightSensor` importa el `GroveLightSensor` de las bibliotecas de Python Grove. Esta biblioteca contiene el código para interactuar con un sensor de luz Grove y se instaló globalmente durante la configuración de la Pi.

1. Agrega el siguiente código después del código anterior para crear una instancia de la clase que gestiona el sensor de luz:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    La línea `light_sensor = GroveLightSensor(0)` crea una instancia de la clase `GroveLightSensor` conectándose al pin **A0**, el pin analógico Grove al que está conectado el sensor de luz.

1. Agrega un bucle infinito después del código anterior para consultar el valor del sensor de luz y mostrarlo en la consola:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Esto leerá el nivel de luz actual en una escala de 0-1,023 utilizando la propiedad `light` de la clase `GroveLightSensor`. Esta propiedad lee el valor analógico del pin. Este valor se imprimirá en la consola.

1. Agrega una pequeña pausa de un segundo al final del `loop`, ya que no es necesario verificar los niveles de luz continuamente. Una pausa reduce el consumo de energía del dispositivo.

    ```python
    time.sleep(1)
    ```

1. Desde el Terminal de VS Code, ejecuta lo siguiente para ejecutar tu aplicación de Python:

    ```sh
    python3 app.py
    ```

    Los valores de luz se mostrarán en la consola. Cubre y descubre el sensor de luz, y los valores cambiarán:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Puedes encontrar este código en la carpeta [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 ¡Agregar un sensor a tu programa de luz nocturna fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.