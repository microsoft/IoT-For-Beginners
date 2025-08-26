<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-26T14:18:56+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "es"
}
-->
# Ejecutar otros servicios en el edge

## Instrucciones

No solo los clasificadores de imágenes pueden ejecutarse en el edge, cualquier cosa que pueda empaquetarse en un contenedor puede desplegarse en un dispositivo IoT Edge. Código sin servidor que se ejecuta como Azure Functions, como los triggers que creaste en lecciones anteriores, puede ejecutarse en contenedores y, por lo tanto, en IoT Edge.

Elige una de las lecciones anteriores e intenta ejecutar la aplicación de Azure Functions en un contenedor de IoT Edge. Puedes encontrar una guía que muestra cómo hacerlo utilizando un proyecto diferente de aplicación de Functions en el [Tutorial: Implementar Azure Functions como módulos de IoT Edge en la documentación de Microsoft](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Criterios de evaluación

| Criterio | Ejemplar | Adecuado | Necesita Mejorar |
| -------- | --------- | -------- | ---------------- |
| Implementar una aplicación de Azure Functions en IoT Edge | Fue capaz de implementar una aplicación de Azure Functions en IoT Edge y usarla con un dispositivo IoT para ejecutar un trigger a partir de datos de IoT | Fue capaz de implementar una aplicación de Functions en IoT Edge, pero no logró que el trigger se activara | No pudo implementar una aplicación de Functions en IoT Edge |

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.