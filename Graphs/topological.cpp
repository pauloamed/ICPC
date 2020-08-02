#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000

vector<size_t> ts; // Lista com respostas
vector<size_t> v[MAXN]; // Lista de adj
bool perm[MAXN]; // Vetor temporario para marcar vertices permanentemente vis
bool temp[MAXN]; // Vetor temporario para marcar vertices temporariamente vis

/*
Ordenacao topoligica com DFS (O(m+n))
 - Se v eh ancestral de u, v aparece depois na ordenacao topolocia (so inverter se
  precisar do contrario)

 - Dada uma aresta (v,w)
 - Aresta de arvore: v é vis antes de w na busca e w estava desmarcado  (perm(w) = temp(w) = false)
 - Aresta de avanco: v é vis antes de w na busca e w ja estava marcado (perm(w) = true, temp(w) = false)
 - Aresta de retorno: w ja foi vis na busca e ta sendo percorrida uma subarvore de w (perm(w) = false, temp(w) = true)
 - Aresta de cruzamento: w ja foi vis na busca e w ja foi marcado (perm(w) = true, temp(w) = false)
 Aresta de avanco e de cruzamento nao sao distiguindas classe aqui

*/

bool loop(int x){
    if(perm[x]) return false; // Visitando novamente um vertice, mas nao na sua subarvore
    if(temp[x]) return true; // Se temp[x] ta ativo, estou numa subarvore de temp[x]. Ciclo

    if(v[x].size() > 0) temp[x] = true; // Se tem filho, ponho x na pilha de recursao

    bool ans = false; // Retorno se tem ciclo
    for(size_t i = 0; i < v[x].size(); i++)
        ans |= loop(v[x][i]; // Checo se da em loop

    temp[x] = false; // Tiro x da pilha de recursao
    ts.push_back(x); // Adiciono x na ordenacao topologica (isso so eh feito depois que todos seus filhos
    // ja foram checados)
    perm[x] = true; // Acabando de visitar toda subarvore do vertice, ele fica vis perm
    return ans;
}

int main(){
    size_t n,m;
    cin >> n >> m;

    // Init
    for(int i = 0; i < n; i++) perm[i] = temp[i] = false;

    // Read
    for(int i = 0; i < m; i++){
        size_t x,y; scanf("%lu %lu", &x, &y);
        v[x].push_back(y);
    }

    // Chama pra cada possivel raiz, checando se tem ciclo
    for(int i = 0; i < n; i++){
        if(!perm[i]) if(loop(i)) printf("Tem ciclo\n");
    }

    // Imprime a ordenacao
    for(int i = 0; i < ts.size(); i++){
        printf("%lu ", ts[i]);
    } cout << '\n';
}
