<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-24T21:00:27+00:00",
  "source_file": "clean-up.md",
  "language_code": "zh"
}
-->
# 清理您的项目

完成每个项目后，最好删除您的云资源。

在每个项目的课程中，您可能创建了以下一些资源：

* 一个资源组
* 一个 IoT 中心
* IoT 设备注册
* 一个存储账户
* 一个 Functions 应用
* 一个 Azure Maps 账户
* 一个自定义视觉项目
* 一个 Azure 容器注册表
* 一个认知服务资源

这些资源中的大多数是没有成本的——要么完全免费，要么您使用的是免费层。对于需要付费层的服务，您可能使用的是包含在免费额度内的级别，或者仅需花费几美分。

即使成本相对较低，完成后删除这些资源也是值得的。例如，您只能有一个使用免费层的 IoT 中心，因此如果您想创建另一个，就需要使用付费层。

您所有的服务都创建在资源组中，这使得管理更加方便。您可以删除资源组，资源组中的所有服务也会随之被删除。

要删除资源组，请在终端或命令提示符中运行以下命令：

```sh
az group delete --name <resource-group-name>
```

将 `<resource-group-name>` 替换为您感兴趣的资源组的名称。

会出现一个确认提示：

```output
Are you sure you want to perform this operation? (y/n): 
```

输入 `y` 以确认并删除资源组。

删除所有服务需要一些时间。

> 💁 您可以在 [Microsoft Docs 上的 Azure 资源管理器资源组和资源删除文档](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli) 中阅读更多关于删除资源组的信息。

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用此翻译而引起的任何误解或误读不承担责任。