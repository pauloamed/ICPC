#define MAXN 400020
#define K 19

namespace SA{
	using arrayType = string; // vector<int>

  // suffix id is position where it starts
  // id(s[i...]) = i

  // r is indexed using suffix id
  vector<int> r; // r[i]: equiv class (order) of suffix s[i...]

  // p is indexed using suffix order id
  vector<int> p; // p[i]=j: suffix s[j...] is in index i in order

  int h; // step in suffix array construction (in 2^i form)
  
	int n;
  arrayType s;

	void n_alpha_sort(int offset){
		vector<int> cnt(n);
		for(int i = 0; i < n; ++i) 
			cnt[r[(i + offset) % n]]++;

		vector<int> pos(n); // positon where each bucket starts
		for(int i = 1; i < n; ++i) 
			pos[i] = pos[i - 1] + cnt[i - 1];

		vector<int> tmp(n); // tmp vector for keeping new p order
		for(int i = 0; i < n; ++i){
			int eqivClass = r[(p[i] + offset) % n]; // eqiv class for first/second half
			tmp[pos[eqivClass]++] = p[i]; // defining new order
		}
		p = move(tmp);
	}

	void n_log_sort(int offset){
		stable_sort(p.begin(), p.end(), [&](int x, int y){
			return r[(x + offset) % n] < r[(y + offset) % n];
		});
	}

  // function for suffix array construction
  // tot cost: n log(n)
  void prepare(const arrayType &_s){
    s = _s; s.push_back(0); 
		n = s.size();
    p = r = vector<int>(n);

		{
			arrayType u = s;
			sort(u.begin(), u.end());
			u.erase(unique(u.begin(), u.end()), u.end());
			for(int i = 0; i < n; ++i){
				// init s[i...] in index i
				int si_id = lower_bound(u.begin(), u.end(), s[i]) - u.begin();
				p[i] = i; r[i] = si_id;
			}
		}

    vector<int> aux(n);
    for(h = 1;; h <<= 1){ // log steps
			for(int j = 1; j >= 0; --j){ 
				// h*j \in {0, h}. used for retriving suffixes halves
				n_alpha_sort(j * h);
				// n_log_sort(j * h);
			}

      // computing new equiv classes
      // if two consecutives substrs in the new order compare diff, 
			// it is a new equiv class
      aux[p[0]] = 0;
      for(int i = 1; i < n; ++i){
        int diff = (r[p[i-1]] < r[p[i]]);
        diff |= (r[p[i-1]] == r[p[i]] && r[(p[i-1]+h)%n] < r[(p[i]+h)%n]);
        aux[p[i]] = aux[p[i-1]] + diff;
      }
      swap(aux, r);

      // if there are already n equiv classes
      if(r[p[n-1]] == n-1) break;
    }
  }

  // finds t. O(|t|*log(n))
  int queryStr(arrayType t){
    if(t.size() > s.size()) return 0;
    else if(t.size() == s.size()) return (t==s? 1 : 0);

    int bigPot = 1; while(bigPot < n) bigPot *= 2;

		// delimiters of current search. indexes of S.A
    int top = 0, bottom = n - 1; 

    int currPos = 0; // current position in t

    for(;currPos < t.size(); currPos++){
      if(s[p[top]+currPos] < t[currPos]){
        // trying to find last substr in SA[top...bottom] such that
        // its char at suffix[currPos] is less than t[currPos]
        int pot = bigPot;
        while(pot){
          int newTop = top + pot;
          if(newTop <= bottom){
             if(p[newTop]+currPos < n){
                if(s[p[newTop]+currPos] < t[currPos]) top = newTop;
             }else top = newTop;
          }
          pot /= 2;
        }
        top++;
      }
      if(top > min(n-1, bottom) || p[top]+currPos >= n || s[p[top]+currPos] != t[currPos]) return 0;
      int pot = bigPot;
      int newBottom = top;
      while(pot){
        int maybeNewBottom = newBottom + pot;
        if(maybeNewBottom <= bottom){
          if(p[maybeNewBottom]+currPos < n){
            if(s[p[maybeNewBottom]+currPos] == t[currPos])
              newBottom = maybeNewBottom;
          }
        }
        pot /= 2;
      }
      bottom = newBottom;
    }
    // return p[top];
    return bottom - top + 1;
  }
};

namespace LCP{
	vector<int> lcp; // lcp[i]: lcp between i-th and (i+1)-th ordered suffix
  vector<vector<int>> st;
  vector<int> vlog;

  // function for calc lcp function
  void prepare_lcp() {
    lcp = vector<int>(SA::n, 0);
    int k = 0;
    for (int i = 0; i < SA::n; i++){
      if (SA::r[i] == SA::n - 1){ // substr on last pos
        lcp[SA::r[i]] = k = 0;
      }else{
        // r[i]: index of suffix s[i...] in order
        // r[i] + 1: id of consecutive suffix after s[i...]
        // p[r[i] + 1]: suffix id of consecutive suffix
        int j = SA::p[SA::r[i] + 1];

        // keep moving k forward
        while(max(i, j) + k < SA::n && SA::s[i+k] == SA::s[j+k])
          k++;

        lcp[SA::r[i]] = k; // setting r[i]'s lcp
        if(k) k--;
      }
    }
  }

  void precalc_st(){
		vlog = {0, 0};
    for(int i = 2; i < MAXN; ++i){
      vlog.push_back(vlog[i/2] + 1);
    }

    st = vector<vector<int>>(MAXN, vector<int>(K));
    for(int i = 0; i < SA::n; ++i) st[i][0] = SA::n - SA::p[i];
    for(int i = 0; i < SA::n; ++i) st[i][1] = lcp[i];

    for(int i = 2; i < K; ++i){
      int j = 0;
      int intvSize = (1 << i);
      while(j + intvSize <= SA::n){
        int lastIntv = i-1;
        int lastIntvSz = (1 << (i-1));

        int a = st[j][lastIntv];
        int b = st[j + lastIntvSz][lastIntv];
        int c = st[j + lastIntvSz - 1][1];
        st[j][i] = min(a, min(b, c));
        j++;
      }
    }
  }

  int query(int l, int r){
    // O(1)
    int interv_size = r - l + 1;
    int j = vlog[interv_size];
    int used_interv_size = (1 << j);

    int ans = min({st[l][j], st[r - used_interv_size + 1][j]});
    return ans;
  }
}
