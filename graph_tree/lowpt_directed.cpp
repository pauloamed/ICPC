#define MAXN 5010
 
/*
two vertices `i`, `j` are strongly connected in a directed graph G iff 
there exists a direct path from `i` to `j` and from `j` to `i`.

(v,w) is an advance edge iff in_time(v) < in_time(w)
(v,w) is a return edge iff in_time(v) > in_time(w) AND out_time(v) < out_time(w)
(v,w) is a cross edge iff in_time(v) > in_time(w) AND out_time(v) > out_time(w)

low(v) = min{v, in_time(z)}, s.t. z is the vertex w/ lowest in_time in the same SCC as v.
it can be reached using 0 or more consecutive advance edges followed by at most one return or cross edge.
*/
 
vector<int> v[MAXN];

namespace scc{
  int t = 0;
  int in_time[MAXN];

  int low[MAXN];
  bool active[MAXN];
  stack<int> curr_comp;

  int scc_cnt = 0;
  int scc[MAXN];
  
  void dfs(int x, int _root){
    low[x] = in_time[x] = ++t;
    active[x] = true;
    curr_comp.push(x);

    for(auto y : v[x]){
      if(in_time[y] == 0){ 
        // advance edge
        dfs(y, _root);
        low[x] = min(low[x], low[y]);
      }else if(active[y] && in_time[y] < in_time[x]){      
        // return or cross edge
        low[x] = min(low[x], in_time[y]);
      }
    }

    if(low[x] == in_time[x]){
      while(true){
        int y = curr_comp.top(); 
        curr_comp.pop();

        scc[y] = scc_cnt;
        active[y] = false;
        if(y == x) break;
      }scc_cnt++;
    }
  }
}
