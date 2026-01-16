<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-27T21:25:49+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "fi"
}
-->
# Kalibroi anturisi

## Ohjeet

Tässä osiossa keräsit maankosteusanturin lukemia, jotka mitataan arvoina välillä 0–1023. Jotta voit muuntaa nämä todellisiksi maankosteuslukemiksi, sinun täytyy kalibroida anturisi. Tämä tapahtuu ottamalla lukemia maaperänäytteistä ja laskemalla näytteistä gravimetrinen maankosteuspitoisuus.

Sinun täytyy toistaa nämä vaiheet useita kertoja saadaksesi tarvittavat lukemat, käyttäen joka kerta eri kosteustasoa maaperässä.

1. Ota maankosteuslukema maankosteusanturilla. Kirjoita tämä lukema ylös.

1. Ota maaperänäyte ja punnitse se. Kirjoita tämä paino ylös.

1. Kuivaa maaperä – lämmin uuni 110°C:ssa (230°F) muutaman tunnin ajan on paras tapa. Voit myös kuivata sen auringonvalossa tai asettaa sen lämpimään, kuivaan paikkaan, kunnes maaperä on täysin kuiva. Sen pitäisi olla jauhemaista ja irtonaista.

    > 💁 Laboratoriossa tarkimpien tulosten saamiseksi maaperä kuivattaisiin uunissa 48–72 tuntia. Jos koulussasi on kuivausuuneja, kysy, voitko käyttää niitä pidempään kuivaamiseen. Mitä pidempään kuivaat, sitä kuivempi näyte ja tarkemmat tulokset.

1. Punnitse maaperä uudelleen.

    > 🔥 Jos kuivaat sen uunissa, varmista, että se on ensin jäähtynyt!

Gravimetrinen maankosteus lasketaan seuraavasti:

![maankosteus % on märän paino miinus kuivan paino, jaettuna kuivan painolla, kerrottuna 100](../../../../../translated_images/fi/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W - märän maaperän paino  
* W - kuivan maaperän paino  

Esimerkiksi, jos sinulla on maaperänäyte, joka painaa 212 g märkänä ja 197 g kuivana:

![Täytetty laskelma](../../../../../translated_images/fi/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212 g  
* W = 197 g  
* 212 - 197 = 15  
* 15 / 197 = 0.076  
* 0.076 * 100 = 7.6 %

Tässä esimerkissä maaperän gravimetrinen maankosteus on 7.6 %.

Kun sinulla on lukemat vähintään kolmesta näytteestä, piirrä graafi maankosteusprosentista maankosteusanturin lukemaan ja lisää paras sovitusviiva pisteisiin. Voit sitten käyttää tätä laskemaan gravimetrisen maankosteuspitoisuuden tietylle anturin lukemalle lukemalla arvon viivalta.

## Arviointikriteerit

| Kriteeri | Erinomainen | Riittävä | Parannettavaa |
| -------- | ----------- | -------- | ------------- |
| Kalibrointidatan kerääminen | Kerää vähintään 3 kalibrointinäytettä | Kerää vähintään 2 kalibrointinäytettä | Kerää vähintään 1 kalibrointinäyte |
| Kalibroitu lukema | Piirrä onnistuneesti kalibrointigraafi, tee lukema anturista ja muunna se gravimetriseksi maankosteuspitoisuudeksi | Piirrä onnistuneesti kalibrointigraafi | Ei pysty piirtämään graafia |

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.