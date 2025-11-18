<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-11-18T19:44:14+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "pcm"
}
-->
# Add manual relay control

## Instructions

Serverless code fit trigger by many different things, like HTTP requests. You fit use HTTP triggers take add manual override to your relay control, so person fit turn the relay on or off from web request.

For dis assignment, you go need add two HTTP triggers to your Functions App to turn the relay on and off, dey reuse wetin you don learn from dis lesson to send commands to the device.

Some hints:

* You fit add HTTP trigger to your Functions App wey dey already exist with dis command:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Replace `<trigger name>` with the name wey you wan give your HTTP trigger. Use something like `relay_on` and `relay_off`

* HTTP triggers fit get access control. By default dem dey require function-specific API key wey go follow the URL to run. For dis assignment, you fit remove dis restriction so anybody fit run the function. To do dis, update the `authLevel` setting for the `function.json` file for the HTTP triggers to dis:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 You fit read more about dis access control for [Function access keys documentation](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP triggers by default dey support GET and POST requests. Dis mean say you fit call dem using your web browser - web browsers dey make GET requests.

    When you dey run your Functions App locally, you go see the URL of the trigger:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Paste the URL inside your browser and press `return`, or `Ctrl+click` (`Cmd+click` for macOS) the link for the terminal window for VS Code to open am for your default browser. Dis go run the trigger.

    > 💁 Notice say the URL get `/api` inside am - HTTP triggers by default dey for the `api` subdomain.

* When you deploy the Functions App, the HTTP trigger URL go be:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Where `<functions app name>` na the name of your Functions App, and `<trigger name>` na the name of your trigger.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Create HTTP triggers | Create 2 triggers to turn the relay on and off, with correct names | Create one trigger with correct name | No fit create any trigger |
| Control the relay from the HTTP triggers | Fit connect both triggers to IoT Hub and control the relay well | Fit connect one trigger to IoT Hub and control the relay well | No fit connect the triggers to IoT Hub |

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI transleshion service [Co-op Translator](https://github.com/Azure/co-op-translator) do di transleshion. Even as we dey try make am accurate, abeg make you sabi say transleshion wey machine do fit get mistake or no correct well. Di original dokyument for im native language na di one wey you go take as di correct source. For important mata, e good make you use professional human transleshion. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis transleshion.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->