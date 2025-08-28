<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-28T02:34:51+00:00",
  "source_file": "clean-up.md",
  "language_code": "br"
}
-->
# Limpe seu projeto

Após concluir cada projeto, é uma boa prática excluir seus recursos na nuvem.

Nas lições de cada projeto, você pode ter criado alguns dos seguintes recursos:

* Um Grupo de Recursos
* Um IoT Hub
* Registros de dispositivos IoT
* Uma Conta de Armazenamento
* Um App de Funções
* Uma conta do Azure Maps
* Um projeto de visão personalizada
* Um Registro de Contêiner do Azure
* Um recurso de serviços cognitivos

A maioria desses recursos não terá custo - ou são completamente gratuitos, ou você está utilizando uma camada gratuita. Para serviços que exigem uma camada paga, você provavelmente os utilizou em um nível incluído na cota gratuita ou que custará apenas alguns centavos.

Mesmo com os custos relativamente baixos, vale a pena excluir esses recursos quando terminar. Por exemplo, você só pode ter um IoT Hub utilizando a camada gratuita, então, se quiser criar outro, precisará usar uma camada paga.

Todos os seus serviços foram criados dentro de Grupos de Recursos, o que facilita a gestão. Você pode excluir o Grupo de Recursos, e todos os serviços dentro desse Grupo de Recursos serão excluídos junto com ele.

Para excluir o Grupo de Recursos, execute o seguinte comando no seu terminal ou prompt de comando:

```sh
az group delete --name <resource-group-name>
```

Substitua `<resource-group-name>` pelo nome do Grupo de Recursos que você deseja excluir.

Uma confirmação aparecerá:

```output
Are you sure you want to perform this operation? (y/n): 
```

Digite `y` para confirmar e excluir o Grupo de Recursos.

Levará algum tempo para excluir todos os serviços.

> 💁 Você pode ler mais sobre como excluir grupos de recursos na [documentação sobre exclusão de grupos de recursos e recursos do Azure Resource Manager no Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.