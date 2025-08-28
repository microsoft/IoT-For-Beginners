<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "34010c663d96d5f419eda6ac2366a78d",
  "translation_date": "2025-08-27T22:11:00+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/assignment.md",
  "language_code": "tl"
}
-->
# Gumawa ng bagong IoT device

## Mga Instruksyon

Sa nakaraang 6 na aralin, natutunan mo ang tungkol sa digital na agrikultura at kung paano gamitin ang mga IoT device upang mangolekta ng datos para hulaan ang paglago ng halaman, at awtomatikong magdilig base sa mga pagbasa ng moisture sa lupa.

Gamitin ang iyong mga natutunan upang gumawa ng bagong IoT device gamit ang isang sensor at actuator na iyong napili. Magpadala ng telemetry sa isang IoT Hub, at gamitin ito upang kontrolin ang isang actuator gamit ang serverless na code. Maaari mong gamitin ang sensor at actuator na ginamit mo na sa proyektong ito o sa nakaraang proyekto, o kung mayroon kang ibang hardware, subukan ang bago.

## Rubric

| Pamantayan | Napakahusay | Katanggap-tanggap | Kailangan ng Pagpapabuti |
| ---------- | ----------- | ----------------- | ------------------------ |
| Mag-code ng IoT device na gumagamit ng sensor at actuator | Nakapag-code ng IoT device na gumagana gamit ang sensor at actuator | Nakapag-code ng IoT device na gumagana gamit ang sensor o actuator | Hindi nakapag-code ng IoT device na gumagamit ng sensor o actuator |
| Ikonekta ang IoT device sa IoT Hub | Nakapag-deploy ng IoT Hub at nakapagpadala ng telemetry dito, at nakatanggap ng mga utos mula rito | Nakapag-deploy ng IoT Hub at nakapagpadala ng telemetry o nakatanggap ng mga utos | Hindi nakapag-deploy ng IoT Hub at nakipag-ugnayan dito mula sa isang IoT device |
| Kontrolin ang actuator gamit ang serverless na code | Nakapag-deploy ng Azure Function upang kontrolin ang device na na-trigger ng mga telemetry event | Nakapag-deploy ng Azure Function na na-trigger ng mga telemetry event ngunit hindi nakontrol ang actuator | Hindi nakapag-deploy ng Azure Function |

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.