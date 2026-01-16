<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-28T10:54:38+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "sk"
}
-->
# Meranie vlhkosti pôdy - Raspberry Pi

V tejto časti lekcie pridáte kapacitný senzor vlhkosti pôdy k vášmu Raspberry Pi a prečítate z neho hodnoty.

## Hardvér

Raspberry Pi potrebuje kapacitný senzor vlhkosti pôdy.

Senzor, ktorý budete používať, je [Kapacitný senzor vlhkosti pôdy](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), ktorý meria vlhkosť pôdy detekovaním kapacity pôdy, čo je vlastnosť, ktorá sa mení v závislosti od vlhkosti pôdy. Ako sa vlhkosť pôdy zvyšuje, napätie klesá.

Toto je analógový senzor, takže používa analógový pin a 10-bitový ADC v Grove Base Hat na Pi na prevod napätia na digitálny signál v rozsahu od 1 do 1 023. Tento signál sa potom posiela cez I²C cez GPIO piny na Pi.

### Pripojenie senzora vlhkosti pôdy

Grove senzor vlhkosti pôdy je možné pripojiť k Raspberry Pi.

#### Úloha - pripojenie senzora vlhkosti pôdy

Pripojte senzor vlhkosti pôdy.

![Grove senzor vlhkosti pôdy](../../../../../translated_images/sk/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. Zasuňte jeden koniec Grove kábla do konektora na senzore vlhkosti pôdy. Kábel sa dá zasunúť iba jedným spôsobom.

1. Pri vypnutom Raspberry Pi pripojte druhý koniec Grove kábla do analógového konektora označeného **A0** na Grove Base Hat pripojenom k Pi. Tento konektor je druhý sprava v rade konektorov vedľa GPIO pinov.

![Grove senzor vlhkosti pôdy pripojený do konektora A0](../../../../../translated_images/sk/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.png)

1. Zasuňte senzor vlhkosti pôdy do pôdy. Na senzore je biela čiara označujúca „najvyššiu polohu“. Zasuňte senzor až po túto čiaru, ale nie hlbšie.

![Grove senzor vlhkosti pôdy v pôde](../../../../../translated_images/sk/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## Naprogramovanie senzora vlhkosti pôdy

Raspberry Pi teraz môžete naprogramovať na používanie pripojeného senzora vlhkosti pôdy.

### Úloha - naprogramovanie senzora vlhkosti pôdy

Naprogramujte zariadenie.

1. Zapnite Pi a počkajte, kým sa nespustí.

1. Spustite VS Code, buď priamo na Pi, alebo sa pripojte cez rozšírenie Remote SSH.

    > ⚠️ Môžete sa odvolať na [pokyny na nastavenie a spustenie VS Code v nightlight - lekcia 1, ak je to potrebné](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. V termináli vytvorte nový priečinok v domovskom adresári používateľa `pi` s názvom `soil-moisture-sensor`. V tomto priečinku vytvorte súbor s názvom `app.py`.

1. Otvorte tento priečinok vo VS Code.

1. Pridajte nasledujúci kód do súboru `app.py`, aby ste importovali potrebné knižnice:

    ```python
    import time
    from grove.adc import ADC
    ```

    Príkaz `import time` importuje modul `time`, ktorý sa bude používať neskôr v tejto úlohe.

    Príkaz `from grove.adc import ADC` importuje `ADC` z knižníc Grove pre Python. Táto knižnica obsahuje kód na interakciu s analógovo-digitálnym prevodníkom na základnej doske Pi a na čítanie napätí z analógových senzorov.

1. Pridajte nasledujúci kód pod tento, aby ste vytvorili inštanciu triedy `ADC`:

    ```python
    adc = ADC()
    ```

1. Pridajte nekonečnú slučku, ktorá číta hodnoty z ADC na pine A0 a zapisuje výsledok do konzoly. Táto slučka potom môže spať 10 sekúnd medzi jednotlivými čítaniami.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Spustite Python aplikáciu. Uvidíte, ako sa hodnoty vlhkosti pôdy zapisujú do konzoly. Pridajte vodu do pôdy alebo vyberte senzor z pôdy a sledujte, ako sa hodnota mení.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    V príklade výstupu vyššie môžete vidieť, ako napätie klesá, keď sa pridáva voda.

> 💁 Tento kód nájdete v priečinku [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 Program senzora vlhkosti pôdy bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.