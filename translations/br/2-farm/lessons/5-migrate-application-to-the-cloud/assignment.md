<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-28T04:01:02+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "br"
}
-->
# Adicionar controle manual de relé

## Instruções

Código serverless pode ser acionado por diversos eventos, incluindo requisições HTTP. Você pode usar gatilhos HTTP para adicionar uma substituição manual ao controle do relé, permitindo que alguém ligue ou desligue o relé por meio de uma requisição web.

Para esta tarefa, você precisa adicionar dois gatilhos HTTP ao seu Functions App para ligar e desligar o relé, reutilizando o que você aprendeu nesta lição para enviar comandos ao dispositivo.

Algumas dicas:

* Você pode adicionar um gatilho HTTP ao seu Functions App existente com o seguinte comando:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Substitua `<trigger name>` pelo nome do seu gatilho HTTP. Use algo como `relay_on` e `relay_off`.

* Gatilhos HTTP podem ter controle de acesso. Por padrão, eles exigem uma chave de API específica da função para ser passada com a URL para serem executados. Para esta tarefa, você pode remover essa restrição para que qualquer pessoa possa executar a função. Para fazer isso, atualize a configuração `authLevel` no arquivo `function.json` para os gatilhos HTTP com o seguinte:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Você pode ler mais sobre este controle de acesso na [documentação de chaves de acesso de funções](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* Gatilhos HTTP, por padrão, suportam requisições GET e POST. Isso significa que você pode chamá-los usando seu navegador web - navegadores web fazem requisições GET.

    Quando você executa seu Functions App localmente, verá a URL do gatilho:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Cole a URL no seu navegador e pressione `return`, ou `Ctrl+click` (`Cmd+click` no macOS) no link na janela do terminal no VS Code para abri-lo no navegador padrão. Isso executará o gatilho.

    > 💁 Note que a URL contém `/api` - gatilhos HTTP estão, por padrão, no subdomínio `api`.

* Quando você implantar o Functions App, a URL do gatilho HTTP será:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Onde `<functions app name>` é o nome do seu Functions App, e `<trigger name>` é o nome do seu gatilho.

## Rubrica

| Critério | Exemplar | Adequado | Precisa Melhorar |
| -------- | --------- | -------- | ---------------- |
| Criar gatilhos HTTP | Criou 2 gatilhos para ligar e desligar o relé, com nomes apropriados | Criou um gatilho com um nome apropriado | Não conseguiu criar nenhum gatilho |
| Controlar o relé a partir dos gatilhos HTTP | Conectou ambos os gatilhos ao IoT Hub e controlou o relé corretamente | Conectou um gatilho ao IoT Hub e controlou o relé corretamente | Não conseguiu conectar os gatilhos ao IoT Hub |

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.