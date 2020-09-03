// https://www.codechef.com/submit/CHSQARR

#include<bits/stdc++.h>
using namespace std;

#define MAXN 1010
#define K 12
#define INF 1e9

int sum[MAXN][MAXN];
int vlog[MAXN];
int st[MAXN][MAXN][K][K];

void precalc(int n, int m){
    vlog[1] = 0; // precalc do log
    for(int i = 2; i <= MAXN; i++) vlog[i] = vlog[i/2] + 1; // precalc do log


    // N ^ 2 * log
    for(int i = 0; i < n; ++i){
        // primeiro faz linha por linha
        for(int k = 1; k < K; ++k){ // para cada tam de intervalo
            int j = 0;
            int interval_size = (1 << k); // tamanho do intervalo def pelo for externo
            while(j + interval_size <= m){ // enquanto o interv. estiver num pos valida
                int last_invert_size = (1 << (k-1)); // recuperando tam do interv anterior

                // calculo o intervalo atual somando as metades
                // uma comecando em j e outra em j+((2^j)/2)
                st[i][j][0][k] = max(st[i][j][0][k-1],  st[i][j + last_invert_size][0][k-1]); // OPERACAO
                j++;
            }
        }
    }

    // N^2 * log ^ 2
    for(int j = 0; j < m; ++j){
        for(int l = 0; l < K; ++l){
            for(int k = 1; k < K; ++k){ // para cada tam de intervalo
                int i = 0;
                int interval_size = (1 << k); // tamanho do intervalo def pelo for externo
                while(i + interval_size <= n){ // enquanto o interv. estiver num pos valida
                    int last_invert_size = (1 << (k-1)); // recuperando tam do interv anterior

                    // calculo o intervalo atual somando as metades
                    // uma comecando em j e outra em j+((2^j)/2)
                    st[i][j][k][l] = max(st[i][j][k-1][l],  st[i + last_invert_size][j][k-1][l]); // OPERACAO
                    i++;
                }
            }
        }
    }
}


int query(int u, int l, int d, int r){
    // O(1)
    int interv_size_hor = r - l + 1; // recuperando o tamanho do intervalo
    int interv_size_ver = d - u + 1; // recuperando o tamanho do intervalo
    int hor = vlog[interv_size_hor]; // recuperando pot que def o tam do interv.
    int ver = vlog[interv_size_ver]; // recuperando pot que def o tam do interv.
    // tamanho de intervalo que vai ser considerado ja que o log eh capado
    int used_interv_size_hor = (1 << hor);
    int used_interv_size_ver = (1 << ver);

    /*
    A----B----
    ----------
    C----D----
    */

    vector<pair<int,int>> points = {
        {u, l},
        {u, r - used_interv_size_hor + 1},
        {d - used_interv_size_ver + 1, l},
        {d - used_interv_size_ver + 1, r - used_interv_size_hor + 1}
    };

    int ans = -INF;
    for(auto x : points){
        ans = max(ans, st[x.first][x.second][ver][hor]);
    }
    return ans;
}

int sumQuery(int u, int l, int d, int r, int n, int m){
    int a = sum[u][l];
    int b = 0; if(r + 1 < m) b = sum[u][r + 1];
    int c = 0; if(d + 1 < n) c = sum[d + 1][l];
    int e = 0; if(r + 1 < m && d + 1 < n) e = sum[d + 1][r + 1];
    return a - (b + c) + e;
}

int32_t main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            scanf("%d", &st[i][j][0][0]);
        }
    }
    precalc(n, m);


    for(int i = n - 1; i >= 0; --i){
        for(int j = m - 1; j >= 0; --j){
            int val = matrix[i][j];
            int a = 0, b = 0, c = 0;
            if(i < n - 1) a = sum[i + 1][j];
            if(j < m - 1) b = sum[i][j + 1];
            if(i < n - 1 && j < m - 1) c = sum[i + 1][j + 1];
            sum[i][j] = a + b - c + val;
        }
    }

    int q; scanf("%d", &q);
    while(q--){
        int ans = INF;
        int a, b; scanf("%d %d", &a, &b);
        for(int i = 0; i + a <= n; ++i){
            for(int j = 0; j + b <= m; ++j){
                // printf("%d\n", query(i, j, i + a - 1, j + b - 1));
                int tot = query(i, j, i + a - 1, j + b - 1) * a * b;
                int sum = sumQuery(i, j, i + a - 1, j + b - 1, n, m);
                // printf("%d\n", tot - sum);
                // if(tot < 0) printf("%d\n", tot);
                ans = min(ans, tot - sum);
            }
        }
        printf("%d\n", ans);
    }
}
