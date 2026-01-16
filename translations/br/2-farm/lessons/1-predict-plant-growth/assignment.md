<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-28T04:12:46+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "br"
}
-->
# Visualizar dados de GDD usando um Jupyter Notebook

## Instruções

Nesta lição, você coletou dados de GDD usando um sensor IoT. Para obter bons dados de GDD, é necessário coletar dados por vários dias. Para ajudar a visualizar os dados de temperatura e calcular o GDD, você pode usar ferramentas como [Jupyter Notebooks](https://jupyter.org) para analisar os dados.

Comece coletando dados por alguns dias. Você precisará garantir que o código do servidor esteja funcionando o tempo todo enquanto seu dispositivo IoT estiver ativo, seja ajustando as configurações de gerenciamento de energia ou executando algo como [este script Python para manter o sistema ativo](https://github.com/jaqsparow/keep-system-active).

Depois de ter os dados de temperatura, você pode usar o Jupyter Notebook neste repositório para visualizá-los e calcular o GDD. Jupyter Notebooks misturam código e instruções em blocos chamados *células*, geralmente com código em Python. Você pode ler as instruções e executar cada bloco de código, um por vez. Também é possível editar o código. Neste notebook, por exemplo, você pode editar a temperatura base usada para calcular o GDD para sua planta.

1. Crie uma pasta chamada `gdd-calculation`

1. Baixe o arquivo [gdd.ipynb](./code-notebook/gdd.ipynb) e copie-o para a pasta `gdd-calculation`.

1. Copie o arquivo `temperature.csv` criado pelo servidor MQTT.

1. Crie um novo ambiente virtual Python na pasta `gdd-calculation`.

1. Instale alguns pacotes pip para Jupyter Notebooks, junto com bibliotecas necessárias para gerenciar e plotar os dados:

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

    O Jupyter será iniciado e abrirá o notebook no seu navegador. Siga as instruções no notebook para visualizar as temperaturas medidas e calcular os graus-dia de crescimento.

    ![O jupyter notebook](../../../../../translated_images/br/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Rubrica

| Critério | Exemplar | Adequado | Precisa Melhorar |
| -------- | --------- | -------- | ---------------- |
| Capturar dados | Capturar pelo menos 2 dias completos de dados | Capturar pelo menos 1 dia completo de dados | Capturar alguns dados |
| Calcular GDD | Executar o notebook com sucesso e calcular o GDD | Executar o notebook com sucesso | Não conseguir executar o notebook |

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.