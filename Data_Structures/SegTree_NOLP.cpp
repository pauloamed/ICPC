#include<bits/stdc++.h>
using namespace std;

vector<int> vals; // vetor com valores inciais
int segt[3000]; // segtree

// pre processamento
int build(int l, int r, int node){
    if(l == r) return segt[node] = vals[l]; // atribuicao inicial
    int mid = (l + r)/2; // mid
    int left_build = build(l, mid, (node<<1)+1); // calc build da subarv esq
    int right_build = build(mid+1, r, (node<<1)+2);  // calc build da subarv dir
    return segt[node] = left_build + right_build; // MERGE
}

// update (pontual)
void update(int l, int r, int node, int i, int diff){
    if(i < l || i > r) return; // se fora do intervalo
    segt[node] = segt[node] + diff; // ta dentro, atualizo no OPERACAO
    if(l < r){ // nao eh uma folha ainda
        int mid = (l + r)/2; // mid
        update(l, mid, (node<<1)+1, i, diff); // update da subarv esq
        update(mid+1, r, (node<<1)+2, i, diff); // update da subarv dir
    }
}

// query (range)
int query(int l, int r, int node, int lq, int rq){
    if(rq < l || lq > r) // se tiver fora do intervalo definido pelo no
        return 0; // retorna elemento neutro
    else if(l >= lq && r <= rq) // se tiver incluso no intervalo def pelo no
        return segt[node]; // retorna valor no no
    else{
        int mid = (l + r)/2; // mid
        int left_query = query(l, mid, (node<<1)+1, lq, rq); // faz query da esq
        int right_query = query(mid+1, r, (node<<1)+2, lq, rq); // query da dir
        return left_query + right_query; // MERGE
    }
}

pair<int,int> find(int l, int r, int node, int lq, int rq, int x){
    if(segt[node].first <= x || r < lq || l > rq) return {-INF, -1};
    if(l == r) return segt[node];
    int mid = (l + r)/2; // mid
    auto ret = find(mid+1, r, (node<<1)+2, lq, rq, x); // find da subarv dir
    // cout << ret.first << endl;
    if(ret.first != -INF) return ret;
    else return find(l, mid, (node<<1)+1, lq, rq, x); // find da subarv esq
}

int main(){
    build(0, n-1, 0); // dar o build sempre antes de usar
    // valores inicais: l=0, r=n-1, node=0
}
