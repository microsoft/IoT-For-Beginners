<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-27T23:39:42+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "tl"
}
-->
# Suportahan ang Maraming Wika

![Isang sketchnote overview ng araling ito](../../../../../translated_images/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.tl.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

Ang video na ito ay nagbibigay ng overview ng Azure speech services, kabilang ang speech to text at text to speech mula sa mga naunang aralin, pati na rin ang pagsasalin ng speech, isang paksa na tatalakayin sa araling ito:

[![Pagkilala sa speech gamit ang ilang linya ng Python mula sa Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 I-click ang imahe sa itaas upang panoorin ang video

## Pre-lecture Quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Panimula

Sa huling 3 aralin, natutunan mo ang tungkol sa pag-convert ng speech to text, pag-unawa sa wika, at pag-convert ng text to speech, lahat ay pinapagana ng AI. Isa pang aspeto ng komunikasyon ng tao na maaaring tulungan ng AI ay ang pagsasalin ng wika - pag-convert mula sa isang wika patungo sa iba, tulad ng mula Ingles patungo sa Pranses.

Sa araling ito, matutunan mo ang paggamit ng AI upang magsalin ng text, na magpapahintulot sa iyong smart timer na makipag-ugnayan sa mga user sa maraming wika.

Sa araling ito, tatalakayin natin:

* [Magsalin ng text](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Mga serbisyo ng pagsasalin](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Gumawa ng translator resource](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Suportahan ang maraming wika sa mga aplikasyon gamit ang pagsasalin](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Magsalin ng text gamit ang AI service](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Ito ang huling aralin sa proyektong ito, kaya pagkatapos makumpleto ang araling ito at ang assignment, huwag kalimutang linisin ang iyong cloud services. Kakailanganin mo ang mga serbisyo upang makumpleto ang assignment, kaya tiyaking tapusin muna ito.
>
> Sumangguni sa [ang gabay sa paglilinis ng iyong proyekto](../../../clean-up.md) kung kinakailangan para sa mga tagubilin kung paano ito gawin.

## Magsalin ng Text

Ang pagsasalin ng text ay isang problema sa computer science na pinag-aaralan nang higit sa 70 taon, at ngayon lamang, salamat sa mga pag-unlad sa AI at computer power, malapit nang malutas sa puntong halos kasing galing ng mga tagasalin na tao.

> 💁 Ang mga pinagmulan nito ay maaaring masubaybayan pa sa [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), isang cryptographer na Arabo noong ika-9 na siglo na bumuo ng mga teknik para sa pagsasalin ng wika.

### Mga Pagsasalin ng Makina

Ang pagsasalin ng text ay nagsimula bilang isang teknolohiya na kilala bilang Machine Translation (MT), na maaaring magsalin sa pagitan ng iba't ibang pares ng wika. Ang MT ay gumagana sa pamamagitan ng pagpapalit ng mga salita sa isang wika patungo sa iba, na may mga teknik upang piliin ang tamang paraan ng pagsasalin ng mga parirala o bahagi ng mga pangungusap kapag ang simpleng word-for-word na pagsasalin ay hindi makatuwiran.

> 🎓 Kapag ang mga tagasalin ay sumusuporta sa pagsasalin sa pagitan ng isang wika at iba pa, ang mga ito ay kilala bilang *language pairs*. Ang iba't ibang mga tool ay sumusuporta sa iba't ibang mga pares ng wika, at maaaring hindi ito kumpleto. Halimbawa, ang isang tagasalin ay maaaring sumuporta sa Ingles patungo sa Espanyol bilang isang pares ng wika, at Espanyol patungo sa Italyano bilang isang pares ng wika, ngunit hindi Ingles patungo sa Italyano.

Halimbawa, ang pagsasalin ng "Hello world" mula Ingles patungo sa Pranses ay maaaring gawin sa pamamagitan ng substitution - "Bonjour" para sa "Hello", at "le monde" para sa "world", na nagreresulta sa tamang pagsasalin na "Bonjour le monde".

Ang substitution ay hindi gumagana kapag ang iba't ibang wika ay gumagamit ng iba't ibang paraan ng pagsasabi ng parehong bagay. Halimbawa, ang pangungusap sa Ingles na "My name is Jim", ay isinasalin sa "Je m'appelle Jim" sa Pranses - literal na "I call myself Jim". Ang "Je" ay Pranses para sa "I", ang "moi" ay "me", ngunit pinagsama sa pandiwa dahil nagsisimula ito sa patinig, kaya nagiging "m'", ang "appelle" ay "to call", at ang "Jim" ay hindi isinasalin dahil ito ay isang pangalan, at hindi isang salitang maaaring isalin. Ang pagkakasunod-sunod ng mga salita ay nagiging isyu rin - ang simpleng substitution ng "Je m'appelle Jim" ay nagiging "I myself call Jim", na may ibang pagkakasunod-sunod ng mga salita kumpara sa Ingles.

> 💁 Ang ilang mga salita ay hindi kailanman isinasalin - ang pangalan ko ay Jim anuman ang wika na ginagamit upang ipakilala ako. Kapag nagsasalin sa mga wika na gumagamit ng iba't ibang alpabeto, o gumagamit ng iba't ibang mga letra para sa iba't ibang tunog, ang mga salita ay maaaring *transliterated*, ibig sabihin ay pumipili ng mga letra o karakter na nagbibigay ng tamang tunog upang magtunog katulad ng ibinigay na salita.

Ang mga idiom ay isa ring problema sa pagsasalin. Ito ay mga parirala na may nauunawaang kahulugan na iba sa direktang interpretasyon ng mga salita. Halimbawa, sa Ingles ang idiom na "I've got ants in my pants" ay hindi literal na tumutukoy sa pagkakaroon ng mga langgam sa iyong damit, ngunit sa pagiging balisa. Kung isasalin mo ito sa Aleman, malilito ang tagapakinig, dahil ang bersyon sa Aleman ay "I have bumble bees in the bottom".

> 💁 Ang iba't ibang mga lokalidad ay nagdaragdag ng iba't ibang mga komplikasyon. Sa idiom na "ants in your pants", sa American English ang "pants" ay tumutukoy sa panlabas na kasuotan, sa British English, ang "pants" ay panloob na kasuotan.

✅ Kung marunong kang magsalita ng maraming wika, mag-isip ng ilang mga parirala na hindi direktang maisasalin.

Ang mga sistema ng machine translation ay umaasa sa malalaking database ng mga panuntunan na naglalarawan kung paano isalin ang ilang mga parirala at idiom, kasama ang mga pamamaraang estadistikal upang piliin ang naaangkop na mga pagsasalin mula sa mga posibleng opsyon. Ang mga pamamaraang estadistikal na ito ay gumagamit ng malalaking database ng mga gawaing isinalin ng tao sa maraming wika upang piliin ang pinaka-malamang na pagsasalin, isang teknik na tinatawag na *statistical machine translation*. Ang ilan sa mga ito ay gumagamit ng intermediate na representasyon ng wika, na nagpapahintulot sa isang wika na isalin sa intermediate, pagkatapos mula sa intermediate patungo sa isa pang wika. Sa ganitong paraan, ang pagdaragdag ng higit pang mga wika ay kinabibilangan ng mga pagsasalin sa at mula sa intermediate, hindi sa at mula sa lahat ng iba pang mga wika.

### Mga Pagsasalin ng Neural

Ang mga pagsasalin ng neural ay gumagamit ng kapangyarihan ng AI upang magsalin, karaniwang isinasalin ang buong pangungusap gamit ang isang modelo. Ang mga modelong ito ay sinasanay sa malalaking data set na isinalin ng tao, tulad ng mga web page, libro, at dokumentasyon ng United Nations.

Ang mga neural translation model ay karaniwang mas maliit kaysa sa mga machine translation model dahil hindi nangangailangan ng malalaking database ng mga parirala at idiom. Ang mga modernong AI service na nagbibigay ng pagsasalin ay madalas na naghahalo ng maraming teknik, pinagsasama ang statistical machine translation at neural translation.

Walang 1:1 na pagsasalin para sa anumang pares ng wika. Ang iba't ibang mga modelo ng pagsasalin ay magbibigay ng bahagyang magkakaibang resulta depende sa data na ginamit upang sanayin ang modelo. Ang mga pagsasalin ay hindi palaging simetriko - sa paraang kung isasalin mo ang isang pangungusap mula sa isang wika patungo sa isa pa, pagkatapos ay pabalik sa unang wika, maaari kang makakita ng bahagyang naiibang pangungusap bilang resulta.

✅ Subukan ang iba't ibang online translator tulad ng [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com), o ang Apple translate app. Ihambing ang mga bersyon ng pagsasalin ng ilang pangungusap. Subukan din ang pagsasalin sa isa, pagkatapos ay pagsasalin pabalik sa isa pa.

## Mga Serbisyo ng Pagsasalin

Mayroong ilang mga AI service na maaaring gamitin mula sa iyong mga aplikasyon upang magsalin ng speech at text.

### Cognitive Services Speech Service

![Ang speech service logo](../../../../../translated_images/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.tl.png)

Ang speech service na ginagamit mo sa nakaraang mga aralin ay may kakayahan sa pagsasalin para sa speech recognition. Kapag kinikilala mo ang speech, maaari kang humiling hindi lamang ng text ng speech sa parehong wika, kundi pati na rin sa ibang mga wika.

> 💁 Ito ay magagamit lamang mula sa speech SDK, ang REST API ay walang built-in na pagsasalin.

### Cognitive Services Translator Service

![Ang translator service logo](../../../../../translated_images/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.tl.png)

Ang Translator service ay isang dedikadong serbisyo ng pagsasalin na maaaring magsalin ng text mula sa isang wika, patungo sa isa o higit pang target na wika. Bukod sa pagsasalin, sinusuportahan nito ang malawak na hanay ng mga karagdagang tampok kabilang ang masking ng profanity. Pinapayagan ka rin nitong magbigay ng partikular na pagsasalin para sa isang partikular na salita o pangungusap, upang magtrabaho sa mga termino na hindi mo nais isalin, o magkaroon ng partikular na kilalang pagsasalin.

Halimbawa, kapag isinasalin ang pangungusap na "I have a Raspberry Pi", na tumutukoy sa single-board computer, sa ibang wika tulad ng Pranses, nais mong panatilihin ang pangalan na "Raspberry Pi" na hindi isinalin, na nagbibigay ng "J’ai un Raspberry Pi" sa halip na "J’ai une pi aux framboises".

## Gumawa ng Translator Resource

Para sa araling ito, kakailanganin mo ng Translator resource. Gagamitin mo ang REST API upang magsalin ng text.

### Gawain - Gumawa ng Translator Resource

1. Mula sa iyong terminal o command prompt, patakbuhin ang sumusunod na command upang gumawa ng translator resource sa iyong `smart-timer` resource group.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Palitan ang `<location>` ng lokasyon na ginamit mo noong gumawa ng Resource Group.

1. Kunin ang key para sa translator service:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Kopyahin ang isa sa mga key.

## Suportahan ang Maraming Wika sa mga Aplikasyon gamit ang Pagsasalin

Sa isang ideal na mundo, ang buong aplikasyon mo ay dapat makaunawa ng maraming iba't ibang wika hangga't maaari, mula sa pakikinig sa speech, sa pag-unawa sa wika, hanggang sa pagsagot gamit ang speech. Ito ay maraming trabaho, kaya ang mga serbisyo ng pagsasalin ay maaaring pabilisin ang oras ng pag-deliver ng iyong aplikasyon.

![Isang smart timer architecture na nagsasalin ng Japanese patungo sa English, nagpoproseso sa English pagkatapos ay nagsasalin pabalik sa Japanese](../../../../../translated_images/translated-smart-timer.08ac20057fdc5c3778ed41cb425dca5d7fbcd4584b6da7b73ca67115a5b8a883.tl.png)

Isipin na gumagawa ka ng smart timer na gumagamit ng English end-to-end, nauunawaan ang sinasalitang English at kino-convert ito sa text, pinapatakbo ang pag-unawa sa wika sa English, bumubuo ng mga sagot sa English, at sumasagot gamit ang English speech. Kung nais mong magdagdag ng suporta para sa Japanese, maaari kang magsimula sa pagsasalin ng sinasalitang Japanese patungo sa English text, pagkatapos ay panatilihin ang core ng aplikasyon na pareho, pagkatapos ay isalin ang response text sa Japanese bago magsalita ng sagot. Papayagan ka nitong mabilis na magdagdag ng suporta para sa Japanese, at maaari kang mag-expand upang magbigay ng full end-to-end na suporta para sa Japanese sa hinaharap.

> 💁 Ang downside ng pag-asa sa machine translation ay ang iba't ibang wika at kultura ay may iba't ibang paraan ng pagsasabi ng parehong bagay, kaya ang pagsasalin ay maaaring hindi tumugma sa ekspresyon na inaasahan mo.

Ang mga machine translation ay nagbubukas din ng mga posibilidad para sa mga app at device na maaaring magsalin ng user-created content habang ito ay ginagawa. Ang science fiction ay regular na nagtatampok ng 'universal translators', mga device na maaaring magsalin mula sa mga alien na wika patungo sa (karaniwang) American English. Ang mga device na ito ay mas science fact kaysa science fiction, kung hindi mo isasama ang bahagi ng alien. Mayroon nang mga app at device na nagbibigay ng real-time na pagsasalin ng speech at nakasulat na text, gamit ang kombinasyon ng speech at translation services.

Isang halimbawa ay ang [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn) mobile phone app, na ipinakita sa video na ito:

[![Microsoft Translator live feature in action](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 I-click ang imahe sa itaas upang panoorin ang video

Isipin na may ganitong device na magagamit mo, lalo na kapag naglalakbay o nakikipag-ugnayan sa mga tao na ang wika ay hindi mo alam. Ang pagkakaroon ng mga automatic translation device sa mga paliparan o ospital ay magbibigay ng kinakailangang accessibility improvements.

✅ Mag-research: Mayroon bang mga translation IoT device na komersyal na magagamit? Paano naman ang mga kakayahan sa pagsasalin na naka-built in sa mga smart device?

> 👽 Bagaman walang tunay na universal translators na nagpapahintulot sa atin na makipag-usap sa mga alien, ang [Microsoft translator ay sumusuporta sa Klingon](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Magsalin ng Text gamit ang AI Service

Maaari mong gamitin ang AI service upang idagdag ang kakayahan sa pagsasalin sa iyong smart timer.

### Gawain - Magsalin ng Text gamit ang AI Service

Sundin ang kaukulang gabay upang magsalin ng text sa iyong IoT device:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Single-board computer - Raspberry Pi](pi-translate-speech.md)
* [Single-board computer - Virtual device](virtual-device-translate-speech.md)

---

## 🚀 Hamon

Paano makikinabang ang machine translations sa iba pang IoT applications bukod sa mga smart device? Mag-isip ng iba't ibang paraan kung paano makakatulong ang pagsasalin, hindi lamang sa sinasalitang salita kundi pati na rin sa text.

## Post-lecture Quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Review & Self Study

* Magbasa pa tungkol sa machine translation sa [machine translation page sa Wikipedia](https://wikipedia.org/wiki/Machine_translation)
* Magbasa pa tungkol sa neural machine translation sa [neural machine translation page sa Wikipedia](https://wikipedia.org/wiki/Neural_machine_translation)
* Tingnan ang listahan ng mga suportadong wika para sa Microsoft speech services sa [language and voice support para sa Speech service documentation sa Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Assignment

[Gumawa ng universal translator](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa orihinal nitong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.