// https://www.codechef.com/problems/MIXFLVOR
// two pointers
// internal state is 2 stacks ressembling a queue
// may be used for keeping structres with no REMOVE operation and MERGE op
// keeps merging top of left stack with top of right stack

#include<bits/stdc++.h>
using namespace std;

#define BITS 31

struct Gaussian{
  bitset<BITS> m[BITS];

  int add(bitset<BITS> x){
    for(int i = 0; i < BITS; ++i){
      int j = BITS - 1 - i;
      if(!x.any()) return -1;
      // checando pos i e pos i no vetor x
      if(x[j]){ // tenho bit ativo nessa posicao
        // tem um vetor nessa posicao
        if(m[i][j]) x ^= m[i];
        else{ // adiciono
          m[i] = x; return i;
        }
      }
    }
    return -1;
  }

  int getMax(){
    bitset<BITS> ans;
    for(int i = 0; i < BITS; ++i){
      int j = BITS - 1 - i;
      if(m[i][j] && !ans[j]) ans ^= m[i];
    }
    return ans.to_ulong();
  }
};

int getMaxFromMerge(stack<Gaussian> &a, stack<Gaussian> &b){
  Gaussian ret;
  if(a.size()) ret = a.top();
  if(b.size()){
    for(int i = 0; i < BITS; ++i) ret.add(b.top().m[i]);
  }
  return ret.getMax();
}


int main(){
  int t; cin >> t;
  while(t--){
    int n; long long k;
    cin >> n >> k;

    vector<int> c, f;
    for(int i = 0; i < n; ++i){
      int x, y; cin >> x >> y;
      c.push_back(x); f.push_back(y);
    }

    stack<Gaussian> backward, forward;
    int l = 0, r = 0; // nao adicionei r ainda
    long long currSum = 0;
    int ans = 0;

    while(l < n){
      if(r < l){
        r = l, currSum = 0;
        forward = stack<Gaussian>();
      }

      // increasing r
      while(r < n && currSum + c[r] <= k){
        // adding r to Gaussian Struct
        auto lastAdded = Gaussian();
        if(forward.size()) lastAdded = forward.top();
        lastAdded.add(bitset<BITS>(f[r]));
        forward.push(lastAdded);
        currSum += c[r++];
      }

      ans = max(ans, getMaxFromMerge(forward, backward));
      // removing left side
      // if r == l (cant add this flavour), wont change anything
      if(backward.empty() && r != l){
        Gaussian curr;
        for(int i = r - 1; i >= l; --i){
          curr.add(bitset<BITS>(f[i]));
          backward.push(curr);
        }
        forward = stack<Gaussian>();
      }

      if(backward.size()) backward.pop();
      currSum -= c[l++];
    }

    cout << ans << endl;
  }
}
