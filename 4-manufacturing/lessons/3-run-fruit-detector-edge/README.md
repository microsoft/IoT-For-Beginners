# Run your fruit detector on the edge

Add a sketchnote if possible/appropriate

This video gives an overview of running image classifiers on IoT devices, the topic that is covered in this lesson.

[![Custom Vison AI on Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Pre-lecture quiz

[Pre-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/33)

## Introduction

In this lesson you will learn about how to run machine learning (ML) models on the edge. We'll cover the benefits and drawbacks of edge computing versus cloud computing


In this lesson we'll cover:

* [Comparison of Edge and Cloud Computing](#Comparison-of-Edge-and-Cloud-Computing)
* [How to register an edge device in Azure IoT Edge](#Azure-IoT-Edge)
* [How to configure a Custom Vision classifier for the edge](#Task----Create-a-CV-classifier-that-can-run-on-the-edge)
* [How to run the CV classifier on the edge via IoT Edge](#Run-your-classifier-on-the-edge)

## Comparison of Edge and Cloud Computing
Like most technologies, there are pros and cons to both edge computing and cloud computing. 

Edge computing may be preferred over cloud computing for four primary reasons:
1. **Speed**: edge computing is ideal for time-sensitive data as actions are done on the device, enabling higher speeds and requiring  less network traffic;
2. **Remote accessibility**: local compute is preferred in areas with limited or no connectivity to a centralized location; 
3. **Lower costs**: Performing data collection, storage, analysis, and triggering actions on the device reduces usage of cloud services which can reduce the overall cost of an IoT system; and
3. **Privacy and security**: with edge compute, data stays on the device and is not uploaded to the cloud. This is often preferred for sensitive and personally identifiable information, especially because data does not need to be saved on the device, which greatly reduces the risk of data leaks.

However, there are also situations in which cloud computing may be preferred. The main reasons include:
1. Scale and flexibility: Cloud computing can adjust to network and data needs in real-time by adding or reducing servers and other resources;
1. Reliability and resiliency: Cloud computing leverages multiple servers often in multiple locations for redundancy and disaster recovery; and
1. Maintenance: Cloud service providers provide system maintenance and updates. 

For IoT systems, you'll often want a blend of cloud and edge computing, leveraging each service based on the needs of the system, its customers, and its maintainers.

---

## Azure IoT Edge

![The Azure IoT Edge logo](../../../images/azure-iot-edge-logo.png)

Azure IoT Edge can make your IoT solution more efficient by moving workloads out of the cloud and to the edge. This capability lends itself well to services that process a lot of data, like computer vision models. 

IoT Edge runs code from containers. You can use Custom Vision to build custom image classifiers and deploy them to devices as containers. Together, these two services enable you to find insights from images or video streams without having to transfer all of the data to the cloud. 

## Register an IoT Edge device
![The Azure IoT Edge Diagram: Step 1 - Register an IoT Edge Device](../../images/register-device.png)

To use an IoT Edge device, it needs to be registered in IoT Hub. 

### Task - register an IoT Edge device

1. Create an IoT Hub in the `fruit-quality-detector` resource group. Give it a unique name based around `fruit-quality-detector`.

1. Register an IoT Edge device called `fruit-quality-detector-edge` in your IoT Hub. The command to do this is similar to the one used to register a non-edge device, except you pass the `--edge-enabled` flag.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Replace `<hub_name>` with the name of your IoT Hub.

1. Get the connection string for your device using the following command:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Replace `<hub_name>` with the name of your IoT Hub.

    Take a copy of the connection string that is shown in the output.

## Set up an IoT Edge device

### Task - Install and start the IoT Edge Runtime
![The Azure IoT Edge Diagram: Step 2 - Install and start the IoT Edge Runtime](/../../images/start-runtime.png)

**The IoT Edge runtime only runs Linux containers.** It can be run on Linux, or on Windows using Linux Virtual Machines.

* If you are using a Raspberry Pi as your IoT device, then this runs a supported version of Linux and can host the IoT Edge runtime. Follow the [Install Azure IoT Edge for Linux guide on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) to install IoT Edge and set the connection string.

    > 💁 Remember, Raspberry Pi OS is a variant of Debian Linux.

* If you are not using a Raspberry Pi, but have a Linux computer, you can run the IoT Edge runtime. Follow the [Install Azure IoT Edge for Linux guide on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) to install IoT Edge and set the connection string.

* If you are using Windows, you can install the IoT Edge runtime in a Linux Virtual Machine by following the [Install and start the IoT Edge runtime section of the Deploy your first IoT Edge module to a Windows device quickstart on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). You can stop when you reach the *Deploy a module* section.

* If you are using macOS, you can create a virtual machine (VM) in the cloud to use for your IoT Edge device. These are computers you can create in the cloud and access over the internet. You can create a Linux VM that has IoT Edge installed. Follow the [Create a virtual machine running IoT Edge guide](vm-iotedge.md) for instructions on how to do this.

#### Troubleshooting tips:
##### Virtual Machine:
1. Uninstall and try again

		```sh 
        . {Invoke-WebRequest -useb aka.ms/iotedge-win} | Invoke-Expression; 
		Uninstall-IoTEdge
        ```
1. More info: [Install Azure IoT Edge for Windows](https://docs.microsoft.com/en-us/azure/iot-edge/how-to-install-iot-edge-windows-on-windows?view=iotedge-2018-06#uninstall-iot-edge)

##### Raspberry Pi:
1. Uninstall and try again:

    ```sh 
    sudo apt-get remove aziot-edge
    ```
    When the IoT Edge runtime is removed, any containers that it created are stopped but still exist on your device. View all containers to see which ones remain:

    ```sh 
    sudo docker ps -a
    ```

    Delete the containers from your device, including the two runtime containers:

    ```sh
    sudo docker rm -f <container name>
    ```

    Finally, remove the container runtime from your device.

    ```sh
    sudo apt-get remove --purge moby-cli
    sudo apt-get remove --purge moby-engine
    ```
2. More info: [Install Azure IoT Edge for Windows](https://docs.microsoft.com/en-us/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11#uninstall-iot-edge)

## Task -- Create a CV classifier that can run on the edge
Since edge devices tend to have smaller amounts of storage space, we'll need to create a new Custom Vision image classification model that is compact. 

1. Login to your Custom Vision account
1. Open your Fruit Classifier project.
1. Click on 'Settings' (the ⚙ icon)
1. Change the Domain type to General (compact) domain 

    *Note: be sure to select the 'General (compact)' domain and **NOT** the 'General (compact) [S1]' domain*

1. Under 'Export Capabilities', select 'Basic platforms (Tensorflow, CoreML, ONNX, ...)'
    
1. At the bottom of the Settings page, click 'Save Changes'. 
1. Nagivate back to the Perfomance tab on the Custom Vision site and retrain your model using the Quick Training option.
1.  click the 'Export' button at the top.
1.  Choose the export option that matches your edge device:
    * For a Virtual Machine, select 'Dockerfile' and 'Linux' platform.
    * For a Raspberry Pi, select 'Dockerfile' and the 'ARM (Raspberry Pi 3)' platform. 
1. Save the files to your computer, then unzip the folder.

## Run your classifier on the edge
Next, we need to load the CV image classifier onto our edge device.
### Task - deploy your classifier using IoT Edge
To deploy our classifier, we'll need a service called [Docker](https://www.docker.com/).

* [Download Docker for the Raspberry Pi here](https://docs.docker.com/engine/install/debian/)
* [Download Docker for Linux here](https://docs.docker.com/engine/install/)

#### Raspberry Pi Instructions
⚠ **Important:** Be sure to use 'sudo' each time you run a docker command, otherwise you'll get a 'permission denied' error.

1. On your Pi, create a folder in your home directory called ```iot-edge-docker``` 
1. Transfer your CV export files from your PC into the Raspberry Pi ```iot-edge-docker``` folder.
1. In the Raspberry Pi terminal, navigate to the ```iot-edge-docker``` folder. B
1. Build the docker image with the following command, replacing <your-image-name> with ```fruit-detector-classifier```:

	```sh
    sudo docker build -t <your-image-name> .
    ```
1. Run the container using the following command:

    ```sh
    sudo docker run -p 127.0.0.1:80:80 -d fruit-detector-classifier
    ```

1. Check the images Docker created:

    ```sh
    sudo docker images
    ```
1. Test the container with one of the test images:

    ```sh
     curl -X POST http://127.0.0.1/url -d '{ "url": "https://raw.githubusercontent.com/microsoft/IoT-For-Beginners/main/4-manufacturing/lessons/1-train-fruit-detector/images/testing/ripe/banana-ripe-1.png?token=AB7YU53D4PFAEZDJHKXKXLDA5FAOE"}'
     ```
1. You should see an output like the following:

    ```sh
    {"created":"2021-07-03T06:41:19.706346","id":"","iteration":"","predictions":[{"boundingBox":null,"probability":1.0,"tagId":"","tagName":"ripe"}],"project":""}
    ```
    💁‍♀️```tagName``` is the prediction for the image we provided. ```probability``` is the model prediction estimate of its accuracy.

🎉 Congratulations! You've successfully deployed your Custom Vison model to your Raspberry Pi edge device!

#### Linux Virtual Machine Instructions

### Task - Use the edge classifier from your IoT device

## 🚀 Challenge

## Post-lecture quiz

[Post-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/34)

## Review & Self Study

## Assignment

[](assignment.md)
