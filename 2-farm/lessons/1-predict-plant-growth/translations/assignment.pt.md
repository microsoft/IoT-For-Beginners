# Visualize dados GDD usando um Jupyter Notebook

## Instruções

Nesta lição, você coletou dados do GDD usando um sensor de IoT. Para obter bons dados do GDD, você precisa coletar dados por vários dias. Para ajudar a visualizar os dados de temperatura e calcular o GDD, você pode usar ferramentas como [Jupyter Notebooks](https://jupyter.org) para analisar os dados.

Comece coletando dados por alguns dias. Você precisará garantir que seu código de servidor esteja em execução o tempo todo em que seu dispositivo IoT estiver em execução, ajustando suas configurações de gerenciamento de energia ou executando algo como [este script em python para manter o sistema ativo](https://github.com/jaqsparow/keep-system-active).

Depois de ter os dados de temperatura, você pode usar o Jupyter Notebook neste repositório para visualizá-los e calcular o GDD. Os notebooks Jupyter misturam código e instruções em blocos chamados *cells*, geralmente código em Python. Você pode ler as instruções e executar cada bloco de código, bloco por bloco. Você também pode editar o código. Neste notebook, por exemplo, você pode editar a temperatura base usada para calcular o GDD para sua planta.

1. Crie uma pasta chamada `gdd-calculation`

1. Baixe o arquivo [gdd.ipynb](./../code-notebook/gdd.ipynb) e copie-o para a pasta `gdd-calculation`.

1. Copie o arquivo `temperature.csv` criado pelo servidor MQTT

1. Crie um novo ambiente virtual Python na pasta `gdd-calculation`.

1. Instale alguns pacotes pip para notebooks Jupyter, juntamente com as bibliotecas necessárias para gerenciar e plotar os dados:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Execute o notebook no Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    O Jupyter iniciará e abrirá o notebook em seu navegador. Trabalhe com as instruções no notebook para visualizar as temperaturas medidas e calcular os graus-dia crescentes.

    ![O notebook jupyter](../../../../images/gdd-jupyter-notebook.png)

## Rubrica

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Capture dados | Capture ao menos 2 dias completos de dados | Capture ao menos 1 dia completo de dados | Capture algum dado |
| Calcule o GDD | Execute o notebook com sucesso e calcule o GDD | Execute o notebook com sucesso | Não consigo executar o notebook |
