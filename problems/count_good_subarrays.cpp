// https://codeforces.com/gym/101991/problem/G
/*
Essa questao eh legal pq meio que resolve dois subproblemas que parecem ser independentes.
Um subproblema é, pra todo i, achar [r1;r2] maximal t.q. gcd(i,i+1,...,r1) = gcd(i,i+1,...,r2)

Outro subproblema (+ interessante) é algo que talvez de pra generalizar pra outras questões:

Contar quantos subarrays bons existem dentro de [L;R] dado que:
- tenho uma lista de tamanho tratável de subarrays bons no formato (L, R1, R2)
-- todo subarray [L;r], R1 <= r <= R2 é bom
- todo subarray de um subarray bom é bom

Da pra resolver isso da seguinte forma:
- ordenar queries e subarrays bons por L decrescente
- itera nas queries e faz 2ptrs pra ir liberando todo array bom com L >= ql
- manter uma seg onde seg[i] = subarrays bons terminando em i (o começo é o L q estamos expandindo)
- quando liberar um subarrays bom (L, R1, R2), note que:
-- todo intervalo [L;r], r > R2 vai conter todos (R2-R1+1) subarrays bons liberados agora
-- todo intervalo [L;r], R1 <= r <= R2, vai conter (r-R1+1) subarrays bons
- ou seja, adicionar (R2-R1+1) em [R2;n-1] e PA de (1 até R2-R1+1) em [R1;R2]
-- da pra resolver esses updates com segtree lazy de progressao aritmetica
-- a resposta da query [ql;qr] é seg[qr] (ja que seg assume que tenho todos intervalos com L >= ql)



*/


#include<bits/stdc++.h>
using namespace std;

#define MAXN 100010
#define int long long
#define ll long long

namespace sparse_table {
  const int K = 20;
  int st[MAXN][K]; 
  int vlog[MAXN+1];

  void precalc(int n, int* v){
    for(int i = 0; i < n; ++i) st[i][0] = v[i];
    for(int i = 1; i < K; ++i){ 
      int j = 0; 
      int interv_sz = (1 << i); 
      while(j + interv_sz <= n){ 
        st[j][i] = __gcd(st[j][i - 1], st[j + interv_sz / 2][i - 1]); // OP
        j++;
      }
    }
    // below only for idempotent functions
    vlog[1] = 0;
    for(int i = 2; i <= MAXN; i++) vlog[i] = vlog[i/2] + 1; 
  }

  int query(int l, int r){
    int interv_sz = r - l + 1; 
    int j = vlog[interv_sz]; 
    return __gcd(st[l][j], st[r - (1 << j) + 1][j]); // OP
  }
}

struct LazyNode{
  ll start, step;
  bool to_reset, reset_child;

  LazyNode(ll sa=0, ll se=0):
  start(sa), step(se), to_reset(false), reset_child(false){}
  
  ll get_sum(ll n){
    ll pa = (n * (n - 1)) / 2;
    return n * start + pa * step;
  }

  void merge(LazyNode &ln, int sz_at_left=0){
    // called in `update` and `lazy_prop`
    // in both cases, when updting right tree, 
    // start needs to add steps from right subtree
    start += ln.start + ln.step * sz_at_left;
    step += ln.step;
  }

  void to_neutral(){
    start = step = 0;
  }

  void reset(ll &segv){
    to_neutral(); 
    segv = 0;
    to_reset = false;
  }
};


namespace seg {
	ll seg[4*MAXN];
  LazyNode lazy[4*MAXN];
	int n;

	ll build(int p=1, int l=0, int r=n-1) {
		lazy[p] = LazyNode();
		if (l == r) return seg[p] = 0;
		int m = (l+r)/2;
		return seg[p] = build(2*p, l, m) + build(2*p+1, m+1, r);
	}

  void init(int nn){
    n = nn;
    build();
  }

