# Chame o seu detetor de objetos a partir do seu dispositivo IoT - Wio Terminal

Depois de publicar o seu detetor de objetos, ele pode ser utilizado a partir do seu dispositivo IoT.

## Copie o projeto do classificador de imagens

A maior parte do seu detetor de stock é semelhante ao classificador de imagens que criou numa lição anterior.

### Tarefa - copiar o projeto do classificador de imagens

1. Ligue a sua ArduCam ao Wio Terminal, seguindo os passos da [lição 2 do projeto de manufatura](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Também pode querer fixar a câmara numa posição estável, por exemplo, pendurando o cabo sobre uma caixa ou lata, ou fixando a câmara a uma caixa com fita adesiva de dupla face.

1. Crie um novo projeto Wio Terminal utilizando o PlatformIO. Dê o nome de `stock-counter` a este projeto.

1. Replique os passos da [lição 2 do projeto de manufatura](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) para capturar imagens com a câmara.

1. Replique os passos da [lição 2 do projeto de manufatura](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) para chamar o classificador de imagens. A maior parte deste código será reutilizada para detetar objetos.

## Alterar o código de um classificador para um detetor de imagens

O código que utilizou para classificar imagens é muito semelhante ao código para detetar objetos. A principal diferença é o URL que é chamado, obtido do Custom Vision, e os resultados da chamada.

### Tarefa - alterar o código de um classificador para um detetor de imagens

1. Adicione a seguinte diretiva de inclusão ao topo do ficheiro `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Renomeie a função `classifyImage` para `detectStock`, tanto o nome da função como a chamada na função `buttonPressed`.

1. Acima da função `detectStock`, declare um limiar para filtrar quaisquer deteções com baixa probabilidade:

    ```cpp
    const float threshold = 0.3f;
    ```

    Ao contrário de um classificador de imagens que retorna apenas um resultado por etiqueta, o detetor de objetos retornará múltiplos resultados, por isso é necessário filtrar os que têm baixa probabilidade.

1. Acima da função `detectStock`, declare uma função para processar as previsões:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    Esta função recebe uma lista de previsões e imprime-as no monitor serial.

1. Na função `detectStock`, substitua o conteúdo do ciclo `for` que percorre as previsões pelo seguinte:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    Este ciclo percorre as previsões, comparando a probabilidade com o limiar. Todas as previsões com uma probabilidade superior ao limiar são adicionadas a uma `list` e passadas para a função `processPredictions`.

1. Carregue e execute o seu código. Aponte a câmara para objetos numa prateleira e pressione o botão C. Verá a saída no monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 Pode ser necessário ajustar o `threshold` para um valor apropriado às suas imagens.

    Poderá ver a imagem capturada e estes valores no separador **Predictions** no Custom Vision.

    ![4 latas de polpa de tomate numa prateleira com previsões para as 4 deteções de 35.8%, 33.5%, 25.7% e 16.6%](../../../../../translated_images/pt-PT/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Pode encontrar este código na pasta [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 O seu programa de contagem de stock foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.