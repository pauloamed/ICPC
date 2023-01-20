namespace circular_arc{
bool between(int l, int r, int x){
  if(l > r) return (x >= l || x <= r);
  else return (x >= l && x <= r);
}
 
bool intersect(pair<int,int> &a, pair<int,int> &b){
	return (between(a.first, a.second, b.first) || between(a.first, a.second, b.second) || 
		between(b.first, b.second, a.first) || between(b.first, b.second, a.second));
}
 
struct Point{
	int x, arc_id;
	bool is_l;
	bool operator<(const Point &b) const{
		if(x == b.x) return is_l > b.is_l;
		else return x < b.x;
	}
};
 
vector<pair<int,int>> v;
vector<int> gd; // last one is not in GD

Point pts[2 * MAXN];
bool is_open[MAXN], vis[MAXN];
int n, next[MAXN], time_vis[MAXN][2];

vector<int> get_cycle(){
	stack<int> path;

	vector<int> cycle; 
	int x = 0;
	while(true){ vis[x] = 1;
		path.push(x);
		if(vis[next[x]]){
			do{
				cycle.push_back(path.top());
				vis[path.top()] = 0;
				path.pop();
			}while(cycle.back() != next[x]);
			break;
		} else x = next[x];
	}

	while(path.size()){
		vis[path.top()] = 0; path.pop();
	}
	return cycle;
}
 
void compute_next(){
	memset(is_open, 0, sizeof(bool) * n);
	for(int i = 0; i < n; ++i){
		time_vis[i][0] = time_vis[i][1] = next[i] = -1;
	}
 
	queue<int> closed;
	for(int i = 0; i < 6 * n; ++i){
		int j = i % (2 * n);
		auto [p, arc_id, is_l] = pts[j];
 
		if(is_l){ // is L
			time_vis[arc_id][0] = i;
			is_open[arc_id] = 1;
		}else if(is_open[arc_id]){ // is R and already openned
			time_vis[arc_id][1] = i;
			is_open[arc_id] = 0;
			while(closed.size()){
				if(closed.front() != arc_id){
					if(time_vis[arc_id][0] < time_vis[closed.front()][1]) 
						break;
				}
				next[closed.front()] = arc_id;
				closed.pop();
			}
			if(next[arc_id] == -1)
				closed.push(arc_id);
		}
	}
}
 
void compute_gd(const vector<int> &cycle){
	gd.clear();
	int i = cycle[0];
	gd.push_back(i);
	for(int j = 1; j < cycle.size(); ++j){
		gd.push_back(cycle[j]);
		if(intersect(v[i], v[cycle[j]])) break;
	}
}

void built_pts(int MAX_COORD){
	if(true){ // v sorted
	
	auto norm = [&](int x){ return (x + MAX_COORD) % MAX_COORD; };
	for(int i = 0; i < n; ++i){
		pts[i] = {v[i].first, i, 1};
		pts[i + n] = {v[i].second, i, 0};
	}
	for(auto &[l, r] : v) l = norm(l), r = norm(r);	

	inplace_merge(pts, pts + n, pts + 2 * n);
	int m = lower_bound(pts, pts + 2 * n, MAX_COORD, [](Point &p, int x){
		return p.x < x;
	}) - pts;
	for(int i = 0; i < 2 * n; ++i) pts[i].x = norm(pts[i].x);
	inplace_merge(pts, pts + m, pts + 2 * n);

	return;
	}

	// v not sorted
	for(int i = 0; i < n; ++i){
		pts[2 * i] = {v[i].first, i, 1};
		pts[2 * i + 1] = {v[i].second, i, 0};
	}

	sort(pts, pts + 2 * n, [](Point &a, Point &b){
		if(a.x == b.x) return a.is_l > b.is_l;
		else return a.x < b.x;
	});
}
 
int get_min_clique(const vector<pair<int,int>> &_v, int MAX_COORD = MAXN){
	v = _v;
	n = v.size();
	if(n == 0) return 0;
	 
	built_pts(MAX_COORD);
	compute_next(); 
	compute_gd(move(get_cycle()));
 
	if(gd.size() == 1) return 1;
	if(gd.front() == gd.back()) return gd.size() - 1;
	else return gd.size();
}
}
