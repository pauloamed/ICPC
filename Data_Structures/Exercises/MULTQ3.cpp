#include<bits/stdc++.h>
using namespace std;

#define MAX 110000

// A B C
// 0 2
// C B A
// 1 2
// C A B

int vals[MAX];
int segt[3*MAX][3];
int lp[3*MAX];

void maybe_updt_lazy(int l, int r, int node){
    if(lp[node] != 0){
        lp[node] %= 3;
        if(l!=r){
            lp[(node<<1)+1] += lp[node];
            lp[(node<<1)+2] += lp[node];
        }
        while( --lp[node] >= 0 ){
            swap(segt[node][0],segt[node][2]);
            swap(segt[node][1],segt[node][2]);
        }
        lp[node] = 0;
    }
}

void build(int l, int r, int node){
    lp[node] = 0;
    if(l == r){
        segt[node][1] = segt[node][2] = 0;
        segt[node][0] = 1;
    }
    else{
        int mid = (l + r)/2;

        build(l, mid, (node<<1)+1);
        build(mid+1, r, (node<<1)+2);

        segt[node][0] = segt[(node<<1)+1][0] + segt[(node<<1)+2][0];
        segt[node][1] = segt[(node<<1)+1][1] + segt[(node<<1)+2][1];
        segt[node][2] = segt[(node<<1)+1][2] + segt[(node<<1)+2][2];
    }
}

void update_range(int l, int r, int node, int lu, int ru){
    maybe_updt_lazy(l,r,node); // atualiza lp
    if( lu > r || l > ru ) return; //totalmente fora, nao faz updt
    if(lu <= l && r <= ru){ // totalmente dentro, nao updt nos filhos
        if(l!=r){
            lp[(node<<1)+1]++;
            lp[(node<<1)+2]++;
        }
        swap(segt[node][0],segt[node][2]);
        swap(segt[node][1],segt[node][2]);

    }else{ //parcialmente dentro, nao faz lp nos filhos
        if(l==r){
            swap(segt[node][0],segt[node][2]);
            swap(segt[node][1],segt[node][2]);
        }
        else{
        int mid = (l + r)/2;
        update_range(l, mid, (node<<1)+1, lu, ru);
        update_range(mid+1, r, (node<<1)+2, lu, ru);

        segt[node][0] = segt[(node<<1)+1][0] + segt[(node<<1)+2][0];
        segt[node][1] = segt[(node<<1)+1][1] + segt[(node<<1)+2][1];
        segt[node][2] = segt[(node<<1)+1][2] + segt[(node<<1)+2][2];
        }
    }
}

int query(int l, int r, int node, int lq, int rq){
    maybe_updt_lazy(l,r,node);
    if(rq < l || lq > r) return 0;
    else if(l >= lq && r <= rq) return segt[node][0];
    else{
        int mid = (l + r)/2;
        return query(l, mid, (node<<1)+1, lq, rq) +
               query(mid+1, r, (node<<1)+2, lq, rq);
    }
}

int main(){
    int N, Q, a, b, c;
    scanf("%d %d", &N, &Q);
    build(0,N-1,0);

    for(int i = 0; i < Q; ++i){
        scanf("%d %d %d", &a, &b, &c);
        if(a == 0){
            update_range(0,N-1,0,b,c);
        }else{
            printf("%d\n", query(0,N-1,0,b,c));
        }
    }


}
