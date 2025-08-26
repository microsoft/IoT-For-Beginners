<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-26T15:28:05+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "es"
}
-->
# Configurar un temporizador - Hardware IoT Virtual y Raspberry Pi

En esta parte de la lección, llamarás a tu código sin servidor para interpretar el habla y configurar un temporizador en tu dispositivo IoT virtual o Raspberry Pi basado en los resultados.

## Configurar un temporizador

El texto que se obtiene de la llamada de reconocimiento de voz debe enviarse a tu código sin servidor para ser procesado por LUIS, obteniendo el número de segundos para el temporizador. Este número de segundos se puede usar para configurar un temporizador.

Los temporizadores se pueden configurar utilizando la clase `threading.Timer` de Python. Esta clase toma un tiempo de retraso y una función, y después del tiempo de retraso, la función se ejecuta.

### Tarea - enviar el texto a la función sin servidor

1. Abre el proyecto `smart-timer` en VS Code y asegúrate de que el entorno virtual esté cargado en la terminal si estás utilizando un dispositivo IoT virtual.

1. Encima de la función `process_text`, declara una función llamada `get_timer_time` para llamar al endpoint REST que creaste:

    ```python
    def get_timer_time(text):
    ```

1. Agrega el siguiente código a esta función para definir la URL que se llamará:

    ```python
    url = '<URL>'
    ```

    Reemplaza `<URL>` con la URL de tu endpoint REST que construiste en la última lección, ya sea en tu computadora o en la nube.

1. Agrega el siguiente código para establecer el texto como una propiedad pasada como JSON en la llamada:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Debajo de esto, recupera los `seconds` del payload de la respuesta, devolviendo 0 si la llamada falló:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Las llamadas HTTP exitosas devuelven un código de estado en el rango de 200, y tu código sin servidor devuelve 200 si el texto fue procesado y reconocido como la intención de configurar un temporizador.

### Tarea - configurar un temporizador en un hilo en segundo plano

1. Agrega la siguiente declaración de importación al principio del archivo para importar la biblioteca de Python `threading`:

    ```python
    import threading
    ```

1. Encima de la función `process_text`, agrega una función para hablar una respuesta. Por ahora, esto solo escribirá en la consola, pero más adelante en esta lección, esto hablará el texto.

    ```python
    def say(text):
        print(text)
    ```

1. Debajo de esto, agrega una función que será llamada por un temporizador para anunciar que el temporizador ha terminado:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    Esta función toma el número de minutos y segundos del temporizador y construye una frase para decir que el temporizador ha terminado. Verificará el número de minutos y segundos, e incluirá cada unidad de tiempo solo si tiene un valor. Por ejemplo, si el número de minutos es 0, solo se incluirán los segundos en el mensaje. Esta frase se envía luego a la función `say`.

1. Debajo de esto, agrega la siguiente función `create_timer` para crear un temporizador:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Esta función toma el número total de segundos para el temporizador que se enviará en el comando y lo convierte en minutos y segundos. Luego crea y comienza un objeto temporizador utilizando el número total de segundos, pasando la función `announce_timer` y una lista que contiene los minutos y segundos. Cuando el temporizador finaliza, llamará a la función `announce_timer` y pasará el contenido de esta lista como parámetros, de modo que el primer elemento de la lista se pase como el parámetro `minutes` y el segundo elemento como el parámetro `seconds`.

1. Al final de la función `create_timer`, agrega algo de código para construir un mensaje que se le dirá al usuario para anunciar que el temporizador está comenzando:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Nuevamente, esto solo incluye la unidad de tiempo que tiene un valor. Esta frase se envía luego a la función `say`.

1. Agrega lo siguiente al final de la función `process_text` para obtener el tiempo del temporizador a partir del texto y luego crear el temporizador:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    El temporizador solo se crea si el número de segundos es mayor que 0.

1. Ejecuta la aplicación y asegúrate de que la aplicación de funciones también esté en ejecución. Configura algunos temporizadores y la salida mostrará que el temporizador se está configurando y luego mostrará cuando finaliza:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Puedes encontrar este código en la carpeta [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) o [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 ¡Tu programa de temporizador fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por lograr precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.