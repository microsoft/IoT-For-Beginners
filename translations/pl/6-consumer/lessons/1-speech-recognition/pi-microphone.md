<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-26T07:26:10+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "pl"
}
-->
# Konfiguracja mikrofonu i głośników - Raspberry Pi

W tej części lekcji dodasz mikrofon i głośniki do swojego Raspberry Pi.

## Sprzęt

Raspberry Pi potrzebuje mikrofonu.

Pi nie ma wbudowanego mikrofonu, więc musisz podłączyć zewnętrzny mikrofon. Istnieje kilka sposobów, aby to zrobić:

* Mikrofon USB
* Zestaw słuchawkowy USB
* Zintegrowany głośnik konferencyjny USB
* Adapter audio USB i mikrofon z wtykiem 3,5 mm
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Mikrofony Bluetooth nie są w pełni obsługiwane na Raspberry Pi, więc jeśli masz mikrofon lub zestaw słuchawkowy Bluetooth, możesz napotkać problemy z parowaniem lub nagrywaniem dźwięku.

Raspberry Pi posiada gniazdo słuchawkowe 3,5 mm. Możesz je wykorzystać do podłączenia słuchawek, zestawu słuchawkowego lub głośnika. Możesz również dodać głośniki za pomocą:

* Dźwięku HDMI przez monitor lub telewizor
* Głośników USB
* Zestawu słuchawkowego USB
* Zintegrowanego głośnika konferencyjnego USB
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) z podłączonym głośnikiem, albo do gniazda 3,5 mm, albo do portu JST

## Podłączanie i konfiguracja mikrofonu i głośników

Mikrofon i głośniki muszą być podłączone i skonfigurowane.

### Zadanie - podłączanie i konfiguracja mikrofonu

1. Podłącz mikrofon odpowiednią metodą. Na przykład, podłącz go do jednego z portów USB.

1. Jeśli używasz ReSpeaker 2-Mics Pi HAT, możesz zdjąć bazowy hat Grove, a następnie zamontować hat ReSpeaker w jego miejsce.

    ![Raspberry Pi z zamontowanym hatem ReSpeaker](../../../../../translated_images/pl/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    W późniejszej części lekcji będziesz potrzebować przycisku Grove, ale jeden jest wbudowany w ten hat, więc bazowy hat Grove nie jest potrzebny.

    Po zamontowaniu hatu, musisz zainstalować sterowniki. Zapoznaj się z [instrukcjami rozpoczęcia pracy od Seeed](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) dotyczącymi instalacji sterowników.

    > ⚠️ Instrukcje używają `git` do klonowania repozytorium. Jeśli nie masz zainstalowanego `git` na swoim Pi, możesz go zainstalować, uruchamiając następujące polecenie:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Uruchom następujące polecenie w Terminalu na Pi lub połączonym za pomocą VS Code i sesji zdalnej SSH, aby zobaczyć informacje o podłączonym mikrofonie:

    ```sh
    arecord -l
    ```

    Zobaczysz listę podłączonych mikrofonów. Wygląda to mniej więcej tak:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Zakładając, że masz tylko jeden mikrofon, powinieneś zobaczyć tylko jeden wpis. Konfiguracja mikrofonów na Linuxie może być trudna, więc najłatwiej jest używać tylko jednego mikrofonu i odłączyć pozostałe.

    Zanotuj numer karty, ponieważ będzie potrzebny później. W powyższym przykładzie numer karty to 1.

### Zadanie - podłączanie i konfiguracja głośnika

1. Podłącz głośniki odpowiednią metodą.

1. Uruchom następujące polecenie w Terminalu na Pi lub połączonym za pomocą VS Code i sesji zdalnej SSH, aby zobaczyć informacje o podłączonych głośnikach:

    ```sh
    aplay -l
    ```

    Zobaczysz listę podłączonych głośników. Wygląda to mniej więcej tak:

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Zawsze zobaczysz `card 0: Headphones`, ponieważ jest to wbudowane gniazdo słuchawkowe. Jeśli dodałeś dodatkowe głośniki, takie jak głośnik USB, zobaczysz je również na liście.

1. Jeśli używasz dodatkowego głośnika, a nie głośnika lub słuchawek podłączonych do wbudowanego gniazda słuchawkowego, musisz skonfigurować go jako domyślny. Aby to zrobić, uruchom następujące polecenie:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Otworzy się plik konfiguracyjny w `nano`, edytorze tekstu działającym w terminalu. Przewiń w dół za pomocą strzałek na klawiaturze, aż znajdziesz następującą linię:

    ```output
    defaults.pcm.card 0
    ```

    Zmień wartość z `0` na numer karty, którą chcesz używać z listy uzyskanej z wywołania `aplay -l`. Na przykład, w powyższym przykładzie jest druga karta dźwiękowa o nazwie `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, używająca karty 1. Aby ją użyć, zaktualizowałbym linię do:

    ```output
    defaults.pcm.card 1
    ```

    Ustaw tę wartość na odpowiedni numer karty. Możesz nawigować do numeru za pomocą strzałek na klawiaturze, a następnie usunąć i wpisać nowy numer jak w przypadku edycji zwykłych plików tekstowych.

1. Zapisz zmiany i zamknij plik, naciskając `Ctrl+x`. Naciśnij `y`, aby zapisać plik, a następnie `Enter`, aby wybrać nazwę pliku.

### Zadanie - testowanie mikrofonu i głośnika

1. Uruchom następujące polecenie, aby nagrać 5 sekund dźwięku za pomocą mikrofonu:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Podczas działania tego polecenia wydawaj dźwięki do mikrofonu, na przykład mówiąc, śpiewając, beatboxując, grając na instrumencie lub robiąc cokolwiek, co Ci się podoba.

1. Po 5 sekundach nagrywanie się zatrzyma. Uruchom następujące polecenie, aby odtworzyć nagrany dźwięk:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Usłyszysz odtwarzany dźwięk przez głośniki. W razie potrzeby dostosuj głośność wyjściową na głośniku.

1. Jeśli musisz dostosować głośność wbudowanego portu mikrofonowego lub wzmocnienie mikrofonu, możesz użyć narzędzia `alsamixer`. Więcej informacji o tym narzędziu znajdziesz na [stronie man alsamixer dla Linuxa](https://linux.die.net/man/1/alsamixer).

1. Jeśli napotkasz błędy podczas odtwarzania dźwięku, sprawdź kartę ustawioną jako `defaults.pcm.card` w pliku `alsa.conf`.

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia wykonanego przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.