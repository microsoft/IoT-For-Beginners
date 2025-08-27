<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-27T23:30:46+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "sw"
}
-->
# Jenga Mzunguko wa Kumwagilia Maji Ulio Bora Zaidi

## Maelekezo

Somo hili lilifundisha jinsi ya kudhibiti relay kupitia data ya kihisi, ambapo relay hiyo inaweza kudhibiti pampu kwa mfumo wa umwagiliaji. Kwa eneo fulani la udongo, kuendesha pampu kwa muda maalum kunapaswa kuwa na athari sawa kwenye unyevu wa udongo. Hii inamaanisha unaweza kupata wazo la sekunde ngapi za umwagiliaji zinahusiana na upungufu fulani wa usomaji wa unyevu wa udongo. Kutumia data hii, unaweza kujenga mfumo wa umwagiliaji ulio na udhibiti zaidi.

Kwa kazi hii, utahesabu muda ambao pampu inapaswa kuendeshwa ili kuongeza unyevu wa udongo kwa kiwango fulani.

> ⚠️ Ikiwa unatumia vifaa vya IoT vya kawaida, unaweza kufuata mchakato huu, lakini uigize matokeo kwa kuongeza usomaji wa unyevu wa udongo kwa mkono kwa kiwango maalum kwa sekunde kila relay inapowashwa.

1. Anza na udongo mkavu. Pima unyevu wa udongo.

1. Ongeza kiasi maalum cha maji, ama kwa kuendesha pampu kwa sekunde 1 au kwa kumimina kiasi maalum cha maji.

    > Pampu inapaswa kila mara kuendeshwa kwa kiwango cha kasi kisichobadilika, hivyo kila sekunde pampu inapofanya kazi inapaswa kutoa kiasi sawa cha maji.

1. Subiri hadi kiwango cha unyevu wa udongo kitulie na uchukue usomaji.

1. Rudia hatua hii mara kadhaa na tengeneza jedwali la matokeo. Mfano wa jedwali hili umeonyeshwa hapa chini.

    | Muda wa Jumla wa Pampu | Unyevu wa Udongo | Upungufu |
    | --- | --: | -: |
    | Kavu | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Hesabu ongezeko la wastani la unyevu wa udongo kwa sekunde ya maji. Katika mfano hapo juu, kila sekunde ya maji inapunguza usomaji kwa wastani wa 20.3.

1. Tumia data hii kuboresha ufanisi wa msimbo wa seva yako, kwa kuendesha pampu kwa muda unaohitajika ili kufikia kiwango kinachohitajika cha unyevu wa udongo.

## Rubric

| Vigezo | Bora Kabisa | Inaridhisha | Inahitaji Kuboresha |
| -------- | --------- | -------- | ----------------- |
| Kukusanya data ya unyevu wa udongo | Inaweza kukusanya usomaji mwingi baada ya kuongeza kiasi maalum cha maji | Inaweza kukusanya baadhi ya usomaji kwa kiasi maalum cha maji | Inaweza tu kukusanya usomaji mmoja au miwili, au haiwezi kutumia kiasi maalum cha maji |
| Kurekebisha msimbo wa seva | Inaweza kuhesabu wastani wa upungufu wa usomaji wa unyevu wa udongo na kusasisha msimbo wa seva kutumia hii | Inaweza kuhesabu wastani wa upungufu, lakini haiwezi kusasisha msimbo wa seva, au haiwezi kuhesabu wastani kwa usahihi, lakini inatumia thamani hii kusasisha msimbo wa seva kwa usahihi | Haiwezi kuhesabu wastani, au kusasisha msimbo wa seva |

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.