# Construye una luz nocturna - Raspberry Pi

En esta parte de la lección, agregarás un LED a tu Raspberry Pi y lo usarás para crear una luz nocturna.

## Hardware

La luz nocturna ahora necesita un actuador.

El actuador es un **LED**, un [diodo emisor de luz](https://wikipedia.org/wiki/Diodo_emisor_de_luz) que emite luz cuando la corriente fluye a través de él. Este es un actuador digital que tiene 2 estados: encendido y apagado. Enviar un valor de 1 enciende el LED, y un valor de 0 lo apaga. El LED es un actuador externo Grove y necesita conectarse al Grove Base hat en la Raspberry Pi.

La lógica de la luz nocturna en pseudocódigo es:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Conecta el LED

El LED Grove viene como un módulo con una selección de LEDs, lo que te permite elegir el color.

#### Tarea - conecta el LED

Conecta el LED.

![Un LED Grove](../../../../../translated_images/es/grove-led.6c853be93f473cf2.webp)

1. Elige tu LED favorito e inserta las patas en los dos agujeros del módulo LED.

    Los LEDs son diodos emisores de luz, y los diodos son dispositivos electrónicos que solo pueden conducir corriente en una dirección. Esto significa que el LED debe conectarse en la orientación correcta, de lo contrario, no funcionará.

    Una de las patas del LED es el pin positivo, y la otra es el pin negativo. El LED no es perfectamente redondo y es ligeramente más plano en un lado. El lado ligeramente más plano es el pin negativo. Cuando conectes el LED al módulo, asegúrate de que la pata del lado redondeado esté conectada al enchufe marcado con **+** en el exterior del módulo, y el lado más plano esté conectado al enchufe más cercano al centro del módulo.

1. El módulo LED tiene un botón giratorio que te permite controlar el brillo. Gíralo completamente hacia arriba al principio, rotándolo en sentido antihorario hasta el tope, usando un destornillador pequeño de cabeza Phillips.

1. Inserta un extremo de un cable Grove en el enchufe del módulo LED. Solo encajará en una dirección.

1. Con la Raspberry Pi apagada, conecta el otro extremo del cable Grove al enchufe digital marcado como **D5** en el Grove Base hat conectado a la Pi. Este enchufe es el segundo desde la izquierda, en la fila de enchufes junto a los pines GPIO.

![El LED Grove conectado al enchufe D5](../../../../../translated_images/es/pi-led.97f1d474981dc35d.webp)

## Programa la luz nocturna

Ahora se puede programar la luz nocturna usando el sensor de luz Grove y el LED Grove.

### Tarea - programa la luz nocturna

Programa la luz nocturna.

1. Enciende la Raspberry Pi y espera a que arranque.

1. Abre el proyecto de la luz nocturna en VS Code que creaste en la parte anterior de esta tarea, ya sea ejecutándolo directamente en la Pi o conectado usando la extensión Remote SSH.

1. Agrega el siguiente código al archivo `app.py` para importar una biblioteca requerida. Esto debe añadirse al principio, debajo de las otras líneas `import`.

    ```python
    from grove.grove_led import GroveLed
    ```

    La declaración `from grove.grove_led import GroveLed` importa el `GroveLed` de las bibliotecas de Python de Grove. Esta biblioteca contiene el código para interactuar con un LED Grove.

1. Agrega el siguiente código después de la declaración de `light_sensor` para crear una instancia de la clase que gestiona el LED:

    ```python
    led = GroveLed(5)
    ```

    La línea `led = GroveLed(5)` crea una instancia de la clase `GroveLed` conectada al pin **D5**, el pin digital Grove al que está conectado el LED.

    > 💁 Todos los enchufes tienen números de pin únicos. Los pines 0, 2, 4 y 6 son pines analógicos, mientras que los pines 5, 16, 18, 22, 24 y 26 son pines digitales.

1. Agrega una verificación dentro del bucle `while`, y antes del `time.sleep`, para comprobar los niveles de luz y encender o apagar el LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Este código verifica el valor de `light`. Si es menor que 300, llama al método `on` de la clase `GroveLed`, que envía un valor digital de 1 al LED, encendiéndolo. Si el valor de luz es mayor o igual a 300, llama al método `off`, enviando un valor digital de 0 al LED, apagándolo.

    > 💁 Este código debe estar indentado al mismo nivel que la línea `print('Light level:', light)` para estar dentro del bucle while.

    > 💁 Al enviar valores digitales a los actuadores, un valor de 0 es 0V, y un valor de 1 es el voltaje máximo para el dispositivo. Para la Raspberry Pi con sensores y actuadores Grove, el voltaje de 1 es 3.3V.

1. Desde el Terminal de VS Code, ejecuta lo siguiente para ejecutar tu aplicación en Python:

    ```sh
    python3 app.py
    ```

    Los valores de luz se mostrarán en la consola.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Cubre y descubre el sensor de luz. Observa cómo el LED se enciende si el nivel de luz es 300 o menos, y se apaga cuando el nivel de luz es mayor a 300.

    > 💁 Si el LED no se enciende, asegúrate de que esté conectado en la orientación correcta y que el botón giratorio esté ajustado al máximo.

![El LED conectado a la Pi encendiéndose y apagándose según cambian los niveles de luz](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Puedes encontrar este código en la carpeta [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 ¡Tu programa de luz nocturna fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por lograr precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.