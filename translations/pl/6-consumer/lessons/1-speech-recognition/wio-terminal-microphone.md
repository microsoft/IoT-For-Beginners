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

![Mikrofon w Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.pl.png)

Aby dodać głośnik, możesz użyć [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Jest to zewnętrzna płytka zawierająca 2 mikrofony MEMS, a także złącze głośnika i gniazdo słuchawkowe.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.pl.png)

Będziesz potrzebować słuchawek, głośnika z wtykiem 3,5 mm lub głośnika z połączeniem JST, takiego jak [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Do podłączenia ReSpeaker 2-Mics Pi Hat będziesz potrzebować 40 przewodów typu pin-to-pin (nazywanych również przewodami męski-męski).

> 💁 Jeśli potrafisz lutować, możesz użyć [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html), aby podłączyć ReSpeaker.

Będziesz także potrzebować karty SD do pobierania i odtwarzania dźwięku. Wio Terminal obsługuje tylko karty SD o pojemności do 16 GB, które muszą być sformatowane w systemie plików FAT32 lub exFAT.

### Zadanie - podłącz ReSpeaker Pi Hat

1. Przy wyłączonym Wio Terminal podłącz ReSpeaker 2-Mics Pi Hat do Wio Terminal za pomocą przewodów jumper i gniazd GPIO znajdujących się z tyłu Wio Terminal:

    Piny muszą być podłączone w następujący sposób:

    ![Schemat pinów](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.pl.png)

1. Ustaw ReSpeaker i Wio Terminal tak, aby gniazda GPIO były skierowane do góry i znajdowały się po lewej stronie.

1. Zacznij od gniazda w lewym górnym rogu gniazda GPIO na ReSpeaker. Podłącz przewód jumper od lewego górnego gniazda ReSpeaker do lewego górnego gniazda Wio Terminal.

1. Powtarzaj ten proces wzdłuż gniazd GPIO po lewej stronie. Upewnij się, że piny są dobrze osadzone.

    ![ReSpeaker z lewymi pinami podłączonymi do lewych pinów Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.pl.png)

    ![ReSpeaker z lewymi pinami podłączonymi do lewych pinów Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.pl.png)

    > 💁 Jeśli twoje przewody jumper są połączone w taśmy, trzymaj je razem - ułatwi to upewnienie się, że wszystkie przewody są podłączone w odpowiedniej kolejności.

1. Powtórz proces, używając prawych gniazd GPIO na ReSpeaker i Wio Terminal. Te przewody muszą przechodzić wokół już podłączonych przewodów.

    ![ReSpeaker z prawymi pinami podłączonymi do prawych pinów Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.pl.png)

    ![ReSpeaker z prawymi pinami podłączonymi do prawych pinów Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.pl.png)

    > 💁 Jeśli twoje przewody jumper są połączone w taśmy, rozdziel je na dwie taśmy. Przeprowadź każdą z nich po jednej stronie istniejących przewodów.

    > 💁 Możesz użyć taśmy klejącej, aby przytrzymać piny w bloku, co pomoże zapobiec ich wypadaniu podczas podłączania.

    > ![Piny zabezpieczone taśmą](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.pl.png)

1. Będziesz musiał dodać głośnik.

    * Jeśli używasz głośnika z kablem JST, podłącz go do portu JST na ReSpeaker.

      ![Głośnik podłączony do ReSpeaker za pomocą kabla JST](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.pl.png)

    * Jeśli używasz głośnika z wtykiem 3,5 mm lub słuchawek, włóż je do gniazda 3,5 mm.

      ![Głośnik podłączony do ReSpeaker przez gniazdo 3,5 mm](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.pl.png)

### Zadanie - skonfiguruj kartę SD

1. Podłącz kartę SD do komputera, używając zewnętrznego czytnika, jeśli nie masz wbudowanego gniazda na karty SD.

1. Sformatuj kartę SD za pomocą odpowiedniego narzędzia na swoim komputerze, upewniając się, że używasz systemu plików FAT32 lub exFAT.

1. Włóż kartę SD do gniazda na karty SD znajdującego się po lewej stronie Wio Terminal, tuż pod przyciskiem zasilania. Upewnij się, że karta jest całkowicie wsunięta i "kliknęła" - możesz potrzebować cienkiego narzędzia lub innej karty SD, aby pomóc ją wsunąć.

    ![Wkładanie karty SD do gniazda pod przełącznikiem zasilania](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.pl.png)

    > 💁 Aby wyjąć kartę SD, musisz ją lekko wcisnąć, aby się wysunęła. Do tego może być potrzebne cienkie narzędzie, takie jak płaski śrubokręt lub inna karta SD.

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.