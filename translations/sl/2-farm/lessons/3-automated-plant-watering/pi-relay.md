<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-28T15:23:41+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "sl"
}
-->
# Upravljanje releja - Raspberry Pi

V tem delu lekcije boste na svoj Raspberry Pi dodali rele poleg senzorja za vlago v tleh in ga upravljali glede na raven vlage v tleh.

## Strojna oprema

Raspberry Pi potrebuje rele.

Rele, ki ga boste uporabili, je [Grove rele](https://www.seeedstudio.com/Grove-Relay.html), običajno odprt rele (kar pomeni, da je izhodni krogotok odprt ali prekinjen, ko rele ne prejme signala), ki lahko upravlja izhodne krogotoke do 250V in 10A.

To je digitalni aktuator, zato se poveže na digitalni pin na Grove Base Hat.

### Povežite rele

Grove rele lahko povežete z Raspberry Pi.

#### Naloga

Povežite rele.

![Grove rele](../../../../../translated_images/sl/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Vstavite en konec Grove kabla v vtičnico na releju. Kabel bo šel noter samo v eni smeri.

1. Ko je Raspberry Pi izklopljen, povežite drugi konec Grove kabla z digitalno vtičnico, označeno **D5**, na Grove Base Hat, ki je pritrjen na Pi. Ta vtičnica je druga z leve strani v vrsti vtičnic poleg GPIO pinov. Senzor za vlago v tleh pustite povezan na vtičnico **A0**.

![Grove rele povezan na vtičnico D5, senzor za vlago v tleh povezan na vtičnico A0](../../../../../translated_images/sl/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. Vstavite senzor za vlago v tleh v zemljo, če tega še niste storili v prejšnji lekciji.

## Programiranje releja

Zdaj lahko Raspberry Pi programirate za uporabo pritrjenega releja.

### Naloga

Programirajte napravo.

1. Vklopite Pi in počakajte, da se zažene.

1. Odprite projekt `soil-moisture-sensor` iz prejšnje lekcije v VS Code, če še ni odprt. Dodali boste k temu projektu.

1. Dodajte naslednjo kodo v datoteko `app.py` pod obstoječimi uvozi:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Ta ukaz uvozi `GroveRelay` iz knjižnic Grove Python za interakcijo z Grove relejem.

1. Dodajte naslednjo kodo pod deklaracijo razreda `ADC`, da ustvarite instanco `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    To ustvari rele, ki uporablja pin **D5**, digitalni pin, na katerega ste povezali rele.

1. Da preverite, ali rele deluje, dodajte naslednjo kodo v zanko `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Koda vklopi rele, počaka 0,5 sekunde, nato rele izklopi.

1. Zaženite Python aplikacijo. Rele se bo vklapljal in izklapljal vsakih 10 sekund, s polsekundnim zamikom med vklopom in izklopom. Slišali boste klik releja ob vklopu in izklopu. LED na Grove plošči bo zasvetila, ko je rele vklopljen, in ugasnila, ko je rele izklopljen.

    ![Rele se vklaplja in izklaplja](../../../../../images/relay-turn-on-off.gif)

## Upravljanje releja glede na vlago v tleh

Zdaj, ko rele deluje, ga lahko upravljate glede na odčitke senzorja za vlago v tleh.

### Naloga

Upravljajte rele.

1. Izbrišite 3 vrstice kode, ki ste jih dodali za testiranje releja. Zamenjajte jih z naslednjo kodo:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Ta koda preveri raven vlage v tleh s senzorjem za vlago v tleh. Če je nad 450, vklopi rele, in ga izklopi, ko pade pod 450.

    > 💁 Ne pozabite, da kapacitivni senzor za vlago v tleh bere: nižja kot je raven vlage v tleh, več vlage je v tleh, in obratno.

1. Zaženite Python aplikacijo. Videli boste, da se rele vklopi ali izklopi glede na raven vlage v tleh. Preizkusite v suhi zemlji, nato dodajte vodo.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 To kodo lahko najdete v mapi [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 Vaš program za upravljanje releja glede na senzor za vlago v tleh je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve AI za prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.