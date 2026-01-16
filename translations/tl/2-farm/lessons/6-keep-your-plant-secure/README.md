<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "81c437c568eee1b0dda1f04e88150d37",
  "translation_date": "2025-08-27T22:09:37+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/README.md",
  "language_code": "tl"
}
-->
# Panatilihing Ligtas ang Iyong Halaman

![Isang sketchnote overview ng araling ito](../../../../../translated_images/tl/lesson-10.829c86b80b9403bb770929ee553a1d293afe50dc23121aaf9be144673ae012cc.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

## Pre-lecture Quiz

[Pre-lecture Quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Panimula

Sa mga nakaraang aralin, nakagawa ka ng IoT device para sa pagsubaybay sa lupa at naikonekta ito sa cloud. Ngunit paano kung ang mga hacker na nagtatrabaho para sa isang karibal na magsasaka ay nakontrol ang iyong mga IoT device? Paano kung magpadala sila ng mataas na soil moisture readings upang hindi kailanman madiligan ang iyong mga halaman, o buksan ang iyong sistema ng patubig nang tuluy-tuloy, na magdudulot ng sobrang pagdidilig at magastos sa tubig?

Sa araling ito, matututunan mo ang tungkol sa pag-secure ng mga IoT device. Dahil ito ang huling aralin para sa proyektong ito, matututunan mo rin kung paano linisin ang iyong mga cloud resources upang mabawasan ang mga posibleng gastos.

Sa araling ito, tatalakayin natin:

* [Bakit kailangan mong i-secure ang mga IoT device?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Cryptography](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [I-secure ang iyong mga IoT device](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Gumawa at gumamit ng X.509 certificate](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 Ito ang huling aralin sa proyektong ito, kaya pagkatapos makumpleto ang aralin at ang assignment, huwag kalimutang linisin ang iyong mga cloud services. Kakailanganin mo ang mga serbisyo upang makumpleto ang assignment, kaya tiyaking tapusin muna ito.
>
> Sumangguni sa [ang gabay sa paglilinis ng iyong proyekto](../../../clean-up.md) kung kinakailangan para sa mga tagubilin kung paano ito gawin.

## Bakit kailangan mong i-secure ang mga IoT device?

Ang seguridad ng IoT ay nangangahulugan ng pagtiyak na ang mga inaasahang device lamang ang maaaring kumonekta sa iyong cloud IoT service at magpadala ng telemetry, at ang iyong cloud service lamang ang maaaring magpadala ng mga utos sa iyong mga device. Ang data ng IoT ay maaari ring maging personal, kabilang ang medikal o sensitibong data, kaya ang buong aplikasyon mo ay kailangang isaalang-alang ang seguridad upang maiwasan ang pagtagas ng data na ito.

Kung ang iyong IoT application ay hindi secure, may ilang mga panganib:

* Ang isang pekeng device ay maaaring magpadala ng maling data, na magdudulot ng maling tugon ng iyong aplikasyon. Halimbawa, maaari silang magpadala ng patuloy na mataas na soil moisture readings, na nangangahulugang hindi kailanman magbubukas ang iyong sistema ng patubig at mamamatay ang iyong mga halaman dahil sa kakulangan ng tubig.
* Ang mga hindi awtorisadong user ay maaaring magbasa ng data mula sa mga IoT device, kabilang ang personal o kritikal na data ng negosyo.
* Ang mga hacker ay maaaring magpadala ng mga utos upang kontrolin ang isang device sa paraang maaaring makapinsala sa device o sa mga konektadong hardware.
* Sa pamamagitan ng pagkonekta sa isang IoT device, maaaring gamitin ito ng mga hacker upang ma-access ang karagdagang mga network at makakuha ng access sa mga pribadong sistema.
* Ang mga malisyosong user ay maaaring ma-access ang personal na data at gamitin ito para sa pananakot.

Ito ay mga totoong sitwasyon at nangyayari sa lahat ng oras. Ang ilang mga halimbawa ay ibinigay sa mga naunang aralin, ngunit narito ang ilan pa:

* Noong 2018, ginamit ng mga hacker ang isang open WiFi access point sa isang thermostat ng fish tank upang makakuha ng access sa network ng isang casino at magnakaw ng data. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* Noong 2016, inilunsad ng Mirai Botnet ang isang denial of service attack laban sa Dyn, isang Internet service provider, na nagdulot ng pagbagsak ng malaking bahagi ng Internet. Ginamit ng botnet na ito ang malware upang kumonekta sa mga IoT device tulad ng DVRs at mga camera na gumagamit ng default usernames at passwords, at mula doon inilunsad ang pag-atake. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Ang Spiral Toys ay may database ng mga user ng kanilang CloudPets connected toys na pampublikong available sa Internet. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Ang Strava ay nag-tag ng mga runner na nadaanan mo at ipinakita ang kanilang mga ruta, na nagpapahintulot sa mga estranghero na makita kung saan ka nakatira. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Mag-research: Maghanap ng higit pang mga halimbawa ng IoT Hacks at paglabag sa data ng IoT, lalo na sa mga personal na item tulad ng Internet-connected toothbrushes o scales. Pag-isipan ang epekto ng mga hack na ito sa mga biktima o customer.

> 💁 Ang seguridad ay isang napakalaking paksa, at ang araling ito ay tatalakayin lamang ang ilan sa mga pangunahing kaalaman sa pagkonekta ng iyong device sa cloud. Ang iba pang mga paksa na hindi saklaw ay kinabibilangan ng pagsubaybay sa mga pagbabago sa data habang nasa transit, pag-hack ng mga device nang direkta, o mga pagbabago sa mga configuration ng device. Ang IoT hacking ay isang malaking banta, kaya't ang mga tool tulad ng [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn) ay binuo. Ang mga tool na ito ay katulad ng mga anti-virus at security tools na maaaring mayroon ka sa iyong computer, ngunit idinisenyo para sa maliliit, mababang power na IoT device.

## Cryptography

Kapag kumonekta ang isang device sa isang IoT service, gumagamit ito ng ID upang kilalanin ang sarili nito. Ang problema ay ang ID na ito ay maaaring kopyahin - maaaring mag-set up ang isang hacker ng malisyosong device na gumagamit ng parehong ID ng isang tunay na device ngunit nagpapadala ng maling data.

![Parehong valid at malisyosong device ay maaaring gumamit ng parehong ID upang magpadala ng telemetry](../../../../../translated_images/tl/iot-device-and-hacked-device-connecting.e0671675df74d6d99eb1dedb5a670e606f698efa6202b1ad4c8ae548db299cc6.png)

Ang solusyon dito ay ang pag-convert ng data na ipinapadala sa isang scrambled na format, gamit ang isang halaga na kilala lamang ng device at ng cloud. Ang prosesong ito ay tinatawag na *encryption*, at ang halaga na ginamit upang i-encrypt ang data ay tinatawag na *encryption key*.

![Kung gagamit ng encryption, tanging mga encrypted na mensahe lamang ang tatanggapin, ang iba ay tatanggihan](../../../../../translated_images/tl/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f979e46f2849b573564eeb4a4dc5b52f669f62745397492fb.png)

Ang cloud service ay maaaring i-convert ang data pabalik sa nababasang format, gamit ang isang proseso na tinatawag na *decryption*, gamit ang parehong encryption key, o isang *decryption key*. Kung ang encrypted na mensahe ay hindi ma-decrypt ng key, ang device ay na-hack at ang mensahe ay tatanggihan.

Ang teknolohiya para sa paggawa ng encryption at decryption ay tinatawag na *cryptography*.

### Maagang Cryptography

Ang pinakaunang uri ng cryptography ay ang substitution ciphers, na nagsimula 3,500 taon na ang nakalipas. Ang substitution ciphers ay nagsasangkot ng pagpapalit ng isang letra sa iba. Halimbawa, ang [Caesar cipher](https://wikipedia.org/wiki/Caesar_cipher) ay nagsasangkot ng pag-shift ng alpabeto sa isang tinukoy na dami, kung saan ang nagpadala ng encrypted na mensahe at ang intended recipient lamang ang nakakaalam kung ilang letra ang i-shift.

Ang [Vigenère cipher](https://wikipedia.org/wiki/Vigenère_cipher) ay nagpaunlad pa nito sa pamamagitan ng paggamit ng mga salita upang i-encrypt ang teksto, upang ang bawat letra sa orihinal na teksto ay ma-shift sa iba't ibang dami, sa halip na palaging i-shift sa parehong bilang ng mga letra.

Ang cryptography ay ginamit para sa iba't ibang layunin, tulad ng pagprotekta sa recipe ng glaze ng palayok sa sinaunang Mesopotamia, pagsusulat ng mga lihim na love notes sa India, o pagpapanatili ng mga sinaunang Egyptian na mahika na lihim.

### Modernong Cryptography

Ang modernong cryptography ay mas advanced, na ginagawang mas mahirap i-crack kaysa sa mga maagang pamamaraan. Ang modernong cryptography ay gumagamit ng komplikadong matematika upang i-encrypt ang data na may napakaraming posibleng keys upang gawing imposible ang brute force attacks.

Ang cryptography ay ginagamit sa maraming iba't ibang paraan para sa secure na komunikasyon. Kung binabasa mo ang pahinang ito sa GitHub, maaaring mapansin mo na ang web site address ay nagsisimula sa *HTTPS*, na nangangahulugang ang komunikasyon sa pagitan ng iyong browser at ng mga web server ng GitHub ay naka-encrypt. Kung may makakabasa ng internet traffic na dumadaloy sa pagitan ng iyong browser at GitHub, hindi nila mababasa ang data dahil ito ay naka-encrypt. Ang iyong computer ay maaaring i-encrypt pa ang lahat ng data sa iyong hard drive upang kung may magnakaw nito, hindi nila mababasa ang anumang data nang walang iyong password.

> 🎓 Ang HTTPS ay nangangahulugang HyperText Transfer Protocol **Secure**

Sa kasamaang palad, hindi lahat ay secure. Ang ilang mga device ay walang seguridad, ang iba ay secured gamit ang madaling i-crack na keys, o minsan kahit lahat ng device ng parehong uri ay gumagamit ng parehong key. May mga ulat ng napaka-personal na IoT device na lahat ay may parehong password upang kumonekta sa kanila sa WiFi o Bluetooth. Kung maaari kang kumonekta sa iyong sariling device, maaari kang kumonekta sa device ng iba. Kapag nakakonekta, maaari kang makakuha ng access sa napaka-pribadong data, o magkaroon ng kontrol sa kanilang device.

> 💁 Sa kabila ng mga komplikasyon ng modernong cryptography at ang mga claim na ang pag-crack ng encryption ay maaaring tumagal ng bilyong taon, ang pag-usbong ng quantum computing ay nagdulot ng posibilidad na ma-crack ang lahat ng kilalang encryption sa napakaikling panahon!

### Symmetric at Asymmetric Keys

Ang encryption ay may dalawang uri - symmetric at asymmetric.

**Symmetric** encryption ay gumagamit ng parehong key upang i-encrypt at i-decrypt ang data. Parehong kailangang malaman ng sender at receiver ang parehong key. Ito ang hindi gaanong secure na uri, dahil ang key ay kailangang maibahagi sa kung anumang paraan. Para sa sender na magpadala ng encrypted na mensahe sa recipient, maaaring kailangang ipadala muna ng sender ang key sa recipient.

![Ang symmetric key encryption ay gumagamit ng parehong key upang i-encrypt at i-decrypt ang mensahe](../../../../../translated_images/tl/send-message-symmetric-key.a2e8ad0d495896ff.webp)

Kung ang key ay nanakaw habang nasa transit, o ang sender o recipient ay na-hack at nahanap ang key, maaaring ma-crack ang encryption.

![Ang symmetric key encryption ay secure lamang kung hindi makuha ng hacker ang key - kung makuha nila, maaari nilang i-intercept at i-decrypt ang mensahe](../../../../../translated_images/tl/send-message-symmetric-key-hacker.e7cb53db1707adfb.webp)

**Asymmetric** encryption ay gumagamit ng 2 keys - isang encryption key at isang decryption key, na tinutukoy bilang public/private key pair. Ang public key ay ginagamit upang i-encrypt ang mensahe, ngunit hindi maaaring gamitin upang i-decrypt ito, ang private key ay ginagamit upang i-decrypt ang mensahe ngunit hindi maaaring gamitin upang i-encrypt ito.

![Ang asymmetric encryption ay gumagamit ng magkaibang key upang i-encrypt at i-decrypt. Ang encryption key ay ipinapadala sa mga sender ng mensahe upang ma-encrypt nila ang mensahe bago ito ipadala sa recipient na may-ari ng mga keys](../../../../../translated_images/tl/send-message-asymmetric.7abe327c62615b8c.webp)

Ibinabahagi ng recipient ang kanilang public key, at ginagamit ito ng sender upang i-encrypt ang mensahe. Kapag naipadala na ang mensahe, i-decrypt ito ng recipient gamit ang kanilang private key. Ang asymmetric encryption ay mas secure dahil ang private key ay pinapanatiling pribado ng recipient at hindi kailanman ibinabahagi. Ang public key ay maaaring ibigay sa kahit sino dahil maaari lamang itong gamitin upang i-encrypt ang mga mensahe.

Ang symmetric encryption ay mas mabilis kaysa sa asymmetric encryption, ngunit ang asymmetric ay mas secure. Ang ilang mga sistema ay gumagamit ng pareho - gumagamit ng asymmetric encryption upang i-encrypt at ibahagi ang symmetric key, pagkatapos ay gumagamit ng symmetric key upang i-encrypt ang lahat ng data. Ginagawa nitong mas secure ang pagbabahagi ng symmetric key sa pagitan ng sender at recipient, at mas mabilis kapag nag-e-encrypt at nag-de-decrypt ng data.

## I-secure ang Iyong mga IoT Device

Ang mga IoT device ay maaaring ma-secure gamit ang symmetric o asymmetric encryption. Ang symmetric ay mas madali, ngunit hindi gaanong secure.

### Symmetric Keys

Kapag na-set up mo ang iyong IoT device upang makipag-ugnayan sa IoT Hub, gumamit ka ng connection string. Isang halimbawa ng connection string ay:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Ang connection string na ito ay binubuo ng tatlong bahagi na pinaghihiwalay ng semi-colons, kung saan ang bawat bahagi ay isang key at isang value:

| Key | Value | Deskripsyon |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | Ang URL ng IoT Hub |
| DeviceId | `soil-moisture-sensor` | Ang natatanging ID ng device |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | Isang symmetric key na kilala ng device at ng IoT Hub |

Ang huling bahagi ng connection string na ito, ang `SharedAccessKey`, ay ang symmetric key na kilala ng parehong device at ng IoT Hub. Ang key na ito ay hindi kailanman ipinapadala mula sa device papunta sa cloud, o mula sa cloud papunta sa device. Sa halip, ginagamit ito upang i-encrypt ang data na ipinapadala o natatanggap.

✅ Gumawa ng eksperimento. Ano sa tingin mo ang mangyayari kung babaguhin mo ang bahagi ng `SharedAccessKey` ng connection string kapag kumokonekta ang iyong IoT device? Subukan ito.

Kapag unang sinubukan ng device na kumonekta, nagpapadala ito ng shared access signature (SAS) token na binubuo ng URL ng IoT Hub, isang timestamp kung kailan mag-e-expire ang access signature (karaniwang 1 araw mula sa kasalukuyang oras), at isang signature. Ang signature na ito ay binubuo ng URL at ng expiry time na naka-encrypt gamit ang shared access key mula sa connection string.

I-decrypt ng IoT Hub ang signature na ito gamit ang shared access key, at kung ang decrypted value ay tumutugma sa URL at expiry, papayagan ang device na kumonekta. Tinitiyak din nito na ang kasalukuyang oras ay bago ang expiry, upang maiwasan ang isang malisyosong device na makuha ang SAS token ng isang tunay na device at gamitin ito.

Ito ay isang eleganteng paraan upang i-verify na ang sender ay ang tamang device. Sa pamamagitan ng pagpapadala ng ilang kilalang data sa parehong decrypted at encrypted na anyo, maaaring i-verify ng server ang device sa pamamagitan ng pagtiyak na kapag na-decrypt nito ang encrypted na data, ang resulta ay tumutugma sa decrypted na bersyon na ipinadala. Kung tumutugma, nangangahulugan ito na parehong may symmetric encryption key ang sender at recipient.
💁 Dahil sa oras ng pag-expire, kailangang malaman ng iyong IoT device ang tamang oras, na karaniwang kinukuha mula sa isang [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) server. Kung hindi tama ang oras, mabibigo ang koneksyon.
Pagkatapos ng koneksyon, lahat ng datos na ipinadala sa IoT Hub mula sa device, o sa device mula sa IoT Hub ay mai-encrypt gamit ang shared access key.

✅ Ano sa tingin mo ang mangyayari kung maraming device ang gumagamit ng parehong connection string?

> 💁 Hindi magandang security practice ang pag-iimbak ng key na ito sa code. Kung makuha ng hacker ang iyong source code, makukuha rin nila ang iyong key. Mas mahirap din ito kapag nagre-release ng code dahil kailangan mong i-recompile gamit ang updated na key para sa bawat device. Mas mainam na i-load ang key na ito mula sa hardware security module - isang chip sa IoT device na nag-iimbak ng encrypted values na mababasa ng iyong code.
>
> Kapag nag-aaral ng IoT, mas madali kadalasan na ilagay ang key sa code, tulad ng ginawa mo sa naunang aralin, ngunit dapat mong tiyakin na ang key na ito ay hindi ma-check in sa public source code control.

Ang mga device ay may 2 key, at 2 kaukulang connection string. Pinapayagan nito ang pag-rotate ng mga key - ibig sabihin, magpalit mula sa isang key patungo sa isa pa kung sakaling ma-kompromiso ang una, at muling i-generate ang unang key.

### X.509 certificates

Kapag gumagamit ka ng asymmetric encryption gamit ang public/private key pair, kailangan mong ibigay ang iyong public key sa sinumang nais magpadala sa iyo ng datos. Ang problema ay, paano masisiguro ng tatanggap ng iyong key na ito talaga ang iyong public key, at hindi ng ibang tao na nagpapanggap na ikaw? Sa halip na magbigay ng key, maaari kang magbigay ng iyong public key sa loob ng isang certificate na na-verify ng isang pinagkakatiwalaang third party, na tinatawag na X.509 certificate.

Ang X.509 certificates ay mga digital na dokumento na naglalaman ng public key na bahagi ng public/private key pair. Karaniwang ini-issue ito ng isa sa maraming pinagkakatiwalaang organisasyon na tinatawag na [Certification authorities](https://wikipedia.org/wiki/Certificate_authority) (CAs), at digitally signed ng CA upang ipakita na ang key ay valid at galing sa iyo. Pinagkakatiwalaan mo ang certificate at ang public key na galing sa kung sino ang sinasabi ng certificate dahil pinagkakatiwalaan mo ang CA, katulad ng pagtitiwala mo sa passport o lisensya sa pagmamaneho dahil pinagkakatiwalaan mo ang bansang nag-issue nito. Ang mga certificate ay may bayad, kaya maaari ka ring 'self-sign', ibig sabihin gumawa ng certificate na ikaw mismo ang nag-sign, para sa testing purposes.

> 💁 Huwag kailanman gumamit ng self-signed certificate para sa production release.

Ang mga certificate na ito ay may iba't ibang fields, kabilang ang kung sino ang may-ari ng public key, ang detalye ng CA na nag-issue nito, kung gaano katagal ito valid, at ang public key mismo. Bago gamitin ang certificate, magandang practice na i-verify ito sa pamamagitan ng pag-check kung ito ay na-sign ng original CA.

✅ Maaari mong basahin ang kumpletong listahan ng mga fields sa certificate sa [Microsoft Understanding X.509 Public Key Certificates tutorial](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields)

Kapag gumagamit ng X.509 certificates, parehong ang sender at ang recipient ay magkakaroon ng kanilang sariling public at private keys, pati na rin ang X.509 certificates na naglalaman ng public key. Magpapalitan sila ng X.509 certificates sa anumang paraan, gamit ang public key ng isa't isa upang i-encrypt ang datos na kanilang ipinapadala, at ang kanilang sariling private key upang i-decrypt ang datos na kanilang natatanggap.

![Sa halip na magbahagi ng public key, maaari kang magbahagi ng certificate. Maaaring i-verify ng user ng certificate na ito ay galing sa iyo sa pamamagitan ng pag-check sa certificate authority na nag-sign nito.](../../../../../translated_images/tl/send-message-certificate.9cc576ac1e46b76e.webp)

Isang malaking bentahe ng paggamit ng X.509 certificates ay maaari itong ibahagi sa pagitan ng mga device. Maaari kang gumawa ng isang certificate, i-upload ito sa IoT Hub, at gamitin ito para sa lahat ng iyong device. Ang bawat device ay kailangan lamang malaman ang private key upang i-decrypt ang mga mensaheng natatanggap nito mula sa IoT Hub.

Ang certificate na ginagamit ng iyong device upang i-encrypt ang mga mensaheng ipinapadala nito sa IoT Hub ay inilathala ng Microsoft. Ito ang parehong certificate na ginagamit ng maraming Azure services, at minsan ay built-in sa mga SDKs.

> 💁 Tandaan, ang public key ay pampubliko. Ang Azure public key ay maaari lamang gamitin upang i-encrypt ang datos na ipinapadala sa Azure, hindi upang i-decrypt ito, kaya maaari itong ibahagi kahit saan, kabilang sa source code. Halimbawa, makikita mo ito sa [Azure IoT C SDK source code](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c).

✅ Maraming jargon sa X.509 certificates. Maaari mong basahin ang mga kahulugan ng ilang mga terminong maaaring makaharap mo sa [The layman’s guide to X.509 certificate jargon](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn)

## Gumawa at gumamit ng X.509 certificate

Ang mga hakbang upang gumawa ng X.509 certificate ay:

1. Gumawa ng public/private key pair. Isa sa mga pinakalaganap na algorithm upang gumawa ng public/private key pair ay tinatawag na [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem))(RSA).

1. I-submit ang public key kasama ang kaukulang datos para sa signing, alinman sa pamamagitan ng CA, o sa pamamagitan ng self-signing.

Ang Azure CLI ay may mga command upang gumawa ng bagong device identity sa IoT Hub, at awtomatikong gumawa ng public/private key pair at gumawa ng self-signed certificate.

> 💁 Kung nais mong makita ang mga hakbang nang detalyado, sa halip na gamitin ang Azure CLI, maaari mo itong makita sa [Using OpenSSL to create self-signed certificates tutorial in the Microsoft IoT Hub documentation](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn)

### Gawain - gumawa ng device identity gamit ang X.509 certificate

1. Patakbuhin ang sumusunod na command upang irehistro ang bagong device identity, awtomatikong gumagawa ng mga keys at certificates:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Palitan ang `<hub_name>` ng pangalan na ginamit mo para sa iyong IoT Hub.

    Ito ay gagawa ng device na may ID na `soil-moisture-sensor-x509` upang maiba mula sa device identity na ginawa mo sa nakaraang aralin. Ang command na ito ay gagawa rin ng 2 files sa kasalukuyang directory:

    * `soil-moisture-sensor-x509-key.pem` - ang file na ito ay naglalaman ng private key para sa device.
    * `soil-moisture-sensor-x509-cert.pem` - ito ang X.509 certificate file para sa device.

    Panatilihing ligtas ang mga file na ito! Ang private key file ay hindi dapat ma-check in sa public source code control.

### Gawain - gamitin ang X.509 certificate sa iyong device code

Sundan ang kaukulang gabay upang ikonekta ang iyong IoT device sa cloud gamit ang X.509 certificate:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-x509.md)

---

## 🚀 Hamon

Mayroong iba't ibang paraan upang gumawa, mag-manage, at mag-delete ng Azure services tulad ng Resource Groups at IoT Hubs. Isa sa mga paraan ay ang [Azure Portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) - isang web-based interface na nagbibigay ng GUI upang mag-manage ng iyong Azure services.

Pumunta sa [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) at suriin ang portal. Subukang gumawa ng IoT Hub gamit ang portal, pagkatapos ay i-delete ito.

**Pahiwatig** - kapag gumagawa ng services sa pamamagitan ng portal, hindi mo kailangang gumawa ng Resource Group nang maaga, maaaring gumawa ng isa habang gumagawa ng service. Siguraduhing i-delete ito kapag tapos ka na!

Makakahanap ka ng maraming dokumentasyon, tutorials, at gabay tungkol sa Azure Portal sa [Azure portal documentation](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Review & Self Study

* Basahin ang kasaysayan ng cryptography sa [History of cryptography page on Wikipedia](https://wikipedia.org/wiki/History_of_cryptography).
* Basahin ang tungkol sa X.509 certificates sa [X.509 page on Wikipedia](https://wikipedia.org/wiki/X.509).

## Assignment

[Gumawa ng bagong IoT device](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.