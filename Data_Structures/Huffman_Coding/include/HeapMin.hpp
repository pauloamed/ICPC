#ifndef HEAPMIN
#define HEAPMIN

#include"Node.hpp"

class HeapMin{
private:
    std::pair<size_t, Node *> *v;
    size_t _size;

    void descer_itr(size_t ipai){
        size_t ifilho; // Variavel auxilar com indice do filho
        while(true){
            // ifilho apontando para o filho a esq de ipai
            ifilho = (ipai << 1);

            // Se passou do limite de nos, acaba (1-indexado)
            if(ifilho > _size) break;

            // Se existe filho a direita e esse filho a direita tem maior
            // prioridade que o da esquerda
            if(ifilho+1 <= _size && v[ifilho+1].first < v[ifilho].first)
                ifilho++;

            // Se o filho com maior prioridade tiver prioridade maior que o pai,
            // troque esse filho com o pai. Se nao, nao conseguimos mais descer
            if(v[ifilho].first < v[ipai].first)
                swap(v[ifilho],v[ipai]);
            else break;

            // Segue com descer
            ipai = ifilho;
        }
    }

    void subir_itr(size_t ifilho){
        size_t ipai; // Variavel auxilar com indice do filho
        while(true){
            // ipai apontando para o pai de ifilho
            ipai = ifilho / 2;

            // Caso o ipai seja 0, que eh um indice invalido, nao podemos mais subir
            if(ipai == 0)
                return;

            // Caso a prioridade do filho seja maior que a do pai, troque
            // CC. nao conseguimos mais subir
            if(v[ifilho].first < v[ipai].first)
                swap(v[ipai],v[ifilho]);
            else return;

            // Segue com subir
            ifilho = ipai;
        }
    }

public:
    // Construtor
    HeapMin(size_t maxSize){
        v = new std::pair<size_t, Node *>[maxSize + 1];
        _size = 0;
    }

    // Destrutor
    ~HeapMin(){
        delete v;
    }

    // Remove
    void remove(){
        // Se tamanho for 0, nao ha oq remover
        if(_size == 0)
            return;
        else{
            // Caso tamanho nao seja nulo, trocamos o primeiro no com o
            // ultimo e diminuimos o tamanho, excluindo assim esse No.
            // Em seguida descemos esse ultimo no posto na primeira posicao
            swap(v[1],v[_size--]);
            descer_itr(1);
        }
    }

    void insert(std::pair<size_t, Node *> e){
        // Adicionamos o no ao fim do vetor e tentamos subi-lo o maximo possivel,
        // tornando assim a heap valida
        v[++_size] = e;
        subir_itr(_size);
    }

    size_t size(){ return this->_size; }

    std::pair<size_t, Node*> top(){
        return v[1];
    }
};


#endif
