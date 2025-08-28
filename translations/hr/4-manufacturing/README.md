<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-28T12:03:33+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "hr"
}
-->
# Proizvodnja i obrada - korištenje IoT-a za poboljšanje obrade hrane

Kada hrana stigne u centralni centar ili pogon za obradu, ne šalje se uvijek odmah u supermarkete. Često hrana prolazi kroz niz koraka obrade, poput sortiranja prema kvaliteti. Ovo je nekada bio ručni proces - započinjao bi na polju kada bi berači brali samo zrelo voće, a zatim bi u tvornici voće prolazilo pokretnu traku, gdje bi zaposlenici ručno uklanjali oštećeno ili trulo voće. Budući da sam i sam ljeti tijekom školovanja brao i sortirao jagode, mogu potvrditi da to nije zabavan posao.

Moderniji sustavi oslanjaju se na IoT za sortiranje. Neki od najranijih uređaja, poput sortera tvrtke [Weco](https://wecotek.com), koriste optičke senzore za otkrivanje kvalitete proizvoda, odbacujući, na primjer, zelene rajčice. Ovi uređaji mogu se koristiti na kombajnima na samoj farmi ili u pogonima za obradu.

Kako napreduju tehnologije umjetne inteligencije (AI) i strojnog učenja (ML), ovi strojevi postaju sve napredniji, koristeći ML modele obučene za razlikovanje između voća i stranih objekata poput kamenja, prljavštine ili insekata. Ovi modeli također se mogu obučiti za otkrivanje kvalitete voća, ne samo oštećenog voća, već i za rano otkrivanje bolesti ili drugih problema s usjevima.

> 🎓 Pojam *ML model* odnosi se na rezultat obuke softvera za strojno učenje na skupu podataka. Na primjer, možete obučiti ML model da razlikuje zrele od nezrelih rajčica, a zatim koristiti model na novim slikama kako biste utvrdili jesu li rajčice zrele ili ne.

U ovih 4 lekcije naučit ćete kako obučiti AI modele temeljene na slikama za otkrivanje kvalitete voća, kako ih koristiti na IoT uređaju i kako ih pokrenuti na rubu - to jest na IoT uređaju umjesto u oblaku.

> 💁 Ove lekcije koristit će neke resurse u oblaku. Ako ne završite sve lekcije u ovom projektu, obavezno [očistite svoj projekt](../clean-up.md).

## Teme

1. [Obučite detektor kvalitete voća](./lessons/1-train-fruit-detector/README.md)
1. [Provjerite kvalitetu voća s IoT uređaja](./lessons/2-check-fruit-from-device/README.md)
1. [Pokrenite svoj detektor voća na rubu](./lessons/3-run-fruit-detector-edge/README.md)
1. [Pokrenite detekciju kvalitete voća pomoću senzora](./lessons/4-trigger-fruit-detector/README.md)

## Zasluge

Sve lekcije napisane su s ♥️ od strane [Jen Fox](https://github.com/jenfoxbot) i [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati mjerodavnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije proizašle iz korištenja ovog prijevoda.