#include<bits/stdc++.h>
using namespace std;

int inc[100][100];

void dn(int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(inc[i][j]){
                for(int k = 0; k < n; ++k){
                    inc[k][j] = max(inc[k][j], inc[k][i]);
                }
            }
        }
    }
}

int main(){
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int a, b; cin >> a >> b;
        inc[a][b] = 1;
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            printf("%d ", inc[i][j]);
        }
        printf("\n");
    }

    dn(n);

    printf("\n");

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            printf("%d ", inc[i][j]);
        }
        printf("\n");
    }
}
