# Medir la temperatura - Hardware IoT Virtual

En esta parte de la lección, agregarás un sensor de temperatura a tu dispositivo IoT virtual.

## Hardware Virtual

El dispositivo IoT virtual usará un sensor simulado de Humedad y Temperatura Digital Grove. Esto mantiene este laboratorio igual que usar un Raspberry Pi con un sensor físico Grove DHT11.

El sensor combina un **sensor de temperatura** con un **sensor de humedad**, pero en este laboratorio solo te interesará el componente del sensor de temperatura. En un dispositivo IoT físico, el sensor de temperatura sería un [termistor](https://wikipedia.org/wiki/Thermistor) que mide la temperatura detectando un cambio en la resistencia a medida que cambia la temperatura. Los sensores de temperatura suelen ser sensores digitales que convierten internamente la resistencia medida en una temperatura en grados Celsius (o Kelvin, o Fahrenheit).

### Agregar los sensores a CounterFit

Para usar un sensor virtual de humedad y temperatura, necesitas agregar los dos sensores a la aplicación CounterFit.

#### Tarea - agregar los sensores a CounterFit

Agrega los sensores de humedad y temperatura a la aplicación CounterFit.

1. Crea una nueva aplicación de Python en tu computadora en una carpeta llamada `temperature-sensor` con un único archivo llamado `app.py`, un entorno virtual de Python, y agrega los paquetes pip de CounterFit.

    > ⚠️ Puedes consultar [las instrucciones para crear y configurar un proyecto de Python de CounterFit en la lección 1 si es necesario](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Instala un paquete adicional de Pip para instalar un shim de CounterFit para el sensor DHT11. Asegúrate de instalarlo desde una terminal con el entorno virtual activado.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Asegúrate de que la aplicación web de CounterFit esté en ejecución.

1. Crea un sensor de humedad:

    1. En el cuadro *Create sensor* en el panel *Sensors*, despliega el cuadro *Sensor type* y selecciona *Humidity*.

    1. Deja las *Units* configuradas en *Percentage*.

    1. Asegúrate de que el *Pin* esté configurado en *5*.

    1. Selecciona el botón **Add** para crear el sensor de humedad en el Pin 5.

    ![Configuración del sensor de humedad](../../../../../translated_images/es/counterfit-create-humidity-sensor.2750e27b6f30e09c.webp)

    El sensor de humedad será creado y aparecerá en la lista de sensores.

    ![Sensor de humedad creado](../../../../../translated_images/es/counterfit-humidity-sensor.7b12f7f339e430cb.webp)

1. Crea un sensor de temperatura:

    1. En el cuadro *Create sensor* en el panel *Sensors*, despliega el cuadro *Sensor type* y selecciona *Temperature*.

    1. Deja las *Units* configuradas en *Celsius*.

    1. Asegúrate de que el *Pin* esté configurado en *6*.

    1. Selecciona el botón **Add** para crear el sensor de temperatura en el Pin 6.

    ![Configuración del sensor de temperatura](../../../../../translated_images/es/counterfit-create-temperature-sensor.199350ed34f7343d.webp)

    El sensor de temperatura será creado y aparecerá en la lista de sensores.

    ![Sensor de temperatura creado](../../../../../translated_images/es/counterfit-temperature-sensor.f0560236c96a9016.webp)

## Programar la aplicación del sensor de temperatura

Ahora se puede programar la aplicación del sensor de temperatura utilizando los sensores de CounterFit.

### Tarea - programar la aplicación del sensor de temperatura

Programa la aplicación del sensor de temperatura.

1. Asegúrate de que la aplicación `temperature-sensor` esté abierta en VS Code.

1. Abre el archivo `app.py`.

1. Agrega el siguiente código al inicio de `app.py` para conectar la aplicación a CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Agrega el siguiente código al archivo `app.py` para importar las bibliotecas necesarias:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    La declaración `from seeed_dht import DHT` importa la clase `DHT` para interactuar con un sensor virtual de temperatura Grove utilizando un shim del módulo `counterfit_shims_seeed_python_dht`.

1. Agrega el siguiente código después del anterior para crear una instancia de la clase que gestiona el sensor virtual de humedad y temperatura:

    ```python
    sensor = DHT("11", 5)
    ```

    Esto declara una instancia de la clase `DHT` que gestiona el sensor virtual de **H**umedad y **T**emperatura **D**igital. El primer parámetro indica que el sensor utilizado es un sensor virtual *DHT11*. El segundo parámetro indica que el sensor está conectado al puerto `5`.

    > 💁 CounterFit simula este sensor combinado de humedad y temperatura conectándose a 2 sensores: un sensor de humedad en el pin indicado al crear la clase `DHT`, y un sensor de temperatura que funciona en el pin siguiente. Si el sensor de humedad está en el pin 5, el shim espera que el sensor de temperatura esté en el pin 6.

1. Agrega un bucle infinito después del código anterior para consultar el valor del sensor de temperatura e imprimirlo en la consola:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    La llamada a `sensor.read()` devuelve una tupla de humedad y temperatura. Solo necesitas el valor de la temperatura, por lo que se ignora la humedad. El valor de la temperatura se imprime en la consola.

1. Agrega una pequeña pausa de diez segundos al final del `loop`, ya que no es necesario verificar continuamente los niveles de temperatura. Una pausa reduce el consumo de energía del dispositivo.

    ```python
    time.sleep(10)
    ```

1. Desde la Terminal de VS Code con un entorno virtual activado, ejecuta lo siguiente para ejecutar tu aplicación de Python:

    ```sh
    python app.py
    ```

1. Desde la aplicación CounterFit, cambia el valor del sensor de temperatura que será leído por la aplicación. Puedes hacerlo de dos maneras:

    * Ingresa un número en el cuadro *Value* del sensor de temperatura y selecciona el botón **Set**. El número que ingreses será el valor devuelto por el sensor.

    * Marca la casilla *Random* e ingresa un valor *Min* y *Max*, luego selecciona el botón **Set**. Cada vez que el sensor lea un valor, leerá un número aleatorio entre *Min* y *Max*.

    Deberías ver los valores que configures apareciendo en la consola. Cambia el *Value* o la configuración de *Random* para ver cómo cambia el valor.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Puedes encontrar este código en la carpeta [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device).

😀 ¡Tu programa del sensor de temperatura fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.