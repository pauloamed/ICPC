#include <bits/stdc++.h>
#define debug
using namespace std;

struct {
	// creates d1 and d2
	// D1[i] says that every string (with odd size) of indices from i-D1[i] to i+D1[i] (inclusive) is a palindrome
	// D2[i] says that every string (with even size) of indices from i-D2[i]+1 to i+D2[i] (inclusive) is a palindrome
	// these arrays are built in O(N) where N is the size of str
	vector<int> buildD(string &str, int even){
		vector<int> d(str.size(), 0);
		for(int i = 0, l = 0, r = 0; i < (int)str.size(); i++){
			int ind = r-i-1+even+l;
			assert(i>=r || ind >= 0);
			int k = (i >= r) ? even : max(even, min(r-i-1, d[ind]));
			while(i+k-even < (int)str.size() && i-k >= 0 && str[i+k-even] == str[i-k]) k++;
			d[i] = k-1;
			assert(d[i] >= 0);
			if(i+d[i]-even >= r){
				r = i+d[i]-even;
				l = i-d[i];
			}
		}
		return d;
	}
	
	// counts how many substrings of str are palindromes
	// watch out as this can be very large
	long long run(string &str){
		vector<int> d1 = buildD(str, 0);
		vector<int> d2 = buildD(str, 1);
		long long s = str.size();
		for(auto k : d1) s += k;
		for(auto k : d2) s += k;
		return s;
	}
} manacher;

int main(){
	string str;
	while(cin >> str){
		cout << manacher.run(str) << endl;
	}
}
