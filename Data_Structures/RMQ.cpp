#include<bits/stdc++.h>
using namespace std;

vector<int> vals;
int segt[3000];

int build(int l, int r, int node){
    if(l == r){
        segt[node] = l;
        return segt[node];
    }
    int mid = (l + r)/2;
    int lc = build(l, mid, (node<<1)+1);
    int rc = build(mid+1, r, (node<<1)+2);
    if(vals[lc] < vals[rc]) segt[node] = lc;
    else segt[node] = rc;
    return segt[node];
}

void update(int l, int r, int node, int i, int new_val){
    if(i < l || i > r) return;
    if(l != r){
        int mid = (l + r)/2;
        update(l, mid, (node<<1)+1, i, new_val);
        update(mid+1, r, (node<<1)+2, i, new_val);

        int lc = segt[(node<<1)+1];
        int rc = segt[(node<<1)+2];

        if(vals[lc] < vals[rc]) segt[node] = lc;
        else segt[node] = rc;
    }else{
        //segt[i] = ?
        vals[i] = new_val;
    }
}

int query(int l, int r, int node, int lq, int rq){
    // printf("l:%d r:%d node:%d lq:%d rq:%d\n", l,r,node,lq,rq);
    if(rq < l || lq > r) return -1;
    else if(l >= lq && r <= rq) return segt[node];
    else{
        int mid = (l + r)/2;
        int lc = query(l, mid, (node<<1)+1, lq, rq);
        int rc = query(mid+1, r, (node<<1)+2, lq, rq);

        if(lc == -1) return rc;
        if(rc == -1) return lc;

        if(vals[lc] < vals[rc]) return lc;
        else return rc;
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

    update(0,n-1,0,0,-100);

    cout << query(0,n-1,0,0,n-1) << endl;
    cout << query(0,n-1,0,0,(n-1)/2) << endl;
    cout << query(0,n-1,0,(n-1)/2 + 1,n-1) << endl;
}
