#include<bits/stdc++.h>
using namespace std;

#define MAXN 10000

vector<size_t> adj[MAXN];

void dfs(size_t x, size_t ini, list<size_t> &temp, list<size_t> *v, size_t **matrix, bool init=true){
    if(temp.front() != x) temp.push_front(x); // Nao inserir elementos repetidos
    if(!init && x == ini){ // Se fechou o ciclo
        return;
    }else{ // Se nao fechou o ciclo
        while(matrix[x][v[x].front()] > matrix[v[x].front()][x]){ // Atualizando lista de adjacencia
            matrix[x][v[x].front()]--;
            v[x].pop_front();
        }

        size_t next = v[x].front(); v[x].pop_front(); // Recuperando proximo vertice a ser acessado
        matrix[x][next]--; // Atualizando matriz auxiliar
        dfs(next, ini, temp, v, matrix, false); // Passo recursivo
    }
}

list<size_t> hierholzer(size_t n){

    list<pair<size_t, size_t>> v[n]; // Lista de adjacencia com (adjacente, id da aresta)
    // vetor que relaciona o id da aresta a seus ids
    pair<list<size_t>::iterator, list<size_t>::iterator> id2itrs;

    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < adj[i].size(); ++j){
            v[i].push_back(adj[i][j]);
            v[adj[i][j]].push_back(j);

            id2itrs.push_back
        }
    }

    // ----------------------------------- HIERHOLZER --------------------------------------


    list<size_t> temp, ret; // Declaracao de lista auxiliar e lista de retorno
    // temp vai guardar quem ta no ciclo e ainda pode ser usado para iniciar
    // uma nova busca
    // ret vai guardar circuito em sua ordem final

    dfs(1,1, temp, v, matrix); // Buscando ciclo inicial

    while(true){ // Loop externo (construcao de temp)
        while(true){ // // Loop interno (alimentando ret)
            if(temp.empty()) break; // Se nao posso aproveitar mais ninguem de temp, cabou

            if(!v[temp.front()].empty()){ // Se meu vertice de temp ainda tiver adjacentes
                // Checando se o proximo adjacente a temp.front() é invalido
                if(matrix[temp.front()][v[temp.front()].front()] > matrix[v[temp.front()].front()][temp.front()]){
                    // Se for invalido, atualize a lista de adjacencia
                    matrix[temp.front()][v[temp.front()].front()]--;
                    v[temp.front()].pop_front();
                    continue;
                }else break; // Nao tem problema
            }
            ret.splice(ret.cend(), temp, temp.cbegin()); //
        }
        if(temp.empty()) break; // Se nao posso aproveitar mais ninguem de temp, cabou
        dfs(temp.front(), temp.front(), temp, v, matrix); // Tentar achar mais um ciclo
    }

    return ret;
}
