# Construir una luz nocturna - Hardware IoT Virtual

En esta parte de la lección, agregarás un sensor de luz a tu dispositivo IoT virtual.

## Hardware Virtual

La luz nocturna necesita un sensor, creado en la aplicación CounterFit.

El sensor es un **sensor de luz**. En un dispositivo IoT físico, sería un [fotodiodo](https://wikipedia.org/wiki/Photodiode) que convierte la luz en una señal eléctrica. Los sensores de luz son sensores analógicos que envían un valor entero indicando una cantidad relativa de luz, que no se corresponde con ninguna unidad estándar de medida como el [lux](https://wikipedia.org/wiki/Lux).

### Agregar los sensores a CounterFit

Para usar un sensor de luz virtual, necesitas agregarlo a la aplicación CounterFit.

#### Tarea - agregar los sensores a CounterFit

Agrega el sensor de luz a la aplicación CounterFit.

1. Asegúrate de que la aplicación web CounterFit esté ejecutándose desde la parte anterior de esta tarea. Si no, iníciala.

1. Crea un sensor de luz:

    1. En el cuadro *Create sensor* en el panel *Sensors*, despliega el cuadro *Sensor type* y selecciona *Light*.

    1. Deja las *Units* configuradas como *NoUnits*.

    1. Asegúrate de que el *Pin* esté configurado como *0*.

    1. Selecciona el botón **Add** para crear el sensor de luz en el Pin 0.

    ![Configuración del sensor de luz](../../../../../translated_images/es/counterfit-create-light-sensor.9f36a5e0d4458d8d.webp)

    El sensor de luz será creado y aparecerá en la lista de sensores.

    ![Sensor de luz creado](../../../../../translated_images/es/counterfit-light-sensor.5d0f5584df56b90f.webp)

## Programar el sensor de luz

El dispositivo ahora puede ser programado para usar el sensor de luz integrado.

### Tarea - programar el sensor de luz

Programa el dispositivo.

1. Abre el proyecto de luz nocturna en VS Code que creaste en la parte anterior de esta tarea. Mata y vuelve a crear el terminal para asegurarte de que se esté ejecutando usando el entorno virtual si es necesario.

1. Abre el archivo `app.py`.

1. Agrega el siguiente código en la parte superior del archivo `app.py` junto con el resto de las declaraciones `import` para importar algunas bibliotecas necesarias:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    La declaración `import time` importa el módulo `time` de Python que se usará más adelante en esta tarea.

    La declaración `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` importa el `GroveLightSensor` de las bibliotecas Python de CounterFit Grove shim. Esta biblioteca tiene código para interactuar con un sensor de luz creado en la aplicación CounterFit.

1. Agrega el siguiente código al final del archivo para crear instancias de clases que gestionan el sensor de luz:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    La línea `light_sensor = GroveLightSensor(0)` crea una instancia de la clase `GroveLightSensor` conectándose al pin **0** - el pin de CounterFit Grove al que está conectado el sensor de luz.

1. Agrega un bucle infinito después del código anterior para consultar el valor del sensor de luz y mostrarlo en la consola:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Esto leerá el nivel de luz actual usando la propiedad `light` de la clase `GroveLightSensor`. Esta propiedad lee el valor analógico del pin. Este valor luego se imprime en la consola.

1. Agrega una pequeña pausa de un segundo al final del bucle `while`, ya que no es necesario verificar los niveles de luz continuamente. Una pausa reduce el consumo de energía del dispositivo.

    ```python
    time.sleep(1)
    ```

1. Desde el terminal de VS Code, ejecuta lo siguiente para ejecutar tu aplicación de Python:

    ```sh
    python3 app.py
    ```

    Los valores de luz se mostrarán en la consola. Inicialmente este valor será 0.

1. Desde la aplicación CounterFit, cambia el valor del sensor de luz que será leído por la aplicación. Puedes hacerlo de dos maneras:

    * Ingresa un número en el cuadro *Value* del sensor de luz y luego selecciona el botón **Set**. El número que ingreses será el valor devuelto por el sensor.

    * Marca la casilla *Random* y escribe un valor *Min* y *Max*, luego selecciona el botón **Set**. Cada vez que el sensor lea un valor, leerá un número aleatorio entre *Min* y *Max*.

    Los valores que configures se mostrarán en la consola. Cambia el *Value* o la configuración *Random* para que el valor cambie.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Puedes encontrar este código en la carpeta [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 ¡Tu programa de luz nocturna fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.