<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-28T20:24:17+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "en"
}
-->
# Migrate your application logic to the cloud

![A sketchnote overview of this lesson](../../../../../translated_images/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.en.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya). Click the image for a larger version.

This lesson was taught as part of the [IoT for Beginners Project 2 - Digital Agriculture series](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) from the [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Control your IoT device with serverless code](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Introduction

In the previous lesson, you learned how to connect your plant soil moisture monitoring system and relay control to a cloud-based IoT service. The next step is to move the server code that manages the relay's timing to the cloud. In this lesson, you'll learn how to achieve this using serverless functions.

In this lesson, we’ll cover:

* [What is serverless?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Create a serverless application](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Create an IoT Hub event trigger](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Send direct method requests from serverless code](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Deploy your serverless code to the cloud](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## What is serverless?

Serverless, or serverless computing, involves creating small blocks of code that run in the cloud in response to specific events. When an event occurs, your code is executed and receives data about the event. These events can originate from various sources, such as web requests, messages added to a queue, changes in a database, or messages sent to an IoT service by IoT devices.

![Events being sent from an IoT service to a serverless service, all being processed at the same time by multiple functions being run](../../../../../translated_images/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.en.png)

> 💁 If you've used database triggers before, think of this as a similar concept—code being triggered by an event, such as inserting a row.

![When many events are sent at the same time, the serverless service scales up to run them all at the same time](../../../../../translated_images/serverless-scaling.f8c769adf0413fd1.en.png)

Your code only runs when an event occurs; it doesn’t remain active at other times. When an event happens, your code is loaded and executed. This makes serverless highly scalable—if multiple events occur simultaneously, the cloud provider can execute your function as many times as needed, across available servers. However, if you need to share information between events, you’ll need to store it in a database or another persistent storage, as serverless functions don’t maintain in-memory state.

Your code is written as a function that takes event details as a parameter. A variety of programming languages can be used to write these serverless functions.

> 🎓 Serverless is also known as Functions as a Service (FaaS) because each event trigger is implemented as a function in code.

Despite the name, serverless does use servers. The term "serverless" refers to the fact that developers don’t need to manage the servers running their code. Instead, the cloud provider handles server allocation, networking, storage, CPU, memory, and other resources. You pay for the time your code runs and the memory it uses, rather than for a specific server.

> 💰 Serverless is one of the most cost-effective ways to run code in the cloud. For example, at the time of writing, one cloud provider allows up to 1,000,000 function executions per month for free. Beyond that, they charge $0.20 per 1,000,000 executions. You only pay when your code runs.

For IoT developers, the serverless model is ideal. You can write a function that responds to messages from any IoT device connected to your cloud-hosted IoT service. Your code will handle all incoming messages but will only run when needed.

✅ Reflect on the server code you wrote to listen for MQTT messages. How might this code operate in the cloud using serverless? What changes would be necessary to adapt it for serverless computing?

> 💁 The serverless model is expanding to other cloud services. For instance, serverless databases are available, where you pay per request (e.g., a query or insert). Pricing is often based on the complexity of the request. For example, a simple query for one row costs less than a complex operation involving multiple table joins and thousands of rows.

## Create a serverless application

Microsoft’s serverless computing service is called Azure Functions.

![The Azure Functions logo](../../../../../translated_images/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.en.png)

The short video below provides an overview of Azure Functions:

[![Azure Functions overview video](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Click the image above to watch the video.

✅ Take a moment to research and read the overview of Azure Functions in the [Microsoft Azure Functions documentation](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

To create Azure Functions, you start with a Functions app in your preferred programming language. Azure Functions natively supports Python, JavaScript, TypeScript, C#, F#, Java, and PowerShell. In this lesson, you’ll learn how to create an Azure Functions app using Python.

> 💁 Azure Functions also supports custom handlers, allowing you to write functions in any language that supports HTTP requests, including older languages like COBOL.

A Functions app consists of one or more *triggers*—functions that respond to events. Multiple triggers can exist within a single app, sharing common configurations. For example, the app’s configuration file can store IoT Hub connection details, which all triggers in the app can use.

### Task - Install the Azure Functions tooling

> At the time of writing, the Azure Functions tools for Python projects are not fully compatible with Apple Silicon. Use an Intel-based Mac, Windows PC, or Linux PC instead.

One advantage of Azure Functions is the ability to run them locally. The same runtime used in the cloud can be run on your computer, enabling you to test and debug your code locally. Once satisfied, you can deploy the code to the cloud.

The Azure Functions tooling is available as a CLI, called the Azure Functions Core Tools.

1. Install the Azure Functions Core Tools by following the instructions in the [Azure Functions Core Tools documentation](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Install the Azure Functions extension for VS Code. This extension supports creating, debugging, and deploying Azure Functions. Refer to the [Azure Functions extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) for installation instructions.

When deploying your Azure Functions app to the cloud, it requires a small amount of cloud storage for application files and logs. Locally, you can use a storage emulator called [Azurite](https://github.com/Azure/Azurite), which mimics cloud storage.

> 🎓 In Azure, the storage used by Azure Functions is an Azure Storage Account. These accounts can store files, blobs, tables, or queues. A single storage account can be shared across multiple apps, such as a Functions app and a web app.

1. Azurite is a Node.js app, so you’ll need to install Node.js. Download and install it from the [Node.js website](https://nodejs.org/). On a Mac, you can also use [Homebrew](https://formulae.brew.sh/formula/node).

1. Install Azurite using the following command (`npm` is included with Node.js):

    ```sh
    npm install -g azurite
    ```

1. Create a folder named `azurite` for Azurite to store data:

    ```sh
    mkdir azurite
    ```

1. Run Azurite, specifying the new folder:

    ```sh
    azurite --location azurite
    ```

    Azurite will launch and be ready for the local Functions runtime to connect.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Task - Create an Azure Functions project

The Azure Functions CLI can be used to create a new Functions app.

1. Create a folder for your Functions app and navigate to it. Name it `soil-moisture-trigger`:

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Create a Python virtual environment in this folder:

    ```sh
    python3 -m venv .venv
    ```

1. Activate the virtual environment:

    * On Windows:
        * If using the Command Prompt or Windows Terminal, run:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * If using PowerShell, run:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * On macOS or Linux, run:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Always run the activation command from the folder where you created the virtual environment. Avoid navigating into the `.venv` folder directly.

1. Create a Functions app in this folder:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    This will generate three files:

    * `host.json` - Contains settings for your Functions app. No modifications are needed.
    * `local.settings.json` - Stores local settings, such as IoT Hub connection strings. These settings are not included in source control or deployed to the cloud.
    * `requirements.txt` - A [Pip requirements file](https://pip.pypa.io/en/stable/user_guide/#requirements-files) listing the necessary Pip packages.

1. Update the `local.settings.json` file to connect to the Azurite emulator:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Install the required Pip packages:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Ensure all required Pip packages are listed in this file so they are installed when the app is deployed to the cloud.

1. Test the setup by starting the Functions runtime:

    ```sh
    func start
    ```

    The runtime will start and indicate that no job functions (triggers) were found.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ If you receive a firewall notification, allow access because the `func` application needs permission to read and write to your network.
> ⚠️ If you are using macOS, there may be warnings in the output:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> You can ignore these as long as the Functions app starts correctly and lists the running functions. As mentioned in [this question on the Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) it can be ignored.

1. Stop the Functions app by pressing `ctrl+c`.

1. Open the current folder in VS Code, either by opening VS Code, then opening this folder, or by running the following:

    ```sh
    code .
    ```

    VS Code will detect your Functions project and show a notification saying:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![The notification](../../../../../translated_images/vscode-azure-functions-init-notification.bd19b49229963edb.en.png)

    Select **Yes** from this notification.

1. Make sure the Python virtual environment is running in the VS Code terminal. Terminate it and restart it if necessary.

## Create an IoT Hub event trigger

The Functions app acts as the framework for your serverless code. To handle IoT Hub events, you can add an IoT Hub trigger to this app. This trigger connects to the stream of messages sent to the IoT Hub and processes them. To access this stream, your trigger must connect to the IoT Hub's *event hub compatible endpoint*.

IoT Hub is built on another Azure service called Azure Event Hubs. Event Hubs enables sending and receiving messages, and IoT Hub extends this functionality with features tailored for IoT devices. The process of connecting to read messages from IoT Hub is the same as connecting to Event Hubs.

✅ Research task: Read the overview of Event Hubs in the [Azure Event Hubs documentation](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). How do its basic features compare to IoT Hub?

For an IoT device to connect to the IoT Hub, it must use a secret key to ensure only authorized devices can connect. Similarly, when connecting to read messages, your code will need a connection string containing a secret key and details about the IoT Hub.

> 💁 The default connection string provided has **iothubowner** permissions, granting full access to the IoT Hub. Ideally, you should use the minimum permissions required. This will be covered in the next lesson.

Once the trigger is connected, the function's code will execute for every message sent to the IoT Hub, regardless of the device that sent it. The trigger passes the message as a parameter.

### Task - Get the Event Hub compatible endpoint connection string

1. Run the following command in the VS Code terminal to retrieve the connection string for the IoT Hub's Event Hub compatible endpoint:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Replace `<hub_name>` with the name of your IoT Hub.

1. In VS Code, open the `local.settings.json` file. Add the following value inside the `Values` section:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Replace `<connection string>` with the value obtained in the previous step. Ensure you add a comma after the preceding line to maintain valid JSON formatting.

### Task - Create an event trigger

You are now ready to create the event trigger.

1. From the VS Code terminal, run the following command inside the `soil-moisture-trigger` folder:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    This creates a new Function called `iot-hub-trigger`. The trigger connects to the Event Hub compatible endpoint on the IoT Hub, using an event hub trigger (there is no specific IoT Hub trigger).

This will create a folder named `iot-hub-trigger` inside the `soil-moisture-trigger` folder. The folder will contain the following files:

* `__init__.py` - This Python file contains the trigger code. The file name follows Python's standard convention for turning a folder into a module.

    This file will include the following code:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    The core of the trigger is the `main` function, which is called whenever events are received from the IoT Hub. The `main` function has a parameter named `event` that contains an `EventHubEvent`. Each time a message is sent to the IoT Hub, this function is invoked with the message as the `event`, along with properties similar to the annotations discussed in the previous lesson.

    The function's primary task is to log the event.

* `function.json` - This file contains the trigger's configuration. The main configuration resides in a section called `bindings`. A binding is the connection between Azure Functions and other Azure services. This function has an input binding to an event hub, enabling it to receive data.

    > 💁 Output bindings are also possible, allowing the function's output to be sent to another service. For example, you could add an output binding to a database, and the IoT Hub event returned by the function would be automatically inserted into the database.

    ✅ Research task: Learn more about bindings in the [Azure Functions triggers and bindings concepts documentation](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    The `bindings` section includes the following key configurations:

  * `"type": "eventHubTrigger"` - Specifies that the function listens to events from an Event Hub.
  * `"name": "events"` - Defines the parameter name for the Event Hub events, matching the parameter name in the Python `main` function.
  * `"direction": "in"` - Indicates this is an input binding, where data flows into the function from the event hub.
  * `"connection": ""` - Specifies the name of the setting containing the connection string. When running locally, this setting is read from the `local.settings.json` file.

    > 💁 The connection string cannot be stored directly in the `function.json` file to prevent accidental exposure.

1. Due to [a bug in the Azure Functions template](https://github.com/Azure/azure-functions-templates/issues/1250), the `function.json` file contains an incorrect value for the `cardinality` field. Update this field from `many` to `one`:

    ```json
    "cardinality": "one",
    ```

1. Update the `"connection"` value in the `function.json` file to reference the new setting added to the `local.settings.json` file:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Remember, this should reference the setting name, not the actual connection string.

1. The connection string includes the `eventHubName` value, so the `eventHubName` field in the `function.json` file should be cleared. Set this value to an empty string:

    ```json
    "eventHubName": "",
    ```

### Task - Run the event trigger

1. Ensure the IoT Hub event monitor is not running. If it runs simultaneously with the Functions app, the Functions app won't be able to connect and process events.

    > 💁 Multiple apps can connect to IoT Hub endpoints using different *consumer groups*. This will be covered in a later lesson.

1. To start the Functions app, run the following command in the VS Code terminal:

    ```sh
    func start
    ```

    The Functions app will start, discover the `iot-hub-trigger` function, and process any events sent to the IoT Hub in the past day.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    Each function call will be logged with `Executing 'Functions.iot-hub-trigger'` and `Executed 'Functions.iot-hub-trigger'` blocks, showing the number of messages processed in each call.

1. Ensure your IoT device is running. You should see new soil moisture messages appearing in the Functions app.

1. Stop and restart the Functions app. It will only process new messages, not previously processed ones.

> 💁 VS Code supports debugging Functions. You can set breakpoints by clicking next to the line numbers, selecting *Run -> Toggle breakpoint*, or pressing `F9`. Start debugging by selecting *Run -> Start debugging*, pressing `F5`, or using the *Run and debug* pane. This allows you to inspect the details of the events being processed.

#### Troubleshooting

* If you encounter the following error:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Ensure Azurite is running and the `AzureWebJobsStorage` setting in `local.settings.json` is set to `UseDevelopmentStorage=true`.

* If you encounter the following error:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Verify that the `cardinality` field in `function.json` is set to `one`.

* If you encounter the following error:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Ensure the `eventHubName` field in `function.json` is set to an empty string.

## Send direct method requests from serverless code

So far, your Functions app listens to messages from the IoT Hub using the Event Hub compatible endpoint. Now, you need to send commands to the IoT device. This is achieved by connecting to the IoT Hub via the *Registry Manager*. The Registry Manager allows you to manage registered devices, send cloud-to-device messages, invoke direct method requests, or update the device twin. It also enables registering, updating, or deleting IoT devices.

To connect to the Registry Manager, you need a connection string.

### Task - Get the Registry Manager connection string

1. Run the following command to retrieve the connection string:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Replace `<hub_name>` with the name of your IoT Hub.

    The connection string is requested for the *ServiceConnect* policy using the `--policy-name service` parameter. This policy allows your code to send messages to IoT devices.

    ✅ Research task: Learn about the different policies in the [IoT Hub permissions documentation](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn).

1. In VS Code, open the `local.settings.json` file. Add the following value inside the `Values` section:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Replace `<connection string>` with the value obtained in the previous step. Ensure you add a comma after the preceding line to maintain valid JSON formatting.

### Task - Send a direct method request to a device

1. The SDK for the Registry Manager is available as a Pip package. Add the following line to the `requirements.txt` file to include the dependency:

    ```sh
    azure-iot-hub
    ```

1. Ensure the VS Code terminal has the virtual environment activated, and run the following command to install the Pip packages:

    ```sh
    pip install -r requirements.txt
    ```

1. Add the following imports to the `__init__.py` file:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    This imports system libraries and the libraries required to interact with the Registry Manager and send direct method requests.

1. Remove the existing code inside the `main` method, but retain the method itself.

1. Add the following code to the `main` method:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    This code extracts the event body containing the JSON message sent by the IoT device. It retrieves the device ID from the annotations passed with the message. The event body contains the telemetry message, while the `iothub_metadata` dictionary includes properties like the device ID and the message's timestamp.

    The extracted information is logged, and you will see this in the terminal when running the Functions app locally.

1. Add the following code below the previous section:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    This code retrieves the soil moisture value from the message. Based on the value, it creates a helper class for the `relay_on` or `relay_off` direct method request. Since the method request doesn't require a payload, an empty JSON document is sent.

1. Add the following code below this section:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
This code loads the `REGISTRY_MANAGER_CONNECTION_STRING` from the `local.settings.json` file. The values in this file are made available as environment variables, which can be accessed using the `os.environ` function. This function returns a dictionary of all the environment variables.

> 💁 When this code is deployed to the cloud, the values in the `local.settings.json` file will be set as *Application Settings*, and these can be accessed from environment variables.

The code then creates an instance of the Registry Manager helper class using the connection string.

1. Add the following code below this:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    This code instructs the registry manager to send the direct method request to the device that sent the telemetry.

    > 💁 In the earlier versions of the app you created using MQTT, the relay control commands were sent to all devices. The code assumed there would only be one device. This version of the code sends the method request to a single device, making it suitable for setups with multiple moisture sensors and relays, ensuring the correct direct method request is sent to the appropriate device.

1. Run the Functions app and ensure your IoT device is sending data. You will see the messages being processed and the direct method requests being sent. Move the soil moisture sensor in and out of the soil to observe the values change and the relay turn on and off.

> 💁 You can find this code in the [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) folder.

## Deploy your serverless code to the cloud

Your code is now functioning locally, so the next step is to deploy the Functions App to the cloud.

### Task - create the cloud resources

Your Functions app needs to be deployed to a Functions App resource in Azure, which will reside inside the Resource Group you created for your IoT Hub. Additionally, you will need to create a Storage Account in Azure to replace the emulated one running locally.

1. Run the following command to create a storage account:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Replace `<storage_name>` with a name for your storage account. This name must be globally unique as it forms part of the URL used to access the storage account. Only lowercase letters and numbers are allowed, and the name is limited to 24 characters. Use something like `sms` and append a unique identifier, such as random words or your name.

    The `--sku Standard_LRS` specifies the pricing tier, selecting the lowest-cost general-purpose account. There is no free tier for storage, and you pay based on usage. The costs are relatively low, with the most expensive storage costing less than US$0.05 per month per gigabyte stored.

    ✅ Learn more about pricing on the [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Run the following command to create a Function App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Replace `<location>` with the location you used when creating the Resource Group in the previous lesson.

    Replace `<storage_name>` with the name of the storage account you created in the previous step.

    Replace `<functions_app_name>` with a unique name for your Functions App. This name must also be globally unique as it forms part of the URL used to access the Functions App. Use something like `soil-moisture-sensor-` and append a unique identifier, such as random words or your name.

    The `--functions-version 3` option specifies the version of Azure Functions to use. Version 3 is the latest version.

    The `--os-type Linux` tells the Functions runtime to use Linux as the operating system to host these functions. Functions can be hosted on Linux or Windows, depending on the programming language used. Python apps are only supported on Linux.

### Task - upload your application settings

When developing your Functions App, you stored some settings in the `local.settings.json` file for the IoT Hub connection strings. These settings need to be written to Application Settings in your Function App in Azure so they can be used by your code.

> 🎓 The `local.settings.json` file is intended for local development settings only and should not be checked into source code control, such as GitHub. When deployed to the cloud, Application Settings are used. Application Settings are key/value pairs hosted in the cloud and are accessed as environment variables either in your code or by the runtime when connecting your code to IoT Hub.

1. Run the following command to set the `IOT_HUB_CONNECTION_STRING` setting in the Functions App Application Settings:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Replace `<functions_app_name>` with the name you used for your Functions App.

    Replace `<connection string>` with the value of `IOT_HUB_CONNECTION_STRING` from your `local.settings.json` file.

1. Repeat the step above, but set the value of `REGISTRY_MANAGER_CONNECTION_STRING` to the corresponding value from your `local.settings.json` file.

When you run these commands, they will also output a list of all the Application Settings for the Functions App. You can use this to verify that your values are set correctly.

> 💁 You will notice a value already set for `AzureWebJobsStorage`. In your `local.settings.json` file, this was set to use the local storage emulator. When you created the Functions App, the storage account was passed as a parameter, and this value was automatically set in the Application Settings.

### Task - deploy your Functions App to the cloud

Now that the Functions App is ready, you can deploy your code.

1. Run the following command from the VS Code terminal to publish your Functions App:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Replace `<functions_app_name>` with the name you used for your Functions App.

The code will be packaged and sent to the Functions App, where it will be deployed and started. The console will display a lot of output, ending with confirmation of the deployment and a list of the deployed functions. In this case, the list will only include the trigger.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Ensure your IoT device is running. Adjust the soil moisture levels by moving the sensor in and out of the soil. You will see the relay turn on and off as the soil moisture changes.

---

## 🚀 Challenge

In the previous lesson, you managed the relay timing by unsubscribing from MQTT messages while the relay was on and for a short period after it was turned off. This method cannot be used here because you cannot unsubscribe your IoT Hub trigger.

Think about alternative ways to handle this in your Functions App.

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Review & Self Study

* Learn about serverless computing on the [Serverless Computing page on Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* Explore using serverless in Azure, including additional examples, in the [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Dive deeper into Azure Functions on the [Azure Functions YouTube channel](https://www.youtube.com/c/AzureFunctions)

## Assignment

[Add manual relay control](assignment.md)

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.