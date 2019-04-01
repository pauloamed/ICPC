#include<bits/stdc++.h>
using namespace std;

#define MAXN 100
#define INF 1<<20

vector<int> coins;
int pd[MAXN];

int solve(int n){
    pd[0] = 1;
    for(int i = 1; i<=n;++i){
        pd[i] = 0;
        for(int j = 0; j < coins.size(); ++j){
            if(coins[j] <= i){
                pd[i] += pd[i-coins[j]];
            }
        }
    }
    return pd[n];
}

int main(){
    int n,x; cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> x; coins.push_back(x);
    }

    int val; cin >> val;
    printf("%d\n", solve(val));
}
