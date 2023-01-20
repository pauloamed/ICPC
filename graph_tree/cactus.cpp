namespace cactus{
	vector<vector<int>> get_cycles(int* to, int n){
		queue<int> q;
 
		vector<int> indeg(n, 0);
		for(int i = 0; i < n; ++i) indeg[to[i]]++;
		for(int i = 0; i < n; ++i) if(indeg[i] == 0)
			q.push(i);
 
		while(q.size()){
			int x = q.front(); q.pop();
			if(--indeg[to[x]] == 0)
				q.push(to[x]);
		}
 
		vector<vector<int>> cycles;
		for(int i = 0; i < n; ++i) if(indeg[i] == 1){
			vector<int> cycle;
			int x = to[i];
			while(true){
				cycle.push_back(x);
				indeg[x] = 0;
				if(x == i) break;
				x = to[x];
			}
			cycles.push_back(cycle);
		}
		return cycles;
	}
}
