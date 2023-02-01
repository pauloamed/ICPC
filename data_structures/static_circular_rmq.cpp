namespace static_circular_rmq{
  const int NEUTRAL = INT_MAX;
  
  int st[MAXN][K]; 
  int vlog[MAXN+1];
  int pref[MAXN], suf[MAXN];
  int n;
  int pos[MAXN];

  void build(int n, vector<pair<int,int>> &v){
    for(int i = 0; i < n; ++i) st[i][0] = v[i].second;
    for(int i = 1; i < K; ++i){ 
      int j = 0, interv_sz = (1 << i); 
      while(j + interv_sz <= n){ 
        st[j][i] = min(st[j][i - 1],  st[j + interv_sz / 2][i - 1]); // OP
        j++;
      }
    }
    vlog[1] = 0;
    for(int i = 2; i <= MAXN; i++) vlog[i] = vlog[i/2] + 1; 
  }

  int _query_range(int l, int r){
    if(r < l) return NEUTRAL;
    int interv_sz = r - l + 1; 
    int j = vlog[interv_sz]; 
    return min(st[l][j], st[r - (1 << j) + 1][j]); 
  }

  void init(vector<pair<int,int>> cycle){
    n = cycle.size();
    for(int i = 0; i < n; ++i){
      pos[cycle[i].first] = i;
    }
    
    build(n, cycle);

    pref[0] = NEUTRAL;
    suf[n - 1] = cycle[n - 1].second;
    for(int i = 1; i < n; ++i){
      int j = n - 1 - i;
      pref[i] = min(pref[i - 1], cycle[i - 1].second);
      suf[j] = min(suf[j + 1], cycle[j].second);
    }
  }

  pair<int,int> query(int a, int b){
    if(a == b) return {NEUTRAL, NEUTRAL};
    int l = pos[a], r = pos[b];
    if(l > r) swap(l, r);
    return {min(pref[l], suf[r]), _query_range(l, r - 1)};
  }
}
