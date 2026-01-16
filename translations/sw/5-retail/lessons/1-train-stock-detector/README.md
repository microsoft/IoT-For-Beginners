<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8df310a42f902139a01417dacb1ffbef",
  "translation_date": "2025-08-27T22:37:05+00:00",
  "source_file": "5-retail/lessons/1-train-stock-detector/README.md",
  "language_code": "sw"
}
-->
# Fanya Kifaa cha Kugundua Hisa

![Muhtasari wa somo hili kwa sketchnote](../../../../../translated_images/sw/lesson-19.cf6973cecadf080c4b526310620dc4d6f5994c80fb0139c6f378cc9ca2d435cd.jpg)

> Sketchnote na [Nitya Narasimhan](https://github.com/nitya). Bofya picha kwa toleo kubwa zaidi.

Video hii inatoa muhtasari wa Kugundua Vitu kwa kutumia huduma ya Azure Custom Vision, huduma ambayo itajadiliwa katika somo hili.

[![Custom Vision 2 - Object Detection Made Easy | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Bofya picha hapo juu kutazama video

## Jaribio la kabla ya somo

[Jaribio la kabla ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Utangulizi

Katika mradi uliopita, ulitumia AI kufundisha kifaa cha kuainisha picha - mfano ambao unaweza kusema kama picha ina kitu fulani, kama vile tunda lililoiva au lisiloiva. Aina nyingine ya mfano wa AI inayoweza kutumika na picha ni kugundua vitu. Miundo hii haifanyi uainishaji wa picha kwa kutumia lebo, badala yake hufundishwa kutambua vitu, na inaweza kuvipata kwenye picha, si tu kugundua kuwa kitu kipo, bali pia mahali kilipo kwenye picha. Hii inakuruhusu kuhesabu vitu kwenye picha.

Katika somo hili utajifunza kuhusu kugundua vitu, ikiwa ni pamoja na jinsi inavyoweza kutumika katika biashara ya rejareja. Pia utajifunza jinsi ya kufundisha kifaa cha kugundua vitu mtandaoni.

Katika somo hili tutajadili:

* [Kugundua vitu](../../../../../5-retail/lessons/1-train-stock-detector)
* [Kutumia kugundua vitu katika rejareja](../../../../../5-retail/lessons/1-train-stock-detector)
* [Kufundisha kifaa cha kugundua vitu](../../../../../5-retail/lessons/1-train-stock-detector)
* [Kujaribu kifaa chako cha kugundua vitu](../../../../../5-retail/lessons/1-train-stock-detector)
* [Kufundisha tena kifaa chako cha kugundua vitu](../../../../../5-retail/lessons/1-train-stock-detector)

## Kugundua vitu

Kugundua vitu kunahusisha kugundua vitu kwenye picha kwa kutumia AI. Tofauti na kifaa cha kuainisha picha ulichofundisha kwenye mradi uliopita, kugundua vitu hakuhusu kutabiri lebo bora kwa picha nzima, bali kutafuta kitu kimoja au zaidi kwenye picha.

### Kugundua vitu dhidi ya uainishaji wa picha

Uainishaji wa picha unahusu kuainisha picha nzima - ni uwezekano gani kwamba picha nzima inalingana na kila lebo. Unapata uwezekano kwa kila lebo iliyotumika kufundisha mfano.

![Uainishaji wa picha wa korosho na nyanya ya kopo](../../../../../translated_images/sw/image-classifier-cashews-tomato.bc2e16ab8f05cf9ac0f59f73e32efc4227f9a5b601b90b2c60f436694547a965.png)

Katika mfano hapo juu, picha mbili zimeainishwa kwa kutumia mfano uliotengenezwa kuainisha vyombo vya korosho au makopo ya nyanya ya kopo. Picha ya kwanza ni chombo cha korosho, na ina matokeo mawili kutoka kwa kifaa cha kuainisha picha:

| Lebo           | Uwezekano   |
| -------------- | ----------: |
| `korosho`      | 98.4%       |
| `nyanya ya kopo` | 1.6%        |

Picha ya pili ni ya kopo la nyanya ya kopo, na matokeo ni:

| Lebo           | Uwezekano   |
| -------------- | ----------: |
| `korosho`      | 0.7%        |
| `nyanya ya kopo` | 99.3%       |

Unaweza kutumia thamani hizi na asilimia ya kizingiti kutabiri kilichomo kwenye picha. Lakini vipi kama picha ina makopo mengi ya nyanya ya kopo, au korosho na nyanya ya kopo? Matokeo hayawezi kukupa kile unachotaka. Hapa ndipo kugundua vitu kunapokuja.

Kugundua vitu kunahusisha kufundisha mfano kutambua vitu. Badala ya kumpa picha zenye kitu na kumwambia kila picha ni lebo moja au nyingine, unasisitiza sehemu ya picha inayojumuisha kitu maalum, na kuipa lebo hiyo. Unaweza kuipa lebo kitu kimoja kwenye picha au vitu vingi. Kwa njia hii mfano hujifunza jinsi kitu chenyewe kinavyoonekana, si tu jinsi picha zinazojumuisha kitu zinavyoonekana.

Unapoitumia kutabiri picha, badala ya kupata orodha ya lebo na asilimia, unapata orodha ya vitu vilivyogunduliwa, na sanduku la mipaka na uwezekano kwamba sanduku la mipaka linafanana na lebo iliyotolewa.

> 🎓 *Sanduku la mipaka* ni masanduku yanayozunguka kitu.

![Kugundua vitu vya korosho na nyanya ya kopo](../../../../../translated_images/sw/object-detector-cashews-tomato.1af7c26686b4db0e709754aeb196f4e73271f54e2085db3bcccb70d4a0d84d97.png)

Picha hapo juu ina chombo cha korosho na makopo matatu ya nyanya ya kopo. Kifaa cha kugundua vitu kiligundua korosho, kikitoa sanduku la mipaka linalojumuisha korosho na asilimia ya uwezekano kwamba sanduku la mipaka lina kitu hicho, katika kesi hii 97.6%. Kifaa cha kugundua vitu pia kimegundua makopo matatu ya nyanya ya kopo, na kinatoa masanduku matatu tofauti ya mipaka, moja kwa kila kopo lililogunduliwa, na kila moja lina asilimia ya uwezekano kwamba sanduku la mipaka lina kopo la nyanya ya kopo.

✅ Fikiria baadhi ya hali tofauti ambazo unaweza kutaka kutumia mifano ya AI inayotegemea picha. Ni zipi zingehitaji uainishaji, na zipi zingehitaji kugundua vitu?

### Jinsi kugundua vitu kunavyofanya kazi

Kugundua vitu kunatumia mifano changamano ya ML. Mifano hii hufanya kazi kwa kugawanya picha katika seli nyingi, kisha hukagua kama kituo cha sanduku la mipaka ni kituo cha picha kinacholingana na moja ya picha zilizotumika kufundisha mfano. Unaweza kufikiria hili kama kuendesha kifaa cha kuainisha picha juu ya sehemu tofauti za picha kutafuta mechi.

> 💁 Hii ni rahisi sana kuelezea. Kuna mbinu nyingi za kugundua vitu, na unaweza kusoma zaidi kuhusu hizo kwenye [ukurasa wa Kugundua Vitu kwenye Wikipedia](https://wikipedia.org/wiki/Object_detection).

Kuna mifano kadhaa tofauti inayoweza kugundua vitu. Mfano mmoja maarufu sana ni [YOLO (You Only Look Once)](https://pjreddie.com/darknet/yolo/), ambao ni wa haraka sana na unaweza kugundua madarasa 20 tofauti ya vitu, kama watu, mbwa, chupa na magari.

✅ Soma kuhusu mfano wa YOLO kwenye [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/)

Mifano ya kugundua vitu inaweza kufundishwa tena kwa kutumia kujifunza kwa uhamisho ili kugundua vitu maalum.

## Kutumia kugundua vitu katika rejareja

Kugundua vitu kuna matumizi mengi katika rejareja. Baadhi ni pamoja na:

* **Ukaguzi wa hisa na kuhesabu** - kutambua wakati hisa zimepungua kwenye rafu. Ikiwa hisa zimepungua sana, arifa zinaweza kutumwa kwa wafanyakazi au roboti ili kujaza tena rafu.
* **Kutambua barakoa** - katika maduka yenye sera za barakoa wakati wa matukio ya afya ya umma, kugundua vitu kunaweza kutambua watu waliovaa barakoa na wasio na barakoa.
* **Malipo ya kiotomatiki** - kugundua vitu vilivyochukuliwa kutoka rafu katika maduka ya kiotomatiki na kuwatoza wateja ipasavyo.
* **Kutambua hatari** - kutambua vitu vilivyovunjika sakafuni, au vimiminika vilivyomwagika, na kuwaarifu wafanyakazi wa usafi.

✅ Fanya utafiti: Ni matumizi gani mengine ya kugundua vitu katika rejareja?

## Kufundisha kifaa cha kugundua vitu

Unaweza kufundisha kifaa cha kugundua vitu kwa kutumia Custom Vision, kwa njia sawa na ulivyofundisha kifaa cha kuainisha picha.

### Kazi - tengeneza kifaa cha kugundua vitu

1. Tengeneza Kikundi cha Rasilimali kwa mradi huu kinachoitwa `stock-detector`

1. Tengeneza rasilimali ya mafunzo ya Custom Vision ya bure, na rasilimali ya utabiri ya bure ya Custom Vision katika kikundi cha rasilimali `stock-detector`. Wape majina `stock-detector-training` na `stock-detector-prediction`.

    > 💁 Unaweza kuwa na rasilimali moja tu ya mafunzo na utabiri ya bure, kwa hivyo hakikisha umefuta mradi wako kutoka masomo ya awali.

    > ⚠️ Unaweza kurejelea [maelekezo ya kutengeneza rasilimali za mafunzo na utabiri kutoka mradi wa 4, somo la 1 ikiwa inahitajika](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. Fungua lango la Custom Vision kwenye [CustomVision.ai](https://customvision.ai), na uingie kwa akaunti ya Microsoft uliyotumia kwa akaunti yako ya Azure.

1. Fuata [Sehemu ya Kutengeneza Mradi Mpya ya mwongozo wa haraka wa Kujenga kifaa cha kugundua vitu kwenye nyaraka za Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project) kutengeneza mradi mpya wa Custom Vision. UI inaweza kubadilika na nyaraka hizi daima ni rejeleo la kisasa zaidi.

    Weka jina la mradi wako `stock-detector`.

    Unapounda mradi wako, hakikisha unatumia rasilimali ya `stock-detector-training` uliyotengeneza awali. Tumia aina ya mradi wa *Object Detection*, na kikoa cha *Products on Shelves*.

    ![Mipangilio ya mradi wa Custom Vision na jina limewekwa kuwa fruit-quality-detector, hakuna maelezo, rasilimali imewekwa kuwa fruit-quality-detector-training, aina ya mradi imewekwa kuwa classification, aina za classification zimewekwa kuwa multi class na kikoa kimewekwa kuwa food](../../../../../translated_images/sw/custom-vision-create-object-detector-project.32d4fb9aa8e7e7375f8a799bfce517aca970f2cb65e42d4245c5e635c734ab29.png)

    ✅ Kikoa cha bidhaa kwenye rafu kinalenga hasa kugundua hisa kwenye rafu za maduka. Soma zaidi kuhusu kikoa tofauti kwenye [Nyaraka za kuchagua kikoa kwenye Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection)

✅ Chukua muda kuchunguza UI ya Custom Vision kwa kifaa chako cha kugundua vitu.

### Kazi - fundisha kifaa chako cha kugundua vitu

Ili kufundisha mfano wako utahitaji seti ya picha zinazojumuisha vitu unavyotaka kugundua.

1. Kusanya picha zinazojumuisha kitu cha kugundua. Utahitaji angalau picha 15 zinazojumuisha kila kitu cha kugundua kutoka pembe tofauti na katika hali tofauti za mwanga, lakini kadri unavyokuwa nazo zaidi ndivyo ilivyo bora. Kifaa hiki cha kugundua vitu kinatumia kikoa cha *Products on shelves*, kwa hivyo jaribu kupanga vitu kana kwamba viko kwenye rafu ya duka. Pia utahitaji picha chache za kujaribu mfano. Ikiwa unagundua zaidi ya kitu kimoja, utahitaji baadhi ya picha za majaribio zinazojumuisha vitu vyote.

    > 💁 Picha zilizo na vitu tofauti tofauti zinahesabika kuelekea kiwango cha chini cha picha 15 kwa vitu vyote vilivyo kwenye picha.

    Picha zako zinapaswa kuwa png au jpeg, ndogo kuliko 6MB. Ikiwa utazitengeneza kwa kutumia iPhone kwa mfano zinaweza kuwa picha za azimio la juu za HEIC, kwa hivyo zitahitaji kubadilishwa na labda kupunguzwa. Kadri unavyokuwa na picha nyingi ndivyo ilivyo bora, na unapaswa kuwa na idadi sawa ya vitu vilivyoiva na visivyoiva.

    Mfano umeundwa kwa bidhaa kwenye rafu, kwa hivyo jaribu kupiga picha za vitu kwenye rafu.

    Unaweza kupata baadhi ya picha za mfano ambazo unaweza kutumia kwenye [folda ya picha](../../../../../5-retail/lessons/1-train-stock-detector/images) ya korosho na nyanya ya kopo ambazo unaweza kutumia.

1. Fuata [Sehemu ya Kupakia na Kuweka Lebo Picha ya mwongozo wa haraka wa Kujenga kifaa cha kugundua vitu kwenye nyaraka za Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) kupakia picha zako za mafunzo. Tengeneza lebo zinazofaa kulingana na aina za vitu unavyotaka kugundua.

    ![Vidirisha vya kupakia vikionyesha upakiaji wa picha za ndizi zilizoiva na zisizoiva](../../../../../translated_images/sw/image-upload-object-detector.77c7892c3093cb59b79018edecd678749a75d71a099bc8a2d2f2f76320f88a5b.png)

    Unapochora masanduku ya mipaka kwa vitu, yaweke karibu na kitu. Inaweza kuchukua muda kuainisha picha zote, lakini zana itagundua kile inachofikiri ni masanduku ya mipaka, na kufanya iwe haraka zaidi.

    ![Kuweka lebo kwa nyanya ya kopo](../../../../../translated_images/sw/object-detector-tag-tomato-paste.f47c362fb0f0eb582f3bc68cf3855fb43a805106395358d41896a269c210b7b4.png)

    > 💁 Ikiwa una zaidi ya picha 15 kwa kila kitu, unaweza kufundisha baada ya 15 kisha kutumia kipengele cha **Suggested tags**. Hii itatumia mfano uliotengenezwa kugundua vitu kwenye picha ambazo hazijawekwa lebo. Unaweza kisha kuthibitisha vitu vilivyogunduliwa, au kukataa na kuchora tena masanduku ya mipaka. Hii inaweza kuokoa *muda mwingi*.

1. Fuata [Sehemu ya Kufundisha kifaa cha kugundua vitu ya mwongozo wa haraka wa Kujenga kifaa cha kugundua vitu kwenye nyaraka za Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector) kufundisha kifaa cha kugundua vitu kwenye picha zako zilizowekwa lebo.

    Utapewa chaguo la aina ya mafunzo. Chagua **Quick Training**.

Kifaa cha kugundua vitu kisha kitafundishwa. Itachukua dakika chache kukamilisha mafunzo.

## Jaribu kifaa chako cha kugundua vitu

Baada ya kifaa chako cha kugundua vitu kufundishwa, unaweza kukijaribu kwa kukipa picha mpya za kugundua vitu ndani yake.

### Kazi - jaribu kifaa chako cha kugundua vitu

1. Tumia kitufe cha **Quick Test** kupakia picha za majaribio na kuthibitisha vitu vimegunduliwa. Tumia picha za majaribio ulizotengeneza awali, si picha zozote ulizotumia kwa mafunzo.

    ![Makopo 3 ya nyanya ya kopo yaliyogunduliwa na uwezekano wa 38%, 35.5% na 34.6%](../../../../../translated_images/sw/object-detector-detected-tomato-paste.52656fe87af4c37b4ee540526d63e73ed075da2e54a9a060aa528e0c562fb1b6.png)

1. Jaribu picha zote za majaribio ulizonazo na uangalie uwezekano.

## Fundisha tena kifaa chako cha kugundua vitu

Unapojaribu kifaa chako cha kugundua vitu, kinaweza kisitoe matokeo unayotarajia, sawa na vifaa vya kuainisha picha katika mradi uliopita. Unaweza kuboresha kifaa chako cha kugundua vitu kwa kukifundisha tena kwa picha ambazo hakikupatia matokeo sahihi.

Kila wakati unapotoa utabiri kwa kutumia chaguo la majaribio ya haraka, picha na matokeo huhifadhiwa. Unaweza kutumia picha hizi kufundisha tena mfano wako.

1. Tumia kichupo cha **Predictions** kupata picha ulizotumia kwa majaribio

1. Thibitisha ugunduzi wowote sahihi, futa zisizo sahihi na ongeza vitu vyovyote vilivyokosekana.

1. Fundisha tena na ujaribu tena mfano.

---

## 🚀 Changamoto

Nini kitatokea ikiwa utatumia kifaa cha kugundua vitu na vitu vinavyofanana, kama makopo ya nyanya ya kopo na nyanya zilizokatwa za chapa moja?

Ikiwa una vitu vyovyote vinavyofanana, jaribu kwa kuongeza picha zake kwenye kifaa chako cha kugundua vitu.

## Jaribio la baada ya somo
[Jaribio la baada ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Mapitio na Kujisomea

* Ulipokuwa unafundisha kigunduzi chako cha vitu, ungeona thamani za *Precision*, *Recall*, na *mAP* ambazo hupima ubora wa mfano ulioundwa. Soma zaidi kuhusu thamani hizi ukitumia [sehemu ya Tathmini ya kigunduzi katika mwongozo wa haraka wa Kujenga kigunduzi cha vitu kwenye nyaraka za Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector)
* Soma zaidi kuhusu ugunduzi wa vitu kwenye [ukurasa wa Ugunduzi wa vitu kwenye Wikipedia](https://wikipedia.org/wiki/Object_detection)

## Kazi

[Linganisha maeneo](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.