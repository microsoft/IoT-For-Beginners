<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-10-11T11:43:14+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "et"
}
-->
# Käivita teisi teenuseid servas

## Juhised

Servas ei saa käivitada ainult pildiklassifitseerijaid – kõike, mida saab konteinerisse pakendada, saab juurutada IoT Edge seadmesse. Serverivaba kood, mis töötab Azure Functionsina, näiteks päästikud, mida olete varasemates tundides loonud, saab konteinerites käivitada ja seega ka IoT Edge'is.

Valige üks varasematest tundidest ja proovige käivitada Azure Functions rakendus IoT Edge konteineris. Juhendi, mis näitab, kuidas seda teha teise Functions rakendusprojekti abil, leiate [Õpetus: Azure Functions juurutamine IoT Edge moodulitena Microsofti dokumentatsioonis](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Hindamiskriteeriumid

| Kriteerium | Silmapaistev | Piisav | Vajab parandamist |
| ---------- | ------------ | ------ | ----------------- |
| Azure Functions rakenduse juurutamine IoT Edge'i | Suutis juurutada Azure Functions rakenduse IoT Edge'i ja kasutada seda IoT seadmega, et käivitada päästik IoT andmetest | Suutis juurutada Functions rakenduse IoT Edge'i, kuid ei suutnud päästikut käivitada | Ei suutnud juurutada Functions rakendust IoT Edge'i |

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.