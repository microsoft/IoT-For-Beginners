<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-28T19:07:30+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "en"
}
-->
# Run other services on the edge

## Instructions

It's not just image classifiers that can be run on the edge—anything that can be packaged into a container can be deployed to an IoT Edge device. Serverless code running as Azure Functions, such as the triggers you've created in earlier lessons, can also be run in containers, and therefore on IoT Edge.

Choose one of the previous lessons and try running the Azure Functions app in an IoT Edge container. You can find a guide that explains how to do this using a different Functions app project in the [Tutorial: Deploy Azure Functions as IoT Edge modules on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Deploy an Azure Functions app to IoT Edge | Successfully deployed an Azure Functions app to IoT Edge and used it with an IoT device to run a trigger from IoT data | Successfully deployed a Functions app to IoT Edge, but was unable to get the trigger to activate | Unable to deploy a Functions app to IoT Edge |

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.