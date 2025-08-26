<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-25T23:10:02+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "pt"
}
-->
# Investigar ligações de funções

## Instruções

As ligações de funções permitem que o seu código salve blobs no armazenamento de blobs ao retorná-los da função `main`. A conta de armazenamento Azure, a coleção e outros detalhes são configurados no ficheiro `function.json`.

Ao trabalhar com o Azure ou outras tecnologias da Microsoft, a melhor fonte de informação é [a documentação da Microsoft em docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). Nesta tarefa, será necessário ler a documentação sobre ligações de funções do Azure para entender como configurar a ligação de saída.

Algumas páginas para começar são:

* [Conceitos de gatilhos e ligações do Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Visão geral das ligações de armazenamento de blobs para Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Ligação de saída de armazenamento de blobs para Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Rubrica

| Critério | Exemplar | Adequado | Necessita Melhorias |
| -------- | --------- | -------- | ------------------- |
| Configurar a ligação de saída para armazenamento de blobs | Foi capaz de configurar a ligação de saída, retornar o blob e armazená-lo com sucesso no armazenamento de blobs | Foi capaz de configurar a ligação de saída ou retornar o blob, mas não conseguiu armazená-lo com sucesso no armazenamento de blobs | Não foi capaz de configurar a ligação de saída |

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.