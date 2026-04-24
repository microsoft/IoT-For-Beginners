## Predvidite rast biljaka pomoću IoT-a

![Sketchnote pregled ove lekcije](../../../../../translated_images/hr/lesson-5.42b234299279d263.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Uvod

Biljkama su potrebne određene stvari za rast - voda, ugljikov dioksid, hranjive tvari, svjetlost i toplina. U ovoj lekciji naučit ćete kako izračunati stope rasta i zrelosti biljaka mjerenjem temperature zraka.

U ovoj lekciji obradit ćemo:

* [Digitalna poljoprivreda](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Zašto je temperatura važna u poljoprivredi?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Mjerenje temperature okoline](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Dani rasta (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Izračunajte GDD koristeći podatke senzora temperature](../../../../../2-farm/lessons/1-predict-plant-growth)

## Digitalna poljoprivreda

Digitalna poljoprivreda mijenja način na koji obrađujemo zemlju, koristeći alate za prikupljanje, pohranu i analizu podataka iz poljoprivrede. Trenutno se nalazimo u razdoblju koje Svjetski ekonomski forum opisuje kao 'Četvrtu industrijsku revoluciju', a uspon digitalne poljoprivrede nazvan je 'Četvrtom poljoprivrednom revolucijom' ili 'Poljoprivreda 4.0'.

> 🎓 Pojam Digitalna poljoprivreda također uključuje cijeli 'lanac vrijednosti poljoprivrede', odnosno cijeli put od farme do stola. To uključuje praćenje kvalitete proizvoda dok se hrana transportira i obrađuje, sustave skladištenja i e-trgovine, pa čak i aplikacije za iznajmljivanje traktora!

Ove promjene omogućuju poljoprivrednicima povećanje prinosa, korištenje manje gnojiva i pesticida te učinkovitije korištenje vode. Iako se prvenstveno koristi u bogatijim zemljama, senzori i drugi uređaji postupno postaju jeftiniji, čineći ih dostupnijima u zemljama u razvoju.

Neke tehnike omogućene digitalnom poljoprivredom su:

* Mjerenje temperature - mjerenje temperature omogućuje poljoprivrednicima predviđanje rasta i zrelosti biljaka.
* Automatizirano zalijevanje - mjerenje vlažnosti tla i uključivanje sustava za navodnjavanje kada je tlo previše suho, umjesto zalijevanja u određeno vrijeme. Zalijevanje u određeno vrijeme može dovesti do nedovoljnog zalijevanja tijekom vrućih, suhih razdoblja ili prekomjernog zalijevanja tijekom kiše. Zalijevanjem samo kada je tlu potrebno, poljoprivrednici mogu optimizirati korištenje vode.
* Suzbijanje štetočina - poljoprivrednici mogu koristiti kamere na automatiziranim robotima ili dronovima za provjeru štetočina, a zatim primijeniti pesticide samo tamo gdje je potrebno, smanjujući količinu korištenih pesticida i smanjujući otjecanje pesticida u lokalne izvore vode.

✅ Istražite. Koje se druge tehnike koriste za poboljšanje poljoprivrednih prinosa?

> 🎓 Pojam 'Precizna poljoprivreda' koristi se za definiranje promatranja, mjerenja i reagiranja na usjeve na razini polja ili čak dijelova polja. To uključuje mjerenje razine vode, hranjivih tvari i štetočina te precizno reagiranje, poput zalijevanja samo malog dijela polja.

## Zašto je temperatura važna u poljoprivredi?

Kada učimo o biljkama, većina nas uči o važnosti vode, svjetlosti, ugljikovog dioksida i hranjivih tvari. Biljkama je također potrebna toplina za rast - zato biljke cvjetaju u proljeće kada temperatura raste, zašto visibabe ili narcisi mogu niknuti rano zbog kratkog toplog razdoblja i zašto su staklenici i plastenici tako dobri za uzgoj biljaka.

> 🎓 Plastenici i staklenici obavljaju sličan posao, ali s važnom razlikom. Plastenici se umjetno zagrijavaju i omogućuju poljoprivrednicima preciznije kontroliranje temperature, dok staklenici ovise o suncu za toplinu, a obično jedina kontrola su prozori ili drugi otvori za ispuštanje topline.

Biljke imaju osnovnu ili minimalnu temperaturu, optimalnu temperaturu i maksimalnu temperaturu, sve temeljene na prosječnim dnevnim temperaturama.

* Osnovna temperatura - ovo je minimalna prosječna dnevna temperatura potrebna za rast biljke.
* Optimalna temperatura - ovo je najbolja prosječna dnevna temperatura za postizanje najvećeg rasta.
* Maksimalna temperatura - ovo je maksimalna temperatura koju biljka može podnijeti. Iznad ove temperature biljka će zaustaviti rast kako bi sačuvala vodu i preživjela.

> 💁 Ovo su prosječne temperature, izračunate na temelju dnevnih i noćnih temperatura. Biljkama su također potrebne različite temperature danju i noću kako bi fotosinteza bila učinkovitija i kako bi štedjele energiju noću.

Svaka vrsta biljke ima različite vrijednosti za osnovnu, optimalnu i maksimalnu temperaturu. Zato neke biljke uspijevaju u toplim zemljama, a druge u hladnijim.

✅ Istražite. Za bilo koje biljke koje imate u svom vrtu, školi ili lokalnom parku, pokušajte pronaći osnovnu temperaturu.

![Grafikon koji prikazuje stopu rasta koja raste s porastom temperature, a zatim opada kada temperatura postane previsoka](../../../../../translated_images/hr/plant-growth-temp-graph.c6d69c9478e6ca83.webp)

Gornji grafikon prikazuje primjer stope rasta u odnosu na temperaturu. Do osnovne temperature nema rasta. Stopa rasta povećava se do optimalne temperature, a zatim opada nakon što dosegne vrhunac. 

Oblik ovog grafikona varira od vrste biljke do vrste biljke. Neke imaju oštriji pad iznad optimalne temperature, dok druge imaju sporiji porast od osnovne do optimalne temperature.

> 💁 Da bi poljoprivrednik postigao najbolji rast, mora znati tri temperaturne vrijednosti i razumjeti oblik grafikona za biljke koje uzgaja.

Ako poljoprivrednik može kontrolirati temperaturu, na primjer u komercijalnom plasteniku, tada može optimizirati uvjete za svoje biljke. Komercijalni plastenik koji uzgaja rajčice, na primjer, postavit će temperaturu na oko 25°C tijekom dana i 20°C noću kako bi postigao najbrži rast.

> 🍅 Kombiniranjem ovih temperatura s umjetnim svjetlom, gnojivima i kontroliranim razinama CO
Ovaj kod otvara CSV datoteku, a zatim dodaje novi redak na kraju. Redak sadrži trenutni datum i vrijeme formatirano u čitljiv oblik, nakon čega slijedi temperatura primljena od IoT uređaja. Podaci se pohranjuju u [ISO 8601 formatu](https://wikipedia.org/wiki/ISO_8601) s vremenskom zonom, ali bez mikrosekundi.

1. Pokrenite ovaj kod na isti način kao i prije, pazeći da vaš IoT uređaj šalje podatke. CSV datoteka pod nazivom `temperature.csv` bit će stvorena u istom direktoriju. Ako je otvorite, vidjet ćete datume/vremena i mjerenja temperature:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Pokrenite ovaj kod neko vrijeme kako biste prikupili podatke. Idealno bi bilo da ga pokrenete cijeli dan kako biste prikupili dovoljno podataka za izračun GDD-a.

    
> 💁 Ako koristite virtualni IoT uređaj, označite opciju za nasumične vrijednosti i postavite raspon kako biste izbjegli dobivanje iste temperature svaki put kada se vrati vrijednost temperature.
    ![Označite opciju za nasumične vrijednosti i postavite raspon](../../../../../translated_images/hr/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.webp) 

    > 💁 Ako želite pokrenuti ovo cijeli dan, trebate osigurati da računalo na kojem se izvršava vaš serverski kod neće prijeći u stanje mirovanja, bilo promjenom postavki napajanja ili pokretanjem nečega poput [ovog Python skripta za održavanje sustava aktivnim](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Ovaj kod možete pronaći u direktoriju [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Zadatak - izračunajte GDD koristeći pohranjene podatke

Kada server prikupi podatke o temperaturi, GDD za biljku može se izračunati.

Koraci za ručni izračun su:

1. Pronađite osnovnu temperaturu za biljku. Na primjer, za jagode osnovna temperatura je 10°C.

1. Iz datoteke `temperature.csv` pronađite najvišu i najnižu temperaturu za dan.

1. Koristite ranije navedenu formulu za izračun GDD-a.

Na primjer, ako je najviša temperatura za dan 25°C, a najniža 12°C:

![GDD = 25 + 12 podijeljeno s 2, zatim oduzmite 10 iz rezultata, što daje 8.5](../../../../../translated_images/hr/gdd-calculation-strawberries.59f57db94b22adb8.webp)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Dakle, jagode su primile **8.5** GDD. Jagodama je potrebno oko 250 GDD da bi donijele plod, tako da još ima vremena.

---

## 🚀 Izazov

Biljkama je potrebno više od topline za rast. Što im još treba?

Za ove potrebe, istražite postoje li senzori koji ih mogu mjeriti. Što je s aktuatorima za kontrolu tih razina? Kako biste sastavili jedan ili više IoT uređaja za optimizaciju rasta biljaka?

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Pregled i samostalno učenje

* Pročitajte više o digitalnoj poljoprivredi na [Wikipedijinoj stranici o digitalnoj poljoprivredi](https://wikipedia.org/wiki/Digital_agriculture). Također pročitajte više o preciznoj poljoprivredi na [Wikipedijinoj stranici o preciznoj poljoprivredi](https://wikipedia.org/wiki/Precision_agriculture).
* Potpuni izračun stupnjeva rasta (GDD) je složeniji od pojednostavljenog prikazanog ovdje. Pročitajte više o složenijoj formuli i kako se nositi s temperaturama ispod osnovne na [Wikipedijinoj stranici o stupnjevima rasta](https://wikipedia.org/wiki/Growing_degree-day).
* Hrana bi mogla postati oskudna u budućnosti ako nastavimo koristiti iste metode poljoprivrede. Saznajte više o visokotehnološkim tehnikama uzgoja u ovom [YouTube videu o visokotehnološkim farmama budućnosti](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Zadatak

[Vizualizirajte GDD podatke koristeći Jupyter Notebook](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.