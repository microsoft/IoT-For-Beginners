<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-26T14:01:32+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "es"
}
-->
# Verificar inventario desde un dispositivo IoT

![Una vista general en sketchnote de esta lección](../../../../../translated_images/es/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.jpg)

> Sketchnote por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Introducción

En la lección anterior aprendiste sobre los diferentes usos de la detección de objetos en el comercio minorista. También aprendiste cómo entrenar un detector de objetos para identificar inventario. En esta lección aprenderás cómo usar tu detector de objetos desde tu dispositivo IoT para contar inventario.

En esta lección cubriremos:

* [Conteo de inventario](../../../../../5-retail/lessons/2-check-stock-device)
* [Llamar a tu detector de objetos desde tu dispositivo IoT](../../../../../5-retail/lessons/2-check-stock-device)
* [Cajas delimitadoras](../../../../../5-retail/lessons/2-check-stock-device)
* [Reentrenar el modelo](../../../../../5-retail/lessons/2-check-stock-device)
* [Contar inventario](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Esta es la última lección de este proyecto, así que después de completar esta lección y la tarea, no olvides limpiar tus servicios en la nube. Necesitarás los servicios para completar la tarea, así que asegúrate de hacerlo primero.
>
> Consulta [la guía para limpiar tu proyecto](../../../clean-up.md) si necesitas instrucciones sobre cómo hacerlo.

## Conteo de inventario

Los detectores de objetos pueden ser utilizados para verificar inventario, ya sea contando productos o asegurándose de que estén donde deberían estar. Los dispositivos IoT con cámaras pueden ser desplegados por toda la tienda para monitorear inventario, comenzando por áreas clave donde es importante reabastecer productos, como zonas donde se almacenan pocos artículos de alto valor.

Por ejemplo, si una cámara apunta a un conjunto de estantes que pueden contener 8 latas de pasta de tomate, y un detector de objetos solo detecta 7 latas, entonces falta una y necesita ser reabastecida.

![7 latas de pasta de tomate en un estante, 4 en la fila superior, 3 en la inferior](../../../../../translated_images/es/stock-7-cans-tomato-paste.f86059cc573d7bec.webp)

En la imagen anterior, un detector de objetos ha detectado 7 latas de pasta de tomate en un estante que puede contener 8 latas. No solo puede el dispositivo IoT enviar una notificación de la necesidad de reabastecer, sino que incluso puede dar una indicación de la ubicación del artículo faltante, información importante si estás utilizando robots para reabastecer estantes.

> 💁 Dependiendo de la tienda y la popularidad del artículo, probablemente no se reabastecería si solo falta 1 lata. Necesitarías construir un algoritmo que determine cuándo reabastecer basado en tus productos, clientes y otros criterios.

✅ ¿En qué otros escenarios podrías combinar detección de objetos y robots?

A veces el inventario incorrecto puede estar en los estantes. Esto podría ser un error humano al reabastecer, o clientes cambiando de opinión sobre una compra y colocando un artículo en el primer espacio disponible. Cuando se trata de un artículo no perecedero como productos enlatados, esto es una molestia. Si es un artículo perecedero como productos congelados o refrigerados, esto puede significar que el producto ya no puede ser vendido, ya que podría ser imposible determinar cuánto tiempo estuvo fuera del congelador.

La detección de objetos puede ser utilizada para detectar artículos inesperados, alertando nuevamente a un humano o robot para devolver el artículo tan pronto como sea detectado.

![Una lata de maíz bebé fuera de lugar en el estante de pasta de tomate](../../../../../translated_images/es/stock-rogue-corn.be1f3ada8c457854.webp)

En la imagen anterior, una lata de maíz bebé ha sido colocada en el estante junto a la pasta de tomate. El detector de objetos ha detectado esto, permitiendo que el dispositivo IoT notifique a un humano o robot para devolver la lata a su ubicación correcta.

## Llamar a tu detector de objetos desde tu dispositivo IoT

El detector de objetos que entrenaste en la última lección puede ser llamado desde tu dispositivo IoT.

### Tarea - publicar una iteración de tu detector de objetos

Las iteraciones se publican desde el portal de Custom Vision.

1. Abre el portal de Custom Vision en [CustomVision.ai](https://customvision.ai) e inicia sesión si no lo tienes abierto ya. Luego abre tu proyecto `stock-detector`.

1. Selecciona la pestaña **Performance** de las opciones en la parte superior.

1. Selecciona la última iteración de la lista *Iterations* en el lado.

1. Haz clic en el botón **Publish** para la iteración.

    ![El botón de publicar](../../../../../translated_images/es/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.png)

1. En el cuadro de diálogo *Publish Model*, configura el *Prediction resource* al recurso `stock-detector-prediction` que creaste en la última lección. Deja el nombre como `Iteration2`, y selecciona el botón **Publish**.

1. Una vez publicado, selecciona el botón **Prediction URL**. Esto mostrará detalles de la API de predicción, y necesitarás estos para llamar al modelo desde tu dispositivo IoT. La sección inferior está etiquetada como *If you have an image file*, y estos son los detalles que necesitas. Toma una copia de la URL que se muestra, que será algo como:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Donde `<location>` será la ubicación que usaste al crear tu recurso de Custom Vision, y `<id>` será un ID largo compuesto de letras y números.

    También toma una copia del valor *Prediction-Key*. Esta es una clave segura que debes pasar cuando llames al modelo. Solo las aplicaciones que pasen esta clave pueden usar el modelo, cualquier otra aplicación será rechazada.

    ![El cuadro de diálogo de la API de predicción mostrando la URL y la clave](../../../../../translated_images/es/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Cuando se publica una nueva iteración, tendrá un nombre diferente. ¿Cómo crees que podrías cambiar la iteración que está utilizando un dispositivo IoT?

### Tarea - llamar a tu detector de objetos desde tu dispositivo IoT

Sigue la guía relevante a continuación para usar el detector de objetos desde tu dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Computadora de placa única - Raspberry Pi/Dispositivo virtual](single-board-computer-object-detector.md)

## Cajas delimitadoras

Cuando usas el detector de objetos, no solo obtienes los objetos detectados con sus etiquetas y probabilidades, sino que también obtienes las cajas delimitadoras de los objetos. Estas definen dónde el detector de objetos detectó el objeto con la probabilidad dada.

> 💁 Una caja delimitadora es un cuadro que define el área que contiene el objeto detectado, un cuadro que define el límite para el objeto.

Los resultados de una predicción en la pestaña **Predictions** en Custom Vision tienen las cajas delimitadoras dibujadas en la imagen que se envió para la predicción.

![4 latas de pasta de tomate en un estante con predicciones para las 4 detecciones de 35.8%, 33.5%, 25.7% y 16.6%](../../../../../translated_images/es/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

En la imagen anterior, se detectaron 4 latas de pasta de tomate. En los resultados, se superpone un cuadro rojo para cada objeto que fue detectado en la imagen, indicando la caja delimitadora para la imagen.

✅ Abre las predicciones en Custom Vision y revisa las cajas delimitadoras.

Las cajas delimitadoras se definen con 4 valores: top, left, height y width. Estos valores están en una escala de 0-1, representando las posiciones como un porcentaje del tamaño de la imagen. El origen (la posición 0,0) es la esquina superior izquierda de la imagen, por lo que el valor top es la distancia desde la parte superior, y la parte inferior de la caja delimitadora es el top más la height.

![Una caja delimitadora alrededor de una lata de pasta de tomate](../../../../../translated_images/es/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.png)

La imagen anterior tiene 600 píxeles de ancho y 800 píxeles de alto. La caja delimitadora comienza a 320 píxeles hacia abajo, dando un valor top de 0.4 (800 x 0.4 = 320). Desde la izquierda, la caja delimitadora comienza a 240 píxeles hacia adentro, dando un valor left de 0.4 (600 x 0.4 = 240). La altura de la caja delimitadora es de 240 píxeles, dando un valor height de 0.3 (800 x 0.3 = 240). El ancho de la caja delimitadora es de 120 píxeles, dando un valor width de 0.2 (600 x 0.2 = 120).

| Coordenada | Valor |
| ---------- | ----: |
| Top        | 0.4   |
| Left       | 0.4   |
| Height     | 0.3   |
| Width      | 0.2   |

Usar valores porcentuales de 0-1 significa que, sin importar el tamaño al que se escale la imagen, la caja delimitadora comienza a 0.4 de la distancia hacia abajo y hacia adentro, y tiene un 0.3 de la altura y un 0.2 del ancho.

Puedes usar las cajas delimitadoras combinadas con las probabilidades para evaluar qué tan precisa es una detección. Por ejemplo, un detector de objetos puede detectar múltiples objetos que se superponen, por ejemplo, detectando una lata dentro de otra. Tu código podría revisar las cajas delimitadoras, entender que esto es imposible, y ignorar cualquier objeto que tenga una superposición significativa con otros objetos.

![Dos cajas delimitadoras superpuestas en una lata de pasta de tomate](../../../../../translated_images/es/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.png)

En el ejemplo anterior, una caja delimitadora indicó una lata de pasta de tomate predicha con un 78.3%. Una segunda caja delimitadora es ligeramente más pequeña y está dentro de la primera caja delimitadora con una probabilidad de 64.3%. Tu código puede revisar las cajas delimitadoras, ver que se superponen completamente, e ignorar la probabilidad más baja ya que no hay forma de que una lata esté dentro de otra.

✅ ¿Puedes pensar en una situación donde sea válido detectar un objeto dentro de otro?

## Reentrenar el modelo

Al igual que con el clasificador de imágenes, puedes reentrenar tu modelo usando datos capturados por tu dispositivo IoT. Usar estos datos del mundo real asegurará que tu modelo funcione bien cuando se use desde tu dispositivo IoT.

A diferencia del clasificador de imágenes, no puedes simplemente etiquetar una imagen. En cambio, necesitas revisar cada caja delimitadora detectada por el modelo. Si la caja está alrededor de algo incorrecto, necesita ser eliminada; si está en la ubicación incorrecta, necesita ser ajustada.

### Tarea - reentrenar el modelo

1. Asegúrate de haber capturado una variedad de imágenes usando tu dispositivo IoT.

1. Desde la pestaña **Predictions**, selecciona una imagen. Verás cuadros rojos que indican las cajas delimitadoras de los objetos detectados.

1. Revisa cada caja delimitadora. Selecciónala primero y verás un cuadro emergente mostrando la etiqueta. Usa los manejadores en las esquinas de la caja delimitadora para ajustar el tamaño si es necesario. Si la etiqueta es incorrecta, elimínala con el botón **X** y agrega la etiqueta correcta. Si la caja delimitadora no contiene un objeto, elimínala con el botón de la papelera.

1. Cierra el editor cuando termines y la imagen se moverá de la pestaña **Predictions** a la pestaña **Training Images**. Repite el proceso para todas las predicciones.

1. Usa el botón **Train** para reentrenar tu modelo. Una vez que se haya entrenado, publica la iteración y actualiza tu dispositivo IoT para usar la URL de la nueva iteración.

1. Vuelve a desplegar tu código y prueba tu dispositivo IoT.

## Contar inventario

Usando una combinación del número de objetos detectados y las cajas delimitadoras, puedes contar el inventario en un estante.

### Tarea - contar inventario

Sigue la guía relevante a continuación para contar inventario usando los resultados del detector de objetos desde tu dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Computadora de placa única - Raspberry Pi/Dispositivo virtual](single-board-computer-count-stock.md)

---

## 🚀 Desafío

¿Puedes detectar inventario incorrecto? Entrena tu modelo con múltiples objetos, luego actualiza tu aplicación para alertarte si se detecta el inventario incorrecto.

Tal vez incluso lleva esto más allá y detecta inventario lado a lado en el mismo estante, y verifica si algo ha sido colocado en el lugar incorrecto definiendo límites en las cajas delimitadoras.

## Cuestionario posterior a la lección

[Cuestionario posterior a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Revisión y autoestudio

* Aprende más sobre cómo diseñar un sistema de detección de inventario de extremo a extremo en la guía de patrones [Detección de falta de inventario en el borde en Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Aprende otras formas de construir soluciones de comercio minorista de extremo a extremo combinando una variedad de servicios IoT y en la nube viendo este [Detrás de escena de una solución de comercio minorista - ¡Manos a la obra! video en YouTube](https://www.youtube.com/watch?v=m3Pc300x2Mw).

## Tarea

[Usa tu detector de objetos en el borde](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.