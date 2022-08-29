// https://cses.fi/problemset/task/1741
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200000
#define INF LONG_LONG_MAX
#define int long long

struct Node{
  int cnt_min, sum_min;

  Node():cnt_min(INF), sum_min(0){}
  Node(int cm, int sm):cnt_min(cm), sum_min(sm){}

  void add(int x){
    cnt_min += x;
  }
};

Node merge(const Node &a, const Node &b){
  if(a.cnt_min == b.cnt_min){
    return Node(a.cnt_min, a.sum_min + b.sum_min);
  }else if(a.cnt_min < b.cnt_min){
    return a;
  }else return b;
}

void merge(Node &c, const Node &a, const Node &b){
  if(a.cnt_min == b.cnt_min){
    c = Node(a.cnt_min, a.sum_min + b.sum_min);
  }else if(a.cnt_min < b.cnt_min){
    c = a;
  }else c = b;
}


template<int N>
struct SegTreeRect{
  Node segt[4*N]; // segtree
  Node NEUTRAL_VAL;
  
  int lp[4*N]; // lazy prop
  int NEUTRAL_LP;
  
  int n;
  SegTreeRect(){}
  
  
  void init(int _n, Node neutralVal, int neutralLp, vector<Node>* vals=NULL){
    n = _n;
    NEUTRAL_VAL = neutralVal;
    NEUTRAL_LP = neutralLp;
    build(0, n - 1, 0, vals);
  }
  
  void lazyProp(int node, int val, int l, int r){
    segt[node].add(val); // ATTENTION
    if(l != r){
      lp[(node<<1)+1] += val;  // ATTENTION
      lp[(node<<1)+2] += val;  // ATTENTION
    }
  }
  
  
  void maybeUpdtLazy(int l, int r, int node){
    if(lp[node] != NEUTRAL_LP){
      lazyProp(node, lp[node], l, r);
      lp[node] = NEUTRAL_LP;
    }
  }
  
  
  void build(int l, int r, int node, vector<Node> *initVals){
    lp[node] = NEUTRAL_LP;
    if(l == r){
      if(initVals) segt[node] = (*initVals)[l];
      else segt[node] = NEUTRAL_VAL;
    }else{
      int mid = (l + r)/2;
      build(l, mid, (node<<1) + 1, initVals);
      build(mid + 1, r, (node<<1) + 2, initVals);
      merge(segt[node], segt[(node<<1)+1], segt[(node<<1)+2]);
    }
  }
  
  void _updateRange(int l, int r, int node, int lu, int ru, int val){
    maybeUpdtLazy(l,r,node);
    if(lu > r || l > ru) return;
    if(lu <= l && r <= ru){
      lazyProp(node, val, l, r);
    }else{
      int mid = (l + r)/2;
      _updateRange(l, mid, (node<<1)+1, lu, ru, val);
      _updateRange(mid+1, r, (node<<1)+2, lu, ru, val);
      merge(segt[node], segt[(node<<1)+1], segt[(node<<1)+2]);
    }
  }
  
  void update(int lu, int ru, int val){
    _updateRange(0, n - 1, 0, lu, ru, val);
  }
  
  
  Node _queryRange(int l, int r, int node, int lq, int rq){
    maybeUpdtLazy(l, r, node);
    if(rq < l || lq > r) return NEUTRAL_VAL;
    else if(l >= lq && r <= rq) return segt[node];
    else{
      int mid = (l + r)/2; // mid
      return merge(
        _queryRange(l, mid, (node<<1) + 1, lq, rq),
        _queryRange(mid+1, r, (node<<1) + 2, lq, rq)
      );
    }
  }
  
  Node query(int lq, int rq){
    return _queryRange(0, n - 1, 0, lq, rq);
  }
};

SegTreeRect<MAXN> segtree;
int32_t main(){
  int n; cin >> n;
  map<int, vector<pair<int,int>>> adds, removes;
  vector<int> y_vals, x_vals;

  for(int i = 0; i < n; ++i){
    int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
    adds[x1].push_back({y1, y2});
    removes[x2].push_back({y1, y2});

    y_vals.push_back(y1);
    y_vals.push_back(y2);
    x_vals.push_back(x1);
    x_vals.push_back(x2);
  }

  sort(y_vals.begin(), y_vals.end());
  sort(x_vals.begin(), x_vals.end());
  y_vals.resize(unique(y_vals.begin(), y_vals.end()) - y_vals.begin());
  x_vals.resize(unique(x_vals.begin(), x_vals.end()) - x_vals.begin());

  int nn = y_vals.size();
  map<int,int> coord2segsize;
  for(int i = 0; i < nn; ++i){
    if(i < nn - 1){
      coord2segsize[y_vals[i]] = y_vals[i + 1] - y_vals[i];
    }else{
      coord2segsize[y_vals[i]] = 0;
    }
  }

  vector<Node> init_nodes;
  int sum_all = 0;
  for(int i = 0; i < y_vals.size(); ++i){
    // cout << y_vals[i] << " " << coord2segsize[y_vals[i]] << endl;
    init_nodes.push_back(Node(0, coord2segsize[y_vals[i]]));
    sum_all += coord2segsize[y_vals[i]];
  }

  segtree.init(nn, Node(), 0, &init_nodes);

  // cout << "-1\n";
  // for(int j = 0; j < nn - 1; ++j){
  //   cout << segtree.query(j, j).sum_min << " " << segtree.query(j, j).cnt_min << ", ";
  // }cout << endl;

  int ans = 0;
  int last = 0;
  for(int i = 0; i < x_vals.size(); ++i){
    int curr_pos = x_vals[i];

    // computes
    Node x = segtree.query(0, nn - 1);
    if(x.cnt_min == 0){
      ans += (sum_all - x.sum_min) * (curr_pos - last);
    }
    
    // adds
    for(auto [a, b] : adds[curr_pos]){
      a = lower_bound(y_vals.begin(), y_vals.end(), a) - y_vals.begin();
      b = lower_bound(y_vals.begin(), y_vals.end(), b) - y_vals.begin();
      segtree.update(a, b - 1, 1);
      // cout << a << " " << b << "\n";
    }
    // removes
    for(auto [a, b] : removes[curr_pos]){
      a = lower_bound(y_vals.begin(), y_vals.end(), a) - y_vals.begin();
      b = lower_bound(y_vals.begin(), y_vals.end(), b) - y_vals.begin();
      segtree.update(a, b - 1, -1);
    }

    last = curr_pos;
  }
  cout << ans << endl;
  
}