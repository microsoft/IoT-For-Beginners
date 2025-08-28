<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-27T21:36:17+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "tl"
}
-->
# Gumawa ng Mas Mabisang Sistema ng Pagdidilig

## Mga Instruksyon

Tinalakay sa araling ito kung paano kontrolin ang isang relay gamit ang datos mula sa sensor, at ang relay na ito ay maaaring magkontrol ng bomba para sa isang sistema ng irigasyon. Para sa isang tiyak na dami ng lupa, ang pagpapatakbo ng bomba sa loob ng nakatakdang oras ay dapat palaging may parehong epekto sa antas ng kahalumigmigan ng lupa. Nangangahulugan ito na maaari mong matantya kung ilang segundo ng irigasyon ang tumutugma sa isang partikular na pagbaba sa pagbasa ng kahalumigmigan ng lupa. Gamit ang datos na ito, maaari kang bumuo ng mas kontroladong sistema ng irigasyon.

Sa gawaing ito, kakalkulahin mo kung gaano katagal dapat tumakbo ang bomba para makamit ang nais na pagtaas sa kahalumigmigan ng lupa.

> ⚠️ Kung gumagamit ka ng virtual na IoT hardware, maaari mong sundan ang prosesong ito, ngunit i-simulate ang mga resulta sa pamamagitan ng manu-manong pagtaas ng pagbasa ng kahalumigmigan ng lupa ng isang tiyak na halaga bawat segundo na naka-on ang relay.

1. Magsimula sa tuyong lupa. Sukatin ang kahalumigmigan ng lupa.

1. Magdagdag ng tiyak na dami ng tubig, alinman sa pamamagitan ng pagpapatakbo ng bomba sa loob ng 1 segundo o sa pamamagitan ng pagbuhos ng tiyak na dami ng tubig.

    > Ang bomba ay dapat palaging tumakbo sa pare-parehong bilis, kaya bawat segundo na tumatakbo ang bomba, dapat itong magbigay ng parehong dami ng tubig.

1. Maghintay hanggang maging stable ang antas ng kahalumigmigan ng lupa at kumuha ng pagbasa.

1. Ulitin ito nang maraming beses at gumawa ng talahanayan ng mga resulta. Ang halimbawa ng talahanayan ay nasa ibaba.

    | Kabuuang Oras ng Bomba | Kahalumigmigan ng Lupa | Pagbaba |
    | --- | --: | -: |
    | Tuyong Lupa | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Kalkulahin ang karaniwang pagtaas sa kahalumigmigan ng lupa bawat segundo ng tubig. Sa halimbawa sa itaas, bawat segundo ng tubig ay nagdudulot ng pagbaba sa pagbasa ng average na 20.3.

1. Gamitin ang datos na ito upang mapabuti ang kahusayan ng iyong server code, sa pamamagitan ng pagpapatakbo ng bomba sa kinakailangang oras upang maabot ang nais na antas ng kahalumigmigan ng lupa.

## Rubric

| Pamantayan | Napakahusay | Katanggap-tanggap | Kailangan ng Pagbuti |
| -------- | --------- | -------- | ----------------- |
| Pagkuha ng datos ng kahalumigmigan ng lupa | Kayang kumuha ng maraming pagbasa matapos magdagdag ng tiyak na dami ng tubig | Kayang kumuha ng ilang pagbasa gamit ang tiyak na dami ng tubig | Kayang kumuha lamang ng isa o dalawang pagbasa, o hindi kayang gumamit ng tiyak na dami ng tubig |
| Pag-calibrate ng server code | Kayang kalkulahin ang karaniwang pagbaba sa pagbasa ng kahalumigmigan at i-update ang server code gamit ito | Kayang kalkulahin ang karaniwang pagbaba, ngunit hindi ma-update ang server code, o hindi tamang makalkula ang average ngunit nagagamit ang halagang ito upang ma-update nang tama ang server code | Hindi kayang kalkulahin ang average, o ma-update ang server code |

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.