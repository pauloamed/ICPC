#include<bits/stdc++.h>
using namespace std;

#define MAXN 200010

vector<int> v[MAXN];
int inCount[MAXN];
int state[MAXN];
int id[MAXN]; // id[x]: pos de x na fila
int currId;

bool solve(int x){
    state[x] = 1;

    bool ans = true;
    for(auto y : v[x]){
        if(state[y] == 0){
            ans &= solve(y);
        }else if(state[y] == 1){
            ans = false;
        }
    }

    state[x] = 2;
    id[x] = currId--;
    return ans;
}

int main(){

    int n, m; cin >> n >> m;
    for(int i = 0; i < n; ++i){
        inCount[i] = 0;
        state[i] = 0;
        v[i].clear();
        id[i] = -1;
    }


    for(int i = 0; i < m; ++i){
        int a, b; cin >> a >> b; a--; b--;
        v[a].push_back(b);
        inCount[b]++;
    }


    currId = n;
    bool ans = true;
    for(int i = 0; i < n; ++i){
        if(inCount[i] == 0 && state[i] == 0){
            ans &= solve(i);
        }
    }

    // checar se todos foram visitados
    int vis = MAXN;
    for(int i = 0; i < n; ++i) vis = min(vis, state[i]);
}
