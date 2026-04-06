# Capturarea unei imagini - Raspberry Pi

În această parte a lecției, vei adăuga un senzor de cameră la Raspberry Pi și vei citi imagini de la acesta.

## Hardware

Raspberry Pi are nevoie de o cameră.

Camera pe care o vei folosi este un [Modul Cameră Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/). Această cameră este proiectată să funcționeze cu Raspberry Pi și se conectează printr-un conector dedicat pe Pi.

> 💁 Această cameră folosește [Camera Serial Interface, un protocol al Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), cunoscut sub numele de MIPI-CSI. Acesta este un protocol dedicat pentru transmiterea imaginilor.

## Conectarea camerei

Camera poate fi conectată la Raspberry Pi folosind un cablu panglică.

### Sarcină - conectarea camerei

![O cameră Raspberry Pi](../../../../../translated_images/ro/pi-camera-module.4278753c31bd6e75.webp)

1. Oprește alimentarea Pi-ului.

1. Conectează cablul panglică care vine cu camera la aceasta. Pentru a face acest lucru, trage ușor de clema de plastic neagră din suport astfel încât să iasă puțin, apoi glisează cablul în soclu, cu partea albastră orientată în direcția opusă lentilei, iar benzile metalice orientate spre lentilă. După ce cablul este complet introdus, împinge clema de plastic neagră înapoi la loc.

    Poți găsi o animație care arată cum să deschizi clema și să introduci cablul în [documentația Raspberry Pi pentru modulul cameră](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![Cablul panglică introdus în modulul cameră](../../../../../translated_images/ro/pi-camera-ribbon-cable.0bf82acd251611c2.webp)

1. Scoate Grove Base Hat de pe Pi.

1. Trece cablul panglică prin slotul pentru cameră din Grove Base Hat. Asigură-te că partea albastră a cablului este orientată spre porturile analogice etichetate **A0**, **A1** etc.

    ![Cablul panglică trecând prin Grove Base Hat](../../../../../translated_images/ro/grove-base-hat-ribbon-cable.501fed202fcf73b1.webp)

1. Introdu cablul panglică în portul pentru cameră de pe Pi. Din nou, trage clema de plastic neagră în sus, introdu cablul, apoi împinge clema înapoi. Partea albastră a cablului ar trebui să fie orientată spre porturile USB și Ethernet.

    ![Cablul panglică conectat la soclul camerei de pe Pi](../../../../../translated_images/ro/pi-camera-socket-ribbon-cable.a18309920b118009.webp)

1. Reinstalează Grove Base Hat.

## Programarea camerei

Raspberry Pi poate fi acum programat să folosească camera utilizând biblioteca Python [PiCamera](https://pypi.org/project/picamera/).

### Sarcină - activarea modului de cameră legacy

Din păcate, odată cu lansarea Raspberry Pi OS Bullseye, software-ul camerei inclus în sistemul de operare s-a schimbat, ceea ce înseamnă că, implicit, PiCamera nu mai funcționează. Există un înlocuitor în dezvoltare, numit PiCamera2, dar acesta nu este încă pregătit pentru utilizare.

Pentru moment, poți seta Pi-ul în modul de cameră legacy pentru a permite funcționarea PiCamera. Soclul camerei este, de asemenea, dezactivat implicit, dar activarea software-ului de cameră legacy îl activează automat.

1. Pornește Pi-ul și așteaptă să se încarce.

1. Lansează VS Code, fie direct pe Pi, fie conectându-te prin extensia Remote SSH.

1. Rulează următoarele comenzi din terminal:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Aceste comenzi vor activa o setare pentru software-ul de cameră legacy, apoi vor reporni Pi-ul pentru ca setarea să intre în vigoare.

1. Așteaptă ca Pi-ul să se repornească, apoi relansează VS Code.

### Sarcină - programarea camerei

Programează dispozitivul.

1. Din terminal, creează un nou folder în directorul home al utilizatorului `pi`, numit `fruit-quality-detector`. Creează un fișier în acest folder numit `app.py`.

1. Deschide acest folder în VS Code.

1. Pentru a interacționa cu camera, poți folosi biblioteca Python PiCamera. Instalează pachetul Pip pentru aceasta cu următoarea comandă:

    ```sh
    pip3 install picamera
    ```

1. Adaugă următorul cod în fișierul `app.py`:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Acest cod importă câteva biblioteci necesare, inclusiv biblioteca `PiCamera`.

1. Adaugă următorul cod sub acesta pentru a inițializa camera:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Acest cod creează un obiect PiCamera, setează rezoluția la 640x480. Deși sunt suportate rezoluții mai mari (până la 3280x2464), clasificatorul de imagini funcționează pe imagini mult mai mici (227x227), așa că nu este nevoie să capturezi și să trimiți imagini mai mari.

    Linia `camera.rotation = 0` setează rotația imaginii. Cablul panglică intră în partea de jos a camerei, dar dacă camera ta a fost rotită pentru a permite o orientare mai ușoară spre obiectul pe care vrei să-l clasifici, atunci poți modifica această linie cu numărul de grade de rotație.

    ![Camera suspendată deasupra unei doze de băutură](../../../../../translated_images/ro/pi-camera-upside-down.5376961ba3145988.webp)

    De exemplu, dacă suspenzi cablul panglică deasupra unui obiect astfel încât să fie în partea de sus a camerei, setează rotația la 180:

    ```python
    camera.rotation = 180
    ```

    Camera are nevoie de câteva secunde pentru a porni, de aceea linia `time.sleep(2)` este necesară.

1. Adaugă următorul cod sub acesta pentru a captura imaginea ca date binare:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Acest cod creează un obiect `BytesIO` pentru a stoca date binare. Imaginea este citită de la cameră ca fișier JPEG și stocată în acest obiect. Obiectul are un indicator de poziție pentru a ști unde se află în date, astfel încât mai multe date să poată fi scrise la sfârșit, dacă este necesar. Linia `image.seek(0)` mută acest indicator înapoi la început, astfel încât toate datele să poată fi citite ulterior.

1. Sub acesta, adaugă următorul cod pentru a salva imaginea într-un fișier:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Acest cod deschide un fișier numit `image.jpg` pentru scriere, apoi citește toate datele din obiectul `BytesIO` și le scrie în fișier.

    > 💁 Poți captura imaginea direct într-un fișier în loc de un obiect `BytesIO` prin transmiterea numelui fișierului la apelul `camera.capture`. Motivul utilizării obiectului `BytesIO` este că, mai târziu în această lecție, vei putea trimite imaginea către clasificatorul de imagini.

1. Îndreaptă camera spre ceva și rulează acest cod.

1. O imagine va fi capturată și salvată ca `image.jpg` în folderul curent. Vei vedea acest fișier în exploratorul VS Code. Selectează fișierul pentru a vizualiza imaginea. Dacă este necesară rotația, actualizează linia `camera.rotation = 0` și fă o altă fotografie.

> 💁 Poți găsi acest cod în folderul [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 Programul camerei tale a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.