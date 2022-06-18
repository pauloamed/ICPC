// https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTree.cpp
// SegTree
//
// Recursiva com Lazy Propagation
// Query: soma do range [a, b]
// Update: soma x em cada elemento do range [a, b]
// Pode usar a seguinte funcao para indexar os nohs:
// f(l, r) = (l+r)|(l!=r), usando 2N de memoria
//
// Complexidades:
// build - O(n)
// query - O(log(n))
// update - O(log(n))

#define MAXN 100010
#define int long long

struct Node{
  int x;
  Node(int y=0):x(y){}
  Node operator+(Node n){
    return {x + n.x};
  }
};

namespace seg {
	Node seg[4*MAXN];
  int lazy[4*MAXN];
	int n, *v;
  const Node NEUTRAL;

	Node build(int p=1, int l=0, int r=n-1) {
		lazy[p] = 0;
		if (l == r) return seg[p] = (v? v[l] : NEUTRAL);
		int m = (l+r)/2;
		return seg[p] = build(2*p, l, m) + build(2*p+1, m+1, r);
	}
	void init(int n2, int* v2=nullptr) {
		n = n2, v = v2;
		build();
	}
	void prop(int p, int l, int r) {
		seg[p].x += lazy[p]*(r-l+1);
		if (l != r) lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	Node query(int lq, int rq, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (lq <= l && r <= rq) return seg[p];
		if (rq < l || r < lq) return NEUTRAL;
		int m = (l+r)/2;
		return query(lq, rq, 2*p, l, m) + query(lq, rq, 2*p+1, m+1, r);
	}
	void update(int lu, int ru, int x, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if(lu <= l && r <= ru){
			lazy[p] += x;
			prop(p, l, r);
		}else if(ru >= l && r >= lu){
      int m = (l+r)/2;
      update(lu, ru, x, 2*p, l, m); update(lu, ru, x, 2*p+1, m+1, r);
      seg[p] = seg[2*p] +	seg[2*p+1];
    }
	}
};


// Se tiver uma seg de max, da pra descobrir em O(log(n))
// o primeiro e ultimo elemento >= val numa range:

// primeira posicao >= val em [a, b] (ou -1 se nao tem)
int get_left(int a, int b, int val, int p=1, int l=0, int r=n-1) {
	if (b < l or r < a or seg[p] < val) return -1;
	if (r == l) return l;
	int m = (l+r)/2;
	int x = get_left(a, b, val, 2*p, l, m);
	if (x != -1) return x;
	return get_left(a, b, val, 2*p+1, m+1, r);
}
// ultima posicao >= val em [a, b] (ou -1 se nao tem)
int get_right(int a, int b, int val, int p=1, int l=0, int r=n-1) {
	if (b < l or r < a or seg[p] < val) return -1;
	if (r == l) return l;
	int m = (l+r)/2;
	int x = get_right(a, b, val, 2*p+1, m+1, r);
	if (x != -1) return x;
	return get_right(a, b, val, 2*p, l, m);
}

// Se tiver uma seg de soma sobre um array nao negativo v, da pra
// descobrir em O(log(n)) o maior j tal que v[i]+v[i+1]+...+v[j-1] < val

int lower_bound(int i, ll& val, int p, int l, int r) {
	if (r < i) return n;
	if (i <= l and seg[p] < val) {
		val -= seg[p];
		return n;
	}
	if (l == r) return l;
	int m = (l+r)/2;
	int x = lower_bound(i, val, 2*p, l, m);
	if (x != n) return x;
	return lower_bound(i, val, 2*p+1, m+1, r);
}
