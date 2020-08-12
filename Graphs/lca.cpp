#include<bits/stdc++.h>
using namespace std;

#define MAXV 100100
#define MAXLOG 17
#define INF 1e9

vector<int> v[MAXV]; // lista de adj

int st[MAXV][MAXLOG]; // sparse table (x,i) guardando ancestral de ordem 2^i de x
int lvl[MAXV]; // lvl=profundidade de cada no
bool vis_lca[MAXV]; // vis

void init_dfs(int x, int par){
    vis_lca[x] = true; // marcando vertice como visitado
    st[x][0] = par; // o ancestral de ordem 2^0 (1) de x eh o pai dele
    // se tiver pai valido (!= raiz), a prof aumenta em 1
    if(par != -1) lvl[x] = lvl[par] + 1;

    for(int i = 0; i < v[x].size(); ++i) // visitar todos adjacentes
        if(!vis_lca[v[x][i]]) init_dfs(v[x][i], x); // passo recursivo
}

void init_st(){
    // processo cada nivel de cada vertice
    for(int x = 1; x < MAXLOG; ++x) // 2^0 ja foi calculado, calculo pro resto
        for(int i = 0; i < MAXV; ++i){ // pra cada vertice
            // olho o ancestral 2^(i-1) do meu 2^(i-1), achando entao o meu 2^i
            st[i][x] = st[st[i][x-1]][x-1];
    }
}

void init(int root, int n){ // funcao init, raiz e #nos
    // botando que o pai da raiz eh -1, pode ser ela mesma tbm
    init_dfs(root, -1); // calcular os ancestrais imediatos
    init_st(); // init da sparse table
}


int lca(int x, int y){ // lca de x e y
    // cout << lvl[x] << " " << lvl[y] << endl;
    if(lvl[x] < lvl[y]) swap(x, y); // quero q x seja mais profundo q y

    int falta_subir = (lvl[x] - lvl[y]); // igualo as profundidades
    // simples representacao binaria de (falta_subir)
    for(int i = MAXLOG-1; i >= 0; --i){ // encontro os bits para representar o
        if((1<<i) <= falta_subir){ //      numero, dos mais signif. para os menos
            falta_subir -= (1<<i);
            x = st[x][i];
        }
    }

    if(x == y) return x; // ocorre quando x ta numa subarvore de y

    // acho o ponto abaixo do encontro (LCA)
    // se eu tentar subir 2^i e eles ja estiverem juntos, nao subo
    // tento entao subir 2^(i-1)
    for(int i = MAXLOG-1; i >= 0; --i){
        if(st[x][i] != st[y][i]){ // se continuarem diferentes, subo
            x = st[x][i]; // subindo pra x
            y = st[y][i]; // subindo pra y
        }
    }

    return st[x][0]; // retornando o ponto de encontro
}

int _dist(int a, int b){
    int x = lca(a, b);
    return (lvl[a] - lvl[x]) + (lvl[b] - lvl[x]);
}
