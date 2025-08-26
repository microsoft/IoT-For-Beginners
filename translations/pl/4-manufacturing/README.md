<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-26T06:30:00+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "pl"
}
-->
# Produkcja i przetwarzanie - wykorzystanie IoT do poprawy przetwarzania żywności

Gdy żywność dociera do centralnego punktu lub zakładu przetwórczego, nie zawsze jest od razu wysyłana do supermarketów. Często przechodzi przez szereg etapów przetwarzania, takich jak sortowanie według jakości. Jest to proces, który kiedyś był wykonywany ręcznie - zaczynał się na polu, gdzie zbieracze wybierali tylko dojrzałe owoce, a następnie w fabryce owoce jechały na taśmie, a pracownicy ręcznie usuwali uszkodzone lub zgniłe owoce. Sam miałem okazję zbierać i sortować truskawki jako wakacyjną pracę w szkole, więc mogę potwierdzić, że nie jest to przyjemne zajęcie.

Nowocześniejsze rozwiązania opierają się na IoT do sortowania. Jedne z pierwszych urządzeń, takie jak sortery od [Weco](https://wecotek.com), wykorzystują czujniki optyczne do wykrywania jakości produktów, odrzucając na przykład zielone pomidory. Mogą być stosowane zarówno w kombajnach na farmie, jak i w zakładach przetwórczych.

Wraz z postępem w dziedzinie sztucznej inteligencji (AI) i uczenia maszynowego (ML), te maszyny mogą stawać się coraz bardziej zaawansowane, wykorzystując modele ML trenowane do rozróżniania owoców od obcych obiektów, takich jak kamienie, ziemia czy owady. Modele te mogą być również trenowane do oceny jakości owoców, nie tylko wykrywania uszkodzeń, ale także wczesnego wykrywania chorób lub innych problemów z uprawami.

> 🎓 Termin *model ML* odnosi się do wyniku trenowania oprogramowania uczenia maszynowego na zestawie danych. Na przykład, można wytrenować model ML do rozróżniania dojrzałych i niedojrzałych pomidorów, a następnie używać tego modelu na nowych obrazach, aby sprawdzić, czy pomidory są dojrzałe czy nie.

W tych 4 lekcjach nauczysz się, jak trenować modele AI oparte na obrazach do oceny jakości owoców, jak korzystać z nich na urządzeniu IoT oraz jak uruchamiać je na urządzeniu brzegowym - czyli na urządzeniu IoT, a nie w chmurze.

> 💁 W tych lekcjach zostaną wykorzystane zasoby chmurowe. Jeśli nie ukończysz wszystkich lekcji w tym projekcie, upewnij się, że [posprzątasz swój projekt](../clean-up.md).

## Tematy

1. [Trenowanie detektora jakości owoców](./lessons/1-train-fruit-detector/README.md)
1. [Sprawdzanie jakości owoców z urządzenia IoT](./lessons/2-check-fruit-from-device/README.md)
1. [Uruchamianie detektora owoców na urządzeniu brzegowym](./lessons/3-run-fruit-detector-edge/README.md)
1. [Wyzwalanie detekcji jakości owoców za pomocą czujnika](./lessons/4-trigger-fruit-detector/README.md)

## Autorzy

Wszystkie lekcje zostały napisane z ♥️ przez [Jen Fox](https://github.com/jenfoxbot) i [Jim Bennett](https://GitHub.com/JimBobBennett)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.