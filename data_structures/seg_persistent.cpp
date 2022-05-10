template<int MAXN>
struct PersSegtree{
  using ValType = int;

  ValType segt[64*MAXN];
  int l_ptr[64*MAXN], r_ptr[64*MAXN];
  int time2node[MAXN];
 
  int n;
  int next_node = 0;
  int next_time = 0;
 
  ValType NEUTRAL;

  int build_node(int l, int r, ValType val){
    segt[next_node] = val;
    l_ptr[next_node] = l;
    r_ptr[next_node] = r;
    return next_node++;
  }

  // ATTENTION
  ValType BinaryOp(ValType a, ValType b){
    return a + b;
  }
 
  void init(ValType neut, int sz, vector<ValType> *v=nullptr){
    n = sz;
    NEUTRAL = neut;
    time2node[next_time++] = build(0, n - 1, v);
  }

  int build(int l, int r, vector<ValType> *init_vals){
    if(l == r){
      return build_node(l, r, (init_vals? (*init_vals)[l] : NEUTRAL));
    }else{
      int mid = (l + r) / 2;
      int left_id = build(l, mid, init_vals);
      int right_id = build(mid + 1, r, init_vals);
      return build_node(left_id, right_id, BinaryOp(segt[left_id], segt[right_id]));
    }
  }
 
  ValType _rng_query(int l, int r, int node, int lq, int rq){
    if(rq < l || lq > r) return NEUTRAL;
    else if(l >= lq && r <= rq) return segt[node];
    else{
      int mid = (l + r) / 2;
      return BinaryOp(
        _rng_query(l, mid, l_ptr[node], lq, rq),
        _rng_query(mid+1, r, r_ptr[node], lq, rq)
      );
    }
  }
  
  ValType query(int lq,int rq, int time = -1){
    if(time == -1) time = next_time - 1;
    return _rng_query(0, n - 1, time2node[time], lq, rq);
  }
  
  int update(int pos, ValType x, int time = -1){
    if(time == -1) time = next_time - 1;
    time2node[next_time] = _update_range(0, n - 1, time2node[time], pos, x);
    return next_time++;
  }

  int _update_range(int l, int r, int node, int pos, ValType val){
    if(pos > r || l > pos) return node;
    if(pos == r && pos == l){
      return build_node(-1, -1, val);
    }else{
      int mid = (l + r)/2;
      int left_id = _update_range(l, mid, l_ptr[node], pos, val);
      int right_id = _update_range(mid+1, r, r_ptr[node], pos, val);
      ValType new_val = BinaryOp(segt[left_id], segt[right_id]);
      return build_node(left_id, right_id, new_val);
    }
  }

  int kth(int k, int l, int r, vector<int> &pos, vector<int> &neg){
    if(l == r) return l;
    int tot_left = 0;
    for(auto x : pos) tot_left += segt[l_ptr[x]];
    for(auto x : neg) tot_left -= segt[l_ptr[x]];

    int mid = (l + r) / 2;
    if(tot_left >= k){
      for(auto &x : pos) x = l_ptr[x];
      for(auto &x : neg) x = l_ptr[x];
      return kth(k, l, mid, pos, neg);
    }else{
      for(auto &x : pos) x = r_ptr[x];
      for(auto &x : neg) x = r_ptr[x];
      return kth(k - tot_left, mid + 1, r, pos, neg);
    } 
  }
};
