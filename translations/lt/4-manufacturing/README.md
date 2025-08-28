<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-28T18:58:11+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "lt"
}
-->
# Gamyba ir perdirbimas - IoT naudojimas maisto perdirbimo gerinimui

Kai maistas pasiekia centrinį centrą ar perdirbimo gamyklą, jis ne visada tiesiogiai išsiunčiamas į prekybos centrus. Dažnai maistas pereina kelis perdirbimo etapus, pavyzdžiui, rūšiavimą pagal kokybę. Tai buvo procesas, kuris anksčiau buvo atliekamas rankiniu būdu - jis prasidėdavo laukuose, kai rinkėjai rinkdavo tik prinokusius vaisius, o vėliau gamykloje vaisiai keliaudavo konvejerio juosta, o darbuotojai rankiniu būdu pašalindavo sužalotus ar supuvusius vaisius. Pats vasaros metu mokykloje dirbau braškių rinkimo ir rūšiavimo darbus, todėl galiu patvirtinti, kad tai nėra malonus darbas.

Šiuolaikinės sistemos remiasi IoT technologijomis rūšiavimui. Vieni iš ankstyviausių įrenginių, kaip rūšiuotojai iš [Weco](https://wecotek.com), naudoja optinius jutiklius, kad nustatytų produktų kokybę, pavyzdžiui, atmesdami žalius pomidorus. Šie įrenginiai gali būti naudojami tiek ūkyje, tiek perdirbimo gamyklose.

Tobulėjant dirbtinio intelekto (AI) ir mašininio mokymosi (ML) technologijoms, šie įrenginiai gali tapti dar pažangesni, naudodami ML modelius, apmokytus atskirti vaisius nuo pašalinių objektų, tokių kaip akmenys, purvas ar vabzdžiai. Šie modeliai taip pat gali būti apmokyti nustatyti vaisių kokybę, ne tik sužalotus vaisius, bet ir ankstyvą ligų ar kitų pasėlių problemų aptikimą.

> 🎓 Terminas *ML modelis* reiškia mašininio mokymosi programinės įrangos apmokymo rezultatą naudojant duomenų rinkinį. Pavyzdžiui, galite apmokyti ML modelį atskirti prinokusius ir neprinokusius pomidorus, o tada naudoti modelį naujoms nuotraukoms analizuoti, kad nustatytumėte, ar pomidorai prinokę.

Šiose 4 pamokose išmoksite, kaip apmokyti vaizdais pagrįstus AI modelius vaisių kokybei nustatyti, kaip juos naudoti iš IoT įrenginio ir kaip juos paleisti ties kraštu - tai yra IoT įrenginyje, o ne debesyje.

> 💁 Šiose pamokose bus naudojami kai kurie debesų ištekliai. Jei nebaigsite visų pamokų šiame projekte, būtinai [išvalykite savo projektą](../clean-up.md).

## Temos

1. [Apmokykite vaisių kokybės detektorių](./lessons/1-train-fruit-detector/README.md)
1. [Patikrinkite vaisių kokybę iš IoT įrenginio](./lessons/2-check-fruit-from-device/README.md)
1. [Paleiskite savo vaisių detektorių ties kraštu](./lessons/3-run-fruit-detector-edge/README.md)
1. [Aktyvuokite vaisių kokybės nustatymą iš jutiklio](./lessons/4-trigger-fruit-detector/README.md)

## Kreditas

Visos pamokos buvo parašytos su ♥️ [Jen Fox](https://github.com/jenfoxbot) ir [Jim Bennett](https://GitHub.com/JimBobBennett).

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.