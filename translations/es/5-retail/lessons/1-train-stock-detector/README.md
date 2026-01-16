<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8df310a42f902139a01417dacb1ffbef",
  "translation_date": "2025-08-26T14:05:26+00:00",
  "source_file": "5-retail/lessons/1-train-stock-detector/README.md",
  "language_code": "es"
}
-->
# Entrena un detector de existencias

![Una vista general ilustrada de esta lección](../../../../../translated_images/es/lesson-19.cf6973cecadf080c4b526310620dc4d6f5994c80fb0139c6f378cc9ca2d435cd.jpg)

> Ilustración por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

Este video ofrece una visión general sobre la detección de objetos con el servicio Azure Custom Vision, un servicio que se cubrirá en esta lección.

[![Custom Vision 2 - Object Detection Made Easy | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Haz clic en la imagen de arriba para ver el video

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Introducción

En el proyecto anterior, utilizaste IA para entrenar un clasificador de imágenes: un modelo que puede determinar si una imagen contiene algo, como fruta madura o inmadura. Otro tipo de modelo de IA que se puede usar con imágenes es la detección de objetos. Estos modelos no clasifican una imagen por etiquetas, sino que están entrenados para reconocer objetos y pueden encontrarlos en imágenes, no solo detectando que el objeto está presente, sino también dónde se encuentra en la imagen. Esto permite contar objetos en imágenes.

En esta lección aprenderás sobre la detección de objetos, incluyendo cómo puede ser utilizada en el comercio minorista. También aprenderás cómo entrenar un detector de objetos en la nube.

En esta lección cubriremos:

* [Detección de objetos](../../../../../5-retail/lessons/1-train-stock-detector)
* [Uso de la detección de objetos en el comercio minorista](../../../../../5-retail/lessons/1-train-stock-detector)
* [Entrenar un detector de objetos](../../../../../5-retail/lessons/1-train-stock-detector)
* [Probar tu detector de objetos](../../../../../5-retail/lessons/1-train-stock-detector)
* [Reentrenar tu detector de objetos](../../../../../5-retail/lessons/1-train-stock-detector)

## Detección de objetos

La detección de objetos implica identificar objetos en imágenes utilizando IA. A diferencia del clasificador de imágenes que entrenaste en el último proyecto, la detección de objetos no se trata de predecir la mejor etiqueta para una imagen en su conjunto, sino de encontrar uno o más objetos en una imagen.

### Detección de objetos vs clasificación de imágenes

La clasificación de imágenes se trata de clasificar una imagen en su totalidad: cuáles son las probabilidades de que toda la imagen coincida con cada etiqueta. Obtienes probabilidades para cada etiqueta utilizada para entrenar el modelo.

![Clasificación de imágenes de nueces de marañón y pasta de tomate](../../../../../translated_images/es/image-classifier-cashews-tomato.bc2e16ab8f05cf9ac0f59f73e32efc4227f9a5b601b90b2c60f436694547a965.png)

En el ejemplo anterior, dos imágenes son clasificadas utilizando un modelo entrenado para clasificar envases de nueces de marañón o latas de pasta de tomate. La primera imagen es un envase de nueces de marañón y tiene dos resultados del clasificador de imágenes:

| Etiqueta         | Probabilidad |
| ---------------- | -----------: |
| `nueces de marañón` | 98.4%       |
| `pasta de tomate`   | 1.6%        |

La segunda imagen es una lata de pasta de tomate, y los resultados son:

| Etiqueta         | Probabilidad |
| ---------------- | -----------: |
| `nueces de marañón` | 0.7%        |
| `pasta de tomate`   | 99.3%       |

Podrías usar estos valores con un porcentaje de umbral para predecir qué hay en la imagen. Pero, ¿qué pasaría si una imagen contuviera múltiples latas de pasta de tomate o tanto nueces de marañón como pasta de tomate? Los resultados probablemente no te darían lo que necesitas. Aquí es donde entra la detección de objetos.

La detección de objetos implica entrenar un modelo para reconocer objetos. En lugar de darle imágenes que contienen el objeto y decirle que cada imagen es una etiqueta u otra, destacas la sección de una imagen que contiene el objeto específico y la etiquetas. Puedes etiquetar un solo objeto en una imagen o varios. De esta manera, el modelo aprende cómo se ve el objeto en sí, no solo cómo se ven las imágenes que contienen el objeto.

Cuando lo usas para predecir imágenes, en lugar de obtener una lista de etiquetas y porcentajes, obtienes una lista de objetos detectados, con su cuadro delimitador y la probabilidad de que el objeto coincida con la etiqueta asignada.

> 🎓 *Cuadros delimitadores* son los cuadros alrededor de un objeto.

![Detección de objetos de nueces de marañón y pasta de tomate](../../../../../translated_images/es/object-detector-cashews-tomato.1af7c26686b4db0e709754aeb196f4e73271f54e2085db3bcccb70d4a0d84d97.png)

La imagen anterior contiene tanto un envase de nueces de marañón como tres latas de pasta de tomate. El detector de objetos detectó las nueces de marañón, devolviendo el cuadro delimitador que contiene las nueces de marañón con el porcentaje de probabilidad de que el cuadro delimitador contenga el objeto, en este caso 97.6%. El detector de objetos también ha detectado tres latas de pasta de tomate y proporciona tres cuadros delimitadores separados, uno para cada lata detectada, y cada uno tiene una probabilidad de que el cuadro delimitador contenga una lata de pasta de tomate.

✅ Piensa en algunos escenarios diferentes en los que podrías querer usar modelos de IA basados en imágenes. ¿Cuáles necesitarían clasificación y cuáles necesitarían detección de objetos?

### Cómo funciona la detección de objetos

La detección de objetos utiliza modelos de aprendizaje automático complejos. Estos modelos funcionan dividiendo la imagen en múltiples celdas y luego verifican si el centro del cuadro delimitador coincide con el centro de una imagen que coincide con una de las imágenes utilizadas para entrenar el modelo. Puedes pensar en esto como una especie de ejecución de un clasificador de imágenes sobre diferentes partes de la imagen para buscar coincidencias.

> 💁 Esto es una simplificación drástica. Existen muchas técnicas para la detección de objetos, y puedes leer más sobre ellas en la [página de detección de objetos en Wikipedia](https://wikipedia.org/wiki/Object_detection).

Hay varios modelos diferentes que pueden realizar detección de objetos. Un modelo particularmente famoso es [YOLO (You only look once)](https://pjreddie.com/darknet/yolo/), que es increíblemente rápido y puede detectar 20 clases diferentes de objetos, como personas, perros, botellas y autos.

✅ Investiga sobre el modelo YOLO en [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/)

Los modelos de detección de objetos pueden ser reentrenados utilizando aprendizaje por transferencia para detectar objetos personalizados.

## Uso de la detección de objetos en el comercio minorista

La detección de objetos tiene múltiples usos en el comercio minorista. Algunos incluyen:

* **Revisión y conteo de existencias** - reconocer cuando las existencias son bajas en los estantes. Si las existencias son demasiado bajas, se pueden enviar notificaciones al personal o a robots para reabastecer los estantes.
* **Detección de mascarillas** - en tiendas con políticas de uso de mascarillas durante eventos de salud pública, la detección de objetos puede reconocer personas con mascarillas y sin ellas.
* **Facturación automatizada** - detectar artículos tomados de los estantes en tiendas automatizadas y facturar a los clientes de manera adecuada.
* **Detección de peligros** - reconocer artículos rotos en el suelo o líquidos derramados, alertando a los equipos de limpieza.

✅ Investiga: ¿Cuáles son algunos otros casos de uso para la detección de objetos en el comercio minorista?

## Entrenar un detector de objetos

Puedes entrenar un detector de objetos utilizando Custom Vision, de manera similar a como entrenaste un clasificador de imágenes.

### Tarea - crear un detector de objetos

1. Crea un grupo de recursos para este proyecto llamado `stock-detector`.

1. Crea un recurso de entrenamiento gratuito de Custom Vision y un recurso de predicción gratuito de Custom Vision en el grupo de recursos `stock-detector`. Nómbralos `stock-detector-training` y `stock-detector-prediction`.

    > 💁 Solo puedes tener un recurso gratuito de entrenamiento y predicción, así que asegúrate de haber limpiado tu proyecto de las lecciones anteriores.

    > ⚠️ Puedes consultar [las instrucciones para crear recursos de entrenamiento y predicción del proyecto 4, lección 1 si es necesario](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. Inicia el portal de Custom Vision en [CustomVision.ai](https://customvision.ai) e inicia sesión con la cuenta de Microsoft que utilizaste para tu cuenta de Azure.

1. Sigue la [sección Crear un nuevo proyecto del inicio rápido para construir un detector de objetos en la documentación de Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project) para crear un nuevo proyecto de Custom Vision. La interfaz de usuario puede cambiar y esta documentación siempre será la referencia más actualizada.

    Llama a tu proyecto `stock-detector`.

    Cuando crees tu proyecto, asegúrate de usar el recurso `stock-detector-training` que creaste anteriormente. Usa el tipo de proyecto *Detección de objetos* y el dominio *Productos en estantes*.

    ![La configuración del proyecto de Custom Vision con el nombre configurado como fruit-quality-detector, sin descripción, el recurso configurado como fruit-quality-detector-training, el tipo de proyecto configurado como clasificación, los tipos de clasificación configurados como multi-clase y los dominios configurados como alimentos](../../../../../translated_images/es/custom-vision-create-object-detector-project.32d4fb9aa8e7e7375f8a799bfce517aca970f2cb65e42d4245c5e635c734ab29.png)

    ✅ El dominio de productos en estantes está específicamente dirigido a detectar existencias en estantes de tiendas. Lee más sobre los diferentes dominios en la [documentación Seleccionar un dominio en Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection)

✅ Tómate un tiempo para explorar la interfaz de usuario de Custom Vision para tu detector de objetos.

### Tarea - entrenar tu detector de objetos

Para entrenar tu modelo necesitarás un conjunto de imágenes que contengan los objetos que deseas detectar.

1. Reúne imágenes que contengan el objeto a detectar. Necesitarás al menos 15 imágenes que contengan cada objeto a detectar desde una variedad de ángulos diferentes y en diferentes condiciones de iluminación, pero mientras más, mejor. Este detector de objetos utiliza el dominio *Productos en estantes*, así que intenta configurar los objetos como si estuvieran en un estante de tienda. También necesitarás algunas imágenes para probar el modelo. Si estás detectando más de un objeto, querrás algunas imágenes de prueba que contengan todos los objetos.

    > 💁 Las imágenes con múltiples objetos diferentes cuentan para el mínimo de 15 imágenes para todos los objetos en la imagen.

    Tus imágenes deben ser png o jpeg, menores a 6MB. Si las creas con un iPhone, por ejemplo, pueden ser imágenes HEIC de alta resolución, por lo que necesitarán ser convertidas y posiblemente reducidas. Mientras más imágenes, mejor, y deberías tener un número similar de objetos maduros e inmaduros.

    El modelo está diseñado para productos en estantes, así que intenta tomar las fotos de los objetos en estantes.

    Puedes encontrar algunas imágenes de ejemplo que puedes usar en la carpeta [images](../../../../../5-retail/lessons/1-train-stock-detector/images) de nueces de marañón y pasta de tomate que puedes usar.

1. Sigue la [sección Subir y etiquetar imágenes del inicio rápido para construir un detector de objetos en la documentación de Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) para subir tus imágenes de entrenamiento. Crea etiquetas relevantes dependiendo de los tipos de objetos que deseas detectar.

    ![Los cuadros de diálogo de carga muestran la carga de imágenes de plátanos maduros e inmaduros](../../../../../translated_images/es/image-upload-object-detector.77c7892c3093cb59b79018edecd678749a75d71a099bc8a2d2f2f76320f88a5b.png)

    Cuando dibujes cuadros delimitadores para los objetos, mantenlos ajustados alrededor del objeto. Puede tomar un tiempo delinear todas las imágenes, pero la herramienta detectará lo que cree que son los cuadros delimitadores, haciéndolo más rápido.

    ![Etiquetando algo de pasta de tomate](../../../../../translated_images/es/object-detector-tag-tomato-paste.f47c362fb0f0eb582f3bc68cf3855fb43a805106395358d41896a269c210b7b4.png)

    > 💁 Si tienes más de 15 imágenes para cada objeto, puedes entrenar después de 15 y usar la función **Etiquetas sugeridas**. Esto utilizará el modelo entrenado para detectar los objetos en la imagen no etiquetada. Luego puedes confirmar los objetos detectados o rechazar y volver a dibujar los cuadros delimitadores. Esto puede ahorrar *mucho* tiempo.

1. Sigue la [sección Entrenar el detector del inicio rápido para construir un detector de objetos en la documentación de Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector) para entrenar el detector de objetos en tus imágenes etiquetadas.

    Se te dará una opción de tipo de entrenamiento. Selecciona **Entrenamiento rápido**.

El detector de objetos comenzará a entrenarse. Tomará unos minutos para que el entrenamiento se complete.

## Probar tu detector de objetos

Una vez que tu detector de objetos esté entrenado, puedes probarlo dándole nuevas imágenes para detectar objetos.

### Tarea - probar tu detector de objetos

1. Usa el botón **Prueba rápida** para subir imágenes de prueba y verificar que los objetos sean detectados. Usa las imágenes de prueba que creaste anteriormente, no ninguna de las imágenes que usaste para entrenar.

    ![3 latas de pasta de tomate detectadas con probabilidades de 38%, 35.5% y 34.6%](../../../../../translated_images/es/object-detector-detected-tomato-paste.52656fe87af4c37b4ee540526d63e73ed075da2e54a9a060aa528e0c562fb1b6.png)

1. Prueba todas las imágenes de prueba que tengas y observa las probabilidades.

## Reentrenar tu detector de objetos

Cuando pruebes tu detector de objetos, puede que no dé los resultados que esperas, al igual que con los clasificadores de imágenes en el proyecto anterior. Puedes mejorar tu detector de objetos reentrenándolo con imágenes que no detecta correctamente.

Cada vez que haces una predicción utilizando la opción de prueba rápida, la imagen y los resultados se almacenan. Puedes usar estas imágenes para reentrenar tu modelo.

1. Usa la pestaña **Predicciones** para localizar las imágenes que usaste para probar.

1. Confirma cualquier detección precisa, elimina las incorrectas y agrega cualquier objeto faltante.

1. Reentrena y vuelve a probar el modelo.

---

## 🚀 Desafío

¿Qué pasaría si usaras el detector de objetos con artículos de aspecto similar, como latas de pasta de tomate y latas de tomates picados de la misma marca?

Si tienes artículos de aspecto similar, pruébalo agregando imágenes de ellos a tu detector de objetos.

## Cuestionario posterior a la lección
[Cuestionario posterior a la clase](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Revisión y estudio personal

* Cuando entrenaste tu detector de objetos, habrás visto valores como *Precisión*, *Recall* y *mAP* que califican el modelo creado. Investiga qué significan estos valores utilizando [la sección Evaluar el detector del inicio rápido para construir un detector de objetos en la documentación de Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector)
* Lee más sobre la detección de objetos en la [página de detección de objetos en Wikipedia](https://wikipedia.org/wiki/Object_detection)

## Tarea

[Comparar dominios](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.