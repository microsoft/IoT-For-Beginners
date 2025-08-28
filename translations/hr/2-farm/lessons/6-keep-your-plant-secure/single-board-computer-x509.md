<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-28T14:55:51+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "hr"
}
-->
# Koristite X.509 certifikat u kodu vašeg uređaja - Virtualni IoT hardver i Raspberry Pi

U ovom dijelu lekcije, povezat ćete svoj virtualni IoT uređaj ili Raspberry Pi s IoT Hubom koristeći X.509 certifikat.

## Povežite svoj uređaj s IoT Hubom

Sljedeći korak je povezivanje vašeg uređaja s IoT Hubom koristeći X.509 certifikate.

### Zadatak - povezivanje s IoT Hubom

1. Kopirajte datoteke ključa i certifikata u mapu koja sadrži kod vašeg IoT uređaja. Ako koristite Raspberry Pi putem VS Code Remote SSH i kreirali ste ključeve na svom PC-u ili Macu, možete povući i ispustiti datoteke u explorer u VS Code-u kako biste ih kopirali.

1. Otvorite datoteku `app.py`

1. Za povezivanje koristeći X.509 certifikat, trebat će vam naziv hosta IoT Huba i X.509 certifikat. Započnite stvaranjem varijable koja sadrži naziv hosta dodavanjem sljedećeg koda prije nego što se kreira klijent uređaja:

    ```python
    host_name = "<host_name>"
    ```

    Zamijenite `<host_name>` nazivom hosta vašeg IoT Huba. Možete ga pronaći u odjeljku `HostName` unutar `connection_string`. To će biti naziv vašeg IoT Huba, koji završava s `.azure-devices.net`.

1. Ispod toga, deklarirajte varijablu s ID-om uređaja:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Trebat će vam instanca klase `X509` koja sadrži X.509 datoteke. Dodajte `X509` na popis klasa uvezenih iz modula `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Kreirajte instancu klase `X509` koristeći vaše certifikate i datoteke ključeva dodavanjem ovog koda ispod deklaracije `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Ovo će kreirati klasu `X509` koristeći datoteke `soil-moisture-sensor-x509-cert.pem` i `soil-moisture-sensor-x509-key.pem` koje ste ranije kreirali.

1. Zamijenite liniju koda koja kreira `device_client` iz connection stringa sljedećim:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Ovo će se povezati koristeći X.509 certifikat umjesto connection stringa.

1. Obrišite liniju s varijablom `connection_string`.

1. Pokrenite svoj kod. Pratite poruke koje se šalju IoT Hubu i šaljite zahtjeve za direktne metode kao i prije. Vidjet ćete kako se uređaj povezuje i šalje očitanja vlažnosti tla, kao i prima zahtjeve za direktne metode.

> 💁 Ovaj kod možete pronaći u mapi [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) ili [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Vaš program senzora vlažnosti tla povezan je s vašim IoT Hubom koristeći X.509 certifikat!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.