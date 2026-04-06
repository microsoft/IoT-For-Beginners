# Detectar proximidad - Wio Terminal

En esta parte de la lección, agregarás un sensor de proximidad a tu Wio Terminal y leerás la distancia desde él.

## Hardware

El Wio Terminal necesita un sensor de proximidad.

El sensor que usarás es un [sensor de distancia Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Este sensor utiliza un módulo de medición láser para detectar la distancia. Tiene un rango de 10mm a 2000mm (1cm - 2m) y reportará valores en ese rango con bastante precisión, aunque las distancias superiores a 1000mm se reportarán como 8109mm.

El telémetro láser está en la parte trasera del sensor, en el lado opuesto al conector Grove.

Este es un socket combinado digital e I²C.

### Conectar el sensor de tiempo de vuelo

El sensor Grove Time of Flight puede conectarse al Wio Terminal.

#### Tarea - conectar el sensor de tiempo de vuelo

Conecta el sensor de tiempo de vuelo.

![Un sensor Grove Time of Flight](../../../../../translated_images/es/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Inserta un extremo del cable Grove en el conector del sensor de tiempo de vuelo. Solo encajará de una manera.

1. Con el Wio Terminal desconectado de tu computadora u otra fuente de alimentación, conecta el otro extremo del cable Grove al conector Grove del lado izquierdo del Wio Terminal, mirando la pantalla. Este es el conector más cercano al botón de encendido. Este es un socket combinado digital e I²C.

![El sensor Grove Time of Flight conectado al conector izquierdo](../../../../../translated_images/es/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Ahora puedes conectar el Wio Terminal a tu computadora.

## Programar el sensor de tiempo de vuelo

El Wio Terminal ahora puede ser programado para usar el sensor de tiempo de vuelo conectado.

### Tarea - programar el sensor de tiempo de vuelo

1. Crea un nuevo proyecto para el Wio Terminal usando PlatformIO. Llama a este proyecto `distance-sensor`. Agrega código en la función `setup` para configurar el puerto serial.

1. Agrega una dependencia de biblioteca para la biblioteca del sensor de distancia Grove Time of Flight al archivo `platformio.ini` del proyecto:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. En `main.cpp`, agrega lo siguiente debajo de las directivas de inclusión existentes para declarar una instancia de la clase `Seeed_vl53l0x` para interactuar con el sensor de tiempo de vuelo:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Agrega lo siguiente al final de la función `setup` para inicializar el sensor:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. En la función `loop`, lee un valor del sensor:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Este código inicializa una estructura de datos para leer datos, luego la pasa al método `PerformSingleRangingMeasurement`, donde se llenará con la medición de distancia.

1. Debajo de esto, escribe la medición de distancia y luego espera 1 segundo:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Compila, sube y ejecuta este código. Podrás ver las mediciones de distancia en el monitor serial. Coloca objetos cerca del sensor y verás la medición de distancia:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    El telémetro está en la parte trasera del sensor, así que asegúrate de usar el lado correcto al medir la distancia.

    ![El telémetro en la parte trasera del sensor de tiempo de vuelo apuntando a un plátano](../../../../../translated_images/es/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Puedes encontrar este código en la carpeta [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 ¡Tu programa del sensor de proximidad fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.