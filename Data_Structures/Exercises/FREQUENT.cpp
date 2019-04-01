#include<bits/stdc++.h>
using namespace std;

#define MAX 100010

vector<int> vals;
int segt[3*MAX];
map<int,pair<int,int>> mapa;

void build(int l, int r, int node){
    if(l == r){
        segt[node]=1;
    }else{
        int mid = (l + r)/2;
        build(l, mid, (node<<1)+1);
        build(mid+1, r, (node<<1)+2);

        segt[node] = max(segt[(node<<1)+1],segt[(node<<1)+2]);
        if(vals[mid]==vals[mid+1]){
            segt[node] = max(segt[node], min(r,mapa[vals[mid]].second)-max(l,mapa[vals[mid]].first)+1);
        }
    }
    // printf("%d %d %d\n", l, r, segt[node]);
}

int query(int l, int r, int node, int lq, int rq){
    // printf("%d %d %d %d\n", l,r,lq,rq);
    if(rq < l || lq > r) return 0;
    else if(l >= lq && r <= rq) return segt[node];
    else{
        int mid = (l + r)/2;
        int ql = query(l, mid, (node<<1)+1, lq, rq);
        int qr = query(mid+1, r, (node<<1)+2, lq, rq);
        if(vals[mid]==vals[mid+1]){
            // printf("%d %d %d %d %d %d\n", r,rq,mapa[vals[mid]].second,l,lq,mapa[vals[mid]].first);
            ql = max(ql, min(min(r,rq),mapa[vals[mid]].second)-max(max(l,lq),mapa[vals[mid]].first)+1);
        }
        // printf("%d %d %d\n", l,r, ans);
        return max(ql,qr);
    }
}

int main(){
    int n,q,a,b;
    while(scanf("%d %d", &n, &q)==2){
        a=0;
        for(int i(0); i < n; ++i){
            scanf("%d", &b);
            vals.push_back(b);

            if(i>0){
                if(b!=vals[i-1]){
                    mapa[vals[i-1]]=make_pair(a,i-1);
                    a=i;
                }
            }
        }
        mapa[vals.back()] = make_pair(a,vals.size()-1);

        // for(auto it(mapa.begin()); it!=mapa.end(); ++it){
        //     printf("%d %d %d\n", it->first, it->second.first, it->second.second);
        // }

        build(0,n-1,0);
        for(int i(0); i < q; ++i){
            scanf("%d %d", &a, &b);
            printf("%d\n", query(0,n-1,0,a-1,b-1));
        }
        vals.clear();
        mapa.clear();
    }
}
