#include<bits/stdc++.h>
using namespace std;

struct BipartiteDSU{
  vector<int> p, sz, color, is_bipartite;
  BipartiteDSU(int n):p(n),sz(n),color(n),is_bipartite(n, 1){
    iota(p.begin(), p.end(), 0);
  }

  // FINDS AND UPDATES COLORS + PATH COMPRESSION
  int find(int x){
    int new_par=x;
    int xoor = 0;
    while(p[new_par] != new_par){
      xoor ^= color[new_par]; // connected vertexes are guaranteed to have diff colors
      new_par = p[new_par];
    }
    // cout << "sera?" << endl;
    // if xoor == 1: x and new_par have the same color
    // else: diff colors
    while(p[x] != x){
      int old_color = color[x];
      int old_paar = p[x];
      color[x] = xoor;
      xoor ^= old_color;
      p[x] = new_par;
      x = old_paar;
    }
    return p[x];
  }

  int get_color(int x){
    find(x); return color[x];
  }

  bool can_onion(int a, int b){
    return (find(a) != find(b)) || (color[a] == color[b]); 
  }

  bool onion(int a, int b){
    int pa = find(a), pb = find(b);
    if(pa == pb){
      if(color[a] == color[b]){
        return is_bipartite[pa] = false; // oops
      }else return true; // changes nothing
    }else{
      if(sz[pa] < sz[pb]) swap(pa, pb);
      color[pb] = (color[a] == color[b]);
      p[pb] = pa; sz[pa] += sz[pb];
      is_bipartite[pa] &= is_bipartite[pb];
      return true;
    }
  }
};

int main(){
  cin.tie(NULL); cin.sync_with_stdio(false);

  int n, m; cin >> n >> m;
  map<int, vector<pair<int,int>>, greater<int>> b2l;
  for(int i = 0; i < m; ++i){
    int a, b, c; cin >> a >> b >> c;
    b2l[c].push_back({--a, --b});
  }

  vector<int> ans;
  BipartiteDSU dsu(n);
  for(auto &x : b2l){
    vector<pair<int,int>> valid;
    for(auto [a,b] : x.second){
      // cout << "ta mesmo?" << endl;
      if(dsu.can_onion(a, b)){
        valid.push_back({a, b});
      }
    }

    // cout << x.first << "\n";
    // for(auto [a,b] : valid){
    //   cout << a << " " << b << "\n";
    // }

    
    set<pair<int,int>> cond_valid;
    for(auto [a,b] : valid){
      // cout << a << " " << b << " " << dsu.find(a) << " " << dsu.find(b) << " " << dsu.color[a] << " " << dsu.color[b] << "\n";
      int x = dsu.find(a) + 1, y = dsu.find(b) + 1;
      if(dsu.color[a] == 0) x *= -1;
      if(dsu.color[b] == 0) y *= -1;
      cond_valid.insert({x, y});
    }
    int i = 0;

    // for(auto e : cond_valid){
    //   cout << e.first << " " << e.second << "\n";
    // }

    bool ok = false;
    for(auto e : cond_valid){
      if(i++ == 10) break;
      auto [c, d] = e;
      for(auto [a,b] : cond_valid){
        if(a != c && a != d && b != c && b != d){
          ok = true;
        }
      }
    }



    if(ok) ans.push_back(x.first);
    for(auto [a,b] : valid) if(!dsu.onion(a, b)) goto OUT;
  }
  OUT:
  bool all_bip = true;
  for(int i = 0; i < n; ++i){
    all_bip &= dsu.is_bipartite[dsu.find(i)];
  }
  if(all_bip) ans.push_back(0);
  reverse(ans.begin(), ans.end());
  if(ans.empty()) cout << "IMPOSSIBLE\n";
  else for(auto x : ans) cout << x << "\n";





}
