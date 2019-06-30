#include<bits/stdc++.h>
using namespace std;

#define MAXN 10000
#define lpss list<pair<size_t, size_t>>
#define edgelist vector<pair<lpss::iterator, lpss::iterator>

vector<size_t> v[MAXN]; // lista de adjacencia original

void dfs(size_t x, size_t ini, list<size_t> &temp, lpss *_v, edgelist &edges, bool init=true){
    if(temp.front() != x) temp.push_front(x); // Nao inserir elementos repetidos
    if(!init && x == ini) return; // Se fechou o ciclo
    else{ // Se nao fechou o ciclo
        size_t next = _v[x].front().first; // Recuperando proximo vertice a ser acessado
        size_t e = _v[x].front().second; // Recuperando id da aresta

        // Removendo aresta de ambas listas de adjacencias
        if(x < next){
            // Entao o it da esquerda ta na lista de x e o da dir na lista de next
            _v[x].erase(edges[e].first);
            _v[next].erase(edges[e].second);
        }else{
            // Entao o it da esquerda ta na lista de next e o da dir na lista de x
            _v[x].erase(edges[e].second);
            _v[next].erase(edges[e].first);
        }
        dfs(next, ini, temp, v, matrix, false); // Passo recursivo
    }
}

list<size_t> hierholzer(size_t n){

     // Lista de adjacencia com (adjacente, id_no_adjacente, bool valido)
    lpss _v[n];

    // Vetor auxiliar relacionando os dois lados da aresta
    edgelist edges;

    // Lendo as arestas e construindo estruturas
    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < adj[i].size(); ++j){
            if(i > v[i][j]) continue; // ignoro metade das arestas

            // adiciono na list de adj
            _v[i].push_back({v[i][j], arestas.size()});
            _v[v[i][j]].push_back({i, arestas.size()});

            // adiciono no vetor auxiliar
            // o itr da esq eh da lista do menor id
            // o itr da dir eh da lista de maior id
            edges.push_back({_v[i].end()-1, _v[v[i][j]].end()-1});
        }
    }

    list<size_t> temp, ret; // Declaracao de lista auxiliar e lista de retorno
    // temp vai guardar quem ta no ciclo e ainda pode ser usado para iniciar
    // uma nova busca
    // ret vai guardar circuito em sua ordem final

    dfs(1,1, temp, v, matrix); // Buscando ciclo inicial

    while(true){ // Loop externo (construcao de temp)

        // Loop interno (alimentando ret)
        while(!temp.empty() && !v[temp.front()].empty()){
            // Vou preenchendo ret com os vertices de temp, enquanto tem gnt em
            // temp e enquanto nao posso comecar um novo ciclo do inicio de temp
            ret.splice(ret.cend(), temp, temp.cbegin());
        }
        if(temp.empty()) return ret; // Se nao posso aproveitar mais ninguem de temp, cabou
        dfs(temp.front(), temp.front(), temp, v, edges); // Tentar achar mais um ciclo
    }
}
