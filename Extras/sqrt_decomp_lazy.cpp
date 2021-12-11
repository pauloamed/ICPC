// https://codeforces.com/gym/101889 D

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define MAXN 100010
#define BLOCK_SIZE 500
#define NUM_BLOCKS 500

// CONSTS
int block_id[MAXN];
int block_start[NUM_BLOCKS];
int block_size[NUM_BLOCKS];

// VAR
int v[MAXN];
int block2color[NUM_BLOCKS][MAXN];
int lazy[NUM_BLOCKS];

int N;

void update_pos(int i, int x){ // i: idx de posicao
  int b = block_id[i];
  block2color[b][v[i]]--;
  v[i] = x;
  block2color[b][v[i]]++;
}

void maybe_lazy(int b){ // b: idx de algum bloco
  if(lazy[b] == 0) return;
  for(int i = block_start[b]; i < N; i++){
    if(block_id[i] != b) break;
    update_pos(i, lazy[b]);
  }
  lazy[b] = 0;
}

int query(int x){
  int ans = 0;
  for(int b = 0; b < NUM_BLOCKS; ++b){
    if(lazy[b] == 0){
      ans += block2color[b][x];
    }else if(lazy[b] == x){
      ans += block_size[b];
    }
  }
  return ans;
}

void update(int l, int r, int x){

  if(block_id[l] == block_id[r]){ // sqrt(N)
    maybe_lazy(block_id[l]);
    for(int i = l; i <= r; ++i) update_pos(i, x);
  }else{
    int lb = block_id[l];
    int rb = block_id[r];

    maybe_lazy(lb);
    maybe_lazy(rb);

    for(int i = l; i < N; ++i){
      if(block_id[i] != lb) break;
      update_pos(i, x);
    }
    for(int i = block_start[rb]; i <= r; ++i){
      update_pos(i, x);
    }

    // sqrt(N)
    for(int i = lb + 1; i < rb; ++i){
      lazy[i] = x;
    }
  }
}


int32_t main(){
  cin.tie(NULL)->sync_with_stdio(false);

  int _, q; cin >> N >> _ >> q;

  for(int i = N - 1; i >= 0; --i){
    int b = i / BLOCK_SIZE;
    block_start[b] = i;
    block_id[i] = b;
    block_size[b]++;
    block2color[b][1]++;
    v[i] = 1;
  }

  for(int i = 0; i < q; ++i){
    ll p, x, a, b; cin >> p >> x >> a >> b;
    ll s = query(p);
    s %= N, a %= N, b %= N;
    // cout << p << " " << s << endl;
    int l = (a + (s * s)) % N;
    int r = (a + (s + b) * (s + b)) % N;
    if(l > r) swap(l, r);
    update(l, r, x);
  }


  map<int,int> cnt;
  int maxv = 0;
  for(int i = 0; i < N; ++i){
    // cout << v[i] << " ";
    maybe_lazy(block_id[i]);
    maxv = max(maxv, ++cnt[v[i]]);
  }
  cout << maxv << endl;
}