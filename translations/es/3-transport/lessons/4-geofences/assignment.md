<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-26T15:45:35+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "es"
}
-->
# Enviar notificaciones usando Twilio

## Instrucciones

En tu código hasta ahora, solo has registrado la distancia a la geovalla. En esta tarea, necesitarás agregar una notificación, ya sea un mensaje de texto o un correo electrónico, cuando las coordenadas GPS estén dentro de la geovalla.

Azure Functions tiene muchas opciones para enlaces, incluyendo servicios de terceros como Twilio, una plataforma de comunicaciones.

* Regístrate para obtener una cuenta gratuita en [Twilio.com](https://www.twilio.com)
* Lee la documentación sobre cómo enlazar Azure Functions con Twilio SMS en la [página de documentación de Microsoft sobre el enlace Twilio para Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Lee la documentación sobre cómo enlazar Azure Functions con Twilio SendGrid para enviar correos electrónicos en la [página de documentación de Microsoft sobre los enlaces de Azure Functions SendGrid](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Agrega el enlace a tu aplicación de Functions para ser notificado sobre las coordenadas GPS ya sea dentro o fuera de la geovalla, pero no ambas.

## Rúbrica

| Criterios | Sobresaliente | Adecuado | Necesita Mejorar |
| --------- | ------------- | -------- | ----------------- |
| Configurar los enlaces de las funciones y recibir un correo o SMS | Fue capaz de configurar los enlaces de las funciones y recibir un correo o SMS cuando estaba dentro o fuera de la geovalla, pero no ambas | Fue capaz de configurar los enlaces pero no pudo enviar el correo o SMS, o solo pudo enviarlo cuando las coordenadas estaban tanto dentro como fuera | No fue capaz de configurar los enlaces ni enviar un correo o SMS |

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.