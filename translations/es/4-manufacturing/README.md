<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-26T14:06:47+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "es"
}
-->
# Fabricación y procesamiento - usando IoT para mejorar el procesamiento de alimentos

Una vez que los alimentos llegan a un centro central o planta de procesamiento, no siempre se envían directamente a los supermercados. Muchas veces, los alimentos pasan por una serie de pasos de procesamiento, como la clasificación por calidad. Este es un proceso que solía ser manual: comenzaba en el campo cuando los recolectores solo recogían fruta madura, luego en la fábrica la fruta pasaba por una cinta transportadora y los empleados retiraban manualmente cualquier fruta magullada o podrida. Habiendo recogido y clasificado fresas yo mismo como trabajo de verano durante la escuela, puedo dar fe de que este no es un trabajo divertido.

Configuraciones más modernas dependen del IoT para la clasificación. Algunos de los primeros dispositivos, como los clasificadores de [Weco](https://wecotek.com), utilizan sensores ópticos para detectar la calidad de los productos, rechazando, por ejemplo, tomates verdes. Estos pueden ser implementados en cosechadoras en la propia granja o en plantas de procesamiento.

A medida que se producen avances en Inteligencia Artificial (IA) y Aprendizaje Automático (ML), estas máquinas pueden volverse más avanzadas, utilizando modelos de ML entrenados para distinguir entre fruta y objetos extraños como piedras, tierra o insectos. Estos modelos también pueden ser entrenados para detectar la calidad de la fruta, no solo fruta magullada, sino también la detección temprana de enfermedades u otros problemas en los cultivos.

> 🎓 El término *modelo de ML* se refiere al resultado de entrenar software de aprendizaje automático con un conjunto de datos. Por ejemplo, puedes entrenar un modelo de ML para distinguir entre tomates maduros e inmaduros, y luego usar el modelo en nuevas imágenes para determinar si los tomates están maduros o no.

En estas 4 lecciones aprenderás cómo entrenar modelos de IA basados en imágenes para detectar la calidad de la fruta, cómo utilizarlos desde un dispositivo IoT y cómo ejecutarlos en el edge, es decir, en un dispositivo IoT en lugar de en la nube.

> 💁 Estas lecciones utilizarán algunos recursos en la nube. Si no completas todas las lecciones de este proyecto, asegúrate de [limpiar tu proyecto](../clean-up.md).

## Temas

1. [Entrenar un detector de calidad de fruta](./lessons/1-train-fruit-detector/README.md)
1. [Verificar la calidad de la fruta desde un dispositivo IoT](./lessons/2-check-fruit-from-device/README.md)
1. [Ejecutar tu detector de fruta en el edge](./lessons/3-run-fruit-detector-edge/README.md)
1. [Activar la detección de calidad de fruta desde un sensor](./lessons/4-trigger-fruit-detector/README.md)

## Créditos

Todas las lecciones fueron escritas con ♥️ por [Jen Fox](https://github.com/jenfoxbot) y [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.