<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-27T20:33:03+00:00",
  "source_file": "clean-up.md",
  "language_code": "sw"
}
-->
# Safisha mradi wako

Baada ya kukamilisha kila mradi, ni vizuri kufuta rasilimali zako za wingu.

Katika masomo ya kila mradi, huenda ulitengeneza baadhi ya yafuatayo:

* Kikundi cha Rasilimali
* IoT Hub
* Usajili wa vifaa vya IoT
* Akaunti ya Hifadhi
* Programu ya Functions
* Akaunti ya Azure Maps
* Mradi wa maono maalum
* Usajili wa Kontena la Azure
* Rasilimali ya huduma za kognitivi

Rasilimali nyingi kati ya hizi hazitakuwa na gharama - aidha ni bure kabisa, au unatumia kiwango cha bure. Kwa huduma zinazohitaji kiwango cha kulipia, huenda ulikuwa unazitumia kwa kiwango kilichojumuishwa katika posho ya bure, au zitagharimu senti chache tu.

Hata kwa gharama ndogo kiasi, ni vyema kufuta rasilimali hizi unapomaliza. Kwa mfano, unaweza kuwa na IoT Hub moja tu inayotumia kiwango cha bure, kwa hivyo ukitaka kutengeneza nyingine utahitaji kutumia kiwango cha kulipia.

Huduma zako zote zilitengenezwa ndani ya Vikundi vya Rasilimali, na hili hufanya iwe rahisi kusimamia. Unaweza kufuta Kikundi cha Rasilimali, na huduma zote ndani ya Kikundi hicho cha Rasilimali zitafutwa pamoja nacho.

Ili kufuta Kikundi cha Rasilimali, endesha amri ifuatayo kwenye terminal au command prompt yako:

```sh
az group delete --name <resource-group-name>
```

Badilisha `<resource-group-name>` na jina la Kikundi cha Rasilimali unalovutiwa nacho.

Uthibitisho utaonekana:

```output
Are you sure you want to perform this operation? (y/n): 
```

Ingiza `y` kuthibitisha na kufuta Kikundi cha Rasilimali.

Itachukua muda kufuta huduma zote.

> 💁 Unaweza kusoma zaidi kuhusu kufuta vikundi vya rasilimali kwenye [Nyaraka za Microsoft Docs kuhusu kufuta vikundi vya rasilimali na rasilimali za Azure Resource Manager](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.