<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-26T14:02:47+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "es"
}
-->
# Contar inventario desde tu dispositivo IoT - Wio Terminal

Una combinación de las predicciones y sus cuadros delimitadores puede ser utilizada para contar inventario en una imagen.

## Contar inventario

![4 latas de pasta de tomate con cuadros delimitadores alrededor de cada lata](../../../../../translated_images/es/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

En la imagen mostrada arriba, los cuadros delimitadores tienen un pequeño solapamiento. Si este solapamiento fuera mucho mayor, entonces los cuadros delimitadores podrían indicar el mismo objeto. Para contar los objetos correctamente, necesitas ignorar los cuadros con un solapamiento significativo.

### Tarea - contar inventario ignorando solapamientos

1. Abre tu proyecto `stock-counter` si no está abierto ya.

1. Encima de la función `processPredictions`, agrega el siguiente código:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Esto define el porcentaje de solapamiento permitido antes de que los cuadros delimitadores sean considerados como el mismo objeto. 0.20 define un solapamiento del 20%.

1. Debajo de esto, y encima de la función `processPredictions`, agrega el siguiente código para calcular el solapamiento entre dos rectángulos:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    Este código define una estructura `Point` para almacenar puntos en la imagen, y una estructura `Rect` para definir un rectángulo usando una coordenada superior izquierda y una inferior derecha. Luego define una función `area` que calcula el área de un rectángulo a partir de una coordenada superior izquierda e inferior derecha.

    A continuación, define una función `overlappingArea` que calcula el área de solapamiento de 2 rectángulos. Si no se solapan, devuelve 0.

1. Debajo de la función `overlappingArea`, declara una función para convertir un cuadro delimitador en un `Rect`:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    Esto toma una predicción del detector de objetos, extrae el cuadro delimitador y utiliza los valores del cuadro delimitador para definir un rectángulo. El lado derecho se calcula sumando el ancho al lado izquierdo. La parte inferior se calcula sumando la altura a la parte superior.

1. Las predicciones necesitan ser comparadas entre sí, y si 2 predicciones tienen un solapamiento mayor al umbral, una de ellas debe ser eliminada. El umbral de solapamiento es un porcentaje, por lo que necesita ser multiplicado por el tamaño del cuadro delimitador más pequeño para verificar que el solapamiento exceda el porcentaje dado del cuadro delimitador, no el porcentaje dado de toda la imagen. Comienza eliminando el contenido de la función `processPredictions`.

1. Agrega lo siguiente a la función `processPredictions` vacía:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    Este código declara un vector para almacenar las predicciones que no se solapan. Luego recorre todas las predicciones, creando un `Rect` a partir del cuadro delimitador.

    A continuación, este código recorre las predicciones restantes, comenzando con la que está después de la predicción actual. Esto evita que las predicciones sean comparadas más de una vez: una vez que se han comparado 1 y 2, no hay necesidad de comparar 2 con 1, solo con 3, 4, etc.

    Para cada par de predicciones, se calcula el área de solapamiento. Esto se compara con el área del cuadro delimitador más pequeño: si el solapamiento excede el porcentaje umbral del cuadro delimitador más pequeño, la predicción se marca como no aprobada. Si después de comparar todos los solapamientos, la predicción pasa las verificaciones, se agrega a la colección `passed_predictions`.

    > 💁 Este es un método muy simplista para eliminar solapamientos, simplemente eliminando el primero en un par de solapamientos. Para código de producción, querrías agregar más lógica aquí, como considerar los solapamientos entre múltiples objetos, o si un cuadro delimitador está contenido dentro de otro.

1. Después de esto, agrega el siguiente código para enviar detalles de las predicciones aprobadas al monitor serial:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    Este código recorre las predicciones aprobadas y imprime sus detalles en el monitor serial.

1. Debajo de esto, agrega código para imprimir el número de elementos contados en el monitor serial:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Esto podría ser enviado a un servicio IoT para alertar si los niveles de inventario son bajos.

1. Sube y ejecuta tu código. Apunta la cámara a objetos en un estante y presiona el botón C. Intenta ajustar el valor de `overlap_threshold` para ver cómo se ignoran las predicciones.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 Puedes encontrar este código en la carpeta [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 ¡Tu programa para contar inventario fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.