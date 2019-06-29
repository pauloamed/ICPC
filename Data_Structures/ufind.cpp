#include<iostream>

#define MAXN 100

/*
 - union find (disjoint union set) com compressao de caminho e uniao por tamanhos
    - acaba ficando O(1) amortizada
    - se usar so um dos dois fica O(log n)
*/

size_t sizes[MAXN]; // vetor com tamanhos
size_t parents[MAXN]; // vetor com pai de cada no

void init(size_t n){
    for(size_t i = 0; i < n; ++i){
        sizes[i] = 1; // tamanho inicial
        parents[i] = i; // valor padrao: cada um eh seu pai
    }
}

size_t do_find(current){
    size_t new_root = current; // variavel para guardar nova raiz
    while(new_root != parents[new_root]) // enquanto nao encontro no raiz
        new_root = parents[new_root]; // subo na arvore


    // compressao de caminho (*)
    size_t next; // backup do pai
    while(parents[current] != new_root){ // enquanto nao acho a nova raiz
        next = parents[current]; // faco o backup do pai
        parents[current] = new_root; // digo que o pai eh a raiz achada (*)
        current = next; // subo na arvore pro backup
    }

    return new_root; // retornamo a raiz da arvore
}

void do_union(size_t a, size_t b){
    a = do_find(a); b = do_find(b); // unimos uma raiz a outra

    if(a == b) return; // se for a mesma raiz, nao tenho o que unir

    // uniao por tamanho
    if(sizes[a] > sizes[b]) swap(a,b); // quero unir "b" a "a"
    sizes[a] += sizes[b]; // atualizando tamanho de "a"
    parents[b] = a; // pai de "b" eh "a"
}
