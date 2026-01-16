<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2026-01-07T06:51:13+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "kn"
}
-->
# ಚಿತ್ರವನ್ನು ವರ್ಗೀಕರಿಸಿ - ವರ್ಚುವಲ್ ಐಒಟಿ ಹಾರ್ಡ್‌ವೇರ್ ಮತ್ತು ರಾಸ್ಬೆರಿ ಪಿ

ಪಾಠದ ಈ ಭಾಗದಲ್ಲಿ, ನೀವು ಕ್ಯಾಮೆರಾ ಮೂಲಕ ಹಿಡಿದ ಚಿತ್ರವನ್ನು ಕಸ್ಟಮ್ ವಿಜೆನ್ ಸೇವೆಗೆ ಕಳುಹಿಸಿ ಅದನ್ನು ವರ್ಗೀಕರಿಸುವಿರಿ.

## ಚಿತ್ರಗಳನ್ನು ಕಸ್ಟಮ್ ವಿಜೆನ್ ಗೆ ಕಳುಹಿಸಿ

ಕಸ್ಟಮ್ ವಿಜೆನ್ ಸೇವೆಗೆ ಚಿತ್ರಗಳನ್ನು ವರ್ಗೀಕರಿಸಲು ಪೈಥಾನ್ SDK ದೊರಕಿದೆ.

### ಕಾರ್ಯ - ಚಿತ್ರಗಳನ್ನು ಕಸ್ಟಮ್ ವಿಜೆನ್ ಗೆ ಕಳುಹಿಸಿ

1. VS ಕೋಡ್ ನಲ್ಲಿ `fruit-quality-detector` ಫೋಲ್ಡರ್ ಅನ್ನು ತೆರೆಯಿರಿ. ನೀವು ವರ್ಚುವಲ್ ಐಒಟಿ ಸಾಧನವನ್ನು ಬಳಸುತ್ತಿದ್ದರೆ, ಟರ್ಮಿನಲ್ನಲ್ಲಿ ವರ್ಚುವಲ್ ಪರಿಸರ ಚಾಲನೆಯಲ್ಲಿದೆ ಎಂದು ಖಚಿತಪಡಿಸಿಕೊಳ್ಳಿ.

1. ಕಸ್ಟಮ್ ವಿಜೆನ್ ಗೆ ಚಿತ್ರಗಳನ್ನು ಕಳುಹಿಸಲು ಪೈಥಾನ್ SDK ಪಿಪ್ ಪ್ಯಾಕೇಜ್ ಆಗಿದೆ. ಕೆಳಗಿನ ಕಮಾಂಡ್ ಬಳಸಿ ಅದನ್ನು ಸ್ಥಾಪಿಸಿ:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. `app.py` ಫೈಲ್ ಟಾಪ್ ನಲ್ಲಿ ಕೆಳಗಿನ ಇಂಪೋರ್ಟ್ ಸ್ಟೇಟ್‌ಮೆಂಟ್‌ಗಳನ್ನು ಸೇರಿಸಿ:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    ಇದು ಕಸ್ಟಮ್ ವಿಜೆನ್ ಲೈಬ್ರರಿಗಳಿಂದ ಕೆಲವು ಮೋಡುಲ್‌ಗಳನ್ನು ತರುತ್ತದೆ, ಒಂದು prediction key ಯೊಂದಿಗೆ ಪ್ರಮಾಣೀಕರಿಸಲು, ಮತ್ತೊಂದು prediction client ಕ್ಲಾಸ್ ಅನ್ನು ಒದಗಿಸಲು ಅದನ್ನು ಕಸ್ಟಮ್ ವಿಜೆನ್ ಕರೆ ಮಾಡಲು ಬಳಸಬಹುದು.

1. ಫೈಲ್ ಕೊನೆಗೆ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    ಈ ಪಾಠದ ಮುಂಚೆ *Prediction URL* ಸಂವಾದದಿಂದ ನಕಲಿಸಿದ URL ಅನ್ನು `<prediction_url>` ನೊಂದಿಗೆ ಬದಲಾಯಿಸಿ. ಅದೇ ಸಂವಾದದಿಂದ ನಕಲಿಸಿದ prediction key ಯನ್ನು `<prediction key>` ನೊಂದಿಗೆ ಬದಲಾಯಿಸಿ.

