<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-28T09:06:02+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "ro"
}
-->
# Setează un cronometru - Hardware IoT Virtual și Raspberry Pi

În această parte a lecției, vei apela codul tău serverless pentru a înțelege vorbirea și vei seta un cronometru pe dispozitivul tău IoT virtual sau pe Raspberry Pi, pe baza rezultatelor.

## Setează un cronometru

Textul care este returnat din apelul de conversie vorbire-la-text trebuie trimis către codul tău serverless pentru a fi procesat de LUIS, obținând astfel numărul de secunde pentru cronometru. Acest număr de secunde poate fi folosit pentru a seta un cronometru.

Cronometrele pot fi setate folosind clasa `threading.Timer` din Python. Această clasă primește un timp de întârziere și o funcție, iar după timpul de întârziere, funcția este executată.

### Sarcină - trimite textul către funcția serverless

1. Deschide proiectul `smart-timer` în VS Code și asigură-te că mediul virtual este încărcat în terminal dacă folosești un dispozitiv IoT virtual.

1. Deasupra funcției `process_text`, declară o funcție numită `get_timer_time` pentru a apela endpoint-ul REST pe care l-ai creat:

    ```python
    def get_timer_time(text):
    ```

1. Adaugă următorul cod în această funcție pentru a defini URL-ul care trebuie apelat:

    ```python
    url = '<URL>'
    ```

    Înlocuiește `<URL>` cu URL-ul endpoint-ului REST pe care l-ai construit în lecția anterioară, fie pe computerul tău, fie în cloud.

1. Adaugă următorul cod pentru a seta textul ca proprietate transmisă ca JSON în apel:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Sub acest cod, preia `seconds` din payload-ul răspunsului, returnând 0 dacă apelul a eșuat:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Apelurile HTTP reușite returnează un cod de stare în intervalul 200, iar codul tău serverless returnează 200 dacă textul a fost procesat și recunoscut ca intenția de setare a cronometrului.

### Sarcină - setează un cronometru pe un fir de execuție în fundal

1. Adaugă următoarea instrucțiune de import în partea de sus a fișierului pentru a importa biblioteca threading din Python:

    ```python
    import threading
    ```

1. Deasupra funcției `process_text`, adaugă o funcție pentru a reda un răspuns. Deocamdată, aceasta va scrie doar în consolă, dar mai târziu în această lecție va reda textul.

    ```python
    def say(text):
        print(text)
    ```

1. Sub aceasta, adaugă o funcție care va fi apelată de un cronometru pentru a anunța că timpul cronometrului s-a terminat:

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

    Această funcție primește numărul de minute și secunde pentru cronometru și construiește o propoziție care anunță că timpul cronometrului s-a terminat. Va verifica numărul de minute și secunde și va include fiecare unitate de timp doar dacă are o valoare. De exemplu, dacă numărul de minute este 0, atunci doar secundele sunt incluse în mesaj. Această propoziție este apoi trimisă funcției `say`.

1. Sub aceasta, adaugă următoarea funcție `create_timer` pentru a crea un cronometru:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Această funcție primește numărul total de secunde pentru cronometru care va fi transmis în comandă și îl convertește în minute și secunde. Apoi creează și pornește un obiect cronometru folosind numărul total de secunde, transmițând funcția `announce_timer` și o listă care conține minutele și secundele. Când cronometrul expiră, va apela funcția `announce_timer` și va transmite conținutul acestei liste ca parametri - astfel, primul element din listă este transmis ca parametru `minutes`, iar al doilea element ca parametru `seconds`.

1. La finalul funcției `create_timer`, adaugă un cod pentru a construi un mesaj care să fie redat utilizatorului pentru a anunța că cronometrul începe:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Din nou, acest mesaj include doar unitatea de timp care are o valoare. Această propoziție este apoi trimisă funcției `say`.

1. Adaugă următorul cod la finalul funcției `process_text` pentru a obține timpul pentru cronometru din text, apoi pentru a crea cronometrul:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Cronometrul este creat doar dacă numărul de secunde este mai mare decât 0.

1. Rulează aplicația și asigură-te că aplicația funcțională rulează de asemenea. Setează câteva cronometre, iar ieșirea va arăta că cronometrul este setat și apoi va arăta când expiră:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Poți găsi acest cod în folderul [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) sau [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Programul tău de cronometru a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.