<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e978534a245b000725ed2a048f943213",
  "translation_date": "2025-08-26T07:27:35+00:00",
  "source_file": "3-transport/README.md",
  "language_code": "pl"
}
-->
# Transport z farmy do fabryki - wykorzystanie IoT do śledzenia dostaw żywności

Wielu rolników uprawia żywność na sprzedaż – albo są to rolnicy komercyjni, którzy sprzedają wszystko, co wyprodukują, albo rolnicy samozaopatrzeniowi, którzy sprzedają nadwyżki, aby kupić niezbędne rzeczy. W jakiś sposób żywność musi trafić z farmy do konsumenta, a zazwyczaj odbywa się to za pomocą transportu zbiorowego z farm do centrów dystrybucji lub zakładów przetwórczych, a następnie do sklepów. Na przykład rolnik uprawiający pomidory zbiera je, pakuje do skrzynek, ładuje skrzynki na ciężarówkę, a następnie dostarcza do zakładu przetwórczego. Tam pomidory są sortowane, a następnie trafiają do konsumentów w postaci przetworzonej żywności, sprzedaży detalicznej lub są spożywane w restauracjach.

IoT może wspomóc ten łańcuch dostaw, śledząc żywność w trakcie transportu – zapewniając, że kierowcy jadą tam, gdzie powinni, monitorując lokalizację pojazdów i wysyłając powiadomienia, gdy pojazdy dotrą na miejsce, aby żywność mogła zostać rozładowana i była gotowa do przetworzenia tak szybko, jak to możliwe.

> 🎓 *Łańcuch dostaw* to sekwencja działań prowadzących do wytworzenia i dostarczenia czegoś. Na przykład w przypadku uprawy pomidorów obejmuje to dostarczenie nasion, gleby, nawozów i wody, uprawę pomidorów, dostarczenie ich do centralnego punktu, transport do lokalnego centrum supermarketu, transport do poszczególnych sklepów, wystawienie na półki, sprzedaż konsumentowi i zabranie do domu w celu spożycia. Każdy etap jest jak ogniwo w łańcuchu.

> 🎓 Część łańcucha dostaw związana z transportem nazywana jest *logistyką*.

W tych 4 lekcjach dowiesz się, jak zastosować Internet Rzeczy (IoT), aby usprawnić łańcuch dostaw poprzez monitorowanie żywności podczas jej załadunku na (wirtualną) ciężarówkę, która jest śledzona w drodze do miejsca docelowego. Nauczysz się, jak działa śledzenie GPS, jak przechowywać i wizualizować dane GPS oraz jak otrzymywać powiadomienia, gdy ciężarówka dotrze na miejsce.

> 💁 Te lekcje będą korzystać z niektórych zasobów w chmurze. Jeśli nie ukończysz wszystkich lekcji w tym projekcie, upewnij się, że [wyczyścisz swój projekt](../clean-up.md).

## Tematy

1. [Śledzenie lokalizacji](lessons/1-location-tracking/README.md)  
1. [Przechowywanie danych lokalizacyjnych](lessons/2-store-location-data/README.md)  
1. [Wizualizacja danych lokalizacyjnych](lessons/3-visualize-location-data/README.md)  
1. [Geosiatki](lessons/4-geofences/README.md)  

## Podziękowania

Wszystkie lekcje zostały napisane z ♥️ przez [Jen Looper](https://github.com/jlooper) i [Jim Bennett](https://GitHub.com/JimBobBennett)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia wykonanego przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.