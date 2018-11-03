#include<bits/stdc++.h>
using namespace std;

#define MAXN 110000
#define K 25

int logq[MAXN];
void pre_log(){
    logq[1] = 0;
    for (int i = 2; i < MAXN; i++)
        logq[i] = logq[i/2] + 1;
}

int st[MAXN][K];
vector<int> v;

void build(int N){
    for (int i = 0; i < N; i++){
        st[i][0] = v[i];
    }

    for (int j = 1; j <= K; j++){
        for (int i = 0; i + (1 << j) <= N; i++){
            st[i][j] = min(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r){
    int j = logq[r - l + 1];
    return min(st[l][j], st[r - (1 << j) + 1][j]);
}


int main(){
    int n, k, x;
    cin >> n >> k;

    for(int i = 0; i < n; ++i){
        scanf("%d", &x);
        v.push_back(x);
    }

    if(k == 1){
        int menor = v[0];
        for(int i = 0; i < n; ++i){
            menor = min(menor, v[i]);
        }
        cout << menor << endl;
    }else if(k == 2){
        // se tiver na ponta ok
        int maior = v[0];
        int imaior = 0;
        for(int i = 0; i < n; ++i){
            if(v[i] > maior){
                imaior = i;
                maior = v[i];
            }
        }

        if(imaior == 0 || imaior == n-1){
            cout << maior << endl;
        }else{
            build(n);
            int ans = -1e9;
            for(int i = 0; i < n-2; ++i){
                ans = max(ans, max(query(0,i), query(i+1, n-1)));
            }
            cout << ans << endl;
        }
    }else{
        int maior = v[0];
        for(int i = 0; i < n; ++i){
            maior = max(maior, v[i]);
        }
        cout << maior << endl;
    }
}
