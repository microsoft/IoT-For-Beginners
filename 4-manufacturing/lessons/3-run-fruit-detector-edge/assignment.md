# Run other services on the edge

## Instructions

It's not just image classifiers that can be run on the edge, anything that can be packaged up into a container can be deployed to an IoT Edge device. Serverless code running as Azure Functions, such as the triggers you've created in earlier lessons can be run in containers, and therefor on IoT Edge.

Pick one of the previous lessons and try to run the Azure Functions app in an IoT Edge container. You can find a guide that shows how to do this using a different Functions app project in the [Tutorial: Deploy Azure Functions as IoT Edge modules on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?view=iotedge-2020-11&WT.mc_id=academic-17441-jabenn).

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Deploy an Azure Functions app to IoT Edge | Was able to deploy an Azure Functions app to IoT Edge and use it with an IoT device to run a trigger from IoT data | Was able to deploy a Functions App to IoT Edge, but was unable to get the trigger to fire | Was unable to deploy a Functions App to IoT Edge |
