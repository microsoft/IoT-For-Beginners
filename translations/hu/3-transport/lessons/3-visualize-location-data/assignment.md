<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ccdc1faa676a485c4c6ecbddb9f9067",
  "translation_date": "2025-08-27T21:52:35+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/assignment.md",
  "language_code": "hu"
}
-->
# Alkalmazás telepítése

## Útmutató

Számos módja van annak, hogy telepítse az alkalmazását, és megossza a világgal, például a GitHub Pages használatával vagy a számos szolgáltató egyikével. Egy igazán kiváló módszer erre az Azure Static Web Apps használata. Ebben a feladatban építse fel webalkalmazását, és telepítse a felhőbe az [ezekben az útmutatókban](https://github.com/Azure/static-web-apps-cli) leírtak vagy [ezekben a videókban](https://www.youtube.com/watch?v=ADVGIXciYn8&list=PLlrxD0HtieHgMPeBaDQFx9yNuFxx6S1VG&index=3) bemutatottak alapján.  
Az Azure Static Web Apps használatának egyik előnye, hogy elrejtheti az API kulcsokat a portálon, így használja ki ezt a lehetőséget, és refaktorálja a subscriptionKey-t változóként, majd tárolja a felhőben.

## Értékelési szempontok

| Kritérium | Kiemelkedő                                                                                                                             | Megfelelő                                                                                                          | Fejlesztésre szoruló                                 |
| --------- | --------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------- | --------------------------------------------------- |
|           | Egy működő webalkalmazás van bemutatva egy dokumentált GitHub-tárhelyen, ahol a subscriptionKey a felhőben van tárolva és változóként van meghívva | Egy működő webalkalmazás van bemutatva egy dokumentált GitHub-tárhelyen, de a subscriptionKey nincs a felhőben tárolva | A webalkalmazás hibákat tartalmaz vagy nem működik megfelelően |

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.