1. *Prediction URL* ಸಂವಾದದಿಂದ ಒದಗಿಸಿದ prediction URL ನೇರವಾಗಿ REST ಎಂಡ್‌ಪಾಯಿಂಟ್ ಅನ್ನು ಕರೆ ಮಾಡಲು ವಿನ್ಯಾಸಗೊಳಿಸಲಾಗಿದೆ. ಪೈಥಾನ್ SDK URL ಭಾಗಗಳನ್ನು ವಿವಿಧ ಸ್ಥಾನಗಳಲ್ಲಿ ಬಳಸುತ್ತದೆ. ಈ URL ಅನ್ನು ಅಗತ್ಯಭಾಗಗಳಾಗಿ ವಿಭಜಿಸಲು ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    ಇದು URL ಅನ್ನು ವಿಭಜಿಸಿ, `https://<location>.api.cognitive.microsoft.com` ಎಂಬ ಎಂಡ್‌ಪಾಯಿಂಟ್, ಪ್ರಾಜೆಕ್ಟ್ ಐಡಿ ಮತ್ತು ಪ್ರಕಟಿತ iteration ನ ಹೆಸರನ್ನು ತೆಗೆಯುತ್ತದೆ.

1. prediction ಮಾಡಲು ಕೆಳಗಿನ ಕೋಡ್ ಬಳಸಿ predictor ಆಬ್ಜೆಕ್ಟ್ ಸೃಷ್ಟಿಸಿ:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` prediction key ನ್ನು ಸುತ್ತಿಕೊಂಡಿವೆ. ಅವುಗಳನ್ನು ಬಳಸಿಕೊಂಡು prediction client ಆಬ್ಜೆಕ್ಟ್ ಅನ್ನು ಎಂಡ್‌ಪಾಯಿಂಟ್ ಕಡೆ ಕೊಂಡೊಯ್ಯಲಾಗುತ್ತದೆ.

1. ಕೆಳಗಿನ ಕೋಡ್ ಬಳಸಿ ಚಿತ್ರವನ್ನು ಕಸ್ಟಮ್ ವಿಜೆನ್ ಗೆ ಕಳುಹಿಸಿ:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    ಇದು ಚಿತ್ರವನ್ನು ಆರಂಭಕ್ಕೆ ಮರಳಿಸಿ, ನಂತರ prediction client ಗೆ ಕಳುಹಿಸುತ್ತದೆ.

1. ಕೊನೆಗೆ, ಫಲಿತಾಂಶಗಳನ್ನು ಕೆಳಗಿನ ಕೋಡ್ ಬಳಸಿ ತೋರಿಸಿ:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    ಇದು ಮರಳಿಸಲಾದ ಎಲ್ಲಾ prediction ಗಳ ಮೂಲಕ ಲೂಪ್ ಆಗಿ, ಅವುಗಳನ್ನು ಟರ್ಮಿನಲ್ ನಲ್ಲಿ ತೋರಿಸುತ್ತದೆ. ಮರಳಿಸಲಾದ ಸಾಧ್ಯತೆಗಳು 0-1 ವರೆಗೆ ಫ್ಲೋಟಿಂಗ್ ಪಾಯಿಂಟ್ ಸಂಖ್ಯೆಗಳನ್ನು ಹೊಂದಿದ್ದು, 0 ಎಂದರೆ ಟ್ಯಾಗ್ ಗೆ ಮ್ಯಾಚ್ ಆಗುವ ಸಾಧ್ಯತೆ 0%, ಮತ್ತು 1 ಎಂದರೆ 100% ಸಾಧ್ಯತೆ.

    > 💁 ಚಿತ್ರ ವರ್ಗೀಕರಿಸುವವರಿಗೆ ಬಳಸಲಾದ ಎಲ್ಲಾ ಟ್ಯಾಗ್ ಗಳ ಶೇಕಡಾವಾರು ಫಲಿತಾಂಶಗಳು ಮರಳಿಸಲ್ಪಡುವುವು. ಪ್ರತಿ ಟ್ಯಾಗ್ ಗೆ ಚಿತ್ರವು ಅದಕ್ಕೆ ಹೊಂದಿದ ಸಾಧ್ಯತೆ ಇರುತ್ತದೆ.

1. ನಿಮ್ಮ ಕ್ಯಾಮೆರಾ ಕೆಲವು ಹಣ್ಣುಗಳ ಮೇಲೆ ಇಟ್ಟು, ಅಥವಾ ಸೂಕ್ತ ಚಿತ್ರ ಸರಣಿಯನ್ನು ಬಳಸಿಕೊಂಡು, ಅಥವಾ ವರ್ಚುವಲ್ ಐಒಟಿ ಹಾರ್ಡ್‌ವೇರ್ ಬಳಸಿ ವೆಬ್ಕ್ಯಾಮ್ ನಲ್ಲಿ ಹಣ್ಣು ಕಾಣಿಸುವಂತೆ ನಿಮ್ಮ ಕೋಡ್ ರನ್ ಮಾಡಿ. ಕಾನ್ಸೋಲ್ ನಲ್ಲಿ ಔಟ್‌ಪುಟ್ ಕಾಣಿಸಿಕೊಳ್ಳುತ್ತದೆ:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    ನೀವು ತೆಗೆಸಿದ ಚಿತ್ರವನ್ನು ಮತ್ತು ಈ ಮೌಲ್ಯಗಳನ್ನು **Predictions** ಟ್ಯಾಬ್ ನಲ್ಲಿ ಕಸ್ಟಮ್ ವಿಜೆನ್ ನಲ್ಲಿ ನೋಡಬಹುದು.

    ![A banana in custom vision predicted ripe at 56.8% and unripe at 43.1%](../../../../../translated_images/kn/custom-vision-banana-prediction.30cdff4e1d72db5d.png)

> 💁 ನೀವು ಈ ಕೋಡ್ ಅನ್ನು [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) ಅಥವಾ [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಹುಡುಕಬಹುದು.

😀 ನಿಮ್ಮ ಹಣ್ಣು ಗುಣಮಟ್ಟ ವರ್ಗೀಕರಿಸುವ ಕಾರ್ಯಕ್ರಮ ಯಶಸ್ವಿಯಾಯಿತು!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ಅತ್ಯಂತಮುಕ್ತ ಸೂಚನೆ**:  
ಈ ದಾಖಲೆಯನ್ನು AI ಭಾಷಾಂತರ ಸೇವೆ [Co-op Translator](https://github.com/Azure/co-op-translator) ಬಳಸಿ ಅನುವದಿಸಲಾಗಿದೆ. ನಾವು ಸರಿಯಾದ ಅನುವಾದಕ್ಕಾಗಿ ಪ್ರಯತ್ನಿಸುತ್ತಿದ್ದರೂ, ಸ್ವಯಂಚಾಲಿತ ಭಾಷಾಂತರಗಳಲ್ಲಿ ತಪ್ಪುಗಳು ಅಥವಾ ಅಸತ್ಯತೆಗಳು ಇರಬಹುದು ಎಂಬುದನ್ನು ಗಮನದಲ್ಲಿರಿಸಿ. ಮೂಲ ಭಾಷೆಯ ಮೂಲ ದಾಖಲೆನ್ನು ನಂಬಿಗಸ್ಥ ಮೂಲವಾಗಿ ಪರಿಗಣಿಸಬೇಕು. ಮಹತ್ವಪೂರ್ಣ ಮಾಹಿತಿಗಾಗಿ, ಪೇಸ್ ಪ್ರವೀಣ ಮಾನವ ಭಾಷಾಂತರವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗಿದೆ. ಈ ಭಾಷಾಂತರವನ್ನು ಬಳಸಿದಾಗ ಉಂಟಾಗುವ ಯಾವುದೇ ಅರ್ಥಬದಲಾಗುವ ತಪ್ಪುಗಳಿಗೆ ನಾವು ಹೊಣೆಗಾರರಾಗುವುದಿಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->