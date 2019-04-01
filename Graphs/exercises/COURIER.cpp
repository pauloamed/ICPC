#include<bits/stdc++.h>
using namespace std;

#define INF 10000000

int dist[101][101];
int pd[101][(1<<13)];

void init(int n){
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            dist[i][j] = INF;
        }
        for(int j = 0; j < (1<<13); ++j){
            pd[i][j] = -1;
        }
    }
}

void fw(int n){
    for (int k = 1; k <= n; k++){
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for(int i = 1; i<= n; ++i) dist[i][i] = 0;
}


int flip_bit(int estado, int i){
    return estado ^ (1<<i);
}

bool get_bit(int estado, int i){
    return (estado >> i) & 1;
}

vector<pair<int,int>> entregas;
int home,n,m;

int solve(int atual, int estado){
    if(pd[atual][estado] == -1){
        if(estado == (1<<entregas.size())-1){
            pd[atual][estado] = dist[atual][home];
        }else{
            int ans = INF, temp;
            for(int i = 0; i < entregas.size(); ++i){
                if(!get_bit(estado, i)){
                    // to em atual
                    // vou pra inicial
                    temp = dist[atual][entregas[i].first] + dist[entregas[i].first][entregas[i].second];
                    ans = min(ans, temp + solve(entregas[i].second, flip_bit(estado, i)));
                }
            }
            pd[atual][estado] = ans;
        }

    }
    return pd[atual][estado];
}



int main(){
    int t; cin >> t;
    while(t--){
        cin >> n >> m >> home;
        init(n);

        int a,b,c;
        for(int i = 0; i < m; ++i){
            cin >> a >> b >> c;
            dist[a][b] = c;
            dist[b][a] = c;
        }

        fw(n);

        int z; cin >> z;
        for(int i = 0; i < z; ++i){
            cin >> a >> b >> c;
            while(c--) entregas.push_back({a,b});
        }

        cout << solve(home, 0) << endl;

        entregas.clear();
    }
}
