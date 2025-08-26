<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-26T15:39:23+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "es"
}
-->
# Conversión de voz a texto - Wio Terminal

En esta parte de la lección, escribirás código para convertir el audio capturado en texto utilizando el servicio de voz.

## Enviar el audio al servicio de voz

El audio puede enviarse al servicio de voz utilizando la API REST. Para usar el servicio de voz, primero necesitas solicitar un token de acceso y luego usar ese token para acceder a la API REST. Estos tokens de acceso expiran después de 10 minutos, por lo que tu código debe solicitarlos regularmente para asegurarse de que siempre estén actualizados.

### Tarea - obtener un token de acceso

1. Abre el proyecto `smart-timer` si no está ya abierto.

1. Agrega las siguientes dependencias de biblioteca al archivo `platformio.ini` para acceder a WiFi y manejar JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Agrega el siguiente código al archivo de encabezado `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Reemplaza `<SSID>` y `<PASSWORD>` con los valores relevantes para tu red WiFi.

    Reemplaza `<API_KEY>` con la clave API de tu recurso del servicio de voz. Reemplaza `<LOCATION>` con la ubicación que usaste al crear el recurso del servicio de voz.

    Reemplaza `<LANGUAGE>` con el nombre de la configuración regional del idioma en el que hablarás, por ejemplo, `en-GB` para inglés o `zn-HK` para cantonés. Puedes encontrar una lista de los idiomas admitidos y sus nombres de configuración regional en la [documentación de soporte de idiomas y voces en Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    La constante `TOKEN_URL` es la URL del emisor del token sin la ubicación. Esto se combinará con la ubicación más adelante para obtener la URL completa.

1. Al igual que al conectarse a Custom Vision, necesitarás usar una conexión HTTPS para conectarte al servicio emisor de tokens. Al final de `config.h`, agrega el siguiente código:

    ```cpp
    const char *TOKEN_CERTIFICATE =
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

    Este es el mismo certificado que usaste al conectarte a Custom Vision.

1. Agrega una inclusión para el archivo de encabezado WiFi y el archivo de configuración en la parte superior del archivo `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Agrega código para conectarte a WiFi en `main.cpp` encima de la función `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

1. Llama a esta función desde la función `setup` después de que se haya establecido la conexión serial:

    ```cpp
    connectWiFi();
    ```

