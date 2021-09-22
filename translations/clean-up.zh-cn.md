# 清理你的项目

当你完成每个项目后，请删除你的云端资源。

在每个项目的课程中，也许你创建了下列的某些：

* 一个资源组
* 一个物联网中心
* 物联网设备注册
* 一个存储账户
* 一个函数应用
* 一个 Azure 地图账户
* 一个自定义视觉项目
* 一个 Azure 容器注册表
* 一个认知服务资源

这些资源中大部分都不收费 - 完全免费或者是免费层。对于规定了付费层的服务，你的使用额度会在免费范围内，或只花费几分钱。

即使成本相对较低，当你完成项目后也建议删除这些资源。例如，免费层只能有一个物联网中心，所以如果你想额外创建一个，你需要使用付费层。

你的所有服务都是在资源组内创建的，这让管理更加轻松。你可以删除某个资源组，所有资源组内的资源都会跟着删除。

在你的终端或命令提示符中运行以下命令来删除资源组：

```sh
az group delete --name <resource-group-name>
```

替代 `<resource-group-name>` 为你想删除的资源组名字。

接下来会显示下列的确认信息：

```output
Are you sure you want to perform this operation? (y/n): 
```

输入 `y` 确认并删除资源组.

删除所有服务会耗费一些时间。

> 💁 你可以在 [Microsoft 文档的 Azure 资源管理器资源组和资源删除](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli) 获取更多删除资源组的相关内容。