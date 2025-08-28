<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-27T23:39:00+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "tl"
}
-->
# Magpadala ng mga Notipikasyon gamit ang Twilio

## Mga Instruksyon

Sa iyong code sa ngayon, inilalagay mo lamang sa log ang distansya sa geofence. Sa gawaing ito, kailangan mong magdagdag ng notipikasyon, maaaring isang text message o email, kapag ang GPS coordinates ay nasa loob ng geofence.

Ang Azure Functions ay may maraming opsyon para sa bindings, kabilang na ang sa mga third-party na serbisyo tulad ng Twilio, isang platform para sa komunikasyon.

* Mag-sign up para sa libreng account sa [Twilio.com](https://www.twilio.com)
* Basahin ang dokumentasyon tungkol sa pag-bind ng Azure Functions sa Twilio SMS sa [Microsoft docs Twilio binding for Azure Functions page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Basahin ang dokumentasyon tungkol sa pag-bind ng Azure Functions sa Twilio SendGrid para magpadala ng mga email sa [Microsoft docs Azure Functions SendGrid bindings page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Idagdag ang binding sa iyong Functions app upang makatanggap ng notipikasyon kapag ang GPS coordinates ay nasa loob o labas ng geofence - hindi pareho.

## Rubric

| Pamantayan | Natatangi | Katanggap-tanggap | Kailangan ng Pagbuti |
| ---------- | --------- | ----------------- | -------------------- |
| I-configure ang functions bindings at makatanggap ng email o SMS | Na-configure ang functions bindings at nakatanggap ng email o SMS kapag nasa loob o labas ng geofence, ngunit hindi pareho | Na-configure ang bindings ngunit hindi nakapagpadala ng email o SMS, o nakapagpadala lamang kapag ang coordinates ay parehong nasa loob at labas | Hindi na-configure ang bindings at hindi nakapagpadala ng email o SMS |

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.