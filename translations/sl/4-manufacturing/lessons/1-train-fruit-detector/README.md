<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f5e63c916d2dd97d58be12aaf76bd9f1",
  "translation_date": "2025-08-28T12:06:47+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/README.md",
  "language_code": "sl"
}
-->
# Ustvarite detektor kakovosti sadja

![Sketchnote pregled te lekcije](../../../../../translated_images/lesson-15.843d21afdc6fb2bba70cd9db7b7d2f91598859fafda2078b0bdc44954194b6c0.sl.jpg)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite sliko za večjo različico.

Ta video ponuja pregled storitve Azure Custom Vision, ki bo obravnavana v tej lekciji.

[![Custom Vision – Strojno učenje na enostaven način | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 Kliknite zgornjo sliko za ogled videa

## Kviz pred predavanjem

[Kviz pred predavanjem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## Uvod

Nedavni vzpon umetne inteligence (AI) in strojnega učenja (ML) razvijalcem danes ponuja širok spekter zmogljivosti. ML modeli se lahko naučijo prepoznavati različne stvari na slikah, vključno z nezrelim sadjem, kar se lahko uporablja v IoT napravah za pomoč pri sortiranju pridelkov bodisi med žetvijo bodisi med obdelavo v tovarnah ali skladiščih.

V tej lekciji se boste naučili o razvrščanju slik – uporabi ML modelov za razlikovanje med slikami različnih stvari. Naučili se boste, kako usposobiti klasifikator slik za razlikovanje med dobrim in slabim sadjem, bodisi nezrelim, prezrelim, poškodovanim ali gnijočim.

V tej lekciji bomo obravnavali:

* [Uporaba AI in ML za sortiranje hrane](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Razvrščanje slik s pomočjo strojnega učenja](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Usposabljanje klasifikatorja slik](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Testiranje vašega klasifikatorja slik](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Ponovno usposabljanje vašega klasifikatorja slik](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## Uporaba AI in ML za sortiranje hrane

Prehranjevanje svetovnega prebivalstva je zahtevno, še posebej po ceni, ki omogoča dostopnost hrane za vse. Eden največjih stroškov je delo, zato se kmetje vse bolj obračajo k avtomatizaciji in orodjem, kot je IoT, za zmanjšanje stroškov dela. Ročna žetev je delovno intenzivna (in pogosto zelo naporna), zato jo v bogatejših državah vse bolj nadomeščajo stroji. Kljub prihrankom pri stroških uporabe strojev za žetev pa obstaja pomanjkljivost – sposobnost sortiranja hrane med žetvijo.

Vsi pridelki ne dozorijo enakomerno. Paradižniki, na primer, lahko še vedno vsebujejo nekaj zelenih plodov na trti, ko je večina že pripravljena za žetev. Čeprav je škoda, da se ti nezreli plodovi poberejo prezgodaj, je za kmeta ceneje in lažje pobrati vse s stroji in kasneje odstraniti nezrele pridelke.

✅ Oglejte si različne vrste sadja ali zelenjave, bodisi na bližnjih kmetijah, v vašem vrtu ali v trgovinah. Ali so vsi enako zreli, ali opazite razlike?

Vzpon avtomatizirane žetve je premaknil sortiranje pridelkov z žetve v tovarne. Hrana je potovala po dolgih tekočih trakovih, kjer so ekipe ljudi pregledovale pridelke in odstranjevale vse, kar ni ustrezalo zahtevanim standardom kakovosti. Žetev je bila cenejša zaradi strojev, vendar je še vedno obstajal strošek ročnega sortiranja hrane.

![Če je zaznan rdeč paradižnik, nadaljuje svojo pot brez prekinitve. Če je zaznan zeleni paradižnik, ga ročica preusmeri v koš za odpadke.](../../../../../translated_images/optical-tomato-sorting.61aa134bdda4e5b1bfb16a212c1e35a6ef0c426cbb8b1c975f79d7bfbf48d068.sl.png)

Naslednja evolucija je bila uporaba strojev za sortiranje, bodisi vgrajenih v kombajne ali v obratih za predelavo. Prva generacija teh strojev je uporabljala optične senzorje za zaznavanje barv, ki so upravljali aktuatorje za preusmerjanje zelenih paradižnikov v koš za odpadke z uporabo ročic ali zračnih sunkov, medtem ko so rdeči paradižniki nadaljevali svojo pot po mreži tekočih trakov.

V tem videu, ko paradižniki padajo z enega tekočega traku na drugega, so zeleni paradižniki zaznani in preusmerjeni v koš z uporabo ročic.

✅ Kakšne pogoje bi potrebovali v tovarni ali na polju, da bi ti optični senzorji pravilno delovali?

Najbolj napredni stroji za sortiranje zdaj izkoriščajo AI in ML, pri čemer uporabljajo modele, usposobljene za razlikovanje dobrih pridelkov od slabih, ne le na podlagi očitnih barvnih razlik, kot so zeleni paradižniki proti rdečim, temveč tudi na podlagi bolj subtilnih razlik v videzu, ki lahko kažejo na bolezni ali poškodbe.

## Razvrščanje slik s pomočjo strojnega učenja

Tradicionalno programiranje vključuje uporabo podatkov in algoritma za pridobitev rezultata. Na primer, v zadnjem projektu ste uporabili GPS koordinate in geografsko ograjo, uporabili algoritem, ki ga je zagotovil Azure Maps, in dobili rezultat, ali je točka znotraj ali zunaj geografske ograje. Vnesete več podatkov, dobite več rezultatov.

![Tradicionalni razvoj uporablja vhodne podatke in algoritem za pridobitev izhoda. Strojno učenje uporablja vhodne in izhodne podatke za usposabljanje modela, ta model pa lahko nato obdeluje nove vhodne podatke za ustvarjanje novih izhodov.](../../../../../translated_images/traditional-vs-ml.5c20c169621fa539.sl.png)

Strojno učenje to obrne – začnete s podatki in znanimi izhodi, algoritem strojnega učenja pa se uči iz podatkov. Nato lahko uporabite ta usposobljeni algoritem, imenovan *model strojnega učenja* ali *model*, in vnesete nove podatke za pridobitev novih rezultatov.

> 🎓 Proces, pri katerem se algoritem strojnega učenja uči iz podatkov, se imenuje *usposabljanje*. Vhodni podatki in znani izhodi se imenujejo *podatki za usposabljanje*.

Na primer, modelu bi lahko dali milijone slik nezrelih banan kot vhodne podatke za usposabljanje, z izhodom za usposabljanje nastavljenim na `nezrelo`, in milijone slik zrelih banan kot podatke za usposabljanje z izhodom nastavljenim na `zrelo`. Algoritem ML bi nato ustvaril model na podlagi teh podatkov. Nato bi temu modelu dali novo sliko banane, in napovedal bi, ali je nova slika zrela ali nezrela banana.

> 🎓 Rezultati ML modelov se imenujejo *napovedi*.

![2 banani, ena zrela z napovedjo 99,7 % zrela, 0,3 % nezrela, in ena nezrela z napovedjo 1,4 % zrela, 98,6 % nezrela.](../../../../../translated_images/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50ece4e4589e724b142da0681f35470fe3db3f7d51240f69c85.sl.png)

ML modeli ne dajejo binarnih odgovorov, temveč verjetnosti. Na primer, modelu bi lahko dali sliko banane, ki bi napovedal `zrela` z 99,7 % in `nezrela` z 0,3 %. Vaša koda bi nato izbrala najboljšo napoved in odločila, da je banana zrela.

Model ML, uporabljen za zaznavanje slik, kot je ta, se imenuje *klasifikator slik* – dobi označene slike in nato razvršča nove slike na podlagi teh oznak.

> 💁 To je poenostavitev, obstajajo pa tudi drugi načini za usposabljanje modelov, ki ne potrebujejo vedno označenih izhodov, kot je nenadzorovano učenje. Če želite izvedeti več o ML, si oglejte [ML za začetnike, 24-lekcijski učni načrt o strojnem učenju](https://aka.ms/ML-beginners).

## Usposabljanje klasifikatorja slik

Za uspešno usposabljanje klasifikatorja slik potrebujete milijone slik. Kot se izkaže, ko imate enkrat klasifikator slik, usposobljen na milijonih ali milijardah različnih slik, ga lahko ponovno uporabite in ponovno usposobite z majhnim naborom slik ter dosežete odlične rezultate, s postopkom, imenovanim *prenosno učenje*.

> 🎓 Prenosno učenje je proces prenosa znanja iz obstoječega ML modela na nov model, ki temelji na novih podatkih.

Ko je klasifikator slik usposobljen za širok spekter slik, so njegove notranje funkcije odlične pri prepoznavanju oblik, barv in vzorcev. Prenosno učenje omogoča modelu, da uporabi to, kar se je že naučil pri prepoznavanju delov slik, za prepoznavanje novih slik.

![Ko enkrat prepoznate oblike, jih lahko razporedite v različne konfiguracije, da ustvarite ladjo ali mačko.](../../../../../translated_images/shapes-to-images.1a309f0ea88dd66f.sl.png)

To si lahko predstavljate kot otroške knjige z oblikami, kjer lahko, ko prepoznate polkrog, pravokotnik in trikotnik, prepoznate jadrnico ali mačko, odvisno od konfiguracije teh oblik. Klasifikator slik lahko prepozna oblike, prenosno učenje pa ga nauči, katera kombinacija predstavlja ladjo ali mačko – ali zrelo banano.

Na voljo je širok spekter orodij, ki vam lahko pri tem pomagajo, vključno s storitvami v oblaku, ki vam omogočajo usposabljanje modela in njegovo uporabo prek spletnih API-jev.

> 💁 Usposabljanje teh modelov zahteva veliko računalniške moči, običajno prek grafičnih procesnih enot (GPU). Ista specializirana strojna oprema, zaradi katere igre na vašem Xboxu izgledajo neverjetno, se lahko uporablja tudi za usposabljanje modelov strojnega učenja. Z uporabo oblaka lahko najamete čas na zmogljivih računalnikih z GPU-ji za usposabljanje teh modelov, kar vam omogoča dostop do potrebne računalniške moči le za čas, ko jo potrebujete.

## Custom Vision

Custom Vision je orodje v oblaku za usposabljanje klasifikatorjev slik. Omogoča vam usposabljanje klasifikatorja z uporabo le majhnega števila slik. Slike lahko naložite prek spletnega portala, spletnega API-ja ali SDK-ja, pri čemer vsaki sliki dodelite *oznako*, ki predstavlja klasifikacijo te slike. Nato usposobite model in ga preizkusite, da vidite, kako dobro deluje. Ko ste zadovoljni z modelom, lahko objavite njegove različice, ki so dostopne prek spletnega API-ja ali SDK-ja.

![Logotip Azure Custom Vision](../../../../../translated_images/custom-vision-logo.d3d4e7c8a87ec9daf825e72e210576c3cbf60312577be7a139e22dd97ab7f1e6.sl.png)

> 💁 Model Custom Vision lahko usposobite že s 5 slikami na klasifikacijo, vendar je več bolje. Boljše rezultate lahko dosežete z vsaj 30 slikami.

Custom Vision je del nabora AI orodij Microsofta, imenovanih Cognitive Services. To so AI orodja, ki jih je mogoče uporabljati bodisi brez usposabljanja bodisi z majhno količino usposabljanja. Vključujejo prepoznavanje in prevajanje govora, razumevanje jezika in analizo slik. Na voljo so z brezplačno stopnjo kot storitve v Azure.

> 💁 Brezplačna stopnja je več kot dovolj za ustvarjanje modela, njegovo usposabljanje in uporabo za razvoj. Več o omejitvah brezplačne stopnje si lahko preberete na [strani z omejitvami in kvotami za Custom Vision na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn).

### Naloga – ustvarite vir za kognitivne storitve

Za uporabo Custom Vision morate najprej ustvariti dva vira za kognitivne storitve v Azure z uporabo Azure CLI, enega za usposabljanje in enega za napovedovanje.

1. Ustvarite skupino virov za ta projekt z imenom `fruit-quality-detector`.

1. Uporabite naslednji ukaz za ustvarjanje brezplačnega vira za usposabljanje Custom Vision:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Zamenjajte `<location>` z lokacijo, ki ste jo uporabili pri ustvarjanju skupine virov.

    To bo ustvarilo vir za usposabljanje Custom Vision v vaši skupini virov. Imenoval se bo `fruit-quality-detector-training` in uporabljal `F0` sku, kar je brezplačna stopnja. Možnost `--yes` pomeni, da se strinjate s pogoji in določili kognitivnih storitev.

> 💁 Uporabite `S0` sku, če že imate brezplačen račun, ki uporablja katero koli od kognitivnih storitev.

1. Uporabite naslednji ukaz za ustvarjanje brezplačnega vira za napovedovanje Custom Vision:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Zamenjajte `<location>` z lokacijo, ki ste jo uporabili pri ustvarjanju skupine virov.

    To bo ustvarilo vir za napovedovanje Custom Vision v vaši skupini virov. Imenoval se bo `fruit-quality-detector-prediction` in uporabljal `F0` sku, kar je brezplačna stopnja. Možnost `--yes` pomeni, da se strinjate s pogoji in določili kognitivnih storitev.

### Naloga – ustvarite projekt klasifikatorja slik

1. Zaženite portal Custom Vision na [CustomVision.ai](https://customvision.ai) in se prijavite z Microsoftovim računom, ki ste ga uporabili za svoj Azure račun.

1. Sledite [oddelku za ustvarjanje novega projekta v hitrem začetku gradnje klasifikatorja na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project), da ustvarite nov projekt Custom Vision. Uporabniški vmesnik se lahko spremeni, zato so ti dokumenti vedno najbolj ažuren vir.

    Poimenujte svoj projekt `fruit-quality-detector`.

    Ko ustvarite svoj projekt, se prepričajte, da uporabljate vir `fruit-quality-detector-training`, ki ste ga ustvarili prej. Uporabite vrsto projekta *Classification*, vrsto klasifikacije *Multiclass* in domeno *Food*.

    ![Nastavitve za projekt Custom Vision z imenom nastavljenim na fruit-quality-detector, brez opisa, virom nastavljenim na fruit-quality-detector-training, vrsto projekta nastavljenim na classification, vrsto klasifikacije nastavljenim na multi class in domeno nastavljenim na food.](../../../../../translated_images/custom-vision-create-project.cf46325b92d8b131089f6647cf5e07b664cb77850e106d66e3c057b6b69756c6.sl.png)

✅ Vzemite si čas za raziskovanje uporabniškega vmesnika Custom Vision za vaš klasifikator slik.

### Naloga – usposobite svoj projekt klasifikatorja slik

Za usposabljanje klasifikatorja slik boste potrebovali več slik sadja, tako dobrega kot slabega, da jih označite kot dobre ali slabe, na primer zrele in prezrele banane.
💁 Ti klasifikatorji lahko razvrščajo slike česarkoli, zato, če nimate sadja različne kakovosti pri roki, lahko uporabite dve različni vrsti sadja ali mačke in pse!
Vsaka slika naj prikazuje samo sadež, bodisi z enotnim ozadjem ali z raznolikimi ozadji. Poskrbite, da v ozadju ne bo ničesar, kar bi nakazovalo na zrelost ali nezrelost sadeža.

> 💁 Pomembno je, da ozadja niso specifična ali da ni predmetov, ki niso povezani z razvrščanjem oznak, saj bi lahko klasifikator razvrščal na podlagi ozadja. Obstajal je klasifikator za kožnega raka, ki je bil treniran na znamenjih, tako normalnih kot rakavih, pri čemer so bila rakava znamenja vedno fotografirana z ravnilom za merjenje velikosti. Izkazalo se je, da je bil klasifikator skoraj 100 % natančen pri prepoznavanju ravnil na slikah, ne pa rakavih znamenj.

Klasifikatorji slik delujejo pri zelo nizki ločljivosti. Na primer, Custom Vision lahko sprejme slike za treniranje in napovedovanje do velikosti 10240x10240, vendar model trenira in izvaja na slikah velikosti 227x227. Večje slike se zmanjšajo na to velikost, zato poskrbite, da predmet, ki ga klasificirate, zavzame velik del slike, sicer bo premajhen na manjši sliki, ki jo uporablja klasifikator.

1. Zberite slike za svoj klasifikator. Za treniranje klasifikatorja boste potrebovali vsaj 5 slik za vsako oznako, vendar več je bolje. Potrebovali boste tudi nekaj dodatnih slik za testiranje klasifikatorja. Te slike naj bodo različne slike istega predmeta. Na primer:

    * Uporabite 2 zrela banan in posnemite nekaj slik vsake iz različnih kotov, pri čemer posnemite vsaj 7 slik (5 za treniranje, 2 za testiranje), vendar idealno več.

        ![Fotografije 2 različnih banan](../../../../../translated_images/banana-training-images.530eb203346d73bc23b8b990fb4609470bf4ff7c942ccc13d4cfffeed9be1ad4.sl.png)

    * Ponovite isti postopek z 2 nezrelimi bananami.

    Imeti bi morali vsaj 10 slik za treniranje, z vsaj 5 zrelimi in 5 nezrelimi, ter 4 slike za testiranje, 2 zreli in 2 nezreli. Vaše slike naj bodo v formatu png ali jpeg, manjše od 6 MB. Če jih na primer ustvarite z iPhonom, so lahko slike visoke ločljivosti HEIC, zato jih bo treba pretvoriti in morda zmanjšati. Več slik je bolje, pri čemer naj bo število zrelih in nezrelih podobno.

    Če nimate tako zrelih kot nezrelih sadežev, lahko uporabite različne sadeže ali katera koli dva predmeta, ki jih imate na voljo. Prav tako lahko najdete nekaj primerov slik v mapi [images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images) z zrelimi in nezrelimi bananami, ki jih lahko uporabite.

1. Sledite [oddelku za nalaganje in označevanje slik v hitrem začetku za izdelavo klasifikatorja na Microsoftovi dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images), da naložite svoje slike za treniranje. Zrele sadeže označite kot `ripe`, nezrele pa kot `unripe`.

    ![Dialogi za nalaganje, ki prikazujejo nalaganje slik zrelih in nezrelih banan](../../../../../translated_images/image-upload-bananas.0751639f3815e0ec42bdbc6254d1e4357a185834d1ae10c9948a0e7d6d336695.sl.png)

1. Sledite [oddelku za treniranje klasifikatorja v hitrem začetku za izdelavo klasifikatorja na Microsoftovi dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier), da trenirate klasifikator slik na svojih naloženih slikah.

    Ponujena vam bo izbira vrste treniranja. Izberite **Quick Training**.

Klasifikator se bo nato treniral. Treniranje bo trajalo nekaj minut.

> 🍌 Če se odločite pojesti svoje sadeže med treniranjem klasifikatorja, poskrbite, da imate najprej dovolj slik za testiranje!

## Testirajte svoj klasifikator slik

Ko je vaš klasifikator treniran, ga lahko testirate tako, da mu podate novo sliko za klasifikacijo.

### Naloga - testirajte svoj klasifikator slik

1. Sledite [dokumentaciji za testiranje modela na Microsoftovi dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model), da testirate svoj klasifikator slik. Uporabite slike za testiranje, ki ste jih ustvarili prej, ne pa slik, ki ste jih uporabili za treniranje.

    ![Nezrela banana napovedana kot nezrela z verjetnostjo 98,9 %, zrela z verjetnostjo 1,1 %](../../../../../translated_images/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64886422438850ea14f0be6ac918c217ea3b255c685abfabe7.sl.png)

1. Preizkusite vse slike za testiranje, ki jih imate na voljo, in opazujte verjetnosti.

## Ponovno trenirajte svoj klasifikator slik

Ko testirate svoj klasifikator, morda ne bo dal pričakovanih rezultatov. Klasifikatorji slik uporabljajo strojno učenje za napovedovanje, kaj je na sliki, na podlagi verjetnosti, da določene značilnosti slike pomenijo, da ustreza določeni oznaki. Ne razume, kaj je na sliki - ne ve, kaj je banana ali kaj naredi banano banano namesto čolna. Svoj klasifikator lahko izboljšate tako, da ga ponovno trenirate s slikami, pri katerih se zmoti.

Vsakič, ko naredite napoved z možnostjo hitrega testiranja, se slika in rezultati shranijo. Te slike lahko uporabite za ponovno treniranje svojega modela.

### Naloga - ponovno trenirajte svoj klasifikator slik

1. Sledite [dokumentaciji za uporabo napovedane slike za treniranje na Microsoftovi dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training), da ponovno trenirate svoj model, pri čemer uporabite pravilno oznako za vsako sliko.

1. Ko je vaš model ponovno treniran, ga testirajte na novih slikah.

---

## 🚀 Izziv

Kaj mislite, da bi se zgodilo, če bi uporabili sliko jagode z modelom, treniranim na bananah, ali sliko napihljive banane, ali osebo v kostumu banane, ali celo rumenega risanega lika, kot je nekdo iz Simpsonov?

Preizkusite in si oglejte napovedi. Slike za preizkus lahko najdete z uporabo [iskanja slik Bing](https://www.bing.com/images/trending).

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## Pregled in samostojno učenje

* Ko ste trenirali svoj klasifikator, ste videli vrednosti za *Precision*, *Recall* in *AP*, ki ocenjujejo model, ki je bil ustvarjen. Preberite, kaj te vrednosti pomenijo, z uporabo [oddelka za ocenjevanje klasifikatorja v hitrem začetku za izdelavo klasifikatorja na Microsoftovi dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier).
* Preberite, kako izboljšati svoj klasifikator z uporabo [dokumentacije o izboljšanju modela Custom Vision na Microsoftovi dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn).

## Naloga

[Trenirajte svoj klasifikator za več vrst sadja in zelenjave](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.