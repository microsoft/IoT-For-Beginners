<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-25T22:33:44+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "pt"
}
-->
# Cancelar o temporizador

## Instruções

Até agora nesta lição, treinaste um modelo para compreender como definir um temporizador. Outra funcionalidade útil é cancelar um temporizador - talvez o teu pão já esteja pronto e possa ser retirado do forno antes que o temporizador termine.

Adiciona uma nova intenção à tua aplicação LUIS para cancelar o temporizador. Não será necessário usar entidades, mas precisarás de algumas frases de exemplo. Trata disso no teu código serverless se for a intenção principal, registando que a intenção foi reconhecida e devolvendo uma resposta apropriada.

## Critérios de Avaliação

| Critério | Exemplar | Adequado | Precisa de Melhorias |
| -------- | --------- | -------- | -------------------- |
| Adicionar a intenção de cancelar o temporizador à aplicação LUIS | Conseguiu adicionar a intenção e treinar o modelo | Conseguiu adicionar a intenção, mas não treinar o modelo | Não conseguiu adicionar a intenção nem treinar o modelo |
| Tratar a intenção na aplicação serverless | Conseguiu detetar a intenção como a principal e registá-la | Conseguiu detetar a intenção como a principal | Não conseguiu detetar a intenção como a principal |

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.