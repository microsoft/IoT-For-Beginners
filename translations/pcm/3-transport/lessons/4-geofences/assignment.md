<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-11-18T19:03:40+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "pcm"
}
-->
# Send notifications using Twilio

## Instructions

For di code wey you don write so far, you just dey log di distance to di geofence. For dis assignment, you go need add notification, either text message or email, wen di GPS coordinates dey inside di geofence.

Azure Functions get plenty options for bindings, including third-party services like Twilio, wey be communication platform.

* Sign up for free account for [Twilio.com](https://www.twilio.com)
* Read di documentation on how to bind Azure Functions to Twilio SMS for di [Microsoft docs Twilio binding for Azure Functions page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Read di documentation on how to bind Azure Functions to Twilio SendGrid to send emails for di [Microsoft docs Azure Functions SendGrid bindings page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Add di binding to your Functions app so you fit get notification wen di GPS coordinates dey either inside or outside di geofence - but no do both.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Configure di functions bindings and receive email or SMS | You fit configure di functions bindings and receive email or SMS wen di coordinates dey inside or outside di geofence, but no do both | You fit configure di bindings but you no fit send di email or SMS, or you only fit send wen di coordinates dey both inside and outside | You no fit configure di bindings and send email or SMS |

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don translate wit AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). Even as we dey try make am accurate, abeg sabi say machine translation fit get mistake or no dey correct well. Di original dokyument for di native language na di main source wey you go trust. For important mata, e good make professional human translator check am. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->