<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-27T21:18:56+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "tl"
}
-->
# Gumawa ng Detector ng Kalidad ng Prutas

## Mga Instruksyon

Gumawa ng detector ng kalidad ng prutas!

Gamitin ang lahat ng natutunan mo hanggang ngayon upang makabuo ng prototype na detector ng kalidad ng prutas. Mag-trigger ng image classification batay sa lapit gamit ang isang AI model na tumatakbo sa edge, i-store ang mga resulta ng classification sa storage, at kontrolin ang isang LED batay sa pagkahinog ng prutas.

Dapat mong magawang buuin ito gamit ang code na isinulat mo sa lahat ng mga aralin hanggang ngayon.

## Rubric

| Pamantayan | Napakahusay | Katamtaman | Kailangang Pagbutihin |
| ---------- | ----------- | ---------- | --------------------- |
| I-configure ang lahat ng serbisyo | Nagawang i-set up ang IoT Hub, Azure functions application, at Azure storage | Nagawang i-set up ang IoT Hub, ngunit hindi ang Azure functions app o Azure storage | Hindi nagawang i-set up ang anumang internet IoT services |
| I-monitor ang lapit at ipadala ang data sa IoT Hub kung ang isang bagay ay mas malapit kaysa sa itinakdang distansya at i-trigger ang camera gamit ang isang command | Nagawang sukatin ang distansya at magpadala ng mensahe sa IoT Hub kapag ang isang bagay ay sapat na malapit, at magpadala ng command upang i-trigger ang camera | Nagawang sukatin ang lapit at magpadala sa IoT Hub, ngunit hindi nagawang magpadala ng command sa camera | Hindi nagawang sukatin ang distansya at magpadala ng mensahe sa IoT Hub, o mag-trigger ng command |
| Kumuha ng larawan, i-classify ito, at ipadala ang mga resulta sa IoT Hub | Nagawang kumuha ng larawan, i-classify ito gamit ang isang edge device, at ipadala ang mga resulta sa IoT Hub | Nagawang i-classify ang larawan ngunit hindi gamit ang isang edge device, o hindi nagawang ipadala ang mga resulta sa IoT Hub | Hindi nagawang i-classify ang larawan |
| I-on o i-off ang LED batay sa mga resulta ng classification gamit ang isang command na ipinadala sa isang device | Nagawang i-on ang LED gamit ang isang command kung ang prutas ay hilaw | Nagawang magpadala ng command sa device ngunit hindi makontrol ang LED | Hindi nagawang magpadala ng command upang makontrol ang LED |

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.