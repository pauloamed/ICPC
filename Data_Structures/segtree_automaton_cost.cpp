#include<bits/stdc++.h>
using namespace std;

#define MAXN 200010
#define MAXV 5
#define INF 1e9

struct Node{
  int cost[MAXV][MAXV];
  
  void init_inf(){
    for(int i = 0; i < MAXV; ++i) for(int j = 0; j < MAXV; ++j) cost[i][j] = INF;
  }

  void init_id(){
    for(int i = 0; i < MAXV; ++i) cost[i][i] = 0;
  }

  Node(bool flag=true){ 
    init_inf();
    if(flag) init_id();
  }

  Node(int x){
    init_inf(); init_id();
    if(x == 2){
      cost[0][0] = 1;
      cost[0][1] = 0;
    }else if(x == 0){
      cost[1][1] = 1;
      cost[1][2] = 0;
    }else if(x == 1){
      cost[2][2] = 1;
      cost[2][3] = 0;
    }else if(x == 6){
      cost[3][3] = 1;
      cost[4][4] = 1;
    }else if(x == 7){
      cost[3][3] = 1;
      cost[3][4] = 0;
    }
  }
};

Node mergeFunc(Node x, Node y){
  Node ret(false);
  for(int i = 0; i < MAXV; ++i){
    for(int k = i; k < MAXV; ++k){
      for(int j = k; j < MAXV; ++j){
        ret.cost[i][j] = min(ret.cost[i][j], x.cost[i][k] + y.cost[k][j]);
      }
    }
  }
  return ret;
}

void mergeFunc2(Node &ret, Node &x, Node &y){
  ret.init_inf();
  for(int i = 0; i < MAXV; ++i){
    for(int k = i; k < MAXV; ++k){
      for(int j = k; j < MAXV; ++j){
        ret.cost[i][j] = min(ret.cost[i][j], x.cost[i][k] + y.cost[k][j]);
      }
    }
  }
}

template<int N, class T, T (*BinaryOp)(T,T)>
struct SegTreeLazy{
  T segt[4*N]; // segtree
  T lp[4*N]; // lazy prop
  
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
    if(l == r){
    segt[node] = val; // ATTENTION
    }
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
      mergeFunc2(segt[node], segt[(node<<1)+1], segt[(node<<1)+2]);
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
      mergeFunc2(segt[node], segt[(node<<1)+1], segt[(node<<1)+2]);
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



SegTreeLazy<MAXN, Node, mergeFunc> segtree;
int main(){
  cin.tie(NULL)->sync_with_stdio(false);
  int n, q; cin >> n >> q;
  string s; cin >> s;

  vector<Node> v;
  for(auto c : s) v.push_back(Node(c - '0'));

  segtree.init(n, Node(), Node(), &v);

  // cout << segtree.query(0 ,n - 1).abc << endl;
  // return 0;

  while(q--){
    int l, r; cin >> l >> r; r--, l--;
    int x = segtree.query(l, r).cost[0][4];
    if(x == INF) x = -1;
    cout << x << "\n";
  }
}