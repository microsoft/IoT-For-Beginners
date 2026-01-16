<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-27T21:55:15+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "tl"
}
-->
# I-calibrate ang iyong sensor

## Mga Instruksyon

Sa araling ito, nakakuha ka ng mga pagbasa mula sa soil moisture sensor, na sinusukat bilang mga halaga mula 0-1023. Upang ma-convert ang mga ito sa aktwal na mga pagbasa ng soil moisture, kailangan mong i-calibrate ang iyong sensor. Magagawa mo ito sa pamamagitan ng pagkuha ng mga pagbasa mula sa mga sample ng lupa, pagkatapos ay kalkulahin ang gravimetric soil moisture content mula sa mga sample na ito.

Kailangan mong ulitin ang mga hakbang na ito nang maraming beses upang makuha ang mga kinakailangang pagbasa, gamit ang iba't ibang antas ng basa ng lupa sa bawat pagkakataon.

1. Kumuha ng pagbasa ng soil moisture gamit ang soil moisture sensor. Isulat ang pagbasa na ito.

1. Kumuha ng sample ng lupa, at timbangin ito. Isulat ang timbang na ito.

1. Patuyuin ang lupa - ang mainit na oven sa 110°C (230°F) sa loob ng ilang oras ang pinakamainam na paraan, maaari mo itong gawin sa sikat ng araw, o ilagay ito sa isang mainit, tuyong lugar hanggang sa ang lupa ay ganap na matuyo. Dapat itong maging pulbos at maluwag.

    > 💁 Sa isang laboratoryo, para sa pinaka-eksaktong resulta, patuyuin ito sa oven sa loob ng 48-72 oras. Kung may drying ovens sa inyong paaralan, tingnan kung maaari mong gamitin ang mga ito para sa mas mahabang oras ng pagpapatuyo. Mas matagal, mas tuyo ang sample at mas eksakto ang resulta.

1. Timbangin muli ang lupa.

    > 🔥 Kung pinatuyo mo ito sa oven, siguraduhing lumamig muna ito!

Ang gravimetric soil moisture ay kinakalkula bilang:

![soil moisture % ay timbang ng basa minus timbang ng tuyo, hinati sa timbang ng tuyo, times 100](../../../../../translated_images/tl/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W - ang timbang ng basang lupa  
* W - ang timbang ng tuyong lupa  

Halimbawa, sabihin nating mayroon kang sample ng lupa na may timbang na 212g basa, at 197g tuyo.

![Ang kalkulasyon na may sagot](../../../../../translated_images/tl/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212g  
* W = 197g  
* 212 - 197 = 15  
* 15 / 197 = 0.076  
* 0.076 * 100 = 7.6%

Sa halimbawang ito, ang lupa ay may gravimetric soil moisture na 7.6%.

Kapag mayroon ka nang mga pagbasa para sa hindi bababa sa 3 sample, gumawa ng graph ng soil moisture % kumpara sa pagbasa ng soil moisture sensor at magdagdag ng linya na pinakamahusay na magkasya sa mga puntos. Magagamit mo ito upang kalkulahin ang gravimetric soil moisture content para sa isang partikular na pagbasa ng sensor sa pamamagitan ng pagkuha ng halaga mula sa linya.

## Rubric

| Pamantayan | Napakahusay | Katamtaman | Kailangan ng Pagpapabuti |
| -------- | --------- | -------- | ----------------- |
| Mangolekta ng calibration data | Nakakuha ng hindi bababa sa 3 calibration sample | Nakakuha ng hindi bababa sa 2 calibration sample | Nakakuha ng hindi bababa sa 1 calibration sample |
| Gumawa ng calibrated na pagbasa | Matagumpay na nakagawa ng calibration graph at nakakuha ng pagbasa mula sa sensor, at na-convert ito sa gravimetric soil moisture content | Matagumpay na nakagawa ng calibration graph | Hindi nakagawa ng graph |

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.