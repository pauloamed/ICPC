#include<bits/stdc++.h>
using namespace std;
 
#define int long long
#define mp make_pair

int X, Y, Z;
 
/*
moving fertilizer being able to buy, sell and transfer between adjacents
- f_i(x) = f_(i-1)(x) + |x| (we transfer x from i-1 to i; or contrary if x is neg)
- shift f_i according to A,B (use contraints from i)
- always enforcing the min values of buying and selling in dp
*/

struct{
  // supports:
    // shifting f(x) = f(x +- delta) in O(delta)
    // f(x) = min(f(x), f(x - 1) + A) in O(1)
    // f(x) = min(f(x), f(x + 1) + B) in O(1)
    // adding |x| to f(x)
  
  // we will keep f(x + 1) - f(x) instead of f(x)
  // and two deques, one for x < 0 and other for x >= 0
  
  deque<int> neg, pos;
  int lazy_neg = 0, lazy_pos = 0;

  int f0 = 0;

  void right() { // f(x) = f(x - 1)
    // x from neg goes to pos
    if(neg.empty()) neg.push_back(-Y - lazy_neg);
    int x = neg.front() + lazy_neg; neg.pop_front();
    x = max(x, -Y);
    f0 -= x;
    pos.push_front(x - lazy_pos);
  }

  void left() { // f(x) = f(x + 1)
    // x from pos goes to neg
    if(pos.empty()) pos.push_back(X - lazy_pos);
    int x = pos.front() + lazy_pos; pos.pop_front();
    x = min(x, X);
    f0 += x;
    neg.push_front(x - lazy_neg);
  }

  void add_mod() { // f(x) += |x| * Z
    lazy_neg -= Z;
    lazy_pos += Z;
  }
} slope;
 
int32_t main(){

  int n;
  cin >> n >> X >> Y >> Z;
  // cout << slope.f0 << endl;

  for(int i = 0; i < n; ++i) {
    slope.add_mod();
    int a, b; cin >> a >> b;
    int bal = a - b;

    // cout << bal << endl;

    if(bal < 0) while(bal < 0) slope.left(), bal++;
    else if(bal > 0) while(bal > 0) slope.right(), bal--;

    // cout << slope.f0 << endl;
    // return 0;
    

  }

  cout << slope.f0 << "\n";
}
