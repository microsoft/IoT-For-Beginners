<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-26T14:40:51+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "es"
}
-->
# Agregar control manual del relé

## Instrucciones

El código sin servidor puede ser activado por muchas cosas diferentes, incluidas las solicitudes HTTP. Puedes usar disparadores HTTP para agregar un control manual a tu relé, permitiendo que alguien encienda o apague el relé desde una solicitud web.

Para esta tarea, necesitas agregar dos disparadores HTTP a tu Functions App para encender y apagar el relé, reutilizando lo que has aprendido en esta lección para enviar comandos al dispositivo.

Algunas pistas:

* Puedes agregar un disparador HTTP a tu Functions App existente con el siguiente comando:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Reemplaza `<trigger name>` con el nombre de tu disparador HTTP. Usa algo como `relay_on` y `relay_off`.

* Los disparadores HTTP pueden tener control de acceso. Por defecto, requieren que se pase una clave API específica de la función con la URL para ejecutarse. Para esta tarea, puedes eliminar esta restricción para que cualquiera pueda ejecutar la función. Para hacerlo, actualiza la configuración `authLevel` en el archivo `function.json` de los disparadores HTTP a lo siguiente:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Puedes leer más sobre este control de acceso en la [documentación de claves de acceso de funciones](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* Los disparadores HTTP, por defecto, soportan solicitudes GET y POST. Esto significa que puedes llamarlos usando tu navegador web, ya que los navegadores web realizan solicitudes GET.

    Cuando ejecutes tu Functions App localmente, verás la URL del disparador:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Pega la URL en tu navegador y presiona `return`, o `Ctrl+click` (`Cmd+click` en macOS) en el enlace en la ventana del terminal en VS Code para abrirlo en tu navegador predeterminado. Esto ejecutará el disparador.

    > 💁 Nota que la URL tiene `/api` en ella: los disparadores HTTP están, por defecto, en el subdominio `api`.

* Cuando despliegues la Functions App, la URL del disparador HTTP será:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Donde `<functions app name>` es el nombre de tu Functions App, y `<trigger name>` es el nombre de tu disparador.

## Rúbrica

| Criterios | Ejemplar | Adecuado | Necesita Mejorar |
| --------- | -------- | -------- | ---------------- |
| Crear disparadores HTTP | Creó 2 disparadores para encender y apagar el relé, con nombres apropiados | Creó un disparador con un nombre apropiado | No pudo crear ningún disparador |
| Controlar el relé desde los disparadores HTTP | Pudo conectar ambos disparadores al IoT Hub y controlar el relé adecuadamente | Pudo conectar un disparador al IoT Hub y controlar el relé adecuadamente | No pudo conectar los disparadores al IoT Hub |

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de ningún malentendido o interpretación errónea que surja del uso de esta traducción.