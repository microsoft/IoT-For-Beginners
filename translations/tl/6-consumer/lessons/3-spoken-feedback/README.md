<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b73fe10ec6b580fba2affb6f6e0a5c4d",
  "translation_date": "2025-08-27T23:11:00+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/README.md",
  "language_code": "tl"
}
-->
# Mag-set ng Timer at Magbigay ng Pasalitang Feedback

![Isang sketchnote na buod ng araling ito](../../../../../translated_images/tl/lesson-23.f38483e1d4df4828990d3f02d60e46c978b075d384ae7cb4f7bab738e107c850.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

## Pre-lecture Quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/45)

## Panimula

Ang mga smart assistant ay hindi lamang para sa isang direksyon ng komunikasyon. Kinakausap mo sila, at sumasagot sila:

"Alexa, mag-set ng 3 minutong timer"

"Ok, ang iyong timer ay na-set para sa 3 minuto"

Sa huling 2 aralin, natutunan mo kung paano kumuha ng boses at gawing teksto, pagkatapos ay kunin ang kahilingan para sa timer mula sa tekstong iyon. Sa araling ito, matutunan mo kung paano mag-set ng timer sa IoT device, tumugon sa gumagamit gamit ang pasalitang kumpirmasyon ng kanilang timer, at alertuhan sila kapag natapos na ang kanilang timer.

Sa araling ito, tatalakayin natin ang:

* [Teksto sa Boses](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Mag-set ng Timer](../../../../../6-consumer/lessons/3-spoken-feedback)
* [I-convert ang Teksto sa Boses](../../../../../6-consumer/lessons/3-spoken-feedback)

## Teksto sa Boses

Ang Teksto sa Boses, tulad ng ipinahihiwatig ng pangalan, ay ang proseso ng pag-convert ng teksto sa audio na naglalaman ng mga salitang binibigkas. Ang pangunahing prinsipyo ay hatiin ang mga salita sa teksto sa kanilang mga tunog (kilala bilang phonemes), at pagsamahin ang audio para sa mga tunog na iyon, gamit ang pre-recorded na audio o audio na ginawa ng mga AI model.

![Ang tatlong yugto ng karaniwang mga sistema ng Teksto sa Boses](../../../../../translated_images/tl/tts-overview.193843cf3f5ee09f.webp)

Karaniwang may 3 yugto ang mga sistema ng Teksto sa Boses:

* Pagsusuri ng Teksto
* Pagsusuri ng Lingguwistika
* Pagbuo ng Wave-form

### Pagsusuri ng Teksto

Ang pagsusuri ng teksto ay kinabibilangan ng pagkuha ng ibinigay na teksto at pag-convert nito sa mga salitang maaaring gamitin upang makabuo ng boses. Halimbawa, kung iko-convert mo ang "Hello world", walang kinakailangang pagsusuri ng teksto, ang dalawang salita ay maaaring direktang gawing boses. Kung mayroon kang "1234" gayunpaman, maaaring kailanganin itong i-convert sa mga salitang "Isang libo, dalawang daan tatlumpu't apat" o "Isa, dalawa, tatlo, apat" depende sa konteksto. Para sa "Mayroon akong 1234 mansanas", magiging "Isang libo, dalawang daan tatlumpu't apat", ngunit para sa "Binilang ng bata ang 1234" magiging "Isa, dalawa, tatlo, apat".

Ang mga salitang nalikha ay nag-iiba hindi lamang sa wika, kundi pati na rin sa lokasyon ng wika. Halimbawa, sa American English, ang 120 ay "One hundred twenty", sa British English ito ay "One hundred and twenty", na may paggamit ng "and" pagkatapos ng daan.

✅ Ilang iba pang halimbawa na nangangailangan ng pagsusuri ng teksto ay kinabibilangan ng "in" bilang maikling anyo ng inch, at "st" bilang maikling anyo ng saint at street. Makakaisip ka ba ng iba pang halimbawa sa iyong wika ng mga salitang hindi malinaw kung walang konteksto?

Kapag ang mga salita ay naitakda na, ipapadala ang mga ito para sa pagsusuri ng lingguwistika.

### Pagsusuri ng Lingguwistika

Ang pagsusuri ng lingguwistika ay hinahati ang mga salita sa phonemes. Ang mga phonemes ay batay hindi lamang sa mga letra na ginamit, kundi pati na rin sa iba pang mga letra sa salita. Halimbawa, sa Ingles ang tunog na 'a' sa 'car' at 'care' ay magkaiba. Ang wikang Ingles ay may 44 na iba't ibang phonemes para sa 26 na letra sa alpabeto, ang ilan ay ginagamit ng iba't ibang letra, tulad ng parehong phoneme na ginagamit sa simula ng 'circle' at 'serpent'.

✅ Mag-research: Ano ang mga phoneme sa iyong wika?

Kapag ang mga salita ay na-convert na sa phonemes, ang mga phonemes na ito ay nangangailangan ng karagdagang datos upang suportahan ang intonasyon, ina-adjust ang tono o tagal depende sa konteksto. Isang halimbawa ay sa Ingles, ang pagtaas ng pitch ay maaaring gamitin upang gawing tanong ang isang pangungusap, kung saan ang pagtaas ng pitch sa huling salita ay nagpapahiwatig ng tanong.

Halimbawa - ang pangungusap na "You have an apple" ay isang pahayag na nagsasabing mayroon kang mansanas. Kung ang pitch ay tataas sa dulo, tumataas para sa salitang apple, ito ay nagiging tanong na "You have an apple?", nagtatanong kung mayroon kang mansanas. Ang pagsusuri ng lingguwistika ay kailangang gamitin ang tandang pananong sa dulo upang magdesisyon na itaas ang pitch.

Kapag ang mga phonemes ay nalikha na, maaari na silang ipadala para sa pagbuo ng wave-form upang makabuo ng audio output.

### Pagbuo ng Wave-form

Ang mga unang electronic text to speech system ay gumamit ng iisang audio recording para sa bawat phoneme, na nagresulta sa napaka-monotonous, robotic na tunog ng mga boses. Ang pagsusuri ng lingguwistika ay gagawa ng mga phoneme, ang mga ito ay kukunin mula sa isang database ng mga tunog at pagsasamahin upang makabuo ng audio.

✅ Mag-research: Maghanap ng mga audio recording mula sa mga unang sistema ng speech synthesis. Ihambing ito sa modernong speech synthesis, tulad ng ginagamit sa mga smart assistant.

Ang mas modernong pagbuo ng wave-form ay gumagamit ng mga ML model na binuo gamit ang deep learning (napakalaking neural networks na gumagana sa katulad na paraan sa mga neuron sa utak) upang makabuo ng mas natural na tunog ng boses na maaaring hindi maipagkaiba sa tao.

> 💁 Ang ilan sa mga ML model na ito ay maaaring ma-retrain gamit ang transfer learning upang tunog tulad ng totoong tao. Nangangahulugan ito na ang paggamit ng boses bilang isang sistema ng seguridad, na sinusubukan ng mga bangko, ay hindi na magandang ideya dahil ang sinuman na may recording ng ilang minuto ng iyong boses ay maaaring magpanggap bilang ikaw.

Ang mga malalaking ML model na ito ay sinasanay upang pagsamahin ang lahat ng tatlong hakbang sa end-to-end na speech synthesizers.

## Mag-set ng Timer

Upang mag-set ng timer, kailangang tawagan ng iyong IoT device ang REST endpoint na ginawa mo gamit ang serverless code, pagkatapos ay gamitin ang bilang ng mga segundo upang mag-set ng timer.

### Gawain - tawagan ang serverless function upang makuha ang oras ng timer

Sundin ang kaukulang gabay upang tawagan ang REST endpoint mula sa iyong IoT device at mag-set ng timer para sa kinakailangang oras:

* [Arduino - Wio Terminal](wio-terminal-set-timer.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-set-timer.md)

## I-convert ang Teksto sa Boses

Ang parehong speech service na ginamit mo upang i-convert ang boses sa teksto ay maaaring gamitin upang i-convert ang teksto pabalik sa boses, at ito ay maaaring patugtugin sa pamamagitan ng speaker sa iyong IoT device. Ang teksto na iko-convert ay ipinapadala sa speech service, kasama ang uri ng audio na kinakailangan (tulad ng sample rate), at ang binary data na naglalaman ng audio ay ibinabalik.

Kapag ipinadala mo ang kahilingang ito, ginagamit mo ang *Speech Synthesis Markup Language* (SSML), isang XML-based na markup language para sa mga speech synthesis application. Ito ay nagde-define hindi lamang ng teksto na iko-convert, kundi pati na rin ang wika ng teksto, ang boses na gagamitin, at maaari ring gamitin upang i-define ang bilis, volume, at pitch para sa ilan o lahat ng mga salita sa teksto.

Halimbawa, ang SSML na ito ay nagde-define ng kahilingan upang i-convert ang teksto na "Your 3 minute 5 second time has been set" sa boses gamit ang British English voice na tinatawag na `en-GB-MiaNeural`

```xml
<speak version='1.0' xml:lang='en-GB'>
    <voice xml:lang='en-GB' name='en-GB-MiaNeural'>
        Your 3 minute 5 second time has been set
    </voice>
</speak>
```

> 💁 Karamihan sa mga text to speech system ay may maraming boses para sa iba't ibang wika, na may kaukulang accent tulad ng British English voice na may English accent at New Zealand English voice na may New Zealand accent.

### Gawain - i-convert ang teksto sa boses

Gawin ang kaukulang gabay upang i-convert ang teksto sa boses gamit ang iyong IoT device:

* [Arduino - Wio Terminal](wio-terminal-text-to-speech.md)
* [Single-board computer - Raspberry Pi](pi-text-to-speech.md)
* [Single-board computer - Virtual device](virtual-device-text-to-speech.md)

---

## 🚀 Hamon

Ang SSML ay may mga paraan upang baguhin kung paano binibigkas ang mga salita, tulad ng pagdaragdag ng diin sa ilang mga salita, pagdaragdag ng mga pause, o pagbabago ng pitch. Subukan ang ilan sa mga ito, magpadala ng iba't ibang SSML mula sa iyong IoT device at ihambing ang output. Maaari kang magbasa pa tungkol sa SSML, kabilang kung paano baguhin ang paraan ng pagbigkas ng mga salita sa [Speech Synthesis Markup Language (SSML) Version 1.1 specification mula sa World Wide Web consortium](https://www.w3.org/TR/speech-synthesis11/).

## Post-lecture Quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/46)

## Review at Pag-aaral sa Sarili

* Magbasa pa tungkol sa speech synthesis sa [speech synthesis page sa Wikipedia](https://wikipedia.org/wiki/Speech_synthesis)
* Magbasa pa tungkol sa mga paraan kung paano ginagamit ng mga kriminal ang speech synthesis upang magnakaw sa [fake voices 'help cyber crooks steal cash' story sa BBC news](https://www.bbc.com/news/technology-48908736)
* Alamin pa ang tungkol sa mga panganib sa mga voice actor mula sa synthesized na bersyon ng kanilang mga boses sa [artikulong ito sa Vice tungkol sa TikTok lawsuit at AI](https://www.vice.com/en/article/z3xqwj/this-tiktok-lawsuit-is-highlighting-how-ai-is-screwing-over-voice-actors)

## Takdang Aralin

[Ikansela ang timer](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.