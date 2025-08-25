<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-25T23:01:27+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "pt"
}
-->
# Decodificar dados GPS - Hardware IoT Virtual e Raspberry Pi

Nesta parte da lição, vais decodificar as mensagens NMEA lidas do sensor GPS pelo Raspberry Pi ou Dispositivo IoT Virtual e extrair a latitude e a longitude.

## Decodificar dados GPS

Depois de os dados NMEA brutos serem lidos da porta serial, podem ser decodificados utilizando uma biblioteca NMEA de código aberto.

### Tarefa - decodificar dados GPS

Programa o dispositivo para decodificar os dados GPS.

1. Abre o projeto da aplicação `gps-sensor` se ainda não estiver aberto.

1. Instala o pacote Pip `pynmea2`. Este pacote contém código para decodificar mensagens NMEA.

    ```sh
    pip3 install pynmea2
    ```

1. Adiciona o seguinte código às importações no ficheiro `app.py` para importar o módulo `pynmea2`:

    ```python
    import pynmea2
    ```

1. Substitui o conteúdo da função `print_gps_data` pelo seguinte:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    Este código utiliza a biblioteca `pynmea2` para analisar a linha lida da porta serial UART.

    Se o tipo de sentença da mensagem for `GGA`, então trata-se de uma mensagem de fixação de posição e será processada. Os valores de latitude e longitude são lidos da mensagem e convertidos para graus decimais a partir do formato NMEA `(d)ddmm.mmmm`. A função `dm_to_sd` realiza esta conversão.

    Em seguida, verifica-se a direção da latitude, e se a latitude for sul, o valor é convertido para um número negativo. O mesmo acontece com a longitude: se for oeste, é convertida para um número negativo.

    Por fim, as coordenadas são impressas na consola, juntamente com o número de satélites utilizados para obter a localização.

1. Executa o código. Se estiveres a usar um dispositivo IoT virtual, certifica-te de que a aplicação CounterFit está em execução e os dados GPS estão a ser enviados.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Podes encontrar este código na pasta [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) ou na pasta [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 O teu programa do sensor GPS com decodificação de dados foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.