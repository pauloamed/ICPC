#include<bits/stdc++.h>
using namespace std;

#define MAXN 100

int vals[MAXN][MAXN];
int dp[MAXN][MAXN];
pair<int,int> pai[MAXN][MAXN];

int solve(int n){
    int temp;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            pai[i][j] = {-1,-1};
            temp = 0;
            if(i != 0){
                // temp = max(temp, dp[i-1][j]);
                if(dp[i-1][j] > temp){
                    pai[i][j] = {i-1,j};
                    temp = dp[i-1][j];
                }
            }
            if(j != 0){
                // temp = max(temp, dp[i][j-1]);
                if(dp[i][j-1] > temp){
                    pai[i][j] = {i,j-1};
                    temp = dp[i][j-1];
                }
            }
            dp[i][j] = temp + vals[i][j];
        }
    }
    return dp[n-1][n-1];
}

int main(){
    int n; cin >> n;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> vals[i][j];
        }
    }
    cout << solve(n) << endl;

    int a=n-1, b=n-1;
    pair<int,int> temp;

    printf("%d ", vals[a][b]);
    while(pai[a][b].first != -1){
        printf("%d ", vals[pai[a][b].first][pai[a][b].second]);
        temp.first = pai[a][b].first;
        temp.second = pai[a][b].second;

        a = temp.first;
        b = temp.second;
    }
    printf("\n");

}
