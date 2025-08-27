<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T20:58:51+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "sv"
}
-->
# Ställ in en timer - Virtuell IoT-hårdvara och Raspberry Pi

I den här delen av lektionen kommer du att anropa din serverlösa kod för att förstå talet och ställa in en timer på din virtuella IoT-enhet eller Raspberry Pi baserat på resultaten.

## Ställ in en timer

Texten som kommer tillbaka från tal-till-text-anropet behöver skickas till din serverlösa kod för att bearbetas av LUIS, som returnerar antalet sekunder för timern. Detta antal sekunder kan användas för att ställa in en timer.

Timers kan ställas in med hjälp av Pythons `threading.Timer`-klass. Denna klass tar en fördröjningstid och en funktion, och efter fördröjningstiden körs funktionen.

### Uppgift - skicka texten till den serverlösa funktionen

1. Öppna projektet `smart-timer` i VS Code och se till att den virtuella miljön är laddad i terminalen om du använder en virtuell IoT-enhet.

1. Ovanför funktionen `process_text`, deklarera en funktion som heter `get_timer_time` för att anropa REST-endpunkten du skapade:

    ```python
    def get_timer_time(text):
    ```

1. Lägg till följande kod i denna funktion för att definiera URL:en som ska anropas:

    ```python
    url = '<URL>'
    ```

    Ersätt `<URL>` med URL:en till din REST-endpunkt som du byggde i den senaste lektionen, antingen på din dator eller i molnet.

1. Lägg till följande kod för att ange texten som en egenskap som skickas som JSON i anropet:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Nedanför detta, hämta `seconds` från svarspayloaden och returnera 0 om anropet misslyckades:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Lyckade HTTP-anrop returnerar en statuskod i 200-serien, och din serverlösa kod returnerar 200 om texten bearbetades och identifierades som en "set timer"-intention.

### Uppgift - ställ in en timer i en bakgrundstråd

1. Lägg till följande import-sats högst upp i filen för att importera Pythons threading-bibliotek:

    ```python
    import threading
    ```

1. Ovanför funktionen `process_text`, lägg till en funktion för att ge ett svar. För tillfället kommer detta bara att skriva till konsolen, men senare i lektionen kommer detta att läsa upp texten.

    ```python
    def say(text):
        print(text)
    ```

1. Nedanför detta, lägg till en funktion som kommer att anropas av en timer för att meddela att timern är klar:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    Denna funktion tar antalet minuter och sekunder för timern och bygger en mening som säger att timern är klar. Den kommer att kontrollera antalet minuter och sekunder och endast inkludera varje tidsenhet om den har ett värde. Till exempel, om antalet minuter är 0, inkluderas endast sekunder i meddelandet. Denna mening skickas sedan till funktionen `say`.

1. Nedanför detta, lägg till följande funktion `create_timer` för att skapa en timer:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Denna funktion tar det totala antalet sekunder för timern som skickas i kommandot och konverterar detta till minuter och sekunder. Den skapar och startar sedan ett timer-objekt med det totala antalet sekunder, och skickar in funktionen `announce_timer` och en lista som innehåller minuter och sekunder. När timern löper ut kommer den att anropa funktionen `announce_timer` och skicka innehållet i denna lista som parametrar - så det första objektet i listan skickas som parametern `minutes` och det andra objektet som parametern `seconds`.

1. I slutet av funktionen `create_timer`, lägg till lite kod för att bygga ett meddelande som ska läsas upp för användaren för att meddela att timern startar:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Återigen, detta inkluderar endast tidsenheten som har ett värde. Denna mening skickas sedan till funktionen `say`.

1. Lägg till följande i slutet av funktionen `process_text` för att hämta tiden för timern från texten och sedan skapa timern:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Timern skapas endast om antalet sekunder är större än 0.

1. Kör appen och se till att funktionsappen också körs. Ställ in några timers, och utdata kommer att visa att timern ställs in och sedan visa när den löper ut:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Du hittar denna kod i mappen [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) eller [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Ditt timerprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess modersmål bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.