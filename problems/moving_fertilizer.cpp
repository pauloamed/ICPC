#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N;
ll fst = 0;                 // value of DP function at 0
priority_queue<ll> points;  // points where DP function changes slope

int main() {
	cin >> N;
	vector<ll> dif(N + 1);
	for (int i = 1; i <= N; ++i) {
		int a, b;
		cin >> a >> b;
		dif[i] = a - b + dif[i - 1];
	}
	assert(dif[N] >= 0);  // assume solution exists
	for (int i = 1; i < N; ++i) {
		if (dif[i] < 0) fst -= dif[i], dif[i] = 0;
		fst += dif[i];
		points.push(dif[i]);
		points.push(dif[i]);
		points.pop();
	}
	while (points.size()) {
		ll a = points.top();
		points.pop();
		fst -= min(a, dif[N]);
	}
	cout << fst << "\n";
}
