template<class T, class E> struct segtree{
	const int n, h;
	vector<T> tree;
 
	inline void calc(int id){
		tree[id].update(tree[id<<1], tree[id<<1|1]);
	}
 
	segtree() : segtree(0){ }
	segtree(int N) : n(N), h((int)(sizeof(int)*8 - __builtin_clz(n))), tree(2 * n){ }
 
	segtree(vector<E>& base) : n((int)base.size()), h((int)(sizeof(int)*8 - __builtin_clz(n))), tree(n){
		for(int i = 0; i < n; i++)
			tree.push_back(T(base[i], i));
		for(int i = n - 1; i > 0; i--) calc(i);
	}
 
	void push(int l, int r){
		int s = h, k = 1 << (h-1);
		for(l += n, r += n-1; s > 0; --s, k >>= 1){
			for(int i = l >> s; i <= r >> s; i++) if(!tree[i].updated()){
				tree[i<<1].propagate(tree[i], k);
				tree[i<<1|1].propagate(tree[i], k);
				tree[i].clear_lazy();
			}
		}
	}
 
	void modify(int l, int r, E value){
		push(l, l + 1);
		push(r - 1, r);
		bool cl = false, cr = false;
		int k = 1;
		for(l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1){
			if(cl) calc(l - 1);
			if(cr) calc(r);
			if(l&1) tree[l++].apply(value, k), cl = true;
			if(r&1) tree[--r].apply(value, k), cr = true;
		}
		for(--l; r > 0; l >>= 1, r >>= 1, k <<= 1){
			if(cl) calc(l);
			if(cr && (!cl || l != r)) calc(r);
		}
	}
 
	T query(int l, int r){
		push(l, l + 1);
		push(r - 1, r);
		T resl = T(), resr = T();
		for(l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l&1) resl.merge_right(tree[l++]);
			if(r&1) resr.merge_left(tree[--r]);
		}
		resl.merge_right(resr);
		return resl;
	}
};
 
/*
Node() ~ identity value
Node(E& value, int p) ~ value from base array element and position
update(Node& l, Node& r) ~ update node from its children
propagate(Node& father, int len) ~ propagates lazy from father (update value and lazy)
clear_lazy() ~ clears lazy
updated() ~ checks whether lazy was cleared
apply(E& value, int len) ~ updates node from a value and segment length
merge_right(Node& r) ~ merges this node with r on the right
merge_left(Node& l) ~ if the operation is commutative, simply call merge_right(l);
struct Node{
	Node(){ }
	Node(E& value, int p){ }
	void update(Node& l, Node& r){ }
	void propagate(Node& father, int len){ }
	void clear_lazy(){ }
	bool updated(){ return true; }
	void apply(E& value, int len){ }
	void merge_right(Node& r){ }
	void merge_left(Node& l){ }
};
*/
// example of a minimum query segtree
struct Node{
	int lazy, mn, posm;
	Node() : lazy(0), mn(1e9), posm(-1){ }
	Node(int value, int p) : lazy(0), mn(value), posm(p) { }
	void update(Node& l, Node& r){
		if(l.mn < r.mn){
			mn = l.mn;
			posm = l.posm;
		}
		else{
			mn = r.mn;
			posm = r.posm;
		}
	}
	void propagate(Node& father, int){
		mn += father.lazy;
		lazy += father.lazy;
	}
	void clear_lazy(){ lazy = 0; }
	bool updated(){ return lazy == 0; }
	void apply(int value, int){ mn += value; lazy += value;}
	void merge_right(Node& r){
		if(r.mn < mn){
			mn = r.mn;
			posm = r.posm;
		}
	}
	void merge_left(Node& l){ merge_right(l); }
};

