#include<bits/stdc++.h>
using namespace std;
 
#define int long long

/*
    Fast Walsh Hadamard Transform 
    Works just like a FFT but for bitwise operations such as ^ | &
    O(m*2^m)
    
    (A*B)[k] = sum_(i,j s.t. op(i,j) = k){A[i] * B[j]}  
*/
template<char op, bool inv = false> vector<int> FWHT(vector<int> f) {
	int n = f.size();
	for (int k = 0; (n-1)>>k; k++) for (int i = 0; i < n; i++) if (i>>k&1) {
		int j = i^(1<<k);
		if (op == '^') f[j] += f[i], f[i] = f[j] - 2*f[i];
		if (op == '|') f[i] += (inv ? -1 : 1) * f[j];
		if (op == '&') f[j] += (inv ? -1 : 1) * f[i];
	}
	if (op == '^' and inv) for (auto& i : f) i /= n;
	return f;
}
 
//Outputs the convolution for given operation
template<char op> vector<int> transformed(vector<int> f){
  f = FWHT<op>(f);
  for(auto &x : f) x *= x;
  f = FWHT<op, true>(f);
  return f;
}
 
