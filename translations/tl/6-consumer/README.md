<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5de7dc1e2ddc402d415473bb795568d4",
  "translation_date": "2025-08-27T22:55:19+00:00",
  "source_file": "6-consumer/README.md",
  "language_code": "tl"
}
-->
# Consumer IoT - gumawa ng matalinong voice assistant

Ang pagkain ay naitanim, naihatid sa planta ng pagpoproseso, nasuri para sa kalidad, naibenta sa tindahan, at ngayon ay oras na para magluto! Isa sa mga pangunahing gamit sa kusina ay ang timer. Sa simula, ang mga ito ay parang hourglass - naluto ang pagkain kapag ang lahat ng buhangin ay bumaba sa ilalim na bahagi. Pagkatapos, naging mekanikal, at kalaunan ay elektrikal.

Ang pinakabagong bersyon ay bahagi na ngayon ng ating mga smart device. Sa mga kusina sa mga tahanan sa buong mundo, maririnig mo ang mga nagluluto na sumisigaw ng "Hey Siri - mag-set ng 10 minutong timer", o "Alexa - kanselahin ang timer ng tinapay ko". Hindi mo na kailangang bumalik sa kusina para tingnan ang timer, magagawa mo ito mula sa iyong telepono, o sa pamamagitan ng pagsigaw sa buong silid.

Sa 4 na araling ito, matututo kang gumawa ng matalinong timer, gamit ang AI para kilalanin ang iyong boses, intindihin ang iyong hinihiling, at magbigay ng impormasyon tungkol sa iyong timer. Magdadagdag ka rin ng suporta para sa iba't ibang wika.

> ⚠️ Ang paggamit ng speech at microphone data ay nangangailangan ng maraming memorya, kaya madali itong umabot sa limitasyon ng mga microcontroller. Ang proyekto dito ay may mga solusyon sa mga isyung ito, ngunit tandaan na ang mga Wio Terminal labs ay mas kumplikado at maaaring mas tumagal kumpara sa ibang mga lab sa kurikulum na ito.

> 💁 Ang mga araling ito ay gagamit ng ilang cloud resources. Kung hindi mo matatapos ang lahat ng aralin sa proyektong ito, siguraduhing [linisin ang iyong proyekto](../clean-up.md).

## Mga Paksa

1. [Kilalanin ang boses gamit ang IoT device](./lessons/1-speech-recognition/README.md)
1. [Unawain ang wika](./lessons/2-language-understanding/README.md)
1. [Mag-set ng timer at magbigay ng feedback na binibigkas](./lessons/3-spoken-feedback/README.md)
1. [Suportahan ang iba't ibang wika](./lessons/4-multiple-language-support/README.md)

## Mga Kredito

Ang lahat ng aralin ay isinulat nang may ♥️ ni [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa orihinal nitong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.