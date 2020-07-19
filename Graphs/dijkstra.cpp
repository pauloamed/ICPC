#include<bits/stdc++.h>
using namespace std;

#define INF 10000000
#define MAXN 100

int dist[MAXN]; // Vetor de distancias
int parent[MAXN]; // Vetor com o pai
vector<pair<int, int>> v[MAXN]; // Lista de adjacencia com pesos

/*
Analisa um vertice por vez, aquele com menor distancia ja calculada
Como nao tem aresta negativa, depois que um vertice for removido, ele nao sera
mais visitado
COMPLEXIDADE TEMPO:
    HEAP TEM SIMULTANEAMENTE O(n) CARAS
    n OPERACOES DE INSERT E DELETE (log n)
    O(m) OPERACOES DE ATUALIZACAO (log n)
    O((n+n+m)log n)
COMPLEXIDADE ESPACO:
    O(n)
*/

void dijkstra(int u, int n){
    set<pair<int,int>> s; // Set do Dijkstra com dists e atuais
    for(int i = 0; i < n; ++i){
        dist[i] = INF; // inicializando distancias
        parent[i] = i; // inicializando pai
    }

    dist[u] = 0; // Distancia para o vertice de inicio atualizada
    s.insert({0, u}); // Adiciono a dist p ele e ele, na heap ordenada por dists

    while(!s.empty()){
        int cur_dist = s.begin()->first; // Recuperando dist pro vertice atual
        int cur_vertice = s.begin()->second; // Recuperando o vertice atual
        s.erase(s.begin()); // Removendo vertice atual do set, cada vertice passa por isso 1
        // vez, ja que nao ha aresta negativa

        for(int i = 0; i < v[cur_vertice].size(); i++){ // Pra cada adjacente
            // Distancia pro adjacente
            int dist_adj = cur_dist + v[cur_vertice][i].second;

            // Se a dist computada pro adj for menor que a armazenada
            if(dist_adj < dist[v[cur_vertice][i].first]){
                // Remove registro antigo se tiver
                s.erase({dist[v[cur_vertice][i].first], v[cur_vertice][i].first});

                dist[v[cur_vertice][i].first] = dist_adj; // Atualiza distancia
                parent[v[cur_vertice][i].first] = cur_vertice; // Atualiza pai
                s.insert({dist_adj,v[cur_vertice][i].first}); // Manda pro set
            }
        }
    }
}