	void prop(int p, int l, int r) {
    if(lazy[p].to_reset) lazy[p].reset(seg[p]);

    if((lazy[p].reset_child) && (l != r)){
      lazy[2*p].to_reset = lazy[2*p].reset_child = true;
      lazy[2*p+1].to_reset = lazy[2*p+1].reset_child = true;
      lazy[p].reset_child = false;
    }

    seg[p] += lazy[p].get_sum(r - l + 1);

    if(l != r){
      int m = (l + r) / 2;
      if(lazy[2*p].to_reset) lazy[2*p].reset(seg[2*p]);
      if(lazy[2*p+1].to_reset) lazy[2*p+1].reset(seg[2*p+1]);
		  
      lazy[2*p].merge(lazy[p]);
		  lazy[2*p+1].merge(lazy[p], m - l + 1);
    }

		lazy[p].to_neutral();
	}

	ll query(int a, int b, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b){
      return seg[p];
    }
		if (b < l or r < a) return 0;
		int m = (l+r)/2;
		return query(a, b, 2*p, l, m) + query(a, b, 2*p+1, m+1, r);
	}

	ll update(int a, int b, LazyNode &x, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) {
			lazy[p].merge(x);
			prop(p, l, r);
			return seg[p];
		}
		if (b < l or r < a) return seg[p];
		int m = (l+r)/2;

    LazyNode to_right;
    to_right.merge(x, max(m - max(l, a) + 1, 0LL));
		return seg[p] = update(a, b, x, 2*p, l, m) +
			update(a, b, to_right, 2*p+1, m+1, r);
	}

  void reset(){
    lazy[1].reset_child = lazy[1].to_reset = true;
  }
};

struct GCDRange{
  int l, r_start, r_end, d;
};

vector<GCDRange> find_ranges(vector<int> &v){
  int n = v.size();
  vector<GCDRange> ret;
  sparse_table::precalc(n, &(v[0]));

  for(int i = 0; i < n; ++i){
    int l = i;
    int nxt_start = i;
    while(nxt_start < n){
      int r_start = nxt_start;
      int d = sparse_table::query(i, r_start);
      
      int r_size = 0;
      {
        int pot = (1 << 20);
        while(pot){
          int maybe_sz = r_size + pot;
          int idx = r_start + maybe_sz;
          if(idx < n && sparse_table::query(i, idx) == d){
            r_size = maybe_sz;
          }
          pot /= 2;
        }
      }
      int r_end = r_start + r_size;
      ret.push_back({l, r_start, r_end, d});
      nxt_start = r_end + 1;
    }
  }

  sort(ret.begin(), ret.end(), [](GCDRange &a, GCDRange &b){
    if(a.d == b.d) return a.l > b.l;
    else return a.d < b.d;
  });
  return ret;
}

int32_t main(){
  cin.tie(NULL)->sync_with_stdio(false);
  freopen("gcdrng.in", "r", stdin);    
  int t; cin >> t;
  while(t--){
    int n, q; cin >> n >> q;
    vector<int> v(n); for(auto &x : v) cin >> x;
    auto ranges = find_ranges(v);

    struct QueryNode{ int l, r, d, i; };
    vector<QueryNode> qs;
    for(int i = 0; i < q; ++i){
      int l, r, d; cin >> l >> r >> d; l--, r--;
      qs.push_back({l, r, d, i});
    }
    sort(qs.begin(), qs.end(), [](QueryNode &a, QueryNode &b){
      if(a.d == b.d) return a.l > b.l;
      else return a.d < b.d;
    });

    seg::init(n);
    vector<int> ans(q, -1);
    int ri = 0;
    int last_d = -1;
    for(auto [ql, qr, qd, qi] : qs){
      while(ri < ranges.size() && ranges[ri].d < qd) ri++;

      if(qd != last_d) seg::reset();
      last_d = qd;
      
      while(true){
        if(ri == ranges.size()) break;
        if(ranges[ri].d > qd) break;
        if(ranges[ri].l < ql) break;
        // add ri

        int r_sz = ranges[ri].r_end - ranges[ri].r_start + 1;
        LazyNode inside_range(1, 1), outside_range(r_sz, 0);
        seg::update(ranges[ri].r_start, ranges[ri].r_end, inside_range);
        seg::update(ranges[ri].r_end + 1, n - 1, outside_range);

        ri++;
      }
      ans[qi] = seg::query(qr, qr);
    }

    for(int i = 0; i < q; ++i){
      cout << ans[i] << "\n";
    }
  }
}