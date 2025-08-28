<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-28T12:21:06+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "hr"
}
-->
# Kreiranje virtualnog stroja koji pokreće IoT Edge

U Azureu možete kreirati virtualni stroj - računalo u oblaku koje možete konfigurirati na bilo koji način i pokretati vlastiti softver na njemu.

> 💁 Više o virtualnim strojevima možete pročitati na [stranici o virtualnim strojevima na Wikipediji](https://wikipedia.org/wiki/Virtual_machine).

## Zadatak - Postavljanje IoT Edge virtualnog stroja

1. Pokrenite sljedeću naredbu za kreiranje virtualnog stroja koji već ima unaprijed instaliran Azure IoT Edge:

    ```sh
    az deployment group create \
                --resource-group fruit-quality-detector \
                --template-uri https://raw.githubusercontent.com/Azure/iotedge-vm-deploy/1.2.0/edgeDeploy.json \
                --parameters dnsLabelPrefix=<vm_name> \
                --parameters adminUsername=<username> \
                --parameters deviceConnectionString="<connection_string>" \
                --parameters authenticationType=password \
                --parameters adminPasswordOrKey="<password>"
    ```

    Zamijenite `<vm_name>` nazivom za ovaj virtualni stroj. Naziv mora biti globalno jedinstven, pa koristite nešto poput `fruit-quality-detector-vm-` s vašim imenom ili nekom drugom vrijednošću na kraju.

    Zamijenite `<username>` i `<password>` korisničkim imenom i lozinkom koje ćete koristiti za prijavu na virtualni stroj. Lozinka mora biti relativno sigurna, pa ne možete koristiti admin/password.

    Zamijenite `<connection_string>` veznim nizom vašeg IoT Edge uređaja `fruit-quality-detector-edge`.

    Ova naredba će kreirati virtualni stroj konfiguriran kao `DS1 v2`. Ove kategorije označavaju koliko je stroj moćan, a time i koliko košta. Ovaj virtualni stroj ima 1 CPU i 3.5GB RAM-a.

    > 💰 Trenutne cijene ovih virtualnih strojeva možete vidjeti na [Azure vodiču za cijene virtualnih strojeva](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn).

    Kada se virtualni stroj kreira, IoT Edge runtime će se automatski instalirati i konfigurirati za povezivanje s vašim IoT Hubom kao uređajem `fruit-quality-detector-edge`.

1. Trebat će vam IP adresa ili DNS ime virtualnog stroja kako biste pozvali klasifikator slika s njega. Pokrenite sljedeću naredbu da biste to dobili:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Zabilježite vrijednost polja `PublicIps` ili polja `Fqdns`.

1. Virtualni strojevi koštaju novac. U trenutku pisanja, DS1 virtualni stroj košta oko $0.06 po satu. Kako biste smanjili troškove, trebali biste isključiti virtualni stroj kada ga ne koristite i obrisati ga kada završite s projektom.

    Možete konfigurirati svoj virtualni stroj da se automatski isključi u određeno vrijeme svaki dan. To znači da, ako zaboravite isključiti stroj, nećete biti naplaćeni za više od vremena do automatskog isključivanja. Koristite sljedeću naredbu za postavljanje:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Zamijenite `<vm_name>` nazivom vašeg virtualnog stroja.

    Zamijenite `<shutdown_time_utc>` UTC vremenom kada želite da se virtualni stroj isključi koristeći 4 znamenke u formatu HHMM. Na primjer, ako želite isključivanje u ponoć po UTC vremenu, postavite ovo na `0000`. Za 19:30 na zapadnoj obali SAD-a, koristite 0230 (19:30 na zapadnoj obali SAD-a je 2:30 po UTC vremenu).

1. Vaš klasifikator slika će se pokretati na ovom edge uređaju, slušajući na portu 80 (standardni HTTP port). Prema zadanim postavkama, virtualni strojevi imaju blokirane ulazne portove, pa ćete morati omogućiti port 80. Portovi se omogućuju na grupama sigurnosnih pravila mreže, pa prvo trebate saznati naziv grupe sigurnosnih pravila mreže za vaš virtualni stroj, što možete pronaći sljedećom naredbom:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Zabilježite vrijednost polja `Name`.

1. Pokrenite sljedeću naredbu za dodavanje pravila koje otvara port 80 u grupi sigurnosnih pravila mreže:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Zamijenite `<nsg name>` nazivom grupe sigurnosnih pravila mreže iz prethodnog koraka.

### Zadatak - upravljanje virtualnim strojem za smanjenje troškova

1. Kada ne koristite svoj virtualni stroj, trebali biste ga isključiti. Za isključivanje virtualnog stroja koristite sljedeću naredbu:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Zamijenite `<vm_name>` nazivom vašeg virtualnog stroja.

    > 💁 Postoji naredba `az vm stop` koja će zaustaviti virtualni stroj, ali računalo ostaje dodijeljeno vama, pa i dalje plaćate kao da je stroj pokrenut.

1. Za ponovno pokretanje virtualnog stroja koristite sljedeću naredbu:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Zamijenite `<vm_name>` nazivom vašeg virtualnog stroja.

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.