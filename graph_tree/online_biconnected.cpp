#include<bits/stdc++.h>
using namespace std;

#define MAXN 200010
#define MAXLOG 20

vector<int> v[MAXN];

namespace lca{
  int st[MAXN][MAXLOG], d[MAXN];

  void get_par(int x, int p){
    st[x][0] = p;
    if(p != -1) d[x] = d[p] + 1;
    for(auto y : v[x]) if(y != p) get_par(y, x);
  }

  void init(int root, int n){
    get_par(root, -1);
    for(int l = 1; l < MAXLOG; ++l) for(int i = 0; i < MAXN; ++i){
      if(st[i][l-1] == -1) st[i][l] = -1;
      else st[i][l] = st[st[i][l-1]][l-1];
    }
  }

  int lca(int x, int y){
      if(d[x] < d[y]) swap(x, y);
      int falta_subir = (d[x] - d[y]);
      for(int i = MAXLOG-1; i >= 0; --i) if((1<<i) <= falta_subir){
        falta_subir -= (1<<i);
        x = st[x][i];
      }
      if(x == y) return x;
      for(int i = MAXLOG-1; i >= 0; --i) if(st[x][i] != st[y][i])
        x = st[x][i], y = st[y][i];
      return st[x][0];
  }

  int dist(int a, int b){
    int x = lca(a, b);
    return (d[a] - d[x]) + (d[b] - d[x]);
  }
}

struct DSU{
  int sizes[MAXN];
  int parents[MAXN];
  int less_deep[MAXN];
  
  DSU(int n=0){
    for(int i = 0; i < n; ++i){
      sizes[i] = 1;
      parents[i] = i;
      less_deep[i] = i;
    }
  }

  int find(int current){
    int newRoot = current;
    while(newRoot != parents[newRoot]) newRoot = parents[newRoot];

    // rmv if using rollback
    int next;
    while(parents[current] != newRoot){
      next = parents[current];
      parents[current] = newRoot;
    }
    return newRoot;
  }

  void onion(int a, int b){
    a = find(a); b = find(b);
    if(a == b) return;
    if(sizes[a] < sizes[b]) swap(a,b);

    if(lca::d[less_deep[a]] > lca::d[less_deep[b]]) 
      less_deep[a] = less_deep[b];
    sizes[a] += sizes[b];
    parents[b] = a;
  }
};


int32_t main(){
  cin.tie(NULL)->sync_with_stdio(false);
  
  int n, m; cin >> n >> m;

  vector<int> h(n); 
  for(auto &x : h) cin >> x;

  // FIRST, GENERATE ANY SPANNING TREE
  // in this problem, the MST was needed
  vector<pair<int, pair<int,int>>> edges;
  {
    DSU tree_dsu(n);
    for(int i = 0; i < m; ++i){
      int a, b; cin >> a >> b;
      a--; b--;

      int c = abs(h[a] - h[b]);
      edges.push_back({c, make_pair(a, b)});
    }

    sort(edges.begin(), edges.end());

    vector<pair<int, pair<int,int>>> nedges;
    for(auto [c, ab] : edges){
      auto [a,b] = ab;
      if(tree_dsu.find(a) != tree_dsu.find(b)){
        v[a].push_back(b);
        v[b].push_back(a);
        tree_dsu.onion(a, b);
      }else nedges.push_back({c, make_pair(a, b)});
    }
    swap(edges, nedges);
  }

  lca::init(0, n);
  DSU biconn_dsu(n);

  vector<int> ans(n, -1);
  
  // MERGE TREE INTO BICONNECTED COMPONENTS USING THE REMAINING EDGES
  auto merge = [&](int a, int b, int val){
    int l = biconn_dsu.find(lca::lca(a, b));
    if(ans[l] == -1)
      ans[l] = val;

    l = biconn_dsu.less_deep[l];


    auto keep_merging = [&](int x, int d){
      int curr = x;
      while(true){
        if(ans[curr] == -1) ans[curr] = val;
        biconn_dsu.onion(x, curr);
        if(lca::d[curr] == 0) break;
        curr = lca::st[curr][0];
        curr = biconn_dsu.less_deep[biconn_dsu.find(curr)];
        if(lca::d[curr] < d) break;
      }
      // cout << "\n";
    };

    keep_merging(a, lca::d[l]);
    keep_merging(b, lca::d[l]);
  };

  for(auto [c, ab] : edges){
    auto [a,b] = ab;
    merge(a, b, c);
  }
  
  for(auto x : ans) cout << x << " ";
  cout << "\n";
}
