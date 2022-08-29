#include<bits/stdc++.h>
using namespace std;;


namespace kmp_auto{
  string pat;
  vector<vector<int>> aut;
  vector<int> pi;
  int ALPHA = 26;
  int ACC_STATE;
  int n;

  void preprocess(){
    pi = vector<int>(pat.size());
    pi[0] = 0;
    int j = 0, i = 1;
    while (i < pat.size()){
      if(pat[i] == pat[j]) pi[i] = ++j;
      else if(j == 0) pi[i] = 0;
      else{ j = pi[j - 1]; continue; }
      i++;
    }
  }

  void compute(){
    preprocess();
    pat += '#';
    n = pat.size();
    aut.assign(n, vector<int>(ALPHA, 0)); 
    aut[0][pat[0] - 'a'] = 1;
    for (int i = 1; i < n; i++) {
      for (int c = 'a'; c <= 'z'; c++) {
        if(c == pat[i]) aut[i][c - 'a'] = i + 1; 
        else aut[i][c - 'a'] = aut[pi[i-1]][c - 'a']; 
      }
    }
    ACC_STATE = n - 1;
  }
}

#define MAXP 101
#define MAXN 100010


struct Node{
  struct Edge{
    int to;
    int val;
  };

  vector<Edge> edges_f, edges_b;
  void init(){
    edges_f = edges_b = vector<Edge>(MAXP);
  }

  void set_char(char c){
    for(int from = 0; from < kmp_auto::n; ++from){
      {
        int to = kmp_auto::aut[from][c - 'a'];
        edges_f[from] = Edge{to, (to == kmp_auto::ACC_STATE)};
        edges_b[from] = Edge{to, (to == kmp_auto::ACC_STATE)};
      }
    }    
  }

  Node(){ init(); }
  Node(char c){
    init();
    set_char(c);
  }

  void merge(const Node &a, const Node &b){
    {
      for(int from = 0; from < kmp_auto::n; ++from){
        auto &e_a = a.edges_f[from];
        auto &e_b = b.edges_f[e_a.to];
        edges_f[from] = Edge{e_b.to, e_a.val + e_b.val};
      }
      for(int from = 0; from < kmp_auto::n; ++from){
        auto &e_a = b.edges_b[from];
        auto &e_b = a.edges_b[e_a.to];
        edges_b[from] = Edge{e_b.to, e_a.val + e_b.val};
      }
    }
  }
};

struct Query{
  int pts = 0;
  int pos;
  bool use_f;
  Query(int p, bool f):pos(p), use_f(f){}

  void run(const Node &x){
    if(use_f){
      pts += x.edges_f[pos].val;
      pos = x.edges_f[pos].to;
    }else{
      pts += x.edges_b[pos].val;
      pos = x.edges_b[pos].to;
    }
  }
};

namespace seg {
	Node seg[4*MAXN];
	int n, *v;

	void build(int p=1, int l=0, int r=n-1) {
		if (l == r){
      seg[p] = Node(v[l]);
    }else{
      int m = (l+r)/2; build(2*p, l, m), build(2*p+1, m+1, r);
      seg[p].merge(seg[2*p], seg[2*p+1]);
    } 
	}
	void build(int n2, int *v2) {
		n = n2; v = v2;
		build();
	}
	void prop(int p, int l, int r, char c) {
    assert(l == r);
		seg[p].set_char(c);
	}
	void query(int a, int b, Query &x, int p=1, int l=0, int r=n-1) {
		if (a <= l and r <= b) x.run(seg[p]);
		else if (b < l or r < a) return;
    else{
      int m = (l+r)/2;
      if(x.use_f){
        query(a, b, x, 2*p, l, m); 
        query(a, b, x, 2*p+1, m+1, r);
      }else{
        query(a, b, x, 2*p+1, m+1, r);
        query(a, b, x, 2*p, l, m); 
      }
    }
	}
	void update(int a, int b, int x, int p=1, int l=0, int r=n-1) {
		if (a <= l and r <= b) {
			prop(p, l, r, x);
			return;
		}
		if (b < l or r < a) return;
		int m = (l+r)/2;
    update(a, b, x, 2*p, l, m), update(a, b, x, 2*p+1, m+1, r);
		seg[p].merge(seg[2*p], seg[2*p+1]);
	}
};


