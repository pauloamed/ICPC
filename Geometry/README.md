# Geometria
## Orientações
1. Evite usar floating points

## Tricks
- Eliminar pontos muito próximos
- Adicionar ruído a alguns pontos para evitar colinearidade/planaridade
- Diminuir a magnitude dos floatings trabalhados, alterando conseq. o erro
- Usar a estrutura `stableSum` para somatório de floatings não negativos


## Erro, cutoff e chance
### Erro relativo e absoluto
#### Catastrophic cancelletion
### Considerações sobre pontos flutuantes
- Valores decimais no codigo ou como entrada são representados pela representação mais próxima
- As 5 operações básicas (+, -, x, /, sqrt()) são realizadas como se a precisão fosse infinita (sobre a entrada) e então o resultado é arredondado para a representação mais próxima
- *machine epsilon* (%e): 1.2*10^(-16) para double e 5.5*10^(-20) para long double
### Estimativa de erros de precisão 
