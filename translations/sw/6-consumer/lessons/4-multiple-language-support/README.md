<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-27T21:29:43+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "sw"
}
-->
# Kusaidia Lugha Nyingi

![Muhtasari wa somo hili kwa sketchnote](../../../../../translated_images/sw/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.jpg)

> Sketchnote na [Nitya Narasimhan](https://github.com/nitya). Bonyeza picha kwa toleo kubwa zaidi.

Video hii inatoa muhtasari wa huduma za sauti za Azure, ikijumuisha sauti hadi maandishi na maandishi hadi sauti kutoka masomo ya awali, pamoja na kutafsiri sauti, mada inayoshughulikiwa katika somo hili:

[![Kutambua sauti kwa mistari michache ya Python kutoka Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Bonyeza picha hapo juu kutazama video

## Jaribio la Kabla ya Somo

[Jaribio la kabla ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Utangulizi

Katika masomo matatu yaliyopita ulijifunza kuhusu kubadilisha sauti kuwa maandishi, kuelewa lugha, na kubadilisha maandishi kuwa sauti, yote yakitumia AI. Eneo lingine la mawasiliano ya binadamu ambalo AI inaweza kusaidia ni tafsiri ya lugha - kubadilisha kutoka lugha moja kwenda nyingine, kama vile kutoka Kiingereza kwenda Kifaransa.

Katika somo hili utajifunza jinsi ya kutumia AI kutafsiri maandishi, kuruhusu kipima muda chako mahiri kuwasiliana na watumiaji kwa lugha nyingi.

Katika somo hili tutashughulikia:

* [Tafsiri maandishi](../../../../../6-consumer/lessons/4-multiple-language-support)  
* [Huduma za tafsiri](../../../../../6-consumer/lessons/4-multiple-language-support)  
* [Unda rasilimali ya mtafsiri](../../../../../6-consumer/lessons/4-multiple-language-support)  
* [Kusaidia lugha nyingi katika programu kwa tafsiri](../../../../../6-consumer/lessons/4-multiple-language-support)  
* [Tafsiri maandishi kwa kutumia huduma ya AI](../../../../../6-consumer/lessons/4-multiple-language-support)  

> 🗑 Hili ni somo la mwisho katika mradi huu, kwa hivyo baada ya kukamilisha somo hili na kazi, usisahau kusafisha huduma zako za wingu. Utahitaji huduma hizo kukamilisha kazi, kwa hivyo hakikisha unakamilisha hiyo kwanza.  
>  
> Rejelea [mwongozo wa kusafisha mradi wako](../../../clean-up.md) ikiwa ni lazima kwa maelekezo ya jinsi ya kufanya hivyo.

## Tafsiri Maandishi

Tafsiri ya maandishi imekuwa tatizo la sayansi ya kompyuta lililofanyiwa utafiti kwa zaidi ya miaka 70, na sasa tu kutokana na maendeleo ya AI na nguvu ya kompyuta imekaribia kutatuliwa kwa kiwango ambacho ni karibu sawa na watafsiri wa binadamu.

> 💁 Asili yake inaweza kufuatiliwa hata zaidi, hadi kwa [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), mtaalamu wa kriptografia wa Kiarabu wa karne ya 9 ambaye alitengeneza mbinu za kutafsiri lugha.

### Tafsiri za Mashine

Tafsiri ya maandishi ilianza kama teknolojia inayojulikana kama Tafsiri ya Mashine (MT), ambayo inaweza kutafsiri kati ya jozi za lugha tofauti. MT hufanya kazi kwa kubadilisha maneno katika lugha moja na maneno ya lugha nyingine, ikiongeza mbinu za kuchagua njia sahihi za kutafsiri misemo au sehemu za sentensi wakati tafsiri ya neno kwa neno haifanyi maana.

> 🎓 Wakati watafsiri wanaposaidia kutafsiri kati ya lugha moja na nyingine, hizi hujulikana kama *jozi za lugha*. Zana tofauti zinaunga mkono jozi tofauti za lugha, na hizi zinaweza kuwa si kamili. Kwa mfano, mtafsiri anaweza kusaidia Kiingereza hadi Kihispania kama jozi ya lugha, na Kihispania hadi Kiitaliano kama jozi ya lugha, lakini si Kiingereza hadi Kiitaliano.

Kwa mfano, kutafsiri "Hello world" kutoka Kiingereza kwenda Kifaransa kunaweza kufanywa kwa mbadala - "Bonjour" kwa "Hello", na "le monde" kwa "world", na kusababisha tafsiri sahihi ya "Bonjour le monde".

Mbadala hazifanyi kazi wakati lugha tofauti zinatumia njia tofauti za kusema kitu kimoja. Kwa mfano, sentensi ya Kiingereza "My name is Jim", inatafsiriwa kuwa "Je m'appelle Jim" kwa Kifaransa - kwa maana halisi "Najiita Jim". "Je" ni Kifaransa kwa "I", "moi" ni mimi, lakini huunganishwa na kitenzi kwa kuwa huanza na vokali, hivyo inakuwa "m'", "appelle" ni kuita, na "Jim" haitafsiriwi kwa kuwa ni jina, na si neno linaloweza kutafsiriwa. Mpangilio wa maneno pia huwa tatizo - mbadala rahisi wa "Je m'appelle Jim" unakuwa "I myself call Jim", na mpangilio tofauti wa maneno kwa Kiingereza.

> 💁 Baadhi ya maneno hayatafsiriwi kamwe - jina langu ni Jim bila kujali lugha inayotumika kujitambulisha. Wakati wa kutafsiri kwa lugha zinazotumia alfabeti tofauti, au herufi tofauti kwa sauti tofauti, basi maneno yanaweza *kutamkwa kwa herufi*, yaani kuchagua herufi au alama zinazotoa sauti inayofanana na neno lililotolewa.

Misemo ya methali pia ni tatizo kwa tafsiri. Hizi ni misemo ambayo ina maana inayofahamika ambayo ni tofauti na tafsiri ya moja kwa moja ya maneno. Kwa mfano, kwa Kiingereza methali "I've got ants in my pants" hairejelei moja kwa moja kuwa na mchwa kwenye nguo zako, bali kuwa na wasiwasi. Ukitafsiri hii kwa Kijerumani, utamchanganya msikilizaji, kwa kuwa toleo la Kijerumani ni "I have bumble bees in the bottom".

> 💁 Maeneo tofauti huongeza changamoto tofauti. Kwa methali "ants in your pants", kwa Kiingereza cha Marekani "pants" inarejelea mavazi ya nje, kwa Kiingereza cha Uingereza, "pants" ni nguo za ndani.

✅ Ikiwa unazungumza lugha nyingi, fikiria baadhi ya misemo ambayo haiwezi kutafsiriwa moja kwa moja.

Mifumo ya tafsiri ya mashine hutegemea hifadhidata kubwa za sheria zinazofafanua jinsi ya kutafsiri misemo fulani na methali, pamoja na mbinu za takwimu za kuchagua tafsiri sahihi kutoka kwa chaguo zinazowezekana. Mbinu hizi za takwimu hutumia hifadhidata kubwa za kazi zilizotafsiriwa na binadamu kwa lugha nyingi kuchagua tafsiri inayowezekana zaidi, mbinu inayoitwa *tafsiri ya mashine ya takwimu*. Baadhi ya hizi hutumia uwakilishi wa kati wa lugha, kuruhusu lugha moja kutafsiriwa kwa kati, kisha kutoka kwa kati kwenda lugha nyingine. Kwa njia hii kuongeza lugha zaidi kunahusisha tafsiri kwa na kutoka kwa kati, si kwa na kutoka kwa lugha zote nyingine.

### Tafsiri za Neural

Tafsiri za neural zinahusisha kutumia nguvu ya AI kutafsiri, kwa kawaida kutafsiri sentensi nzima kwa kutumia mfano mmoja. Mifano hii hufunzwa kwa seti kubwa za data zilizotafsiriwa na binadamu, kama kurasa za wavuti, vitabu na nyaraka za Umoja wa Mataifa.

Mifano ya tafsiri ya neural kwa kawaida ni midogo kuliko mifano ya tafsiri ya mashine kwa sababu haihitaji hifadhidata kubwa za misemo na methali. Huduma za kisasa za AI zinazotoa tafsiri mara nyingi huchanganya mbinu nyingi, zikichanganya tafsiri ya mashine ya takwimu na tafsiri ya neural.

Hakuna tafsiri ya 1:1 kwa jozi yoyote ya lugha. Mifano tofauti ya tafsiri itatoa matokeo tofauti kidogo kulingana na data iliyotumika kufundisha mfano. Tafsiri si mara zote za kielelezo - yaani, ukitafsiri sentensi kutoka lugha moja kwenda nyingine, kisha kurudi kwa lugha ya kwanza unaweza kuona sentensi tofauti kidogo kama matokeo.

✅ Jaribu watafsiri tofauti mtandaoni kama [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com), au programu ya Apple Translate. Linganisha matoleo yaliyotafsiriwa ya sentensi chache. Pia jaribu kutafsiri kwa moja, kisha kutafsiri tena kwa nyingine.

## Huduma za Tafsiri

Kuna huduma kadhaa za AI ambazo zinaweza kutumika kutoka kwa programu zako kutafsiri sauti na maandishi.

### Huduma ya Sauti ya Cognitive Services

![Nembo ya huduma ya sauti](../../../../../translated_images/sw/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.png)

Huduma ya sauti ambayo umekuwa ukitumia katika masomo yaliyopita ina uwezo wa kutafsiri kwa utambuzi wa sauti. Unapotambua sauti, unaweza kuomba si tu maandishi ya sauti hiyo kwa lugha ile ile, bali pia kwa lugha nyingine.

> 💁 Hii inapatikana tu kutoka kwa SDK ya sauti, API ya REST haina tafsiri zilizojengwa ndani.

### Huduma ya Mtafsiri ya Cognitive Services

![Nembo ya huduma ya mtafsiri](../../../../../translated_images/sw/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.png)

Huduma ya Mtafsiri ni huduma maalum ya tafsiri inayoweza kutafsiri maandishi kutoka lugha moja kwenda lugha moja au zaidi za lengo. Mbali na kutafsiri, inasaidia vipengele vingi vya ziada ikiwa ni pamoja na kuficha matusi. Pia inakuruhusu kutoa tafsiri maalum kwa neno au sentensi fulani, kufanya kazi na maneno ambayo hutaki kutafsiriwa, au kuwa na tafsiri maalum inayojulikana.

Kwa mfano, wakati wa kutafsiri sentensi "I have a Raspberry Pi", ikimaanisha kompyuta ya bodi moja, kwenda lugha nyingine kama Kifaransa, ungependa kuweka jina "Raspberry Pi" kama lilivyo, na si kutafsiri, ukitoa "J’ai un Raspberry Pi" badala ya "J’ai une pi aux framboises".

## Unda Rasilimali ya Mtafsiri

Kwa somo hili utahitaji rasilimali ya Mtafsiri. Utatumia API ya REST kutafsiri maandishi.

### Kazi - unda rasilimali ya mtafsiri

1. Kutoka kwa terminal yako au command prompt, endesha amri ifuatayo kuunda rasilimali ya mtafsiri katika kikundi chako cha rasilimali `smart-timer`.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Badilisha `<location>` na eneo ulilotumia wakati wa kuunda Kikundi cha Rasilimali.

1. Pata ufunguo wa huduma ya mtafsiri:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Chukua nakala ya moja ya funguo.

## Kusaidia Lugha Nyingi Katika Programu kwa Tafsiri

Katika ulimwengu bora, programu yako yote inapaswa kuelewa lugha nyingi iwezekanavyo, kutoka kusikiliza sauti, kuelewa lugha, hadi kujibu kwa sauti. Hii ni kazi kubwa, kwa hivyo huduma za tafsiri zinaweza kuharakisha muda wa utoaji wa programu yako.

![Mimomemo ya kipima muda mahiri ikitafsiri Kijapani kwenda Kiingereza, kuchakata kwa Kiingereza kisha kutafsiri tena kwenda Kijapani](../../../../../translated_images/sw/translated-smart-timer.08ac20057fdc5c37.webp)

Fikiria unajenga kipima muda mahiri kinachotumia Kiingereza kutoka mwanzo hadi mwisho, kuelewa Kiingereza kilichozungumzwa na kukibadilisha kuwa maandishi, kuendesha uelewa wa lugha kwa Kiingereza, kuunda majibu kwa Kiingereza na kujibu kwa sauti ya Kiingereza. Ikiwa ungependa kuongeza msaada kwa Kijapani, ungeweza kuanza kwa kutafsiri Kijapani kilichozungumzwa kuwa maandishi ya Kiingereza, kisha kuweka msingi wa programu sawa, kisha kutafsiri maandishi ya majibu kwenda Kijapani kabla ya kuyazungumza. Hii ingeruhusu kuongeza msaada wa Kijapani haraka, na unaweza kupanua kutoa msaada kamili wa Kijapani baadaye.

> 💁 Hasara ya kutegemea tafsiri ya mashine ni kwamba lugha na tamaduni tofauti zina njia tofauti za kusema mambo sawa, kwa hivyo tafsiri inaweza isilingane na usemi unaotarajia.

Tafsiri za mashine pia hufungua uwezekano wa programu na vifaa vinavyoweza kutafsiri maudhui yaliyoundwa na watumiaji wakati yanaundwa. Sayansi ya kubuni mara kwa mara huonyesha 'watafsiri wa ulimwengu wote', vifaa vinavyoweza kutafsiri kutoka lugha za kigeni kwenda (kwa kawaida) Kiingereza cha Marekani. Vifaa hivi si sayansi ya kubuni, bali ni ukweli wa kisayansi, ukiondoa sehemu ya kigeni. Tayari kuna programu na vifaa vinavyotoa tafsiri ya papo hapo ya sauti na maandishi, kwa kutumia mchanganyiko wa huduma za sauti na tafsiri.

Mfano mmoja ni programu ya simu ya [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn), iliyoonyeshwa katika video hii:

[![Kipengele cha moja kwa moja cha Microsoft Translator kikifanya kazi](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Bonyeza picha hapo juu kutazama video

Fikiria kuwa na kifaa kama hicho kinachopatikana kwako, hasa unapokuwa safarini au unapoingiliana na watu ambao lugha yao huijui. Kuwa na vifaa vya tafsiri moja kwa moja katika viwanja vya ndege au hospitali kungeleta maboresho makubwa ya upatikanaji.

✅ Fanya utafiti: Je, kuna vifaa vyovyote vya IoT vya tafsiri vinavyopatikana kibiashara? Vipi kuhusu uwezo wa tafsiri uliojengwa ndani ya vifaa mahiri?

> 👽 Ingawa hakuna watafsiri wa kweli wa ulimwengu wote wanaoturuhusu kuzungumza na viumbe wa kigeni, [Microsoft Translator inasaidia lugha ya Klingon](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Tafsiri Maandishi kwa Kutumia Huduma ya AI

Unaweza kutumia huduma ya AI kuongeza uwezo huu wa tafsiri kwenye kipima muda chako mahiri.

### Kazi - tafsiri maandishi kwa kutumia huduma ya AI

Fanya kazi kupitia mwongozo husika kubadilisha tafsiri ya maandishi kwenye kifaa chako cha IoT:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)  
* [Kompyuta ya bodi moja - Raspberry Pi](pi-translate-speech.md)  
* [Kompyuta ya bodi moja - Kifaa cha Virtual](virtual-device-translate-speech.md)  

---

## 🚀 Changamoto

Tafsiri za mashine zinaweza kufaidisha vipi programu nyingine za IoT zaidi ya vifaa mahiri? Fikiria njia tofauti ambazo tafsiri zinaweza kusaidia, si tu kwa maneno yaliyosemwa bali pia kwa maandishi.

## Jaribio la Baada ya Somo

[Jaribio la baada ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Mapitio na Kujisomea

* Soma zaidi kuhusu tafsiri ya mashine kwenye [ukurasa wa tafsiri ya mashine kwenye Wikipedia](https://wikipedia.org/wiki/Machine_translation)  
* Soma zaidi kuhusu tafsiri ya mashine ya neural kwenye [ukurasa wa tafsiri ya mashine ya neural kwenye Wikipedia](https://wikipedia.org/wiki/Neural_machine_translation)  
* Angalia orodha ya lugha zinazoungwa mkono kwa huduma za sauti za Microsoft katika [msaada wa lugha na sauti kwa nyaraka za huduma ya sauti kwenye Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)  

## Kazi

[Jenga mtafsiri wa ulimwengu wote](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutokuelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.