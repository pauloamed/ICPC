// https://atcoder.jp/contests/abc253/tasks/abc253_h

#include<bits/stdc++.h>
using namespace std;

#define MAXN 14
#define MOD 998244353
#define EPS 1e-9
#define MAXM 501
const int MAXB = (1 << 14);

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
			int p = (1LL * a[j][i] * fastexp(a[i][i], MOD - 2)) % MOD;
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

int f[MAXB];
int g[MAXM][MAXB];

int get_g(int i, int mask){
  if(i < 0) return 0;
  else if(i == 0) return 1;
  return g[i][mask];
}

int main(){
  int n, m; cin >> n >> m;
  vector<pair<int,int>> edges(m);
  for(auto &[a,b] : edges){
    cin >> a >> b; a--, b--;
  }

  lap = vector<vector<int>>(n, vector<int>(n));

  const int masks = (1 << n);
  for(int i = 1; i < masks; ++i){
    f[i] = number_spanning_trees(i, edges);
  }

  int fat = 1;
  // g[i][msk]: number of dif. forests using nodes from msk w/ i edges
  for(int i = 1; i < n; ++i){
    for(int msk = 1; msk < masks; ++msk){
      int b = 0;
      while(true){
        if((msk >> b) & 1) break;
        b++;
      }

      if(__builtin_popcount(msk) - 1 == i) g[i][msk] = f[msk];
      for(int smsk = (msk - 1) & msk; smsk; smsk = (smsk - 1) & msk){
        if((smsk >> b) & 1){
          // smsk is Tree
          // #nodes in Tree
          int l = __builtin_popcount(smsk);
          int tree_cnt = f[smsk];
          
          // nodes not in Tree
          int inv = msk ^ smsk; 

          // num of forests with inv_nodes
          int forst_cnt = get_g(i - (l - 1), inv);

          g[i][msk] += (1LL * tree_cnt * forst_cnt) % MOD;
          g[i][msk] %= MOD;
        }
      }
    }

    fat = (1LL * i * fat) % MOD;
    int num = (1LL * fat * g[i][masks - 1]) % MOD;
    int den = fastexp(m, i);
    int x = (1LL * num * fastexp(den, MOD - 2)) % MOD;
    cout << x << "\n";
  }



}