#include<bits/stdc++.h>
using namespace std;


template<int MAXN, class T, T (*BinaryOp)(T,T)>
struct SegTreeLazy{
  T segt[3*MAXN]; // segtree
  T lp[3*MAXN]; // lazy prop
  
  T NEUTRAL_LP;
  T NEUTRAL_VAL;
  int n;
  
  
  void init(int _n, T neutralVal, T neutralLp, vector<T>* vals=NULL){
    n = _n;
    NEUTRAL_VAL = neutralVal;
    NEUTRAL_LP = neutralLp;
    build(0, n - 1, 0, vals);
  }
  
  void lazyProp(int node, T val, int l, int r){
    assert(l == r);
    // if(l == r){
    segt[node] = val; // ATTENTION
    // }
    // if(l != r){
    //     lp[(node<<1)+1] = val;  // ATTENTION
    //     lp[(node<<1)+2] = val;  // ATTENTION
    // }
  }
  
  
  void maybeUpdtLazy(int l, int r, int node){
    if(lp[node] != NEUTRAL_LP){
      lazyProp(node, lp[node], l, r);
      lp[node] = NEUTRAL_LP;
    }
  }
  
  
  void build(int l, int r, int node, vector<T> *initVals){
    lp[node] = NEUTRAL_LP;
    if(l == r){
      if(initVals) segt[node] = (*initVals)[l];
      else segt[node] = NEUTRAL_VAL;
    }else{
      int mid = (l + r)/2;
      build(l, mid, (node<<1) + 1, initVals);
      build(mid + 1, r, (node<<1) + 2, initVals);
      segt[node] = BinaryOp(segt[(node<<1)+1], segt[(node<<1)+2]);
    }
  }
  
  void _updateRange(int l, int r, int node, int lu, int ru, T val){
    // maybeUpdtLazy(l,r,node);
    if(lu > r || l > ru) return;
    if(lu <= l && r <= ru){
      lazyProp(node, val, l, r);
    }else{
      int mid = (l + r)/2;
      _updateRange(l, mid, (node<<1)+1, lu, ru, val);
      _updateRange(mid+1, r, (node<<1)+2, lu, ru, val);
      segt[node] = BinaryOp(segt[(node<<1)+1], segt[(node<<1)+2]);
    }
  }
  
  void update(int lu, int ru, T val){
    _updateRange(0, n - 1, 0, lu, ru, val);
  }
  
  
  T _queryRange(int l, int r, int node, int lq, int rq){
    // maybeUpdtLazy(l, r, node);
    if(rq < l || lq > r) return NEUTRAL_VAL;
    else if(l >= lq && r <= rq) return segt[node];
    else{
      int mid = (l + r)/2; // mid
      return BinaryOp(
        _queryRange(l, mid, (node<<1) + 1, lq, rq),
        _queryRange(mid+1, r, (node<<1) + 2, lq, rq)
      );
    }
  }
  
  T query(int lq, int rq){
    return _queryRange(0, n - 1, 0, lq, rq);
  }
};

pair<int,int> mergeFunc(pair<int,int> a, pair<int,int> b){
  if(a.first == b.first){
    return make_pair(a.first, b.second + a.second);
  }else{
    if(b.first < a.first) return b;
    else return a;
  }
}

int main(){
  SegTreeLazy<100000, pair<int,int>, mergeFunc> segtree;
  int n, q; cin >> n >> q;
  vector<pair<int,int>> v(n);
  for(auto &x : v){
    cin >> x.first;
    x.second = 1;
  }
  segtree.init(n, {INT_MAX, 0}, {0, 0}, &v);
  while(q--){
    int a, b, c; cin >> a >> b >> c;
    if(a == 1){
      segtree.update(b, b, make_pair(c, 1));
    }else{
      auto x = segtree.query(b, c - 1);
      cout << x.first << " " << x.second << endl;
    }
  }
}
