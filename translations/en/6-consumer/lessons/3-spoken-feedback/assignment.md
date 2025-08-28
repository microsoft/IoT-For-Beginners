<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da5d9360fe02fdcc1e91a725016c846d",
  "translation_date": "2025-08-28T19:22:24+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/assignment.md",
  "language_code": "en"
}
-->
# Cancel the timer

## Instructions

In the assignment from the previous lesson, you added a cancel timer intent to LUIS. For this assignment, you need to handle this intent in the serverless code, send a command to the IoT device, and then cancel the timer.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Handle the intent in serverless code and send a command | Successfully handled the intent and sent a command to the device | Successfully handled the intent but failed to send the command to the device | Failed to handle the intent |
| Cancel the timer on the device | Successfully received the command and canceled the timer | Successfully received the command but failed to cancel the timer | Failed to receive the command |

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.