# Geometria
## Orientações
- Evitar usar floating points (junto a isso: divisão, raiz quadrada, funções trigonométricas)
- Fazer a menor quantidade de comparações possível
- Atentar aos limites da imagem das operações usadas (ex: cosseno in [-1;1])
- Evitar criar muitos casos, quando muitos casos implicam em mais código e então mais erro
- Atentar ao erro quando comparar floating points (prática) com números reais
- Diminuir a magnitude dos floatings trabalhados, alterando conseq. o erro
- Usar a estrutura `stableSum` para somatório de floatings não negativos
-* Eliminar pontos muito próximos
-* Adicionar ruído a alguns pontos para evitar colinearidade/planaridade

## Erro, *cutoff* e *chance*
### Erro relativo e absoluto
#### *Catastrophic cancelletion*
### Considerações sobre pontos flutuantes
- Valores decimais no codigo ou como entrada são representados pela representação mais próxima
- As 5 operações básicas (+, -, x, /, sqrt()) são realizadas como se a precisão fosse infinita (sobre a entrada) e então o resultado é arredondado para a representação mais próxima
- *machine epsilon* (%e): 1.2\*10^(-16) para double e 5.5\*10^(-20) para long double
### Estimativa de erros de precisão 
