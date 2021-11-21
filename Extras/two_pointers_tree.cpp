// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/F
// two pointers
// internal state is a tree

#include<bits/stdc++.h>
using namespace std;

#define MAXN 1010
#define MAXM 10010
#define INF 2e9+1

int activeEdges = 0;

bitset<MAXN> vis;
list<pair<int,int>> v[MAXN];
pair<int,pair<int,int>> edges[MAXM];
vector<pair<int, list<pair<int,int>>::iterator>> id2owner[MAXM];
// first: dest
// second: cost

void dfs(int x){
  vis[x] = true;
  for(auto z : v[x]) if(!vis[z.first]) dfs(z.first);
}

bool isConn(int n){
  vis.reset();
  dfs(0);
  return vis.count() == n;
}

void rmEdge(int i){
  for(int j = 0; j < id2owner[i].size(); ++j){
    v[id2owner[i][j].first].erase(id2owner[i][j].second);
  }
  id2owner[i].clear();
  activeEdges--;
}

bool getPath(int x, int par, int target, int& best){
  vis[x] = true;
  if(x == target) return true;
  for(auto z : v[x]){
    int next = z.first;
    if(next == par) continue;

    if(getPath(next, x, target, best)){
      best = min(best, z.second);
      return true;
    }
  }
  return false;
}


void addEdge(int i){
  int a = edges[i].second.first;
  int b = edges[i].second.second;
  if(a==b) return;

  // maybe remove an edge
  int badEdge = INF;
  if(getPath(a, -1, b, badEdge)) rmEdge(badEdge);


  activeEdges++;
  id2owner[i].push_back(make_pair(a, v[a].insert(v[a].begin(), {b, i})));
  id2owner[i].push_back(make_pair(b, v[b].insert(v[b].begin(), {a, i})));
}



int main(){
  int n, m; cin >> n >> m;
  if(m < n - 1){
    cout << "NO\n"; return 0;
  }
  for(int i = 0; i < m; ++i){
    int a, b, c; cin >> a >> b >> c; a--, b--;
    edges[i] = {c, {a, b}};
  }
  sort(edges, edges + m);

  // tem l, vou botar r
  long long ans = INF;
  int l = 0, r = 0;
  while(r < m){
    while(r < m && !isConn(n)){
      addEdge(r++);
      assert(activeEdges <= n - 1);
    }
    if(!isConn(n)) break;

    while(id2owner[l].empty()) l++;
    ans = min(ans, (long long)(edges[r - 1].first - edges[l].first));
    rmEdge(l);
  }
  if(ans == INF){
    cout << "NO" << endl;
  }else{
    cout << "YES" << endl;
    cout << ans << endl;
  }
}
