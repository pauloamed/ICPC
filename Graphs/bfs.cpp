#include<bits/stdc++.h>
using namespace std;

#define MAXN 100
bool visited[MAXN]; // Vetor de visitados
vector<size_t> v[MAXN]; // Lista de adjacencia


/*
COMPLEXIDADE TEMPO:
    CADA VERTICE EH VISITADO (O(n)), E TODOS SEUS ADJACENTES OLHADOS (O(m))
    O(n+m)
COMPLEXIDADE ESPACO:
    O(n) - VETOR DE VISITADOS

    - Menor caminho para grafos sem pesos
*/


void bfs_iter(){
    queue<size_t> q; // Fila da BFS
    size_t u = 0; // Vertice current
    q.push(u); // Dou inicio a fila

    while(!q.empty()){ // Enquanto nao estiver vazia
        u = q.front(); // Recuperando o proximo vertice
        visited[u] = true; // Marco-o como visitado
        q.pop(); // Retiro-o da fila

        for(size_t i = 0; i < v[u].size(); i++)  // Para cada adjacente do vertice,
            if(!visited[v[u][i]])   // Se nao foi visitado ainda,
                q.push(v[u][i]); // Visite
    }

}
