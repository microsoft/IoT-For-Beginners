<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-28T19:17:17+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "en"
}
-->
# Cancel the timer

## Instructions

In this lesson, you've trained a model to understand how to set a timer. Another useful feature is the ability to cancel a timer—perhaps your bread is ready and can be taken out of the oven before the timer runs out.

Add a new intent to your LUIS app for canceling the timer. This intent won't require any entities, but it will need some example sentences. In your serverless code, handle this intent if it is identified as the top intent, log that the intent was recognized, and return an appropriate response.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Add the cancel timer intent to the LUIS app | Successfully added the intent and trained the model | Successfully added the intent but did not train the model | Failed to add the intent and train the model |
| Handle the intent in the serverless app | Successfully detected the intent as the top intent and logged it | Successfully detected the intent as the top intent | Failed to detect the intent as the top intent |

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.