#include<bits/stdc++.h>
using namespace std;
 
#define MAXN 300010
#define INF 1e9
 
struct TimelyDSU{
  int n;
  int parent[MAXN];
  int sz[MAXN];
  int connTime[MAXN];
  // connTime[a] keeps the time the node was connected
  // if it was never connected, we set it to INF
 
  TimelyDSU(){}
 
  void init(int n){
      this->n=n;
      for(int i = 0; i < n; ++i){
        parent[i] = i; 
        sz[i] = 1;
        connTime[i] = INF;
      }
  }
 
  int find(int current){
    int x = current;
    while(current != parent[current]){ // while cant find a root nome
      current = parent[current]; // go up on the tree
    }
    return current;
  }
 
 
  void onion(int a, int b, int t){
    a = find(a), b = find(b);
    if(a == b) return;
    if(sz[b] > sz[a]) swap(a, b);
    sz[a] += sz[b];
    parent[b] = a;
    connTime[b] = t;
  }
 
  int timelyFind(int current, int t){
    // go up in the tree while my time is <= the edges times
    while(current != parent[current] && connTime[current] <= t){ 
        current = parent[current];
    }
    return current;
  }
 
 
  // only works for non-reflexive orders (>, not >=)
  // runs in log
  int earliestConn(int a, int b){
    if(a == b) return 0; // same node, connected since beggining
    if(find(a) != find(b)) return -1; // not connected now, were never connected
    int ret = -1; // latest conneciton before they get united
    while(a != b){
      if(connTime[a] > connTime[b]) swap(a,b); 
      // go up means get me to a newer connection (until i get to the LCA)
      ret = max(connTime[a], ret); 
      // our goal is to get the times when the subtrees of A and B connected to the LCA
      // since the LCA has connTime greatest than the roots of these trees, we wont go upper
      // the correct answer will than be the latest connection between the roots of A or B subtrees
      a = parent[a]; // a is the pivot, the one going up
    }
    return ret;
  }

  // runs in log^2
  int earliestConnBinarySearch(int a, int b){
    int ans = 0;
    int pot = (1 << 29);
    // finds smallest time in which they are connected
    while(pot){
      int maybe_ans = ans + pot;
      if(timelyFind(a, maybe_ans) != timelyFind(b, maybe_ans)) ans = maybe_ans;
      pot /= 2;
    }
    return ans;
  }

};

int main(){
  TimelyDSU dsu;
  int n, m, s; cin >> n >> m >> s;
  dsu.init(n+1);

  vector<int> vals;
  vector<pair<int,pair<int,int>>> edges;
  for(int i = 0; i < m; ++i){
    int a, b, c; cin >> a >> b >> c;
    edges.push_back({-c, {a, b}});
    vals.push_back(-c);
  }
  vals.push_back(-INF);
  sort(edges.begin(), edges.end());
  sort(vals.begin(), vals.end());
  vals.resize(unique(vals.begin(), vals.end()) - vals.begin());

  int tempo = 0;
  map<int,int> tempo2c;
  for(auto e : edges){
    int c = lower_bound(vals.begin(), vals.end(), e.first) - vals.begin();
    auto [a,b] = e.second;
    dsu.onion(a, b, tempo);
    tempo2c[tempo] = -e.first;
    tempo++;
  }

  for(int i = 0; i < s; ++i){
    int a, b; cin >> a >> b;
    cout << tempo2c[dsu.earliestConn(a, b)] << "\n";
  }
}
