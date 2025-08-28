<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-28T14:56:05+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "sl"
}
-->
# Uporaba potrdila X.509 v kodi vaše naprave - Virtualna IoT strojna oprema in Raspberry Pi

V tem delu lekcije boste svojo virtualno IoT napravo ali Raspberry Pi povezali z vašim IoT Hubom s pomočjo potrdila X.509.

## Povežite svojo napravo z IoT Hubom

Naslednji korak je povezava vaše naprave z IoT Hubom s pomočjo potrdil X.509.

### Naloga - povezava z IoT Hubom

1. Kopirajte datoteke s ključem in potrdilom v mapo, ki vsebuje kodo vaše IoT naprave. Če uporabljate Raspberry Pi prek VS Code Remote SSH in ste ključe ustvarili na svojem računalniku (PC ali Mac), lahko datoteke povlečete in spustite v raziskovalec v VS Code, da jih kopirate.

1. Odprite datoteko `app.py`.

1. Za povezavo s potrdilom X.509 boste potrebovali ime gostitelja IoT Huba in potrdilo X.509. Začnite z ustvarjanjem spremenljivke, ki vsebuje ime gostitelja, tako da pred ustvarjanjem odjemalca naprave dodate naslednjo kodo:

    ```python
    host_name = "<host_name>"
    ```

    Zamenjajte `<host_name>` z imenom gostitelja vašega IoT Huba. To lahko pridobite iz razdelka `HostName` v `connection_string`. To bo ime vašega IoT Huba, ki se konča z `.azure-devices.net`.

1. Pod to vrstico deklarirajte spremenljivko z ID-jem naprave:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Potrebovali boste instanco razreda `X509`, ki vsebuje datoteke s potrdilom X.509. Dodajte `X509` na seznam razredov, uvoženih iz modula `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Ustvarite instanco razreda `X509` z uporabo vaših datotek s potrdilom in ključem, tako da dodate to kodo pod deklaracijo `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    To bo ustvarilo razred `X509` z uporabo datotek `soil-moisture-sensor-x509-cert.pem` in `soil-moisture-sensor-x509-key.pem`, ki ste jih ustvarili prej.

1. Zamenjajte vrstico kode, ki ustvarja `device_client` iz niza za povezavo, z naslednjo:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    To bo omogočilo povezavo s potrdilom X.509 namesto z nizom za povezavo.

1. Izbrišite vrstico s spremenljivko `connection_string`.

1. Zaženite svojo kodo. Spremljajte sporočila, poslana v IoT Hub, in pošiljajte zahteve za neposredne metode kot prej. Videli boste, kako se naprava povezuje in pošilja odčitke vlage v tleh ter prejema zahteve za neposredne metode.

> 💁 To kodo lahko najdete v mapi [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) ali [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Vaš program za senzor vlage v tleh je povezan z vašim IoT Hubom s pomočjo potrdila X.509!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.