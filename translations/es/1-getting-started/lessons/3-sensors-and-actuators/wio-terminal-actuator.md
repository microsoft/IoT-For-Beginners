# Construye una luz nocturna - Wio Terminal

En esta parte de la lección, agregarás un LED a tu Wio Terminal y lo usarás para crear una luz nocturna.

## Hardware

La luz nocturna ahora necesita un actuador.

El actuador es un **LED**, un [diodo emisor de luz](https://wikipedia.org/wiki/Light-emitting_diode) que emite luz cuando la corriente pasa a través de él. Este es un actuador digital que tiene dos estados: encendido y apagado. Enviar un valor de 1 enciende el LED, y un valor de 0 lo apaga. Este es un actuador externo Grove y necesita conectarse al Wio Terminal.

La lógica de la luz nocturna en pseudocódigo es:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Conecta el LED

El Grove LED viene como un módulo con una selección de LEDs, permitiéndote elegir el color.

#### Tarea - conecta el LED

Conecta el LED.

![Un Grove LED](../../../../../translated_images/es/grove-led.6c853be93f473cf2.webp)

1. Elige tu LED favorito e inserta las patas en los dos agujeros del módulo LED.

    Los LEDs son diodos emisores de luz, y los diodos son dispositivos electrónicos que solo pueden conducir corriente en una dirección. Esto significa que el LED debe conectarse en la orientación correcta, de lo contrario no funcionará.

    Una de las patas del LED es el pin positivo, la otra es el pin negativo. El LED no es perfectamente redondo y es ligeramente más plano en un lado. El lado más plano es el pin negativo. Cuando conectes el LED al módulo, asegúrate de que la pata del lado redondeado esté conectada al enchufe marcado con **+** en el exterior del módulo, y el lado más plano esté conectado al enchufe más cercano al centro del módulo.

1. El módulo LED tiene un botón giratorio que te permite controlar el brillo. Gíralo completamente hacia arriba al principio, rotándolo en sentido antihorario hasta que no pueda girar más usando un pequeño destornillador de cabeza Phillips.

1. Inserta un extremo de un cable Grove en el enchufe del módulo LED. Solo entrará en una dirección.

1. Con el Wio Terminal desconectado de tu computadora u otra fuente de alimentación, conecta el otro extremo del cable Grove al enchufe Grove del lado derecho del Wio Terminal mientras miras la pantalla. Este es el enchufe más alejado del botón de encendido.

    > 💁 El enchufe Grove del lado derecho puede usarse con sensores y actuadores analógicos o digitales. El enchufe del lado izquierdo es solo para sensores y actuadores digitales. C se cubrirá en una lección posterior.

![El Grove LED conectado al enchufe del lado derecho](../../../../../translated_images/es/wio-led.265a1897e72d7f21.webp)

## Programa la luz nocturna

La luz nocturna ahora puede programarse usando el sensor de luz incorporado y el Grove LED.

### Tarea - programa la luz nocturna

Programa la luz nocturna.

1. Abre el proyecto de luz nocturna en VS Code que creaste en la parte anterior de esta asignación.

1. Agrega la siguiente línea al final de la función `setup`:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Esta línea configura el pin utilizado para comunicarse con el LED a través del puerto Grove.

    El pin `D0` es el pin digital para el enchufe Grove del lado derecho. Este pin se configura como `OUTPUT`, lo que significa que se conecta a un actuador y se escribirán datos en el pin.

1. Agrega el siguiente código inmediatamente antes del `delay` en la función loop:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Este código verifica el valor de `light`. Si es menor que 300, envía un valor `HIGH` al pin digital `D0`. Este `HIGH` es un valor de 1, encendiendo el LED. Si el valor de luz es mayor o igual a 300, se envía un valor `LOW` de 0 al pin, apagando el LED.

    > 💁 Al enviar valores digitales a actuadores, un valor LOW es 0v, y un valor HIGH es el voltaje máximo para el dispositivo. Para el Wio Terminal, el voltaje HIGH es 3.3V.

1. Reconecta el Wio Terminal a tu computadora y sube el nuevo código como lo hiciste antes.

1. Conecta el Monitor Serial. Los valores de luz se mostrarán en el terminal.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. Cubre y descubre el sensor de luz. Observa cómo el LED se enciende si el nivel de luz es 300 o menos, y se apaga cuando el nivel de luz es mayor a 300.

![El LED conectado al WIO encendiéndose y apagándose según cambia el nivel de luz](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Puedes encontrar este código en la carpeta [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal).

😀 ¡Tu programa de luz nocturna fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.