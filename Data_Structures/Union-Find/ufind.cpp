#include<iostream>

class Union_Find{
private:
    size_t *sizes;
    size_t *parents;
    size_t size;
public:

    // Construtor da estrura
    Union_Find(size_t size){
        this->size = size;

        // Incializando a estrura a partir do tamanho
        // passado por parametro
        sizes = new size_t[size];
        parents = new size_t[size];

        // Inicializando as estruturas interas
        // vetor para referenciar pai e tamanho
        for(auto i = 0u; i < size; ++i){
            sizes[i] = 1;
            parents[i] = i;
        }
    }

    // Destrutor da estrutura, libera estruturas internas
    ~Union_Find(){
        delete sizes, parents;
    }

    // Funcao para o find, retorna a raiz do grupo a quem
    // a id passada por parametro pertence
    // Find com compressao de caminhos
    size_t do_find(size_t current){
        // Primeiro achamos a raiz do grupo ao qual
        // current pertence
        size_t new_root = current;
        while(new_root != parents[new_root])
            new_root = parents[new_root];

        // Em seguida, percorremos o mesmo caminho ate a raiz
        // e definimos os pais diretos de cada no nesse caminho
        // como a propria raiz do grupo
        size_t next;
        while(parents[current] != new_root){
            next = parents[current];
            parents[current] = new_root;
            current = next;
        }

        // Retornamos a raiz do grupo
        return new_root;
    }

    void do_union(size_t a, size_t b){
        // Realizamos o find em A e em B para acharmos
        // a raiz de seus grupos
        // Se adicionarmos a direto em b ou o contrario,
        // a arvore resultante teria altura = altura(a) + altura(b)
        // Ja que a complexidade temporal do find eh dada por essa altura,
        // essa alternativa perde para adicionarmos a raiz de b na raiz de a
        // ou o contrario (resulta em altura = max(altura(a), altura(b)) + 1)
        a = do_find(a);
        b = do_find(b);

        // Pela Uniao por tamanho, queremos adicionar a menor arvore
        // à maior.
        // Quando ligamos a arvore menor à arvore maior, a arvore menor aumenta
        // sua altura em 1, enquanto a arvore maior tem sua altura inalterada.
        // Dessa forma, sempre precisamos de uma arvore maior que atual para
        // aumentar seu tamanho em 1. Comecando com uma arvore de somente 1 no,
        // vemos que essa operacao pode ser realizada no maximo logn vezes.
        // Portanto, logn sera a altura maxima da arvore.
        // Eh facil ver que, se permitimos adicionar a arvore maior à arvore
        // menor, a altura pode chegar a N. Tome o exemplo em que adicionamos
        // um no de cada vez a ao mesmo grupo.
        // Se for a mesma raiz, nao ha uniao a ser feita
        if(a == b) return;
        else if(sizes[a] > sizes[b]){
        // Caso a arvore em A tenha mais nos do que a arvore em B
            sizes[a] += sizes[b];
            parents[b] = a;
        }else{
        // CC
            sizes[b] += sizes[a];
            parents[a] = b;
        }
    }

    void print(){
        std::cout << "Ids:\t\t";
        for(size_t i = 0; i < size; ++i){
            std::cout << i << " ";
        }std::cout << std::endl;
        std::cout << "Parents:\t";
        for(size_t i = 0; i < size; ++i){
            std::cout << parents[i] << " ";
        }std::cout << std::endl;
    }
};

int main(){
    Union_Find uf(10);
    char OP;
    int A, B;
    while(true){
        scanf(" %c", &OP);
        if(OP == 'Q'){
            break;
        }else if(OP == 'U'){
            std::cin >> A >> B;
            uf.do_union(A, B);
        }else if(OP == 'F'){
            std::cin >> A;
            std::cout << uf.do_find(A) << std::endl;
        }else
            uf.print();
    }
}
