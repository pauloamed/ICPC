#include<bits/stdc++.h>
using namespace std;

#define MAX 210000
#define INF 1000000000
#define int long long

int vals[MAX];
int segt[3*MAX];
int lp[3*MAX];

void maybe_updt_lazy(int l, int r, int node){
    if(lp[node] != 0){
        segt[node] += lp[node];
        if(l!=r){
            lp[(node<<1)+1] += lp[node];
            lp[(node<<1)+2] += lp[node];
        }
        lp[node] = 0;
    }
}

int build(int l, int r, int node){
    lp[node] = 0;
    if(l == r){
        return segt[node] = vals[l];
    }
    int mid = (l + r)/2;
    return segt[node] = min(build(l, mid, (node<<1)+1),build(mid+1, r, (node<<1)+2));
}


void update_range(int l, int r, int node, int lu, int ru, int diff){
    maybe_updt_lazy(l,r,node); // atualiza lp
    if( lu > r || l > ru ) return; //totalmente fora, nao faz updt
    if(lu <= l && r <= ru){ // totalmente dentro, nao updt nos filhos
        segt[node] += diff;
        if(l!=r){
            lp[(node<<1)+1] += diff;
            lp[(node<<1)+2] += diff;
        }
    }else{ //parcialmente dentro, nao faz lp nos filhos
        if(l==r){
            segt[node] += diff;
        }else{
        int mid = (l + r)/2;
        update_range(l, mid, (node<<1)+1, lu, ru, diff);
        update_range(mid+1, r, (node<<1)+2, lu, ru, diff);
        segt[node] = min(segt[(node<<1)+1],segt[(node<<1)+2]);
        }
    }
}

int query(int l, int r, int node, int lq, int rq){
    maybe_updt_lazy(l,r,node); // atualiza lp
    if(rq < l || lq > r) return INF;
    else if(l >= lq && r <= rq) return segt[node];
    else{
        int mid = (l + r)/2;
        return min(query(l, mid, (node<<1)+1, lq, rq),query(mid+1, r, (node<<1)+2, lq, rq));
    }
}

main(){
    int N, a, b, c, Q, temp1, temp2;
    scanf("%lld", &N);

    for(int i = 0; i < N; ++i){
        scanf("%lld", &vals[i]);
    }

    build(0,N-1,0);

    scanf("%lld", &Q);
    char x;
    for(int i = 0; i < Q; ++i){
        scanf("%lld %lld", &a, &b);
        scanf("%c", &x);
        if(x == ' '){
            scanf("%lld", &c);
            if(a > b){
                update_range(0,N-1,0,a,N-1,c);
                update_range(0,N-1,0,0,b,c);
            }else{
                update_range(0,N-1,0,a,b,c);
            }
        }else if(x == '\n'){
            if(a > b){
                temp1 = query(0,N-1,0,a,N-1);
                temp2 = query(0,N-1,0,0,b);
                printf("%lld\n", min(temp1,temp2));
            }else{
                printf("%lld\n", query(0,N-1,0,a,b));
            }

            // cout <<"c: " << c << endl;

        }else{
            cout << "CILADA\n";
        }
    }

}
