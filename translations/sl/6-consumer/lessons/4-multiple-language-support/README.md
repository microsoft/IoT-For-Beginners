# Podpora več jezikov

![Sketchnote pregled te lekcije](../../../../../translated_images/sl/lesson-24.4246968ed058510a.webp)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliko za večjo različico.

Ta video ponuja pregled storitev Azure za govor, ki zajema pretvorbo govora v besedilo in besedila v govor iz prejšnjih lekcij, ter prevajanje govora, kar je tema te lekcije:

[![Prepoznavanje govora z nekaj vrsticami kode v Pythonu iz Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Kliknite na zgornjo sliko za ogled videa

## Predhodni kviz

[Predhodni kviz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Uvod

V zadnjih treh lekcijah ste se naučili pretvoriti govor v besedilo, razumeti jezik in pretvoriti besedilo v govor, vse to s pomočjo umetne inteligence. Drugo področje človeške komunikacije, kjer lahko AI pomaga, je prevajanje jezikov – pretvorba iz enega jezika v drugega, na primer iz angleščine v francoščino.

V tej lekciji se boste naučili uporabljati AI za prevajanje besedila, kar omogoča vašemu pametnemu časovniku interakcijo z uporabniki v več jezikih.

V tej lekciji bomo obravnavali:

* [Prevajanje besedila](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Prevajalske storitve](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Ustvarjanje prevajalskega vira](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Podpora več jezikov v aplikacijah s prevodi](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Prevajanje besedila z uporabo AI storitve](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 To je zadnja lekcija v tem projektu, zato po zaključku te lekcije in naloge ne pozabite počistiti svojih oblačnih storitev. Storitve boste potrebovali za dokončanje naloge, zato se prepričajte, da jo najprej dokončate.
>
> Če je potrebno, si oglejte [navodila za čiščenje projekta](../../../clean-up.md).

## Prevajanje besedila

Prevajanje besedila je računalniški problem, ki se raziskuje že več kot 70 let, in šele zdaj, zahvaljujoč napredku v AI in računalniški moči, se približuje rešitvi, ki je skoraj tako dobra kot človeški prevajalci.

> 💁 Izvor lahko zasledimo še dlje nazaj, do [Al-Kindija](https://wikipedia.org/wiki/Al-Kindi), arabskega kriptografa iz 9. stoletja, ki je razvil tehnike za prevajanje jezikov.

### Strojno prevajanje

Prevajanje besedila se je začelo kot tehnologija, znana kot strojno prevajanje (MT), ki lahko prevaja med različnimi jezikovnimi pari. MT deluje tako, da zamenja besede v enem jeziku z drugim, pri čemer uporablja tehnike za izbiro pravilnih načinov prevajanja fraz ali delov stavkov, kadar preprosto prevajanje beseda za besedo nima smisla.

> 🎓 Ko prevajalniki podpirajo prevajanje med enim jezikom in drugim, so to znani kot *jezikovni pari*. Različna orodja podpirajo različne jezikovne pare, ki morda niso popolni. Na primer, prevajalnik lahko podpira angleščino v španščino kot jezikovni par in španščino v italijanščino kot jezikovni par, vendar ne angleščino v italijanščino.

Na primer, prevajanje "Hello world" iz angleščine v francoščino se lahko izvede z zamenjavo – "Bonjour" za "Hello" in "le monde" za "world", kar vodi do pravilnega prevoda "Bonjour le monde".

Zamenjave ne delujejo, kadar različni jeziki uporabljajo različne načine izražanja istega. Na primer, angleški stavek "My name is Jim" se v francoščino prevede kot "Je m'appelle Jim" – dobesedno "Jaz se kličem Jim". "Je" je francosko za "jaz", "moi" je "me", vendar se združi z glagolom, ker se začne z samoglasnikom, zato postane "m'", "appelle" pomeni klicati, in "Jim" se ne prevede, ker je ime in ne beseda, ki bi jo lahko prevedli. Tudi vrstni red besed postane težava – preprosta zamenjava "Je m'appelle Jim" postane "I myself call Jim", z drugačnim vrstnim redom besed kot v angleščini.

> 💁 Nekatere besede se nikoli ne prevajajo – moje ime je Jim ne glede na to, kateri jezik se uporablja za predstavitev. Pri prevajanju v jezike, ki uporabljajo različne abecede ali različne črke za različne zvoke, se besede lahko *transliterirajo*, torej izberejo črke ali znake, ki dajejo ustrezen zvok, da zvenijo enako kot dana beseda.

Idiomi so prav tako težava pri prevajanju. To so fraze, ki imajo razumljen pomen, ki je drugačen od neposredne interpretacije besed. Na primer, v angleščini idiom "I've got ants in my pants" ne pomeni dobesedno, da imate mravlje v oblačilih, ampak da ste nemirni. Če bi to prevedli v nemščino, bi zmedli poslušalca, saj je nemška različica "I have bumble bees in the bottom".

> 💁 Različne lokalne različice dodajajo različne zapletenosti. Pri idiomu "ants in your pants" v ameriški angleščini "pants" pomeni zunanja oblačila, v britanski angleščini pa "pants" pomeni spodnje perilo.

✅ Če govorite več jezikov, pomislite na nekaj fraz, ki se ne prevajajo neposredno.

Sistemi za strojno prevajanje se zanašajo na velike baze podatkov pravil, ki opisujejo, kako prevesti določene fraze in idiome, skupaj s statističnimi metodami za izbiro ustreznih prevodov iz možnih možnosti. Te statistične metode uporabljajo ogromne baze podatkov del, ki so jih ljudje prevedli v več jezikov, za izbiro najbolj verjetnega prevoda, tehniko, imenovano *statistično strojno prevajanje*. Številni od teh uporabljajo vmesne predstavitve jezika, kar omogoča, da se en jezik prevede v vmesni jezik, nato pa iz vmesnega v drug jezik. Na ta način dodajanje več jezikov vključuje prevode v in iz vmesnega jezika, ne pa v in iz vseh drugih jezikov.

### Nevronsko prevajanje

Nevronsko prevajanje vključuje uporabo moči AI za prevajanje, običajno prevajanje celotnih stavkov z enim modelom. Ti modeli so usposobljeni na ogromnih podatkovnih nizih, ki so jih ljudje prevedli, kot so spletne strani, knjige in dokumentacija Združenih narodov.

Nevronski prevajalski modeli so običajno manjši od modelov strojnega prevajanja, saj ne potrebujejo ogromnih baz podatkov fraz in idiomov. Sodobne AI storitve, ki zagotavljajo prevajanje, pogosto mešajo več tehnik, kombinirajo statistično strojno prevajanje in nevronsko prevajanje.

Za noben jezikovni par ne obstaja 1:1 prevod. Različni prevajalski modeli bodo dali nekoliko različne rezultate, odvisno od podatkov, uporabljenih za usposabljanje modela. Prevajanja niso vedno simetrična – če stavek prevedete iz enega jezika v drugega, nato pa nazaj v prvi jezik, lahko dobite nekoliko drugačen stavek kot rezultat.

✅ Preizkusite različne spletne prevajalnike, kot so [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) ali aplikacija Apple Translate. Primerjajte prevedene različice nekaj stavkov. Poskusite tudi prevajanje v enem, nato pa prevajanje nazaj v drugem.

## Prevajalske storitve

Obstaja več AI storitev, ki jih lahko uporabite v svojih aplikacijah za prevajanje govora in besedila.

### Cognitive services Speech service

![Logotip storitve za govor](../../../../../translated_images/sl/azure-speech-logo.a1f08c4befb0159f.webp)

Storitev za govor, ki ste jo uporabljali v prejšnjih lekcijah, ima prevajalske zmogljivosti za prepoznavanje govora. Ko prepoznate govor, lahko zahtevate ne le besedilo govora v istem jeziku, ampak tudi v drugih jezikih.

> 💁 To je na voljo samo prek SDK za govor, REST API nima vgrajenih prevodov.

### Cognitive services Translator service

![Logotip prevajalske storitve](../../../../../translated_images/sl/azure-translator-logo.c6ed3a4a433edfd2.webp)

Prevajalska storitev je namenski prevajalski servis, ki lahko prevede besedilo iz enega jezika v enega ali več ciljnih jezikov. Poleg prevajanja podpira širok nabor dodatnih funkcij, vključno z maskiranjem neprimernih besed. Prav tako vam omogoča, da zagotovite specifičen prevod za določeno besedo ali stavek, da delate s pojmi, ki jih ne želite prevesti, ali imate specifičen, dobro znan prevod.

Na primer, pri prevajanju stavka "I have a Raspberry Pi", ki se nanaša na enoploščni računalnik, v drug jezik, kot je francoščina, bi želeli ohraniti ime "Raspberry Pi" nespremenjeno in ga ne prevesti, kar bi dalo "J’ai un Raspberry Pi" namesto "J’ai une pi aux framboises".

## Ustvarjanje prevajalskega vira

Za to lekcijo boste potrebovali prevajalski vir. Uporabili boste REST API za prevajanje besedila.

### Naloga - ustvarjanje prevajalskega vira

1. V terminalu ali ukazni vrstici zaženite naslednji ukaz za ustvarjanje prevajalskega vira v vaši skupini virov `smart-timer`.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Zamenjajte `<location>` z lokacijo, ki ste jo uporabili pri ustvarjanju skupine virov.

1. Pridobite ključ za prevajalsko storitev:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Kopirajte enega od ključev.

## Podpora več jezikov v aplikacijah s prevodi

V idealnem svetu bi morala vaša celotna aplikacija razumeti čim več različnih jezikov, od poslušanja govora, do razumevanja jezika, do odgovarjanja z govorom. To je veliko dela, zato lahko prevajalske storitve pospešijo čas dostave vaše aplikacije.

![Arhitektura pametnega časovnika, ki prevaja japonščino v angleščino, obdeluje v angleščini in nato prevaja nazaj v japonščino](../../../../../translated_images/sl/translated-smart-timer.08ac20057fdc5c37.webp)

Predstavljajte si, da gradite pametni časovnik, ki uporablja angleščino od začetka do konca, razume govorjeno angleščino in jo pretvori v besedilo, izvaja razumevanje jezika v angleščini, sestavlja odgovore v angleščini in odgovarja z govorom v angleščini. Če bi želeli dodati podporo za japonščino, bi lahko začeli s prevajanjem govorjene japonščine v angleško besedilo, nato pa ohranili jedro aplikacije enako, nato pa prevedli besedilo odgovora v japonščino, preden bi odgovorili z govorom. To bi vam omogočilo hitro dodajanje podpore za japonščino, kasneje pa lahko razširite na popolno podporo za japonščino od začetka do konca.

> 💁 Slabost zanašanja na strojno prevajanje je, da imajo različni jeziki in kulture različne načine izražanja istih stvari, zato prevod morda ne bo ustrezal izrazu, ki ga pričakujete.

Strojno prevajanje odpira tudi možnosti za aplikacije in naprave, ki lahko prevajajo vsebino, ki jo ustvarijo uporabniki, medtem ko je ustvarjena. Znanstvena fantastika pogosto prikazuje 'univerzalne prevajalnike', naprave, ki lahko prevajajo iz tujih jezikov v (običajno) ameriško angleščino. Te naprave so manj znanstvena fantastika, bolj znanstveno dejstvo, če ignoriramo del o tujcih. Obstajajo že aplikacije in naprave, ki omogočajo sprotno prevajanje govora in napisanega besedila, z uporabo kombinacij storitev za govor in prevajanje.

Eden od primerov je mobilna aplikacija [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn), prikazana v tem videu:

[![Microsoft Translator funkcija v živo v akciji](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Kliknite na zgornjo sliko za ogled videa

Predstavljajte si, da imate takšno napravo na voljo, še posebej med potovanjem ali interakcijo z ljudmi, katerih jezika ne poznate. Samodejne prevajalske naprave na letališčih ali v bolnišnicah bi zagotovile zelo potrebne izboljšave dostopnosti.

✅ Raziskujte: Ali obstajajo kakšne komercialno dostopne IoT naprave za prevajanje? Kaj pa prevajalske zmogljivosti, vgrajene v pametne naprave?

> 👽 Čeprav ni pravih univerzalnih prevajalnikov, ki bi nam omogočili pogovor z nezemljani, [Microsoft Translator podpira klingonščino](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Prevajanje besedila z uporabo AI storitve

S pomočjo AI storitve lahko dodate to prevajalsko zmogljivost svojemu pametnemu časovniku.

### Naloga - prevajanje besedila z uporabo AI storitve

Sledite ustreznemu vodiču za prevajanje besedila na vaši IoT napravi:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Enoploščni računalnik - Raspberry Pi](pi-translate-speech.md)
* [Enoploščni računalnik - Virtualna naprava](virtual-device-translate-speech.md)

---

## 🚀 Izziv

Kako lahko strojno prevajanje koristi drugim IoT aplikacijam poleg pametnih naprav? Razmislite o različnih načinih, kako lahko prevajanje pomaga, ne le pri govorjenih besedah, ampak tudi pri besedilu.

## Zaključni kviz

[Zaključni kviz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Pregled in samostojno učenje

* Preberite več o strojnem prevajanju na [strani o strojnem prevajanju na Wikipediji](https://wikipedia.org/wiki/Machine_translation)
* Preberite več o nevronskem strojnem prevajanju na [strani o nevronskem strojnem prevajanju na Wikipediji](https://wikipedia.org/wiki/Neural_machine_translation)
* Oglejte si seznam podprtih jezikov za Microsoftove storitve za govor v [dokumentaciji o podpori za jezike in glasove za storitev za govor na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Naloga

[Zgradite univerzalni prevajalnik](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.