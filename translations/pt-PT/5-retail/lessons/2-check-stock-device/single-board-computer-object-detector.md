# Chame o seu detector de objetos a partir do seu dispositivo IoT - Hardware IoT Virtual e Raspberry Pi

Depois de publicar o seu detector de objetos, ele pode ser utilizado a partir do seu dispositivo IoT.

## Copie o projeto do classificador de imagens

A maior parte do seu detector de stock é semelhante ao classificador de imagens que criou numa lição anterior.

### Tarefa - copiar o projeto do classificador de imagens

1. Crie uma pasta chamada `stock-counter` no seu computador, caso esteja a usar um dispositivo IoT virtual, ou no seu Raspberry Pi. Se estiver a usar um dispositivo IoT virtual, certifique-se de configurar um ambiente virtual.

1. Configure o hardware da câmara.

    * Se estiver a usar um Raspberry Pi, será necessário instalar a PiCamera. Também pode fixar a câmara numa posição estável, por exemplo, pendurando o cabo sobre uma caixa ou lata, ou fixando a câmara a uma caixa com fita adesiva dupla face.
    * Se estiver a usar um dispositivo IoT virtual, será necessário instalar o CounterFit e o CounterFit PyCamera shim. Caso vá usar imagens estáticas, capture algumas imagens que o seu detector de objetos ainda não tenha visto. Se for usar a sua webcam, certifique-se de que está posicionada de forma a visualizar o stock que está a detetar.

1. Replique os passos da [lição 2 do projeto de manufatura](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) para capturar imagens com a câmara.

1. Replique os passos da [lição 2 do projeto de manufatura](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) para chamar o classificador de imagens. A maior parte deste código será reutilizada para detetar objetos.

## Alterar o código de um classificador para um detector de imagens

O código que utilizou para classificar imagens é muito semelhante ao código para detetar objetos. A principal diferença está no método chamado no SDK do Custom Vision e nos resultados da chamada.

### Tarefa - alterar o código de um classificador para um detector de imagens

1. Elimine as três linhas de código que classificam a imagem e processam as previsões:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Remova estas três linhas.

1. Adicione o seguinte código para detetar objetos na imagem:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Este código chama o método `detect_image` no predictor para executar o detector de objetos. Em seguida, reúne todas as previsões com uma probabilidade acima de um limite, imprimindo-as no console.

    Ao contrário de um classificador de imagens que retorna apenas um resultado por etiqueta, o detector de objetos retornará múltiplos resultados, por isso é necessário filtrar os que têm baixa probabilidade.

1. Execute este código e ele capturará uma imagem, enviando-a para o detector de objetos, e imprimirá os objetos detetados. Se estiver a usar um dispositivo IoT virtual, certifique-se de que tem uma imagem apropriada configurada no CounterFit ou que a sua webcam está selecionada. Se estiver a usar um Raspberry Pi, certifique-se de que a sua câmara está apontada para os objetos numa prateleira.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Pode ser necessário ajustar o `threshold` para um valor apropriado às suas imagens.

    Poderá ver a imagem capturada e estes valores na aba **Predictions** no Custom Vision.

    ![4 latas de polpa de tomate numa prateleira com previsões para as 4 deteções de 35.8%, 33.5%, 25.7% e 16.6%](../../../../../translated_images/pt-PT/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Pode encontrar este código na pasta [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) ou [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 O seu programa de contador de stock foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.