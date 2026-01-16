<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-26T14:31:53+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "es"
}
-->
# Medir la temperatura - Raspberry Pi

En esta parte de la lección, agregarás un sensor de temperatura a tu Raspberry Pi.

## Hardware

El sensor que usarás es un [sensor de humedad y temperatura DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), que combina 2 sensores en un solo paquete. Este sensor es bastante popular, con varios modelos comerciales que combinan temperatura, humedad y, a veces, presión atmosférica. El componente del sensor de temperatura es un termistor de coeficiente de temperatura negativo (NTC), un tipo de termistor cuya resistencia disminuye a medida que aumenta la temperatura.

Este es un sensor digital, por lo que tiene un ADC integrado que genera una señal digital con los datos de temperatura y humedad que el microcontrolador puede leer.

### Conectar el sensor de temperatura

El sensor de temperatura Grove se puede conectar a la Raspberry Pi.

#### Tarea

Conecta el sensor de temperatura.

![Un sensor de temperatura Grove](../../../../../translated_images/es/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Inserta un extremo de un cable Grove en el conector del sensor de humedad y temperatura. Solo encajará de una manera.

1. Con la Raspberry Pi apagada, conecta el otro extremo del cable Grove al conector digital marcado como **D5** en el Grove Base Hat conectado a la Pi. Este conector es el segundo desde la izquierda, en la fila de conectores junto a los pines GPIO.

![El sensor de temperatura Grove conectado al conector A0](../../../../../translated_images/es/pi-temperature-sensor.3ff82fff672c8e565ef25a39d26d111de006b825a7e0867227ef4e7fbff8553c.png)

## Programar el sensor de temperatura

Ahora se puede programar el dispositivo para usar el sensor de temperatura conectado.

### Tarea

Programa el dispositivo.

1. Enciende la Raspberry Pi y espera a que inicie.

1. Abre VS Code, ya sea directamente en la Pi o conectándote a través de la extensión Remote SSH.

    > ⚠️ Puedes consultar [las instrucciones para configurar y abrir VS Code en la lección 1 si es necesario](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Desde el terminal, crea una nueva carpeta en el directorio de inicio del usuario `pi` llamada `temperature-sensor`. Crea un archivo en esta carpeta llamado `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Abre esta carpeta en VS Code.

1. Para usar el sensor de temperatura y humedad, es necesario instalar un paquete adicional de Pip. Desde el terminal en VS Code, ejecuta el siguiente comando para instalar este paquete en la Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Agrega el siguiente código al archivo `app.py` para importar las bibliotecas necesarias:

    ```python
    import time
    from seeed_dht import DHT
    ```

    La instrucción `from seeed_dht import DHT` importa la clase `DHT` para interactuar con un sensor de temperatura Grove desde el módulo `seeed_dht`.

1. Agrega el siguiente código después del anterior para crear una instancia de la clase que gestiona el sensor de temperatura:

    ```python
    sensor = DHT("11", 5)
    ```

    Esto declara una instancia de la clase `DHT` que gestiona el sensor de **H**umedad y **T**emperatura **D**igital. El primer parámetro indica que el sensor utilizado es el *DHT11* (la biblioteca que estás usando admite otras variantes de este sensor). El segundo parámetro indica que el sensor está conectado al puerto digital `D5` en el Grove Base Hat.

    > ✅ Recuerda, todos los conectores tienen números de pines únicos. Los pines 0, 2, 4 y 6 son pines analógicos, mientras que los pines 5, 16, 18, 22, 24 y 26 son pines digitales.

1. Agrega un bucle infinito después del código anterior para consultar el valor del sensor de temperatura y mostrarlo en la consola:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    La llamada a `sensor.read()` devuelve una tupla con la humedad y la temperatura. Solo necesitas el valor de la temperatura, por lo que se ignora la humedad. El valor de la temperatura se imprime en la consola.

1. Agrega una pequeña pausa de diez segundos al final del `loop`, ya que no es necesario verificar los niveles de temperatura continuamente. Una pausa reduce el consumo de energía del dispositivo.

    ```python
    time.sleep(10)
    ```

1. Desde el terminal de VS Code, ejecuta lo siguiente para ejecutar tu aplicación en Python:

    ```sh
    python3 app.py
    ```

    Deberías ver los valores de temperatura en la consola. Usa algo para calentar el sensor, como presionar tu pulgar sobre él o usar un ventilador, para observar cómo cambian los valores:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Puedes encontrar este código en la carpeta [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 ¡Tu programa del sensor de temperatura fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.