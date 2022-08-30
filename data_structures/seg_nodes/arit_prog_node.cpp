struct LazyNode{
  int start, step;
  LazyNode(int _start=0, int _step=0):
    start(_start),step(_step){}

  int get_sum(int n){
    int pa = (n * (n - 1)) / 2;
    return n * start + pa * step;
  }

  void merge(LazyNode &ln, int sz_at_left=0){
    start += ln.start + ln.step * sz_at_left;
    step += ln.step;
  }

  void reset(){ start = step = 0; }
};

const LazyNode LAZY_NEUTRAL;
 
namespace seg {
	int seg[4*MAXN];
  LazyNode lazy[4*MAXN];
	int n;
 
  void build(int nn){
    n = nn;
  }
 
	void prop(int p, int l, int r) {
    seg[p] += lazy[p].get_sum(r - l + 1);
    if(l != r){
      int m = (l + r) / 2;
		  lazy[2*p].merge(lazy[p]);
		  lazy[2*p + 1].merge(lazy[p], m - l + 1);
    }
		lazy[p].reset();
	}
	int query(int a, int b, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) return seg[p];
		if (b < l or r < a) return 0;
		int m = (l+r)/2;
		return query(a, b, 2*p, l, m) + query(a, b, 2*p+1, m+1, r);
	}
	int update(int a, int b, LazyNode &x, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) {
			lazy[p].merge(x);
			prop(p, l, r);
			return seg[p];
		}
		if (b < l or r < a) return seg[p];
		int m = (l+r)/2;
 
    LazyNode lnl, lnr;
    lnl.merge(x); lnr.merge(x, max(m - max(l, a) + 1, 0LL));
		return seg[p] = update(a, b, lnl, 2*p, l, m) +
			update(a, b, lnr, 2*p+1, m+1, r);
	}
};
