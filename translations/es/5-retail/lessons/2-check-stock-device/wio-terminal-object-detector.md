# Llama a tu detector de objetos desde tu dispositivo IoT - Wio Terminal

Una vez que tu detector de objetos haya sido publicado, puede ser utilizado desde tu dispositivo IoT.

## Copia el proyecto del clasificador de imágenes

La mayor parte de tu detector de inventario es igual al clasificador de imágenes que creaste en una lección anterior.

### Tarea - copia el proyecto del clasificador de imágenes

1. Conecta tu ArduCam a tu Wio Terminal, siguiendo los pasos de [la lección 2 del proyecto de manufactura](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    También podrías querer fijar la cámara en una posición estable, por ejemplo, colgando el cable sobre una caja o lata, o fijando la cámara a una caja con cinta adhesiva de doble cara.

1. Crea un proyecto nuevo para Wio Terminal usando PlatformIO. Llama a este proyecto `stock-counter`.

1. Repite los pasos de [la lección 2 del proyecto de manufactura](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) para capturar imágenes desde la cámara.

1. Repite los pasos de [la lección 2 del proyecto de manufactura](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) para llamar al clasificador de imágenes. La mayor parte de este código será reutilizado para detectar objetos.

## Cambia el código de un clasificador a un detector de imágenes

El código que usaste para clasificar imágenes es muy similar al código para detectar objetos. La principal diferencia es la URL que se llama, que obtuviste de Custom Vision, y los resultados de la llamada.

### Tarea - cambia el código de un clasificador a un detector de imágenes

1. Agrega la siguiente directiva de inclusión al inicio del archivo `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Renombra la función `classifyImage` a `detectStock`, tanto el nombre de la función como la llamada en la función `buttonPressed`.

1. Encima de la función `detectStock`, declara un umbral para filtrar cualquier detección que tenga una baja probabilidad:

    ```cpp
    const float threshold = 0.3f;
    ```

    A diferencia de un clasificador de imágenes que solo devuelve un resultado por etiqueta, el detector de objetos devolverá múltiples resultados, por lo que cualquier resultado con baja probabilidad debe ser filtrado.

1. Encima de la función `detectStock`, declara una función para procesar las predicciones:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    Esto toma una lista de predicciones y las imprime en el monitor serial.

1. En la función `detectStock`, reemplaza el contenido del bucle `for` que recorre las predicciones con lo siguiente:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    Esto recorre las predicciones, comparando la probabilidad con el umbral. Todas las predicciones que tienen una probabilidad mayor que el umbral se agregan a una `list` y se pasan a la función `processPredictions`.

1. Sube y ejecuta tu código. Apunta la cámara hacia objetos en una estantería y presiona el botón C. Verás la salida en el monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 Puede que necesites ajustar el `threshold` a un valor apropiado para tus imágenes.

    Podrás ver la imagen que se tomó y estos valores en la pestaña **Predictions** en Custom Vision.

    ![4 latas de pasta de tomate en una estantería con predicciones para las 4 detecciones de 35.8%, 33.5%, 25.7% y 16.6%](../../../../../translated_images/es/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Puedes encontrar este código en la carpeta [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 ¡Tu programa de contador de inventario fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de ningún malentendido o interpretación errónea que surja del uso de esta traducción.