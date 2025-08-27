<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T21:15:13+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "hu"
}
-->
# Állíts be egy időzítőt - Virtuális IoT hardver és Raspberry Pi

A lecke ezen részében hívni fogod a szerver nélküli kódodat, hogy megértsd a beszédet, és az eredmények alapján beállíts egy időzítőt a virtuális IoT eszközödön vagy a Raspberry Pi-n.

## Időzítő beállítása

A beszéd szöveggé alakításából visszakapott szöveget el kell küldeni a szerver nélküli kódodnak, hogy a LUIS feldolgozza, és visszaadja az időzítőhöz szükséges másodpercek számát. Ez a másodpercek száma használható az időzítő beállításához.

Az időzítők beállításához a Python `threading.Timer` osztályát használhatod. Ez az osztály egy késleltetési időt és egy függvényt vesz át, és a késleltetési idő után végrehajtja a függvényt.

### Feladat - küldd el a szöveget a szerver nélküli függvénynek

1. Nyisd meg a `smart-timer` projektet a VS Code-ban, és győződj meg róla, hogy a virtuális környezet betöltődött a terminálban, ha virtuális IoT eszközt használsz.

1. A `process_text` függvény fölött deklarálj egy `get_timer_time` nevű függvényt, amely a létrehozott REST végpontot hívja meg:

    ```python
    def get_timer_time(text):
    ```

1. Adj hozzá a következő kódot ehhez a függvényhez, hogy meghatározd a hívandó URL-t:

    ```python
    url = '<URL>'
    ```

    Cseréld ki a `<URL>` helyére a REST végpontod URL-jét, amelyet az előző leckében hoztál létre, akár a számítógépeden, akár a felhőben.

1. Adj hozzá a következő kódot, hogy a szöveget JSON tulajdonságként add át a hívásban:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Ezután szerezd meg a válasz payload-jából a `seconds` értéket, és térj vissza 0-val, ha a hívás sikertelen volt:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    A sikeres HTTP hívások 200-as tartományba eső állapotkódot adnak vissza, és a szerver nélküli kódod 200-at ad vissza, ha a szöveget feldolgozták és időzítő beállítási szándékként ismerték fel.

### Feladat - időzítő beállítása háttérszálon

1. Add hozzá a következő import utasítást a fájl tetejére, hogy importáld a Python `threading` könyvtárát:

    ```python
    import threading
    ```

1. A `process_text` függvény fölött adj hozzá egy függvényt, amely válaszként szöveget mond ki. Egyelőre ez csak a konzolra ír, de később a leckében ez a szöveg ki lesz mondva.

    ```python
    def say(text):
        print(text)
    ```

1. Ezután adj hozzá egy függvényt, amelyet az időzítő hív meg, hogy bejelentse, hogy az időzítő lejárt:

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

    Ez a függvény az időzítőhöz tartozó percek és másodpercek számát veszi át, és egy mondatot épít, amely bejelenti, hogy az időzítő lejárt. Ellenőrzi a percek és másodpercek számát, és csak azokat az időegységeket tartalmazza, amelyeknek van értéke. Például, ha a percek száma 0, akkor csak a másodpercek szerepelnek az üzenetben. Ez a mondat ezután a `say` függvénynek kerül átadásra.

1. Ezután add hozzá a következő `create_timer` függvényt, hogy létrehozz egy időzítőt:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Ez a függvény az időzítőhöz küldött teljes másodpercek számát veszi át, és átalakítja percekké és másodpercekké. Ezután létrehoz és elindít egy időzítő objektumot a teljes másodpercek számával, átadva az `announce_timer` függvényt és egy listát, amely tartalmazza a perceket és másodperceket. Amikor az időzítő lejár, meghívja az `announce_timer` függvényt, és a lista tartalmát paraméterként adja át - így a lista első eleme a `minutes` paraméterként, a második pedig a `seconds` paraméterként kerül átadásra.

1. A `create_timer` függvény végére adj hozzá néhány kódot, amely egy üzenetet épít a felhasználónak, hogy bejelentse, hogy az időzítő elindul:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Ez ismét csak azokat az időegységeket tartalmazza, amelyeknek van értéke. Ez a mondat ezután a `say` függvénynek kerül átadásra.

1. Add hozzá a következőket a `process_text` függvény végéhez, hogy a szövegből megszerezd az időzítőhöz szükséges időt, majd létrehozd az időzítőt:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Az időzítő csak akkor jön létre, ha a másodpercek száma nagyobb, mint 0.

1. Futtasd az alkalmazást, és győződj meg róla, hogy a függvényalkalmazás is fut. Állíts be néhány időzítőt, és a kimenet megmutatja, hogy az időzítő beállításra került, majd azt is, amikor lejár:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Ezt a kódot megtalálod a [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) vagy a [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device) mappában.

😀 Az időzítő programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.