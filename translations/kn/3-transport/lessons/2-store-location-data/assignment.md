<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2026-01-07T05:00:08+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "kn"
}
-->
# ಕಾರ್ಯ ಬಾಂಧನೆಗಳ ಪರಿಶೀಲನೆ

## ಸೂಚನೆಗಳು

ಕಾರ್ಯ ಬಾಂಧನೆಗಳು ನಿಮ್ಮ ಕೋಡ್ ಅನ್ನು `main` ಕಾರ್ಯದಿಂದ ಮರಳಿಸುವ ಮೂಲಕ ಬ್ಲಾಬ್‌ಗಳನ್ನು ಬ್ಲಾಬ್ ಸಂರಕ್ಷಣೆಗೆ ಉಳಿಸುವಂತೆ ಅನುಮತಿಸುತ್ತವೆ. Azure ಸ್ಟೋರೆಜ್ ಖಾತೆ, ಸಂಗ್ರಹಣಾ ಮತ್ತು ಇತರ ವಿವರಗಳು `function.json` ಫೈಲ್‌ನಲ್ಲಿ ಸಂರಚಿಸಲ್ಪಟ್ಟಿವೆ.

Azure ಅಥವಾ ಇತರ Microsoft ತಂತ್ರಜ್ಞಾನಗಳೊಂದಿಗೆ ಕೆಲಸ ಮಾಡುವಾಗ, ಅತ್ಯುತ್ತಮ ಮಾಹಿತಿ ಮೂಲವು [docs.com-ನಲ್ಲಿ Microsoft ಡಾಕ್ಯುಮೆಂಟೇಶನ್](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn) ಆಗಿದೆ. ಈ ಕಾರ್ಯದಲ್ಲಿ ನಿಮ್ಮಿಗೆ ಔಟ್‌ಪುಟ್ ಬಾಂಧನವನ್ನು ಹೊಂದಿಸಲು ದೂರ ಮಾಡಲು Azure Functions ಬಾಂಧನೆಗಳ ಡಾಕ್ಯುಮೆಂಟೇಶನ್ ಓದಬೇಕಾಗುತ್ತದೆ.

ಪ್ರಾರಂಭಿಸಲು ಕೆಲವು ಪುಟಗಳು:

* [Azure Functions ಟ್ರಿಗ್ಗರ್‌ಗಳು ಮತ್ತು ಬಾಂಧನೆಗಳ ಕಲ್ಪನೆಗಳು](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob ಸ್ಟೋರೆಜ್ ಬಾಂಧನೆಗಳು Azure Functionsನೆ ಸಹಿತ ಅವಲೋಕನ](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Functionsಗೆ Azure Blob ಸ್ಟೋರೆಜ್ ಔಟ್‌ಪುಟ್ ಬಾಂಧನೆ](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## ಮೌಲ್ಯಮಾಪನ

| ಮಾನದಂಡ | ಮಾದರಿ | ಸೂಕ್ತ | ಸುಧಾರಣೆ ಬೇಕು |
| -------- | --------- | -------- | ----------------- |
| ಬ್ಲಾಬ್ ಸ್ಟೋರೆಜ್ ಔಟ್‌ಪುಟ್ ಬಾಂಧನವನ್ನು ಸಂರಚಿಸಿ | ಔಟ್‌ಪುಟ್ ಬಾಂಧನವನ್ನು ಸಂರಚಿಸಿ, ಬ್ಲಾಬ್ ಅನ್ನು ಮರಳು ಮತ್ತು ಅದನ್ನು ಬ್ಲಾಬ್ ಸ್ಟೋರೆಜ್‌ನಲ್ಲಿ ಯಶಸ್ವಿಯಾಗಿ ಸಂರಕ್ಷಿಸಲಾಯಿತು | ಔಟ್‌ಪುಟ್ ಬಾಂಧನವನ್ನು ಸಂರಚಿಸಲು ಸಾಧ್ಯವಾಯಿತು ಅಥವಾ ಬ್ಲಾಬ್ ಅನ್ನು ಮರಳಿಸುವ ಮೂಲಕ ಬ್ಲಾಬ್ ಸ್ಟೋರೆಜ್‌ನಲ್ಲಿ ಸಂರಕ್ಷಿಸಲು ಸಾಧ್ಯವಿಲ್ಲ |  ಔಟ್‌ಪುಟ್ ಬಾಂಧನವನ್ನು ಸಂರಚಿಸಲು ಸಾಧ್ಯವಾಗಲಿಲ್ಲ |

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ತಪ್ಪು ಬಿಟ್ಟಿದ್ದೇವೆ**:  
ಈ ದಾಖಲೆ [Co-op Translator](https://github.com/Azure/co-op-translator) ಎಂಬ AI ಅನುವಾದ ಸೇವೆಯನ್ನು ಬಳಸಿ ಅನುವಾದಿಸಲಾಗಿದೆ. ನಾವು ನಿಖರತೆಯನ್ನು ಗಮನಿಸುತ್ತಿದ್ದರೂ, ಸ್ವಯಂಚಾಲಿತ ಅನುವಾದಗಳಲ್ಲಿ ತಪ್ಪುಗಳಾಗುವ ಸಾಧ್ಯತೆ ಇರುವುದನ್ನು ತಿಳಿದುಕೊಳ್ಳಿ. ಮೂಲ ಪಾಠವನ್ನು ಅದರ ಸ್ವದೇಶಿ ಭಾಷೆಯಲ್ಲಿ ಅಧಿಕೃತ ಮೂಲವೆಂದು ಪರಿಗಣಿಸಬೇಕು. ಪ್ರಮುಖ ಮಾಹಿತಿಗಾಗಿ ವೃತ್ತಿಪರ ಮಾನವನ ಅನುವಾದವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗುತ್ತದೆ. ಈ ಅನುವಾದದ ಬಳಸುವಿಕೆಯಿಂದ ಉಂಟಾಗುವ ಯಾವುದೇ误解ಗಳು ಅಥವಾ ತಪ್ಪು ವಿವರಣೆಗೆ ನಾವು ಜವಾಬ್ದಾರರಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->