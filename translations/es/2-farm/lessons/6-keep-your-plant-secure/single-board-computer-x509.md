<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-26T14:55:19+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "es"
}
-->
# Usa el certificado X.509 en el código de tu dispositivo - Hardware IoT Virtual y Raspberry Pi

En esta parte de la lección, conectarás tu dispositivo IoT virtual o Raspberry Pi a tu IoT Hub utilizando el certificado X.509.

## Conecta tu dispositivo al IoT Hub

El siguiente paso es conectar tu dispositivo al IoT Hub utilizando los certificados X.509.

### Tarea - conectar al IoT Hub

1. Copia los archivos de clave y certificado a la carpeta que contiene el código de tu dispositivo IoT. Si estás utilizando una Raspberry Pi a través de VS Code Remote SSH y creaste las claves en tu PC o Mac, puedes arrastrar y soltar los archivos en el explorador de VS Code para copiarlos.

1. Abre el archivo `app.py`.

1. Para conectarte utilizando un certificado X.509, necesitarás el nombre del host del IoT Hub y el certificado X.509. Comienza creando una variable que contenga el nombre del host añadiendo el siguiente código antes de que se cree el cliente del dispositivo:

    ```python
    host_name = "<host_name>"
    ```

    Sustituye `<host_name>` por el nombre del host de tu IoT Hub. Puedes obtenerlo de la sección `HostName` en el `connection_string`. Será el nombre de tu IoT Hub, terminando con `.azure-devices.net`.

1. Debajo de esto, declara una variable con el ID del dispositivo:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Necesitarás una instancia de la clase `X509` que contenga los archivos X.509. Añade `X509` a la lista de clases importadas del módulo `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Crea una instancia de la clase `X509` utilizando tus archivos de certificado y clave añadiendo este código debajo de la declaración de `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Esto creará la clase `X509` utilizando los archivos `soil-moisture-sensor-x509-cert.pem` y `soil-moisture-sensor-x509-key.pem` creados anteriormente.

1. Sustituye la línea de código que crea el `device_client` a partir de una cadena de conexión con lo siguiente:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Esto conectará utilizando el certificado X.509 en lugar de una cadena de conexión.

1. Elimina la línea con la variable `connection_string`.

1. Ejecuta tu código. Monitorea los mensajes enviados al IoT Hub y envía solicitudes de métodos directos como antes. Verás que el dispositivo se conecta y envía lecturas de humedad del suelo, además de recibir solicitudes de métodos directos.

> 💁 Puedes encontrar este código en la carpeta [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) o [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 ¡Tu programa del sensor de humedad del suelo está conectado a tu IoT Hub utilizando un certificado X.509!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.