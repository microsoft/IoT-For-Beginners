<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-28T20:27:10+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "en"
}
-->
# Add manual relay control

## Instructions

Serverless code can be activated by various events, including HTTP requests. You can use HTTP triggers to add a manual override for your relay control, enabling someone to turn the relay on or off via a web request.

For this task, you need to add two HTTP triggers to your Functions App to control the relay (turn it on and off), applying what you've learned in this lesson to send commands to the device.

Some tips:

* You can add an HTTP trigger to your existing Functions App using the following command:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Replace `<trigger name>` with the name of your HTTP trigger. Use names like `relay_on` and `relay_off`.

* HTTP triggers can include access control. By default, they require a function-specific API key to be included in the URL to execute. For this task, you can remove this restriction so anyone can run the function. To do this, modify the `authLevel` setting in the `function.json` file for the HTTP triggers to the following:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 You can find more details about this access control in the [Function access keys documentation](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP triggers support GET and POST requests by default. This means you can call them using your web browser, as browsers make GET requests.

    When running your Functions App locally, you will see the URL of the trigger:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Copy the URL into your browser and press `Enter`, or `Ctrl+click` (`Cmd+click` on macOS) the link in the terminal window in VS Code to open it in your default browser. This will execute the trigger.

    > 💁 Note that the URL includes `/api` - HTTP triggers are placed in the `api` subdomain by default.

* Once you deploy the Functions App, the HTTP trigger URL will be:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Here, `<functions app name>` is the name of your Functions App, and `<trigger name>` is the name of your trigger.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Create HTTP triggers | Created 2 triggers to turn the relay on and off, with appropriate names | Created one trigger with an appropriate name | Was unable to create any triggers |
| Control the relay from the HTTP triggers | Successfully connected both triggers to IoT Hub and controlled the relay as intended | Successfully connected one trigger to IoT Hub and controlled the relay as intended | Failed to connect the triggers to IoT Hub |

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.