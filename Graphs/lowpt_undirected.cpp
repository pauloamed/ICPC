#include<bits/stdc++.h>
using namespace std;

#define MAXN 100000

vector<int> v[MAXN]; // lista de adjacencia

int lowpt[MAXN]; // vetor auxiliar com o lowpt de cada vertice
int lvl[MAXN]; // vetor auxiliar com o level de cada vertice


/*
 - O(m+n)
Componentes biconexas de um grafo nao direcionado
 - Numa DFS, podemos formar dois tipos de arestas:
     - Aresta da arvore: aresta conectando um vertice ja visitado a um ainda nao visitado
     - Aresta de retorno: aresta conectando um vertice ja visitado a um ja visitado. ARESTAS DE RETORNO CONECTA UM VERTICE A UM ANCESTRAL.
 - Lowpt(v) é igual ao vértice mais próximo da raiz da arvore de recursao (T) que pode
   ser alcançado a partir de v, caminhando-se em T para baixo através de zero ou mais
   arestas na árvore e, em seguida, para cima utilizando no máximo uma aresta de retorno.
 - Demarcador – vértice v com lowpt(v) = v ou w, sendo w pai de v em T.
 - Articulação – Vértice pai de um ou mais demarcadores.
*/

vector<int> temp;

void dfs(int x, int last){ // x: atual, adj que o invocou
    temp.push_back(x);
    lvl[x] = lvl[last] + 1; // calculando level do atual
    lowpt[x] = x; // nao ha arestas partindo de x (AINDA). logo, lowpt(x) = x
    for(int i = 0; i < v[x].size(); ++i){
        if(lvl[v[x][i]] == 0){ // se o vertice nao foi visitado ainda (aresta de arvore)
            dfs(v[x][i], x); // passo recursivo (calcula lvl)

            // ve se o lowpt de algum filho de x eh mais proximo da raiz pra
            // sobrescrever o lowpt atual de x (meio que uma PD aqui)
            if(lvl[lowpt[v[x][i]]] < lvl[lowpt[x]]) lowpt[x] = lowpt[v[x][i]];

            //checando se v[x][i] eh um demarcador -> x eh articulacao
            if(lowpt[v[x][i]] == v[x][i] || lowpt[v[x][i]] == x){
                printf("Mais uma comp biconexa\n");
                while(true){ // subarvore em questao: raiz em v[x][i]
                    printf("%d ", temp.back()); // toda vetice da subarvore eh do componente
                    if(temp.back() == x) break; // nao retiro a articulacao
                    else temp.pop_back(); // se nao eh a articulacao (subarvore propria), retiro
                }
                printf("\n");
            }
        }else{ // vertice ja foi visitado, aresta de retorno
            // se lvl adj por essa aresta de retorno eh melhor q o meu lowpt, att lowpt
            if(lvl[v[x][i]] < lvl[lowpt[x]]) lowpt[x] = v[x][i];
        }
    }
}

int main(){
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        // 1 indexado
        int a, b; cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }

    dfs(1, 0); // 1 indexado, pai eh valor nulo: 0

}
