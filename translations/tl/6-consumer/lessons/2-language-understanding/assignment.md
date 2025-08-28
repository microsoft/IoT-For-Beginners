<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-27T23:13:08+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "tl"
}
-->
# Kanselahin ang timer

## Mga Instruksyon

Sa ngayon sa araling ito, natutunan mo kung paano sanayin ang isang modelo upang maunawaan ang pag-set ng timer. Isa pang kapaki-pakinabang na tampok ay ang pagkansela ng timer - halimbawa, kung handa na ang iyong tinapay at maaari na itong alisin sa oven bago matapos ang timer.

Magdagdag ng bagong intent sa iyong LUIS app upang kanselahin ang timer. Hindi nito kakailanganin ang anumang mga entity, ngunit kakailanganin nito ng ilang mga halimbawa ng pangungusap. I-handle ito sa iyong serverless code kung ito ang top intent, i-log na na-recognize ang intent, at magbalik ng angkop na tugon.

## Rubric

| Pamantayan | Napakahusay | Katanggap-tanggap | Kailangan ng Pagpapabuti |
| ---------- | ----------- | ----------------- | ------------------------ |
| Magdagdag ng intent para sa pagkansela ng timer sa LUIS app | Naidagdag ang intent at nasanay ang modelo | Naidagdag ang intent ngunit hindi nasanay ang modelo | Hindi naidagdag ang intent at hindi nasanay ang modelo |
| I-handle ang intent sa serverless app | Na-detect ang intent bilang top intent at na-log ito | Na-detect ang intent bilang top intent | Hindi na-detect ang intent bilang top intent |

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.