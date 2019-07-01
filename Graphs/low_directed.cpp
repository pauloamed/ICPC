#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000

/*
Dois vértices i e j estão fortemente conectados em um grafo direcionado G, se
existe caminho direcionado de i para j e de j para i em G.

PE: posicao de entrada  PS: posicao de saida
(v,w) é aresta da árvore ou avanço se e somente se PE(v) < PE(w)
(v,w) é aresta de retorno se e somente se PE(v) > PE(w) e PS(v) < PS(w)
(v,w) é aresta de cruzamento se e somente se PE(v) > PE(w) e PS(v) > PS(w)

low(v) = min{v, PE(z)}, onde z é o vértice de menor profundidade de entrada
localizado no mesmo componente conexo de v, que pode ser alcançado a partir de v,
através de zero ou mais arestas de arvore seguidas por, no máximo, uma aresta de
retorno ou cruzamento.


*/

size_t idx[MAXN]; // vetor com id de cada vertice (posicao de entrada)
size_t low[MAXN]; // vetor com lowpt
size_t root[MAXN]; // vetor indicando qual a raiz da arvore de cada vertice
vector<size_t> v[MAXN]; // lista de adjacencia
vector<size_t> temp; // vetor temporario para impressao, pilha de recursao

void dfs(int x, int _root, int &t){
    low[x] = idx[x] = t++; // att low e id
    root[x] = _root; // att raiz
    temp.push_back(x); // ad na pilha de recur

    for(int i = 0; i < v[x].size(); ++i){
        if(!idx[v[x][i]]){ // se o adj nao foi vis ainda (aresta de arvore)
            dfs(v[x][i], _root, t); // passo recursivo
            low[x] = min(low[x], low[v[x][i]]); // tento atualizar lowpt do atual
        }else{ // eh aresta de arvore, avanco ou cruzamento
            if(root[x] == root[v[x][i]] && idx[v[x][i]] < id[x]){
                // primeira condicao: estao na msm arvore
                // segunda condicao: eh aresta de retorno ou cruzamento
                low[x] = min(low[x], idx[v[x][i]]); // tenta atualizar lowpt de x
            }
        }
    }

    // printf("%d: %d %d\n", x, low[x], idx[x]);
    if(low[x] == idx[x]){ // x raiz de arvore (eh forte)
        printf("Componente fortemente conexa: ");
        while(true){
            printf("%d ", temp.back());
            if(temp.back() == x){ // se cheguei na arvore
                temp.pop_back(); break; // tiro raiz e paro de tirar
            }else temp.pop_back(); // vou consumindo a lista
        }
        printf("\n");
    }
}

int main(){
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int a, b; cin >> a >> b;
        v[a].push_back(b);
    }

    int t = 0;
    for(int i = 1; i <= n; ++i){
        if(!idx[i]) dfs(i, i, t); // se nao foi visitado ainda, visite
    }
}
