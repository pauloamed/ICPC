namespace ahocorasick {
	const static int K = 26; // size of the alphabet
	// this structure allows insertion of several strings in O(m*K)
	// where m is the sum of the sizes of all strings and K is the size of 
	// the alphabet.
	// every node in the automaton represents some prefix of a string
	// let s(v) be the string represented by the node v
	// every link through character c going from v represents the largest 
	// suffix of s(v)+c that is contained inside the trie

	// node structure used in trie/automaton
	struct node {
		int next[K];
		bool leaf = false;
		int p = -1;
		char pch;
		int link = -1;
		int go[K];

		node(int _p=-1, char _ch='$') : p(_p), pch(_ch) {
		    fill(begin(next), end(next), -1);
		    fill(begin(go), end(go), -1);
		}
	};

	// stores the whole trie/automaton
	vector<node> t{1};

	// adds string to automaton, runs in O(|s|)
	void add_string(const string& s){
		int v = 0;
		for(char ch : s){
			int c = ch-'a';
			if(t[v].next[c] == -1){
				t[v].next[c] = (int)t.size();
				t.emplace_back(v, ch);
			}
			v = t[v].next[c];
		}
		t[v].leaf = true;
	}

	int go(int, char);

	int get_link(int v){
		if(t[v].link == -1){
			if(v == 0 || t[v].p == 0) t[v].link = 0;
			else t[v].link = go(get_link(t[v].p), t[v].pch);
		}
		return t[v].link;
	}
	
	// this function is the heart of the algorithm.
	// v is the position of the vertex of the automaton
	// ch is the character to which you want to make the transition
	// returns the node representing the largest suffix of the string
	// represented by v
	int go(int v, char ch){
		int c = ch-'a';
		if(t[v].go[c] == -1){
			if(t[v].next[c] != -1) t[v].go[c] = t[v].next[c];
			else t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
		}
		return t[v].go[c];
	}
}
