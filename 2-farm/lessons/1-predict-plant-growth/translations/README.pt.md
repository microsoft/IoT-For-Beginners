# Preveja o crescimento da planta com IoT

![Uma visão geral do sketchnote desta lição](../../../../sketchnotes/lesson-5.jpg)

> Sketchnote por [Nitya Narasimhan](https://github.com/nitya). Clique na imagem para uma versão maior.

## Teste pré-aula

[Teste pré-aula](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Introdução

As plantas precisam de certas coisas para crescer - água, dióxido de carbono, nutrientes, luz e calor. Nesta lição, você aprenderá a calcular as taxas de crescimento e maturidade das plantas medindo a temperatura do ar.

Nesta lição abordaremos:

* [Agricultura digital](#agricultura-digital)
* [Por que a temperatura é importante na agricultura?](#por-que-a-temperatura-é-importante-na-agricultura?)
* [Medir a temperatura ambiente](#medir-a-temperatura-ambiente)
* [Graus-dias crescentes (GDD)](#graus-dias-crescentes)
* [Calcular GDD usando dados do sensor de temperatura](#calculate-gdd-using-temperature-sensor-data)

## Agricultura Digital 

A Agricultura Digital está transformando a forma como cultivamos, usando ferramentas para coletar, armazenar e analisar dados da agricultura. Estamos atualmente em um período descrito como a 'Quarta Revolução Industrial' pelo Fórum Econômico Mundial, e a ascensão da agricultura digital foi rotulada como a 'Quarta Revolução Agrícola', ou 'Agricultura 4.0'.

> 🎓 O termo Agricultura Digital também inclui toda a 'cadeia de valor da agricultura', que é toda a jornada da fazenda à mesa. Inclui o rastreamento da qualidade dos produtos à medida que os alimentos são enviados e processados, sistemas de armazém e comércio eletrônico, até mesmo aplicativos de aluguel de tratores!

Essas mudanças permitem que os agricultores aumentem os rendimentos, usem menos fertilizantes e pesticidas e reguem com mais eficiência. Embora usados principalmente em nações mais ricas, sensores e outros dispositivos estão diminuindo lentamente de preço, tornando-os mais acessíveis em países em desenvolvimento.

Algumas técnicas habilitadas pela agricultura digital são:

* Medição de temperatura - a medição de temperatura permite que os agricultores prevejam o crescimento e a maturidade das plantas.
* Rega automatizada - medindo a umidade do solo e ligando os sistemas de irrigação quando o solo está muito seco, em vez de regar com tempo. A rega cronometrada pode levar a que as colheitas sejam subregadas durante um período quente e seco ou regadas em excesso durante a chuva. Ao regar apenas quando o solo precisa, os agricultores podem otimizar o uso da água.
* Controle de pragas - os agricultores podem usar câmeras em robôs automatizados ou drones para verificar se há pragas e, em seguida, aplicar pesticidas apenas onde necessário, reduzindo a quantidade de pesticidas usados e reduzindo o escoamento de pesticidas no abastecimento de água local.

✅ Pesquise. Que outras técnicas são usadas para melhorar os rendimentos agrícolas?

> 🎓 O termo 'Agricultura de Precisão' é usado para definir a observação, medição e resposta às culturas por campo, ou mesmo em partes de um campo. Isso inclui medir os níveis de água, nutrientes e pragas e responder com precisão, como regar apenas uma pequena parte de um campo.

## Por que a temperatura é importante na agricultura?

Ao aprender sobre plantas, a maioria dos alunos é ensinada sobre a necessidade de água, luz, dióxido de carbono (CO<sub>2</sub>) e nutrientes. As plantas também precisam de calor para crescer - é por isso que as plantas florescem na primavera à medida que a temperatura aumenta, por que os flocos de neve ou narcisos podem brotar cedo devido a um curto período de calor e por que as estufas e estufas são tão boas para fazer as plantas crescerem.

> 🎓 Estufas e estufas fazem um trabalho semelhante, mas com uma diferença importante. As estufas são aquecidas artificialmente e permitem que os agricultores controlem as temperaturas com mais precisão, as estufas dependem do sol para se aquecer e geralmente o único controle são as janelas ou outras aberturas para deixar o calor sair.

As plantas têm uma temperatura base ou mínima, temperatura ótima e temperatura máxima, todas baseadas nas temperaturas médias diárias.

* Temperatura base - esta é a temperatura média diária mínima necessária para que uma planta cresça.
* Temperatura ideal - esta é a melhor temperatura média diária para obter o maior crescimento.
* Temperatura máxima - É a temperatura máxima que uma planta pode suportar. Acima disso, a planta interromperá seu crescimento na tentativa de conservar a água e permanecer viva.

> 💁 Estas são temperaturas médias, calculadas sobre as temperaturas diárias e noturnas. As plantas também precisam de temperaturas diferentes dia e noite para ajudá-las a fotossintetizar com mais eficiência e economizar energia à noite.

Cada espécie de planta tem valores diferentes para sua base, ótima e máxima. É por isso que algumas plantas prosperam em países quentes e outras em países mais frios.

✅ Pesquise. Para quaisquer plantas que você tenha em seu jardim, escola ou parque local, veja se consegue encontrar a temperatura base.

![Um gráfico mostrando a taxa de crescimento aumentando à medida que a temperatura aumenta e depois caindo à medida que a temperatura fica muito alta](../../../../images/plant-growth-temp-graph.png)

O gráfico acima mostra um exemplo de gráfico de taxa de crescimento para temperatura. Até a temperatura base não há crescimento. A taxa de crescimento aumenta até a temperatura ótima, depois cai após atingir esse pico. Na temperatura máxima o crescimento para.

A forma deste gráfico varia de espécie de planta para espécie de planta. Alguns têm quedas mais acentuadas acima do ótimo, alguns têm aumentos mais lentos da base para o ótimo.

> 💁 Para um agricultor obter o melhor crescimento, ele precisará conhecer os três valores de temperatura e entender a forma dos gráficos para as plantas que estão cultivando.

Se um agricultor tem controle de temperatura, por exemplo, em uma estufa comercial, ele pode otimizar suas plantas. Uma estufa comercial que cultiva tomates, por exemplo, terá a temperatura definida para cerca de 25°C durante o dia e 20°C à noite para obter o crescimento mais rápido.

> 🍅 A combinação dessas temperaturas com luzes artificiais, fertilizantes e níveis controlados de CO<sub>2</sub> significa que os produtores comerciais podem cultivar e colher durante todo o ano.

## Medir a temperatura ambiente

Sensores de temperatura podem ser usados com dispositivos IoT para medir a temperatura ambiente.

### Tarefa - medir a temperatura

Trabalhe com o guia relevante para monitorar as temperaturas usando seu dispositivo IoT:

* [Arduino - Wio Terminal](wio-terminal-temp.pt.md)
* [Single-board computer - Raspberry Pi](pi-temp.pt.md)
* [Single-board computer - Virtual device](virtual-device-temp.pt.md)

## Graus-dias crescentes

Os graus-dia de crescimento (também conhecidos como unidades de graus de crescimento) são uma maneira de medir o crescimento das plantas com base na temperatura. Assumindo que uma planta tem bastante água, nutrientes e CO<sub>2</sub>, a temperatura determina a taxa de crescimento.

Os graus-dia crescentes, ou GDD, são calculados por dia como a temperatura média em Celsius para um dia acima da temperatura base da planta. Cada planta precisa de um certo número de GDD para crescer, florescer ou produzir e amadurecer uma safra. Quanto mais GDD a cada dia, mais rápido a planta crescerá.

> 🇧🇷 Para os americanos, graus-dia crescentes também podem ser calculados usando Fahrenheit. 5 GDD<sup>C</sup> (graus-dias crescentes em Celsius) é o equivalente a 9 GDD<sup>F</sup> (graus-dias crescentes em Fahrenheit).

A fórmula completa para o GDD é um pouco complicada, mas existe uma equação simplificada que costuma ser usada como uma boa aproximação:

![GDD = T max + T min dividido por 2, tudo menos T base](../../../../images/gdd-calculation.png)

* **GDD** - este é o número de graus-dia crescentes
* **T<sub>max</sub>** - esta é a temperatura máxima diária em graus Celsius
* **T<sub>min</sub>** - esta é a temperatura mínima diária em graus Celsius
* **T<sub>base</sub>** - esta é a temperatura base das plantas em graus Celsius

> 💁 Existem variações que lidam com T<sub>max</sub> acima de 30°C ou T<sub>min</sub> abaixo de T<sub>base</sub>, mas vamos ignorá-las por enquanto.

### Exemplo - Milho 🌽

Dependendo da variedade, o milho (ou milho) precisa entre 800 e 2.700 GDD para amadurecer, com temperatura base de 10°C.

No primeiro dia acima da temperatura base, foram medidas as seguintes temperaturas:

| Measurement | Temp °C |
| :---------- | :-----: |
| Máximo     | 16      |
| Mínimo     | 12      |

Colocando esses números em nosso cálculo:

* T<sub>max</sub> = 16
* T<sub>min</sub> = 12
* T<sub>base</sub> = 10

Isso dá um cálculo de:

![GDD = 16 + 12 dividido por 2, tudo menos 10, resultando 4](../../../../images/gdd-calculation-corn.png)

O milho recebeu 4 GDD naquele dia. Assumindo uma variedade de milho que precisa de 800 dias de GDD para amadurecer, precisará de outros 796 GDD para atingir a maturidade.

✅ Pesquise. Para quaisquer plantas que você tenha em seu jardim, escola ou parque local, veja se consegue encontrar o número de GDD necessário para atingir a maturidade ou produzir colheitas.

## Calcular GDD usando dados do sensor de temperatura

As plantas não crescem em datas fixas - por exemplo, você não pode plantar uma semente e saber que a planta dará frutos exatamente 100 dias depois. Em vez disso, como agricultor, você pode ter uma ideia aproximada de quanto tempo uma planta leva para crescer, então você verificaria diariamente para ver quando as colheitas estavam prontas.

Isso tem um enorme impacto trabalhista em uma grande fazenda e corre o risco de o agricultor perder colheitas que estão prontas inesperadamente cedo. Ao medir as temperaturas, o agricultor pode calcular o GDD que uma planta recebeu, permitindo que ele verifique apenas próximo à maturidade esperada.

Ao coletar dados de temperatura usando um dispositivo IoT, um agricultor pode ser notificado automaticamente quando as plantas estiverem próximas da maturidade. Uma arquitetura típica para isso é fazer com que os dispositivos IoT meçam a temperatura e, em seguida, publiquem esses dados de telemetria pela Internet usando algo como MQTT. O código do servidor então escuta esses dados e os salva em algum lugar, como em um banco de dados. Isso significa que os dados podem ser analisados ​​posteriormente, como um trabalho noturno para calcular o GDD do dia, totalizar o GDD para cada safra até o momento e alertar se uma planta estiver próxima da maturidade.

![Os dados de telemetria são enviados para um servidor e salvos em um banco de dados](../../../../images/save-telemetry-database.png)

O código do servidor também pode aumentar os dados adicionando informações extras. Por exemplo, o dispositivo IoT pode publicar um identificador para indicar qual é o dispositivo, e o código do servidor pode usar isso para pesquisar a localização do dispositivo e quais culturas ele está monitorando. Ele também pode adicionar dados básicos, como a hora atual, pois alguns dispositivos IoT não possuem o hardware necessário para acompanhar uma hora exata ou exigem código adicional para ler a hora atual pela Internet.

✅ Por que você acha que campos diferentes podem ter temperaturas diferentes?

### Tarefa - publicar informações de temperatura

Trabalhe com o guia relevante para publicar dados de temperatura no MQTT usando seu dispositivo IoT para que possam ser analisados posteriormente:

* [Arduino - Wio Terminal](wio-terminal-temp-publish.pt.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-temp-publish.pt.md)

### Tarefa - capturar e armazenar as informações de temperatura

Depois que o dispositivo IoT estiver publicando a telemetria, o código do servidor pode ser escrito para assinar esses dados e armazená-los. Em vez de salvá-lo em um banco de dados, o código do servidor o salvará em um arquivo de valores separados por vírgula (CSV). Os arquivos CSV armazenam dados como linhas de valores como texto, com cada valor separado por uma vírgula e cada registro em uma nova linha. Eles são uma maneira conveniente, legível e bem suportada de salvar dados como um arquivo.

O arquivo CSV terá duas colunas - *data* e *temperatura*. A coluna *data* é definida como a data e hora atuais em que a mensagem foi recebida pelo servidor, a *temperatura* vem da mensagem de telemetria.

1. Repita as etapas na lição 4 para criar o código do servidor para assinar a telemetria. Você não precisa adicionar código para publicar comandos.

    Os passos para isso são:

    * Configurar e ativar um ambiente virtual Python

    * Instale o pacote pip paho-mqtt

    * Escreva o código para escutar mensagens MQTT publicadas no tópico de telemetria

      > ⚠️ Você pode consultar [as instruções na lição 4 para criar um aplicativo Python para receber telemetria, se necessário](../../../../1-getting-started/lessons/4-connect-internet/translations/README.pt.md#receber-telemetria-do-broker-mqtt).

    Nomeie a pasta para este projeto `temperature-sensor-server`.

1. Certifique-se de `client_name` reflete este projeto:

    ```cpp
    client_name = id + 'temperature_sensor_server'
    ```

1. Adicione as seguintes importações ao topo do arquivo, abaixo das importações existentes:

    ```python
    from os import path
    import csv
    from datetime import datetime
    ```

   Isso importa uma biblioteca para leitura de arquivos, uma biblioteca para interagir com arquivos CSV e uma biblioteca para ajudar com datas e horas.

1. Adicione o seguinte código antes da função `handle_telemetry`:

    ```python
    temperature_file_name = 'temperature.csv'
    fieldnames = ['date', 'temperature']
    
    if not path.exists(temperature_file_name):
        with open(temperature_file_name, mode='w') as csv_file:
            writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
            writer.writeheader()
    ```

    Esse código declara algumas constantes para o nome do arquivo no qual gravar e o nome dos cabeçalhos de coluna do arquivo CSV. A primeira linha de um arquivo CSV tradicionalmente contém cabeçalhos de coluna separados por vírgulas.

     O código então verifica se o arquivo CSV já existe. Se não existir, será criado com os cabeçalhos das colunas na primeira linha.

1. Adicione o seguinte código ao final da função `handle_telemetry`:

    ```python
    with open(temperature_file_name, mode='a') as temperature_file:        
        temperature_writer = csv.DictWriter(temperature_file, fieldnames=fieldnames)
        temperature_writer.writerow({'date' : datetime.now().astimezone().replace(microsecond=0).isoformat(), 'temperature' : payload['temperature']})
    ```

    Esse código abre o arquivo CSV e anexa uma nova linha no final. A linha tem os dados atuais e a hora formatados em um formato legível, seguido pela temperatura recebida do dispositivo IoT. Os dados são armazenados no [formato ISO 8601](https://wikipedia.org/wiki/ISO_8601) com o fuso horário, mas sem microssegundos.

1. Execute este código da mesma forma que antes, certificando-se de que seu dispositivo IoT está enviando dados. Um arquivo CSV chamado `temperature.csv` será criado na mesma pasta. Se você visualizá-lo, verá as medições de data/hora e temperatura:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Execute este código por um tempo para capturar dados. Idealmente, você deve executar isso por um dia inteiro para coletar dados suficientes para cálculos de GDD.

    > 💁 Se você estiver usando o dispositivo IoT virtual, marque a caixa de seleção aleatória e defina um intervalo para evitar obter a mesma temperatura toda vez que o valor da temperatura for retornado.
    ![Marque a caixa de seleção aleatória e defina um intervalo](../../../../images/select-the-random-checkbox-and-set-a-range.png) 

    > 💁 Se você quiser executar isso por um dia inteiro, precisará garantir que o computador no qual o código do servidor está sendo executado não entre no modo de suspensão, alterando suas configurações de energia ou executando algo como [este script em python para manter o sistema ativo](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Você pode encontrar este código na pasta [code-server/temperature-sensor-server](../code-server/temperature-sensor-server).

### Tarefa - calcular GDD usando os dados armazenados

Uma vez que o servidor tenha capturado os dados de temperatura, o GDD de uma planta pode ser calculado.

As etapas para fazer isso manualmente são:

1. Encontre a temperatura base para a planta. Por exemplo, para morangos a temperatura base é 10°C.

1. A partir do arquivo `temperature.csv`, encontre as temperaturas mais altas e mais baixas do dia

1. Use o cálculo de GDD fornecido anteriormente para calcular o GDD

Por exemplo, se a temperatura mais alta do dia for 25°C e a mais baixa for 12°C:

![GDD = 25 + 12 dividido por 2, então subtrair 10 do resultado retornando 8.5](../../../../images/gdd-calculation-strawberries.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Portanto, os morangos receberam **8,5** GDD. Morangos precisam de cerca de 250 GDD para dar frutos, então ainda falta um tempo.
---

## 🚀 Desafio

As plantas precisam de mais do que calor para crescer. Que outras coisas são necessárias?

Para estes, descubra se existem sensores que possam medi-los. E os atuadores para controlar esses níveis? Como você montaria um ou mais dispositivos IoT para otimizar o crescimento da planta?

## Questionário pós-aula

[Questionário pós-aula](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Revisão e autoestudo

* Leia mais sobre agricultura digital na [página da Wikipedia sobre agricultura digital](https://wikipedia.org/wiki/Digital_agriculture). Leia também mais sobre agricultura de precisão na [página da Wikipedia sobre agricultura de precisão](https://wikipedia.org/wiki/Precision_agriculture).
* O cálculo completo dos graus-dias de crescimento é mais complicado do que o simplificado fornecido aqui. Leia mais sobre a equação mais complicada e como lidar com temperaturas abaixo da linha de base na [página da Wikipedia sobre Growing Degree Day](https://wikipedia.org/wiki/Growing_degree-day).
* A comida pode ser escassa no futuro, mesmo que ainda usemos os mesmos métodos para a agricultura. Saiba mais sobre técnicas agrícolas de alta tecnologia neste [Vídeo Hi-Tech Farms of Future no YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Tarefa

[Visualize dados GDD usando um Jupyter Notebook](assignment.pt.md)
