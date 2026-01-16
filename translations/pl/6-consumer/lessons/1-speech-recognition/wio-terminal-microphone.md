<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-26T07:26:38+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "pl"
}
-->
# Skonfiguruj mikrofon i głośniki - Wio Terminal

W tej części lekcji dodasz głośniki do swojego Wio Terminal. Wio Terminal ma już wbudowany mikrofon, który może być używany do rejestrowania mowy.

## Sprzęt

Wio Terminal ma już wbudowany mikrofon, który może być używany do rejestrowania dźwięku na potrzeby rozpoznawania mowy.

![Mikrofon w Wio Terminal](../../../../../translated_images/pl/wio-mic.3f8c843dbe8ad917.png)

Aby dodać głośnik, możesz użyć [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Jest to zewnętrzna płytka zawierająca 2 mikrofony MEMS, a także złącze głośnika i gniazdo słuchawkowe.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/pl/respeaker.f5d19d1c6b14ab16.png)

Będziesz potrzebować słuchawek, głośnika z wtykiem 3,5 mm lub głośnika z połączeniem JST, takiego jak [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Do podłączenia ReSpeaker 2-Mics Pi Hat będziesz potrzebować 40 przewodów typu pin-to-pin (nazywanych również przewodami męski-męski).

> 💁 Jeśli potrafisz lutować, możesz użyć [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html), aby podłączyć ReSpeaker.

Będziesz także potrzebować karty SD do pobierania i odtwarzania dźwięku. Wio Terminal obsługuje tylko karty SD o pojemności do 16 GB, które muszą być sformatowane w systemie plików FAT32 lub exFAT.

### Zadanie - podłącz ReSpeaker Pi Hat

1. Przy wyłączonym Wio Terminal podłącz ReSpeaker 2-Mics Pi Hat do Wio Terminal za pomocą przewodów jumper i gniazd GPIO znajdujących się z tyłu Wio Terminal:

    Piny muszą być podłączone w następujący sposób:

    ![Schemat pinów](../../../../../translated_images/pl/wio-respeaker-wiring-0.767f80aa65081038.png)

1. Ustaw ReSpeaker i Wio Terminal tak, aby gniazda GPIO były skierowane do góry i znajdowały się po lewej stronie.

1. Zacznij od gniazda w lewym górnym rogu gniazda GPIO na ReSpeaker. Podłącz przewód jumper od lewego górnego gniazda ReSpeaker do lewego górnego gniazda Wio Terminal.

1. Powtarzaj ten proces wzdłuż gniazd GPIO po lewej stronie. Upewnij się, że piny są dobrze osadzone.

    ![ReSpeaker z lewymi pinami podłączonymi do lewych pinów Wio Terminal](../../../../../translated_images/pl/wio-respeaker-wiring-1.8d894727f2ba2400.png)

    ![ReSpeaker z lewymi pinami podłączonymi do lewych pinów Wio Terminal](../../../../../translated_images/pl/wio-respeaker-wiring-2.329e1cbd306e754f.png)

    > 💁 Jeśli twoje przewody jumper są połączone w taśmy, trzymaj je razem - ułatwi to upewnienie się, że wszystkie przewody są podłączone w odpowiedniej kolejności.

1. Powtórz proces, używając prawych gniazd GPIO na ReSpeaker i Wio Terminal. Te przewody muszą przechodzić wokół już podłączonych przewodów.

    ![ReSpeaker z prawymi pinami podłączonymi do prawych pinów Wio Terminal](../../../../../translated_images/pl/wio-respeaker-wiring-3.75b0be447e2fa930.png)

    ![ReSpeaker z prawymi pinami podłączonymi do prawych pinów Wio Terminal](../../../../../translated_images/pl/wio-respeaker-wiring-4.aa9cd434d8779437.png)

    > 💁 Jeśli twoje przewody jumper są połączone w taśmy, rozdziel je na dwie taśmy. Przeprowadź każdą z nich po jednej stronie istniejących przewodów.

    > 💁 Możesz użyć taśmy klejącej, aby przytrzymać piny w bloku, co pomoże zapobiec ich wypadaniu podczas podłączania.

    > ![Piny zabezpieczone taśmą](../../../../../translated_images/pl/wio-respeaker-wiring-5.af117c20acf622f3.png)

1. Będziesz musiał dodać głośnik.

    * Jeśli używasz głośnika z kablem JST, podłącz go do portu JST na ReSpeaker.

      ![Głośnik podłączony do ReSpeaker za pomocą kabla JST](../../../../../translated_images/pl/respeaker-jst-speaker.a441d177809df945.png)

    * Jeśli używasz głośnika z wtykiem 3,5 mm lub słuchawek, włóż je do gniazda 3,5 mm.

      ![Głośnik podłączony do ReSpeaker przez gniazdo 3,5 mm](../../../../../translated_images/pl/respeaker-35mm-speaker.ad79ef4f128c7751.png)

### Zadanie - skonfiguruj kartę SD

1. Podłącz kartę SD do komputera, używając zewnętrznego czytnika, jeśli nie masz wbudowanego gniazda na karty SD.

1. Sformatuj kartę SD za pomocą odpowiedniego narzędzia na swoim komputerze, upewniając się, że używasz systemu plików FAT32 lub exFAT.

1. Włóż kartę SD do gniazda na karty SD znajdującego się po lewej stronie Wio Terminal, tuż pod przyciskiem zasilania. Upewnij się, że karta jest całkowicie wsunięta i "kliknęła" - możesz potrzebować cienkiego narzędzia lub innej karty SD, aby pomóc ją wsunąć.

    ![Wkładanie karty SD do gniazda pod przełącznikiem zasilania](../../../../../translated_images/pl/wio-sd-card.acdcbe322fa4ee7f.png)

    > 💁 Aby wyjąć kartę SD, musisz ją lekko wcisnąć, aby się wysunęła. Do tego może być potrzebne cienkie narzędzie, takie jak płaski śrubokręt lub inna karta SD.

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.