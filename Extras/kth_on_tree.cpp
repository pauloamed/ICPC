// https://www.spoj.com/problems/COT/

#include <bits/stdc++.h>
 
using namespace std;

template<int MAXN>
struct PersSegtree{
  using ValType = int;

  ValType segt[64*MAXN];
  int l_ptr[64*MAXN], r_ptr[64*MAXN];
  int time2node[MAXN];
 
  int n;
  int next_node = 0;
  int next_time = 0;
 
  ValType NEUTRAL;

  int build_node(int l, int r, ValType val){
    segt[next_node] = val;
    l_ptr[next_node] = l;
    r_ptr[next_node] = r;
    return next_node++;
  }

  // ATTENTION
  ValType BinaryOp(ValType a, ValType b){
    return a + b;
  }
 
  void init(ValType neut, int sz, vector<ValType> *v=nullptr){
    n = sz;
    NEUTRAL = neut;
    time2node[next_time++] = build(0, n - 1, v);
  }

  int build(int l, int r, vector<ValType> *init_vals){
    if(l == r){
      return build_node(l, r, (init_vals? (*init_vals)[l] : NEUTRAL));
    }else{
      int mid = (l + r) / 2;
      int left_id = build(l, mid, init_vals);
      int right_id = build(mid + 1, r, init_vals);
      return build_node(left_id, right_id, BinaryOp(segt[left_id], segt[right_id]));
    }
  }
 
  ValType _rng_query(int l, int r, int node, int lq, int rq){
    if(rq < l || lq > r) return NEUTRAL;
    else if(l >= lq && r <= rq) return segt[node];
    else{
      int mid = (l + r) / 2;
      return BinaryOp(
        _rng_query(l, mid, l_ptr[node], lq, rq),
        _rng_query(mid+1, r, r_ptr[node], lq, rq)
      );
    }
  }
  
  ValType query(int lq,int rq, int time = -1){
    if(time == -1) time = next_time - 1;
    return _rng_query(0, n - 1, time2node[time], lq, rq);
  }
  
  int update(int pos, ValType x, bool inplace, int time = -1){
    if(time == -1) time = next_time - 1;
    int node = _update_range(0, n - 1, time2node[time], pos, x, inplace);
    if(inplace){
      time2node[time] = node;
      return time;
    }else{
      time2node[next_time] = node;
      return next_time++;
    }
  }

  int _update_range(int l, int r, int node, int pos, ValType val, bool inplace){
    if(pos > r || l > pos) return node;
    if(pos == r && pos == l){
      if(inplace){
        segt[node] = val; return node;
      }else return build_node(-1, -1, val);
    }else{
      int mid = (l + r)/2;
      int left_id = _update_range(l, mid, l_ptr[node], pos, val, inplace);
      int right_id = _update_range(mid+1, r, r_ptr[node], pos, val, inplace);
      ValType new_val = BinaryOp(segt[left_id], segt[right_id]);
      if(inplace){
        segt[node] = new_val; return node;
      }else return build_node(left_id, right_id, new_val);
    }
  }

  int kth(int k, int l, int r, vector<int> &pos, vector<int> &neg){
    if(l == r) return l;
    int tot_left = 0;
    for(auto x : pos) tot_left += segt[l_ptr[x]];
    for(auto x : neg) tot_left -= segt[l_ptr[x]];

    int mid = (l + r) / 2;
    if(tot_left >= k){
      for(auto &x : pos) x = l_ptr[x];
      for(auto &x : neg) x = l_ptr[x];
      return kth(k, l, mid, pos, neg);
    }else{
      for(auto &x : pos) x = r_ptr[x];
      for(auto &x : neg) x = r_ptr[x];
      return kth(k - tot_left, mid + 1, r, pos, neg);
    } 
  }
};


const int MAXV=2e5+10;
const int MAXLOG=20;

vector<int> v[MAXV];

namespace LCA{
  int st[MAXV][MAXLOG];
  int lvl[MAXV];

  void init_dfs(int x, int par){
    st[x][0] = par;
    if(par != -1) lvl[x] = lvl[par] + 1;
    for(auto y : v[x]) if(y != par) init_dfs(y, x);
  }

  void init_st(){
    for(int x = 1; x < MAXLOG; ++x){
      for(int i = 0; i < MAXV; ++i){
        if(st[i][x-1] == -1) st[i][x] = -1;
        else st[i][x] = st[st[i][x-1]][x-1];
      }
    }
  }

  void init(int root){
    init_dfs(root, -1); init_st();
  }

  int lca(int x, int y){
    if(lvl[x] < lvl[y]) swap(x, y); // x is deeper

    int falta_subir = (lvl[x] - lvl[y]);

    for(int i = MAXLOG-1; i >= 0; --i){
      if((1<<i) <= falta_subir){
        falta_subir -= (1<<i);
        x = st[x][i];
      }
    }

    if(x == y) return x;

    for(int i = MAXLOG-1; i >= 0; --i){
      if(st[x][i] != st[y][i]){
        x = st[x][i];
        y = st[y][i];
      }
    }
    return st[x][0];
  }
}



PersSegtree<MAXV> pers_seg;

vector<int> id2time, par, w;


void dfs(int x, int p){
  par[x] = p;
  int old_count = pers_seg.query(w[x], w[x], id2time[p]);
  id2time[x] = pers_seg.update(w[x], old_count + 1, false, id2time[p]);

  for(auto y : v[x]){
    if(y != p) dfs(y, x);
  }
}


int32_t main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n, q; cin >> n >> q;

  pers_seg.init(0, n*2);

  w = vector<int>(n + 1);
  id2time = vector<int>(n + 1);
  par = vector<int>(n + 1);

  for(int i = 1; i <= n; ++i) cin >> w[i];


  vector<int> vals_sorted;
  {
    vector<int> vals(w);
    sort(vals.begin(), vals.end());
    map<int,int> m;
    for(auto x : vals){
      if(m.count(x) == 0){
        m[x] = m.size();
        vals_sorted.push_back(x);
      }
    }
    for(auto &x : w) x = m[x];
  }

  for(int i = 1; i < n; ++i){
    int a, b; cin >> a >> b;
    v[a].push_back(b);
    v[b].push_back(a);
  }

  id2time[0] = 0;
  dfs(1, 0);

  LCA::init(1);

  while(q--){
    int u, v, k; cin >> u >> v >> k;
    int l = LCA::lca(u, v);

    vector<int> pos = {u, v};
    vector<int> neg = {l, par[l]};

    for(auto &x : pos) x = pers_seg.time2node[id2time[x]];
    for(auto &x : neg) x = pers_seg.time2node[id2time[x]];

    int kth_idx = pers_seg.kth(k, 0, pers_seg.n - 1, pos, neg);

    cout << vals_sorted[kth_idx] << "\n";
  }
}