<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-26T06:39:14+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "pl"
}
-->
# Zbuduj detektor jakości owoców

## Instrukcje

Zbuduj detektor jakości owoców!

Wykorzystaj wszystko, czego nauczyłeś się do tej pory, aby stworzyć prototyp detektora jakości owoców. Uruchom klasyfikację obrazów na podstawie bliskości, korzystając z modelu AI działającego na urządzeniu brzegowym, zapisz wyniki klasyfikacji w pamięci, a następnie steruj diodą LED w zależności od dojrzałości owocu.

Powinieneś być w stanie złożyć to wszystko w całość, korzystając z kodu, który pisałeś we wszystkich dotychczasowych lekcjach.

## Kryteria oceny

| Kryterium | Wzorowe | Wystarczające | Wymaga poprawy |
| --------- | --------- | --------- | --------------- |
| Konfiguracja wszystkich usług | Udało się skonfigurować IoT Hub, aplikację Azure Functions i magazyn Azure | Udało się skonfigurować IoT Hub, ale nie aplikację Azure Functions lub magazyn Azure | Nie udało się skonfigurować żadnych usług IoT |
| Monitorowanie bliskości i wysyłanie danych do IoT Hub, jeśli obiekt znajduje się bliżej niż zdefiniowana odległość, oraz uruchamianie kamery za pomocą polecenia | Udało się zmierzyć odległość, wysłać wiadomość do IoT Hub, gdy obiekt był wystarczająco blisko, oraz wysłać polecenie uruchamiające kamerę | Udało się zmierzyć odległość i wysłać dane do IoT Hub, ale nie udało się wysłać polecenia do kamery | Nie udało się zmierzyć odległości, wysłać wiadomości do IoT Hub ani uruchomić polecenia |
| Przechwycenie obrazu, sklasyfikowanie go i wysłanie wyników do IoT Hub | Udało się przechwycić obraz, sklasyfikować go za pomocą urządzenia brzegowego i wysłać wyniki do IoT Hub | Udało się sklasyfikować obraz, ale nie za pomocą urządzenia brzegowego, lub nie udało się wysłać wyników do IoT Hub | Nie udało się sklasyfikować obrazu |
| Włączanie lub wyłączanie diody LED w zależności od wyników klasyfikacji za pomocą polecenia wysłanego do urządzenia | Udało się włączyć diodę LED za pomocą polecenia, jeśli owoc był niedojrzały | Udało się wysłać polecenie do urządzenia, ale nie udało się sterować diodą LED | Nie udało się wysłać polecenia do sterowania diodą LED |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.