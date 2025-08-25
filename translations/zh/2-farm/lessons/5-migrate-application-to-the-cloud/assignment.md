<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-24T22:27:32+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "zh"
}
-->
# 添加手动继电器控制

## 说明

无服务器代码可以由多种方式触发，包括 HTTP 请求。你可以使用 HTTP 触发器为继电器控制添加手动覆盖功能，从而允许通过网页请求来打开或关闭继电器。

在本任务中，你需要为你的 Functions App 添加两个 HTTP 触发器，用于打开和关闭继电器，复用本课中学到的知识向设备发送命令。

一些提示：

* 你可以使用以下命令为现有的 Functions App 添加一个 HTTP 触发器：

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    将 `<trigger name>` 替换为你的 HTTP 触发器的名称。可以使用类似 `relay_on` 和 `relay_off` 的名称。

* HTTP 触发器可以设置访问控制。默认情况下，它们需要一个特定于函数的 API 密钥随 URL 一起传递才能运行。对于本任务，你可以移除此限制，以便任何人都可以运行该函数。为此，请在 HTTP 触发器的 `function.json` 文件中将 `authLevel` 设置更新为以下内容：

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 你可以在 [Function access keys documentation](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys) 中阅读更多关于此访问控制的信息。

* HTTP 触发器默认支持 GET 和 POST 请求。这意味着你可以使用网页浏览器调用它们——网页浏览器会发出 GET 请求。

    当你在本地运行 Functions App 时，你会看到触发器的 URL：

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    将 URL 粘贴到浏览器中并按下 `回车`，或者在 VS Code 的终端窗口中 `Ctrl+点击`（macOS 上为 `Cmd+点击`）链接以在默认浏览器中打开。这将运行触发器。

    > 💁 注意 URL 中包含 `/api`——HTTP 触发器默认位于 `api` 子域中。

* 当你部署 Functions App 时，HTTP 触发器的 URL 将是：

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    其中 `<functions app name>` 是你的 Functions App 的名称，`<trigger name>` 是触发器的名称。

## 评分标准

| 标准 | 优秀 | 合格 | 需要改进 |
| ---- | ---- | ---- | -------- |
| 创建 HTTP 触发器 | 创建了两个用于打开和关闭继电器的触发器，并使用了合适的名称 | 创建了一个具有合适名称的触发器 | 未能创建任何触发器 |
| 从 HTTP 触发器控制继电器 | 能够将两个触发器连接到 IoT Hub 并正确控制继电器 | 能够将一个触发器连接到 IoT Hub 并正确控制继电器 | 未能将触发器连接到 IoT Hub |

**免责声明**：  
本文档使用AI翻译服务 [Co-op Translator](https://github.com/Azure/co-op-translator) 进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对于因使用此翻译而引起的任何误解或误读不承担责任。