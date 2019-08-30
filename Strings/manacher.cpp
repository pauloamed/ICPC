#include <bits/stdc++.h>
#define debug printf
using namespace std;

struct {
	// creates d1 and d2
	// D1[i] says that every string (with odd size) of indices from i-D1[i] to i+D1[i] (inclusive) is a palindrome
	// D2[i] says that every string (with even size) of indices from i-D2[i]+1 to i+D2[i] (inclusive) is a palindrome
	// these arrays are built in O(N) where N is the size of str
	vector<int> buildD(string &str, int even){
		vector<int> d(str.size(), 0);
		for(int i = 0, l = 0, r = 0; i < str.size(); i++){
			int k = (i >= r) ? even : min(r-i-1, d[r-i-1+l-even]);
			while(i+k < str.size() && i-k+even >= 0 && str[i+k] == str[i-k+even]) k++;
			d[i] = --k;
		}
		return d;
	}
	
	// counts how many substrings of str are palindromes
	int run(string &str){
		vector<int> d1 = buildD(str, 0);
		vector<int> d2 = buildD(str, 1);
		int s = str.size();
		for(auto k : d1) s += k;
		for(auto k : d2) s += k;
		return s;
		
	}
} manacher;

int main(){
	string str;
	cin >> str;
	cout << manacher.run(str) << endl;
}