namespace hld {
	vector<int> g[MAXN];
	int pos[MAXN], sz[MAXN];
	int peso[MAXN], pai[MAXN];
	int h[MAXN], v[MAXN], t;
  int d[MAXN];

  set<pair<int,int>> h2d[MAXN];

	void build_hld(int k, int p = -1, int f = 1) {
		v[pos[k] = t++] = peso[k]; sz[k] = 1;
    if(p != -1) d[k] = d[p] + 1;
		for (auto& i : g[k]) if (i != p) {
			pai[i] = k;
			h[i] = (i == g[k][0] ? h[k] : i);
			build_hld(i, k, f); sz[k] += sz[i];
			if (sz[i] > sz[g[k][0]] or g[k][0] == p) swap(i, g[k][0]);
		}
		if (p*f == -1) build_hld(h[k] = k, -1, t = 0);
	}
	void build(int root = 0) {
		t = 0;
    d[root] = 0;
		build_hld(root);
		seg::build(t, v);
    for(int k = 0; k < MAXN; ++k){
      h2d[h[k]].insert({d[k], k});
    }
	}
	void query_path(int a, int b, Query &x) { // b eh ancestral de a
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) seg::query(pos[b], pos[a], x);
		else{
      if(x.use_f){
        query_path(b, pai[h[a]], x);
        seg::query(pos[h[a]], pos[a], x);
      }else{
        seg::query(pos[h[a]], pos[a], x);
        query_path(b, pai[h[a]], x);
      }
    }
	}
	void update_point(int a, char x) {
    seg::update(pos[a], pos[a], x);
	}
	int lca(int a, int b) {
    while(h[a] != h[b]){
      if (pos[a] < pos[b]){
        b = pai[h[b]];
      }else{
        a = pai[h[a]];
      }
    }
		return (pos[a] < pos[b]? a : b);
	}

  int up(int k, int to){
    while(d[k] != to){
      if(d[h[k]] > to) k = pai[h[k]];
      else{
        auto it = h2d[h[k]].upper_bound({to, -1});
        assert(it->first == to);
        k = it->second;
      }
    }
    return k;
  }
}

int main(){
  cin.tie(NULL)->sync_with_stdio(false);

  int n, q; cin >> n >> q;
  cin >> kmp_auto::pat; kmp_auto::compute();

  string s; cin >> s;
  for(int i = 0; i < n - 1; ++i){
    int a, b; cin >> a >> b; a--, b--;
    hld::g[a].push_back(b);
    hld::g[b].push_back(a);
  }
  for(int i = 0; i < n; ++i) hld::peso[i] = s[i];
  hld::build();

  for(int i = 0; i < q; ++i){
    int t; cin >> t;
    if(t == 1){
      int u, v; cin >> u >> v; u--, v--;
      int lca = hld::lca(u, v);

      if(u == lca){
        Query x(0, true);
        hld::query_path(lca, v, x);
        cout << x.pts << "\n";
      }else if(v == lca){
        Query x(0, false);
        hld::query_path(u, lca, x);
        cout << x.pts << "\n";
      }else{
        int to_v = hld::up(v, hld::d[lca] + 1);
        
        Query x(0, false);
        hld::query_path(u, lca, x);
        
        Query y(x.pos, true);
        hld::query_path(to_v, v, y);

        cout << x.pts + y.pts << "\n";
      }

    }else{
      int u; cin >> u; u--;
      char c; cin >> c;
      hld::update_point(u, c);
    }
  }
}
