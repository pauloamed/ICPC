#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200010;
const int MAXLOG = 25;
const int BLOCK_SIZE = 450;

bool mos_comp(pair<pair<int,int>, int> &a, pair<pair<int,int>, int> &b){
  int block_a = a.first.first / BLOCK_SIZE;
  int block_b = b.first.first / BLOCK_SIZE;
  if(block_a == block_b){
    if(block_b & 1) return a.first.second < b.first.second;
    else return a.first.second > b.first.second;
  }else{
    return block_a < block_b;
  }
}

vector<pair<int,int>> v[MAXN];
vector<int> euler;
int node_start[MAXN], node_end[MAXN];
int edge[MAXN];

void dfs(int x, int p, int ep){
  edge[x] = ep;
  node_start[x] = euler.size();
  euler.push_back(x);
  for(auto [y,e] : v[x]) if(y != p){
    dfs(y, x, e);
  }
  node_end[x] = euler.size();
  euler.push_back(x);
}


int bit[MAXN];
int first_zero(){
  int ans = 0;
  if(bit[1] == 0) return 0;
  for(int i = MAXLOG-1; i >= 0; --i){
    int maybe_ans = (ans | (1<<i)); // novo indice se o bit for ativo
    if(maybe_ans >= MAXN) continue; // caso ultrapasse o limite no calc do indice
    if(bit[maybe_ans] == (1 << i)) ans = maybe_ans;
  }
  return ans;
}

void update( int index, int val ){
    index++; // bit eh 1-indexada
    while(index < MAXN){ // enquanto eu puder subir na BIT
        bit[index] += val; // atualizando valores dos ancestrais
        index += index & (-index); // subindo pro pai
    }
}

unordered_map<int,int> active;

void deactivate_val(int x){
  if(x == -1) return;
  if(--active[x] == 0){
    update(x, -1);
    active.erase(x);
  }
}

void activate_val(int x){
  if(x == -1) return;
  if(active[x]++ == 0) update(x, 1);
}

bool is_on[MAXN];
void toggle(int x){
  int e = edge[x];
  if(is_on[x]) deactivate_val(e);
  else activate_val(e);
  is_on[x] = !is_on[x];
}


int walk_r_left(int r){
  // unexecute v[r] and r++
  toggle(euler[r]);
  return --r;
}
 
int walk_r_right(int r){
  // execute v[r+1]
  r++;
  toggle(euler[r]);
  return r;
}
 
int walk_l_left(int l){
  // execute v[l-1]
  l--;
  toggle(euler[l]);
  return l;
}
 
int walk_l_right(int l){
  // unexecute inv v[l] and l++
  toggle(euler[l]);
  return ++l;
}
 

int main(){
  cin.tie(NULL)->sync_with_stdio(false);

  int n, q; cin >> n >> q;
  euler.reserve(n * 2);

  for(int i = 0; i < n - 1; ++i){
    int a, b; cin >> a >> b;
    int c; cin >> c;
    v[a].push_back({b, c});
    v[b].push_back({a, c});
  }

  dfs(1, -1, -1);

  vector<pair<pair<int,int>,int>> qs;
  for(int i = 0; i < q; ++i){
    int a, b; cin >> a >> b;
    int sa = node_start[a];
    int ea = node_end[a];
    int sb = node_start[b];
    int eb = node_end[b];

    if(sa > sb){
      swap(a, b);
      swap(sa, sb);
      swap(ea, eb);
    }

    if(a == b){
      qs.push_back({make_pair(-1,-1), i});
    }else if(sa <= sb && sb <= ea){
      // a is lca
      // dont consider lca's edge (sa + 1)
      qs.push_back({make_pair(sa + 1, sb), i});
    }else{
      // lca is neither a nor b
      qs.push_back({make_pair(ea, sb), i});
    }
  }

  sort(qs.begin(), qs.end(), mos_comp);

  int curr_l = 0;
  int curr_r = walk_r_right(-1);

  vector<int> ans(q);
  for(auto [lr, i] : qs){
    auto [l,r] = lr;
    if(l == -1){
      ans[i] = 0; continue;
    }

    // expands
    while(curr_l > l) curr_l = walk_l_left(curr_l);
    while(curr_r < r) curr_r = walk_r_right(curr_r);

    // narrows
    while(curr_l < l) curr_l = walk_l_right(curr_l);
    while(curr_r > r) curr_r = walk_r_left(curr_r);

    ans[i] = first_zero();
  }

  for(auto x : ans){
    cout << x << "\n";
  }
}