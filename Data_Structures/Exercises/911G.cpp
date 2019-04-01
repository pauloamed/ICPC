#include<bits/stdc++.h>
using namespace std;

#define MAXV 200010
#define MAXA 101

int segt[3*MAXV][MAXA];
int vals[MAXV];

vector<pair<int,int>> lp[3*MAXV];
int cont_lp[3*MAXV];
int last_seen_lp[3*MAXV][MAXA];

void maybe_updt_lazy(int l, int r, int node, int X=-1, int Y=-1){
    int x, y, temp;

    if(X == -1){
        temp = lp[node].size();
    }else{
        temp = max(last_seen_lp[node][X], last_seen_lp[node][Y]);
    }


    for(int i = cont_lp[node]; i < temp; ++i){
        x = lp[node][i].first;
        y = lp[node][i].second;
        segt[node][y] += segt[node][x];
        segt[node][x] = 0;
        if(l!=r){
            lp[(node<<1)+1].push_back(lp[node][i]);
            lp[(node<<1)+2].push_back(lp[node][i]);
        }

    }
    cont_lp[node] = max(cont_lp[node], temp);
}

int build(int l, int r, int node, int qual){
    if(l == r){
        if(vals[l] == qual) return segt[node][qual] = 1;
        else return segt[node][qual] = 0;
    }
    else{
        int mid = (l + r)/2;
        return segt[node][qual] = build(l, mid, (node<<1)+1, qual) +
                     build(mid+1, r, (node<<1)+2, qual);
    }
}

void update_range(int l, int r, int node, int lu, int ru, int x, int y){
    maybe_updt_lazy(l,r,node,x,y);

    if( lu > r || l > ru ) return; //totalmente fora, nao faz updt
    if(lu <= l && r <= ru){ // totalmente dentro, nao updt nos filhos
        segt[node][y] += segt[node][x];
        segt[node][x] = 0;
        if(l!=r){
            lp[(node<<1)+1].push_back({x,y});
            lp[(node<<1)+2].push_back({x,y});

            last_seen_lp[(node<<1)+1][x] = lp[(node<<1)+1].size();
            last_seen_lp[(node<<1)+1][y] = lp[(node<<1)+1].size();
            last_seen_lp[(node<<1)+2][x] = lp[(node<<1)+2].size();
            last_seen_lp[(node<<1)+2][y] = lp[(node<<1)+2].size();
        }
    }else{ //parcialmente dentro, nao faz lp nos filhos
        if(l==r){
            segt[node][y] += segt[node][x];
            segt[node][x] = 0;
        }else{
        int mid = (l + r)/2;
        update_range(l, mid, (node<<1)+1, lu, ru, x, y);
        update_range(mid+1, r, (node<<1)+2, lu, ru, x ,y);
        segt[node][y] = segt[(node<<1)+1][y] + segt[(node<<1)+2][y];
        segt[node][x] = segt[(node<<1)+1][x] + segt[(node<<1)+2][x];
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
    int n,m;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", &vals[i]);
    scanf("%d", &m);

    for(int i = 1; i <= 100; ++i) build(0,n-1,0,i);

    int l, r, x, y, temp;
    for(int i = 0; i < m; ++i){
        scanf("%d %d %d %d", &l, &r, &x, &y);
        if(x==y) continue;
        update_range(0,n-1,0,l-1,r-1,x,y);
    }


    int j;
    for(int i = 0; i < n; ++i){
        for(j = 1; j <= 100; ++j){
            temp = query(0,n-1,0,i,i,j);
            if(temp == 1) break;
        }
        printf("%d ", j);
    }printf("\n");

}
