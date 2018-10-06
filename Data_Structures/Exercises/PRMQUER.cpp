#include<bits/stdc++.h>
using namespace std;

#define MAXN 100100
#define MAXP 10000010

bool nao_eh_primo[100000010];

int vals[MAXN];
int segt[3*MAXN];
int lp_vals[3*MAXN];

void sieve(){
    nao_eh_primo[1] = true;
    int j;
    for(int i = 2; i < MAXP; ++i){
        if(!nao_eh_primo[i]){
            j = i * 2;
            while(j < MAXP){
                nao_eh_primo[j] = true;
                j+=i;
            }
        }
    }

    for(int i = 10000001; i < 100000000; ++i){
        nao_eh_primo[i] = true;
    }
}


void maybe_updt_lazy(int l, int r, int node){
    if(lp_vals[node] != -1){
        segt[node] = (r-l+1) * (1 - nao_eh_primo[lp_vals[node]]);
        if(l!=r){
            lp_vals[(node<<1)+1] = lp_vals[node];
            lp_vals[(node<<1)+2] = lp_vals[node];
        }else{
            vals[l] = lp_vals[node];
        }
        lp_vals[node] = -1;
    }
}

int build(int l, int r, int node){
    lp_vals[node] = -1;
    if(l == r) return segt[node] = 1-nao_eh_primo[vals[l]];
    else{
        int mid = (l + r)/2;
        segt[node] = build(l, mid, (node<<1)+1) +
                     build(mid+1, r, (node<<1)+2);
    }return segt[node];
}

void update_range(int l, int r, int node, int lu, int ru, int val){
    int diff = 1 - nao_eh_primo[val];

    maybe_updt_lazy(l,r,node); // atualiza lp
    if( lu > r || l > ru ) return; //totalmente fora, nao faz updt
    if(lu <= l && r <= ru){ // totalmente dentro, nao updt nos filhos
        segt[node] = (r-l+1) * diff;
        if(l!=r){
            lp_vals[(node<<1)+1] = val;
            lp_vals[(node<<1)+2] = val;
        }else{
            vals[l] = val;
        }
    }else{ //parcialmente dentro, nao faz lp nos filhos
        if(l==r){
            segt[node] = diff;
            vals[l] = val;
        }else{
            int mid = (l + r)/2;
            update_range(l, mid, (node<<1)+1, lu, ru, val);
            update_range(mid+1, r, (node<<1)+2, lu, ru, val);
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

int query_val(int l, int r, int node, int i){
    maybe_updt_lazy(l,r,node);
    if(l == r) return vals[l];
    else{
        int mid = (l + r)/2;
        if(i > mid) return query_val(mid+1, r, (node<<1)+2, i);
        else return query_val(l, mid, (node<<1)+1, i);
    }
}

int main(){
    sieve();

    int N, Q, a, b, d;
    char c;

    scanf("%d %d", &N, &Q);

    for(int i = 0; i < N; ++i){
        scanf("%d", &vals[i]);
    }

    build(0,N-1,0);

    int temp, temp2, temp3;
    for(int i = 0; i < Q; ++i){
        scanf(" %c %d %d", &c, &a, &b);
        if(c == 'A'){
            b--;
            temp = query_val(0,N-1,0,b);
            update_range(0,N-1,0,b,b,temp+a);
        }else if(c == 'R'){
            scanf("%d", &d);
            b--;d--;
            update_range(0,N-1,0,b,d,a);
        }else{
            printf("%d\n", query(0,N-1,0,--a,--b));
        }
    }
}
