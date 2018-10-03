#include<bits/stdc++.h>
using namespace std;

#define MAX 100010
#define int long long

int vals[MAX];
int segt[3*MAX];
int lp[3*MAX];

void maybe_updt_lazy(int l, int r, int node){
    if(lp[node] != 0){
        segt[node] += (r-l+1) * lp[node];
        if(l!=r){
            lp[(node<<1)+1] += lp[node];
            lp[(node<<1)+2] += lp[node];
        }
        lp[node] = 0;
    }
}

int build(int l, int r, int node){
    lp[node] = 0;

    if(l == r) return segt[node] = 0;
    int mid = (l + r)/2;
    segt[node] = build(l, mid, (node<<1)+1) +
                 build(mid+1, r, (node<<1)+2);
    return segt[node];
}

void update_range(int l, int r, int node, int lu, int ru, int diff){
    maybe_updt_lazy(l,r,node); // atualiza lp
    if( lu > r || l > ru ) return; //totalmente fora, nao faz updt
    if(lu <= l && r <= ru){ // totalmente dentro, nao updt nos filhos
        segt[node] += (r-l+1) * diff;
        if(l!=r){
            lp[(node<<1)+1] += diff;
            lp[(node<<1)+2] += diff;
        }
    }else{ //parcialmente dentro, nao faz lp nos filhos
        if(l==r) segt[node] += diff;
        else{
        int mid = (l + r)/2;
        update_range(l, mid, (node<<1)+1, lu, ru, diff);
        update_range(mid+1, r, (node<<1)+2, lu, ru, diff);
        segt[node] = segt[(node<<1)+1] + segt[(node<<1)+2];
        }
    }
}

int query(int l, int r, int node, int lq, int rq){
    maybe_updt_lazy(l,r,node);
    if(rq < l || lq > r) return 0;
    else if(l >= lq && r <= rq) return segt[node];
    else{
        int mid = (l + r)/2;
        return query(l, mid, (node<<1)+1, lq, rq) +
               query(mid+1, r, (node<<1)+2, lq, rq);
    }
}

main(){
    int T;
    cin >> T;
    while(T--){
        int n, c1;
        cin >> n >> c1;

        int a, b, c, d;

        build(0,n-1,0);
        for(int i(0); i < c1; ++i){
            cin >> a >> b >> c;
            if(a==0){
                cin >> d;
                update_range(0,n-1,0,b-1,c-1,d);
            }else{
                cout << query(0,n-1,0,b-1,c-1) << endl;
            }
        }
    }

}
