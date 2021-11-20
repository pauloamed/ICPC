// https://codeforces.com/gym/103388/problem/F

#include<bits/stdc++.h>
using namespace std;

#define MAXN 5000000

struct Point{
    int x, y;
    Point(){}
    Point(int a, int b):x(a),y(b){}
    bool operator==(Point const& p) const{ return x==p.x && y==p.y;}
};


int orient(Point a, Point b, Point c){
    pair<int,int> ba = {b.x - a.x, b.y - a.y};
    pair<int,int> ca = {c.x - a.x, c.y - a.y};
    auto ret = 1LL * ba.first * ca.second - 1LL * ba.second * ca.first;
    if(ret < 0) return -1;
    else if(ret > 0) return 1;
    else return 0;
}

struct Segment{
    Point l, r;
    int pol_id, seg_id;
    bool is_upper;

    Segment(Point A, Point B, int pol, int id){
        seg_id = id;
        is_upper = A.x > B.x;
        pol_id = pol;
        l = A, r = B;
        if(is_upper) swap(l, r);
    }

    // it is guaranteed that *this and s intersect in x axis
    bool operator<(const Segment &s) const{ // *this is less then s => this vem embaixo
        // se os segmentos se tocam, fica ordenado antes quem chegou antes
        if(s.r == r) return orient(l, r, s.l) > 0;
        else if(s.r.x <= r.x) return orient(l, r, s.r) > 0; // R do S ta na minha range
        else return orient(s.l, s.r, r) < 0; // meu R ta na range de S
    }

    bool operator<(const Point & p) const{ 
        // query para lower_bound: achar primeiro segmento que essa condicao falha
        // achar primeiro segmento em que o ponto nao ta dentro nem acima
        return orient(l, r, p) >= 0;
    }

    void print() const{
        printf("Pol: %d L.X: %d L.Y: %d R.X: %d R.Y: %d ID: %d\n", pol_id, l.x, l.y, r.x, r.y, seg_id);
    }
};

vector<Segment> pols;
vector<Point> pol_heads;
vector<int> x_coords;
vector<int> events[MAXN][3];
int parent[MAXN];

void retrieve_parents(){
    multiset<Segment,less<>> active_segments;
    
    for(int i = 0; i < x_coords.size(); ++i){
        // remove todo mundo
        for(auto seg_id : events[i][1]){
            assert(active_segments.erase(pols[seg_id]));
        }
        // insere todo mundo
        for(auto seg_id : events[i][0]){
            assert(active_segments.insert(pols[seg_id]) != active_segments.end());
        }

        // faz as queries, de cima pra baixo
        sort(events[i][2].begin(), events[i][2].end(), 
        [](int a, int b) -> bool{ return pol_heads[a].y > pol_heads[b].y; });

        for(auto query : events[i][2]){
            auto it = active_segments.lower_bound(pol_heads[query]);
            if(it == active_segments.end()) continue;
            if(it->is_upper) parent[query] = it->pol_id;
            else parent[query] = parent[it->pol_id];
        }
    }
}

vector<int> v[MAXN];
int ans;

int solve(int x, int prof){
    if(v[x].empty()) return prof;

    // cout << x << " " << ans << "\n";

    vector<int> childs;
    for(auto y : v[x]) childs.push_back(solve(y, prof + 1));
    childs.push_back(prof);
    sort(childs.rbegin(), childs.rend());   
    
    ans = max(ans, 2 * childs[0] + childs[1] - 2 * prof);

    return childs[0];
}

bool cmp(const Segment &a, const Segment &b){
    if(a.l.x == b.l.x) return a.l.y > b.l.y;
    else return a.l.x < b.l.x;
}

int main(){
    cin.sync_with_stdio(false);
    cin.tie(NULL);
    memset(parent, -1, sizeof parent);
    int n; cin >> n;

    for(int j = 0; j < n; ++j){
        int k; cin >> k;
        vector<Point> pts;

        for(int i = 0; i < k; ++i){
            int a, b; cin >> a >> b;
            pts.push_back(Point{a, b});
            x_coords.push_back(a);
        }

        for(int i = 0; i < k; ++i){
            int next = (i + 1) % k;
            if(pts[i].x != pts[next].x) pols.push_back(Segment(pts[i], pts[next], j, -1));
        }

        // K
        pol_heads.push_back(pts[0]);
        for(auto pt : pts){
            if(pt.x < pol_heads.back().x) pol_heads.back() = pt;
            else if(pt.x == pol_heads.back().x && pt.y > pol_heads.back().y) pol_heads.back() = pt;
        }
    }

    // N log N
    sort(pols.begin(), pols.end(), cmp); 
    for(int i = 0; i < pols.size(); ++i) pols[i].seg_id = i;

    // K log K
    sort(x_coords.begin(), x_coords.end());
    x_coords.resize(unique(x_coords.begin(), x_coords.end()) - x_coords.begin());
    
    // K log K
    for(int i = 0; i < pols.size(); ++i){
        int start = lower_bound(x_coords.begin(), x_coords.end(), pols[i].l.x) - x_coords.begin();
        int endd = lower_bound(x_coords.begin(), x_coords.end(), pols[i].r.x) - x_coords.begin();
        events[start][0].push_back(i);
        events[endd][1].push_back(i);
    }


    // N log N
    for(int i = 0; i < n; ++i){
        int start = lower_bound(x_coords.begin(), x_coords.end(), pol_heads[i].x) - x_coords.begin();
        events[start][2].push_back(i);
    }


    retrieve_parents();

    // N
    for(int i = 0; i < n; ++i){
        if(parent[i] != -1) v[parent[i]].push_back(i);
        else v[n].push_back(i);
    }

    // N
    ans = -1;
    solve(n, 0);
    cout << ans << "\n";
}
