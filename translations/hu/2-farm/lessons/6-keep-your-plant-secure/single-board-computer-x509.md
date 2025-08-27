<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-27T23:06:51+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "hu"
}
-->
# Használja az X.509 tanúsítványt az eszközkódjában - Virtuális IoT Hardver és Raspberry Pi

Ebben a leckében csatlakoztatni fogja virtuális IoT eszközét vagy Raspberry Pi-jét az IoT Hubhoz egy X.509 tanúsítvány segítségével.

## Csatlakoztassa eszközét az IoT Hubhoz

A következő lépés az, hogy eszközét X.509 tanúsítványokkal csatlakoztassa az IoT Hubhoz.

### Feladat - csatlakozás az IoT Hubhoz

1. Másolja a kulcs- és tanúsítványfájlokat az IoT eszközkódot tartalmazó mappába. Ha Raspberry Pi-t használ a VS Code Remote SSH-n keresztül, és a kulcsokat a PC-jén vagy Mac-jén hozta létre, egyszerűen húzza át a fájlokat a VS Code felfedezőjébe, hogy átmásolja őket.

1. Nyissa meg az `app.py` fájlt.

1. Az X.509 tanúsítvánnyal való csatlakozáshoz szüksége lesz az IoT Hub hosztnevére és az X.509 tanúsítványra. Kezdje azzal, hogy létrehoz egy változót, amely tartalmazza a hosztnevet, az alábbi kód hozzáadásával, mielőtt a device client létrejön:

    ```python
    host_name = "<host_name>"
    ```

    Cserélje le a `<host_name>` helyére az IoT Hub hosztnevét. Ezt a `connection_string` `HostName` szakaszában találhatja meg. Ez az IoT Hub neve lesz, amely `.azure-devices.net` végződéssel zárul.

1. Ezután deklaráljon egy változót az eszközazonosítóval:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Szüksége lesz az `X509` osztály egy példányára, amely tartalmazza az X.509 fájlokat. Adja hozzá az `X509`-et az `azure.iot.device` modulból importált osztályok listájához:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Hozzon létre egy `X509` osztálypéldányt a tanúsítvány- és kulcsfájlok használatával, az alábbi kód hozzáadásával a `host_name` deklaráció alá:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Ez létrehozza az `X509` osztályt a korábban létrehozott `soil-moisture-sensor-x509-cert.pem` és `soil-moisture-sensor-x509-key.pem` fájlok használatával.

1. Cserélje le azt a kódsort, amely a `device_client`-et egy connection string alapján hozza létre, az alábbira:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Ez X.509 tanúsítványt fog használni a connection string helyett.

1. Törölje a `connection_string` változót tartalmazó sort.

1. Futtassa a kódját. Figyelje az IoT Hubhoz küldött üzeneteket, és küldjön közvetlen metóduskéréseket, ahogy korábban is. Látni fogja, hogy az eszköz csatlakozik, és talajnedvesség-értékeket küld, valamint fogadja a közvetlen metóduskéréseket.

> 💁 Ezt a kódot megtalálja a [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) vagy [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) mappában.

😀 A talajnedvesség-érzékelő programja X.509 tanúsítvány segítségével csatlakozik az IoT Hubhoz!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.