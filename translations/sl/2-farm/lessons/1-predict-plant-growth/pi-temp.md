<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-28T15:07:06+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "sl"
}
-->
# Merjenje temperature - Raspberry Pi

V tem delu lekcije boste dodali temperaturni senzor na vaš Raspberry Pi.

## Strojna oprema

Senzor, ki ga boste uporabili, je [DHT11 senzor za vlago in temperaturo](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), ki združuje dva senzorja v enem paketu. Ta senzor je precej priljubljen, saj je na voljo veliko komercialnih senzorjev, ki združujejo temperaturo, vlago in včasih tudi atmosferski tlak. Komponenta za merjenje temperature je termistor z negativnim temperaturnim koeficientom (NTC), pri katerem se upornost zmanjša, ko se temperatura poveča.

Gre za digitalni senzor, ki ima vgrajen ADC za ustvarjanje digitalnega signala, ki vsebuje podatke o temperaturi in vlagi, ki jih lahko mikrokrmilnik prebere.

### Povežite temperaturni senzor

Grove temperaturni senzor lahko povežete z Raspberry Pi.

#### Naloga

Povežite temperaturni senzor.

![Grove temperaturni senzor](../../../../../translated_images/sl/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Vstavite en konec Grove kabla v vtičnico na senzorju za vlago in temperaturo. Kabel bo šel noter samo v eni smeri.

1. Ko je Raspberry Pi izklopljen, povežite drugi konec Grove kabla z digitalno vtičnico, označeno **D5**, na Grove Base hat, ki je priključen na Pi. Ta vtičnica je druga z leve strani v vrsti vtičnic poleg GPIO pinov.

![Grove temperaturni senzor povezan z vtičnico A0](../../../../../translated_images/sl/pi-temperature-sensor.3ff82fff672c8e56.webp)

## Programirajte temperaturni senzor

Napravo lahko zdaj programirate za uporabo priključenega temperaturnega senzorja.

### Naloga

Programirajte napravo.

1. Vklopite Pi in počakajte, da se zažene.

1. Zaženite VS Code, bodisi neposredno na Pi, bodisi se povežite prek razširitve Remote SSH.

    > ⚠️ Če potrebujete, si lahko ogledate [navodila za nastavitev in zagon VS Code v lekciji 1](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. V terminalu ustvarite novo mapo v domačem imeniku uporabnika `pi`, imenovano `temperature-sensor`. V tej mapi ustvarite datoteko z imenom `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Odprite to mapo v VS Code.

1. Za uporabo senzorja za temperaturo in vlago je treba namestiti dodatni Pip paket. V terminalu v VS Code zaženite naslednji ukaz za namestitev tega Pip paketa na Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Dodajte naslednjo kodo v datoteko `app.py` za uvoz potrebnih knjižnic:

    ```python
    import time
    from seeed_dht import DHT
    ```

    Izjava `from seeed_dht import DHT` uvozi razred `DHT` za interakcijo z Grove temperaturnim senzorjem iz modula `seeed_dht`.

1. Dodajte naslednjo kodo za zgornjo kodo, da ustvarite instanco razreda, ki upravlja temperaturni senzor:

    ```python
    sensor = DHT("11", 5)
    ```

    To deklarira instanco razreda `DHT`, ki upravlja **D**igitalni senzor za **V**lago in **T**emperaturo. Prvi parameter pove kodi, da se uporablja senzor *DHT11* - knjižnica, ki jo uporabljate, podpira tudi druge različice tega senzorja. Drugi parameter pove kodi, da je senzor povezan z digitalnim priključkom `D5` na Grove Base hat.

    > ✅ Ne pozabite, vse vtičnice imajo edinstvene številke pinov. Pini 0, 2, 4 in 6 so analogni pini, pini 5, 16, 18, 22, 24 in 26 pa so digitalni pini.

1. Dodajte neskončno zanko za zgornjo kodo, da pridobite vrednost temperaturnega senzorja in jo natisnete na konzolo:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Klic `sensor.read()` vrne nabor vrednosti za vlago in temperaturo. Potrebujete samo vrednost temperature, zato vlago ignorirate. Vrednost temperature se nato natisne na konzolo.

1. Na koncu zanke dodajte kratko pavzo desetih sekund, saj ni potrebno neprekinjeno preverjati ravni temperature. Pavza zmanjša porabo energije naprave.

    ```python
    time.sleep(10)
    ```

1. V terminalu VS Code zaženite naslednji ukaz za zagon vaše Python aplikacije:

    ```sh
    python3 app.py
    ```

    Na konzoli bi morali videti vrednosti temperature. Uporabite nekaj za segrevanje senzorja, na primer pritisnite nanj s palcem ali uporabite ventilator, da vidite, kako se vrednosti spreminjajo:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 To kodo lahko najdete v mapi [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Vaš program za temperaturni senzor je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za strojno prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo strokovno človeško prevajanje. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki izhajajo iz uporabe tega prevoda.