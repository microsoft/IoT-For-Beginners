# Controlar un relé - Raspberry Pi

En esta parte de la lección, agregarás un relé a tu Raspberry Pi además del sensor de humedad del suelo, y lo controlarás en función del nivel de humedad del suelo.

## Hardware

La Raspberry Pi necesita un relé.

El relé que usarás es un [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), un relé normalmente abierto (lo que significa que el circuito de salida está abierto o desconectado cuando no se envía señal al relé) que puede manejar circuitos de salida de hasta 250V y 10A.

Este es un actuador digital, por lo que se conecta a un pin digital en el Grove Base Hat.

### Conectar el relé

El relé Grove puede conectarse a la Raspberry Pi.

#### Tarea

Conecta el relé.

![Un relé Grove](../../../../../translated_images/es/grove-relay.d426958ca210fbd0.webp)

1. Inserta un extremo de un cable Grove en el conector del relé. Solo encajará de una manera.

1. Con la Raspberry Pi apagada, conecta el otro extremo del cable Grove al conector digital marcado como **D5** en el Grove Base Hat conectado a la Pi. Este conector es el segundo desde la izquierda, en la fila de conectores junto a los pines GPIO. Deja el sensor de humedad del suelo conectado al conector **A0**.

![El relé Grove conectado al conector D5, y el sensor de humedad del suelo conectado al conector A0](../../../../../translated_images/es/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e.webp)

1. Inserta el sensor de humedad del suelo en la tierra, si no lo has hecho ya en la lección anterior.

## Programar el relé

La Raspberry Pi ahora puede ser programada para usar el relé conectado.

### Tarea

Programa el dispositivo.

1. Enciende la Pi y espera a que arranque.

1. Abre el proyecto `soil-moisture-sensor` de la lección anterior en VS Code si no está ya abierto. Estarás agregando a este proyecto.

1. Añade el siguiente código al archivo `app.py` debajo de las importaciones existentes:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Esta declaración importa el `GroveRelay` de las bibliotecas de Python Grove para interactuar con el relé Grove.

1. Añade el siguiente código debajo de la declaración de la clase `ADC` para crear una instancia de `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Esto crea un relé usando el pin **D5**, el pin digital al que conectaste el relé.

1. Para probar que el relé funciona, añade lo siguiente al bucle `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    El código enciende el relé, espera 0.5 segundos, luego apaga el relé.

1. Ejecuta la aplicación de Python. El relé se encenderá y apagará cada 10 segundos, con un retraso de medio segundo entre encender y apagar. Escucharás el clic del relé al encenderse y apagarse. Un LED en la placa Grove se encenderá cuando el relé esté encendido y se apagará cuando el relé esté apagado.

    ![El relé encendiéndose y apagándose](../../../../../images/relay-turn-on-off.gif)

## Controlar el relé según la humedad del suelo

Ahora que el relé funciona, puede ser controlado en respuesta a las lecturas de humedad del suelo.

### Tarea

Controla el relé.

1. Elimina las 3 líneas de código que agregaste para probar el relé. Reemplázalas con el siguiente código:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Este código verifica el nivel de humedad del suelo desde el sensor de humedad del suelo. Si está por encima de 450, enciende el relé, y lo apaga cuando baja de 450.

    > 💁 Recuerda que el sensor capacitivo de humedad del suelo lee que cuanto más bajo es el nivel de humedad del suelo, más humedad hay en la tierra y viceversa.

1. Ejecuta la aplicación de Python. Verás que el relé se enciende o apaga dependiendo del nivel de humedad del suelo. Prueba en tierra seca, luego añade agua.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Puedes encontrar este código en la carpeta [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 ¡Tu programa para controlar un relé con el sensor de humedad del suelo fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.