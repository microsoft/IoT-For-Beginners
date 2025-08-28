<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-28T02:46:02+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "br"
}
-->
# Classifique uma imagem usando um classificador de imagens baseado em IoT Edge - Hardware Virtual de IoT e Raspberry Pi

Nesta parte da lição, você usará o Classificador de Imagens executado no dispositivo IoT Edge.

## Use o classificador IoT Edge

O dispositivo IoT pode ser redirecionado para usar o classificador de imagens do IoT Edge. A URL para o Classificador de Imagens é `http://<IP address or name>/image`, substituindo `<IP address or name>` pelo endereço IP ou nome do host do computador que está executando o IoT Edge.

A biblioteca Python para o Custom Vision funciona apenas com modelos hospedados na nuvem, e não com modelos hospedados no IoT Edge. Isso significa que você precisará usar a API REST para chamar o classificador.

### Tarefa - usar o classificador IoT Edge

1. Abra o projeto `fruit-quality-detector` no VS Code, caso ainda não esteja aberto. Se você estiver usando um dispositivo IoT virtual, certifique-se de que o ambiente virtual está ativado.

1. Abra o arquivo `app.py` e remova as declarações de importação de `azure.cognitiveservices.vision.customvision.prediction` e `msrest.authentication`.

1. Adicione a seguinte importação no início do arquivo:

    ```python
    import requests
    ```

1. Exclua todo o código após a imagem ser salva em um arquivo, a partir de `image_file.write(image.read())` até o final do arquivo.

1. Adicione o seguinte código ao final do arquivo:

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

    Substitua `<URL>` pela URL do seu classificador.

    Este código faz uma solicitação REST POST ao classificador, enviando a imagem como o corpo da solicitação. Os resultados são retornados como JSON, que é decodificado para exibir as probabilidades.

1. Execute seu código, apontando sua câmera para alguma fruta, ou usando um conjunto de imagens apropriado, ou frutas visíveis na sua webcam, caso esteja utilizando hardware virtual de IoT. Você verá a saída no console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Você pode encontrar este código na pasta [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) ou [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Seu programa de classificação de qualidade de frutas foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.