# Limpando seu projeto

Depois de concluir cada projeto, é bom excluir seus recursos de nuvem.

Nas lições de cada projeto, você pode ter criado alguns dos itens a seguir:

* Um grupo de recursos
* Um Hub IoT
* Registros de dispositivos IoT
* Uma conta de armazenamento
* Um aplicativo de funções
* Uma conta do Azure Mapas
* Um projeto de visão personalizado
* Um Registro de Contêiner do Azure
* Um recurso de serviços cognitivos

A maioria desses recursos não terá custo - ou eles são totalmente gratuitos ou você está usando um nível gratuito. Para serviços que exigem um nível pago, você os usaria em um nível incluído no subsídio gratuito ou custaria apenas alguns centavos.

Mesmo com os custos relativamente baixos, vale a pena excluir esses recursos quando terminar. Você só pode ter um Hub IoT usando o nível gratuito, por exemplo, portanto, se quiser criar outro, precisará usar um nível pago.

Todos os seus serviços foram criados dentro de Grupos de Recursos, e isso facilita o gerenciamento. Você pode excluir o Grupo de Recursos e todos os serviços desse Grupo de Recursos serão excluídos junto com ele.

Para excluir o grupo de recursos, execute o seguinte comando em seu terminal ou prompt de comando:

```sh
az group delete --name <resource-group-name>
```

Substitua `<resource-group-name>` com o nome do Grupo de Recursos no qual você está interessado.

Uma confirmação aparecerá:

```output
Are you sure you want to perform this operation? (y/n): 
```

Digite `y` para confirmar e excluir o grupo de recursos.

Pode demorar um pouco para excluir todos os serviços.

> 💁 Você pode ler mais sobre como excluir grupos de recursos no [Grupo de recursos do Azure Resource Manager e documentação de exclusão de recursos no Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)