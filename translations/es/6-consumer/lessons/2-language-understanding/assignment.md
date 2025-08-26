<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-26T15:27:40+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "es"
}
-->
# Cancelar el temporizador

## Instrucciones

Hasta ahora en esta lección has entrenado un modelo para entender cómo configurar un temporizador. Otra función útil es cancelar un temporizador, por ejemplo, si tu pan ya está listo y puede sacarse del horno antes de que el temporizador termine.

Agrega una nueva intención a tu aplicación LUIS para cancelar el temporizador. No necesitará ninguna entidad, pero sí algunas frases de ejemplo. Maneja esto en tu código serverless si es la intención principal, registrando que la intención fue reconocida y devolviendo una respuesta adecuada.

## Rúbrica

| Criterios | Sobresaliente | Adecuado | Necesita Mejorar |
| --------- | ------------- | -------- | ---------------- |
| Agregar la intención de cancelar el temporizador a la aplicación LUIS | Fue capaz de agregar la intención y entrenar el modelo | Fue capaz de agregar la intención pero no entrenar el modelo | No fue capaz de agregar la intención ni entrenar el modelo |
| Manejar la intención en la aplicación serverless | Fue capaz de detectar la intención como la principal y registrarla | Fue capaz de detectar la intención como la principal | No fue capaz de detectar la intención como la principal |

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.