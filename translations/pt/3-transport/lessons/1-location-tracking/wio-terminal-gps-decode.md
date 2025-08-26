<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-25T23:02:53+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "pt"
}
-->
# Decodificar dados GPS - Wio Terminal

Nesta parte da lição, vais decodificar as mensagens NMEA lidas do sensor GPS pelo Wio Terminal e extrair a latitude e a longitude.

## Decodificar dados GPS

Depois de os dados NMEA brutos serem lidos da porta série, podem ser decodificados utilizando uma biblioteca NMEA de código aberto.

### Tarefa - decodificar dados GPS

Programa o dispositivo para decodificar os dados GPS.

1. Abre o projeto da aplicação `gps-sensor` se ainda não estiver aberto.

1. Adiciona uma dependência de biblioteca para a biblioteca [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) no ficheiro `platformio.ini` do projeto. Esta biblioteca contém código para decodificar dados NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. No ficheiro `main.cpp`, adiciona uma diretiva de inclusão para a biblioteca TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Abaixo da declaração de `Serial3`, declara um objeto TinyGPSPlus para processar as sentenças NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Altera o conteúdo da função `printGPSData` para o seguinte:

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

    Este código lê o próximo carácter da porta série UART para o decodificador NMEA `gps`. Após cada carácter, verifica se o decodificador leu uma sentença válida e, em seguida, verifica se leu uma localização válida. Se a localização for válida, envia-a para o monitor série, juntamente com o número de satélites que contribuíram para esta fixação.

1. Compila e carrega o código para o Wio Terminal.

1. Depois de carregado, podes monitorizar os dados de localização GPS utilizando o monitor série.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Podes encontrar este código na pasta [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 O teu programa do sensor GPS com decodificação de dados foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.