#include<bits/stdc++.h>
using namespace std;

/*
There are 2 choices to be made

acc[x]: marker for accpeted nodes; initialized at `add`
vis[x]: used at offline, string positions visiting node `x` will update `vis[x]`

Precomputing transitions:
	- Needed (performance) if input is not string (eg. tree, trie, dag)
	- Meanwhile, consumes N*SIGMA time and memory

Online/Offline
	- Online: using as automaton; `acc` will have all info pushed down in trie after build; 
		process matches online
	
	- Offline: first mark visited positions; then process those using the suffix link tree 
	positions in the subtree of an accepted position is also accepted

*/

template <int N, int SIGMA, char FIRST_CHAR>
struct AhoCorasick{
  const int ROOT = 0;
  
  int to[N][SIGMA]; // IF PRECOMPUTING TRANSITIONS
  // map<int,int> to[N]; // IF NOT PRECOMPUTING TRANSITIONS
  
  int acc[N];

  // suffix_link[x] points to greatest proper prefsufix of x
  int sl[N];
  
	// a match in node `x` is a match in its whole subtree
  vector<int> sl_tree[N]; 

  int next_node = 1; // to add to trie

  void init(){
    next_node = 1;
		// init `to` to 0 if reusing
  }

  void add(const string &s){
    int curr = ROOT;
    for(auto c : s){ c -= FIRST_CHAR;
      if(to[curr][c] == 0) curr = to[curr][c] = next_node++;
      else curr = to[curr][c];
    }
    acc[curr]++;
  }

	void build_precompute(){
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
	}

	void build_non_precompute(){
    const int P = -1;
    sl[ROOT] = P;
		queue<int> q; q.push(ROOT);
    while(q.size()){
      int x = q.front(); q.pop();
      for(auto [c, child] : to[x]){
        // trying to match a prefsufix, starts with parents suffixlink
        int child_sl = sl[x]; 
        while(child_sl != P){
          if(to[child_sl].count(c)) break;
          else child_sl = sl[child_sl];
        }

				// couldnt match a prefsufix+c
        if(child_sl == P) sl[child] = ROOT; 
        else // found match (prefsufix+c)
					sl[child] = to[child_sl][c];

        q.push(child);
        sl_tree[sl[child]].push_back(child);
      }
    }
    sl[ROOT] = ROOT;
	}

  void build(){
		build_precompute();
		// build_non_precompute();

		/* IF ONLINE, bottom up for merging accs
    function<void(int)> merge_accs = [&](int x){
      for(auto y : sl_tree[x]){
        acc[y] = max(acc[x], acc[y]);
        merge_accs(y);
      }
    };
    merge_accs(ROOT); */
  }

  // ONLINE
	int go(int curr, char c){ c = c - FIRST_CHAR;
		// IF PRECOMPUTED TRANSITIONS
		return to[curr][c];

		/* IF NOT PRECOMPUTED TRANSITIONS
		while(true){
			if(to[curr].count(c)) return to[curr][c];
			else if(curr == ROOT) return ROOT;
			else curr = sl[curr];
		}*/
	}

  // OFFLINE
	vector<int> vis[N]; // OFFLINE
  // node X was visited by positions vis[x] from T
  void process(string &t){
    int curr = ROOT;
    for(int i = 0; i < t.size(); ++i){
			curr = go(curr, t[i]);
			vis[curr].push_back(i);
    }
  }

  map<int,int> ans;
  void solve(int x, int curr_on = 0){ // ATTENTION
    curr_on += acc[x];
    for(auto y : sl_tree[x]){
      solve(y, curr_on);
    }
 
    for(auto y : vis[x]){
      ans[y] += curr_on;
    }
  }
};

const int MAXN = 200100;
AhoCorasick<MAXN, 30, 'a'> aho_end, aho_start;
 
int main(){
  string s; cin >> s;
  string rs = s; reverse(rs.begin(), rs.end());
  int m = s.size();
 
	aho_end.init();
	aho_start.init();
  
  int n; cin >> n;
  for(int i = 0; i < n; ++i){
    string t; cin >> t;
    aho_end.add(t);
    reverse(t.begin(), t.end()); aho_start.add(t);
  }
 
  aho_end.build();
  aho_start.build();
 
  aho_end.process(s);
  aho_start.process(rs);
 
  aho_end.solve(aho_end.ROOT);
  aho_start.solve(aho_start.ROOT);
 
  long long ans = 0;
  for(int i = 0; i < m - 1; ++i){
    int orig_pos = i;
    int rev_pos = (m - 1 - (i + 1));
    ans += (1LL * aho_end.ans[orig_pos] * aho_start.ans[rev_pos]);
  }
  cout << ans << endl;
}
