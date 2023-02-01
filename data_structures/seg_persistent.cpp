#include<bits/stdc++.h>
using namespace std;

struct Node{

  Node operator+(const Node x){

  }
};

template<int MAXN> struct PersSegtree{
  // 4 * MAXN + 50 * MAXQ
  Node segt[64*MAXN];
  int l_ptr[64*MAXN], r_ptr[64*MAXN];
  int time2node[MAXN];
 
  int n;
  int next_node = 0;
  int next_time = 0;
 
  Node NEUTRAL;

  int build_node(int l, int r, Node x){
    segt[next_node] = x;
    l_ptr[next_node] = l;
    r_ptr[next_node] = r;
    return next_node++;
  }
 
  void init(int sz, vector<Node> *v=nullptr){
    n = sz;
    time2node[next_time++] = build(0, n - 1, v);
  }

  int build(int l, int r, vector<Node> *init_vals){
    if(l == r){
      return build_node(l, r, (init_vals? (*init_vals)[l] : NEUTRAL));
    }else{
      int mid = (l + r) / 2;
      int left_id = build(l, mid, init_vals);
      int right_id = build(mid + 1, r, init_vals);
      return build_node(left_id, right_id, segt[left_id] + segt[right_id]);
    }
  }
 
  Node _rng_query(int l, int r, int node, int lq, int rq){
    if(rq < l || lq > r) return NEUTRAL;
    else if(l >= lq && r <= rq) return segt[node];
    else{
      int mid = (l + r) / 2;
      return (_rng_query(l, mid, l_ptr[node], lq, rq) +
        _rng_query(mid+1, r, r_ptr[node], lq, rq)
      );
    }
  }
  
  Node query(int lq,int rq, int time = -1){
    if(time == -1) time = next_time - 1;
    return _rng_query(0, n - 1, time2node[time], lq, rq);
  }
  
  int update(int pos, int x, int time = -1){
    if(time == -1) time = next_time - 1;
    time2node[next_time] = _point_update(0, n - 1, time2node[time], pos, x);
    return next_time++;
  }

  int _point_update(int l, int r, int node, int i, int x){
    if(i > r || l > i) return node;
    if(i == r && i == l){
      return build_node(-1, -1, x);
    }else{
      int mid = (l + r)/2;
      int left_id = _point_update(l, mid, l_ptr[node], i, x);
      int right_id = _point_update(mid+1, r, r_ptr[node], i, x);
      return build_node(left_id, right_id, segt[left_id] + segt[right_id]);
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

int main(){

}
