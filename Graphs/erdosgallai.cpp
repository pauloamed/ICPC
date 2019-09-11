//https://github.com/splucs/Competitive-Programming/blob/master/Macac%C3%A1rio/Graphs/erdosgallai.cpp


// degs[1] >= degs[2] >= ... >= degs[n]
bool erdosgallai(vector<int>& d) {
	sort(d.begin(), d.end(), greater<int>());
	vector<long long> pd(d.size());
	int n = d.size(), p = n-1;
	for(int i = 0; i < n; i++)
		pd[i] = d[i] + (i > 0 ? pd[i-1] : 0);
	for(int k = 1; k <= n; k++) {
		while(p >= 0 && d[p] < k) p--;
		long long sum;
		if (p >= k-1) sum = (p-k+1)*1ll*k + pd[n-1] - pd[p];
		else sum = pd[n-1] - pd[k-1];
		if (pd[k-1] > k*(k-1LL) + sum) return false;
	}
	return pd[n-1] % 2 == 0;
}
