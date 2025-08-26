<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-26T14:20:54+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "es"
}
-->
# Clasificar una imagen usando un clasificador de imágenes basado en IoT Edge - Hardware IoT Virtual y Raspberry Pi

En esta parte de la lección, usarás el clasificador de imágenes que se ejecuta en el dispositivo IoT Edge.

## Usar el clasificador de IoT Edge

El dispositivo IoT puede ser redirigido para usar el clasificador de imágenes de IoT Edge. La URL para el clasificador de imágenes es `http://<IP address or name>/image`, reemplazando `<IP address or name>` con la dirección IP o el nombre del host del ordenador que ejecuta IoT Edge.

La biblioteca de Python para Custom Vision solo funciona con modelos alojados en la nube, no con modelos alojados en IoT Edge. Esto significa que necesitarás usar la API REST para llamar al clasificador.

### Tarea - usar el clasificador de IoT Edge

1. Abre el proyecto `fruit-quality-detector` en VS Code si aún no está abierto. Si estás usando un dispositivo IoT virtual, asegúrate de que el entorno virtual esté activado.

1. Abre el archivo `app.py` y elimina las declaraciones de importación de `azure.cognitiveservices.vision.customvision.prediction` y `msrest.authentication`.

1. Agrega la siguiente importación al inicio del archivo:

    ```python
    import requests
    ```

1. Elimina todo el código después de que la imagen se guarda en un archivo, desde `image_file.write(image.read())` hasta el final del archivo.

1. Agrega el siguiente código al final del archivo:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Reemplaza `<URL>` con la URL de tu clasificador.

    Este código realiza una solicitud POST REST al clasificador, enviando la imagen como el cuerpo de la solicitud. Los resultados regresan como JSON, y este se decodifica para imprimir las probabilidades.

1. Ejecuta tu código, con tu cámara apuntando a alguna fruta, o un conjunto de imágenes apropiado, o fruta visible en tu cámara web si estás usando hardware IoT virtual. Verás la salida en la consola:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Puedes encontrar este código en la carpeta [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) o [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 ¡Tu programa clasificador de calidad de frutas fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.