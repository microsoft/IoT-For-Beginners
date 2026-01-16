<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-25T20:47:12+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "pt"
}
-->
# Contar stock a partir do seu dispositivo IoT - Hardware IoT Virtual e Raspberry Pi

Uma combinação das previsões e das suas caixas delimitadoras pode ser usada para contar o stock numa imagem.

## Mostrar caixas delimitadoras

Como um passo útil de depuração, pode não só imprimir as caixas delimitadoras, mas também desenhá-las na imagem que foi gravada no disco quando uma imagem foi capturada.

### Tarefa - imprimir as caixas delimitadoras

1. Certifique-se de que o projeto `stock-counter` está aberto no VS Code e que o ambiente virtual está ativado, caso esteja a usar um dispositivo IoT virtual.

1. Altere a instrução `print` no ciclo `for` para o seguinte, para imprimir as caixas delimitadoras no terminal:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Execute a aplicação com a câmara apontada para algum stock numa prateleira. As caixas delimitadoras serão impressas no terminal, com valores de esquerda, topo, largura e altura entre 0 e 1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Tarefa - desenhar caixas delimitadoras na imagem

1. O pacote Pip [Pillow](https://pypi.org/project/Pillow/) pode ser usado para desenhar em imagens. Instale-o com o seguinte comando:

    ```sh
    pip3 install pillow
    ```

    Se estiver a usar um dispositivo IoT virtual, certifique-se de que executa este comando dentro do ambiente virtual ativado.

1. Adicione a seguinte instrução de importação ao topo do ficheiro `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Isto importa o código necessário para editar a imagem.

1. Adicione o seguinte código ao final do ficheiro `app.py`:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    Este código abre a imagem que foi guardada anteriormente para edição. Em seguida, percorre as previsões, obtendo as caixas delimitadoras e calcula a coordenada inferior direita usando os valores da caixa delimitadora entre 0 e 1. Estes valores são então convertidos para coordenadas da imagem, multiplicando pela dimensão relevante da imagem. Por exemplo, se o valor da esquerda fosse 0.5 numa imagem com 600 píxeis de largura, isso seria convertido para 300 (0.5 x 600 = 300).

    Cada caixa delimitadora é desenhada na imagem usando uma linha vermelha. Finalmente, a imagem editada é guardada, substituindo a imagem original.

1. Execute a aplicação com a câmara apontada para algum stock numa prateleira. Verá o ficheiro `image.jpg` no explorador do VS Code e poderá selecioná-lo para ver as caixas delimitadoras.

    ![4 latas de polpa de tomate com caixas delimitadoras em volta de cada lata](../../../../../translated_images/pt/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

## Contar stock

Na imagem mostrada acima, as caixas delimitadoras têm uma pequena sobreposição. Se esta sobreposição fosse muito maior, as caixas delimitadoras poderiam indicar o mesmo objeto. Para contar os objetos corretamente, é necessário ignorar caixas com uma sobreposição significativa.

### Tarefa - contar stock ignorando sobreposição

1. O pacote Pip [Shapely](https://pypi.org/project/Shapely/) pode ser usado para calcular a interseção. Se estiver a usar um Raspberry Pi, precisará de instalar uma dependência de biblioteca primeiro:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Instale o pacote Pip Shapely:

    ```sh
    pip3 install shapely
    ```

    Se estiver a usar um dispositivo IoT virtual, certifique-se de que executa este comando dentro do ambiente virtual ativado.

1. Adicione a seguinte instrução de importação ao topo do ficheiro `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Isto importa o código necessário para criar polígonos e calcular sobreposições.

1. Acima do código que desenha as caixas delimitadoras, adicione o seguinte código:

    ```python
    overlap_threshold = 0.20
    ```

    Isto define a percentagem de sobreposição permitida antes de as caixas delimitadoras serem consideradas como representando o mesmo objeto. 0.20 define uma sobreposição de 20%.

1. Para calcular a sobreposição usando o Shapely, as caixas delimitadoras precisam de ser convertidas em polígonos Shapely. Adicione a seguinte função para fazer isso:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Esta função cria um polígono usando a caixa delimitadora de uma previsão.

1. A lógica para remover objetos sobrepostos envolve comparar todas as caixas delimitadoras e, se algum par de previsões tiver caixas delimitadoras que se sobreponham mais do que o limite, uma das previsões é eliminada. Para comparar todas as previsões, compara-se a previsão 1 com 2, 3, 4, etc., depois a 2 com 3, 4, etc. O seguinte código faz isso:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    A sobreposição é calculada usando o método `Polygon.intersection` do Shapely, que retorna um polígono com a área de sobreposição. A área é então calculada a partir deste polígono. Este limite de sobreposição não é um valor absoluto, mas precisa de ser uma percentagem da caixa delimitadora, por isso a menor caixa delimitadora é encontrada, e o limite de sobreposição é usado para calcular qual a área de sobreposição que não pode exceder a percentagem definida. Se a sobreposição exceder este valor, a previsão é marcada para eliminação.

    Uma vez que uma previsão foi marcada para eliminação, não precisa de ser verificada novamente, por isso o ciclo interno é interrompido para verificar a próxima previsão. Não se pode eliminar itens de uma lista enquanto se itera sobre ela, por isso as caixas delimitadoras que se sobrepõem mais do que o limite são adicionadas à lista `to_delete`, sendo eliminadas no final.

    Finalmente, o número de stocks é impresso no terminal. Este valor poderia ser enviado para um serviço IoT para alertar se os níveis de stock estiverem baixos. Todo este código é executado antes de as caixas delimitadoras serem desenhadas, por isso verá as previsões de stock sem sobreposições nas imagens geradas.

    > 💁 Este é um método muito simples para remover sobreposições, eliminando apenas o primeiro de um par sobreposto. Para código de produção, seria necessário adicionar mais lógica, como considerar as sobreposições entre múltiplos objetos ou se uma caixa delimitadora está contida dentro de outra.

1. Execute a aplicação com a câmara apontada para algum stock numa prateleira. O resultado indicará o número de caixas delimitadoras sem sobreposições que excedam o limite. Experimente ajustar o valor de `overlap_threshold` para ver previsões a serem ignoradas.

> 💁 Pode encontrar este código na pasta [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) ou [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 O seu programa de contagem de stock foi um sucesso!

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, tenha em atenção que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes da utilização desta tradução.