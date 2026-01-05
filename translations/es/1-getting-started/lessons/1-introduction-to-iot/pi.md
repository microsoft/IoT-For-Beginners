<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-26T15:13:31+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "es"
}
-->
# Raspberry Pi

El [Raspberry Pi](https://raspberrypi.org) es un ordenador de placa única. Puedes añadir sensores y actuadores utilizando una amplia gama de dispositivos y ecosistemas. Para estas lecciones, utilizaremos un ecosistema de hardware llamado [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Programarás tu Pi y accederás a los sensores Grove usando Python.

![Un Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.es.jpg)

## Configuración

Si estás utilizando un Raspberry Pi como tu hardware IoT, tienes dos opciones: puedes trabajar directamente en el Pi y completar todas las lecciones ahí, o puedes conectarte de forma remota a un Pi 'sin cabeza' y programarlo desde tu computadora.

Antes de comenzar, también necesitas conectar el Grove Base Hat a tu Pi.

### Tarea - configuración

Instala el Grove Base Hat en tu Pi y configura el Pi.

1. Conecta el Grove Base Hat a tu Pi. El conector del hat encaja sobre todos los pines GPIO del Pi, deslizándose completamente hacia abajo para quedar firmemente asentado en la base. Cubre el Pi al colocarse.

    ![Colocando el Grove Hat](../../../../../images/pi-grove-hat-fitting.gif)

1. Decide cómo quieres programar tu Pi y dirígete a la sección correspondiente a continuación:

    * [Trabajar directamente en tu Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Acceso remoto para programar el Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Trabajar directamente en tu Pi

Si deseas trabajar directamente en tu Pi, puedes usar la versión de escritorio del sistema operativo Raspberry Pi OS e instalar todas las herramientas necesarias.

#### Tarea - trabajar directamente en tu Pi

Configura tu Pi para el desarrollo.

1. Sigue las instrucciones en la [guía de configuración de Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) para configurar tu Pi, conectarlo a un teclado/ratón/monitor, conectarlo a tu red WiFi o Ethernet, y actualizar el software.

Para programar el Pi utilizando los sensores y actuadores Grove, necesitarás instalar un editor para escribir el código del dispositivo, así como varias bibliotecas y herramientas que interactúan con el hardware Grove.

1. Una vez que tu Pi se haya reiniciado, abre el Terminal haciendo clic en el icono **Terminal** en la barra de menú superior, o selecciona *Menú -> Accesorios -> Terminal*.

1. Ejecuta el siguiente comando para asegurarte de que el sistema operativo y el software instalado estén actualizados:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Ejecuta los siguientes comandos para instalar todas las bibliotecas necesarias para el hardware Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Esto comienza instalando Git, junto con Pip para instalar paquetes de Python.

    Una de las características más potentes de Python es la capacidad de instalar [paquetes Pip](https://pypi.org), que son paquetes de código escritos por otras personas y publicados en Internet. Puedes instalar un paquete Pip en tu computadora con un solo comando y luego usar ese paquete en tu código.

    Los paquetes de Python de Seeed Grove necesitan ser instalados desde el código fuente. Estos comandos clonarán el repositorio que contiene el código fuente de este paquete y luego lo instalarán localmente.

    > 💁 Por defecto, cuando instalas un paquete, está disponible en toda tu computadora, lo que puede generar problemas con las versiones de los paquetes, como cuando una aplicación depende de una versión específica de un paquete que se rompe al instalar una nueva versión para otra aplicación. Para evitar este problema, puedes usar un [entorno virtual de Python](https://docs.python.org/3/library/venv.html), que es esencialmente una copia de Python en una carpeta dedicada. Cuando instalas paquetes Pip, se instalan solo en esa carpeta. Sin embargo, no usarás entornos virtuales al usar tu Pi. El script de instalación de Grove instala los paquetes de Python de Grove de forma global, por lo que, si quisieras usar un entorno virtual, tendrías que configurarlo y luego reinstalar manualmente los paquetes de Grove dentro de ese entorno. Es más fácil usar paquetes globales, especialmente porque muchos desarrolladores de Pi suelen volver a flashear una tarjeta SD limpia para cada proyecto.

    Finalmente, esto habilita la interfaz I<sup>2</sup>C.

1. Reinicia el Pi utilizando el menú o ejecutando el siguiente comando en el Terminal:

    ```sh
    sudo reboot
    ```

1. Una vez que el Pi se haya reiniciado, vuelve a abrir el Terminal y ejecuta el siguiente comando para instalar [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn), que es el editor que usarás para escribir tu código de dispositivo en Python.

    ```sh
    sudo apt install code
    ```

    Una vez instalado, VS Code estará disponible desde el menú superior.

    > 💁 Eres libre de usar cualquier IDE o editor de Python para estas lecciones si tienes una herramienta preferida, pero las instrucciones de las lecciones estarán basadas en el uso de VS Code.

1. Instala Pylance. Esta es una extensión para VS Code que proporciona soporte para el lenguaje Python. Consulta la [documentación de la extensión Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) para obtener instrucciones sobre cómo instalar esta extensión en VS Code.

### Acceso remoto para programar el Pi

En lugar de programar directamente en el Pi, este puede ejecutarse 'sin cabeza', es decir, sin estar conectado a un teclado/ratón/monitor, y configurarse y programarse desde tu computadora utilizando Visual Studio Code.

#### Configurar el sistema operativo del Pi

Para programar de forma remota, el sistema operativo del Pi debe instalarse en una tarjeta SD.

##### Tarea - configurar el sistema operativo del Pi

Configura el sistema operativo sin cabeza del Pi.

1. Descarga el **Raspberry Pi Imager** desde la [página de software de Raspberry Pi OS](https://www.raspberrypi.org/software/) e instálalo.

1. Inserta una tarjeta SD en tu computadora, utilizando un adaptador si es necesario.

1. Abre el Raspberry Pi Imager.

1. Desde el Raspberry Pi Imager, selecciona el botón **CHOOSE OS**, luego selecciona *Raspberry Pi OS (Other)*, seguido de *Raspberry Pi OS Lite (32-bit)*.

    ![El Raspberry Pi Imager con Raspberry Pi OS Lite seleccionado](../../../../../translated_images/raspberry-pi-imager.24aedeab9e233d84.es.png)

    > 💁 Raspberry Pi OS Lite es una versión de Raspberry Pi OS que no tiene la interfaz de usuario de escritorio ni herramientas basadas en interfaz gráfica. Estas no son necesarias para un Pi sin cabeza y hacen que la instalación sea más pequeña y el tiempo de arranque más rápido.

1. Selecciona el botón **CHOOSE STORAGE**, luego selecciona tu tarjeta SD.

1. Abre las **Opciones Avanzadas** presionando `Ctrl+Shift+X`. Estas opciones permiten preconfigurar el sistema operativo Raspberry Pi antes de grabarlo en la tarjeta SD.

    1. Marca la casilla **Enable SSH** y establece una contraseña para el usuario `pi`. Esta será la contraseña que usarás para iniciar sesión en el Pi más tarde.

    1. Si planeas conectarte al Pi por WiFi, marca la casilla **Configure WiFi** e ingresa tu SSID y contraseña de WiFi, además de seleccionar tu país de WiFi. No necesitas hacer esto si usarás un cable Ethernet. Asegúrate de que la red a la que te conectes sea la misma en la que está tu computadora.

    1. Marca la casilla **Set locale settings** y configura tu país y zona horaria.

    1. Selecciona el botón **SAVE**.

1. Selecciona el botón **WRITE** para escribir el sistema operativo en la tarjeta SD. Si estás usando macOS, se te pedirá que ingreses tu contraseña, ya que la herramienta subyacente que escribe imágenes de disco necesita acceso privilegiado.

El sistema operativo se escribirá en la tarjeta SD y, una vez completado, el sistema operativo expulsará la tarjeta y se te notificará. Retira la tarjeta SD de tu computadora, insértala en el Pi, enciende el Pi y espera unos 2 minutos para que arranque correctamente.

#### Conectarse al Pi

El siguiente paso es acceder al Pi de forma remota. Puedes hacerlo utilizando `ssh`, que está disponible en macOS, Linux y versiones recientes de Windows.

##### Tarea - conectarse al Pi

Accede al Pi de forma remota.

1. Abre un Terminal o Símbolo del sistema y escribe el siguiente comando para conectarte al Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Si estás en Windows usando una versión más antigua que no tiene `ssh` instalado, puedes usar OpenSSH. Puedes encontrar las instrucciones de instalación en la [documentación de instalación de OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Esto debería conectarte a tu Pi y pedirte la contraseña.

    Poder encontrar computadoras en tu red usando `<hostname>.local` es una adición relativamente reciente en Linux y Windows. Si estás usando Linux o Windows y obtienes errores sobre que no se encuentra el nombre del host, necesitarás instalar software adicional para habilitar la red ZeroConf (también conocida por Apple como Bonjour):

    1. Si estás usando Linux, instala Avahi con el siguiente comando:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Si estás usando Windows, la forma más sencilla de habilitar ZeroConf es instalar [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). También puedes instalar [iTunes para Windows](https://www.apple.com/itunes/download/) para obtener una versión más reciente de la utilidad (que no está disponible de forma independiente).

    > 💁 Si no puedes conectarte usando `raspberrypi.local`, puedes usar la dirección IP de tu Pi. Consulta la [documentación de direcciones IP de Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) para obtener instrucciones sobre varias formas de obtener la dirección IP.

1. Ingresa la contraseña que configuraste en las Opciones Avanzadas del Raspberry Pi Imager.

#### Configurar software en el Pi

Una vez conectado al Pi, necesitas asegurarte de que el sistema operativo esté actualizado e instalar varias bibliotecas y herramientas que interactúan con el hardware Grove.

##### Tarea - configurar software en el Pi

Configura el software instalado en el Pi e instala las bibliotecas Grove.

1. Desde tu sesión `ssh`, ejecuta el siguiente comando para actualizar y luego reiniciar el Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    El Pi se actualizará y reiniciará. La sesión `ssh` terminará cuando el Pi se reinicie, así que espera unos 30 segundos y vuelve a conectarte.

1. Desde la sesión `ssh` reconectada, ejecuta los siguientes comandos para instalar todas las bibliotecas necesarias para el hardware Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Esto comienza instalando Git, junto con Pip para instalar paquetes de Python.

    Una de las características más potentes de Python es la capacidad de instalar [paquetes Pip](https://pypi.org), que son paquetes de código escritos por otras personas y publicados en Internet. Puedes instalar un paquete Pip en tu computadora con un solo comando y luego usar ese paquete en tu código.

    Los paquetes de Python de Seeed Grove necesitan ser instalados desde el código fuente. Estos comandos clonarán el repositorio que contiene el código fuente de este paquete y luego lo instalarán localmente.

    > 💁 Por defecto, cuando instalas un paquete, está disponible en toda tu computadora, lo que puede generar problemas con las versiones de los paquetes, como cuando una aplicación depende de una versión específica de un paquete que se rompe al instalar una nueva versión para otra aplicación. Para evitar este problema, puedes usar un [entorno virtual de Python](https://docs.python.org/3/library/venv.html), que es esencialmente una copia de Python en una carpeta dedicada. Cuando instalas paquetes Pip, se instalan solo en esa carpeta. Sin embargo, no usarás entornos virtuales al usar tu Pi. El script de instalación de Grove instala los paquetes de Python de Grove de forma global, por lo que, si quisieras usar un entorno virtual, tendrías que configurarlo y luego reinstalar manualmente los paquetes de Grove dentro de ese entorno. Es más fácil usar paquetes globales, especialmente porque muchos desarrolladores de Pi suelen volver a flashear una tarjeta SD limpia para cada proyecto.

    Finalmente, esto habilita la interfaz I<sup>2</sup>C.

1. Reinicia el Pi ejecutando el siguiente comando:

    ```sh
    sudo reboot
    ```

    La sesión `ssh` terminará cuando el Pi se reinicie. No es necesario volver a conectarse.

#### Configurar VS Code para acceso remoto

Una vez que el Pi esté configurado, puedes conectarte a él utilizando Visual Studio Code (VS Code) desde tu computadora. Este es un editor de texto gratuito para desarrolladores que usarás para escribir tu código de dispositivo en Python.

##### Tarea - configurar VS Code para acceso remoto

Instala el software necesario y conéctate de forma remota a tu Pi.

1. Instala VS Code en tu computadora siguiendo la [documentación de VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Sigue las instrucciones en la [documentación de desarrollo remoto de VS Code usando SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) para instalar los componentes necesarios.

1. Siguiendo las mismas instrucciones, conecta VS Code al Pi.

1. Una vez conectado, sigue las instrucciones de [gestión de extensiones](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) para instalar la [extensión Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) de forma remota en el Pi.

## Hola mundo
Es tradicional, al comenzar con un nuevo lenguaje de programación o tecnología, crear una aplicación 'Hola Mundo': una pequeña aplicación que muestra algo como el texto `"Hola Mundo"` para confirmar que todas las herramientas están configuradas correctamente.

La aplicación Hola Mundo para el Pi garantizará que tienes Python y Visual Studio Code instalados correctamente.

Esta aplicación estará en una carpeta llamada `nightlight`, y se reutilizará con diferentes códigos en partes posteriores de esta tarea para construir la aplicación de luz nocturna.

### Tarea - hola mundo

Crea la aplicación Hola Mundo.

1. Inicia VS Code, ya sea directamente en el Pi, o en tu computadora conectada al Pi usando la extensión Remote SSH.

1. Abre el Terminal de VS Code seleccionando *Terminal -> Nuevo Terminal*, o presionando `` CTRL+` ``. Se abrirá en el directorio principal del usuario `pi`.

1. Ejecuta los siguientes comandos para crear un directorio para tu código y un archivo Python llamado `app.py` dentro de ese directorio:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Abre esta carpeta en VS Code seleccionando *Archivo -> Abrir...* y seleccionando la carpeta *nightlight*, luego selecciona **OK**.

    ![El cuadro de diálogo de apertura de VS Code mostrando la carpeta nightlight](../../../../../translated_images/vscode-open-nightlight-remote.d3d2a4011e30d535.es.png)

1. Abre el archivo `app.py` desde el explorador de VS Code y agrega el siguiente código:

    ```python
    print('Hello World!')
    ```

    La función `print` imprime en la consola lo que se le pase como argumento.

1. Desde el Terminal de VS Code, ejecuta lo siguiente para correr tu aplicación Python:

    ```sh
    python app.py
    ```

    > 💁 Es posible que necesites llamar explícitamente a `python3` para ejecutar este código si tienes Python 2 instalado además de Python 3 (la última versión). Si tienes Python 2 instalado, al llamar a `python` se usará Python 2 en lugar de Python 3. Por defecto, las versiones más recientes del sistema operativo Raspberry Pi solo tienen Python 3 instalado.

    La siguiente salida aparecerá en el terminal:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Puedes encontrar este código en la carpeta [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 ¡Tu programa 'Hola Mundo' fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.