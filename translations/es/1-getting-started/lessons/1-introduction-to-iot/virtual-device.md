<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-26T15:12:02+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "es"
}
-->
# Computadora de placa única virtual

En lugar de comprar un dispositivo IoT junto con sensores y actuadores, puedes usar tu computadora para simular hardware IoT. El proyecto [CounterFit](https://github.com/CounterFit-IoT/CounterFit) te permite ejecutar una aplicación localmente que simula hardware IoT como sensores y actuadores, y acceder a ellos desde código Python local escrito de la misma manera que lo harías en una Raspberry Pi utilizando hardware físico.

## Configuración

Para usar CounterFit, necesitarás instalar algunos programas gratuitos en tu computadora.

### Tarea

Instala el software necesario.

1. Instala Python. Consulta la [página de descargas de Python](https://www.python.org/downloads/) para obtener instrucciones sobre cómo instalar la última versión de Python.

1. Instala Visual Studio Code (VS Code). Este es el editor que usarás para escribir el código de tu dispositivo virtual en Python. Consulta la [documentación de VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) para obtener instrucciones sobre cómo instalar VS Code.

    > 💁 Puedes usar cualquier IDE o editor de Python para estas lecciones si tienes una herramienta preferida, pero las instrucciones de las lecciones estarán basadas en el uso de VS Code.

1. Instala la extensión Pylance de VS Code. Esta es una extensión para VS Code que proporciona soporte para el lenguaje Python. Consulta la [documentación de la extensión Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) para obtener instrucciones sobre cómo instalar esta extensión en VS Code.

Las instrucciones para instalar y configurar la aplicación CounterFit se proporcionarán en el momento adecuado en las instrucciones de la asignación, ya que se instala por proyecto.

## Hola Mundo

Es tradicional al comenzar con un nuevo lenguaje de programación o tecnología crear una aplicación 'Hola Mundo': una pequeña aplicación que muestra un texto como `"Hello World"` para verificar que todas las herramientas están configuradas correctamente.

La aplicación Hola Mundo para el hardware IoT virtual asegurará que tienes Python y Visual Studio Code instalados correctamente. También se conectará a CounterFit para los sensores y actuadores IoT virtuales. No usará ningún hardware, solo se conectará para demostrar que todo está funcionando.

Esta aplicación estará en una carpeta llamada `nightlight`, y se reutilizará con diferentes códigos en partes posteriores de esta asignación para construir la aplicación de luz nocturna.

### Configurar un entorno virtual de Python

Una de las características más poderosas de Python es la capacidad de instalar [paquetes Pip](https://pypi.org), que son paquetes de código escritos por otras personas y publicados en Internet. Puedes instalar un paquete Pip en tu computadora con un solo comando y luego usar ese paquete en tu código. Usarás Pip para instalar un paquete que permita interactuar con CounterFit.

Por defecto, cuando instalas un paquete, está disponible en toda tu computadora, lo que puede generar problemas con las versiones de los paquetes, como que una aplicación dependa de una versión que se rompa al instalar una nueva versión para otra aplicación. Para evitar este problema, puedes usar un [entorno virtual de Python](https://docs.python.org/3/library/venv.html), que es esencialmente una copia de Python en una carpeta dedicada, y cuando instalas paquetes Pip, se instalan solo en esa carpeta.

> 💁 Si estás usando una Raspberry Pi, no configuraste un entorno virtual en ese dispositivo para gestionar los paquetes Pip; en su lugar, estás usando paquetes globales, ya que los paquetes Grove se instalan globalmente mediante el script de instalación.

#### Tarea - configurar un entorno virtual de Python

Configura un entorno virtual de Python e instala los paquetes Pip para CounterFit.

1. Desde tu terminal o línea de comandos, ejecuta lo siguiente en una ubicación de tu elección para crear y navegar a un nuevo directorio:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Ahora ejecuta lo siguiente para crear un entorno virtual en la carpeta `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Necesitas llamar explícitamente a `python3` para crear el entorno virtual en caso de que tengas Python 2 instalado además de Python 3 (la última versión). Si tienes Python 2 instalado, llamar a `python` usará Python 2 en lugar de Python 3.

1. Activa el entorno virtual:

    * En Windows:
        * Si estás usando el Command Prompt o el Command Prompt a través de Windows Terminal, ejecuta:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Si estás usando PowerShell, ejecuta:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Si obtienes un error sobre que los scripts están deshabilitados en este sistema, necesitarás habilitar la ejecución de scripts configurando una política de ejecución adecuada. Puedes hacerlo iniciando PowerShell como administrador y ejecutando el siguiente comando:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Ingresa `Y` cuando se te pida confirmar. Luego, reinicia PowerShell e intenta nuevamente.

            Puedes restablecer esta política de ejecución más adelante si es necesario. Puedes leer más sobre esto en la [página de Políticas de Ejecución en Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * En macOS o Linux, ejecuta:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Estos comandos deben ejecutarse desde la misma ubicación donde ejecutaste el comando para crear el entorno virtual. Nunca necesitarás navegar dentro de la carpeta `.venv`; siempre debes ejecutar el comando de activación y cualquier comando para instalar paquetes o ejecutar código desde la carpeta donde creaste el entorno virtual.

1. Una vez que el entorno virtual esté activado, el comando `python` por defecto ejecutará la versión de Python que se usó para crear el entorno virtual. Ejecuta lo siguiente para obtener la versión:

    ```sh
    python --version
    ```

    La salida debería contener lo siguiente:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Tu versión de Python puede ser diferente; mientras sea la versión 3.6 o superior, estás bien. Si no, elimina esta carpeta, instala una versión más reciente de Python e inténtalo nuevamente.

1. Ejecuta los siguientes comandos para instalar los paquetes Pip para CounterFit. Estos paquetes incluyen la aplicación principal de CounterFit, así como adaptadores para hardware Grove. Estos adaptadores te permiten escribir código como si estuvieras programando con sensores y actuadores físicos del ecosistema Grove pero conectados a dispositivos IoT virtuales.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Estos paquetes Pip solo se instalarán en el entorno virtual y no estarán disponibles fuera de este.

### Escribir el código

Una vez que el entorno virtual de Python esté listo, puedes escribir el código para la aplicación 'Hola Mundo'.

#### Tarea - escribir el código

Crea una aplicación en Python para imprimir `"Hello World"` en la consola.

1. Desde tu terminal o línea de comandos, ejecuta lo siguiente dentro del entorno virtual para crear un archivo Python llamado `app.py`:

    * En Windows, ejecuta:

        ```cmd
        type nul > app.py
        ```

    * En macOS o Linux, ejecuta:

        ```cmd
        touch app.py
        ```

1. Abre la carpeta actual en VS Code:

    ```sh
    code .
    ```

    > 💁 Si tu terminal devuelve `command not found` en macOS, significa que VS Code no se ha agregado a tu PATH. Puedes agregar VS Code a tu PATH siguiendo las instrucciones en la [sección de Lanzamiento desde la línea de comandos de la documentación de VS Code](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) y luego ejecutar el comando nuevamente. VS Code se agrega a tu PATH por defecto en Windows y Linux.

1. Cuando VS Code se inicie, activará el entorno virtual de Python. El entorno virtual seleccionado aparecerá en la barra de estado inferior:

    ![VS Code mostrando el entorno virtual seleccionado](../../../../../translated_images/es/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Si el terminal de VS Code ya está ejecutándose cuando VS Code se inicia, no tendrá el entorno virtual activado. Lo más fácil es cerrar el terminal usando el botón **Kill the active terminal instance**:

    ![Botón de VS Code para cerrar la instancia activa del terminal](../../../../../translated_images/es/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Puedes saber si el terminal tiene el entorno virtual activado porque el nombre del entorno virtual será un prefijo en el prompt del terminal. Por ejemplo, podría ser:

    ```sh
    (.venv) ➜  nightlight
    ```

    Si no tienes `.venv` como prefijo en el prompt, el entorno virtual no está activo en el terminal.

1. Inicia un nuevo terminal en VS Code seleccionando *Terminal -> New Terminal*, o presionando `` CTRL+` ``. El nuevo terminal cargará el entorno virtual y la llamada para activarlo aparecerá en el terminal. El prompt también tendrá el nombre del entorno virtual (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Abre el archivo `app.py` desde el explorador de VS Code y agrega el siguiente código:

    ```python
    print('Hello World!')
    ```

    La función `print` imprime lo que se le pase en la consola.

1. Desde el terminal de VS Code, ejecuta lo siguiente para ejecutar tu aplicación en Python:

    ```sh
    python app.py
    ```

    La salida será la siguiente:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 ¡Tu programa 'Hola Mundo' fue un éxito!

### Conectar el 'hardware'

Como un segundo paso de 'Hola Mundo', ejecutarás la aplicación CounterFit y conectarás tu código a ella. Esto es el equivalente virtual de conectar hardware IoT a un kit de desarrollo.

#### Tarea - conectar el 'hardware'

1. Desde el terminal de VS Code, inicia la aplicación CounterFit con el siguiente comando:

    ```sh
    counterfit
    ```

    La aplicación comenzará a ejecutarse y se abrirá en tu navegador web:

    ![La aplicación CounterFit ejecutándose en un navegador](../../../../../translated_images/es/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.png)

    Estará marcada como *Disconnected*, con el LED en la esquina superior derecha apagado.

1. Agrega el siguiente código al inicio de `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Este código importa la clase `CounterFitConnection` del módulo `counterfit_connection`, que proviene del paquete Pip `counterfit-connection` que instalaste anteriormente. Luego inicializa una conexión a la aplicación CounterFit que se ejecuta en `127.0.0.1`, que es una dirección IP que siempre puedes usar para acceder a tu computadora local (a menudo llamada *localhost*), en el puerto 5000.

    > 💁 Si tienes otras aplicaciones ejecutándose en el puerto 5000, puedes cambiar esto actualizando el puerto en el código y ejecutando CounterFit usando `CounterFit --port <port_number>`, reemplazando `<port_number>` con el puerto que deseas usar.

1. Necesitarás iniciar un nuevo terminal en VS Code seleccionando el botón **Create a new integrated terminal**. Esto se debe a que la aplicación CounterFit está ejecutándose en el terminal actual.

    ![Botón de VS Code para crear un nuevo terminal integrado](../../../../../translated_images/es/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. En este nuevo terminal, ejecuta el archivo `app.py` como antes. El estado de CounterFit cambiará a **Connected** y el LED se encenderá.

    ![CounterFit mostrando como conectado](../../../../../translated_images/es/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.png)

> 💁 Puedes encontrar este código en la carpeta [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device).

😀 ¡Tu conexión al hardware fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.