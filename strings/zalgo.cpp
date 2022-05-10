struct {
	// this function returns the Z-vector.
	// the Z-vector is defined as: Z[i] says that the string s[0..Z[i]] matches the string s[i..i+Z[i]]
	// the construction of the array is made in O(n)
	// this code was tested with the problem https://codeforces.com/contest/149/problem/E, martian strings
	vector<int> build(const string& s) {
		int n = (int) s.length();
		vector<int> z(n);
		for (int i = 1, l = 0, r = 0; i < n; ++i) {
			if (i <= r)
				z[i] = min (r - i + 1, z[i - l]);
			while (i + z[i] < n && s[z[i]] == s[i + z[i]])
				++z[i];
			if (i + z[i] - 1 > r)
				l = i, r = i + z[i] - 1;
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
