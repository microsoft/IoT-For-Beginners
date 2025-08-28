<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-28T12:48:13+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "hr"
}
-->
# Postavite mjerač vremena - Virtualni IoT uređaj i Raspberry Pi

U ovom dijelu lekcije pozvat ćete svoj serverless kod kako biste razumjeli govor i postavili mjerač vremena na svom virtualnom IoT uređaju ili Raspberry Pi-u na temelju rezultata.

## Postavite mjerač vremena

Tekst koji se vraća iz poziva za pretvaranje govora u tekst treba poslati vašem serverless kodu kako bi ga obradio LUIS, koji će vratiti broj sekundi za mjerač vremena. Ovaj broj sekundi može se koristiti za postavljanje mjerača vremena.

Mjerači vremena mogu se postaviti pomoću Python klase `threading.Timer`. Ova klasa uzima vrijeme odgode i funkciju, a nakon isteka vremena odgode funkcija se izvršava.

### Zadatak - pošaljite tekst serverless funkciji

1. Otvorite projekt `smart-timer` u VS Code-u i osigurajte da je virtualno okruženje učitano u terminalu ako koristite virtualni IoT uređaj.

1. Iznad funkcije `process_text`, deklarirajte funkciju nazvanu `get_timer_time` za pozivanje REST krajnje točke koju ste kreirali:

    ```python
    def get_timer_time(text):
    ```

1. Dodajte sljedeći kod u ovu funkciju kako biste definirali URL za poziv:

    ```python
    url = '<URL>'
    ```

    Zamijenite `<URL>` s URL-om vaše REST krajnje točke koju ste izgradili u prošloj lekciji, bilo na vašem računalu ili u oblaku.

1. Dodajte sljedeći kod kako biste postavili tekst kao svojstvo koje se prosljeđuje kao JSON u pozivu:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Ispod toga, dohvatite `seconds` iz odgovora, vraćajući 0 ako poziv nije uspio:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Uspješni HTTP pozivi vraćaju statusni kod u rasponu 200, a vaš serverless kod vraća 200 ako je tekst obrađen i prepoznat kao namjera za postavljanje mjerača vremena.

### Zadatak - postavite mjerač vremena u pozadinskom threadu

1. Dodajte sljedeću naredbu za uvoz na vrh datoteke kako biste uvezli Python biblioteku threading:

    ```python
    import threading
    ```

1. Iznad funkcije `process_text`, dodajte funkciju za izgovaranje odgovora. Za sada će samo ispisivati na konzolu, ali kasnije u ovoj lekciji će izgovarati tekst.

    ```python
    def say(text):
        print(text)
    ```

1. Ispod toga dodajte funkciju koja će biti pozvana od strane mjerača vremena kako bi najavila da je mjerač vremena završen:

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

    Ova funkcija uzima broj minuta i sekundi za mjerač vremena i gradi rečenicu koja kaže da je mjerač vremena završen. Provjerit će broj minuta i sekundi te uključiti samo jedinicu vremena koja ima vrijednost. Na primjer, ako je broj minuta 0, tada se u poruci uključuju samo sekunde. Ova rečenica se zatim šalje funkciji `say`.

1. Ispod toga, dodajte sljedeću funkciju `create_timer` za kreiranje mjerača vremena:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Ova funkcija uzima ukupan broj sekundi za mjerač vremena koji će biti poslan u naredbi i pretvara ga u minute i sekunde. Zatim kreira i pokreće objekt mjerača vremena koristeći ukupan broj sekundi, prosljeđujući funkciju `announce_timer` i listu koja sadrži minute i sekunde. Kada mjerač vremena istekne, pozvat će funkciju `announce_timer` i proslijediti sadržaj ove liste kao parametre - tako da prvi element liste bude proslijeđen kao parametar `minutes`, a drugi element kao parametar `seconds`.

1. Na kraj funkcije `create_timer` dodajte kod za izgradnju poruke koja će se izgovoriti korisniku kako bi najavila da mjerač vremena počinje:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Opet, uključuje se samo jedinica vremena koja ima vrijednost. Ova rečenica se zatim šalje funkciji `say`.

1. Dodajte sljedeće na kraj funkcije `process_text` kako biste dobili vrijeme za mjerač vremena iz teksta, a zatim kreirali mjerač vremena:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Mjerač vremena se kreira samo ako je broj sekundi veći od 0.

1. Pokrenite aplikaciju i osigurajte da funkcijska aplikacija također radi. Postavite nekoliko mjerača vremena, a izlaz će pokazati da je mjerač vremena postavljen, a zatim će pokazati kada istekne:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) ili [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Vaš program za mjerač vremena bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešne interpretacije koje mogu proizaći iz korištenja ovog prijevoda.