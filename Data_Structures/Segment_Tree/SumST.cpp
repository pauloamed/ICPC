#include<bits/stdc++.h>
using namespace std;

vector<int> vals;
int segt[3000];

int build(int l, int r, int node){
    if(l == r){
        segt[node] = vals[l];
        return segt[node];
    }
    int mid = (l + r)/2;
    segt[node] = build(l, mid, (node<<1)+1) +
                 build(mid+1, r, (node<<1)+2);
    return segt[node];
}

void update(int l, int r, int node, int i, int diff){
    if(i < l || i > r) return;
    segt[node] += diff;
    if(l < r){
        int mid = (l + r)/2;
        update(l, mid, (node<<1)+1, i, diff);
        update(mid+1, r, (node<<1)+2, i, diff);
    }
}

void update_range(int l, int r, int node, int lu, int ru, int diff){
    if( lu > r || l > ru ) return;
    if(l < r){
        int mid = (l + r)/2;
        update_range(l, mid, (node<<1)+1, lu, ru, diff);
        update_range(mid+1, r, (node<<1)+2, lu, ru, diff);

        segt[node] = segt[(node<<1)+1] + segt[(node<<1)+2];
    }else{
        segt[node] += diff;
    }
}

int query(int l, int r, int node, int lq, int rq){
    // printf("l:%d r:%d node:%d lq:%d rq:%d\n", l,r,node,lq,rq);

    if(rq < l || lq > r) return 0;
    else if(l >= lq && r <= rq) return segt[node];
    else{
        int mid = (l + r)/2;
        return query(l, mid, (node<<1)+1, lq, rq) +
               query(mid+1, r, (node<<1)+2, lq, rq);
    }
}

int main(){
    int n, x;
    cin >> n;
    for(int i(0); i < n; ++i){
        cin >> x;
        vals.push_back(x);
    }
    build(0, n-1, 0);
    cout << query(0,n-1,0,0,n-1) << endl;
    cout << query(0,n-1,0,0,(n-1)/2) << endl;
    cout << query(0,n-1,0,(n-1)/2 + 1,n-1) << endl;

    update_range(0,n-1,0,1,1,100);

    cout << query(0,n-1,0,0,n-1) << endl;
    cout << query(0,n-1,0,0,(n-1)/2) << endl;
    cout << query(0,n-1,0,(n-1)/2 + 1,n-1) << endl;
}
