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

void solve(int x, bool keep){ // maybe worry about parent
  if(v[x].size() > 0){
    int heavy_child = -1;
    for(auto y : v[x]){
      if(sz[y] > sz[heavy_child]) heavy_child = y;
    }
 
    // vising light and then heavy childs of x
    for(auto y : v[x]){
      if(y != heavy_child) solve(y, false);
    }
    solve(heavy_child, true);
 
    for(auto y : v[x]){
      if(y == heavyChild || y == par) continue;
      for(int t = in_time[y]; t < out_time[y]; ++t){
        int z = time2node[t];
        // add z
      }
    }
  }
 
  // add x
 
  // solve queries
 
  if(!keep){
    for(int t = in_time[x]; t < out_time[x]; ++t){
      int z = time2node[t];
      // rmv z
    }
  }
}
