#include<bits/stdc++.h>
using namespace std;

#define MAXN 100
#define INF 1<<20

vector<int> coins;
int pd[MAXN];
int taken[MAXN];

int solve(int n){
    for(int i = 1; i<=n;++i){
        pd[i] = INF;
        for(int j = 0; j < coins.size(); ++j){
            if(coins[j] <= i && pd[i-coins[j]] + 1 < pd[i]){
                pd[i] = pd[i-coins[j]] + 1;
                taken[i] = coins[j];
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
    while(val){
        printf("%d ", taken[val]);
        val -= taken[val];
    }printf("\n");
}
