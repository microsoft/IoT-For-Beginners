<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-25T21:41:18+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "pt"
}
-->
# Medir a humidade do solo - Raspberry Pi

Nesta parte da lição, vais adicionar um sensor capacitivo de humidade do solo ao teu Raspberry Pi e ler os valores obtidos.

## Hardware

O Raspberry Pi necessita de um sensor capacitivo de humidade do solo.

O sensor que vais utilizar é um [Sensor Capacitivo de Humidade do Solo](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), que mede a humidade do solo ao detetar a capacitância do mesmo, uma propriedade que muda conforme a humidade do solo varia. À medida que a humidade do solo aumenta, a voltagem diminui.

Este é um sensor analógico, por isso utiliza um pino analógico e o ADC de 10 bits no Grove Base Hat do Pi para converter a voltagem num sinal digital entre 1 e 1.023. Este sinal é então enviado via I2C através dos pinos GPIO do Pi.

### Ligar o sensor de humidade do solo

O sensor de humidade do solo Grove pode ser ligado ao Raspberry Pi.

#### Tarefa - ligar o sensor de humidade do solo

Liga o sensor de humidade do solo.

![Um sensor Grove de humidade do solo](../../../../../translated_images/pt/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. Insere uma extremidade de um cabo Grove na entrada do sensor de humidade do solo. Só encaixará de uma forma.

1. Com o Raspberry Pi desligado, liga a outra extremidade do cabo Grove à entrada analógica marcada como **A0** no Grove Base Hat ligado ao Pi. Esta entrada é a segunda da direita, na fila de entradas ao lado dos pinos GPIO.

![O sensor Grove de humidade do solo ligado à entrada A0](../../../../../translated_images/pt/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.png)

1. Insere o sensor de humidade do solo na terra. O sensor tem uma 'linha de posição máxima' - uma linha branca ao longo do sensor. Insere o sensor até essa linha, mas não ultrapasses.

![O sensor Grove de humidade do solo na terra](../../../../../translated_images/pt/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## Programar o sensor de humidade do solo

O Raspberry Pi pode agora ser programado para utilizar o sensor de humidade do solo ligado.

### Tarefa - programar o sensor de humidade do solo

Programa o dispositivo.

1. Liga o Pi e espera que ele arranque.

1. Abre o VS Code, diretamente no Pi ou através da extensão Remote SSH.

    > ⚠️ Podes consultar [as instruções para configurar e abrir o VS Code no nightlight - lição 1, se necessário](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. No terminal, cria uma nova pasta no diretório home do utilizador `pi` chamada `soil-moisture-sensor`. Cria um ficheiro nesta pasta chamado `app.py`.

1. Abre esta pasta no VS Code.

1. Adiciona o seguinte código ao ficheiro `app.py` para importar algumas bibliotecas necessárias:

    ```python
    import time
    from grove.adc import ADC
    ```

    A instrução `import time` importa o módulo `time`, que será utilizado mais tarde nesta tarefa.

    A instrução `from grove.adc import ADC` importa o `ADC` das bibliotecas Python do Grove. Esta biblioteca contém código para interagir com o conversor analógico-digital no Base Hat do Pi e ler voltagens de sensores analógicos.

1. Adiciona o seguinte código abaixo para criar uma instância da classe `ADC`:

    ```python
    adc = ADC()
    ```

1. Adiciona um loop infinito que lê este ADC no pino A0 e escreve o resultado na consola. Este loop pode então aguardar 10 segundos entre leituras.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Executa a aplicação Python. Vais ver as medições de humidade do solo escritas na consola. Adiciona água à terra ou remove o sensor da terra e observa a mudança nos valores.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    No exemplo de saída acima, podes ver a voltagem a diminuir à medida que a água é adicionada.

> 💁 Podes encontrar este código na pasta [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 O programa do sensor de humidade do solo foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.