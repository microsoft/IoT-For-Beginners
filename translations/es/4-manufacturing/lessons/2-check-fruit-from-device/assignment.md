<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-26T14:10:46+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "es"
}
-->
# Responder a los resultados de clasificación

## Instrucciones

Tu dispositivo ha clasificado imágenes y tiene los valores de las predicciones. Tu dispositivo podría usar esta información para realizar alguna acción: podría enviarla a IoT Hub para que otros sistemas la procesen, o podría controlar un actuador, como encender un LED cuando la fruta está inmadura.

Añade código a tu dispositivo para responder de la manera que elijas: ya sea enviando datos a un IoT Hub, controlando un actuador, o combinando ambas opciones y enviando datos a un IoT Hub con algún código sin servidor que determine si la fruta está madura o no y envíe un comando para controlar un actuador.

## Rúbrica

| Criterios | Ejemplar | Adecuado | Necesita Mejorar |
| --------- | --------- | -------- | ---------------- |
| Responder a las predicciones | Fue capaz de implementar una respuesta a las predicciones que funciona de manera consistente con predicciones del mismo valor. | Fue capaz de implementar una respuesta que no depende de las predicciones, como simplemente enviar datos sin procesar a un IoT Hub. | No fue capaz de programar el dispositivo para responder a las predicciones. |

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.