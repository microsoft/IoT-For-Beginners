<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-26T15:15:03+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "es"
}
-->
# Wio Terminal

El [Wio Terminal de Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) es un microcontrolador compatible con Arduino, con WiFi y algunos sensores y actuadores integrados, así como puertos para añadir más sensores y actuadores utilizando un ecosistema de hardware llamado [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![Un Wio Terminal de Seeed Studios](../../../../../translated_images/es/wio-terminal.b8299ee16587db9a.webp)

## Configuración

Para usar tu Wio Terminal, necesitarás instalar software gratuito en tu computadora. También deberás actualizar el firmware del Wio Terminal antes de poder conectarlo a WiFi.

### Tarea - configuración

Instala el software necesario y actualiza el firmware.

1. Instala Visual Studio Code (VS Code). Este será el editor que usarás para escribir el código de tu dispositivo en C/C++. Consulta la [documentación de VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) para obtener instrucciones sobre cómo instalar VS Code.

    > 💁 Otro IDE popular para el desarrollo con Arduino es el [Arduino IDE](https://www.arduino.cc/en/software). Si ya estás familiarizado con esta herramienta, puedes usarla en lugar de VS Code y PlatformIO, pero las lecciones proporcionarán instrucciones basadas en el uso de VS Code.

1. Instala la extensión PlatformIO para VS Code. Esta es una extensión para VS Code que permite programar microcontroladores en C/C++. Consulta la [documentación de la extensión PlatformIO](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) para obtener instrucciones sobre cómo instalar esta extensión en VS Code. Esta extensión depende de la extensión Microsoft C/C++ para trabajar con código en C y C++, y esta última se instala automáticamente al instalar PlatformIO.

1. Conecta tu Wio Terminal a tu computadora. El Wio Terminal tiene un puerto USB-C en la parte inferior, y este debe conectarse a un puerto USB de tu computadora. El Wio Terminal incluye un cable USB-C a USB-A, pero si tu computadora solo tiene puertos USB-C, necesitarás un cable USB-C o un adaptador de USB-A a USB-C.

1. Sigue las instrucciones en la [documentación de configuración de WiFi del Wio Terminal Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) para configurar tu Wio Terminal y actualizar el firmware.

## Hola Mundo

Es tradicional al comenzar con un nuevo lenguaje de programación o tecnología crear una aplicación 'Hola Mundo': una pequeña aplicación que muestra algo como el texto `"Hello World"` para confirmar que todas las herramientas están configuradas correctamente.

La aplicación Hola Mundo para el Wio Terminal asegurará que tienes Visual Studio Code instalado correctamente con PlatformIO y configurado para el desarrollo de microcontroladores.

### Crear un proyecto PlatformIO

El primer paso es crear un nuevo proyecto usando PlatformIO configurado para el Wio Terminal.

#### Tarea - crear un proyecto PlatformIO

Crea el proyecto PlatformIO.

1. Conecta el Wio Terminal a tu computadora.

1. Abre VS Code.

1. El ícono de PlatformIO estará en la barra de menú lateral:

    ![La opción de menú de PlatformIO](../../../../../translated_images/es/vscode-platformio-menu.297be26b9733e5c4.webp)

    Selecciona este ícono, luego selecciona *PIO Home -> Open*.

    ![La opción de abrir PlatformIO](../../../../../translated_images/es/vscode-platformio-home-open.3f9a41bfd3f4da1c.webp)

1. Desde la pantalla de bienvenida, selecciona el botón **+ New Project**.

    ![El botón de nuevo proyecto](../../../../../translated_images/es/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.webp)

1. Configura el proyecto en el *Asistente de Proyecto*:

    1. Nombra tu proyecto `nightlight`.

    1. En el menú desplegable *Board*, escribe `WIO` para filtrar las placas y selecciona *Seeeduino Wio Terminal*.

    1. Deja el *Framework* como *Arduino*.

    1. Puedes dejar marcada la casilla *Use default location* o desmarcarla y seleccionar una ubicación para tu proyecto.

    1. Selecciona el botón **Finish**.

    ![El asistente de proyecto completado](../../../../../translated_images/es/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.webp)

    PlatformIO descargará los componentes necesarios para compilar el código para el Wio Terminal y creará tu proyecto. Esto puede tardar unos minutos.

### Explorar el proyecto PlatformIO

El explorador de VS Code mostrará varios archivos y carpetas creados por el asistente de PlatformIO.

#### Carpetas

* `.pio` - esta carpeta contiene datos temporales necesarios para PlatformIO, como bibliotecas o código compilado. Se recrea automáticamente si se elimina, y no necesitas añadirla al control de código fuente si compartes tu proyecto en sitios como GitHub.
* `.vscode` - esta carpeta contiene la configuración utilizada por PlatformIO y VS Code. Se recrea automáticamente si se elimina, y no necesitas añadirla al control de código fuente si compartes tu proyecto en sitios como GitHub.
* `include` - esta carpeta es para archivos de cabecera externos necesarios al añadir bibliotecas adicionales a tu código. No usarás esta carpeta en estas lecciones.
* `lib` - esta carpeta es para bibliotecas externas que quieras llamar desde tu código. No usarás esta carpeta en estas lecciones.
* `src` - esta carpeta contiene el código fuente principal de tu aplicación. Inicialmente, contendrá un único archivo: `main.cpp`.
* `test` - esta carpeta es donde colocarías cualquier prueba unitaria para tu código.

#### Archivos

* `main.cpp` - este archivo en la carpeta `src` contiene el punto de entrada para tu aplicación. Ábrelo y contendrá el siguiente código:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Cuando el dispositivo se inicia, el framework de Arduino ejecutará la función `setup` una vez, y luego ejecutará la función `loop` repetidamente hasta que el dispositivo se apague.

* `.gitignore` - este archivo lista los archivos y directorios que deben ignorarse al añadir tu código al control de código fuente, como al subirlo a un repositorio en GitHub.

* `platformio.ini` - este archivo contiene la configuración para tu dispositivo y aplicación. Ábrelo y contendrá el siguiente código:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    La sección `[env:seeed_wio_terminal]` tiene la configuración para el Wio Terminal. Puedes tener múltiples secciones `env` para que tu código pueda compilarse para varias placas.

    Los otros valores coinciden con la configuración del asistente de proyecto:

  * `platform = atmelsam` define el hardware que usa el Wio Terminal (un microcontrolador basado en ATSAMD51).
  * `board = seeed_wio_terminal` define el tipo de placa del microcontrolador (el Wio Terminal).
  * `framework = arduino` define que este proyecto usa el framework de Arduino.

### Escribir la aplicación Hola Mundo

Ahora estás listo para escribir la aplicación Hola Mundo.

#### Tarea - escribir la aplicación Hola Mundo

Escribe la aplicación Hola Mundo.

1. Abre el archivo `main.cpp` en VS Code.

1. Cambia el código para que coincida con lo siguiente:

    ```cpp
    #include <Arduino.h>

    void setup()
    {
        Serial.begin(9600);

        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    
    void loop()
    {
        Serial.println("Hello World");
        delay(5000);
    }
    ```

    La función `setup` inicializa una conexión al puerto serie, en este caso, el puerto USB que se usa para conectar el Wio Terminal a tu computadora. El parámetro `9600` es la [tasa de baudios](https://wikipedia.org/wiki/Symbol_rate) (también conocida como tasa de símbolos), o la velocidad a la que se enviarán los datos por el puerto serie en bits por segundo. Esta configuración significa que se envían 9,600 bits (0s y 1s) de datos por segundo. Luego, espera a que el puerto serie esté listo.

    La función `loop` envía la línea `Hello World!` al puerto serie, junto con un carácter de nueva línea. Luego, duerme durante 5,000 milisegundos o 5 segundos. Después de que termina el `loop`, se ejecuta nuevamente, y así sucesivamente mientras el microcontrolador esté encendido.

1. Pon tu Wio Terminal en modo de carga. Necesitarás hacer esto cada vez que subas un nuevo código al dispositivo:

    1. Baja dos veces rápidamente el interruptor de encendido; este volverá automáticamente a la posición de encendido cada vez.

    1. Verifica el LED azul de estado a la derecha del puerto USB. Debería estar pulsando.
    
    [![Un video que muestra cómo poner el Wio Terminal en modo de carga](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Haz clic en la imagen de arriba para ver un video que muestra cómo hacerlo.

1. Compila y sube el código al Wio Terminal.

    1. Abre el paleta de comandos de VS Code.

    1. Escribe `PlatformIO Upload` para buscar la opción de carga y selecciona *PlatformIO: Upload*.

        ![La opción de carga de PlatformIO en la paleta de comandos](../../../../../translated_images/es/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.webp)

        PlatformIO compilará automáticamente el código si es necesario antes de subirlo.

    1. El código será compilado y subido al Wio Terminal.

        > 💁 Si estás usando macOS, aparecerá una notificación sobre un *DISCO NO EXPULSADO CORRECTAMENTE*. Esto ocurre porque el Wio Terminal se monta como una unidad durante el proceso de carga y se desconecta cuando el código compilado se escribe en el dispositivo. Puedes ignorar esta notificación.

    ⚠️ Si obtienes errores sobre que el puerto de carga no está disponible, primero asegúrate de que el Wio Terminal esté conectado a tu computadora, encendido con el interruptor en el lado izquierdo de la pantalla y en modo de carga. La luz verde en la parte inferior debería estar encendida y la luz azul debería estar pulsando. Si aún obtienes el error, baja el interruptor de encendido/apagado dos veces rápidamente nuevamente para forzar al Wio Terminal a entrar en modo de carga e intenta subir el código nuevamente.

PlatformIO tiene un Monitor Serie que puede monitorear los datos enviados por el cable USB desde el Wio Terminal. Esto te permite monitorear los datos enviados por el comando `Serial.println("Hello World");`.

1. Abre el paleta de comandos de VS Code.

1. Escribe `PlatformIO Serial` para buscar la opción del Monitor Serie y selecciona *PlatformIO: Serial Monitor*.

    ![La opción del Monitor Serie de PlatformIO en la paleta de comandos](../../../../../translated_images/es/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.webp)

    Se abrirá un nuevo terminal y los datos enviados por el puerto serie se transmitirán a este terminal:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` se imprimirá en el monitor serie cada 5 segundos.

> 💁 Puedes encontrar este código en la carpeta [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal).

😀 ¡Tu programa 'Hola Mundo' fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.