<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-28T19:22:02+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "lt"
}
-->
# Nustatykite laikmatį - Virtuali IoT įranga ir Raspberry Pi

Šioje pamokos dalyje jūs iškviesite savo serverless kodą, kad suprastumėte kalbą ir nustatytumėte laikmatį savo virtualiame IoT įrenginyje arba Raspberry Pi, remdamiesi rezultatais.

## Nustatykite laikmatį

Tekstas, grįžtantis iš kalbos į tekstą funkcijos, turi būti išsiųstas į jūsų serverless kodą, kad jį apdorotų LUIS, kuris grąžins laikmačio sekundžių skaičių. Šis sekundžių skaičius gali būti naudojamas laikmačiui nustatyti.

Laikmačius galima nustatyti naudojant Python `threading.Timer` klasę. Ši klasė priima uždelsimo laiką ir funkciją, o po uždelsimo laiko funkcija yra vykdoma.

### Užduotis - išsiųskite tekstą į serverless funkciją

1. Atidarykite `smart-timer` projektą VS Code ir įsitikinkite, kad terminale įjungta virtuali aplinka, jei naudojate virtualų IoT įrenginį.

1. Virš `process_text` funkcijos deklaruokite funkciją, pavadintą `get_timer_time`, kad iškviestumėte REST galinį tašką, kurį sukūrėte:

    ```python
    def get_timer_time(text):
    ```

1. Pridėkite šį kodą į šią funkciją, kad apibrėžtumėte URL, kurį reikia iškviesti:

    ```python
    url = '<URL>'
    ```

    Pakeiskite `<URL>` į jūsų sukurto REST galinio taško URL, kuris gali būti jūsų kompiuteryje arba debesyje.

1. Pridėkite šį kodą, kad nustatytumėte tekstą kaip JSON savybę, perduodamą iškvietimui:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Po to gaukite `seconds` iš atsakymo duomenų, grąžindami 0, jei iškvietimas nepavyko:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Sėkmingi HTTP iškvietimai grąžina statuso kodą 200 diapazone, o jūsų serverless kodas grąžina 200, jei tekstas buvo apdorotas ir atpažintas kaip laikmačio nustatymo ketinimas.

### Užduotis - nustatykite laikmatį fone veikiančioje gijoje

1. Pridėkite šį importo sakinį failo viršuje, kad importuotumėte Python `threading` biblioteką:

    ```python
    import threading
    ```

1. Virš `process_text` funkcijos pridėkite funkciją, kuri kalbės atsakymą. Šiuo metu ji tik rašys į konsolę, bet vėliau šioje pamokoje ji kalbės tekstą.

    ```python
    def say(text):
        print(text)
    ```

1. Po to pridėkite funkciją, kurią iškvies laikmatis, kad praneštų, jog laikmatis baigėsi:

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

    Ši funkcija priima laikmačio minučių ir sekundžių skaičių ir sukuria sakinį, kuris praneša, kad laikmatis baigėsi. Ji patikrina minučių ir sekundžių skaičių ir įtraukia tik tas laiko vienetus, kurie turi reikšmę. Pavyzdžiui, jei minučių skaičius yra 0, pranešime bus įtrauktos tik sekundės. Šis sakinys tada perduodamas `say` funkcijai.

1. Po to pridėkite šią `create_timer` funkciją, kad sukurtumėte laikmatį:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Ši funkcija priima bendrą laikmačio sekundžių skaičių, kuris bus perduotas komandoje, ir konvertuoja jį į minutes ir sekundes. Tada ji sukuria ir paleidžia laikmačio objektą, naudodama bendrą sekundžių skaičių, perduodama `announce_timer` funkciją ir sąrašą, kuriame yra minutės ir sekundės. Kai laikmatis baigiasi, jis iškviečia `announce_timer` funkciją ir perduoda šio sąrašo turinį kaip parametrus - pirmas sąrašo elementas perduodamas kaip `minutes` parametras, o antrasis kaip `seconds` parametras.

1. Į `create_timer` funkcijos pabaigą pridėkite kodą, kuris sukurs pranešimą, skirtą vartotojui pranešti, kad laikmatis pradedamas:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Vėlgi, įtraukiamas tik tas laiko vienetas, kuris turi reikšmę. Šis sakinys tada perduodamas `say` funkcijai.

1. Pridėkite šį kodą į `process_text` funkcijos pabaigą, kad gautumėte laikmačio laiką iš teksto, o tada sukurtumėte laikmatį:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Laikmatis sukuriamas tik tuo atveju, jei sekundžių skaičius yra didesnis nei 0.

1. Paleiskite programą ir įsitikinkite, kad funkcijų programa taip pat veikia. Nustatykite keletą laikmačių, ir išvestis parodys, kaip laikmatis nustatomas, o tada parodys, kai jis baigiasi:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Šį kodą galite rasti [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) arba [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device) aplanke.

😀 Jūsų laikmačio programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.