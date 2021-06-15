# Understand language

Add a sketchnote if possible/appropriate

![Embed a video here if available](video-url)

## Pre-lecture quiz

[Pre-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/33)

## Introduction

In the last lesson you converted speech to text. For this to be used to program a smart timer, your code will need to have an understanding of what was said. You could assume the user will speak a fixed phrase, such as "Set a 3 minute timer", and parse that expression to get how long the timer should be, but this isn't very user-friendly. If a user were to say "Set a timer for 3 minutes", you or I would understand what they mean, but your code would not, it would be expecting a fixed phrase.

This is where language understanding comes in, using AI models to interpret text and return the details that are needed, for example being able to take both "Set a 3 minute timer" and "Set a timer for 3 minutes", and understand that a timer is required for 3 minutes.

In this lesson you will learn about language understanding models, how to create them, train them, and use them from your code.

In this lesson we'll cover:

* [Language understanding](#language-understanding)
* [Create a language understanding model](create-a-language-understanding-model)
* [Intents and entities](#intents-and-entities)
* [Use the language understanding model](#use-the-language-understanding-model)

## Language understanding

## Create a language understanding model

![The LUIS logo](../../../images/luis-logo.png)

You can create language understanding models using LUIS, a language understanding service from Microsoft that is part of Cognitive Services.

### Task - create an authoring resource

To use LUIS, you need to create an authoring resource.

1. Use the following command to create an authoring resource in your `smart-timer` resource group:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Replace `<location>` with the location you used when creating the Resource Group.

    > ⚠️ LUIS isn't available in all regions, so if you get the following error:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > pick a different region.

    This will create a free-tier LUIS authoring resource.

### Task - create a language understanding app

1. Open the LUIS portal at [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) in your browser, and sign in with the same account you have been using for Azure.

1. Follow the instructions on the dialog to select your Azure subscription, then select the `smart-timer-luis-authoring` resource you have just created.

1. From the *Conversation apps* list, select the **New app** button to create a new application. Name the new app `smart-timer`, and set the *Culture* to your language.

    > 💁 There is a field for a prediction resource. You can create a second resource just for prediction, but the free authoring resource allows 1,000 predictions a month which should be enough for development, so you can leave this blank.

1. Read through the guide that appears once you cerate the app to get an understanding of the steps you need to take to train the language understanding model. Close this guide when you are done.

## Intents and entities

Language understanding is based around *intents* and *entities*. Intents are what the intent of the words are, for example setting a timer or ordering food. Entities are what the intent is referring to, such as the length of the timer, or the type of food. Each sentence that the model interprets should have at least one intent, and optionally one or more entities.

For example:

* "Set a 3 minute timer" - the intent is to *set a timer*, the entity is *3 minutes*.
* "Cancel my timer" - the intent is to *cancel a timer*, and there are no entities.
* "Order 3 large pineapple pizzas and a caesar salad" - the intent is to *order food*, the entities are *3 large pineapple pizzas* and *caesar salad*.

To train LUIS, first you set the entities. These can be a fixed list of terms, or learned from the text. For example, you could provide a fixed list of food available from your menu, with variations (or synonyms) of each word, such as *egg plant* and *aubergine* as variations of *aubergine*. LUIS also has pre-built entities that can be used, such as numbers and locations.

For setting a timer, you could have one entity using the pre-built number entities for the time, and another for the units, such as minutes and seconds. Each unit would have multiple variations to cover the singular and plural forms - such as minute and minutes.

Once the entities are defined, you create intents. These are learned by the model based on example sentences that you provide (known as utterances). For example, for a *set timer* intent, you might provide the following sentences:

* `set a 1 second timer`
* `set a timer for 1 minute and 12 seconds`
* `set a timer for 3 minutes`
* `set a 9 minute 30 second timer`

You then tell LUIS what parts of these sentences map to the entities:

![The sentence set a timer for 1 minute and 12 seconds broken into entities](../../../images/sentence-as-intent-entities.png)

The sentence `set a timer for 1 minute and 12 seconds` has the intent of `set timer`. It also has 2 entities with 2 values each:

|            | time | unit   |
| ---------- | ---: | ------ |
| 1 minute   | 1    | minute |
| 12 seconds | 12   | second |

To train a good model, you need a range of different example sentences to cover the many different ways someone might ask for the same thing.

> 💁 As with any AI model, the more data and the more accurate the data you use to train, the better the model.

✅ Think about the different ways you might ask the same thing and expect a human to understand.

### Task - add entities to the language understanding models

For the timer, you need to add 2 entities - one for the unit of time (minutes or seconds), and one for the number of minutes or seconds.

You can find instructions for using the LUIS portal in the [Quickstart: Build your app in LUIS portal documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. From the LUIS portal, select the *Entities* tab and add the *number* prebuilt entity by selecting the **Add prebuilt entity** button, then selecting *number* from the list.

1. Create a new entity for the time unit using the **Create** button. Name the entity `time unit` and set the type to *List*. Add values for `minute` and `second` to the *Normalized values* list, adding the singular and plural forms to the *synonyms* list. Press `return` after adding each synonym to add it to the list.

    | Normalized value | Synonyms        |
    | ---------------- | --------------- |
    | minute           | minute, minutes |
    | second           | second, seconds |

### Task - add intents to the language understanding models

1. From the *Intents* tab, select the **Create** button to create a new intent. Name this intent `set timer`.

1. In the examples, enter different ways to set a timer using both minutes, seconds and minutes and seconds combined. Examples could be:

    * `set a 1 second timer`
    * `set a 4 minute timer`
    * `set a 9 minute 30 second timer`
    * `set a timer for 1 minute and 12 seconds`
    * `set a timer for 3 minutes`
    * `set a timer for 3 minutes and 1 second`
    * `set a timer for 1 minute1 and 1 second`
    * `set a timer for 30 seconds`
    * `set a timer for 1 second`

1. As you enter each example, LUIS will start detecting entities, and will underline and label any it finds.

    ![The examples with the numbers and time units underlined by LUIS](../../../images/luis-intent-examples.png)

### Task - train and test the model

1. Once the entities and intents are configured, you can train the model using the **Train** button on the top menu. Select this button, and the model should train in a few seconds. The button will be greyed out whilst training, and be re-enabled once done.

1. Select the **Test** button from the top menu to test the language understanding model. Enter text such as `set a timer for 5 minutes and 4 seconds` and press return. The sentence will appear in a box under the text box that you typed it in to, and blow that will be the *top intent*, or the intent that was detected with the highest probability. This should be `set timer`. The intent name will be followed by the probability that the intent detected was the right one.

1. Select the **Inspect** option to see a breakdown of the results. You will see the top-scoring intent with it's percentage probability, along with lists of the entities detected.

1. Close the *Test* pane when you are done testing.

### Task - publish the model

To use this model from code, you need to publish it. When publishing from LUIS, you can publish to either a staging environment for testing, or a product environment for a full release. In this lesson, a staging environment is fine.

1. From the LUIS portal, select the **Publish** button from the top menu.

1. Make sure *Staging slot* is selected, then select **Done**. You will see a notification when the app is published.

1. You can test this using curl. To build the curl command, you need three values - the endpoint, the application ID (App ID) and an API key. These can be accessed from the **MANAGE** tab that can be selected from the top menu.

    1. From the *Settings* section, copy the App ID

    1. From the *Azure Resources* section, select *Authoring Resource*, and copy the *Primary Key* and *Endpoint URL*

1. Run the following curl command in your command prompt or terminal:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Replace `<endpoint url>` with the Endpoint URL from the *Azure Resources* section.

    Replace `<app id>` with the App ID from the *Settings* section.

    Replace `<primary key>` with the Primary Key from the *Azure Resources* section.

    Replace `<sentence>` with the sentence you want to test with.

1. The output of this call will be a JSON document that details the query, the top intent, and a list of entities broken down by type.

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    The JSON above came from querying with `set a timer for 45 minutes and 12 seconds`, The `set timer` was the top intent with a probability of 97%. Two *number* entities were detected, 45 and 12. Two *time-unit* entities were detected, `minute` and `second`.

## Use the language understanding model

### Task - create a serverless functions app

### Task - use the language understanding model

---

## 🚀 Challenge

## Post-lecture quiz

[Post-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/34)

## Review & Self Study

* Read more about LUIS and it's capabilities on the [Language Understanding (LUIS) documentation page on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)

## Assignment

[](assignment.md)
