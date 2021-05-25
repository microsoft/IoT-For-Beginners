# Add manual relay control

## Instructions

Serverless code can be triggered by many different things, including HTTP requests. You can use HTTP triggers to add a manual override to your relay control, allowing someone to turn the relay on or off from a web request.

For this assignment, you need to add two HTTP triggers to your Functions App to turn the relay on and off, reusing what you have learned from this lesson to send commands to the device.

Some hints:

* You can add an HTTP trigger to your existing Functions App with the following command:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Replace `<trigger name>` with the name for your HTTP trigger. Use something like `relay_on` and `relay_off`

* HTTP triggers can have access control. By default they require a function-specific API key to be passed with the URL to run. For this assignment, you can remove this restriction so anyone can run the function. To do this, update the `authLevel` setting in the `function.json` file for the HTTP triggers to the following:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 You can read more about this access control in the [Function access keys documentation](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP triggers by default support GET and POST requests. This means you can call them using your web browser - web browsers make GET requests.

    When you run your Functions App locally, you will see the URL of the trigger:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot_hub_trigger: eventHubTrigger
    ```

    Paste the URL into your browser and hit `return`, or `Ctrl+click` (`Cmd+click` on macOS) the link in the terminal window in VS Code to open it in your default browser. This will run the trigger.

    > 💁 Notice that the URL has `/api` in it - HTTP triggers are by default in the `api` subdomain.

* When you deploy the Functions App, the HTTP trigger URL will be:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Where `<functions app name>` is the name of your Functions App, and `<trigger name>` is the name of your trigger.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Create HTTP triggers | Created 2 triggers to turn the relay on and off, with appropriate names | Created one trigger with an appropriate name | Was unable to create any triggers |
| Control the relay from the HTTP triggers | Was able to connect both triggers to IoT Hub and control the relay appropriately | Was able to connect one trigger to IoT Hub and control the relay appropriately | Was unable connect the triggers to IoT Hub |
