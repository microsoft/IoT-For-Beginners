<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-26T06:24:13+00:00",
  "source_file": "clean-up.md",
  "language_code": "pl"
}
-->
# Posprzątaj swój projekt

Po zakończeniu każdego projektu warto usunąć zasoby w chmurze.

Podczas lekcji związanych z każdym projektem mogłeś utworzyć niektóre z poniższych zasobów:

* Grupę zasobów (Resource Group)
* IoT Hub
* Rejestracje urządzeń IoT
* Konto magazynu (Storage Account)
* Aplikację Functions App
* Konto Azure Maps
* Projekt Custom Vision
* Rejestr kontenerów Azure (Azure Container Registry)
* Zasób usług kognitywnych (Cognitive Services)

Większość z tych zasobów nie generuje kosztów – albo są całkowicie darmowe, albo korzystasz z darmowego poziomu. W przypadku usług wymagających płatnego poziomu, korzystałeś z nich na poziomie objętym darmowym limitem lub kosztowały one tylko kilka groszy.

Nawet przy stosunkowo niskich kosztach warto usunąć te zasoby po zakończeniu pracy. Na przykład, możesz mieć tylko jeden IoT Hub korzystający z darmowego poziomu, więc jeśli chcesz utworzyć kolejny, będziesz musiał skorzystać z płatnego poziomu.

Wszystkie Twoje usługi zostały utworzone w ramach Grup Zasobów, co ułatwia zarządzanie. Możesz usunąć Grupę Zasobów, a wszystkie usługi w niej zawarte zostaną usunięte razem z nią.

Aby usunąć Grupę Zasobów, uruchom następujące polecenie w terminalu lub wierszu poleceń:

```sh
az group delete --name <resource-group-name>
```

Zastąp `<resource-group-name>` nazwą Grupy Zasobów, którą chcesz usunąć.

Pojawi się potwierdzenie:

```output
Are you sure you want to perform this operation? (y/n): 
```

Wpisz `y`, aby potwierdzić i usunąć Grupę Zasobów.

Usunięcie wszystkich usług może zająć trochę czasu.

> 💁 Więcej informacji na temat usuwania grup zasobów znajdziesz w [dokumentacji Microsoft Docs dotyczącej usuwania grup zasobów i zasobów w Azure Resource Manager](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.