#include<bits/stdc++.h>
using namespace std;
 
#define int long long
#define mp make_pair
 
template<typename T> struct OffsetPq : 
  priority_queue<int,vector<int>,T> {
  int offset = 0;
 
  void push(int x) {
    priority_queue<int,vector<int>, T>::push(x - offset);
  }
 
  int top() {
    return priority_queue<int,vector<int>,T>::top() + offset;
  }
 
  void addToOffset(int x) {
    offset += x;
  }
};
 
struct PiecewiseConvex{
  int a, b; // ax + b
  OffsetPq<less<int>> slopeChangeUntil0;
  OffsetPq<greater<int>> slopeChangeAfter0;
 
  PiecewiseConvex(int _a=0, int _b=0):a(_a), b(_b){}
  
  void merge(PiecewiseConvex &st){
    a += st.a, b += st.b;
 
    auto addToPQs = [&](int x) {
      if(slopeChangeAfter0.size() && slopeChangeAfter0.top() <= x)
        slopeChangeAfter0.push(x);
      else slopeChangeUntil0.push(x);
    };
 
    while(st.slopeChangeUntil0.size()) {
      addToPQs(st.slopeChangeUntil0.top());
      st.slopeChangeUntil0.pop();
    }
    
    while(st.slopeChangeAfter0.size()) {
      addToPQs(st.slopeChangeAfter0.top());
      st.slopeChangeAfter0.pop();
    }
 
    if(a < 0) {
      while(-a > slopeChangeUntil0.size()) {
        int x = slopeChangeAfter0.top();
        slopeChangeAfter0.pop();
        slopeChangeUntil0.push(x);
      }
  
      while(-a < slopeChangeUntil0.size()) {
        int x = slopeChangeUntil0.top();
        slopeChangeUntil0.pop();
        slopeChangeAfter0.push(x);
      }
    } else if(a >= 0) {
      while(slopeChangeUntil0.size()) {
        int x = slopeChangeUntil0.top();
        slopeChangeUntil0.pop();
        slopeChangeAfter0.push(x);
      }
    }
 
  }


 
  void min_pref() {
    a = min(a, 0LL);
    slopeChangeAfter0 = OffsetPq<greater<int>>();
  }
 
  void min_op(int h0, int h1) {
    // f(x) = g(t), t - x <= h0, x - t <= h1
    b += h0 * a;
    slopeChangeUntil0.addToOffset(-h0);
    slopeChangeAfter0.addToOffset(h1);
  }

  
  void print(){
    cout << "PRINT: \n";
    cout << a << " " << b << "\n";
    {
      auto x = slopeChangeUntil0;
      vector<int> v;
      while(x.size()) {
        v.push_back(x.top()); x.pop();
      }
      reverse(v.begin(), v.end());
      for(auto y : v) cout << y << " "; cout << endl;
    }
    {
      auto x = slopeChangeAfter0;
      vector<int> v;
      while(x.size()) {
        v.push_back(x.top()); x.pop();
      }
      for(auto y : v) cout << y << " "; cout << endl;
    }
    cout << "------------------------\n";
  }
};
 
 
PiecewiseConvex buildAbs(int a){
  // builds |a - x|
  PiecewiseConvex st(-1, a);
  st.slopeChangeUntil0.push(a);
  st.slopeChangeAfter0.push(a);
  return st;
}
 
int32_t main(){
cin.tie(NULL)->sync_with_stdio(false);
int t; cin >> t; while(t--) {

  int n, d = 2; cin >> n;
  string s; cin >> s;

  vector<int> v;
  for(int i = 0; i < n; ++i) if(s[i] == '1') {
    v.push_back(i);
  }

  if(v.size() > (n + 1) / 2) {
    cout << "impossible\n";
    continue;
  }

  int left = n - 1 - v.back();

  for(int i = 0; i < v.size(); ++i)
    v[i] -= d * i; 

  // for(auto x : v) cout << x << ", "; cout << endl;
  
  PiecewiseConvex dp = buildAbs(v[0]);
  dp.min_pref();
  // dp.print();
  for(int i = 1; i < v.size(); ++i) {
    // cout << "processing " << i << ": " << v[i] << endl;

    // dp guarda g_{i-1}(x)
 
    PiecewiseConvex transition;
    if(v[i] < 0) {
      transition = PiecewiseConvex(1, -v[i]);
    } else {
      transition = buildAbs(v[i]);
    }
 
    dp.merge(transition);
    dp.min_pref();

    // dp.print();
    // cout << "-----------------------\n";
  }
 
 
  int eval_pt = v.back() + left;
  int sum_b = 0;
  int still_slope = 0;
  while(dp.slopeChangeUntil0.size()) {
    int pt = dp.slopeChangeUntil0.top();
    dp.slopeChangeUntil0.pop();
 
    if(pt <= eval_pt) sum_b += pt;
    else still_slope++;
  }
 
 
  cout << dp.b - sum_b - still_slope * eval_pt << "\n";
}
}
