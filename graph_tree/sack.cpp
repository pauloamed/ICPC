// each node is visited by O(logN) calls as a light node
// until it turns a heavy node

// inTime[v]: time in which node v was entered
// outTime[v]: time in which node v was left
// time2node[t]: node which was entered in time t
// inTime[time2Node[t]] = t // time2Node[inTime[v]] = v
int curr_time;
int in_time[MAXN], out_time[MAXN], time2node[MAXN];

int sz[MAXN];
vector<int> v[MAXN];

int depth[MAXN];

void precalc(int x, int par=-1, int d=0){
  time2node[curr_time] = x; in_time[x] = curr_time++;
  depth[x] = d;
  sz[x] = 1;
  for(auto y : v[x]) if(y != par) {
    precalc(y, x, d + 1);
    sz[x] += sz[y];
  }
  out_time[x] = curr_time;
}

void solve(int x, int par=-1, bool keep=0){
  int heavy_child = -1;
  for(auto y : v[x]) if(y != par) {
    if(heavy_child == -1 || sz[y] > sz[heavy_child]) 
      heavy_child = y;
  }

  if(heavy_child != -1){
    // solve but dont keep light nodes
    for(auto y : v[x]) if(y != par && y != heavy_child)
      solve(y, x, false);
    // solve and keep heavy nodes
    solve(heavy_child, x, true);
  }

  for(auto y : v[x]) if(y != par && y != heavy_child) {
    // maybe solve queries (light -> (heavy + past_lights))
    for(int t = in_time[y]; t < out_time[y]; ++t){
      int z = time2node[t];
      // query z
    }
    // add light nodes after solving, avoid info leakage
    for(int t = in_time[y]; t < out_time[y]; ++t){
      int z = time2node[t];
      // add z
    }
  }
 
  // solve queries (x -> all subtrees)
  // add x for querying or for keeping as heavy child

  if(!keep){
    for(int t = in_time[x]; t < out_time[x]; ++t){
      int z = time2node[t];
      // rmv z
    }
  }
}
