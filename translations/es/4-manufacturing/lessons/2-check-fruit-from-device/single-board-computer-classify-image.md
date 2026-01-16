<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-26T14:11:56+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "es"
}
-->
# Clasificar una imagen - Hardware IoT Virtual y Raspberry Pi

En esta parte de la lección, enviarás la imagen capturada por la cámara al servicio Custom Vision para clasificarla.

## Enviar imágenes a Custom Vision

El servicio Custom Vision tiene un SDK de Python que puedes usar para clasificar imágenes.

### Tarea - enviar imágenes a Custom Vision

1. Abre la carpeta `fruit-quality-detector` en VS Code. Si estás utilizando un dispositivo IoT virtual, asegúrate de que el entorno virtual esté ejecutándose en la terminal.

1. El SDK de Python para enviar imágenes a Custom Vision está disponible como un paquete de Pip. Instálalo con el siguiente comando:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Agrega las siguientes declaraciones de importación en la parte superior del archivo `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Esto incluye algunos módulos de las bibliotecas de Custom Vision, uno para autenticar con la clave de predicción y otro para proporcionar una clase cliente de predicción que puede llamar a Custom Vision.

1. Agrega el siguiente código al final del archivo:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Reemplaza `<prediction_url>` con la URL que copiaste del cuadro de diálogo *Prediction URL* anteriormente en esta lección. Reemplaza `<prediction key>` con la clave de predicción que copiaste del mismo cuadro de diálogo.

1. La URL de predicción proporcionada por el cuadro de diálogo *Prediction URL* está diseñada para ser utilizada al llamar directamente al endpoint REST. El SDK de Python utiliza partes de la URL en diferentes lugares. Agrega el siguiente código para descomponer esta URL en las partes necesarias:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Esto divide la URL, extrayendo el endpoint de `https://<location>.api.cognitive.microsoft.com`, el ID del proyecto y el nombre de la iteración publicada.

1. Crea un objeto predictor para realizar la predicción con el siguiente código:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    Las `prediction_credentials` envuelven la clave de predicción. Estas se utilizan para crear un objeto cliente de predicción que apunta al endpoint.

1. Envía la imagen a Custom Vision utilizando el siguiente código:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Esto rebobina la imagen al inicio y luego la envía al cliente de predicción.

1. Finalmente, muestra los resultados con el siguiente código:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Esto recorrerá todas las predicciones que se han devuelto y las mostrará en la terminal. Las probabilidades devueltas son números de punto flotante entre 0 y 1, donde 0 representa un 0% de probabilidad de coincidir con la etiqueta, y 1 representa un 100% de probabilidad.

    > 💁 Los clasificadores de imágenes devolverán los porcentajes para todas las etiquetas que se hayan utilizado. Cada etiqueta tendrá una probabilidad de que la imagen coincida con esa etiqueta.

1. Ejecuta tu código, con tu cámara apuntando a alguna fruta, o un conjunto de imágenes apropiado, o fruta visible en tu cámara web si estás utilizando hardware IoT virtual. Verás la salida en la consola:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Podrás ver la imagen que se tomó y estos valores en la pestaña **Predictions** en Custom Vision.

    ![Un plátano en Custom Vision predicho como maduro al 56.8% y no maduro al 43.1%](../../../../../translated_images/es/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Puedes encontrar este código en la carpeta [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) o [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 ¡Tu programa clasificador de calidad de frutas fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por lograr precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.