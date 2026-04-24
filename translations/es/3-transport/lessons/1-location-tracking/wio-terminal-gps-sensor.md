# Leer datos GPS - Wio Terminal

En esta parte de la lección, agregarás un sensor GPS a tu Wio Terminal y leerás valores de él.

## Hardware

El Wio Terminal necesita un sensor GPS.

El sensor que usarás es un [sensor Grove GPS Air530](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Este sensor puede conectarse a múltiples sistemas GPS para obtener una ubicación rápida y precisa. El sensor está compuesto por 2 partes: la electrónica principal del sensor y una antena externa conectada por un cable delgado para captar las ondas de radio de los satélites.

Este es un sensor UART, por lo que envía datos GPS a través de UART.

### Conectar el sensor GPS

El sensor Grove GPS se puede conectar al Wio Terminal.

#### Tarea - conectar el sensor GPS

Conecta el sensor GPS.

![Un sensor Grove GPS](../../../../../translated_images/es/grove-gps-sensor.247943bf69b03f0d.webp)

1. Inserta un extremo de un cable Grove en el conector del sensor GPS. Solo encajará de una manera.

1. Con el Wio Terminal desconectado de tu computadora u otra fuente de alimentación, conecta el otro extremo del cable Grove al conector Grove del lado izquierdo del Wio Terminal, mirando la pantalla. Este es el conector más cercano al botón de encendido.

    ![El sensor Grove GPS conectado al conector izquierdo](../../../../../translated_images/es/wio-gps-sensor.19fd52b81ce58095.webp)

1. Coloca el sensor GPS de manera que la antena conectada tenga visibilidad al cielo, idealmente cerca de una ventana abierta o al aire libre. Es más fácil obtener una señal clara sin obstáculos frente a la antena.

1. Ahora puedes conectar el Wio Terminal a tu computadora.

1. El sensor GPS tiene 2 LEDs: un LED azul que parpadea cuando se transmiten datos y un LED verde que parpadea cada segundo al recibir datos de los satélites. Asegúrate de que el LED azul parpadee cuando enciendas el Wio Terminal. Después de unos minutos, el LED verde debería parpadear; si no, es posible que necesites reposicionar la antena.

## Programar el sensor GPS

Ahora se puede programar el Wio Terminal para usar el sensor GPS conectado.

### Tarea - programar el sensor GPS

Programa el dispositivo.

1. Crea un nuevo proyecto para el Wio Terminal usando PlatformIO. Llama a este proyecto `gps-sensor`. Agrega código en la función `setup` para configurar el puerto serial.

1. Agrega la siguiente directiva `include` en la parte superior del archivo `main.cpp`. Esto incluye un archivo de cabecera con funciones para configurar el puerto Grove izquierdo para UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Debajo de esto, agrega la siguiente línea de código para declarar una conexión de puerto serial al puerto UART:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Necesitas agregar algo de código para redirigir algunos manejadores de señales internas a este puerto serial. Agrega el siguiente código debajo de la declaración de `Serial3`:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. En la función `setup`, debajo de donde se configura el puerto `Serial`, configura el puerto serial UART con el siguiente código:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Debajo de este código en la función `setup`, agrega el siguiente código para conectar el pin Grove al puerto serial:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Agrega la siguiente función antes de la función `loop` para enviar los datos GPS al monitor serial:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. En la función `loop`, agrega el siguiente código para leer del puerto serial UART e imprimir la salida en el monitor serial:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Este código lee del puerto serial UART. La función `readStringUntil` lee hasta un carácter terminador, en este caso, una nueva línea. Esto leerá una oración completa en formato NMEA (las oraciones NMEA terminan con un carácter de nueva línea). Mientras se puedan leer datos del puerto serial UART, se leen y se envían al monitor serial a través de la función `printGPSData`. Una vez que no se puedan leer más datos, el `loop` se retrasa por 1 segundo (1,000 ms).

1. Compila y sube el código al Wio Terminal.

1. Una vez subido, puedes monitorear los datos GPS usando el monitor serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 Puedes encontrar este código en la carpeta [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 ¡Tu programa del sensor GPS fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.