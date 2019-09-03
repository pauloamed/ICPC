#include <bits/stdc++.h>

using namespace std;
struct {
	// this function returns the Z-vector.
	// the Z-vector is defined as: Z[i] says that the string s[0..Z[i]] matches the string s[i..i+Z[i]]
	// the construction of the array is made in O(n)
	vector<int> build(const string &str){
		vector<int> z(str.size(), 0);
		z[0] = str.size();
		int n = str.size();
		for(int i = 1, l = 0, r = 0; i < n; i++){
			assert(r >= l);
			z[i] = i >= r ? 0 : min(z[i-l], r-i-1);
			while(i+z[i] < n && str[i+z[i]] == str[z[i]]) z[i]++;
		}
		return z;
	}
	
	// counts the number of occurrences of p inside s
	// the algorithm runs in O(n)
	int countMatches(const string &s, const string &p){
		vector<int> z = build(p + "$" + s);
		int ans = 0;
		for(auto x : z) ans += (x == (int)p.size());
		return ans;
	}

} zalgo;
int main(){
	string s, p;
	cin >> s >> p;
	cout << zalgo.countMatches(s, p) << endl;
	
}
