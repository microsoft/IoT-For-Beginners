<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6d6aa1be033625d201a190fc9c5cbfb4",
  "translation_date": "2025-08-27T21:16:13+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/README.md",
  "language_code": "sw"
}
-->
# Kutambua Sauti kwa Kifaa cha IoT

![Muhtasari wa somo hili kwa sketchnote](../../../../../translated_images/lesson-21.e34de51354d6606fb5ee08d8c89d0222eea0a2a7aaf744a8805ae847c4f69dc4.sw.jpg)

> Sketchnote na [Nitya Narasimhan](https://github.com/nitya). Bofya picha kwa toleo kubwa zaidi.

Video hii inatoa muhtasari wa huduma ya sauti ya Azure, mada itakayojadiliwa katika somo hili:

[![Jinsi ya kuanza kutumia rasilimali yako ya Cognitive Services Speech kutoka kwenye kituo cha YouTube cha Microsoft Azure](https://img.youtube.com/vi/iW0Fw0l3mrA/0.jpg)](https://www.youtube.com/watch?v=iW0Fw0l3mrA)

> 🎥 Bofya picha hapo juu kutazama video

## Jaribio la Kabla ya Somo

[Jaribio la kabla ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/41)

## Utangulizi

'Alexa, weka kengele ya dakika 12'

'Alexa, hali ya kengele'

'Alexa, weka kengele ya dakika 8 inayoitwa broccoli ya mvuke'

Vifaa vya kisasa vinazidi kuwa sehemu ya maisha yetu. Sio tu kama spika mahiri kama HomePods, Echos na Google Homes, bali pia vimejumuishwa kwenye simu zetu, saa, hata taa na thermostats.

> 💁 Nina angalau vifaa 19 nyumbani kwangu vyenye wasaidizi wa sauti, na hivyo ni vile tu ninavyovijua!

Udhibiti wa sauti huongeza upatikanaji kwa kuruhusu watu wenye ulemavu wa mwili kuingiliana na vifaa. Iwe ni ulemavu wa kudumu kama kuzaliwa bila mikono, ulemavu wa muda kama mkono uliovunjika, au mikono yako ikiwa imejaa ununuzi au watoto wadogo, uwezo wa kudhibiti nyumba zetu kwa sauti badala ya mikono hufungua ulimwengu wa upatikanaji. Kusema 'Hey Siri, funga mlango wa karakana yangu' huku ukihangaika na mtoto mchanga na mtoto mdogo asiye na nidhamu kunaweza kuwa mabadiliko madogo lakini yenye manufaa katika maisha.

Moja ya matumizi maarufu ya wasaidizi wa sauti ni kuweka kengele, hasa kengele za jikoni. Uwezo wa kuweka kengele nyingi kwa kutumia sauti yako ni msaada mkubwa jikoni - hakuna haja ya kusimamisha kukanda unga, kuchochea supu, au kusafisha mikono yenye kujaza dumplings ili kutumia kengele ya kimwili.

Katika somo hili utajifunza jinsi ya kujenga utambuzi wa sauti kwenye vifaa vya IoT. Utajifunza kuhusu maikrofoni kama vihisi, jinsi ya kunasa sauti kutoka kwa maikrofoni iliyounganishwa na kifaa cha IoT, na jinsi ya kutumia AI kubadilisha kile kinachosikika kuwa maandishi. Katika mradi huu, utajenga kengele mahiri ya jikoni, inayoweza kuweka kengele kwa kutumia sauti yako katika lugha nyingi.

Katika somo hili tutajadili:

* [Maikrofoni](../../../../../6-consumer/lessons/1-speech-recognition)
* [Kunasa sauti kutoka kwa kifaa chako cha IoT](../../../../../6-consumer/lessons/1-speech-recognition)
* [Sauti hadi maandishi](../../../../../6-consumer/lessons/1-speech-recognition)
* [Kubadilisha sauti kuwa maandishi](../../../../../6-consumer/lessons/1-speech-recognition)

## Maikrofoni

Maikrofoni ni vihisi vya analogi vinavyobadilisha mawimbi ya sauti kuwa ishara za umeme. Mitetemo ya hewa husababisha vipengele ndani ya maikrofoni kusogea kwa kiasi kidogo, na hii husababisha mabadiliko madogo katika ishara za umeme. Mabadiliko haya huimarishwa ili kutoa ishara ya umeme.

### Aina za Maikrofoni

Maikrofoni huja katika aina mbalimbali:

* **Dynamic** - Maikrofoni za dynamic zina sumaku iliyounganishwa na diaphragm inayosogea ndani ya coil ya waya, na hivyo kuzalisha mkondo wa umeme. Hii ni kinyume na spika nyingi, ambazo hutumia mkondo wa umeme kusogeza sumaku ndani ya coil ya waya, kusogeza diaphragm ili kuzalisha sauti. Hii inamaanisha spika zinaweza kutumika kama maikrofoni za dynamic, na maikrofoni za dynamic zinaweza kutumika kama spika. Katika vifaa kama intercoms ambapo mtumiaji anasikiliza au kuzungumza, lakini si vyote kwa wakati mmoja, kifaa kimoja kinaweza kufanya kazi kama spika na maikrofoni.

    Maikrofoni za dynamic hazihitaji nguvu kufanya kazi, ishara ya umeme inazalishwa moja kwa moja kutoka kwa maikrofoni.

    ![Patti Smith akiimba kwenye maikrofoni ya Shure SM58 (aina ya dynamic cardioid)](../../../../../translated_images/dynamic-mic.8babac890a2d80dfb0874b5bf37d4b851fe2aeb9da6fd72945746176978bf3bb.sw.jpg)

* **Ribbon** - Maikrofoni za ribbon zinafanana na maikrofoni za dynamic, isipokuwa zina ribbon ya chuma badala ya diaphragm. Ribbon hii husogea kwenye uwanja wa sumaku na kuzalisha mkondo wa umeme. Kama maikrofoni za dynamic, maikrofoni za ribbon hazihitaji nguvu kufanya kazi.

    ![Edmund Lowe, mwigizaji wa Marekani, akiwa amesimama kwenye maikrofoni ya redio (iliyotajwa kwa (NBC) Blue Network), akiwa ameshikilia maandishi, 1942](../../../../../translated_images/ribbon-mic.eacc8e092c7441ca.sw.jpg)

* **Condenser** - Maikrofoni za condenser zina diaphragm nyembamba ya chuma na sahani ya nyuma ya chuma iliyowekwa. Umeme hutumika kwa vyote viwili na diaphragm inapovibrate, chaji ya static kati ya sahani hubadilika na kuzalisha ishara. Maikrofoni za condenser zinahitaji nguvu kufanya kazi - inayoitwa *Phantom power*.

    ![Maikrofoni ya condenser ya diaframu ndogo ya C451B na AKG Acoustics](../../../../../translated_images/condenser-mic.6f6ed5b76ca19e0ec3fd0c544601542d4479a6cb7565db336de49fbbf69f623e.sw.jpg)

* **MEMS** - Maikrofoni za Microelectromechanical systems, au MEMS, ni maikrofoni kwenye chipu. Zina diaphragm inayohisi shinikizo iliyochongwa kwenye chipu ya silicon, na hufanya kazi sawa na maikrofoni ya condenser. Maikrofoni hizi zinaweza kuwa ndogo sana, na kuunganishwa kwenye mzunguko.

    ![Maikrofoni ya MEMS kwenye ubao wa mzunguko](../../../../../translated_images/mems-microphone.80574019e1f5e4d9ee72fed720ecd25a39fc2969c91355d17ebb24ba4159e4c4.sw.png)

    Katika picha hapo juu, chipu iliyoandikwa **LEFT** ni maikrofoni ya MEMS, yenye diaphragm ndogo chini ya milimita moja.

✅ Fanya utafiti: Ni maikrofoni gani unazo karibu nawe - iwe kwenye kompyuta yako, simu yako, headset yako au vifaa vingine. Ni aina gani ya maikrofoni?

### Sauti ya Kidijitali

Sauti ni ishara ya analogi inayobeba taarifa za kina sana. Ili kubadilisha ishara hii kuwa ya kidijitali, sauti inahitaji kuchukuliwa sampuli mara maelfu kwa sekunde.

> 🎓 Kuchukua sampuli ni kubadilisha ishara ya sauti kuwa thamani ya kidijitali inayowakilisha ishara hiyo kwa wakati huo.

![Chati ya mstari inayoonyesha ishara, na pointi maalum kwa vipindi vilivyowekwa](../../../../../translated_images/sampling.6f4fadb3f2d9dfe7.sw.png)

Sauti ya kidijitali inachukuliwa sampuli kwa kutumia Pulse Code Modulation, au PCM. PCM inahusisha kusoma voltage ya ishara, na kuchagua thamani ya karibu zaidi ya kidijitali kwa voltage hiyo kwa kutumia ukubwa ulioainishwa.

> 💁 Unaweza kufikiria PCM kama toleo la kihisi la Pulse Width Modulation, au PWM (PWM ilijadiliwa nyuma katika [somo la 3 la mradi wa kuanza](../../../1-getting-started/lessons/3-sensors-and-actuators/README.md#pulse-width-modulation)). PCM inahusisha kubadilisha ishara ya analogi kuwa ya kidijitali, PWM inahusisha kubadilisha ishara ya kidijitali kuwa ya analogi.

Kwa mfano, huduma nyingi za muziki wa mtandaoni hutoa sauti ya 16-bit au 24-bit. Hii inamaanisha zinabadilisha voltage kuwa thamani inayofaa kwenye integer ya 16-bit, au integer ya 24-bit. Sauti ya 16-bit inafaa thamani kwenye nambari inayotoka -32,768 hadi 32,767, 24-bit ni katika safu ya −8,388,608 hadi 8,388,607. Kadri bits zinavyoongezeka, ndivyo sampuli inavyokaribia kile masikio yetu yanavyosikia.

> 💁 Huenda umewahi kusikia kuhusu sauti ya 8-bit, mara nyingi huitwa LoFi. Hii ni sauti iliyochukuliwa sampuli kwa kutumia bits 8 tu, hivyo -128 hadi 127. Sauti ya kompyuta ya kwanza ilipunguzwa hadi 8-bit kutokana na vikwazo vya vifaa, hivyo mara nyingi huonekana katika michezo ya video ya zamani.

Sampuli hizi huchukuliwa mara maelfu kwa sekunde, kwa kutumia viwango vya sampuli vilivyoainishwa vizuri vinavyopimwa kwa KHz (maelfu ya usomaji kwa sekunde). Huduma za muziki wa mtandaoni hutumia 48KHz kwa sauti nyingi, lakini baadhi ya sauti za 'lossless' hutumia hadi 96KHz au hata 192KHz. Kadri kiwango cha sampuli kinavyoongezeka, ndivyo sauti inavyokaribia asili, hadi kufikia kiwango fulani. Kuna mjadala kama binadamu wanaweza kutofautisha zaidi ya 48KHz.

✅ Fanya utafiti: Ikiwa unatumia huduma ya muziki wa mtandaoni, ni kiwango gani cha sampuli na ukubwa kinachotumika? Ikiwa unatumia CD, ni kiwango gani cha sampuli na ukubwa wa sauti ya CD?

Kuna miundo mbalimbali ya data ya sauti. Huenda umewahi kusikia kuhusu faili za mp3 - data ya sauti iliyoshinikizwa ili kuifanya ndogo bila kupoteza ubora wowote. Sauti isiyoshinikizwa mara nyingi huhifadhiwa kama faili ya WAV - hii ni faili yenye baiti 44 za taarifa ya kichwa, ikifuatiwa na data ya sauti ghafi. Kichwa kina taarifa kama kiwango cha sampuli (kwa mfano 16000 kwa 16KHz) na ukubwa wa sampuli (16 kwa 16-bit), na idadi ya njia. Baada ya kichwa, faili ya WAV ina data ya sauti ghafi.

> 🎓 Njia zinahusu idadi ya mito tofauti ya sauti inayounda sauti. Kwa mfano, kwa sauti ya stereo yenye kushoto na kulia, kungekuwa na njia 2. Kwa sauti ya 7.1 surround sound kwa mfumo wa sinema ya nyumbani, hii ingekuwa njia 8.

### Ukubwa wa Data ya Sauti

Data ya sauti ni kubwa kiasi. Kwa mfano, kunasa sauti isiyoshinikizwa ya 16-bit kwa 16KHz (kiwango kizuri kwa matumizi na modeli ya sauti hadi maandishi), huchukua 32KB ya data kwa kila sekunde ya sauti:

* 16-bit inamaanisha baiti 2 kwa sampuli (1 baiti ni bits 8).
* 16KHz ni sampuli 16,000 kwa sekunde.
* 16,000 x baiti 2 = baiti 32,000 kwa sekunde.

Hii inaonekana kama kiasi kidogo cha data, lakini ikiwa unatumia microcontroller yenye kumbukumbu ndogo, hii inaweza kuwa nyingi. Kwa mfano, Wio Terminal ina kumbukumbu ya 192KB, na hiyo inahitaji kuhifadhi msimbo wa programu na vigezo. Hata kama msimbo wako wa programu ungekuwa mdogo, usingeweza kunasa zaidi ya sekunde 5 za sauti.

Microcontrollers zinaweza kufikia hifadhi ya ziada, kama kadi za SD au kumbukumbu ya flash. Unapojenga kifaa cha IoT kinachonasa sauti, utahitaji kuhakikisha sio tu una hifadhi ya ziada, bali msimbo wako unaandika sauti iliyonaswa kutoka kwa maikrofoni moja kwa moja kwenye hifadhi hiyo, na unapoituma kwenye wingu, unastream kutoka hifadhi hadi ombi la wavuti. Kwa njia hiyo unaweza kuepuka kumaliza kumbukumbu kwa kujaribu kushikilia kizuizi kizima cha data ya sauti kwenye kumbukumbu mara moja.

## Kunasa Sauti kutoka kwa Kifaa chako cha IoT

Kifaa chako cha IoT kinaweza kuunganishwa na maikrofoni ili kunasa sauti, tayari kwa kubadilishwa kuwa maandishi. Pia kinaweza kuunganishwa na spika kutoa sauti. Katika masomo ya baadaye, hii itatumika kutoa maoni ya sauti, lakini ni muhimu kusanidi spika sasa ili kujaribu maikrofoni.

### Kazi - Sanidi Maikrofoni na Spika Zako

Fanya kazi kupitia mwongozo husika ili kusanidi maikrofoni na spika kwa kifaa chako cha IoT:

* [Arduino - Wio Terminal](wio-terminal-microphone.md)
* [Kompyuta ya bodi moja - Raspberry Pi](pi-microphone.md)
* [Kompyuta ya bodi moja - Kifaa cha Virtual](virtual-device-microphone.md)

### Kazi - Kunasa Sauti

Fanya kazi kupitia mwongozo husika ili kunasa sauti kwenye kifaa chako cha IoT:

* [Arduino - Wio Terminal](wio-terminal-audio.md)
* [Kompyuta ya bodi moja - Raspberry Pi](pi-audio.md)
* [Kompyuta ya bodi moja - Kifaa cha Virtual](virtual-device-audio.md)

## Sauti hadi Maandishi

Sauti hadi maandishi, au utambuzi wa sauti, inahusisha kutumia AI kubadilisha maneno katika ishara ya sauti kuwa maandishi.

### Miundo ya Utambuzi wa Sauti

Ili kubadilisha sauti kuwa maandishi, sampuli kutoka kwa ishara ya sauti huwekwa pamoja na kulishwa kwenye modeli ya kujifunza kwa mashine inayotegemea Recurrent Neural Network (RNN). Hii ni aina ya modeli ya kujifunza kwa mashine inayoweza kutumia data ya awali kufanya uamuzi kuhusu data inayoingia. Kwa mfano, RNN inaweza kugundua kizuizi kimoja cha sampuli za sauti kama sauti 'Hel', na inapopokea nyingine inayofikiri ni sauti 'lo', inaweza kuchanganya hii na sauti ya awali, kugundua kuwa 'Hello' ni neno halali na kuchagua hilo kama jibu.

Modeli za ML daima hukubali data ya ukubwa sawa kila wakati. Kainishaji cha picha ulichojenga katika somo la awali hupunguza picha hadi ukubwa maalum na kuzichakata. Vivyo hivyo na modeli za sauti, zinapaswa kuchakata vipande vya sauti vya ukubwa maalum. Modeli za sauti zinahitaji kuwa na uwezo wa kuchanganya matokeo ya utabiri mwingi kupata jibu, ili kuruhusu kutofautisha kati ya 'Hi' na 'Highway', au 'flock' na 'floccinaucinihilipilification'.

Modeli za sauti pia ni za hali ya juu kiasi cha kuelewa muktadha, na zinaweza kusahihisha maneno yanayogunduliwa kadri sauti zaidi inavyosindikwa. Kwa mfano, ukisema "Nilienda dukani kununua ndizi mbili na tufaha pia", ungetumia maneno matatu yanayofanana sauti, lakini yanayoandikwa tofauti - to, two na too. Modeli za sauti zinaweza kuelewa muktadha na kutumia tahajia sahihi ya neno.
💁 Huduma zingine za sauti huruhusu ubinafsishaji ili kufanya kazi vizuri zaidi katika mazingira yenye kelele kama vile viwandani, au na maneno maalum ya sekta kama majina ya kemikali. Ubinafsishaji huu hufundishwa kwa kutoa sampuli za sauti na maandishi, na hufanya kazi kwa kutumia kujifunza kwa uhamisho, sawa na jinsi ulivyofundisha kionyesha picha kwa kutumia picha chache tu katika somo la awali.
### Faragha

Unapotumia teknolojia ya kutambua sauti kwenye kifaa cha IoT cha watumiaji, faragha ni jambo la msingi sana. Vifaa hivi husikiliza sauti bila kukoma, hivyo kama mtumiaji hutaki kila unachosema kutumwa kwenye wingu na kubadilishwa kuwa maandishi. Hii haitatumia tu kiwango kikubwa cha mtandao, bali pia ina athari kubwa kwa faragha, hasa pale ambapo baadhi ya watengenezaji wa vifaa mahiri huchagua sauti kiholela kwa [wanadamu kuthibitisha dhidi ya maandishi yaliyotengenezwa ili kuboresha modeli zao](https://www.theverge.com/2019/4/10/18305378/amazon-alexa-ai-voice-assistant-annotation-listen-private-recordings).

Unataka kifaa chako mahiri kitume sauti kwenye wingu kwa ajili ya uchakataji tu pale unapokitumia, si pale kinaposikia sauti nyumbani kwako, sauti ambayo inaweza kujumuisha mikutano ya faragha au mazungumzo ya karibu. Njia ambayo vifaa vingi mahiri hufanya kazi ni kwa kutumia *neno la kuamsha*, kifungu cha maneno kama "Alexa", "Hey Siri", au "OK Google" ambacho husababisha kifaa 'kuamka' na kusikiliza unachosema hadi kinapogundua mapumziko katika hotuba yako, ikionyesha kuwa umemaliza kuzungumza na kifaa.

> 🎓 Utambuzi wa neno la kuamsha pia hujulikana kama *Keyword spotting* au *Keyword recognition*.

Maneno haya ya kuamsha hutambuliwa kwenye kifaa, si kwenye wingu. Vifaa hivi mahiri vina modeli ndogo za AI zinazokimbia kwenye kifaa ambazo husikiliza neno la kuamsha, na pale linapogunduliwa, huanza kutuma sauti kwenye wingu kwa ajili ya utambuzi. Modeli hizi ni maalum sana, na husikiliza tu neno la kuamsha.

> 💁 Baadhi ya kampuni za teknolojia zinaongeza faragha zaidi kwenye vifaa vyao na kufanya sehemu ya ubadilishaji wa sauti kuwa maandishi kwenye kifaa. Apple imetangaza kuwa kama sehemu ya masasisho yao ya iOS na macOS ya 2021 wataunga mkono ubadilishaji wa sauti kuwa maandishi kwenye kifaa, na kuweza kushughulikia maombi mengi bila hitaji la kutumia wingu. Hii ni kutokana na kuwa na prosesa zenye nguvu kwenye vifaa vyao zinazoweza kuendesha modeli za ML.

✅ Unadhani ni athari gani za faragha na maadili za kuhifadhi sauti inayotumwa kwenye wingu? Je, sauti hii inapaswa kuhifadhiwa, na ikiwa ndiyo, inapaswa kuhifadhiwa vipi? Je, unadhani matumizi ya rekodi kwa ajili ya utekelezaji wa sheria ni ubadilishaji mzuri kwa kupoteza faragha?

Utambuzi wa neno la kuamsha kwa kawaida hutumia mbinu inayojulikana kama TinyML, ambayo ni kubadilisha modeli za ML ili ziweze kukimbia kwenye microcontrollers. Modeli hizi ni ndogo kwa ukubwa, na hutumia nguvu kidogo sana kuendesha.

Ili kuepuka ugumu wa kufundisha na kutumia modeli ya neno la kuamsha, kipima muda mahiri unachojenga katika somo hili kitatumia kitufe kuwasha utambuzi wa sauti.

> 💁 Ikiwa unataka kujaribu kuunda modeli ya utambuzi wa neno la kuamsha ili kukimbia kwenye Wio Terminal au Raspberry Pi, angalia [mafunzo ya kujibu sauti yako na Edge Impulse](https://docs.edgeimpulse.com/docs/responding-to-your-voice). Ikiwa unataka kutumia kompyuta yako kufanya hivyo, unaweza kujaribu [kuanza haraka na Keyword ya kawaida kwenye Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Badilisha sauti kuwa maandishi

![Nembo ya huduma za sauti](../../../../../translated_images/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.sw.png)

Kama ilivyo kwenye uainishaji wa picha katika mradi wa awali, kuna huduma za AI zilizojengwa tayari ambazo zinaweza kuchukua sauti kama faili ya sauti na kuibadilisha kuwa maandishi. Mojawapo ya huduma hizo ni Huduma ya Sauti, sehemu ya Huduma za Kognitivi, huduma za AI zilizojengwa tayari unazoweza kutumia kwenye programu zako.

### Kazi - sanidi rasilimali ya AI ya sauti

1. Unda Kikundi cha Rasilimali kwa mradi huu kinachoitwa `smart-timer`

1. Tumia amri ifuatayo kuunda rasilimali ya sauti ya bure:

    ```sh
    az cognitiveservices account create --name smart-timer \
                                        --resource-group smart-timer \
                                        --kind SpeechServices \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Badilisha `<location>` na eneo ulilotumia wakati wa kuunda Kikundi cha Rasilimali.

1. Utahitaji funguo ya API kufikia rasilimali ya sauti kutoka kwa msimbo wako. Endesha amri ifuatayo kupata funguo:

    ```sh
    az cognitiveservices account keys list --name smart-timer \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Chukua nakala ya mojawapo ya funguo.

### Kazi - badilisha sauti kuwa maandishi

Fanya kazi kupitia mwongozo husika kubadilisha sauti kuwa maandishi kwenye kifaa chako cha IoT:

* [Arduino - Wio Terminal](wio-terminal-speech-to-text.md)
* [Kompyuta ya bodi moja - Raspberry Pi](pi-speech-to-text.md)
* [Kompyuta ya bodi moja - Kifaa cha kawaida](virtual-device-speech-to-text.md)

---

## 🚀 Changamoto

Utambuzi wa sauti umekuwepo kwa muda mrefu, na unaendelea kuboreka. Fanya utafiti kuhusu uwezo wa sasa na linganisha jinsi uwezo huu umebadilika kwa muda, ikiwa ni pamoja na jinsi maandishi ya mashine yanavyolingana na yale ya binadamu.

Unadhani siku zijazo zinashikilia nini kwa utambuzi wa sauti?

## Jaribio la baada ya somo

[Jaribio la baada ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/42)

## Mapitio na Kujisomea

* Soma kuhusu aina tofauti za maikrofoni na jinsi zinavyofanya kazi kwenye [tofauti kati ya maikrofoni za dynamic na condenser kwenye makala ya Musician's HQ](https://musicianshq.com/whats-the-difference-between-dynamic-and-condenser-microphones/).
* Soma zaidi kuhusu huduma ya sauti ya Huduma za Kognitivi kwenye [nyaraka za huduma ya sauti kwenye Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn)
* Soma kuhusu utambuzi wa neno kuu kwenye [nyaraka za utambuzi wa neno kuu kwenye Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn)

## Kazi

[](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.