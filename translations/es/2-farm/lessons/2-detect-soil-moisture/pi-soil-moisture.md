<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-26T14:46:48+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "es"
}
-->
# Medir la humedad del suelo - Raspberry Pi

En esta parte de la lección, agregarás un sensor capacitivo de humedad del suelo a tu Raspberry Pi y leerás valores de él.

## Hardware

La Raspberry Pi necesita un sensor capacitivo de humedad del suelo.

El sensor que usarás es un [Sensor Capacitivo de Humedad del Suelo](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), que mide la humedad del suelo detectando la capacitancia del mismo, una propiedad que cambia a medida que varía la humedad del suelo. A medida que aumenta la humedad del suelo, el voltaje disminuye.

Este es un sensor analógico, por lo que utiliza un pin analógico y el ADC de 10 bits en el Grove Base Hat de la Pi para convertir el voltaje en una señal digital de 1-1,023. Luego, esta señal se envía a través de I

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.