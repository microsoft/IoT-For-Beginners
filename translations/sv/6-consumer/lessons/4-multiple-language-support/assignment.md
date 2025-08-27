<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-27T21:17:43+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "sv"
}
-->
# Bygg en universell översättare

## Instruktioner

En universell översättare är en enhet som kan översätta mellan flera språk, vilket gör det möjligt för personer som talar olika språk att kommunicera. Använd det du har lärt dig under de senaste lektionerna för att bygga en universell översättare med hjälp av två IoT-enheter.

> Om du inte har två enheter, följ stegen i de föregående lektionerna för att konfigurera en virtuell IoT-enhet som en av IoT-enheterna.

Du bör konfigurera en enhet för ett språk och en annan för ett annat. Varje enhet ska kunna ta emot tal, konvertera det till text, skicka det till den andra enheten via IoT Hub och en Functions-app, översätta det och spela upp det översatta talet.

> 💁 Tips: När du skickar tal från en enhet till en annan, skicka även med vilket språk det är på, vilket gör det enklare att översätta. Du kan till och med låta varje enhet registrera sig via IoT Hub och en Functions-app först, och skicka vilket språk de stödjer för att lagras i Azure Storage. Du kan sedan använda en Functions-app för att göra översättningarna och skicka den översatta texten till IoT-enheten.

## Bedömningskriterier

| Kriterier | Exemplariskt | Tillräckligt | Behöver förbättras |
| --------- | ------------ | ------------ | ------------------ |
| Skapa en universell översättare | Lyckades bygga en universell översättare som konverterar tal detekterat av en enhet till tal som spelas upp av en annan enhet på ett annat språk | Lyckades få vissa komponenter att fungera, såsom att fånga tal eller översätta, men kunde inte bygga en komplett lösning | Kunde inte bygga några delar av en fungerande universell översättare |

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.