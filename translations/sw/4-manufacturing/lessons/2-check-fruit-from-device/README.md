<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-27T20:52:35+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "sw"
}
-->
# Angalia Ubora wa Matunda Kutoka Kifaa cha IoT

![Muhtasari wa somo hili kwa njia ya mchoro](../../../../../translated_images/sw/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> Mchoro na [Nitya Narasimhan](https://github.com/nitya). Bonyeza picha kwa toleo kubwa.

## Jaribio la Kabla ya Somo

[Jaribio la kabla ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Utangulizi

Katika somo lililopita ulijifunza kuhusu vichanganuzi vya picha, na jinsi ya kuvifundisha kutambua matunda mazuri na mabaya. Ili kutumia kichanganuzi hiki cha picha katika programu ya IoT, unahitaji uwezo wa kunasa picha kwa kutumia aina fulani ya kamera, na kutuma picha hiyo kwenye wingu ili ichanganuliwe.

Katika somo hili utajifunza kuhusu vihisi vya kamera, na jinsi ya kuvitumia na kifaa cha IoT kunasa picha. Pia utajifunza jinsi ya kuita kichanganuzi cha picha kutoka kwenye kifaa chako cha IoT.

Katika somo hili tutajadili:

* [Vihisi vya kamera](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Kunasa picha kwa kutumia kifaa cha IoT](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Kuchapisha kichanganuzi chako cha picha](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Kuchanganua picha kutoka kwenye kifaa chako cha IoT](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Kuboresha mfano](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Vihisi vya Kamera

Vihisi vya kamera, kama jina linavyopendekeza, ni kamera ambazo unaweza kuunganisha kwenye kifaa chako cha IoT. Zinaweza kunasa picha za kawaida, au kurekodi video inayoendelea. Baadhi zitarudisha data ghafi ya picha, wakati nyingine zitakandamiza data hiyo kuwa faili la picha kama JPEG au PNG. Kwa kawaida, kamera zinazofanya kazi na vifaa vya IoT ni ndogo zaidi na zina azimio la chini ukilinganisha na zile ulizozoea, lakini unaweza kupata kamera zenye azimio la juu zinazolingana na simu za hali ya juu. Unaweza pia kupata lenzi zinazobadilishika, mipangilio ya kamera nyingi, kamera za joto za infraredi, au kamera za miale ya UV.

![Mwanga kutoka eneo fulani unapita kwenye lenzi na kuelekezwa kwenye kihisi cha CMOS](../../../../../translated_images/sw/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

Vihisi vingi vya kamera hutumia vihisi vya picha ambapo kila pikseli ni fotodiode. Lenzi huweka picha kwenye kihisi cha picha, na maelfu au mamilioni ya fotodiode hugundua mwanga unaoangukia kila moja, na kurekodi hiyo kama data ya pikseli.

> 💁 Lenzi hubadilisha picha kuwa chini juu, na kihisi cha kamera kisha hurekebisha picha hiyo kuwa sawa. Hii ni sawa na jinsi macho yako yanavyofanya kazi - kile unachokiona hugunduliwa chini juu nyuma ya jicho lako na ubongo wako hurekebisha.

> 🎓 Kihisi cha picha kinajulikana kama Kihisi cha Pikseli Hai (APS), na aina maarufu zaidi ya APS ni kihisi cha metali-oksidi ya semikondakta kinachosaidiana, au CMOS. Huenda umewahi kusikia neno kihisi cha CMOS kinapotajwa kwa vihisi vya kamera.

Vihisi vya kamera ni vihisi vya kidijitali, vinavyotuma data ya picha kama data ya kidijitali, kwa kawaida kwa msaada wa maktaba inayotoa mawasiliano. Kamera huunganishwa kwa kutumia itifaki kama SPI ili kuruhusu kutuma kiasi kikubwa cha data - picha ni kubwa zaidi ukilinganisha na namba moja kutoka kwa kihisi kama cha joto.

✅ Je, ni vizuizi gani kuhusu ukubwa wa picha kwenye vifaa vya IoT? Fikiria kuhusu vikwazo hasa kwenye vifaa vya mikrokontroli.

## Kunasa Picha kwa Kutumia Kifaa cha IoT

Unaweza kutumia kifaa chako cha IoT kunasa picha ili ichanganuliwe.

### Kazi - kunasa picha kwa kutumia kifaa cha IoT

Fanya kazi kupitia mwongozo husika ili kunasa picha kwa kutumia kifaa chako cha IoT:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Kompyuta ya bodi moja - Raspberry Pi](pi-camera.md)
* [Kompyuta ya bodi moja - Kifaa cha Virtual](virtual-device-camera.md)

## Kuchapisha Kichanganuzi Chako cha Picha

Ulifundisha kichanganuzi chako cha picha katika somo lililopita. Kabla ya kukitumia kutoka kwenye kifaa chako cha IoT, unahitaji kuchapisha mfano huo.

### Mizunguko ya Mfano

Wakati mfano wako ulipokuwa ukifundishwa katika somo lililopita, huenda uliona kwamba kichupo cha **Utendaji** kinaonyesha mizunguko upande wa kushoto. Wakati ulipofundisha mfano kwa mara ya kwanza ungeona *Mzunguko wa 1* ukiwa kwenye mafunzo. Ulipoboresha mfano kwa kutumia picha za utabiri, ungeona *Mzunguko wa 2* ukiwa kwenye mafunzo.

Kila wakati unapofundisha mfano, unapata mzunguko mpya. Hii ni njia ya kufuatilia matoleo tofauti ya mfano wako yaliyofundishwa kwa seti tofauti za data. Unapofanya **Jaribio la Haraka**, kuna menyu kunjuzi unayoweza kutumia kuchagua mzunguko, ili uweze kulinganisha matokeo katika mizunguko mingi.

Unapokuwa na furaha na mzunguko fulani, unaweza kuuchapisha ili uweze kutumika kutoka kwa programu za nje. Kwa njia hii unaweza kuwa na toleo lililochapishwa linalotumiwa na vifaa vyako, kisha ufanye kazi kwenye toleo jipya kwa mizunguko mingi, kisha ulichapishe mara unapokuwa na furaha nalo.

### Kazi - kuchapisha mzunguko

Mizunguko huchapishwa kutoka kwenye lango la Custom Vision.

1. Fungua lango la Custom Vision kwenye [CustomVision.ai](https://customvision.ai) na ingia ikiwa hujafanya hivyo tayari. Kisha fungua mradi wako wa `fruit-quality-detector`.

1. Chagua kichupo cha **Utendaji** kutoka kwenye chaguo za juu.

1. Chagua mzunguko wa hivi karibuni kutoka kwenye orodha ya *Mizunguko* upande wa kushoto.

1. Chagua kitufe cha **Chapisha** kwa mzunguko huo.

    ![Kitufe cha kuchapisha](../../../../../translated_images/sw/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. Katika kisanduku cha mazungumzo cha *Chapisha Mfano*, weka *Rasilimali ya Utabiri* kuwa rasilimali ya `fruit-quality-detector-prediction` uliyounda katika somo lililopita. Acha jina liwe `Iteration2`, na uchague kitufe cha **Chapisha**.

1. Mara baada ya kuchapishwa, chagua kitufe cha **URL ya Utabiri**. Hii itaonyesha maelezo ya API ya utabiri, na utahitaji haya ili kuita mfano kutoka kwenye kifaa chako cha IoT. Sehemu ya chini imeandikwa *Ikiwa una faili ya picha*, na haya ndiyo maelezo unayohitaji. Chukua nakala ya URL inayoonyeshwa ambayo itakuwa kama:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Ambapo `<location>` itakuwa eneo ulilotumia wakati wa kuunda rasilimali yako ya Custom Vision, na `<id>` itakuwa kitambulisho kirefu kilichotengenezwa na herufi na namba.

    Pia chukua nakala ya thamani ya *Ufunguo wa Utabiri*. Huu ni ufunguo wa usalama ambao lazima upitishwe unapokuita mfano. Ni programu tu zinazopitisha ufunguo huu ndizo zinaruhusiwa kutumia mfano, programu nyingine zote zinakataliwa.

    ![Kisanduku cha mazungumzo cha API ya utabiri kinachoonyesha URL na ufunguo](../../../../../translated_images/sw/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Wakati mzunguko mpya unachapishwa, utakuwa na jina tofauti. Unafikiri ungewezaje kubadilisha mzunguko unaotumiwa na kifaa cha IoT?

## Kuchanganua Picha Kutoka Kwenye Kifaa Chako cha IoT

Sasa unaweza kutumia maelezo haya ya muunganisho kuita kichanganuzi cha picha kutoka kwenye kifaa chako cha IoT.

### Kazi - kuchanganua picha kutoka kwenye kifaa chako cha IoT

Fanya kazi kupitia mwongozo husika ili kuchanganua picha kwa kutumia kifaa chako cha IoT:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Kompyuta ya bodi moja - Raspberry Pi/Kifaa cha Virtual cha IoT](single-board-computer-classify-image.md)

## Kuboresha Mfano

Huenda ukagundua kuwa matokeo unayopata unapoitumia kamera iliyounganishwa kwenye kifaa chako cha IoT hayalingani na matarajio yako. Utabiri si sahihi kila wakati kama unavyokuwa ukitumia picha zilizopakiwa kutoka kwenye kompyuta yako. Hii ni kwa sababu mfano ulifundishwa kwa data tofauti na ile inayotumiwa kwa utabiri.

Ili kupata matokeo bora kwa kichanganuzi cha picha, unataka kufundisha mfano kwa picha zinazofanana zaidi na picha zinazotumiwa kwa utabiri. Ikiwa ulitumia kamera ya simu yako kunasa picha za mafunzo, kwa mfano, ubora wa picha, ukali, na rangi zitakuwa tofauti na kamera iliyounganishwa kwenye kifaa cha IoT.

![Picha 2 za ndizi, moja ya azimio la chini na mwanga duni kutoka kifaa cha IoT, na nyingine ya azimio la juu na mwanga mzuri kutoka simu](../../../../../translated_images/sw/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

Katika picha hapo juu, picha ya ndizi upande wa kushoto ilichukuliwa kwa kutumia Kamera ya Raspberry Pi, ile ya kulia ilichukuliwa ya ndizi hiyo hiyo katika eneo lile lile kwa kutumia iPhone. Kuna tofauti kubwa ya ubora - picha ya iPhone ni kali zaidi, yenye rangi angavu na utofauti mkubwa.

✅ Ni nini kingine kinaweza kusababisha picha zinazonaswa na kifaa chako cha IoT kuwa na utabiri usio sahihi? Fikiria kuhusu mazingira ambayo kifaa cha IoT kinaweza kutumika, ni mambo gani yanaweza kuathiri picha inayonaswa?

Ili kuboresha mfano, unaweza kuufundisha tena kwa kutumia picha zilizonaswa kutoka kwenye kifaa cha IoT.

### Kazi - kuboresha mfano

1. Changanua picha nyingi za matunda yaliyoiva na yasiyoiva kwa kutumia kifaa chako cha IoT.

1. Katika lango la Custom Vision, fundisha tena mfano kwa kutumia picha kwenye kichupo cha *Utabiri*.

    > ⚠️ Unaweza kurejelea [maelekezo ya kufundisha tena kichanganuzi chako katika somo la 1 ikiwa inahitajika](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Ikiwa picha zako zinaonekana tofauti sana na zile za awali zilizotumika kufundisha, unaweza kufuta picha zote za awali kwa kuzichagua kwenye kichupo cha *Picha za Mafunzo* na kuchagua kitufe cha **Futa**. Ili kuchagua picha, peleka kipanya chako juu yake na tiki itaonekana, chagua tiki hiyo ili kuchagua au kuondoa picha.

1. Fundisha mzunguko mpya wa mfano na uuchapishe kwa kutumia hatua zilizo hapo juu.

1. Sasisha URL ya mwisho katika msimbo wako, na uendeshe tena programu.

1. Rudia hatua hizi hadi uwe na furaha na matokeo ya utabiri.

---

## 🚀 Changamoto

Je, azimio la picha au mwanga linaathiri kiasi gani utabiri?

Jaribu kubadilisha azimio la picha kwenye msimbo wa kifaa chako na uone kama linafanya tofauti kwenye ubora wa picha. Pia jaribu kubadilisha mwanga.

Ikiwa ungeunda kifaa cha uzalishaji kuuza kwa mashamba au viwanda, ungehakikishaje kinatoa matokeo thabiti kila wakati?

## Jaribio la Baada ya Somo

[Jaribio la baada ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Mapitio na Kujisomea

Ulifundisha mfano wako wa Custom Vision kwa kutumia lango. Hii inategemea kuwa na picha zinazopatikana - na katika ulimwengu halisi huenda usiweze kupata data ya mafunzo inayolingana na ile inayonaswa na kamera kwenye kifaa chako. Unaweza kuzunguka changamoto hii kwa kufundisha moja kwa moja kutoka kwenye kifaa chako kwa kutumia API ya mafunzo, ili kufundisha mfano kwa kutumia picha zilizonaswa kutoka kwenye kifaa chako cha IoT.

* Soma kuhusu API ya mafunzo katika [kuanza haraka kwa kutumia SDK ya Custom Vision](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Kazi

[Itikieni matokeo ya uchanganuzi](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutokuelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.