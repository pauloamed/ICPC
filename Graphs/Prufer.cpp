#include<bits/stdc++.h>
using namespace std;

#define MAXN 10000

// Funcao pra converter codigo prufer em lista de aresatas (nlogn)
vector<pair<size_t,size_t>> PrufetToTree(vector<size_t> pseq){ // Vetor com a lista de prufer
    vector<pair<size_t,size_t>> ret; // Vetor com retorno
    size_t n = pseq.size(); // Recuperando tamanho da lista
    size_t degree[n+3]; // Vetor com graus de cada vertice

    for(int i = 0; i <= n+2; i++) degree[i] = 1; // Init grau de cada vertice
    for(auto &x : pseq) degree[x]++; // Contando os graus dos vertices

    priority_queue<size_t> pq; // Estrutura ordenada
    for(size_t i = 0; i < n; ++i){
        size_t va = pq.top(); pq.pop(); // Extrindo menor no com grau 1
        ret.push_back({va, pseq[i]}) // Existe uma aresta dele com o atual da lista
        if(--degree[pseq[i]] == 1) pq.push(pseq[i]); // Adiciono o atual da lista
        // na pq se necessario
    }

    // Adicionando os ultimos dois os da lista
    size_t temp = pq.top(); pq.pop();
    ret.push_back({temp, pq.top()});

    return ret;
}

/////////////////////////////////////////////////////////////////////////////////

vector<size_t> v[MAXN]; // Lista de adj da arvore (bidirecional)

vector<size_t> TreeToPrufer(size_t n){
    size_t degree[n]; // Vetor auxiliar para contagem de grau

    vector<size_t> ret; // Vetor com sequencia de retorno

    priority_queue<size_t> pq; // Estrutura ordenada que vai manter as folhas
    for(size_t i = 0; i < n; i++){
        degree[i] = v[i].size(); // Grau eh igual a qnt de conex na lista de adj
        if(degree[i] == 1) pq.push(i); // Se eh folha, adiciono na estrutura
    }

    for(size_t i = 0; i < n-2; ++i){ // Construindo lista
        size_t x = pq.top(); pq.pop(); // Extraindo menor folha da pq
        degree[x]--; // x sera removido da arvore, grau torna 0

        for(size_t i = 0; i < v[x].size(); i++){
            if(degree[v[x][i]]){ // Acessando so unico vertice ligado (x eh folha)
                ret.push_back(v[x][i]); // Adicionando vertice
                if(--degree[v[x][i]] == 1) // Se o adjacente virou folha
                    folhas.insert(v[x][i]); // Adiciono na pq
            }
        }
    }

    return ret;
}
