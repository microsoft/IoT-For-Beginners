# Run your fruit detector on the edge

<!-- This lesson is still under development -->

This video gives an overview of running image classifiers on IoT devices, the topic that is covered in this lesson.

[![Custom Vison AI on Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

> 🎥 Click the image above to watch a video

## Pre-lecture quiz

[Pre-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/33)

## Introduction

In this lesson you will learn about

In this lesson we'll cover:

* [Edge computing](#edge-computing)
* [Azure IoT Edge](#azure-iot-edge)
* [Register an IoT Edge device](#registeran-iot-edge-device)
* [Set up an IoT Edge device](#set-up-an-iot-dge-device)
* [Run your classifier on the edge](run-your-classifier-on-the-edge)

## Edge computing

## Azure IoT Edge

![The Azure IoT Edge logo](../../../images/azure-iot-edge-logo.png)

IoT Edge runs code from containers.

## Register an IoT Edge device

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

### Task - set up an IoT Edge device

The IoT Edge runtime only runs Linux containers. It can be run on Linux, or on Windows using Linux Virtual Machines.

* If you are using a Raspberry Pi as your IoT device, then this runs a supported version of Linux and can host the IoT Edge runtime. Follow the [Install Azure IoT Edge for Linux guide on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) to install IoT Edge and set the connection string.

    > 💁 Remember, Raspberry Pi OS is a variant of Debian Linux.

* If you are not using a Raspberry Pi, but have a Linux computer, you can run the IoT Edge runtime. Follow the [Install Azure IoT Edge for Linux guide on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) to install IoT Edge and set the connection string.

* If you are using Windows, you can install the IoT Edge runtime in a Linux Virtual Machine by following the [Install and start the IoT Edge runtime section of the Deploy your first IoT Edge module to a Windows device quickstart on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). You can stop when you reach the *Deploy a module* section.

* If you are using macOS, you can create a virtual machine (VM) in the cloud to use for your IoT Edge device. These are computers you can create in the cloud and access over the internet. You can create a Linux VM that has IoT Edge installed. Follow the [Create a virtual machine running IoT Edge guide](vm-iotedge.md) for instructions on how to do this.

## Create a classifier that can run on the edge

## Run your classifier on the edge

### Task - deploy your classifier using IoT Edge

### Task - use the edge classifier from your IoT device

---

## 🚀 Challenge

## Post-lecture quiz

[Post-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/34)

## Review & Self Study

## Assignment

[](assignment.md)
