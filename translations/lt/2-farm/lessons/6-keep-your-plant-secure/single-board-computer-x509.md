<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-28T20:30:00+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "lt"
}
-->
# Naudokite X.509 sertifikatą savo įrenginio kode - Virtuali IoT įranga ir Raspberry Pi

Šioje pamokos dalyje prijungsite savo virtualų IoT įrenginį arba Raspberry Pi prie IoT Hub naudodami X.509 sertifikatą.

## Prijunkite savo įrenginį prie IoT Hub

Kitas žingsnis – prijungti savo įrenginį prie IoT Hub naudojant X.509 sertifikatus.

### Užduotis - prisijungti prie IoT Hub

1. Nukopijuokite raktų ir sertifikatų failus į aplanką, kuriame yra jūsų IoT įrenginio kodas. Jei naudojate Raspberry Pi per VS Code Remote SSH ir raktus sukūrėte savo kompiuteryje ar Mac, galite vilkti ir numesti failus į VS Code naršyklę, kad juos nukopijuotumėte.

1. Atidarykite failą `app.py`

1. Norėdami prisijungti naudojant X.509 sertifikatą, jums reikės IoT Hub hosto pavadinimo ir X.509 sertifikato. Pradėkite sukurdami kintamąjį, kuriame bus hosto pavadinimas, pridėdami šį kodą prieš sukuriant įrenginio klientą:

    ```python
    host_name = "<host_name>"
    ```

    Pakeiskite `<host_name>` savo IoT Hub hosto pavadinimu. Jį galite rasti `HostName` sekcijoje `connection_string`. Tai bus jūsų IoT Hub pavadinimas, kuris baigiasi `.azure-devices.net`

1. Po šiuo kodu deklaruokite kintamąjį su įrenginio ID:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Jums reikės `X509` klasės egzemplioriaus, kuriame yra X.509 failai. Pridėkite `X509` prie klasių, importuojamų iš `azure.iot.device` modulio, sąrašo:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Sukurkite `X509` klasės egzempliorių naudodami savo sertifikato ir rakto failus, pridėdami šį kodą po `host_name` deklaracijos:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Tai sukurs `X509` klasę naudojant anksčiau sukurtus failus `soil-moisture-sensor-x509-cert.pem` ir `soil-moisture-sensor-x509-key.pem`.

1. Pakeiskite kodo eilutę, kuri sukuria `device_client` iš prisijungimo eilutės, į šią:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Tai leis prisijungti naudojant X.509 sertifikatą vietoj prisijungimo eilutės.

1. Ištrinkite eilutę su `connection_string` kintamuoju.

1. Paleiskite savo kodą. Stebėkite pranešimus, siunčiamus į IoT Hub, ir siųskite tiesioginius metodų užklausimus kaip anksčiau. Pamatysite, kaip įrenginys prisijungia ir siunčia dirvožemio drėgmės rodmenis, taip pat gauna tiesioginius metodų užklausimus.

> 💁 Šį kodą galite rasti [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) arba [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) aplanke.

😀 Jūsų dirvožemio drėgmės jutiklio programa prijungta prie jūsų IoT Hub naudojant X.509 sertifikatą!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.