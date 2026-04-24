# Snimanje slike - Raspberry Pi

U ovom dijelu lekcije dodat ćete senzor kamere na svoj Raspberry Pi i čitati slike s njega.

## Hardver

Raspberry Pi treba kameru.

Kamera koju ćete koristiti je [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). Ova kamera je dizajnirana za rad s Raspberry Pi-jem i povezuje se putem namjenskog konektora na Pi-ju.

> 💁 Ova kamera koristi [Camera Serial Interface, protokol Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), poznat kao MIPI-CSI. Ovo je namjenski protokol za prijenos slika.

## Povezivanje kamere

Kamera se može povezati s Raspberry Pi-jem pomoću vrpčastog kabela.

### Zadatak - povezivanje kamere

![Raspberry Pi kamera](../../../../../translated_images/hr/pi-camera-module.4278753c31bd6e75.webp)

1. Isključite napajanje Pi-ja.

1. Spojite vrpčasti kabel koji dolazi s kamerom na kameru. Da biste to učinili, lagano povucite crnu plastičnu kopču u držaču tako da se malo izvuče, zatim umetnite kabel u utičnicu, s plavom stranom okrenutom od objektiva, a metalnim kontaktima prema objektivu. Kada je kabel potpuno umetnut, gurnite crnu plastičnu kopču natrag na mjesto.

    Animaciju koja prikazuje kako otvoriti kopču i umetnuti kabel možete pronaći u [Raspberry Pi dokumentaciji za početak rada s modulom kamere](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![Vrpčasti kabel umetnut u modul kamere](../../../../../translated_images/hr/pi-camera-ribbon-cable.0bf82acd251611c2.webp)

1. Uklonite Grove Base Hat s Pi-ja.

1. Provucite vrpčasti kabel kroz utor za kameru na Grove Base Hat-u. Provjerite je li plava strana kabela okrenuta prema analognim priključcima označenim **A0**, **A1** itd.

    ![Vrpčasti kabel prolazi kroz Grove Base Hat](../../../../../translated_images/hr/grove-base-hat-ribbon-cable.501fed202fcf73b1.webp)

1. Umetnite vrpčasti kabel u priključak za kameru na Pi-ju. Ponovno, povucite crnu plastičnu kopču prema gore, umetnite kabel, a zatim gurnite kopču natrag. Plava strana kabela trebala bi biti okrenuta prema USB i Ethernet priključcima.

    ![Vrpčasti kabel povezan s priključkom za kameru na Pi-ju](../../../../../translated_images/hr/pi-camera-socket-ribbon-cable.a18309920b118009.webp)

1. Ponovno postavite Grove Base Hat.

## Programiranje kamere

Raspberry Pi sada se može programirati za korištenje kamere pomoću Python biblioteke [PiCamera](https://pypi.org/project/picamera/).

### Zadatak - omogućavanje naslijeđenog načina rada kamere

Nažalost, s izdanjem Raspberry Pi OS Bullseye, softver za kameru koji dolazi s OS-om promijenio se, što znači da PiCamera prema zadanim postavkama više ne radi. U pripremi je zamjena, nazvana PiCamera2, ali još nije spremna za korištenje.

Za sada možete postaviti svoj Pi u naslijeđeni način rada kamere kako bi PiCamera radila. Priključak za kameru također je prema zadanim postavkama onemogućen, ali uključivanjem naslijeđenog softvera za kameru automatski se omogućuje priključak.

1. Uključite Pi i pričekajte da se pokrene.

1. Pokrenite VS Code, bilo izravno na Pi-ju ili se povežite putem Remote SSH ekstenzije.

1. Pokrenite sljedeće naredbe iz terminala:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Ovo će omogućiti postavku za naslijeđeni softver kamere, a zatim ponovno pokrenuti Pi kako bi postavka stupila na snagu.

1. Pričekajte da se Pi ponovno pokrene, a zatim ponovno pokrenite VS Code.

### Zadatak - programiranje kamere

Programirajte uređaj.

1. Iz terminala, stvorite novu mapu u početnom direktoriju korisnika `pi` nazvanu `fruit-quality-detector`. Stvorite datoteku u ovoj mapi nazvanu `app.py`.

1. Otvorite ovu mapu u VS Code-u.

1. Za interakciju s kamerom možete koristiti Python biblioteku PiCamera. Instalirajte Pip paket za ovo pomoću sljedeće naredbe:

    ```sh
    pip3 install picamera
    ```

1. Dodajte sljedeći kod u svoju datoteku `app.py`:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Ovaj kod uvozi potrebne biblioteke, uključujući biblioteku `PiCamera`.

1. Dodajte sljedeći kod ispod ovog za inicijalizaciju kamere:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Ovaj kod stvara PiCamera objekt, postavlja rezoluciju na 640x480. Iako su podržane veće rezolucije (do 3280x2464), klasifikator slika radi na mnogo manjim slikama (227x227), tako da nema potrebe za snimanjem i slanjem većih slika.

    Linija `camera.rotation = 0` postavlja rotaciju slike. Vrpčasti kabel ulazi na dno kamere, ali ako je vaša kamera rotirana kako bi lakše usmjerila predmet koji želite klasificirati, možete promijeniti ovu liniju na broj stupnjeva rotacije.

    ![Kamera visi iznad limenke pića](../../../../../translated_images/hr/pi-camera-upside-down.5376961ba3145988.webp)

    Na primjer, ako objesite vrpčasti kabel iznad nečega tako da je na vrhu kamere, postavite rotaciju na 180:

    ```python
    camera.rotation = 180
    ```

    Kamere treba nekoliko sekundi da se pokrene, zbog čega je tu linija `time.sleep(2)`.

1. Dodajte sljedeći kod ispod ovog za snimanje slike kao binarnih podataka:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Ovaj kod stvara `BytesIO` objekt za pohranu binarnih podataka. Slika se čita s kamere kao JPEG datoteka i pohranjuje u ovaj objekt. Ovaj objekt ima pokazivač pozicije kako bi znao gdje se nalazi u podacima, tako da se više podataka može dodati na kraj ako je potrebno, pa linija `image.seek(0)` pomiče ovu poziciju natrag na početak kako bi se svi podaci mogli kasnije pročitati.

1. Ispod ovoga, dodajte sljedeće za spremanje slike u datoteku:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Ovaj kod otvara datoteku nazvanu `image.jpg` za pisanje, zatim čita sve podatke iz `BytesIO` objekta i zapisuje ih u datoteku.

    > 💁 Slika se može snimiti izravno u datoteku umjesto u `BytesIO` objekt tako da se naziv datoteke proslijedi pozivu `camera.capture`. Razlog za korištenje `BytesIO` objekta je taj što kasnije u ovoj lekciji možete poslati sliku svom klasifikatoru slika.

1. Usmjerite kameru na nešto i pokrenite ovaj kod.

1. Slika će biti snimljena i spremljena kao `image.jpg` u trenutnoj mapi. Vidjet ćete ovu datoteku u VS Code exploreru. Odaberite datoteku za pregled slike. Ako je potrebno rotirati, ažurirajte liniju `camera.rotation = 0` prema potrebi i snimite novu sliku.

> 💁 Ovaj kod možete pronaći u mapi [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 Vaš program za kameru je uspješno završen!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.