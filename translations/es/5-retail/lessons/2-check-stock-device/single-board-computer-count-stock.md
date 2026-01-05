<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-26T14:03:27+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "es"
}
-->
# Contar inventario desde tu dispositivo IoT - Hardware IoT Virtual y Raspberry Pi

Una combinación de las predicciones y sus cuadros delimitadores puede ser utilizada para contar inventario en una imagen.

## Mostrar cuadros delimitadores

Como un paso útil de depuración, no solo puedes imprimir los cuadros delimitadores, sino también dibujarlos en la imagen que se guardó en el disco cuando se capturó una imagen.

### Tarea - imprimir los cuadros delimitadores

1. Asegúrate de que el proyecto `stock-counter` esté abierto en VS Code y que el entorno virtual esté activado si estás utilizando un dispositivo IoT virtual.

1. Cambia la declaración `print` en el bucle `for` por la siguiente para imprimir los cuadros delimitadores en la consola:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Ejecuta la aplicación con la cámara apuntando a algún inventario en un estante. Los cuadros delimitadores se imprimirán en la consola, con valores de izquierda, arriba, ancho y alto entre 0 y 1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Tarea - dibujar cuadros delimitadores en la imagen

1. El paquete Pip [Pillow](https://pypi.org/project/Pillow/) puede ser utilizado para dibujar en imágenes. Instálalo con el siguiente comando:

    ```sh
    pip3 install pillow
    ```

    Si estás utilizando un dispositivo IoT virtual, asegúrate de ejecutar esto desde dentro del entorno virtual activado.

1. Agrega la siguiente declaración de importación al inicio del archivo `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Esto importa el código necesario para editar la imagen.

1. Agrega el siguiente código al final del archivo `app.py`:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    Este código abre la imagen que se guardó anteriormente para editarla. Luego, recorre las predicciones obteniendo los cuadros delimitadores y calcula la coordenada inferior derecha utilizando los valores del cuadro delimitador entre 0 y 1. Estos valores se convierten en coordenadas de la imagen multiplicándolos por la dimensión correspondiente de la imagen. Por ejemplo, si el valor izquierdo es 0.5 en una imagen de 600 píxeles de ancho, esto se convertiría en 300 (0.5 x 600 = 300).

    Cada cuadro delimitador se dibuja en la imagen utilizando una línea roja. Finalmente, la imagen editada se guarda, sobrescribiendo la imagen original.

1. Ejecuta la aplicación con la cámara apuntando a algún inventario en un estante. Verás el archivo `image.jpg` en el explorador de VS Code y podrás seleccionarlo para ver los cuadros delimitadores.

    ![4 latas de pasta de tomate con cuadros delimitadores alrededor de cada lata](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.es.jpg)

## Contar inventario

En la imagen mostrada arriba, los cuadros delimitadores tienen un pequeño solapamiento. Si este solapamiento fuera mucho mayor, entonces los cuadros delimitadores podrían indicar el mismo objeto. Para contar los objetos correctamente, necesitas ignorar los cuadros con un solapamiento significativo.

### Tarea - contar inventario ignorando solapamientos

1. El paquete Pip [Shapely](https://pypi.org/project/Shapely/) puede ser utilizado para calcular la intersección. Si estás utilizando un Raspberry Pi, primero necesitarás instalar una dependencia de biblioteca:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Instala el paquete Pip Shapely:

    ```sh
    pip3 install shapely
    ```

    Si estás utilizando un dispositivo IoT virtual, asegúrate de ejecutar esto desde dentro del entorno virtual activado.

1. Agrega la siguiente declaración de importación al inicio del archivo `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Esto importa el código necesario para crear polígonos y calcular solapamientos.

1. Por encima del código que dibuja los cuadros delimitadores, agrega el siguiente código:

    ```python
    overlap_threshold = 0.20
    ```

    Esto define el porcentaje de solapamiento permitido antes de que los cuadros delimitadores sean considerados como el mismo objeto. 0.20 define un solapamiento del 20%.

1. Para calcular el solapamiento utilizando Shapely, los cuadros delimitadores necesitan ser convertidos en polígonos de Shapely. Agrega la siguiente función para hacerlo:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Esto crea un polígono utilizando el cuadro delimitador de una predicción.

1. La lógica para eliminar objetos solapados implica comparar todos los cuadros delimitadores y, si algún par de predicciones tiene cuadros delimitadores que se solapan más allá del umbral, eliminar una de las predicciones. Para comparar todas las predicciones, comparas la predicción 1 con la 2, 3, 4, etc., luego la 2 con la 3, 4, etc. El siguiente código hace esto:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    El solapamiento se calcula utilizando el método `Polygon.intersection` de Shapely, que devuelve un polígono que tiene el solapamiento. El área se calcula a partir de este polígono. Este umbral de solapamiento no es un valor absoluto, sino que necesita ser un porcentaje del cuadro delimitador, por lo que se encuentra el cuadro delimitador más pequeño y se utiliza el umbral de solapamiento para calcular qué área puede tener el solapamiento sin exceder el porcentaje de solapamiento del cuadro delimitador más pequeño. Si el solapamiento excede esto, la predicción se marca para eliminación.

    Una vez que una predicción ha sido marcada para eliminación, no necesita ser revisada nuevamente, por lo que el bucle interno se rompe para revisar la siguiente predicción. No puedes eliminar elementos de una lista mientras iteras sobre ella, por lo que los cuadros delimitadores que se solapan más allá del umbral se agregan a la lista `to_delete` y luego se eliminan al final.

    Finalmente, el conteo de inventario se imprime en la consola. Esto podría ser enviado a un servicio IoT para alertar si los niveles de inventario son bajos. Todo este código está antes de que se dibujen los cuadros delimitadores, por lo que verás las predicciones de inventario sin solapamientos en las imágenes generadas.

    > 💁 Esta es una forma muy simplista de eliminar solapamientos, simplemente eliminando el primero en un par solapado. Para código de producción, querrías agregar más lógica aquí, como considerar los solapamientos entre múltiples objetos o si un cuadro delimitador está contenido dentro de otro.

1. Ejecuta la aplicación con la cámara apuntando a algún inventario en un estante. La salida indicará el número de cuadros delimitadores sin solapamientos que excedan el umbral. Prueba ajustando el valor de `overlap_threshold` para ver cómo se ignoran las predicciones.

> 💁 Puedes encontrar este código en la carpeta [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) o [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 ¡Tu programa contador de inventario fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.