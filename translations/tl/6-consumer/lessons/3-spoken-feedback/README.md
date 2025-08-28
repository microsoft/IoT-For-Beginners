<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b73fe10ec6b580fba2affb6f6e0a5c4d",
  "translation_date": "2025-08-27T23:15:37+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/README.md",
  "language_code": "tl"
}
-->
# Mag-set ng Timer at Magbigay ng Pasalitang Feedback

![Isang sketchnote na buod ng araling ito](../../../../../translated_images/lesson-23.f38483e1d4df4828990d3f02d60e46c978b075d384ae7cb4f7bab738e107c850.tl.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

## Pre-lecture Quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/45)

## Panimula

Ang mga smart assistant ay hindi lang para sa isang direksyon ng komunikasyon. Kinakausap mo sila, at sumasagot sila:

"Alexa, mag-set ng 3 minutong timer"

"Ok, ang iyong timer ay na-set na para sa 3 minuto"

Sa huling 2 aralin, natutunan mo kung paano kumuha ng speech at gawing text, pagkatapos ay kunin ang kahilingan para mag-set ng timer mula sa text na iyon. Sa araling ito, matutunan mo kung paano mag-set ng timer sa IoT device, tumugon sa user gamit ang pasalitang kumpirmasyon ng kanilang timer, at alertuhan sila kapag natapos na ang kanilang timer.

Sa araling ito, tatalakayin natin ang:

* [Text to speech](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Mag-set ng timer](../../../../../6-consumer/lessons/3-spoken-feedback)
* [I-convert ang text sa speech](../../../../../6-consumer/lessons/3-spoken-feedback)

## Text to Speech

Ang Text to Speech, tulad ng ipinapahiwatig ng pangalan, ay ang proseso ng pag-convert ng text sa audio na naglalaman ng mga salitang binibigkas. Ang pangunahing prinsipyo nito ay hatiin ang mga salita sa text sa kanilang mga tunog (kilala bilang phonemes), at pagsama-samahin ang audio para sa mga tunog na iyon, gamit ang pre-recorded audio o audio na ginawa ng mga AI model.

![Ang tatlong yugto ng karaniwang text to speech systems](../../../../../translated_images/tts-overview.193843cf3f5ee09f8b3371a9fdaeb0f116698a07ca69daaa77158da4800e5453.tl.png)

Karaniwang may 3 yugto ang mga text to speech systems:

* Text analysis  
* Linguistic analysis  
* Wave-form generation  

### Text Analysis

Ang Text analysis ay ang proseso ng pagkuha ng text na ibinigay at pag-convert nito sa mga salitang maaaring gamitin upang makabuo ng speech. Halimbawa, kung iko-convert mo ang "Hello world", walang kailangang text analysis, ang dalawang salita ay maaaring direktang gawing speech. Ngunit kung "1234" ang text, maaaring kailangang i-convert ito sa "One thousand, two hundred thirty four" o "One, two, three, four" depende sa konteksto. Para sa "I have 1234 apples", magiging "One thousand, two hundred thirty four", ngunit para sa "The child counted 1234", magiging "One, two, three, four".

Nagkakaiba ang mga salitang nabubuo hindi lang sa wika, kundi pati sa lokasyon ng wikang iyon. Halimbawa, sa American English, ang 120 ay "One hundred twenty", habang sa British English ito ay "One hundred and twenty", na may paggamit ng "and" pagkatapos ng hundreds.

✅ Ilang halimbawa na nangangailangan ng text analysis ay ang "in" bilang pinaikling anyo ng inch, at "st" bilang pinaikling anyo ng saint at street. Makakaisip ka ba ng iba pang halimbawa sa iyong wika ng mga salitang hindi malinaw ang kahulugan kung walang konteksto?

Kapag naitakda na ang mga salita, ipapadala ang mga ito para sa linguistic analysis.

### Linguistic Analysis

Ang Linguistic analysis ay hinahati ang mga salita sa phonemes. Ang mga phonemes ay batay hindi lang sa mga letra, kundi pati sa ibang letra sa salita. Halimbawa, sa Ingles, ang tunog ng 'a' sa 'car' at 'care' ay magkaiba. Ang wikang Ingles ay may 44 na phonemes para sa 26 na letra sa alpabeto, ang ilan ay ginagamit ng iba't ibang letra, tulad ng parehong phoneme na ginagamit sa simula ng 'circle' at 'serpent'.

✅ Mag-research: Ano ang mga phonemes sa iyong wika?

Kapag ang mga salita ay na-convert na sa phonemes, kailangan ng karagdagang datos para sa intonasyon, ina-adjust ang tono o tagal depende sa konteksto. Halimbawa, sa Ingles, ang pagtaas ng pitch ay maaaring gawing tanong ang isang pangungusap, kung saan ang huling salita ay may mas mataas na tono.

Halimbawa - ang pangungusap na "You have an apple" ay isang pahayag na nagsasabing may apple ka. Kung tataas ang pitch sa dulo, magiging tanong ito: "You have an apple?", nagtatanong kung may apple ka. Kailangang gamitin ng linguistic analysis ang question mark sa dulo upang magdesisyon na itaas ang pitch.

Kapag ang mga phonemes ay nabuo na, ipapadala ang mga ito para sa wave-form generation upang makabuo ng audio output.

### Wave-form Generation

Ang mga unang electronic text to speech systems ay gumamit ng iisang audio recording para sa bawat phoneme, na nagresulta sa napaka-monotonous at robotic na tunog. Ang linguistic analysis ay magpo-produce ng phonemes, kukunin ang mga ito mula sa isang database ng tunog, at pagsasama-samahin upang makabuo ng audio.

✅ Mag-research: Maghanap ng mga audio recording mula sa mga unang speech synthesis systems. I-kumpara ito sa modernong speech synthesis, tulad ng ginagamit sa mga smart assistant.

Ang mas modernong wave-form generation ay gumagamit ng ML models na binuo gamit ang deep learning (napakalaking neural networks na gumagana tulad ng neurons sa utak) upang makabuo ng mas natural na tunog na halos hindi maipagkaiba sa tao.

> 💁 Ang ilan sa mga ML models na ito ay maaaring i-retrain gamit ang transfer learning upang magtunog tulad ng totoong tao. Dahil dito, ang paggamit ng boses bilang security system, na sinusubukan ng ilang bangko, ay hindi na magandang ideya dahil ang sinumang may recording ng ilang minuto ng iyong boses ay maaaring magpanggap bilang ikaw.

Ang mga malalaking ML models na ito ay sinasanay upang pagsamahin ang lahat ng tatlong hakbang sa end-to-end speech synthesizers.

## Mag-set ng Timer

Upang mag-set ng timer, kailangang tawagan ng iyong IoT device ang REST endpoint na ginawa mo gamit ang serverless code, pagkatapos ay gamitin ang bilang ng segundo upang mag-set ng timer.

### Gawain - Tawagan ang serverless function upang makuha ang oras ng timer

Sundin ang kaukulang gabay upang tawagan ang REST endpoint mula sa iyong IoT device at mag-set ng timer para sa kinakailangang oras:

* [Arduino - Wio Terminal](wio-terminal-set-timer.md)  
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-set-timer.md)  

