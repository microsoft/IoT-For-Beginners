<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-25T21:26:23+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "pt"
}
-->
# Construir um ciclo de rega mais eficiente

## Instruções

Esta lição abordou como controlar um relé através de dados de sensores, e esse relé, por sua vez, pode controlar uma bomba para um sistema de irrigação. Para um volume definido de solo, operar uma bomba por um período fixo de tempo deve sempre ter o mesmo impacto na humidade do solo. Isto significa que pode ter uma ideia de quantos segundos de irrigação correspondem a uma determinada redução na leitura da humidade do solo. Usando estes dados, pode construir um sistema de irrigação mais controlado.

Para esta tarefa, irá calcular quanto tempo a bomba deve funcionar para alcançar um aumento específico na humidade do solo.

> ⚠️ Se estiver a usar hardware IoT virtual, pode seguir este processo, mas simular os resultados aumentando manualmente a leitura da humidade do solo por uma quantidade fixa por segundo enquanto o relé está ligado.

1. Comece com o solo seco. Meça a humidade do solo.

1. Adicione uma quantidade fixa de água, seja operando a bomba durante 1 segundo ou despejando uma quantidade fixa de água.

    > A bomba deve funcionar sempre a uma taxa constante, de modo que, a cada segundo de funcionamento, forneça a mesma quantidade de água.

1. Aguarde até que o nível de humidade do solo estabilize e faça uma leitura.

1. Repita este processo várias vezes e crie uma tabela com os resultados. Um exemplo desta tabela é apresentado abaixo.

    | Tempo total da bomba | Humidade do solo | Redução |
    | --- | --: | -: |
    | Seco | 643 |  0 |
    | 1s   | 621 | 22 |
    | 2s   | 601 | 20 |
    | 3s   | 579 | 22 |
    | 4s   | 560 | 19 |
    | 5s   | 539 | 21 |
    | 6s   | 521 | 18 |

1. Calcule um aumento médio na humidade do solo por segundo de água. No exemplo acima, cada segundo de água reduz a leitura em uma média de 20,3.

1. Use estes dados para melhorar a eficiência do código do servidor, fazendo a bomba funcionar pelo tempo necessário para atingir o nível de humidade desejado.

## Rubrica

| Critério | Exemplar | Adequado | Necessita de Melhorias |
| -------- | --------- | -------- | ---------------------- |
| Captura de dados de humidade do solo | Consegue capturar várias leituras após adicionar quantidades fixas de água | Consegue capturar algumas leituras com quantidades fixas de água | Só consegue capturar uma ou duas leituras, ou não consegue usar quantidades fixas de água |
| Calibração do código do servidor | Consegue calcular uma redução média na leitura da humidade do solo e atualizar o código do servidor para usar este valor | Consegue calcular uma redução média, mas não consegue atualizar o código do servidor, ou não consegue calcular corretamente uma média, mas usa este valor para atualizar corretamente o código do servidor | Não consegue calcular uma média ou atualizar o código do servidor |

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos pela precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original na sua língua nativa deve ser considerado a fonte autoritária. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações incorretas decorrentes do uso desta tradução.