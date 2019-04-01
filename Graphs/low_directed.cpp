#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000

int idx[MAXN];
int low[MAXN];
int root[MAXN];
vector<int> v[MAXN];
vector<int> temp;

void dfs(int x, int _root, int &t){
    low[x] = idx[x] = t++;
    root[x] = _root;

    temp.push_back(x);

    for(int i = 0; i < v[x].size(); ++i){
        if(!idx[v[x][i]]){
            dfs(v[x][i], _root, t);
            low[x] = min(low[x], low[v[x][i]]);
        }else if(root[x] == root[v[x][i]] && idx[x] > idx[v[x][i]]){
            // primeira condicao: estao na msm arvore
            // segunda condicao: nao eh aresta de avanco
            low[x] = min(low[x], idx[v[x][i]]);
        }
    }

    printf("%d: %d %d\n", x, low[x], idx[x]);
    if(low[x] == idx[x]){
        printf("Componente fortemente conexa: ");
        while(true){
            printf("%d ", temp.back());
            if(temp.back() == x){
                temp.pop_back();
                break;
            }
            temp.pop_back();
        }
        printf("\n");
    }
}

int main(){
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int a, b; cin >> a >> b;
        v[a].push_back(b);
    }

    int t = 0;
    for(int i = 1; i <= n; ++i){
        if(!idx[i]) dfs(i, i, t);
    }

}
