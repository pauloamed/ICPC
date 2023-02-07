#include<bits/stdc++.h>
using namespace std;

struct Node{
  int x;
  Node(){x = 0;}
  Node(int y){x = y;}
  Node operator+(const Node n){
    Node ret;
    ret.x = x + n.x;
    return ret;
  }
};

template<int MAXN, int MAXQ> struct PersSegtree{
  const static int MAX = 4 * MAXN + 25 * MAXQ;
  Node segt[MAX];
  int l_ptr[MAX], r_ptr[MAX];
  int time2node[MAX];
 
  int n;
  int next_node = 0;
  int next_time = 0;
 
  Node NEUTRAL;

  int build_node(int l, int r, Node x){
    segt[next_node] = x;
    l_ptr[next_node] = l;
    r_ptr[next_node] = r;
    return next_node++;
  }
 
  void init(int sz, vector<Node> *v=nullptr){
    n = sz;
    time2node[next_time++] = build(0, n - 1, v);
  }

  int build(int l, int r, vector<Node> *init_vals){
    if(l == r){
      return build_node(l, r, (init_vals? (*init_vals)[l] : NEUTRAL));
    }else{
      int mid = (l + r) / 2;
      int left_id = build(l, mid, init_vals);
      int right_id = build(mid + 1, r, init_vals);
      return build_node(left_id, right_id, segt[left_id] + segt[right_id]);
    }
  }
 
  Node _rng_query(int l, int r, int node, int lq, int rq){
    if(rq < l || lq > r) return NEUTRAL;
    else if(l >= lq && r <= rq) return segt[node];
    else{
      int mid = (l + r) / 2;
      return (_rng_query(l, mid, l_ptr[node], lq, rq) +
        _rng_query(mid+1, r, r_ptr[node], lq, rq)
      );
    }
  }
  
  Node query(int lq,int rq, int time = -1){
    if(time == -1) time = next_time - 1;
    return _rng_query(0, n - 1, time2node[time], lq, rq);
  }
  
  int update(int pos, int x, int time = -1){
    if(time == -1) time = next_time - 1;
    time2node[next_time] = _point_update(0, n - 1, time2node[time], pos, x);
    return next_time++;
  }

  int _point_update(int l, int r, int node, int i, int x){
    if(i > r || l > i) return node;
    if(i == r && i == l){
      return build_node(-1, -1, {x});
    }else{
      int mid = (l + r)/2;
      int left_id = _point_update(l, mid, l_ptr[node], i, x);
      int right_id = _point_update(mid+1, r, r_ptr[node], i, x);
      return build_node(left_id, right_id, segt[left_id] + segt[right_id]);
    }
  }
};

PersSegtree<100000, 100000> seg;

int32_t main(){
  cin.tie(NULL)->sync_with_stdio(false);
  
  int n; cin >> n;
  map<int, vector<int>> m;
  for(int i = 0; i < n; ++i){
    int x; cin >> x;
    m[x].push_back(i);
  }
  
  seg.init(n);
 
  vector<pair<int,int>> v;
  map<int, int> m2;
  for(auto [x, u] : m){
    int t;
    for(auto i : u) t = seg.update(i, x);
    v.push_back({x, t});
  }


  int q; cin >> q;
  while(q--){
    int l, r; cin >> l >> r; l--; r--;
    if(v[0].first > 1){
      cout << 1 << "\n";
      continue;
    }

    int ans = 1;
    int prev_id = -1;
    while(true){
      auto it = prev(lower_bound(v.begin(), v.end(), ans, [](const pair<int,int> &a, int x){
        return x >= a.first;
      }));
      auto ic = it - v.begin();
      if(ic <= prev_id) break;
      prev_id = ic;
      if(it->first <= ans){
        auto t = it->second;
        ans = seg.query(l, r, t).x + 1;
      }else break;
    }
    cout << ans << "\n";
  }


}
