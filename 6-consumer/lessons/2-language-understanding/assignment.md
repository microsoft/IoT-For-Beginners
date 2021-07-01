# Cancel the timer

## Instructions

So far in this lesson you have trained a model to understand setting a timer. Another useful feature is cancelling a timer - maybe your bread is ready and can be taken out of the oven before the timer is elapsed.

Add a new intent to your LUIS app to cancel the timer. It won't need any entities, but will need some example sentences. Handle this in your serverless code if it is the top intent, logging that the intent was recognized and returning an appropriate response.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Add the cancel timer intent to the LUIS app | Was able to add the intent and train the model | Was able to add the intent but not train the model | Was unable to add the intent and train the model  |
| Handle the intent in the serverless app | Was able to detect the intent as the top intent and log it | Was able to detect the intent as the top intent | Was unable to detect the intent as the top intent |
