// http://www.usaco.org/index.php?page=viewproblem2&cpid=533

#include<bits/stdc++.h>
using namespace std;


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

	// #####: once you add a string, you need to use init() once again

	// state 0: not a real state, used for marking non init values
	// state 1: start state
	int next_node = 2;
	const int START_STATE = 1;
	

	int to[N][ALPHA_SIZE];
  int acc[N];

	AhoCorasickAutomaton(){}

	int add(string &s, int id){ // basic trie insertion
		// (id: could be used for adding the id to a acc vector)
		int curr = START_STATE; // current state: initial state 1
		
		for(int i = 0; i < s.size(); i++){ // for each char at the string
			int ch = s[i] - FIRST_LETTER; // retrive char id
			// if the following state hasnt been computed yet, create a new one
			if(!to[curr][ch]) to[curr][ch] = next_node++;
			curr = to[curr][ch]; // go to the following state
		}

    // ATTENTION: PROBLEM SPECIFIC
    // WHAT SHOULD BE KEPT AT THE ENDING NODE?
		acc[curr] = s.size();
		return curr;
	}

	int suffixLink[N];

	void init(){
		// init suffixLinks to the starting state
		for(int i = 0; i < next_node; i++) suffixLink[i] = START_STATE;

		// preparing queue for BFS adding the start state
		queue<int> q; q.push(START_STATE);

		while(!q.empty()){ // for all reachable nodes
			int u = q.front(); q.pop(); // retriving node from bfs' queue
			for(int i = 0; i < ALPHA_SIZE; i++){ // for each edge (transition) (letter of the alfabet)
				if(to[u][i]){ // if there is an active transition (from trie)
					int v = to[u][i]; q.push(v); // add it to the queue
					if(u != START_STATE){
						// just as in KMP construction in success case
						suffixLink[v] = to[suffixLink[u]][i];
						// if the suffixLink[v] state is a valid string
						// since s[i-suffixLink[v]:i] = string(suffixLink[v])
						// Im also a terminal state and represent the same as those from my
						// suffixlink

						acc[v] = max(acc[v], acc[suffixLink[v]]);
					}
				}else if(u != START_STATE){
					// I'm not on the start state and there is no active conn:
					// I will values (DP) from already computed states
					// as in suffix automata
					to[u][i] = to[suffixLink[u]][i];
				}else{
					// I'm on the start state and there is no active connection:
					// I will stay on the start state
					to[u][i] = START_STATE;
				}
			}
		}
	}

	int go(int x, char c){
		return to[x][c - FIRST_LETTER];
	}
};

AhoCorasickAutomaton<100010, 30, 'a'> aho; 

int main(){
  freopen("censor.in", "r", stdin);
  freopen("censor.out", "w", stdout);
  string t; cin >> t;
  int n; cin >> n;
  for(int i = 0; i < n; ++i){
    string s; cin >> s;
    aho.add(s, i);
  }

  aho.init();

	string ans;
	stack<int> states;
	states.push(aho.START_STATE);
	for(int i = 0; i < t.size(); ++i){
		states.push(aho.go(states.top(), t[i]));
		ans.push_back(t[i]);
		if(aho.acc[states.top()]){
			// cout << "?" << endl;
			int x = aho.acc[states.top()];
			while(x--){
				states.pop();
				ans.pop_back();
			}
		}
	}
	cout << ans << endl;
}