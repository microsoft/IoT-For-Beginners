# Controlar un relé - Hardware IoT Virtual

En esta parte de la lección, agregarás un relé a tu dispositivo IoT virtual además del sensor de humedad del suelo, y lo controlarás en función del nivel de humedad del suelo.

## Hardware Virtual

El dispositivo IoT virtual usará un relé simulado de Grove. Esto mantiene este laboratorio igual que usar un Raspberry Pi con un relé físico de Grove.

En un dispositivo IoT físico, el relé sería un relé normalmente abierto (lo que significa que el circuito de salida está abierto o desconectado cuando no se envía señal al relé). Un relé como este puede manejar circuitos de salida de hasta 250V y 10A.

### Agregar el relé a CounterFit

Para usar un relé virtual, necesitas agregarlo a la aplicación CounterFit.

#### Tarea

Agrega el relé a la aplicación CounterFit.

1. Abre el proyecto `soil-moisture-sensor` de la lección anterior en VS Code si no está ya abierto. Estarás agregando a este proyecto.

1. Asegúrate de que la aplicación web de CounterFit esté en ejecución.

1. Crea un relé:

    1. En el cuadro *Create actuator* en el panel *Actuators*, despliega el cuadro *Actuator type* y selecciona *Relay*.

    1. Configura el *Pin* en *5*.

    1. Selecciona el botón **Add** para crear el relé en el Pin 5.

    ![Configuración del relé](../../../../../translated_images/es/counterfit-create-relay.fa7c40fd0f2f6afc.webp)

    El relé será creado y aparecerá en la lista de actuadores.

    ![Relé creado](../../../../../translated_images/es/counterfit-relay.bbf74c1dbdc8b9ac.webp)

## Programar el relé

La aplicación del sensor de humedad del suelo ahora puede ser programada para usar el relé virtual.

### Tarea

Programa el dispositivo virtual.

1. Abre el proyecto `soil-moisture-sensor` de la lección anterior en VS Code si no está ya abierto. Estarás agregando a este proyecto.

1. Agrega el siguiente código al archivo `app.py` debajo de las importaciones existentes:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Esta declaración importa el `GroveRelay` de las bibliotecas shim de Grove para interactuar con el relé virtual de Grove.

1. Agrega el siguiente código debajo de la declaración de la clase `ADC` para crear una instancia de `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Esto crea un relé usando el pin **5**, el pin al que conectaste el relé.

1. Para probar que el relé funciona, agrega lo siguiente al bucle `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    El código enciende el relé, espera 0.5 segundos y luego lo apaga.

1. Ejecuta la aplicación de Python. El relé se encenderá y apagará cada 10 segundos, con un retraso de medio segundo entre encenderse y apagarse. Verás el relé virtual en la aplicación CounterFit cerrarse y abrirse a medida que el relé se enciende y apaga.

    ![El relé virtual encendiéndose y apagándose](../../../../../images/virtual-relay-turn-on-off.gif)

## Controlar el relé según la humedad del suelo

Ahora que el relé funciona, puede ser controlado en respuesta a las lecturas de humedad del suelo.

### Tarea

Controla el relé.

1. Elimina las 3 líneas de código que agregaste para probar el relé. Reemplázalas con el siguiente código en su lugar:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Este código verifica el nivel de humedad del suelo desde el sensor de humedad del suelo. Si está por encima de 450, enciende el relé, apagándolo si baja de 450.

    > 💁 Recuerda que el sensor capacitivo de humedad del suelo lee que cuanto más bajo es el nivel de humedad del suelo, más humedad hay en el suelo y viceversa.

1. Ejecuta la aplicación de Python. Verás que el relé se enciende o apaga dependiendo de los niveles de humedad del suelo. Cambia el *Value* o la configuración de *Random* del sensor de humedad del suelo para ver cómo cambia el valor.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Puedes encontrar este código en la carpeta [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 ¡Tu programa de sensor de humedad del suelo virtual controlando un relé fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.