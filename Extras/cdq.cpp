#include<bits/stdc++.h>
using namespace std;

#define MAXN 200010
#define ll long long

namespace BIT{
  ll bit[MAXN];
  ll query( int index ){
    ll ans(0);
    index++;
    while(index > 0){
      ans += bit[index];
      index -= index & (-index);
    }
    return ans;
  }

  void update( int index, int val ){
    index++;
    while(index < MAXN){
      bit[index] += val;
      index += index & (-index);
    }
  }
}

// CDQs idea is about processing 3d points in a specific order
// change cmp_main and process_updt for setting the desired order
namespace CDQ{
  vector<int> queries;

  struct Coord{ int x, y, z; };
  struct Event{
    Coord c;
    int query_id; // queries[query_id] += query_coeaf * pref_sum(x,y,z)
    int query_coef;
    int updt_val; // (x,y,z) += val
    // Event is updt iff query_id = -1
  };
  
  vector<Event> events;
  void add_query(int x, int y, int z, int query_id, int coef){ events.push_back({{x,y,z}, query_id, coef, -1}); }
  void add_update(int x, int y, int z, int val){ events.push_back({{x,y,z}, -1, 0, val}); }


  // MODIFY
  bool cmp_main(Event &a, Event &b){
    if(a.c.x == b.c.x){
      if(a.c.y == b.c.y) return a.c.z < b.c.z;
      else return a.c.y < b.c.y;
    }
    else return a.c.x > b.c.x;
  }

  // MODIFY (also sorts)
  bool process_updt(Event &updt, Event &query){
    return updt.c.y > query.c.y;
  }

  void solve_2d(int start_u, int end_u, int start_q, int end_q, vector<Event> &output){
    // querying on q_e (ignore updates)
    // updating from u_e (ignore queries)
    int curr_u = start_u;
    for(int curr_q = start_q; curr_q <= end_q; ++curr_q){
      int q_id = events[curr_q].query_id;
      while(curr_u <= end_u && process_updt(events[curr_u], events[curr_q])){
        output.push_back(events[curr_u]);
        if(events[curr_u].query_id == -1){
          BIT::update(events[curr_u].c.z, events[curr_u].updt_val);
        }
        curr_u++;
      }

      output.push_back(events[curr_q]);

      if(q_id != -1){
        int qv = BIT::query(events[curr_q].c.z);
        queries[q_id] += events[curr_q].query_coef * qv;
      }
    }

    for(int i = start_u; i < curr_u; ++i){
      if(events[i].query_id == -1) BIT::update(events[i].c.z, -events[i].updt_val);
    }

    for(int i = curr_u; i <= end_u; i++) output.push_back(events[i]);
  }

  void solve_3d(int l, int r){ // [l;r]
    if(l == r) return;
    int m = (l + r) / 2;

    solve_3d(l, m); solve_3d(m + 1, r);

    vector<Event> new_l_r;

    // solve_2d(updates, queries)
    solve_2d(l, m, m + 1, r, new_l_r);

    assert(new_l_r.size() == (r - l + 1));
    std::copy(new_l_r.begin(), new_l_r.end(), events.begin() + l); 
  }

  void run(int qs){
    queries = vector<int>(qs);
    sort(events.begin(), events.end(), cmp_main);
    solve_3d(0, (int)events.size() - 1);
  }
}

/* https://zerojudge.tw/ShowProblem?problemid=c571
int32_t main(){
  cin.tie(NULL)->sync_with_stdio(false);

  int n; cin >> n;
  for(int i = 0; i < n; ++i){
    int a, b, c; cin >> a >> b >> c;
    CDQ::add_update(a, b, c, 1);
    CDQ::add_query(a, b, c, i, -1);
    CDQ::add_query(a, b, MAXN - 2, i, +1);
  }
  CDQ::run(n);
  
  for(int i = 0; i < n; ++i){
    cout << CDQ::queries[i] << "\n";
  }
}
*/

/* https://codeforces.com/contest/1093/problem/E
int32_t main(){
  cin.tie(NULL)->sync_with_stdio(false);

  int n, e; cin >> n >> e;
  int v[2][n];
  for(int j = 0; j < 2; ++j){
    for(int i = 0; i < n; ++i){
      cin >> v[j][i]; v[j][i]--;
    }
  }
  
  int pos[2][n];
  for(int j = 0; j < 2; ++j){
    for(int i = 0; i < n; ++i){
      pos[j][v[j][i]] = i;
    }
  }

  for(int x = 0; x < n; ++x){
    CDQ::add_update(-1, pos[0][x], pos[1][x], 1);
  }

  int q = 0;
  for(int i = 0; i < e; ++i){
    int id; cin >> id;
    if(id == 1){
      int la, ra, lb, rb; cin >> la >> ra >> lb >> rb;
      la--, ra--, lb--, rb--;
      // 2d sum from (la, lb) to (ra, rb)
      CDQ::add_query(i, ra, rb, q, 1);
      CDQ::add_query(i, la - 1, lb - 1, q, 1);
      CDQ::add_query(i, ra, lb - 1, q, -1);
      CDQ::add_query(i, la - 1, rb, q, -1);
      q++;
    }else{
      int x, y; cin >> x >> y; x--, y--; // swap x,y perm
      int val1 = v[1][x];
      int val2 = v[1][y];

      CDQ::add_update(i, pos[0][val1], pos[1][val1], -1);
      CDQ::add_update(i, pos[0][val2], pos[1][val2], -1);

      swap(v[1][x], v[1][y]);
      pos[1][v[1][x]] = x;
      pos[1][v[1][y]] = y;

      CDQ::add_update(i, pos[0][val1], pos[1][val1], +1);
      CDQ::add_update(i, pos[0][val2], pos[1][val2], +1);
    }
  }

  CDQ::run(q);
  
  for(int i = 0; i < q; ++i){
    cout << CDQ::queries[i] << "\n";
  }
}
*/