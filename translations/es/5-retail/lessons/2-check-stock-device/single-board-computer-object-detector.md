<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-26T14:00:02+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "es"
}
-->
# Llama a tu detector de objetos desde tu dispositivo IoT - Hardware IoT Virtual y Raspberry Pi

Una vez que tu detector de objetos haya sido publicado, podrá ser utilizado desde tu dispositivo IoT.

## Copia el proyecto del clasificador de imágenes

La mayor parte de tu detector de inventario es similar al clasificador de imágenes que creaste en una lección anterior.

### Tarea - copia el proyecto del clasificador de imágenes

1. Crea una carpeta llamada `stock-counter` en tu computadora si estás usando un dispositivo IoT virtual, o en tu Raspberry Pi. Si estás usando un dispositivo IoT virtual, asegúrate de configurar un entorno virtual.

1. Configura el hardware de la cámara.

    * Si estás usando una Raspberry Pi, necesitarás instalar la PiCamera. También podrías querer fijar la cámara en una posición estable, por ejemplo, colgando el cable sobre una caja o lata, o fijando la cámara a una caja con cinta adhesiva de doble cara.
    * Si estás usando un dispositivo IoT virtual, necesitarás instalar CounterFit y el shim CounterFit PyCamera. Si vas a usar imágenes fijas, captura algunas imágenes que tu detector de objetos no haya visto antes. Si vas a usar tu cámara web, asegúrate de que esté posicionada de manera que pueda ver el inventario que estás detectando.

1. Repite los pasos de [la lección 2 del proyecto de manufactura](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) para capturar imágenes desde la cámara.

1. Repite los pasos de [la lección 2 del proyecto de manufactura](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) para llamar al clasificador de imágenes. La mayor parte de este código será reutilizado para detectar objetos.

## Cambia el código de un clasificador a un detector de imágenes

El código que usaste para clasificar imágenes es muy similar al código para detectar objetos. La principal diferencia es el método llamado en el SDK de Custom Vision y los resultados de la llamada.

### Tarea - cambia el código de un clasificador a un detector de imágenes

1. Elimina las tres líneas de código que clasifican la imagen y procesan las predicciones:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Elimina estas tres líneas.

1. Agrega el siguiente código para detectar objetos en la imagen:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Este código llama al método `detect_image` en el predictor para ejecutar el detector de objetos. Luego reúne todas las predicciones con una probabilidad por encima de un umbral, imprimiéndolas en la consola.

    A diferencia de un clasificador de imágenes que solo devuelve un resultado por etiqueta, el detector de objetos devolverá múltiples resultados, por lo que es necesario filtrar aquellos con una probabilidad baja.

1. Ejecuta este código y capturará una imagen, la enviará al detector de objetos y mostrará los objetos detectados. Si estás usando un dispositivo IoT virtual, asegúrate de tener una imagen adecuada configurada en CounterFit o que tu cámara web esté seleccionada. Si estás usando una Raspberry Pi, asegúrate de que tu cámara esté apuntando a los objetos en un estante.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Es posible que necesites ajustar el `threshold` a un valor adecuado para tus imágenes.

    Podrás ver la imagen que se tomó y estos valores en la pestaña **Predictions** en Custom Vision.

    ![4 latas de pasta de tomate en un estante con predicciones para las 4 detecciones de 35.8%, 33.5%, 25.7% y 16.6%](../../../../../translated_images/es/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Puedes encontrar este código en la carpeta [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) o [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 ¡Tu programa de contador de inventario fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.