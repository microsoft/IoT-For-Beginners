<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f5e63c916d2dd97d58be12aaf76bd9f1",
  "translation_date": "2025-08-26T14:07:54+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/README.md",
  "language_code": "es"
}
-->
# Entrena un detector de calidad de frutas

![Una vista general ilustrada de esta lección](../../../../../translated_images/lesson-15.843d21afdc6fb2bba70cd9db7b7d2f91598859fafda2078b0bdc44954194b6c0.es.jpg)

> Ilustración por [Nitya Narasimhan](https://github.com/nitya). Haz clic en la imagen para una versión más grande.

Este video ofrece una visión general del servicio Azure Custom Vision, un servicio que se cubrirá en esta lección.

[![Custom Vision – Machine Learning Made Easy | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 Haz clic en la imagen de arriba para ver el video

## Cuestionario previo a la lección

[Cuestionario previo a la lección](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## Introducción

El reciente auge de la Inteligencia Artificial (IA) y el Aprendizaje Automático (ML) está proporcionando una amplia gama de capacidades a los desarrolladores de hoy en día. Los modelos de ML pueden entrenarse para reconocer diferentes cosas en imágenes, incluyendo frutas inmaduras, y esto puede usarse en dispositivos IoT para ayudar a clasificar productos, ya sea durante la cosecha o durante el procesamiento en fábricas o almacenes.

En esta lección aprenderás sobre la clasificación de imágenes: usar modelos de ML para distinguir entre imágenes de diferentes cosas. Aprenderás cómo entrenar un clasificador de imágenes para distinguir entre frutas que están en buen estado y frutas que están en mal estado, ya sea demasiado maduras, golpeadas o podridas.

En esta lección cubriremos:

* [Usar IA y ML para clasificar alimentos](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Clasificación de imágenes mediante Aprendizaje Automático](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Entrenar un clasificador de imágenes](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Probar tu clasificador de imágenes](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Reentrenar tu clasificador de imágenes](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## Usar IA y ML para clasificar alimentos

Alimentar a la población mundial es difícil, especialmente a un precio que haga que los alimentos sean asequibles para todos. Uno de los mayores costos es la mano de obra, por lo que los agricultores están recurriendo cada vez más a la automatización y herramientas como IoT para reducir sus costos laborales. La cosecha manual es intensiva en mano de obra (y a menudo un trabajo agotador), y está siendo reemplazada por maquinaria, especialmente en países más ricos. A pesar de los ahorros en costos al usar maquinaria para cosechar, hay un inconveniente: la capacidad de clasificar los alimentos mientras se cosechan.

No todos los cultivos maduran de manera uniforme. Los tomates, por ejemplo, pueden tener algunos frutos verdes en la planta cuando la mayoría está lista para cosechar. Aunque es un desperdicio cosechar estos frutos verdes, es más barato y fácil para el agricultor cosechar todo usando maquinaria y desechar los productos inmaduros más tarde.

✅ Observa diferentes frutas o verduras, ya sea creciendo cerca de ti en granjas o en tu jardín, o en tiendas. ¿Están todas en el mismo grado de madurez, o ves variaciones?

El auge de la cosecha automatizada trasladó la clasificación de productos de la cosecha a la fábrica. Los alimentos viajarían en largas cintas transportadoras con equipos de personas revisando los productos y eliminando cualquier cosa que no cumpliera con el estándar de calidad requerido. La cosecha era más barata gracias a la maquinaria, pero todavía había un costo asociado con la clasificación manual de los alimentos.

![Si se detecta un tomate rojo, continúa su trayecto sin interrupciones. Si se detecta un tomate verde, se lanza a un contenedor de desechos mediante una palanca](../../../../../translated_images/optical-tomato-sorting.61aa134bdda4e5b1bfb16a212c1e35a6ef0c426cbb8b1c975f79d7bfbf48d068.es.png)

La siguiente evolución fue usar máquinas para clasificar, ya sea integradas en la cosechadora o en las plantas de procesamiento. La primera generación de estas máquinas usaba sensores ópticos para detectar colores, controlando actuadores para empujar tomates verdes a un contenedor de desechos usando palancas o ráfagas de aire, dejando que los tomates rojos continuaran en una red de cintas transportadoras.

En este video, mientras los tomates caen de una cinta transportadora a otra, los tomates verdes son detectados y lanzados a un contenedor usando palancas.

✅ ¿Qué condiciones necesitarías en una fábrica o en un campo para que estos sensores ópticos funcionen correctamente?

Las últimas evoluciones de estas máquinas de clasificación aprovechan la IA y el ML, utilizando modelos entrenados para distinguir productos buenos de malos, no solo por diferencias obvias de color como tomates verdes frente a rojos, sino por diferencias más sutiles en apariencia que pueden indicar enfermedad o golpes.

## Clasificación de imágenes mediante Aprendizaje Automático

La programación tradicional consiste en tomar datos, aplicar un algoritmo a los datos y obtener un resultado. Por ejemplo, en el último proyecto tomaste coordenadas GPS y una geocerca, aplicaste un algoritmo proporcionado por Azure Maps y obtuviste un resultado sobre si el punto estaba dentro o fuera de la geocerca. Introduces más datos, obtienes más resultados.

![El desarrollo tradicional toma datos de entrada y un algoritmo y da un resultado. El aprendizaje automático usa datos de entrada y salida para entrenar un modelo, y este modelo puede tomar nuevos datos de entrada para generar nuevos resultados](../../../../../translated_images/traditional-vs-ml.5c20c169621fa539.es.png)

El aprendizaje automático cambia esto: comienzas con datos y resultados conocidos, y el algoritmo de aprendizaje automático aprende de los datos. Luego puedes tomar ese algoritmo entrenado, llamado *modelo de aprendizaje automático* o *modelo*, e introducir nuevos datos para obtener nuevos resultados.

> 🎓 El proceso de un algoritmo de aprendizaje automático aprendiendo de los datos se llama *entrenamiento*. Los datos de entrada y los resultados conocidos se llaman *datos de entrenamiento*.

Por ejemplo, podrías darle a un modelo millones de imágenes de plátanos inmaduros como datos de entrenamiento de entrada, con el resultado de entrenamiento configurado como `inmaduro`, y millones de imágenes de plátanos maduros como datos de entrenamiento con el resultado configurado como `maduro`. El algoritmo de ML entonces creará un modelo basado en estos datos. Luego le das a este modelo una nueva imagen de un plátano y predice si la nueva imagen es de un plátano maduro o inmaduro.

> 🎓 Los resultados de los modelos de ML se llaman *predicciones*

![2 plátanos, uno maduro con una predicción de 99.7% maduro, 0.3% inmaduro, y uno inmaduro con una predicción de 1.4% maduro, 98.6% inmaduro](../../../../../translated_images/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50ece4e4589e724b142da0681f35470fe3db3f7d51240f69c85.es.png)

Los modelos de ML no dan una respuesta binaria, en cambio, dan probabilidades. Por ejemplo, un modelo puede recibir una imagen de un plátano y predecir `maduro` con un 99.7% y `inmaduro` con un 0.3%. Tu código luego elegiría la mejor predicción y decidiría que el plátano está maduro.

El modelo de ML utilizado para detectar imágenes como esta se llama *clasificador de imágenes*: se le dan imágenes etiquetadas y luego clasifica nuevas imágenes basándose en estas etiquetas.

> 💁 Esto es una simplificación, y hay muchas otras formas de entrenar modelos que no siempre necesitan resultados etiquetados, como el aprendizaje no supervisado. Si quieres aprender más sobre ML, consulta [ML para principiantes, un currículo de 24 lecciones sobre Aprendizaje Automático](https://aka.ms/ML-beginners).

## Entrenar un clasificador de imágenes

Para entrenar con éxito un clasificador de imágenes necesitas millones de imágenes. Sin embargo, una vez que tienes un clasificador de imágenes entrenado con millones o miles de millones de imágenes variadas, puedes reutilizarlo y reentrenarlo usando un pequeño conjunto de imágenes y obtener excelentes resultados, utilizando un proceso llamado *aprendizaje por transferencia*.

> 🎓 El aprendizaje por transferencia es cuando transfieres el aprendizaje de un modelo de ML existente a un nuevo modelo basado en nuevos datos.

Una vez que un clasificador de imágenes ha sido entrenado para una amplia variedad de imágenes, sus componentes internos son excelentes para reconocer formas, colores y patrones. El aprendizaje por transferencia permite que el modelo tome lo que ya ha aprendido al reconocer partes de imágenes y lo use para reconocer nuevas imágenes.

![Una vez que puedes reconocer formas, pueden colocarse en diferentes configuraciones para formar un barco o un gato](../../../../../translated_images/shapes-to-images.1a309f0ea88dd66f.es.png)

Puedes pensar en esto como los libros de formas para niños, donde una vez que puedes reconocer un semicírculo, un rectángulo y un triángulo, puedes reconocer un velero o un gato dependiendo de la configuración de estas formas. El clasificador de imágenes puede reconocer las formas, y el aprendizaje por transferencia le enseña qué combinación forma un barco o un gato, o un plátano maduro.

Hay una amplia gama de herramientas que pueden ayudarte a hacer esto, incluyendo servicios basados en la nube que pueden ayudarte a entrenar tu modelo y luego usarlo a través de APIs web.

> 💁 Entrenar estos modelos requiere mucha potencia de cómputo, generalmente mediante Unidades de Procesamiento Gráfico (GPUs). El mismo hardware especializado que hace que los juegos en tu Xbox se vean increíbles también puede usarse para entrenar modelos de aprendizaje automático. Al usar la nube, puedes alquilar tiempo en computadoras potentes con GPUs para entrenar estos modelos, obteniendo acceso a la potencia de cómputo que necesitas, solo por el tiempo que la necesitas.

## Custom Vision

Custom Vision es una herramienta basada en la nube para entrenar clasificadores de imágenes. Te permite entrenar un clasificador usando solo un pequeño número de imágenes. Puedes subir imágenes a través de un portal web, una API web o un SDK, dando a cada imagen una *etiqueta* que clasifique esa imagen. Luego entrenas el modelo y lo pruebas para ver qué tan bien funciona. Una vez que estés satisfecho con el modelo, puedes publicar versiones de este que pueden ser accesibles a través de una API web o un SDK.

![El logo de Azure Custom Vision](../../../../../translated_images/custom-vision-logo.d3d4e7c8a87ec9daf825e72e210576c3cbf60312577be7a139e22dd97ab7f1e6.es.png)

> 💁 Puedes entrenar un modelo de Custom Vision con tan solo 5 imágenes por clasificación, pero más es mejor. Puedes obtener mejores resultados con al menos 30 imágenes.

Custom Vision es parte de una gama de herramientas de IA de Microsoft llamadas Cognitive Services. Estas son herramientas de IA que pueden usarse ya sea sin ningún entrenamiento o con una pequeña cantidad de entrenamiento. Incluyen reconocimiento y traducción de voz, comprensión del lenguaje y análisis de imágenes. Estas están disponibles con un nivel gratuito como servicios en Azure.

> 💁 El nivel gratuito es más que suficiente para crear un modelo, entrenarlo y luego usarlo para trabajos de desarrollo. Puedes leer sobre los límites del nivel gratuito en la [página de límites y cuotas de Custom Vision en la documentación de Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn).

### Tarea - crear un recurso de servicios cognitivos

Para usar Custom Vision, primero necesitas crear dos recursos de servicios cognitivos en Azure usando la CLI de Azure, uno para el entrenamiento de Custom Vision y otro para la predicción de Custom Vision.

1. Crea un Grupo de Recursos para este proyecto llamado `fruit-quality-detector`.

1. Usa el siguiente comando para crear un recurso gratuito de entrenamiento de Custom Vision:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Reemplaza `<location>` con la ubicación que usaste al crear el Grupo de Recursos.

    Esto creará un recurso de entrenamiento de Custom Vision en tu Grupo de Recursos. Se llamará `fruit-quality-detector-training` y usará el SKU `F0`, que es el nivel gratuito. La opción `--yes` significa que aceptas los términos y condiciones de los servicios cognitivos.

> 💁 Usa el SKU `S0` si ya tienes una cuenta gratuita usando cualquiera de los Servicios Cognitivos.

1. Usa el siguiente comando para crear un recurso gratuito de predicción de Custom Vision:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Reemplaza `<location>` con la ubicación que usaste al crear el Grupo de Recursos.

    Esto creará un recurso de predicción de Custom Vision en tu Grupo de Recursos. Se llamará `fruit-quality-detector-prediction` y usará el SKU `F0`, que es el nivel gratuito. La opción `--yes` significa que aceptas los términos y condiciones de los servicios cognitivos.

### Tarea - crear un proyecto de clasificador de imágenes

1. Abre el portal de Custom Vision en [CustomVision.ai](https://customvision.ai) e inicia sesión con la cuenta de Microsoft que usaste para tu cuenta de Azure.

1. Sigue la [sección de creación de un nuevo proyecto en el inicio rápido para construir un clasificador en la documentación de Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project) para crear un nuevo proyecto de Custom Vision. La interfaz de usuario puede cambiar y esta documentación siempre será la referencia más actualizada.

    Llama a tu proyecto `fruit-quality-detector`.

    Cuando crees tu proyecto, asegúrate de usar el recurso `fruit-quality-detector-training` que creaste anteriormente. Usa un tipo de proyecto *Clasificación*, un tipo de clasificación *Multiclase* y el dominio *Alimentos*.

    ![La configuración para el proyecto de Custom Vision con el nombre configurado como fruit-quality-detector, sin descripción, el recurso configurado como fruit-quality-detector-training, el tipo de proyecto configurado como clasificación, el tipo de clasificación configurado como multiclase y el dominio configurado como alimentos](../../../../../translated_images/custom-vision-create-project.cf46325b92d8b131089f6647cf5e07b664cb77850e106d66e3c057b6b69756c6.es.png)

✅ Tómate un tiempo para explorar la interfaz de usuario de Custom Vision para tu clasificador de imágenes.

### Tarea - entrenar tu proyecto de clasificador de imágenes

Para entrenar un clasificador de imágenes, necesitarás múltiples imágenes de frutas, tanto de buena como de mala calidad, para etiquetarlas como buenas y malas, como un plátano maduro y uno demasiado maduro.
💁 Estos clasificadores pueden clasificar imágenes de cualquier cosa, así que si no tienes frutas de diferentes calidades a mano, puedes usar dos tipos diferentes de frutas, ¡o gatos y perros!
Idealmente, cada imagen debería mostrar solo la fruta, con un fondo consistente o una amplia variedad de fondos. Asegúrate de que no haya nada en el fondo que sea específico para frutas maduras o inmaduras.

> 💁 Es importante no tener fondos específicos ni elementos que no estén relacionados con lo que se está clasificando para cada etiqueta, de lo contrario, el clasificador podría clasificar basándose en el fondo. Hubo un clasificador para cáncer de piel que se entrenó con lunares normales y cancerosos, y los cancerosos siempre tenían reglas para medir el tamaño. Resultó que el clasificador era casi 100% preciso identificando reglas en las imágenes, no lunares cancerosos.

Los clasificadores de imágenes funcionan con resoluciones muy bajas. Por ejemplo, Custom Vision puede tomar imágenes de entrenamiento y predicción de hasta 10240x10240, pero entrena y ejecuta el modelo en imágenes de 227x227. Las imágenes más grandes se reducen a este tamaño, así que asegúrate de que el objeto que estás clasificando ocupe una gran parte de la imagen, de lo contrario, podría ser demasiado pequeño en la imagen reducida utilizada por el clasificador.

1. Reúne imágenes para tu clasificador. Necesitarás al menos 5 imágenes para cada etiqueta para entrenar el clasificador, pero mientras más, mejor. También necesitarás algunas imágenes adicionales para probar el clasificador. Estas imágenes deben ser diferentes imágenes del mismo objeto. Por ejemplo:

    * Usando 2 plátanos maduros, toma algunas fotos de cada uno desde diferentes ángulos, tomando al menos 7 fotos (5 para entrenar, 2 para probar), pero idealmente más.

        ![Fotos de 2 plátanos diferentes](../../../../../translated_images/banana-training-images.530eb203346d73bc23b8b990fb4609470bf4ff7c942ccc13d4cfffeed9be1ad4.es.png)

    * Repite el mismo proceso usando 2 plátanos inmaduros.

    Deberías tener al menos 10 imágenes de entrenamiento, con al menos 5 maduras y 5 inmaduras, y 4 imágenes de prueba, 2 maduras y 2 inmaduras. Tus imágenes deben ser png o jpeg, de menos de 6MB. Si las creas con un iPhone, por ejemplo, podrían ser imágenes HEIC de alta resolución, por lo que necesitarán ser convertidas y posiblemente reducidas. Mientras más imágenes tengas, mejor, y deberías tener un número similar de maduras e inmaduras.

    Si no tienes frutas maduras e inmaduras, puedes usar diferentes frutas o cualquier par de objetos que tengas disponibles. También puedes encontrar algunas imágenes de ejemplo en la carpeta [images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images) de plátanos maduros e inmaduros que puedes usar.

1. Sigue la [sección de subir y etiquetar imágenes del tutorial rápido para construir un clasificador en la documentación de Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) para subir tus imágenes de entrenamiento. Etiqueta las frutas maduras como `ripe` y las inmaduras como `unripe`.

    ![Los diálogos de subida mostrando la carga de imágenes de plátanos maduros e inmaduros](../../../../../translated_images/image-upload-bananas.0751639f3815e0ec42bdbc6254d1e4357a185834d1ae10c9948a0e7d6d336695.es.png)

1. Sigue la [sección de entrenar el clasificador del tutorial rápido para construir un clasificador en la documentación de Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier) para entrenar el clasificador de imágenes con tus imágenes subidas.

    Se te dará una opción de tipo de entrenamiento. Selecciona **Quick Training**.

El clasificador comenzará a entrenarse. Tomará unos minutos para completar el entrenamiento.

> 🍌 Si decides comer tu fruta mientras el clasificador se está entrenando, asegúrate de tener suficientes imágenes para probar primero.

## Prueba tu clasificador de imágenes

Una vez que tu clasificador esté entrenado, puedes probarlo dándole una nueva imagen para clasificar.

### Tarea - prueba tu clasificador de imágenes

1. Sigue la [documentación para probar tu modelo en los documentos de Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model) para probar tu clasificador de imágenes. Usa las imágenes de prueba que creaste anteriormente, no ninguna de las imágenes que usaste para entrenar.

    ![Un plátano inmaduro predicho como inmaduro con una probabilidad del 98.9%, maduro con una probabilidad del 1.1%](../../../../../translated_images/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64886422438850ea14f0be6ac918c217ea3b255c685abfabe7.es.png)

1. Prueba todas las imágenes de prueba que tengas y observa las probabilidades.

## Reentrena tu clasificador de imágenes

Cuando pruebes tu clasificador, puede que no dé los resultados que esperas. Los clasificadores de imágenes usan aprendizaje automático para hacer predicciones sobre lo que hay en una imagen, basándose en probabilidades de que ciertas características de una imagen signifiquen que coincide con una etiqueta particular. No entiende lo que hay en la imagen: no sabe qué es un plátano ni entiende qué hace que un plátano sea un plátano en lugar de un barco. Puedes mejorar tu clasificador reentrenándolo con imágenes en las que se equivoque.

Cada vez que haces una predicción usando la opción de prueba rápida, la imagen y los resultados se almacenan. Puedes usar estas imágenes para reentrenar tu modelo.

### Tarea - reentrena tu clasificador de imágenes

1. Sigue la [documentación para usar la imagen predicha para entrenamiento en los documentos de Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training) para reentrenar tu modelo, usando la etiqueta correcta para cada imagen.

1. Una vez que tu modelo haya sido reentrenado, prueba con nuevas imágenes.

---

## 🚀 Desafío

¿Qué crees que pasaría si usas una imagen de una fresa con un modelo entrenado en plátanos, o una imagen de un plátano inflable, o una persona disfrazada de plátano, o incluso un personaje amarillo de caricatura como alguien de Los Simpson?

Pruébalo y observa cuáles son las predicciones. Puedes encontrar imágenes para probar usando [Bing Image search](https://www.bing.com/images/trending).

## Cuestionario post-lectura

[Cuestionario post-lectura](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## Revisión y autoestudio

* Cuando entrenaste tu clasificador, habrás visto valores para *Precision*, *Recall* y *AP* que califican el modelo creado. Investiga qué significan estos valores usando [la sección de evaluar el clasificador del tutorial rápido para construir un clasificador en la documentación de Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)
* Investiga cómo mejorar tu clasificador en [cómo mejorar tu modelo de Custom Vision en la documentación de Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)

## Asignación

[Entrena tu clasificador para múltiples frutas y verduras](assignment.md)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.