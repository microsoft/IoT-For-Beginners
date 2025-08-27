<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T20:51:07+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "fi"
}
-->
# Luo virtuaalikone, jossa IoT Edge on käytössä

Azuren avulla voit luoda virtuaalikoneen - pilvessä toimivan tietokoneen, jonka voit konfiguroida haluamallasi tavalla ja ajaa omia ohjelmiasi.

> 💁 Voit lukea lisää virtuaalikoneista [Wikipedian virtuaalikone-sivulta](https://wikipedia.org/wiki/Virtual_machine).

## Tehtävä - IoT Edge -virtuaalikoneen käyttöönotto

1. Suorita seuraava komento luodaksesi virtuaalikoneen, jossa Azure IoT Edge on jo valmiiksi asennettuna:

    ```sh
    az deployment group create \
                --resource-group fruit-quality-detector \
                --template-uri https://raw.githubusercontent.com/Azure/iotedge-vm-deploy/1.2.0/edgeDeploy.json \
                --parameters dnsLabelPrefix=<vm_name> \
                --parameters adminUsername=<username> \
                --parameters deviceConnectionString="<connection_string>" \
                --parameters authenticationType=password \
                --parameters adminPasswordOrKey="<password>"
    ```

    Korvaa `<vm_name>` virtuaalikoneen nimellä. Nimen täytyy olla maailmanlaajuisesti uniikki, joten käytä esimerkiksi `fruit-quality-detector-vm-` ja lisää loppuun oma nimesi tai jokin muu arvo.

    Korvaa `<username>` ja `<password>` käyttäjänimellä ja salasanalla, joita käytät kirjautuessasi virtuaalikoneeseen. Näiden täytyy olla suhteellisen turvallisia, joten et voi käyttää esimerkiksi admin/password-yhdistelmää.

    Korvaa `<connection_string>` `fruit-quality-detector-edge` IoT Edge -laitteesi yhteysmerkkijonolla.

    Tämä komento luo virtuaalikoneen, joka on konfiguroitu `DS1 v2` -tyyppiseksi. Nämä kategoriat määrittävät koneen suorituskyvyn ja siten myös sen kustannukset. Tämä virtuaalikone sisältää yhden suorittimen ja 3,5 GB RAM-muistia.

    > 💰 Voit tarkistaa näiden virtuaalikoneiden ajantasaiset hinnat [Azure Virtual Machine -hinnoitteluoppaasta](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn).

    Kun virtuaalikone on luotu, IoT Edge -ajonaikainen ympäristö asennetaan automaattisesti ja konfiguroidaan yhdistämään IoT Hubiin `fruit-quality-detector-edge` -laitteena.

1. Tarvitset joko virtuaalikoneen IP-osoitteen tai DNS-nimen, jotta voit kutsua kuvanluokittelijaa siitä. Suorita seuraava komento saadaksesi tämän tiedon:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Kopioi joko `PublicIps`-kentän tai `Fqdns`-kentän arvo.

1. Virtuaalikoneet maksavat rahaa. Tämän kirjoitushetkellä DS1-virtuaalikone maksaa noin 0,06 dollaria tunnilta. Kustannusten minimoimiseksi sinun tulisi sammuttaa virtuaalikone, kun et käytä sitä, ja poistaa se, kun olet valmis projektin kanssa.

    Voit konfiguroida virtuaalikoneesi sammumaan automaattisesti tiettyyn aikaan joka päivä. Tämä tarkoittaa, että jos unohdat sammuttaa sen, sinua laskutetaan vain siihen asti, kunnes automaattinen sammutus tapahtuu. Käytä seuraavaa komentoa asettaaksesi tämän:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Korvaa `<vm_name>` virtuaalikoneesi nimellä.

    Korvaa `<shutdown_time_utc>` UTC-ajalla, jolloin haluat virtuaalikoneen sammuvan, käyttäen neljää numeroa muodossa HHMM. Esimerkiksi, jos haluat sammuttaa koneen keskiyöllä UTC-aikaa, aseta tämä arvoon `0000`. Jos haluat sammuttaa koneen klo 19:30 Yhdysvaltojen länsirannikolla, käytä arvoa `0230` (klo 19:30 Yhdysvaltojen länsirannikolla on klo 2:30 UTC-aikaa).

1. Kuvanluokittelijasi toimii tällä edge-laitteella ja kuuntelee porttia 80 (standardi HTTP-portti). Oletuksena virtuaalikoneiden saapuvat portit ovat estettyjä, joten sinun täytyy avata portti 80. Portit avataan verkkoturvaryhmissä, joten ensin sinun täytyy tietää virtuaalikoneesi verkkoturvaryhmän nimi, jonka voit selvittää seuraavalla komennolla:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Kopioi `Name`-kentän arvo.

1. Suorita seuraava komento lisätäksesi säännön, joka avaa portin 80 verkkoturvaryhmään:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Korvaa `<nsg name>` edellisessä vaiheessa saadulla verkkoturvaryhmän nimellä.

### Tehtävä - hallitse virtuaalikonettasi kustannusten vähentämiseksi

1. Kun et käytä virtuaalikonettasi, sinun tulisi sammuttaa se. Sammuttaaksesi virtuaalikoneen, käytä seuraavaa komentoa:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Korvaa `<vm_name>` virtuaalikoneesi nimellä.

    > 💁 On olemassa myös `az vm stop` -komento, joka pysäyttää virtuaalikoneen, mutta pitää koneen varattuna sinulle, joten maksat edelleen ikään kuin se olisi käynnissä.

1. Käynnistääksesi virtuaalikoneen uudelleen, käytä seuraavaa komentoa:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Korvaa `<vm_name>` virtuaalikoneesi nimellä.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.