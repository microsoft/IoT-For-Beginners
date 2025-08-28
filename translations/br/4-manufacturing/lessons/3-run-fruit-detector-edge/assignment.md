<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-28T02:45:47+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "br"
}
-->
# Execute outros serviços na borda

## Instruções

Não são apenas classificadores de imagens que podem ser executados na borda; qualquer coisa que possa ser empacotada em um contêiner pode ser implantada em um dispositivo IoT Edge. Código sem servidor executado como Azure Functions, como os gatilhos que você criou em lições anteriores, pode ser executado em contêineres e, portanto, na IoT Edge.

Escolha uma das lições anteriores e tente executar o aplicativo Azure Functions em um contêiner IoT Edge. Você pode encontrar um guia que mostra como fazer isso usando um projeto de aplicativo Functions diferente no [Tutorial: Implantar Azure Functions como módulos IoT Edge na documentação da Microsoft](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Rubrica

| Critério | Exemplar | Adequado | Precisa Melhorar |
| -------- | --------- | -------- | ---------------- |
| Implantar um aplicativo Azure Functions no IoT Edge | Conseguiu implantar um aplicativo Azure Functions no IoT Edge e usá-lo com um dispositivo IoT para executar um gatilho a partir de dados IoT | Conseguiu implantar um aplicativo Functions no IoT Edge, mas não conseguiu fazer o gatilho funcionar | Não conseguiu implantar um aplicativo Functions no IoT Edge |

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.