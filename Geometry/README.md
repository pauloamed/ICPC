# Geometria
Material utilizado:
- Handbook of geometry for competitive programmers, Victor Lecomte
- Competitive Programming 3, Steven & Felix
## Orientações
- Evitar usar floating points (junto a isso: divisão, raiz quadrada, funções trigonométricas)
- Fazer a menor quantidade de comparações possível
- Atentar aos limites da imagem das operações usadas (ex: cosseno in [-1;1])
- Evitar criar muitos casos, quando muitos casos implicam em mais código e então mais erro
- Atentar ao erro quando comparar floating points (prática) com números reais
- Diminuir a magnitude dos floatings trabalhados, alterando conseq. o erro
- Use a estrutura implementada para somatório de floatings
- Cuidado com corner-cases
  - Linhas verticais, pontos colineares, Convex hull de um único ponto, 
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

## Considerações sobre pontos flutuantes
- Valores decimais no codigo ou como entrada são representados pela representação mais próxima
- As 5 operações básicas (+, -, x, /, sqrt()) são realizadas como se a precisão fosse infinita (sobre a entrada) e então o resultado é arredondado para a representação mais próxima
- *machine epsilon* (%e): 1.2\*10^(-16) para double e 5.5\*10^(-20) para long double. É o erro relativo.

## Estimativa de erros de precisão 
Erros de precisão podem ser estimados em dois cenários:
- Entrada da operação é exata
- Entrada da operação é imprecisa

### Entrada exata
Aqui eu entendi que fica legal kkk

### Entrada imprecisa
#### +, -

#### *
#### /, sqrt()
Para essas operações, não há garantias

## Objetos geométricos
0D,1D,2D,3D
### 0D
Pontos
### 1D
Linhas
Vetores
Segmentos
### 2D
Circulos
Poligonos
### 3D

## *Winding number*

## Algoritmos simples - não implementados
### 3 pontos colineares
Para cada ponto, realizar ordenação polar ((N)(NlogN)). Checar se pontos adjacentes sao colineares para cada ordenação.
### Área do polígono - Shoelace formula
- Polígono nao se intersecta. Origem não precisa estar dentro do polígono;
- Polígono é dado ordenado (anti ou horário);
- Aplica produto vetorial aos vetores induzidos (origem) pelos pontos, dois a dois, achando a área do paralelogramo. Divide essa área por dois;
- Processar o polígono no sentido reverso resulta na área negativa.
### Orientação do polígono (anti/horário)
Examinar o sinal da área calculada usando o Shoelace formula.
### Perímetro de polígono
Dado que o polígono foi dado ordenado, basta somar as distâncias dos segmentos.
### Convexidade de polígono
Checar se todos produtos vetoriais (de pontos 3 a 3) possuem o mesmo sinal.

## Estruturas implementadas
### `neumaierSum`
Acumulador de pontos flutuantes com melhor precisão
