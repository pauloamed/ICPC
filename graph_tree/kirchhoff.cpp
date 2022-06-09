int fastexp(int base, int expo){
  int ans = 1; // identity
  while(expo > 0){
    if(expo & 1) ans = (1LL * ans * base) % MOD;
    expo >>= 1;
    base = (1LL * base * base) % MOD;
  }
  return ans;
}


typedef vector<vector<int>> matrix;

bool gauss(matrix &a, int n){
	for(int i = 0, l; i < n; i++){
		l = i;
		while(l < n && a[l][i] == 0) l++;
		if (l == n) return false;
    for(int k = 0; k < n; k++) swap(a[i][k], a[l][k]);
		for(int j = 0; j < n; j++) {
			if (i == j) continue;
			int p = (1LL * a[j][i] * fastexp(a[i][i], MOD - 2)) % MOD; // multiplicative inverse
      for(int k = 0; k < n; k++){
        a[j][k] -= (1LL * p * a[i][k]) % MOD;
        a[j][k] = (a[j][k] + MOD) % MOD;
      }
		}
	}
	return true;
}

// kirschhoff theorem
// lapacian matrix, global to prevent reallocation
// set size in main
matrix lap; 
int number_spanning_trees(int mask, vector<pair<int,int>> edges){
  int n = __builtin_popcount(mask);
  if(n == 1) return 1;
  
  for(int i = 0; i < n; ++i) 
    fill(lap[i].begin(), lap[i].begin() + n, 0);

  map<int,int> id;
  for(auto [a, b] : edges) if (a != b){
    if((mask >> a) & (mask >> b) & 1){
      if(id.count(a) == 0) id[a] = id.size();
      if(id.count(b) == 0) id[b] = id.size();
      lap[id[a]][id[a]]++; lap[id[b]][id[b]]++;
      lap[id[a]][id[b]]--; lap[id[b]][id[a]]--;
    }
  }

  if(n - 1 == 1) return lap[0][0];
	if(gauss(lap, n - 1)){
		int ans = 1;
		for(int i = 0; i < n - 1; i++) 
      ans = (1LL * ans * lap[i][i]) % MOD;
		return ans;
	}else return 0;
}
