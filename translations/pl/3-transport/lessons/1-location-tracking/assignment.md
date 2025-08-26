<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bded364fc06ce37d7a76aed3be1ba73a",
  "translation_date": "2025-08-26T07:32:26+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/assignment.md",
  "language_code": "pl"
}
-->
# Zbadaj inne dane GPS

## Instrukcje

Zdania NMEA pochodzące z Twojego czujnika GPS zawierają inne dane oprócz lokalizacji. Zbadaj dodatkowe dane i wykorzystaj je w swoim urządzeniu IoT.

Na przykład - czy możesz uzyskać aktualną datę i czas? Jeśli używasz mikrokontrolera, czy możesz ustawić zegar za pomocą danych GPS w taki sam sposób, jak robiłeś to za pomocą sygnałów NTP w poprzednim projekcie? Czy możesz uzyskać wysokość (swoją wysokość nad poziomem morza) lub aktualną prędkość?

Jeśli używasz wirtualnego urządzenia IoT, możesz uzyskać niektóre z tych danych, wysyłając zdania NMEA wygenerowane za pomocą narzędzi [nmeagen.org](https://www.nmeagen.org).

## Kryteria oceny

| Kryterium | Wzorowe | Wystarczające | Wymaga poprawy |
| --------- | ------- | ------------- | -------------- |
| Uzyskanie dodatkowych danych GPS | Potrafi uzyskać i wykorzystać dodatkowe dane GPS, zarówno jako telemetrię, jak i do konfiguracji urządzenia IoT | Potrafi uzyskać dodatkowe dane GPS, ale nie potrafi ich wykorzystać | Nie potrafi uzyskać dodatkowych danych GPS |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.