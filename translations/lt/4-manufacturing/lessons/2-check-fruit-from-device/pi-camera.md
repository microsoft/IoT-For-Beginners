<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-28T19:10:06+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "lt"
}
-->
# Užfiksuokite vaizdą - Raspberry Pi

Šioje pamokos dalyje pridėsite kameros jutiklį prie savo Raspberry Pi ir nuskaitysite vaizdus iš jo.

## Aparatinė įranga

Raspberry Pi reikalinga kamera.

Kamera, kurią naudosite, yra [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). Ši kamera sukurta veikti su Raspberry Pi ir jungiasi per specialų jungtį ant Pi.

> 💁 Ši kamera naudoja [Camera Serial Interface, protokolą iš Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), žinomą kaip MIPI-CSI. Tai specialus protokolas vaizdams perduoti.

## Prijunkite kamerą

Kamera gali būti prijungta prie Raspberry Pi naudojant juostinį kabelį.

### Užduotis - prijunkite kamerą

![Raspberry Pi kamera](../../../../../translated_images/lt/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Išjunkite Pi.

1. Prijunkite juostinį kabelį, kuris yra su kamera, prie kameros. Norėdami tai padaryti, švelniai patraukite juodą plastikinį klipą laikiklyje, kad jis šiek tiek išslystų, tada įstumkite kabelį į lizdą, mėlyną pusę nukreipdami nuo objektyvo, o metalines kontaktų juostas nukreipdami link objektyvo. Kai kabelis bus visiškai įstumtas, pastumkite juodą plastikinį klipą atgal į vietą.

    Animaciją, kaip atidaryti klipą ir įstatyti kabelį, galite rasti [Raspberry Pi dokumentacijoje apie kameros modulio naudojimą](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![Juostinis kabelis įstatytas į kameros modulį](../../../../../translated_images/lt/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Nuimkite Grove Base Hat nuo Pi.

1. Perkiškite juostinį kabelį per kameros angą Grove Base Hat. Įsitikinkite, kad mėlyna kabelio pusė nukreipta link analoginių prievadų, pažymėtų **A0**, **A1** ir pan.

    ![Juostinis kabelis perkištas per Grove Base Hat](../../../../../translated_images/lt/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Įstatykite juostinį kabelį į kameros jungtį ant Pi. Vėlgi, patraukite juodą plastikinį klipą aukštyn, įstatykite kabelį, tada pastumkite klipą atgal. Mėlyna kabelio pusė turėtų būti nukreipta į USB ir Ethernet prievadus.

    ![Juostinis kabelis prijungtas prie kameros jungties ant Pi](../../../../../translated_images/lt/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Vėl pritvirtinkite Grove Base Hat.

## Programuokite kamerą

Dabar Raspberry Pi galima programuoti naudoti kamerą naudojant [PiCamera](https://pypi.org/project/picamera/) Python biblioteką.

### Užduotis - įjunkite senąjį kameros režimą

Deja, su Raspberry Pi OS Bullseye išleidimu, kameros programinė įranga, kuri buvo su OS, pasikeitė, todėl pagal numatymą PiCamera nebeveikia. Šiuo metu kuriama nauja versija, vadinama PiCamera2, tačiau ji dar nėra paruošta naudojimui.

Kol kas galite nustatyti savo Pi į senąjį kameros režimą, kad PiCamera veiktų. Kamero jungtis taip pat yra išjungta pagal numatymą, tačiau įjungus senąją kameros programinę įrangą, jungtis automatiškai įjungiama.

1. Įjunkite Pi ir palaukite, kol jis užsikraus.

1. Paleiskite VS Code, tiesiogiai ant Pi arba prisijungę per Remote SSH plėtinį.

1. Paleiskite šias komandas iš terminalo:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Tai pakeis nustatymą, kad įjungtų senąją kameros programinę įrangą, tada perkraus Pi, kad šis nustatymas įsigaliotų.

1. Palaukite, kol Pi bus perkrautas, tada vėl paleiskite VS Code.

### Užduotis - programuokite kamerą

Programuokite įrenginį.

1. Terminale sukurkite naują aplanką `pi` vartotojo namų kataloge, pavadintą `fruit-quality-detector`. Sukurkite failą šiame aplanke, pavadintą `app.py`.

1. Atidarykite šį aplanką VS Code.

1. Norėdami sąveikauti su kamera, galite naudoti PiCamera Python biblioteką. Įdiekite Pip paketą su šia komanda:

    ```sh
    pip3 install picamera
    ```

1. Pridėkite šį kodą į savo `app.py` failą:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Šis kodas importuoja reikalingas bibliotekas, įskaitant `PiCamera` biblioteką.

1. Pridėkite šį kodą žemiau, kad inicializuotumėte kamerą:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Šis kodas sukuria PiCamera objektą, nustato rezoliuciją į 640x480. Nors palaikomos didesnės rezoliucijos (iki 3280x2464), vaizdų klasifikatorius veikia su daug mažesniais vaizdais (227x227), todėl nėra reikalo fiksuoti ir siųsti didesnių vaizdų.

    Eilutė `camera.rotation = 0` nustato vaizdo pasukimą. Juostinis kabelis įeina į kameros apačią, tačiau jei jūsų kamera buvo pasukta, kad būtų lengviau nukreipti į objektą, kurį norite klasifikuoti, galite pakeisti šią eilutę į pasukimo laipsnių skaičių.

    ![Kamera pakabinta virš gėrimo skardinės](../../../../../translated_images/lt/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    Pavyzdžiui, jei pakabinsite juostinį kabelį virš objekto, kad jis būtų kameros viršuje, nustatykite pasukimą į 180:

    ```python
    camera.rotation = 180
    ```

    Kamera užtrunka kelias sekundes, kol pradeda veikti, todėl naudojama `time.sleep(2)`.

1. Pridėkite šį kodą žemiau, kad užfiksuotumėte vaizdą kaip dvejetainius duomenis:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Šis kodas sukuria `BytesIO` objektą, skirtą saugoti dvejetainius duomenis. Vaizdas iš kameros nuskaitomas kaip JPEG failas ir saugomas šiame objekte. Šis objektas turi pozicijos indikatorių, kad žinotų, kur yra duomenyse, todėl `image.seek(0)` eilutė perkelia šią poziciją atgal į pradžią, kad vėliau būtų galima perskaityti visus duomenis.

1. Žemiau pridėkite šį kodą, kad išsaugotumėte vaizdą į failą:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Šis kodas atidaro failą, pavadintą `image.jpg`, rašymui, tada perskaito visus duomenis iš `BytesIO` objekto ir įrašo juos į failą.

    > 💁 Vaizdą galite užfiksuoti tiesiai į failą, o ne į `BytesIO` objektą, perduodami failo pavadinimą `camera.capture` iškvietimui. Priežastis, kodėl naudojamas `BytesIO` objektas, yra ta, kad vėliau šioje pamokoje galėsite siųsti vaizdą į savo vaizdų klasifikatorių.

1. Nukreipkite kamerą į ką nors ir paleiskite šį kodą.

1. Vaizdas bus užfiksuotas ir išsaugotas kaip `image.jpg` dabartiniame aplanke. Šį failą matysite VS Code naršyklėje. Pasirinkite failą, kad peržiūrėtumėte vaizdą. Jei reikia pasukimo, atnaujinkite eilutę `camera.rotation = 0` pagal poreikį ir padarykite kitą nuotrauką.

> 💁 Šį kodą galite rasti [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi) aplanke.

😀 Jūsų kameros programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.