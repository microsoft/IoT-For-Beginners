<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-26T14:34:57+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "es"
}
-->
# Construye un ciclo de riego más eficiente

## Instrucciones

Esta lección cubrió cómo controlar un relé mediante datos de sensores, y ese relé podría, a su vez, controlar una bomba para un sistema de riego. Para un volumen definido de suelo, hacer funcionar una bomba durante un tiempo fijo debería tener siempre el mismo impacto en la humedad del suelo. Esto significa que puedes tener una idea de cuántos segundos de riego corresponden a una cierta disminución en la lectura de humedad del suelo. Usando estos datos, puedes construir un sistema de riego más controlado.

Para esta tarea, calcularás cuánto tiempo debe funcionar la bomba para lograr un aumento particular en la humedad del suelo.

> ⚠️ Si estás utilizando hardware IoT virtual, puedes seguir este proceso, pero simula los resultados aumentando manualmente la lectura de humedad del suelo por una cantidad fija por segundo mientras el relé está encendido.

1. Comienza con suelo seco. Mide la humedad del suelo.

1. Agrega una cantidad fija de agua, ya sea haciendo funcionar la bomba durante 1 segundo o vertiendo una cantidad fija de agua.

    > La bomba siempre debe funcionar a una velocidad constante, por lo que cada segundo que funcione debe suministrar la misma cantidad de agua.

1. Espera hasta que el nivel de humedad del suelo se estabilice y toma una lectura.

1. Repite esto varias veces y crea una tabla con los resultados. Un ejemplo de esta tabla se muestra a continuación.

    | Tiempo total de la bomba | Humedad del suelo | Disminución |
    | --- | --: | -: |
    | Seco | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Calcula un aumento promedio en la humedad del suelo por segundo de agua. En el ejemplo anterior, cada segundo de agua disminuye la lectura en un promedio de 20.3.

1. Usa estos datos para mejorar la eficiencia de tu código del servidor, haciendo funcionar la bomba durante el tiempo necesario para llevar la humedad del suelo al nivel deseado.

## Rúbrica

| Criterios | Ejemplar | Adecuado | Necesita Mejorar |
| --------- | -------- | -------- | ---------------- |
| Captura de datos de humedad del suelo | Es capaz de capturar múltiples lecturas después de agregar cantidades fijas de agua | Es capaz de capturar algunas lecturas con cantidades fijas de agua | Solo puede capturar una o dos lecturas, o no puede usar cantidades fijas de agua |
| Calibración del código del servidor | Es capaz de calcular una disminución promedio en la lectura de humedad del suelo y actualizar el código del servidor para usar este valor | Es capaz de calcular una disminución promedio, pero no puede actualizar el código del servidor, o no puede calcular correctamente un promedio, pero usa este valor para actualizar correctamente el código del servidor | No es capaz de calcular un promedio ni de actualizar el código del servidor |

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.