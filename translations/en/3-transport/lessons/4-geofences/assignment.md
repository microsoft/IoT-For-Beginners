<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-28T19:42:32+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "en"
}
-->
# Send notifications using Twilio

## Instructions

In your code so far, you've only logged the distance to the geofence. In this assignment, you'll need to add a notification—either a text message or an email—when the GPS coordinates are inside the geofence.

Azure Functions offers various options for bindings, including integrations with third-party services like Twilio, a communications platform.

* Sign up for a free account at [Twilio.com](https://www.twilio.com)
* Review the documentation on how to bind Azure Functions to Twilio SMS on the [Microsoft docs Twilio binding for Azure Functions page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Review the documentation on how to bind Azure Functions to Twilio SendGrid for sending emails on the [Microsoft docs Azure Functions SendGrid bindings page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Add the binding to your Functions app to send notifications based on whether the GPS coordinates are inside or outside the geofence—but not both.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Configure the functions bindings and receive an email or SMS | Successfully configured the functions bindings and received an email or SMS when the coordinates were inside or outside the geofence, but not both | Configured the bindings but was unable to send the email or SMS, or sent notifications for both inside and outside the geofence | Unable to configure the bindings or send an email or SMS |

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we strive for accuracy, please note that automated translations may contain errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is recommended. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.