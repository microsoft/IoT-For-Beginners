<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-28T08:43:06+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "ro"
}
-->
# Capturarea unei imagini - Hardware IoT Virtual

În această parte a lecției, vei adăuga un senzor de cameră dispozitivului tău IoT virtual și vei citi imagini de la acesta.

## Hardware

Dispozitivul IoT virtual va folosi o cameră simulată care trimite fie imagini din fișiere, fie de la camera web.

### Adaugă camera în CounterFit

Pentru a utiliza o cameră virtuală, trebuie să adaugi una în aplicația CounterFit.

#### Sarcină - adaugă camera în CounterFit

Adaugă camera în aplicația CounterFit.

1. Creează o nouă aplicație Python pe computerul tău într-un folder numit `fruit-quality-detector`, cu un singur fișier numit `app.py` și un mediu virtual Python, și adaugă pachetele pip CounterFit.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea și configurarea unui proiect Python CounterFit în lecția 1, dacă este necesar](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Instalează un pachet Pip suplimentar pentru a instala un shim CounterFit care poate comunica cu senzorii de cameră simulând unele funcționalități ale [pachetului Pip Picamera](https://pypi.org/project/picamera/). Asigură-te că instalezi acest pachet dintr-un terminal cu mediul virtual activat.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Asigură-te că aplicația web CounterFit este pornită.

1. Creează o cameră:

    1. În caseta *Create sensor* din panoul *Sensors*, deschide meniul derulant *Sensor type* și selectează *Camera*.

    1. Setează *Name* la `Picamera`.

    1. Selectează butonul **Add** pentru a crea camera.

    ![Setările camerei](../../../../../translated_images/ro/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    Camera va fi creată și va apărea în lista de senzori.

    ![Camera creată](../../../../../translated_images/ro/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## Programează camera

Dispozitivul IoT virtual poate fi acum programat pentru a utiliza camera virtuală.

### Sarcină - programează camera

Programează dispozitivul.

1. Asigură-te că aplicația `fruit-quality-detector` este deschisă în VS Code.

1. Deschide fișierul `app.py`.

1. Adaugă următorul cod în partea de sus a fișierului `app.py` pentru a conecta aplicația la CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Adaugă următorul cod în fișierul `app.py`:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Acest cod importă câteva biblioteci necesare, inclusiv clasa `PiCamera` din biblioteca counterfit_shims_picamera.

1. Adaugă următorul cod mai jos pentru a inițializa camera:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Acest cod creează un obiect PiCamera, setează rezoluția la 640x480. Deși sunt acceptate rezoluții mai mari, clasificatorul de imagini funcționează cu imagini mult mai mici (227x227), așa că nu este nevoie să capturezi și să trimiți imagini mai mari.

    Linia `camera.rotation = 0` setează rotația imaginii în grade. Dacă trebuie să rotești imaginea de la camera web sau din fișier, setează această valoare corespunzător. De exemplu, dacă vrei să schimbi imaginea unei banane de pe o cameră web în mod peisaj la portret, setează `camera.rotation = 90`.

1. Adaugă următorul cod mai jos pentru a captura imaginea ca date binare:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Acest cod creează un obiect `BytesIO` pentru a stoca date binare. Imaginea este citită de la cameră ca un fișier JPEG și stocată în acest obiect. Acest obiect are un indicator de poziție pentru a ști unde se află în date, astfel încât mai multe date să poată fi scrise la final, dacă este necesar. Linia `image.seek(0)` mută această poziție înapoi la început, astfel încât toate datele să poată fi citite ulterior.

1. Mai jos, adaugă următorul cod pentru a salva imaginea într-un fișier:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Acest cod deschide un fișier numit `image.jpg` pentru scriere, apoi citește toate datele din obiectul `BytesIO` și le scrie în fișier.

    > 💁 Poți captura imaginea direct într-un fișier în loc de un obiect `BytesIO` prin transmiterea numelui fișierului în apelul `camera.capture`. Motivul utilizării obiectului `BytesIO` este că mai târziu în această lecție vei putea trimite imaginea către clasificatorul tău de imagini.

1. Configurează imaginea pe care camera din CounterFit o va captura. Poți seta *Source* la *File*, apoi să încarci un fișier imagine, sau să setezi *Source* la *WebCam*, iar imaginile vor fi capturate de la camera web. Asigură-te că selectezi butonul **Set** după ce alegi o imagine sau camera web.

    ![CounterFit cu un fișier setat ca sursă de imagine și o cameră web afișând o persoană care ține o banană într-o previzualizare a camerei web](../../../../../translated_images/ro/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. O imagine va fi capturată și salvată ca `image.jpg` în folderul curent. Vei vedea acest fișier în exploratorul VS Code. Selectează fișierul pentru a vizualiza imaginea. Dacă este necesară rotația, actualizează linia `camera.rotation = 0` corespunzător și fă o altă fotografie.

> 💁 Poți găsi acest cod în folderul [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device).

😀 Programul tău pentru cameră a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.