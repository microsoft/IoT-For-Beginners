# Store location data

## Pre-lecture quiz

[Pre-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/23)

## Introduction

In the last lesson, you learned how to use a GPS sensor to capture location data. To use this data to visualize the location of a truck laden with food, and it's journey, it needs to be sent to an IoT service in the cloud, and then stored somewhere.

In this lesson you will learn about the different ways to store IoT data, and learn how to store data from your IoT service using serverless code.

In this lesson we'll cover:

* [Structured and unstructured data](#structured-and-unstructured-data)
* [Send GPS data to an IoT Hub](#send-gps-data-to-an-iot-hub)
* [Hot, warm, and cold paths](#hot-warm-and-cold-paths)
* [Handle GPS events using serverless code](#handle-gps-events-using-serverless-code)
* [Azure Storage Accounts](#azure-storage-accounts)
* [Connect your serverless code to storage](#connect-your-serverless-code-to-storage)

## Structured and unstructured data

Computer systems deal with data, and this data comes in all manner of different shapes and sizes. It can vary from single numbers, to large amounts of text, to videos and images, and to IoT data. Data can usually be divided into one of two categories - *structured* data and *unstructured* data.

* **Structured data** is data with a well-defined, rigid structure that doesn't change and usually maps to tables of data with relationships. One example is a persons details including their name, date of birth and address.

* **Unstructured data** is data without a well-defined, rigid structure, including data that can change structure frequently. One example is documents such as written documents or spreadsheets.

✅ Do some research: Can you think of some other examples of structured and unstructured data?

> 💁 There is also semi-structured data that is structured but doesn't fit into fixed tables of data

IoT data is usually considered to be unstructured data.

Imagine you were adding IoT devices to a fleet of vehicles for a large commercial farm. You might want to use different devices for different types of vehicle. For example:

* For farm vehicles like tractors you want GPS data to ensure they are working on the correct fields
* For delivery trucks transporting food to warehouses you want GPS data as well as speed and acceleration data to ensure the driver is driving safely, and drive identity and start/stop data to ensure drive compliance with local laws on working hours
* For refrigerated trucks you also want temperature data to ensure the food doesn't get too hot or cold and spoil in transit

This data can change constantly. For example, if the IoT device is in a truck cab, then the data it sends may change as the trailer changes, for example only sending temperature data when a refrigerated trailer is used.

✅ What other IoT data might be captured? Think about the kinds of loads trucks can carry, as well as maintenance data.

This data varies from vehicle to vehicle, but it all gets sent to the same IoT service for processing. The IoT service needs to be able to process this unstructured data, storing it in a way that allows it to be searched or analyzed, but works with different structures to this data.

### SQL vs NoSQL storage

Databases are services that allow you to store and query data. Database come in two types - SQL and NoSQL

#### SQL databases

The first databases were Relational Database Management Systems (RDBMS), or relational database. These are also known as SQL databases after the Structured Query Language (SQL) used to interact with them to add, remove, update or query data. These database consist of a schema - a well-defined set of tables of data, similar to a spreadsheet. Each table has multiple named columns. When you insert data, you add a row to the table, putting values into each of the columns. This keeps the data in a very rigid structure - although you can leave columns empty, if you want to add a new column you have to do this on the database, populating values for the existing rows. These databases are relational - in that one table can have a relationship to another.

![A relational database with the ID of the User table relating to the user ID column of the purchases table, and the ID of the products table relating to the product ID of the purchases table](../../../images/sql-database.png)

For example, if you stored a users personal details in a table, you would have some kind of internal unique ID per user that is used in a row in a table that contains the users name and address. If you then wanted to store other details about that user, such as their purchases, in another table, you would have one column in the new table for that users ID. When you look up a user, you can use their ID to get their personal details from one table, and their purchases from another.

SQL databases are ideal for storing structured data, and for when you want to ensure the data matches your schema.

✅ If you haven't used SQL before, take a moment to read up on it on the [SQL page on Wikipedia](https://wikipedia.org/wiki/SQL).

Some well known SQL databases are Microsoft SQL Server, MySQL, and PostgreSQL.

✅ Do some research: Read up on some of these SQL databases and their capabilities.

#### NoSQL database

NoSQL databases are called NoSQL because they don't have the same rigid structure of SQL databases. They are also known as document databases as they can store unstructured data such as documents.

> 💁 Despite their name, some NoSQL databases allow you to use SQL to query the data.

![Documents in folders in a NoSQL database](../../../images/noqsl-database.png)

NoSQL database do not have a pre-defined schema that limits how data is stored, instead you can insert any unstructured data, usually using JSON documents. These documents can be organized into folders, similar to files on your computer. Each document can have different fields from other documents - for example if you were storing IoT data from your farm vehicles, some may have fields for accelerometer and speed data, others may have fields for the temperature in the trailer. If you were to add a new truck type, such as one with built in scales to track the weight of produce carried, then your IoT device could add this new field and it could be stored without any changes to the database.

Some well known NoSQL databases include Azure CosmosDB, MongoDB, and CouchDB.

✅ Do some research: Read up on some of these NoSQL databases and their capabilities.

In this lesson, you will be using NoSQL storage to store IoT data.

## Send GPS data to an IoT Hub

In the last lesson you captured GPS data from a GPS sensor connected to your IoT device. To store this IoT data in the cloud, you need to send it to an IoT service. Once again, you will be using Azure IoT Hub, the same IoT cloud service you used in the previous project.

![Sending GPS telemetry from an IoT device to IoT Hub](../../../images/gps-telemetry-iot-hub.png)

### Task - send GPS data to an IoT Hub

1. Create a new IoT Hub using the free tier.

    > ⚠️ You can refer to the [instructions for creating an IoT Hub from project 2, lesson 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud) if needed.

    Remember to create a new Resource Group. Name the new Resource Group `gps-sensor`, and the new IoT Hub a unique name based on `gps-sensor`, such as `gps-sensor-<your name>`.

    > 💁 If you still have your IoT Hub from the previous project, you can re-use it. Remember to use the name of this IoT Hub and the Resource Group it is in when creating other services.

1. Add a new device to the IoT Hub. Call this device `gps-sensor`. Grab the connection string for the device.

1. Update your device code to send the GPS data to the new IoT Hub using the device connection string from the previous step.

    > ⚠️ You can refer to the [instructions for connecting your device to an IoT from project 2, lesson 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service) if needed.

1. When you send the GPS data, do it as JSON in the following format:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Send GPS data every minute so you don't use up your daily message allocation.

If you are using the Wio Terminal, remember to add all the necessary libraries, and set the time using an NTP server. Your code will also need to ensure that it has read all the data from the serial port before sending the GPS location, using the existing code from the last lesson. Use the following code to construct the JSON document:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

If you are using a Virtual IoT device, remember to install all the needed libraries using a virtual environment.

For both the Raspberry Pi and Virtual IoT device, use the existing code from the last lesson to get the latitude and longitude values, then send them in the correct JSON format with the following code:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 You can find this code in the [code/wio-terminal](code/wio-terminal), [code/pi](code/pi) or [code/virtual-device](code/virtual-device) folder.

Run your device code and ensure messages are flowing into IoT Hub using the `az iot hub monitor-events` CLI command.

## Hot, warm, and cold paths

Data that flows from an IoT device to the cloud is not always processed in real time. Some data needs real time processing, other data can be processed a short time later, and other data can be processed much later. The flow of data to different services that process the data at different times is referred to hot, warm and cold paths.

### Hot path

The hot path refers to data that needs to be processed in real time or near real time. You would use hot path data for alerts, such as getting alerts that a vehicle is approaching a depot, or that the temperature in a refrigerated truck is too high.

To use hot path data, your code would respond to events as soon as they are received by your cloud services.

### Warm path

The warm path refers to data that can be processed a short while after being received, for example for reporting or short term analytics. You would use warm path data for daily reports on vehicle mileage, using data gathered the previous day.

Warm path data is stored once it is received by the cloud service inside some kind of storage that can be quickly accessed.

### Cold path

THe cold path refers to historic data, storing data for the long term to be processed whenever needed. For example, you could use the cold path to get annual mileage reports for vehicles, or run analytics on routes to find the most optimal route to reduce fuel costs.

Cold path data is stored in data warehouses - databases designed for storing large amounts of data that will never change and can be queried quickly and easily. You would normally have a regular job in your cloud application that would run at a regular time each day, week, or month to move data from warm path storage into the data warehouse.

✅ Think about the data you have captured so far in these lessons. Is it hot, warm or cold path data?

## Handle GPS events using serverless code

Once data is flowing into your IoT Hub, you can write some serverless code to listen for events published to the Event-Hub compatible endpoint. This is the warm path - this data will be stored and used in the next lesson for reporting on the journey.

![Sending GPS telemetry from an IoT device to IoT Hub, then to Azure Functions via an event hub trigger](../../../images/gps-telemetry-iot-hub-functions.png)

### Task - handle GPS events using serverless code

1. Create an Azure Functions app using the Azure Functions CLI. Use the Python runtime, and create it in a folder called `gps-trigger`, and use the same name for the Functions App project name. Make sure you create a virtual environment to use for this.

    > ⚠️ You can refer to the [instructions for creating an Azure Functions Project from project 2, lesson 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application) if needed.

1. Add an IoT Hub event trigger that uses the IoT Hub's Event Hub compatible endpoint.

    > ⚠️ You can refer to the [instructions for creating an IoT Hub event trigger from project 2, lesson 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger) if needed.

1. Set the Event Hub compatible endpoint connection string in the `local.settings.json` file, and use the key for that entry in the `function.json` file.

1. Use the Azurite app as a local storage emulator

1. Run your functions app to ensure it is receiving events from your GPS device. Make sure your IoT device is also running and sending GPS data.

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Azure Storage Accounts

![The Azure Storage logo](../../../images/azure-storage-logo.png)

Azure Storage Accounts is a general purpose storage service that can store data in a variety of different ways. You can store data as blobs, in queues, in tables, or as files, and all at the same time.

### Blob storage

The word *Blob* means binary large objects, but has become the term for any unstructured data. You can store any data in blob storage, from JSON documents containing IoT data, to image and movie files. Blob storage has the concept of *containers*, named buckets that you can store data in, similar to tables in a relational database. These containers can have one or more folders to store blobs, and each folder can contain other folders, similar to how files are stored on your computer hard disk.

You will use blob storage in this lesson to store IoT data.

✅ Do some research: Read up on [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Table storage

Table storage allows you to store semi-structured data. Table storage is actually a NoSQL database, so doesn't require a defined set of tables up front, but it is designed to store data in one or more tables, with unique keys to define each row.

✅ Do some research: Read up on [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Queue storage

Queue storage allows you to store messages of up to 64KB in size in a queue. You can add messages to the back of the queue, and read them off the front. Queues store messages indefinitely as long as there is still storage space, so it allows messages to be stored long term. then read off when needed. For example, if you wanted to run a monthly job to process GPS data you could add it to a queue every day for a month, then at the end of the month process all the messages off the queue.

✅ Do some research: Read up on [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### File storage

File storage is storage of files in the cloud, and any apps or devices can connect using industry standard protocols. You can write files to file storage, then mount it as a drive on your PC or Mac.

✅ Do some research: Read up on [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Connect your serverless code to storage

Your function app now needs to connect to blob storage to store the messages from the IoT Hub. There's 2 ways to do this:

* Inside the function code, connect to blob storage using the blob storage Python SDK and write the data as blobs
* Use an output function binding to bind the return value of the function to blob storage and have the blob saved automatically

In this lesson, you will use the Python SDK to see how to interact with blob storage.

![Sending GPS telemetry from an IoT device to IoT Hub, then to Azure Functions via an event hub trigger, then saving it to blob storage](../../../images/save-telemetry-to-storage-from-functions.png)

The data will be saved as a JSON blob with the following format:

```json
{
    "device_id": <device_id>,
    "timestamp" : <time>,
    "gps" :
    {
        "lat" : <latitude>,
        "lon" : <longitude>
    }
}
```

### Task - connect your serverless code to storage

1. Create an Azure Storage account. Name it something like `gps<your name>`.

    > ⚠️ You can refer to the [instructions for creating a storage account from project 2, lesson 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources)  if needed.

    If you still have a storage account from the previous project, you can re-use this.

    > 💁 You will be able to use the same storage account to deploy your Azure Functions app later in this lesson.

1. Run the following command to get the connection string for the storage account:

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    Replace `<storage_name>` with the name of the storage account you created in the previous step.

1. Add a new entry to the `local.settings.json` file for your storage account connection string, using the value from the previous step. Name it `STORAGE_CONNECTION_STRING`

1. Add the following to the `requirements.txt` file to install the Azure storage Pip packages:

    ```sh
    azure-storage-blob
    ```

    Install the packages from this file in your virtual environment.

    > If you get an error, then upgrade your Pip version in your virtual environment to the latest version with the following command, then try again:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. In the `__init__.py` file for the `iot-hub-trigger`, add the following import statements:

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    The `json` system module will be used to read and write JSON, the `os` system module will be used to read the connection string, the `uuid` system module will be used to generate a unique ID for the GPS reading.

    The `azure.storage.blob` package contains the Python SDK to work with blob storage.

1. Before the `main` method, add the following helper function:

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    The Python blob SDK doesn't have a helper method to create a container if it doesn't exist. This code will load the connection string from the `local.settings.json` file (or the Application Settings once deployed to the cloud), then create a `BlobServiceClient` class from this to interact with the blob storage account. It then loops through all the containers for the blob storage account, looking for one with the provided name - if it finds one it will return a `ContainerClient` class that can interact with the container to create blobs. If it doesn't find one, then the container is created and the client for the new container is returned.

    When the new container is created, public access is granted to query the blobs in the container. This will be used in the next lesson to visualize the GPS data on a map.

1. Unlike with soil moisture, with this code we want to store every event, so add the following code inside the `for event in events:` loop in the `main` function, below the `logging` statement:

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    This code gets the device ID from the event metadata, then uses it to create a blob name. Blobs can be stored in folders, and device ID will be used for the folder name, so each device will have all its GPS events in one folder. The blob name is this folder, followed by a document name, separated with forward slashes, similar to Linux and macOS paths (similar to Windows as well, but Windows uses back slashes). The document name is a unique ID generated using the Python `uuid` module, with the file type of `json`.

    For example, for the `gps-sensor` device ID, the blob name might be `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Add the following code below this:

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    This code gets the container client using the `get_or_create_container` helper class, and then gets a blob client object using the blob name. These blob clients can refer to existing blobs, or as in this case, to new blob.

1. Add the following code after this:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    This builds the body of the blob that will be written to blob storage. It is a JSON document containing the device ID, the time the telemetry was sent to IoT Hub, and the GPS coordinates from the telemetry.

    > 💁 It is important to use the enqueued time of the message as opposed to the current time to get the time that the message was sent. It could be sitting on the hub for a while before being picked up if the Functions App is not running.

1. Add the following below this code:

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    This code logs that a blob is about to be written with it's details, then uploads the blob body as the content of the new blob.

1. Run the Functions app. You will see blobs being written for all the GPS events in the output:

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 Make sure you are not running the IoT Hub event monitor at the same time.

> 💁 You can find this code in the [code/functions](code/functions) folder.

### Task - verify the uploaded blobs

1. To view the blobs created, you can either use the [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), a free tool that allows you to view and manage your storage accounts, or from the CLI.

    1. To use the CLI, first you will need an account key. Run the following command to get this key:

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        Replace `<storage_name>` with the name of the storage account.

        Copy the value of `key1`.

    1. Run the following command to list the blobs in the container:

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        Replace `<storage_name>` with the name of the storage account, and `<key1>` with the value of `key1` you copied in the last step.

        This will list out all the blobs in the container:

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. Download one of the blobs using the following command:

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        Replace `<storage_name>` with the name of the storage account, and `<key1>` with the value of `key1` you copied in the earlier step.

        Replace `<blob_name>` with the full name from the `Name` column of the output of the last step, including the folder name. Replace `<file_name>` with the name of a local file to save the blob to.

    Once downloaded, you can open the JSON file in VS Code, and you will see the blob containing the GPS location details:

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Task - deploy your Functions App to the cloud

Now that your Function app is working, you can deploy it to the cloud.

1. Create a new Azure Functions app, using the storage account you created earlier. Name this something like `gps-sensor-` and add a unique identifier on the end, like some random words or your name.

    > ⚠️ You can refer to the [instructions for creating a Functions app from project 2, lesson 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) if needed.

1. Upload the `IOT_HUB_CONNECTION_STRING` and `STORAGE_CONNECTION_STRING` values to the Application Settings

    > ⚠️ You can refer to the [instructions for uploading Application Settings from project 2, lesson 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings) if needed.

1. Deploy your local Functions app to the cloud.

    > ⚠️ You can refer to the [instructions for deploying your Functions app from project 2, lesson 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud) if needed.

---

## 🚀 Challenge

GPS data is not perfectly accurate, and the locations being detected can be out by a few meters, if not more especially in tunnels and areas of tall buildings.

Think about how satellite navigation could overcome this? What data does your sat-nav have that would allow it to make better predictions on your location?

## Post-lecture quiz

[Post-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/24)

## Review & Self Study

* Read about structured data on the [Data model page on Wikipedia](https://wikipedia.org/wiki/Data_model)
* Read about semi-structured data on the [Semi-structured data page on Wikipedia](https://wikipedia.org/wiki/Semi-structured_data)
* Read about unstructured data on the [Unstructured data page on Wikipedia](https://wikipedia.org/wiki/Unstructured_data)
* Read more on Azure Storage and the different storage types in the [Azure Storage documentation](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Assignment

[Investigate function bindings](assignment.md)
