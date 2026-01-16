<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-26T14:12:36+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "es"
}
-->
# Clasificar una imagen - Wio Terminal

En esta parte de la lección, enviarás la imagen capturada por la cámara al servicio Custom Vision para clasificarla.

## Clasificar una imagen

El servicio Custom Vision tiene una API REST que puedes llamar desde el Wio Terminal para clasificar imágenes. Esta API REST se accede a través de una conexión HTTPS, que es una conexión HTTP segura.

Al interactuar con puntos finales HTTPS, el código cliente necesita solicitar el certificado de clave pública del servidor al que se accede y usarlo para cifrar el tráfico que envía. Tu navegador web hace esto automáticamente, pero los microcontroladores no. Necesitarás solicitar este certificado manualmente y usarlo para crear una conexión segura con la API REST. Estos certificados no cambian, por lo que una vez que tengas un certificado, puede ser codificado directamente en tu aplicación.

Estos certificados contienen claves públicas y no necesitan mantenerse seguros. Puedes usarlos en tu código fuente y compartirlos públicamente en lugares como GitHub.

### Tarea - configurar un cliente SSL

1. Abre el proyecto de la aplicación `fruit-quality-detector` si no está ya abierto.

1. Abre el archivo de encabezado `config.h` y añade lo siguiente:

    ```cpp
    const char *CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQAueRcfuAIek/4tmDg0xQwDANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwNjCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBALVGARl56bx3KBUSGuPc4H5uoNFkFH4e7pvTCxRi4j/+z+Xb\r\n"
        "wjEz+5CipDOqjx9/jWjskL5dk7PaQkzItidsAAnDCW1leZBOIi68Lff1bjTeZgMY\r\n"
        "iwdRd3Y39b/lcGpiuP2d23W95YHkMMT8IlWosYIX0f4kYb62rphyfnAjYb/4Od99\r\n"
        "ThnhlAxGtfvSbXcBVIKCYfZgqRvV+5lReUnd1aNjRYVzPOoifgSx2fRyy1+pO1Uz\r\n"
        "aMMNnIOE71bVYW0A1hr19w7kOb0KkJXoALTDDj1ukUEDqQuBfBxReL5mXiu1O7WG\r\n"
        "0vltg0VZ/SZzctBsdBlx1BkmWYBW261KZgBivrql5ELTKKd8qgtHcLQA5fl6JB0Q\r\n"
        "gs5XDaWehN86Gps5JW8ArjGtjcWAIP+X8CQaWfaCnuRm6Bk/03PQWhgdi84qwA0s\r\n"
        "sRfFJwHUPTNSnE8EiGVk2frt0u8PG1pwSQsFuNJfcYIHEv1vOzP7uEOuDydsmCjh\r\n"
        "lxuoK2n5/2aVR3BMTu+p4+gl8alXoBycyLmj3J/PUgqD8SL5fTCUegGsdia/Sa60\r\n"
        "N2oV7vQ17wjMN+LXa2rjj/b4ZlZgXVojDmAjDwIRdDUujQu0RVsJqFLMzSIHpp2C\r\n"
        "Zp7mIoLrySay2YYBu7SiNwL95X6He2kS8eefBBHjzwW/9FxGqry57i71c2cDAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQU1cFnOsKjnfR3UltZEjgp5lVou6UwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQB2oWc93fB8esci/8esixj++N22meiGDjgF\r\n"
        "+rA2LUK5IOQOgcUSTGKSqF9lYfAxPjrqPjDCUPHCURv+26ad5P/BYtXtbmtxJWu+\r\n"
        "cS5BhMDPPeG3oPZwXRHBJFAkY4O4AF7RIAAUW6EzDflUoDHKv83zOiPfYGcpHc9s\r\n"
        "kxAInCedk7QSgXvMARjjOqdakor21DTmNIUotxo8kHv5hwRlGhBJwps6fEVi1Bt0\r\n"
        "trpM/3wYxlr473WSPUFZPgP1j519kLpWOJ8z09wxay+Br29irPcBYv0GMXlHqThy\r\n"
        "8y4m/HyTQeI2IMvMrQnwqPpY+rLIXyviI2vLoI+4xKE4Rn38ZZ8m\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

    Este es el *certificado Microsoft Azure DigiCert Global Root G2* - es uno de los certificados utilizados por muchos servicios de Azure a nivel mundial.

    > 💁 Para verificar que este es el certificado que debes usar, ejecuta el siguiente comando en macOS o Linux. Si estás usando Windows, puedes ejecutar este comando utilizando el [Subsistema de Windows para Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > La salida mostrará el certificado DigiCert Global Root G2.

1. Abre `main.cpp` y añade la siguiente directiva de inclusión:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Debajo de las directivas de inclusión, declara una instancia de `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Esta clase contiene el código para comunicarse con puntos finales web a través de HTTPS.

1. En el método `connectWiFi`, configura el `WiFiClientSecure` para usar el certificado DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Tarea - clasificar una imagen

