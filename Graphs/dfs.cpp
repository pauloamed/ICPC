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
    O(n) - OCORRE NUM GRAFO LINHA, OLHO TODO MUNDO + VETOR DE VISITADOS
*/


void dfs_recur(size_t x){
    visited[x] = true; // Marca vertice como visitado

    for(size_t i = 0; i < v[x].size(); i++) // Para cada adjacente do vertice,
        if(!visited[v[x][i]])  // Se nao foi visitado ainda,
            dfs_recur(v[x][i]); // Visite

}

void dfs_iter(){
    stack<size_t> s; // Pilha de recursao
    size_t u = 0; // Vertice current
    s.push(u); // Adiciono o vertice inicial a pilha de recursao
    do{
        u = s.top(); // Recupero o vertice atual da recursao
        visited[u] = true; // Marco-o como visitado
        s.pop(); // Retiro-o da pilha de recursao

        for(size_t i = 0; i < v[u].size(); i++)  // Para cada adjacente do vertice,
            if(!visited[v[u][i]])   // Se nao foi visitado ainda,
                s.push(v[u][i]); // Visite

    }while(!s.empty()) // Enquanto tiver alguem p ser visitado

}
