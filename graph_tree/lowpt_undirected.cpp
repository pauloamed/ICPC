#include<bits/stdc++.h>
using namespace std;

#define MAXN 200010

// https://codeforces.com/gym/102835/problem/I


/*
Block-cut tree and biconnected components O(M+N)
 
Two edge types:
- Tree/span edge: connects to a still not visited node
- Back edge: connects to an already visited node. This node will be an ancestral in non-directed graphs.
- lowpt(v): node closest to the root in the recursion tree that can be reached from v by using 
  one or more tree edge followed by only one back edge
 - Marker – node v s.t. lowpt(v) = v or w and w is parent of v in recursion tree
 - Articulations – Parent node of a marker. If it is root, needs to have more than one span edge.
*/

namespace biconn{
  vector<int> v[MAXN];

  int lowpt[MAXN], depth[MAXN]; 

  int arts;
  bool is_art[MAXN];

  vector<vector<int>> comps;
  vector<int> bridges;
  vector<vector<pair<int,int>>> edge_comps;

  stack<int> comp;
  stack<pair<int,int>> edges;
  void dfs(int x, int par, int d){
    depth[x] = d, lowpt[x] = x;

    int cnt_tree_edge = 0;
    bool has_marker = false;

    for(auto y : v[x]){
      if(depth[y] == 0){ cnt_tree_edge++; // tree edge

        comp.push(y); edges.push({x, y});
        dfs(y, x, d + 1);

        if(depth[lowpt[y]] < depth[lowpt[x]]) 
          lowpt[x] = lowpt[y];

        if(lowpt[y] == y || lowpt[y] == x){ has_marker = true;
          
          // nodes
          comps.push_back({x});
          while(true){
            int z = comp.top(); comp.pop();
            comps.back().push_back(z);
            if(z == y) break;
          }
          if(comps.back().size() == 2)
            bridges.push_back(comps.size() - 1);

          // /* edges remove if not needed
          edge_comps.push_back({});
          while(true){
            auto z = edges.top(); edges.pop();
            edge_comps.back().push_back(z);
            if(z == make_pair(x,y)) break;
          }
          // */
        }
      }else{ // back edge
        if(depth[y] < depth[lowpt[x]]) lowpt[x] = y;
        if(depth[y] < depth[x] && y != par) edges.push({x, y});
      }
    }

    if(has_marker && (d != 1 || cnt_tree_edge > 1))
      arts += (is_art[x] = true);
  }

  void run(int n){
    comps.clear();
    bridges.clear();
    edge_comps.clear(); // remove if not needed

    memset(is_art, false, sizeof is_art);
    arts = 0;

    memset(lowpt, -1, sizeof lowpt);
    memset(depth, 0, sizeof depth);
    for(int i = 0; i < n; ++i) if(depth[i] == 0)
       dfs(i, -1, 1);
  }
}




int main(){
  cin.tie(NULL)->sync_with_stdio(false);
  int _t; 
  cin >> _t;
  while(_t--){
    int n, m, k; cin >> n >> m;
    // cin >> k;

    for(int i = 0; i < n; ++i){
      biconn::v[i].clear();
    }

    for(int i = 0; i < m; ++i){
      int a, b; cin >> a >> b;
      a--; b--;
      if(a == b) continue;
      biconn::v[a].push_back(b);
      biconn::v[b].push_back(a);
    }

    biconn::run(n);


    int x = biconn::comps.size();
    int maxs = 0;
    for(auto x : biconn::edge_comps) maxs = max(maxs, (int)x.size());
    // cout << maxs << " " << x << endl;

    // cout << " :: " << biconn::comps.size()  << " " << biconn::bridges.size() << endl;

    int gg = __gcd(x, maxs);
    cout << biconn::arts << " " << biconn::bridges.size() << " ";
    cout << x / gg << " " << maxs / gg << endl;

    // int cnt_non_triv = 0;
    // for(auto &x : comps) cnt_non_triv += x.size() > 2;

    // cout << cnt_non_triv << "\n";
    // for(auto x : comps) if(x.size() > 2){
    //   cout << x.size() << " ";
    //   for(auto y : x) cout << y - 1 << " ";
    //   cout << endl;
    // }
  }
}
