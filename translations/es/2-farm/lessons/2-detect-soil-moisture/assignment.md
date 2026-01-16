<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-26T14:45:31+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "es"
}
-->
# Calibra tu sensor

## Instrucciones

En esta lección obtuviste lecturas del sensor de humedad del suelo, medidas como valores de 0-1023. Para convertir estos valores en lecturas reales de humedad del suelo, necesitas calibrar tu sensor. Puedes hacerlo tomando lecturas de muestras de suelo y luego calculando el contenido gravimétrico de humedad del suelo a partir de estas muestras.

Necesitarás repetir estos pasos varias veces para obtener las lecturas necesarias, utilizando suelos con diferentes niveles de humedad cada vez.

1. Toma una lectura de humedad del suelo utilizando el sensor de humedad del suelo. Anota esta lectura.

1. Toma una muestra del suelo y pésala. Anota este peso.

1. Seca el suelo. Un horno cálido a 110°C (230°F) durante unas horas es la mejor opción. También puedes hacerlo al sol o colocarlo en un lugar cálido y seco hasta que el suelo esté completamente seco. Debe quedar pulverizado y suelto.

    > 💁 En un laboratorio, para obtener resultados más precisos, deberías secar el suelo en un horno durante 48-72 horas. Si tu escuela tiene hornos de secado, consulta si puedes utilizarlos para secar las muestras por más tiempo. Cuanto más tiempo, más seco estará el suelo y más precisos serán los resultados.

1. Pesa el suelo nuevamente.

    > 🔥 Si lo secaste en un horno, asegúrate de que se haya enfriado primero.

La humedad gravimétrica del suelo se calcula como:

![La humedad del suelo % es el peso húmedo menos el peso seco, dividido por el peso seco, multiplicado por 100](../../../../../translated_images/es/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W - el peso del suelo húmedo  
* W - el peso del suelo seco  

Por ejemplo, supongamos que tienes una muestra de suelo que pesa 212g húmeda y 197g seca.

![El cálculo completado](../../../../../translated_images/es/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212g  
* W = 197g  
* 212 - 197 = 15  
* 15 / 197 = 0.076  
* 0.076 * 100 = 7.6%  

En este ejemplo, el suelo tiene una humedad gravimétrica del 7.6%.

Una vez que tengas las lecturas de al menos 3 muestras, traza un gráfico del porcentaje de humedad del suelo frente a la lectura del sensor de humedad del suelo y añade una línea que se ajuste mejor a los puntos. Luego, puedes usar esto para calcular el contenido gravimétrico de humedad del suelo para una lectura específica del sensor leyendo el valor de la línea.

## Rúbrica

| Criterios | Ejemplar | Adecuado | Necesita Mejorar |
| --------- | -------- | -------- | ---------------- |
| Recopilar datos de calibración | Captura al menos 3 muestras de calibración | Captura al menos 2 muestras de calibración | Captura al menos 1 muestra de calibración |
| Realizar una lectura calibrada | Traza exitosamente el gráfico de calibración y realiza una lectura del sensor, convirtiéndola en contenido gravimétrico de humedad del suelo | Traza exitosamente el gráfico de calibración | No logra trazar el gráfico |

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por lograr precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.