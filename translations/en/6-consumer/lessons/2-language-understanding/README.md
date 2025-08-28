<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-28T19:15:04+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "en"
}
-->
and paste it somewhere safe for later use.

    2. From the *Azure Resources* section, copy the *Primary Key* (API key) and the *Endpoint* URL.

1. Use these values to construct a curl command. Replace `<endpoint>`, `<app_id>`, and `<api_key>` with the values you copied:

    ```bash
    curl -X GET "<endpoint>/luis/prediction/v3.0/apps/<app_id>/slots/staging/predict?query=set%20a%20timer%20for%205%20minutes%20and%204%20seconds" -H "Ocp-Apim-Subscription-Key: <api_key>"
    ```

1. Run the curl command in your terminal. You should see a JSON response with the detected intent and entities.

## Use the language understanding model

Once the model is published, you can use it in your code to interpret user input. This involves sending the user's text to the LUIS endpoint and processing the JSON response to extract the intent and entities.

### Task - integrate the model into your code

1. Open your smart timer project in your code editor.

1. Add a function to send user input to the LUIS endpoint. Use the `requests` library in Python or an equivalent library in your programming language of choice to make an HTTP GET request to the LUIS endpoint.

1. Parse the JSON response to extract the intent and entities. For example, if the intent is `set timer` and the entities include `5 minutes` and `4 seconds`, your code should set a timer for 5 minutes and 4 seconds.

1. Test your code with various inputs to ensure it correctly interprets the user's intent and entities.

### Example code snippet (Python)

```python
import requests

def get_luis_prediction(query):
    endpoint = "<endpoint>"
    app_id = "<app_id>"
    api_key = "<api_key>"
    url = f"{endpoint}/luis/prediction/v3.0/apps/{app_id}/slots/staging/predict"
    params = {
        "query": query
    }
    headers = {
        "Ocp-Apim-Subscription-Key": api_key
    }
    response = requests.get(url, headers=headers, params=params)
    return response.json()

# Example usage
query = "set a timer for 5 minutes and 4 seconds"
result = get_luis_prediction(query)
print(result)
```

### Task - test the integration

1. Run your code and provide various inputs, such as "set a timer for 10 minutes" or "set a timer for 2 minutes and 30 seconds."

2. Verify that the correct intent and entities are extracted and that the timer is set accordingly.

3. Debug any issues by inspecting the JSON response from LUIS and ensuring your code correctly handles the data.

## Summary

In this lesson, you learned about language understanding and how to create, train, and use a language understanding model with LUIS. You explored the concepts of intents and entities, trained a model to interpret timer-related commands, and integrated the model into your code. By leveraging language understanding, you can create more intuitive and user-friendly applications that understand natural language input.
<your_ip_address>:7071/api/text-to-timer`, where `<your_ip_address>` is the IP address of your computer.

      For example, if your IP address is `192.168.1.100`, the URL will be `http://192.168.1.100:7071/api/text-to-timer`.

      > ⚠️ Make sure your firewall allows incoming connections on port 7071, or your IoT device won't be able to access the function.

2. Update your IoT device code to call the REST endpoint. Replace the placeholder URL with the URL of your function app, either the cloud URL or the local IP address URL.

3. Test your IoT device to ensure it can call the function app and receive the correct number of seconds for the timer.

> 💁 If you encounter issues, check the logs of your function app to see if the request is being received and processed correctly. Logs can provide valuable insights into any errors or unexpected behavior.
<IP_ADDRESS>
:7071/api/text-to-timer`, where `<IP_ADDRESS>` will be your IP address, for example `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Note that this uses port 7071, so after the IP address you will need to include `:7071`.

      > 💁 This will only work if your IoT device is on the same network as your computer.

1. Test the endpoint by accessing it using curl.

---

## 🚀 Challenge

There are many ways to request the same thing, such as setting a timer. Think of different ways to do this, and use them as examples in your LUIS app. Test these out to see how well your model can handle multiple ways to request a timer.

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Review & Self Study

* Learn more about LUIS and its capabilities on the [Language Understanding (LUIS) documentation page on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Explore more about language understanding on the [natural-language understanding page on Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* Dive deeper into HTTP triggers in the [Azure Functions HTTP trigger documentation on Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Assignment

[Cancel the timer](assignment.md)

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the definitive source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.