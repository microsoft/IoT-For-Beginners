<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5de7dc1e2ddc402d415473bb795568d4",
  "translation_date": "2025-08-27T23:07:50+00:00",
  "source_file": "6-consumer/README.md",
  "language_code": "tl"
}
-->
# Consumer IoT - gumawa ng matalinong voice assistant

Ang pagkain ay itinanim, dinala sa planta ng pagpoproseso, sinuri para sa kalidad, ibinenta sa tindahan, at ngayon ay oras na para magluto! Isa sa mga pangunahing gamit sa kusina ay ang timer. Sa simula, ito ay parang hourglass - ang pagkain mo ay luto na kapag ang lahat ng buhangin ay bumaba na sa ilalim. Pagkatapos, naging mekanikal ito, at kalaunan ay naging de-kuryente.

Ang pinakabagong bersyon nito ay bahagi na ngayon ng ating mga smart device. Sa mga kusina sa buong mundo, maririnig mo ang mga nagluluto na sumisigaw ng "Hey Siri - mag-set ng 10 minutong timer", o "Alexa - kanselahin ang bread timer ko". Hindi mo na kailangang bumalik sa kusina para tingnan ang timer, magagawa mo na ito mula sa iyong telepono, o sa pamamagitan ng pagsigaw mula sa kabilang kwarto.

Sa 4 na araling ito, matututuhan mong gumawa ng matalinong timer, gamit ang AI upang makilala ang iyong boses, maunawaan ang iyong hinihiling, at magbigay ng impormasyon tungkol sa iyong timer. Magdadagdag ka rin ng suporta para sa iba't ibang wika.

> ⚠️ Ang paggamit ng speech at microphone data ay nangangailangan ng maraming memorya, kaya madaling maabot ang mga limitasyon sa microcontrollers. Ang proyektong ito ay may mga solusyon para sa mga isyung ito, ngunit tandaan na ang mga Wio Terminal labs ay mas kumplikado at maaaring mas tumagal kumpara sa ibang mga aralin sa kurikulum na ito.

> 💁 Ang mga araling ito ay gagamit ng ilang cloud resources. Kung hindi mo matatapos ang lahat ng aralin sa proyektong ito, siguraduhing [linisin ang iyong proyekto](../clean-up.md).

## Mga Paksa

1. [Kilalanin ang boses gamit ang isang IoT device](./lessons/1-speech-recognition/README.md)
1. [Unawain ang wika](./lessons/2-language-understanding/README.md)
1. [Mag-set ng timer at magbigay ng spoken feedback](./lessons/3-spoken-feedback/README.md)
1. [Suportahan ang iba't ibang wika](./lessons/4-multiple-language-support/README.md)

## Mga Kredito

Ang lahat ng aralin ay isinulat nang may ♥️ ni [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.