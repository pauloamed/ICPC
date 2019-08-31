
struct {
	// in order to use, you should define 'total', which is the amount of nodes in the
	// flow graph.
	// the algorithm will create a matrix with size total*total.
	// the complexity of the algorithm is O(VE^2)
	vector<vector<int>> capacity(total, vector<int>(total, 0));
	
	// the adjacency list must represent an UNDIRECTED graph,
	// which means it should contain u->v and v->u edges
	vector<vector<int>> adj(total);
	 
	int bfs(int s, int t, vector<int>& parent) {
		fill(parent.begin(), parent.end(), -1);
		parent[s] = -2;
		queue<pair<int, int>> q;
		q.push({s, INF});
	 
		while (!q.empty()) {
		    int cur = q.front().first;
		    int flow = q.front().second;
		    q.pop();
	 
		    for (int next : adj[cur]) {
		        if (parent[next] == -1 && capacity[cur][next]) {
		            parent[next] = cur;
		            int new_flow = min(flow, capacity[cur][next]);
		            if (next == t)
		                return new_flow;
		            q.push({next, new_flow});
		        }
		    }
		}
	 
		return 0;
	}
	 
	int maxflow(int s, int t) {
		int flow = 0;
		vector<int> parent(total); 
		int new_flow;
	 
		while ((new_flow = bfs(s, t, parent))) {
		    flow += new_flow;
		    int cur = t;
		    while (cur != s) {
		        int prev = parent[cur];
		        capacity[prev][cur] -= new_flow;
		        capacity[cur][prev] += new_flow;
		        cur = prev;
		    }
		}
	 
		return flow;
	}
} edmondskarp;

int main(){
	
}
