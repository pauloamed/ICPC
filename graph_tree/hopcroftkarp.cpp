// implements hopcroft karp algorithm and vertex cover for bipartite graph
// hopcroft karp runs in O(Vsqrt(E))
// to use it, just run the constructor with the size of the two partitions of the graph
// then add the edges with the function addEdge(), from partition U to V
// note that the vertices must be 1-indexed, as the 0 value is used for a dummy vertex
	// also, quite obvious, all indexes i must be inside [1;m] (for U) or [1;n] (for V)
// code inspired by https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/
const int INF = 2e9;
const int NIL=0;

// since this is a bipartite graph, there are two vertex sets: U and V. m = size(U), n = size(V).
// the edges to be added must go from U to V (assume that they are undirected).

// independent set: n - vertex cover
// each connected component must (?) be executed separatedly

struct bpGraph{
	int n, m;
	int *pairU;
	int *pairV;
	int *dist;
	  //adjacencies from U to V
	  vector<vector<int>> adj;
	  //adjacencies from V to U (used only on vertex cover)
	  vector<vector<int>> radj;

	  bpGraph(int _m, int _n){
	    this->n = _n;
	    this->m = _m;
	    adj = vector<vector<int>>(m+1);
	    radj = vector<vector<int>>(n+1);
	  }

	void addEdge(int u, int v){
		adj[u].push_back(v);
		radj[v].push_back(u);
	}

	bool dfs(int u){
		if (u != NIL){
		    for(auto v : adj[u]){
			if (dist[pairV[v]] == dist[u]+1){
			    if (dfs(pairV[v]) == true){
				pairV[v] = u;
				pairU[u] = v;
				return true;
			    }
			}
		    }
		    dist[u] = INF;
		    return false;
		}
		return true;
	}

	bool bfs(){
		queue<int> Q;
		for (int u=1; u<=m; u++){
		    if (pairU[u]==NIL){
			dist[u] = 0;
			Q.push(u);
		    }
		    else dist[u] = INF;
		}
		dist[NIL] = INF;
		while (!Q.empty()){
		    int u = Q.front();
		    Q.pop();
		    if (dist[u] < dist[NIL]){
			for(auto v : adj[u]){
			    if (dist[pairV[v]] == INF){
				dist[pairV[v]] = dist[u] + 1;
				Q.push(pairV[v]);
			    }
			}
		    }
		}
		return (dist[NIL] != INF);
	}

	int hopcroftKarp(){
		pairU = new int[m+1];
		pairV = new int[n+1];
		dist = new int[m+1];

		for (int u=0; u<=m; u++) pairU[u] = NIL;
		for (int v=0; v<=n; v++) pairV[v] = NIL;

		int result = 0;
		while (bfs()){
			for (int u=1; u<=m; u++)
				if (pairU[u]==NIL && dfs(u))
				    result++;
		}

		return result;
	}

	void alternate(int vertex, set<int> &su, set<int> &sv, int inU){
		if(inU){
			for(auto v : adj[vertex]){
				if(!sv.count(v) && pairU[vertex] != v){
					sv.insert(v);
					alternate(v, su, sv, 0);
				}
			}
		}
		else{
			for(auto u : radj[vertex]){
				if(!su.count(u) && pairV[vertex] == u){
					su.insert(u);
					alternate(u, su, sv, 1);
				}
			}
		}
	}

	int vertexCover(){
		hopcroftKarp();
		set<int> su;
		set<int> sv;
		set<int> matchedu;
		set<int> matchedv;
		for(int i = 1; i <= m; i++){
			if(pairU[i] == NIL) su.insert(i);
		}
		for(auto u : su){
			alternate(u, su, sv, 1);
		}
		return m-(int)su.size()+(int)sv.size();
	}
};
