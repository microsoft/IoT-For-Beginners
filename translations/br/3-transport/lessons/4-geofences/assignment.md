<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-28T03:18:48+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "br"
}
-->
# Enviar notificações usando Twilio

## Instruções

No seu código até agora, você apenas registrou a distância até a geofence. Nesta tarefa, você precisará adicionar uma notificação, seja uma mensagem de texto ou um e-mail, quando as coordenadas de GPS estiverem dentro da geofence.

O Azure Functions oferece muitas opções de bindings, incluindo serviços de terceiros, como o Twilio, uma plataforma de comunicação.

* Cadastre-se para uma conta gratuita em [Twilio.com](https://www.twilio.com)
* Leia a documentação sobre como vincular o Azure Functions ao Twilio SMS na [página de bindings do Twilio para Azure Functions na documentação da Microsoft](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Leia a documentação sobre como vincular o Azure Functions ao Twilio SendGrid para enviar e-mails na [página de bindings do SendGrid para Azure Functions na documentação da Microsoft](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Adicione o binding ao seu aplicativo Functions para ser notificado sobre as coordenadas de GPS dentro ou fora da geofence - mas não ambos.

## Critérios de Avaliação

| Critério | Exemplary (Exemplar) | Adequate (Adequado) | Needs Improvement (Precisa Melhorar) |
| -------- | --------------------- | ------------------- | ------------------------------------- |
| Configurar os bindings das funções e receber um e-mail ou SMS | Foi capaz de configurar os bindings das funções e receber um e-mail ou SMS quando dentro ou fora da geofence, mas não ambos | Foi capaz de configurar os bindings, mas não conseguiu enviar o e-mail ou SMS, ou só conseguiu enviar quando as coordenadas estavam tanto dentro quanto fora | Não foi capaz de configurar os bindings e enviar um e-mail ou SMS |

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.