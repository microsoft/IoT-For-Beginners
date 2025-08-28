<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-28T12:48:29+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "sl"
}
-->
# Nastavite časovnik - Virtualna IoT strojna oprema in Raspberry Pi

V tem delu lekcije boste poklicali svojo strežniško kodo, da razumete govor, in nastavili časovnik na svoji virtualni IoT napravi ali Raspberry Pi glede na rezultate.

## Nastavite časovnik

Besedilo, ki ga dobite iz klica za pretvorbo govora v besedilo, je treba poslati vaši strežniški kodi, da ga obdela LUIS, ki vrne število sekund za časovnik. To število sekund lahko uporabite za nastavitev časovnika.

Časovnike lahko nastavite z uporabo razreda Python `threading.Timer`. Ta razred sprejme čas zakasnitve in funkcijo, ki se izvede po preteku zakasnitve.

### Naloga - pošljite besedilo strežniški funkciji

1. Odprite projekt `smart-timer` v VS Code in se prepričajte, da je virtualno okolje naloženo v terminalu, če uporabljate virtualno IoT napravo.

1. Nad funkcijo `process_text` deklarirajte funkcijo z imenom `get_timer_time`, ki bo poklicala REST končno točko, ki ste jo ustvarili:

    ```python
    def get_timer_time(text):
    ```

1. Dodajte naslednjo kodo tej funkciji, da definirate URL, ki ga je treba poklicati:

    ```python
    url = '<URL>'
    ```

    Zamenjajte `<URL>` z URL-jem vaše REST končne točke, ki ste jo zgradili v prejšnji lekciji, bodisi na svojem računalniku bodisi v oblaku.

1. Dodajte naslednjo kodo, da nastavite besedilo kot lastnost, ki se pošlje kot JSON v klic:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Pod tem pridobite `seconds` iz odzivnega paketa, pri čemer vrnite 0, če je klic spodletel:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Uspešni HTTP klici vrnejo statusno kodo v območju 200, vaša strežniška koda pa vrne 200, če je bilo besedilo obdelano in prepoznano kot namen za nastavitev časovnika.

### Naloga - nastavite časovnik v ozadju

1. Na vrhu datoteke dodajte naslednjo uvozno izjavo, da uvozite knjižnico Python `threading`:

    ```python
    import threading
    ```

1. Nad funkcijo `process_text` dodajte funkcijo za izgovor odgovora. Za zdaj bo ta funkcija samo pisala v konzolo, kasneje v tej lekciji pa bo izgovarjala besedilo.

    ```python
    def say(text):
        print(text)
    ```

1. Pod to funkcijo dodajte funkcijo, ki jo bo poklical časovnik, da naznani, da je časovnik končan:

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

    Ta funkcija sprejme število minut in sekund za časovnik ter sestavi stavek, ki pove, da je časovnik končan. Preveri število minut in sekund ter vključi vsako časovno enoto le, če ima vrednost. Na primer, če je število minut 0, so v sporočilu vključene samo sekunde. Ta stavek se nato pošlje funkciji `say`.

1. Pod to funkcijo dodajte naslednjo funkcijo `create_timer`, da ustvarite časovnik:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Ta funkcija sprejme skupno število sekund za časovnik, ki bo poslano v ukazu, in ga pretvori v minute in sekunde. Nato ustvari in zažene objekt časovnika z uporabo skupnega števila sekund, pri čemer posreduje funkcijo `announce_timer` in seznam, ki vsebuje minute in sekunde. Ko časovnik poteče, bo poklical funkcijo `announce_timer` in posredoval vsebino tega seznama kot parametre - tako bo prvi element na seznamu posredovan kot parameter `minutes`, drugi element pa kot parameter `seconds`.

1. Na konec funkcije `create_timer` dodajte nekaj kode za sestavo sporočila, ki ga bo uporabnik slišal, da naznani začetek časovnika:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Tudi tukaj je vključena le časovna enota, ki ima vrednost. Ta stavek se nato pošlje funkciji `say`.

1. Na konec funkcije `process_text` dodajte naslednje, da pridobite čas za časovnik iz besedila in nato ustvarite časovnik:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Časovnik se ustvari le, če je število sekund večje od 0.

1. Zaženite aplikacijo in se prepričajte, da aplikacija funkcij prav tako deluje. Nastavite nekaj časovnikov, in izpis bo pokazal, da je časovnik nastavljen, nato pa bo pokazal, kdaj poteče:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 To kodo lahko najdete v mapi [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) ali [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Vaš program za časovnik je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitne nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.