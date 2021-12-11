#include<bits/stdc++.h>
using namespace std;

#define FIRST_LETTER '0' // first letter of the alphabet
#define N 100010 // number of states: sum of length of all patterns
#define ALFA 80 // size of alfabet


struct AhoCorasick{
	// MEMORY: THETA(ALFA * N)

	// TIME:
	//	addString: THETA(|S|)
	//  init(): THETA(ALFA * N)

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

	int suffixLink[N], term[N];
	int to[N][ALFA];
	int stateCount = 1;

	AhoCorasick(){}

	int addString(const char *str, int id){ // basic trie insertion
		// (id: could be used for adding the id to a term vector)
		int curr = 1; // current state: initial state 1
		int i = 0; // will be used to get the string size
		for(i = 0; str[i]; i++){ // for each char at the string
			int ch = str[i] - FIRST_LETTER; // retrive char id
			// if the following state hasnt been computed yet, create a new one
			if(!to[curr][ch]) to[curr][ch] = ++stateCount;
			curr = to[curr][ch]; // go to the following state
		}
		term[curr]++; // mark that another string ends on this state
		return curr;
	}

	void init(){
		// init suffixLinks to the starting state
		for(int i = 0; i < stateCount; i++) suffixLink[i] = 1;

		// preparing queue for BFS adding the start state
		queue<int> q; q.push(1);

		while(!q.empty()){ // for all reachable nodes
			int u = q.front(); q.pop(); // retriving node from bfs' queue
			for(int i = 0; i < ALFA; i++){ // for each edge (transition) (letter of the alfabet)
				if(to[u][i]){ // if there is an active transition (from trie)
					int v = to[u][i]; q.push(v); // add it to the queue
					if(u != 1){
						// just as in KMP construction in success case
						suffixLink[v] = to[suffixLink[u]][i];
						// if the suffixLink[v] state is a valid string
						// since s[i-suffixLink[v]:i] = string(suffixLink[v])
						// Im also a terminal state and represent the same as those from my
						// suffixlink
						term[v] += term[suffixLink[v]];
					}
				}else if(u != 1){
					// I'm not on the start state and there is no active conn:
					// I will values (DP) from already computed states
					// as in suffix automata
					to[u][i] = to[suffixLink[u]][i];
				}else{
					// I'm on the start state and there is no active connection:
					// I will stay on the start state
					to[u][i] = 1;
				}
			}
		}
	}

	int go(int x, char c){
		return to[x][c - FIRST_LETTER];
	}
};

AhoCorasick aho; // se botar pra alocar na stack pode dar seg fault kkkk
