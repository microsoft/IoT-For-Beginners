<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T20:59:11+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "da"
}
-->
# Indstil en timer - Virtuel IoT-hardware og Raspberry Pi

I denne del af lektionen vil du kalde din serverløse kode for at forstå talen og indstille en timer på din virtuelle IoT-enhed eller Raspberry Pi baseret på resultaterne.

## Indstil en timer

Den tekst, der kommer tilbage fra tale-til-tekst-kaldet, skal sendes til din serverløse kode for at blive behandlet af LUIS, som returnerer antallet af sekunder for timeren. Dette antal sekunder kan bruges til at indstille en timer.

Timere kan indstilles ved hjælp af Python-klassen `threading.Timer`. Denne klasse tager en forsinkelsestid og en funktion, og efter forsinkelsestiden udføres funktionen.

### Opgave - send teksten til den serverløse funktion

1. Åbn `smart-timer`-projektet i VS Code, og sørg for, at det virtuelle miljø er indlæst i terminalen, hvis du bruger en virtuel IoT-enhed.

1. Over funktionen `process_text`, deklarer en funktion kaldet `get_timer_time` for at kalde REST-endepunktet, du oprettede:

    ```python
    def get_timer_time(text):
    ```

1. Tilføj følgende kode til denne funktion for at definere URL'en, der skal kaldes:

    ```python
    url = '<URL>'
    ```

    Erstat `<URL>` med URL'en til dit REST-endepunkt, som du byggede i den sidste lektion, enten på din computer eller i skyen.

1. Tilføj følgende kode for at indstille teksten som en egenskab, der sendes som JSON til kaldet:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Under dette, hent `seconds` fra svarpayloaden, og returner 0, hvis kaldet mislykkedes:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Succesfulde HTTP-kald returnerer en statuskode i 200-området, og din serverløse kode returnerer 200, hvis teksten blev behandlet og genkendt som en "set timer"-intention.

### Opgave - indstil en timer på en baggrundstråd

1. Tilføj følgende import-sætning øverst i filen for at importere Python-biblioteket threading:

    ```python
    import threading
    ```

1. Over funktionen `process_text`, tilføj en funktion til at tale et svar. Indtil videre vil denne funktion blot skrive til konsollen, men senere i lektionen vil den tale teksten.

    ```python
    def say(text):
        print(text)
    ```

1. Under dette, tilføj en funktion, der vil blive kaldt af en timer for at annoncere, at timeren er færdig:

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

    Denne funktion tager antallet af minutter og sekunder for timeren og bygger en sætning, der siger, at timeren er færdig. Den vil kontrollere antallet af minutter og sekunder og kun inkludere hver tidsenhed, hvis den har en værdi. For eksempel, hvis antallet af minutter er 0, inkluderes kun sekunder i beskeden. Denne sætning sendes derefter til funktionen `say`.

1. Under dette, tilføj følgende funktion `create_timer` for at oprette en timer:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Denne funktion tager det samlede antal sekunder for timeren, der vil blive sendt i kommandoen, og konverterer dette til minutter og sekunder. Den opretter og starter derefter et timerobjekt ved hjælp af det samlede antal sekunder, og sender funktionen `announce_timer` og en liste, der indeholder minutter og sekunder. Når timeren udløber, vil den kalde funktionen `announce_timer` og sende indholdet af denne liste som parametre - så det første element i listen sendes som parameteren `minutes`, og det andet element som parameteren `seconds`.

1. Til slutningen af funktionen `create_timer`, tilføj noget kode for at bygge en besked, der skal tales til brugeren for at annoncere, at timeren starter:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Igen, dette inkluderer kun den tidsenhed, der har en værdi. Denne sætning sendes derefter til funktionen `say`.

1. Tilføj følgende til slutningen af funktionen `process_text` for at få tiden for timeren fra teksten og derefter oprette timeren:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Timeren oprettes kun, hvis antallet af sekunder er større end 0.

1. Kør appen, og sørg for, at funktionsappen også kører. Indstil nogle timere, og outputtet vil vise, at timeren bliver indstillet, og derefter vil det vise, når den udløber:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Du kan finde denne kode i mappen [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) eller [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Dit timerprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal det bemærkes, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os intet ansvar for misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.