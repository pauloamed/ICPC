#include<bits/stdc++.h>
using namespace std;
 
#define MAXN 10
#define MOD 998244353
#define int long long
 
typedef vector< vector< int > > matrix;
matrix operator *(matrix a, matrix b) {
	int n = (int)a.size();
	//assert(a[0].size() == b.size());
	int m = (int)b.size();
	int p = (int)b[0].size();
	matrix c(n, vector<int>(p));
	vector<int> col(m);
	for (int j = 0; j < p; j++) {
		for (int k = 0; k < m; k++)
			col[k] = b[k][j];
		for (int i = 0; i < n; i++) {
			int s = 0;
			for (int k = 0; k < m; k++){
				s += (a[i][k] * col[k]) % MOD;
        s = (s + MOD) % MOD;
      }
			c[i][j] = s % MOD;
		}
	}
	return c;
}
 
matrix fastexp(matrix base, int expo, int n){
  matrix ans = matrix(n, vector<int>(n)); // identity
  for(int i = 0; i < n; ++i) ans[i][i] = 1;
  while(expo > 0){
    if(expo & 1) ans = ans * base;
    expo >>= 1;
    base = base * base;
  }
  return ans;
}
 
int solve_recur(vector<int> vars, int S){
  vector<int> recur;
 
  int n = vars.size();
  int memory = 0;
  for(int i = 1; i < (1 << n); ++i){
    int sum = 0;
    for(int j = 0; j < n; ++j){
      if((i >> j) & 1) sum += vars[j];
    }
    memory = max(memory, sum);
    if(__builtin_popcount(i) % 2) recur.push_back(sum);
    else recur.push_back(-sum);
  }
 
  matrix M(memory, vector<int>(memory));
  for(int i = 1; i < memory; ++i) M[i][i - 1] = 1; // rep casos base
  for(auto x : recur){
    int idx = abs(x) - 1;
    if(x < 0) M[0][idx]--;
    else M[0][idx]++;
  }
  
  int adjust_zero_sum = 0;
  for(auto x : vars) adjust_zero_sum += x;
 
  if(S - adjust_zero_sum < 0) return 0;
 
  M = fastexp(M, S - adjust_zero_sum, memory);
  matrix base(memory, vector<int>(1));
  base[0][0] = 1;
 
  int ret = (M * base)[0][0];
 
  // for(auto x : vars) cout << x << " "; cout << "\n";
  // for(auto x : recur) cout << x << " "; cout << "\n";
  // cout << ret << "\n";
 
  return ret;
}
 
set<vector<int>> rot;
 
int solve_rotations(vector<int> &vars){
  vector<int> v(6);
  for(auto x : vars){
    for(int i = 0; i < x; ++i) v[5 - i]++;
  }
  
  set<vector<int>> rotations;
  do{
    vector<int> u;
    for(auto rotation : rot){
      vector<int> w(6);
      for(int i = 0; i < 6; ++i){
        w[i] = v[rotation[i]];
      }
      if(u.empty()) u = w;
      else u = min(u, w);
    }
    rotations.insert(u);
  }while(next_permutation(v.begin(), v.end()));
 
  return rotations.size();
}
 
int32_t main(){
  int S; cin >> S;
 
  vector<int> P = {0, 0, 0, 1, 1, 1, 2, 2, 2};
  do{
    vector<int> a = {0,1,2,3,4,5};
    for(int i = 0; i < 9; ++i){
      rot.insert(a);
      if(P[i] == 0){
        swap(a[2], a[4]);
        swap(a[3], a[5]);
        swap(a[4], a[5]);
      }else if(P[i] == 1){
        swap(a[0], a[4]);
        swap(a[1], a[5]);
        swap(a[0], a[1]);
      }else{
        swap(a[0], a[2]);
        swap(a[1], a[3]);
        swap(a[2], a[3]);
      }
      rot.insert(a);
    }
  }while(next_permutation(P.begin(), P.end()));
 
  int ans = 0;
  for(int i = 0; i < (1 << 5); ++i){
    // se bit ativo, sou igual ao anterior
    vector<int> vars;
    int cnt = 1;
    for(int j = 0; j < 5; ++j){
      if((i >> j) & 1) vars.push_back(cnt);
      cnt++;
    }
    vars.push_back(cnt);
 
    int a = solve_rotations(vars);
    int b = solve_recur(vars, S);
    ans = (ans + (a * b) % MOD) % MOD;
  }
 
  cout << ans << "\n";
}