1. Añade la siguiente línea adicional a la lista `lib_deps` en el archivo `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Esto importa [ArduinoJson](https://arduinojson.org), una biblioteca JSON para Arduino, que se usará para decodificar la respuesta JSON de la API REST.

1. En `config.h`, añade constantes para la URL de predicción y la clave del servicio Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Sustituye `<PREDICTION_URL>` por la URL de predicción de Custom Vision. Sustituye `<PREDICTION_KEY>` por la clave de predicción.

1. En `main.cpp`, añade una directiva de inclusión para la biblioteca ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Añade la siguiente función a `main.cpp`, encima de la función `buttonPressed`.

    ```cpp
    void classifyImage(byte *buffer, uint32_t length)
    {
        HTTPClient httpClient;
        httpClient.begin(client, PREDICTION_URL);
        httpClient.addHeader("Content-Type", "application/octet-stream");
        httpClient.addHeader("Prediction-Key", PREDICTION_KEY);
    
        int httpResponseCode = httpClient.POST(buffer, length);
    
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
    
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());
    
            JsonObject obj = doc.as<JsonObject>();
            JsonArray predictions = obj["predictions"].as<JsonArray>();
    
            for(JsonVariant prediction : predictions) 
            {
                String tag = prediction["tagName"].as<String>();
                float probability = prediction["probability"].as<float>();
    
                char buff[32];
                sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
                Serial.println(buff);
            }
        }
    
        httpClient.end();
    }
    ```

    Este código comienza declarando un `HTTPClient`, una clase que contiene métodos para interactuar con APIs REST. Luego conecta el cliente a la URL de predicción usando la instancia de `WiFiClientSecure` configurada con la clave pública de Azure.

    Una vez conectado, envía encabezados, que son información sobre la solicitud que se hará contra la API REST. El encabezado `Content-Type` indica que la llamada a la API enviará datos binarios en bruto, y el encabezado `Prediction-Key` pasa la clave de predicción de Custom Vision.

    A continuación, se realiza una solicitud POST al cliente HTTP, subiendo un arreglo de bytes. Este contendrá la imagen JPEG capturada por la cámara cuando se llame a esta función.

    > 💁 Las solicitudes POST están diseñadas para enviar datos y obtener una respuesta. Existen otros tipos de solicitudes, como las solicitudes GET, que recuperan datos. Las solicitudes GET son utilizadas por tu navegador web para cargar páginas web.

    La solicitud POST devuelve un código de estado de respuesta. Estos son valores bien definidos, donde 200 significa **OK** - la solicitud POST fue exitosa.

    > 💁 Puedes ver todos los códigos de estado de respuesta en la [página de Lista de códigos de estado HTTP en Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Si se devuelve un 200, el resultado se lee desde el cliente HTTP. Esta es una respuesta en texto de la API REST con los resultados de la predicción en un documento JSON. El JSON tiene el siguiente formato:

    ```jSON
    {
        "id":"45d614d3-7d6f-47e9-8fa2-04f237366a16",
        "project":"135607e5-efac-4855-8afb-c93af3380531",
        "iteration":"04f1c1fa-11ec-4e59-bb23-4c7aca353665",
        "created":"2021-06-10T17:58:58.959Z",
        "predictions":[
            {
                "probability":0.5582016,
                "tagId":"05a432ea-9718-4098-b14f-5f0688149d64",
                "tagName":"ripe"
            },
            {
                "probability":0.44179836,
                "tagId":"bb091037-16e5-418e-a9ea-31c6a2920f17",
                "tagName":"unripe"
            }
        ]
    }
    ```

    La parte importante aquí es el arreglo `predictions`. Este contiene las predicciones, con una entrada para cada etiqueta que incluye el nombre de la etiqueta y la probabilidad. Las probabilidades devueltas son números de punto flotante entre 0 y 1, donde 0 significa un 0% de coincidencia con la etiqueta, y 1 significa un 100% de coincidencia.

    > 💁 Los clasificadores de imágenes devolverán los porcentajes para todas las etiquetas que se hayan utilizado. Cada etiqueta tendrá una probabilidad de que la imagen coincida con esa etiqueta.

    Este JSON se decodifica y las probabilidades de cada etiqueta se envían al monitor serial.

1. En la función `buttonPressed`, reemplaza el código que guarda en la tarjeta SD con una llamada a `classifyImage`, o añádelo después de que la imagen se escriba, pero **antes** de que se elimine el búfer:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Si reemplazas el código que guarda en la tarjeta SD, puedes limpiar tu código eliminando las funciones `setupSDCard` y `saveToSDCard`.

1. Sube y ejecuta tu código. Apunta la cámara hacia alguna fruta y presiona el botón C. Verás la salida en el monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Podrás ver la imagen que se tomó y estos valores en la pestaña **Predictions** en Custom Vision.

    ![Un plátano en Custom Vision predicho como maduro al 56.8% y no maduro al 43.1%](../../../../../translated_images/es/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Puedes encontrar este código en la carpeta [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 ¡Tu programa clasificador de calidad de frutas fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por lograr precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.