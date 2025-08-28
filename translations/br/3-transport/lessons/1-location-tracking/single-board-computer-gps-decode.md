<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-28T03:15:25+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "br"
}
-->
# Decodificar dados de GPS - Hardware IoT Virtual e Raspberry Pi

Nesta parte da lição, você irá decodificar as mensagens NMEA lidas pelo sensor GPS no Raspberry Pi ou Dispositivo IoT Virtual e extrair a latitude e longitude.

## Decodificar dados de GPS

Depois que os dados brutos NMEA forem lidos da porta serial, eles podem ser decodificados usando uma biblioteca NMEA de código aberto.

### Tarefa - decodificar dados de GPS

Programe o dispositivo para decodificar os dados do GPS.

1. Abra o projeto do aplicativo `gps-sensor`, caso ainda não esteja aberto.

1. Instale o pacote Pip `pynmea2`. Este pacote contém o código necessário para decodificar mensagens NMEA.

    ```sh
    pip3 install pynmea2
    ```

1. Adicione o seguinte código às importações no arquivo `app.py` para importar o módulo `pynmea2`:

    ```python
    import pynmea2
    ```

1. Substitua o conteúdo da função `print_gps_data` pelo seguinte:

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

    Se o tipo de sentença da mensagem for `GGA`, então esta é uma mensagem de fixação de posição e será processada. Os valores de latitude e longitude são extraídos da mensagem e convertidos para graus decimais a partir do formato NMEA `(d)ddmm.mmmm`. A função `dm_to_sd` realiza essa conversão.

    Em seguida, a direção da latitude é verificada, e se a latitude for sul, o valor é convertido para um número negativo. O mesmo ocorre com a longitude: se for oeste, ela é convertida para um número negativo.

    Por fim, as coordenadas são exibidas no console, juntamente com o número de satélites usados para obter a localização.

1. Execute o código. Se você estiver usando um dispositivo IoT virtual, certifique-se de que o aplicativo CounterFit esteja em execução e os dados do GPS estejam sendo enviados.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Você pode encontrar este código na pasta [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) ou na pasta [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 O programa do sensor GPS com decodificação de dados foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.