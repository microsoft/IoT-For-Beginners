<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-28T01:16:54+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "tl"
}
-->
# I-calibrate ang iyong sensor

## Mga Instruksyon

Sa araling ito, nakakuha ka ng mga pagbabasa mula sa soil moisture sensor, na sinusukat bilang mga halaga mula 0-1023. Upang ma-convert ang mga ito sa aktwal na pagbabasa ng soil moisture, kailangan mong i-calibrate ang iyong sensor. Magagawa mo ito sa pamamagitan ng pagkuha ng mga pagbabasa mula sa mga sample ng lupa, pagkatapos ay kalkulahin ang gravimetric soil moisture content mula sa mga sample na ito.

Kailangan mong ulitin ang mga hakbang na ito nang maraming beses upang makuha ang mga kinakailangang pagbabasa, gamit ang iba't ibang antas ng pagkabasa ng lupa sa bawat pagkakataon.

1. Kumuha ng pagbabasa ng soil moisture gamit ang soil moisture sensor. Isulat ang pagbabasa na ito.

1. Kumuha ng sample ng lupa, at timbangin ito. Isulat ang timbang na ito.

1. Patuyuin ang lupa - ang isang mainit na oven sa 110°C (230°F) sa loob ng ilang oras ang pinakamainam na paraan. Maaari mo rin itong gawin sa sikat ng araw, o ilagay ito sa isang mainit at tuyong lugar hanggang sa ganap na matuyo ang lupa. Dapat itong maging pulbos at maluwag.

    > 💁 Sa isang laboratoryo, para sa pinakatumpak na resulta, patuyuin ito sa oven sa loob ng 48-72 oras. Kung may mga drying oven sa inyong paaralan, tingnan kung maaari mong gamitin ang mga ito para sa mas mahabang oras ng pagpapatuyo. Mas matagal, mas tuyo ang sample at mas tumpak ang resulta.

1. Timbangin muli ang lupa.

    > 🔥 Kung pinatuyo mo ito sa oven, siguraduhing lumamig muna ito!

Ang gravimetric soil moisture ay kinakalkula bilang:

![soil moisture % ay timbang ng basa minus timbang ng tuyo, hinati sa timbang ng tuyo, times 100](../../../../../translated_images/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.tl.png)

* W - ang timbang ng basang lupa  
* W - ang timbang ng tuyong lupa  

Halimbawa, sabihin nating mayroon kang sample ng lupa na may timbang na 212g kapag basa, at 197g kapag tuyo.

![Ang kalkulasyon na may sagot](../../../../../translated_images/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.tl.png)

* W = 212g  
* W = 197g  
* 212 - 197 = 15  
* 15 / 197 = 0.076  
* 0.076 * 100 = 7.6%  

Sa halimbawang ito, ang lupa ay may gravimetric soil moisture na 7.6%.

Kapag mayroon ka nang mga pagbabasa para sa hindi bababa sa 3 sample, gumawa ng graph ng soil moisture % laban sa pagbabasa ng soil moisture sensor at magdagdag ng linya na pinakamalapit sa mga puntos. Magagamit mo ito upang kalkulahin ang gravimetric soil moisture content para sa isang partikular na pagbabasa ng sensor sa pamamagitan ng pagbabasa ng halaga mula sa linya.

## Rubric

| Pamantayan | Napakahusay | Katanggap-tanggap | Kailangan ng Pagpapabuti |
| ---------- | ----------- | ----------------- | ------------------------ |
| Mangolekta ng calibration data | Nakakuha ng hindi bababa sa 3 calibration sample | Nakakuha ng hindi bababa sa 2 calibration sample | Nakakuha ng hindi bababa sa 1 calibration sample |
| Gumawa ng calibrated na pagbabasa | Matagumpay na nag-plot ng calibration graph at gumawa ng pagbabasa mula sa sensor, at na-convert ito sa gravimetric soil moisture content | Matagumpay na nag-plot ng calibration graph | Hindi nagawang mag-plot ng graph |

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa orihinal nitong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.