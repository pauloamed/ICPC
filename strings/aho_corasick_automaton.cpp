#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int MAXN = 100010;

// N: number of states: sum of length of all patterns
template<int N, int ALPHA_SIZE, char FIRST_LETTER> 
struct AhoCorasickAutomaton{
	// MEMORY: THETA(ALFA * N)

	// TIME:
	//	addString: THETA(|S|)
	//  init(): THETA(ALPHA_SIZE * N)

	// stateCount: number of active states
	// suffixLink[i]: link to the state S representing the greater preffix that is also a suffix on s[:i]
	// term[i]: indicates how many strings end at the state i. Can be extended to indicating the size of a
	// string ending on that state OR a vector of states ending there
	// to[i][x]: transition from state i using letter x

	// addString: adds a string to the trie
	// init: prepare the automaton for being use. Uses a BFS

	// #####: once you add a new string, you need to use init() once again

	// STATE 0: not a real state, used for marking non init values
	int next_node;
	const int START_STATE = 1;
  int suffixLink[N];
	int to[N][ALPHA_SIZE];

  struct Node{
    int pts, occur;
    Node(int pt=0, int occ=0){ pts = pt, occur = occ; }
  };
  Node acc[N];

	AhoCorasickAutomaton(){}

  void build(int n){
    next_node = 2;
    for(int i = 0; i < n; ++i) memset(to[i], 0, sizeof to[i]);
  }

	int add(string &s, vector<int> &pts){ // string and string_id
		int curr = START_STATE;
		
		for(int i = 0; i < s.size(); i++){
			int ch = s[i] - FIRST_LETTER;
			if(!to[curr][ch]){
        to[curr][ch] = next_node++;
        acc[to[curr][ch]] = Node();
      }
      curr = to[curr][ch];

      // adding all prefixes
      acc[curr].occur++;
      acc[curr].pts = max(acc[curr].pts, pts[i]);
		}

		// acc[curr] = s.size(); // may add only the whole string also
		return curr;
	}

  vector<int> sl_tree[N];
  void traverse_tree(int x){
    // cout << x << " " << acc[x].pts << endl;
    for(auto y : sl_tree[x]){
      traverse_tree(y);
      acc[x].pts = max(acc[x].pts, acc[y].pts);
    }
    // cout << x << " " << acc[x].pts << endl;
  }

	void init(){
		for(int i = 0; i < next_node; i++){
      suffixLink[i] = START_STATE;
      sl_tree[i].clear();
    }
		queue<int> q; q.push(START_STATE);

		while(!q.empty()){
			int u = q.front(); q.pop();
			for(int i = 0; i < ALPHA_SIZE; i++){
				if(to[u][i]){ // existent transition from `u` using `i`
					int v = to[u][i]; q.push(v);
          
					if(u != START_STATE){
						// just as in KMP construction in success case
						suffixLink[v] = to[suffixLink[u]][i]; // since s[i-suffixLink[v]:i] = string(suffixLink[v])
            // do some suffix link stuff
					}
          sl_tree[suffixLink[v]].push_back(v);
				}else{ // inexistent transition from `u` using `i`, if theres a suffixlink, uses it
          if(u != START_STATE) to[u][i] = to[suffixLink[u]][i];
          else to[u][i] = START_STATE;
        }
			}
		}

    traverse_tree(START_STATE);
	}

	int go(int x, char c){
		return to[x][c - FIRST_LETTER];
	}
};

AhoCorasickAutomaton<MAXN, 30, 'a'> aho; 

int main(){
  freopen("exciting.in", "r", stdin);
  int t; cin >> t;
  while(t--){
    int n; cin >> n;
    int tot_sz = 0;
    vector<string> vs(n); 
    for(auto &s : vs){
      cin >> s;
      tot_sz += s.size();
    }
    aho.build(tot_sz + 10);

    for(int i = 0; i < n; ++i){
      vector<int> v(vs[i].size());
      for(auto &x : v) cin >> x;
      aho.add(vs[i], v);
    }
    aho.init();

    ll ans = 0;
    for(int j = 0; j < n; ++j){
      auto &s = vs[j];
      int curr = aho.START_STATE;
      for(int i = 0; i < s.size(); ++i){
        curr = aho.go(curr, s[i]);
        ll val = 1LL * aho.acc[curr].occur * aho.acc[curr].pts * (i + 1);
        ans = max(ans, val);
      }
    }
    cout << ans << endl;
  }
}
