<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-27T22:41:13+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "sw"
}
-->
# Angalia Hisa Kutoka Kifaa cha IoT

![Muhtasari wa somo hili kwa sketchnote](../../../../../translated_images/sw/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.jpg)

> Sketchnote na [Nitya Narasimhan](https://github.com/nitya). Bofya picha kwa toleo kubwa.

## Maswali ya awali ya somo

[Maswali ya awali ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Utangulizi

Katika somo lililopita ulijifunza kuhusu matumizi tofauti ya utambuzi wa vitu katika sekta ya rejareja. Pia ulijifunza jinsi ya kufundisha kifaa cha kutambua vitu ili kutambua hisa. Katika somo hili, utajifunza jinsi ya kutumia kifaa chako cha kutambua vitu kutoka kwa kifaa chako cha IoT kuhesabu hisa.

Katika somo hili tutajadili:

* [Kuhesabu hisa](../../../../../5-retail/lessons/2-check-stock-device)
* [Kuita kifaa chako cha kutambua vitu kutoka kwa kifaa chako cha IoT](../../../../../5-retail/lessons/2-check-stock-device)
* [Maboksi ya mipaka](../../../../../5-retail/lessons/2-check-stock-device)
* [Kufundisha tena mfano](../../../../../5-retail/lessons/2-check-stock-device)
* [Kuhesabu hisa](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Hili ni somo la mwisho katika mradi huu, kwa hivyo baada ya kukamilisha somo hili na kazi, usisahau kusafisha huduma zako za wingu. Utahitaji huduma hizo kukamilisha kazi, kwa hivyo hakikisha unakamilisha hiyo kwanza.
>
> Rejelea [mwongozo wa kusafisha mradi wako](../../../clean-up.md) ikiwa ni lazima kwa maelekezo ya jinsi ya kufanya hivyo.

## Kuhesabu hisa

Vifaa vya kutambua vitu vinaweza kutumika kwa ukaguzi wa hisa, ama kwa kuhesabu hisa au kuhakikisha hisa ziko mahali zinapopaswa kuwa. Vifaa vya IoT vyenye kamera vinaweza kuwekwa kote dukani kufuatilia hisa, kuanzia maeneo muhimu ambapo kuweka bidhaa ni muhimu, kama vile maeneo yenye bidhaa za thamani kubwa.

Kwa mfano, ikiwa kamera inaelekezwa kwenye rafu inayoweza kushikilia makopo 8 ya tomato paste, na kifaa cha kutambua vitu kinatambua makopo 7 tu, basi moja linakosekana na linahitaji kuwekwa tena.

![Makopo 7 ya tomato paste kwenye rafu, 4 kwenye safu ya juu, 3 juu yake](../../../../../translated_images/sw/stock-7-cans-tomato-paste.f86059cc573d7bec.webp)

Katika picha hapo juu, kifaa cha kutambua vitu kimetambua makopo 7 ya tomato paste kwenye rafu inayoweza kushikilia makopo 8. Si tu kwamba kifaa cha IoT kinaweza kutuma arifa ya hitaji la kuweka bidhaa, lakini pia kinaweza kutoa maelezo ya eneo la bidhaa inayokosekana, data muhimu ikiwa unatumia roboti kuweka bidhaa.

> 💁 Kulingana na duka na umaarufu wa bidhaa, kuweka bidhaa pengine hakutafanyika ikiwa kopo moja tu linakosekana. Utahitaji kujenga algoriti inayobainisha wakati wa kuweka bidhaa kulingana na bidhaa zako, wateja na vigezo vingine.

✅ Katika hali gani nyingine unaweza kuchanganya utambuzi wa vitu na roboti?

Wakati mwingine bidhaa zisizofaa zinaweza kuwa kwenye rafu. Hii inaweza kuwa kosa la binadamu wakati wa kuweka bidhaa, au wateja kubadilisha mawazo yao kuhusu ununuzi na kuweka bidhaa mahali popote. Ikiwa ni bidhaa isiyoharibika kama makopo, hili ni tatizo dogo. Ikiwa ni bidhaa inayoharibika kama bidhaa za baridi au zilizogandishwa, hii inaweza kumaanisha kuwa bidhaa haiwezi kuuzwa tena kwani inaweza kuwa vigumu kujua muda ambao bidhaa ilikuwa nje ya friji.

Utambuzi wa vitu unaweza kutumika kugundua bidhaa zisizotarajiwa, tena kuarifu binadamu au roboti kurudisha bidhaa mara tu inapogunduliwa.

![Kopo la mahindi ya mtoto kwenye rafu ya tomato paste](../../../../../translated_images/sw/stock-rogue-corn.be1f3ada8c457854.webp)

Katika picha hapo juu, kopo la mahindi ya mtoto limewekwa kwenye rafu karibu na tomato paste. Kifaa cha kutambua vitu kimetambua hili, kuruhusu kifaa cha IoT kuarifu binadamu au roboti kurudisha kopo mahali pake sahihi.

## Kuita kifaa chako cha kutambua vitu kutoka kwa kifaa chako cha IoT

Kifaa cha kutambua vitu ulichofundisha katika somo lililopita kinaweza kuitwa kutoka kwa kifaa chako cha IoT.

### Kazi - kuchapisha toleo la kifaa chako cha kutambua vitu

Toleo linachapishwa kutoka kwenye portal ya Custom Vision.

1. Fungua portal ya Custom Vision kwenye [CustomVision.ai](https://customvision.ai) na ingia ikiwa hujafungua tayari. Kisha fungua mradi wako wa `stock-detector`.

1. Chagua kichupo cha **Performance** kutoka kwenye chaguo za juu.

1. Chagua toleo la hivi karibuni kutoka kwenye orodha ya *Iterations* upande wa kushoto.

1. Chagua kitufe cha **Publish** kwa toleo hilo.

    ![Kitufe cha kuchapisha](../../../../../translated_images/sw/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.png)

1. Katika kisanduku cha mazungumzo cha *Publish Model*, weka *Prediction resource* kuwa rasilimali ya `stock-detector-prediction` uliyounda katika somo lililopita. Acha jina liwe `Iteration2`, na uchague kitufe cha **Publish**.

1. Baada ya kuchapishwa, chagua kitufe cha **Prediction URL**. Hii itaonyesha maelezo ya API ya utabiri, na utahitaji haya ili kuita mfano kutoka kwa kifaa chako cha IoT. Sehemu ya chini imeandikwa *If you have an image file*, na haya ndiyo maelezo unayohitaji. Chukua nakala ya URL inayoonyeshwa ambayo itakuwa kama:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Ambapo `<location>` itakuwa eneo ulilotumia wakati wa kuunda rasilimali yako ya Custom Vision, na `<id>` itakuwa kitambulisho kirefu kilichojumuisha herufi na nambari.

    Pia chukua nakala ya thamani ya *Prediction-Key*. Hii ni ufunguo wa usalama ambao lazima upitishwe unapokuita mfano. Programu tu zinazopitisha ufunguo huu ndizo zinazoruhusiwa kutumia mfano, programu nyingine zote zinakataliwa.

    ![Kisanduku cha mazungumzo cha API ya utabiri kinachoonyesha URL na ufunguo](../../../../../translated_images/sw/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Wakati toleo jipya linachapishwa, litakuwa na jina tofauti. Unafikiri ungebadilisha vipi toleo ambalo kifaa cha IoT kinatumia?

### Kazi - kuita kifaa chako cha kutambua vitu kutoka kwa kifaa chako cha IoT

Fuata mwongozo husika hapa chini kutumia kifaa cha kutambua vitu kutoka kwa kifaa chako cha IoT:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Kompyuta ndogo - Raspberry Pi/Kifaa cha Virtual](single-board-computer-object-detector.md)

## Maboksi ya mipaka

Unapotumia kifaa cha kutambua vitu, hupokea si tu vitu vilivyotambuliwa na lebo na uwezekano wao, bali pia maboksi ya mipaka ya vitu hivyo. Maboksi haya yanaonyesha mahali kifaa cha kutambua vitu kilipogundua kitu kwa uwezekano uliotolewa.

> 💁 Boksi la mipaka ni sanduku linalofafanua eneo linaloshikilia kitu kilichotambuliwa, sanduku linalofafanua mipaka ya kitu.

Matokeo ya utabiri katika kichupo cha **Predictions** kwenye Custom Vision yana maboksi ya mipaka yaliyochorwa kwenye picha iliyotumwa kwa utabiri.

![Makopo 4 ya tomato paste kwenye rafu na utabiri wa makopo 4 yaliyotambuliwa kwa asilimia 35.8%, 33.5%, 25.7% na 16.6%](../../../../../translated_images/sw/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

Katika picha hapo juu, makopo 4 ya tomato paste yalitambuliwa. Katika matokeo, mraba mwekundu umewekwa juu kwa kila kitu kilichotambuliwa kwenye picha, kuonyesha boksi la mipaka kwa picha hiyo.

✅ Fungua utabiri kwenye Custom Vision na angalia maboksi ya mipaka.

Maboksi ya mipaka yanafafanuliwa na thamani 4 - juu, kushoto, urefu na upana. Thamani hizi ziko kwenye kiwango cha 0-1, zikionyesha nafasi kama asilimia ya ukubwa wa picha. Asili (nafasi ya 0,0) ni kona ya juu kushoto ya picha, kwa hivyo thamani ya juu ni umbali kutoka juu, na chini ya boksi la mipaka ni juu pamoja na urefu.

![Boksi la mipaka karibu na kopo la tomato paste](../../../../../translated_images/sw/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.png)

Picha hapo juu ina upana wa pikseli 600 na urefu wa pikseli 800. Boksi la mipaka linaanza kwenye pikseli 320 chini, likitoa thamani ya juu ya 0.4 (800 x 0.4 = 320). Kutoka kushoto, boksi la mipaka linaanza kwenye pikseli 240, likitoa thamani ya kushoto ya 0.4 (600 x 0.4 = 240). Urefu wa boksi la mipaka ni pikseli 240, likitoa thamani ya urefu ya 0.3 (800 x 0.3 = 240). Upana wa boksi la mipaka ni pikseli 120, likitoa thamani ya upana ya 0.2 (600 x 0.2 = 120).

| Koordini | Thamani |
| -------- | ------: |
| Juu      | 0.4     |
| Kushoto  | 0.4     |
| Urefu    | 0.3     |
| Upana    | 0.2     |

Kutumia thamani za asilimia kutoka 0-1 kunamaanisha haijalishi ukubwa wa picha umebadilishwa kwa kiasi gani, boksi la mipaka linaanza 0.4 ya njia kando na chini, na ni 0.3 ya urefu na 0.2 ya upana.

Unaweza kutumia maboksi ya mipaka pamoja na uwezekano kutathmini jinsi utambuzi ulivyo sahihi. Kwa mfano, kifaa cha kutambua vitu kinaweza kutambua vitu vingi vinavyofunikana, kwa mfano kutambua kopo moja ndani ya jingine. Msimbo wako unaweza kuangalia maboksi ya mipaka, kuelewa kuwa hili haliwezekani, na kupuuza vitu vyovyote vinavyofunikana kwa kiasi kikubwa na vitu vingine.

![Maboksi mawili ya mipaka yanayofunikana na kopo la tomato paste](../../../../../translated_images/sw/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.png)

Katika mfano hapo juu, boksi moja la mipaka linaonyesha kopo la tomato paste lililotabiriwa kwa asilimia 78.3%. Boksi la pili la mipaka ni dogo kidogo, na liko ndani ya boksi la kwanza la mipaka kwa uwezekano wa asilimia 64.3%. Msimbo wako unaweza kuangalia maboksi ya mipaka, kuona yanayofunikana kabisa, na kupuuza uwezekano wa chini kwani hakuna njia moja inaweza kuwa ndani ya jingine.

✅ Je, unaweza kufikiria hali ambapo ni halali kutambua kitu kimoja ndani ya kingine?

## Kufundisha tena mfano

Kama ilivyokuwa na kifaa cha kuainisha picha, unaweza kufundisha tena mfano wako kwa kutumia data iliyokusanywa na kifaa chako cha IoT. Kutumia data hii ya ulimwengu halisi kutahakikisha mfano wako unafanya kazi vizuri unapotumiwa kutoka kwa kifaa chako cha IoT.

Tofauti na kifaa cha kuainisha picha, huwezi tu kuweka lebo kwenye picha. Badala yake, unahitaji kupitia kila boksi la mipaka lililotambuliwa na mfano. Ikiwa boksi liko karibu na kitu kisichofaa basi linahitaji kufutwa, ikiwa liko mahali pabaya linahitaji kurekebishwa.

### Kazi - kufundisha tena mfano

1. Hakikisha umekusanya picha mbalimbali kwa kutumia kifaa chako cha IoT.

1. Kutoka kwenye kichupo cha **Predictions**, chagua picha. Utaona maboksi mekundu yanayoonyesha maboksi ya mipaka ya vitu vilivyotambuliwa.

1. Pitia kila boksi la mipaka. Chagua kwanza na utaona dirisha dogo linaloonyesha lebo. Tumia vipini kwenye pembe za boksi la mipaka kurekebisha ukubwa ikiwa ni lazima. Ikiwa lebo si sahihi, iondoe kwa kitufe cha **X** na ongeza lebo sahihi. Ikiwa boksi la mipaka halina kitu, lifute kwa kitufe cha takataka.

1. Funga mhariri unapomaliza na picha itahamia kutoka kwenye kichupo cha **Predictions** hadi kwenye kichupo cha **Training Images**. Rudia mchakato kwa utabiri wote.

1. Tumia kitufe cha **Train** kufundisha tena mfano wako. Baada ya kufundishwa, chapisha toleo na sasisha kifaa chako cha IoT kutumia URL ya toleo jipya.

1. Weka tena msimbo wako na ujaribu kifaa chako cha IoT.

## Kuhesabu hisa

Kwa kutumia mchanganyiko wa idadi ya vitu vilivyotambuliwa na maboksi ya mipaka, unaweza kuhesabu hisa kwenye rafu.

### Kazi - kuhesabu hisa

Fuata mwongozo husika hapa chini kuhesabu hisa kwa kutumia matokeo kutoka kwa kifaa cha kutambua vitu kutoka kwa kifaa chako cha IoT:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Kompyuta ndogo - Raspberry Pi/Kifaa cha Virtual](single-board-computer-count-stock.md)

---

## 🚀 Changamoto

Je, unaweza kugundua hisa zisizofaa? Fundisha mfano wako kwa vitu mbalimbali, kisha sasisha programu yako ili ikupe tahadhari ikiwa hisa zisizofaa zitatambuliwa.

Labda hata chukua hatua zaidi na ugundue hisa zilizo karibu kwenye rafu moja, na uone ikiwa kitu kimewekwa mahali pabaya kwa kufafanua mipaka kwenye maboksi ya mipaka.

## Maswali ya baada ya somo

[Maswali ya baada ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Mapitio na Kujisomea

* Jifunze zaidi kuhusu jinsi ya kuunda mfumo wa kugundua hisa kutoka mwanzo hadi mwisho kutoka kwenye [Mwongozo wa mifumo ya kugundua hisa kwenye makali kwenye Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Jifunze njia nyingine za kujenga suluhisho za rejareja kutoka mwanzo hadi mwisho kwa kuchanganya huduma mbalimbali za IoT na wingu kwa kutazama [Behind the scenes of a retail solution - Hands On! video kwenye YouTube](https://www.youtube.com/watch?v=m3Pc300x2Mw).

## Kazi

[Tumia kifaa chako cha kutambua vitu kwenye makali](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kwa usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, inashauriwa kutumia huduma ya tafsiri ya kitaalamu ya binadamu. Hatutawajibika kwa maelewano mabaya au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.