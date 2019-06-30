#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000
#define INF 1000000

size_t parent[MAXN]; // vetor para guardar o pai do vertice na mst
vector<pair<int,int>> v[MAXN]; // lista de adjacencia (adjacente e peso)

/*
Funciona mantendo uma estrutura de ordenacao. Ta dentro da estrutura quem ainda
nao entrou na MST. A cada passo, tiro um cara da estrutura, adicionando-o a MST.
Quando faco isso, tambem olho seus adjacentes, pra possivelmente atualizar o custo
salvo na est. de ord. pra chegar nele.

Funciona OK com aresta negativa.

O(m log m)
*/

vector<pair<int,int>> prim(size_t n){
    int cost[MAXN]; // estrutura auxiliar para manter track do custo de adicionar vertice
    for(size_t i = 0; i < n; ++i) cost[i] = INF; // inicializando est. aux.

    set<pair<int,int>> s; // estrutura de ordenacao
    vector<pair<int,int>> ans; // vetor resposta (vertice, pai dele na MST)
    cost[0] = parent[0] = 0; // escolho 0 (arbitrario) como raiz e atualizo seus valores
    s.insert({cost[0],0}); // insiro ele na estrutura de ordenacao

    // completo a estrutura de ordenacao com os vertices restantes
    for(size_t i = 1; i < n; ++i) s.insert({key[i], i});

    int x, y, val;
    while(ans.size()+1 < n && !s.empty()){ // analisa cada vertice

        x = s.begin()->second; // recupero o vertice com menor custo de ser adicionado

        // fazndo isso, "adiciono" na mst
        s.erase(s.find({cost[x], x})); // e removo ele da est de ord (log n)
        if(x != parent[x]) ans.push_back({x, parent[x]}); //

        // analiso os adjacentes do vertice que acabo de adicionar para
        // possivelmente adiconar os pesos salvos na est de ordenacao
        for(int i = 0; i < v[x].size(); ++i){ // para todos os adj do vertice atual
            y = v[x][i].first; // vertice adjacente
            val = v[x][i].second; // peso da aresta
            auto temp = s.find({cost[y], y}); // logn
            // temp vai retornar um itr valido se ele ainda nao foi adicionado na mst

            // se o peso pra chegar em y for menor que o salvo na est de ord
            if(val < cost[y] && temp != s.end()){
                s.erase(temp); s.insert({val, y}); // atualizo o valor pra chegar em y
                cost[y] = val; // atualizo est auxiliar
                parent[y] = x; // agora o "pai" de y eh x
            }
        }
    }
    if(ans.size() + 1 == n) return ans; // se completou as n-1 arestas
    else return vector<pair<int,int>>(); // senao, retorna vetor vazio
}
