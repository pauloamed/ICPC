# Árvore Binária de Busca (ABB)

### Integrantes

```
Amanda Albuquerque
Paulo Medeiros
```

## Relatório

Para repreentarmos a ABB usamos duas estruturas: nó e a própria ABB

```
Nó:
	Atributos:
		- chave
		- ponteiro para filho esquerdo
		- ponteiro para filho direito
		- quantidade de nós na subárvore à esquerda
		- quantidade de nós na subárvore à direita
		- altura
	Procedimentos:
		- construtor
```

```
Árvore:
	Atributos:
		- ponteiro para nó cabeça
		- tamanho (quantidade de nós)
		- altura da árvore (da raiz)
	Procedimentos privados:
		- (1) atualizar altura do nó
		- (2) inserir nó recursivamente na árvore
		- (3) descobrir qual o caso de remoção de dado nó
		- (4) remover nó filho dado o pai
		- (5) descobrir o nó antecessor de outro
		- (6) remover um nó do caso 1 ou 2
		- (7) remover nó recursivamente da árvore
		- (8) remover um nó do caso 3
		- (9) destrutor dos nós da arvore
	Procedimentos públicos:
		- (1) construtor
		- (2) destrutor
		- (3) retornar tamanho
		- (4) retornar altura
		- (5) buscar nó na árvore
		- (6) retornar enésimo elemento
		- (7) retornar posição
		- (8) retornar mediana
		- (9) retornar se é cheia
		- (10) retornar se é completa
		- (11) retornar string com percorrimento por nível
		- (12) inserir nó a partir de chave
		- (13) remover nó a partir de chave
		
```

### Procedimentos da Árvore

#### Privados

**1 - **  `_atualizar_altura(no* atual)`

O método tem como função atualizar a altura do nó passado por parâmetro.

Para esse método, a análise de melhor e pior caso são semelhantes. Como esse consiste de apenas operações constantes sendo repetidas de forma constante, tem como complexidade `Θ(1)`.

**2 - ** `bool _inserir(int chave, no* atual)`

A função tenta inserir um nó com a chave passada por parâmetro em sua devida posição na árvore recursivamente. Caso essa chave já esteja presente na árvore, ela não será inserida e a função retornará `false`, caso contrário, retorna `true`.

O melhor caso é quando inserimos na raiz da árvore. Por se tratar de operações constantes sendo repetidas de forma constante, tem como complexidade `Θ(1)`.

O pior caso é quando tentamos inserir abaixo de um nó de nível máximo da árvore. Para isso, precisamos percorrer todos os níveis da árvore, passando de um nó pai para um nó filho a cada passo. Assim, o pior caso tem complexidade `O(h)`. 

Quando a árvore está em formato zigue-zague, a altura é igual à quantidade de nós. Logo, a complexidade nesse caso fica `O(n)`.

**3 - ** `size_t _caso_remocao(no *atual)`

O método tem como função retornar o caso de remoção de um nó filho dado seu nó pai e a direção do filho.

Para esse método, a análise de melhor e pior caso são semelhantes. Como esse consiste de apenas operações constantes sendo repetidas de forma constante, tem como complexidade `Θ(1)`.

**4 - ** `void _remover_filho(no* pai, bool dir)`

O método tem como função remover um nó filho dado um nó pai e a direção do filho.

Para esse método, a análise de melhor e pior caso são semelhantes. Como esse consiste de apenas operações constantes sendo repetidas de forma constante, tem como complexidade `Θ(1)`.

**5 -** `no* _antecessor(no *atual)`

O método tem como função retornar uma referência ao antecessor do nó passado por parâmetro.

O melhor caso e pior caso tem análise de complexidade semelhante. A complexidade desse método depende da quantidade de filhos na cadeia de nós andando à direita a partir do nó à esquerda do nó passado como parâmetro. Tome que `m` é igual à quantidade de nós nessa cadeia, esse método tem complexidade `O(m)`.

**6 - ** `void _remocao_caso12(no* pai, bool dir)`

O método tem como função remover um nó do caso 1 ou 2 dado seu pai e a sua direção em relação ao seu pai. 

Sua análise de complexidade depende unicamente da função (4). Logo, é `Θ(1)`.

**7 - ** `bool _remover(int chave, no* atual)` 
A função recursiva tem como objetivo remover o nó com a chave passada por parâmetro. Caso o nó não exista, a remoção não será efetuada e retornará `false`, caso contrário, retornará `true`.

O melhor caso é quando tentamos remover o nó da raiz e esse configura caso de remoção 1 ou 2. Sua análise de complexidade dependerá da função (6). Logo, é `Θ(1)`.

O pior caso é quando tentamos remover um nó de nível máximo da árvore. Para isso, precisamos percorrer todos os níveis da árvore, passando de um nó pai para um nó filho a cada passo. Assim, o pior caso tem complexidade `O(h)`. 

