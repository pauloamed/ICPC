#include<bits/stdc++.h>
using namespace std;

#define MAXN 1001

int pd[MAXN][2];

vector<int> v;
int solve(int n){
    if(n <= 2) return n;
    else{
        for(int i = 0; i < n; ++i){
            pd[i][0] = pd[i][1] = 1;
            for(int j = 0; j < i; ++j){
                if(v[i] - v[j] < 0){
                    pd[i][0] = max(pd[i][0], pd[j][1]+1);
                }
                else if(v[i] - v[j] > 0){
                    pd[i][1] = max(pd[i][1], pd[j][0]+1);
                }
                // printf("i:%d j:%d pd[i][0]: %d pd[i][1]: %d\n", i,j,pd[i][0],pd[i][1]);
            }
        }
    }
    return max(pd[n-1][0],pd[n-1][1]);
}

int main(){
    int n, x; cin >> n;

    for(int i = 0; i < n; ++i){
        cin >> x; v.push_back(x);
    }
    cout << solve(n) << endl;
}
