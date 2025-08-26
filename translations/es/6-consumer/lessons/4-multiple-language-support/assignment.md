<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-26T15:22:38+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "es"
}
-->
# Construir un traductor universal

## Instrucciones

Un traductor universal es un dispositivo que puede traducir entre múltiples idiomas, permitiendo que personas que hablan diferentes idiomas puedan comunicarse. Usa lo que has aprendido en las últimas lecciones para construir un traductor universal utilizando 2 dispositivos IoT.

> Si no tienes 2 dispositivos, sigue los pasos de las lecciones anteriores para configurar un dispositivo IoT virtual como uno de los dispositivos IoT.

Deberías configurar un dispositivo para un idioma y otro para otro idioma. Cada dispositivo debe aceptar voz, convertirla a texto, enviarla al otro dispositivo a través de IoT Hub y una aplicación de Functions, luego traducirla y reproducir el discurso traducido.

> 💁 Consejo: Al enviar el discurso de un dispositivo a otro, envía también el idioma en el que está, facilitando la traducción. Incluso podrías hacer que cada dispositivo se registre usando IoT Hub y una aplicación de Functions primero, pasando el idioma que soportan para almacenarlo en Azure Storage. Luego podrías usar una aplicación de Functions para realizar las traducciones, enviando el texto traducido al dispositivo IoT.

## Rúbrica

| Criterios | Ejemplar | Adecuado | Necesita Mejorar |
| --------- | -------- | -------- | ---------------- |
| Crear un traductor universal | Fue capaz de construir un traductor universal, convirtiendo el discurso detectado por un dispositivo en discurso reproducido por otro dispositivo en un idioma diferente | Fue capaz de hacer funcionar algunos componentes, como capturar voz o traducir, pero no logró construir la solución completa de principio a fin | No fue capaz de construir ninguna parte de un traductor universal funcional |

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.