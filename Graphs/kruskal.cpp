#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000

int parent[MAXN]; // vetor com pais do union find
int size[MAXN]; // vetor com tamanhos do union find
vector<pair<size_t,pair<size_t,size_t>>> a; // vetor com arestas

/*
Ordena as arestas por peso decrescente, e vai gulosamente tentando adiciona-las
a MST, sem formar ciclos.
Funciona OK com aresta negativa.

COMPLEXIDADE TEMPO:
    O(m log m) - ORDENACAO DAS ARESTAS
    ~O(m) - AMORTIZADA NO UNION FIND
COMPLEXIDADE ESPACO:
    O(n+m) - GUARDANDO UNION FIND E ARESTAS

*/

size_t find(size_t cur){ // Find do union find com comp de caminho
    size_t temp, root = cur;

    // Procurando a raiz
    while(parent[root] != root)
        root = parent[root];

    // Vou a caminho da raiz
    while(parent[x] != cur){
        temp = parent[cur]; // backup do pai do current
        parent[cur] = root; // o novo pai do current eh a raiz
        cur = temp; // subo pro pai no backup
    }

    return root;
}

void join(size_t x, size_t y){ // Union do union find
    // acho as respectivas raizes
    x = find(x); y = find(y);

    if(x == y) return; // for a mesma, faco nada

    // quero sempre botar o x no y
    if(size[x] > size[y]) swap(x,y);
    size[y] += size[x]; // arvore y tem seu tamanho aumentado
    parent[x] = y; // pai de x eh o y
}

vector<pair<size_t,pair<size_t,size_t>>> kruskal(size_t n){ // param: tamanho do grafo
    sort(a.begin(), a.end()); // ordenando lista de arestas
    vector<pair<size_t,pair<size_t,size_t>>> ans; // lista de arestas que serao selecionadas

    size_t cont = 0;
    for(size_t i = 0; i < a.size(); ++i){ // para cada aresta na lista
        if(find(a[i].second.first) == find(a[i].second.second))
            continue; // se formar ciclo, nao adiciona

        join(a[i].second.first, a[i].second.second); // adiciona no union find
        ans.push_back(a[i]); // adiciona no vetor resposta
        if(ans.size() == n-1) return ans; // se chegar a n-1 arestas, eh arvore
    }
    return vector<pair<size_t,pair<size_t,size_t>>>(); // se n der certo, retorna vazio
}
