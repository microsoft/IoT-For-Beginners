<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-25T21:18:49+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "pt"
}
-->
# Visualizar dados de GDD usando um Jupyter Notebook

## Instruções

Nesta lição, recolheste dados de GDD utilizando um sensor IoT. Para obter bons dados de GDD, é necessário recolher dados durante vários dias. Para ajudar a visualizar os dados de temperatura e calcular o GDD, podes usar ferramentas como [Jupyter Notebooks](https://jupyter.org) para analisar os dados.

Começa por recolher dados durante alguns dias. Terás de garantir que o código do teu servidor está a funcionar durante todo o tempo em que o dispositivo IoT estiver ativo, ajustando as definições de gestão de energia ou executando algo como [este script Python para manter o sistema ativo](https://github.com/jaqsparow/keep-system-active).

Depois de teres os dados de temperatura, podes usar o Jupyter Notebook neste repositório para visualizá-los e calcular o GDD. Os Jupyter Notebooks misturam código e instruções em blocos chamados *células*, frequentemente com código em Python. Podes ler as instruções e executar cada bloco de código, um de cada vez. Também podes editar o código. Neste notebook, por exemplo, podes editar a temperatura base usada para calcular o GDD para a tua planta.

1. Cria uma pasta chamada `gdd-calculation`

1. Faz o download do ficheiro [gdd.ipynb](../../../../../2-farm/lessons/1-predict-plant-growth/code-notebook/gdd.ipynb) e copia-o para a pasta `gdd-calculation`.

1. Copia o ficheiro `temperature.csv` criado pelo servidor MQTT.

1. Cria um novo ambiente virtual Python na pasta `gdd-calculation`.

1. Instala alguns pacotes pip para Jupyter Notebooks, juntamente com bibliotecas necessárias para gerir e visualizar os dados:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Executa o notebook no Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    O Jupyter será iniciado e abrirá o notebook no teu navegador. Segue as instruções no notebook para visualizar as temperaturas medidas e calcular os graus-dia de crescimento.

    ![O Jupyter Notebook](../../../../../translated_images/pt/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Rubrica

| Critério | Exemplar | Adequado | Necessita de Melhorias |
| -------- | --------- | -------- | ---------------------- |
| Recolher dados | Recolher pelo menos 2 dias completos de dados | Recolher pelo menos 1 dia completo de dados | Recolher alguns dados |
| Calcular GDD | Executar o notebook com sucesso e calcular o GDD | Executar o notebook com sucesso | Não conseguir executar o notebook |

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.