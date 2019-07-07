# Geometria
Material utilizado:
- Handbook of geometry for competitive programmers
## Orientações
- Evitar usar floating points (junto a isso: divisão, raiz quadrada, funções trigonométricas)
- Fazer a menor quantidade de comparações possível
- Atentar aos limites da imagem das operações usadas (ex: cosseno in [-1;1])
- Evitar criar muitos casos, quando muitos casos implicam em mais código e então mais erro
- Atentar ao erro quando comparar floating points (prática) com números reais
- Diminuir a magnitude dos floatings trabalhados, alterando conseq. o erro
- Usar a estrutura `stableSum` para somatório de floatings não negativos
- \* Eliminar pontos muito próximos
- \* Adicionar ruído a alguns pontos para evitar colinearidade/planaridade

## Erro, *cutoff* e *chance*
Esses três conceitos estão atrelados à tomada de decisões
- Erro: maior imprecisão possível quando for tomar a decisão
- *chance*: o menor valor (fronteira) antes da mudança de decisão
- *cutoff*: valor usado para permitir intervalo de possíveis valores numa tomada de decisão

Erro e *chance* podem ser calculados. Queremos que `erro < cutoff < chance`. É bom escolher um valor igualmente espaçado aos limites.

### Erro relativo e absoluto
Erros podem ser indicados de forma relativa ou absoluta:
- Relativo: proporcional á magnitude do número
- Absoluto: valor do erro

#### *Catastrophic cancelletion*
Fenômeno que permite um número de pequena magintude ter um erro (muito) maior que o erro esperado (relativo). Tome que o erro relativo é de 10^(-6). Logo, para 10^6, o erro esperado é de 10^0. Tome agora que dois números com essa magnitude serão cancelados, gerando um número de magnitude 10^0. O erro anterior era de 10^0. Agora temos um número 10^0 com erro 10^0 (10^0 >>> 10^(-6)).

### Considerações sobre pontos flutuantes
- Valores decimais no codigo ou como entrada são representados pela representação mais próxima
- As 5 operações básicas (+, -, x, /, sqrt()) são realizadas como se a precisão fosse infinita (sobre a entrada) e então o resultado é arredondado para a representação mais próxima
- *machine epsilon* (%e): 1.2\*10^(-16) para double e 5.5\*10^(-20) para long double. É o erro relativo.

### Estimativa de erros de precisão 
Erros de precisão podem ser estimados em dois cenários:
- Entrada da operação é exata
- Entrada da operação é imprecisa

#### Entrada exata
Aqui eu entendi que fica legal kkk

#### Entrada imprecisa
##### +, -

##### *
##### /, sqrt()
Para essas operações, não há garantias
