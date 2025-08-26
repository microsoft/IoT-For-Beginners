<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-26T06:37:23+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "pl"
}
-->
# Utwórz maszynę wirtualną z uruchomionym IoT Edge

W Azure możesz utworzyć maszynę wirtualną - komputer w chmurze, który możesz skonfigurować według własnych potrzeb i uruchomić na nim własne oprogramowanie.

> 💁 Więcej informacji o maszynach wirtualnych znajdziesz na [stronie Wikipedii o maszynach wirtualnych](https://wikipedia.org/wiki/Virtual_machine).

## Zadanie - Skonfiguruj maszynę wirtualną z IoT Edge

1. Uruchom poniższe polecenie, aby utworzyć maszynę wirtualną z już zainstalowanym Azure IoT Edge:

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

    Zamień `<vm_name>` na nazwę dla tej maszyny wirtualnej. Nazwa musi być unikalna globalnie, więc użyj czegoś w stylu `fruit-quality-detector-vm-` z Twoim imieniem lub inną wartością na końcu.

    Zamień `<username>` i `<password>` na nazwę użytkownika i hasło, które będą używane do logowania do maszyny wirtualnej. Muszą być one stosunkowo bezpieczne, więc nie możesz użyć admin/password.

    Zamień `<connection_string>` na ciąg połączenia swojego urządzenia IoT Edge `fruit-quality-detector-edge`.

    To polecenie utworzy maszynę wirtualną skonfigurowaną jako `DS1 v2`. Kategorie te wskazują na moc maszyny, a co za tym idzie, jej koszt. Ta maszyna wirtualna ma 1 CPU i 3,5 GB RAM.

    > 💰 Aktualne ceny tych maszyn wirtualnych znajdziesz w [przewodniku cenowym Azure Virtual Machine](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Po utworzeniu maszyny wirtualnej, środowisko IoT Edge zostanie automatycznie zainstalowane i skonfigurowane do połączenia z Twoim IoT Hub jako urządzenie `fruit-quality-detector-edge`.

1. Aby wywołać klasyfikator obrazów z maszyny wirtualnej, będziesz potrzebować jej adresu IP lub nazwy DNS. Uruchom poniższe polecenie, aby je uzyskać:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Skopiuj wartość z pola `PublicIps` lub `Fqdns`.

1. Maszyny wirtualne generują koszty. W momencie pisania tego tekstu, maszyna DS1 kosztuje około $0.06 za godzinę. Aby ograniczyć koszty, powinieneś wyłączać maszynę wirtualną, gdy jej nie używasz, oraz usuwać ją po zakończeniu projektu.

    Możesz skonfigurować maszynę wirtualną tak, aby automatycznie wyłączała się o określonej godzinie każdego dnia. Dzięki temu, jeśli zapomnisz ją wyłączyć, nie będziesz obciążony kosztami za czas przekraczający automatyczne wyłączenie. Użyj poniższego polecenia, aby to ustawić:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Zamień `<vm_name>` na nazwę swojej maszyny wirtualnej.

    Zamień `<shutdown_time_utc>` na czas UTC, o którym chcesz wyłączyć maszynę wirtualną, używając 4 cyfr w formacie HHMM. Na przykład, jeśli chcesz wyłączyć maszynę o północy UTC, ustaw wartość na `0000`. Dla godziny 19:30 czasu zachodniego wybrzeża USA, użyj `0230` (19:30 czasu zachodniego wybrzeża USA to 2:30 UTC).

1. Twój klasyfikator obrazów będzie działał na tym urządzeniu edge, nasłuchując na porcie 80 (standardowy port HTTP). Domyślnie maszyny wirtualne mają zablokowane porty przychodzące, więc musisz odblokować port 80. Porty są odblokowywane w grupach zabezpieczeń sieciowych, więc najpierw musisz znać nazwę grupy zabezpieczeń sieciowych dla swojej maszyny wirtualnej, którą możesz znaleźć za pomocą poniższego polecenia:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Skopiuj wartość z pola `Name`.

1. Uruchom poniższe polecenie, aby dodać regułę otwierającą port 80 w grupie zabezpieczeń sieciowych:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Zamień `<nsg name>` na nazwę grupy zabezpieczeń sieciowych z poprzedniego kroku.

### Zadanie - zarządzaj swoją maszyną wirtualną, aby zmniejszyć koszty

1. Gdy nie używasz swojej maszyny wirtualnej, powinieneś ją wyłączyć. Aby wyłączyć maszynę wirtualną, użyj poniższego polecenia:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Zamień `<vm_name>` na nazwę swojej maszyny wirtualnej.

    > 💁 Istnieje polecenie `az vm stop`, które zatrzymuje maszynę wirtualną, ale nadal utrzymuje komputer przypisany do Ciebie, więc nadal płacisz, jakby była uruchomiona.

1. Aby ponownie uruchomić maszynę wirtualną, użyj poniższego polecenia:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Zamień `<vm_name>` na nazwę swojej maszyny wirtualnej.

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.