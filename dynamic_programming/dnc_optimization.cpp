#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 5010;

int C[MAXN][MAXN];
int query(int l, int r){
  return C[l][r];
}

int last_dp[MAXN];
int curr_dp[MAXN];
int get_dp(int i){
  if(i < 0) return 0;
  else return last_dp[i];
}

void solve(int l, int r, int searchL, int searchR){
  if(l > r) return;
  int j = (l + r) / 2;
  if(curr_dp[j] == -1){
    int validR = min(j, searchR);
    pair<int,int> best = {LLONG_MIN, -1LL};
    for(int k = searchL; k <= validR; ++k){
      // getting first best position, change if last is needed
      best = max(best, {query(k, j) + get_dp(k - 1), k});
    }
    curr_dp[j] = best.first;
    solve(l, j - 1, searchL, best.second);
    solve(j + 1, r, best.second, searchR);
  }
}

int32_t main(){
  int t; cin >> t;
  while(t--){
    int n, m; cin >> n >> m;
    for(int i = 0; i < n; ++i){
      cin >> C[i][i];
      for(int j = i - 1; j >= 0; j--){
        C[j][i] = C[j + 1][i] | C[j][j];
      }
    }

    for(int i = 0; i < n; ++i){
      last_dp[i] = query(0, i);
    }
    for(int i = 1; i < m; ++i){
      memset(curr_dp, -1, sizeof curr_dp);
      solve(0, n - 1, 0, n - 1);
      swap(curr_dp, last_dp);
    }

    cout << last_dp[n - 1] << "\n";
  }
}
