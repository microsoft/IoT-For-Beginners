<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T21:15:38+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "cs"
}
-->
# Nastavení časovače - Virtuální IoT zařízení a Raspberry Pi

V této části lekce zavoláte svůj serverless kód, abyste porozuměli řeči, a nastavíte časovač na svém virtuálním IoT zařízení nebo Raspberry Pi na základě výsledků.

## Nastavení časovače

Text, který se vrátí z volání převodu řeči na text, musí být odeslán do vašeho serverless kódu, aby byl zpracován pomocí LUIS, který vrátí počet sekund pro časovač. Tento počet sekund může být použit k nastavení časovače.

Časovače lze nastavit pomocí třídy Python `threading.Timer`. Tato třída přijímá dobu zpoždění a funkci, která se po uplynutí doby zpoždění vykoná.

### Úkol - odeslání textu do serverless funkce

1. Otevřete projekt `smart-timer` ve VS Code a ujistěte se, že je v terminálu načteno virtuální prostředí, pokud používáte virtuální IoT zařízení.

1. Nad funkcí `process_text` deklarujte funkci nazvanou `get_timer_time`, která bude volat REST endpoint, který jste vytvořili:

    ```python
    def get_timer_time(text):
    ```

1. Přidejte do této funkce následující kód, který definuje URL pro volání:

    ```python
    url = '<URL>'
    ```

    Nahraďte `<URL>` URL adresou vašeho REST endpointu, který jste vytvořili v předchozí lekci, buď na svém počítači, nebo v cloudu.

1. Přidejte následující kód, který nastaví text jako vlastnost předanou jako JSON při volání:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Pod tímto kódem získejte `seconds` z odpovědi payloadu, přičemž vraťte 0, pokud volání selhalo:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Úspěšná HTTP volání vracejí status kód v rozmezí 200, a váš serverless kód vrací 200, pokud byl text zpracován a rozpoznán jako záměr nastavení časovače.

### Úkol - nastavení časovače na pozadí

1. Přidejte následující import na začátek souboru, abyste importovali knihovnu Python `threading`:

    ```python
    import threading
    ```

1. Nad funkcí `process_text` přidejte funkci pro mluvení odpovědi. Prozatím bude pouze zapisovat do konzole, ale později v této lekci bude text mluvený.

    ```python
    def say(text):
        print(text)
    ```

1. Pod tímto kódem přidejte funkci, která bude volána časovačem, aby oznámila, že časovač skončil:

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

    Tato funkce přijímá počet minut a sekund pro časovač a sestavuje větu, která oznamuje, že časovač skončil. Zkontroluje počet minut a sekund a zahrne pouze ty jednotky času, které mají hodnotu. Například pokud je počet minut 0, zahrnou se pouze sekundy. Tato věta je poté odeslána do funkce `say`.

1. Pod tímto kódem přidejte následující funkci `create_timer` pro vytvoření časovače:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Tato funkce přijímá celkový počet sekund pro časovač, který bude odeslán v příkazu, a převádí je na minuty a sekundy. Poté vytvoří a spustí objekt časovače pomocí celkového počtu sekund, přičemž předá funkci `announce_timer` a seznam obsahující minuty a sekundy. Když časovač vyprší, zavolá funkci `announce_timer` a předá obsah tohoto seznamu jako parametry - první položka v seznamu se předá jako parametr `minutes` a druhá položka jako parametr `seconds`.

1. Na konec funkce `create_timer` přidejte kód, který sestaví zprávu, která bude uživateli oznámena, že časovač začíná:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Opět zahrnuje pouze jednotky času, které mají hodnotu. Tato věta je poté odeslána do funkce `say`.

1. Na konec funkce `process_text` přidejte následující kód, který získá čas pro časovač z textu a poté vytvoří časovač:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Časovač se vytvoří pouze tehdy, pokud je počet sekund větší než 0.

1. Spusťte aplikaci a ujistěte se, že funkce aplikace také běží. Nastavte několik časovačů a výstup ukáže, že časovač byl nastaven, a poté ukáže, kdy vyprší:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Tento kód najdete ve složce [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) nebo [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Váš program pro časovač byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.