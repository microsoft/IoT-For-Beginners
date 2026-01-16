<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-28T12:26:43+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "sl"
}
-->
# Zajem slike - Raspberry Pi

V tem delu lekcije boste svojemu Raspberry Pi-ju dodali senzor kamere in iz njega prebrali slike.

## Strojna oprema

Raspberry Pi potrebuje kamero.

Kamera, ki jo boste uporabili, je [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). Ta kamera je zasnovana za delo z Raspberry Pi-jem in se poveže prek namenskega priključka na Pi-ju.

> 💁 Ta kamera uporablja [Camera Serial Interface, protokol združenja Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), znan kot MIPI-CSI. To je namenski protokol za pošiljanje slik.

## Povežite kamero

Kamera se lahko poveže z Raspberry Pi-jem z uporabo traku kabla.

### Naloga - povežite kamero

![Raspberry Pi kamera](../../../../../translated_images/sl/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Izklopite Pi.

1. Povežite trak kabla, ki je priložen kameri, s kamero. Da to storite, nežno povlecite črno plastično sponko v držalu, da se nekoliko odmakne, nato pa vstavite kabel v vtičnico, pri čemer naj bo modra stran obrnjena stran od leče, kovinski kontakti pa proti leči. Ko je kabel popolnoma vstavljen, potisnite črno plastično sponko nazaj na svoje mesto.

    Animacijo, ki prikazuje, kako odpreti sponko in vstaviti kabel, najdete v [dokumentaciji Raspberry Pi za začetek uporabe kamere](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![Trak kabla vstavljen v modul kamere](../../../../../translated_images/sl/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Odstranite Grove Base Hat iz Pi-ja.

1. Potegnite trak kabla skozi režo za kamero v Grove Base Hat. Prepričajte se, da je modra stran kabla obrnjena proti analognim priključkom, označenim z **A0**, **A1** itd.

    ![Trak kabla, ki poteka skozi Grove Base Hat](../../../../../translated_images/sl/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Vstavite trak kabla v priključek za kamero na Pi-ju. Spet povlecite črno plastično sponko navzgor, vstavite kabel in nato potisnite sponko nazaj. Modra stran kabla naj bo obrnjena proti USB in ethernet priključkom.

    ![Trak kabla povezan s priključkom za kamero na Pi-ju](../../../../../translated_images/sl/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Ponovno namestite Grove Base Hat.

## Programiranje kamere

Raspberry Pi lahko zdaj programirate za uporabo kamere z uporabo Python knjižnice [PiCamera](https://pypi.org/project/picamera/).

### Naloga - omogočite način za starejše kamere

Na žalost se je z izdajo Raspberry Pi OS Bullseye spremenila programska oprema za kamere, ki je bila privzeto vključena v OS, kar pomeni, da PiCamera privzeto ne deluje več. Razvija se zamenjava, imenovana PiCamera2, vendar še ni pripravljena za uporabo.

Za zdaj lahko nastavite svoj Pi v način za starejše kamere, da omogočite delovanje PiCamera. Priključek za kamero je privzeto onemogočen, vendar omogočanje programske opreme za starejše kamere samodejno omogoči priključek.

1. Vklopite Pi in počakajte, da se zažene.

1. Zaženite VS Code, bodisi neposredno na Pi-ju bodisi prek razširitve Remote SSH.

1. Zaženite naslednje ukaze iz terminala:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    To bo omogočilo nastavitev za uporabo programske opreme za starejše kamere, nato pa bo Pi znova zagnan, da bo nastavitev začela veljati.

1. Počakajte, da se Pi znova zažene, nato ponovno zaženite VS Code.

### Naloga - programirajte kamero

Programirajte napravo.

1. V terminalu ustvarite novo mapo v domačem imeniku uporabnika `pi`, imenovano `fruit-quality-detector`. V tej mapi ustvarite datoteko z imenom `app.py`.

1. Odprite to mapo v VS Code.

1. Za interakcijo s kamero lahko uporabite Python knjižnico PiCamera. Namestite Pip paket za to z naslednjim ukazom:

    ```sh
    pip3 install picamera
    ```

1. Dodajte naslednjo kodo v svojo datoteko `app.py`:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Ta koda uvozi nekaj potrebnih knjižnic, vključno s knjižnico `PiCamera`.

1. Dodajte naslednjo kodo pod to, da inicializirate kamero:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Ta koda ustvari objekt PiCamera, nastavi ločljivost na 640x480. Čeprav so podprte višje ločljivosti (do 3280x2464), razvrščevalnik slik deluje na veliko manjših slikah (227x227), zato ni potrebe po zajemanju in pošiljanju večjih slik.

    Vrstica `camera.rotation = 0` nastavi rotacijo slike. Trak kabla vstopa na dno kamere, vendar če je vaša kamera obrnjena, da lažje usmeri predmet, ki ga želite razvrstiti, lahko to vrstico spremenite na število stopinj rotacije.

    ![Kamera, obrnjena navzdol nad pločevinko pijače](../../../../../translated_images/sl/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    Na primer, če trak kabla obesite nad nekaj, tako da je na vrhu kamere, nastavite rotacijo na 180:

    ```python
    camera.rotation = 180
    ```

    Kamera potrebuje nekaj sekund, da se zažene, zato je tu vrstica `time.sleep(2)`.

1. Dodajte naslednjo kodo pod to, da zajamete sliko kot binarne podatke:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Ta koda ustvari objekt `BytesIO` za shranjevanje binarnih podatkov. Slika se prebere iz kamere kot datoteka JPEG in shrani v ta objekt. Ta objekt ima kazalec položaja, ki označuje, kje se nahaja v podatkih, zato vrstica `image.seek(0)` premakne ta kazalec nazaj na začetek, da se lahko vsi podatki kasneje preberejo.

1. Pod to dodajte naslednjo kodo za shranjevanje slike v datoteko:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Ta koda odpre datoteko z imenom `image.jpg` za pisanje, nato prebere vse podatke iz objekta `BytesIO` in jih zapiše v datoteko.

    > 💁 Sliko lahko zajamete neposredno v datoteko namesto v objekt `BytesIO` tako, da ime datoteke posredujete klicu `camera.capture`. Razlog za uporabo objekta `BytesIO` je, da boste kasneje v tej lekciji sliko poslali svojemu razvrščevalniku slik.

1. Usmerite kamero v nekaj in zaženite to kodo.

1. Slika bo zajeta in shranjena kot `image.jpg` v trenutni mapi. To datoteko boste videli v raziskovalcu VS Code. Izberite datoteko, da si ogledate sliko. Če je potrebna rotacija, posodobite vrstico `camera.rotation = 0` po potrebi in posnemite novo sliko.

> 💁 To kodo najdete v mapi [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 Vaš program za kamero je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.