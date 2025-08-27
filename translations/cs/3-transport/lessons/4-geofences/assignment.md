<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-27T21:48:50+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "cs"
}
-->
# Odesílání notifikací pomocí Twilio

## Pokyny

Ve svém kódu jste dosud pouze zaznamenávali vzdálenost k geofenci. V tomto úkolu budete muset přidat notifikaci, buď textovou zprávu, nebo e-mail, když jsou GPS souřadnice uvnitř geofencingu.

Azure Functions nabízí mnoho možností pro bindingy, včetně propojení s externími službami, jako je Twilio, komunikační platforma.

* Zaregistrujte si bezplatný účet na [Twilio.com](https://www.twilio.com)
* Přečtěte si dokumentaci o propojení Azure Functions s Twilio SMS na stránce [Microsoft docs Twilio binding for Azure Functions page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Přečtěte si dokumentaci o propojení Azure Functions s Twilio SendGrid pro odesílání e-mailů na stránce [Microsoft docs Azure Functions SendGrid bindings page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Přidejte binding do své Functions aplikace, abyste byli upozorněni na GPS souřadnice buď uvnitř, nebo vně geofencingu – ne obojí.

## Hodnocení

| Kritéria | Vynikající | Přiměřené | Potřebuje zlepšení |
| -------- | ---------- | --------- | ------------------ |
| Nastavení bindingů funkcí a přijetí e-mailu nebo SMS | Podařilo se nastavit bindingy funkcí a přijmout e-mail nebo SMS, když byly souřadnice uvnitř nebo vně geofencingu, ale ne obojí | Podařilo se nastavit bindingy, ale nepodařilo se odeslat e-mail nebo SMS, nebo bylo možné odeslat pouze při souřadnicích uvnitř i vně | Nepodařilo se nastavit bindingy a odeslat e-mail nebo SMS |

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.