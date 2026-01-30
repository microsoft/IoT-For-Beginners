# Sukatin ang Halumigmig ng Lupa - Raspberry Pi

Sa bahaging ito ng aralin, magdadagdag ka ng capacitive soil moisture sensor sa iyong Raspberry Pi, at babasahin ang mga halaga mula rito.

## Kagamitan

Kailangan ng Raspberry Pi ng isang capacitive soil moisture sensor.

Ang sensor na gagamitin mo ay isang [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), na sumusukat sa halumigmig ng lupa sa pamamagitan ng pag-detect ng capacitance ng lupa, isang katangian na nagbabago habang nagbabago ang halumigmig ng lupa. Habang tumataas ang halumigmig ng lupa, bumababa ang boltahe.

Ito ay isang analog sensor, kaya gumagamit ito ng analog pin, at ang 10-bit ADC sa Grove Base Hat sa Pi upang i-convert ang boltahe sa isang digital na signal mula 1-1,023. Ang signal na ito ay ipinapadala sa pamamagitan ng I

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.