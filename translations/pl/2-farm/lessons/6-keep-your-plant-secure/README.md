# Zabezpiecz swoją roślinę

![Szkicowy przegląd tej lekcji](../../../../../translated_images/pl/lesson-10.829c86b80b9403bb.webp)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obraz, aby zobaczyć większą wersję.

## Quiz przed wykładem

[Quiz przed wykładem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Wprowadzenie

W ostatnich lekcjach stworzyłeś urządzenie IoT monitorujące glebę i połączyłeś je z chmurą. Ale co, jeśli hakerzy pracujący dla konkurencyjnego rolnika przejęliby kontrolę nad Twoimi urządzeniami IoT? Co, jeśli wysyłaliby fałszywe odczyty wysokiej wilgotności gleby, przez co Twoje rośliny nigdy nie byłyby podlewane, albo włączyliby system nawadniania na stałe, co doprowadziłoby do przelania roślin i ogromnych kosztów za wodę?

W tej lekcji dowiesz się, jak zabezpieczyć urządzenia IoT. Ponieważ jest to ostatnia lekcja w tym projekcie, nauczysz się również, jak posprzątać swoje zasoby w chmurze, aby zminimalizować potencjalne koszty.

W tej lekcji omówimy:

* [Dlaczego musisz zabezpieczać urządzenia IoT?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Kryptografia](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Zabezpiecz swoje urządzenia IoT](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Generowanie i używanie certyfikatu X.509](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 To ostatnia lekcja w tym projekcie, więc po jej ukończeniu i wykonaniu zadania nie zapomnij posprzątać swoich usług w chmurze. Usługi będą potrzebne do ukończenia zadania, więc upewnij się, że najpierw je wykonasz.
>
> W razie potrzeby zapoznaj się z [przewodnikiem dotyczącym sprzątania projektu](../../../clean-up.md), aby uzyskać instrukcje, jak to zrobić.

## Dlaczego musisz zabezpieczać urządzenia IoT?

Bezpieczeństwo IoT polega na zapewnieniu, że tylko oczekiwane urządzenia mogą łączyć się z Twoją usługą IoT w chmurze i wysyłać do niej dane telemetryczne, a tylko Twoja usługa w chmurze może wysyłać polecenia do Twoich urządzeń. Dane IoT mogą być również osobiste, obejmując dane medyczne lub intymne, dlatego cała Twoja aplikacja musi uwzględniać bezpieczeństwo, aby zapobiec wyciekowi tych danych.

Jeśli Twoja aplikacja IoT nie jest bezpieczna, istnieje wiele ryzyk:

* Fałszywe urządzenie może wysyłać nieprawidłowe dane, powodując, że Twoja aplikacja zareaguje nieprawidłowo. Na przykład, mogłoby wysyłać ciągłe odczyty wysokiej wilgotności gleby, przez co system nawadniania nigdy by się nie włączał, a Twoje rośliny uschłyby z braku wody.
* Nieautoryzowani użytkownicy mogliby odczytywać dane z urządzeń IoT, w tym dane osobiste lub kluczowe dla biznesu.
* Hakerzy mogliby wysyłać polecenia, aby kontrolować urządzenie w sposób, który mógłby spowodować uszkodzenie urządzenia lub podłączonego sprzętu.
* Łącząc się z urządzeniem IoT, hakerzy mogliby uzyskać dostęp do dodatkowych sieci, aby dostać się do prywatnych systemów.
* Złośliwi użytkownicy mogliby uzyskać dostęp do danych osobowych i wykorzystać je do szantażu.

To są scenariusze z prawdziwego życia i zdarzają się cały czas. Niektóre przykłady zostały podane w poprzednich lekcjach, ale oto kilka kolejnych:

* W 2018 roku hakerzy wykorzystali otwarty punkt dostępu WiFi na termostacie akwarium, aby uzyskać dostęp do sieci kasyna i ukraść dane. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* W 2016 roku botnet Mirai przeprowadził atak typu denial of service na Dyn, dostawcę usług internetowych, co spowodowało zakłócenia w dużej części Internetu. Botnet ten używał złośliwego oprogramowania do łączenia się z urządzeniami IoT, takimi jak rejestratory DVR i kamery, które korzystały z domyślnych nazw użytkowników i haseł, a następnie przeprowadził atak. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys miało bazę danych użytkowników swoich zabawek CloudPets publicznie dostępną w Internecie. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava oznaczała biegaczy, których mijałeś, i pokazywała ich trasy, umożliwiając obcym osobom praktycznie zobaczenie, gdzie mieszkasz. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Zrób badania: Poszukaj więcej przykładów włamań do IoT i naruszeń danych IoT, zwłaszcza w przypadku przedmiotów osobistych, takich jak szczoteczki do zębów czy wagi podłączone do Internetu. Zastanów się, jaki wpływ te włamania mogłyby mieć na ofiary lub klientów.

> 💁 Bezpieczeństwo to ogromny temat, a ta lekcja poruszy jedynie podstawy związane z łączeniem urządzenia z chmurą. Inne tematy, które nie zostaną omówione, to monitorowanie zmian danych w trakcie przesyłu, bezpośrednie włamania do urządzeń czy zmiany konfiguracji urządzeń. Zagrożenie związane z hakowaniem IoT jest tak poważne, że opracowano narzędzia takie jak [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn). Narzędzia te są podobne do programów antywirusowych i zabezpieczających, które możesz mieć na swoim komputerze, ale są zaprojektowane dla małych, niskowydajnych urządzeń IoT.

## Kryptografia

Kiedy urządzenie łączy się z usługą IoT, używa identyfikatora, aby się zidentyfikować. Problem polega na tym, że ten identyfikator można sklonować – haker mógłby skonfigurować złośliwe urządzenie, które używa tego samego identyfikatora co prawdziwe urządzenie, ale wysyła fałszywe dane.

![Zarówno prawidłowe, jak i złośliwe urządzenia mogą używać tego samego identyfikatora do wysyłania telemetrii](../../../../../translated_images/pl/iot-device-and-hacked-device-connecting.e0671675df74d6d9.webp)

Rozwiązaniem tego problemu jest przekształcenie wysyłanych danych w zaszyfrowany format, używając wartości znanej tylko urządzeniu i chmurze. Proces ten nazywa się *szyfrowaniem*, a wartość używana do szyfrowania danych to *klucz szyfrujący*.

![Jeśli używane jest szyfrowanie, akceptowane są tylko zaszyfrowane wiadomości, inne są odrzucane](../../../../../translated_images/pl/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f.webp)

Usługa w chmurze może następnie przekształcić dane z powrotem w czytelny format, używając procesu zwanego *odszyfrowaniem*, korzystając z tego samego klucza szyfrującego lub *klucza deszyfrującego*. Jeśli zaszyfrowana wiadomość nie może zostać odszyfrowana za pomocą klucza, oznacza to, że urządzenie zostało zhakowane, a wiadomość jest odrzucana.

Technika szyfrowania i odszyfrowywania nazywa się *kryptografią*.

### Wczesna kryptografia

Najwcześniejsze rodzaje kryptografii to szyfry podstawieniowe, które sięgają 3500 lat wstecz. Szyfry podstawieniowe polegają na zastępowaniu jednej litery inną. Na przykład [szyfr Cezara](https://wikipedia.org/wiki/Caesar_cipher) polega na przesunięciu alfabetu o określoną liczbę miejsc, przy czym tylko nadawca zaszyfrowanej wiadomości i jej odbiorca wiedzą, o ile liter należy przesunąć.

[Szyfr Vigenère’a](https://wikipedia.org/wiki/Vigenère_cipher) poszedł o krok dalej, używając słów do szyfrowania tekstu, tak aby każda litera w oryginalnym tekście była przesunięta o inną wartość, zamiast zawsze przesuwać o tę samą liczbę liter.

Kryptografia była używana w różnych celach, takich jak ochrona receptury glazury garncarskiej w starożytnej Mezopotamii, pisanie sekretnych listów miłosnych w Indiach czy utrzymywanie w tajemnicy starożytnych egipskich zaklęć magicznych.

### Współczesna kryptografia

Współczesna kryptografia jest znacznie bardziej zaawansowana, co sprawia, że jest trudniejsza do złamania niż wczesne metody. Współczesna kryptografia wykorzystuje skomplikowaną matematykę do szyfrowania danych, zbyt skomplikowaną, aby ataki brute force były możliwe.

Kryptografia jest używana na wiele różnych sposobów w celu zapewnienia bezpiecznej komunikacji. Jeśli czytasz tę stronę na GitHubie, możesz zauważyć, że adres strony zaczyna się od *HTTPS*, co oznacza, że komunikacja między Twoją przeglądarką a serwerami GitHuba jest zaszyfrowana. Jeśli ktoś byłby w stanie odczytać ruch internetowy między Twoją przeglądarką a GitHubem, nie byłby w stanie odczytać danych, ponieważ są one zaszyfrowane. Twój komputer może nawet szyfrować wszystkie dane na dysku twardym, aby w przypadku kradzieży nikt nie mógł odczytać Twoich danych bez hasła.

> 🎓 HTTPS oznacza HyperText Transfer Protocol **Secure**

Niestety, nie wszystko jest bezpieczne. Niektóre urządzenia nie mają żadnych zabezpieczeń, inne są zabezpieczone łatwymi do złamania kluczami, a czasami wszystkie urządzenia tego samego typu używają tego samego klucza. Zdarzały się przypadki bardzo osobistych urządzeń IoT, które wszystkie miały to samo hasło do połączenia przez WiFi lub Bluetooth. Jeśli możesz połączyć się ze swoim urządzeniem, możesz połączyć się z urządzeniem innej osoby. Po połączeniu możesz uzyskać dostęp do bardzo prywatnych danych lub przejąć kontrolę nad ich urządzeniem.

> 💁 Pomimo złożoności współczesnej kryptografii i twierdzeń, że złamanie szyfrowania może zająć miliardy lat, rozwój komputerów kwantowych otworzył możliwość złamania wszystkich znanych metod szyfrowania w bardzo krótkim czasie!

### Klucze symetryczne i asymetryczne

Szyfrowanie występuje w dwóch rodzajach – symetrycznym i asymetrycznym.

**Symetryczne** szyfrowanie używa tego samego klucza do szyfrowania i odszyfrowywania danych. Zarówno nadawca, jak i odbiorca muszą znać ten sam klucz. Jest to najmniej bezpieczny rodzaj szyfrowania, ponieważ klucz musi zostać w jakiś sposób udostępniony. Aby nadawca mógł wysłać zaszyfrowaną wiadomość odbiorcy, nadawca najpierw musi przesłać odbiorcy klucz.

![Szyfrowanie symetryczne używa tego samego klucza do szyfrowania i odszyfrowywania wiadomości](../../../../../translated_images/pl/send-message-symmetric-key.a2e8ad0d495896ff.webp)

Jeśli klucz zostanie przechwycony podczas przesyłania lub jeśli nadawca lub odbiorca zostaną zhakowani i klucz zostanie znaleziony, szyfrowanie można złamać.

![Szyfrowanie symetryczne jest bezpieczne tylko wtedy, gdy haker nie przechwyci klucza – jeśli tak się stanie, może przechwycić i odszyfrować wiadomość](../../../../../translated_images/pl/send-message-symmetric-key-hacker.e7cb53db1707adfb.webp)

**Asymetryczne** szyfrowanie używa dwóch kluczy – klucza szyfrującego i klucza deszyfrującego, nazywanych parą kluczy publicznego i prywatnego. Klucz publiczny służy do szyfrowania wiadomości, ale nie można go użyć do jej odszyfrowania, natomiast klucz prywatny służy do odszyfrowania wiadomości, ale nie można go użyć do jej zaszyfrowania.

![Szyfrowanie asymetryczne używa różnych kluczy do szyfrowania i odszyfrowywania. Klucz szyfrujący jest wysyłany do nadawców wiadomości, aby mogli zaszyfrować wiadomość przed wysłaniem jej do odbiorcy, który posiada klucze](../../../../../translated_images/pl/send-message-asymmetric.7abe327c62615b8c.webp)

Odbiorca udostępnia swój klucz publiczny, a nadawca używa go do zaszyfrowania wiadomości. Po wysłaniu wiadomości odbiorca odszyfrowuje ją za pomocą swojego klucza prywatnego. Szyfrowanie asymetryczne jest bardziej bezpieczne, ponieważ klucz prywatny jest przechowywany w tajemnicy przez odbiorcę i nigdy nie jest udostępniany. Klucz publiczny może być dostępny dla każdego, ponieważ można go użyć tylko do szyfrowania wiadomości.

Szyfrowanie symetryczne jest szybsze niż asymetryczne, ale asymetryczne jest bardziej bezpieczne. Niektóre systemy używają obu rodzajów – asymetrycznego do szyfrowania i udostępniania klucza symetrycznego, a następnie symetrycznego do szyfrowania wszystkich danych. Dzięki temu udostępnianie klucza symetrycznego między nadawcą a odbiorcą jest bardziej bezpieczne, a szyfrowanie i odszyfrowywanie danych jest szybsze.

## Zabezpiecz swoje urządzenia IoT

Urządzenia IoT można zabezpieczyć za pomocą szyfrowania symetrycznego lub asymetrycznego. Szyfrowanie symetryczne jest łatwiejsze, ale mniej bezpieczne.

### Klucze symetryczne

Kiedy konfigurowałeś swoje urządzenie IoT do współpracy z IoT Hub, używałeś ciągu połączenia. Przykładowy ciąg połączenia wygląda następująco:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Ten ciąg połączenia składa się z trzech części oddzielonych średnikami, z każdą częścią będącą kluczem i wartością:

| Klucz | Wartość | Opis |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | Adres URL IoT Hub |
| DeviceId | `soil-moisture-sensor` | Unikalny identyfikator urządzenia |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | Klucz symetryczny znany urządzeniu i IoT Hub |

Ostatnia część tego ciągu połączenia, `SharedAccessKey`, to klucz symetryczny znany zarówno urządzeniu, jak i IoT Hub. Klucz ten nigdy nie jest wysyłany z urządzenia do chmury ani z chmury do urządzenia. Zamiast tego jest używany do szyfrowania danych, które są wysyłane lub odbierane.

✅ Zrób eksperyment. Jak myślisz, co się stanie, jeśli zmienisz część `SharedAccessKey` w ciągu połączenia podczas łączenia swojego urządzenia IoT? Wypróbuj to.

Kiedy urządzenie po raz pierwszy próbuje się połączyć, wysyła token podpisu dostępu współdzielonego (SAS) składający się z adresu URL IoT Hub, znacznika czasu, kiedy podpis dostępu wygaśnie (zazwyczaj 1 dzień od bieżącego czasu), oraz podpisu. Ten podpis składa się z adresu URL i czasu wygaśnięcia zaszyfrowanych za pomocą klucza dostępu współdzielonego z ciągu połączenia.

IoT Hub odszyfrowuje ten podpis za pomocą klucza dostępu współdzielonego i jeśli odszyfrowana wartość pasuje do adres
💁 Ze względu na czas wygaśnięcia, Twoje urządzenie IoT musi znać dokładny czas, który zazwyczaj jest odczytywany z serwera [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Jeśli czas nie jest dokładny, połączenie się nie powiedzie.
Po nawiązaniu połączenia wszystkie dane wysyłane do IoT Hub z urządzenia lub z IoT Hub do urządzenia będą szyfrowane za pomocą współdzielonego klucza dostępu.

✅ Co myślisz, że się stanie, jeśli wiele urządzeń będzie korzystać z tego samego ciągu połączenia?

> 💁 Przechowywanie tego klucza w kodzie to zła praktyka bezpieczeństwa. Jeśli haker uzyska dostęp do twojego kodu źródłowego, może zdobyć twój klucz. Utrudnia to również wydawanie kodu, ponieważ musiałbyś rekompilować go z zaktualizowanym kluczem dla każdego urządzenia. Lepiej jest załadować ten klucz z modułu bezpieczeństwa sprzętowego - układu na urządzeniu IoT, który przechowuje zaszyfrowane wartości, które mogą być odczytane przez twój kod.
>
> Podczas nauki IoT często łatwiej jest umieścić klucz w kodzie, tak jak zrobiłeś to w poprzedniej lekcji, ale musisz upewnić się, że ten klucz nie zostanie umieszczony w publicznym systemie kontroli wersji.

Urządzenia mają 2 klucze i 2 odpowiadające im ciągi połączenia. Pozwala to na rotację kluczy - czyli przełączanie się z jednego klucza na drugi, jeśli pierwszy zostanie skompromitowany, oraz ponowne wygenerowanie pierwszego klucza.

### Certyfikaty X.509

Kiedy używasz szyfrowania asymetrycznego z parą kluczy publiczny/prywatny, musisz dostarczyć swój klucz publiczny każdemu, kto chce wysłać ci dane. Problem polega na tym, jak odbiorca twojego klucza może być pewien, że to faktycznie twój klucz publiczny, a nie kogoś, kto się pod ciebie podszywa? Zamiast dostarczać klucz, możesz dostarczyć swój klucz publiczny w certyfikacie, który został zweryfikowany przez zaufaną trzecią stronę, zwaną certyfikatem X.509.

Certyfikaty X.509 to cyfrowe dokumenty zawierające klucz publiczny z pary kluczy publiczny/prywatny. Zazwyczaj są one wydawane przez jedną z wielu zaufanych organizacji zwanych [urzędy certyfikacji](https://wikipedia.org/wiki/Certificate_authority) (CAs) i cyfrowo podpisywane przez CA, aby wskazać, że klucz jest ważny i pochodzi od ciebie. Ufasz certyfikatowi i temu, że klucz publiczny pochodzi od osoby, którą certyfikat wskazuje, ponieważ ufasz CA, podobnie jak ufasz paszportowi lub prawu jazdy, ponieważ ufasz krajowi, który je wydał. Certyfikaty kosztują, więc możesz również „podpisać samodzielnie”, czyli stworzyć certyfikat samodzielnie, podpisany przez ciebie, do celów testowych.

> 💁 Nigdy nie powinieneś używać samopodpisanego certyfikatu w wersji produkcyjnej.

Te certyfikaty zawierają szereg pól, w tym informacje o tym, od kogo pochodzi klucz publiczny, szczegóły CA, który go wydał, jak długo jest ważny oraz sam klucz publiczny. Przed użyciem certyfikatu dobrą praktyką jest jego weryfikacja poprzez sprawdzenie, czy został podpisany przez oryginalny CA.

✅ Pełną listę pól w certyfikacie możesz przeczytać w [samouczku Microsoft Understanding X.509 Public Key Certificates](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields)

Podczas korzystania z certyfikatów X.509 zarówno nadawca, jak i odbiorca będą mieli swoje własne klucze publiczne i prywatne, a także certyfikaty X.509 zawierające klucz publiczny. Następnie wymieniają się certyfikatami X.509 w jakiś sposób, używając kluczy publicznych drugiej strony do szyfrowania danych, które wysyłają, oraz swoich własnych kluczy prywatnych do odszyfrowywania danych, które otrzymują.

![Zamiast udostępniać klucz publiczny, możesz udostępnić certyfikat. Użytkownik certyfikatu może zweryfikować, że pochodzi on od ciebie, sprawdzając u urzędu certyfikacji, który go podpisał.](../../../../../translated_images/pl/send-message-certificate.9cc576ac1e46b76e.webp)

Jedną z dużych zalet korzystania z certyfikatów X.509 jest to, że mogą być one współdzielone między urządzeniami. Możesz stworzyć jeden certyfikat, przesłać go do IoT Hub i używać go dla wszystkich swoich urządzeń. Każde urządzenie musi wtedy znać tylko klucz prywatny, aby odszyfrować wiadomości, które otrzymuje z IoT Hub.

Certyfikat używany przez twoje urządzenie do szyfrowania wiadomości wysyłanych do IoT Hub jest publikowany przez Microsoft. Jest to ten sam certyfikat, którego używa wiele usług Azure i czasami jest wbudowany w SDK.

> 💁 Pamiętaj, klucz publiczny jest właśnie tym - publiczny. Klucz publiczny Azure może być używany tylko do szyfrowania danych wysyłanych do Azure, a nie do ich odszyfrowywania, więc może być udostępniany wszędzie, w tym w kodzie źródłowym. Na przykład możesz go zobaczyć w [kodzie źródłowym Azure IoT C SDK](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c).

✅ Istnieje wiele żargonu związanego z certyfikatami X.509. Możesz przeczytać definicje niektórych terminów, które możesz napotkać, w [Przewodniku po żargonie certyfikatów X.509 dla laików](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn)

## Generowanie i używanie certyfikatu X.509

Kroki do wygenerowania certyfikatu X.509 są następujące:

1. Utwórz parę kluczy publiczny/prywatny. Jednym z najczęściej używanych algorytmów do generowania pary kluczy publiczny/prywatny jest [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem))(RSA).

1. Prześlij klucz publiczny z powiązanymi danymi do podpisania, albo przez CA, albo przez samopodpisanie.

Azure CLI ma polecenia do tworzenia nowej tożsamości urządzenia w IoT Hub, automatycznego generowania pary kluczy publiczny/prywatny oraz tworzenia samopodpisanego certyfikatu.

> 💁 Jeśli chcesz zobaczyć szczegółowe kroki, zamiast używać Azure CLI, możesz znaleźć je w [samouczku Microsoft IoT Hub dotyczącym używania OpenSSL do tworzenia samopodpisanych certyfikatów](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn)

### Zadanie - utwórz tożsamość urządzenia za pomocą certyfikatu X.509

1. Uruchom następujące polecenie, aby zarejestrować nową tożsamość urządzenia, automatycznie generując klucze i certyfikaty:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Zamień `<hub_name>` na nazwę, której użyłeś dla swojego IoT Hub.

    To polecenie utworzy urządzenie o identyfikatorze `soil-moisture-sensor-x509`, aby odróżnić je od tożsamości urządzenia, którą utworzyłeś w poprzedniej lekcji. To polecenie utworzy również 2 pliki w bieżącym katalogu:

    * `soil-moisture-sensor-x509-key.pem` - ten plik zawiera klucz prywatny urządzenia.
    * `soil-moisture-sensor-x509-cert.pem` - to plik certyfikatu X.509 dla urządzenia.

    Przechowuj te pliki w bezpiecznym miejscu! Plik z kluczem prywatnym nie powinien być umieszczany w publicznym systemie kontroli wersji.

### Zadanie - użyj certyfikatu X.509 w kodzie swojego urządzenia

Przejdź przez odpowiedni przewodnik, aby połączyć swoje urządzenie IoT z chmurą za pomocą certyfikatu X.509:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Komputer jednopłytkowy - Raspberry Pi/Wirtualne urządzenie IoT](single-board-computer-x509.md)

---

## 🚀 Wyzwanie

Istnieje wiele sposobów tworzenia, zarządzania i usuwania usług Azure, takich jak Grupy Zasobów i IoT Hub. Jednym z nich jest [Azure Portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) - interfejs internetowy, który oferuje GUI do zarządzania usługami Azure.

Przejdź na [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) i zapoznaj się z portalem. Sprawdź, czy potrafisz utworzyć IoT Hub za pomocą portalu, a następnie go usunąć.

**Wskazówka** - podczas tworzenia usług przez portal nie musisz tworzyć Grupy Zasobów z wyprzedzeniem, można ją utworzyć podczas tworzenia usługi. Upewnij się, że usuniesz ją, gdy skończysz!

W dokumentacji portalu Azure znajdziesz wiele dokumentów, samouczków i przewodników: [Azure portal documentation](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Przegląd i samodzielna nauka

* Przeczytaj o historii kryptografii na stronie [Historia kryptografii na Wikipedii](https://wikipedia.org/wiki/History_of_cryptography).
* Przeczytaj o certyfikatach X.509 na stronie [X.509 na Wikipedii](https://wikipedia.org/wiki/X.509).

## Zadanie

[Zbuduj nowe urządzenie IoT](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia wykonanego przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.