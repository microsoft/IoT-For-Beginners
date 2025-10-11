<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-10-11T12:05:51+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "et"
}
-->
# Uuri funktsioonide sidumisi

## Juhised

Funktsioonide sidumised võimaldavad teie koodil salvestada objekte blob-salvestusse, tagastades need `main` funktsioonist. Azure Storage konto, kogum ja muud üksikasjad konfigureeritakse `function.json` failis.

Azure'i või teiste Microsofti tehnoloogiatega töötades on parim teabeallikas [Microsofti dokumentatsioon aadressil docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). Selles ülesandes peate lugema Azure Functions sidumise dokumentatsiooni, et välja selgitada, kuidas seadistada väljundsidumist.

Mõned lehed, mida alustamiseks vaadata:

* [Azure Functions triggerite ja sidumiste kontseptsioonid](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob Storage sidumised Azure Functions jaoks - ülevaade](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob Storage väljundsidumine Azure Functions jaoks](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Hindamiskriteeriumid

| Kriteerium | Näidislik | Piisav | Vajab parandamist |
| ---------- | --------- | ------ | ----------------- |
| Blob-salvestuse väljundsidumise seadistamine | Suutis seadistada väljundsidumise, tagastada blob'i ja salvestada selle edukalt blob-salvestusse | Suutis seadistada väljundsidumise või tagastada blob'i, kuid ei suutnud seda edukalt blob-salvestusse salvestada | Ei suutnud seadistada väljundsidumist |

---

**Lahtiütlus**:  
See dokument on tõlgitud, kasutades AI tõlketeenust [Co-op Translator](https://github.com/Azure/co-op-translator). Kuigi püüame tagada täpsust, palun arvestage, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks lugeda autoriteetseks allikaks. Olulise teabe puhul on soovitatav kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valede tõlgenduste eest.