1. Crea un nuevo archivo de encabezado en la carpeta `src` llamado `speech_to_text.h`. En este archivo de encabezado, agrega el siguiente código:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "mic.h"
    
    class SpeechToText
    {
    public:

    private:

    };

    SpeechToText speechToText;
    ```

    Esto incluye algunos archivos de encabezado necesarios para una conexión HTTP, configuración y el archivo de encabezado `mic.h`, y define una clase llamada `SpeechToText`, antes de declarar una instancia de esa clase que se puede usar más adelante.

1. Agrega los siguientes 2 campos a la sección `private` de esta clase:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    El `_token_client` es un cliente WiFi que usa HTTPS y se utilizará para obtener el token de acceso. Este token se almacenará luego en `_access_token`.

1. Agrega el siguiente método a la sección `private`:

    ```cpp
    String getAccessToken()
    {
        char url[128];
        sprintf(url, TOKEN_URL, SPEECH_LOCATION);
    
        HTTPClient httpClient;
        httpClient.begin(_token_client, url);
    
        httpClient.addHeader("Ocp-Apim-Subscription-Key", SPEECH_API_KEY);
        int httpResultCode = httpClient.POST("{}");
    
        if (httpResultCode != 200)
        {
            Serial.println("Error getting access token, trying again...");
            delay(10000);
            return getAccessToken();
        }
    
        Serial.println("Got access token.");
        String result = httpClient.getString();
    
        httpClient.end();
    
        return result;
    }
    ```

    Este código construye la URL para la API del emisor de tokens utilizando la ubicación del recurso de voz. Luego crea un `HTTPClient` para realizar la solicitud web, configurándolo para usar el cliente WiFi configurado con el certificado del emisor de tokens. Establece la clave API como un encabezado para la llamada. Luego realiza una solicitud POST para obtener el certificado, reintentando si encuentra errores. Finalmente, se devuelve el token de acceso.

1. En la sección `public`, agrega un método para obtener el token de acceso. Esto será necesario en lecciones posteriores para convertir texto a voz.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. En la sección `public`, agrega un método `init` que configure el cliente de tokens:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Esto establece el certificado en el cliente WiFi y luego obtiene el token de acceso.

1. En `main.cpp`, agrega este nuevo archivo de encabezado a las directivas de inclusión:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Inicializa la clase `SpeechToText` al final de la función `setup`, después de la llamada a `mic.init` pero antes de que se escriba `Ready` en el monitor serial:

    ```cpp
    speechToText.init();
    ```

### Tarea - leer audio desde la memoria flash

1. En una parte anterior de esta lección, el audio se grabó en la memoria flash. Este audio deberá enviarse a la API REST del servicio de voz, por lo que debe leerse desde la memoria flash. No puede cargarse en un búfer en memoria ya que sería demasiado grande. La clase `HTTPClient` que realiza las llamadas REST puede transmitir datos utilizando un Stream de Arduino, una clase que puede cargar datos en pequeños fragmentos, enviándolos uno a la vez como parte de la solicitud. Cada vez que llamas a `read` en un stream, devuelve el siguiente bloque de datos. Se puede crear un stream de Arduino que lea desde la memoria flash. Crea un nuevo archivo llamado `flash_stream.h` en la carpeta `src` y agrega el siguiente código:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <HTTPClient.h>
    #include <sfud.h>

    #include "config.h"
    
    class FlashStream : public Stream
    {
    public:
        virtual size_t write(uint8_t val)
        {    
        }
    
        virtual int available()
        {
        }
    
        virtual int read()
        {
        }
    
        virtual int peek()
        {
        }
    private:
    
    };
    ```

    Esto declara la clase `FlashStream`, derivada de la clase `Stream` de Arduino. Esta es una clase abstracta: las clases derivadas deben implementar algunos métodos antes de que la clase pueda instanciarse, y estos métodos se definen en esta clase.

    ✅ Lee más sobre Streams de Arduino en la [documentación de Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Agrega los siguientes campos a la sección `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Esto define un búfer temporal para almacenar datos leídos desde la memoria flash, junto con campos para almacenar la posición actual al leer desde el búfer, la dirección actual para leer desde la memoria flash y el dispositivo de memoria flash.

1. En la sección `private`, agrega el siguiente método:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Este código lee desde la memoria flash en la dirección actual y almacena los datos en un búfer. Luego incrementa la dirección, por lo que la siguiente llamada lee el siguiente bloque de memoria. El tamaño del búfer se basa en el fragmento más grande que el `HTTPClient` enviará a la API REST en un momento dado.

    > 💁 Borrar la memoria flash debe hacerse utilizando el tamaño del grano, pero leer no tiene esta restricción.

1. En la sección `public` de esta clase, agrega un constructor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Este constructor configura todos los campos para comenzar a leer desde el inicio del bloque de memoria flash y carga el primer fragmento de datos en el búfer.

1. Implementa el método `write`. Este stream solo leerá datos, por lo que este método no hará nada y devolverá 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementa el método `peek`. Este devuelve los datos en la posición actual sin mover el stream. Llamar a `peek` varias veces siempre devolverá los mismos datos mientras no se lean datos del stream.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementa la función `available`. Esta devuelve cuántos bytes pueden leerse del stream o -1 si el stream está completo. Para esta clase, el máximo disponible no será mayor que el tamaño del fragmento del `HTTPClient`. Cuando este stream se usa en el cliente HTTP, llama a esta función para ver cuántos datos están disponibles y luego solicita esa cantidad de datos para enviar a la API REST. No queremos que cada fragmento sea mayor que el tamaño del fragmento del cliente HTTP, por lo que si hay más disponible, se devuelve el tamaño del fragmento. Si hay menos, se devuelve lo que está disponible. Una vez que se han transmitido todos los datos, se devuelve -1.

    ```cpp
    virtual int available()
    {
        int remaining = BUFFER_SIZE - ((_flash_address - HTTP_TCP_BUFFER_SIZE) + _pos);
        int bytes_available = min(HTTP_TCP_BUFFER_SIZE, remaining);

        if (bytes_available == 0)
        {
            bytes_available = -1;
        }

        return bytes_available;
    }
    ```

1. Implementa el método `read` para devolver el siguiente byte del búfer, incrementando la posición. Si la posición excede el tamaño del búfer, se llena el búfer con el siguiente bloque de la memoria flash y se reinicia la posición.

    ```cpp
    virtual int read()
    {
        int retVal = _buffer[_pos++];

        if (_pos == HTTP_TCP_BUFFER_SIZE)
        {
            populateBuffer();
        }

        return retVal;
    }
    ```

1. En el archivo de encabezado `speech_to_text.h`, agrega una directiva de inclusión para este nuevo archivo de encabezado:

    ```cpp
    #include "flash_stream.h"
    ```

### Tarea - convertir la voz a texto

1. La voz puede convertirse en texto enviando el audio al servicio de voz a través de una API REST. Esta API REST tiene un certificado diferente al del emisor de tokens, por lo que agrega el siguiente código al archivo de encabezado `config.h` para definir este certificado:

    ```cpp
    const char *SPEECH_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQCq+mxcpjxFFB6jvh98dTFzANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwMTCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBAMedcDrkXufP7pxVm1FHLDNA9IjwHaMoaY8arqqZ4Gff4xyr\r\n"
        "RygnavXL7g12MPAx8Q6Dd9hfBzrfWxkF0Br2wIvlvkzW01naNVSkHp+OS3hL3W6n\r\n"
        "l/jYvZnVeJXjtsKYcXIf/6WtspcF5awlQ9LZJcjwaH7KoZuK+THpXCMtzD8XNVdm\r\n"
        "GW/JI0C/7U/E7evXn9XDio8SYkGSM63aLO5BtLCv092+1d4GGBSQYolRq+7Pd1kR\r\n"
        "EkWBPm0ywZ2Vb8GIS5DLrjelEkBnKCyy3B0yQud9dpVsiUeE7F5sY8Me96WVxQcb\r\n"
        "OyYdEY/j/9UpDlOG+vA+YgOvBhkKEjiqygVpP8EZoMMijephzg43b5Qi9r5UrvYo\r\n"
        "o19oR/8pf4HJNDPF0/FJwFVMW8PmCBLGstin3NE1+NeWTkGt0TzpHjgKyfaDP2tO\r\n"
        "4bCk1G7pP2kDFT7SYfc8xbgCkFQ2UCEXsaH/f5YmpLn4YPiNFCeeIida7xnfTvc4\r\n"
        "7IxyVccHHq1FzGygOqemrxEETKh8hvDR6eBdrBwmCHVgZrnAqnn93JtGyPLi6+cj\r\n"
        "WGVGtMZHwzVvX1HvSFG771sskcEjJxiQNQDQRWHEh3NxvNb7kFlAXnVdRkkvhjpR\r\n"
        "GchFhTAzqmwltdWhWDEyCMKC2x/mSZvZtlZGY+g37Y72qHzidwtyW7rBetZJAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQUDyBd16FXlduSzyvQx8J3BM5ygHYwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQAlFvNh7QgXVLAZSsNR2XRmIn9iS8OHFCBA\r\n"
        "WxKJoi8YYQafpMTkMqeuzoL3HWb1pYEipsDkhiMnrpfeYZEA7Lz7yqEEtfgHcEBs\r\n"
        "K9KcStQGGZRfmWU07hPXHnFz+5gTXqzCE2PBMlRgVUYJiA25mJPXfB00gDvGhtYa\r\n"
        "+mENwM9Bq1B9YYLyLjRtUz8cyGsdyTIG/bBM/Q9jcV8JGqMU/UjAdh1pFyTnnHEl\r\n"
        "Y59Npi7F87ZqYYJEHJM2LGD+le8VsHjgeWX2CJQko7klXvcizuZvUEDTjHaQcs2J\r\n"
        "+kPgfyMIOY1DMJ21NxOJ2xPRC/wAh/hzSBRVtoAnyuxtkZ4VjIOh\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Agrega una constante a este archivo para la URL de voz sin la ubicación. Esto se combinará con la ubicación y el idioma más adelante para obtener la URL completa.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. En el archivo de encabezado `speech_to_text.h`, en la sección `private` de la clase `SpeechToText`, define un campo para un cliente WiFi que use el certificado de voz:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. En el método `init`, establece el certificado en este cliente WiFi:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Agrega el siguiente código a la sección `public` de la clase `SpeechToText` para definir un método que convierta voz a texto:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Agrega el siguiente código a este método para crear un cliente HTTP utilizando el cliente WiFi configurado con el certificado de voz y utilizando la URL de voz configurada con la ubicación y el idioma:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Se deben establecer algunos encabezados en la conexión:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Esto establece encabezados para la autorización utilizando el token de acceso, el formato de audio utilizando la frecuencia de muestreo y establece que el cliente espera el resultado como JSON.

1. Después de esto, agrega el siguiente código para realizar la llamada a la API REST:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Esto crea un `FlashStream` y lo utiliza para transmitir datos a la API REST.

1. Debajo de esto, agrega el siguiente código:

    ```cpp
    String text = "";

    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        text = obj["DisplayText"].as<String>();
    }
    else if (httpResponseCode == 401)
    {
        Serial.println("Access token expired, trying again with a new token");
        _access_token = getAccessToken();
        return convertSpeechToText();
    }
    else
    {
        Serial.print("Failed to convert text to speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Este código verifica el código de respuesta.

    Si es 200, el código para éxito, entonces se recupera el resultado, se decodifica desde JSON y la propiedad `DisplayText` se establece en la variable `text`. Esta es la propiedad donde se devuelve la versión en texto de la voz.

    Si el código de respuesta es 401, entonces el token de acceso ha expirado (estos tokens solo duran 10 minutos). Se solicita un nuevo token de acceso y se realiza nuevamente la llamada.

    De lo contrario, se envía un error al monitor serial y la variable `text` queda vacía.

1. Agrega el siguiente código al final de este método para cerrar el cliente HTTP y devolver el texto:

    ```cpp
    httpClient.end();

    return text;
    ```

1. En `main.cpp`, llama a este nuevo método `convertSpeechToText` en la función `processAudio`, luego registra la voz convertida en el monitor serial:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Compila este código, súbelo a tu Wio Terminal y pruébalo a través del monitor serial. Una vez que veas `Ready` en el monitor serial, presiona el botón C (el de la izquierda, más cercano al interruptor de encendido) y habla. Se capturarán 4 segundos de audio y luego se convertirán en texto.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    ```

> 💁 Puedes encontrar este código en la carpeta [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 ¡Tu programa de conversión de voz a texto fue un éxito!

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.