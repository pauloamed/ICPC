#include<bits/stdc++.h>
using namespace std;

#define MAXN 100010

// global time var for computing the following arrays
// (only incremented when entering node)
int currTime;
// inTime[v]: time in which node v was entered
// outTime[v]: time in which node v was left
// time2node[t]: node which was entered in time t
// inTime[time2Node[t]] = t // time2Node[inTime[v]] = v
int inTime[MAXN], outTime[MAXN], time2Node[MAXN];
int sz[MAXN]; // sz[v]: size of subtree rooted at v
vector<int> v[MAXN]; // adj list

int depth[MAXN]; // depth[v] = depth of node v
int c[MAXN]; // c[v]: char at node v

void precalc(int x, int par, int d){
  time2Node[currTime] = x; inTime[x] = currTime++;
  depth[x] = d;
  sz[x] = 1;
  for(auto y : v[x]){
    if(y == par) continue;
    precalc(y, x, d + 1);
    sz[x] += sz[y];
  }
  outTime[x] = currTime;
}

map<int, int> names[MAXN]; // bitset for each depth
vector<pair<int,int>> queries[MAXN]; // queries at node x
vector<int> ans; // ans for each query

void solve(int x, int par, bool keep){
  // cout << x << endl;
  if(v[x].size() > 1 || par == -1){
    // retrieving heavy child from x
    int heavyChildSize = -1;
    int heavyChild = -1;
    for(auto y : v[x]){
      if(y == par) continue;
      if(sz[y] > heavyChildSize){
        heavyChild = y;
        heavyChildSize = sz[y];
      }
    }

    // vising light and then heavy childs of x
    for(auto y : v[x]){
      if(y == heavyChild || y == par) continue;
      solve(y, x, false);
    }
    solve(heavyChild, x, true);

    for(auto y : v[x]){
      if(y == heavyChild || y == par) continue;
      for(int t = inTime[y]; t < outTime[y]; ++t){
        int z = time2Node[t];
        names[depth[z]][c[z]]++;
      }
    }
  }

  names[depth[x]][c[x]]++;

  for(auto q : queries[x]){
    if(q.first >= MAXN) ans[q.second] = 0;
    else ans[q.second] = names[q.first].size();
  }

  if(!keep){
    for(int t = inTime[x]; t < outTime[x]; ++t){
      int y = time2Node[t];
      names[depth[y]][c[y]]--;
      if(names[depth[y]][c[y]] == 0){
        names[depth[y]].erase(c[y]);
      }
    }
  }
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  int n; cin >> n;
  c[0] = -1;
  unordered_map<string,int> s2i;
  for(int i = 1; i <= n; ++i){
    string s; cin >> s;
    if(s2i.count(s) == 0) s2i[s] = s2i.size();
    c[i] = s2i[s];
    int x; cin >> x;
    v[x].push_back(i);
    v[i].push_back(x);
  }

  precalc(0, -1, 1);

  int q; cin >> q;
  ans = vector<int>(q);
  for(int i = 0; i < q; ++i){
    int a, b; cin >> a >> b;
    queries[a].push_back({depth[a] + b, i});
  }

  solve(0, -1, true);

  for(auto x : ans) cout << x << "\n";
}
