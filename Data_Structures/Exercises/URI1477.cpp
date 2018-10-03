#include<bits/stdc++.h>
using namespace std;

#define MAX 100010

int segt[3*MAX][3];
int lp[3*MAX];

void maybe_updt_lazy(int l, int r, int node){
    lp[node] %= 3;
    while(lp[node]>0){
        swap(segt[node][0],segt[node][1]);
        swap(segt[node][0],segt[node][2]);
        if(l!=r){
            lp[(node<<1)+1]++;
            lp[(node<<1)+2]++;
        }
        lp[node]--;
    }
}

int build(int l, int r, int node, int qual){
    lp[node] = 0;
    if(l == r){
        if(qual==0){
            return segt[node][qual] = 1;
        }else{
            return segt[node][qual] = 0;
        }
    }
    else{
        int mid = (l + r)/2;
        segt[node][qual] = build(l, mid, (node<<1)+1, qual) +
                     build(mid+1, r, (node<<1)+2, qual);
        return segt[node][qual];
    }
}

void update_range(int l, int r, int node, int lu, int ru){
    maybe_updt_lazy(l,r,node); // atualiza lp
    if( lu > r || l > ru ) return; //totalmente fora, nao faz updt
    if(lu <= l && r <= ru){ // totalmente dentro, nao updt nos filhos
        swap(segt[node][0],segt[node][1]);
        swap(segt[node][0],segt[node][2]);
        if(l!=r){
            lp[(node<<1)+1]++;
            lp[(node<<1)+2]++;
        }
    }else{ //parcialmente dentro, nao faz lp nos filhos
        if(l==r){
            swap(segt[node][0],segt[node][1]);
            swap(segt[node][0],segt[node][2]);
        }else{
        int mid = (l + r)/2;
        update_range(l, mid, (node<<1)+1, lu, ru);
        update_range(mid+1, r, (node<<1)+2, lu, ru);

        segt[node][0] = segt[(node<<1)+1][0] + segt[(node<<1)+2][0];
        segt[node][1] = segt[(node<<1)+1][1] + segt[(node<<1)+2][1];
        segt[node][2] = segt[(node<<1)+1][2] + segt[(node<<1)+2][2];
        }
    }
}

int query(int l, int r, int node, int lq, int rq, int qual){
    maybe_updt_lazy(l,r,node);
    if(rq < l || lq > r) return 0;
    else if(l >= lq && r <= rq) return segt[node][qual];
    else{
        int mid = (l + r)/2;
        return query(l, mid, (node<<1)+1, lq, rq, qual) +
               query(mid+1, r, (node<<1)+2, lq, rq, qual);
    }
}


int main(){
    int N, M, a, b;
    char c;
    while(scanf("%d %d", &N, &M) == 2){
        build(0,N-1,0,0);
        build(0,N-1,0,1);
        build(0,N-1,0,2);
        while(M--){
            scanf(" %c %d %d", &c, &a, &b);
            if(c == 'C'){
                printf("%d %d %d\n", query(0,N-1,0,a-1,b-1,0),query(0,N-1,0,a-1,b-1,1),query(0,N-1,0,a-1,b-1,2));
            }else{
                update_range(0,N-1,0,a-1,b-1);
            }
        }
        cout << endl;
    }
}
