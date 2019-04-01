# Relatório - Codificador de Huffman
##### Autores
```
Amanda Albuquerque
Paulo Medeiros
```
## Decisões de Projeto
Para realizarmos o projeto, construímos 3 classes:
+ `Node` - Classe representando o elemento mais básico da árvore: o nó.
+ `HeapMin` - Classe representando a Heap que será usada na construção da árvore.
+ `Huffman` - Classe principal onde a compressão/descompressão será feita.

Para representarmos uma sequência de bits, decidimos usar um `std::vector<bool>` , vetor de booleanos. Apesar de que no C++ o tipo `bool` ocupa 1 byte, ao invés de 1 bit, esse *overhead* ocorre somente durante a execução do programa, não interferindo na compressão.

Para gravarmos/lermos os bits num arquivo, usamos da representatividade do tipo `unsigned char` que junto dos procedimentos `_addCharToBoolVec`, `_charFromBoolVec` e `_mostSigBit` , que serão apresentados abaixo. Fazendo isso, conseguimos efetivamente escrever blocos de 8 bits (1 byte) na memória.

Para a criação da árvore a partir da contagem de letras do arquivo, fizemos uso da `HeapMin` aqui implementada. Com essa estrutura, pudemos implementar o método de construção. Para facilitar a implementação, o elemento da `HeapMin` é um `pair<size_t, Node*>` (par com um inteiro sem sinal e um ponteiro para nó). Com isso, resumimos a operação de `merge` em criar um novo nó a partir dos elementos na segunda posição dos pares e obter a nova pontuação a partir dos elementos na primeira posição. Mais detalhes podem ser observados no construtor da classe `Huffman`.

Para percorrer a árvore, os percorrimentos de pré e pós-ordem foram utilziados, ambos de forma recursiva. O percorrimento em pré-ordem foi usado no contexto do cabeçalho e o em pós-ordem, na construção da tabela de compressão.

Infelizmente, foi usado um caractere como delimitador. Os autores entendem que, quando implementado de forma mais versátil, o projeto dispensaria o uso de um delimitador, evitando possíveis erros de descompressão. O caso em que o delimitador seria dispensado é quando sempre é possível acessar o próximo bit do arquivo, sem interrupção da construção da árvore. Sendo assim, o próprio algoritmo de pré-ordem identificaria o fim do cabeçalho (esse sendo somente a árvore).



## Estrutura do Código

### `Node`
#### Atributos
```
Node **children - Ponteiro de ponteiro para o mesmo tipo. Será usado para apontar para os filhos do nó.
unsigned char content - O conteúdo do nó expresso em char. Será "nulo" no nós internos e um valor específico nas folhas.
```
#### Métodos
```
Node(Node* a = nullptr, Node* b = nullptr, char _content = '\0') - Construtor da classe.
```

### `HeapMin`
#### Atributos
```
std::pair<size_t, Node *> *v - Ponteiro para que representará vetor que compõe a Heap.
size_t _size - O tamanho atualizado da Heap.
```
#### Métodos
```
void descer_itr(size_t ipai) : Método que recebe um indice para um nó pai e compara sua prioridade com seus filhos e caso seja de menor prioridade, irá trocar de posição com seu filho de maior prioridade

void subir_itr(size_t ifilho): Método que recebe um indice para um nó filho e compara sua prioridade com seu pai e caso seja de maior prioridade, irá trocar de posição.

HeapMin(size_t maxSize) : Construtor da classe

~HeapMin(): Destrutor da classe

void remove(): Método usado para remover nó. O primeiro nó é trocado com o ultimo e depois é diminuido o tamanho da heap. No final é chamado o método descer para voltar a ser uma heapmin válida.

void insert(std::pair<size_t, Node *> e): Método usado para inserir nó. O nó é adicionado no fim do vetor e usamos o método subir para tornar a heapmin válida novamente.

size_t size(): Método que retorna o tamanho atual.

std::pair<size_t, Node*> top(): Método que retorna o topo do vetor.
```
### `Huffman`
#### Atributos
```
size_t _numChars - Quantidade de chars diferentes na arvore
Node *_root - Ponteiro para nó raiz
```
#### Métodos
```
void _addCharToBoolVec - Metodo para adiconar bits de char a um vetor de booleanos

void _headerGen: Metodo para gerar o cabecalho. Percorrimento eh pre-ordem

unsigned char _charFromBoolVec: Recuperar um char dos proximos 8 bits de um vetor de bool

void _treeGenHeader: Gerador do header a partir da sequencia de bits

void _comprTableGen: Gerador da tabela de compressao

void _maybeResetBuffer: Lógica do Buffer: Atualização do próximo char e checagem se já está cheio.

bool _mostSigBit: Função para retornar o bit mais significativo de um char

std::vector<bool> _bitsFromString: Função para recuperar os bits de uma string

Huffman(std::string file_name, bool fromCompressed) : Construtor da classe.

~Huffman(): Destrutor da classe.

void compress(std::string file_name): Método que compacta o arquivo passado por parâmetro, salvando a versão comprimida em outro arquivo.

void uncompress(std::string file_name): Método que descompacta o arquivo passado por parâmetro, salvando a versão descomprimida em outro arquivo.
```



## Bibliotecas utilizadas

+ `fstream` - Responsável pela escrita/leitura de arquivos.
+ `iostream` - Responsável pela stream de comunicação de erros.
+ `string` - Usada para representar o nome dos arquivos e na leitura do cabeçalho do arquivo comprimido.
+ `vector` - Por ser uma estrutura sequencial, foi usada para representar uma sequência de bits.
+ `map` - Usado na tabela de compressão