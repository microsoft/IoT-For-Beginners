<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T22:24:11+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "nl"
}
-->
# Stel een timer in - Virtuele IoT-hardware en Raspberry Pi

In dit deel van de les roep je je serverloze code aan om de spraak te begrijpen en stel je een timer in op je virtuele IoT-apparaat of Raspberry Pi op basis van de resultaten.

## Stel een timer in

De tekst die terugkomt van de spraak-naar-tekst-aanroep moet naar je serverloze code worden gestuurd om door LUIS te worden verwerkt, waarbij het aantal seconden voor de timer wordt teruggegeven. Dit aantal seconden kan worden gebruikt om een timer in te stellen.

Timers kunnen worden ingesteld met behulp van de Python-klasse `threading.Timer`. Deze klasse neemt een wachttijd en een functie, en na de wachttijd wordt de functie uitgevoerd.

### Taak - stuur de tekst naar de serverloze functie

1. Open het `smart-timer`-project in VS Code en zorg ervoor dat de virtuele omgeving is geladen in de terminal als je een virtueel IoT-apparaat gebruikt.

1. Boven de functie `process_text`, declareer een functie genaamd `get_timer_time` om het REST-eindpunt dat je hebt gemaakt aan te roepen:

    ```python
    def get_timer_time(text):
    ```

1. Voeg de volgende code toe aan deze functie om de URL te definiëren die moet worden aangeroepen:

    ```python
    url = '<URL>'
    ```

    Vervang `<URL>` door de URL van je REST-eindpunt dat je in de vorige les hebt gebouwd, ofwel op je computer of in de cloud.

1. Voeg de volgende code toe om de tekst als een eigenschap door te geven in JSON-formaat bij de aanroep:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Haal hieronder de `seconds` op uit de response payload en geef 0 terug als de aanroep is mislukt:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Succesvolle HTTP-aanroepen geven een statuscode in het bereik van 200 terug, en je serverloze code geeft 200 terug als de tekst is verwerkt en herkend als de intentie om een timer in te stellen.

### Taak - stel een timer in op een achtergrondthread

1. Voeg de volgende importverklaring toe bovenaan het bestand om de threading-bibliotheek van Python te importeren:

    ```python
    import threading
    ```

1. Voeg boven de functie `process_text` een functie toe om een reactie uit te spreken. Voor nu zal deze alleen naar de console schrijven, maar later in deze les zal deze de tekst uitspreken.

    ```python
    def say(text):
        print(text)
    ```

1. Voeg hieronder een functie toe die door een timer wordt aangeroepen om aan te kondigen dat de timer is voltooid:

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

    Deze functie neemt het aantal minuten en seconden voor de timer en bouwt een zin om te zeggen dat de timer is voltooid. Het controleert het aantal minuten en seconden en neemt alleen elke tijdseenheid op als deze een waarde heeft. Bijvoorbeeld, als het aantal minuten 0 is, worden alleen seconden opgenomen in het bericht. Deze zin wordt vervolgens naar de functie `say` gestuurd.

1. Voeg hieronder de volgende functie `create_timer` toe om een timer te maken:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Deze functie neemt het totale aantal seconden voor de timer dat in het commando wordt verzonden en zet dit om in minuten en seconden. Vervolgens maakt en start het een timerobject met het totale aantal seconden, waarbij de functie `announce_timer` en een lijst met de minuten en seconden worden doorgegeven. Wanneer de timer afloopt, zal het de functie `announce_timer` aanroepen en de inhoud van deze lijst als parameters doorgeven - dus het eerste item in de lijst wordt doorgegeven als de parameter `minutes` en het tweede item als de parameter `seconds`.

1. Voeg aan het einde van de functie `create_timer` wat code toe om een bericht te bouwen dat aan de gebruiker wordt uitgesproken om aan te kondigen dat de timer begint:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Ook hier worden alleen de tijdseenheden opgenomen die een waarde hebben. Deze zin wordt vervolgens naar de functie `say` gestuurd.

1. Voeg het volgende toe aan het einde van de functie `process_text` om de tijd voor de timer uit de tekst te halen en vervolgens de timer te maken:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    De timer wordt alleen gemaakt als het aantal seconden groter is dan 0.

1. Voer de app uit en zorg ervoor dat de functie-app ook actief is. Stel enkele timers in en de uitvoer zal laten zien dat de timer wordt ingesteld en vervolgens laten zien wanneer deze afloopt:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Je kunt deze code vinden in de map [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) of [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Je timerprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.