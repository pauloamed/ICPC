#include<bits/stdc++.h>
using namespace std;

#define MAXN 200000
#define lpss list<pair<int, int>>
#define edgelist vector<vector<lpss::iterator>>

/*
 - Passeio euclidiano em O(m)
 Vai construindo ciclos disjuntos em arestas
*/


vector<int> v[MAXN]; // lista de adjacencia original


struct Hierholzer{
  vector<lpss> _v;
  int N;

  list<int> temp; // Declaracao de lista auxiliar e lista de retorno
  // temp vai guardar quem ta no ciclo e ainda pode ser usado para iniciar
  // uma nova busca
  // ret vai guardar circuito em sua ordem final

  // Vetor auxiliar relacionando os dois lados da aresta
  edgelist edges;

  bool is_directed = false;

  Hierholzer(int n, bool is_dir):N(n), is_directed(is_dir){ 
    _v = vector<lpss>(N); 
  }

  void dfs(int x, int ini, bool init=true){
    if(!init)temp.push_front(x);
    if(!init && x == ini) return; // closed cycle
    else{
      int next = _v[x].front().first; 
      int e = _v[x].front().second;
      if(is_directed){
        _v[x].erase(edges[e][0]);
      }else{
        if(x < next){
          _v[x].erase(edges[e][0]);
          _v[next].erase(edges[e][1]);
        }else{
          _v[x].erase(edges[e][1]);
          _v[next].erase(edges[e][0]);
        }
      }
      dfs(next, ini, false);
    }
  }

  list<int> run_euler(int start){
    for(int i = 0; i < N; ++i){
      for(int j = 0; j < v[i].size(); ++j){
        if(!is_directed && i > v[i][j]) continue; // assert(i < v[i][j])
        if(is_directed){
          auto it_i = _v[i].insert(_v[i].end(), {v[i][j], edges.size()});
          edges.push_back({it_i});
        }else{
          auto it_i = _v[i].insert(_v[i].end(), {v[i][j], edges.size()});
          auto it_vij = _v[v[i][j]].insert(_v[v[i][j]].end(), {i, edges.size()});
          edges.push_back({it_i, it_vij});
        }
      }
    }
    list<int> ret;
    temp.push_back(start);
    dfs(start, start); 
    while(true){ 
      while(temp.size() && _v[temp.front()].empty()){
        ret.splice(ret.begin(), temp, temp.begin());
      }
      if(temp.empty()) break; // Se nao posso aproveitar mais ninguem de temp, cabou
      dfs(temp.front(), temp.front()); // Tentar achar mais um ciclo
    }
    return ret;
  }

  list<int> get_cycle(int start){
    auto ret = run_euler(start);
    return ret;
  }

  list<int> get_path(int start, int target){
    v[target].push_back(start);
    if(!is_directed){
      v[start].push_back(target);
    }

    auto ret = run_euler(start);
    ret.pop_back();

    if(start != -1){
      list<int> a;
      for(auto it = ret.begin(); next(it) != ret.end(); it++){
        a.push_back(*it);
        if(!is_directed && (*it == start && *next(it) == target)){ // start, target (rev slice)
          list<int> b(next(it), ret.end());
          reverse(b.begin(), b.end());
          a.splice(a.end(), b);
          return a;
        }else if(*next(it) == start && *it == target){ // target, start (just swap)
          list<int> b(next(it), ret.end());
          b.splice(b.end(), a);
          return b;
        }
      }
    }
    return ret;
  }
};



int main(){
  int n, m; cin >> n >> m;

  vector<int> degrees(n);
  for(int i = 0; i < m; ++i){
    int a, b; cin >> a >> b;
    a--, b--;
    v[a].push_back(b);
    v[b].push_back(a);
    degrees[a]++;
    degrees[b]++;
  }


  for(int i = 0; i < n; ++i){
    if(degrees[i] % 2){
      cout << "IMPOSSIBLE\n";
      return 0;    
    }
  }


  Hierholzer h(n, false);
  auto x = h.get_cycle(0);
  // cerr << x.size() << endl;
  if(x.size() != m + 1){
    cout << "IMPOSSIBLE\n";
    return 0;
  }

  for(auto y : x){
    cout << y + 1 << " ";
  }
  cout << "\n";
}
