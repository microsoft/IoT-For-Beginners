# Send notifications using Twilio

## Instructions

In your code so far you have just logged the distance to the geofence. In this assignment you will need to add a notification, either a text message, or an email, when the GPS coordinates are inside the geofence.

Azure Functions has many options for bindings, including to third-party services such as Twilio, a communications platform.

* Sign up for a free account at [Twilio.com](https://www.twilio.com)
* Read the documentation on binding Azure Functions to Twilio SMS on the [Microsoft docs Twilio binding for Azure Functions page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?tabs=python&WT.mc_id=academic-17441-jabenn).
* Read the documentation on binding Azure Functions to Twilio SendGrid to send emails on the [Microsoft docs Azure Functions SendGrid bindings page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?tabs=python&WT.mc_id=academic-17441-jabenn).
* Add the binding to your Functions app to be notified on the GPS coordinates either inside or outside the geofence - not both.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Configure the functions bindings and receive an email or SMS | Was able to configure the functions bindings and receive an email or SMS when inside or outside the geofence, but not both | Was able to configure the bindings but was unable to send the email or SMS, or was only able to send when the coordinates were both inside and outside | Was unable to configure the bindings and send an email or SMS |
