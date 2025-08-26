<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-26T14:23:22+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "es"
}
-->
# Construir un detector de calidad de frutas

## Instrucciones

¡Construye el detector de calidad de frutas!

Usa todo lo que has aprendido hasta ahora para construir el prototipo del detector de calidad de frutas. Activa la clasificación de imágenes basada en proximidad utilizando un modelo de IA que se ejecuta en el edge, almacena los resultados de la clasificación en almacenamiento y controla un LED según el nivel de madurez de la fruta.

Deberías poder ensamblar esto utilizando el código que has escrito previamente en todas las lecciones hasta ahora.

## Rúbrica

| Criterio | Ejemplar | Adecuado | Necesita Mejorar |
| -------- | --------- | -------- | ---------------- |
| Configurar todos los servicios | Fue capaz de configurar un IoT Hub, una aplicación de funciones de Azure y almacenamiento de Azure | Fue capaz de configurar el IoT Hub, pero no la aplicación de funciones de Azure ni el almacenamiento de Azure | No fue capaz de configurar ningún servicio de IoT en internet |
| Monitorear proximidad y enviar los datos al IoT Hub si un objeto está más cerca que una distancia predefinida y activar la cámara mediante un comando | Fue capaz de medir la distancia y enviar un mensaje al IoT Hub cuando un objeto estaba lo suficientemente cerca, y enviar un comando para activar la cámara | Fue capaz de medir la proximidad y enviar datos al IoT Hub, pero no pudo enviar un comando a la cámara | No fue capaz de medir la distancia ni enviar un mensaje al IoT Hub, ni activar un comando |
| Capturar una imagen, clasificarla y enviar los resultados al IoT Hub | Fue capaz de capturar una imagen, clasificarla utilizando un dispositivo edge y enviar los resultados al IoT Hub | Fue capaz de clasificar la imagen pero no utilizando un dispositivo edge, o no pudo enviar los resultados al IoT Hub | No fue capaz de clasificar una imagen |
| Encender o apagar el LED dependiendo de los resultados de la clasificación utilizando un comando enviado a un dispositivo | Fue capaz de encender un LED mediante un comando si la fruta estaba inmadura | Fue capaz de enviar el comando al dispositivo pero no controlar el LED | No fue capaz de enviar un comando para controlar el LED |

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.