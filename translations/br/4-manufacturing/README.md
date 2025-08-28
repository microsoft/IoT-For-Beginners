<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-28T02:36:01+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "br"
}
-->
# Fabricação e processamento - usando IoT para melhorar o processamento de alimentos

Quando os alimentos chegam a um centro de distribuição ou planta de processamento, nem sempre são apenas enviados diretamente para os supermercados. Muitas vezes, os alimentos passam por várias etapas de processamento, como a classificação por qualidade. Esse é um processo que costumava ser manual - começava no campo, quando os colhedores escolhiam apenas os frutos maduros, e depois, na fábrica, os frutos passavam por uma esteira transportadora, onde os funcionários removiam manualmente os frutos machucados ou podres. Tendo colhido e classificado morangos como um trabalho de verão durante a escola, posso afirmar que esse não é um trabalho divertido.

Configurações mais modernas dependem de IoT para a classificação. Alguns dos primeiros dispositivos, como os classificadores da [Weco](https://wecotek.com), usam sensores ópticos para detectar a qualidade dos produtos, rejeitando, por exemplo, tomates verdes. Esses dispositivos podem ser implantados em colheitadeiras na própria fazenda ou em plantas de processamento.

Com os avanços na Inteligência Artificial (IA) e no Aprendizado de Máquina (ML), essas máquinas podem se tornar mais sofisticadas, utilizando modelos de ML treinados para distinguir entre frutas e objetos estranhos, como pedras, sujeira ou insetos. Esses modelos também podem ser treinados para detectar a qualidade das frutas, não apenas frutos machucados, mas também a detecção precoce de doenças ou outros problemas nas plantações.

> 🎓 O termo *modelo de ML* refere-se ao resultado do treinamento de um software de aprendizado de máquina em um conjunto de dados. Por exemplo, você pode treinar um modelo de ML para distinguir entre tomates maduros e verdes e, em seguida, usar o modelo em novas imagens para verificar se os tomates estão maduros ou não.

Nestes 4 módulos, você aprenderá como treinar modelos de IA baseados em imagens para detectar a qualidade das frutas, como utilizá-los em um dispositivo IoT e como executá-los na borda - ou seja, em um dispositivo IoT em vez de na nuvem.

> 💁 Estes módulos utilizarão alguns recursos na nuvem. Se você não concluir todas as lições deste projeto, certifique-se de [limpar seu projeto](../clean-up.md).

## Tópicos

1. [Treinar um detector de qualidade de frutas](./lessons/1-train-fruit-detector/README.md)
1. [Verificar a qualidade das frutas a partir de um dispositivo IoT](./lessons/2-check-fruit-from-device/README.md)
1. [Executar seu detector de frutas na borda](./lessons/3-run-fruit-detector-edge/README.md)
1. [Acionar a detecção de qualidade de frutas a partir de um sensor](./lessons/4-trigger-fruit-detector/README.md)

## Créditos

Todas as lições foram escritas com ♥️ por [Jen Fox](https://github.com/jenfoxbot) e [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automatizadas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte autoritativa. Para informações críticas, recomenda-se a tradução profissional realizada por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.