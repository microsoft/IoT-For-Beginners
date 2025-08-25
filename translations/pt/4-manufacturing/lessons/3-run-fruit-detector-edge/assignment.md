<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-25T21:07:50+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "pt"
}
-->
# Executar outros serviços na edge

## Instruções

Não são apenas os classificadores de imagens que podem ser executados na edge; qualquer coisa que possa ser empacotada num contentor pode ser implementada num dispositivo IoT Edge. Código sem servidor, executado como Azure Functions, como os triggers que criaste em lições anteriores, pode ser executado em contentores e, consequentemente, na IoT Edge.

Escolhe uma das lições anteriores e tenta executar a aplicação Azure Functions num contentor IoT Edge. Podes encontrar um guia que mostra como fazer isto utilizando um projeto diferente de aplicação Functions no [Tutorial: Implementar Azure Functions como módulos IoT Edge na documentação da Microsoft](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Rubrica

| Critério | Exemplar | Adequado | Necessita de Melhorias |
| -------- | --------- | -------- | ---------------------- |
| Implementar uma aplicação Azure Functions na IoT Edge | Foi capaz de implementar uma aplicação Azure Functions na IoT Edge e utilizá-la com um dispositivo IoT para executar um trigger a partir de dados IoT | Foi capaz de implementar uma aplicação Functions na IoT Edge, mas não conseguiu ativar o trigger | Não foi capaz de implementar uma aplicação Functions na IoT Edge |

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, é importante notar que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.