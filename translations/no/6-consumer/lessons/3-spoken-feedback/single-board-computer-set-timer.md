<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T20:59:33+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "no"
}
-->
# Sett en timer - Virtuell IoT-maskinvare og Raspberry Pi

I denne delen av leksjonen vil du kjøre serverløs kode for å forstå tale og sette en timer på din virtuelle IoT-enhet eller Raspberry Pi basert på resultatene.

## Sett en timer

Teksten som kommer tilbake fra tale-til-tekst-kallet må sendes til din serverløse kode for å bli behandlet av LUIS, som returnerer antall sekunder for timeren. Dette antallet sekunder kan brukes til å sette en timer.

Timere kan settes ved hjelp av Python-klassen `threading.Timer`. Denne klassen tar en forsinkelsestid og en funksjon, og etter forsinkelsestiden blir funksjonen utført.

### Oppgave - send teksten til den serverløse funksjonen

1. Åpne prosjektet `smart-timer` i VS Code, og sørg for at det virtuelle miljøet er lastet inn i terminalen hvis du bruker en virtuell IoT-enhet.

1. Over funksjonen `process_text`, deklarer en funksjon kalt `get_timer_time` for å kalle REST-endepunktet du opprettet:

    ```python
    def get_timer_time(text):
    ```

1. Legg til følgende kode i denne funksjonen for å definere URL-en som skal kalles:

    ```python
    url = '<URL>'
    ```

    Erstatt `<URL>` med URL-en til ditt REST-endepunkt som du bygde i forrige leksjon, enten på din datamaskin eller i skyen.

1. Legg til følgende kode for å sette teksten som en egenskap som sendes som JSON til kallet:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Under dette, hent `seconds` fra responsens payload, og returner 0 hvis kallet mislyktes:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Vellykkede HTTP-kall returnerer en statuskode i 200-serien, og din serverløse kode returnerer 200 hvis teksten ble behandlet og gjenkjent som intensjonen for å sette en timer.

### Oppgave - sett en timer på en bakgrunnstråd

1. Legg til følgende import-setning øverst i filen for å importere Python-biblioteket threading:

    ```python
    import threading
    ```

1. Over funksjonen `process_text`, legg til en funksjon for å gi en respons. Foreløpig vil denne bare skrive til konsollen, men senere i leksjonen vil den lese opp teksten.

    ```python
    def say(text):
        print(text)
    ```

1. Under dette, legg til en funksjon som vil bli kalt av en timer for å annonsere at timeren er ferdig:

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

    Denne funksjonen tar antall minutter og sekunder for timeren og bygger en setning som sier at timeren er ferdig. Den vil sjekke antall minutter og sekunder, og kun inkludere hver tidsenhet hvis den har en verdi. For eksempel, hvis antall minutter er 0, vil kun sekunder inkluderes i meldingen. Denne setningen sendes deretter til funksjonen `say`.

1. Under dette, legg til følgende funksjon `create_timer` for å opprette en timer:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Denne funksjonen tar det totale antallet sekunder for timeren som skal sendes i kommandoen, og konverterer dette til minutter og sekunder. Den oppretter og starter deretter et timer-objekt ved hjelp av det totale antallet sekunder, og sender inn funksjonen `announce_timer` og en liste som inneholder minuttene og sekundene. Når timeren utløper, vil den kalle funksjonen `announce_timer` og sende innholdet i denne listen som parametere - slik at det første elementet i listen blir sendt som parameteren `minutes`, og det andre elementet som parameteren `seconds`.

1. Til slutt i funksjonen `create_timer`, legg til litt kode for å bygge en melding som skal leses opp til brukeren for å annonsere at timeren starter:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Igjen, dette inkluderer kun tidsenheten som har en verdi. Denne setningen sendes deretter til funksjonen `say`.

1. Legg til følgende på slutten av funksjonen `process_text` for å hente tiden for timeren fra teksten, og deretter opprette timeren:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Timeren opprettes kun hvis antall sekunder er større enn 0.

1. Kjør appen, og sørg for at funksjonsappen også kjører. Sett noen timere, og utdataene vil vise at timeren blir satt, og deretter vil det vises når den utløper:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Du finner denne koden i mappen [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) eller [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Timer-programmet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi tilstreber nøyaktighet, vennligst vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør betraktes som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.