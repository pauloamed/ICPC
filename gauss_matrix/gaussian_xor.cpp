const int MAXN = 1500;

namespace xor_base{
  // number of vectors in basis
  // size of vector space is 2^cnt
  int cnt = 0;
  bitset<MAXN> base[MAXN];
  bitset<MAXN> aux[MAXN];
  
  // adds X as basis of vector space
  // returns -1 if it is already inside the span
  // runs in O(N^2/64)
  int add(bitset<MAXN> &x){
    bitset<MAXN> auxX(0);
    for(int i = MAXN - 1; i >= 0; --i){
      if(!x[i]) continue;
      if(!base[i][i]){ cnt++;
        base[i] = x, auxX[i] = 1;
        aux[i] = move(auxX);
        return i;
      }
      x ^= base[i];
      auxX ^= aux[i];
    }
    return -1;
  }
  
  // checks if X is inside the span
  // if it is, returns the linear combination of base vectors
  // runs in O(N^2/64)
  bitset<MAXN> query(bitset<MAXN> &x){
    bitset<MAXN> ans(0);
    for(int i = MAXN - 1; i >= 0; --i){
      if(x[i] && base[i][i]){
        x ^= base[i];
        ans ^= aux[i];
      }
    }
    return (x.any()? bitset<MAXN>(0) : ans);
  }

  // get maximum value inside the span
  // runs in O(N^2/64)
  int get_max(){
    bitset<MAXN> ans;
    for(int i = MAXN - 1; i >= 0; --i){
      if(base[i][i] && !ans[i]){
        ans ^= base[i];
      }
    }
    return ans.to_ulong();
  }

  // get kth value inside the span
  // runs in O(N^2/64)
  int get_kth(int k){
    int curr_cnt = cnt;

    bitset<MAXN> ans;
    for(int i = MAXN - 1; i >= 0; --i){
      if(!base[i][i]) continue;
      int half = (1 << (curr_cnt - 1));
      if(!ans[i]){
        if(k > half){
          ans ^= base[i];
          k -= half;
        }
      }else{
        if(k <= half) ans ^= base[i];
        else k -= half;
      }
      curr_cnt--;
    }
    return ans.to_ulong();
  }
}
