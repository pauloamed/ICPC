const int MAXQ = 300010;

// OfflineDel wrapper for allowing offline addition, deletion and querying
// query function needs to be associative
// first and last queries need to be "guards"
namespace OfflineDel{
  typedef DynamicCHT DS;
  struct WrapperLine{
    TYPE m, b; int id; 
  };
  typedef WrapperLine Element;

  int n;
  DS seg[4 * MAXQ];

  void build(int query_cnt){
    n = query_cnt;
  }

  // `start` and `end`: lifespan of element
  // `e`: element to be added
  void insert(int start, int end, Element e, int p=1, int l=0, int r=n-1) {
    if(start <= l && r <= end){
			seg[p].add(e.m, e.b, e.id); // MODIFY
		}else if(end >= l && start <= r){
      int m = (l+r)/2;
      insert(start, end, e, 2*p, l, m); 
      insert(start, end, e, 2*p+1, m+1, r);
    }
  }

  // `query_param`: argument for querying DS
  // `query_function`: doesn't need to be idempotent, only associative
	TYPE query(int q_param, int q_id, int p=1, int l=0, int r=n-1) {
    TYPE ret = LLONG_MIN; // neutral
    if(seg[p].size()) ret = seg[p].query(q_param);
    if(l < r){
      int m = (l+r)/2;
      if(q_id <= m) ret = max(ret, query(q_param, q_id, 2*p, l, m));
      else ret = max(ret, query(q_param, q_id, 2*p+1, m+1, r));
    }
    return ret;
	}
}

int main(){
  cin.tie(NULL)->sync_with_stdio(false);
  int n; cin >> n;

  vector<Operation> v(n);
  // need to know:
  // when an element starts and ends
  // we are interested in all queries inside [start;end]
  // for this, we will compute and use nxt_query (start) and last_quety (end)
  // time_dist[i] = -1 if it does not die
  // next_query[i] = -1 if there isnt a query after this moment
  vector<int> time_dies(n, -1), last_query(n), next_query(n);
  int query_cnt = 0;

  for(int i = 0; i < n; ++i){
    auto &op = v[i];
    cin >> op.t;
    if(op.t == 1){
      // ADDITION
      cin >> op.to_add.first >> op.to_add.second;
    }else if(op.t == 2){
      // DELETION
      cin >> op.to_del;
      time_dies[--v[i].to_del] = i;
    }else{
      // QUERY
      cin >> op.to_query;
      query_cnt++;
    }
    last_query[i] = query_cnt;
  }

  // computing next_query
  int nxt_query_id = -1;
  for(int i = n - 1; i >= 0; --i){
    if(v[i].t == 3) nxt_query_id = last_query[i];
    next_query[i] = nxt_query_id;
  }

  OfflineDel::build(query_cnt + 1);
  for(int i = 0; i < n; ++i){
    if(v[i].t == 1){
      int start = next_query[i];
      if(start == -1) break; // there isnt any query after i
      int dies = (time_dies[i] == -1? query_cnt : last_query[time_dies[i]]);
      if(start > dies) continue; // invalid range
      OfflineDel::insert(start, dies, {v[i].to_add.first, v[i].to_add.second});
    }else if(v[i].t == 3){
      auto ret = OfflineDel::query(v[i].to_query, last_query[i]);
      if(ret == LLONG_MIN) cout << "EMPTY SET\n";
      else cout << ret << "\n";
    }
  }
}
