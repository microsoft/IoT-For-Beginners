<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-25T21:33:57+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "pt"
}
-->
# Adicionar controlo manual ao relé

## Instruções

Código serverless pode ser acionado por diversos eventos, incluindo pedidos HTTP. Pode usar triggers HTTP para adicionar um controlo manual ao relé, permitindo que alguém ligue ou desligue o relé através de um pedido web.

Para esta tarefa, precisa de adicionar dois triggers HTTP à sua Functions App para ligar e desligar o relé, reutilizando o que aprendeu nesta lição para enviar comandos ao dispositivo.

Algumas dicas:

* Pode adicionar um trigger HTTP à sua Functions App existente com o seguinte comando:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Substitua `<trigger name>` pelo nome do seu trigger HTTP. Use algo como `relay_on` e `relay_off`.

* Triggers HTTP podem ter controlo de acesso. Por padrão, requerem uma chave API específica da função que deve ser passada com o URL para serem executados. Para esta tarefa, pode remover esta restrição para que qualquer pessoa possa executar a função. Para fazer isso, atualize a configuração `authLevel` no ficheiro `function.json` para os triggers HTTP com o seguinte:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Pode ler mais sobre este controlo de acesso na [documentação sobre chaves de acesso de funções](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* Triggers HTTP, por padrão, suportam pedidos GET e POST. Isto significa que pode chamá-los usando o seu navegador web - navegadores web fazem pedidos GET.

    Quando executar a sua Functions App localmente, verá o URL do trigger:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Cole o URL no seu navegador e pressione `enter`, ou `Ctrl+click` (`Cmd+click` no macOS) no link na janela do terminal no VS Code para abri-lo no navegador padrão. Isto irá executar o trigger.

    > 💁 Note que o URL contém `/api` - triggers HTTP estão, por padrão, no subdomínio `api`.

* Quando publicar a Functions App, o URL do trigger HTTP será:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Onde `<functions app name>` é o nome da sua Functions App, e `<trigger name>` é o nome do seu trigger.

## Rubrica

| Critério | Exemplar | Adequado | Necessita Melhorias |
| -------- | --------- | -------- | ------------------- |
| Criar triggers HTTP | Criou 2 triggers para ligar e desligar o relé, com nomes apropriados | Criou um trigger com um nome apropriado | Não conseguiu criar nenhum trigger |
| Controlar o relé a partir dos triggers HTTP | Conseguiu ligar ambos os triggers ao IoT Hub e controlar o relé corretamente | Conseguiu ligar um trigger ao IoT Hub e controlar o relé corretamente | Não conseguiu ligar os triggers ao IoT Hub |

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.