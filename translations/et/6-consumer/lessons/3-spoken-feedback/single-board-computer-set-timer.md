<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-10-11T12:07:52+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "et"
}
-->
# Taimeri seadistamine - Virtuaalne IoT riistvara ja Raspberry Pi

Selles õppetunni osas kutsud serverivaba koodi, et mõista kõnet ja seadistada taimer oma virtuaalses IoT seadmes või Raspberry Pi-s saadud tulemuste põhjal.

## Taimeri seadistamine

Kõneteksti kõneks muundamise tulemusena saadud tekst tuleb saata serverivabale koodile, et seda LUIS-i abil töödelda ja saada tagasi taimeri sekundite arv. Seda sekundite arvu saab kasutada taimeri seadistamiseks.

Taimerid saab seadistada, kasutades Pythoni `threading.Timer` klassi. See klass võtab viivituse aja ja funktsiooni ning pärast viivituse aega käivitatakse funktsioon.

### Ülesanne - teksti saatmine serverivabale funktsioonile

1. Ava projekt `smart-timer` VS Code'is ja veendu, et virtuaalne keskkond on terminalis laaditud, kui kasutad virtuaalset IoT seadet.

1. Deklareeri funktsiooni `process_text` kohal funktsioon nimega `get_timer_time`, et kutsuda REST lõpp-punkti, mille sa lõid:

    ```python
    def get_timer_time(text):
    ```

1. Lisa sellele funktsioonile järgmine kood, et määrata URL, mida kutsuda:

    ```python
    url = '<URL>'
    ```

   Asenda `<URL>` URL-iga, mis viitab sinu eelmises õppetunnis loodud REST lõpp-punktile, kas sinu arvutis või pilves.

1. Lisa järgmine kood, et määrata tekst JSON-omadusena, mis edastatakse kõnes:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Selle alla lisa kood, et saada vastuse andmestikust `seconds`, tagastades 0, kui kõne ebaõnnestus:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

   Edukad HTTP-kutsed tagastavad staatusekoodi vahemikus 200, ja sinu serverivaba kood tagastab 200, kui tekst on töödeldud ja tuvastatud taimeri seadistamise kavatsusena.

### Ülesanne - taimeri seadistamine taustalõimes

1. Lisa faili algusesse järgmine import-lause, et importida Pythoni threading teek:

    ```python
    import threading
    ```

1. Lisa funktsiooni `process_text` kohale funktsioon, mis räägib vastuse. Praegu kirjutab see lihtsalt konsooli, kuid hiljem selles õppetunnis räägib see teksti.

    ```python
    def say(text):
        print(text)
    ```

1. Selle alla lisa funktsioon, mida taimer kutsub, et teatada taimeri lõppemisest:

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

   See funktsioon võtab taimeri minutite ja sekundite arvu ning koostab lause, mis teatab, et taimer on lõppenud. See kontrollib minutite ja sekundite arvu ning lisab sõnumisse ainult need ajaühikud, millel on väärtus. Näiteks, kui minutite arv on 0, siis lisatakse sõnumisse ainult sekundid. See lause saadetakse seejärel funktsioonile `say`.

1. Selle alla lisa järgmine funktsioon `create_timer`, et luua taimer:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

   See funktsioon võtab taimeri jaoks määratud sekundite koguarvu ja teisendab selle minutiteks ja sekunditeks. Seejärel loob ja käivitab taimeri objekti, kasutades sekundite koguarvu, edastades funktsiooni `announce_timer` ja loendi, mis sisaldab minuteid ja sekundeid. Kui taimer aegub, kutsub see funktsiooni `announce_timer` ja edastab selle loendi sisu parameetritena - nii et loendi esimene element edastatakse parameetrina `minutes` ja teine element parameetrina `seconds`.

1. Lisa funktsiooni `create_timer` lõppu kood, et koostada sõnum, mis teatab kasutajale taimeri käivitamisest:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

   Jällegi, see sisaldab ainult ajaühikut, millel on väärtus. See lause saadetakse seejärel funktsioonile `say`.

1. Lisa järgmine kood funktsiooni `process_text` lõppu, et saada tekstist taimeri aeg ja seejärel luua taimer:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

   Taimer luuakse ainult siis, kui sekundite arv on suurem kui 0.

1. Käivita rakendus ja veendu, et funktsiooni rakendus töötab samuti. Seadista mõned taimerid ja väljund näitab taimeri seadistamist ning seejärel, kui see aegub:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Selle koodi leiad kaustast [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) või [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Sinu taimeri programm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud, kasutades AI tõlketeenust [Co-op Translator](https://github.com/Azure/co-op-translator). Kuigi püüame tagada täpsuse, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks lugeda autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valede tõlgenduste eest.