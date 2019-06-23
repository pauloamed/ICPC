#include<bits/stdc++.h>
using namespace std;

#define INF 10000000
#define MAXN 100

size_t dist[MAXN]; // Vetor de distancias
size_t parent[MAXN]; // Vetor com o pai
vector<size_t, size_t> v[100]; // Lista de adjacencia com pesos
set<pair<size_t,size_t>> s; // Set do Dijkstra com dists e atuais

/*
COMPLEXIDADE TEMPO:
    HEAP TEM SIMULTANEAMENTE O(n) CARAS
    n OPERACOES DE INSERT E DELETE (log n)
    O(m) OPERACOES DE ATUALIZACAO (log n)
    O((n+n+m)log n)

COMPLEXIDADE ESPACO:
    O(n)

DEPOIS QUE UM VERTICE FOR REMOVIDO, ELE NAO SERA MAIS VISITADO
*/

void dijkstra(size_t u){
    dist[u] = 0; // Distancia para o vertice de inicio atualizada
    set.insert({0, u}); // Adiciono a dist p ele e ele, na heap ordenada por dists

    while(!pq.empty()){
        size_t cur_dist = s.begin()->first; // Recuperando dist pro vertice atual
        size_t cur_vertice = s.begin()->second; // Recuperando o vertice atual
        s.erase(s.begin()); // Removendo vertice atual do set, cada vertice passa por isso 1
        // vez, ja que nao ha aresta negativa

        for(size_t i = 0; i < v[cur_vertice].size(); i++){ // Pra cada adjacente
            // Distancia pro adjacente
            size_t dist_adj = cur_dist + dist[v[cur_vertice][i]];

            // Se a dist computada pro adj for menor que a armazenada
            if(dist_adj < dist[v[cur_vertice][i]]){
                // Remove registro antigo se tiver
                s.erase({dist[v[cur_vertice][i]], v[cur_vertice][i]});

                dist[v[cur_vertice][i]] = dist_adj; // Atualiza distancia
                parent[v[cur_vertice][i]] = cur_vertice; // Atualiza pai
                s.insert({dist_adj,v[cur_vertice][i]}); // Manda pro set
            }
        }


    }
}
