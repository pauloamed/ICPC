#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000100;

struct BIT{
  int n; vector<int> v;
  BIT(int m = 0):n(m + 2), v(vector<int>(n)){}

  int query(int i){ int ans = 0;
    for(i++; i > 0; i -= i & (-i))
      ans += v[i];
    return ans;
  }

  void update(int i, int val){
    for(i++; i < n; i += i & (-i)) 
      v[i] += val;
  }
};

BIT bit(MAXN);
int ans[MAXN];

// init -> add -> build
// ONLINE: go
// OFFLINE: process, solve

namespace AhoCorasick{
  const int N = 200000;
  const int SIGMA = 30;
  const char FIRST_CHAR = 'a';
  const int ROOT = 0;
  
  // IF PRECOMPUTING TRANSITIONS
  int to[N][SIGMA]; 
  // IF NOT PRECOMPUTING TRANSITIONS
  // map<int,int> to;

  // next node to be added to the trie
  int next_node = 1;

  void init(int n){
    next_node = 1;
    for(int i = 0; i < n; ++i) 
      memset(to[i], 0, sizeof to[i]);
  }

  // marker for accepted nodes
  vector<pair<int,int>> acc[N]; // ATTENTION: may change depending on application

  void add(const string &s, int query_pos, int query_id){
    int curr = ROOT;
    for(auto c : s){ c -= FIRST_CHAR;
      // ATTENTION: precomputing transitions?
      if(to[curr][c] == 0) curr = to[curr][c] = next_node++;
      else curr = to[curr][c];

      // ATTENTION: add prefixes as patterns?
    }
    acc[curr].push_back({query_pos, query_id}); // ATTENTION
  }

  // preffix function on trie nodes
  // suffix_link[x] points to greatest proper prefsufix of x
  int sl[N];
  
  // reversed edges of sl (DFS/sack). note that if, when processing T, we visit a
  // node X in the sl subtree of a accepted node Y, we are on a accepted string position
  vector<int> sl_tree[N]; 

  // similar to calculation of preffix function
  // compute suffix links and transitions
  void build(){
    // IF PRECOMPUTING TRANSITIONS
		for(int i = 0; i < next_node; i++){
      sl[i] = ROOT;
      sl_tree[i].clear();
    }
		queue<int> q; q.push(ROOT);

		while(!q.empty()){
			int u = q.front(); q.pop();
			for(int i = 0; i < SIGMA; i++){
				if(to[u][i]){
          // existent transition from `u` using `i`
					int v = to[u][i]; q.push(v);
 
          // just as in KMP construction in success case
          // since s[i-sl[v]:i] = string(sl[v])
					if(u != ROOT) sl[v] = to[sl[u]][i];

          sl_tree[sl[v]].push_back(v);
				}else{ 
          // inexistent transition from `u` using `i`, 
          // if theres a suffixlink, uses it
          if(u != ROOT) to[u][i] = to[sl[u]][i];
          else to[u][i] = ROOT;
        }
			}
		}

    /* IF NOT PRECOMPUTING TRANSITIONS
    const int P = -1;
    sl[ROOT] = P;
    while(q.size()){
      int x = q.front(); q.pop();
      for(auto [c, child] : to[x]){
        // trying to match a prefsufix, starts with parents suffixlink
        int child_sl = sl[x]; 
        while(child_sl != P){
          if(to[child_sl].count(c)) break;
          else child_sl = sl[child_sl];
        }
        if(child_sl == P){
          // couldnt match a prefsufix+c
          sl[child] = ROOT; 
        }else{
          // found match (prefsufix+c)
          sl[child] = to[child_sl][c]; 
        } 
        
        q.push(child);
        sl_tree[sl[child]].push_back(child);
      }
    }
    sl[ROOT] = ROOT;
    */

    /* IF ONLINE,
    run collapse_accs(ROOT);

    something like:
    void collapse_accs(int x){
      for(auto y : sl_tree[x]){
        collapse_accs(y);
        acc[x].pts = max(acc[x].pts, acc[y].pts);
      }
    }
    */
  }

  // ONLINE
	int go(int x, char c){
    // ATTENTION: precomputing transitions?
		return to[x][c - FIRST_CHAR];
	}


  // OFFLINE
  // marker for visited nodes when processing T string
  set<int> vis[N]; // ATTENTION
  void process(string &t){ // ATTENTION (args)
    int curr = ROOT;
    for(int i = 0; i < t.size(); ++i){
      // ATTENTION: precomputing transitions?
      curr = to[curr][t[i] - FIRST_CHAR];
      vis[curr].insert(i); // ATTENTION
    }
  }

  /* IF OFFLINE,
  void solve(int x=ROOT){
    for(auto y : sl_tree[x]){
      for(auto x : vis[x]){
        ...
      }
    }
  }
  */
};
