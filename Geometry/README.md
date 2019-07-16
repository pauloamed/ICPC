# Geometria
Material utilizado:
- Handbook of geometry for competitive programmers, Victor Lecomte
- Competitive Programming 3, Steven & Felix
- https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
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

## *Floating points*
### Erro, *cutoff* e *chance*
Esses três conceitos estão atrelados à tomada de decisões
- Erro: maior imprecisão possível quando for tomar a decisão
- *chance*: o menor valor (fronteira) antes da mudança de decisão
- *cutoff*: valor usado para permitir intervalo de possíveis valores numa tomada de decisão

Erro e *chance* podem ser calculados. Queremos que `erro < cutoff < chance`. É bom escolher um valor igualmente espaçado aos limites.

#### Erro relativo e absoluto
Erros podem ser indicados de forma relativa ou absoluta:
- Relativo: proporcional á magnitude do número
- Absoluto: valor do erro

##### *Catastrophic cancelletion*
Fenômeno que permite um número de pequena magintude ter um erro (muito) maior que o erro esperado (relativo). Tome que o erro relativo é de 10^(-6). Logo, para 10^6, o erro esperado é de 10^0. Tome agora que dois números com essa magnitude serão cancelados, gerando um número de magnitude 10^0. O erro anterior era de 10^0. Agora temos um número 10^0 com erro 10^0 (10^0 >>> 10^(-6)).

### Considerações sobre pontos flutuantes
- Valores decimais no codigo ou como entrada são representados pela representação mais próxima
- As 5 operações básicas (+, -, x, /, sqrt()) são realizadas como se a precisão fosse infinita (sobre a entrada) e então o resultado é arredondado para a representação mais próxima
- *machine epsilon* (%e): 1.2\*10^(-16) para double e 5.5\*10^(-20) para long double. É o erro relativo.

### Estimativa de erros de precisão 
Erros de precisão podem ser estimados em dois cenários:
- Entrada da operação é exata
- Entrada da operação é imprecisa

#### TODO

## Objetos geométricos
#### 0D
- Pontos: (...)
#### 1D
- Linhas: (...)
- Vetores: (...)
Segmentos
#### 2D
- Circulos: (...)
- Poligonos: (...)

## Algoritmos (e extensões) não implementados
### 3 pontos colineares
Para cada ponto, realizar ordenação polar ((N)(NlogN)). Checar se pontos adjacentes sao colineares para cada ordenação.
### Área do polígono - *Shoelace formula*
- Polígono nao se intersecta. Origem não precisa estar dentro do polígono;
- Polígono é dado ordenado (anti ou horário);
- Aplica produto vetorial aos vetores induzidos (origem) pelos pontos, dois a dois, achando a área do paralelogramo. Divide essa área por dois;
- Processar o polígono no sentido reverso resulta na área com sinal oposto.
### Orientação do polígono (anti/horário)
Examinar o sinal da área calculada usando o *shoelace formula*.
### Perímetro de polígono
Dado que o polígono foi dado ordenado, basta somar as distâncias dos segmentos.
### Convexidade de polígono
Checar se todos produtos vetoriais (de pontos 3 a 3) possuem o mesmo sinal.
### *Online convex hull*
Dado um convex hull, quero saber se consigo adicionar um ponto a ele (tornar área igual ou menor?). Pode ser implementado com `set`. Acho a posição em que o ponto deveria ficar (log) e checo se o produto vetorial dele com os adjacentes indica se o polígono ainda é convexo. Caso de borda: pontos colineares (fico com o ponto mais distante).

## Teoria
### Teorema de Helly
Let C be a finite family of convex sets in Rn such that, for k ≤ n + 1, any k members of C have a nonempty intersection. Then the intersection of all members of C is nonempty
### Soma de Minkowski
- Soma/diferença (n^2) entre conjuntos de pontos no R²
- O *zero set* (conjunto com o vetor nulo) é o elemento nulo da operação
- O conjunto vazio somado a qualquer outro conjunto resulta no conjunto vazio
- For all non-empty subsets S1 and S2 of a real vector-space, the convex hull of their Minkowski sum is the Minkowski sum of their convex hulls
- If S is a convex set then also μS+λS is a convex set; furthermore μS+λS=(μ+λ)S for every μ,λ≥0. Conversely, if this “distributive property” holds for all non-negative real numbers, μ,λ, then the set is convex.
- Soma de Minkowski entre conjuntos convexos: O(n+m) [implementado]
### *Winding number*
In mathematics, the winding number of a closed curve in the plane around a given point is an integer representing the total number of times that curve travels counterclockwise around the point. The winding number depends on the orientation of the curve, and is negative if the curve travels around the point clockwise.
Se for nulo, o ponto está fora do polígono. Caso contrário (?).
### Teorema de *Pick*
- Pontos inteiros: pontos com coordenadas inteiras
```
- A: área do polígono
- i: #pontos inteiros no interior do polígono
- b: #pontos inteiros na borda do polígono
A = i + (b/2) - 1
```
### Trigonometria
#### Soma, diferença de ângulos
```
sin(x+y) = sin(x)*cos(y)+sin(y)*cos(x)
sin(x-y) = sin(x)*cos(y)-sin(y)*cos(x)
cos(x+y) = cos(x)*cos(y)-sin(y)*sin(x)
cos(x-y) = sin(x)*sin(y)+cos(y)*cos(x)
```
#### Lei dos senos
```
Em um triângulo ABC qualquer, inscrito em uma circunferência de raio r, de lados AB, BC e AC, que medem respectivamente a, b
e c, com ângulos internos Â, ^B e Ĉ, vale a seguinte relação:
(a/sin(Â)) = (b/sin(^B)) = (c/sin(Ĉ)) = 2r
```
#### Lei dos cossenos
```
Triângulo ABC qualquer de lados AB, BC e AC, que medem respectivamente a, b e c, com ângulos internos Â, ^B e Ĉ, vale a 
seguinte relação:
a² = b² + c² - 2*b*c*cos(Â)
```