## I-convert ang Text sa Speech

Ang parehong speech service na ginamit mo upang i-convert ang speech sa text ay maaaring gamitin upang i-convert ang text pabalik sa speech, at ito ay maaaring patugtugin sa pamamagitan ng speaker ng iyong IoT device. Ang text na iko-convert ay ipinapadala sa speech service, kasama ang uri ng audio na kinakailangan (tulad ng sample rate), at ang binary data na naglalaman ng audio ay ibinabalik.

Kapag ipinadala mo ang request na ito, gagamit ka ng *Speech Synthesis Markup Language* (SSML), isang XML-based markup language para sa speech synthesis applications. Tinutukoy nito hindi lang ang text na iko-convert, kundi pati ang wika ng text, ang boses na gagamitin, at maaari ring gamitin upang tukuyin ang bilis, volume, at pitch para sa ilan o lahat ng mga salita sa text.

Halimbawa, ang SSML na ito ay tumutukoy sa isang request upang i-convert ang text na "Your 3 minute 5 second time has been set" sa speech gamit ang British English voice na tinatawag na `en-GB-MiaNeural`

```xml
<speak version='1.0' xml:lang='en-GB'>
    <voice xml:lang='en-GB' name='en-GB-MiaNeural'>
        Your 3 minute 5 second time has been set
    </voice>
</speak>
```

> 💁 Karamihan sa mga text to speech systems ay may iba't ibang boses para sa iba't ibang wika, na may kaukulang accent tulad ng British English voice na may English accent at New Zealand English voice na may New Zealand accent.

### Gawain - I-convert ang text sa speech

Sundin ang kaukulang gabay upang i-convert ang text sa speech gamit ang iyong IoT device:

* [Arduino - Wio Terminal](wio-terminal-text-to-speech.md)  
* [Single-board computer - Raspberry Pi](pi-text-to-speech.md)  
* [Single-board computer - Virtual device](virtual-device-text-to-speech.md)  

---

## 🚀 Hamon

Ang SSML ay may mga paraan upang baguhin kung paano binibigkas ang mga salita, tulad ng pagdaragdag ng diin sa ilang salita, pagdaragdag ng mga pause, o pagbabago ng pitch. Subukan ang ilan sa mga ito, magpadala ng iba't ibang SSML mula sa iyong IoT device at ikumpara ang output. Maaari kang magbasa pa tungkol sa SSML, kabilang ang kung paano baguhin ang paraan ng pagbigkas ng mga salita sa [Speech Synthesis Markup Language (SSML) Version 1.1 specification mula sa World Wide Web consortium](https://www.w3.org/TR/speech-synthesis11/).

## Post-lecture Quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/46)

## Review at Pag-aaral sa Sarili

* Magbasa pa tungkol sa speech synthesis sa [speech synthesis page sa Wikipedia](https://wikipedia.org/wiki/Speech_synthesis)  
* Magbasa pa tungkol sa mga paraan kung paano ginagamit ng mga kriminal ang speech synthesis upang magnakaw sa [fake voices 'help cyber crooks steal cash' story sa BBC news](https://www.bbc.com/news/technology-48908736)  
* Alamin pa ang tungkol sa mga panganib sa mga voice actor mula sa synthesized na bersyon ng kanilang mga boses sa [this TikTok lawsuit is highlighting how AI is screwing over voice actors article sa Vice](https://www.vice.com/en/article/z3xqwj/this-tiktok-lawsuit-is-highlighting-how-ai-is-screwing-over-voice-actors)  

## Takdang Aralin

[Cancel the timer](assignment.md)  

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.