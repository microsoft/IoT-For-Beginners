<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e9ee00eb5fc55922a73762acc542166b",
  "translation_date": "2025-08-27T22:26:46+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/README.md",
  "language_code": "hu"
}
-->
# Érzékelők és működtetők használata a fizikai világban

![A lecke vázlatos áttekintése](../../../../../translated_images/lesson-3.cc3b7b4cd646de598698cce043c0393fd62ef42bac2eaf60e61272cd844250f4.hu.jpg)

> Vázlatrajz: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

Ez a lecke a [Hello IoT sorozat](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) részeként került bemutatásra a [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) keretében. A lecke két videóból állt: egy 1 órás tanórából és egy 1 órás konzultációból, amely mélyebben foglalkozott a lecke egyes részeivel és válaszolt a kérdésekre.

[![3. lecke: Érzékelők és működtetők használata a fizikai világban](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![3. lecke: Érzékelők és működtetők használata a fizikai világban - Konzultáció](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Kattints a fenti képekre a videók megtekintéséhez

## Előzetes kvíz

[Előzetes kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Bevezetés

Ez a lecke két fontos fogalmat mutat be az IoT eszközökkel kapcsolatban: az érzékelőket és a működtetőket. Gyakorlatban is kipróbálhatod őket: hozzáadsz egy fényérzékelőt az IoT projektedhez, majd egy LED-et, amelyet a fényerősség szabályoz, így gyakorlatilag egy éjszakai fényt építesz.

A lecke során az alábbiakat tárgyaljuk:

* [Mik azok az érzékelők?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Érzékelő használata](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Érzékelőtípusok](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Mik azok a működtetők?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Működtető használata](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Működtetőtípusok](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Mik azok az érzékelők?

Az érzékelők olyan hardvereszközök, amelyek érzékelik a fizikai világot – vagyis mérik a környezetük egy vagy több tulajdonságát, és továbbítják az információt egy IoT eszköznek. Az érzékelők széles skálán mozognak, mivel rengeteg dolgot lehet mérni, a természetes tulajdonságoktól, mint például a levegő hőmérséklete, egészen a fizikai interakciókig, mint például a mozgás.

Néhány gyakori érzékelő:

* Hőmérsékletérzékelők – ezek érzékelik a levegő hőmérsékletét vagy azt, amelybe belemerítik őket. Hobbi célokra és fejlesztők számára ezek gyakran egyetlen érzékelőben kombinálják a légnyomást és a páratartalmat.
* Gombok – ezek érzékelik, ha megnyomták őket.
* Fényérzékelők – ezek érzékelik a fényerősséget, és lehetnek specifikus színekre, UV fényre, infravörös fényre vagy általános látható fényre érzékenyek.
* Kamerák – ezek vizuális reprezentációt érzékelnek a világról, például fényképek készítésével vagy videó streamelésével.
* Gyorsulásmérők – ezek több irányú mozgást érzékelnek.
* Mikrofonok – ezek hangot érzékelnek, akár általános hangerőszintet, akár irányított hangot.

✅ Kutass egy kicsit! Milyen érzékelők vannak a telefonodban?

Minden érzékelőben közös, hogy amit érzékelnek, azt elektromos jellé alakítják, amelyet egy IoT eszköz értelmezni tud. Az, hogy ez az elektromos jel hogyan kerül értelmezésre, az érzékelőtől és az IoT eszközzel való kommunikációs protokolltól függ.

## Érzékelő használata

Kövesd az alábbi útmutatók egyikét, hogy érzékelőt adj az IoT eszközödhöz:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Egylapkás számítógép - Raspberry Pi](pi-sensor.md)
* [Egylapkás számítógép - Virtuális eszköz](virtual-device-sensor.md)

## Érzékelőtípusok

Az érzékelők lehetnek analógok vagy digitálisak.

### Analóg érzékelők

A legegyszerűbb érzékelők közé tartoznak az analóg érzékelők. Ezek az érzékelők feszültséget kapnak az IoT eszköztől, az érzékelő komponensei módosítják ezt a feszültséget, és az érzékelő által visszaküldött feszültséget mérik az érzékelő értékének meghatározásához.

> 🎓 A feszültség azt méri, hogy mekkora "nyomás" van az elektromosság egyik helyről a másikra történő mozgatására, például egy elem pozitív pólusától a negatív pólusáig. Például egy szabványos AA elem 1,5V (a V a volt jele), és 1,5V erővel képes elektromosságot mozgatni a pozitív pólusától a negatív pólusáig. Különböző elektromos hardverek különböző feszültségeket igényelnek a működéshez, például egy LED 2-3V között világít, de egy 100W-os izzólámpa 240V-ot igényel. További információt a feszültségről a [Feszültség Wikipedia oldalán](https://wikipedia.org/wiki/Voltage) találhatsz.

Egy példa erre a potenciométer. Ez egy forgatható tárcsa, amelyet két pozíció között lehet elforgatni, és az érzékelő méri a forgást.

![Egy potenciométer középső állásban, amely 5 voltot kap, és 3,8 voltot ad vissza](../../../../../translated_images/potentiometer.35a348b9ce22f6ec.hu.png)

Az IoT eszköz elektromos jelet küld a potenciométernek egy adott feszültségen, például 5 volton (5V). Ahogy a potenciométert állítod, az megváltoztatja a másik oldalon kijövő feszültséget. Képzeld el, hogy van egy potenciométered, amelyet egy 0-tól [11-ig](https://wikipedia.org/wiki/Up_to_eleven) terjedő skálán jelöltek, például egy hangerőszabályzó gombot egy erősítőn. Amikor a potenciométer teljesen kikapcsolt állásban van (0), akkor 0V (0 volt) jön ki. Amikor teljesen bekapcsolt állásban van (11), akkor 5V (5 volt) jön ki.

> 🎓 Ez egy leegyszerűsítés, további információt a potenciométerekről és a változó ellenállásokról a [potenciométer Wikipedia oldalán](https://wikipedia.org/wiki/Potentiometer) találhatsz.

Az érzékelőből kijövő feszültséget az IoT eszköz olvassa, és az eszköz reagálhat rá. Az érzékelőtől függően ez a feszültség lehet tetszőleges érték, vagy egy szabványos mértékegységhez rendelhető. Például egy analóg hőmérsékletérzékelő, amely egy [termisztorra](https://wikipedia.org/wiki/Thermistor) alapul, az ellenállását a hőmérséklet függvényében változtatja. A kimeneti feszültség kódban végzett számításokkal átalakítható Kelvin, illetve ennek megfelelően °C vagy °F hőmérsékletté.

✅ Mit gondolsz, mi történik, ha az érzékelő magasabb feszültséget ad vissza, mint amit kapott (például egy külső áramforrásból)? ⛔️ NE próbáld ki!

#### Analóg-digitális átalakítás

Az IoT eszközök digitálisak – nem tudnak analóg értékekkel dolgozni, csak 0-kat és 1-eket értenek. Ez azt jelenti, hogy az analóg érzékelő értékeket digitális jellé kell alakítani, mielőtt feldolgozhatók lennének. Sok IoT eszköz rendelkezik analóg-digitális átalakítóval (ADC), amely az analóg bemeneteket digitális értékekké alakítja. Az érzékelők ADC-kkel is működhetnek egy csatlakozópanelen keresztül. Például a Seeed Grove ökoszisztémában egy Raspberry Pi-vel az analóg érzékelők egy 'hat'-hoz csatlakoznak, amely a Pi GPIO tüskéire van kötve, és ez a hat végzi az analóg értékek digitális jellé alakítását.

Képzeld el, hogy van egy analóg fényérzékelőd, amely egy 3,3V-os IoT eszközhöz van csatlakoztatva, és 1V-ot ad vissza. Ez az 1V a digitális világban nem jelent semmit, ezért át kell alakítani. A feszültséget egy skála alapján analóg értékké alakítják az eszköz és az érzékelő függvényében. Például a Seeed Grove fényérzékelő 0-tól 1,023-ig terjedő értékeket ad vissza. Ennél az érzékelőnél, amely 3,3V-on működik, egy 1V-os kimenet 300-as értéket jelentene. Az IoT eszköz nem tud 300-at analóg értékként kezelni, ezért a Grove hat ezt az értéket `0000000100101100`-ra, a 300 bináris reprezentációjára alakítja. Ezt az értéket az IoT eszköz dolgozza fel.

✅ Ha nem ismered a bináris számokat, kutass egy kicsit, hogy megtudd, hogyan ábrázolják a számokat 0-k és 1-ek segítségével. A [BBC Bitesize bináris számok bevezető leckéje](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) egy remek kiindulópont.

Kódolási szempontból mindezt általában az érzékelőkkel érkező könyvtárak kezelik, így neked nem kell ezzel a konverzióval foglalkoznod. A Grove fényérzékelő esetében például a Python könyvtárat használva a `light` tulajdonságot hívhatod meg, vagy az Arduino könyvtárat használva az `analogRead`-ot, hogy megkapd a 300-as értéket.

### Digitális érzékelők

A digitális érzékelők, az analóg érzékelőkhöz hasonlóan, az elektromos feszültség változásait érzékelik. A különbség az, hogy digitális jelet adnak ki, akár csak két állapotot mérve, akár beépített ADC-t használva. A digitális érzékelők egyre gyakoribbak, hogy elkerüljék az ADC használatát akár egy csatlakozópanelen, akár magán az IoT eszközön.

A legegyszerűbb digitális érzékelő egy gomb vagy kapcsoló. Ez egy olyan érzékelő, amelynek két állapota van: be vagy ki.

![Egy gomb 5 voltot kap. Ha nincs lenyomva, 0 voltot ad vissza, ha lenyomva van, 5 voltot ad vissza](../../../../../translated_images/button.eadb560b77ac45e56f523d9d8876e40444f63b419e33eb820082d461fa79490b.hu.png)

Az IoT eszközök, például a GPIO tüskék, közvetlenül mérhetik ezt a jelet 0-ként vagy 1-ként. Ha a küldött feszültség megegyezik a visszaküldött feszültséggel, az olvasott érték 1, különben az olvasott érték 0. Nincs szükség a jel átalakítására, az csak 1 vagy 0 lehet.

> 💁 A feszültségek soha nem pontosak, különösen, mivel az érzékelő alkatrészei némi ellenállással rendelkeznek, ezért általában van egy tűrés. Például a Raspberry Pi GPIO tüskéi 3,3V-on működnek, és a 1,8V feletti visszajelzést 1-nek, az 1,8V alatti visszajelzést 0-nak olvassák.

* 3,3V megy a gombba. A gomb ki van kapcsolva, így 0V jön ki, ami 0 értéket ad.
* 3,3V megy a gombba. A gomb be van kapcsolva, így 3,3V jön ki, ami 1 értéket ad.

Fejlettebb digitális érzékelők analóg értékeket olvasnak, majd beépített ADC-kkel digitális jelekké alakítják azokat. Például egy digitális hőmérsékletérzékelő továbbra is használ egy hőelemet, ugyanúgy, mint egy analóg érzékelő, és továbbra is méri a hőelem ellenállásának változását az aktuális hőmérsékleten. Ahelyett, hogy analóg értéket adna vissza, és az eszközre vagy a csatlakozópanelre bízná a digitális jellé alakítást, az érzékelőbe épített ADC átalakítja az értéket, és 0-k és 1-ek sorozataként küldi el az IoT eszköznek. Ezek a 0-k és 1-ek ugyanúgy kerülnek továbbításra, mint egy gomb digitális jele, ahol az 1 a teljes feszültséget, a 0 pedig a 0V-ot jelenti.

![Egy digitális hőmérsékletérzékelő, amely egy analóg értéket bináris adatokra alakít, ahol 0 a 0 voltot, 1 az 5 voltot jelenti, mielőtt elküldi az IoT eszköznek](../../../../../translated_images/temperature-as-digital.85004491b977bae1.hu.png)

A digitális adatok küldése lehetővé teszi, hogy az érzékelők bonyolultabbá váljanak, és részletesebb adatokat, akár titkosított adatokat is küldjenek biztonságos érzékelők esetén. Egy példa erre egy kamera. Ez egy olyan érzékelő, amely képet rögzít, és digitális adatként küldi el az IoT eszköznek, általában tömörített formátumban, például JPEG-ben. Akár videót is streamelhet, képkockánként teljes képet vagy tömörített videófolyamot küldve.

## Mik azok a működtetők?

A működtetők az érzékelők ellentétei – egy IoT eszköz elektromos jelét alakítják át a fizikai világgal való interakcióvá, például fény vagy hang kibocsátására, vagy egy motor mozgatására.

Néhány gyakori működtető:

* LED – ezek fényt bocsátanak ki, amikor bekapcsolják őket.
* Hangszóró – ezek hangot bocsátanak ki a nekik küldött jel alapján, az egyszerű csipogótól a zenét lejátszó hangszóróig.
* Lépésmotor – ezek egy meghatározott forgási szöget hajtanak végre, például egy tárcsa 90°-os elforgatását.
* Relé – ezek kapcsolók, amelyeket elektromos jellel lehet be- vagy kikapcsolni. Lehetővé teszik, hogy egy IoT eszköz kis feszültsége nagyobb feszültségeket kapcsoljon be.
* Képernyők – ezek összetettebb működtetők, amelyek több szegmensű kijelzőn jelenítenek meg információkat. A képernyők az egyszerű LED kijelzőktől a nagy felbontású videómonitorokig terjednek.

✅ Kutass egy kicsit! Milyen működtetők vannak a telefonodban?

## Működt
![Egy fény alacsony feszültségen halványan, magasabb feszültségen pedig fényesen világít](../../../../../translated_images/dimmable-light.9ceffeb195dec1a849da718b2d71b32c35171ff7dfea9c07bbf82646a67acf6b.hu.png)

Akárcsak az érzékelők esetében, a tényleges IoT eszköz digitális jelekkel működik, nem analóg jelekkel. Ez azt jelenti, hogy analóg jel küldéséhez az IoT eszköznek szüksége van egy digitális-analóg átalakítóra (DAC), amely lehet közvetlenül az IoT eszközön vagy egy csatlakozópanelen. Ez átalakítja az IoT eszköz 0 és 1 értékeit olyan analóg feszültséggé, amelyet az aktuátor használni tud.

✅ Mit gondolsz, mi történik, ha az IoT eszköz magasabb feszültséget küld, mint amit az aktuátor kezelni tud?
⛔️ NE próbáld ki ezt.

#### Impulzusszélesség-moduláció

Egy másik lehetőség az IoT eszköz digitális jeleinek analóg jellé alakítására az impulzusszélesség-moduláció (PWM). Ez rövid digitális impulzusok küldését jelenti, amelyek úgy viselkednek, mintha analóg jelek lennének.

Például PWM segítségével vezérelheted egy motor sebességét.

Képzeld el, hogy egy motort vezérlesz 5V-os táppal. Rövid impulzust küldesz a motorodnak, amely 0,02 másodpercre (0,02s) magas feszültségre (5V) kapcsol. Ez idő alatt a motor egy tized fordulatot, azaz 36°-ot tesz meg. Ezután a jel szünetel 0,02 másodpercre (0,02s), alacsony jelet (0V) küldve. Minden be- és kikapcsolási ciklus 0,04 másodpercig tart. A ciklus ismétlődik.

![Impulzusszélesség-modulációval egy motor forgása 150 RPM sebességgel](../../../../../translated_images/pwm-motor-150rpm.83347ac04ca38482.hu.png)

Ez azt jelenti, hogy egy másodperc alatt 25 darab 0,02 másodperces 5V-os impulzust küldesz a motor forgatására, amelyeket 0,02 másodperces 0V-os szünet követ, amikor a motor nem forog. Minden impulzus egy tized fordulatot eredményez, így a motor másodpercenként 2,5 fordulatot tesz meg. Digitális jelet használtál arra, hogy a motort másodpercenként 2,5 fordulatra, vagy 150 [fordulat/perc](https://wikipedia.org/wiki/Revolutions_per_minute) sebességre állítsd (egy nem szabványos forgási sebesség mértékegység).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Amikor egy PWM jel az idő felében be van kapcsolva, a másik felében pedig ki, azt [50%-os kitöltési tényezőnek](https://wikipedia.org/wiki/Duty_cycle) nevezzük. A kitöltési tényezőt az idő százalékában mérik, amely alatt a jel be van kapcsolva a kikapcsolt állapothoz képest.

![Impulzusszélesség-modulációval egy motor forgása 75 RPM sebességgel](../../../../../translated_images/pwm-motor-75rpm.a5e4c939934b6e14.hu.png)

A motor sebességét az impulzusok méretének változtatásával tudod szabályozni. Például ugyanazzal a motorral megtarthatod a ciklusidőt 0,04 másodpercen, miközben a bekapcsolási impulzust felére csökkented, 0,01 másodpercre, és a kikapcsolási impulzust 0,03 másodpercre növeled. Ugyanannyi impulzus van másodpercenként (25), de minden bekapcsolási impulzus fele olyan hosszú. Egy fele hosszú impulzus csak egy huszad fordulatot eredményez, és 25 impulzus másodpercenként 1,25 fordulatot, vagy 75 RPM-et eredményez. A digitális jel impulzussebességének változtatásával felére csökkentetted az analóg motor sebességét.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Hogyan tartanád a motor forgását egyenletesen, különösen alacsony sebességnél? Hosszú impulzusok kis számát használnád hosszú szünetekkel, vagy sok nagyon rövid impulzust nagyon rövid szünetekkel?

> 💁 Néhány érzékelő is PWM-et használ az analóg jelek digitális jelekké alakítására.

> 🎓 További információt az impulzusszélesség-modulációról a [Wikipedia PWM oldalán](https://wikipedia.org/wiki/Pulse-width_modulation) olvashatsz.

### Digitális aktuátorok

A digitális aktuátorok, akárcsak a digitális érzékelők, vagy két állapotban működnek, amelyeket magas vagy alacsony feszültség vezérel, vagy beépített DAC-kal rendelkeznek, így képesek a digitális jelet analóggá alakítani.

Egy egyszerű digitális aktuátor például egy LED. Amikor az eszköz digitális 1 jelet küld, magas feszültséget küld, amely bekapcsolja a LED-et. Amikor digitális 0 jelet küld, a feszültség 0V-ra csökken, és a LED kikapcsol.

![Egy LED 0 voltnál kikapcsolva, 5V-nál bekapcsolva](../../../../../translated_images/led.ec6d94f66676a174ad06d9fa9ea49c2ee89beb18b312d5c6476467c66375b07f.hu.png)

✅ Milyen más egyszerű, kétállapotú aktuátorokat tudsz elképzelni? Egy példa lehet egy szolenoid, amely egy elektromágnes, amely aktiválható például egy ajtózár reteszének mozgatására, az ajtó nyitására/zárására.

A fejlettebb digitális aktuátorok, mint például a képernyők, megkövetelik, hogy a digitális adatokat bizonyos formátumokban küldjék. Általában könyvtárakkal érkeznek, amelyek megkönnyítik a megfelelő adatok küldését a vezérlésükhöz.

---

## 🚀 Kihívás

Az előző két leckében az volt a kihívás, hogy sorold fel az otthonodban, iskoládban vagy munkahelyeden található IoT eszközöket, és döntsd el, hogy mikrovezérlőkre vagy egykártyás számítógépekre épülnek-e, vagy esetleg mindkettő keverékére.

Minden felsorolt eszköznél milyen érzékelők és aktuátorok vannak hozzájuk csatlakoztatva? Mi a célja az ezekhez az eszközökhöz csatlakoztatott érzékelőknek és aktuátoroknak?

## Utólagos kvíz

[Utólagos kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Áttekintés és önálló tanulás

* Olvass az elektromosságról és áramkörökről a [ThingLearn](http://thinglearn.jenlooper.com/curriculum/) oldalon.
* Olvass a különböző típusú hőmérséklet-érzékelőkről a [Seeed Studios Temperature Sensors guide](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/) oldalon.
* Olvass a LED-ekről a [Wikipedia LED oldalán](https://wikipedia.org/wiki/Light-emitting_diode).

## Feladat

[Érzékelők és aktuátorok kutatása](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.