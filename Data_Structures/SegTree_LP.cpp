#include<bits/stdc++.h>
using namespace std;

#define MAX 1000

int vals[MAX]; // vetor com valores inciais
int segt[3*MAX]; // segtree
int lp[3*MAX]; // lazy prop

void maybe_updt_lazy(int l, int r, int node){
    if(lp[node] != 0){ // se a LP nao estiver inativa (espefic. da OPERACAO)
        segt[node] = segt[node] + (r-l+1) * lp[node]; // atualizo no atual (OPERACAO)
        if(l!=r){ // se tiver filho
            lp[(node<<1)+1] = lp[(node<<1)+1] + lp[node]; // atualizo LP dos filhos OPERACAO
            lp[(node<<1)+2] = lp[(node<<1)+2] + lp[node]; // atualizo LP dos filhos OPERACAO
        }
        lp[node] = 0; // deixo o estado atual como inativo
    }
}


int build(int l, int r, int node){
    lp[node] = 0; // init lazy
    if(l == r) return segt[node] = vals[l]; // atribuicao inicial
    int mid = (l + r)/2; // mid
    int left_build = build(l, mid, (node<<1)+1); // calc build da subarv esq
    int right_build = build(mid+1, r, (node<<1)+2);  // calc build da subarv dir
    return segt[node] = left_build + right_build; // MERGE
}

void update_range(int l, int r, int node, int lu, int ru, int diff){
    maybe_updt_lazy(l,r,node); // atualiza lp
    if( lu > r || l > ru ) return; //totalmente fora, nao faz updt
    if(lu <= l && r <= ru){ // totalmente dentro, nao precisa updt nos filhos
        segt[node] = segt[node] + (r-l+1) * diff; // especifico da OPERACAO
        if(l!=r){ // se tiver fiho
            lp[(node<<1)+1] = lp[(node<<1)+1] + diff; // atualiza lp OPERACAO
            lp[(node<<1)+2] = lp[(node<<1)+2] + diff; // atualiza lp OPERACAO
        }
    }else{ //parcialmente dentro, nao faz lp nos filhos
        int mid = (l + r)/2; // mid
        int left_query = query(l, mid, (node<<1)+1, lq, rq); // faz query da esq
        int right_query = query(mid+1, r, (node<<1)+2, lq, rq); // query da dir
        return left_query + right_query; // MERGE
    }
}

// query (range)
int query(int l, int r, int node, int lq, int rq){
    maybe_updt_lazy(l,r,node); // checar se precisa atualizar por lazy
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

int main(){
    build(0, n-1, 0); // dar o build sempre antes de usar
    // valores inicais: l=0, r=n-1, node=0
}
