# Kutsu objektintunnistinta IoT-laitteestasi - Virtuaalinen IoT-laitteisto ja Raspberry Pi

Kun objektintunnistin on julkaistu, sitä voidaan käyttää IoT-laitteestasi.

## Kopioi kuvaluokitteluprojekti

Suurin osa varastotunnistimestasi on sama kuin kuvaluokitin, jonka loit aiemmassa oppitunnissa.

### Tehtävä - kopioi kuvaluokitteluprojekti

1. Luo kansio nimeltä `stock-counter` joko tietokoneellesi, jos käytät virtuaalista IoT-laitetta, tai Raspberry Pi:llesi. Jos käytät virtuaalista IoT-laitetta, varmista, että asetat virtuaalisen ympäristön.

1. Asenna kameran laitteisto.

    * Jos käytät Raspberry Pi:tä, sinun täytyy asentaa PiCamera. Saatat myös haluta kiinnittää kameran yhteen paikkaan, esimerkiksi ripustamalla kaapelin laatikon tai tölkin päälle, tai kiinnittämällä kameran laatikkoon kaksipuolisella teipillä.
    * Jos käytät virtuaalista IoT-laitetta, sinun täytyy asentaa CounterFit ja CounterFit PyCamera -lisäosa. Jos aiot käyttää still-kuvia, ota kuvia, joita objektintunnistin ei ole vielä nähnyt. Jos aiot käyttää verkkokameraa, varmista, että se on sijoitettu niin, että se näkee tunnistettavan varaston.

1. Toista vaiheet [valmistusprojektin oppitunnista 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) kuvien ottamiseksi kameralla.

1. Toista vaiheet [valmistusprojektin oppitunnista 2](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) kutsuaksesi kuvaluokitinta. Suurin osa tästä koodista käytetään uudelleen objektien tunnistamiseen.

## Muuta koodi luokittimesta objektintunnistimeksi

Koodi, jota käytit kuvien luokitteluun, on hyvin samanlainen kuin koodi objektien tunnistamiseen. Suurin ero on Custom Vision SDK:n kutsutussa metodissa ja kutsun tuloksissa.

### Tehtävä - muuta koodi luokittimesta objektintunnistimeksi

1. Poista kolme riviä koodia, jotka luokittelevat kuvan ja käsittelevät ennusteet:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Poista nämä kolme riviä.

1. Lisää seuraava koodi tunnistaaksesi objektit kuvasta:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Tämä koodi kutsuu `detect_image`-metodia ennustajassa suorittaakseen objektintunnistimen. Se kerää kaikki ennusteet, joiden todennäköisyys ylittää kynnyksen, ja tulostaa ne konsoliin.

    Toisin kuin kuvaluokitin, joka palauttaa vain yhden tuloksen per tunniste, objektintunnistin palauttaa useita tuloksia, joten kaikki matalan todennäköisyyden tulokset täytyy suodattaa pois.

1. Suorita tämä koodi, ja se ottaa kuvan, lähettää sen objektintunnistimelle ja tulostaa tunnistetut objektit. Jos käytät virtuaalista IoT-laitetta, varmista, että CounterFitissä on asetettu sopiva kuva tai että verkkokamera on valittu. Jos käytät Raspberry Pi:tä, varmista, että kamerasi osoittaa hyllyllä oleviin objekteihin.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Saatat joutua säätämään `threshold`-arvoa sopivaksi kuvillesi.

    Näet otetun kuvan ja nämä arvot **Predictions**-välilehdellä Custom Visionissa.

    ![4 tölkkiä tomaattipyrettä hyllyllä, jossa ennusteet 35,8 %, 33,5 %, 25,7 % ja 16,6 % neljälle tunnistukselle](../../../../../translated_images/fi/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Löydät tämän koodin [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) tai [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device) -kansiosta.

😀 Varastolaskuriohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.