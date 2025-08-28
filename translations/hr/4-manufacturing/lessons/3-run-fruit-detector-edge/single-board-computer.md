<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-28T12:22:19+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "hr"
}
-->
# Klasificirajte sliku pomoću IoT Edge uređaja za klasifikaciju slika - Virtualni IoT hardver i Raspberry Pi

U ovom dijelu lekcije koristit ćete uređaj za klasifikaciju slika koji radi na IoT Edge uređaju.

## Koristite IoT Edge uređaj za klasifikaciju

IoT uređaj može biti preusmjeren da koristi IoT Edge uređaj za klasifikaciju slika. URL za uređaj za klasifikaciju slika je `http://<IP adresa ili ime>/image`, pri čemu `<IP adresa ili ime>` zamjenjujete IP adresom ili nazivom računala na kojem radi IoT Edge.

Python knjižnica za Custom Vision radi samo s modelima hostiranim u oblaku, a ne s modelima hostiranim na IoT Edge uređaju. To znači da ćete morati koristiti REST API za pozivanje uređaja za klasifikaciju.

### Zadatak - koristite IoT Edge uređaj za klasifikaciju

1. Otvorite projekt `fruit-quality-detector` u VS Code-u ako već nije otvoren. Ako koristite virtualni IoT uređaj, provjerite je li virtualno okruženje aktivirano.

1. Otvorite datoteku `app.py` i uklonite naredbe za uvoz iz `azure.cognitiveservices.vision.customvision.prediction` i `msrest.authentication`.

1. Dodajte sljedeći uvoz na vrh datoteke:

    ```python
    import requests
    ```

1. Izbrišite sav kod nakon što je slika spremljena u datoteku, od `image_file.write(image.read())` do kraja datoteke.

1. Dodajte sljedeći kod na kraj datoteke:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Zamijenite `<URL>` s URL-om vašeg uređaja za klasifikaciju.

    Ovaj kod šalje REST POST zahtjev uređaju za klasifikaciju, šaljući sliku kao tijelo zahtjeva. Rezultati se vraćaju u JSON formatu, koji se dekodira kako bi se ispisale vjerojatnosti.

1. Pokrenite svoj kod, usmjeravajući kameru prema nekom voću, odgovarajućem skupu slika ili voću vidljivom na vašoj web kameri ako koristite virtualni IoT hardver. Vidjet ćete izlaz u konzoli:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) ili [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Vaš program za klasifikaciju kvalitete voća bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.