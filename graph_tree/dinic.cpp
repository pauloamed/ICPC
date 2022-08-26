// solves https://cses.fi/problemset/task/1709

#include<bits/stdc++.h>
using namespace std;

#define int long long
 
// Edge structure: handles node pointed to, capacity
// and the index in v[to] to its reverse edge
struct Edge{
  int to, rev;
  int cap; //
  bool is_rev;
  Edge(int t, int c, int r, bool irev):to{t},rev{r},cap{c},is_rev{irev}
  {}
};
 
 
struct Flow{
  int n, s, t; // n: # nodes, s: source, t: sink
  vector<vector<Edge>> v; // extended adj list
  vector<int> lvl; // indicates the lvl for each node. used for the lvl graph
 
  // assures that each edge is completely visited only once. keeps sort of backup
  // of the index of the last visited edge
  // there is no need to revisit an edge, hence, these can be skipped
  vector<int> lastPos;
 
  // constructor
  Flow(int N, int src, int snk){
    this->n = N;
    this->s = src;
    this->t = snk;
    v = vector<vector<Edge>>(n, vector<Edge>());
  }
 
  // adding edges: endpoints and capacities
  // in case of bidirecitonal edges, use this function twice, one for each direction
  // using the full capacity on both
  void addEdge(int a, int b, int c){
    v[a].push_back({b,c,(int)v[b].size(),false});
    v[b].push_back({a,0,((int)v[a].size()) - 1,true});
  }
 
  // "builds" the lvl graph. simple bfs indicating the lvl for each node
  void getLvls(){
    queue<int> q; q.push(s);
    lvl.assign(n,-1); lvl[s] = 0;
    while(q.size()){
      int x = q.front(); q.pop();
      for(auto e : v[x]){
        if(lvl[e.to] == -1 && e.cap){
          // lvl graph only reaches new nodes and possible edges (cap > 0)
          q.push(e.to);
          lvl[e.to] = lvl[x] + 1;
        }
      }
    }
  }
 
  // finds an augmenting path and updates edges
  int dfs(int i, int curr = LONG_LONG_MAX){
    if(i == t){
      return curr; // reached sink, returning collected flow
    }else{
      for(; lastPos[i] < v[i].size(); ++lastPos[i]){
        auto &e = v[i][lastPos[i]];
        if(e.cap && lvl[i] + 1 == lvl[e.to]){
          // possible edges (cap > 0) and lvl-graph structure (consecutive lvls traversal)
 
          int maybe_flow = dfs(e.to, min(curr, e.cap));
          if(maybe_flow == 0) continue;
 
          e.cap -= maybe_flow; // updating edge
          v[e.to][e.rev].cap += maybe_flow; // and its reverse
          return maybe_flow;
        }
      }
    }
    return 0;
  }
 
  // main funct
  int run(){
    int flow = 0; // initial flow
    while(true){
      getLvls(); // builds lvl graph
      // if the sink cant be reached, the max flow has been found
      if(lvl[t]==-1) break;
      // get a blocking flow for the current lvl graph
      int blocking = -1;
      lastPos.assign(n,0);
      while((blocking = dfs(s))) flow += blocking;
    }
    return flow;
  }
 
  vector<pair<int,int>> get_cut(){
    vector<pair<int,int>> cut;
    for(int i = 0; i < n; ++i){
      for(int j = 0; j < v[i].size(); ++j){
        auto &e = v[i][j];
        if(!e.is_rev && lvl[i] != -1 && lvl[e.to] == -1){
          cut.push_back({i, e.to});
        }
      }
    }
    return cut;
  }

  void print(){
    printf("N:%lld\n", n);
    for(int i = 0; i < n; ++i){
      printf("%lld: ", i);
      for(int j = 0; j < v[i].size(); ++j){
        auto &e = v[i][j];
        printf("(%lld, %lld, %lld) ", e.to, e.cap, e.is_rev);
      }
      printf("\n");
    }
  }
};

const int SRC = 0;
const int SINK = 1;
const int OFFSET = 2;

void solve(vector<string> matrix){
  int n = matrix.size();
  int m = matrix[0].size();
  Flow f(n + m + 3, SRC, SINK);

  for(int i = 0; i < n; ++i) f.addEdge(SRC, i + OFFSET, 1);
  for(int i = 0; i < m; ++i) f.addEdge(i + n + OFFSET, SINK, 1);
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m; ++j){
      if(matrix[i][j] == 'o'){
        f.addEdge(i + OFFSET, j + n + OFFSET, 1);
      }
    }
  }
  cout << f.run() << "\n";
  for(auto x : f.get_cut()){
    // cout << x.first << " " << x.second << "\n";
    if(x.first == SRC){
      cout << 1 << " " << x.second - OFFSET + 1 << "\n";
    }else{
      cout << 2 << " " << x.first - OFFSET - n + 1 << "\n";
    }
  }
  // f.print();
}

int32_t main(){
  int n; cin >> n;
  vector<string> mm(n);
  for(auto &x : mm) cin >> x;
  solve(mm);
}
