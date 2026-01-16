<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-28T12:27:39+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "hr"
}
-->
# Snimanje slike - Virtualni IoT hardver

U ovom dijelu lekcije, dodati ćete senzor kamere svom virtualnom IoT uređaju i čitati slike s njega.

## Hardver

Virtualni IoT uređaj koristit će simuliranu kameru koja šalje slike iz datoteka ili s vaše web kamere.

### Dodavanje kamere u CounterFit

Kako biste koristili virtualnu kameru, trebate je dodati u aplikaciju CounterFit.

#### Zadatak - dodavanje kamere u CounterFit

Dodajte kameru u aplikaciju CounterFit.

1. Kreirajte novu Python aplikaciju na svom računalu u mapi nazvanoj `fruit-quality-detector` s jednim datotekama nazvanim `app.py` i Python virtualnim okruženjem, te dodajte CounterFit pip pakete.

    > ⚠️ Možete se referirati na [upute za kreiranje i postavljanje CounterFit Python projekta u lekciji 1 ako je potrebno](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Instalirajte dodatni Pip paket za instalaciju CounterFit shima koji može komunicirati sa senzorima kamere simulirajući dio [Picamera Pip paketa](https://pypi.org/project/picamera/). Pobrinite se da ovo instalirate iz terminala s aktiviranim virtualnim okruženjem.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Pobrinite se da je CounterFit web aplikacija pokrenuta.

1. Kreirajte kameru:

    1. U okviru *Create sensor* u panelu *Sensors*, otvorite padajući izbornik *Sensor type* i odaberite *Camera*.

    1. Postavite *Name* na `Picamera`.

    1. Odaberite gumb **Add** za kreiranje kamere.

    ![Postavke kamere](../../../../../translated_images/hr/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    Kamera će biti kreirana i pojavit će se na popisu senzora.

    ![Kreirana kamera](../../../../../translated_images/hr/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## Programiranje kamere

Virtualni IoT uređaj sada se može programirati za korištenje virtualne kamere.

### Zadatak - programiranje kamere

Programirajte uređaj.

1. Pobrinite se da je aplikacija `fruit-quality-detector` otvorena u VS Code.

1. Otvorite datoteku `app.py`.

1. Dodajte sljedeći kod na vrh datoteke `app.py` kako biste povezali aplikaciju s CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Dodajte sljedeći kod u datoteku `app.py`:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Ovaj kod uvozi potrebne biblioteke, uključujući klasu `PiCamera` iz biblioteke counterfit_shims_picamera.

1. Dodajte sljedeći kod ispod ovog za inicijalizaciju kamere:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Ovaj kod kreira objekt PiCamera, postavlja rezoluciju na 640x480. Iako su podržane veće rezolucije, klasifikator slika radi na mnogo manjim slikama (227x227), pa nema potrebe za snimanjem i slanjem većih slika.

    Linija `camera.rotation = 0` postavlja rotaciju slike u stupnjevima. Ako trebate rotirati sliku s web kamere ili datoteke, postavite ovo prema potrebi. Na primjer, ako želite promijeniti sliku banane na web kameri u pejzažnom načinu u portretni način, postavite `camera.rotation = 90`.

1. Dodajte sljedeći kod ispod ovog za snimanje slike kao binarnih podataka:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Ovaj kod kreira objekt `BytesIO` za pohranu binarnih podataka. Slika se čita s kamere kao JPEG datoteka i pohranjuje u ovaj objekt. Ovaj objekt ima pokazatelj pozicije kako bi znao gdje se nalazi u podacima, tako da se može dodati više podataka na kraj ako je potrebno, pa linija `image.seek(0)` pomiče ovu poziciju natrag na početak kako bi se svi podaci mogli kasnije pročitati.

1. Ispod ovog, dodajte sljedeće za spremanje slike u datoteku:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Ovaj kod otvara datoteku nazvanu `image.jpg` za pisanje, zatim čita sve podatke iz objekta `BytesIO` i zapisuje ih u datoteku.

    > 💁 Slika se može snimiti direktno u datoteku umjesto u objekt `BytesIO` tako da se ime datoteke proslijedi pozivu `camera.capture`. Razlog za korištenje objekta `BytesIO` je taj što kasnije u ovoj lekciji možete poslati sliku svom klasifikatoru slika.

1. Konfigurirajte sliku koju će kamera u CounterFit snimiti. Možete postaviti *Source* na *File*, zatim učitati datoteku slike, ili postaviti *Source* na *WebCam*, i slike će se snimati s vaše web kamere. Pobrinite se da odaberete gumb **Set** nakon odabira slike ili web kamere.

    ![CounterFit s datotekom postavljenom kao izvor slike i web kamerom koja prikazuje osobu koja drži bananu u pregledu web kamere](../../../../../translated_images/hr/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. Slika će biti snimljena i spremljena kao `image.jpg` u trenutnoj mapi. Vidjet ćete ovu datoteku u exploreru VS Code-a. Odaberite datoteku za pregled slike. Ako je potrebna rotacija, ažurirajte liniju `camera.rotation = 0` prema potrebi i snimite novu sliku.

> 💁 Ovaj kod možete pronaći u mapi [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device).

😀 Vaš program za kameru je uspješno završen!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.