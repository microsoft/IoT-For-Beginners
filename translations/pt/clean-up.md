<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-25T20:40:05+00:00",
  "source_file": "clean-up.md",
  "language_code": "pt"
}
-->
# Limpe o seu projeto

Depois de concluir cada projeto, é uma boa prática eliminar os seus recursos na cloud.

Nas lições de cada projeto, pode ter criado alguns dos seguintes recursos:

* Um Grupo de Recursos
* Um IoT Hub
* Registos de dispositivos IoT
* Uma Conta de Armazenamento
* Uma App de Funções
* Uma conta do Azure Maps
* Um projeto de visão personalizada
* Um Registo de Contentores do Azure
* Um recurso de serviços cognitivos

A maioria destes recursos não terá custos - ou são completamente gratuitos, ou está a utilizar um nível gratuito. Para serviços que exigem um nível pago, terá estado a utilizá-los num nível incluído na quota gratuita, ou que custará apenas alguns cêntimos.

Mesmo com custos relativamente baixos, vale a pena eliminar estes recursos quando terminar. Por exemplo, só pode ter um IoT Hub a utilizar o nível gratuito, por isso, se quiser criar outro, terá de usar um nível pago.

Todos os seus serviços foram criados dentro de Grupos de Recursos, o que facilita a gestão. Pode eliminar o Grupo de Recursos, e todos os serviços nesse Grupo de Recursos serão eliminados juntamente com ele.

Para eliminar o Grupo de Recursos, execute o seguinte comando no seu terminal ou prompt de comando:

```sh
az group delete --name <resource-group-name>
```

Substitua `<resource-group-name>` pelo nome do Grupo de Recursos que deseja eliminar.

Aparecerá uma confirmação:

```output
Are you sure you want to perform this operation? (y/n): 
```

Digite `y` para confirmar e eliminar o Grupo de Recursos.

A eliminação de todos os serviços pode demorar algum tempo.

> 💁 Pode ler mais sobre como eliminar grupos de recursos na [documentação sobre eliminação de grupos de recursos e recursos do Azure Resource Manager no Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.