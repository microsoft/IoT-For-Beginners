<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-27T23:06:40+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "sw"
}
-->
# Tumia Cheti cha X.509 katika Msimbo wa Kifaa Chako - Vifaa vya IoT vya Kijumla na Raspberry Pi

Katika sehemu hii ya somo, utaunganisha kifaa chako cha IoT cha kijumla au Raspberry Pi kwenye IoT Hub yako ukitumia cheti cha X.509.

## Unganisha kifaa chako kwenye IoT Hub

Hatua inayofuata ni kuunganisha kifaa chako kwenye IoT Hub ukitumia vyeti vya X.509.

### Kazi - Unganisha kwenye IoT Hub

1. Nakili faili za funguo na vyeti kwenye folda inayoshikilia msimbo wa kifaa chako cha IoT. Ikiwa unatumia Raspberry Pi kupitia VS Code Remote SSH na uliunda funguo kwenye PC au Mac yako, unaweza kuburuta na kuachia faili hizo kwenye sehemu ya explorer ndani ya VS Code ili kuzinakili.

1. Fungua faili `app.py`

1. Ili kuunganisha ukitumia cheti cha X.509, utahitaji jina la mwenyeji wa IoT Hub, na cheti cha X.509. Anza kwa kuunda kigezo kinachoshikilia jina la mwenyeji kwa kuongeza msimbo ufuatao kabla ya mteja wa kifaa kuundwa:

    ```python
    host_name = "<host_name>"
    ```

    Badilisha `<host_name>` na jina la mwenyeji wa IoT Hub yako. Unaweza kupata hili kutoka sehemu ya `HostName` katika `connection_string`. Litakuwa jina la IoT Hub yako, likimalizika na `.azure-devices.net`

1. Chini ya hii, tangaza kigezo chenye kitambulisho cha kifaa:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Utahitaji mfano wa darasa la `X509` linaloshikilia faili za X.509. Ongeza `X509` kwenye orodha ya madarasa yaliyoingizwa kutoka moduli ya `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Unda mfano wa darasa la `X509` ukitumia faili zako za cheti na funguo kwa kuongeza msimbo huu chini ya tangazo la `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Hii itaunda darasa la `X509` ukitumia faili za `soil-moisture-sensor-x509-cert.pem` na `soil-moisture-sensor-x509-key.pem` zilizoundwa awali.

1. Badilisha mstari wa msimbo unaounda `device_client` kutoka kwa connection string, na ufuatao:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Hii itaunganisha ukitumia cheti cha X.509 badala ya connection string.
    
1. Futa mstari wenye kigezo cha `connection_string`.

1. Endesha msimbo wako. Fuata ujumbe unaotumwa kwenye IoT Hub, na tuma maombi ya njia ya moja kwa moja kama ulivyofanya awali. Utaona kifaa kikijiunganisha na kutuma vipimo vya unyevu wa udongo, pamoja na kupokea maombi ya njia ya moja kwa moja.

> 💁 Unaweza kupata msimbo huu katika folda [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) au [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Programu yako ya sensor ya unyevu wa udongo imeunganishwa kwenye IoT Hub yako ukitumia cheti cha X.509!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati asilia katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.