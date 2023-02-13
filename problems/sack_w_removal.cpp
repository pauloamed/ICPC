#include<bits/stdc++.h>
using namespace std;

const int MAXN = 400010;

int curr_time;
int in_time[MAXN], out_time[MAXN], time2node[MAXN];

int sz[MAXN];
vector<int> v[MAXN];

int depth[MAXN];
int A[MAXN], B[MAXN];

void precalc(int x, int par=-1, int d=0){
  time2node[curr_time] = x; in_time[x] = curr_time++;
  if(par != -1) B[x] = A[x] ^ B[par];


  depth[x] = d;
  sz[x] = 1;
  for(auto y : v[x]) if(y != par) {
    precalc(y, x, d + 1);
    sz[x] += sz[y];
  }
  out_time[x] = curr_time++;
}


map<int, int> M;
void add(int x){
  M[x]++;
}
void rmv(int x){
  if(--M[x] == 0) M.erase(x);
}

int off[MAXN];

int ans = 0;
void solve(int x, int par=-1, bool keep=0){
  int heavy_child = -1;
  for(auto y : v[x]) if(y != par) {
    if(heavy_child == -1 || sz[y] > sz[heavy_child]) 
      heavy_child = y;
  }

  if(heavy_child != -1){
    for(auto y : v[x]) if(y != par && y != heavy_child)
      solve(y, x, false);
    solve(heavy_child, x, true);
  }

  bool has = false;
  for(auto y : v[x]) if(y != par && y != heavy_child) {
    {
      int cnt_off = 0;
      for(int t = in_time[y]; t <= out_time[y]; ++t){
        if((cnt_off += off[t]) == 0 && time2node[t]){
          int z = time2node[t];
          if(M.count(B[z] ^ A[x])) has = true;
        }
      }
    }
    {
      int cnt_off = 0;
      for(int t = in_time[y]; t <= out_time[y]; ++t){
        if((cnt_off += off[t]) == 0 && time2node[t]){
          int z = time2node[t];
          add(B[z]);
        }
      }
    }
  }
  add(B[x]);

  // cout << x << ": ";
  // for(auto [a, b] : M) cout << a << " " << b << ","; cout << endl;
  
  if(M.count(B[par])) has = true;
  if(has){
    // cout << "____ " << x << endl;
    ans++;
  }

  if(!keep){
    int cnt_off = 0;
    for(int t = in_time[x]; t <= out_time[x]; ++t){
      if((cnt_off += off[t]) == 0 && time2node[t]){
        int z = time2node[t];
        rmv(B[z]);
      }
    }
  }

  if(has){
    off[in_time[x]] = 1;
    off[out_time[x]] = -1;
    M.clear();
  }
}


int32_t main(){
  int n; cin >> n;
  for(int i = 1; i <= n; ++i) cin >> A[i];
  for(int i = 0; i < n - 1; ++i){
    int a, b; cin >> a >> b;
    v[a].push_back(b);
    v[b].push_back(a);
  }
  v[0].push_back(1);

  precalc(0);
  solve(1, 0);

  cout << ans << "\n";
}
