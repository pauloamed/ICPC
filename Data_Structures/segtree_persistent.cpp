int l[MAXN], r[MAXN], st[MAXN], NODES = 0;
int n;

int newleaf(int value=0){ // identity
	assert(NODES+1 < MAXN);
	int p = ++NODES;
	l[p] = r[p] = 0;
	st[p] = value;
	return p;
}

int newparent(int lef, int rig){
	assert(NODES+1 < MAXN);
	int p = ++NODES;
	l[p] = lef;
	r[p] = rig;
	st[p] = st[lef] + st[rig];
	return p;
}

int build(const vector<int>& arr, int L=0, int R=n-1){
	int M = (L+R)/2;
	if(L == R) return newleaf(arr[L]);
	else return newparent(build(arr, L, M), build(arr, M+1, R));
}

int update(int idx, int val, int p, int L=0, int R=n-1){
	int M = (L+R)/2;
	if(L == R) 		return newleaf(st[p]+val); // can generalize the operation here
	if(idx <= M) 	return newparent(update(idx, val, l[p], L, M), r[p]);
	else			return newparent(l[p], update(idx, val, r[p], M+1, R));
}

// returns kth smallest element
int query(int k, int p1, int p2, int L=0, int R=n-1){
	int sl = st[l[p2]]-st[l[p1]];
	int M = (L+R)/2;
	if(L == R) return L;
	if(sl >= k) return query(k, l[p1], l[p2], L, M);
	else return query(k-sl, r[p1], r[p2], M+1, R);
}
