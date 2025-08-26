<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-25T21:09:27+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "pt"
}
-->
# Classificar uma imagem usando um classificador de imagens baseado em IoT Edge - Hardware Virtual IoT e Raspberry Pi

Nesta parte da lição, irá utilizar o Classificador de Imagens a funcionar no dispositivo IoT Edge.

## Utilizar o classificador IoT Edge

O dispositivo IoT pode ser redirecionado para usar o classificador de imagens IoT Edge. O URL para o Classificador de Imagens é `http://<IP address or name>/image`, substituindo `<IP address or name>` pelo endereço IP ou nome do host do computador que está a executar o IoT Edge.

A biblioteca Python para Custom Vision apenas funciona com modelos hospedados na nuvem, e não com modelos hospedados no IoT Edge. Isto significa que terá de usar a API REST para chamar o classificador.

### Tarefa - utilizar o classificador IoT Edge

1. Abra o projeto `fruit-quality-detector` no VS Code, caso ainda não esteja aberto. Se estiver a usar um dispositivo IoT virtual, certifique-se de que o ambiente virtual está ativado.

1. Abra o ficheiro `app.py` e remova as instruções de importação de `azure.cognitiveservices.vision.customvision.prediction` e `msrest.authentication`.

1. Adicione a seguinte importação no topo do ficheiro:

    ```python
    import requests
    ```

1. Apague todo o código após a imagem ser guardada num ficheiro, desde `image_file.write(image.read())` até ao final do ficheiro.

1. Adicione o seguinte código ao final do ficheiro:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Substitua `<URL>` pelo URL do seu classificador.

    Este código faz uma solicitação REST POST ao classificador, enviando a imagem como corpo da solicitação. Os resultados são devolvidos em formato JSON, que é decodificado para imprimir as probabilidades.

1. Execute o seu código, com a câmara apontada para alguma fruta, ou um conjunto de imagens apropriado, ou fruta visível na sua webcam, caso esteja a usar hardware IoT virtual. Verá o resultado no console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Pode encontrar este código na pasta [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) ou [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 O seu programa de classificação de qualidade de fruta foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.