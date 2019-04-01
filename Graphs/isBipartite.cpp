#include<bits/stdc++.h>
using namespace std;

#define MAXN 100000

vector<int> v[MAXN];
int flag[MAXN];

bool isBipartite(int x, int f){
    flag[x] = f;

    for(int i = 0; i < v[x].size(); ++i){
        if(flag[v[x][i]] == 0) isBipartite(v[x][i], (3-f));
        else if(flag[v[x][i]] == f) return false;
    }

    return true;
}

int main(){
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int a, b; cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }

    isBipartite(0, 1)? printf("Yes\n") : printf("No\n");
}
