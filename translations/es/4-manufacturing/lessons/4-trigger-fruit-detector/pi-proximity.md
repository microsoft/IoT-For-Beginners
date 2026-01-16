<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-26T14:23:48+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "es"
}
-->
# Detectar proximidad - Raspberry Pi

En esta parte de la lección, agregarás un sensor de proximidad a tu Raspberry Pi y leerás la distancia desde él.

## Hardware

La Raspberry Pi necesita un sensor de proximidad.

El sensor que usarás es un [sensor de distancia Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Este sensor utiliza un módulo de medición láser para detectar la distancia. Tiene un rango de 10mm a 2000mm (1cm - 2m) y reporta valores en ese rango con bastante precisión, aunque las distancias superiores a 1000mm se reportan como 8109mm.

El telémetro láser está en la parte trasera del sensor, en el lado opuesto al conector Grove.

Este es un sensor I²C.

### Conectar el sensor Time of Flight

El sensor Grove Time of Flight puede conectarse a la Raspberry Pi.

#### Tarea - conectar el sensor Time of Flight

Conecta el sensor Time of Flight.

![Un sensor Grove Time of Flight](../../../../../translated_images/es/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Inserta un extremo de un cable Grove en el conector del sensor Time of Flight. Solo encajará de una manera.

1. Con la Raspberry Pi apagada, conecta el otro extremo del cable Grove a uno de los conectores I²C marcados como **I²C** en el Grove Base Hat conectado a la Pi. Estos conectores están en la fila inferior, en el extremo opuesto a los pines GPIO y junto a la ranura del cable de la cámara.

![El sensor Grove Time of Flight conectado al conector I²C](../../../../../translated_images/es/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Programar el sensor Time of Flight

Ahora se puede programar la Raspberry Pi para usar el sensor Time of Flight conectado.

### Tarea - programar el sensor Time of Flight

Programa el dispositivo.

1. Enciende la Raspberry Pi y espera a que inicie.

1. Abre el código `fruit-quality-detector` en VS Code, ya sea directamente en la Pi o conectándote mediante la extensión Remote SSH.

1. Instala el paquete Pip `rpi-vl53l0x`, un paquete de Python que interactúa con un sensor de distancia VL53L0X Time of Flight. Instálalo usando este comando pip:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Crea un nuevo archivo en este proyecto llamado `distance-sensor.py`.

    > 💁 Una forma sencilla de simular múltiples dispositivos IoT es hacerlo en diferentes archivos de Python y ejecutarlos al mismo tiempo.

1. Agrega el siguiente código a este archivo:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Esto importa la biblioteca Grove I²C bus y una biblioteca para el hardware principal del sensor incorporado en el sensor Grove Time of Flight.

1. A continuación, agrega el siguiente código para acceder al sensor:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Este código declara un sensor de distancia utilizando el bus Grove I²C y luego inicia el sensor.

1. Finalmente, agrega un bucle infinito para leer las distancias:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Este código espera a que un valor esté listo para ser leído desde el sensor y luego lo imprime en la consola.

1. Ejecuta este código.

    > 💁 ¡No olvides que este archivo se llama `distance-sensor.py`! Asegúrate de ejecutarlo con Python, no con `app.py`.

1. Verás las mediciones de distancia aparecer en la consola. Coloca objetos cerca del sensor y observarás la medición de distancia:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    El telémetro está en la parte trasera del sensor, así que asegúrate de usar el lado correcto al medir la distancia.

    ![El telémetro en la parte trasera del sensor Time of Flight apuntando a un plátano](../../../../../translated_images/es/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Puedes encontrar este código en la carpeta [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 ¡Tu programa del sensor de proximidad fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.