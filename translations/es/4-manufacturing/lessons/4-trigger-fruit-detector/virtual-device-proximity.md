# Detectar proximidad - Hardware IoT Virtual

En esta parte de la lección, agregarás un sensor de proximidad a tu dispositivo IoT virtual y leerás la distancia desde él.

## Hardware

El dispositivo IoT virtual utilizará un sensor de distancia simulado.

En un dispositivo IoT físico, usarías un sensor con un módulo de medición láser para detectar la distancia.

### Agregar el sensor de distancia a CounterFit

Para usar un sensor de distancia virtual, necesitas agregar uno a la aplicación CounterFit.

#### Tarea - agregar el sensor de distancia a CounterFit

Agrega el sensor de distancia a la aplicación CounterFit.

1. Abre el código `fruit-quality-detector` en VS Code y asegúrate de que el entorno virtual esté activado.

1. Instala un paquete adicional de Pip para agregar un shim de CounterFit que pueda comunicarse con sensores de distancia simulando el paquete [rpi-vl53l0x Pip](https://pypi.org/project/rpi-vl53l0x/), un paquete de Python que interactúa con [un sensor de distancia VL53L0X de tiempo de vuelo](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Asegúrate de instalar esto desde una terminal con el entorno virtual activado.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Asegúrate de que la aplicación web de CounterFit esté en ejecución.

1. Crea un sensor de distancia:

    1. En el cuadro *Create sensor* en el panel *Sensors*, despliega el cuadro *Sensor type* y selecciona *Distance*.

    1. Deja las *Units* como `Millimeter`.

    1. Este sensor es un sensor I²C, así que configura la dirección en `0x29`. Si usaras un sensor físico VL53L0X, estaría codificado en esta dirección.

    1. Selecciona el botón **Add** para crear el sensor de distancia.

    ![Configuración del sensor de distancia](../../../../../translated_images/es/counterfit-create-distance-sensor.967c9fb98f27888d.webp)

    El sensor de distancia se creará y aparecerá en la lista de sensores.

    ![Sensor de distancia creado](../../../../../translated_images/es/counterfit-distance-sensor.079eefeeea0b68af.webp)

## Programar el sensor de distancia

El dispositivo IoT virtual ahora puede ser programado para usar el sensor de distancia simulado.

### Tarea - programar el sensor de tiempo de vuelo

1. Crea un nuevo archivo en el proyecto `fruit-quality-detector` llamado `distance-sensor.py`.

    > 💁 Una forma sencilla de simular múltiples dispositivos IoT es hacerlo en diferentes archivos de Python y ejecutarlos al mismo tiempo.

1. Inicia una conexión con CounterFit con el siguiente código:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Agrega el siguiente código debajo de esto:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Esto importa la biblioteca shim del sensor para el sensor de tiempo de vuelo VL53L0X.

1. Debajo de esto, agrega el siguiente código para acceder al sensor:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Este código declara un sensor de distancia y luego inicia el sensor.

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

1. Verás mediciones de distancia aparecer en la consola. Cambia el valor en CounterFit para ver cómo cambia este valor, o usa valores aleatorios.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Puedes encontrar este código en la carpeta [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 ¡Tu programa del sensor de proximidad fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.