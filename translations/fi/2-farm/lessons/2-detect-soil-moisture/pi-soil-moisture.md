# Mittaa maaperän kosteutta - Raspberry Pi

Tässä oppitunnin osassa lisäät kapasiivisen maaperän kosteusanturin Raspberry Pi:hin ja luet siitä arvoja.

## Laitteisto

Raspberry Pi tarvitsee kapasiivisen maaperän kosteusanturin.

Käytettävä anturi on [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), joka mittaa maaperän kosteutta havaitsemalla maaperän kapasitanssin, ominaisuuden, joka muuttuu maaperän kosteuden muuttuessa. Kun maaperän kosteus kasvaa, jännite laskee.

Tämä on analoginen anturi, joten se käyttää analogista pinniä ja Grove Base Hatin 10-bittistä ADC:tä Pi:ssä muuntaakseen jännitteen digitaaliseksi signaaliksi välillä 1-1,023. Tämä signaali lähetetään sitten I

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.