#include<bits/stdc++.h>
using namespace std;

#define MAXN 50
int pd[MAXN][2];

vector<int> v;
int solve(int n){
    pd[0][0] = 0;
    pd[0][1] = v[0];

    int ans = max(pd[0][1], pd[0][0]);

    for(int i = 1; i < v.size(); ++i){

        pd[i][0] = pd[i][1] = v[i];
        for(int j = 0; j < i-1; ++j){
            pd[i][0] = max(pd[i][0], pd[j][0] + v[i]);

            if(i < v.size()-1){
                pd[i][1] = max(pd[i][1], pd[j][1] + v[i]);
            }

        }
        ans = max(ans, pd[i][0]);
        ans = max(ans, pd[i][1]);
        // printf("%d %d %d\n", i, pd[i][0], pd[i][1]);
    }
    return ans;
}

int main(){
    int n, x; cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> x; v.push_back(x);
    }
    cout << solve(n) << endl;
}
