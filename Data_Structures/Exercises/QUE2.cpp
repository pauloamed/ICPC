#include<bits/stdc++.h>
using namespace std;

#define MAXN 100010

pair<int,int> vals[MAXN];
pair<int,int> segt[3*MAXN];
int lp[3*MAXN];

void maybe_updt_lazy(int l, int r, int node){
    if(lp[node] != 0){
        segt[node].first += lp[node];
        if(l!=r){
            lp[(node<<1)+1] += lp[node];
            lp[(node<<1)+2] += lp[node];
        }
        lp[node] = 0;
    }
}

pair<int,int> build(int l, int r, int node){
    lp[node] = 0;
    if(l == r) return segt[node] = {vals[l].first, l};
    int mid = (l + r)/2;
    segt[node] = min(build(l, mid, (node<<1)+1),
                 build(mid+1, r, (node<<1)+2));
    return segt[node];
}

void update_range(int l, int r, int node, int lu, int ru, int diff){
    maybe_updt_lazy(l,r,node); // atualiza lp
    if( lu > r || l > ru ) return; //totalmente fora, nao faz updt
    if(lu <= l && r <= ru){ // totalmente dentro, nao updt nos filhos
        segt[node].first += diff;
        if(l!=r){
            lp[(node<<1)+1] += diff;
            lp[(node<<1)+2] += diff;
        }
    }else{ //parcialmente dentro, nao faz lp nos filhos
        if(l==r) segt[node].first += diff;
        else{
        int mid = (l + r)/2;
        update_range(l, mid, (node<<1)+1, lu, ru, diff);
        update_range(mid+1, r, (node<<1)+2, lu, ru, diff);
        segt[node] = min(segt[(node<<1)+1], segt[(node<<1)+2]);
        }
    }
}

pair<int,int> query(int l, int r, int node, int lq, int rq){
    maybe_updt_lazy(l,r,node);
    if(rq < l || lq > r) return {MAXN,MAXN};
    else if(l >= lq && r <= rq) return segt[node];
    else{
        int mid = (l + r)/2;
        return min(query(l, mid, (node<<1)+1, lq, rq),
               query(mid+1, r, (node<<1)+2, lq, rq));
    }
}

bool cmp_(const pair<int,int> &a, const pair<int,int> &b){
    if(a.second == b.second) return a.first < b.first;
    return a.second < b.second;
}

int main(){
    int t, n, x;
    cin >> t;
    while(t--){
        cin >> n;


        for(int i = 0;i < n;++i){
            cin >> vals[i].second;
        }
        for(int i = 0;i < n;++i){
            cin >> vals[i].first;
        }
        sort(vals, vals+n, cmp_);
        build(0,n-1,0);


        pair<int,int> temp;
        for(int i = 0; i < n; ++i){
            temp = query(0, n-1, 0, 0,n-1);
            // cout << temp.first << " ";
            cout << vals[temp.second].second << " ";
            update_range(0,n-1,0,0,temp.second,-1);
            update_range(0,n-1,0,temp.second,temp.second,MAXN);
        }cout << endl;
    }
}
