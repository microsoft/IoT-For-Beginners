<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-27T20:54:36+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "sw"
}
-->
# Kupiga picha - Raspberry Pi

Katika sehemu hii ya somo, utaongeza kihisi cha kamera kwenye Raspberry Pi yako, na kusoma picha kutoka kwake.

## Vifaa

Raspberry Pi inahitaji kamera.

Kamera utakayotumia ni [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). Kamera hii imetengenezwa kufanya kazi na Raspberry Pi na inaunganishwa kupitia kiunganishi maalum kwenye Pi.

> 💁 Kamera hii hutumia [Camera Serial Interface, itifaki kutoka Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), inayojulikana kama MIPI-CSI. Hii ni itifaki maalum ya kutuma picha.

## Unganisha kamera

Kamera inaweza kuunganishwa na Raspberry Pi kwa kutumia kebo ya ribbon.

### Kazi - unganisha kamera

![Kamera ya Raspberry Pi](../../../../../translated_images/sw/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Zima Pi.

1. Unganisha kebo ya ribbon inayokuja na kamera kwenye kamera. Ili kufanya hivyo, vuta kwa upole kipande cha plastiki cheusi kwenye kishikiliaji ili kitoke kidogo, kisha telezesha kebo kwenye soketi, upande wa bluu ukiwa mbali na lenzi, na vipande vya pini za chuma vikiwa karibu na lenzi. Mara kebo itakapokuwa ndani kabisa, sukuma kipande cha plastiki cheusi kurudi mahali pake.

    Unaweza kupata uhuishaji unaoonyesha jinsi ya kufungua kipande na kuingiza kebo kwenye [Raspberry Pi Getting Started with the Camera module documentation](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![Kebo ya ribbon imeingizwa kwenye moduli ya kamera](../../../../../translated_images/sw/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Ondoa Grove Base Hat kutoka Pi.

1. Pitisha kebo ya ribbon kupitia nafasi ya kamera kwenye Grove Base Hat. Hakikisha upande wa bluu wa kebo unakabili bandari za analog zilizoandikwa **A0**, **A1** nk.

    ![Kebo ya ribbon ikipitia Grove Base Hat](../../../../../translated_images/sw/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Ingiza kebo ya ribbon kwenye soketi ya kamera kwenye Pi. Tena, vuta kipande cha plastiki cheusi juu, ingiza kebo, kisha sukuma kipande kurudi mahali pake. Upande wa bluu wa kebo unapaswa kuelekea bandari za USB na ethernet.

    ![Kebo ya ribbon imeunganishwa kwenye soketi ya kamera kwenye Pi](../../../../../translated_images/sw/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Rudisha Grove Base Hat.

## Programu ya kamera

Raspberry Pi sasa inaweza kupangwa kutumia kamera kwa kutumia maktaba ya Python ya [PiCamera](https://pypi.org/project/picamera/).

### Kazi - wezesha hali ya kamera ya urithi

Kwa bahati mbaya, na kutolewa kwa Raspberry Pi OS Bullseye, programu ya kamera iliyokuja na OS ilibadilika, ikimaanisha kwa default PiCamera haifanyi kazi tena. Kuna mbadala unaotengenezwa, unaoitwa PiCamera2, lakini bado haujawa tayari kutumika.

Kwa sasa, unaweza kuweka Pi yako katika hali ya kamera ya urithi ili kuruhusu PiCamera kufanya kazi. Soketi ya kamera pia imezimwa kwa default, lakini kuwasha programu ya kamera ya urithi kunawezesha soketi moja kwa moja.

1. Washa Pi na subiri ianze.

1. Fungua VS Code, ama moja kwa moja kwenye Pi, au unganisha kupitia kiendelezi cha Remote SSH.

1. Endesha amri zifuatazo kutoka kwa terminal yako:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Hii itabadilisha mpangilio kuwezesha programu ya kamera ya urithi, kisha kuanzisha upya Pi ili mpangilio huo uanze kutumika.

1. Subiri Pi ianzishe upya, kisha fungua tena VS Code.

### Kazi - programu ya kamera

Panga kifaa.

1. Kutoka kwa terminal, tengeneza folda mpya kwenye saraka ya nyumbani ya mtumiaji `pi` inayoitwa `fruit-quality-detector`. Tengeneza faili katika folda hii inayoitwa `app.py`.

1. Fungua folda hii kwenye VS Code.

1. Ili kuingiliana na kamera, unaweza kutumia maktaba ya Python ya PiCamera. Sakinisha kifurushi cha Pip kwa amri ifuatayo:

    ```sh
    pip3 install picamera
    ```

1. Ongeza msimbo ufuatao kwenye faili yako ya `app.py`:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Msimbo huu huingiza baadhi ya maktaba zinazohitajika, ikiwa ni pamoja na maktaba ya `PiCamera`.

1. Ongeza msimbo ufuatao chini ya hii ili kuanzisha kamera:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Msimbo huu huunda kitu cha PiCamera, huweka azimio kuwa 640x480. Ingawa azimio la juu zaidi linaungwa mkono (hadi 3280x2464), kielekezi cha picha hufanya kazi kwenye picha ndogo zaidi (227x227) kwa hivyo hakuna haja ya kunasa na kutuma picha kubwa zaidi.

    Mstari wa `camera.rotation = 0` huweka mzunguko wa picha. Kebo ya ribbon huingia chini ya kamera, lakini ikiwa kamera yako imezungushwa ili kuruhusu iwe rahisi kuelekea kipengee unachotaka kuainisha, basi unaweza kubadilisha mstari huu kwa idadi ya digrii za mzunguko.

    ![Kamera ikining'inia juu ya kopo la kinywaji](../../../../../translated_images/sw/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    Kwa mfano, ikiwa utaweka kebo ya ribbon juu ya kitu ili iwe juu ya kamera, basi weka mzunguko kuwa 180:

    ```python
    camera.rotation = 180
    ```

    Kamera huchukua sekunde chache kuanza, kwa hivyo mstari wa `time.sleep(2)`.

1. Ongeza msimbo ufuatao chini ya hii ili kunasa picha kama data ya binary:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Msimbo huu huunda kitu cha `BytesIO` kuhifadhi data ya binary. Picha inasomwa kutoka kwa kamera kama faili ya JPEG na kuhifadhiwa katika kitu hiki. Kitu hiki kina kiashiria cha nafasi ili kujua kilipo katika data ili data zaidi iweze kuandikwa mwishoni ikiwa inahitajika, kwa hivyo mstari wa `image.seek(0)` husogeza nafasi hii kurudi mwanzo ili data yote iweze kusomwa baadaye.

1. Chini ya hii, ongeza yafuatayo ili kuhifadhi picha kwenye faili:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Msimbo huu hufungua faili inayoitwa `image.jpg` kwa kuandika, kisha husoma data yote kutoka kwa kitu cha `BytesIO` na kuiandika kwenye faili.

    > 💁 Unaweza kunasa picha moja kwa moja kwenye faili badala ya kitu cha `BytesIO` kwa kupitisha jina la faili kwenye wito wa `camera.capture`. Sababu ya kutumia kitu cha `BytesIO` ni ili baadaye katika somo hili uweze kutuma picha kwa kielekezi chako cha picha.

1. Elekeza kamera kwenye kitu na endesha msimbo huu.

1. Picha itanaswa na kuhifadhiwa kama `image.jpg` katika folda ya sasa. Utaona faili hii katika kivinjari cha VS Code. Chagua faili ili kuona picha. Ikiwa inahitaji mzunguko, sasisha mstari wa `camera.rotation = 0` kama inavyohitajika na piga picha nyingine.

> 💁 Unaweza kupata msimbo huu katika folda ya [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 Programu yako ya kamera imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.