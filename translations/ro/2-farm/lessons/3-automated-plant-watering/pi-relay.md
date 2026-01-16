<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-28T11:42:37+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "ro"
}
-->
# Controlați un releu - Raspberry Pi

În această parte a lecției, veți adăuga un releu la Raspberry Pi, pe lângă senzorul de umiditate a solului, și îl veți controla în funcție de nivelul de umiditate a solului.

## Hardware

Raspberry Pi are nevoie de un releu.

Releul pe care îl veți folosi este un [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), un releu normal-deschis (ceea ce înseamnă că circuitul de ieșire este deschis sau deconectat atunci când nu se trimite niciun semnal către releu) care poate gestiona circuite de ieșire de până la 250V și 10A.

Acesta este un actuator digital, deci se conectează la un pin digital pe Grove Base Hat.

### Conectați releul

Releul Grove poate fi conectat la Raspberry Pi.

#### Sarcină

Conectați releul.

![Un releu Grove](../../../../../translated_images/ro/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Introduceți un capăt al unui cablu Grove în soclul releului. Acesta va intra doar într-un singur mod.

1. Cu Raspberry Pi oprit, conectați celălalt capăt al cablului Grove la soclul digital marcat **D5** pe Grove Base Hat atașat la Pi. Acest soclu este al doilea de la stânga, pe rândul de socluri de lângă pinii GPIO. Lăsați senzorul de umiditate a solului conectat la soclul **A0**.

![Releul Grove conectat la soclul D5 și senzorul de umiditate a solului conectat la soclul A0](../../../../../translated_images/ro/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. Introduceți senzorul de umiditate a solului în pământ, dacă nu este deja introdus din lecția anterioară.

## Programați releul

Raspberry Pi poate fi acum programat pentru a utiliza releul atașat.

### Sarcină

Programați dispozitivul.

1. Porniți Pi-ul și așteptați să se încarce.

1. Deschideți proiectul `soil-moisture-sensor` din lecția anterioară în VS Code, dacă nu este deja deschis. Veți adăuga la acest proiect.

1. Adăugați următorul cod în fișierul `app.py` sub importurile existente:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Această instrucțiune importă `GroveRelay` din bibliotecile Grove Python pentru a interacționa cu releul Grove.

1. Adăugați următorul cod sub declarația clasei `ADC` pentru a crea o instanță `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Acesta creează un releu utilizând pinul **D5**, pinul digital la care ați conectat releul.

1. Pentru a testa dacă releul funcționează, adăugați următorul cod în bucla `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Codul pornește releul, așteaptă 0,5 secunde, apoi oprește releul.

1. Rulați aplicația Python. Releul se va porni și opri la fiecare 10 secunde, cu o întârziere de jumătate de secundă între pornire și oprire. Veți auzi clicul releului când se pornește și când se oprește. Un LED de pe placa Grove se va aprinde când releul este pornit, apoi se va stinge când releul este oprit.

    ![Releul se pornește și se oprește](../../../../../images/relay-turn-on-off.gif)

## Controlați releul în funcție de umiditatea solului

Acum că releul funcționează, acesta poate fi controlat în funcție de citirile senzorului de umiditate a solului.

### Sarcină

Controlați releul.

1. Ștergeți cele 3 linii de cod pe care le-ați adăugat pentru a testa releul. Înlocuiți-le cu următorul cod:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Acest cod verifică nivelul de umiditate a solului de la senzorul de umiditate a solului. Dacă este peste 450, pornește releul și îl oprește când scade sub 450.

    > 💁 Rețineți că senzorul capacitiv de umiditate a solului citește: cu cât nivelul de umiditate a solului este mai mic, cu atât solul este mai umed și viceversa.

1. Rulați aplicația Python. Veți vedea releul pornindu-se sau oprindu-se în funcție de nivelul de umiditate a solului. Încercați în sol uscat, apoi adăugați apă.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Puteți găsi acest cod în folderul [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 Programul dvs. de control al releului în funcție de senzorul de umiditate a solului a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.