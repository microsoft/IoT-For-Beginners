<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-28T03:14:35+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "br"
}
-->
# Decodificar dados de GPS - Wio Terminal

Nesta parte da lição, você irá decodificar as mensagens NMEA lidas do sensor GPS pelo Wio Terminal e extrair a latitude e a longitude.

## Decodificar dados de GPS

Uma vez que os dados brutos NMEA tenham sido lidos da porta serial, eles podem ser decodificados usando uma biblioteca NMEA de código aberto.

### Tarefa - decodificar dados de GPS

Programe o dispositivo para decodificar os dados do GPS.

1. Abra o projeto do aplicativo `gps-sensor`, caso ainda não esteja aberto.

1. Adicione uma dependência de biblioteca para a biblioteca [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) no arquivo `platformio.ini` do projeto. Esta biblioteca contém o código necessário para decodificar os dados NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. No arquivo `main.cpp`, adicione uma diretiva de inclusão para a biblioteca TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Abaixo da declaração de `Serial3`, declare um objeto TinyGPSPlus para processar as sentenças NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Altere o conteúdo da função `printGPSData` para o seguinte:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    Este código lê o próximo caractere da porta serial UART no decodificador NMEA `gps`. Após cada caractere, ele verifica se o decodificador leu uma sentença válida e, em seguida, verifica se leu uma localização válida. Se a localização for válida, ela será enviada para o monitor serial, junto com o número de satélites que contribuíram para essa fixação.

1. Compile e envie o código para o Wio Terminal.

1. Após o upload, você pode monitorar os dados de localização do GPS usando o monitor serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Você pode encontrar este código na pasta [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 O programa do sensor GPS com decodificação de dados foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.