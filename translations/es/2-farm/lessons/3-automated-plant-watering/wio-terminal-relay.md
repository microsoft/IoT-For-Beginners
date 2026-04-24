# Controlar un relé - Wio Terminal

En esta parte de la lección, agregarás un relé a tu Wio Terminal además del sensor de humedad del suelo, y lo controlarás en función del nivel de humedad del suelo.

## Hardware

El Wio Terminal necesita un relé.

El relé que usarás es un [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), un relé normalmente abierto (lo que significa que el circuito de salida está abierto o desconectado cuando no se envía señal al relé) que puede manejar circuitos de salida de hasta 250V y 10A.

Este es un actuador digital, por lo que se conecta a los pines digitales del Wio Terminal. El puerto combinado analógico/digital ya está en uso con el sensor de humedad del suelo, así que este se conecta al otro puerto, que es un puerto combinado I2C y digital.

### Conectar el relé

El relé Grove puede conectarse al puerto digital del Wio Terminal.

#### Tarea

Conecta el relé.

![Un relé Grove](../../../../../translated_images/es/grove-relay.d426958ca210fbd0.webp)

1. Inserta un extremo de un cable Grove en el conector del relé. Solo encajará de una manera.

1. Con el Wio Terminal desconectado de tu computadora u otra fuente de alimentación, conecta el otro extremo del cable Grove al conector Grove del lado izquierdo del Wio Terminal, mirando la pantalla. Deja el sensor de humedad del suelo conectado al conector del lado derecho.

![El relé Grove conectado al conector izquierdo, y el sensor de humedad del suelo conectado al conector derecho](../../../../../translated_images/es/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.webp)

1. Inserta el sensor de humedad del suelo en la tierra, si no lo has hecho ya en la lección anterior.

## Programar el relé

El Wio Terminal ahora puede ser programado para usar el relé conectado.

### Tarea

Programa el dispositivo.

1. Abre el proyecto `soil-moisture-sensor` de la lección anterior en VS Code si no está ya abierto. Vas a agregar código a este proyecto.

2. No hay una biblioteca para este actuador: es un actuador digital controlado por una señal alta o baja. Para encenderlo, envías una señal alta al pin (3.3V), y para apagarlo envías una señal baja (0V). Puedes hacerlo usando la función [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/) incorporada en Arduino. Comienza agregando lo siguiente al final de la función `setup` para configurar el puerto combinado I2C/digital como un pin de salida para enviar voltaje al relé:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` es el número de puerto para el puerto combinado I2C/digital.

1. Para probar que el relé funciona, agrega lo siguiente a la función `loop`, debajo del último `delay`:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    El código envía una señal alta al pin al que está conectado el relé para encenderlo, espera 500ms (medio segundo), y luego envía una señal baja para apagar el relé.

1. Compila y sube el código al Wio Terminal.

1. Una vez subido, el relé se encenderá y apagará cada 10 segundos, con un retraso de medio segundo entre encenderse y apagarse. Escucharás el clic del relé al encenderse y apagarse. Un LED en la placa Grove se iluminará cuando el relé esté encendido y se apagará cuando el relé esté apagado.

    ![El relé encendiéndose y apagándose](../../../../../images/relay-turn-on-off.gif)

## Controlar el relé según la humedad del suelo

Ahora que el relé funciona, puede ser controlado en respuesta a las lecturas de humedad del suelo.

### Tarea

Controla el relé.

1. Elimina las 3 líneas de código que agregaste para probar el relé. Reemplázalas con el siguiente código:

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    Este código verifica el nivel de humedad del suelo desde el sensor de humedad del suelo. Si está por encima de 450, enciende el relé, y lo apaga cuando baja de 450.

    > 💁 Recuerda que el sensor capacitivo de humedad del suelo lee que cuanto más bajo es el nivel de humedad del suelo, más humedad hay en la tierra, y viceversa.

1. Compila y sube el código al Wio Terminal.

1. Monitorea el dispositivo a través del monitor serial. Verás que el relé se enciende o apaga dependiendo del nivel de humedad del suelo. Prueba en tierra seca y luego agrega agua.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Puedes encontrar este código en la carpeta [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal).

😀 ¡Tu programa para controlar un relé con el sensor de humedad del suelo fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.