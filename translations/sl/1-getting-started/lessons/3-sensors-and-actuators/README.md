# Interakcija s fizičnim svetom s senzorji in aktuatorji

![Sketchnote pregled te lekcije](../../../../../translated_images/sl/lesson-3.cc3b7b4cd646de59.webp)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliko za večjo različico.

Ta lekcija je bila del [serije Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) iz [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekcija je bila predstavljena v dveh videih - enourni lekciji in enourni pisarniški uri, kjer so podrobneje obravnavali dele lekcije in odgovarjali na vprašanja.

[![Lekcija 3: Interakcija s fizičnim svetom s senzorji in aktuatorji](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Lekcija 3: Interakcija s fizičnim svetom s senzorji in aktuatorji - Pisarniška ura](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Kliknite na zgornje slike za ogled videov

## Kviz pred predavanjem

[Kviz pred predavanjem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Uvod

Ta lekcija uvaja dva pomembna koncepta za vašo IoT napravo - senzorje in aktuatorje. Prav tako boste praktično delali z obema, tako da boste svojemu IoT projektu dodali svetlobni senzor, nato pa LED, ki ga boste nadzorovali glede na raven svetlobe, s čimer boste učinkovito ustvarili nočno lučko.

V tej lekciji bomo obravnavali:

* [Kaj so senzorji?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Uporaba senzorja](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Vrste senzorjev](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Kaj so aktuatorji?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Uporaba aktuatorja](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Vrste aktuatorjev](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Kaj so senzorji?

Senzorji so strojne naprave, ki zaznavajo fizični svet - to pomeni, da merijo eno ali več lastnosti okoli sebe in pošiljajo informacije IoT napravi. Senzorji pokrivajo širok spekter naprav, saj je mogoče meriti veliko stvari, od naravnih lastnosti, kot je temperatura zraka, do fizičnih interakcij, kot je gibanje.

Nekateri pogosti senzorji vključujejo:

* Senzorji temperature - ti zaznavajo temperaturo zraka ali temperaturo, v katero so potopljeni. Za hobi projekte in razvijalce so ti pogosto združeni s senzorji zračnega tlaka in vlage v eni napravi.
* Gumbi - ti zaznavajo, kdaj so bili pritisnjeni.
* Svetlobni senzorji - ti zaznavajo raven svetlobe in so lahko namenjeni specifičnim barvam, UV svetlobi, IR svetlobi ali splošni vidni svetlobi.
* Kamere - te zaznavajo vizualno predstavitev sveta z zajemanjem fotografij ali pretakanjem videa.
* Pospeškomeri - ti zaznavajo gibanje v več smereh.
* Mikrofoni - ti zaznavajo zvok, bodisi splošne ravni zvoka ali usmerjen zvok.

✅ Raziščite. Katere senzorje ima vaš telefon?

Vsi senzorji imajo eno skupno stvar - kar zaznajo, pretvorijo v električni signal, ki ga lahko interpretira IoT naprava. Kako se ta električni signal interpretira, je odvisno od senzorja in komunikacijskega protokola, ki se uporablja za komunikacijo z IoT napravo.

## Uporaba senzorja

Sledite ustreznemu vodniku spodaj, da dodate senzor svoji IoT napravi:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Enokartični računalnik - Raspberry Pi](pi-sensor.md)
* [Enokartični računalnik - Virtualna naprava](virtual-device-sensor.md)

## Vrste senzorjev

Senzorji so lahko analogni ali digitalni.

### Analogni senzorji

Nekateri najosnovnejši senzorji so analogni senzorji. Ti senzorji prejmejo napetost od IoT naprave, komponente senzorja prilagodijo to napetost, in napetost, ki jo senzor vrne, se meri za pridobitev vrednosti senzorja.

> 🎓 Napetost je merilo, koliko "potiska" je potrebnega za premik elektrike z enega mesta na drugo, na primer od pozitivnega pola baterije do negativnega pola. Na primer, standardna AA baterija ima 1,5V (V je simbol za volte) in lahko potisne elektriko z močjo 1,5V od svojega pozitivnega pola do negativnega pola. Različna električna strojna oprema zahteva različne napetosti za delovanje, na primer LED lahko sveti z napetostjo med 2-3V, medtem ko bi 100W žarnica potrebovala 240V. Več o napetosti lahko preberete na [strani o napetosti na Wikipediji](https://wikipedia.org/wiki/Voltage).

Eden od primerov je potenciometer. To je gumb, ki ga lahko zavrtite med dvema položajema, senzor pa meri rotacijo.

![Potenciometer nastavljen na srednjo točko, ki prejema 5 voltov in vrača 3,8 volta](../../../../../translated_images/sl/potentiometer.35a348b9ce22f6ec.webp)

IoT naprava pošlje električni signal potenciometru z določeno napetostjo, na primer 5 voltov (5V). Ko se potenciometer prilagodi, spremeni napetost, ki pride iz druge strani. Predstavljajte si potenciometer, označen kot gumb, ki gre od 0 do [11](https://wikipedia.org/wiki/Up_to_eleven), na primer gumb za glasnost na ojačevalniku. Ko je potenciometer v popolnoma izklopljenem položaju (0), bo iz njega prišlo 0V (0 voltov). Ko je v popolnoma vklopljenem položaju (11), bo iz njega prišlo 5V (5 voltov).

> 🎓 To je poenostavitev, več o potenciometrih in spremenljivih upornikih lahko preberete na [strani o potenciometrih na Wikipediji](https://wikipedia.org/wiki/Potentiometer).

Napetost, ki pride iz senzorja, nato prebere IoT naprava, ki se lahko nanjo odzove. Glede na senzor je lahko ta napetost poljubna vrednost ali pa se preslika v standardno enoto. Na primer, analogni temperaturni senzor, ki temelji na [termistorju](https://wikipedia.org/wiki/Thermistor), spreminja svojo upornost glede na temperaturo. Izhodna napetost se nato lahko pretvori v temperaturo v kelvinih, in ustrezno v °C ali °F, z izračuni v kodi.

✅ Kaj mislite, kaj se zgodi, če senzor vrne višjo napetost, kot je bila poslana (na primer iz zunanjega napajalnika)? ⛔️ NE testirajte tega.

#### Pretvorba iz analognega v digitalno

IoT naprave so digitalne - ne morejo delati z analognimi vrednostmi, delajo le z 0 in 1. To pomeni, da je treba analogne vrednosti senzorjev pretvoriti v digitalni signal, preden jih je mogoče obdelati. Veliko IoT naprav ima pretvornike iz analognega v digitalno (ADC), ki pretvarjajo analogne vhode v digitalne predstavitve njihovih vrednosti. Senzorji lahko delujejo tudi z ADC-ji prek priključne plošče. Na primer, v Seeed Grove ekosistemu z Raspberry Pi, se analogni senzorji povežejo na specifična vrata na 'hat'-u, ki je povezan z GPIO pini Pi-ja, in ta 'hat' ima ADC za pretvorbo napetosti v digitalni signal, ki ga je mogoče poslati prek GPIO pinov Pi-ja.

Predstavljajte si, da imate analogni svetlobni senzor, povezan z IoT napravo, ki uporablja 3,3V in vrača vrednost 1V. Ta 1V v digitalnem svetu ne pomeni nič, zato ga je treba pretvoriti. Napetost bo pretvorjena v analogno vrednost z uporabo lestvice, odvisno od naprave in senzorja. Eden od primerov je Seeed Grove svetlobni senzor, ki vrača vrednosti od 0 do 1.023. Za ta senzor, ki deluje pri 3,3V, bi izhod 1V pomenil vrednost 300. IoT naprava ne more obdelati 300 kot analogno vrednost, zato bi bila vrednost pretvorjena v `0000000100101100`, binarno predstavitev števila 300, s strani Grove 'hat'-a. To bi nato obdelala IoT naprava.

✅ Če ne poznate binarnega sistema, naredite majhno raziskavo, da se naučite, kako so števila predstavljena z 0 in 1. [BBC Bitesize uvod v binarni sistem](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) je odličen začetek.

Z vidika kodiranja je vse to običajno obravnavano z knjižnicami, ki so priložene senzorjem, zato vam ni treba skrbeti za to pretvorbo sami. Za Grove svetlobni senzor bi uporabili Python knjižnico in poklicali lastnost `light`, ali pa Arduino knjižnico in poklicali `analogRead`, da dobite vrednost 300.

### Digitalni senzorji

Digitalni senzorji, podobno kot analogni senzorji, zaznavajo svet okoli sebe z uporabo sprememb električne napetosti. Razlika je v tem, da oddajajo digitalni signal, bodisi z merjenjem le dveh stanj ali z uporabo vgrajenega ADC-ja. Digitalni senzorji postajajo vse bolj pogosti, da se izognejo potrebi po uporabi ADC-ja bodisi v priključni plošči bodisi na sami IoT napravi.

Najenostavnejši digitalni senzor je gumb ali stikalo. To je senzor z dvema stanjem, vklopljen ali izklopljen.

![Gumb prejme 5 voltov. Ko ni pritisnjen, vrača 0 voltov, ko je pritisnjen, vrača 5 voltov](../../../../../translated_images/sl/button.eadb560b77ac45e5.webp)

Pini na IoT napravah, kot so GPIO pini, lahko neposredno merijo ta signal kot 0 ali 1. Če je poslana napetost enaka vrnjeni napetosti, je prebrana vrednost 1, sicer je prebrana vrednost 0. Pretvorba signala ni potrebna, saj je lahko le 1 ali 0.

> 💁 Napetosti nikoli niso natančne, še posebej, ker imajo komponente v senzorju nekaj upornosti, zato je običajno določena toleranca. Na primer, GPIO pini na Raspberry Pi delujejo pri 3,3V in berejo povratni signal nad 1,8V kot 1, pod 1,8V kot 0.

* 3,3V gre v gumb. Gumb je izklopljen, zato pride ven 0V, kar daje vrednost 0.
* 3,3V gre v gumb. Gumb je vklopljen, zato pride ven 3,3V, kar daje vrednost 1.

Naprednejši digitalni senzorji berejo analogne vrednosti, nato pa jih pretvorijo z vgrajenimi ADC-ji v digitalne signale. Na primer, digitalni temperaturni senzor bo še vedno uporabljal termoelement na enak način kot analogni senzor in bo še vedno meril spremembo napetosti, ki jo povzroča upornost termoelementa pri trenutni temperaturi. Namesto da bi vrnil analogno vrednost in se zanašal na napravo ali priključno ploščo za pretvorbo v digitalni signal, bo ADC, vgrajen v senzor, pretvoril vrednost in jo poslal kot niz 0 in 1 IoT napravi. Te 0 in 1 se pošljejo na enak način kot digitalni signal za gumb, pri čemer je 1 polna napetost, 0 pa 0V.

![Digitalni temperaturni senzor pretvarja analogno vrednost v binarne podatke, kjer je 0 enako 0 voltov in 1 enako 5 voltov, preden jih pošlje IoT napravi](../../../../../translated_images/sl/temperature-as-digital.85004491b977bae1.webp)

Pošiljanje digitalnih podatkov omogoča, da senzorji postanejo bolj zapleteni in pošiljajo podrobnejše podatke, celo šifrirane podatke za varne senzorje. Eden od primerov je kamera. To je senzor, ki zajame sliko in jo pošlje kot digitalne podatke, ki vsebujejo to sliko, običajno v stisnjeni obliki, kot je JPEG, da jo prebere IoT naprava. Lahko celo pretaka video z zajemanjem slik in pošiljanjem bodisi celotne slike okvir za okvirjem bodisi stisnjenega video toka.

## Kaj so aktuatorji?

Aktuatorji so nasprotje senzorjev - pretvorijo električni signal iz vaše IoT naprave v interakcijo s fizičnim svetom, kot je oddajanje svetlobe ali zvoka ali premikanje motorja.

Nekateri pogosti aktuatorji vključujejo:

* LED - oddajajo svetlobo, ko so vklopljeni.
* Zvočnik - oddajajo zvok glede na signal, ki jim je poslan, od osnovnega brenčala do zvočnika, ki lahko predvaja glasbo.
* Koračni motor - pretvorijo signal v določeno količino rotacije, na primer zavrtijo gumb za 90°.
* Rele - to so stikala, ki jih je mogoče vklopiti ali izklopiti z električnim signalom. Omogočajo majhni napetosti iz IoT naprave, da vklopi večje napetosti.
* Zasloni - to so bolj zapleteni aktuatorji, ki prikazujejo informacije na večsegmentnem zaslonu. Zasloni se razlikujejo od preprostih LED zaslonov do visokoločljivostnih video monitorjev.

✅ Raziščite. Katere aktuatorje ima vaš telefon?

## Uporaba aktuatorja

Sledite ustreznemu vodniku spodaj, da dodate aktuator svoji IoT napravi, ki ga bo nadzoroval senzor, in zgradite IoT nočno lučko. Ta bo zbirala ravni svetlobe iz svetlobnega senzorja in uporabljala aktuator v obliki LED, da oddaja svetlobo, ko je zaznana raven svetlobe prenizka.

![Diagram poteka naloge, ki prikazuje branje in preverjanje ravni svetlobe ter nadzor LED](../../../../../translated_images/sl/assignment-1-flow.7552a51acb1a5ec8.webp)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Enokartični računalnik - Raspberry Pi](pi-actuator.md)
* [Enokartični računalnik - Virtualna naprava](virtual-device-actuator.md)

## Vrste aktuatorjev

Tako kot senzorji so tudi aktuatorji lahko analogni ali digitalni.

### Analogni aktuatorji

Analogni aktuatorji sprejmejo analogni signal in ga pretvorijo v neko vrsto interakcije, kjer se interakcija spreminja glede na dobavljeno napetost.

Eden od primerov je zatemnilna luč, kot so tiste, ki jih imate morda doma. Količina napetosti, ki jo prejme luč, določa, kako svetla je.
![Svetloba zatemnjena pri nizki napetosti in svetlejša pri višji napetosti](../../../../../translated_images/sl/dimmable-light.9ceffeb195dec1a8.webp)

Tako kot pri senzorjih, IoT naprava deluje na digitalnih signalih, ne analognih. To pomeni, da za pošiljanje analognega signala IoT naprava potrebuje pretvornik iz digitalnega v analogni signal (DAC), bodisi neposredno na IoT napravi ali na priključni plošči. Ta pretvornik spremeni 0 in 1 iz IoT naprave v analogno napetost, ki jo lahko uporabi aktuator.

✅ Kaj mislite, kaj se zgodi, če IoT naprava pošlje višjo napetost, kot jo aktuator lahko prenese?  
⛔️ TEGA NE TESTIRAJTE.

#### Modulacija širine impulza

Druga možnost za pretvorbo digitalnih signalov iz IoT naprave v analogni signal je modulacija širine impulza (PWM). To vključuje pošiljanje številnih kratkih digitalnih impulzov, ki delujejo, kot da bi bil analogni signal.

Na primer, PWM lahko uporabite za nadzor hitrosti motorja.

Predstavljajte si, da upravljate motor s 5V napajanjem. Pošljete kratek impulz motorju, ki za dve stotinki sekunde (0,02s) preklopi napetost na visoko (5V). V tem času se motor lahko zavrti za eno desetino obrata ali 36°. Signal nato za dve stotinki sekunde (0,02s) preklopi na nizko napetost (0V). Vsak cikel vklopa in izklopa traja 0,04s. Cikel se nato ponovi.

![Modulacija širine impulza - rotacija motorja pri 150 RPM](../../../../../translated_images/sl/pwm-motor-150rpm.83347ac04ca38482.webp)

To pomeni, da v eni sekundi pošljete 25 impulzov 5V, ki trajajo 0,02s in zavrtijo motor, vsakemu pa sledi 0,02s premora pri 0V, ko motor ne vrti. Vsak impulz zavrti motor za eno desetino obrata, kar pomeni, da motor opravi 2,5 obrata na sekundo. Uporabili ste digitalni signal za vrtenje motorja pri 2,5 obratih na sekundo ali 150 [obratov na minuto](https://wikipedia.org/wiki/Revolutions_per_minute) (nestandardna enota za merjenje hitrosti vrtenja).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Ko je PWM signal vklopljen polovico časa in izklopljen polovico časa, se to imenuje [50% delovni cikel](https://wikipedia.org/wiki/Duty_cycle). Delovni cikli se merijo kot odstotek časa, ko je signal v stanju vklopa v primerjavi s stanjem izklopa.

![Modulacija širine impulza - rotacija motorja pri 75 RPM](../../../../../translated_images/sl/pwm-motor-75rpm.a5e4c939934b6e14.webp)

Hitrost motorja lahko spremenite s spreminjanjem dolžine impulzov. Na primer, pri istem motorju lahko ohranite enak čas cikla 0,04s, pri čemer je impulz vklopa prepolovljen na 0,01s, impulz izklopa pa povečan na 0,03s. Število impulzov na sekundo (25) ostane enako, vendar je vsak impulz vklopa polovične dolžine. Polovični impulz zavrti motor za eno dvajsetino obrata, in pri 25 impulzih na sekundo motor opravi 1,25 obrata na sekundo ali 75 RPM. S spreminjanjem hitrosti impulzov digitalnega signala ste prepolovili hitrost analognega motorja.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Kako bi ohranili gladko vrtenje motorja, še posebej pri nizkih hitrostih? Bi uporabili majhno število dolgih impulzov z dolgimi premori ali veliko zelo kratkih impulzov z zelo kratkimi premori?

> 💁 Nekateri senzorji uporabljajo PWM za pretvorbo analognih signalov v digitalne.

> 🎓 Več o modulaciji širine impulza si lahko preberete na [strani o modulaciji širine impulza na Wikipediji](https://wikipedia.org/wiki/Pulse-width_modulation).

### Digitalni aktuatorji

Digitalni aktuatorji, podobno kot digitalni senzorji, imajo bodisi dve stanji, ki ju nadzoruje visoka ali nizka napetost, bodisi imajo vgrajen DAC, ki lahko pretvori digitalni signal v analognega.

Enostaven digitalni aktuator je LED. Ko naprava pošlje digitalni signal 1, se pošlje visoka napetost, ki prižge LED. Ko se pošlje digitalni signal 0, napetost pade na 0V in LED ugasne.

![LED je ugasnjen pri 0 voltih in prižgan pri 5V](../../../../../translated_images/sl/led.ec6d94f66676a174.webp)

✅ Katere druge enostavne aktuatorje z dvema stanjem si lahko zamislite? En primer je solenoid, ki je elektromagnet, ki ga je mogoče aktivirati za premikanje zapaha vrat pri zaklepanju/odklepanju vrat.

Bolj napredni digitalni aktuatorji, kot so zasloni, zahtevajo, da se digitalni podatki pošiljajo v določenih formatih. Običajno imajo knjižnice, ki olajšajo pošiljanje pravilnih podatkov za njihovo upravljanje.

---

## 🚀 Izziv

Izziv v zadnjih dveh lekcijah je bil, da naštejete čim več IoT naprav, ki jih imate doma, v šoli ali na delovnem mestu, in ugotovite, ali so zgrajene okoli mikrokrmilnikov ali enokartičnih računalnikov, ali celo mešanice obojega.

Za vsako napravo, ki ste jo navedli, katere senzorje in aktuatorje so povezani z njo? Kakšen je namen vsakega senzorja in aktuatorja, povezanega s temi napravami?

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Pregled in samostojno učenje

* Preberite o elektriki in vezjih na [ThingLearn](http://thinglearn.jenlooper.com/curriculum/).  
* Preberite o različnih vrstah temperaturnih senzorjev na [Seeed Studios Temperature Sensors guide](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/)  
* Preberite o LED diodah na [strani o LED diodah na Wikipediji](https://wikipedia.org/wiki/Light-emitting_diode)  

## Naloga

[Raziskovanje senzorjev in aktuatorjev](assignment.md)  

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.