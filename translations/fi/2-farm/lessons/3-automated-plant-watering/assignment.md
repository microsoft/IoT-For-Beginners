<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-27T21:12:14+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "fi"
}
-->
# Luo tehokkaampi kastelusykli

## Ohjeet

Tässä osiossa käsiteltiin, kuinka relettä voidaan ohjata anturidatan avulla, ja kyseinen rele voi puolestaan ohjata pumppua kastelujärjestelmässä. Määritellylle maaperälle pumpun käyttö tietyn ajan pitäisi aina vaikuttaa samalla tavalla maaperän kosteuteen. Tämä tarkoittaa, että voit arvioida, kuinka monta sekuntia kastelua vastaa tiettyä muutosta maaperän kosteuslukemassa. Tämän datan avulla voit rakentaa hallitumman kastelujärjestelmän.

Tässä tehtävässä lasket, kuinka kauan pumpun tulisi käydä tietyn maaperän kosteuden nousun saavuttamiseksi.

> ⚠️ Jos käytät virtuaalista IoT-laitteistoa, voit käydä läpi tämän prosessin, mutta simuloida tulokset lisäämällä maaperän kosteuslukemaa manuaalisesti kiinteällä määrällä sekuntia kohden, kun rele on päällä.

1. Aloita kuivasta maaperästä. Mittaa maaperän kosteus.

1. Lisää kiinteä määrä vettä joko käyttämällä pumppua 1 sekunnin ajan tai kaatamalla kiinteä määrä vettä.

    > Pumpun tulisi aina toimia tasaisella nopeudella, joten joka sekunti, kun pumppu käy, sen tulisi toimittaa sama määrä vettä.

1. Odota, kunnes maaperän kosteustaso vakiintuu, ja ota lukema.

1. Toista tämä useita kertoja ja luo tuloksista taulukko. Esimerkki tällaisesta taulukosta on annettu alla.

    | Pumpun kokonaisaika | Maaperän kosteus | Muutos |
    | --- | --: | -: |
    | Kuiva | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Laske keskimääräinen maaperän kosteuden muutos sekuntia kohden. Yllä olevassa esimerkissä jokainen sekunti vettä vähentää lukemaa keskimäärin 20,3.

1. Käytä tätä dataa parantaaksesi palvelinkoodisi tehokkuutta, käyttämällä pumppua tarvittavan ajan, jotta maaperän kosteus saadaan halutulle tasolle.

## Arviointikriteerit

| Kriteeri | Erinomainen | Riittävä | Parannusta tarvitaan |
| -------- | ----------- | -------- | -------------------- |
| Maaperän kosteuden mittaus | Osaa ottaa useita lukemia kiinteiden vesimäärien lisäämisen jälkeen | Osaa ottaa joitakin lukemia kiinteiden vesimäärien lisäämisen jälkeen | Osaa ottaa vain yhden tai kaksi lukemaa tai ei osaa käyttää kiinteitä vesimääriä |
| Palvelinkoodin kalibrointi | Osaa laskea keskimääräisen maaperän kosteuden muutoksen ja päivittää palvelinkoodin käyttämään tätä | Osaa laskea keskimääräisen muutoksen, mutta ei osaa päivittää palvelinkoodia, tai ei osaa laskea keskimääräistä oikein, mutta käyttää tätä arvoa palvelinkoodin päivittämiseen oikein | Ei osaa laskea keskimääräistä muutosta tai päivittää palvelinkoodia |

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.