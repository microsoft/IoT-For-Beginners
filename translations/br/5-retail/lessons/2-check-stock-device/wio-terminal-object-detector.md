<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-28T03:49:26+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "br"
}
-->
# Chame seu detector de objetos a partir do seu dispositivo IoT - Wio Terminal

Depois que seu detector de objetos for publicado, ele poderá ser usado a partir do seu dispositivo IoT.

## Copie o projeto do classificador de imagens

A maior parte do seu detector de estoque é semelhante ao classificador de imagens que você criou em uma lição anterior.

### Tarefa - copie o projeto do classificador de imagens

1. Conecte sua ArduCam ao Wio Terminal, seguindo os passos da [lição 2 do projeto de fabricação](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Você também pode querer fixar a câmera em uma posição única, por exemplo, pendurando o cabo sobre uma caixa ou lata, ou fixando a câmera em uma caixa com fita dupla face.

1. Crie um novo projeto para o Wio Terminal usando o PlatformIO. Chame este projeto de `stock-counter`.

1. Replique os passos da [lição 2 do projeto de fabricação](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) para capturar imagens da câmera.

1. Replique os passos da [lição 2 do projeto de fabricação](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) para chamar o classificador de imagens. A maior parte deste código será reutilizada para detectar objetos.

## Alterar o código de um classificador para um detector de imagens

O código que você usou para classificar imagens é muito semelhante ao código para detectar objetos. A principal diferença é a URL que é chamada, obtida do Custom Vision, e os resultados da chamada.

### Tarefa - alterar o código de um classificador para um detector de imagens

1. Adicione a seguinte diretiva de inclusão no topo do arquivo `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Renomeie a função `classifyImage` para `detectStock`, tanto o nome da função quanto a chamada na função `buttonPressed`.

1. Acima da função `detectStock`, declare um limite para filtrar quaisquer detecções com baixa probabilidade:

    ```cpp
    const float threshold = 0.3f;
    ```

    Diferentemente de um classificador de imagens que retorna apenas um resultado por tag, o detector de objetos retornará múltiplos resultados, então qualquer um com baixa probabilidade precisa ser filtrado.

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

    Esta função recebe uma lista de previsões e as imprime no monitor serial.

1. Na função `detectStock`, substitua o conteúdo do `for` loop que percorre as previsões pelo seguinte:

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

    Este loop percorre as previsões, comparando a probabilidade com o limite. Todas as previsões que têm uma probabilidade maior que o limite são adicionadas a uma `list` e passadas para a função `processPredictions`.

1. Faça o upload e execute seu código. Aponte a câmera para objetos em uma prateleira e pressione o botão C. Você verá a saída no monitor serial:

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

    > 💁 Pode ser necessário ajustar o `threshold` para um valor apropriado para suas imagens.

    Você poderá ver a imagem que foi capturada e esses valores na aba **Predictions** no Custom Vision.

    ![4 latas de extrato de tomate em uma prateleira com previsões para as 4 detecções de 35.8%, 33.5%, 25.7% e 16.6%](../../../../../translated_images/br/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Você pode encontrar este código na pasta [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Seu programa de contador de estoque foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.