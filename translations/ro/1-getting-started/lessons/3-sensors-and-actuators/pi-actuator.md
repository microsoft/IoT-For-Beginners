<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-28T10:34:13+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "ro"
}
-->
# Construiește o lampă de veghe - Raspberry Pi

În această parte a lecției, vei adăuga un LED la Raspberry Pi și îl vei folosi pentru a crea o lampă de veghe.

## Hardware

Lampa de veghe are acum nevoie de un actuator.

Actuatorul este un **LED**, o [diodă emițătoare de lumină](https://wikipedia.org/wiki/Light-emitting_diode) care emite lumină atunci când curentul trece prin ea. Acesta este un actuator digital care are 2 stări: pornit și oprit. Trimiterea unei valori de 1 aprinde LED-ul, iar 0 îl stinge. LED-ul este un actuator extern Grove și trebuie conectat la Grove Base hat pe Raspberry Pi.

Logica lămpii de veghe în pseudo-cod este:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Conectează LED-ul

LED-ul Grove vine ca un modul cu o selecție de LED-uri, permițându-ți să alegi culoarea.

#### Sarcină - conectează LED-ul

Conectează LED-ul.

![Un LED Grove](../../../../../translated_images/ro/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. Alege LED-ul preferat și inserează picioarele acestuia în cele două găuri de pe modulul LED.

    LED-urile sunt diode emițătoare de lumină, iar diodele sunt dispozitive electronice care pot transporta curent doar într-o singură direcție. Asta înseamnă că LED-ul trebuie conectat corect, altfel nu va funcționa.

    Unul dintre picioarele LED-ului este pinul pozitiv, iar celălalt este pinul negativ. LED-ul nu este perfect rotund și este ușor mai plat pe o parte. Partea ușor mai plată este pinul negativ. Când conectezi LED-ul la modul, asigură-te că pinul de pe partea rotunjită este conectat la soclul marcat **+** pe exteriorul modulului, iar partea mai plată este conectată la soclul mai aproape de mijlocul modulului.

1. Modulul LED are un buton rotativ care îți permite să controlezi luminozitatea. Rotește-l complet în sens invers acelor de ceasornic pentru început, folosind o șurubelniță mică cu cap Phillips.

1. Introdu un capăt al unui cablu Grove în soclul de pe modulul LED. Acesta va intra doar într-un singur mod.

1. Cu Raspberry Pi oprit, conectează celălalt capăt al cablului Grove la soclul digital marcat **D5** pe Grove Base hat atașat la Pi. Acest soclu este al doilea din stânga, pe rândul de socluri de lângă pini GPIO.

![LED-ul Grove conectat la soclul D5](../../../../../translated_images/ro/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## Programează lampa de veghe

Lampa de veghe poate fi acum programată folosind senzorul de lumină Grove și LED-ul Grove.

### Sarcină - programează lampa de veghe

Programează lampa de veghe.

1. Pornește Pi-ul și așteaptă să se încarce.

1. Deschide proiectul lămpii de veghe în VS Code pe care l-ai creat în partea anterioară a acestui exercițiu, fie rulând direct pe Pi, fie conectându-te folosind extensia Remote SSH.

1. Adaugă următorul cod în fișierul `app.py` pentru a importa o bibliotecă necesară. Acesta ar trebui adăugat la început, sub celelalte linii `import`.

    ```python
    from grove.grove_led import GroveLed
    ```

    Instrucțiunea `from grove.grove_led import GroveLed` importă `GroveLed` din bibliotecile Python Grove. Această bibliotecă conține cod pentru a interacționa cu un LED Grove.

1. Adaugă următorul cod după declarația `light_sensor` pentru a crea o instanță a clasei care gestionează LED-ul:

    ```python
    led = GroveLed(5)
    ```

    Linia `led = GroveLed(5)` creează o instanță a clasei `GroveLed` conectată la pinul **D5** - pinul digital Grove la care este conectat LED-ul.

    > 💁 Toate soclurile au numere de pini unice. Pinii 0, 2, 4 și 6 sunt pini analogici, iar pinii 5, 16, 18, 22, 24 și 26 sunt pini digitali.

1. Adaugă o verificare în interiorul buclei `while`, înainte de `time.sleep`, pentru a verifica nivelurile de lumină și a aprinde sau stinge LED-ul:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Acest cod verifică valoarea `light`. Dacă aceasta este mai mică de 300, se apelează metoda `on` a clasei `GroveLed`, care trimite o valoare digitală de 1 către LED, aprinzându-l. Dacă valoarea luminii este mai mare sau egală cu 300, se apelează metoda `off`, trimițând o valoare digitală de 0 către LED, stingându-l.

    > 💁 Acest cod ar trebui să fie indentat la același nivel cu linia `print('Light level:', light)` pentru a fi în interiorul buclei while!

    > 💁 Când trimiți valori digitale către actuatoare, o valoare de 0 este 0V, iar o valoare de 1 este tensiunea maximă pentru dispozitiv. Pentru Raspberry Pi cu senzori și actuatoare Grove, tensiunea de 1 este 3.3V.

1. Din terminalul VS Code, rulează următorul cod pentru a rula aplicația Python:

    ```sh
    python3 app.py
    ```

    Valorile luminii vor fi afișate în consolă.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Acoperă și descoperă senzorul de lumină. Observă cum LED-ul se va aprinde dacă nivelul luminii este 300 sau mai mic și se va stinge când nivelul luminii este mai mare de 300.

    > 💁 Dacă LED-ul nu se aprinde, asigură-te că este conectat corect și că butonul rotativ este setat la maxim.

![LED-ul conectat la Pi se aprinde și se stinge pe măsură ce nivelul luminii se schimbă](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Poți găsi acest cod în folderul [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Programul tău pentru lampa de veghe a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.