Quando a árvore está em formato zigue-zague, a altura é igual à quantidade de nós. Logo, a complexidade nesse caso fica `O(n)`.

**8 - ** `void _remocao_caso3(no* pai, bool dir)`
O método tem como função remover um nó do caso 3 dado seu pai e a sua direção em relação ao seu pai.

Sua análise de complexidade depende da função (5) e da função (7).

Logo, sabendo que `m <= h`, a complexidade dessa função pelo princípio aditivo é `O(h)`.

**9 - ** `void _destrutor(no* atual)`

Esse método vai destruindo os nós da ávore um por um de forma recursiva semelhante a um percurso pós-ordem.

Por ser basicamente um percurso de pós-ordem, sua complexidade é de`Θ(N)`.

#### Públicos

**1 - ** `ABB()`

Método construtor da árvore.

Como esse consiste de apenas operações constantes sendo repetidas de forma constante, tem como complexidade `Θ(1)`.

**2 - ** `~ABB()`

Método destrutor da árvore.

A complexidade dependerá do método privado 9 e de operações `Θ(1)`. Logo, sua complexidade será de`Θ(N)`.

**3 - ** `size_t tamanho()`

Método que retorna o tamanho atual da árvore.

A complexidade desse método será `Θ(1)`.

**4 - ** `size_t altura()`

Método que retorna a altura atual da árvore.

A complexidade desse método será `Θ(1)`.

**5 - ** `no* buscar(int chave)`

Método iterativo que retorna referência para nó com a chave passada por parâmetro, se ele existir na árvore.

O melhor caso será quando o a chave procurada se encontra no nó raiz. Logo, terá complexidade `Θ(1)`.

O pior caso é quando buscamos uma chave até o nível máximo da árvore. Para isso, precisamos percorrer todos os níveis da árvore, passando de um nó pai para um nó filho a cada passo. Assim, o pior caso tem complexidade `O(h)`. 

Quando a árvore está em formato zigue-zague, a altura é igual à quantidade de nós. Logo, a complexidade nesse caso fica `O(n)`.

**6 - ** `int enesimo_elemento(size_t n)`

Método iterativo que retorna chave do elemento na posição procurada.

O melhor caso será quando a posição passada é a posição do nó raiz. Logo, terá complexidade `Θ(1)`.

O pior caso é quando o nó com a posição passada está no último nível da árvore. Para isso, precisamos percorrer todos os níveis da árvore, passando de um nó pai para um nó filho a cada passo. Assim, o pior caso tem complexidade `O(h)`. 

Quando a árvore está em formato zigue-zague, a altura é igual à quantidade de nós. Logo, a complexidade nesse caso fica `O(n)`.

**7 - ** `size_t posicao(int x)`

Método iterativo que retorna posição do nó com a chave passada por parâmetro.

O melhor caso será quando a chave passada por parâmetro está no nó raiz. Logo, terá complexidade `Θ(1)`.

O pior caso é quando o a chave passada, se presente na árvore, deverá estar em um nó no último nível da árvore. Para isso, precisamos percorrer todos os níveis da árvore, passando de um nó pai para um nó filho a cada passo. Assim, o pior caso tem complexidade `O(h)`. 

Quando a árvore está em formato zigue-zague, a altura é igual à quantidade de nós. Logo, a complexidade nesse caso fica  `O(n)`.

**8 - ** `int mediana()`

Método que retornará nó na posição da mediana da árvore.

Sua complexidade dependerá do método 6. Logo, terá complexidade `O(h)`.

**9 - ** `bool eh_cheia()`

Método que retorna se a árvore é cheia.

Por consistir apenas de uma sequência constante de operações constantes, sua complexidade será `Θ(1)`.

**10 - ** `bool eh_completa()`

Método que retorna se a árvore é completa.

Será realizado um procedimento semelhante ao percorrimento por nível, só que o último nível não será visitado. Logo, serão visitados com operações constantes  [N-1;N/2] nós. Por isso, sua complexidade é `O(N)`.

**11 - ** `string to_string()`

Método que percorre a árvore por nível e retorna uma string com os nós nessa ordem.

Por ser um percorrimento por nível, todos os nós serão visitados. Em cada uma dessas visitas, operações `Θ(1)` serão executadas. Logo, a complexidade é `Θ(N)`.

**12 - ** `bool inserir(int chave)`

Método que tenta inserir nó com chave passada por parâmetro na árvore. Retorna `true` caso consiga, e `false` caso contrário.

Dependerá da função privada 2. Logo, tem como complexidade de melhor caso`Θ(1)` e de pior caso `O(h)`.

**13 - ** `bool remover(int chave)`

Método que tenta remover nó com chave passada por parâmetro na árvore. Retorna `true` caso consiga, e `false` caso contrário.

Dependerá da função privada 7. Logo, tem como complexidade de melhor caso `Θ(1)` e de pior caso `O(h)`.