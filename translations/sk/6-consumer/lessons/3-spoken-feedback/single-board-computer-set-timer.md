<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-28T09:05:40+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "sk"
}
-->
# Nastavenie časovača - Virtuálne IoT zariadenie a Raspberry Pi

V tejto časti lekcie zavoláte svoj serverless kód na rozpoznanie reči a nastavíte časovač na vašom virtuálnom IoT zariadení alebo Raspberry Pi na základe výsledkov.

## Nastavenie časovača

Text, ktorý sa vráti z volania reči na text, je potrebné odoslať do vášho serverless kódu, aby ho spracoval LUIS a získal počet sekúnd pre časovač. Tento počet sekúnd sa potom použije na nastavenie časovača.

Časovače je možné nastaviť pomocou triedy Python `threading.Timer`. Táto trieda prijíma čas oneskorenia a funkciu, ktorá sa vykoná po uplynutí času oneskorenia.

### Úloha - odoslanie textu do serverless funkcie

1. Otvorte projekt `smart-timer` vo VS Code a uistite sa, že virtuálne prostredie je načítané v termináli, ak používate virtuálne IoT zariadenie.

1. Nad funkciou `process_text` deklarujte funkciu s názvom `get_timer_time`, ktorá zavolá REST endpoint, ktorý ste vytvorili:

    ```python
    def get_timer_time(text):
    ```

1. Pridajte do tejto funkcie nasledujúci kód na definovanie URL adresy, ktorú treba zavolať:

    ```python
    url = '<URL>'
    ```

    Nahraďte `<URL>` URL adresou vášho REST endpointu, ktorý ste vytvorili v predchádzajúcej lekcii, buď na vašom počítači alebo v cloude.

1. Pridajte nasledujúci kód na nastavenie textu ako vlastnosti odoslanej vo formáte JSON:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Pod týmto kódom získajte `seconds` z odpovede payloadu, pričom vráťte 0, ak volanie zlyhalo:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Úspešné HTTP volania vracajú stavový kód v rozsahu 200, a váš serverless kód vracia 200, ak bol text spracovaný a rozpoznaný ako úmysel nastavenia časovača.

### Úloha - nastavenie časovača na pozadí

1. Pridajte nasledujúci import na začiatok súboru na importovanie knižnice threading v Pythone:

    ```python
    import threading
    ```

1. Nad funkciou `process_text` pridajte funkciu na vyslovenie odpovede. Zatiaľ bude len zapisovať do konzoly, ale neskôr v tejto lekcii bude hovoriť text.

    ```python
    def say(text):
        print(text)
    ```

1. Pod týmto pridajte funkciu, ktorú zavolá časovač na oznámenie, že časovač skončil:

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

    Táto funkcia prijíma počet minút a sekúnd pre časovač a vytvára vetu, ktorá oznámi, že časovač skončil. Skontroluje počet minút a sekúnd a zahrnie iba tie časové jednotky, ktoré majú hodnotu. Napríklad, ak je počet minút 0, zahrnú sa iba sekundy. Táto veta sa potom odošle do funkcie `say`.

1. Pod týmto pridajte nasledujúcu funkciu `create_timer` na vytvorenie časovača:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Táto funkcia prijíma celkový počet sekúnd pre časovač, ktorý bude odoslaný v príkaze, a konvertuje ich na minúty a sekundy. Potom vytvorí a spustí objekt časovača pomocou celkového počtu sekúnd, pričom odovzdá funkciu `announce_timer` a zoznam obsahujúci minúty a sekundy. Keď časovač vyprší, zavolá funkciu `announce_timer` a odovzdá obsah tohto zoznamu ako parametre - prvá položka v zozname sa odovzdá ako parameter `minutes` a druhá položka ako parameter `seconds`.

1. Na koniec funkcie `create_timer` pridajte kód na vytvorenie správy, ktorá sa oznámi používateľovi, že časovač sa spúšťa:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Opäť sa zahrnie iba tá časová jednotka, ktorá má hodnotu. Táto veta sa potom odošle do funkcie `say`.

1. Pridajte nasledujúce na koniec funkcie `process_text`, aby ste získali čas pre časovač z textu a potom vytvorili časovač:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Časovač sa vytvorí iba vtedy, ak je počet sekúnd väčší ako 0.

1. Spustite aplikáciu a uistite sa, že funkčná aplikácia tiež beží. Nastavte niekoľko časovačov a výstup ukáže, že časovač bol nastavený, a potom ukáže, keď vyprší:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Tento kód nájdete v priečinku [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) alebo [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Váš program na časovač bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.